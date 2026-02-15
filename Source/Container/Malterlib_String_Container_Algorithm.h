// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	// Static functions
	template <typename tf_CTCStrTraits>
	inline_small mint fg_StrLen(TCStr<tf_CTCStrTraits> const &_Str);

	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrHashDJB2(TCStr<tf_CTCStrTraits> const &_Str);

	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrHashSDBM(TCStr<tf_CTCStrTraits> const &_Str);

	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrHash(TCStr<tf_CTCStrTraits> const &_Str);

	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrIsAnsi(TCStr<tf_CTCStrTraits> const &_Str);
	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrIsAnsi(TCStr<tf_CTCStrTraits> const &_Str, mint _MaxLen);

	template <typename tf_CTCStrTraits>
	bool fg_StrIsEmpty(TCStr<tf_CTCStrTraits> const &_Str);
	template <typename tf_CTCStrTraits>
	bool fg_StrIsEmpty(TCFormat<tf_CTCStrTraits> const &_Str);

	template <typename tf_CTCStrTraits>
	inline_small NTraits::TCUnsigned<typename TCStr<tf_CTCStrTraits>::CMaxChar> fg_StrLargestChar(TCStr<tf_CTCStrTraits> const &_Str);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrCopy(TCStr<tf_CTCStrTraits> &_To, tf_CData const *_pFrom);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrCopy(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_From);
	template <typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrCopy(TCStr<tf_CTCStrTraits1> &_To, TCStr<tf_CTCStrTraits2> const &_From);
	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small tf_CData *fg_StrCopy(tf_CData *_pTo, TCStr<tf_CTCStrTraits1> const &_From, mint _MaxLen);
	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrCopy(TCStr<tf_CTCStrTraits1> &_To, tf_CData const *_pFrom, mint _MaxLen);
	template <typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrCopy(TCStr<tf_CTCStrTraits1> &_To, TCStr<tf_CTCStrTraits2> const &_From, mint _MaxLen);

	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrMove(TCStr<tf_CTCStrTraits1> &_To, tf_CData const *_pFrom);
	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small tf_CData *fg_StrMove(tf_CData *_pTo, TCStr<tf_CTCStrTraits1> const &_From);
	template <typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrMove(TCStr<tf_CTCStrTraits1> &_To, TCStr<tf_CTCStrTraits2> const &_From);
	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small tf_CData *fg_StrMove(tf_CData *_pTo, TCStr<tf_CTCStrTraits1> const &_From, mint _MaxLen);
	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrMove(TCStr<tf_CTCStrTraits1> &_To, tf_CData const *_pFrom, mint _MaxLen);
	template <typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrMove(TCStr<tf_CTCStrTraits1> &_To, TCStr<tf_CTCStrTraits2> const &_From, mint _MaxLen);

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To);
	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrUpperCase(TCStr<tf_CTCStrTraits1> &_To, tf_CData const *_pSource);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrUpperCase(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_Source);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrUpperCase(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_Source, mint _MaxLen);
	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To, tf_CData const *_pSource, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrUpperCase(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source, mint _MaxLen);

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, tf_CData const *_pSource);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrLowerCase(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_Source);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrLowerCase(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_Source, mint _MaxLen);
	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, tf_CData const *_pSource, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrLowerCase(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source, mint _MaxLen);

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrCapitalize(TCStr<tf_CTCStrTraits> &_To);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrCapitalize(TCStr<tf_CTCStrTraits> &_To, TCStr<tf_CTCStrTraits2> const &_Source);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmp(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmp(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2, mint _MaxLen)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	;

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	;
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pStr2, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, tf_CData>::CType fg_StrCmpNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Str2, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small auto fg_StrCmpNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Str2, mint _MaxLen)
		-> typename TCChooseStrCompareType<TCStr<tf_CTCStrTraits>, TCStr<tf_CTCStrTraits2>>::CType
	;

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChar(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData _Char, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindChars(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindChars(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pChars, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindCharsReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_Chars, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_Chars, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFind(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen, mint _FindLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverse(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen, mint _FindLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverse(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen, mint _FindLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind, mint _MaxLen, mint _FindLen);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrFindReverseNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind, mint _MaxLen, mint _FindLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrFindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind, mint _MaxLen, mint _FindLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWith(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWith(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrStartsWith(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrStartsWithNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrStartsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWith(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWith(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrEndsWith(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, tf_CData const *_pToFind);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small aint fg_StrEndsWithNoCase(tf_CData const *_pStr1, TCStr<tf_CTCStrTraits> const &_ToFind);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small aint fg_StrEndsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str, TCStr<tf_CTCStrTraits2> const &_ToFind);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrUntabify(TCStr<tf_CTCStrTraits> &_Str, mint _TabSize);

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits2> const &_StrFind, tf_CData2 const *_pStrReplace);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits1> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace);
	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits2> const &_StrFind, tf_CData const *_pStrReplace, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits1> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, mint _LenFind, tf_CData2 const *_pStrReplace, mint _LenReplace);
	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, mint _LenFind, tf_CData2 const *_pStrReplace, mint _LenReplace, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits2> const &_StrFind, tf_CData2 const *_pStrReplace);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, const TCStr<tf_CTCStrTraits2> &_StrReplace);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits1> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace);
	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits2> const &_StrFind, tf_CData const *_pStrReplace, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits1> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, mint _LenFind, tf_CData2 const *_pStrReplace, mint _LenReplace);
	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pFind, mint _LenFind, tf_CData2 const *_pReplace, mint _LenReplace, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceChar(TCStr<tf_CTCStrTraits> &_Str, tf_CData _CharFind, tf_CData2 _CharReplace);
	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceChar(TCStr<tf_CTCStrTraits> &_Str, tf_CData _CharFind, tf_CData2 _CharReplace, mint _MaxLen);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrInsert(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, tf_CData const *_pStrInsert);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrInsert(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, TCStr<tf_CTCStrTraits2> const &_StrInsert);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrInsert(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, tf_CData const *_pStrInsert, mint _MaxLen);
	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrInsert(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, TCStr<tf_CTCStrTraits2> const &_StrInsert, mint _MaxLen);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrDelete(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, mint _nChars);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrLeft(TCStr<tf_CTCStrTraits> &_Str, mint _nChars);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrExtract(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar);
	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrExtract(TCStr<tf_CTCStrTraits> &_Str, aint _StartChar, mint _nChars);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReverse(TCStr<tf_CTCStrTraits> &_Str);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrRight(TCStr<tf_CTCStrTraits> &_Str, mint _nChars);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrimLeft(TCStr<tf_CTCStrTraits> &_Str);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrimLeft(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pCharsToTrim);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrimRight(TCStr<tf_CTCStrTraits> &_Str);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrimRight(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pCharsToTrim);

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrim(TCStr<tf_CTCStrTraits> &_Str);
	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrTrim(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pCharsToTrim);

	template <typename tf_CTCStrTraits>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrClear(TCStr<tf_CTCStrTraits> &_Str);

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrSetAt(TCStr<tf_CTCStrTraits> &_Str, aint _Index, tf_CData _Character);

	template <typename tf_CTCStrTraits0, typename tf_CTCStrTraits1>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStr(TCStr<tf_CTCStrTraits0> &_StrDest, TCStr<tf_CTCStrTraits1> const &_StrSource);
	template <typename tf_CTCStrTraits0, typename tf_CTCStrTraits1, typename tf_CEscapeChar>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStr(TCStr<tf_CTCStrTraits0> &_StrDest, TCStr<tf_CTCStrTraits1> const &_StrSource, tf_CEscapeChar const *_pEscapedChars);
	template <typename tf_CTCStrTraits0, typename tf_CTCStrTraits1, typename tf_CEscapeChar, typename tf_CReplaceChars>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStr
		(
			TCStr<tf_CTCStrTraits0> &_StrDest
			, TCStr<tf_CTCStrTraits1> const &_StrSource
			, tf_CEscapeChar const *_pEscapedChars
			, tf_CReplaceChars const *_pReplaceChars
		)
	;

	template<typename tf_CTCStrTraits0, typename tf_CTCStrTraits1>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStrNoQuotes(TCStr<tf_CTCStrTraits0> &_StrDest, TCStr<tf_CTCStrTraits1> const &_StrSource);
	template<typename tf_CTCStrTraits0, typename tf_CTCStrTraits1, typename tf_CEscapeChar>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStrNoQuotes(TCStr<tf_CTCStrTraits0> &_StrDest, TCStr<tf_CTCStrTraits1> const &_StrSource, tf_CEscapeChar const *_pEscapedChars);
	template<typename tf_CTCStrTraits0, typename tf_CTCStrTraits1, typename tf_CEscapeChar, typename tf_CReplaceChars>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStrNoQuotes
		(
			TCStr<tf_CTCStrTraits0> &_StrDest
			, TCStr<tf_CTCStrTraits1> const &_StrSource
			, tf_CEscapeChar const *_pEscapedChars
			, tf_CReplaceChars const *_pReplaceChars
		)
	;

	template <typename tf_CChar>
	constexpr typename TCFStr<tf_CChar, 2, sizeof(tf_CChar) >= 4 ? EStrType_Unicode : EStrType_UTF>::CType fg_CharToString(tf_CChar const &_Char);
}

#include "Malterlib_String_Container_Algorithm.hpp"
