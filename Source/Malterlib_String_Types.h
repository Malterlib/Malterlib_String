// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CStrTraits, aint t_DataLen>
	class TCStrImp_Fixed;

	template <typename t_CStrTraits>
	class TCStrImp_Ptr;


	template <typename t_TCStrTraits>
	struct TCStr;

	class CStrImp_Dynamic_ParamsDeflauts
	{
	public:
		using CAllocator = NMemory::CAllocator_Heap;
		enum
		{
			EMaxExtraChars = 32
		};
	};

	class CStrImp_Dynamic_ParamsNonTracked
	{
	public:
		using CAllocator = NMemory::CAllocator_NonTrackedHeap;
		enum
		{
			EMaxExtraChars = 32
		};
	};

	class CStrImp_Dynamic_ParamsVirtual : public CStrImp_Dynamic_ParamsDeflauts
	{
	public:
		using CAllocator = NMemory::CAllocator_Virtual;
	};

	class CStrImp_Dynamic_ParamsSecure
	{
	public:
		using CAllocator = NMemory::CAllocator_HeapSecure;
		enum
		{
			EMaxExtraChars = 32
		};
	};

	using CStrTypeUnderlying = int32;
	enum EStrType : int32;

	template <typename t_CStrTraits>
	class TCStrImp_Dynamic;

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	class TCStrTraits;

	template <typename t_CStrTraits, typename t_CImplementation>
	class TCTCStrTraits
	{
	public:
		using CStrTraits = t_CStrTraits;
		using CImp = t_CImplementation;
	};

	template <typename t_CStrTraits, typename t_CImpParams>
	class TICStrImp_Virtual;

	template <typename t_CTStrTraits>
	class TCStrImp_Virtual_PtrWrapper;

	template <typename t_CTStrTraits>
	class TCStrImp_Virtual_TStrWrapper;

	template <typename t_CFormatter>
	struct TICStrFormatType;

	template <typename t_CIntType>
	struct TCStrFormatType_Int_OptionsStatic;

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions = TCStrFormatType_Int_OptionsStatic<t_CIntType> >
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
	class TCStrFormatType_Float;

	template <typename t_CFormatter, typename t_CStrDataType, CStrTypeUnderlying t_Type>
	class TCStrFormatType_String;

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	struct TCStrFormatType_TStr;


	enum EStrTypeClass_Float
	{
	};
	enum EStrTypeClass_String
	{
	};
	enum EStrTypeClass_Integer
	{
	};
	enum EStrTypeClass_Binary
	{
	};
	enum EStrTypeClass_Untyped
	{
	};
	enum EStrTypeClass_Other
	{
	};

	class CDefaultStrFormatTypeClassifier
	{
	public:

		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Other _Value);
	};

	class CStrFormatTypeClassifier_String
	{
	public:

		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_String _Value);
	};
	class CStrFormatTypeClassifier_Integer
	{
	public:

		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Integer _Value);
	};
	class CStrFormatTypeClassifier_Untyped
	{
	public:

		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Untyped _Value);
	};
	class CStrFormatTypeClassifier_Binary
	{
	public:

		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Binary _Value);
	};
	class CStrFormatTypeClassifier_Float
	{
	public:

		template <typename t_CType>
		static NTraits::CFalseBySize f_ClassifiedAs(t_CType _Any);
		static NTraits::CTrueBySize f_ClassifiedAs(EStrTypeClass_Float _Value);
	};
}
