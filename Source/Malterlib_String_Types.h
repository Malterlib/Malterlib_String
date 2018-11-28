// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NStr
	{
		template <typename t_CStrTraits, aint t_DataLen>
		class TCStrImp_Fixed;

		template <typename t_CStrTraits>
		class TCStrImp_Ptr;

		
		template <typename t_TCStrTraits>
		class TCStr;

		class CStrImp_Dynamic_ParamsDeflauts
		{
		public:
			typedef NMem::CAllocator_Heap CAllocator;
			enum
			{
				EMaxExtraChars = 32
			};
		};

		class CStrImp_Dynamic_ParamsNonTracked
		{
		public:
			typedef NMem::CAllocator_NonTrackedHeap CAllocator;
			enum
			{
				EMaxExtraChars = 32
			};
		};

		class CStrImp_Dynamic_ParamsVirtual : public CStrImp_Dynamic_ParamsDeflauts
		{
		public:
			typedef NMem::CAllocator_Virtual CAllocator;
		};

		class CStrImp_Dynamic_ParamsSecure
		{
		public:
			typedef NMem::TCAllocator_Secure<NMem::CAllocator_Heap> CAllocator;
			enum
			{
				EMaxExtraChars = 32
			};
		};

		using CStrTypeUnderlaying = int32;
		enum EStrType : int32;

		template <typename t_CStrTraits> 
		class TCStrImp_Dynamic;

		template <typename t_CChar, CStrTypeUnderlaying t_Type, typename t_CParams>
		class TCStrTraits;

		template <typename t_CStrTraits, typename t_CImplementation>
		class TCTCStrTraits
		{
		public:
			typedef t_CStrTraits CStrTraits;
			typedef t_CImplementation CImp;

		};

		template <typename t_CStrTraits, typename t_CImpParams>	
		class TICStrImp_Virtual;

		template <typename t_CTStrTraits, typename t_CPointerHolder> 
		class TCStrImp_Virtual_PtrWrapper;

		template <typename t_CTStrTraits> 
		class TCStrImp_Virtual_TStrWrapper;

		template <typename t_CFormatter>
		class TICStrFormatType;

		template <typename t_CIntType>
		class TCStrFormatType_Int_OptionsStatic;

		template <typename t_CFormatter, typename t_CIntType, typename t_COptions = TCStrFormatType_Int_OptionsStatic<t_CIntType> >
		class TCStrFormatType_Int;

		template <typename t_CFormatter, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		class TCStrFormatType_Float;

		template <typename t_CFormatter, typename t_CStrDataType, CStrTypeUnderlaying t_Type>
		class TCStrFormatType_String;

		template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
		class TCStrFormatType_TStr;


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
}

