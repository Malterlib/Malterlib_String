// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CTCStrTraits>
	inline_large TCStr<t_CTCStrTraits>::TCStr(CFormat const &_Format)
	{
		CAutoDestroy Cleanup{this};
		_Format.f_FormatToStr(*this);
		Cleanup.f_Clear();
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	inline_large TCStr<t_CTCStrTraits>::TCStr(tf_CStrDataType const *_pStr)
	{
		if (*_pStr)
		{
			CAutoDestroy Cleanup{this};
			f_SetStr(_pStr);
			Cleanup.f_Clear();
		}
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	inline_large TCStr<t_CTCStrTraits>::TCStr(tf_CStrDataType const *_pStr, umint _Len)
		requires (CImp::mc_bInitConstStr)
		: CImp(_pStr, _Len)
	{
	}

	template <typename t_CTCStrTraits>
	inline_large TCStr<t_CTCStrTraits>::TCStr(CInitByRange, CChar const *_pStrStart, CChar const *_pStrEnd)
		requires (CImp::mc_bInitConstStr)
		: CImp(_pStrStart, _pStrEnd - _pStrStart)
	{
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	inline_large TCStr<t_CTCStrTraits>::TCStr(tf_CStrDataType const *_pStr, umint _Len)
		requires (!CImp::mc_bInitConstStr)
	{
		if (!_Len)
			return;

		CAutoDestroy Cleanup{this};
		f_SetStr(_pStr, _Len);
		Cleanup.f_Clear();
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	inline_large TCStr<t_CTCStrTraits>::TCStr(CAllowNUL, tf_CStrDataType const *_pStr, umint _Len)
		requires (!CImp::mc_bInitConstStr)
	{
		if (!_Len)
			return;

		CAutoDestroy Cleanup{this};
		f_SetStr(CAllowNUL(), _pStr, _Len);
		Cleanup.f_Clear();
	}

	template <typename t_CTCStrTraits>
	inline_large TCStr<t_CTCStrTraits>::TCStr(CInitByRange, CChar const *_pStrStart, CChar const *_pStrEnd)
		requires (!CImp::mc_bInitConstStr)
	{
		auto Len = _pStrEnd - _pStrStart;
		if (!Len)
			return;

		CAutoDestroy Cleanup{this};
		f_SetStr(_pStrStart, Len);
		Cleanup.f_Clear();
	}

	template <typename t_CTCStrTraits>
	template <typename ...tfp_CParams>
	constexpr inline_large TCStr<t_CTCStrTraits>::TCStr(CStrInitGeneral _Init, tfp_CParams &&...p_Params)
		requires requires ()
		{
			CImp(fg_Forward<tfp_CParams>(p_Params)...);
		}
		: CImp(fg_Forward<tfp_CParams>(p_Params)...)
	{
	}

	template <typename t_CTCStrTraits>
	constexpr inline_small TCStr<t_CTCStrTraits>::TCStr(TCStr const &_Str)
		: CImp(_Str)
	{
	}

	template <typename t_CTCStrTraits>
	inline_small TCStr<t_CTCStrTraits>::TCStr(TCStr &&_Str)
		: CImp(fg_Move(_Str))
	{
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrTraitsF>
	inline_large TCStr<t_CTCStrTraits>::TCStr(TCStr<tf_CStrTraitsF> const &_From)
	{
		CAutoDestroy Cleanup{this};
		f_SetStr(_From);
		Cleanup.f_Clear();
	}

	template <typename t_CTCStrTraits>
	inline_small void TCStr<t_CTCStrTraits>::f_Assign(TCStr const &_Src)
	{
		CImp::f_Assign(_Src);
	}

	template <typename t_CTCStrTraits>
	inline_small void TCStr<t_CTCStrTraits>::f_Assign(TCStr &&_Src)
	{
		CImp::f_Assign(fg_Move(_Src));
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrTraitsF>
	inline_large auto TCStr<t_CTCStrTraits>::operator = (TCStr<tf_CStrTraitsF> const &_From) -> TCStr &
	{
		if (!(*_From.f_GetStr()))
		{
			this->f_Clear();
			return *this;
		}
		f_SetStr(_From);
		return *this;
	}

	template <typename t_CTCStrTraits>
	inline_large auto TCStr<t_CTCStrTraits>::operator = (TCStr const &_From) -> TCStr &
	{
		CImp::f_Assign(_From);
		return *this;
	}

	template <typename t_CTCStrTraits>
	inline_large auto TCStr<t_CTCStrTraits>::operator = (TCStr &&_From) -> TCStr &
	{
		DMibFastCheck(this != &_From);
		CImp::f_Assign(fg_Move(_From));
		return *this;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CDataF>
	inline_large auto TCStr<t_CTCStrTraits>::operator = (tf_CDataF const *_pFrom) -> TCStr &
	{
		f_SetStr(_pFrom);
		return *this;
	}

	template <typename t_CTCStrTraits>
	inline_large auto TCStr<t_CTCStrTraits>::operator = (CFormat const &_Format) -> TCStr &
	{
		_Format.f_FormatToStr(*this);
		return *this;
	}
}
