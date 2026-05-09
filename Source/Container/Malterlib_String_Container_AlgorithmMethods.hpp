// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small auto TCStr<t_CTCStrTraits>::f_Cmp(tf_CData const *_pStr) const -> typename TCChooseStrCompareType<CChar, tf_CData>::CType
	{
		return fg_StrCmp(*this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits2>
	inline_small auto TCStr<t_CTCStrTraits>::f_Cmp(TCStr<tf_CTCStrTraits2> const &_Str) const -> typename TCChooseStrCompareType<CChar, TCStr<tf_CTCStrTraits2>>::CType
	{
		return fg_StrCmp(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small auto TCStr<t_CTCStrTraits>::f_CmpNoCase(tf_CData const *_pStr) const -> typename TCChooseStrCompareType<CChar, tf_CData>::CType
	{
		return fg_StrCmpNoCase(*this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits2>
	inline_small auto TCStr<t_CTCStrTraits>::f_CmpNoCase(TCStr<tf_CTCStrTraits2> const &_Str) const -> typename TCChooseStrCompareType<CChar, TCStr<tf_CTCStrTraits2>>::CType
	{
		return fg_StrCmpNoCase(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small auto TCStr<t_CTCStrTraits>::f_Cmp(tf_CData const *_pStr, umint _MaxLen) const -> typename TCChooseStrCompareType<CChar, tf_CData>::CType
	{
		return fg_StrCmp(*this, _pStr, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits2>
	inline_small auto TCStr<t_CTCStrTraits>::f_Cmp(TCStr<tf_CTCStrTraits2> const &_Str, umint _MaxLen) const -> typename TCChooseStrCompareType<CChar, TCStr<tf_CTCStrTraits2>>::CType
	{
		return fg_StrCmp(*this, _Str, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small auto TCStr<t_CTCStrTraits>::f_CmpNoCase(tf_CData const *_pStr, umint _MaxLen) const -> typename TCChooseStrCompareType<CChar, tf_CData>::CType
	{
		return fg_StrCmpNoCase(*this, _pStr, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits2>
	inline_small auto TCStr<t_CTCStrTraits>::f_CmpNoCase(TCStr<tf_CTCStrTraits2> const &_Str, umint _MaxLen) const -> typename TCChooseStrCompareType<CChar, TCStr<tf_CTCStrTraits2>>::CType
	{
		return fg_StrCmpNoCase(*this, _Str, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindChar(tf_CData _Char) const
	{
		return fg_StrFindChar(*this, _Char);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharOffset(aint _Start, tf_CData _Char) const
	{
		return fg_StrFindChar(_Start, *this, _Char);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharNoCase(tf_CData _Char) const
	{
		return fg_StrFindCharNoCase(*this, _Char);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharNoCaseOffset(aint _Start, tf_CData _Char) const
	{
		return fg_StrFindCharNoCase(_Start, *this, _Char);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharReverse(tf_CData _Char) const
	{
		return fg_StrFindCharReverse(*this, _Char);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharReverseNoCase(tf_CData _Char) const
	{
		return fg_StrFindCharReverseNoCase(*this, _Char);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindChar(tf_CData _Char, umint _MaxLen) const
	{
		return fg_StrFindChar(*this, _Char, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharOffset(aint _Start, tf_CData _Char, umint _MaxLen) const
	{
		return fg_StrFindChar(_Start, *this, _Char, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharNoCase(tf_CData _Char, umint _MaxLen) const
	{
		return fg_StrFindCharNoCase(*this, _Char, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharNoCaseOffset(aint _Start, tf_CData _Char, umint _MaxLen) const
	{
		return fg_StrFindCharNoCase(_Start, *this, _Char, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharReverse(tf_CData _Char, umint _MaxLen) const
	{
		return fg_StrFindCharReverse(*this, _Char, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharReverseNoCase(tf_CData _Char, umint _MaxLen) const
	{
		return fg_StrFindCharReverseNoCase(*this, _Char, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindChars(tf_CData const *_pChars) const
	{
		return fg_StrFindChars(*this, _pChars);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsNoCase(tf_CData const *_pChars) const
	{
		return fg_StrFindCharsNoCase(*this, _pChars);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsReverse(tf_CData const *_pChars) const
	{
		return fg_StrFindCharsReverse(*this, _pChars);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsReverseNoCase(tf_CData const *_pChars) const
	{
		return fg_StrFindCharsReverseNoCase(*this, _pChars);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindChars(tf_CData const *_pChars, umint _MaxLen) const
	{
		return fg_StrFindChars(*this, _pChars, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsNoCase(tf_CData const *_pChars, umint _MaxLen) const
	{
		return fg_StrFindCharsNoCase(*this, _pChars, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsReverse(tf_CData const *_pChars, umint _MaxLen) const
	{
		return fg_StrFindCharsReverse(*this, _pChars, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsReverseNoCase(tf_CData const *_pChars, umint _MaxLen) const
	{
		return fg_StrFindCharsReverseNoCase(*this, _pChars, _MaxLen);
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindChars(TCStr<tf_CTCStrTraits> const &_Chars) const
	{
		return fg_StrFindChars(*this, _Chars);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Chars) const
	{
		return fg_StrFindCharsNoCase(*this, _Chars);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsReverse(TCStr<tf_CTCStrTraits> const &_Chars) const
	{
		return fg_StrFindCharsReverse(*this, _Chars);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Chars) const
	{
		return fg_StrFindCharsReverseNoCase(*this, _Chars);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindChars(TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen) const
	{
		return fg_StrFindChars(*this, _Chars, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen) const
	{
		return fg_StrFindCharsNoCase(*this, _Chars, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsReverse(TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen) const
	{
		return fg_StrFindCharsReverse(*this, _Chars, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen) const
	{
		return fg_StrFindCharsReverseNoCase(*this, _Chars, _MaxLen);
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_Find(tf_CData const *_pStr) const
	{
		return fg_StrFind(*this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_Find(aint _Start, tf_CData const *_pStr) const
	{
		return fg_StrFind(_Start, *this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindNoCase(tf_CData const *_pStr) const
	{
		return fg_StrFindNoCase(*this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindNoCase(aint _Start, tf_CData const *_pStr) const
	{
		return fg_StrFindNoCase(_Start, *this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_Find(TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrFind(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_Find(aint _Start, TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrFind(_Start, *this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindNoCase(TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrFindNoCase(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrFindNoCase(_Start, *this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverse(tf_CData const *_pStr1) const
	{
		return fg_StrFindReverse(*this, _pStr1);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverseNoCase(tf_CData const *_pStr1) const
	{
		return fg_StrFindReverseNoCase(*this, _pStr1);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverse(TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrFindReverse(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrFindReverseNoCase(*this, _Str);
	}

	/////////

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_Find(tf_CData const *_pStr, umint _MaxLen) const
	{
		return fg_StrFind(*this, _pStr, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_Find(aint _Start, tf_CData const *_pStr, umint _MaxLen) const
	{
		return fg_StrFind(_Start, *this, _pStr, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindNoCase(tf_CData const *_pStr, umint _MaxLen) const
	{
		return fg_StrFindNoCase(*this, _pStr, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindNoCase(aint _Start, tf_CData const *_pStr, umint _MaxLen) const
	{
		return fg_StrFindNoCase(_Start, *this, _pStr, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_Find(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const
	{
		return fg_StrFind(*this, _Str, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_Find(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const
	{
		return fg_StrFind(_Start, *this, _Str, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindNoCase(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const
	{
		return fg_StrFindNoCase(*this, _Str, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const
	{
		return fg_StrFindNoCase(_Start, *this, _Str, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverse(tf_CData const *_pStr1, umint _MaxLen) const
	{
		return fg_StrFindReverse(*this, _pStr1, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverseNoCase(tf_CData const *_pStr1, umint _MaxLen) const
	{
		return fg_StrFindReverseNoCase(*this, _pStr1, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverse(tf_CData const *_pStr1, umint _MaxLen, umint _FindLen) const
	{
		return fg_StrFindReverse(*this, _pStr1, _MaxLen, _FindLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverseNoCase(tf_CData const *_pStr1, umint _MaxLen, umint _FindLen) const
	{
		return fg_StrFindReverseNoCase(*this, _pStr1, _MaxLen, _FindLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverse(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const
	{
		return fg_StrFindReverse(*this, _Str, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const
	{
		return fg_StrFindReverseNoCase(*this, _Str, _MaxLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverse(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen, umint _FindLen) const
	{
		return fg_StrFindReverse(*this, _Str, _MaxLen, _FindLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small aint TCStr<t_CTCStrTraits>::f_FindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen, umint _FindLen) const
	{
		return fg_StrFindReverseNoCase(*this, _Str, _MaxLen, _FindLen);
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small bool TCStr<t_CTCStrTraits>::f_StartsWith(tf_CData const *_pStr) const
	{
		return fg_StrStartsWith(*this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small bool TCStr<t_CTCStrTraits>::f_StartsWithNoCase(tf_CData const *_pStr) const
	{
		return fg_StrStartsWithNoCase(*this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_StartsWith(TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrStartsWith(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_StartsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrStartsWithNoCase(*this, _Str);
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small bool TCStr<t_CTCStrTraits>::f_EndsWith(tf_CData const *_pStr) const
	{
		return fg_StrEndsWith(*this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small bool TCStr<t_CTCStrTraits>::f_EndsWithNoCase(tf_CData const *_pStr) const
	{
		return fg_StrEndsWithNoCase(*this, _pStr);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_EndsWith(TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrEndsWith(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_EndsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str) const
	{
		return fg_StrEndsWithNoCase(*this, _Str);
	}


	template <typename t_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_IsAnsi() const
	{
		return fg_StrIsAnsiLengthAware(f_GetStr(), f_GetLen());
	}


	template <typename t_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_IsAlphaNumeric() const
	{
		CChar const *pStr = *this;
		CChar const *pEndStr = pStr + f_GetLen();
		while (pStr < pEndStr)
		{
			if (!fg_CharIsAlphabetical(*pStr) && !fg_CharIsNumber(*pStr))
				return false;
			++pStr;
		}
		return true;
	}

	template <typename t_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_IsAnsiAlphaNumeric() const
	{
		CChar const *pStr = *this;
		CChar const *pEndStr = pStr + f_GetLen();
		while (pStr < pEndStr)
		{
			if (!fg_CharIsAnsiAlphabetical(*pStr) && !fg_CharIsNumber(*pStr))
				return false;
			++pStr;
		}
		return true;
	}

	template <typename t_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_IsNumeric() const
	{
		if (f_IsEmpty())
			return false;

		CChar const *pStr = *this;
		CChar const *pEndStr = pStr + f_GetLen();
		while (pStr < pEndStr)
		{
			if (!fg_CharIsNumber(*pStr))
				return false;
			++pStr;
		}
		return true;
	}

	template <typename t_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_IsIdentifierStatement() const
	{
		if (f_IsEmpty())
			return false;

		CChar const *pStr = *this;
		CChar const *pEndStr = pStr + f_GetLen();
		if (!(fg_CharIsAlphabetical(*pStr) || *pStr == '_'))
			return false;
		while (pStr < pEndStr)
		{
			if (!fg_CharIsAlphabetical(*pStr) && !fg_CharIsNumber(*pStr) && *pStr != '_')
				return false;
			++pStr;
		}
		return true;
	}

	template <typename t_CTCStrTraits>
	inline_small bool TCStr<t_CTCStrTraits>::f_IsAlphaNumericStatement() const
	{
		if (f_IsEmpty())
			return false;

		CChar const *pStr = *this;
		CChar const *pEndStr = pStr + f_GetLen();
		if (!fg_CharIsAlphabetical(*pStr))
			return false;
		while (pStr < pEndStr)
		{
			if (!fg_CharIsAlphabetical(*pStr) && !fg_CharIsNumber(*pStr))
				return false;
			++pStr;
		}
		return true;
	}

	template <typename t_CTCStrTraits>
	constexpr uint32 TCStr<t_CTCStrTraits>::f_Hash() const
	{
		return fg_StrHash(CImp::f_GetStr(), f_GetLen());
	}

	template <typename t_CTCStrTraits>
	constexpr uint32 TCStr<t_CTCStrTraits>::f_HashDJB2() const
	{
		return fg_StrHashDJB2(CImp::f_GetStr(), f_GetLen());
	}

	template <typename t_CTCStrTraits>
	constexpr uint32 TCStr<t_CTCStrTraits>::f_HashSDBM() const
	{
		return fg_StrHashSDBM(CImp::f_GetStr(), f_GetLen());
	}

	template <typename t_CTCStrTraits>
	inline_small auto TCStr<t_CTCStrTraits>::f_LargestChar() -> CChar
	{
		return fg_StrLargestChar(f_GetStr(), f_GetLen());
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Indent(ch8 const *_pIndent, bool _bIndentFirst, bool _bIndentLastEmpty) const -> TCStr
	{
		auto const *pParse = this->f_GetStr();
		auto const *pParseEnd = pParse + this->f_GetLen();

		TCStr Return;

		while (pParse < pParseEnd)
		{
			auto iSplitPoint = fg_StrFindCharsLengthAware<false, false>(pParse, pParseEnd - pParse, "\r\n");
			if (iSplitPoint < 0)
			{
				if (Return.f_IsEmpty() && !_bIndentFirst)
					return *this;

				Return.f_AddStr(_pIndent);
				Return.f_AddStr(pParse, pParseEnd - pParse);
				return Return;
			}

			auto pParseStart = pParse;

			pParse += iSplitPoint;

			if (*pParse == '\r')
				++pParse;

			if (*pParse == '\n')
				++pParse;

			if (_bIndentFirst || !Return.f_IsEmpty())
				Return.f_AddStr(_pIndent);
			Return.f_AddStr(pParseStart, pParse - pParseStart);
		}

		if (!Return.f_IsEmpty() && _bIndentLastEmpty)
			Return.f_AddStr(_pIndent);

		return Return;
	}


	template <typename t_CTCStrTraits>
	template <bool tf_bRemoveEmpty>
	NContainer::TCVector<TCStr<t_CTCStrTraits>> TCStr<t_CTCStrTraits>::f_SplitEscaped(CChar _Separator) const
	{
		NContainer::TCVector<TCStr<t_CTCStrTraits>> Result;

		auto const *pParse = this->f_GetStr();
		auto const *pParseEnd = pParse + this->f_GetLen();
		auto const *pParseStart = pParse;

		TCStr<t_CTCStrTraits> Next;

		while (pParse < pParseEnd)
		{
			if (*pParse == _Separator)
			{
				Next.f_AddStr(pParseStart, pParse - pParseStart);
				if constexpr (tf_bRemoveEmpty)
				{
					if (Next)
						Result.f_Insert(fg_Move(Next));
				}
				else
					Result.f_Insert(fg_Move(Next));
				++pParse;
				pParseStart = pParse;
				continue;
			}
			else if (*pParse == '\\')
			{
				Next.f_AddStr(pParseStart, pParse - pParseStart);
				++pParse;
				pParseStart = pParse;
				if (*pParse)
					++pParse;
				continue;
			}
			else
				++pParse;
		}

		if (pParse - pParseStart)
			Next.f_AddStr(pParseStart, pParse - pParseStart);

		if constexpr (tf_bRemoveEmpty)
		{
			if (Next)
				Result.f_Insert(fg_Move(Next));
		}
		else
			Result.f_Insert(fg_Move(Next));

		return Result;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CContainer>
	TCStr<t_CTCStrTraits> TCStr<t_CTCStrTraits>::fs_JoinEscaped(tf_CContainer &&_Strings, CChar _Separator)
	{
		CChar EscapeChars[] = {'\\', _Separator, 0};
		TCStr<t_CTCStrTraits> Return;
		bool bFirst = true;
		for (auto &Str : _Strings)
		{
			if (!bFirst)
				Return.f_AddChar(_Separator);
			bFirst = false;
			Return += Str.f_EscapeStrNoQuotes(EscapeChars);
		}
		return Return;
	}

	template <typename t_CTCStrTraits>
	template <bool tf_bRemoveEmpty, typename tf_CStrSeparator>
	NContainer::TCVector<TCStr<t_CTCStrTraits>> TCStr<t_CTCStrTraits>::f_Split(tf_CStrSeparator const &_Separator) const
	{
		NContainer::TCVector<TCStr<t_CTCStrTraits>> Result;

		auto const *pParse = this->f_GetStr();
		auto const *pParseEnd = pParse + this->f_GetLen();
		umint SeparatorLen = fg_StrLen(_Separator);
		auto const *pSeparator = [&]() inline_always_lambda
			{
				if constexpr (requires { _Separator.f_GetStr(); })
					return _Separator.f_GetStr();
				else
					return _Separator;
			}
			()
		;

		while (pParse < pParseEnd)
		{
			auto iSplitPoint = fg_StrFindLengthAware<false>(pParse, pParseEnd - pParse, pSeparator, SeparatorLen);
			if (iSplitPoint < 0)
			{
				if constexpr (tf_bRemoveEmpty)
				{
					if (pParseEnd != pParse)
						Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, pParseEnd - pParse));
				}
				else
					Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, pParseEnd - pParse));
				return Result;
			}
			if constexpr (tf_bRemoveEmpty)
			{
				if (iSplitPoint)
					Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, iSplitPoint));
			}
			else
				Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, iSplitPoint));
			pParse += iSplitPoint + SeparatorLen;
		}

		if constexpr (!tf_bRemoveEmpty)
			Result.f_Insert();

		return Result;
	}

	template <typename t_CTCStrTraits>
	template <bool tf_bRemoveEmpty>
	NContainer::TCVector<TCStr<t_CTCStrTraits>> TCStr<t_CTCStrTraits>::f_SplitLine() const
	{
		NContainer::TCVector<TCStr<t_CTCStrTraits>> Result;

		auto const *pParse = this->f_GetStr();
		auto const *pParseEnd = pParse + this->f_GetLen();

		while (pParse < pParseEnd)
		{
			auto iSplitPoint = fg_StrFindCharsLengthAware<false, false>(pParse, pParseEnd - pParse, "\r\n");
			if (iSplitPoint < 0)
			{
				if constexpr (tf_bRemoveEmpty)
				{
					if (pParseEnd != pParse)
						Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, pParseEnd - pParse));
				}
				else
					Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, pParseEnd - pParse));
				return Result;
			}
			if constexpr (tf_bRemoveEmpty)
			{
				if (iSplitPoint)
					Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, iSplitPoint));
			}
			else
				Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, iSplitPoint));

			pParse += iSplitPoint;
			if (*pParse == '\r')
				++pParse;
			if (*pParse == '\n')
				++pParse;
		}

		if constexpr (!tf_bRemoveEmpty)
			Result.f_Insert();

		return Result;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CContainer, typename tf_CStrSeparator>
	TCStr<t_CTCStrTraits> TCStr<t_CTCStrTraits>::fs_Join(tf_CContainer &&_Strings, tf_CStrSeparator const &_Separator)
	{
		TCStr<t_CTCStrTraits> Return;
		bool bFirst = true;
		for (auto &Str : _Strings)
		{
			if (!bFirst)
				Return += _Separator;
			bFirst = false;
			Return += fg_ForwardAs<tf_CContainer>(Str);
		}
		return Return;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_UpperCase() const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrUpperCase(Temp);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_UpperCase(umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrUpperCase(Temp, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_LowerCase() const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrLowerCase(Temp);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_LowerCase(umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrLowerCase(Temp, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Untabify(umint _TabLength) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrUntabify(Temp, _TabLength);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData, typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_Replace(tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplace(Temp, _pStrFind, _pStrReplace);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_Replace(TCStr<tf_CTCStrTraits> const &_StrFind, tf_CData const *_pStrReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplace(Temp, _StrFind, _pStrReplace);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_Replace(tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits> const &_StrReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplace(Temp, _pStrFind, _StrReplace);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	auto TCStr<t_CTCStrTraits>::f_Replace(TCStr<tf_CTCStrTraits> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplace(Temp, _StrFind, _StrReplace);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CData, typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_ReplaceNoCase(tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceNoCase(Temp, _pStrFind, _pStrReplace);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_ReplaceNoCase(TCStr<tf_CTCStrTraits> const &_StrFind, tf_CData const *_pStrReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceNoCase(Temp, _StrFind, _pStrReplace);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_ReplaceNoCase(tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits> const &_StrReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceNoCase(Temp, _pStrFind, _StrReplace);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	auto TCStr<t_CTCStrTraits>::f_ReplaceNoCase(TCStr<tf_CTCStrTraits> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceNoCase(Temp, _StrFind, _StrReplace);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CData, typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_ReplaceChar(tf_CData _CharFind, tf_CData2 _CharReplace) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceChar(Temp, _CharFind, _CharReplace);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CData, typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_Replace(tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplace(Temp, _pStrFind, _pStrReplace, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_Replace(TCStr<tf_CTCStrTraits> const &_StrFind, tf_CData const *_pStrReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplace(Temp, _StrFind, _pStrReplace, _MaxLen);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_Replace(tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits> const &_StrReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplace(Temp, _pStrFind, _StrReplace, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	auto TCStr<t_CTCStrTraits>::f_Replace(TCStr<tf_CTCStrTraits> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplace(Temp, _StrFind, _StrReplace, _MaxLen);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CData, typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_ReplaceNoCase(tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceNoCase(Temp, _pStrFind, _pStrReplace, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_ReplaceNoCase(TCStr<tf_CTCStrTraits> const &_StrFind, tf_CData2 const *_pStrReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceNoCase(Temp, _StrFind, _pStrReplace, _MaxLen);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_ReplaceNoCase(tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits> const &_StrReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceNoCase(Temp, _pStrFind, _StrReplace, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	auto TCStr<t_CTCStrTraits>::f_ReplaceNoCase(TCStr<tf_CTCStrTraits> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceNoCase(Temp, _StrFind, _StrReplace, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData, typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_ReplaceChar(tf_CData _CharFind, tf_CData2 _CharReplace, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReplaceChar(Temp, _CharFind, _CharReplace, _MaxLen);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_Insert(aint _StartChar, tf_CData2 const *_pStrInsert) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrInsert(Temp, _StartChar, _pStrInsert);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Insert(aint _StartChar, TCStr<tf_CTCStrTraits> const &_StrInsert) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrInsert(Temp, _StartChar, _StrInsert);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData2>
	auto TCStr<t_CTCStrTraits>::f_Insert(aint _StartChar, tf_CData2 const *_pStrInsert, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrInsert(Temp, _StartChar, _pStrInsert, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Insert(aint _StartChar, TCStr<tf_CTCStrTraits> const &_StrInsert, umint _MaxLen) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrInsert(Temp, _StartChar, _StrInsert, _MaxLen);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_EscapeStr() const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrEscapeStr(Temp, *this);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CEscapeChar>
	auto TCStr<t_CTCStrTraits>::f_EscapeStr(tf_CEscapeChar const *_pEscapeChars) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrEscapeStr(Temp, *this, _pEscapeChars);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CEscapeChar, typename tf_CReplaceChars>
	auto TCStr<t_CTCStrTraits>::f_EscapeStr(tf_CEscapeChar const *_pEscapeChars, tf_CReplaceChars const *_pReplaceChars) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrEscapeStr(Temp, *this, _pEscapeChars, _pReplaceChars);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_EscapeStrNoQuotes() const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrEscapeStrNoQuotes(Temp, *this);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CEscapeChar>
	auto TCStr<t_CTCStrTraits>::f_EscapeStrNoQuotes(tf_CEscapeChar const *_pEscapeChars) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrEscapeStrNoQuotes(Temp, *this, _pEscapeChars);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CEscapeChar, typename tf_CReplaceChars>
	auto TCStr<t_CTCStrTraits>::f_EscapeStrNoQuotes(tf_CEscapeChar const *_pEscapeChars, tf_CReplaceChars const *_pReplaceChars) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrEscapeStrNoQuotes(Temp, *this, _pEscapeChars, _pReplaceChars);
		return Temp;
	}


	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Delete(aint _StartChar, umint _nChars) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrDelete(Temp, _StartChar, _nChars);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Left(umint _nChars) const -> TCStr
	{
		TCStr Temp;
		umint Length = this->f_GetLen();
		umint nChars = fg_Min(_nChars, Length);
		if (nChars == Length)
			return *this;
		Temp.f_AddStr(this->f_GetStr(), nChars);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Extract(aint _StartChar, umint _nChars) const -> TCStr
	{
		if (_StartChar < 0)
			return *this;
		TCStr Temp;
		umint Length = this->f_GetLen();
		if (_StartChar == 0 && _nChars == Length)
			return *this;
		umint Start = fg_Min(umint(_StartChar), Length);
		umint nChars = fg_Min(Length - Start, _nChars);
		Temp.f_AddStr(this->f_GetStr() + Start, nChars);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Extract(aint _StartChar) const -> TCStr
	{
		if (_StartChar <= 0)
			return *this;
		TCStr Temp;
		umint Length = this->f_GetLen();
		umint Start = fg_Min(umint(_StartChar), Length);
		Temp.f_AddStr(this->f_GetStr() + Start, Length - Start);
		return Temp;
	}

	/*
	auto TCStr<t_CTCStrTraits>::f_Slice(aint _iStart, aint _iEnd) const -> TCStr

		Returns the substring from unit _iStart -> _iEnd
		(Not including unit _iEnd)

		If _Start or _End is < 0 they are used as offsets from the end of the string.

		(ala Python slice)
	*/
	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Slice(aint _iStart, aint _iEnd) const -> TCStr
	{
		umint Length = this->f_GetLen();
		umint Start;
		umint End;

		// Find first & last unit in slice
		if (_iStart < 0)
			Start = Length + _iStart;
		else
			Start = _iStart;

		if (_iEnd < 0)
			End = Length + _iEnd;
		else
			End = _iEnd;

		if (End > Length)
			End = Length;

		// No units in slice
		if (Start > End)
			return TCStr();

		// Slice is whole string
		if (Start == 0 && End == Length)
			return *this;

		TCStr Temp;
		umint nChars = End - Start;
		Temp.f_AddStr(this->f_GetStr() + Start, nChars);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Reverse() const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrReverse(Temp);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Right(umint _nChars) const -> TCStr
	{
		TCStr Temp;
		umint Length = this->f_GetLen();
		umint nChars = fg_Min(Length, _nChars);
		Temp.f_AddStr(this->f_GetStr() + (Length - nChars), nChars);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_TrimLeft(tf_CData const *_pCharsToTrim) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrTrimLeft(Temp, _pCharsToTrim);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_TrimLeft() const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrTrimLeft(Temp);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_TrimRight(tf_CData const *_pCharsToTrim) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrTrimRight(Temp, _pCharsToTrim);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_TrimRight() const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrTrimRight(Temp);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	auto TCStr<t_CTCStrTraits>::f_Trim(tf_CData const *_pCharsToTrim) const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrTrim(Temp, _pCharsToTrim);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::f_Trim() const -> TCStr
	{
		TCStr Temp = *this;
		fg_StrTrim(Temp);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStr>
	auto TCStr<t_CTCStrTraits>::f_RemovePrefix(tf_CStr const &_ToFind) const -> TCStr
	{
		if (!f_StartsWith(_ToFind))
			return *this;
		return f_Extract(fg_StrLen(_ToFind));
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStr>
	auto TCStr<t_CTCStrTraits>::f_RemoveSuffix(tf_CStr const &_ToFind) const -> TCStr
	{
		if (!f_EndsWith(_ToFind))
			return *this;
		return f_Left(f_GetLen() - fg_StrLen(_ToFind));
	}
}
