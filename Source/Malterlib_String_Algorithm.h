// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	struct TCStrSpan;

	template <typename t_CTCStrTraits>
	class TCStr;

	class CStrTraits_CStr;
	class CStrTraits_CWStr;
	class CStrTraits_CUStr;
	class CStrTraits_CStrNonTracked;
	class CStrTraits_CWStrNonTracked;
	class CStrTraits_CUStrNonTracked;

	using CStr = TCStr<CStrTraits_CStr>;
	using CWStr = TCStr<CStrTraits_CWStr>;
	using CUStr = TCStr<CStrTraits_CUStr>;

	using CStrNonTracked = TCStr<CStrTraits_CStrNonTracked>;
	using CWStrNonTracked = TCStr<CStrTraits_CWStrNonTracked>;
	using CUStrNonTracked = TCStr<CStrTraits_CUStrNonTracked>;

	template <typename t_CData0, typename t_CData1>
	class TCChooseStrCompareType
	{
	public:

		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, t_CData1>>>;
	};

	template <typename t_CData0, typename t_CData1>
	class TCChooseStrCompareType<t_CData0, TCStr<t_CData1> >
	{
	public:

		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, typename TCStr<t_CData1>::CChar>>>;
	};

	template <typename t_CData0, typename t_CData1>
	class TCChooseStrCompareType<TCStr<t_CData1>, t_CData0>
	{
	public:

		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, typename TCStr<t_CData1>::CChar>>>;
	};

	template <typename t_CData0, typename t_CData1>
	class TCChooseStrCompareType<TCStr<t_CData0>, TCStr<t_CData1> >
	{
	public:

		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<typename TCStr<t_CData0>::CChar, typename TCStr<t_CData1>::CChar>>>;
	};

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| String functions																					|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	template <typename t_CData>
	constexpr inline_small t_CData *fg_StrAdd(t_CData *_pStr, aint _Add);

	// Static functions
	template <typename t_CData>
	constexpr inline_medium mint fg_StrLen(const t_CData *_pStr);
	template <typename t_CData>
	constexpr inline_medium mint fg_StrLen(const t_CData *_pStr, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
		inline_medium t_CData1 *fg_StrCopy(t_CData1 *_pTo, const t_CData2 *_pFrom);

	template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrCopy(t_CData1 *_pTo, const t_CData2 *_pFrom, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
		inline_medium t_CData1 *fg_StrMove(t_CData1 *_pTo, const t_CData2 *_pFrom);

	template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrMove(t_CData1 *_pTo, const t_CData2 *_pFrom, mint _MaxLen);


	template <typename t_CData>
	constexpr inline_large uint32 fg_StrHashDJB2(const t_CData *_pStr);

	template <typename t_CData>
	constexpr inline_large uint32 fg_StrHashSDBM(const t_CData *_pStr);

	template <typename t_CData>
	constexpr inline_large uint32 fg_StrHash(const t_CData *_pStr);


	template <typename t_CData1>
	constexpr inline_small bool fg_StrIsAnsi(const t_CData1 *_pStr1);

	template <typename t_CData1>
	constexpr inline_small bool fg_StrIsAnsi(const t_CData1 *_pStr1, mint _MaxLen);


	template <typename t_CStr>
	constexpr bool fg_StrIsEmpty(t_CStr const *_pStr);

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Upper case																						|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	ch8 *fg_StrUpperCase(ch8 *_pStr);
	ch8 *fg_StrUpperCase(ch8 *_pStr, mint _MaxLen);
	ch8 *fg_StrUpperCase(ch8 *_pDest, mint _MaxDestLen, const ch8 *_pSource);
	ch8 *fg_StrUpperCase(ch8 *_pDest, mint _MaxDestLen, const ch8 *_pSource, mint _SourceLen);
	ch8 *fg_StrUpperCase(ch8 *_pDest, const ch8 *_pSource, mint _SourceLen);

	template <typename t_CData>
		inline_large t_CData *fg_StrUpperCase(t_CData *_pStr);
	template <typename t_CData>
		inline_large t_CData *fg_StrUpperCase(t_CData *_pStr, mint _MaxLen);

	template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrUpperCase(t_CData1 *_pDest, mint _MaxDestLen, const t_CData2 *_pSource);

	template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrUpperCase(t_CData1 *_pDest, mint _MaxDestLen, const t_CData2 *_pSource, mint _SourceLen);
	template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrUpperCase(t_CData1 *_pDest, const t_CData2 *_pSource, mint _SourceLen);


	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Lower case																						|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	ch8 *fg_StrLowerCase(ch8 *_pStr);
	ch8 *fg_StrLowerCase(ch8 *_pStr, mint _MaxLen);
	ch8 *fg_StrLowerCase(ch8 *_pDest, mint _MaxDestLen, const ch8 *_pSource);
	ch8 *fg_StrLowerCase(ch8 *_pDest, mint _MaxDestLen, const ch8 *_pSource, mint _SourceLen);
	ch8 *fg_StrLowerCase(ch8 *_pDest, ch8 const *_pSource, mint _SourceLen);

	template <typename t_CData>
		inline_large t_CData *fg_StrLowerCase(t_CData *_pStr);
	template <typename t_CData>
		inline_large t_CData *fg_StrLowerCase(t_CData *_pStr, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrLowerCase(t_CData1 *_pDest, mint _MaxDestLen, const t_CData2 *_pSource);

	template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrLowerCase(t_CData1 *_pDest, mint _MaxDestLen, const t_CData2 *_pSource, mint _SourceLen);

	template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrLowerCase(t_CData1 *_pDest, const t_CData2 *_pSource, mint _SourceLen);

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Capitalize																						|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	ch8 *fg_StrCapitalize(ch8 *_pStr);

	template <typename t_CData>
		inline_large t_CData *fg_StrCapitalize(t_CData *_pStr);

	template <typename t_CData>
		inline_large t_CData *fg_StrCapitalize(t_CData *_pStr, mint _MaxLen);


	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Cmp																								|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/


	template <typename t_CData1, typename t_CData2>
	constexpr inline_large typename TCChooseStrCompareType<t_CData1, t_CData2>::CType fg_StrCmp(const t_CData1 *_pStr1, const t_CData2 *_pStr2);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large typename TCChooseStrCompareType<t_CData1, t_CData2>::CType fg_StrCmpNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large typename TCChooseStrCompareType<t_CData1, t_CData2>::CType fg_StrCmp(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large typename TCChooseStrCompareType<t_CData1, t_CData2>::CType fg_StrCmpNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen);

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Searching
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindChar(const t_CData1 *_pStr1, t_CData2 _Char);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharNoCase(const t_CData1 *_pStr1, t_CData2 _Char);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharReverse(const t_CData1 *_pStr1, t_CData2 _Char);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharReverseNoCase(const t_CData1 *_pStr1, t_CData2 _Char);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindChar(const t_CData1 *_pStr1, t_CData2 _Char, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharNoCase(const t_CData1 *_pStr1, t_CData2 _Char, mint _MaxLen);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharReverse(const t_CData1 *_pStr1, t_CData2 _Char, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharReverseNoCase(const t_CData1 *_pStr1, t_CData2 _Char, mint _MaxLen);



	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindChars(const t_CData1 *_pStr1, const t_CData2 *_pChars);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharsNoCase(const t_CData1 *_pStr1, const t_CData2 *_pChars);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharsReverse(const t_CData1 *_pStr1, const t_CData2 *_pChars);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharsReverseNoCase(const t_CData1 *_pStr1, const t_CData2 *_pChars);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindChars(const t_CData1 *_pStr1, const t_CData2 *_pChars, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharsNoCase(const t_CData1 *_pStr1, const t_CData2 *_pChars, mint _MaxLen);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharsReverse(const t_CData1 *_pStr1, const t_CData2 *_pChars, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindCharsReverseNoCase(const t_CData1 *_pStr1, const t_CData2 *_pChars, mint _MaxLen);



	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFind(const t_CData1 *_pStr1, const t_CData2 *_pStr2);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFind(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen);

	// Returns first character for searched string
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindReverse(const t_CData1 *_pStr1, const t_CData2 *_pStr2);

	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindReverseNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
	constexpr inline_large aint fg_StrFindReverseNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen);

	enum EMatchWildcardResult
	{
		EMatchWildcardResult_NotMatched = 0
		, EMatchWildcardResult_PatternExhausted =  DMibBit(0)
		, EMatchWildcardResult_WholeStringMatched = DMibBit(1)
		, EMatchWildcardResult_WholeStringMatchedAndPatternExhausted = EMatchWildcardResult_WholeStringMatched | EMatchWildcardResult_PatternExhausted
	};
	template <typename tf_CData1, typename tf_CData2>
	constexpr EMatchWildcardResult fg_StrMatchWildcard(const tf_CData1 *_pStr, const tf_CData2 *_pPattern);

	template <typename tf_CData1, typename tf_CData2>
	constexpr EMatchWildcardResult fg_StrMatchWildcardParse(const tf_CData1 *&_pStr, const tf_CData2 *_pPattern);

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Replacing																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/


	template <typename t_CData1, typename t_CData2, typename t_CData3>
		inline_large t_CData1 *fg_StrReplaceChar(t_CData1 *_pStr1, t_CData2 _CharFind, t_CData3 _CharReplace);


	template <typename t_CData1, typename t_CData2, typename t_CData3>
		inline_large t_CData1 *fg_StrReplace(t_CData1 *_pStr1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace);
	template <typename t_CData1, typename t_CData2, typename t_CData3>
		inline_large t_CData1 *fg_StrReplaceNoCase(t_CData1 *_pStr1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace);

	template <typename t_CData1, typename t_CData2, typename t_CData3>
		inline_large t_CData1 *fg_StrReplaceChar(t_CData1 *_pStr1, t_CData2 _CharFind, t_CData3 _CharReplace, mint _MaxLen);

	template <typename t_CData1, typename t_CData2, typename t_CData3>
		inline_large t_CData1 *fg_StrReplace(t_CData1 *_pStr1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace, mint _MaxLen);
	template <typename t_CData1, typename t_CData2, typename t_CData3>
		inline_large t_CData1 *fg_StrReplaceNoCase(t_CData1 *_pStr1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace, mint _MaxLen);

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Insert
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	// Insert
	template <typename t_CData1, typename t_CData2>
	inline_large t_CData1 *fg_StrInsert(t_CData1 *_pStr1, aint _StartChar, const t_CData2 *_pStr2);
	template <typename t_CData1, typename t_CData2>
	inline_large t_CData1 *fg_StrInsert(t_CData1 *_pStr1, aint _StartChar, const t_CData2 *_pStr2, mint _MaxLen);

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Shortening
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	// Shortening
	template <typename t_CData1>
	inline_large t_CData1 *fg_StrDelete(t_CData1 *_pStr1, aint _StartChar, mint _nChars);
	template <typename t_CData1>
	inline_large t_CData1 *fg_StrLeft(t_CData1 *_pStr1, mint _nChars);

	template <typename t_CData1>
	inline_large t_CData1 *fg_StrExtract(t_CData1 *_pStr1, aint _StartChar, mint _nChars);

	template <typename t_CData1>
	inline_large t_CData1 *fg_StrExtract(t_CData1 *_pStr1, aint _StartChar);

	template <typename t_CData1>
	inline_large t_CData1 *fg_StrReverse(t_CData1 *_pStr1);
	template <typename t_CData1>
	inline_large t_CData1 *fg_StrRight(t_CData1 *_pStr1, mint _nChars);

	template <typename t_CData1, typename t_CData2>
	inline_small t_CData1 *fg_StrTrimLeft(t_CData1 *_pStr1, const t_CData2 *_pCharsToTrim);

	template <typename t_CData1>
	inline_small t_CData1 *fg_StrTrimLeft(t_CData1 *_pStr1);

	template <typename t_CData1, typename t_CData2>
	inline_small t_CData1 *fg_StrTrimRight(t_CData1 *_pStr1, const t_CData2 *_pCharsToTrim);

	template <typename t_CData1>
	inline_small t_CData1 *fg_StrTrimRight(t_CData1 *_pStr1);

	template <typename t_CData1, typename t_CData2>
	inline_small t_CData1 *fg_StrTrim(t_CData1 *_pStr1, const t_CData2 *_pCharsToTrim);

	template <typename t_CData1>
	inline_small t_CData1 *fg_StrTrim(t_CData1 *_pStr1);


	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Misc
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/
	template <typename t_CData1>
	inline_small t_CData1 *fg_StrClear(t_CData1 *_pStr1);

	template <typename t_CData1, typename t_CData2>
	inline_small t_CData1 *fg_StrSetAt(t_CData1 *_pStr1, aint _Index, t_CData2 _Character);

	template <typename t_CData1>
	inline_small NTraits::TCUnsigned<t_CData1> fg_StrLargestChar(const t_CData1 *_pStr1);

	template <typename t_CData1, typename t_CData2>
	inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, mint _MaxLen);
	template <typename t_CData1, typename t_CData2>
	inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource);

	template <typename t_CData1, typename t_CData2, typename t_CEscapeChar>
	inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapChars, mint _MaxLen);
	template <typename t_CData1, typename t_CData2, typename t_CEscapeChar>
	inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapChars);

	template <typename t_CData1, typename t_CData2, typename t_CEscapeChar, typename t_CReplaceChar>
	inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapChars, const t_CReplaceChar *_pReplaceChar, mint _MaxLen);
	template <typename t_CData1, typename t_CData2, typename t_CEscapeChar, typename t_CReplaceChar>
	inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapChars, const t_CReplaceChar *_pReplaceChar);


	template<typename t_CData1, typename t_CData2>
	inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, mint _MaxLen);
	template<typename t_CData1, typename t_CData2>
	inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource);

	template<typename t_CData1, typename t_CData2, typename t_CEscapeChar>
	inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapChars, mint _MaxLen);
	template<typename t_CData1, typename t_CData2, typename t_CEscapeChar>
	inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapChars);

	template<typename t_CData1, typename t_CData2, typename t_CEscapeChar, typename t_CReplaceChar>
	inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapChars, const t_CReplaceChar *_pReplaceChar, mint _MaxLen);
	template<typename t_CData1, typename t_CData2, typename t_CEscapeChar, typename t_CReplaceChar>
	inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapChars, const t_CReplaceChar *_pReplaceChar);


	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| Character functions																				|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/


	template <typename t_CData>
	constexpr inline_medium t_CData fg_CharUpperCase(t_CData _Character);
	template <typename t_CData>
	constexpr inline_medium t_CData fg_CharLowerCase(t_CData _Character);

	template <typename t_CData>
	constexpr inline_medium bool fg_CharIsWhiteSpace(const t_CData _Character);

	template <typename t_CData>
	constexpr inline_large bool fg_CharIsAlphabetical(const t_CData _Character);
	template <typename t_CData>
	constexpr inline_large bool fg_CharIsAnsiAlphabetical(const t_CData _Character);
	template <typename t_CData>
	constexpr inline_medium bool fg_CharIsNumber(const t_CData _Character);
	constexpr inline_medium bool fg_CharIsCombining(ch32 const _Character);

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	|| Formatting function
	||________________________________________________________________________________________________
	\************************************************************************************************/
	template <typename tf_CFormat>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format);
	template <typename tf_CFormat, typename tf_CFirst, typename... tfp_CParams>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format, tf_CFirst &&_First);
	template <typename tf_CFormat, typename tf_CFirst, typename... tfp_CParams>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format, tf_CFirst &&_First, tfp_CParams &&...p_Params);

	template <typename tf_CReturnString, typename tf_CFormat, typename... tfp_CParams>
	tf_CReturnString fg_Format(tf_CFormat const &_Format, tfp_CParams &&...p_Params);

	template <typename tf_CFormat, typename... tfp_CParams>
	CStr fg_Format(tf_CFormat const &_Format, tfp_CParams &&...p_Params);

}

#ifndef DMibPNoShortCuts
	using namespace NMib::NStr;
#endif
