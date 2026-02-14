// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#ifdef DMibPCanDo_fp128
#include <Mib/Numeric/fp128>
#endif

namespace NMib::NStr
{
	template
		<
			typename t_CFormatter
			, aint t_SignBits
			, aint t_ExponentBits
			, aint t_MantissaBits
			, aint t_PaddingBits
			, typename t_CImplicitFloat
			, bool t_bDummyOptimize
			, typename t_CIntegerStorage
			, bool t_bReference
		>
	class TCStrFormatType_Float final : public TICStrFormatType<t_CFormatter>
	{
	public:
		using CSuper = TICStrFormatType<t_CFormatter>;
		using CStrFormatTypeClassifier = CStrFormatTypeClassifier_Float;
		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CFloatIn = NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>;

		static constexpr aint mc_MantissaBits = t_MantissaBits + 8;
		static constexpr aint mc_MinExponentBits = gc_HighestBitSet<aint, mc_MantissaBits + (mc_MantissaBits - 1)> + 2;
		static constexpr aint mc_ExponentBits = (t_ExponentBits > mc_MinExponentBits ? t_ExponentBits : mc_MinExponentBits);
		using CFloat = CFloatIn;
		using CChar = typename CTStrTraits::CStrTraits::CChar;
		using CInteger = typename CFloat::CInteger;
		using CUnsignedInteger = typename CFloat::CUnsignedInteger;
		using CString = typename CSuper::CString;
		using COptionsStatic = typename CSuper::COptionsStatic;
		using CVisitor = typename CSuper::CVisitor;
		using CStorage = TCConditional<t_bReference, CFloat const &, CFloat>;
		using CType = CFloat;

		using COption = typename TICStrFormatType<t_CFormatter>::COption;
		using COptions = typename TICStrFormatType<t_CFormatter>::COptions;

		inline_small TCStrFormatType_Float(CFloatIn const &_Value);
		virtual mint f_Destruct() override;
		virtual void f_Move(t_CFormatter &_Formatter) override;

		struct COptionsFloat : public COptions
		{
			enum EFloatFormat
			{
				EFloatFormat_Fixed,
				EFloatFormat_Exponent,
				EFloatFormat_ExponentLowerCase,
				EFloatFormat_Shortest,
				EFloatFormat_ShortestLowerCase,
			};

			inline_medium COptionsFloat();

			uint32 m_bSign:1 = false;
			uint32 m_FloatFormat:3 = EFloatFormat_Fixed;
			uint32 m_bShowInf:1 = 1;
			uint32 m_bShowNaN:1 = 1;
			uint32 m_bShowDenormalized:1 = 0;
			uint32 m_bFractionOnly:1 = 0;
			uint32 m_bAutoRemoveDigits:1 = 1;
			aint m_MinDigits = -1;
			aint m_MaxDigits = -1;
			aint m_MinDecimals = -1;
			aint m_MaxDecimals = -1;
			CChar m_ThousandSeparator = 0;
		};

		class CXprImplementation
		{
		public:
			inline_small static CFloat fs_DefaultValue();
			inline_small static CFloat fs_Modulus(CFloat const &_Value, CFloat const &_Modulus);
			inline_small static CFloat fs_BitwiseOr(CFloat const &_Left, CFloat const &_Right);
			inline_small static CFloat fs_BitwiseAnd(CFloat const &_Left, CFloat const &_Right);
			inline_small static CFloat fs_BitwiseXor(CFloat const &_Left, CFloat const &_Right);
			inline_small static CFloat fs_BitwiseNot(CFloat const &_Right);

			template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
			inline_small static tf_CReturn fs_StrToData(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);

			template <typename tf_CArgument>
			inline_small static auto fs_GetArgumentValue(tf_CArgument *_pArg) -> decltype(_pArg->f_Get_fp64());
		};

