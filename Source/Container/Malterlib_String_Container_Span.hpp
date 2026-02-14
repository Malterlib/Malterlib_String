// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraitsTypes>
	TCStrSpan<t_CStrTraitsTypes>::TCStrSpan(CChar const *_pStr, mint _Length)
		: m_pStr(_pStr)
		, m_Length(_Length)
	{
	}

	template <typename t_CStrTraitsTypes>
	auto TCStrSpan<t_CStrTraitsTypes>::f_GetStr() const -> CChar const *
	{
		return m_pStr;
	}

	template <typename t_CStrTraitsTypes>
	mint TCStrSpan<t_CStrTraitsTypes>::f_GetLen() const
	{
		return m_Length;
	}
}
