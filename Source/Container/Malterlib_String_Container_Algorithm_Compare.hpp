// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2)
	{
		return fg_StrCmp(_Str.f_GetStr(), _pStr2);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2)
	{
		return fg_StrCmp(_pStr1, _Str2.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmp(_Str.f_GetStr(), _Str2.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2)
	{
		return fg_StrCmpNoCase(_Str.f_GetStr(), _pStr2);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2)
	{
		return fg_StrCmpNoCase(_pStr1, _Str2.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmpNoCase(_Str.f_GetStr(), _Str2.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2, mint _MaxLen)
	{
		return fg_StrCmp(_Str.f_GetStr(), _pStr2, _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2, mint _MaxLen)
	{
		return fg_StrCmp(_pStr1, _Str2.f_GetStr(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2, mint _MaxLen)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmp(_Str.f_GetStr(), _Str2.f_GetStr(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2, mint _MaxLen)
	{
		return fg_StrCmpNoCase(_Str.f_GetStr(), _pStr2, _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2, mint _MaxLen)
	{
		return fg_StrCmpNoCase(_pStr1, _Str2.f_GetStr(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2, mint _MaxLen)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmpNoCase(_Str.f_GetStr(), _Str2.f_GetStr(), _MaxLen);
	}
}
