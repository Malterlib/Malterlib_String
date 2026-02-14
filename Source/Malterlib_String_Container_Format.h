// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Container/Malterlib_String_Container_FormatPrivate.hpp"

namespace NMib::NStr
{
	template <typename t_CTCStrTraits>
	struct TCStr;

	enum class EStringFormatTypeFlag : uint8
	{
		mc_None = 0
		, mc_NeedDestruct = fg_Bit(0)
		, mc_NeedDealloc = fg_Bit(1)
	};

	template <typename t_CTCStrTraits>
	struct TCFormat
	{
		using CChar = typename t_CTCStrTraits::CStrTraits::CChar;
		using CAllocator = typename t_CTCStrTraits::CStrTraits::CAllocator;
		using CString = TCStr<t_CTCStrTraits>;
		using CTStrTraits = t_CTCStrTraits;
		using CFomatArgType = TICStrFormatType<TCFormat>;

		static constexpr EStrType mc_Type = t_CTCStrTraits::CStrTraits::mc_Type;

		TCFormat(TCFormat &&_Other);
		TCFormat(const TCFormat &_Other) = delete;
		TCFormat& operator=(TCFormat const& _Other) = delete;

		explicit inline_medium TCFormat(const CChar *_pFormatStr);
		template <typename tf_CTCStrTraits>
		explicit inline_medium TCFormat(TCStr<tf_CTCStrTraits> const &_Format);

		~TCFormat();

		TCFormat &operator=(TCFormat &&_Other);

		void f_MoveFormats(TCFormat &&_Other);
		void fp_AddFormat(TICStrFormatType<TCFormat> *_pFormat, EStringFormatTypeFlag _Flags);
		inline_medium void *f_AllocSpace(mint _Size, EStringFormatTypeFlag &_Flags);

		template <typename tf_CType, typename ...tfp_CParams>
		inline_medium tf_CType *f_Alloc(tfp_CParams && ...p_Params);

		inline_medium const TICStrFormatType<TCFormat> *f_GetArg(aint _iArgument) const;

		mint f_GetNumArgs() const;
		bool f_IsEmpty() const;

		void f_ClearFormats();

		bool operator == (TCFormat const &_Right) const;

		inline_small void f_FormatToStr(TCStr<t_CTCStrTraits> &_Str) const;
		inline_small void f_FormatToStrConcat(TCStr<t_CTCStrTraits> &_Str) const;
		inline_small void f_FormatArgumentsToStr(TCStr<t_CTCStrTraits> &_Str) const;
		inline_small void f_FormatArgumentsToStrConcat(TCStr<t_CTCStrTraits> &_Str) const;
		void f_SetFormatStr(const CChar *_pFormatStr);
		TCStr<t_CTCStrTraits> f_GetStr() const;
		TCStr<t_CTCStrTraits> operator ^ (mint _nCopies) const;

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_FormatInto) const;

		template <typename tf_CType>
		inline_small TCFormat &operator << (tf_CType const &_Type) &
			requires
			( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
				!cHasFormatClass<tf_CType, EStrTypeClass_Untyped>
			)
		;

		template <typename tf_CType>
		inline_small TCFormat &operator << (tf_CType &_Type) &
			requires
			( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
				!cHasFormatClass<tf_CType, EStrTypeClass_Untyped>
			)
		;

		template <typename tf_CType>
		inline_small TCFormat &&operator << (tf_CType const &_Type) &&
			requires
			( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
				!cHasFormatClass<tf_CType, EStrTypeClass_Untyped>
			)
		;

		template <typename tf_CType>
		inline_small TCFormat &&operator << (tf_CType &_Type) &&
			requires
			( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
				!cHasFormatClass<tf_CType, EStrTypeClass_Untyped>
			)
		;

		template <typename tf_CType>
		static auto fs_GetFormatClassifier(tf_CType const &_Type) -> decltype(TCStringFormatterAll<TCFormat, tf_CType>::fs_CreateFormat(*((TCFormat *)0), _Type)); // Only used compile time

