// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include "../../Core/Source/Malterlib_Core_PlatformInterface.h"
#include <Mib/String/UnicodeConversion>
#include <Mib/String/Algorithm>
#include <Mib/Core/EnableIf>

#include "Malterlib_String_Container_Traits.h"
#include "Malterlib_String_Container_Span.h"
#include "Malterlib_String_Container_Format.h"

namespace NMib::NStr
{
	struct CStrInitGeneral {};
	struct CInitByRange {};
	struct CAllowNUL {};

	template <typename t_CString>
	struct TCStringAppender;

	template <typename t_CChar, EStrType t_StrType>
	using TCGetUnicodeIterator = TCConditional
		<
			sizeof(t_CChar) == 1
			, TCConditional
			<
				t_StrType == EStrType_UTF
				, CStrIteratorUTF8
				, TCStrIteratorUnicode<t_CChar>
			>
			, TCConditional
			<
				sizeof(t_CChar) == 2
				, TCConditional
				<
					t_StrType == EStrType_UTF
					, CStrIteratorUTF16
					, TCStrIteratorUnicode<t_CChar>
				>
				, TCStrIteratorUnicode<t_CChar>
			>
		>
	;

	template <typename t_CTCStrTraits>
	struct TCStr : public t_CTCStrTraits::CImp
	{
		static constexpr EStrType mc_Type = t_CTCStrTraits::CStrTraits::mc_Type;

		using CStrTraits = typename t_CTCStrTraits::CStrTraits;
		using CAllocator = typename CStrTraits::CAllocator;
		using CImp = typename t_CTCStrTraits::CImp;
		using CTraits = t_CTCStrTraits;
		using CChar = typename t_CTCStrTraits::CStrTraits::CChar;
		using CUnsignedChar = NTraits::TCUnsigned<typename t_CTCStrTraits::CStrTraits::CChar>;

		using CFormat = TCFormat<t_CTCStrTraits>;
		using CFormatArgVisitor = typename CFormat::CFomatArgType::CVisitor;
		using CFormatArgVisitorInteger = typename CFormat::CFomatArgType::CVisitorInteger;
		using CFormatArgVisitorFloat = typename CFormat::CFomatArgType::CVisitorFloat;
		using CFormatArgVisitorNumber = typename CFormat::CFomatArgType::CVisitorNumber;
		using CFormatArgVisitorString = typename CFormat::CFomatArgType::CVisitorString;

		using CMaxChar = CChar;
		using CString = TCStr;

		using CAppender = TCStringAppender<TCStr>;

		using CUnicodeIterator = TCGetUnicodeIterator<CChar, mc_Type>;

		struct CParse;

		struct CParseResult
		{
			umint m_nCharsParsed = 0;
			umint m_nVariablesParsed = 0;
		};

		struct CAddStrAgrs
		{
			CAddStrAgrs(aint &_StrLen, umint _Len);

			aint &m_StrLen;
			umint m_Len;
		};

		struct CAutoDestroy
		{
			CAutoDestroy(TCStr *_pThis);
			~CAutoDestroy();

			void f_Clear();

		private:
			TCStr *mp_pThis;
		};

		inline_small constexpr TCStr() noexcept = default;
		inline_small constexpr ~TCStr() = default;
		inline_large TCStr(CFormat const &_Format);
		constexpr inline_small TCStr(TCStr const &_Str);
		inline_small TCStr(TCStr &&_Str);

		template <typename tf_CStrDataType>
		inline_large TCStr(tf_CStrDataType const *_pStr);

		template <typename tf_CStrDataType>
		inline_large TCStr(tf_CStrDataType const *_pStr, umint _Len)
			requires (CImp::mc_bInitConstStr)
		;

		inline_large TCStr(CInitByRange, CChar const *_pStrStart, CChar const *_pStrEnd)
			requires (CImp::mc_bInitConstStr)
		;

		template <typename tf_CStrDataType>
		inline_large TCStr(tf_CStrDataType const *_pStr, umint _Len)
			requires (!CImp::mc_bInitConstStr)
		;

		template <typename tf_CStrDataType>
		inline_large TCStr(CAllowNUL, tf_CStrDataType const *_pStr, umint _Len)
			requires (!CImp::mc_bInitConstStr)
		;

