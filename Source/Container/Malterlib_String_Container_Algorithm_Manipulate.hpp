// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrInsert(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, tf_CData const *_pStrInsert)
	{
		mint NeededSize = fg_StrLen(_Str) + fg_StrLen(_pStrInsert);;
		fg_StrInsert(_Str.f_GetStr(NeededSize), _StartChar, _pStrInsert);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrInsert(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, TCStr<tf_CTCStrTraits2> const &_StrInsert)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		mint NeededSize = fg_StrLen(_Str) + fg_StrLen(_StrInsert);;
		fg_StrInsert(_Str.f_GetStr(NeededSize), _StartChar, _StrInsert.f_GetStr());
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrInsert(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, tf_CData const *_pStrInsert, mint _MaxLen)
	{
		mint NeededSize = fg_Min(fg_StrLen(_Str) + fg_StrLen(_pStrInsert), _MaxLen);
		fg_StrInsert(_Str.f_GetStr(NeededSize), _StartChar, _pStrInsert, _MaxLen);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrInsert(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, TCStr<tf_CTCStrTraits2> const &_StrInsert, mint _MaxLen)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		mint NeededSize = fg_Min(fg_StrLen(_Str) + fg_StrLen(_StrInsert), _MaxLen);
		fg_StrInsert(_Str.f_GetStr(NeededSize), _StartChar, _StrInsert.f_GetStr(), _MaxLen);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrDelete(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, mint _nChars)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;

		fg_StrDelete(pStr1, _StartChar, _nChars);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrLeft(TCStr<tf_CTCStrTraits> &_Str, mint _nChars)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;
		fg_StrLeft(pStr1, _nChars);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrExtract(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, mint _nChars)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;
		fg_StrExtract(pStr1, _StartChar, _nChars);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrExtract(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;
		fg_StrExtract(pStr1, _StartChar);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrRight(TCStr<tf_CTCStrTraits> &_Str, mint _nChars)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;
		fg_StrRight(pStr1, _nChars);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrClear(TCStr<tf_CTCStrTraits> &_Str)
	{
		_Str.f_Clear();
		return _Str;
	}
}
