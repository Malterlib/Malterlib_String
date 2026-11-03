// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraitsTypes>
	TCStrSpan<t_CStrTraitsTypes>::TCStrSpan(CChar const *_pStr, umint _Length)
		: mp_pStr(_pStr)
		, mp_Length(_Length)
	{
	}

	template <typename t_CStrTraitsTypes>
	auto TCStrSpan<t_CStrTraitsTypes>::f_GetStr() const -> CChar const *
	{
		return mp_pStr;
	}

	template <typename t_CStrTraitsTypes>
	umint TCStrSpan<t_CStrTraitsTypes>::f_GetLen() const
	{
		return mp_Length;
	}
}
