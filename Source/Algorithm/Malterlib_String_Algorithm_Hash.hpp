// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData>
	constexpr inline_large uint32 fg_StrHashDJB2(tf_CData const *_pStr)
	{
		uint32 Hash = 5381;

		tf_CData const *pStr = _pStr;

		uint32 Char = *(pStr++);
		while (Char)
		{
			Hash = Hash * 33 + Char;
			Char = *(pStr++);
		}

		return Hash;
	}

	template <typename tf_CData>
	constexpr inline_large uint32 fg_StrHashSDBM(tf_CData const *_pStr)
	{
		uint32 Hash = 0;

		tf_CData const *pStr = _pStr;

		uint32 Char = *(pStr++);
		while (Char)
		{
			Hash = Char + (Hash << 6) + (Hash << 16) - Hash;
			Char = *(pStr++);
		}

		return Hash;
	}

	template <typename tf_CData>
	constexpr inline_large uint32 fg_StrHash(tf_CData const *_pStr)
	{
		return fg_StrHashDJB2(_pStr);
	}
}
