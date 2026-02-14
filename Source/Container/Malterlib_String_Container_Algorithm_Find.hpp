// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		return fg_StrFindChar(_Str.f_GetStr(), _Char);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		if (_Start < 0)
			return -1;
		return fg_StrAdd(_Start, fg_StrFindChar(_Str.f_GetStr() + fg_Min(_Start, _Str.f_GetLen()), _Char));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		return fg_StrFindCharNoCase(_Str.f_GetStr(), _Char);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		if (_Start < 0)
			return -1;
		return fg_StrAdd(_Start, fg_StrFindCharNoCase(_Str.f_GetStr() + fg_Min(_Start, _Str.f_GetLen()), _Char));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		return fg_StrFindCharReverse(_Str.f_GetStr(), _Char);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		return fg_StrFindCharReverseNoCase(_Str.f_GetStr(), _Char);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen)
	{
		return fg_StrFindChar(_Str.f_GetStr(), _Char, _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		return fg_StrAdd(_Start, fg_StrFindChar(_Str.f_GetStr() + fg_Min(_Start, _Str.f_GetLen()), _Char, _MaxLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen)
	{
		return fg_StrFindCharNoCase(_Str.f_GetStr(), _Char, _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		return fg_StrAdd(_Start, fg_StrFindCharNoCase(_Str.f_GetStr() + fg_Min(_Start, _Str.f_GetLen()), _Char, _MaxLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen)
	{
		return fg_StrFindCharReverse(_Str.f_GetStr(), _Char, _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen)
	{
		return fg_StrFindCharReverseNoCase(_Str.f_GetStr(), _Char, _MaxLen);
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars)
	{
		return fg_StrFindChars(_Str.f_GetStr(), _Str.f_GetLen(), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars)
	{
		return fg_StrFindCharsNoCase(_Str.f_GetStr(), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars)
	{
		return fg_StrFindCharsReverse(_Str.f_GetStr(), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars)
	{
		return fg_StrFindCharsReverseNoCase(_Str.f_GetStr(), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, mint _MaxLen)
	{
		return fg_StrFindChars(_Str.f_GetStr(), _pChars, _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, mint _MaxLen)
	{
		return fg_StrFindCharsNoCase(_Str.f_GetStr(), _pChars, _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, mint _MaxLen)
	{
		return fg_StrFindCharsReverse(_Str.f_GetStr(), _pChars, _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, mint _MaxLen)
	{
		return fg_StrFindCharsReverseNoCase(_Str.f_GetStr(), _pChars, _MaxLen);
	}


	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindChars(_Str.f_GetStr(), _Chars.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsNoCase(_Str.f_GetStr(), _Chars.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverse(_Str.f_GetStr(), _Chars.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverseNoCase(_Str.f_GetStr(), _Chars.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindChars(_Str.f_GetStr(), _Chars.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsNoCase(_Str.f_GetStr(), _Chars.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverse(_Str.f_GetStr(), _Chars.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverseNoCase(_Str.f_GetStr(), _Chars.f_GetStr(), _MaxLen);
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars)
	{
		return fg_StrFindChars(_pStr1, _Chars.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars)
	{
		return fg_StrFindCharsNoCase(_pStr1, _Chars.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars)
	{
		return fg_StrFindCharsReverse(_pStr1, _Chars.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars)
	{
		return fg_StrFindCharsReverseNoCase(_pStr1, _Chars.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, mint _MaxLen)
	{
		return fg_StrFindChars(_pStr1, _Chars.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, mint _MaxLen)
	{
		return fg_StrFindCharsNoCase(_pStr1, _Chars.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, mint _MaxLen)
	{
		return fg_StrFindCharsReverse(_pStr1, _Chars.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, mint _MaxLen)
	{
		return fg_StrFindCharsReverseNoCase(_pStr1, _Chars.f_GetStr(), _MaxLen);
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrFind(_Str.f_GetStr(), _pToFind);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		if (_Start < 0)
			return -1;
		return fg_StrAdd(_Start, fg_StrFind(_Str.f_GetStr() + fg_Min(_Start, _Str.f_GetLen()), _pToFind));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrFindNoCase(_Str.f_GetStr(), _pToFind);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		if (_Start < 0)
			return -1;
		return fg_StrAdd(_Start, fg_StrFindNoCase(_Str.f_GetStr() + fg_Min(_Start, _Str.f_GetLen()), _pToFind));
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrFind(_pStr1, _ToFind.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrFindNoCase(_pStr1, _ToFind.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Str.f_GetStr(), _ToFind.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		if (_Start < 0)
			return -1;
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Start, _Str, _ToFind.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Str.f_GetStr(), _ToFind.f_GetStr());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		if (_Start < 0)
			return -1;
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Start, _Str, _ToFind.f_GetStr());
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrFindReverse<false, true, false>(_Str.f_GetStr(), _pToFind, _Str.f_GetLen(), 0);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrFindReverse<true, true, false>(_Str.f_GetStr(), _pToFind, _Str.f_GetLen(), 0);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrFindReverse<false, false, true>(_pStr1, _ToFind.f_GetStr(), 0, _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrFindReverse<true, false, true>(_pStr1, _ToFind.f_GetStr(), 0, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse(_Str.f_GetStr(), _ToFind.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverseNoCase(_Str.f_GetStr(), _ToFind.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetLen());
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen)
	{
		return fg_StrFind(_Str.f_GetStr(), _pToFind, _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		return fg_StrAdd(_Start, fg_StrFind(_Str.f_GetStr() + fg_Min(_Start, _Str.f_GetLen()), _pToFind, _MaxLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen)
	{
		return fg_StrFindNoCase(_Str.f_GetStr(), _pToFind, _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		return fg_StrAdd(_Start, fg_StrFindNoCase(_Str.f_GetStr() + fg_Min(_Start, _Str.f_GetLen()), _pToFind, _MaxLen));
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen)
	{
		return fg_StrFind(_pStr1, _ToFind.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen)
	{
		return fg_StrFindNoCase(_pStr1, _ToFind.f_GetStr(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Str.f_GetStr(), _ToFind.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Start, _Str, _ToFind.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Str.f_GetStr(), _ToFind.f_GetStr(), _MaxLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Start, _Str, _ToFind.f_GetStr(), _MaxLen);
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen)
	{
		return fg_StrFindReverse<false, true, false>(_Str.f_GetStr(), _pToFind, fg_Min(_Str.f_GetLen(), _MaxLen), 0);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen)
	{
		return fg_StrFindReverse<true, true, false>(_Str.f_GetStr(), _pToFind, fg_Min(_Str.f_GetLen(), _MaxLen), 0);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen, mint _FindLen)
	{
		return fg_StrFindReverse<false, true, true>(_Str.f_GetStr(), _pToFind, fg_Min(_Str.f_GetLen(), _MaxLen), _FindLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen, mint _FindLen)
	{
		return fg_StrFindReverse<true, true, true>(_Str.f_GetStr(), _pToFind, fg_Min(_Str.f_GetLen(), _MaxLen), _FindLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen)
	{
		return fg_StrFindReverse<false, true, true>(_pStr1, _ToFind.f_GetStr(), _MaxLen, _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen)
	{
		return fg_StrFindReverse<true, true, true>(_pStr1, _ToFind.f_GetStr(), _MaxLen, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen, mint _FindLen)
	{
		return fg_StrFindReverse<false, true, true>(_pStr1, _ToFind.f_GetStr(), _MaxLen, fg_Min(_ToFind.f_GetLen(), _FindLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen, mint _FindLen)
	{
		return fg_StrFindReverse<true, true, true>(_pStr1, _ToFind.f_GetStr(), _MaxLen, fg_Min(_ToFind.f_GetLen(), _FindLen));
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse(_Str.f_GetStr(), _ToFind.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverseNoCase(_Str.f_GetStr(), _ToFind.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen, mint _FindLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse(_Str.f_GetStr(), _ToFind.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), fg_Min(_ToFind.f_GetLen(), _FindLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen, mint _FindLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverseNoCase(_Str.f_GetStr(), _ToFind.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), fg_Min(_ToFind.f_GetLen(), _FindLen));
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWith(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrStartsWith(_Str.f_GetStr(), _pToFind);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrStartsWithNoCase(_Str.f_GetStr(), _pToFind);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWith(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrStartsWith(_pStr1, _ToFind.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWithNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrStartsWithNoCase(_pStr1, _ToFind.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrStartsWith(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrStartsWith(_Str.f_GetStr(), _ToFind.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrStartsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrStartsWithNoCase(_Str.f_GetStr(), _ToFind.f_GetStr());
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWith(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrEndsWith(_Str.f_GetStr(), _pToFind);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrEndsWithNoCase(_Str.f_GetStr(), _pToFind);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWith(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrEndsWith(_pStr1, _ToFind.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWithNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrEndsWithNoCase(_pStr1, _ToFind.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrEndsWith(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrEndsWith(_Str.f_GetStr(), _ToFind.f_GetStr());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrEndsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrEndsWithNoCase(_Str.f_GetStr(), _ToFind.f_GetStr());
	}
}
