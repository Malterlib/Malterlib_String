// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CTStrTraits>
	void TCStrImp_Virtual_PtrWrapper<t_CTStrTraits>::f_Destroy()
	{
		m_pStr->f_Destroy();
	}

	template <typename t_CTStrTraits>
	auto TCStrImp_Virtual_PtrWrapper<t_CTStrTraits>::f_GetStr() const -> typename t_CTStrTraits::CStrTraits::CChar const *
	{
		return m_pStr->f_GetStr();
	}

	template <typename t_CTStrTraits>
	bool TCStrImp_Virtual_PtrWrapper<t_CTStrTraits>::f_IsEmpty()
	{
		return m_pStr->f_IsEmpty();
	}

	template <typename t_CTStrTraits>
	aint TCStrImp_Virtual_PtrWrapper<t_CTStrTraits>::f_CreateWritableBuffer(aint _Length, bool _bDiscard)
	{
		return m_pStr->f_CreateWritableBuffer(_Length, _bDiscard);
	}

	template <typename t_CTStrTraits>
	aint TCStrImp_Virtual_PtrWrapper<t_CTStrTraits>::f_GetAllocLength() const
	{
		return m_pStr->f_GetAllocLength();
	}

	template <typename t_CTStrTraits>
	bool TCStrImp_Virtual_PtrWrapper<t_CTStrTraits>::f_FastLen()
	{
		return m_pStr->f_FastLen();
	}

	template <typename t_CTStrTraits>
	void TCStrImp_Virtual_PtrWrapper<t_CTStrTraits>::f_Clear()
	{
		return m_pStr->f_Clear();
	}

	template <typename t_CTStrTraits>
	void TCStrImp_Virtual_TStrWrapper<t_CTStrTraits>::f_Destroy()
	{
		m_Str.f_Destroy();
	}

	template <typename t_CTStrTraits>
	auto TCStrImp_Virtual_TStrWrapper<t_CTStrTraits>::f_GetStr() const -> typename t_CTStrTraits::CStrTraits::CChar const *
	{
		return m_Str.f_GetStr();
	}

	template <typename t_CTStrTraits>
	bool TCStrImp_Virtual_TStrWrapper<t_CTStrTraits>::f_IsEmpty()
	{
		return m_Str.f_IsEmpty();
	}

	template <typename t_CTStrTraits>
	aint TCStrImp_Virtual_TStrWrapper<t_CTStrTraits>::f_CreateWritableBuffer(aint _Length, bool _bDiscard)
	{
		return m_Str.f_CreateWritableBuffer(_Length, _bDiscard);
	}

	template <typename t_CTStrTraits>
	aint TCStrImp_Virtual_TStrWrapper<t_CTStrTraits>::f_GetAllocLength() const
	{
		return m_Str.f_GetAllocLength();
	}

	template <typename t_CTStrTraits>
	bool TCStrImp_Virtual_TStrWrapper<t_CTStrTraits>::f_FastLen()
	{
		return m_Str.f_FastLen();
	}

	template <typename t_CTStrTraits>
	void TCStrImp_Virtual_TStrWrapper<t_CTStrTraits>::f_Clear()
	{
		return m_Str.f_Clear();
	}
}
