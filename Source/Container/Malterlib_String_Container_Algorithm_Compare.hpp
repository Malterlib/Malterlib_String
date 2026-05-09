// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2)
	{
		return fg_StrCmp(_Str.f_GetStr(), _Str.f_GetLen(), _pStr2);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2)
	{
		return fg_StrCmpLengthAware<false, false, true>(_pStr1, 0, _Str2.f_GetStr(), _Str2.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmp(_Str.f_GetStr(), _Str.f_GetLen(), _Str2.f_GetStr(), _Str2.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2)
	{
		return fg_StrCmpNoCase(_Str.f_GetStr(), _Str.f_GetLen(), _pStr2);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2)
	{
		return fg_StrCmpLengthAware<true, false, true>(_pStr1, 0, _Str2.f_GetStr(), _Str2.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmpNoCase(_Str.f_GetStr(), _Str.f_GetLen(), _Str2.f_GetStr(), _Str2.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2, umint _MaxLen)
	{
		return fg_StrCmpMaxLengthAware<false, true, false>(_Str.f_GetStr(), _Str.f_GetLen(), _pStr2, 0, _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2, umint _MaxLen)
	{
		return fg_StrCmpMaxLengthAware<false, false, true>(_pStr1, 0, _Str2.f_GetStr(), _Str2.f_GetLen(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2, umint _MaxLen)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmp(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _Str2.f_GetStr(), fg_Min(_Str2.f_GetLen(), _MaxLen));
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2, umint _MaxLen)
	{
		return fg_StrCmpMaxLengthAware<true, true, false>(_Str.f_GetStr(), _Str.f_GetLen(), _pStr2, 0, _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2, umint _MaxLen)
	{
		return fg_StrCmpMaxLengthAware<true, false, true>(_pStr1, 0, _Str2.f_GetStr(), _Str2.f_GetLen(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2, umint _MaxLen)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmpNoCase(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _Str2.f_GetStr(), fg_Min(_Str2.f_GetLen(), _MaxLen));
	}
}
