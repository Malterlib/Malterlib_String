// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_String_UTF8.h"

namespace NMib::NStr
{
	umint fg_GetExpectedUTF8SequenceLength(uch8 _Char)
	{
		DMibFastCheck((_Char & 0xC0) == 0xC0);
		return 7 - fg_GetHighestBitSetNoZero(((~uint32(_Char)) & 0xFF) | 1u);
	}

	umint fg_GetRequiredUTF8SequenceLength(ch32 _Codepoint)
	{

		if (_Codepoint > 0x3FFFFFF)
			return 6;
		else if (_Codepoint > 0x1FFFFF)
			return 5;
		else if (_Codepoint > 0xFFFF)
			return 4;
		else if (_Codepoint > 0x7FF)
			return 3;
		else if (_Codepoint > 0x7F)
			return 2;
		return 1;
	}

	bool fg_IsUTF16Surrogate(ch32 _Codepoint)
	{
		return (_Codepoint >= 0xD800) && (_Codepoint <= 0xDFFF);
	}

	bool fg_IsOverlongUTF8Sequence(ch32 _Codepoint, umint _Length)
	{
		return _Length > fg_GetRequiredUTF8SequenceLength(_Codepoint);
	}

	bool fg_IsInvalidCodepoint(ch32 _Codepoint, EValidateUTF8Flag _Flags)
	{
		if (_Codepoint > 0x10FFFF)
			return true;

		if (fg_IsSet(_Flags, EValidateUTF8Flag::mc_DisallowNonCharacters))
		{
			if (_Codepoint == 0xFFFE || _Codepoint == 0xFFFF)
				return true;

			if ((_Codepoint & 0xFFFF) == 0xFFFE || (_Codepoint & 0xFFFF) == 0xFFFF)
				return true;
		}

		return false;
	}

	bool fg_IsValidSequence(ch32 _CodePoint, umint _Length, EValidateUTF8Flag _Flags)
	{
		if (fg_IsUTF16Surrogate(_CodePoint))
			return false;

		if (fg_IsInvalidCodepoint(_CodePoint, _Flags))
			return false;

		if (fg_IsOverlongUTF8Sequence(_CodePoint, _Length))
			return false;

		return true;
	}

	template<typename tf_FProcess, typename tf_CString>
	inline_always bool fg_ProcessUTF8(tf_FProcess &&_fFunctor, tf_CString *_pStr, umint _Len, EValidateUTF8Flag _Flags)
	{
		// BOM
		if (_Len >= 3 && _pStr[0] == 0xEF && _pStr[1] == 0xBB && _pStr[2] == 0xBF)
		{
			if (_fFunctor(_pStr, 3, true))
				return false;
			_pStr += 3;
		}
		umint nOneByteCodepointsProcessed = 0;
		tf_CString *pOneByteCodepoints = nullptr;

		auto pEnd = _pStr + _Len;

		while (_pStr < pEnd)
		{
			uch8 ToTest = *_pStr;
			if (ToTest & 0x80)
			{
				if (nOneByteCodepointsProcessed)
				{
					if (_fFunctor(pOneByteCodepoints, nOneByteCodepointsProcessed, true))
						return false;
					pOneByteCodepoints = nullptr;
					nOneByteCodepointsProcessed = 0;
				}

				if (ToTest & 0x40)
				{
					umint SequenceLengthExpected = fg_GetExpectedUTF8SequenceLength(ToTest);
					if (SequenceLengthExpected < 2)
					{
						if (_fFunctor(_pStr, 1, false))
							return false;
						++_pStr;
					}
					else
					{
						tf_CString *pSequenceStart = _pStr;
						umint SequenceLengthParsed = 1;
						++_pStr;

						ch32 CodePoint = ToTest & ((1 << (8 - (SequenceLengthExpected + 1))) - 1);
						while (SequenceLengthParsed < SequenceLengthExpected)
						{
							if (_pStr >= pEnd)
							{
								if (_fFunctor(pSequenceStart, SequenceLengthParsed, false))
									return false;
								break;
							}

							ToTest = *_pStr;
							if ((ToTest & 0xC0) == 0x80)
							{
								CodePoint = (CodePoint << 6) | (ToTest & 0x3F);
								++SequenceLengthParsed;
								++_pStr;
							}
							else
							{
								if (_fFunctor(pSequenceStart, SequenceLengthParsed, false))
									return false;
								break;
							}
						}
						if (SequenceLengthParsed == SequenceLengthExpected)
						{
							bool bValidSequence = fg_IsValidSequence(CodePoint, SequenceLengthParsed, _Flags);
							if (_fFunctor(pSequenceStart, SequenceLengthParsed, bValidSequence))
								return false;
						}
						else if (_pStr >= pEnd)
						{
							if (_fFunctor(pSequenceStart, SequenceLengthParsed, false))
								return false;
						}
					}
				}
				else
				{
					if (_fFunctor(_pStr, 1, false))
						return false;
					++_pStr;
				}
			}
			else
			{
				if (!pOneByteCodepoints)
					pOneByteCodepoints = _pStr;
				++nOneByteCodepointsProcessed;
				++_pStr;
			}
		}

		if (nOneByteCodepointsProcessed)
		{
			if (_fFunctor(pOneByteCodepoints, nOneByteCodepointsProcessed, true))
				return false;
		}

		return true;
	}

