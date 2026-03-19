// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "../Malterlib_String_Defines.h"

namespace NMib::NStr
{
	enum EMatchWildcardResult
	{
		EMatchWildcardResult_NotMatched = 0
		, EMatchWildcardResult_PatternExhausted =  DMibBit(0)
		, EMatchWildcardResult_WholeStringMatched = DMibBit(1)
		, EMatchWildcardResult_WholeStringMatchedAndPatternExhausted = EMatchWildcardResult_WholeStringMatched | EMatchWildcardResult_PatternExhausted
	};

	template <typename tf_CData>
	constexpr inline_small tf_CData *fg_StrAdd(tf_CData *_pStr, aint _Add);

	// Static functions
	template <typename tf_CData>
	constexpr inline_medium umint fg_StrLen(tf_CData const *_pStr);
	template <typename tf_CData>
	constexpr inline_medium umint fg_StrLen(tf_CData const *_pStr, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	inline_medium tf_CData1 *fg_StrCopy(tf_CData1 *_pTo, tf_CData2 const *_pFrom);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrCopy(tf_CData1 *_pTo, tf_CData2 const *_pFrom, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	inline_medium tf_CData1 *fg_StrMove(tf_CData1 *_pTo, tf_CData2 const *_pFrom);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrMove(tf_CData1 *_pTo, tf_CData2 const *_pFrom, umint _MaxLen);

	template <typename tf_CData>
	constexpr inline_large uint32 fg_StrHashDJB2(tf_CData const *_pStr);
	template <typename tf_CData>
	constexpr inline_large uint32 fg_StrHashSDBM(tf_CData const *_pStr);
	template <typename tf_CData>
	constexpr inline_large uint32 fg_StrHash(tf_CData const *_pStr);

	template <typename tf_CData1>
	constexpr inline_small bool fg_StrIsAnsi(tf_CData1 const *_pStr1);
	template <typename tf_CData1>
	constexpr inline_small bool fg_StrIsAnsi(tf_CData1 const *_pStr1, umint _MaxLen);

	template <typename t_CStr>
	constexpr bool fg_StrIsEmpty(t_CStr const *_pStr);

	ch8 *fg_StrUpperCase(ch8 *_pStr);
	ch8 *fg_StrUpperCase(ch8 *_pStr, umint _MaxLen);
	ch8 *fg_StrUpperCase(ch8 *_pDest, umint _MaxDestLen, const ch8 *_pSource);
	ch8 *fg_StrUpperCase(ch8 *_pDest, umint _MaxDestLen, const ch8 *_pSource, umint _SourceLen);
	ch8 *fg_StrUpperCase(ch8 *_pDest, const ch8 *_pSource, umint _SourceLen);

	template <typename tf_CData>
	inline_large tf_CData *fg_StrUpperCase(tf_CData *_pStr);
	template <typename tf_CData>
	inline_large tf_CData *fg_StrUpperCase(tf_CData *_pStr, umint _MaxLen);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrUpperCase(tf_CData1 *_pDest, umint _MaxDestLen, tf_CData2 const *_pSource);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrUpperCase(tf_CData1 *_pDest, umint _MaxDestLen, tf_CData2 const *_pSource, umint _SourceLen);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrUpperCase(tf_CData1 *_pDest, tf_CData2 const *_pSource, umint _SourceLen);

	ch8 *fg_StrLowerCase(ch8 *_pStr);
	ch8 *fg_StrLowerCase(ch8 *_pStr, umint _MaxLen);
	ch8 *fg_StrLowerCase(ch8 *_pDest, umint _MaxDestLen, const ch8 *_pSource);
	ch8 *fg_StrLowerCase(ch8 *_pDest, umint _MaxDestLen, const ch8 *_pSource, umint _SourceLen);
	ch8 *fg_StrLowerCase(ch8 *_pDest, ch8 const *_pSource, umint _SourceLen);

	template <typename tf_CData>
	inline_large tf_CData *fg_StrLowerCase(tf_CData *_pStr);
	template <typename tf_CData>
	inline_large tf_CData *fg_StrLowerCase(tf_CData *_pStr, umint _MaxLen);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrLowerCase(tf_CData1 *_pDest, tf_CData2 const *_pSource, umint _SourceLen);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrLowerCase(tf_CData1 *_pDest, umint _MaxDestLen, tf_CData2 const *_pSource);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrLowerCase(tf_CData1 *_pDest, umint _MaxDestLen, tf_CData2 const *_pSource, umint _SourceLen);

	ch8 *fg_StrCapitalize(ch8 *_pStr);

	template <typename tf_CData>
	inline_large tf_CData *fg_StrCapitalize(tf_CData *_pStr);
	template <typename tf_CData>
	inline_large tf_CData *fg_StrCapitalize(tf_CData *_pStr, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmp(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2) noexcept;
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2) noexcept;
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmp(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen) noexcept;
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen) noexcept;
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpConstExpr(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2) noexcept;
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrCmpNoCaseIterator(tf_CData1 &_Str1, tf_CData2 &_Str2) noexcept;

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChar(tf_CData1 const *_pStr1, tf_CData2 _Char);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChar(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharNoCase(tf_CData1 const *_pStr1, tf_CData2 _Char);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharNoCase(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverse(tf_CData1 const *_pStr1, tf_CData2 _Char);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverse(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 _Char);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 _Char, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChars(tf_CData1 const *_pStr1, tf_CData2 const *_pChars);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChars(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindChars(tf_CData1 const *_pStr1, umint _Len, tf_CData2 const *_pChars);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pChars);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindCharsReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pChars, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFind(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFind(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen);

	template <bool tf_bNoCase, typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindIterator(tf_CData1 &_Str1, tf_CData2 &_Str2);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen);

	// Returns first character for searched string
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverse(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _FindLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrFindReverseNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _FindLen);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrStartsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWith(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2);

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len);
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large bool fg_StrEndsWithNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _Len, umint _Len2);

	template <typename tf_CData1, typename tf_CData2>
	constexpr EMatchWildcardResult fg_StrMatchWildcard(tf_CData1 const *_pStr, tf_CData2 const *_pPattern);

	template <typename tf_CData1, typename tf_CData2>
	constexpr EMatchWildcardResult fg_StrMatchWildcardParse(tf_CData1 const *&_pStr, tf_CData2 const *_pPattern);

	template <EMatchWildcardResult tf_Result = EMatchWildcardResult_WholeStringMatchedAndPatternExhausted, typename tf_CStr, typename tf_CContainer>
	bool fg_StrMatchesAnyWildcardInContainerKeys(tf_CStr const &_String, tf_CContainer const &_Container);

	template <EMatchWildcardResult tf_Result = EMatchWildcardResult_WholeStringMatchedAndPatternExhausted, typename tf_CStr, typename tf_CContainer>
	bool fg_StrMatchesAnyWildcardInContainer(tf_CStr const &_String, tf_CContainer const &_Container);

	template <typename tf_CData1, typename tf_CData2, typename t_CData3>
	inline_large tf_CData1 *fg_StrReplaceChar(tf_CData1 *_pStr1, tf_CData2 _CharFind, t_CData3 _CharReplace);
	template <typename tf_CData1, typename tf_CData2, typename t_CData3>
	inline_large tf_CData1 *fg_StrReplaceChar(tf_CData1 *_pStr1, tf_CData2 _CharFind, t_CData3 _CharReplace, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2, typename t_CData3>
	inline_large tf_CData1 *fg_StrReplace(tf_CData1 *_pStr1, tf_CData2 const *_pStrFind, t_CData3 const *_pStrReplace);
	template <typename tf_CData1, typename tf_CData2, typename t_CData3>
	inline_large tf_CData1 *fg_StrReplace(tf_CData1 *_pStr1, tf_CData2 const *_pStrFind, t_CData3 const *_pStrReplace, umint _MaxLen);
	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplace(tf_CData1 *_pStr1, umint _Len, tf_CData2 const *_pStrFind, umint _LenFind, tf_CData3 const *_pStrReplace, umint _LenReplace, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplaceWithCount(tf_CData1 *_pStr1, umint _Len, tf_CData2 const *_pStrFind, umint _LenFind, tf_CData3 const *_pStrReplace, umint _LenReplace, umint _MaxLen, umint _Count);

	template <typename tf_CData1, typename tf_CData2, typename t_CData3>
	inline_large tf_CData1 *fg_StrReplaceNoCase(tf_CData1 *_pStr1, tf_CData2 const *_pStrFind, t_CData3 const *_pStrReplace);
	template <typename tf_CData1, typename tf_CData2, typename t_CData3>
	inline_large tf_CData1 *fg_StrReplaceNoCase(tf_CData1 *_pStr1, tf_CData2 const *_pStrFind, t_CData3 const *_pStrReplace, umint _MaxLen);
	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplaceNoCase(tf_CData1 *_pStr1, umint _Len, tf_CData2 const *_pStrFind, umint _LenFind, tf_CData3 const *_pStrReplace, umint _LenReplace, umint _MaxLen);

	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplaceNoCaseWithCount
		(
			tf_CData1 *_pStr1
			, umint _Len, tf_CData2 const *_pStrFind
			, umint _LenFind
			, tf_CData3 const *_pStrReplace
			, umint _LenReplace
			, umint _MaxLen
			, umint _Count
		)
	;

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrInsert(tf_CData1 *_pStr1, aint _StartChar, tf_CData2 const *_pStr2);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrInsert(tf_CData1 *_pStr1, aint _StartChar, tf_CData2 const *_pStr2, umint _MaxLen);

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrDelete(tf_CData1 *_pStr1, aint _StartChar, umint _nChars);

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrLeft(tf_CData1 *_pStr1, umint _nChars);

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrExtract(tf_CData1 *_pStr1, aint _StartChar, umint _nChars);
	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrExtract(tf_CData1 *_pStr1, aint _StartChar);

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrReverse(tf_CData1 *_pStr1);

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrRight(tf_CData1 *_pStr1, umint _nChars);

	template <typename tf_CData1>
	inline_small tf_CData1 *fg_StrTrimLeft(tf_CData1 *_pStr1);
	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *fg_StrTrimLeft(tf_CData1 *_pStr1, tf_CData2 const *_pCharsToTrim);

	template <typename tf_CData1>
	inline_small tf_CData1 *fg_StrTrimRight(tf_CData1 *_pStr1);
	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *fg_StrTrimRight(tf_CData1 *_pStr1, tf_CData2 const *_pCharsToTrim);

	template <typename tf_CData1>
	inline_small tf_CData1 *fg_StrTrim(tf_CData1 *_pStr1);
	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *fg_StrTrim(tf_CData1 *_pStr1, tf_CData2 const *_pCharsToTrim);

	template <typename tf_CData1>
	inline_small tf_CData1 *fg_StrClear(tf_CData1 *_pStr1);

	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *fg_StrSetAt(tf_CData1 *_pStr1, aint _Index, tf_CData2 _Character);

	template <typename tf_CStrType>
	tf_CStrType fg_GetStrSep(tf_CStrType &_Str, ch8 const *_pSep);

	template <typename tf_CStrType>
	tf_CStrType fg_GetStrSepNoTrim(tf_CStrType &_Str, ch8 const *_pSep);

	template <typename tf_CStrType>
	tf_CStrType fg_GetStrLineSep(tf_CStrType &_Str);

	template <typename tf_CStrType, typename tf_CSeparators>
	tf_CStrType fg_GetStrSeparators(tf_CStrType &_Str, tf_CSeparators const *_pSeparators);

	template <typename tf_CStr>
	tf_CStr fg_StrSanitizeOneLine(tf_CStr const &_Str);

	template <typename tf_CStrType0, typename tf_CStrType1, typename tf_CStrType2>
	void fg_StrAddWithSeparator(tf_CStrType0 &_Str, tf_CStrType1 const &_ToAdd, tf_CStrType2 const &_Separator);

	template <typename tf_CStrType0, typename tf_CStrType1, typename tf_CStrType2>
	void fg_AddStrSep(tf_CStrType0 &_Str, tf_CStrType1 const &_ToAdd, tf_CStrType2 const &_Separator);

	template <typename tf_CStrType0, typename tf_CStrType1>
	void fg_AddStrSepEscaped(tf_CStrType0 &_Str, tf_CStrType1 const &_ToAdd, ch8 _Sep, ch8 const *_pNeedEscapeChars = "\"\\");

	template <typename tf_CData1>
	inline_small NTraits::TCUnsigned<tf_CData1> fg_StrLargestChar(tf_CData1 const *_pStr1);

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource);
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, umint _MaxLen);
	template <typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapChars);
	template <typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapChars, umint _MaxLen);
	template <typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar, typename tf_CReplaceChar>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapChars, tf_CReplaceChar const *_pReplaceChar);
	template <typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar, typename tf_CReplaceChar>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapChars, tf_CReplaceChar const *_pReplaceChar, umint _MaxLen);

	template<typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource);
	template<typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, umint _MaxLen);
	template<typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapChars);
	template<typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapChars, umint _MaxLen);
	template<typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar, typename tf_CReplaceChar>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapChars, tf_CReplaceChar const *_pReplaceChar);
	template<typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar, typename tf_CReplaceChar>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes
		(
			tf_CData1 *_pStrDest
			, tf_CData2 const *_pStrSource
			, tf_CEscapeChar const *_pEscapChars
			, tf_CReplaceChar const *_pReplaceChar
			, umint _MaxLen
		)
	;

	template<typename tf_CData2>
	inline_large umint fg_StrEscapedLength(tf_CData2 const *_pStrSource);
	template<typename tf_CData2, typename tf_CEscapeChar>
	inline_large umint fg_StrEscapedLength(tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars);

	template <ch8 tf_EscapeChar, typename tf_CStrType>
	tf_CStrType fg_RemoveEscape(tf_CStrType const &_Str);
	template <typename tf_CStrType>
	tf_CStrType fg_RemoveEscape(tf_CStrType const &_Str);

	template <ch8 tf_EscapeChar, typename tf_CStrType>
	tf_CStrType fg_GetStrSepEscaped(tf_CStrType &_Str, ch8 const *_pSep);
	template <typename tf_CStrType>
	tf_CStrType fg_GetStrSepEscaped(tf_CStrType &_Str, ch8 const *_pSep);

	template <typename tf_CStr>
	bool fg_StrEscapeBashQuotesNeeded(tf_CStr const &_Str);

	template<typename tf_CStr>
	tf_CStr fg_StrEscapeBashSingleQuotes(tf_CStr const &_Str);

	template<typename tf_CStr>
	tf_CStr fg_StrEscapeBashDoubleQuotes(tf_CStr const &_Str);

	constexpr inline_medium bool fg_CharIsCombining(ch32 const _Character);

	template <typename tf_CData>
	constexpr inline_medium tf_CData fg_CharUpperCase(tf_CData _Character);
	template <typename tf_CData>
	constexpr inline_medium tf_CData fg_CharLowerCase(tf_CData _Character);

	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsWhiteSpace(tf_CData const _Character);
	template <typename tf_CData>
	constexpr inline_large bool fg_CharIsAlphabetical(tf_CData const _Character);
	template <typename tf_CData>
	constexpr inline_large bool fg_CharIsAnsiAlphabetical(tf_CData const _Character);
	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsNewLine(tf_CData const _Character);
	template<typename tf_CData>
	constexpr inline_medium bool fg_CharIsWhiteSpaceNoLines(tf_CData const _Character);
	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsNumber(tf_CData const _Character);
	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsOctalNumber(tf_CData const _Character);
	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsHexNumber(tf_CData const _Character);
	template <typename tf_CData>
	constexpr inline_large bool fg_CharIsLowerCaseAnsiAlphabetical(tf_CData const _Character);

	template <ch8 tf_EscapeChar, typename tf_CChar>
	constexpr bool fg_ParseEscape(tf_CChar const * &_pParse, tf_CChar _Abort);

	template <typename tf_CChar>
	constexpr void fg_ParseWhiteSpace(tf_CChar const * &_pParse);
	template <typename tf_CChar>
	constexpr void fg_ParseWhiteSpace(tf_CChar * &_pParse);

	template <typename tf_CChar>
	constexpr void fg_ParseToEndOfLine(tf_CChar const * &_pParse);
	template <typename tf_CChar>
	constexpr void fg_ParseToEndOfLine(tf_CChar * &_pParse);

	template <typename tf_CChar>
	constexpr void fg_ParseWhiteSpaceNoLines(tf_CChar const * &_pParse);

	template <typename tf_CChar>
	constexpr bool fg_ParseEndOfLine(tf_CChar const * &_pParse);

	template <typename tf_CChar>
	constexpr bool fg_ParseEndOfLine(tf_CChar * &_pParse);

	template <typename tf_CChar, typename tf_CSeparators>
	constexpr void fg_ParseNonWhiteSpaceAndSeparators(tf_CChar const * &_pParse, tf_CSeparators const *_pSeparators);

	template <typename tf_CChar>
	constexpr void fg_ParseAlpha(tf_CChar const * &_pParse);

	template <typename tf_CChar>
	constexpr void fg_ParseAlphaNumeric(tf_CChar const * &_pParse);

	template <typename tf_CChar>
	constexpr void fg_ParseNumeric(tf_CChar const * &_pParse);

	template <typename tf_CChar, typename tf_CChar1>
	constexpr void fg_ParseAlphaNumericAndChars(tf_CChar const * &_pParse, tf_CChar1 const *_pChars);

	template <typename tf_CChar, typename tf_CSeparators>
	constexpr void fg_ParseWhiteSpaceAndSeparators(tf_CChar const * &_pParse, tf_CSeparators const *_pSeparators);
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStr;
#endif


