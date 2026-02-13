// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CBinaryType>
	class TCStrFormatType_Binary final : public TICStrFormatType<t_CFormatter>
	{
	public:
		using CStrFormatTypeClassifier = TCConditional<NTraits::cIsSame<CStrFormatBinaryWrapperUntyped, t_CBinaryType>, CStrFormatTypeClassifier_Untyped, CStrFormatTypeClassifier_Binary>;

		virtual mint f_Delete() override
		{
			if constexpr (mc_bNeedDelete)
				this->~TCStrFormatType_Binary();
			return sizeof(*this);
		}

		virtual void f_Move(t_CFormatter &_Formatter) override
		{
			DMibFastCheck(false); // Not supported
		}

		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CChar = typename CTStrTraits::CStrTraits::CChar;
		using CSuper = TICStrFormatType<t_CFormatter>;
		using CType = t_CBinaryType;
		using CVisitor = typename CSuper::CVisitor;

		t_CBinaryType m_Value;
		enum
		{
			mc_bNeedDelete = true
		};

		inline_small TCStrFormatType_Binary(t_CBinaryType const &_Value)
			: m_Value(_Value)
		{
		}

		using COption = typename TICStrFormatType<t_CFormatter>::COption;
		using COptions = typename TICStrFormatType<t_CFormatter>::COptions;
		using COptionsStatic = typename TICStrFormatType<t_CFormatter>::COptionsStatic;

		template <typename t_COptions2>
		inline_small static void fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, const t_COptions2 &_Options, const CType &_Value)
		{
			uint8 OutValue = 0;
			auto Temp = fg_FormatMaxLength<2>(fg_FormatMinLength<2>(fg_FormatFillOut<'0'>(fg_FormatIntFormat<16>(OutValue))));

			using CFormatType = typename TCStringFormatter<t_CFormatter, decltype(Temp)>::CFormatType;

			const uint8 *pValue = (const uint8 *)_Value.f_GetArray();
			mint nBytes = _Value.f_GetSize();

			for (mint i = 0; i < nBytes; ++i)
			{
				NMemory::fg_MemCopy(&OutValue, pValue + i, 1);
				CFormatType::fs_AddToStrStatic(_String, _CurrentStrLen, Temp);
			}

		}

		virtual void f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const override
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

		inline_small static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, const CType &_Value)
		{
			COptionsStatic Options;
			fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
		}

		inline_small static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, const CType &_Value, COptionsStatic &_Options)
		{
			fp_AddToStr(_String, _CurrentStrLen, _Options, _Value);
		}

		virtual aint f_Get_aint() const override
		{
			return 0;
		}

		virtual fp32 f_Get_fp32() const override
		{
			return 0.0f;
		}

		virtual fp64 f_Get_fp64() const override
		{
			return 0.0;
		}

		virtual void f_Visit(CVisitor &_Extractor) const override
		{
			_Extractor();
		}

		virtual void const *f_GetTypeID() const override
		{
			return &ms_TypeID;
		}

		virtual bool f_IsSame(void const *_pRight) const override
		{
			TCStrFormatType_Binary const *pRight = static_cast<TCStrFormatType_Binary const *>(_pRight);

			if (m_Value.f_GetSize() != pRight->m_Value.f_GetSize())
				return false;

			if (NMemory::fg_MemCmp((uint8 const *)m_Value.f_GetArray(), (uint8 const *)pRight->m_Value.f_GetArray(), m_Value.f_GetSize()) != 0)
				return false;

			return true;
		}

		inline static bool const ms_TypeID = false;
	};

	template <typename t_CFormatter>
	class TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapper >
	{
	public:
		using CFormatType = TCStrFormatType_Binary<t_CFormatter, CStrFormatBinaryWrapper>;

		template <typename tf_CTypeWithConst>
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
		using CFormatType = TCStrFormatType_Binary<t_CFormatter, CStrFormatBinaryWrapperUntyped>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CStrFormatBinaryWrapperUntyped const &_Data)
		{
			_Formatter.template f_Alloc<CFormatType>(_Data);
			return typename CFormatType::CStrFormatTypeClassifier();
		}
	};
}
