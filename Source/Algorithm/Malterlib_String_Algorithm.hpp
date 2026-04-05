// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData>
	constexpr inline_small tf_CData *fg_StrAdd(tf_CData *_pStr, aint _Add) // Adding a negative value will null the str
	{
		if (_Add < 0)
			return nullptr;
		else
			return _pStr + _Add;
	}

	constexpr inline_small aint fg_StrAdd(aint _Offset, aint _Add) // Adding a negative value will null the str
	{
		if (_Add < 0)
			return -1;
		else
			return _Offset + _Add;
	}

	template <typename tf_CData>
	constexpr inline_medium umint fg_StrLen(tf_CData const *_pStr)
	{
		tf_CData const *pStr = _pStr;

		while (*pStr)
			++pStr;

		return pStr - _pStr;
	}

	template <typename tf_CData>
	constexpr inline_medium umint fg_StrLen(tf_CData const *_pStr, umint _MaxLen)
	{
		tf_CData const *pStr = _pStr;
		tf_CData const *pEnd = pStr + _MaxLen;

		while (*pStr && pStr < pEnd)
			++pStr;

		return pStr - _pStr;

	}

	template <typename tf_CData1, typename tf_CData2>
	inline_medium tf_CData1 *fg_StrCopy(tf_CData1 *_pTo, tf_CData2 const *_pFrom)
	{
		while (*_pFrom)
			*_pTo++ = *_pFrom++;
		*_pTo = 0;

		return _pTo;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrCopy(tf_CData1 *_pTo, tf_CData2 const *_pFrom, umint _MaxLen)
	{
		tf_CData1 const *_pEnd = _pTo + _MaxLen - 1;
		while (*_pFrom && _pTo < _pEnd)
			*_pTo++ = *_pFrom++;
		*_pTo = 0;
		return _pTo;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_medium tf_CData1 *fg_StrMove(tf_CData1 *_pTo, tf_CData2 const *_pFrom)
	{
		if constexpr (sizeof(tf_CData1) == sizeof(tf_CData2))
		{
			umint Len = fg_StrLen(_pFrom) + 1;
			NMemory::fg_MemMove(_pTo, _pFrom, Len*sizeof(tf_CData2));
			return _pTo;
		}
		else
			return fg_StrCopy(_pTo, _pFrom);
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrMove(tf_CData1 *_pTo, tf_CData2 const *_pFrom, umint _MaxLen)
	{
		if constexpr (sizeof(tf_CData1) == sizeof(tf_CData2))
		{
			umint Len = fg_Min(fg_StrLen(_pFrom, _MaxLen), _MaxLen - 1);
			NMemory::fg_MemMove(_pTo, _pFrom, Len*sizeof(tf_CData2));
			_pTo[Len] = 0;
			return _pTo;
		}
		else
			return fg_StrCopy(_pTo, _pFrom, _MaxLen);
	}

	template <bool tf_bCheckLen, typename tf_CData1>
	constexpr inline_large bool fg_StrIsAnsi(tf_CData1 const *_pStr1, umint _Len)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		CData1 const *pStr1Start = (CData1 const *)_pStr1;
		CData1 const *pStr1 = pStr1Start;
		CData1 const *pStr1End = pStr1Start + _Len;

		while (*pStr1)
		{
			if constexpr (tf_bCheckLen)
			{
				if (pStr1 >= pStr1End)
					return true;
			}

			if (*pStr1 >= 128)
				return false;

			++pStr1;
		}
		return true;
	}

	template <typename tf_CData1>
	constexpr inline_small bool fg_StrIsAnsi(tf_CData1 const *_pStr1)
	{
			return fg_StrIsAnsi<0>(_pStr1, 0);
	}

	template <typename tf_CData1>
	constexpr inline_small bool fg_StrIsAnsi(tf_CData1 const *_pStr1, umint _Len)
	{
			return fg_StrIsAnsi<1>(_pStr1, _Len);
	}

	template <typename tf_CStr>
	constexpr bool fg_StrIsEmpty(tf_CStr const *_pStr)
	{
		return *_pStr == 0;
	}

	template <typename tf_CData1>
	inline_small tf_CData1 *fg_StrClear(tf_CData1 *_pStr1)
	{
		*_pStr1 = 0;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *fg_StrSetAt(tf_CData1 *_pStr1, aint _Index, tf_CData2 _Character)
	{
		_pStr1[_Index] = tf_CData1(_Character);
		return _pStr1;
	}

	template <typename tf_CData1>
	inline_small NTraits::TCUnsigned<tf_CData1> fg_StrLargestChar(tf_CData1 const *_pStr1)
	{
		NTraits::TCUnsigned<tf_CData1> Largest = 0;
		NTraits::TCUnsigned<tf_CData1> const *pStr1 = (NTraits::TCUnsigned<tf_CData1> const *)_pStr1;
		while (*pStr1)
		{
			if (*pStr1 > Largest)
			{
				Largest = *pStr1;
			}
			++pStr1;
		}
		return Largest;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrReverse(tf_CData1 *_pStr1)
	{
		tf_CData1 *pStr1 = _pStr1;
		tf_CData1 *pStr1End = _pStr1;
		while (*pStr1End)
			++pStr1End;
		--pStr1End;

		while (pStr1 < pStr1End)
		{
			tf_CData1 Temp = *pStr1;
			*pStr1 = *pStr1End;
			*pStr1End = Temp;
			++pStr1;
			--pStr1End;
		}
		return _pStr1;
	}
}

#include "Malterlib_String_Algorithm_Case.hpp"
#include "Malterlib_String_Algorithm_Character.hpp"
#include "Malterlib_String_Algorithm_Compare.hpp"
#include "Malterlib_String_Algorithm_Escape.hpp"
#include "Malterlib_String_Algorithm_Find.hpp"
#include "Malterlib_String_Algorithm_Hash.hpp"
#include "Malterlib_String_Algorithm_Join.hpp"
#include "Malterlib_String_Algorithm_Manipulate.hpp"
#include "Malterlib_String_Algorithm_Parse.hpp"
#include "Malterlib_String_Algorithm_Replace.hpp"
#include "Malterlib_String_Algorithm_Sanitize.hpp"
#include "Malterlib_String_Algorithm_Split.hpp"
#include "Malterlib_String_Algorithm_Trim.hpp"
#include "Malterlib_String_Algorithm_Wildcard.hpp"
