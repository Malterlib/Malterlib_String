// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_String_UnicodeConversion.h"

namespace NMib::NStr
{
	void CStrIteratorUTF8::fp_ParseBOM()
	{
		// Remove BOM
		if (mp_pBegin[0] == 0xEF && mp_pBegin[1] == 0xBB && mp_pBegin[2] == 0xBF)
			mp_pBegin += 3;
	}

	ch32 CStrIteratorUTF8::fp_Next()
	{
		ch32 DestChar = 0;
		uch8 const *pParse = mp_pBegin;
		uch8 const *pLastValid = mp_pLastValidBegin;

		mp_bWholeCodePoint = true;
		mp_bValidCodePoint = true;

		while (1)
		{
			if (pParse >= mp_pEnd)
				break;

			uch8 ToTest = *pParse;
			if (ToTest & 0x80)
			{
				if ((ToTest & 0xC0) == 0xC0)
				{
					++pParse;
					umint nChars = 7 - fg_GetHighestBitSetNoZero(((~uint32(ToTest)) & 0xFF) | 1u);
					DestChar = ToTest & ((1 << (8 - (nChars + 1))) - 1);
					--nChars;
					while (pParse < mp_pEnd && *pParse && nChars && (*pParse & 0xC0) == 0x80)
					{
						DestChar = (DestChar << 6) | ((*pParse) & 0x3F);
						++pParse;
						--nChars;
					}

					if (nChars)
					{
						if (pParse >= mp_pEnd || !*pParse)
							mp_bWholeCodePoint = false;
						else
						{
							mp_bValidCodePoint = false;
							pLastValid = pParse;
							break;
						}
					}
					else
						pLastValid = pParse;
					break;
				}
				else
				{
					DestChar = ToTest;
					mp_bValidCodePoint = false;
					pLastValid = pParse;
					++pParse;
					break;
				}
			}
			else
			{
				DestChar = ToTest;
				++pParse;
				pLastValid = pParse;
				break;
			}
		}

		mp_pLastValidBegin = pLastValid;
		mp_pBegin = pParse;

		return DestChar;
	}

	CStrIteratorUTF8::CStrIteratorUTF8(ch8 const *_pStr, umint _StrLen)
		: mp_pBegin((uch8 const *)_pStr)
		, mp_pEnd((uch8 const *)_pStr + _StrLen)
		, mp_pInitialBegin((uch8 const *)_pStr)
		, mp_pLastValidBegin((uch8 const *)_pStr)
		, mp_bWholeCodePoint(true)
		, mp_bValidCodePoint(true)
	{
		fp_ParseBOM();
		mp_Current = fp_Next();
	}

	umint CStrIteratorUTF8::f_GetLastWholeCodePointPos() const
	{
		return mp_pLastValidBegin - mp_pInitialBegin;
	}

	bool CStrIteratorUTF8::f_IsWholeCodePoint() const
	{
		return mp_bWholeCodePoint;
	}

	bool CStrIteratorUTF8::f_IsBroken() const
	{
		return !mp_bValidCodePoint;
	}

	CStrIteratorUTF8 &CStrIteratorUTF8::f_GetIterator()
	{
		return *this;
	}

	void CStrIteratorUTF16::fp_ParseBOM()
	{
		// Remove BOM
		if (mp_pBegin[0] == 0xFFFE)
			++mp_pBegin;
	}

	ch32 CStrIteratorUTF16::fp_Next()
	{
		ch32 DestChar = 0;
		uch16 const *pParse = mp_pBegin;
		while (1)
		{
			if (pParse >= mp_pEnd)
			{
				mp_pBegin = pParse;
				return DestChar;
			}

			if ((*pParse & 0xFC00) == 0xD800)
			{
				ch32 Str0 = *pParse;
				++pParse;
				ch32 Str1 = *pParse;
				if ((Str1 & 0xFC00) != 0xDC00)
					continue;
				++pParse;

				ch32 X = ((Str0 & ((1<<6) -1)) << 10) | (Str1 & ((1<<10) -1));
				ch32 W = (Str0 >> 6) & ((1<<5) - 1);
				ch32 U = W + 1 ;

				DestChar = U << 16 | X;
				break;
			}
			DestChar = (*(pParse++));
			break;
		}

		mp_pBegin = pParse;

		return DestChar;
	}

	CStrIteratorUTF16::CStrIteratorUTF16(ch16 const *_pStr, umint _StrLen)
		: mp_pBegin((uch16 const *)_pStr)
		, mp_pEnd((uch16 const *)_pStr + _StrLen)
	{
		fp_ParseBOM();
		mp_Current = fp_Next();
	}

	CStrIteratorUTF16 &CStrIteratorUTF16::f_GetIterator()
	{
		return *this;
	}
}
