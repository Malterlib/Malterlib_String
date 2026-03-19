// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	inline_small TCStrImp_Ptr<t_CStrTraits>::TCStrImp_Ptr()
	{
		m_pData = nullptr;
		m_MaxLen = 0;
		m_Len = 0;
	}

	template <typename t_CStrTraits>
	inline_small TCStrImp_Ptr<t_CStrTraits>::TCStrImp_Ptr(TCStrImp_Ptr &&_Str)
		: m_pData(_Str.m_pData)
		, m_MaxLen(fg_Exchange(_Str.m_MaxLen, 0))
		, m_Len(_Str.m_Len)
	{
	}

	template <typename t_CStrTraits>
	inline_small TCStrImp_Ptr<t_CStrTraits>::TCStrImp_Ptr(TCStrImp_Ptr const &_Str)
		: m_pData(_Str.m_pData)
		, m_MaxLen(0)
		, m_Len(_Str.m_Len)
	{
	}

	template <typename t_CStrTraits>
	inline_small TCStrImp_Ptr<t_CStrTraits>::TCStrImp_Ptr(CChar *_pString, umint _Len)
	{
		f_SetPtr(_pString, _Len);
	}

	template <typename t_CStrTraits>
	inline_small TCStrImp_Ptr<t_CStrTraits>::TCStrImp_Ptr(CChar const *_pString, umint _Len)
	{
		f_SetConstPtr(_pString, _Len);
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Ptr<t_CStrTraits>::f_Assign(TCStrImp_Ptr &&_Str)
	{
		m_pData = _Str.m_pData;
		m_MaxLen = _Str.m_MaxLen;
		m_Len = _Str.m_Len;
		_Str.m_MaxLen = 0;
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Ptr<t_CStrTraits>::f_Assign(TCStrImp_Ptr const &_Str)
	{
		m_pData = _Str.m_pData;
		m_MaxLen = 0;
		m_Len = _Str.m_Len;
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Ptr<t_CStrTraits>::f_SetPtr(CChar *_pString, umint _Len)
	{
		m_pData = _pString;
		m_MaxLen = _Len;
		m_Len = 0;
		m_pData[0] = 0;
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Ptr<t_CStrTraits>::f_SetConstPtr(CChar const *_pString, umint _Len)
	{
		m_pData = (CChar *)_pString;
		m_MaxLen = 0;
		m_Len = _Len;
	}

	template <typename t_CStrTraits>
	inline_small auto TCStrImp_Ptr<t_CStrTraits>::f_GetStrWritable() -> CChar *
	{
		return m_pData;
	}

	template <typename t_CStrTraits>
	inline_small auto TCStrImp_Ptr<t_CStrTraits>::f_GetStr() const -> CChar const *
	{
		return m_pData;
	}

	template <typename t_CStrTraits>
	inline_small aint TCStrImp_Ptr<t_CStrTraits>::f_GetAllocLength() const
	{
		return m_MaxLen;
	}

	template <typename t_CStrTraits>
	inline_medium aint TCStrImp_Ptr<t_CStrTraits>::f_GetStrLen() const
	{
		if (m_Len == mc_InvalidStrLen)
			const_cast<TCStrImp_Ptr*>(this)->m_Len = t_CStrTraits::fs_StrLen(m_pData);

		return m_Len;
	}

	template <typename t_CStrTraits>
	inline_small bool TCStrImp_Ptr<t_CStrTraits>::f_FastLen()
	{
		return true;
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Ptr<t_CStrTraits>::f_MakeUnique()
	{
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Ptr<t_CStrTraits>::f_SetStrLen(aint _Len)
	{
		if (_Len < 0)
			m_Len = mc_InvalidStrLen;
		else
			m_Len = _Len;
	}

	template <typename t_CStrTraits>
	inline_small aint TCStrImp_Ptr<t_CStrTraits>::f_CreateWritableBuffer(aint _Length, bool _bDiscard)
	{
		return m_MaxLen;
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Ptr<t_CStrTraits>::f_Destroy()
	{
		if (m_MaxLen > 0)
			m_pData[0] = 0;
		m_Len = 0;
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Ptr<t_CStrTraits>::f_Clear()
	{
		f_Destroy();
	}
}
