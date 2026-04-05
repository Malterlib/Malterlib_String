// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CStrTraits, aint t_DataLen>
	struct TCStrImp_Fixed;

	template <typename t_CStrTraits>
	struct TCStrImp_Ptr;

	template <typename t_TCStrTraits>
	struct TCStr;

	struct CStrImp_Dynamic_ParamsDeflauts
	{
		using CAllocator = NMemory::CAllocator_Heap;

		constexpr static umint mc_MaxExtraChars = 32;
	};

	struct CStrImp_Dynamic_ParamsNonTracked
	{
		using CAllocator = NMemory::CAllocator_NonTrackedHeap;

		constexpr static umint mc_MaxExtraChars = 32;
	};

	struct CStrImp_Dynamic_ParamsVirtual : public CStrImp_Dynamic_ParamsDeflauts
	{
		using CAllocator = NMemory::CAllocator_Virtual;
	};

	struct CStrImp_Dynamic_ParamsSecure
	{
		using CAllocator = NMemory::CAllocator_HeapSecure;

		constexpr static umint mc_MaxExtraChars = 32;
	};

	using CStrTypeUnderlying = int32;
	enum EStrType : int32;

	template <typename t_CStrTraits>
	struct TCStrImp_Dynamic;

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	struct TCStrTraits;

	template <typename t_CStrTraits, typename t_CImplementation>
	struct TCTCStrTraits
	{
	public:
		using CStrTraits = t_CStrTraits;
		using CImp = t_CImplementation;
	};

	template <typename t_CStrTraits, typename t_CImpParams>
	struct TICStrImp_Virtual;

	template <typename t_CTStrTraits>
	struct TCStrImp_Virtual_PtrWrapper;

	template <typename t_CTStrTraits>
	struct TCStrImp_Virtual_TStrWrapper;

	template <typename t_CFormatter>
	struct TICStrFormatType;

	template <typename t_CIntType>
	struct TCStrFormatType_Int_OptionsStatic;

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions = TCStrFormatType_Int_OptionsStatic<t_CIntType>>
	struct TCStrFormatType_Int;

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
	struct TCStrFormatType_Float;

	template <typename t_CFormatter, typename t_CStrDataType, CStrTypeUnderlying t_Type>
	struct TCStrFormatType_String;

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	struct TCStrFormatType_TStr;

	enum EStrTypeClass_Float {};
	enum EStrTypeClass_String {};
	enum EStrTypeClass_Integer {};
	enum EStrTypeClass_Binary {};
	enum EStrTypeClass_Untyped {};
	enum EStrTypeClass_Other {};

	struct CDefaultStrFormatTypeClassifier
	{
		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Other _Value);
	};

	struct CStrFormatTypeClassifier_String
	{
		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_String _Value);
	};

	struct CStrFormatTypeClassifier_Integer
	{
		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Integer _Value);
	};

	struct CStrFormatTypeClassifier_Untyped
	{
		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Untyped _Value);
	};

	struct CStrFormatTypeClassifier_Binary
	{
		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Binary _Value);
	};

	struct CStrFormatTypeClassifier_Float
	{
		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Float _Value);
	};
}