		virtual void f_AddToStr(CString &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;
		virtual void f_Visit(CVisitor &_Extractor) const override;
		virtual void const *f_GetTypeID() const override;
		virtual bool f_IsSame(void const *_pRight) const override;

		static void fs_AddToStrStatic(CString &_String, aint &_CurrentStrLen, CFloat const &_Value);
		static void fs_AddToStrStatic(CString &_String, aint &_CurrentStrLen, CFloat const &_Value, COptionsFloat &_Options);

		template <typename t_CData, typename t_CFormatType, typename t_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, COption &_Option) const;

		constexpr static bool mc_bNeedDestruct = !t_bReference;

	private:
		template <typename t_COptions>
		static inline_small void fp_AddToStr(CString &_String, aint &_CurrentStrLen, t_COptions &_Options, CFloat const &_Number);

		inline static bool constexpr mcp_TypeID = false;

		CStorage mp_Value;
	};

	template
	<
		typename t_CFormatter
		, aint t_SignBits
		, aint t_ExponentBits
		, aint t_MantissaBits
		, aint t_PaddingBits
		, typename t_CImplicitFloat
		, bool t_bDummyOptimize
		, typename t_CIntegerStorage
	>
	struct TCStringFormatter<t_CFormatter, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
	{
		using CFloat = NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>;
		using CFormatType = TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, true>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CFloat const&_Data);
	};

	template
	<
		typename t_CFormatter
		, aint t_SignBits
		, aint t_ExponentBits
		, aint t_MantissaBits
		, aint t_PaddingBits
		, typename t_CImplicitFloat
		, bool t_bDummyOptimize
		, typename t_CIntegerStorage
	>
	struct TCStringFormatter
	<
		t_CFormatter
		, TCByValue<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
	>
	{
		using CFloat = NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>;
		using CFormatType = TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, false>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<CFloat> const &_Data);
	};

#ifdef DMibPCanDo_fp32
	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, pfp32>
	{
	public:
		using CFormatType = typename TCStringFormatter<t_CFormatter, fp32>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, pfp32 const &_Data) -> decltype(TCStringFormatter<t_CFormatter, fp32>::template fs_CreateFormat<fp32>(_Formatter, _Data));
	};

	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, TCByValue<pfp32>>
	{
	public:
		using CFormatType = typename TCStringFormatter<t_CFormatter, TCByValue<fp32>>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<pfp32> const &_Data);
	};
#endif
#ifdef DMibPCanDo_fp64
	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, pfp64>
	{
	public:
		using CFormatType = typename TCStringFormatter<t_CFormatter, fp64>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, pfp64 const &_Data) -> decltype(TCStringFormatter<t_CFormatter, fp64>::template fs_CreateFormat<fp64>(_Formatter, _Data));
	};

	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, TCByValue<pfp64>>
	{
	public:
		using CFormatType = typename TCStringFormatter<t_CFormatter, TCByValue<fp64>>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<pfp64> const &_Data);
	};
#endif
#ifdef DMibPCanDo_fp80
	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, pfp80>
	{
	public:
		using CFormatType = typename TCStringFormatter<t_CFormatter, fp80>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, pfp80 const &_Data) -> decltype(TCStringFormatter<t_CFormatter, fp80>::template fs_CreateFormat<fp80>(_Formatter, _Data));
	};

	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, TCByValue<pfp80>>
	{
	public:
		using CFormatType = typename TCStringFormatter<t_CFormatter, TCByValue<fp80>>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<pfp80> const &_Data);
	};
#endif
#ifdef DMibPCanDo_fp128
	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, pfp128>
	{
	public:
		using CFormatType = typename TCStringFormatter<t_CFormatter, fp128>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, pfp128 const &_Data) -> decltype(TCStringFormatter<t_CFormatter, fp128>::template fs_CreateFormat<fp128>(_Formatter, _Data));
	};

	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, TCByValue<pfp128>>
	{
	public:
		using CFormatType = typename TCStringFormatter<t_CFormatter, TCByValue<fp128>>::CFormatType;

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, pfp128 const &_Data);
	};
#endif
}

#include "Container/Malterlib_String_Container_Format_Float.hpp"
