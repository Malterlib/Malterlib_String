// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CFloatType>
	umint TCStrParseType_Float<t_CParser, t_CFloatType>::f_Destruct()
	{
		if constexpr (mc_bNeedDestruct)
			this->~TCStrParseType_Float();
		return sizeof(*this);
	}

	template <typename t_CParser, typename t_CFloatType>
	inline_small TCStrParseType_Float<t_CParser, t_CFloatType>::TCStrParseType_Float(t_CFloatType &_Value)
		: mp_Value(_Value)
	{
	}

	template <typename t_CParser, typename t_CFloatType>
	template <typename tf_COptions>
	inline_small aint TCStrParseType_Float<t_CParser, t_CFloatType>::f_ParseOption(COption &_Option, tf_COptions &_Options, t_CParser const &_ArgData) const
	{
		return CSuper::f_ParseOption(_Option, _Options, _ArgData);
	}

	template <typename t_CParser, typename t_CFloatType>
	bool TCStrParseType_Float<t_CParser, t_CFloatType>::f_ParseData(CChar const * &_pString, CChar const *_pFormat, t_CParser const &_ArgData) const
	{
		COptionsFloat Options;
		CChar Terminator = *CSuper::fs_ParseOptions(*this, Options, _pFormat, _ArgData);

		CChar const Terminators[] = {Terminator, 0};
		mp_Value = NStr::fg_StrToFloatParseExact(_pString, mp_Value, Terminators);
		return true;
	}

	template <typename t_CParser, typename t_CFloatType>
	aint TCStrParseType_Float<t_CParser, t_CFloatType>::f_Get_aint() const
	{
		return fg_Convert<aint>(mp_Value.f_ToInt());
	}

	template <typename t_CParser, typename t_CFloatType>
	fp32 TCStrParseType_Float<t_CParser, t_CFloatType>::f_Get_fp32() const
	{
		return mp_Value;
	}

	template <typename t_CParser, typename t_CFloatType>
	fp64 TCStrParseType_Float<t_CParser, t_CFloatType>::f_Get_fp64() const
	{
		return mp_Value;
	}

	template <typename t_CParser, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	inline_large void TCStringParser<t_CParser, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
		::f_CreateParse(t_CParser &_Formatter, CFloat &_Data)
	{
		EStringParseTypeFlag Flags;
		void *pSpace = _Formatter.f_AllocSpace(sizeof(CParseType), Flags);

		CParseType *pNew = new(pSpace) CParseType(_Data);
		Flags |= (CParseType::mc_bNeedDestruct ? EStringParseTypeFlag::mc_NeedDestruct : EStringParseTypeFlag::mc_None);
		_Formatter.fp_AddParse(pNew, Flags);
	}
}
