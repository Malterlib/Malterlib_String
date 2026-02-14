// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CData>
	struct TCStringFormatter;

	template <typename t_CFormatter, typename t_CData, typename t_CTypeWithConst = t_CData>
	struct TCStringFormatterAll;
}

namespace NMib::NStr::NPrivate
{
	template <typename t_CData, typename t_CFormatter>
	concept cHas_f_GetStringFormatType =
		requires
		(
			t_CData *_pData
			, t_CFormatter &_Formatter
		)
		{
			_pData->f_GetStringFormatType(_Formatter);
		}
	;

	template <typename t_CData, typename t_CFormatter>
	concept cHas_f_CreateStringFormatter =
		requires
		(
			t_CData const *_pData
			, t_CFormatter &_Formatter
		)
		{
			_pData->f_CreateStringFormatter(_Formatter);
		}
	;

	template <typename t_CData>
	concept cHas_f_Format =
		requires (t_CData const *_pData, CStr &o_Str)
		{
			_pData->f_Format(o_Str);
		}
		|| requires (t_CData const *_pData, CStr &o_Str, typename t_CData::CFormatOptions &_Options)
		{
			_pData->f_Format(o_Str, _Options);
		}
	;

	enum class EStringFormatType : uint32
	{
		mc_InlineCreateStringFormatter
		, mc_Inline
		, mc_FormatterTemplate
	};

	template
	<
		typename t_CFormatter
		, typename t_CData
		, EStringFormatType t_FormatType
		= cHas_f_GetStringFormatType<t_CData, t_CFormatter> && cHas_f_CreateStringFormatter<t_CData, t_CFormatter> ? EStringFormatType::mc_InlineCreateStringFormatter
		: cHas_f_Format<t_CData> ? EStringFormatType::mc_Inline
		: EStringFormatType::mc_FormatterTemplate
	>
	struct TCStringFormatterHelper;

	template <typename t_CFormatter, typename t_CData>
	struct TCStringFormatterEnum
	{
	public:
		using CFormatType = TCStrFormatType_Int<t_CFormatter, NTraits::TCEnumUnderlyingType<t_CData>>;

		template <typename tf_CTypeWithConst, typename tf_CData>
		static inline_large CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, tf_CData const &_Data)
		{
			_Formatter.template f_Alloc<CFormatType>(static_cast<NTraits::TCEnumUnderlyingType<tf_CData>>(_Data));
			return typename CFormatType::CStrFormatTypeClassifier();
		}
	};

	template <typename t_CFormatter, typename t_CData, bool t_bIsEnum = NMib::NTraits::cIsEnum<t_CData>>
	struct TCDetermineStringFormatter
	{
		using CType = TCStringFormatter<t_CFormatter, t_CData>;
	};

	template <typename t_CFormatter, typename t_CData>
	struct TCDetermineStringFormatter<t_CFormatter, t_CData, true>
	{
		using CType = TCStringFormatterEnum<t_CFormatter, t_CData>;
	};

	template <typename t_CFormatter, typename t_CData>
	struct TCDetermineStringFormatterReturnType
	{
		using CType = decltype(TCStringFormatterAll<t_CFormatter, t_CData>::fs_CreateFormat(fg_GetType<t_CFormatter &>(), fg_GetType<t_CData const &>()));
	};
}
