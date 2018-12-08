// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>
#include "Malterlib_String_Algorithm.h"

namespace NMib::NStr
{
	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Upper case																						|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/


	ch8 *fg_StrUpperCase(ch8 *_pStr)
	{
		return fg_StrUpperCase(_pStr, fg_StrLen(_pStr));
	}

	ch8 *fg_StrUpperCase(ch8 *_pStr, mint _MaxLen)
	{
		ch32 UpperComapre = 0xffu;
		CStrIteratorUTF8 iStr{_pStr, _MaxLen};

		ch8 *pLast = _pStr;

		auto fSetChar = [&](ch32 _Char)
			{
#if DMibEnableSafeCheck > 0
				ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
#endif

				fg_EncodeUTF8Char
					(
						_Char
						, [&](mint _nChars)
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
				Char -= 'a' - 'A';
				fSetChar(Char);
			}
			else if (Char >= 0xe0u && Char <= UpperComapre)
			{
				Char -= 0xe0u - 0xc0u;
				fSetChar(Char);
			}
			ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
			++iStr;
			pLast = pNext;
		}

		return _pStr;
	}

	ch8 *fg_StrUpperCase(ch8 *_pDest, mint _MaxDestLen, const ch8 *_pSource)
	{
		return fg_StrUpperCase(_pDest, _MaxDestLen, _pSource, fg_StrLen(_pSource));
	}

	ch8 *fg_StrUpperCase(ch8 *_pDest, mint _MaxDestLen, const ch8 *_pSource, mint _SourceLen)
	{
		ch32 UpperComapre = 0xffu;

		CStrIteratorUTF8 iStr{_pSource, _SourceLen};

		ch8 *pOutput = _pDest;
		ch8 *pOutputEnd = _pDest + _MaxDestLen - 1;

		auto fAddChar = [&](ch32 _Char)
			{
				return fg_EncodeUTF8Char
					(
						_Char
						, [&](mint _nChars) -> ch8 *
						{
							if (_nChars > mint(pOutputEnd - pOutput))
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
				Char -= 'a' - 'A';
			if (Char >= 0xe0u && Char <= UpperComapre)
				Char -= 0xe0u - 0xc0u;

			if (!fAddChar(Char))
				break;
			++iStr;
		}

		*pOutput = 0;

		return _pDest;
	}

	ch8 *fg_StrUpperCase(ch8 *_pDest, const ch8 *_pSource, mint _SourceLen)
	{
		return fg_StrUpperCase(_pDest, _SourceLen + 1, _pSource, _SourceLen);
	}


	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Lower case																						|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	ch8 *fg_StrLowerCase(ch8 *_pStr)
	{
		return fg_StrLowerCase(_pStr, fg_StrLen(_pStr));
	}

	ch8 *fg_StrLowerCase(ch8 *_pStr, mint _MaxLen)
	{
		CStrIteratorUTF8 iStr{_pStr, _MaxLen};

		ch8 *pLast = _pStr;

		auto fSetChar = [&](ch32 _Char)
			{
#if DMibEnableSafeCheck > 0
				ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
#endif

				fg_EncodeUTF8Char
					(
						_Char
						, [&](mint _nChars)
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
			else if (Char >= 0xc0u && Char <= 0xdfu)
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


	ch8 *fg_StrLowerCase(ch8 *_pDest, mint _MaxDestLen, const ch8 *_pSource, mint _SourceLen)
	{
		CStrIteratorUTF8 iStr{_pSource, _SourceLen};

		ch8 *pOutput = _pDest;
		ch8 *pOutputEnd = _pDest + _MaxDestLen - 1;

		auto fAddChar = [&](ch32 _Char)
			{
				return fg_EncodeUTF8Char
					(
						_Char
						, [&](mint _nChars) -> ch8 *
						{
							if (_nChars > mint(pOutputEnd - pOutput))
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
			if (Char >= 0xc0u && Char <= 0xdfu)
				Char += 0xe0u - 0xc0u;

			if (!fAddChar(Char))
				break;
			++iStr;
		}

		*pOutput = 0;

		return _pDest;
	}

	ch8 *fg_StrLowerCase(ch8 *_pDest, mint _MaxDestLen, const ch8 *_pSource)
	{
		return fg_StrLowerCase(_pDest, _MaxDestLen, _pSource, fg_StrLen(_pSource));
	}
	ch8 *fg_StrLowerCase(ch8 *_pDest, ch8 const *_pSource, mint _SourceLen)
	{
		return fg_StrLowerCase(_pDest, _SourceLen + 1, _pSource, _SourceLen);
	}
	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Capitalize (Uppercase first char)																						|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/


	ch8 *fg_StrCapitalize(ch8 *_pStr)
	{
		ch32 UpperComapre = 0xffu;

		CStrIteratorUTF8 iStr{_pStr, fg_StrLen(_pStr)};

		ch8 *pLast = _pStr;

		auto fSetChar = [&](ch32 _Char)
			{
#if DMibEnableSafeCheck > 0
				ch8 *pNext = _pStr + iStr.f_GetLastWholeCodePointPos();
#endif

				fg_EncodeUTF8Char
					(
						_Char
						, [&](mint _nChars)
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
				Char -= 'a' - 'A';
				fSetChar(Char);
			}
			else if (Char >= 0xe0u && Char <= UpperComapre)
			{
				Char -= 0xe0u - 0xc0u;
				fSetChar(Char);
			}
		}
		return _pStr;
	}
}
