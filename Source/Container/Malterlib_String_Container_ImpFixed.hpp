// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits, aint t_DataLen>
	inline_small constexpr TCStrImp_Fixed<t_CStrTraits, t_DataLen>::TCStrImp_Fixed()
		: m_Data{0}
		, m_Len(0)
	{
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small TCStrImp_Fixed<t_CStrTraits, t_DataLen>::TCStrImp_Fixed(TCStrImp_Fixed const &_Str)
	{
		umint Len = _Str.f_GetStrLen();
		m_Len = Len;
		//NMib::NMemory::fg_ObjectCopy((CChar *)m_Data, (CChar const*)_Str.m_Data, Len+1);
		NMib::NMemory::fg_MemCopy(m_Data, _Str.m_Data, (Len + 1) * sizeof(CChar));
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small constexpr TCStrImp_Fixed<t_CStrTraits, t_DataLen>::TCStrImp_Fixed(CChar const *_pString, umint _Len)
	{
		umint nChars = fg_Min(t_DataLen - 1, _Len);
		for (umint iChar = 0; iChar < nChars; ++iChar)
			m_Data[iChar] = _pString[iChar];
		m_Data[nChars] = 0;
		m_Len = nChars;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_medium void TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_Assign(TCStrImp_Fixed const &_Str)
	{
		umint Len = _Str.f_GetStrLen();
		m_Len = Len;
		//NMib::NMemory::fg_ObjectCopy((CChar *)m_Data, (CChar const*)_Str.m_Data, Len+1);
		NMib::NMemory::fg_MemCopy(m_Data, _Str.m_Data, (Len + 1) * sizeof(CChar));
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small auto TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_GetStrWritable() -> CChar *
	{
		return m_Data;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small auto TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_GetStr() const -> CChar const *
	{
		return (CChar const *)m_Data;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	constexpr inline_small bool TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_IsEmpty() const
	{
		if (m_Len == mc_InvalidStrLen)
			return m_Data[0] == 0;

		return m_Len == 0;
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
			const_cast<TCStrImp_Fixed *>(this)->m_Len = t_CStrTraits::fs_StrLen(m_Data);

		return m_Len;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small bool TCStrImp_Fixed<t_CStrTraits, t_DataLen>::fs_FastLen()
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
		{
			m_Len = _Len;
			m_Data[_Len] = 0;
		}
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small aint TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_CreateWritableBuffer(aint _Length, bool _bDiscard)
	{
		return t_DataLen;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small constexpr void TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_Destroy()
	{
		m_Data[0] = 0;
		m_Len = 0;
	}

	template <typename t_CStrTraits, aint t_DataLen>
	inline_small void TCStrImp_Fixed<t_CStrTraits, t_DataLen>::f_Clear()
	{
		f_Destroy();
	}
}
