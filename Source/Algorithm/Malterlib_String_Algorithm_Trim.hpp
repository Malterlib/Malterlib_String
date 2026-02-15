// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1>
	inline_small tf_CData1 *fg_StrTrimLeft(tf_CData1 *_pStr1)
	{
		return fg_StrTrimLeft(_pStr1, gc_WhiteSpaceChars);
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *fg_StrTrimRight(tf_CData1 *_pStr1, tf_CData2 const *_pCharsToTrim)
	{
		tf_CData1 *pStr1 = _pStr1;
		while (*pStr1)
		{
			++pStr1;
		}
		--pStr1;

		while (pStr1 >= _pStr1)
		{
			tf_CData2 const *pCharsToTrim = _pCharsToTrim;

			while (*pCharsToTrim)
			{
				if constexpr (sizeof(tf_CData1) > sizeof(tf_CData2))
				{
					if (*pStr1 - *pCharsToTrim == 0)
						break;
				}
				else
				{
					if (*pCharsToTrim - *pStr1  == 0)
						break;
				}
				++pCharsToTrim;
			}

			if (!(*pCharsToTrim))
				break;

			*pStr1 = 0;

			--pStr1;
		}

		return _pStr1;
	}

	template <typename tf_CData1>
	inline_small tf_CData1 *fg_StrTrimRight(tf_CData1 *_pStr1)
	{
		return fg_StrTrimRight(_pStr1, gc_WhiteSpaceChars);
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *fg_StrTrim(tf_CData1 *_pStr1, tf_CData2 const *_pCharsToTrim)
	{
		return fg_StrTrimLeft(fg_StrTrimRight(_pStr1, _pCharsToTrim), _pCharsToTrim);
	}

	template <typename tf_CData1>
	inline_small tf_CData1 *fg_StrTrim(tf_CData1 *_pStr1)
	{
		return fg_StrTrim(_pStr1, gc_WhiteSpaceChars);
	}
}