		template <bool tf_bConcat>
		static void fp_FormatArguments(const TCFormat &_Format, TCStr<t_CTCStrTraits> &_ToStr);

		template <bool tf_bConcat>
		static void fp_FormatArgList(const TCFormat &_Format, const CChar *_pFormat, TCStr<t_CTCStrTraits> &_ToStr);

	private:
		inline_small TICStrFormatType<TCFormat> **fp_GetFormatList() const;
		inline_small TICStrFormatType<TCFormat> const *fp_GetFormatEntry(aint _iEntry) const;
		void *fp_AllocSpace(int _Bytes);

		constexpr static mint mcp_StaticFormats = 16;
		constexpr static mint mcp_StaticSpace = mcp_StaticFormats * 4;

		uaint m_nFormats;
		mutable aint m_iCurrentArgument;
		TICStrFormatType<TCFormat> **m_pFormats;
		const CChar *m_pFormatStr;

		TICStrFormatType<TCFormat> *m_plFormats[mcp_StaticFormats];
		NContainer::TCVector<TICStrFormatType<TCFormat> *, CAllocator> m_lFormats;

		aint m_AllocSpace[mcp_StaticSpace];
		int m_iCurrentAlloc;
	};

	struct CStrFormatBinaryWrapper
	{
		template <typename tf_CType>
		CStrFormatBinaryWrapper(tf_CType const &_Data);
		CStrFormatBinaryWrapper(void const *_pData, mint _Size);

		void const *f_GetArray() const;
		mint f_GetSize() const;

	private:
		const void *mp_pData;
		mint mp_Size;
	};

	struct CStrFormatBinaryWrapperUntyped : public CStrFormatBinaryWrapper
	{
		template <typename tf_CType>
		CStrFormatBinaryWrapperUntyped(tf_CType &_Data);
	};

	template <typename t_CFormatter, typename t_CToFormat, bool t_bByReference>
	struct TCStrFormatType_Inline;

	template <typename t_CFormatter, typename t_CData>
	struct TCStringFormatter : public NPrivate::TCStringFormatterHelper<t_CFormatter, t_CData>
	{
	};

	template <typename t_CFormatter, typename t_CData, typename t_CTypeWithConst>
	struct TCStringFormatterAll
	{
		using CStringFormatter = typename NPrivate::TCDetermineStringFormatter<t_CFormatter, t_CData>::CType;
		using CFormatType = typename CStringFormatter::CFormatType;

		static auto fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data) -> decltype(CStringFormatter::template fs_CreateFormat<t_CTypeWithConst>(_Formatter, _Data));
	};

	template <typename tf_CData>
	CStrFormatBinaryWrapper fg_FormatAsBinary(tf_CData const &_Data);

	template <typename tf_CFormatter, typename tf_CData>
	inline_small typename TCStringFormatterAll<tf_CFormatter, tf_CData>::CFormatType fg_GetStringFormatType(tf_CFormatter &_Formatter, tf_CData const &_Data);

	template <typename tf_CFormatter, typename tf_CData>
	inline_small typename NPrivate::TCDetermineStringFormatterReturnType<tf_CFormatter, tf_CData>::CType fg_CreateStringFormatter(tf_CFormatter &_Formatter, tf_CData const &_Data);

	template <typename tf_CFormat>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format);

	template <typename tf_CFormat, typename tf_CFirst, typename... tfp_CParams>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format, tf_CFirst &&_First);

	template <typename tf_CFormat, typename tf_CFirst, typename... tfp_CParams>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format, tf_CFirst &&_First, tfp_CParams &&...p_Params);

	template <typename tf_CReturnString, typename tf_CFormat, typename... tfp_CParams>
	tf_CReturnString fg_Format(tf_CFormat const &_Format, tfp_CParams &&...p_Params);

	template <typename tf_CReturnString, typename tf_CFormat, typename... tfp_CParams>
	void fg_AppendFormat(tf_CReturnString &_String, tf_CFormat const &_Format, tfp_CParams &&...p_Params);
}

#include "Container/Malterlib_String_Container_Format.hpp"
