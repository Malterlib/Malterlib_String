// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CIntType>
	class TCStrFormatType_Int_Options : public TICStrFormatType<t_CFormatter>::COptions
	{
	public:
		enum
		{
			ERadix = 10,
			ENumTempChar = sizeof(t_CIntType) * 8 + 2 + ((sizeof(t_CIntType) * 8 + 2) / 3)
		};

		uint32 m_Radix:30;
		uint32 m_bNumberCaps:1;
		uint32 m_bSign:1;
		typename TICStrFormatType<t_CFormatter>::CChar m_ThousandSeparator;

		template <typename t_Initializer>
		inline_medium TCStrFormatType_Int_Options(const t_Initializer &_Init)
			: TICStrFormatType<t_CFormatter>::COptions(_Init)
			, m_Radix(_Init.template f_Radix<uint32>())
			, m_bNumberCaps(_Init.f_NumberCaps())
			, m_bSign(_Init.f_Sign())
			, m_ThousandSeparator(_Init.f_ThousandSeparator())
		{
		}

		inline_small static bool f_StaticRadix()
		{
			return false;
		}

		template <typename t_CRadix>
		inline_small t_CRadix f_Radix() const
		{
			return m_Radix;
		}
		inline_small bool f_NumberCaps() const
		{
			return m_bNumberCaps;
		}
		inline_small bool f_Sign() const
		{
			return m_bSign;
		}
		inline_small typename TICStrFormatType<t_CFormatter>::CChar f_ThousandSeparator() const
		{
			return m_ThousandSeparator;
		}
	};
	template <typename t_CIntType>
	class TCStrFormatType_Int_OptionsStatic : public TICStrFormatType_StaticOptions
	{
	public:
		typedef t_CIntType CIntType;
		enum
		{
			ERadix = 10,
			ENumTempChar = (sizeof(CIntType) * 8)/3 + 2
		};

		template <typename t_CRadix>
		inline_small static t_CRadix f_Radix()
		{
			return 10;
		}
		inline_small static bool f_StaticRadix()
		{
			return true;
		}
		inline_small static bool f_NumberCaps()
		{
			return false;
		}
		inline_small static bool f_Sign()
		{
			return false;
		}
		inline_small static ch8 f_ThousandSeparator()
		{
			return 0;
		}

	};

	template <int32 t_Radix, typename t_CParent>
	class TCStrFormatType_Int_OptionsStatic_Radix : public t_CParent
	{
		typedef typename t_CParent::CIntType CIntType;
		static_assert(t_Radix >= 2 && t_Radix <= 36);
		enum
		{
			ENumBits = sizeof(CIntType) * 8,
			ENumBitsPerChar = TCHighestBitSet<int32, t_Radix>::mc_Value - 1
		};
	public:

		enum
		{
			ERadix = t_Radix,
			ENumTempChar = (ENumBits+(ENumBitsPerChar-1))/ENumBitsPerChar + 2
		};

		inline_small TCStrFormatType_Int_OptionsStatic_Radix(const t_CParent &_Parent)
			: t_CParent(_Parent)
		{
		}

		template <typename t_CRadix>
		inline_small static t_CRadix f_Radix()
		{
			return t_Radix;
		}
		inline_small static bool f_StaticRadix()
		{
			return true;
		}
	};

	template <typename t_CFormatter, typename t_CIntType, typename t_COptions>
	class TCStrFormatType_Int final : public TICStrFormatType<t_CFormatter>
	{
	public:

		typedef CStrFormatTypeClassifier_Integer CStrFormatTypeClassifier;

		virtual mint f_Delete() override
		{
			if constexpr (mc_bNeedDelete)
				this->~TCStrFormatType_Int();
			return sizeof(*this);
		}

		virtual void f_Move(t_CFormatter &_Formatter) override
		{
			DMibFastCheck(!NTraits::TCIsReference<t_CIntType>::mc_Value); // Not supported
			if constexpr (!NTraits::TCIsReference<t_CIntType>::mc_Value)
				_Formatter.template f_Alloc<TCStrFormatType_Int>(f_GetValue(), f_GetOptions());
		}

		typedef typename t_CFormatter::CTStrTraits CTStrTraits;
		typedef typename CTStrTraits::CStrTraits::CChar CChar;
		typedef TICStrFormatType<t_CFormatter> CSuper;

		typedef typename NTraits::TCRemoveConst<typename NTraits::TCRemoveReference<t_CIntType>::CType>::CType CType;
		typedef typename NTraits::TCUnsigned<CType>::CType CUnsignedType;
		typedef typename TCChooseType<NTraits::TCIsFundamental<CUnsignedType>::mc_Value, CUnsignedType, uint32>::CType CRadixType;
		typedef typename CSuper::CVisitor CVisitor;

		enum
		{
			mc_bNeedDelete = !NTraits::TCIsReference<t_CIntType>::mc_Value
		};

		class CStorage : public t_COptions
		{
		public:
			t_CIntType m_Value;
			inline_small CStorage(t_CIntType _Value, t_COptions const &_Options)
				: t_COptions(_Options),
				m_Value(_Value)
			{
			}

			inline_small operator const CType &() const
			{
				return m_Value;
			}
		};
		CStorage m_Storage;

		inline_small const t_CIntType &f_GetValue() const
		{
			return m_Storage;
		}

		inline_small const t_COptions &f_GetOptions() const
		{
			return m_Storage;
		}

		inline_small TCStrFormatType_Int(t_CIntType _Value, const t_COptions &_Options = t_COptions()):
			m_Storage(_Value, _Options)
		{
		}

		typedef typename TICStrFormatType<t_CFormatter> :: COption COption;
		typedef typename TICStrFormatType<t_CFormatter> :: COptions COptions;
		typedef TCStrFormatType_Int_Options<t_CFormatter, CType> COptionsInt;
		typedef TCStrFormatType_Int_OptionsStatic<CType> COptionsIntStatic;

		class CXprImplementation
		{
		public:
			inline_small static CType fs_DefaultValue()
			{
				return 0;
			}

			inline_small static CType fs_Modulus(CType const &_Value, CType &_Modulus)
			{
				return _Value % _Modulus;
			}

			inline_small static CType fs_BitwiseOr(CType const &_Left, CType const &_Right)
			{
				return _Left | _Right;
			}

			inline_small static CType fs_BitwiseAnd(CType const &_Left, CType const &_Right)
			{
				return _Left & _Right;
			}

			inline_small static CType fs_BitwiseXor(CType const &_Left, CType const &_Right)
			{
				return _Left ^ _Right;
			}

			inline_small static CType fs_BitwiseNot(CType const &_Right)
			{
				return ~_Right;
			}

			template <typename t_CData, typename t_CReturn, typename t_CTerm>
			inline_small static t_CReturn fs_StrToData(const t_CData *&_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
			{
				return fg_StrToIntParseExact(_pStr, _FailValue, _pStrTerminators);
			}

			template <typename t_CArgument>
			inline_small static auto fs_GetArgumentValue(t_CArgument *_pArg) -> decltype(_pArg->f_Get_aint())
			{
				return _pArg->f_Get_aint();
			}

		};

		template <typename t_CData, typename t_CFormatType, typename t_COptions2>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions2> &_Args, COption &_Option) const
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
						_Args.m_Options.m_Radix = 2;
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
							const CChar *ToCompare = _Option.m_pDataStart;

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
						_Args.m_Options.m_MinLength = _Args.m_Options.m_MaxLength = sizeof(t_CData) * 2;
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
						const CChar *pParse = _Option.m_pDataStart;
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


		template <uint32 t_nBits, typename t_COptions2>
		inline_small static void fs_DoNumber_BitExact(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
		{
			CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;
			CChar * pStrPlace = _pStrPlace;
			while (1)
			{
#define DUnrollCode \
				{\
					CChar InterNum = (CRadixType(_Number) & (DMibBitRangeTyped(0, t_nBits - 1, CRadixType)));\
					_Number >>= t_nBits;\
					if (t_nBits >= 4 && InterNum > 9)\
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

		template <uint32 t_nBits, typename t_COptions2>
		static void fs_DoNumber_BitExactWithThousand(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
		{
			CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;

			aint CurrentNumber = 1;
			CChar * pStrPlace = _pStrPlace;
			while (1)
			{
				CChar InterNum = (CRadixType(_Number) & (DMibBitRangeTyped(0, t_nBits - 1, CRadixType)));
				_Number >>= t_nBits;
				if (t_nBits >= 4 && InterNum > 9)
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

		template <typename t_COptions2>
		inline_small static void fs_DoNumber_Above10(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
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

		template <typename t_COptions2>
		static void fs_DoNumber_Above10WithThousand(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
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

		template <CRadixType t_Radix, typename t_COptions2>
		inline_small static void fs_DoNumber_Above10Static(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
		{
			CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;
			CChar * pStrPlace = _pStrPlace;
			while (1)
			{
				CChar InterNum = fg_Convert<CChar>(CRadixType(_Number) % t_Radix);
				_Number /= t_Radix;
				if (InterNum > 9)
					*(pStrPlace--) = NumberCharAddPast10 + InterNum;
				else
					*(pStrPlace--) = CChar('0') + InterNum;

				if (!_Number)
					break;
			}
			_pStrPlace = pStrPlace;
		};

		template <CRadixType t_Radix, typename t_COptions2>
		static void fs_DoNumber_Above10StaticWithThousand(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
		{
			CChar NumberCharAddPast10 = _Options.f_NumberCaps() ? 'A' - 10 : 'a' - 10;
			aint CurrentNumber = 1;
			CChar * pStrPlace = _pStrPlace;
			while (1)
			{
				CChar InterNum = fg_Convert<CChar>(CRadixType(_Number) % t_Radix);
				_Number /= t_Radix;
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


		template <typename t_COptions2>
		static void fs_DoNumber_GeneralWithThousand(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
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


		template <typename t_COptions2>
		inline_small static void fs_DoNumber_General(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
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

		template <CRadixType t_Radix, typename t_COptions2>
		static void fs_DoNumber_GeneralStaticWithThousand(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
		{
			const CChar NumberCharAdd = '0';
			aint CurrentNumber = 1;
			CUnsignedType Modulu;
			CChar * pStrPlace = _pStrPlace;
			while (1)
			{
				Modulu = CRadixType(_Number) % t_Radix;
				_Number /= t_Radix;
				*(pStrPlace) = NumberCharAdd + fg_Convert<CChar>((Modulu));
				--pStrPlace;
				if (!_Number)
					break;
				if (((CurrentNumber++) % 3) == 0 && _Number != CUnsignedType(0))
					*(_pStrPlace--) = _Options.f_ThousandSeparator();
			}
			_pStrPlace = pStrPlace;
		};


		template <CRadixType t_Radix, typename t_COptions2>
		inline_small static void fs_DoNumber_GeneralStatic(const t_COptions2 &_Options, CUnsignedType _Number, CChar * &_pStrPlace)
		{
			CChar * pStrPlace = _pStrPlace;
			while (1)
			{
#if 0
#define DUnrollCode(_Place) \
				pStrPlace[-_Place] = CChar('0') + fg_Convert<CChar>((_Number % t_Radix));\
				_Number /= t_Radix;\
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
				*(pStrPlace) = CChar('0') + fg_Convert<CChar>((_Number % t_Radix));\
				--pStrPlace;\
				_Number /= t_Radix;\
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

		template <typename t_COptions2>
		inline_small static void fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const t_COptions2 &_Options, const CType &_Integer)
		{
			CUnsignedType Number = _Integer;

			bool bSign = _Options.f_Sign();
			aint bSubStrStart = 0;
			if constexpr (NTraits::TCIsSigned<CType>::mc_Value)
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

			enum {NumTempChar = t_COptions2::ENumTempChar};
			CChar TempStr[NumTempChar];
			CChar *pStrPlaceEnd = TempStr + NumTempChar - 1;
			CChar *pStrPlace = pStrPlaceEnd;

			CRadixType Radix = _Options.template f_Radix<CRadixType>();

			if (_Options.f_StaticRadix())
			{
				if (_Options.f_ThousandSeparator())
				{
					if constexpr (1 << (TCHighestBitSet<int32, t_COptions2::ERadix>::mc_Value - 1) == t_COptions2::ERadix)
						fs_DoNumber_BitExactWithThousand<TCHighestBitSet<int32, t_COptions2::ERadix>::mc_Value - 1>(_Options, Number, pStrPlace);
					else if constexpr (t_COptions2::ERadix > 10)
						fs_DoNumber_Above10StaticWithThousand<t_COptions2::ERadix>(_Options, Number, pStrPlace);
					else
						fs_DoNumber_GeneralStaticWithThousand<t_COptions2::ERadix>(_Options, Number, pStrPlace);
				}
				else
				{
					if constexpr (1 << (TCHighestBitSet<int32, t_COptions2::ERadix>::mc_Value - 1) == t_COptions2::ERadix)
						fs_DoNumber_BitExact<TCHighestBitSet<int32, t_COptions2::ERadix>::mc_Value - 1>(_Options, Number, pStrPlace);
					else if constexpr (t_COptions2::ERadix > 10)
						fs_DoNumber_Above10Static<t_COptions2::ERadix>(_Options, Number, pStrPlace);
					else
						fs_DoNumber_GeneralStatic<t_COptions2::ERadix>(_Options, Number, pStrPlace);
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

		virtual void f_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const override
		{
			COptionsInt Options(f_GetOptions());
			CType Value = f_GetValue();
			if (_pFormat)
			{
				TICStrFormatType_ParseOptionsArgs<CType, TCStrFormatType_Int, COptionsInt> Args(Value, *this, _String, _CurrentStrLen, Options, _ArgData);
				CSuper::fs_ParseOptions(Args, _pFormat);
			}

			fp_AddToStr(_String, _CurrentStrLen, Options, Value);
		}

		inline_small static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const CType &_Value)
		{
			t_COptions Options;
			fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
		}


		template <typename t_COption2, typename t_CIntType2>
		inline_small static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const TCValueWithOptions<t_COption2, t_CIntType2> &_Value)
		{
			fp_AddToStr(_String, _CurrentStrLen, _Value, _Value.f_GetValue());
		}

		virtual aint f_Get_aint() const override
		{
			return fg_Convert<aint>(f_GetValue());
		}

		virtual fp32 f_Get_fp32() const override
		{
			return (fp32)fg_Convert<int32>(f_GetValue());
		}

		virtual fp64 f_Get_fp64() const override
		{
			return (fp64)fg_Convert<int64>(f_GetValue());
		}

		virtual void f_Visit(CVisitor &_Extractor) const override
		{
			if constexpr (NTraits::TCIsSigned<CType>::mc_Value)
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

	};

	template <typename t_CFormatter, typename t_CInt0, typename t_CInt1>
	class TCStringFormatter<t_CFormatter, NNumeric::TCInt<t_CInt0, t_CInt1>>
	{
	public:
		typedef TCStrFormatType_Int<t_CFormatter, NNumeric::TCInt<t_CInt0, t_CInt1> const &> CFormatType;
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, NNumeric::TCInt<t_CInt0, t_CInt1> const &_Data)
		{
			_Formatter.template f_Alloc<CFormatType>(_Data);
			return CFormatType::CStrFormatTypeClassifier();
		}
	};

	template <typename t_CFormatter, typename t_CInt0, typename t_CInt1>
	class TCStringFormatter<t_CFormatter, TCByValue<NNumeric::TCInt<t_CInt0, t_CInt1>>>
	{
	public:
		typedef TCStrFormatType_Int<t_CFormatter, NNumeric::TCInt<t_CInt0, t_CInt1>> CFormatType;
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<NNumeric::TCInt<t_CInt0, t_CInt1>> const &_Data)
		{
			_Formatter.template f_Alloc<CFormatType>(*_Data);
			return CFormatType::CStrFormatTypeClassifier();
		}
	};

	template <typename t_CFormatter, typename t_COption, typename t_CIntType>
	class TCStringFormatter<t_CFormatter, TCValueWithOptions<t_COption, t_CIntType>>
	{
	public:
		typedef TCStrFormatType_Int<t_CFormatter, t_CIntType const &, TCValueWithOptions<t_COption, t_CIntType>> CFormatType;
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCValueWithOptions<t_COption, t_CIntType> const &_Data)
		{
			_Formatter.template f_Alloc<CFormatType>(_Data, _Data);
			return CFormatType::CStrFormatTypeClassifier();
		}
	};

	template <typename t_CFormatter, typename t_COption, typename t_CIntType>
	class TCStringFormatter<t_CFormatter, TCByValue<TCValueWithOptions<t_COption, t_CIntType>>>
	{
	public:
		typedef TCStrFormatType_Int<t_CFormatter, t_CIntType, TCValueWithOptions<t_COption, t_CIntType>> CFormatType;
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<TCValueWithOptions<t_COption, t_CIntType>> const &_Data)
		{
			_Formatter.template f_Alloc<CFormatType>(*_Data, *_Data);
			return CFormatType::CStrFormatTypeClassifier();
		}
	};

	template <int32 t_Radix, typename t_CIntType>
	inline_small TCValueWithOptions<TCStrFormatType_Int_OptionsStatic_Radix<t_Radix, TCStrFormatType_Int_OptionsStatic<t_CIntType>>, t_CIntType> fg_FormatIntFormat(const t_CIntType &_Int)
	{
		return TCValueWithOptions
				<
					TCStrFormatType_Int_OptionsStatic_Radix
						<
							t_Radix,
							TCStrFormatType_Int_OptionsStatic
							<
								t_CIntType
							>
						>,
					t_CIntType
				>
			(_Int, TCStrFormatType_Int_OptionsStatic_Radix<t_Radix, TCStrFormatType_Int_OptionsStatic<t_CIntType>>(TCStrFormatType_Int_OptionsStatic<t_CIntType>()));
	}

	template <int32 t_Radix, typename t_CIntType, typename t_COldOptions>
	inline_small TCValueWithOptions<TCStrFormatType_Int_OptionsStatic_Radix<t_Radix, t_COldOptions>, t_CIntType> fg_FormatIntFormat(const TCValueWithOptions<t_COldOptions, t_CIntType> &_Int)
	{
		return TCValueWithOptions
				<
					TCStrFormatType_Int_OptionsStatic_Radix
						<
							t_Radix,
							t_COldOptions
						>,
					t_CIntType
				>
			(_Int.f_GetValue(), TCStrFormatType_Int_OptionsStatic_Radix<t_Radix, t_COldOptions>(_Int.f_GetOptions()));
	}

	// Default formatter for pointers
	template <typename t_CFormatter, typename t_CData>
	class TCStringFormatter<t_CFormatter, t_CData *>
	{
	public:

		class CPtrOptions : public TCStrFormatType_Int_OptionsStatic_Radix<16, TCStrFormatType_Int_OptionsStatic<mint>>
		{
		public:
			CPtrOptions()
				: TCStrFormatType_Int_OptionsStatic_Radix<16, TCStrFormatType_Int_OptionsStatic<mint>>(TCStrFormatType_Int_OptionsStatic<mint>())
			{
			}
			inline_small static bool f_RestrictLength()
			{
				return true;
			}
			inline_small static mint f_MinLength()
			{
				return sizeof(mint)*2;
			}
			inline_small static mint f_MaxLength()
			{
				return sizeof(mint)*2;
			}

			inline_small static ch8 f_Fillout()
			{
				return '0';
			}
		};

		typedef TCStrFormatType_Int<t_CFormatter, mint, CPtrOptions> CFormatType;
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, t_CData * const &_Data)
		{
			mint Data = (mint)_Data;
			_Formatter.template f_Alloc<CFormatType>(Data);
			return typename CFormatType::CStrFormatTypeClassifier();
		}
	};
	template <typename t_CFormatter>
	class TCStringFormatter<t_CFormatter, bool>
	{
	public:
		typedef TCStrFormatType_Int<t_CFormatter, int8> CFormatType;
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, bool const&_Data)
		{
			_Formatter.template f_Alloc<CFormatType>(_Data);
			return typename CFormatType::CStrFormatTypeClassifier();
		}
	};
}
#define DMibStrStringFormatterImplementInt(_Type) namespace NMib{namespace NStr{\
	template <typename t_CFormatter> \
	class TCStringFormatter<t_CFormatter, _Type> \
	{ \
	public: \
		typedef TCStrFormatType_Int<t_CFormatter, _Type const &> CFormatType;\
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, _Type const&_Data) \
		{ \
			_Formatter.template f_Alloc<CFormatType>(_Data);\
			return typename CFormatType::CStrFormatTypeClassifier();\
		} \
	};\
	template <typename t_CFormatter> \
	class TCStringFormatter<t_CFormatter, TCByValue<_Type>> \
	{ \
	public: \
		typedef TCStrFormatType_Int<t_CFormatter, _Type> CFormatType;\
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<_Type> const &_Data) \
		{ \
			_Formatter.template f_Alloc<CFormatType>(*_Data);\
			return typename CFormatType::CStrFormatTypeClassifier();\
		} \
	};}}


DMibStrStringFormatterImplementInt(uint8);
DMibStrStringFormatterImplementInt(int8);
DMibStrStringFormatterImplementInt(uint16);
DMibStrStringFormatterImplementInt(int16);
DMibStrStringFormatterImplementInt(uint32);
DMibStrStringFormatterImplementInt(int32);
DMibStrStringFormatterImplementInt(uint64);
DMibStrStringFormatterImplementInt(int64);
DMibStrStringFormatterImplementInt(uint80);
DMibStrStringFormatterImplementInt(int80);
DMibStrStringFormatterImplementInt(uint128);
DMibStrStringFormatterImplementInt(int128);
DMibStrStringFormatterImplementInt(uint160);
DMibStrStringFormatterImplementInt(int160);
DMibStrStringFormatterImplementInt(uint256);
DMibStrStringFormatterImplementInt(int256);
DMibStrStringFormatterImplementInt(uint320);
DMibStrStringFormatterImplementInt(int320);
DMibStrStringFormatterImplementInt(uint512);
DMibStrStringFormatterImplementInt(int512);
DMibStrStringFormatterImplementInt(uint1024);
DMibStrStringFormatterImplementInt(int1024);
DMibStrStringFormatterImplementInt(uint2048);
DMibStrStringFormatterImplementInt(int2048);
DMibStrStringFormatterImplementInt(uint4096);
DMibStrStringFormatterImplementInt(int4096);
DMibStrStringFormatterImplementInt(uint8192);
DMibStrStringFormatterImplementInt(int8192);

#ifdef DMibPUniqueType_mint
DMibStrStringFormatterImplementInt(mint);
#endif
#ifdef DMibPUniqueType_smint
DMibStrStringFormatterImplementInt(smint);
#endif
#ifdef DMibPUniqueType_int
DMibStrStringFormatterImplementInt(int);
#endif
#ifdef DMibPUniqueType_uint
DMibStrStringFormatterImplementInt(unsigned int);
#endif
#ifdef DMibPUniqueType_aint
DMibStrStringFormatterImplementInt(aint);
#endif

#ifdef DMibPUniqueType_uaint
DMibStrStringFormatterImplementInt(uaint);
#endif


#ifdef DMibPUniqueType_ch8
DMibStrStringFormatterImplementInt(ch8);
#endif
#ifdef DMibPUniqueType_ch16
DMibStrStringFormatterImplementInt(ch16);
#endif
#ifdef DMibPUniqueType_ch32
DMibStrStringFormatterImplementInt(ch32);
#endif
