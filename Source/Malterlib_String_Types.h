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

	template <typename t_CTCStrTraits>
	struct TCStr;

	struct CStrImp_Dynamic_ParamsDeflauts
	{
		using CAllocator = NMemory::CAllocator_Heap;

		static constexpr umint mc_MaxExtraChars = 32;
	};

	struct CStrImp_Dynamic_ParamsNonTracked
	{
		using CAllocator = NMemory::CAllocator_NonTrackedHeap;

		static constexpr umint mc_MaxExtraChars = 32;
	};

	struct CStrImp_Dynamic_ParamsVirtual : public CStrImp_Dynamic_ParamsDeflauts
	{
		using CAllocator = NMemory::CAllocator_Virtual;
	};

	struct CStrImp_Dynamic_ParamsSecure
	{
		using CAllocator = NMemory::CAllocator_HeapSecure;

		static constexpr umint mc_MaxExtraChars = 32;
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

	enum EStrTypeClassFloat
	{
	};

	enum EStrTypeClassString
	{
	};

	enum EStrTypeClassInteger
	{
	};

	enum EStrTypeClassBinary
	{
	};

	enum EStrTypeClassUntyped
	{
	};

	enum EStrTypeClassOther
	{
	};

	struct CDefaultStrFormatTypeClassifier
	{
		template <typename tf_CType>
		static NTraits::CFalseBySize fs_ClassifiedAs(tf_CType _Any);
		static NTraits::CTrueBySize fs_ClassifiedAs(EStrTypeClassOther _Value);
	};

	struct CStrFormatTypeClassifier_String
	{
		template <typename tf_CType>
		static NTraits::CFalseBySize fs_ClassifiedAs(tf_CType _Any);
		static NTraits::CTrueBySize fs_ClassifiedAs(EStrTypeClassString _Value);
	};

	struct CStrFormatTypeClassifier_Integer
	{
		template <typename tf_CType>
		static NTraits::CFalseBySize fs_ClassifiedAs(tf_CType _Any);
		static NTraits::CTrueBySize fs_ClassifiedAs(EStrTypeClassInteger _Value);
	};

	struct CStrFormatTypeClassifier_Untyped
	{
		template <typename tf_CType>
		static NTraits::CFalseBySize fs_ClassifiedAs(tf_CType _Any);
		static NTraits::CTrueBySize fs_ClassifiedAs(EStrTypeClassUntyped _Value);
	};

	struct CStrFormatTypeClassifier_Binary
	{
		template <typename tf_CType>
		static NTraits::CFalseBySize fs_ClassifiedAs(tf_CType _Any);
		static NTraits::CTrueBySize fs_ClassifiedAs(EStrTypeClassBinary _Value);
	};

	struct CStrFormatTypeClassifier_Float
	{
		template <typename tf_CType>
		static NTraits::CFalseBySize fs_ClassifiedAs(tf_CType _Any);
		static NTraits::CTrueBySize fs_ClassifiedAs(EStrTypeClassFloat _Value);
	};
}
