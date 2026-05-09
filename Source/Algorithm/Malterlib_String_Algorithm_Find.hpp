// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint  fg_StrFindChar(tf_CData1 const *_pStr1, tf_CData2 _Char)
	{
		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStr1 = (CChar1 const *)_pStr1;
		NTraits::TCUnsigned<tf_CData2> Char = _Char;

		while (*pStr1)
		{
			if (*pStr1 == Char)
				return pStr1 - (CChar1 const *)_pStr1;

			++pStr1;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharNoCase(tf_CData1 const *_pStr1, tf_CData2 _Char)
	{
		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStr1 = (CChar1 const *)_pStr1;
		NTraits::TCUnsigned<tf_CData2> Char = fg_CharLowerCase(_Char);

		while (*pStr1)
		{
			if (fg_CharLowerCase(*pStr1) == Char)
				return pStr1 - (CChar1 const *)_pStr1;

			++pStr1;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverse(tf_CData1 const *_pStr1, tf_CData2 _Char)
	{
		if (!(*_pStr1))
			return -1;

		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStr1 = (CChar1 const *)_pStr1;
		NTraits::TCUnsigned<tf_CData2> Char = _Char;

		// Find end
		while (*pStr1)
		{
			++pStr1;
		}
		--pStr1;

		while (pStr1 >= (CChar1 const *)_pStr1)
		{
			if (*pStr1 == Char)
				return pStr1 - (CChar1 const *)_pStr1;

			--pStr1;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 _Char)
	{
		if (!(*_pStr1))
			return -1;

		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStr1 = (CChar1 const *)_pStr1;
		NTraits::TCUnsigned<tf_CData2> Char = fg_CharLowerCase(_Char);

		// Find end
		while (*pStr1)
		{
			++pStr1;
		}
		--pStr1;

		while (pStr1 >= (CChar1 const *)_pStr1)
		{
			if (fg_CharLowerCase(*pStr1) == Char)
				return pStr1 - (CChar1 const *)_pStr1;

			--pStr1;
		}
		return -1;
	}

	template <bool t_bNoCase, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverseLengthAware(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _Len)
	{
		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		using CChar2 = NTraits::TCUnsigned<tf_CData2>;
		CChar1 const *pStr1 = (CChar1 const *)_pStr1;
		CChar2 Char;
		if constexpr (t_bNoCase)
			Char = fg_CharLowerCase(_Char);
		else
			Char = _Char;

		for (umint iChar = _Len; iChar > 0; --iChar)
		{
			CChar1 StrChar = pStr1[iChar - 1];
			if constexpr (t_bNoCase)
				StrChar = fg_CharLowerCase(StrChar);

			if (StrChar == Char)
				return iChar - 1;
		}

		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChar(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _MaxLen)
	{
		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStr1 = (CChar1 const *)_pStr1;
		NTraits::TCUnsigned<tf_CData2> Char = _Char;
		CChar1 const *pStr1End = (CChar1 const *)(_pStr1 + _MaxLen);

		while (pStr1 < pStr1End && *pStr1)
		{
			if (*pStr1 == Char)
				return pStr1 - (CChar1 const *)_pStr1;

			++pStr1;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharNoCase(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _MaxLen)
	{
		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStr1 = (CChar1 const *)_pStr1;
		NTraits::TCUnsigned<tf_CData2> Char = fg_CharLowerCase(_Char);
		CChar1 const *pStr1End = (CChar1 const *)(_pStr1 + _MaxLen);

		while (pStr1 < pStr1End && *pStr1)
		{
			if (fg_CharLowerCase(*pStr1) == Char)
				return pStr1 - (CChar1 const *)_pStr1;

			++pStr1;
		}
		return -1;
	}

	template <bool t_bNoCase, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharLengthAware(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _Len)
	{
		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStr1 = (CChar1 const *)_pStr1;
		NTraits::TCUnsigned<tf_CData2> Char = _Char;
		if constexpr (t_bNoCase)
			Char = fg_CharLowerCase(Char);

		for (umint iChar = 0; iChar < _Len; ++iChar)
		{
			if constexpr (t_bNoCase)
			{
				if (fg_CharLowerCase(pStr1[iChar]) == Char)
					return iChar;
			}
			else
			{
				if (pStr1[iChar] == Char)
					return iChar;
			}
		}

		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverse(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _MaxLen)
	{
		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStartPos = (CChar1 const *)_pStr1;
		CChar1 const *pCurPos = pStartPos;

		while (umint(pCurPos - pStartPos) < _MaxLen && *pCurPos)
			++pCurPos;

		return fg_StrFindCharReverseLengthAware<false>(_pStr1, _Char, pCurPos - pStartPos);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _MaxLen)
	{
		using CChar1 = NTraits::TCUnsigned<tf_CData1>;
		CChar1 const *pStartPos = (CChar1 const *)_pStr1;
		CChar1 const *pCurPos = pStartPos;

		while (umint(pCurPos - pStartPos) < _MaxLen && *pCurPos)
			++pCurPos;

		return fg_StrFindCharReverseLengthAware<true>(_pStr1, _Char, pCurPos - pStartPos);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChars(tf_CData1 const *_pStr1, tf_CData2 const *_pChars)
	{
		tf_CData1 const *pChar = _pStr1;
		while (*pChar)
		{
			if (fg_StrFindChar(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			++pChar;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChars(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pChars)
	{
		tf_CData1 const *pChar = _pStr1;
		tf_CData1 const *pEnd = _pStr1 + _Len;
		while (pChar < pEnd && *pChar)
		{
			if (fg_StrFindChar(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			++pChar;
		}
		return -1;
	}

	template <bool t_bNoCase, bool t_bReverse, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsLengthAware(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pChars, umint _CharsLen)
	{
		if (_Len == 0 || _CharsLen == 0)
			return -1;

		auto fMatches = [&](auto _Char)
			{
				for (umint iChar = 0; iChar < _CharsLen; ++iChar)
				{
					if constexpr (t_bNoCase)
					{
						if (fg_CharLowerCase(_Char) == fg_CharLowerCase(_pChars[iChar]))
							return true;
					}
					else
					{
						if (_Char == _pChars[iChar])
							return true;
					}
				}
				return false;
			}
		;

		if constexpr (t_bReverse)
		{
			for (umint iSource = _Len; iSource > 0; --iSource)
			{
				if (fMatches(_pStr1[iSource - 1]))
					return iSource - 1;
			}
		}
		else
		{
			for (umint iSource = 0; iSource < _Len; ++iSource)
			{
				if (fMatches(_pStr1[iSource]))
					return iSource;
			}
		}

		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChars(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pChars, umint _CharsLen)
	{
		return fg_StrFindCharsLengthAware<false, false>(_pStr1, _Len, _pChars, _CharsLen);
	}

	template <bool t_bNoCase, bool t_bReverse, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsLengthAware(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pChars)
	{
		return fg_StrFindCharsLengthAware<t_bNoCase, t_bReverse>(_pStr1, _Len, _pChars, fg_StrLen(_pChars));
	}

	template <bool t_bNoCase, bool t_bReverse, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsNullTerminatedLengthAware(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen, umint _CharsLen)
	{
		if (_CharsLen == 0)
			return -1;

		if constexpr (!t_bReverse)
		{
			for (umint iChar = 0; iChar < _MaxLen && _pStr1[iChar]; ++iChar)
			{
				for (umint iFindChar = 0; iFindChar < _CharsLen; ++iFindChar)
				{
					if constexpr (t_bNoCase)
					{
						if (fg_CharLowerCase(_pStr1[iChar]) == fg_CharLowerCase(_pChars[iFindChar]))
							return iChar;
					}
					else
					{
						if (_pStr1[iChar] == _pChars[iFindChar])
							return iChar;
					}
				}
			}

			return -1;
		}

		umint Len = 0;
		while (Len < _MaxLen && _pStr1[Len])
			++Len;

		return fg_StrFindCharsLengthAware<t_bNoCase, t_bReverse>(_pStr1, Len, _pChars, _CharsLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChars(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen, umint _CharsLen)
	{
		return fg_StrFindCharsNullTerminatedLengthAware<false, false>(_pStr1, _pChars, _MaxLen, _CharsLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars)
	{
		tf_CData1 const *pChar = _pStr1;
		while (*pChar)
		{
			if (fg_StrFindCharNoCase(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			++pChar;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsNoCase(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pChars, umint _CharsLen)
	{
		return fg_StrFindCharsLengthAware<true, false>(_pStr1, _Len, _pChars, _CharsLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen, umint _CharsLen)
	{
		return fg_StrFindCharsNullTerminatedLengthAware<true, false>(_pStr1, _pChars, _MaxLen, _CharsLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pChars)
	{
		tf_CData1 const *pChar = _pStr1 + fg_StrLen(_pStr1) - 1;
		while (pChar >= _pStr1)
		{
			if (fg_StrFindChar(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			--pChar;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverse(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pChars, umint _CharsLen)
	{
		return fg_StrFindCharsLengthAware<false, true>(_pStr1, _Len, _pChars, _CharsLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen, umint _CharsLen)
	{
		return fg_StrFindCharsNullTerminatedLengthAware<false, true>(_pStr1, _pChars, _MaxLen, _CharsLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars)
	{
		tf_CData1 const *pChar = _pStr1 + fg_StrLen(_pStr1) - 1;
		while (*pChar)
		{
			if (fg_StrFindCharNoCase(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			++pChar;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverseNoCase(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pChars, umint _CharsLen)
	{
		return fg_StrFindCharsLengthAware<true, true>(_pStr1, _Len, _pChars, _CharsLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen, umint _CharsLen)
	{
		return fg_StrFindCharsNullTerminatedLengthAware<true, true>(_pStr1, _pChars, _MaxLen, _CharsLen);
	}


	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChars(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen)
	{
		tf_CData1 const *pChar = _pStr1;
		tf_CData1 const *pCharEnd = _pStr1 + _MaxLen;
		while (pChar < pCharEnd && *pChar)
		{
			if (fg_StrFindChar(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			++pChar;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen)
	{
		tf_CData1 const *pChar = _pStr1;
		tf_CData1 const *pCharEnd = _pStr1 + _MaxLen;
		while (pChar < pCharEnd && *pChar)
		{
			if (fg_StrFindCharNoCase(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			++pChar;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen)
	{
		tf_CData1 const *pChar = _pStr1 + fg_StrLen(_pStr1, _MaxLen) - 1;
		while (pChar >= _pStr1)
		{
			if (fg_StrFindChar(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			--pChar;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen)
	{
		tf_CData1 const *pChar = _pStr1 + fg_StrLen(_pStr1, _MaxLen) - 1;
		while (pChar >= _pStr1)
		{
			if (fg_StrFindCharNoCase(_pChars, *pChar) >= 0)
				return pChar - _pStr1;
			--pChar;
		}
		return -1;
	}

	template <bool tf_bNoCase, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindIterator(tf_CData1 &_Str1, tf_CData2 &_Str2)
	{
		using CData1 = tf_CData1;
		using CData2 = tf_CData2;
		CData1 Str1Start = _Str1;
		CData1 Str1 = Str1Start;
		CData2 Str2 = _Str2;

		while (Str1)
		{
			CData1 Str1Current = Str1;
			CData2 Str2Current = Str2;
			while (1)
			{
				ch32 Data1 = 0;
				ch32 Data2 = 0;
				if constexpr (tf_bNoCase)
				{
					Data1 = fg_CharLowerCase(*Str1Current);
					Data2 = fg_CharLowerCase(*Str2Current);
				}
				else
				{
					Data1 = *Str1Current;
					Data2 = *Str2Current;
				}
				if (Data1 != Data2)
					break;
				++Str1Current;
				++Str2Current;
				if (!(Str2Current))
					return Str1 - Str1Start;
				if (!(Str1Current))
					return -1;
			}

			++Str1;
		}
		return -1;
	}

	template <bool tf_bNoCase, bool tf_bCheckLen, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFind(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		CData1 const *pStr1Start = (CData1 const *)_pStr1;
		CData1 const *pStr1 = pStr1Start;
		CData1 const *pStr1End = pStr1Start + _Len;
		CData2 const *pStr2 = (CData2 const *)_pStr2;

		while (*pStr1)
		{
			if constexpr (tf_bCheckLen)
			{
				if (pStr1 >= pStr1End)
					return -1;
			}

			CData1 const *pStr1Current = pStr1;
			CData2 const *pStr2Current = pStr2;
			while (1)
			{
				CData1 Data1;
				CData2 Data2;
				if constexpr (tf_bNoCase)
				{
					Data1 = fg_CharLowerCase(*pStr1Current);
					Data2 = fg_CharLowerCase(*pStr2Current);
				}
				else
				{
					Data1 = *pStr1Current;
					Data2 = *pStr2Current;
				}
				if (Data1 != Data2)
					break;
				++pStr1Current;
				++pStr2Current;
				if (!(*pStr2Current))
					return pStr1 - pStr1Start;
				if constexpr (tf_bCheckLen)
				{
					if (pStr1Current >= pStr1End)
						return -1;
				}
				if (!(*pStr1Current))
					return -1;
			}

			++pStr1;
		}
		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_small aint fg_StrFind(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		return fg_StrFind<false, false>(_pStr1, _pStr2, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_small aint fg_StrFindNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		return fg_StrFind<true, false>(_pStr1, _pStr2, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_small aint fg_StrFind(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen)
	{
		return fg_StrFind<false, true>(_pStr1, _pStr2, _MaxLen);
	}

	template <bool t_bNoCase, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindLengthAware(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pStr2, umint _FindLen)
	{
		if (_FindLen == 0)
			return -1;
		if (_FindLen > _Len)
			return -1;

		for (umint iSource = 0; iSource <= _Len - _FindLen; ++iSource)
		{
			if (fg_StrStartsWith<t_bNoCase, true, true, true, true>(_pStr1 + iSource, _pStr2, _Len - iSource, _FindLen))
				return iSource;
		}

		return -1;
	}

	template <bool t_bNoCase, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindLengthAware(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pStr2)
	{
		umint FindLen = fg_StrLen(_pStr2);
		return fg_StrFindLengthAware<t_bNoCase>(_pStr1, _Len, _pStr2, FindLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFind(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pStr2, umint _FindLen)
	{
		return fg_StrFindLengthAware<false>(_pStr1, _Len, _pStr2, _FindLen);
	}

	template <bool t_bNoCase, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindNullTerminatedLengthAware(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen, umint _FindLen)
	{
		if (_FindLen == 0)
			return -1;

		for (umint iSource = 0; iSource < _MaxLen && _pStr1[iSource]; ++iSource)
		{
			umint MaxLen = _MaxLen == TCLimitsInt<umint>::mc_Max ? TCLimitsInt<umint>::mc_Max : _MaxLen - iSource;

			if (fg_StrStartsWith<t_bNoCase, true, false, true, true>(_pStr1 + iSource, _pStr2, MaxLen, _FindLen))
				return iSource;
		}

		return -1;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFind(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen, umint _FindLen)
	{
		return fg_StrFindNullTerminatedLengthAware<false>(_pStr1, _pStr2, _MaxLen, _FindLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_small aint fg_StrFindNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen)
	{
		return fg_StrFind<true, true>(_pStr1, _pStr2, _MaxLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindNoCase(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pStr2, umint _FindLen)
	{
		return fg_StrFindLengthAware<true>(_pStr1, _Len, _pStr2, _FindLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen, umint _FindLen)
	{
		return fg_StrFindNullTerminatedLengthAware<true>(_pStr1, _pStr2, _MaxLen, _FindLen);
	}

	template <bool tf_bNoCase, bool tf_bHasLen, bool tf_bHasFindLen, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _FindLen)
	{
		if constexpr (!tf_bHasLen)
		{
			if (!(*_pStr1))
				return -1;
		}
		if constexpr (!tf_bHasFindLen)
		{
			if (!(*_pStr2))
				return -1;
		}

		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		CData1 const *pStr1 = (CData1 const *)_pStr1;
		CData1 const *pStr1Start = (CData1 const *)_pStr1;
		CData2 const *pStr2Start = (CData2 const *)_pStr2;
		CData2 const *pStr2End = (CData2 const *)_pStr2;

		if constexpr (tf_bHasFindLen)
		{
			if (_FindLen == 0)
				return -1;
			if constexpr (tf_bHasLen)
			{
				if (_FindLen > _Len)
					return -1;
			}
			pStr2End += _FindLen - 1;
		}
		else
		{
			// Find end of search pattern
			while (*pStr2End)
				++pStr2End;
			--pStr2End;
		}

		if constexpr (tf_bHasLen)
		{
			if (_Len == 0)
				return -1;
			pStr1 += _Len - 1;
		}
		else
		{
			// Find end of string
			while (*pStr1)
				++pStr1;
			--pStr1;
		}

		// Search backward from pStr1 to pStr1Start
		while (pStr1 >= pStr1Start)
		{
			CData1 const *pStr1Current = pStr1;
			CData2 const *pStr2Current = pStr2End;
			while (1)
			{
				CData1 Data1;
				CData2 Data2;
				if constexpr (tf_bNoCase)
				{
					Data1 = fg_CharLowerCase(*pStr1Current);
					Data2 = fg_CharLowerCase(*pStr2Current);
				}
				else
				{
					Data1 = *pStr1Current;
					Data2 = *pStr2Current;
				}

				if (Data1 != Data2)
					break;

				if (pStr2Current == pStr2Start)
					return pStr1Current - pStr1Start;

				if (pStr1Current == pStr1Start)
					return -1;

				--pStr1Current;
				--pStr2Current;
			}

			--pStr1;
		}

		return -1;
	}

	// Returns first character for searched string
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		return fg_StrFindReverse<false, false, false>(_pStr1, _pStr2, 0, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		return fg_StrFindReverse<true, false, false>(_pStr1, _pStr2, 0, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len)
	{
		return fg_StrFindReverse<false, true, false>(_pStr1, _pStr2, _Len, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len)
	{
		return fg_StrFindReverse<true, true, false>(_pStr1, _pStr2, _Len, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _FindLen)
	{
		return fg_StrFindReverse<false, true, true>(_pStr1, _pStr2, _Len, _FindLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _FindLen)
	{
		return fg_StrFindReverse<true, true, true>(_pStr1, _pStr2, _Len, _FindLen);
	}

	template <bool tf_bNoCase, bool tf_bCheckLen, bool tf_bAuthoritativeLen, bool tf_bCheckLen2, bool tf_bAuthoritativeLen2, typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		auto *pStr1 = _pStr1;
		tf_CData1 const *pStr1End;
		if constexpr (tf_bCheckLen)
		{
			if (_Len == TCLimitsInt<umint>::mc_Max)
				pStr1End = (tf_CData1 const *)TCLimitsInt<umint>::mc_Max;
			else
				pStr1End = pStr1 + _Len;
		}

		auto *pStr2 = _pStr2;
		tf_CData2 const *pStr2End;
		if constexpr (tf_bCheckLen2)
		{
			if (_Len2 == TCLimitsInt<umint>::mc_Max)
				pStr2End = (tf_CData2 const *)TCLimitsInt<umint>::mc_Max;
			else
				pStr2End = pStr2 + _Len2;
		}

		while (true)
		{
			if constexpr (tf_bCheckLen)
			{
				if (pStr1 >= pStr1End)
					break;
			}
			if constexpr (tf_bCheckLen2)
			{
				if (pStr2 >= pStr2End)
					break;
			}

			if constexpr (!tf_bAuthoritativeLen)
			{
				if (!(*pStr1))
					break;
			}
			if constexpr (!tf_bAuthoritativeLen2)
			{
				if (!(*pStr2))
					break;
			}

			CData1 Data1 = 0;
			CData2 Data2 = 0;
			if constexpr (tf_bNoCase)
			{
				Data1 = fg_CharLowerCase(CData1(*pStr1));
				Data2 = fg_CharLowerCase(CData2(*pStr2));
			}
			else
			{
				Data1 = *pStr1;
				Data2 = *pStr2;
			}

			if (Data1 != Data2)
				break;

			++pStr1;
			++pStr2;

		}

		if constexpr (tf_bCheckLen2)
		{
			if (pStr2 >= pStr2End)
				return true;
		}

		if constexpr (tf_bAuthoritativeLen2)
			return false;

		return *pStr2 == 0;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		return fg_StrStartsWith<false, false, false, false, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, 0, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		return fg_StrStartsWith<true, false, false, false, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, 0, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len)
	{
		return fg_StrStartsWith<false, true, false, false, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, _Len, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2)
	{
		return fg_StrStartsWith<false, true, false, true, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, _Len, _Len2);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len)
	{
		return fg_StrStartsWith<true, true, false, false, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, _Len, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2)
	{
		return fg_StrStartsWith<true, true, false, true, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, _Len, _Len2);
	}

	template <bool tf_bNoCase, bool tf_bCheckLen, bool tf_bAuthoritativeLen, bool tf_bCheckLen2, bool tf_bAuthoritativeLen2, typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		CData1 const *pStr1Start = (CData1 const *)_pStr1;

		CData1 const *pStr1End = pStr1Start;
		if constexpr (tf_bCheckLen)
		{
			if constexpr (tf_bAuthoritativeLen)
				pStr1End = pStr1Start + _Len;
			else
			{
				for (umint iChar = 0; iChar < _Len && *pStr1End; ++iChar)
					++pStr1End;
			}
		}
		else
		{
			while (*pStr1End)
				++pStr1End;
		}


		CData2 const *pStr2Start = (CData2 const *)_pStr2;

		CData2 const *pStr2End = pStr2Start;
		if constexpr (tf_bCheckLen2)
		{
			if constexpr (tf_bAuthoritativeLen2)
				pStr2End = pStr2Start + _Len2;
			else
			{
				for (umint iChar = 0; iChar < _Len2 && *pStr2End; ++iChar)
					++pStr2End;
			}
		}
		else
		{
			while (*pStr2End)
				++pStr2End;
		}

		if (pStr2End == pStr2Start)
			return true;
		if (pStr1End == pStr1Start)
			return false;

		CData1 const *pStr1 = pStr1End - 1;
		CData2 const *pStr2 = pStr2End - 1;

		while (pStr1 >= pStr1Start && pStr2 >= pStr2Start)
		{
			CData1 Data1;
			CData2 Data2;
			if constexpr (tf_bNoCase)
			{
				Data1 = fg_CharLowerCase(*pStr1);
				Data2 = fg_CharLowerCase(*pStr2);
			}
			else
			{
				Data1 = *pStr1;
				Data2 = *pStr2;
			}

			if (Data1 != Data2)
				return false;

			--pStr1;
			--pStr2;
		}

		return pStr2 < pStr2Start;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		return fg_StrEndsWith<false, false, false, false, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, 0, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		return fg_StrEndsWith<true, false, false, false, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, 0, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len)
	{
		return fg_StrEndsWith<false, true, false, false, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, _Len, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2)
	{
		return fg_StrEndsWith<false, true, false, true, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, _Len, _Len2);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len)
	{
		return fg_StrEndsWith<true, true, false, false, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, _Len, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2)
	{
		return fg_StrEndsWith<true, true, false, true, false, tf_CData1, tf_CData2>(_pStr1, _pStr2, _Len, _Len2);
	}
}
