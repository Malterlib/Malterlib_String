// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CFloatType>
	class TCStrParseType_Float final : public TICStrParseType<t_CParser>
	{
	private:
		inline_small TCStrParseType_Float(const TCStrParseType_Float &_Value)
		{
		}

		inline_small TCStrParseType_Float &operator =(const TCStrParseType_Float &_Value)
		{
			return *this;
		}

	public:
		virtual mint f_Delete() override
		{
			if constexpr (mc_bNeedDelete)
				this->~TCStrParseType_Float();
			return sizeof(*this);
		}

		using CStrTraits = typename t_CParser::CStrTraits;
		using CChar = typename CStrTraits::CChar;

		enum
		{
			mc_bNeedDelete = false
		};

		t_CFloatType &m_Value;
		inline_small TCStrParseType_Float(t_CFloatType &_Value)
			: m_Value(_Value)
		{
		}

		using CSuper = TICStrParseType<t_CParser>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;

		class COptionsFloat : public COptions
		{
		public:
			inline_medium COptionsFloat()
			{
			}

		};

		template <typename t_COptions>
		inline_small aint f_ParseOption(COption &_Option, t_COptions &_Options, const t_CParser & _ArgData) const
		{
#if 0
			switch (_Option.m_ParseTypes.m_Parse1)
			{
				break;
			}
#endif
			return CSuper::f_ParseOption(_Option, _Options, _ArgData);
		}

		virtual bool f_ParseData(const CChar *&_pString, const CChar *_pFormat, const t_CParser & _ArgData) const override
		{
			COptionsFloat Options;
			CChar Terminator = *CSuper::fs_ParseOptions(*this, Options, _pFormat, _ArgData);

			const CChar Terminators[] = {Terminator, 0};
			m_Value = NStr::fg_StrToFloatParseExact(_pString, m_Value, Terminators);
			return true;
		}

		virtual aint f_Get_aint() const override
		{
			return fg_Convert<aint>(m_Value.f_ToInt());
		}

		virtual fp32 f_Get_fp32() const override
		{
			return m_Value;
		}

		virtual fp64 f_Get_fp64() const override
		{
			return m_Value;
		}

	};

	template <typename t_CParser, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCStringParser<t_CParser, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> >
	{
	public:
		using CFloat = NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>;
		using CParseType = TCStrParseType_Float<t_CParser, CFloat>;

		static inline_large void f_CreateParse(t_CParser &_Formatter, CFloat &_Data)
		{
			mint Flags;
			void *pSpace = _Formatter.f_AllocSpace(sizeof(CParseType), Flags);

			CParseType *pNew = new(pSpace) CParseType(_Data);
			Flags |= (CParseType::mc_bNeedDelete ? 2 : 0);
			_Formatter.fp_AddParse(pNew, Flags);
		}
	};
}
