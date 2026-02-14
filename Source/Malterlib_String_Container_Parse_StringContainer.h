// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CStrTraitsIn>
	struct TCStrParseType_TStr final : public TICStrParseType<t_CParser>
	{
		static_assert(t_CStrTraitsIn::CStrTraits::mc_Type == t_CParser::CStrTraits::mc_Type);

		using CStrTraits = typename t_CParser::CStrTraits;
		using CChar = typename CStrTraits::CChar;
		using CSuper = TICStrParseType<t_CParser>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;

		struct COptionsStr : public COptions
		{
			uint32 m_bEscaped:1 = false;
			uint32 m_bRemoveEscape:1 = false;
			CChar m_EscapedChars[16] = {'\"', '\\', 0};
		};

		inline_small TCStrParseType_TStr(TCStr<t_CStrTraitsIn> &_Str);
		inline_small TCStrParseType_TStr(TCStr<t_CStrTraitsIn> *_pStr);
		TCStrParseType_TStr(TCStrParseType_TStr const &_Value) = delete;
		TCStrParseType_TStr &operator = (TCStrParseType_TStr const &_Value) = delete;

		virtual mint f_Destruct() override;
		virtual bool f_ParseData(CChar const * &_pString, CChar const *_pFormat, t_CParser const &_ArgData) const override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;
		virtual aint f_Get_Str(CChar *_pStr, aint _MaxChars) const override;

		template <typename tf_COptions>
		inline_small aint f_ParseOption(COption &_Option, tf_COptions &_Options, t_CParser const &_ArgData) const;

		constexpr static bool mc_bNeedDestruct = false;

	private:
		TCStr<t_CStrTraitsIn> *mp_pTStr;
	};

	template <typename t_CParser, typename t_CStrTraitsIn>
	struct TCStringParser<t_CParser, TCStr<t_CStrTraitsIn>>
	{
		using CParseType = TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>;

		static inline_large void f_CreateParse(t_CParser &_Formatter, TCStr<t_CStrTraitsIn> &_Data);
	};
}

#include "Container/Malterlib_String_Container_Parse_StringContainer.hpp"
