// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CIntType>
	template <typename tf_CInitializer>
	inline_medium TCStrFormatType_Int_Options<t_CFormatter, t_CIntType>::TCStrFormatType_Int_Options(tf_CInitializer const &_Init)
		: TICStrFormatType<t_CFormatter>::COptions(_Init)
		, m_Radix(_Init.template f_Radix<uint32>())
		, m_bNumberCaps(_Init.f_NumberCaps())
		, m_bSign(_Init.f_Sign())
		, m_bBoolean(_Init.f_Boolean())
		, m_ThousandSeparator(_Init.f_ThousandSeparator())
	{
	}

	template <typename t_CFormatter, typename t_CIntType>
	inline_always bool TCStrFormatType_Int_Options<t_CFormatter, t_CIntType>::f_StaticRadix()
	{
		return false;
	}

	template <typename t_CFormatter, typename t_CIntType>
	template <typename tf_CRadix>
	inline_always tf_CRadix TCStrFormatType_Int_Options<t_CFormatter, t_CIntType>::f_Radix() const
	{
		return m_Radix;
	}

	template <typename t_CFormatter, typename t_CIntType>
	inline_always bool TCStrFormatType_Int_Options<t_CFormatter, t_CIntType>::f_NumberCaps() const
	{
		return m_bNumberCaps;
	}

	template <typename t_CFormatter, typename t_CIntType>
	inline_always bool TCStrFormatType_Int_Options<t_CFormatter, t_CIntType>::f_Boolean() const
	{
		if constexpr (NTraits::cIsSame<t_CIntType, bool>)
			return m_bBoolean;
		else
			return false;
	}

	template <typename t_CFormatter, typename t_CIntType>
	inline_always bool TCStrFormatType_Int_Options<t_CFormatter, t_CIntType>::f_Sign() const
	{
		return m_bSign;
	}

	template <typename t_CFormatter, typename t_CIntType>
	inline_always auto TCStrFormatType_Int_Options<t_CFormatter, t_CIntType>::f_ThousandSeparator() const -> typename TICStrFormatType<t_CFormatter>::CChar
	{
		return m_ThousandSeparator;
	}

	template <typename t_CIntType>
	template <typename tf_CRadix>
	inline_always tf_CRadix TCStrFormatType_Int_OptionsStatic<t_CIntType>::f_Radix()
	{
		return 10;
	}

	template <typename t_CIntType>
	inline_always bool TCStrFormatType_Int_OptionsStatic<t_CIntType>::f_StaticRadix()
	{
		return true;
	}

	template <typename t_CIntType>
	inline_always bool TCStrFormatType_Int_OptionsStatic<t_CIntType>::f_NumberCaps()
	{
		return false;
	}

 	template <typename t_CIntType>
	inline_always bool TCStrFormatType_Int_OptionsStatic<t_CIntType>::f_Boolean()
	{
		return false;
	}

	template <typename t_CIntType>
	inline_always bool TCStrFormatType_Int_OptionsStatic<t_CIntType>::f_Sign()
	{
		return false;
	}

	template <typename t_CIntType>
	inline_always ch8 TCStrFormatType_Int_OptionsStatic<t_CIntType>::f_ThousandSeparator()
	{
		return 0;
	}

	template <int32 t_Radix, typename t_CParent>
	inline_always TCStrFormatType_Int_OptionsStatic_Radix<t_Radix, t_CParent>::TCStrFormatType_Int_OptionsStatic_Radix(t_CParent const &_Parent)
		: t_CParent(_Parent)
	{
	}

	template <int32 t_Radix, typename t_CParent>
	template <typename tf_CRadix>
	inline_always tf_CRadix TCStrFormatType_Int_OptionsStatic_Radix<t_Radix, t_CParent>::f_Radix()
	{
		return t_Radix;
	}

	template <int32 t_Radix, typename t_CParent>
	inline_always bool TCStrFormatType_Int_OptionsStatic_Radix<t_Radix, t_CParent>::f_StaticRadix()
	{
		return true;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	umint TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_Destruct()
	{
		if constexpr (mc_bNeedDestruct)
			this->~TCStrFormatType_Int();
		return sizeof(*this);
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_Move(t_CFormatter &_Formatter)
	{
		DMibFastCheck(!NTraits::cIsReference<t_CIntType>); // Not supported
		if constexpr (!NTraits::cIsReference<t_CIntType>)
			_Formatter.template f_Alloc<TCStrFormatType_Int>(f_GetValue(), f_GetOptions());
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CStorage::CStorage(t_CIntType _Value, t_COptions const &_Options)
		: t_COptions(_Options),
		m_Value(_Value)
	{
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CStorage::operator CType const &() const
	{
		return m_Value;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small t_CIntType const &TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_GetValue() const
	{
		return mp_Storage;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small t_COptions const &TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_GetOptions() const
	{
		return mp_Storage;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::TCStrFormatType_Int(t_CIntType _Value, t_COptions const &_Options):
		mp_Storage(_Value, _Options)
	{
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small auto TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CXprImplementation::fs_DefaultValue() -> CType
	{
		return 0;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small auto TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CXprImplementation::fs_Modulus(CType const &_Value, CType &_Modulus) -> CType
	{
		return _Value % _Modulus;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small auto TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CXprImplementation::fs_BitwiseOr(CType const &_Left, CType const &_Right) -> CType
	{
		return _Left | _Right;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small auto TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CXprImplementation::fs_BitwiseAnd(CType const &_Left, CType const &_Right) -> CType
	{
		return _Left & _Right;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small auto TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CXprImplementation::fs_BitwiseXor(CType const &_Left, CType const &_Right) -> CType
	{
		return _Left ^ _Right;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small auto TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CXprImplementation::fs_BitwiseNot(CType const &_Right) -> CType
	{
		return ~_Right;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	inline_small tf_CReturn TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CXprImplementation
		::fs_StrToData(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators)
	{
		return fg_StrToIntParseExact(_pStr, _FailValue, _pStrTerminators);
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename t_CArgument>
	inline_small auto TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CXprImplementation::fs_GetArgumentValue(t_CArgument *_pArg) -> decltype(_pArg->f_Get_aint())
	{
		return _pArg->f_Get_aint();
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_small aint TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>
		::f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const
	{
		switch (_Option.m_FormatTypes.m_Format1)
		{
		case 'N':
			{
				switch (_Option.m_FormatTypes.m_Format2)
				{
				case 'H':
					_Args.m_Options.m_Radix = 16;
					break;
				case 'O':
					_Args.m_Options.m_Radix = 8;
					break;
				case 'B':
					switch (CTStrTraits::CStrTraits::fs_CharUpperCase(*_Option.m_pDataStart))
					{
					case 'T': _Args.m_Options.m_bBoolean = true; break;
					case 'N': _Args.m_Options.m_bBoolean = false; break;
					default: _Args.m_Options.m_Radix = 2; break;
					}
					break;
				case 'C':
					_Args.m_Options.m_bNumberCaps = *_Option.m_pDataStart != '0';
					break;
				case 'T':
					_Args.m_Options.m_ThousandSeparator = (CChar)_Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
					break;
				case 'S':
					_Args.m_Options.m_ThousandSeparator = *_Option.m_pDataStart;
					break;
				case '+':
					_Args.m_Options.m_bSign = true;
					break;
				case 'F':
					{
						CChar const *ToCompare = _Option.m_pDataStart;

						switch (CTStrTraits::CStrTraits::fs_CharUpperCase(*ToCompare))
						{
						case 'H':
							_Args.m_Options.m_Radix = 16;
							break;
						case 'N':
							_Args.m_Options.m_Radix = 10;
							break;
						case 'O':
							_Args.m_Options.m_Radix = 8;
							break;
						case 'B':
							_Args.m_Options.m_Radix = 2;
							break;
						default:
							{
								aint Form = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 10);

								// Cannot have a format lower than base 2
								if (Form < 2)
									Form = 2;

								// Cannot have a format hight than 36, as alphabet is not enough
								if (Form > 36)
									Form = 36;

								_Args.m_Options.m_Radix = Form;
							}
							break;
						}
						break;
					}
				case 'P':
					_Args.m_Options.m_Radix = 16;
					_Args.m_Options.m_Fillout = '0';
					_Args.m_Options.m_MinLength = _Args.m_Options.m_MaxLength = sizeof(tf_CData) * 2;
					break;
				default:
					return TICStrFormatType<t_CFormatter>::f_ParseOption(_Args, _Option);
					break;
				}
				return true;
			}
			break;
		case 'X':
			{
				switch (_Option.m_FormatTypes.m_Format2)
				{
				case 'P':
					CChar const *pParse = _Option.m_pDataStart;
					if (fg_CharUpperCase(*pParse) == 'R')
					{
						CSuper::template fp_EvalExpression<CXprImplementation>(_Args, pParse + 1);
						return true;
					}
					break;
				}
			}
		}
		return TICStrFormatType<t_CFormatter>::f_ParseOption(_Args, _Option);
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <uint32 tf_nBits, typename tf_COptions>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_BitExact(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
#define DUnrollCode \
			{\
				CChar InterNum = (CRadixType(_Number) & (DMibBitRangeTyped(0, tf_nBits - 1, CRadixType)));\
				_Number >>= tf_nBits;\
				if (tf_nBits >= 4 && InterNum > 9)\
					*(pStrPlace--) = NumberCharAddPast10 + InterNum;\
				else\
					*(pStrPlace--) = CChar('0') + InterNum;\
				if (!_Number)\
					break;\
			}
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
#undef DUnrollCode
		}
		_pStrPlace = pStrPlace;

	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <uint32 tf_nBits, typename tf_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_BitExactWithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;

		aint CurrentNumber = 1;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
			CChar InterNum = (CRadixType(_Number) & (DMibBitRangeTyped(0, tf_nBits - 1, CRadixType)));
			_Number >>= tf_nBits;
			if (tf_nBits >= 4 && InterNum > 9)
				*(pStrPlace--) = NumberCharAddPast10 + InterNum;
			else
				*(pStrPlace--) = CChar('0') + InterNum;
			if (!_Number)
				break;
			if (((CurrentNumber++) % 3) == 0 && _Number != CUnsignedType(0))
				*(pStrPlace--) = _Options.f_ThousandSeparator();
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_COptions>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_Above10(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
			CChar InterNum = fg_Convert<CChar>(_Number % _Options.template f_Radix<CRadixType>());
			_Number /= _Options.template f_Radix<CRadixType>();
			if (InterNum > 9)
				*(pStrPlace--) = NumberCharAddPast10 + InterNum;
			else
				*(pStrPlace--) = CChar('0') + InterNum;

			if (!_Number)
				break;
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_Above10WithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;
		aint CurrentNumber = 1;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
			CChar InterNum = fg_Convert<CChar>(_Number % _Options.template f_Radix<CRadixType>());
			if (InterNum > 9)
				*(pStrPlace--) = NumberCharAddPast10 + InterNum;
			else
				*(pStrPlace--) = CChar('0') + InterNum;
			_Number /= _Options.template f_Radix<CRadixType>();
			if (!_Number)
				break;
			if (((CurrentNumber++) % 3) == 0 && _Number != CUnsignedType(0))
				*(pStrPlace--) = _Options.f_ThousandSeparator();
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CRadixType tf_Radix, typename tf_COptions>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_Above10Static(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
			CChar InterNum = fg_Convert<CChar>(CRadixType(_Number) % tf_Radix);
			_Number /= tf_Radix;
			if (InterNum > 9)
				*(pStrPlace--) = NumberCharAddPast10 + InterNum;
			else
				*(pStrPlace--) = CChar('0') + InterNum;

			if (!_Number)
				break;
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CRadixType tf_Radix, typename tf_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_Above10StaticWithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;
		aint CurrentNumber = 1;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
			CChar InterNum = fg_Convert<CChar>(CRadixType(_Number) % tf_Radix);
			_Number /= tf_Radix;
			if (InterNum > 9)
				*(pStrPlace--) = NumberCharAddPast10 + InterNum;
			else
				*(pStrPlace--) = CChar('0') + InterNum;
			if (!_Number)
				break;
			if (((CurrentNumber++) % 3) == 0 && _Number != CUnsignedType(0))
				*(pStrPlace--) = _Options.f_ThousandSeparator();
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_GeneralWithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		aint CurrentNumber = 1;
		CUnsignedType Modulu;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
			Modulu = _Number % _Options.template f_Radix<CRadixType>();
			_Number /= _Options.template f_Radix<CRadixType>();
			*(pStrPlace) = CChar('0') + fg_Convert<CChar>((Modulu));
			--pStrPlace;
			if (!_Number)
				break;
			if (((CurrentNumber++) % 3) == 0 && _Number != CUnsignedType(0))
				*(pStrPlace--) = _Options.f_ThousandSeparator();
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_COptions>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_General(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CUnsignedType Modulu;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
#define DUnrollCode \
			Modulu = _Number % _Options.template f_Radix<CRadixType>();\
			_Number /= _Options.template f_Radix<CRadixType>();\
			*(pStrPlace) = CChar('0') + fg_Convert<CChar>((Modulu));\
			--pStrPlace;\
			if (!_Number)\
				break

			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
#undef DUnrollCode
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CRadixType tf_Radix, typename tf_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_GeneralStaticWithThousand(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CChar const NumberCharAdd = '0';
		aint CurrentNumber = 1;
		CUnsignedType Modulu;
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
			Modulu = CRadixType(_Number) % tf_Radix;
			_Number /= tf_Radix;
			*(pStrPlace) = NumberCharAdd + fg_Convert<CChar>((Modulu));
			--pStrPlace;
			if (!_Number)
				break;
			if (((CurrentNumber++) % 3) == 0 && _Number != CUnsignedType(0))
				*(_pStrPlace--) = _Options.f_ThousandSeparator();
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::CRadixType tf_Radix, typename tf_COptions>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_DoNumber_GeneralStatic(tf_COptions const &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
	{
		CChar * pStrPlace = _pStrPlace;
		while (1)
		{
#if 0
#define DUnrollCode(_Place) \
			pStrPlace[-_Place] = CChar('0') + fg_Convert<CChar>((_Number % tf_Radix));\
			_Number /= tf_Radix;\
			if (!_Number)\
			{\
				pStrPlace -= (_Place + 1);\
				break;\
			}

			DUnrollCode(0);
			DUnrollCode(1);
			DUnrollCode(2);
			DUnrollCode(3);
			DUnrollCode(4);
			DUnrollCode(5);
#undef DUnrollCode
			pStrPlace -= 6;
#else

#define DUnrollCode \
			*(pStrPlace) = CChar('0') + fg_Convert<CChar>((_Number % tf_Radix));\
			--pStrPlace;\
			_Number /= tf_Radix;\
			if (!_Number)\
				break

			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
			DUnrollCode;
#undef DUnrollCode

#endif
		}
		_pStrPlace = pStrPlace;
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fp_AddToStrBoolean(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CType const &_Integer)
	{
		umint Length;
		CChar const *pValue;
		if (_Integer == 0)
		{
			static constexpr CChar ValueArray[] = {'f', 'a', 'l', 's', 'e', 0};
			pValue = ValueArray;
			Length = 5;
		}
		else
		{
			static constexpr CChar ValueArray[] = {'t', 'r', 'u', 'e', 0};
			pValue = ValueArray;
			Length = 4;
		}

		if (_Options.f_SimpleAlign())
			CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, pValue, Length);
		else
			CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, pValue, Length, false);
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_COptions>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>
		::fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CType const &_Integer)
	{
		CUnsignedType Number = _Integer;

		bool bSign = _Options.f_Sign();
		aint bSubStrStart = 0;
		if constexpr (NTraits::cIsSigned<CType>)
		{
			CType Zero = 0;
			if (_Integer < Zero)
			{
				Number = -Number;
				bSign = true;
				bSubStrStart = 1;
			}
		}

		// Make a temporary buffer that can hold the biggest

		enum {NumTempChar = tf_COptions::ENumTempChar};
		CChar TempStr[NumTempChar];
		CChar *pStrPlaceEnd = TempStr + NumTempChar - 1;
		CChar *pStrPlace = pStrPlaceEnd;

		CRadixType Radix = _Options.template f_Radix<CRadixType>();

		if (_Options.f_StaticRadix())
		{
			if (_Options.f_ThousandSeparator())
			{
				if constexpr (1 << gc_HighestBitSet<tf_COptions::ERadix> == tf_COptions::ERadix)
					fs_DoNumber_BitExactWithThousand<gc_HighestBitSet<tf_COptions::ERadix>>(_Options, Number, pStrPlace);
				else if constexpr (tf_COptions::ERadix > 10)
					fs_DoNumber_Above10StaticWithThousand<tf_COptions::ERadix>(_Options, Number, pStrPlace);
				else
					fs_DoNumber_GeneralStaticWithThousand<tf_COptions::ERadix>(_Options, Number, pStrPlace);
			}
			else
			{
				if constexpr (1 << gc_HighestBitSet<tf_COptions::ERadix> == tf_COptions::ERadix)
					fs_DoNumber_BitExact<gc_HighestBitSet<tf_COptions::ERadix>>(_Options, Number, pStrPlace);
				else if constexpr (tf_COptions::ERadix > 10)
					fs_DoNumber_Above10Static<tf_COptions::ERadix>(_Options, Number, pStrPlace);
				else
					fs_DoNumber_GeneralStatic<tf_COptions::ERadix>(_Options, Number, pStrPlace);
			}
		}
		else
		{
			if (!_Options.f_ThousandSeparator())
			{
				if (Radix == 10)
					fs_DoNumber_GeneralStatic<10>(_Options, Number, pStrPlace);
				else if (Radix == 16)
					fs_DoNumber_BitExact<4>(_Options, Number, pStrPlace);
				else if (Radix > 10)
					fs_DoNumber_Above10(_Options, Number, pStrPlace);
				else
					fs_DoNumber_General(_Options, Number, pStrPlace);
			}
			else
			{
				fs_DoNumber_Above10WithThousand(_Options, Number, pStrPlace);
			}
		}

		if (bSign)
		{
			if (bSubStrStart)
				*(pStrPlace--) = '-';
			else
				*(pStrPlace--) = '+';
		}
		// We don't care about string type as we are always < 128
		if (_Options.f_SimpleAlign())
			CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, pStrPlace + 1, pStrPlaceEnd - pStrPlace);
		else
			CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, pStrPlace + 1, pStrPlaceEnd - pStrPlace, bSubStrStart);
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const
	{
		COptionsInt Options(f_GetOptions());
		CType Value = f_GetValue();
		if (_pFormat)
		{
			TICStrFormatType_ParseOptionsArgs<CType, TCStrFormatType_Int, COptionsInt> Args(Value, *this, _String, _CurrentStrLen, Options, _ArgData);
			CSuper::fs_ParseOptions(Args, _pFormat);
		}

		if (!Options.f_Boolean())
			fp_AddToStr(_String, _CurrentStrLen, Options, Value);
		else
			fp_AddToStrBoolean(_String, _CurrentStrLen, Options, Value);
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CType const &_Value)
	{
		t_COptions Options;
		if (!Options.f_Boolean())
			fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
		else
			fp_AddToStrBoolean(_String, _CurrentStrLen, Options, _Value);
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>
		::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CType const &_Value, t_COptions &_Options)
	{
		if (!_Options.f_Boolean())
			fp_AddToStr(_String, _CurrentStrLen, _Options, _Value);
		else
			fp_AddToStrBoolean(_String, _CurrentStrLen, _Options, _Value);
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	template <typename tf_COption, typename tf_CIntType>
	inline_small void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>
		::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, TCValueWithOptions<tf_COption, tf_CIntType> const &_Value)
	{
		if (!_Value.f_Boolean())
			fp_AddToStr(_String, _CurrentStrLen, _Value, _Value.f_GetValue());
		else
			fp_AddToStrBoolean(_String, _CurrentStrLen, _Value, _Value.f_GetValue());
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	aint TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_Get_aint() const
	{
		return fg_Convert<aint>(f_GetValue());
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	fp32 TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_Get_fp32() const
	{
		return (fp32)fg_Convert<int32>(f_GetValue());
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	fp64 TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_Get_fp64() const
	{
		return (fp64)fg_Convert<int64>(f_GetValue());
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	void TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_Visit(CVisitor &_Extractor) const
	{
		if constexpr (NTraits::cIsSigned<CType>)
		{
			if constexpr (sizeof(CType) > sizeof(int32))
				_Extractor(int64(f_GetValue()));
			else
				_Extractor(int32(f_GetValue()));
		}
		else
		{
			if constexpr (sizeof(CType) > sizeof(uint32))
				_Extractor(uint64(f_GetValue()));
			else
				_Extractor(uint32(f_GetValue()));
		}
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	void const *TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_GetTypeID() const
	{
		return &mcp_TypeID;
	}

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	bool TCStrFormatType_Int<t_CFormatter, t_CIntType, t_COptions>::f_IsSame(void const *_pRight) const
	{
		auto pRight = static_cast<TCStrFormatType_Int const *>(_pRight);
		return mp_Storage.m_Value == pRight->mp_Storage.m_Value;
	}

	template <typename t_CFormatter, typename t_CInt0, typename t_CInt1>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, NNumeric::TCInt<t_CInt0, t_CInt1>>::fs_CreateFormat(t_CFormatter &_Formatter, NNumeric::TCInt<t_CInt0, t_CInt1> const &_Data)
		-> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(_Data);
		return CFormatType::CStrFormatTypeClassifier();
	}

	template <typename t_CFormatter, typename t_CInt0, typename t_CInt1>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, TCByValue<NNumeric::TCInt<t_CInt0, t_CInt1>>>
		::fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<NNumeric::TCInt<t_CInt0, t_CInt1>> const &_Data) -> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(*_Data);
		return CFormatType::CStrFormatTypeClassifier();
	}

	template <typename t_CFormatter, typename t_COption, typename t_CIntType>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, TCValueWithOptions<t_COption, t_CIntType>>
		::fs_CreateFormat(t_CFormatter &_Formatter, TCValueWithOptions<t_COption, t_CIntType> const &_Data) -> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(_Data, _Data);
		return CFormatType::CStrFormatTypeClassifier();
	}

	template <typename t_CFormatter, typename t_COption, typename t_CIntType>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, TCByValue<TCValueWithOptions<t_COption, t_CIntType>>>
		::fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<TCValueWithOptions<t_COption, t_CIntType>> const &_Data) -> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(*_Data, *_Data);
		return CFormatType::CStrFormatTypeClassifier();
	}

	template <int32 tf_Radix, typename tf_CIntType>
	inline_small auto fg_FormatIntFormat(tf_CIntType const &_Int)
		-> TCValueWithOptions<TCStrFormatType_Int_OptionsStatic_Radix<tf_Radix, TCStrFormatType_Int_OptionsStatic<tf_CIntType>>, tf_CIntType>
	{
		return TCValueWithOptions
			<
				TCStrFormatType_Int_OptionsStatic_Radix
					<
						tf_Radix,
						TCStrFormatType_Int_OptionsStatic
						<
							tf_CIntType
						>
					>,
				tf_CIntType
			>
			(_Int, TCStrFormatType_Int_OptionsStatic_Radix<tf_Radix, TCStrFormatType_Int_OptionsStatic<tf_CIntType>>(TCStrFormatType_Int_OptionsStatic<tf_CIntType>()))
		;
	}

	template <int32 tf_Radix, typename tf_CIntType, typename tf_COldOptions>
	inline_small auto fg_FormatIntFormat(TCValueWithOptions<tf_COldOptions, tf_CIntType> const &_Int)
		-> TCValueWithOptions<TCStrFormatType_Int_OptionsStatic_Radix<tf_Radix, tf_COldOptions>, tf_CIntType>
	{
		return TCValueWithOptions
			<
				TCStrFormatType_Int_OptionsStatic_Radix
					<
						tf_Radix,
						tf_COldOptions
					>,
				tf_CIntType
			>
			(_Int.f_GetValue(), TCStrFormatType_Int_OptionsStatic_Radix<tf_Radix, tf_COldOptions>(_Int.f_GetOptions()))
		;
	}

	template <typename t_CFormatter, typename t_CData>
	struct TCStringFormatter<t_CFormatter, t_CData *>::CPtrOptions : public TCStrFormatType_Int_OptionsStatic_Radix<16, TCStrFormatType_Int_OptionsStatic<umint>>
	{
		CPtrOptions()
			: TCStrFormatType_Int_OptionsStatic_Radix<16, TCStrFormatType_Int_OptionsStatic<umint>>(TCStrFormatType_Int_OptionsStatic<umint>())
		{
		}

		constexpr inline_small static bool f_RestrictLength()
		{
			return true;
		}

		constexpr inline_small static umint f_MinLength()
		{
			return sizeof(umint)*2;
		}

		constexpr inline_small static umint f_MaxLength()
		{
			return sizeof(umint)*2;
		}

		inline_small static ch8 f_Fillout()
		{
			return '0';
		}
	};

	template <typename t_CFormatter, typename t_CData>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, t_CData *>::fs_CreateFormat(t_CFormatter &_Formatter, t_CData * const &_Data) -> typename CFormatType::CStrFormatTypeClassifier
	{
		umint Data = (umint)_Data;
		_Formatter.template f_Alloc<CFormatType>(Data);
		return typename CFormatType::CStrFormatTypeClassifier();
	}

	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, bool>::CBoolOptions : public TCStrFormatType_Int_Options<t_CFormatter, bool>
	{
		CBoolOptions()
			: TCStrFormatType_Int_Options<t_CFormatter, bool>(TCStrFormatType_Int_OptionsStatic<bool>())
		{
		}

		inline_small static bool f_Boolean()
		{
			return true;
		}
	};

	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, bool>::fs_CreateFormat(t_CFormatter &_Formatter, bool const &_Data) -> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(_Data);
		return typename CFormatType::CStrFormatTypeClassifier();
	}
}

#define DMibStrStringFormatterImplementInt(_Type) namespace NMib::NStr \
	{ \
		template <typename t_CFormatter> \
		struct TCStringFormatter<t_CFormatter, _Type> \
		{ \
		public: \
			using CFormatType = TCStrFormatType_Int<t_CFormatter, _Type const &>; \
			template <typename tf_CTypeWithConst> \
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, _Type const &_Data) \
			{ \
				_Formatter.template f_Alloc<CFormatType>(_Data);\
				return typename CFormatType::CStrFormatTypeClassifier();\
			} \
		};\
		template <typename t_CFormatter> \
		struct TCStringFormatter<t_CFormatter, TCByValue<_Type>> \
		{ \
		public: \
			using CFormatType = TCStrFormatType_Int<t_CFormatter, _Type>; \
			template <typename tf_CTypeWithConst> \
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<_Type> const &_Data) \
			{ \
				_Formatter.template f_Alloc<CFormatType>(*_Data);\
				return typename CFormatType::CStrFormatTypeClassifier();\
			} \
		}; \
	}