		inline_large TCStr(CInitByRange, CChar const *_pStrStart, CChar const *_pStrEnd)
			requires (!CImp::mc_bInitConstStr)
		;

		template <typename ...tfp_CParams>
		constexpr inline_large TCStr(CStrInitGeneral _Init, tfp_CParams &&...p_Params)
			requires requires ()
			{
				CImp(fg_Forward<tfp_CParams>(p_Params)...);
			}
		;

		inline static TCStr fs_ToStr(CFormat const &_Format);

		template <typename tf_CStrTraitsF>
		inline_large TCStr(TCStr<tf_CStrTraitsF> const &_From);

		template <typename tf_CType>
		inline static TCStr fs_ToStr(tf_CType const &_Format);

		template <typename tf_CType>
		static TCStr fs_ToStr(CChar const *_pFormat, tf_CType const& _Format);

		template <typename tf_CStrDataType>
		static TCStr fs_Create(tf_CStrDataType const *_pStr);

		template <typename tf_CStrDataType>
		static TCStr fs_Create(tf_CStrDataType const *_pStr, aint _Len);

		template <typename tf_CStrTraitsF>
		static TCStr fs_Create(TCStr<tf_CStrTraitsF> const &_From);

		static TCStr fs_ReadTextStream(NStream::CBinaryStream &_Stream, bool _bAssumeUTF8 = false);

		CUnicodeIterator f_GetUnicodeIterator() const
			requires (mc_Type != EStrType_Ansi)
		;

		inline_small void f_Assign(TCStr const &_Src);
		inline_small void f_Assign(TCStr &&_Src);

		inline_small void f_SetModified();

		inline_small CChar const *f_GetStr() const;
		inline_small CChar *f_GetStrUniqueWritable();
		inline_small operator CChar const * () const;

		constexpr inline_small bool f_IsEmpty () const;
		constexpr inline_small explicit operator bool () const;

		TCStrSpan<typename CStrTraits::CTypes> f_Span() const;

		inline_large CChar *f_GetStr(umint _MaxLength);

		void f_TrimSize();

		void f_ConvertFromType(EStrType _Type);

		constexpr inline_small aint f_GetLen() const;
		inline_small umint f_GetSize() const;

		template <typename tf_CStrDataType>
		inline_small void f_AddChar(tf_CStrDataType _Char);

		void f_AddUnicodeChar(ch32 _Character);

		template <typename tf_CStrDataType>
		void f_AddChars(tf_CStrDataType _Char, aint _Count);

		template <typename tf_CStrIterator>
		void f_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From);

		void f_AddStr(CChar const *_pStr);
		void f_AddStr(CChar const *_pStr, aint _Len);
		template <typename tf_CStrDataType>
		void f_AddStr(tf_CStrDataType *_pStr);
		template <typename tf_CStrDataType>
		void f_AddStr(tf_CStrDataType const *_pStr, aint _Len);
		template <typename tf_CStrTraitsF>
		void f_AddStr(TCStr<tf_CStrTraitsF> const &_From);

		inline_small void f_AddStrLengthAwareInline(CAddStrAgrs const &_Args, CChar const *_pStr);
		inline_large void f_AddStrLengthAware(aint &_StrLen, CChar const *_pStr);
		inline_extralarge void f_AddStrLengthAware(CAddStrAgrs const &_Args, CChar const *_pStr);

		template <typename tf_CStrDataType>
		inline_medium void f_AddCharLengthAware(aint &_StrLen, tf_CStrDataType _Char);

		template <typename tf_CStrDataType>
		inline_large void f_AddCharsLengthAware(aint &_StrLen, tf_CStrDataType _Char, aint _Count);

		void f_SetStr(CChar const *_pStr);
		void f_SetStr(CChar const *_pStr, aint _Len);
		void f_SetStr(CAllowNUL, CChar const *_pStr, aint _Len);
		template <typename tf_CStrDataType>
		void f_SetStr(tf_CStrDataType *_pStr);
		template <typename tf_CStrDataType>
		void f_SetStr(tf_CStrDataType const *_pStr, aint _Len);
		template <typename tf_CStrTraitsF>
		void f_SetStr(TCStr<tf_CStrTraitsF> const &_From);

		template <typename tf_CType>
		inline_medium static void fs_ToStrInplace
			(
				TCEnableIf<!NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
				, tf_CType const& _Format
			)
		;

