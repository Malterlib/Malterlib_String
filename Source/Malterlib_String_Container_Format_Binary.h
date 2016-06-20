// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NStr
	{
		template <typename t_CFormatter, typename t_CBinaryType>
		class TCStrFormatType_Binary final : public TICStrFormatType<t_CFormatter>
		{
		public:

			typedef typename TCChooseType<NTraits::TCIsSame<CStrFormatBinaryWrapperUntyped, t_CBinaryType>::mc_Value, CStrFormatTypeClassifier_Untyped, CStrFormatTypeClassifier_Binary>::CType CStrFormatTypeClassifier;

			virtual void f_Delete()
			{
				this->~TCStrFormatType_Binary();
			}

			typedef typename t_CFormatter::CTStrTraits CTStrTraits;
			typedef typename CTStrTraits::CStrTraits::CChar CChar;
			typedef TICStrFormatType<t_CFormatter> CSuper;

			typedef t_CBinaryType CType;
			typedef typename CSuper::CVisitor CVisitor;

			t_CBinaryType m_Value;
			enum
			{
				mc_bNeedDelete = true
			};

			inline_small TCStrFormatType_Binary(t_CBinaryType const &_Value)
				: m_Value(_Value)
			{
			}
			
			typedef typename TICStrFormatType<t_CFormatter> :: COption COption;
			typedef typename TICStrFormatType<t_CFormatter> :: COptions COptions;
			typedef typename TICStrFormatType<t_CFormatter> :: COptionsStatic COptionsStatic;

			template <typename t_COptions2>
			inline_small static void fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const t_COptions2 &_Options, const CType &_Value) 
			{
				uint8 OutValue;
				auto Temp = fg_FormatMaxLength<2>(fg_FormatMinLength<2>(fg_FormatFillOut<'0'>(fg_FormatIntFormat<16>(OutValue))));
				typedef typename TCStringFormatter<t_CFormatter, decltype(Temp)>::CFormatType CFormatType;

				const uint8 *pValue = (const uint8 *)_Value.f_GetArray();
				mint nBytes = _Value.f_GetSize();

				for (mint i = 0; i < nBytes; ++i)
				{
					OutValue = pValue[i];
					CFormatType::fs_AddToStrStatic(_String, _CurrentStrLen, Temp);
				}

			}

			virtual void f_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const
			{
				COptionsStatic Static;
				COptions Options(Static);

				if (_pFormat)
				{
					TICStrFormatType_ParseOptionsArgs<const CType, TCStrFormatType_Binary, COptions> Args(m_Value, *this, _String, _CurrentStrLen, Options, _ArgData);
					CSuper::fs_ParseOptions(Args, _pFormat);
				}

				fp_AddToStr(_String, _CurrentStrLen, Options, m_Value);
			}

			inline_small static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const CType &_Value)
			{
				COptionsStatic Options;
				fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
			}

			virtual aint f_Get_aint() const
			{
				return 0;
			}

			virtual fp32 f_Get_fp32() const
			{
				return 0.0f;
			}

			virtual fp64 f_Get_fp64() const
			{
				return 0.0;
			}

			virtual void f_Visit(CVisitor &_Extractor) const
			{
				_Extractor();
			}

		};			  

		template <typename t_CFormatter>
		class TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapper >
		{
		public:
			typedef TCStrFormatType_Binary<t_CFormatter, CStrFormatBinaryWrapper> CFormatType;
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CStrFormatBinaryWrapper const &_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

		template <typename t_CFormatter>
		class TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped >
		{
		public:
			typedef TCStrFormatType_Binary<t_CFormatter, CStrFormatBinaryWrapperUntyped> CFormatType;
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CStrFormatBinaryWrapperUntyped const &_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

		

	}
}

