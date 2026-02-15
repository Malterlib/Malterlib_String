// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	struct CStrFormatType_StaticOptions
	{
		constexpr inline_small static bool f_RestrictLength();
		constexpr inline_small static mint f_MinLength();
		constexpr inline_small static mint f_MaxLength();
		constexpr inline_small static aint f_Align();
		constexpr inline_small static bool f_LeftAlign();
		constexpr inline_small static bool f_SimpleAlign();
		constexpr inline_small static ch8 f_Fillout();
	};

	template <mint t_MinLength, typename t_CParent>
	struct TICStrFormatType_StaticOptions_MinLength : public t_CParent
	{
		inline_small TICStrFormatType_StaticOptions_MinLength(t_CParent const &_Parent);

		constexpr inline_small static mint f_MinLength();
		constexpr inline_small static bool f_RestrictLength();
	};

	template <mint t_MaxLength, typename t_CParent>
	struct TICStrFormatType_StaticOptions_MaxLength : public t_CParent
	{
		inline_small TICStrFormatType_StaticOptions_MaxLength(t_CParent const &_Parent);

		constexpr inline_small static mint f_MaxLength();
		constexpr inline_small static bool f_RestrictLength();
	};

	template <ch32 t_FillOut, typename t_CParent>
	struct TICStrFormatType_StaticOptions_FillOut : public t_CParent
	{
		inline_small TICStrFormatType_StaticOptions_FillOut (t_CParent const &_Parent);

		constexpr inline_small static ch32 f_Fillout();
	};

	template <typename t_COptions, typename t_CIntType>
	struct TCValueWithOptions : public t_COptions
	{
		using COptions = t_COptions;

		inline_small TCValueWithOptions(t_CIntType const &_Int, t_COptions const &_Options);

		inline_small t_CIntType const & f_GetValue() const;
		inline_small COptions const &f_GetOptions() const;
		inline_small COptions &f_GetOptions();
		inline_small operator t_CIntType const & () const;

		t_CIntType const &m_Int;
	};

	template <typename t_CChar>
	struct TICStrFormatType_Options
	{
		template <typename tf_CInitializer>
		inline_medium TICStrFormatType_Options(tf_CInitializer const &_Init);

		constexpr inline_small bool f_RestrictLength() const;
		constexpr inline_small mint f_MinLength() const;
		constexpr inline_small mint f_MaxLength() const;
		constexpr inline_small aint f_Align() const;
		constexpr inline_small bool f_LeftAlign() const;
		constexpr inline_small bool f_SimpleAlign() const;
		constexpr inline_small t_CChar f_Fillout() const;

		mint m_MaxLength;
		aint m_Align;
		uint32 m_MinLength:30;
		uint32 m_bLeftAlign:1;
		uint32 m_bSimpleAlign:1;
		t_CChar m_Fillout;
	};

	template <typename t_CData, typename t_CFormatType, typename t_COptions>
	struct TICStrFormatType_ParseOptionsArgs
	{
		using CString = typename t_CFormatType::CString;
		using CFormatter = typename t_CFormatType::CFormatter;

		TICStrFormatType_ParseOptionsArgs(t_CData &_Data, t_CFormatType const &_FormatType, CString &_String, aint &_CurrentStrLen, t_COptions &_Options, CFormatter const &_Formatter);

		t_CData &m_Data;
		t_CFormatType const &m_FormatType;
		CString &m_String;
		aint &m_CurrentStrLen;
		t_COptions &m_Options;
		CFormatter const &m_Formatter;
	};

	template <typename t_CFormatter>
	struct TICStrFormatType
	{
		using CStrFormatTypeClassifier = CDefaultStrFormatTypeClassifier;
		using CFormatter = t_CFormatter;
		using CChar = typename t_CFormatter::CString::CStrTraits::CChar;
		using CString = typename t_CFormatter::CString;
		using CStr = typename t_CFormatter::CString;
		using CStrTraits = typename t_CFormatter::CString::CStrTraits;
		using COptions = TICStrFormatType_Options<CChar>;
		using COptionsStatic = CStrFormatType_StaticOptions;

		struct CVisitor
		{
			virtual void operator () (uint32 _Value) = 0;
			virtual void operator () (uint64 _Value) = 0;
			virtual void operator () (int32 _Value) = 0;
			virtual void operator () (int64 _Value) = 0;
			virtual void operator () (fp32 _Value) = 0;
			virtual void operator () (fp64 _Value) = 0;
			virtual void operator () (CChar const *_pValue) = 0;
			virtual void operator () () {}
		};

		struct CVisitorInteger : public CVisitor
		{
			virtual void operator () (fp32 _Value) {}
			virtual void operator () (fp64 _Value) {}
			virtual void operator () (CChar const *_pValue) {}
		};

		struct CVisitorFloat : public CVisitor
		{
			virtual void operator () (uint32 _Value) {}
			virtual void operator () (uint64 _Value) {}
			virtual void operator () (int32 _Value) {}
			virtual void operator () (int64 _Value) {}
			virtual void operator () (CChar const *_pValue) {}
		};

		struct CVisitorNumber : public CVisitor
		{
			virtual void operator () (CChar const *_pValue) {}
		};

		struct CVisitorString : public CVisitor
		{
			virtual void operator () (uint32 _Value) {}
			virtual void operator () (uint64 _Value) {}
			virtual void operator () (int32 _Value) {}
			virtual void operator () (int64 _Value) {}
			virtual void operator () (fp32 _Value) {}
			virtual void operator () (fp64 _Value) {}
		};

		struct COption
		{
 			struct CFormatTypes
			{
				ch32 m_Format1;
				ch32 m_Format2;
			};

			void f_GetData_Str(CChar *_pDestStr, aint _MaxChars) const;
			aint f_GetData_aint(t_CFormatter const &_ArgData, aint _FailValue) const;
			aint f_GetData_aint_NotSigned(t_CFormatter const &_ArgData, aint _FailValue) const;
			fp32 f_GetData_fp32(t_CFormatter const &_ArgData, fp32 _FailValue) const;
			fp64 f_GetData_fp64(t_CFormatter const &_ArgData, fp64 _FailValue) const;
			void f_DisplayUnknownFormat(CString &_String, aint &_CurrentStrLen) const;

			CChar const *m_pDataStart;
			CFormatTypes m_FormatTypes;
		};

		enum EFormatXprOperator
		{
			EFormatXprOperator_None = 0

			//, EFormatXprOperator_UnaryAdd
			//, EFormatXprOperator_UnarySub
			//, EFormatXprOperator_BitwiseNot
			//, EFormatXprOperator_LogicalNot

			, EFormatXprOperator_Multiply
			, EFormatXprOperator_Divide
			, EFormatXprOperator_Modulus

			, EFormatXprOperator_LessThan
			, EFormatXprOperator_GreaterThan
			, EFormatXprOperator_Equal
			, EFormatXprOperator_LessThanEqual
			, EFormatXprOperator_GreaterThanEqual

			, EFormatXprOperator_LogicalOr
			, EFormatXprOperator_LogicalAnd

			, EFormatXprOperator_BitwiseOr
			, EFormatXprOperator_BitwiseAnd
			, EFormatXprOperator_BitwiseXor

			, EFormatXprOperator_Add
			, EFormatXprOperator_Sub
		};

		template <typename t_CData, typename t_CImplementation>
		struct TCValueData
		{
			TCValueData();

			void operator () (t_CData _Value);

			t_CData m_ValuePrec0;
			t_CData m_ValuePrec1;
			EFormatXprOperator m_CurrentOperatorPrec0;
			EFormatXprOperator m_CurrentOperatorPrec1;
			aint m_Precedence;
		};

		virtual mint f_Destruct() = 0;
		virtual void f_Move(t_CFormatter &_Formatter) = 0;
		virtual void f_AddToStr(CString &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const = 0;
		virtual aint f_Get_aint() const = 0;
		virtual fp32 f_Get_fp32() const = 0;
		virtual fp64 f_Get_fp64() const = 0;
		virtual void const *f_GetTypeID() const = 0;
		virtual bool f_IsSame(void const *_pRight) const = 0;

		virtual void f_Visit(CVisitor &_Extractor) const = 0;

		TICStrFormatType const *f_GetPtr() const;

		template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
		inline_small static void fs_ParseOptions(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, CChar const *_pFormat);

		template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const;

		template <typename tf_COptions>
		static void fs_AddSubStrToStr(CString &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CChar const *_pSubStr, mint _SubStrLen, aint _SubStrStart);

		template <typename tf_COptions>
		static inline_small void fs_AddSubStrToStrSimple(CString &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CChar const *_pSubStr, mint _SubStrLen);

	protected:
		inline_small void fp_GetNextFormat(COption &_NewFormat, CChar const * &_pFormat) const;

		template <typename tf_CChar>
		void fp_ReportParseError(CString &_String, aint &_CurrentStrLen, tf_CChar const *_pStr, mint _MaxLen = TCLimitsInt<mint>::mc_Max) const;

		template <typename tf_CImplementation, typename tf_CData, typename tf_CFormatType, typename tf_COptions>
		inline_never void fp_EvalExpression(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, CChar const *_pParse) const;

		template <typename tf_CImplementation, typename tf_CData, typename tf_CFormatType, typename tf_COptions>
		inline_never tf_CData fpr_EvalExpression
			(
				TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args
				, CChar const * &_pParse
				, bool &_bError
				, bool _bExitAtValue
			) const
		;
	};


	template <mint tf_MinLength, typename tf_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_MinLength<tf_MinLength, CStrFormatType_StaticOptions>, tf_CValueType> fg_FormatMinLength(tf_CValueType const &_Value);

	template <mint tf_MinLength, typename tf_CValueType, typename tf_COldOptions>
	inline_small auto fg_FormatMinLength(TCValueWithOptions<tf_COldOptions, tf_CValueType> const &_Value)
		-> TCValueWithOptions<TICStrFormatType_StaticOptions_MinLength<tf_MinLength, tf_COldOptions>, tf_CValueType>
	;


	template <mint tf_MaxLength, typename tf_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_MaxLength<tf_MaxLength, CStrFormatType_StaticOptions>, tf_CValueType> fg_FormatMaxLength(tf_CValueType const &_Value);

	template <mint tf_MaxLength, typename tf_CValueType, typename tf_COldOptions>
	inline_small auto fg_FormatMaxLength(TCValueWithOptions<tf_COldOptions, tf_CValueType> const &_Value)
		-> TCValueWithOptions<TICStrFormatType_StaticOptions_MaxLength<tf_MaxLength, tf_COldOptions>, tf_CValueType>
	;

	template <ch32 tf_FillOut, typename tf_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_FillOut<tf_FillOut, CStrFormatType_StaticOptions>, tf_CValueType> fg_FormatFillOut(tf_CValueType const &_Value);

	template <ch32 tf_FillOut, typename tf_CValueType, typename tf_COldOptions>
	inline_small auto fg_FormatFillOut(TCValueWithOptions<tf_COldOptions, tf_CValueType> const &_Value)
		-> TCValueWithOptions<TICStrFormatType_StaticOptions_FillOut<tf_FillOut, tf_COldOptions>, tf_CValueType>
	;
}

#include "Malterlib_String_Container_Format_Shared.hpp"
#include "Malterlib_String_Container_Format_Shared_Expression.hpp"
