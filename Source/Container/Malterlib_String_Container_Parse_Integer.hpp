// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CIntType>
	umint TCStrParseType_Int<t_CParser, t_CIntType>::f_Destruct()
	{
		if constexpr (mc_bNeedDestruct)
			this->~TCStrParseType_Int();
		return sizeof(*this);
	}

	template <typename t_CParser, typename t_CIntType>
	inline_small TCStrParseType_Int<t_CParser, t_CIntType>::TCStrParseType_Int(t_CIntType &_Value)
		: mp_Value(_Value)
	{
	}

	template <typename t_CParser, typename t_CIntType>
	template <typename tf_COptions>
	inline_small aint TCStrParseType_Int<t_CParser, t_CIntType>::f_ParseOption(COption &_Option, tf_COptions &_Options, t_CParser const &_ArgData) const
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
						CChar const *ToCompare = _Option.m_pDataStart;

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

	template <typename t_CParser, typename t_CIntType>
	bool TCStrParseType_Int<t_CParser, t_CIntType>::f_ParseData(CChar const * &_pString, CChar const *_pFormat, t_CParser const &_ArgData) const
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
			mp_Value = CTStrTraits::fs_StrToIntParseHex(_pString, mp_Value, Terminator);
			break;
		default:
			{
				CChar const Terminators[] = {Terminator, 0};
				mp_Value = CTStrTraits::fs_StrToIntParse(_pString, mp_Value, Terminators, true, Options.m_NumberFormat);
			}
		break;
		}
		return true;
	}

	template <typename t_CParser, typename t_CIntType>
	aint TCStrParseType_Int<t_CParser, t_CIntType>::f_Get_aint() const
	{
		return fg_Convert<aint>(mp_Value);
	}

	template <typename t_CParser, typename t_CIntType>
	fp32 TCStrParseType_Int<t_CParser, t_CIntType>::f_Get_fp32() const
	{
		return (fp32)fg_Convert<int32>(mp_Value);
	}

	template <typename t_CParser, typename t_CIntType>
	fp64 TCStrParseType_Int<t_CParser, t_CIntType>::f_Get_fp64() const
	{
		return (fp64)fg_Convert<int64>(mp_Value);
	}
}

#define DMibStrStringParserImplementInt(_Type) namespace NMib::NStr \
	{\
		template <typename t_CParser> \
		struct TCStringParser<t_CParser, _Type> \
		{ \
			static inline_large void f_CreateParse(t_CParser &_Formatter, _Type &_Data) \
			{ \
				EStringParseTypeFlag Flags; \
				void *pSpace = _Formatter.f_AllocSpace(sizeof(TCStrParseType_Int<t_CParser, _Type>), Flags); \
				TCStrParseType_Int<t_CParser, _Type> *pNew = new(pSpace) TCStrParseType_Int<t_CParser, _Type>(_Data); \
				Flags |= (TCStrParseType_Int<t_CParser, _Type>::mc_bNeedDestruct ? EStringParseTypeFlag::mc_NeedDestruct : EStringParseTypeFlag::mc_None); \
				_Formatter.fp_AddParse(pNew, Flags); \
			} \
		}; \
	}
