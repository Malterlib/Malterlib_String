// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits, aint t_DataLen>
	inline_small constexpr TCStrImp_Fixed<t_CStrTraits, t_DataLen>::TCStrImp_Fixed()
		: m_lData{0}
		, m_Len(0)
	{
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small TCStrImp_Fixed<t_CStrTraits, t_DataLen>::TCStrImp_Fixed(TCStrImp_Fixed const &_Str)
	{
		umint Len = _Str.f_GetStrLen();
		m_Len = Len;
		//NMib::NMemory::fg_ObjectCopy((CChar *)m_lData, (CChar const*)_Str.m_lData, Len+1);
		NMib::NMemory::fg_MemCopy(m_lData, _Str.m_lData, (Len+1) * sizeof(CChar));
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small constexpr TCStrImp_Fixed<t_CStrTraits, t_DataLen>::TCStrImp_Fixed(CChar const *_pString, umint _Len)
	{
		umint nChars = fg_Min(t_DataLen - 1, _Len);
		for (umint i = 0; i < nChars; ++i)
			m_lData[i] = _pString[i];
		m_Len = nChars;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_medium void TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_Assign(TCStrImp_Fixed const &_Str)
	{
		umint Len = _Str.f_GetStrLen();
		m_Len = Len;
		//NMib::NMemory::fg_ObjectCopy((CChar *)m_lData, (CChar const*)_Str.m_lData, Len+1);
		NMib::NMemory::fg_MemCopy(m_lData, _Str.m_lData, (Len+1) * sizeof(CChar));
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small auto TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_GetStrWritable() -> CChar *
	{
		return m_lData;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small auto TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_GetStr() const -> CChar const *
	{
		return (CChar const *)m_lData;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small aint TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_GetAllocLength() const
	{
		return t_DataLen;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_medium aint TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_GetStrLen() const
	{
		if (m_Len == mc_InvalidStrLen)
		{
			const_cast<TCStrImp_Fixed*>(this)->m_Len = t_CStrTraits::fs_StrLen(m_lData);
		}

		return m_Len;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small bool TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_FastLen()
	{
		return true;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small void TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_MakeUnique()
	{
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small void TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_SetStrLen(aint _Len)
	{
		if (_Len < 0)
			m_Len = mc_InvalidStrLen;
		else
			m_Len = _Len;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small aint TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_CreateWritableBuffer(aint _Length, bool _bDiscard)
	{
		return t_DataLen;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small constexpr void TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_Destroy()
	{
		m_lData[0] = 0;
		m_Len = 0;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small void TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_Clear()
	{
		f_Destroy();
	}
}
