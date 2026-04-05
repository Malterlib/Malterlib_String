// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CIntType>
	struct TCStrFormatType_Int_Options : public TICStrFormatType<t_CFormatter>::COptions
	{
	public:
		using CIntType = t_CIntType;

		enum
		{
			ERadix = 10,
			ENumTempChar = sizeof(t_CIntType) * 8 + 2 + ((sizeof(t_CIntType) * 8 + 2) / 3)
		};

		uint32 m_Radix:29;
		uint32 m_bNumberCaps:1;
		uint32 m_bSign:1;
		uint32 m_bBoolean:1;

		typename TICStrFormatType<t_CFormatter>::CChar m_ThousandSeparator;

		template <typename tf_CInitializer>
		inline_medium TCStrFormatType_Int_Options(tf_CInitializer const &_Init);

		inline_always static bool f_StaticRadix();
		inline_always bool f_NumberCaps() const;
		inline_always bool f_Boolean() const;
		inline_always bool f_Sign() const;
		inline_always typename TICStrFormatType<t_CFormatter>::CChar f_ThousandSeparator() const;

		template <typename tf_CRadix>
		inline_always tf_CRadix f_Radix() const;
	};

	template <typename t_CIntType>
	struct TCStrFormatType_Int_OptionsStatic : public CStrFormatType_StaticOptions
	{
		using CIntType = t_CIntType;

		enum
		{
			ERadix = 10,
			ENumTempChar = (sizeof(CIntType) * 8)/3 + 2
		};

		inline_always static bool f_StaticRadix();
		inline_always static bool f_NumberCaps();
		inline_always static bool f_Boolean();
		inline_always static bool f_Sign();
		inline_always static ch8 f_ThousandSeparator();

		template <typename tf_CRadix>
		inline_always static tf_CRadix f_Radix();
	};

	template <int32 t_Radix, typename t_CParent>
	struct TCStrFormatType_Int_OptionsStatic_Radix : public t_CParent
	{
		using CIntType = typename t_CParent::CIntType;

	private:
		static_assert(t_Radix >= 2 && t_Radix <= 36);
		enum
		{
			ENumBits = sizeof(CIntType) * 8,
			ENumBitsPerChar = gc_HighestBitSet<t_Radix>
		};

	public:
		enum
		{
			ERadix = t_Radix,
			ENumTempChar = (ENumBits+(ENumBitsPerChar-1))/ENumBitsPerChar + 2
		};

		inline_always TCStrFormatType_Int_OptionsStatic_Radix(t_CParent const &_Parent);

		inline_always static bool f_StaticRadix();

		template <typename tf_CRadix>
		inline_always static tf_CRadix f_Radix();
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	struct TCStrFormatType_Int final : public TICStrFormatType<t_CFormatter>
	{
		using CStrFormatTypeClassifier = CStrFormatTypeClassifier_Integer;
		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CChar = typename CTStrTraits::CStrTraits::CChar;
		using CSuper = TICStrFormatType<t_CFormatter>;
		using CType = NTraits::TCRemoveConst<NTraits::TCRemoveReference<t_CIntType>>;
		using CUnsignedType = NTraits::TCUnsigned<CType>;
		using CRadixType = TCConditional<NTraits::cIsFundamental<CUnsignedType>, CUnsignedType, uint32>;
		using CVisitor = typename CSuper::CVisitor;

		constexpr static bool mc_bNeedDestruct = !NTraits::cIsReference<t_CIntType>;

		struct CStorage : public t_COptions
		{
			inline_small CStorage(t_CIntType _Value, t_COptions const &_Options);

			inline_small operator CType const & () const;

			t_CIntType m_Value;
		};

		using COption = typename TICStrFormatType<t_CFormatter>::COption;
		using COptions = typename TICStrFormatType<t_CFormatter>::COptions;
		using COptionsInt = TCStrFormatType_Int_Options<t_CFormatter, typename t_COptions::CIntType>;

		struct CXprImplementation
		{
			inline_small static CType fs_DefaultValue();
			inline_small static CType fs_Modulus(CType const &_Value, CType &_Modulus);
			inline_small static CType fs_BitwiseOr(CType const &_Left, CType const &_Right);
			inline_small static CType fs_BitwiseAnd(CType const &_Left, CType const &_Right);
			inline_small static CType fs_BitwiseXor(CType const &_Left, CType const &_Right);
			inline_small static CType fs_BitwiseNot(CType const &_Right);

			template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
			inline_small static tf_CReturn fs_StrToData(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);

			template <typename tf_CArgument>
			inline_small static auto fs_GetArgumentValue(tf_CArgument *_pArg) -> decltype(_pArg->f_Get_aint());
		};

		inline_small TCStrFormatType_Int(t_CIntType _Value, t_COptions const &_Options = t_COptions());
		inline_small t_CIntType const &f_GetValue() const;
		inline_small t_COptions const &f_GetOptions() const;

		virtual umint f_Destruct() override;
		virtual void f_Move(t_CFormatter &_Formatter) override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;
		virtual void f_Visit(CVisitor &_Extractor) const override;
		virtual void const *f_GetTypeID() const override;
		virtual bool f_IsSame(void const *_pRight) const override;

		inline_small static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CType const &_Value);
		inline_small static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CType const &_Value, t_COptions &_Options);

		template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const;

		template <uint32 tf_nBits, typename tf_COptions>
		inline_small static void fs_DoNumber_BitExact(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <uint32 tf_nBits, typename tf_COptions>
		static void fs_DoNumber_BitExactWithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <typename tf_COptions>
		inline_small static void fs_DoNumber_Above10(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <typename tf_COptions>
		static void fs_DoNumber_Above10WithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <CRadixType tf_Radix, typename tf_COptions>
		inline_small static void fs_DoNumber_Above10Static(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <CRadixType tf_Radix, typename tf_COptions>
		static void fs_DoNumber_Above10StaticWithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <typename tf_COptions>
		static void fs_DoNumber_GeneralWithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <typename tf_COptions>
		inline_small static void fs_DoNumber_General(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <CRadixType tf_Radix, typename tf_COptions>
		static void fs_DoNumber_GeneralStaticWithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		template <CRadixType tf_Radix, typename tf_COptions>
		inline_small static void fs_DoNumber_GeneralStatic(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace);

		virtual void f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const & _ArgData) const override;

		template <typename t_COption2, typename t_CIntType2>
		inline_small static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, TCValueWithOptions<t_COption2, t_CIntType2> const &_Value);

	private:
		template <typename tf_COptions>
		static void fp_AddToStrBoolean(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CType const &_Integer);

		template <typename tf_COptions>
		inline_small static void fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CType const &_Integer);

		inline static bool constexpr mcp_TypeID = false;

		CStorage mp_Storage;
	};

	template <typename t_CFormatter, typename t_CInt0, typename t_CInt1>
	struct TCStringFormatter<t_CFormatter, NNumeric::TCInt<t_CInt0, t_CInt1>>
	{
	public:
		using CFormatType = TCStrFormatType_Int<t_CFormatter, NNumeric::TCInt<t_CInt0, t_CInt1> const &>;
		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, NNumeric::TCInt<t_CInt0, t_CInt1> const &_Data);
	};

	template <typename t_CFormatter, typename t_CInt0, typename t_CInt1>
	struct TCStringFormatter<t_CFormatter, TCByValue<NNumeric::TCInt<t_CInt0, t_CInt1>>>
	{
		using CFormatType = TCStrFormatType_Int<t_CFormatter, NNumeric::TCInt<t_CInt0, t_CInt1>>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<NNumeric::TCInt<t_CInt0, t_CInt1>> const &_Data);
	};

	template <typename t_CFormatter, typename t_COption, typename t_CIntType>
	struct TCStringFormatter<t_CFormatter, TCValueWithOptions<t_COption, t_CIntType>>
	{
	public:
		using CFormatType = TCStrFormatType_Int<t_CFormatter, t_CIntType const &, TCValueWithOptions<t_COption, t_CIntType>>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCValueWithOptions<t_COption, t_CIntType> const &_Data);
	};

	template <typename t_CFormatter, typename t_COption, typename t_CIntType>
	struct TCStringFormatter<t_CFormatter, TCByValue<TCValueWithOptions<t_COption, t_CIntType>>>
	{
	public:
		using CFormatType = TCStrFormatType_Int<t_CFormatter, t_CIntType, TCValueWithOptions<t_COption, t_CIntType>>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<TCValueWithOptions<t_COption, t_CIntType>> const &_Data);
	};

	template <int32 tf_Radix, typename tf_CIntType>
	inline_small auto fg_FormatIntFormat(tf_CIntType const &_Int)
		-> TCValueWithOptions<TCStrFormatType_Int_OptionsStatic_Radix<tf_Radix, TCStrFormatType_Int_OptionsStatic<tf_CIntType>>, tf_CIntType>
	;

	template <int32 tf_Radix, typename tf_CIntType, typename tf_COldOptions>
	inline_small auto fg_FormatIntFormat(TCValueWithOptions<tf_COldOptions, tf_CIntType> const &_Int)
		-> TCValueWithOptions<TCStrFormatType_Int_OptionsStatic_Radix<tf_Radix, tf_COldOptions>, tf_CIntType>
	;

	// Default formatter for pointers
	template <typename t_CFormatter, typename t_CData>
	struct TCStringFormatter<t_CFormatter, t_CData *>
	{
		struct CPtrOptions;

		using CFormatType = TCStrFormatType_Int<t_CFormatter, umint, CPtrOptions>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, t_CData * const &_Data);
	};
	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, bool>
	{
		struct CBoolOptions;

		using CFormatType = TCStrFormatType_Int<t_CFormatter, int8, CBoolOptions>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, bool const &_Data);
	};
}

