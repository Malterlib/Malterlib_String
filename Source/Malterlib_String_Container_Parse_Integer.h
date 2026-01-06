// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CIntType>
	class TCStrParseType_Int final : public TICStrParseType<t_CParser>
	{
	public:
		virtual mint f_Delete() override
		{
			if constexpr (mc_bNeedDelete)
				this->~TCStrParseType_Int();
			return sizeof(*this);
		}

		using CTStrTraits = typename t_CParser::CStrTraits;
		using CChar = typename CTStrTraits::CChar;

		enum
		{
			mc_bNeedDelete = false
		};

		t_CIntType &m_Value;
		inline_small TCStrParseType_Int(t_CIntType &_Value):
		m_Value(_Value)
		{
		}

		using CSuper = TICStrParseType<t_CParser>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;

		class COptionsInt : public COptions
		{
		public:
			enum ENumberFormat
			{
				 ENumberFormat_Base16	= 16
				,ENumberFormat_Base10	= 10
				,ENumberFormat_Base8	= 8
				,ENumberFormat_Base2	= 2
			};

			aint m_NumberFormat;

			inline_medium COptionsInt():
			m_NumberFormat(-1)
			{
			}

		};

		template <typename t_COptions>
		inline_small aint f_ParseOption(COption &_Option, t_COptions &_Options, const t_CParser & _ArgData) const
		{
			switch (_Option.m_ParseTypes.m_Parse1)
			{
			case 'N':
				{
					switch (_Option.m_ParseTypes.m_Parse2)
					{
					case 'H':
						_Options.m_NumberFormat = (int)COptionsInt::ENumberFormat_Base16;
						break;
					case 'O':
						_Options.m_NumberFormat = (int)COptionsInt::ENumberFormat_Base8;
						break;
					case 'B':
						_Options.m_NumberFormat = (int)COptionsInt::ENumberFormat_Base2;
						break;
					case 'F':
						{
							const CChar *ToCompare = _Option.m_pDataStart;

							switch (CTStrTraits::fs_CharUpperCase(*ToCompare))
							{
							case 'H':
								_Options.m_NumberFormat = (int)COptionsInt::ENumberFormat_Base16;
								break;
							case 'N':
								_Options.m_NumberFormat = (int)COptionsInt::ENumberFormat_Base10;
								break;
							case 'O':
								_Options.m_NumberFormat = (int)COptionsInt::ENumberFormat_Base8;
								break;
							case 'B':
								_Options.m_NumberFormat = (int)COptionsInt::ENumberFormat_Base2;
								break;
							default:
								{
									t_CIntType Form = t_CIntType(_Option.f_GetData_aint_NotSigned(_ArgData, 10));

									// Cannot have a format lower than base 2
									if (Form < t_CIntType(2))
										Form = t_CIntType(2);

									// Cannot have a format hight than 36, as alphabet is not enough
									if (Form > t_CIntType(36))
										Form = t_CIntType(36);

									_Options.m_NumberFormat = Form;
								}
								break;
							}
							break;
						}
					default:
						return CSuper::f_ParseOption(_Option, _Options, _ArgData);
						break;
					}
					return true;
				}
				break;
			}
			return CSuper::f_ParseOption(_Option, _Options, _ArgData);
		}

		virtual bool f_ParseData(const CChar *&_pString, const CChar *_pFormat, const t_CParser & _ArgData) const override
		{
			COptionsInt Options;
#if 1
			CChar Terminator = *CSuper::fs_ParseOptions(*this, Options, _pFormat, _ArgData);
#else
			CChar Terminator = 0;
#endif
			switch (Options.m_NumberFormat)
			{
			case COptionsInt::ENumberFormat_Base16:
				m_Value = CTStrTraits::fs_StrToIntParseHex(_pString, m_Value, Terminator);
				break;
			default:
				{
					const CChar Terminators[] = {Terminator, 0};
					m_Value = CTStrTraits::fs_StrToIntParse(_pString, m_Value, Terminators, true, Options.m_NumberFormat);
				}
			break;
			}
			return true;
		}

		virtual aint f_Get_aint() const override
		{
			return fg_Convert<aint>(m_Value);
		}

		virtual fp32 f_Get_fp32() const override
		{
			return (fp32)fg_Convert<int32>(m_Value);
		}

		virtual fp64 f_Get_fp64() const override
		{
			return (fp64)fg_Convert<int64>(m_Value);
		}

	};
}

