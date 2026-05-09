// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		return fg_StrFindCharLengthAware<false>(_Str.f_GetStr(), _Char, _Str.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		if (_Start < 0)
			return -1;
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		return fg_StrAdd(Start, fg_StrFindCharLengthAware<false>(_Str.f_GetStr() + Start, _Char, _Str.f_GetLen() - Start));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		return fg_StrFindCharLengthAware<true>(_Str.f_GetStr(), _Char, _Str.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		if (_Start < 0)
			return -1;
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		return fg_StrAdd(Start, fg_StrFindCharLengthAware<true>(_Str.f_GetStr() + Start, _Char, _Str.f_GetLen() - Start));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		return fg_StrFindCharReverseLengthAware<false>(_Str.f_GetStr(), _Char, _Str.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char)
	{
		return fg_StrFindCharReverseLengthAware<true>(_Str.f_GetStr(), _Char, _Str.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, umint _MaxLen)
	{
		return fg_StrFindCharLengthAware<false>(_Str.f_GetStr(), _Char, fg_Min(_Str.f_GetLen(), _MaxLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, umint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		return fg_StrAdd(Start, fg_StrFindCharLengthAware<false>(_Str.f_GetStr() + Start, _Char, fg_Min(_Str.f_GetLen() - Start, _MaxLen)));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, umint _MaxLen)
	{
		return fg_StrFindCharLengthAware<true>(_Str.f_GetStr(), _Char, fg_Min(_Str.f_GetLen(), _MaxLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, umint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		return fg_StrAdd(Start, fg_StrFindCharLengthAware<true>(_Str.f_GetStr() + Start, _Char, fg_Min(_Str.f_GetLen() - Start, _MaxLen)));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, umint _MaxLen)
	{
		return fg_StrFindCharReverseLengthAware<false>(_Str.f_GetStr(), _Char, fg_Min(_Str.f_GetLen(), _MaxLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, umint _MaxLen)
	{
		return fg_StrFindCharReverseLengthAware<true>(_Str.f_GetStr(), _Char, fg_Min(_Str.f_GetLen(), _MaxLen));
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars)
	{
		return fg_StrFindCharsLengthAware<false, false>(_Str.f_GetStr(), _Str.f_GetLen(), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars)
	{
		return fg_StrFindCharsLengthAware<true, false>(_Str.f_GetStr(), _Str.f_GetLen(), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars)
	{
		return fg_StrFindCharsLengthAware<false, true>(_Str.f_GetStr(), _Str.f_GetLen(), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars)
	{
		return fg_StrFindCharsLengthAware<true, true>(_Str.f_GetStr(), _Str.f_GetLen(), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, umint _MaxLen)
	{
		return fg_StrFindCharsLengthAware<false, false>(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, umint _MaxLen)
	{
		return fg_StrFindCharsLengthAware<true, false>(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, umint _MaxLen)
	{
		return fg_StrFindCharsLengthAware<false, true>(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _pChars);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, umint _MaxLen)
	{
		return fg_StrFindCharsLengthAware<true, true>(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _pChars);
	}


	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindChars(_Str.f_GetStr(), _Str.f_GetLen(), _Chars.f_GetStr(), _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsNoCase(_Str.f_GetStr(), _Str.f_GetLen(), _Chars.f_GetStr(), _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverse(_Str.f_GetStr(), _Str.f_GetLen(), _Chars.f_GetStr(), _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverseNoCase(_Str.f_GetStr(), _Str.f_GetLen(), _Chars.f_GetStr(), _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, umint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindChars(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _Chars.f_GetStr(), _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, umint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsNoCase(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _Chars.f_GetStr(), _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, umint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverse(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _Chars.f_GetStr(), _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, umint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverseNoCase(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _Chars.f_GetStr(), _Chars.f_GetLen());
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars)
	{
		return fg_StrFindChars(_pStr1, _Chars.f_GetStr(), TCLimitsInt<umint>::mc_Max, _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars)
	{
		return fg_StrFindCharsNoCase(_pStr1, _Chars.f_GetStr(), TCLimitsInt<umint>::mc_Max, _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars)
	{
		return fg_StrFindCharsReverse(_pStr1, _Chars.f_GetStr(), TCLimitsInt<umint>::mc_Max, _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars)
	{
		return fg_StrFindCharsReverseNoCase(_pStr1, _Chars.f_GetStr(), TCLimitsInt<umint>::mc_Max, _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen)
	{
		return fg_StrFindChars(_pStr1, _Chars.f_GetStr(), _MaxLen, _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen)
	{
		return fg_StrFindCharsNoCase(_pStr1, _Chars.f_GetStr(), _MaxLen, _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen)
	{
		return fg_StrFindCharsReverse(_pStr1, _Chars.f_GetStr(), _MaxLen, _Chars.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen)
	{
		return fg_StrFindCharsReverseNoCase(_pStr1, _Chars.f_GetStr(), _MaxLen, _Chars.f_GetLen());
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrFindLengthAware<false>(_Str.f_GetStr(), _Str.f_GetLen(), _pToFind);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		if (_Start < 0)
			return -1;
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		return fg_StrAdd(Start, fg_StrFindLengthAware<false>(_Str.f_GetStr() + Start, _Str.f_GetLen() - Start, _pToFind));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrFindLengthAware<true>(_Str.f_GetStr(), _Str.f_GetLen(), _pToFind);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		if (_Start < 0)
			return -1;
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		return fg_StrAdd(Start, fg_StrFindLengthAware<true>(_Str.f_GetStr() + Start, _Str.f_GetLen() - Start, _pToFind));
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrFind(_pStr1, _ToFind.f_GetStr(), TCLimitsInt<umint>::mc_Max, _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrFindNoCase(_pStr1, _ToFind.f_GetStr(), TCLimitsInt<umint>::mc_Max, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Str.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetStr(), _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		if (_Start < 0)
			return -1;
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		auto Ret = fg_StrFind(_Str.f_GetStr() + Start, _Str.f_GetLen() - Start, _ToFind.f_GetStr(), _ToFind.f_GetLen());
		return fg_StrAdd(Start, Ret);
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Str.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetStr(), _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		if (_Start < 0)
			return -1;
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		auto Ret = fg_StrFindNoCase(_Str.f_GetStr() + Start, _Str.f_GetLen() - Start, _ToFind.f_GetStr(), _ToFind.f_GetLen());
		return fg_StrAdd(Start, Ret);
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
		return fg_StrFindReverse<false, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse<true, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetLen());
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, umint _MaxLen)
	{
		return fg_StrFindLengthAware<false>(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _pToFind);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, umint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		return fg_StrAdd(Start, fg_StrFindLengthAware<false>(_Str.f_GetStr() + Start, fg_Min(_Str.f_GetLen() - Start, _MaxLen), _pToFind));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, umint _MaxLen)
	{
		return fg_StrFindLengthAware<true>(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _pToFind);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, umint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		return fg_StrAdd(Start, fg_StrFindLengthAware<true>(_Str.f_GetStr() + Start, fg_Min(_Str.f_GetLen() - Start, _MaxLen), _pToFind));
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, umint _MaxLen)
	{
		return fg_StrFind(_pStr1, _ToFind.f_GetStr(), _MaxLen, _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, umint _MaxLen)
	{
		return fg_StrFindNoCase(_pStr1, _ToFind.f_GetStr(), _MaxLen, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, umint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _ToFind.f_GetStr(), _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, umint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		auto Ret = fg_StrFind(_Str.f_GetStr() + Start, fg_Min(_Str.f_GetLen() - Start, _MaxLen), _ToFind.f_GetStr(), _ToFind.f_GetLen());
		return fg_StrAdd(Start, Ret);
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, umint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Str.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _ToFind.f_GetStr(), _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, umint _MaxLen)
	{
		if (_Start < 0)
			return -1;
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		auto Start = fg_Min(_Start, _Str.f_GetLen());
		auto Ret = fg_StrFindNoCase(_Str.f_GetStr() + Start, fg_Min(_Str.f_GetLen() - Start, _MaxLen), _ToFind.f_GetStr(), _ToFind.f_GetLen());
		return fg_StrAdd(Start, Ret);
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, umint _MaxLen)
	{
		return fg_StrFindReverse<false, true, false>(_Str.f_GetStr(), _pToFind, fg_Min(_Str.f_GetLen(), _MaxLen), 0);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, umint _MaxLen)
	{
		return fg_StrFindReverse<true, true, false>(_Str.f_GetStr(), _pToFind, fg_Min(_Str.f_GetLen(), _MaxLen), 0);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, umint _MaxLen, umint _FindLen)
	{
		return fg_StrFindReverse<false, true, true>(_Str.f_GetStr(), _pToFind, fg_Min(_Str.f_GetLen(), _MaxLen), _FindLen);
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, umint _MaxLen, umint _FindLen)
	{
		return fg_StrFindReverse<true, true, true>(_Str.f_GetStr(), _pToFind, fg_Min(_Str.f_GetLen(), _MaxLen), _FindLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, umint _MaxLen)
	{
		return fg_StrFindReverse<false, true, true>(_pStr1, _ToFind.f_GetStr(), _MaxLen, _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, umint _MaxLen)
	{
		return fg_StrFindReverse<true, true, true>(_pStr1, _ToFind.f_GetStr(), _MaxLen, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, umint _MaxLen, umint _FindLen)
	{
		return fg_StrFindReverse<false, true, true>(_pStr1, _ToFind.f_GetStr(), _MaxLen, fg_Min(_ToFind.f_GetLen(), _FindLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, umint _MaxLen, umint _FindLen)
	{
		return fg_StrFindReverse<true, true, true>(_pStr1, _ToFind.f_GetStr(), _MaxLen, fg_Min(_ToFind.f_GetLen(), _FindLen));
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, umint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse<false, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _ToFind.f_GetLen());
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, umint _MaxLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse<true, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, umint _MaxLen, umint _FindLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse<false, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), fg_Min(_ToFind.f_GetLen(), _FindLen));
	}
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, umint _MaxLen, umint _FindLen)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse<true, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), fg_Min(_Str.f_GetLen(), _MaxLen), fg_Min(_ToFind.f_GetLen(), _FindLen));
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWith(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrStartsWith<false, true, true, false, false>(_Str.f_GetStr(), _pToFind, _Str.f_GetLen(), 0);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrStartsWith<true, true, true, false, false>(_Str.f_GetStr(), _pToFind, _Str.f_GetLen(), 0);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWith(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrStartsWith<false, false, false, true, true>(_pStr1, _ToFind.f_GetStr(), 0, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWithNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrStartsWith<true, false, false, true, true>(_pStr1, _ToFind.f_GetStr(), 0, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrStartsWith(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrStartsWith<false, true, true, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrStartsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrStartsWith<true, true, true, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetLen());
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWith(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrEndsWith<false, true, true, false, false>(_Str.f_GetStr(), _pToFind, _Str.f_GetLen(), 0);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind)
	{
		return fg_StrEndsWith<true, true, true, false, false>(_Str.f_GetStr(), _pToFind, _Str.f_GetLen(), 0);
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWith(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrEndsWith<false, false, false, true, true>(_pStr1, _ToFind.f_GetStr(), 0, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWithNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind)
	{
		return fg_StrEndsWith<true, false, false, true, true>(_pStr1, _ToFind.f_GetStr(), 0, _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrEndsWith(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrEndsWith<false, true, true, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrEndsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind)
	{
		static_assert(TCIsStrCompatible<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrEndsWith<true, true, true, true, true>(_Str.f_GetStr(), _ToFind.f_GetStr(), _Str.f_GetLen(), _ToFind.f_GetLen());
	}
}
