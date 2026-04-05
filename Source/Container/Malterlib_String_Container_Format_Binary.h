// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CBinaryType>
	struct TCStrFormatType_Binary final : public TICStrFormatType<t_CFormatter>
	{
	public:
		using CStrFormatTypeClassifier = TCConditional<NTraits::cIsSame<CStrFormatBinaryWrapperUntyped, t_CBinaryType>, CStrFormatTypeClassifier_Untyped, CStrFormatTypeClassifier_Binary>;
		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CChar = typename CTStrTraits::CStrTraits::CChar;
		using CSuper = TICStrFormatType<t_CFormatter>;
		using CType = t_CBinaryType;
		using CVisitor = typename CSuper::CVisitor;
		using COption = typename TICStrFormatType<t_CFormatter>::COption;
		using COptions = typename TICStrFormatType<t_CFormatter>::COptions;
		using COptionsStatic = typename TICStrFormatType<t_CFormatter>::COptionsStatic;

		inline_small TCStrFormatType_Binary(t_CBinaryType const &_Value);

		virtual umint f_Destruct() override;
		virtual void f_Move(t_CFormatter &_Formatter) override;
		virtual void f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;
		virtual void f_Visit(CVisitor &_Extractor) const override;
		virtual void const *f_GetTypeID() const override;
		virtual bool f_IsSame(void const *_pRight) const override;

		inline_small static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CType const &_Value);
		inline_small static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CType const &_Value, COptionsStatic &_Options);

		constexpr static bool mc_bNeedDestruct = true;

	private:
		template <typename tf_COptions>
		inline_small static void fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions const &_Options, const CType &_Value);

		inline static bool constexpr mcp_TypeID = false;

		t_CBinaryType mp_Value;
	};

	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapper>
	{
		using CFormatType = TCStrFormatType_Binary<t_CFormatter, CStrFormatBinaryWrapper>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CStrFormatBinaryWrapper const &_Data);
	};

	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>
	{
		using CFormatType = TCStrFormatType_Binary<t_CFormatter, CStrFormatBinaryWrapperUntyped>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CStrFormatBinaryWrapperUntyped const &_Data);
	};
}

#include "Malterlib_String_Container_Format_Binary.hpp"