		template <typename tf_CType>
		static void fs_ToStrInplace
			(
				TCEnableIf<NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
				, tf_CType const& _Format
			)
		;

		template <typename tf_CType>
		static void fs_ToStrInplace(TCStr &_Destination, CChar const *_pFormat, tf_CType const& _Format);

		template <typename tf_CType>
		inline_medium static void fs_ToStrInplaceConcat
			(
				TCEnableIf<!NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
				, tf_CType const& _Format
			)
		;

		template <typename tf_CType>
		inline_medium static void fs_ToStrInplaceConcat
			(
				TCEnableIf<!NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
				, tf_CType const& _Format
				, aint &_Len
			)
		;

		template <typename tf_CType>
		static void fs_ToStrInplaceConcat
			(
				TCEnableIf<NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
				, tf_CType const& _Format
			)
		;

		template <typename tf_CType>
		static void fs_ToStrInplaceConcat(TCStr &_Destination, CChar const *_pFormat, tf_CType const& _Format);

		template <typename tf_CData>
		inline_small void f_SetAt(aint _Index, tf_CData _Character);
		ch32 f_GetAt(aint _Index) const;

		template <typename tf_CTypeData>
		tf_CTypeData f_ToValue(tf_CTypeData const &_Default) const;

		template <typename tf_CTypeData>
		tf_CTypeData f_ToValue(tf_CTypeData const &_Default, CChar const *_pFormat) const;

		int32 f_ToInt() const;
		template <typename tf_CReturn>
		tf_CReturn f_ToInt(tf_CReturn _FailValue) const;
		template <typename tf_CReturn, typename tf_CTerm>
		tf_CReturn f_ToInt(tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators) const;

		int32 f_ToIntExact() const;
		template <typename tf_CReturn>
		tf_CReturn f_ToIntExact(tf_CReturn _FailValue) const;
		template <typename tf_CReturn, typename tf_CTerm>
		tf_CReturn f_ToIntExact(tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators) const;

		fp32 f_ToFloat() const;
		template <typename tf_CReturn>
		tf_CReturn f_ToFloat(tf_CReturn _FailValue) const;
		template <typename tf_CReturn, typename tf_CTerm>
		tf_CReturn f_ToFloat(tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators) const;

		fp32 f_ToFloatExact() const;
		template <typename tf_CReturn>
		tf_CReturn f_ToFloatExact(tf_CReturn _FailValue) const;
		template <typename tf_CReturn, typename tf_CTerm>
		tf_CReturn f_ToFloatExact(tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators) const;