#define DMibStrStringParserImplementInt(_Type) namespace NMib{namespace NStr{\
	template <typename t_CParser> \
	class TCStringParser<t_CParser, _Type> \
	{ \
	public: \
		static inline_large void f_CreateParse(t_CParser &_Formatter, _Type &_Data) \
		{ \
			mint Flags; \
			void *pSpace = _Formatter.f_AllocSpace(sizeof(TCStrParseType_Int<t_CParser, _Type>), Flags); \
			TCStrParseType_Int<t_CParser, _Type> *pNew = new(pSpace) TCStrParseType_Int<t_CParser, _Type>(_Data); \
			Flags |= (TCStrParseType_Int<t_CParser, _Type>::mc_bNeedDelete ? 2 : 0); \
			_Formatter.fp_AddParse(pNew, Flags); \
		} \
	};}}


DMibStrStringParserImplementInt(uint8);
DMibStrStringParserImplementInt(int8);
DMibStrStringParserImplementInt(uint16);
DMibStrStringParserImplementInt(int16);
DMibStrStringParserImplementInt(uint32);
DMibStrStringParserImplementInt(int32);
DMibStrStringParserImplementInt(uint64);
DMibStrStringParserImplementInt(int64);
DMibStrStringParserImplementInt(uint80);
DMibStrStringParserImplementInt(int80);
DMibStrStringParserImplementInt(uint96);
DMibStrStringParserImplementInt(int96);
DMibStrStringParserImplementInt(uint128);
DMibStrStringParserImplementInt(int128);
DMibStrStringParserImplementInt(uint160);
DMibStrStringParserImplementInt(int160);
DMibStrStringParserImplementInt(uint192);
DMibStrStringParserImplementInt(int192);
DMibStrStringParserImplementInt(uint256);
DMibStrStringParserImplementInt(int256);
DMibStrStringParserImplementInt(uint320);
DMibStrStringParserImplementInt(int320);
DMibStrStringParserImplementInt(uint384);
DMibStrStringParserImplementInt(int384);
DMibStrStringParserImplementInt(uint512);
DMibStrStringParserImplementInt(int512);
DMibStrStringParserImplementInt(uint1024);
DMibStrStringParserImplementInt(int1024);
DMibStrStringParserImplementInt(uint2048);
DMibStrStringParserImplementInt(int2048);
DMibStrStringParserImplementInt(uint4096);
DMibStrStringParserImplementInt(int4096);
DMibStrStringParserImplementInt(uint8192);
DMibStrStringParserImplementInt(int8192);
DMibStrStringParserImplementInt(uint16384);
DMibStrStringParserImplementInt(int16384);


#ifdef DMibPUniqueType_mint
DMibStrStringParserImplementInt(mint);
#endif
#ifdef DMibPUniqueType_smint
DMibStrStringParserImplementInt(smint);
#endif
#ifdef DMibPUniqueType_int
DMibStrStringParserImplementInt(int);
#endif
#ifdef DMibPUniqueType_uint
DMibStrStringParserImplementInt(unsigned int);
#endif
#ifdef DMibPUniqueType_aint
DMibStrStringParserImplementInt(aint);
#endif

#ifdef DMibPUniqueType_uaint
DMibStrStringParserImplementInt(uaint);
#endif


#ifdef DMibPUniqueType_ch8
DMibStrStringParserImplementInt(ch8);
#endif
#ifdef DMibPUniqueType_ch16
DMibStrStringParserImplementInt(ch16);
#endif
#ifdef DMibPUniqueType_ch32
DMibStrStringParserImplementInt(ch32);
#endif