	bool fg_IsValidUTF8(ch8 const *_pStr, umint _Len, EValidateUTF8Flag _Flags)
	{
		umint nValidChars = 0;
		bool bReturn = fg_ProcessUTF8
			(
				[&](uch8 const *, umint _Len, bool _bValid) inline_always_lambda -> bool
				{
					nValidChars += _Len;
					return !_bValid;
				}
				, (uch8 *)_pStr
				, _Len
				, _Flags
			)
		;

		if (!bReturn)
			return false;

		return nValidChars == _Len;
	}

	bool fg_IsValidUTF8(CStr const &_Str, EValidateUTF8Flag _Flags)
	{
		return fg_IsValidUTF8(_Str.f_GetStr(), _Str.f_GetLen(), _Flags);
	}

	CStr fg_ReplaceCharactersUTF8(CStr const &_Str, EValidateUTF8Flag _Flags, uch8 _ReplacementChar)
	{
		CStr StringCopy = _Str;
		uch8* pStr = (uch8*)StringCopy.f_GetStrUniqueWritable();

		fg_ProcessUTF8
			(
				[&](uch8* pStr, umint _Length, bool _bValid) inline_always_lambda -> bool
				{
					if (!_bValid)
					{
						while (_Length)
						{
							*pStr = _ReplacementChar;
							++pStr;
							--_Length;
						}
					}
					return false;
				}
				, pStr
				, _Str.f_GetLen()
				, _Flags
			)
		;
		return StringCopy;
	}

	CStr fg_ReplaceSequenceUTF8(CStr const &_Str, EValidateUTF8Flag _Flags, CStr const &_ReplacementChar)
	{
		CStr Replacement = _ReplacementChar;

		CStr Destination;
		aint Length = 0;
		Destination.f_CreateWritableBuffer(_Str.f_GetStrLen(), true);

		fg_ProcessUTF8
			(
				[&](uch8* _pStr, umint _Length, bool _bValid) inline_always_lambda -> bool
				{
					if (_bValid)
					{
						CStr::CAddStrAgrs Args(Length, _Length);
						Destination.f_AddStrLengthAware(Args, (ch8 const *)_pStr);
					}
					else
					{
						CStr::CAddStrAgrs Args(Length, Replacement.f_GetLen());
						Destination.f_AddStrLengthAware(Args, Replacement.f_GetStr());
					}
					return false;
				}
				, (uch8*)_Str.f_GetStr()
				, _Str.f_GetLen()
				, _Flags
			)
		;
		Destination.f_SetStrLen(Length);
		return Destination;
	}

	CStr fg_CleanUTF8(CStr const &_String, EValidateUTF8Flag _Flags)
	{
		if (fg_IsValidUTF8(_String, _Flags))
			return _String;
		else
			return fg_ReplaceSequenceUTF8(_String, _Flags);
	}
}
