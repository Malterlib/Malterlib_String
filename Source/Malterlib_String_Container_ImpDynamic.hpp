// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	inline_small auto TCStrImp_Dynamic<t_CStrTraits>::CData::f_GetData() const -> CChar *
	{
		return (CChar *)(this+1);
	}

	template <typename t_CStrTraits>
	inline_small aint TCStrImp_Dynamic<t_CStrTraits>::CData::f_GetLength()
	{
		DMibFastCheck(m_Len != 0);
		//DMibFastCheck(m_Len == (CAllocator::f_Size(this) - sizeof(*this)) / sizeof(CChar));
		return m_Len;
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Dynamic<t_CStrTraits>::CData::f_SetLength(mint _MemoryLen)
	{
		m_Len = (_MemoryLen - sizeof(*this)) / sizeof(CChar);
	}

	template <typename t_CStrTraits>
	inline_small mint TCStrImp_Dynamic<t_CStrTraits>::CData::f_GetMemorySize() const
	{
		return m_Len * sizeof(CChar) + sizeof(*this);
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Dynamic<t_CStrTraits>::CData::f_RefcountIncrease()
	{
		m_RefCount.f_FetchAdd(1, NAtomic::EMemoryOrder_Release);
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Dynamic<t_CStrTraits>::CData::f_RefcountDecrease()
	{
		if (m_RefCount.f_FetchSub(1, NAtomic::EMemoryOrder_AcquireRelease) == 1)
			CAllocator::f_Free(this, f_GetMemorySize());
	}
}
