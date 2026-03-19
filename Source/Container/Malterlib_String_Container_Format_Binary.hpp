// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CBinaryType>
	umint TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_Destruct()
	{
		if constexpr (mc_bNeedDestruct)
			this->~TCStrFormatType_Binary();
		return sizeof(*this);
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	void TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_Move(t_CFormatter &_Formatter)
	{
		DMibFastCheck(false); // Not supported
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	inline_small TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::TCStrFormatType_Binary(t_CBinaryType const &_Value)
		: mp_Value(_Value)
	{
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	template <typename tf_COptions>
	inline_small void TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CType const &_Value)
	{
		uint8 OutValue = 0;
		auto Temp = fg_FormatMaxLength<2>(fg_FormatMinLength<2>(fg_FormatFillOut<'0'>(fg_FormatIntFormat<16>(OutValue))));

		using CFormatType = typename TCStringFormatter<t_CFormatter, decltype(Temp)>::CFormatType;

		uint8 const *pValue = (uint8 const *)_Value.f_GetArray();
		umint nBytes = _Value.f_GetSize();

		for (umint i = 0; i < nBytes; ++i)
		{
			NMemory::fg_MemCopy(&OutValue, pValue + i, 1);
			CFormatType::fs_AddToStrStatic(_String, _CurrentStrLen, Temp);
		}

	}

	template <typename t_CFormatter, typename t_CBinaryType>
	void TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const
	{
		COptionsStatic Static;
		COptions Options(Static);

		if (_pFormat)
		{
			TICStrFormatType_ParseOptionsArgs<CType const, TCStrFormatType_Binary, COptions> Args(mp_Value, *this, _String, _CurrentStrLen, Options, _ArgData);
			CSuper::fs_ParseOptions(Args, _pFormat);
		}

		fp_AddToStr(_String, _CurrentStrLen, Options, mp_Value);
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	inline_small void TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CType const &_Value)
	{
		COptionsStatic Options;
		fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	inline_small void TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CType const &_Value, COptionsStatic &_Options)
	{
		fp_AddToStr(_String, _CurrentStrLen, _Options, _Value);
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	aint TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_Get_aint() const
	{
		return 0;
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	fp32 TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_Get_fp32() const
	{
		return 0.0f;
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	fp64 TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_Get_fp64() const
	{
		return 0.0;
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	void TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_Visit(CVisitor &_Extractor) const
	{
		_Extractor();
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	void const *TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_GetTypeID() const
	{
		return &mcp_TypeID;
	}

	template <typename t_CFormatter, typename t_CBinaryType>
	bool TCStrFormatType_Binary<t_CFormatter, t_CBinaryType>::f_IsSame(void const *_pRight) const
	{
		TCStrFormatType_Binary const *pRight = static_cast<TCStrFormatType_Binary const *>(_pRight);

		if (mp_Value.f_GetSize() != pRight->mp_Value.f_GetSize())
			return false;

		if (NMemory::fg_MemCmp((uint8 const *)mp_Value.f_GetArray(), (uint8 const *)pRight->mp_Value.f_GetArray(), mp_Value.f_GetSize()) != 0)
			return false;

		return true;
	}

	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapper>::fs_CreateFormat(t_CFormatter &_Formatter, CStrFormatBinaryWrapper const &_Data)
		-> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(_Data);
		return typename CFormatType::CStrFormatTypeClassifier();
	}

	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>::fs_CreateFormat(t_CFormatter &_Formatter, CStrFormatBinaryWrapperUntyped const &_Data)
		-> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(_Data);
		return typename CFormatType::CStrFormatTypeClassifier();
	}
}
