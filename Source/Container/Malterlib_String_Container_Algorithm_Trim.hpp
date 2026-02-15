// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrimLeft(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pCharsToTrim)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;

		fg_StrTrimLeft(pStr1, _pCharsToTrim);
		_Str.f_SetModified();

		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrimLeft(TCStr<tf_CTCStrTraits> &_Str)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;

		fg_StrTrimLeft(pStr1, gc_WhiteSpaceChars);
		_Str.f_SetModified();

		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrimRight(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pCharsToTrim)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;

		fg_StrTrimRight(pStr1, _pCharsToTrim);
		_Str.f_SetModified();

		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrimRight(TCStr<tf_CTCStrTraits> &_Str)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;

		fg_StrTrimRight(pStr1, gc_WhiteSpaceChars);
		_Str.f_SetModified();

		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrim(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pCharsToTrim)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;

		fg_StrTrim(pStr1, _pCharsToTrim);
		_Str.f_SetModified();

		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrim(TCStr<tf_CTCStrTraits> &_Str)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;

		fg_StrTrim(pStr1, gc_WhiteSpaceChars);
		_Str.f_SetModified();

		return _Str;
	}
}
