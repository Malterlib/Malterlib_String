// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_String_Algorithm.h"

namespace NMib::NStr
{
	ch8 *fg_StrUpperCase(ch8 *_pStr)
	{
		return fg_StrUpperCase(_pStr, fg_StrLen(_pStr));
	}

	ch8 *fg_StrUpperCase(ch8 *_pStr, umint _MaxLen)
	{
		CStrIteratorUTF8 iStr{_pStr, _MaxLen};

		ch8 *pLast = _pStr;

		auto fSetChar = [&](ch32 _Char)
			{
#if DMibEnableSafeCheck > 0
				ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
#endif

				fg_EncodeUTF8Char<false>
					(
						_Char
						, [&](umint _nChars)
						{
							DMibFastCheck(_nChars == (pNext - pLast));
							return pLast;
						}
					)
				;
			}
		;

		while (iStr)
		{
			ch32 Char = *iStr;
			if (Char >= 'a' && Char <= 'z')
			{
				Char -= 0x20;
				fSetChar(Char);
			}
			else if (Char >= 0xe0u && Char <= 0xfeu && Char != 0xf7u)
			{
				Char -= 0x20;
				fSetChar(Char);
			}
			ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
			++iStr;
			pLast = pNext;
		}

		return _pStr;
	}

	ch8 *fg_StrUpperCase(ch8 *_pDest, umint _MaxDestLen, ch8 const *_pSource)
	{
		return fg_StrUpperCase(_pDest, _MaxDestLen, _pSource, fg_StrLen(_pSource));
	}

	ch8 *fg_StrUpperCase(ch8 *_pDest, umint _MaxDestLen, ch8 const *_pSource, umint _SourceLen)
	{
		CStrIteratorUTF8 iStr{_pSource, _SourceLen};

		ch8 *pOutput = _pDest;
		ch8 *pOutputEnd = _pDest + _MaxDestLen - 1;

		auto fAddChar = [&](ch32 _Char)
			{
				return fg_EncodeUTF8Char<true>
					(
						_Char
						, [&](umint _nChars) -> ch8 *
						{
							if (_nChars > umint(pOutputEnd - pOutput))
								return nullptr;
							auto pRet = pOutput;
							pOutput += _nChars;
							return pRet;
						}
					)
				;
			}
		;

		while (iStr)
		{
			ch32 Char = *iStr;
			if (Char >= 'a' && Char <= 'z')
				Char -= 0x20;
			if (Char >= 0xe0u && Char <= 0xfeu && Char != 0xf7u)
				Char -= 0x20;

			if (!fAddChar(Char))
				break;
			++iStr;
		}

		*pOutput = 0;

		return _pDest;
	}

	ch8 *fg_StrUpperCase(ch8 *_pDest, ch8 const *_pSource, umint _SourceLen)
	{
		return fg_StrUpperCase(_pDest, _SourceLen + 1, _pSource, _SourceLen);
	}

	ch8 *fg_StrLowerCase(ch8 *_pStr)
	{
		return fg_StrLowerCase(_pStr, fg_StrLen(_pStr));
	}

	ch8 *fg_StrLowerCase(ch8 *_pStr, umint _MaxLen)
	{
		CStrIteratorUTF8 iStr{_pStr, _MaxLen};

		ch8 *pLast = _pStr;

		auto fSetChar = [&](ch32 _Char)
			{
#if DMibEnableSafeCheck > 0
				ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
#endif

				fg_EncodeUTF8Char<false>
					(
						_Char
						, [&](umint _nChars)
						{
							DMibFastCheck(_nChars == (pNext - pLast));
							return pLast;
						}
					)
				;
			}
		;

		while (iStr)
		{
			ch32 Char = *iStr;
			if (Char >= 'A' && Char <= 'Z')
			{
				Char += 'a' - 'A';
				fSetChar(Char);
			}
			else if (Char >= 0xc0u && Char <= 0xdeu && Char != 0xd7u)
			{
				Char += 0xe0u - 0xc0u;
				fSetChar(Char);
			}
			ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
			++iStr;
			pLast = pNext;
		}

		return _pStr;
	}

	ch8 *fg_StrLowerCase(ch8 *_pDest, umint _MaxDestLen, ch8 const *_pSource, umint _SourceLen)
	{
		CStrIteratorUTF8 iStr{_pSource, _SourceLen};

		ch8 *pOutput = _pDest;
		ch8 *pOutputEnd = _pDest + _MaxDestLen - 1;

		auto fAddChar = [&](ch32 _Char)
			{
				return fg_EncodeUTF8Char<true>
					(
						_Char
						, [&](umint _nChars) -> ch8 *
						{
							if (_nChars > umint(pOutputEnd - pOutput))
								return nullptr;
							auto pRet = pOutput;
							pOutput += _nChars;
							return pRet;
						}
					)
				;
			}
		;

		while (iStr)
		{
			ch32 Char = *iStr;
			if (Char >= 'A' && Char <= 'Z')
				Char += 'a' - 'A';
			if (Char >= 0xc0u && Char <= 0xdeu && Char != 0xd7u)
				Char += 0xe0u - 0xc0u;

			if (!fAddChar(Char))
				break;
			++iStr;
		}

		*pOutput = 0;

		return _pDest;
	}

	ch8 *fg_StrLowerCase(ch8 *_pDest, umint _MaxDestLen, ch8 const *_pSource)
	{
		return fg_StrLowerCase(_pDest, _MaxDestLen, _pSource, fg_StrLen(_pSource));
	}

	ch8 *fg_StrLowerCase(ch8 *_pDest, ch8 const *_pSource, umint _SourceLen)
	{
		return fg_StrLowerCase(_pDest, _SourceLen + 1, _pSource, _SourceLen);
	}

	ch8 *fg_StrCapitalize(ch8 *_pStr)
	{
		CStrIteratorUTF8 iStr{_pStr, fg_StrLen(_pStr)};

		ch8 *pLast = _pStr;

		auto fSetChar = [&](ch32 _Char)
			{
#if DMibEnableSafeCheck > 0
				ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
#endif

				fg_EncodeUTF8Char<false>
					(
						_Char
						, [&](umint _nChars)
						{
							DMibFastCheck(_nChars == (pNext - pLast));
							return pLast;
						}
					)
				;
			}
		;

		if (iStr)
		{
			ch32 Char = *iStr;
			if (Char >= 'a' && Char <= 'z')
			{
				Char -= 0x20;
				fSetChar(Char);
			}
			else if (Char >= 0xe0u && Char <= 0xfeu && Char != 0xf7u)
			{
				Char -= 0x20;
				fSetChar(Char);
			}
		}
		return _pStr;
	}
}
