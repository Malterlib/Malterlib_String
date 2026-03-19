// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CFloatType>
	struct TCStrParseType_Float final : public TICStrParseType<t_CParser>
	{
		using CStrTraits = typename t_CParser::CStrTraits;
		using CChar = typename CStrTraits::CChar;

		using CSuper = TICStrParseType<t_CParser>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;

		struct COptionsFloat : public COptions
		{
			COptionsFloat() = default;
		};

		inline_small TCStrParseType_Float(t_CFloatType &_Value);
		TCStrParseType_Float(TCStrParseType_Float const &_Value) = delete;
		TCStrParseType_Float &operator = (TCStrParseType_Float const &_Value) = delete;

		virtual umint f_Destruct() override;
		virtual bool f_ParseData(CChar const * &_pString, CChar const *_pFormat, t_CParser const &_ArgData) const override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;

		template <typename tf_COptions>
		inline_small aint f_ParseOption(COption &_Option, tf_COptions &_Options, t_CParser const &_ArgData) const;

		constexpr static bool mc_bNeedDestruct = false;

	private:
		t_CFloatType &mp_Value;
	};

	template <typename t_CParser, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	struct TCStringParser<t_CParser, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
	{
		using CFloat = NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>;
		using CParseType = TCStrParseType_Float<t_CParser, CFloat>;

		static inline_large void f_CreateParse(t_CParser &_Formatter, CFloat &_Data);
	};
}

#include "Malterlib_String_Container_Parse_Float.hpp"
