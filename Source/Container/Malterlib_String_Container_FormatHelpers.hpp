// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	static inline CStrNonTracked::CFormat fg_GetStringFormat(const ch8 *_pFormat)
	{
		return CStrNonTracked::CFormat(_pFormat);
	}

	static inline CWStrNonTracked::CFormat fg_GetStringFormat(const ch16 *_pFormat)
	{
		return CWStrNonTracked::CFormat(_pFormat);
	}

	static inline CUStrNonTracked::CFormat fg_GetStringFormat(const ch32 *_pFormat)
	{
		return CUStrNonTracked::CFormat(_pFormat);
	}

	template <typename tf_CFormat, typename... tfp_CParams>
	CStr fg_Format(tf_CFormat const &_Format, tfp_CParams &&...p_Params)
	{
		return fg_Format<CStr>(_Format, fg_Forward<tfp_CParams>(p_Params)...);
	}
}

namespace NMib::NStr::NPrivate
{
	template <typename t_CDataToTest, typename t_CClassToTestAgainst>
	struct TCHasFormatClassHelper
	{
	private:
		static t_CDataToTest const &fps_GetData();
		static t_CClassToTestAgainst &fps_GetFormatClass();
		template <typename tf_CData>
		static auto fps_CheckFormat(tf_CData const& data) -> decltype(CStr::CFormat::fs_GetFormatClassifier(data).f_ClassifiedAs(fps_GetFormatClass()));
		template <typename tf_CData>
		static auto fps_CheckFormat(tf_CData &&) -> NTraits::CFalseBySize;

	public:
		constexpr static bool mc_bValue = sizeof(fps_CheckFormat(fps_GetData())) == sizeof(NTraits::CTrueBySize);
	};

	static_assert(cHas_f_Format<NContainer::TCVector<uint32>>);

	template
	<
		typename t_CFormatter
		, typename t_CData
		, EStringFormatType t_FormatType
	>
	struct TCStringFormatterHelper
	{
	};

	template
	<
		typename t_CFormatter
		, typename t_CData
	>
	struct TCStringFormatterHelper<t_CFormatter, t_CData, EStringFormatType::mc_InlineCreateStringFormatter>
	{
		using CFormatType = decltype(fg_GetType<t_CData &>().f_GetStringFormatType(fg_GetType<t_CFormatter &>()));

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data)
		{
			return _Data.f_CreateStringFormatter(_Formatter);
		}
	};

	template
	<
		typename t_CFormatter
		, typename t_CData
	>
	struct TCStringFormatterHelper<t_CFormatter, t_CData, EStringFormatType::mc_Inline>
	{
		using CFormatType = TCStrFormatType_Inline<t_CFormatter, t_CData, true>;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data)
		{
			using CFormatType = TCStrFormatType_Inline<t_CFormatter, t_CData, true>;
			_Formatter.template f_Alloc<CFormatType>(_Data);
			return typename CFormatType::CStrFormatTypeClassifier();
		}
	};

	template
	<
		typename t_CFormatter
		, typename t_CData
	>
	struct TCStringFormatterHelper<t_CFormatter, t_CData, EStringFormatType::mc_FormatterTemplate>
	{
		using CFormatType = typename TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data)
		{
			return TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>::template fs_CreateFormat<CStrFormatBinaryWrapperUntyped>(_Formatter, _Data);
		}
	};

	template <typename t_CFormatter, typename t_CData>
	struct TCStringFormatterHelper<t_CFormatter, TCByValue<t_CData>, EStringFormatType::mc_FormatterTemplate>
	{
	public:
		using CFormatType = TCStrFormatType_Inline<t_CFormatter, t_CData, false>;

		template <typename tf_CTypeWithConst>
		static inline_large auto fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<t_CData> const &_Data)
		{
			_Formatter.template f_Alloc<CFormatType>(*_Data);
			return typename CFormatType::CStrFormatTypeClassifier();
		}
	};
}
