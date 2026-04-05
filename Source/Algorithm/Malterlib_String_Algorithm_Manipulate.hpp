// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrInsert(tf_CData1 *_pStr1, aint _StartChar, tf_CData2 const *_pStr2)
	{
		if (_StartChar < 0)
			return _pStr1;
		tf_CData1 *pStr1 = _pStr1;
		while (_StartChar)
		{
			if (!(*pStr1))
				break;
			++pStr1;
			--_StartChar;
		}

		umint Str2Len = fg_StrLen(_pStr2);
		fg_StrMove(pStr1 + Str2Len, pStr1);
		NMemory::fg_MemCopy(pStr1, _pStr2, Str2Len * sizeof(tf_CData1));
		return _pStr1;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrInsert(tf_CData1 *_pStr1, aint _StartChar, tf_CData2 const *_pStr2, umint _MaxLen)
	{
		if (_StartChar < 0)
			return _pStr1;
		--_MaxLen;
		tf_CData1 *pStr1 = _pStr1;
		while (_StartChar)
		{
			if (!(*pStr1))
				break;
			++pStr1;
			--_StartChar;
		}

		umint Str2Len = fg_StrLen(_pStr2);
		aint MaxLen = _MaxLen - ((pStr1 + Str2Len) - _pStr1) + 1;
		if (MaxLen > 0)
			fg_StrMove(pStr1 + Str2Len, pStr1, MaxLen);
		umint MaxLen2 = fg_Min(Str2Len, _MaxLen - (pStr1 - _pStr1));
		NMemory::fg_MemCopy(pStr1, _pStr2, MaxLen2 * sizeof(tf_CData1));
		pStr1[fg_Max(MaxLen2, (MaxLen + Str2Len))] = 0;
		return _pStr1;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrDelete(tf_CData1 *_pStr1, aint _StartChar, umint _nChars)
	{
		if (_StartChar < 0)
			return _pStr1;
		tf_CData1 *pStr1 = _pStr1;
		while (_StartChar)
		{
			if (!(*pStr1))
				return _pStr1;
			++pStr1;
			--_StartChar;
		}

		tf_CData1 *pStr2 = pStr1;

		while (_nChars)
		{
			if (!(*pStr2))
				break;

			++pStr2;
			--_nChars;
		}

		while (*pStr2)
		{
			*pStr1 = *pStr2;
			++pStr1;
			++pStr2;
		}
		*pStr1 = 0;
		return _pStr1;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrLeft(tf_CData1 *_pStr1, umint _nChars)
	{
		tf_CData1 *pStr1 = _pStr1;
		while (_nChars)
		{
			if (!(*pStr1))
				return _pStr1;
			++pStr1;
			--_nChars;
		}

		*pStr1 = 0;

		return _pStr1;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrExtract(tf_CData1 *_pStr1, aint _StartChar, umint _nChars)
	{
		if (_StartChar < 0)
			return _pStr1;
		tf_CData1 *pStr1 = _pStr1;
		while (_StartChar)
		{
			if (!(*pStr1))
			{
				*_pStr1 = 0;
				return _pStr1;
			}
			++pStr1;
			--_StartChar;
		}
		fg_StrMove(_pStr1, pStr1, _nChars + 1);
		return _pStr1;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrExtract(tf_CData1 *_pStr1, aint _StartChar)
	{
		if (_StartChar < 0)
			return _pStr1;
		tf_CData1 *pStr1 = _pStr1;
		while (_StartChar)
		{
			if (!(*pStr1))
			{
				*_pStr1 = 0;
				return _pStr1;
			}
			++pStr1;
			--_StartChar;
		}
		fg_StrMove(_pStr1, pStr1);
		return _pStr1;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrRight(tf_CData1 *_pStr1, umint _nChars)
	{
		return fg_StrExtract(_pStr1, fg_StrLen(_pStr1) - _nChars);
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *fg_StrTrimLeft(tf_CData1 *_pStr1, tf_CData2 const *_pCharsToTrim)
	{
		tf_CData1 *pStr1 = _pStr1;
		while (*pStr1)
		{
			tf_CData2 const *pCharsToTrim = _pCharsToTrim;

			while (*pCharsToTrim)
			{
				if constexpr (sizeof(tf_CData1) > sizeof(tf_CData2))
				{
					if (*pStr1 - *pCharsToTrim == 0)
					{
						break;
					}
				}
				else
				{
					if (*pCharsToTrim - *pStr1  == 0)
					{
						break;
					}
				}
				++pCharsToTrim;
			}

			if (!(*pCharsToTrim))
				break;

			++pStr1;
		}

		return fg_StrExtract(_pStr1, pStr1 - _pStr1);
	}
}
