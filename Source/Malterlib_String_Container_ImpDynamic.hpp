// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CChar>
	inline_small auto TCStrImp_Dynamic_StringData<t_CChar>::f_GetData() const -> t_CChar *
	{
		return (t_CChar *)(this+1);
	}

	template <typename t_CChar>
	inline_small void TCStrImp_Dynamic_StringData<t_CChar>::f_SetLength(mint _MemoryLen)
	{
		m_Len = (_MemoryLen - sizeof(*this)) / sizeof(t_CChar);
	}

	template <typename t_CChar>
	inline_small mint TCStrImp_Dynamic_StringData<t_CChar>::f_GetMemorySize() const
	{
		return m_Len * sizeof(t_CChar) + sizeof(*this);
	}

	template <typename t_CChar>
	inline_small void TCStrImp_Dynamic_StringData<t_CChar>::f_RefCountIncrease()
	{
		if (m_bConstant)
			return;

		m_RefCount.f_FetchAdd(1, NAtomic::EMemoryOrder_Release);
	}

	template <typename t_CChar>
	inline_small bool TCStrImp_Dynamic_StringData<t_CChar>::f_RefCountDecrease()
	{
		if (m_bConstant)
			return false;

		return m_RefCount.f_FetchSub(1, NAtomic::EMemoryOrder_AcquireRelease) == 1;
	}
}