#include "Malterlib_String_Container_Format_Integer.hpp"

DMibStrStringFormatterImplementInt(uint8);
DMibStrStringFormatterImplementInt(int8);
DMibStrStringFormatterImplementInt(uint16);
DMibStrStringFormatterImplementInt(int16);
DMibStrStringFormatterImplementInt(uint32);
DMibStrStringFormatterImplementInt(int32);
DMibStrStringFormatterImplementInt(uint64);
DMibStrStringFormatterImplementInt(int64);
DMibStrStringFormatterImplementInt(uint80);
DMibStrStringFormatterImplementInt(int80);
DMibStrStringFormatterImplementInt(uint96);
DMibStrStringFormatterImplementInt(int96);
DMibStrStringFormatterImplementInt(uint128);
DMibStrStringFormatterImplementInt(int128);
DMibStrStringFormatterImplementInt(uint160);
DMibStrStringFormatterImplementInt(int160);
DMibStrStringFormatterImplementInt(uint192);
DMibStrStringFormatterImplementInt(int192);
DMibStrStringFormatterImplementInt(uint256);
DMibStrStringFormatterImplementInt(int256);
DMibStrStringFormatterImplementInt(uint320);
DMibStrStringFormatterImplementInt(int320);
DMibStrStringFormatterImplementInt(uint384);
DMibStrStringFormatterImplementInt(int384);
DMibStrStringFormatterImplementInt(uint512);
DMibStrStringFormatterImplementInt(int512);
DMibStrStringFormatterImplementInt(uint1024);
DMibStrStringFormatterImplementInt(int1024);
DMibStrStringFormatterImplementInt(uint2048);
DMibStrStringFormatterImplementInt(int2048);
DMibStrStringFormatterImplementInt(uint4096);
DMibStrStringFormatterImplementInt(int4096);
DMibStrStringFormatterImplementInt(uint8192);
DMibStrStringFormatterImplementInt(int8192);
DMibStrStringFormatterImplementInt(uint16384);
DMibStrStringFormatterImplementInt(int16384);


#ifdef DMibPUniqueType_mint
DMibStrStringFormatterImplementInt(umint);
#endif
#ifdef DMibPUniqueType_smint
DMibStrStringFormatterImplementInt(smint);
#endif
#ifdef DMibPUniqueType_int
DMibStrStringFormatterImplementInt(int);
#endif
#ifdef DMibPUniqueType_uint
DMibStrStringFormatterImplementInt(unsigned int);
#endif
#ifdef DMibPUniqueType_aint
DMibStrStringFormatterImplementInt(aint);
#endif

#ifdef DMibPUniqueType_uaint
DMibStrStringFormatterImplementInt(uaint);
#endif


#ifdef DMibPUniqueType_ch8
DMibStrStringFormatterImplementInt(ch8);
#endif
#ifdef DMibPUniqueType_ch16
DMibStrStringFormatterImplementInt(ch16);
#endif
#ifdef DMibPUniqueType_ch32
DMibStrStringFormatterImplementInt(ch32);
#endif
