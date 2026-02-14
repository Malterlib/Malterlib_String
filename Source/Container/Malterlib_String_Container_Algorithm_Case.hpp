// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;

		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;

		fg_StrUpperCase(pStr1, _To.f_GetLen());
		return _To;
	}

	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrUpperCase(TCStr<tf_CTCStrTraits1> &_To, tf_CData const *_pSource)
	{
		_To = _pSource;
		fg_StrUpperCase(_To);
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source)
	{
		_To = _Source;
		fg_StrUpperCase(_To);
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrUpperCase(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_Source)
	{
		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;
		static_assert(NTraits::cIsSame<tf_CData, typename TCStr<tf_CTCStrTraits>::CChar>, "Unsupported");
		fg_StrUpperCase(_pTo, _Source.f_GetStr());
		return _pTo;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrUpperCase(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_Source, mint _MaxLen)
	{
		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;
		static_assert(NTraits::cIsSame<tf_CData, typename TCStr<tf_CTCStrTraits>::CChar>, "Unsupported");
		fg_StrUpperCase(_pTo, _MaxLen, _Source.f_GetStr());
		return _pTo;
	}

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To, mint _MaxLen)
	{
		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;
		fg_StrUpperCase(pStr1, _MaxLen);
		_To.f_SetModified();
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To, tf_CData const *_pSource, mint _MaxLen)
	{
		_To = _pSource;
		fg_StrUpperCase(_To, _MaxLen);
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source, mint _MaxLen)
	{
		_To = _Source;
		fg_StrUpperCase(_To, _MaxLen);
		return _To;
	}

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To)
	{
		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;
		fg_StrLowerCase(pStr1, _To.f_GetLen());
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, tf_CData const *_pSource)
	{
		_To = _pSource;
		fg_StrLowerCase(_To);
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source)
	{
		_To = _Source;
		fg_StrLowerCase(_To);
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrLowerCase(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_Source)
	{
		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;
		static_assert(NTraits::cIsSame<tf_CData, typename TCStr<tf_CTCStrTraits>::CChar>, "Unsupported");
		fg_StrLowerCase(_pTo, _Source.f_GetStr());
		return _pTo;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrLowerCase(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_Source, mint _MaxLen)
	{
		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;
		static_assert(NTraits::cIsSame<tf_CData, typename TCStr<tf_CTCStrTraits>::CChar>, "Unsupported");
		fg_StrLowerCase(_pTo, _Source.f_GetStr(), _MaxLen);
		return _pTo;
	}

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, mint _MaxLen)
	{
		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;
		fg_StrLowerCase(pStr1, _MaxLen);
		_To.f_SetModified();
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, tf_CData const *_pSource, mint _MaxLen)
	{
		_To = _pSource;
		fg_StrLowerCase(_To, _MaxLen);
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source, mint _MaxLen)
	{
		_To = _Source;
		fg_StrLowerCase(_To, _MaxLen);
		return _To;
	}

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrCapitalize(TCStr<tf_CTCStrTraits> &_To)
	{
		static_assert
			(
				sizeof(typename TCStr<tf_CTCStrTraits>::CChar) > 1
				|| (NTraits::cIsSame<typename TCStr<tf_CTCStrTraits>::CChar, ch8> && TCStr<tf_CTCStrTraits>::mc_Type == EStrType_UTF)
				, "Unsupported"
			)
		;
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;

		fg_StrCapitalize(pStr1, _To.f_GetLen());
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrCapitalize(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source)
	{
		_To = _Source;
		fg_StrCapitalize(_To);
		return _To;
	}
}