		template <typename tf_CData>
		inline_small typename TCChooseStrCompareType<CChar, tf_CData>::CType f_Cmp(tf_CData const *_pStr) const;
		template <typename tf_CData>
		inline_small typename TCChooseStrCompareType<CChar, tf_CData>::CType f_Cmp(tf_CData const *_pStr, umint _MaxLen) const;
		template <typename tf_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<CChar, TCStr<tf_CTCStrTraits2>>::CType f_Cmp(TCStr<tf_CTCStrTraits2> const &_Str) const;
		template <typename tf_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<CChar, TCStr<tf_CTCStrTraits2>>::CType f_Cmp(TCStr<tf_CTCStrTraits2> const &_Str, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small typename TCChooseStrCompareType<CChar, tf_CData>::CType f_CmpNoCase(tf_CData const *_pStr) const;
		template <typename tf_CData>
		inline_small typename TCChooseStrCompareType<CChar, tf_CData>::CType f_CmpNoCase(tf_CData const *_pStr, umint _MaxLen) const;
		template <typename tf_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<CChar, TCStr<tf_CTCStrTraits2>>::CType f_CmpNoCase(TCStr<tf_CTCStrTraits2> const &_Str) const;
		template <typename tf_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<CChar, TCStr<tf_CTCStrTraits2>>::CType f_CmpNoCase(TCStr<tf_CTCStrTraits2> const &_Str, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindChar(tf_CData _Char) const;
		template <typename tf_CData>
		inline_small aint f_FindChar(tf_CData _Char, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindChars(tf_CData const *_pChars) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindChars(TCStr<tf_CTCStrTraits> const &_Chars) const;
		template <typename tf_CData>
		inline_small aint f_FindChars(tf_CData const *_pChars, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindChars(TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindCharsNoCase(tf_CData const *_pChars) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Chars) const;
		template <typename tf_CData>
		inline_small aint f_FindCharsNoCase(tf_CData const *_pChars, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindCharsNoCase(TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindCharsReverse(tf_CData const *_pChars) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindCharsReverse(TCStr<tf_CTCStrTraits> const &_Chars) const;
		template <typename tf_CData>
		inline_small aint f_FindCharsReverse(tf_CData const *_pChars, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindCharsReverse(TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindCharsReverseNoCase(tf_CData const *_pChars) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Chars) const;
		template <typename tf_CData>
		inline_small aint f_FindCharsReverseNoCase(tf_CData const *_pChars, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindCharsReverseNoCase(TCStr<tf_CTCStrTraits> const &_Chars, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindCharOffset(aint _Start, tf_CData _Char) const;
		template <typename tf_CData>
		inline_small aint f_FindCharOffset(aint _Start, tf_CData _Char, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindCharNoCase(tf_CData _Char) const;
		template <typename tf_CData>
		inline_small aint f_FindCharNoCase(tf_CData _Char, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindCharNoCaseOffset(aint _Start, tf_CData _Char) const;
		template <typename tf_CData>
		inline_small aint f_FindCharNoCaseOffset(aint _Start, tf_CData _Char, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindCharReverse(tf_CData _Char) const;
		template <typename tf_CData>
		inline_small aint f_FindCharReverse(tf_CData _Char, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindCharReverseNoCase(tf_CData _Char) const;
		template <typename tf_CData>
		inline_small aint f_FindCharReverseNoCase(tf_CData _Char, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_Find(tf_CData const *_pStr) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_Find(TCStr<tf_CTCStrTraits> const &_Str) const;
		template <typename tf_CData>
		inline_small aint f_Find(tf_CData const *_pStr, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_Find(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const;
		template <typename tf_CData>
		inline_small aint f_Find(aint _Start, tf_CData const *_pStr) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_Find(aint _Start, TCStr<tf_CTCStrTraits> const &_Str) const;
		template <typename tf_CData>
		inline_small aint f_Find(aint _Start, tf_CData const *_pStr, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_Find(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindNoCase(tf_CData const *_pStr) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindNoCase(TCStr<tf_CTCStrTraits> const &_Str) const;
		template <typename tf_CData>
		inline_small aint f_FindNoCase(tf_CData const *_pStr, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindNoCase(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const;
		template <typename tf_CData>
		inline_small aint f_FindNoCase(aint _Start, tf_CData const *_pStr) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str) const;
		template <typename tf_CData>
		inline_small aint f_FindNoCase(aint _Start, tf_CData const *_pStr, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindNoCase(aint _Start, TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const;

		template <typename tf_CData>
		inline_small aint f_FindReverse(tf_CData const *_pStr1) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindReverse(TCStr<tf_CTCStrTraits> const &_Str) const;
		template <typename tf_CData>
		inline_small aint f_FindReverse(tf_CData const *_pStr1, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindReverse(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const;
		template <typename tf_CData>
		inline_small aint f_FindReverse(tf_CData const *_pStr1, umint _MaxLen, umint _FindLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindReverse(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen, umint _FindLen) const;

		template <typename tf_CData>
		inline_small aint f_FindReverseNoCase(tf_CData const *_pStr1) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str) const;
		template <typename tf_CData>
		inline_small aint f_FindReverseNoCase(tf_CData const *_pStr1, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen) const;
		template <typename tf_CData>
		inline_small aint f_FindReverseNoCase(tf_CData const *_pStr1, umint _MaxLen, umint _FindLen) const;
		template <typename tf_CTCStrTraits>
		inline_small aint f_FindReverseNoCase(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen, umint _FindLen) const;

		template <typename tf_CData>
		inline_small bool f_StartsWith(tf_CData const *_pStr) const;
		template <typename tf_CTCStrTraits>
		inline_small bool f_StartsWith(TCStr<tf_CTCStrTraits> const &_Str) const;

		template <typename tf_CData>
		inline_small bool f_StartsWithNoCase(tf_CData const *_pStr) const;
		template <typename tf_CTCStrTraits>
		inline_small bool f_StartsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str) const;

		template <typename tf_CData>
		inline_small bool f_EndsWith(tf_CData const *_pStr) const;
		template <typename tf_CTCStrTraits>
		inline_small bool f_EndsWith(TCStr<tf_CTCStrTraits> const &_Str) const;

		template <typename tf_CData>
		inline_small bool f_EndsWithNoCase(tf_CData const *_pStr) const;
		template <typename tf_CTCStrTraits>
		inline_small bool f_EndsWithNoCase(TCStr<tf_CTCStrTraits> const &_Str) const;

		inline_small bool f_IsAnsi() const;
		inline_small bool f_IsAlphaNumeric() const;
		inline_small bool f_IsAnsiAlphaNumeric() const;
		inline_small bool f_IsNumeric() const;
		inline_small bool f_IsIdentifierStatement() const;
		inline_small bool f_IsAlphaNumericStatement() const;

		constexpr uint32 f_Hash() const;
		constexpr uint32 f_HashDJB2() const;
		constexpr uint32 f_HashSDBM() const;

		inline_small CChar f_LargestChar();

		TCStr f_Indent(ch8 const *_pIndent, bool _bIndentFirst = true, bool _bIndentLastEmpty = true) const;

		template <bool tf_bRemoveEmpty = false, typename tf_CStrSeparator>
		NContainer::TCVector<TCStr> f_Split(tf_CStrSeparator const &_Separator) const;

		template <bool tf_bRemoveEmpty = false>
		NContainer::TCVector<TCStr> f_SplitEscaped(CChar _Separator) const;

		template <bool tf_bRemoveEmpty = false>
		NContainer::TCVector<TCStr> f_SplitLine() const;

		template <typename tf_CContainer, typename tf_CStrSeparator>
		static TCStr fs_Join(tf_CContainer &&_Strings, tf_CStrSeparator const &_Separator = "");

		template <typename tf_CContainer>
		static TCStr fs_JoinEscaped(tf_CContainer &&_Strings, CChar _Separator);

		TCStr f_UpperCase() const;
		TCStr f_UpperCase(umint _MaxLen) const;

		TCStr f_LowerCase() const;
		TCStr f_LowerCase(umint _MaxLen) const;

		TCStr f_Untabify(umint _TabLength) const;

		template <typename tf_CData, typename tf_CData2>
		TCStr f_ReplaceChar(tf_CData _CharFind, tf_CData2 _CharReplace) const;
		template <typename tf_CData, typename tf_CData2>
		TCStr f_ReplaceChar(tf_CData _CharFind, tf_CData2 _CharReplace, umint _MaxLen) const;

		template <typename tf_CData, typename tf_CData2>
		TCStr f_Replace(tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace) const;
		template <typename tf_CTCStrTraits, typename tf_CData>
		TCStr f_Replace(TCStr<tf_CTCStrTraits> const &_StrFind, tf_CData const *_pStrReplace) const;
		template <typename tf_CTCStrTraits, typename tf_CData>
		TCStr f_Replace(tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits> const &_StrReplace) const;
		template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
		TCStr f_Replace(TCStr<tf_CTCStrTraits> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace) const;
		template <typename tf_CData, typename tf_CData2>
		TCStr f_Replace(tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace, umint _MaxLen) const;
		template <typename tf_CTCStrTraits, typename tf_CData>
		TCStr f_Replace(TCStr<tf_CTCStrTraits> const &_StrFind, tf_CData const *_pStrReplace, umint _MaxLen) const;
		template <typename tf_CTCStrTraits, typename tf_CData>
		TCStr f_Replace(tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits> const &_StrReplace, umint _MaxLen) const;
		template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
		TCStr f_Replace(TCStr<tf_CTCStrTraits> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace, umint _MaxLen) const;

		template <typename tf_CData, typename tf_CData2>
		TCStr f_ReplaceNoCase(tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace) const;
		template <typename tf_CTCStrTraits, typename tf_CData>
		TCStr f_ReplaceNoCase(TCStr<tf_CTCStrTraits> const &_StrFind, tf_CData const *_pStrReplace) const;
		template <typename tf_CTCStrTraits, typename tf_CData>
		TCStr f_ReplaceNoCase(tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits> const &_StrReplace) const;
		template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
		TCStr f_ReplaceNoCase(TCStr<tf_CTCStrTraits> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace) const;
		template <typename tf_CData, typename tf_CData2>
		TCStr f_ReplaceNoCase(tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace, umint _MaxLen) const;
		template <typename tf_CTCStrTraits, typename tf_CData2>
		TCStr f_ReplaceNoCase(TCStr<tf_CTCStrTraits> const &_StrFind, tf_CData2 const *_pStrReplace, umint _MaxLen) const;
		template <typename tf_CTCStrTraits, typename tf_CData>
		TCStr f_ReplaceNoCase(tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits> const &_StrReplace, umint _MaxLen) const;
		template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2>
		TCStr f_ReplaceNoCase(TCStr<tf_CTCStrTraits> const &_StrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace, umint _MaxLen) const;

		template <typename tf_CData2>
		TCStr f_Insert(aint _StartChar, tf_CData2 const *_pStrInsert) const;
		template <typename tf_CTCStrTraits>
		TCStr f_Insert(aint _StartChar, TCStr<tf_CTCStrTraits> const &_StrInsert) const;
		template <typename tf_CData2>
		TCStr f_Insert(aint _StartChar, tf_CData2 const *_pStrInsert, umint _MaxLen) const;
		template <typename tf_CTCStrTraits>
		TCStr f_Insert(aint _StartChar, TCStr<tf_CTCStrTraits> const &_StrInsert, umint _MaxLen) const;

		TCStr f_EscapeStr() const;
		template <typename tf_CEscapeChar>
		TCStr f_EscapeStr(tf_CEscapeChar const *_pEscapeChars) const;
		template <typename tf_CEscapeChar, typename tf_CReplaceChars>
		TCStr f_EscapeStr(tf_CEscapeChar const *_pEscapeChars, tf_CReplaceChars const *_pReplaceChars) const;

		TCStr f_EscapeStrNoQuotes() const;
		template <typename tf_CEscapeChar>
		TCStr f_EscapeStrNoQuotes(tf_CEscapeChar const *_pEscapeChars) const;
		template <typename tf_CEscapeChar, typename tf_CReplaceChars>
		TCStr f_EscapeStrNoQuotes(tf_CEscapeChar const *_pEscapeChars, tf_CReplaceChars const *_pReplaceChars) const;

		TCStr f_Delete(aint _StartChar, umint _nChars) const;
		TCStr f_Left(umint _nChars) const;

		TCStr f_Extract(aint _StartChar, umint _nChars) const;
		TCStr f_Extract(aint _StartChar) const;

		TCStr f_Slice(aint _iStart, aint _iEnd) const;

		TCStr f_Reverse() const;

		TCStr f_Right(umint _nChars) const;

		template <typename tf_CData>
		TCStr f_TrimLeft(tf_CData const *_pCharsToTrim) const;
		TCStr f_TrimLeft() const;

		template <typename tf_CData>
		TCStr f_TrimRight(tf_CData const *_pCharsToTrim) const;
		TCStr f_TrimRight() const;

		template <typename tf_CData>
		TCStr f_Trim(tf_CData const *_pCharsToTrim) const;
		TCStr f_Trim() const;

		template <typename tf_CStr>
		TCStr f_RemovePrefix(tf_CStr const &_ToFind) const;
		template <typename tf_CStr>
		TCStr f_RemoveSuffix(tf_CStr const &_ToFind) const;

		inline_large TCStr &operator = (TCStr const &_From);
		inline_large TCStr &operator = (TCStr &&_From);
		inline_large TCStr &operator = (CFormat const &_Format);

		template <typename tf_CStrTraitsF>
		inline_large TCStr &operator = (TCStr<tf_CStrTraitsF> const &_From);

		template <typename tf_CDataF>
		inline_large TCStr &operator = (tf_CDataF const *_pFrom);

		bool operator ! ();

		template <typename tf_CTCStrTraits>
		bool operator == (TCStr<tf_CTCStrTraits> const &_Right) const noexcept;

		template <typename tf_CData>
		bool operator == (tf_CData const *_pRight) const noexcept;

		template <typename tf_CTCStrTraits>
		COrdering_Strong operator <=> (TCStr<tf_CTCStrTraits> const &_Right) const noexcept;

		template <typename tf_CData>
		COrdering_Strong operator <=> (tf_CData const *_pRight) const noexcept;

		inline_small CChar &operator [] (aint _Index);
		inline_small CChar const &operator [] (aint _Index) const;

		inline_large TCStr &operator += (CFormat const &_Format);
		inline_large TCStr &operator += (ch32 _ToAdd);

		template <typename tf_CStrTraitsF>
		inline_large TCStr &operator += (TCStr<tf_CStrTraitsF> const &_Str);

		template <typename tf_CStrDataType>
		inline_large TCStr &operator += (tf_CStrDataType const *_pToAdd);

		template <typename tf_CStrTraitsF>
		inline_large TCStr &operator += (TCStr<tf_CStrTraitsF> &&_Str);

		template <typename tf_CStrTraitsF>
		TCStr operator + (TCStr<tf_CStrTraitsF> const &_Str)  const;

		template <typename tf_CStrDataType>
		TCStr operator + (tf_CStrDataType const *_pToAdd) const;

		TCStr operator ^ (umint _nCopies) const;

		constexpr static CChar mc_FormatStr[] = {'{', '}', 0};

	private:
		using CTempStr = TCConditional
			<
				NTraits::cIsSame<typename CStrTraits::CAllocator, NMemory::CAllocator_NonTrackedHeap>
				, CStrNonTracked
				, CStr
			>
		;

		static_assert(sizeof(CChar) != 1 || mc_Type == EStrType_Ansi || mc_Type == EStrType_Unicode || mc_Type == EStrType_UTF);
		static_assert(sizeof(CChar) != 2 || mc_Type == EStrType_Unicode || mc_Type == EStrType_UTF);
		static_assert(sizeof(CChar) < 4 || mc_Type == EStrType_Unicode);

		template <int tf_CharSize, typename tf_CStrIterator>
		TCEnableIf<tf_CharSize == 1, void> fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From);

		template <int tf_CharSize, typename tf_CStrIterator>
		TCEnableIf<tf_CharSize == 2, void> fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From);

		template <int tf_CharSize, typename tf_CStrIterator>
		TCEnableIf<tf_CharSize != 1 && tf_CharSize != 2, void> fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From);

		template <int tf_CharSize>
		TCEnableIf<tf_CharSize == 1, void> fp_ConvertFromType(EStrType _Type);

		template <int tf_CharSize>
		TCEnableIf<tf_CharSize == 2, void> fp_ConvertFromType(EStrType _Type);

		template <int tf_CharSize>
		TCEnableIf<tf_CharSize != 1 && tf_CharSize != 2, void> fp_ConvertFromType(EStrType _Type);

		enum
		{
			EDebug_CharSize = sizeof(CChar)
			, EDebug_Type = t_CTCStrTraits::CStrTraits::mc_Type
		};
	};

	template <typename t_TCStr0, typename t_TCStr1>
	struct TCIsStrCompatible
	{
		constexpr static bool mc_Value =
			(
				sizeof(typename t_TCStr0::CStrTraits::CChar) == sizeof(typename t_TCStr1::CStrTraits::CChar)
				&& t_TCStr0::CStrTraits::mc_Type == t_TCStr1::CStrTraits::mc_Type
			)
			||
			(
				t_TCStr0::CStrTraits::mc_Type == EStrType_Unicode
				&& t_TCStr1::CStrTraits::mc_Type == EStrType_Unicode
			)
		;
	};

	template <typename t_TCStr0, typename t_TCStr1>
	struct TCIsStrCompatibleWrite
	{
		constexpr static bool mc_Value =
			(
				sizeof(typename t_TCStr0::CStrTraits::CChar) == sizeof(typename t_TCStr1::CStrTraits::CChar)
				&& t_TCStr0::CStrTraits::mc_Type == t_TCStr1::CStrTraits::mc_Type
			)
			||
			(
				sizeof(typename t_TCStr0::CStrTraits::CChar) >= sizeof(typename t_TCStr1::CStrTraits::CChar)
				&& t_TCStr0::CStrTraits::mc_Type == EStrType_Unicode
				&& t_TCStr1::CStrTraits::mc_Type == EStrType_Unicode
			)
		;
	};

	CStr fg_ReadTextStream(NStream::CBinaryStream &_Stream, bool _bAssumeUTF8 = false);
}

#include "Malterlib_String_Container_Algorithm.h"
