// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
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
	inline_medium TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
	::COptionsFloat::COptionsFloat()
		: COptions(COptionsStatic())
	{
	}

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
	inline_small TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::TCStrFormatType_Float(CFloatIn const &_Value)
		: mp_Value(_Value)
	{
	}

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
	umint TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>::f_Destruct()
	{
		if constexpr (mc_bNeedDestruct)
			this->~TCStrFormatType_Float();
		return sizeof(*this);
	}

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
	void TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_Move(t_CFormatter &_Formatter)
	{
		DMibFastCheck(!t_bReference); // Not supported
		if constexpr (!t_bReference)
			_Formatter.template f_Alloc<TCStrFormatType_Float>(mp_Value);
	}

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
	inline_small auto TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::CXprImplementation::fs_DefaultValue() -> CFloat
	{
		return CFloat(fp32(0.0f));
	}

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
	inline_small auto TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::CXprImplementation::fs_Modulus(CFloat const &_Value, CFloat const &_Modulus) -> CFloat
	{
		return _Value.f_Mod(_Modulus);
	}

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
	inline_small auto TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::CXprImplementation::fs_BitwiseOr(CFloat const &_Left, CFloat const &_Right) -> CFloat
	{
		return _Left;
	}

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
	inline_small auto TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::CXprImplementation::fs_BitwiseAnd(CFloat const &_Left, CFloat const &_Right) -> CFloat
	{
		return _Left;
	}

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
	inline_small auto TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::CXprImplementation::fs_BitwiseXor(CFloat const &_Left, CFloat const &_Right) -> CFloat
	{
		return _Left;
	}

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
	inline_small auto TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::CXprImplementation::fs_BitwiseNot(CFloat const &_Right) -> CFloat
	{
		return _Right;
	}

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
	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	inline_small t_CReturn TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::CXprImplementation::fs_StrToData(t_CData const * &_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators)
	{
		return fg_StrToFloatParseExact(_pStr, _FailValue, _pStrTerminators);
	}

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
	template <typename t_CArgument>
	inline_small auto TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::CXprImplementation::fs_GetArgumentValue(t_CArgument *_pArg) -> decltype(_pArg->f_Get_fp64())
	{
		return _pArg->f_Get_fp64();
	}


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
	template <typename t_CData, typename t_CFormatType, typename t_COptions>
	inline_small aint TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, COption &_Option) const
	{
		switch (_Option.m_FormatTypes.m_Format1)
		{
		case 'F':
			{
				switch (_Option.m_FormatTypes.m_Format2)
				{
				case 'F':
					{
						CChar const *ToCompare = _Option.m_pDataStart;

						switch (*ToCompare)
						{
						case 'E':
							_Args.m_Options.m_FloatFormat = COptionsFloat::EFloatFormat_Exponent;
							break;
						case 'e':
							_Args.m_Options.m_FloatFormat = COptionsFloat::EFloatFormat_ExponentLowerCase;
							break;
						case 'S':
							_Args.m_Options.m_FloatFormat = COptionsFloat::EFloatFormat_Shortest;
							break;
						case 's':
							_Args.m_Options.m_FloatFormat = COptionsFloat::EFloatFormat_ShortestLowerCase;
							break;
						case 'F':
						case 'f':
							_Args.m_Options.m_FloatFormat = COptionsFloat::EFloatFormat_Fixed;
							break;
						default:
							goto ReturnDefault;
						}
					}
					break;
				case 'D':
					{
						CChar const *ToCompare = _Option.m_pDataStart;

						switch (fg_CharUpperCase(*ToCompare))
						{
						case 'B':
							_Args.m_Options.m_MinDigits = -2;
							break;
						case 'S':
							_Args.m_Options.m_MinDigits = -1;
							break;
						default:
							_Args.m_Options.m_MinDigits = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, aint(-1));
						}
					}

					break;
				case 'E':
					{
						_Args.m_Options.m_MinDecimals = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, aint(-1));
					}
					break;
				case 'M':
					{
						_Args.m_Options.m_MaxDigits = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, aint(-1));
					}
					break;
				case 'N':
					{
						_Args.m_Options.m_MaxDecimals = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, aint(-1));
					}
					break;
				case 'S':
					{
						CChar const *ToCompare = _Option.m_pDataStart;

						switch (fg_CharUpperCase(*ToCompare))
						{
						case 'I':
							_Args.m_Options.m_bShowInf = 1;
							break;
						case 'D':
							_Args.m_Options.m_bShowDenormalized = 1;
							break;
						case 'N':
							_Args.m_Options.m_bShowNaN = 1;
							break;
						default:
							goto ReturnDefault;
							break;
						}
					}
					break;
				case 'H':
					{
						CChar const *ToCompare = _Option.m_pDataStart;

						switch (fg_CharUpperCase(*ToCompare))
						{
						case 'I':
							_Args.m_Options.m_bShowInf = 0;
							break;
						case 'D':
							_Args.m_Options.m_bShowDenormalized = 0;
							break;
						case 'N':
							_Args.m_Options.m_bShowNaN = 0;
							break;
						default:
							goto ReturnDefault;
							break;
						}
					}
					break;
				case 'R':
					{
						_Args.m_Options.m_bFractionOnly = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, aint(0)) != 0;
					}
					break;
				case 'A':
					{
						_Args.m_Options.m_bAutoRemoveDigits = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, aint(0)) != 0;
					}
					break;
				default:
					goto ReturnDefault;
					break;
				}
				return true;
			}
			break;
		case 'N':
			{
				switch (_Option.m_FormatTypes.m_Format2)
				{
				case '+':
					_Args.m_Options.m_bSign = true;
					break;
				default:
					goto ReturnDefault;
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
		ReturnDefault:
		return TICStrFormatType<t_CFormatter>::f_ParseOption(_Args, _Option);
	}

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
	template <typename t_COptions>
	inline_small void TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
	::fp_AddToStr(CString &_String, aint &_CurrentStrLen, t_COptions &_Options, CFloat const &_Number)
	{
		CFloat Number = _Number;
		bool bOptionsSign = _Options.m_bSign;
		aint SubStrStart = 0;
		if (Number.f_GetSignBits() != 0)
		{
			SubStrStart = 1;
			bOptionsSign = true;
			Number = -Number;
		}

		bool bRemoveDigits = _Options.m_bAutoRemoveDigits;
		if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_Shortest || _Options.m_FloatFormat == COptionsFloat::EFloatFormat_ShortestLowerCase)
		{
			if (_Options.m_MinDigits > 0)
				_Options.m_MinDigits = -1;
			if (_Options.m_MinDecimals > 0)
				_Options.m_MinDecimals = -1;
		}

		if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_Exponent || _Options.m_FloatFormat == COptionsFloat::EFloatFormat_ExponentLowerCase)
		{
			if (_Options.m_MinDecimals > 0)
			{
				_Options.m_MinDigits = _Options.m_MinDecimals + 1;
				_Options.m_MinDecimals = -1;
			}
			if (_Options.m_MaxDecimals > 0)
			{
				_Options.m_MaxDigits = _Options.m_MinDecimals + 1;
				_Options.m_MaxDecimals = -1;
			}
		}

		CInteger Mantissa = Number.f_GetMantissa();
		CInteger Exponent = Number.f_GetExponent();

		CUnsignedInteger FormatNumber = 0;

		aint nDigits = _Options.m_MaxDigits;
		if (nDigits < 0)
			nDigits = _Options.m_MinDigits;
		aint nDecimals = _Options.m_MaxDecimals;
		if (nDecimals < 0)
			nDecimals = _Options.m_MinDecimals;

		CInteger DecimalDisplacementFloat = 0;
		CInteger DecimalDisplacementConstFloat = 0;

		if (!Number.f_IsInvalid() && Number != CFloat::fs_0())
		{
			DecimalDisplacementConstFloat = ((NMib::fg_Convert<CFloat>(aint(CFloat::mc_MantissaBits)) * CFloat::fs_Log10_2() - CFloat::fs_1())).f_ToInt();
			// (((CFloat::mc_StorageBits - 1) * 100) / 302) - 2;

			if (nDigits > 0 && NMib::fg_Convert<CInteger>(nDigits-1) < DecimalDisplacementConstFloat)
				DecimalDisplacementConstFloat = NMib::fg_Convert<CInteger>(nDigits - 1);
			else if (nDigits == -2)
			{
				DecimalDisplacementConstFloat = ((NMib::fg_Convert<CFloat>(aint(CFloat::mc_StorageBits)) * CFloat::fs_Log10_2()).f_Floor() - CFloat::fs_1()).f_ToInt();
				// (((CFloat::mc_StorageBits - 1) * 100) / 302) - 2;
			}
			else
			{
				DecimalDisplacementConstFloat = ((NMib::fg_Convert<CFloat>(aint(CFloat::mc_MantissaBits)) * CFloat::fs_Log10_2() - CFloat::fs_1())).f_ToInt();
				// (((CFloat::mc_StorageBits - 1) * 100) / 302) - 2;
			}

#if 1
			DecimalDisplacementFloat = -(Number.f_Log10().f_Floor().f_ToInt());
#elif 1
			CFloat Temp = Number;
			Temp.f_SetExponent(0);
			if (Number.f_IsDenormalized())
				Temp -= CFloat::fs_1();
			Temp = Temp.f_Log10();
			DecimalDisplacementFloat = (NMib::fg_Convert<CFloat>(-Exponent) * CFloat::fs_Log10_2() - Temp).f_ToIntRoundTowardZero();
#else
			DecimalDisplacementFloat = (NMib::fg_Convert<CFloat>(-Exponent) * CFloat::fs_Log10_2()).f_ToIntRoundTowardZero();
			CFloat TempFloat = (Number * NMib::fg_Convert<CFloat>(DecimalDisplacementFloat).f_Exp10());
			if (TempFloat >= NMib::fg_Convert<CFloat>(10))
				--DecimalDisplacementFloat;
#endif

			if (nDecimals >= 0 && DecimalDisplacementFloat + DecimalDisplacementConstFloat > NMib::fg_Convert<CInteger>(nDecimals))
				DecimalDisplacementConstFloat = fg_Min(DecimalDisplacementConstFloat, NMib::fg_Convert<CInteger>(nDecimals) - DecimalDisplacementFloat);

			if (((Exponent < 0) || Mantissa != 0))
			{
				CInteger TempDisplacement = DecimalDisplacementConstFloat + DecimalDisplacementFloat;
				// Do this in two stages to be able to multiply up denormalized numbers
				CFloat FloatFormat = Number;
#if 1
				CFloat Pow = NMib::fg_Convert<CFloat>(TempDisplacement).f_Exp10();
				if (!Pow.f_IsInfinity())
					FloatFormat *= Pow;
				else
				{
					CInteger DisplacementPerTime = TempDisplacement / 2;
					while (DisplacementPerTime != 0)
					{
						Pow = NMib::fg_Convert<CFloat>(DisplacementPerTime).f_Exp10();
						if (!Pow.f_IsInfinity())
							break;
						DisplacementPerTime /= 2;
					}
					auto Zero = CInteger(0);
					for (CInteger WholeDisplacement = TempDisplacement; WholeDisplacement > Zero;)
					{
						CInteger ThisTime = fg_Min(DisplacementPerTime, WholeDisplacement);
						FloatFormat *= NMib::fg_Convert<CFloat>(ThisTime).f_Exp10();
						WholeDisplacement -= ThisTime;
					}
				}
#else
				auto Zero = CInteger(0);
				for (CInteger i = TempDisplacement; i < Zero; ++i)
					FloatFormat *= CFloat(fp32(0.1f));
				for (CInteger i = 0; i < TempDisplacement; ++i)
					FloatFormat *= CFloat(fp32(10.0f));
#endif
				FormatNumber = (FloatFormat).f_ToUnsignedIntRound();
			}
		}

		aint DecimalDisplacementConst = NMib::fg_Convert<aint>(DecimalDisplacementConstFloat);
		aint DecimalDisplacement = NMib::fg_Convert<aint>((DecimalDisplacementConstFloat + DecimalDisplacementFloat) - DecimalDisplacementConst);

		if (DecimalDisplacement > 10000)
			_Options.m_FloatFormat = COptionsFloat::EFloatFormat_Exponent;

		{
			// Make a temporary buffer that can
			static constexpr CChar c_NumberCharAdd = '0';
			static constexpr umint c_NumTempChar =
				((fg_MaxConstexpr(sizeof(Exponent), sizeof(FormatNumber)) * 8) / 3) // Approximation of log10(2) * nBits
				+ 1 // +- Sign
			;
			CChar TempStr[c_NumTempChar];
			CChar *pStrPlace = TempStr + c_NumTempChar - 1;

			//	*(pStrPlace--) = 0;
			if (FormatNumber != 0)
			{
				while (FormatNumber != 0)
				{
					auto Modulu = FormatNumber % 10;
					FormatNumber /= 10;

					CChar InterNum = NMib::fg_Convert<CChar>(Modulu);
					*(pStrPlace--) = c_NumberCharAdd + InterNum;
				}
			}
			else
				*(pStrPlace--) = '0';

			aint nRemoved = 0;
			if (bRemoveDigits && Number != CFloat::fs_0())
			{
				// Automaticly remove digits not needed
				CChar *pZero = TempStr + c_NumTempChar - 1;
				while (pZero != pStrPlace && *pZero == '0')
				{
					--pZero;
					--DecimalDisplacementConst;
					nRemoved++;
				}
			}

			aint NumberSize = aint(c_NumTempChar) - ((pStrPlace - TempStr) + 1) - nRemoved;
			aint DecimalPlacement = NumberSize - (DecimalDisplacement + DecimalDisplacementConst);

			static constexpr umint c_nNeededCharacters =
				c_NumTempChar // The number
				+ (sizeof(Exponent) * 8) / 3
				+ 32 // Extra space
			;

			static constexpr umint c_NumTempChar2 = c_nNeededCharacters;
			static constexpr umint c_NumTempCharReal = c_NumTempChar2 > 1024 ? 1 : c_NumTempChar2;

			if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_Shortest || _Options.m_FloatFormat == COptionsFloat::EFloatFormat_ShortestLowerCase)
			{
				if (DecimalPlacement < 0 || DecimalPlacement > (NumberSize+3))
					_Options.m_FloatFormat -= 2;
			}

			umint nRealNeeded = 0;
			{
				if (bOptionsSign)
					nRealNeeded += 1;

				if (Number.f_IsNan())
					nRealNeeded += 4;
				else if (Number.f_IsInfinity())
					nRealNeeded += 3;
				else if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_Exponent || _Options.m_FloatFormat == COptionsFloat::EFloatFormat_ExponentLowerCase)
				{
					nRealNeeded += NumberSize;
					nRealNeeded += 1; // .
					nRealNeeded += 1; // e/E

					CInteger Exponent10 = DecimalPlacement - 1;

					if (Exponent10 != 0)
					{
						nRealNeeded += ((sizeof(Exponent) * 8) / 3); // Approximation of log10(2) * nBits
						nRealNeeded += 1; // +/-
					}
					else
						nRealNeeded += 1; // 0
				}
				else
				{
					if (DecimalPlacement > NumberSize)
					{
						nRealNeeded += fg_Max(NumberSize, DecimalPlacement);

						if (_Options.m_MinDecimals > 0)
						{
							nRealNeeded += 1; // .
							nRealNeeded += _Options.m_MinDecimals;
						}
						else if (_Options.m_MinDigits > 0)
						{
							if (_Options.m_MinDigits > DecimalPlacement)
							{
								nRealNeeded += 1; // .
								nRealNeeded += _Options.m_MinDigits - DecimalPlacement;
							}
						}
						else if (_Options.m_MinDecimals < 0 && _Options.m_MinDigits < 0)
							nRealNeeded += 2; // .0
					}
					else if (DecimalPlacement < 0)
					{
						nRealNeeded += 1; // 0
						if (NumberSize == 0) // Can only happen with Min decimals >= 0
						{
							if (_Options.m_MinDecimals > 0)
							{
								nRealNeeded += 1; // .
								nRealNeeded += _Options.m_MinDecimals;
							}
						}
						else
						{
							nRealNeeded += 1; // .
							nRealNeeded += -DecimalPlacement;
							nRealNeeded += NumberSize;

							if (_Options.m_MinDecimals >= 0)
							{
								if (_Options.m_MinDecimals > (NumberSize - DecimalPlacement))
									nRealNeeded += _Options.m_MinDecimals - (NumberSize - DecimalPlacement);
							}
							else if (_Options.m_MinDigits >= 0)
							{
								if (_Options.m_MinDigits > NumberSize)
									nRealNeeded += _Options.m_MinDigits - NumberSize;
							}
						}
					}
					else
					{
						nRealNeeded += fg_Max(DecimalPlacement, 1);
						if (_Options.m_MinDecimals > 0)
						{
							nRealNeeded += 1;
							if (NumberSize > DecimalPlacement)
								nRealNeeded += NumberSize - DecimalPlacement;
							if (_Options.m_MinDecimals > (NumberSize - DecimalPlacement))
								nRealNeeded += _Options.m_MinDecimals - (NumberSize - DecimalPlacement);
						}
						else if (_Options.m_MinDigits > 0)
						{
							if (NumberSize > DecimalPlacement || _Options.m_MinDigits > NumberSize)
							{
								nRealNeeded += 1; // .
								if (NumberSize > DecimalPlacement)
									nRealNeeded += NumberSize - DecimalPlacement;
								if (_Options.m_MinDigits > NumberSize)
									nRealNeeded += _Options.m_MinDigits - NumberSize;
							}
						}
						else
						{
							if (DecimalPlacement == NumberSize)
							{
									if (_Options.m_MinDecimals < 0 && _Options.m_MinDigits < 0)
									nRealNeeded += 2; // .0
							}
							else
							{
								nRealNeeded += 1; // .
								if (NumberSize > DecimalPlacement)
									nRealNeeded += NumberSize - DecimalPlacement;
							}
						}
					}
				}

				if (_Options.m_bShowDenormalized && Number.f_IsDenormalized())
					nRealNeeded += 7; // #denorm
			}


			CChar *pAlloc = nullptr;
			CChar TempStr2[c_NumTempCharReal];
			CChar *pDestStart;
			umint nDest = c_NumTempCharReal;
			if (nRealNeeded > c_NumTempCharReal)
			{
				nDest = nRealNeeded;
				pAlloc = pDestStart = DMibNew CChar[nRealNeeded];
			}
			else
				pDestStart = TempStr2;

			auto Cleanup = g_OnScopeExit / [&]
				{
					if (pAlloc)
						delete [] pAlloc;
				}
			;

			CChar * const pDestStartConst = pDestStart;

			CChar *pSourceStr = pStrPlace + 1;
			CChar *pDest = pDestStart;
			CChar *pDestEnd = pDest + nDest;
			(void)pDestEnd;

			auto fOutput = [&](CChar _Chararter)
				{
					DMibFastCheck(pDest < pDestEnd);
					*pDest = _Chararter;
					++pDest;
				}
			;

			if (bOptionsSign)
			{
				if (SubStrStart)
					fOutput('-');
				else
					fOutput('+');
			}

			if (Number.f_IsNan())
			{
				if (_Options.m_bShowNaN)
				{
					if (Number.f_IsQNan())
					{
						fOutput('Q');
						fOutput('N');
						fOutput('a');
						fOutput('N');
					}
					else
					{
						fOutput('S');
						fOutput('N');
						fOutput('a');
						fOutput('N');
					}
				}
				else
				{
					fOutput('0');
					fOutput('.');
					fOutput('0');
				}
			}
			else if (Number.f_IsInfinity())
			{
				if (_Options.m_bShowInf)
				{
					fOutput('I');
					fOutput('n');
					fOutput('f');
				}
				else
				{
					fOutput('0');
					fOutput('.');
					fOutput('0');
				}
			}
			else if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_Exponent || _Options.m_FloatFormat == COptionsFloat::EFloatFormat_ExponentLowerCase)
			{
				fOutput(pSourceStr[0]);

				if (NumberSize > 1)
				{
					fOutput('.');

					for (aint i = 1; i < NumberSize; ++i)
						fOutput(pSourceStr[i]);
					if (NumberSize == 0)
						fOutput('0');
				}
				if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_ExponentLowerCase)
					fOutput('e');
				else
					fOutput('E');

				CInteger Exponent10 = DecimalPlacement - 1;

				if (Exponent10 != 0)
				{
					bool bSigned = false;
					bool bSign = bOptionsSign;
					if (Exponent10 < 0)
					{
						bSign = true;
						bSigned = true;
						Exponent10 = -Exponent10;
					}

					CChar *pStrPlace = TempStr + c_NumTempChar - 1;
					while (Exponent10 != 0)
					{
						CChar InterNum = fg_Convert<CChar>(Exponent10 % 10);
						*(pStrPlace--) = c_NumberCharAdd + InterNum;

						Exponent10 /= 10;
					}

					if (bSign)
					{
						if (bSigned)
							*(pStrPlace--) = '-';
						else
							*(pStrPlace--) = '+';
					}

					aint NumberSize = c_NumTempChar - ((pStrPlace - TempStr) + 1);

					CChar *pSourceStr = pStrPlace + 1;
					for (aint i = 0; i < NumberSize; ++i)
						fOutput(pSourceStr[i]);
				}
				else
				{
					fOutput('0');
				}
			}
			else
			{
				if (DecimalPlacement > NumberSize)
				{
					for (aint i = 0; i < NumberSize; ++i)
						fOutput(pSourceStr[i]);
					for (aint i = NumberSize; i < DecimalPlacement; ++i)
						fOutput('0');

					if (_Options.m_MinDecimals > 0)
					{
						fOutput('.');
						for (aint i = 0; i < _Options.m_MinDecimals; ++i)
							fOutput('0');
					}
					else if (_Options.m_MinDigits > 0)
					{
						if (_Options.m_MinDigits > DecimalPlacement)
						{
							fOutput('.');
							for (aint i = DecimalPlacement; i < _Options.m_MinDigits; ++i)
								fOutput('0');
						}
					}
					else if (_Options.m_MinDecimals < 0 && _Options.m_MinDigits < 0)
					{
						fOutput('.');
						fOutput('0');
					}
				}
				else if (DecimalPlacement < 0)
				{
					fOutput('0');
					if (NumberSize == 0) // Can only happen with Min decimals >= 0
					{
						if (_Options.m_MinDecimals > 0)
						{
							fOutput('.');
							for (aint i = 0; i < _Options.m_MinDecimals; ++i)
								fOutput('0');
						}
					}
					else
					{
						fOutput('.');
						for (aint i = DecimalPlacement; i < 0; ++i)
							fOutput('0');
						for (aint i = 0; i < NumberSize; ++i)
							fOutput(pSourceStr[i]);

						if (_Options.m_MinDecimals >= 0)
						{
							for (aint i = NumberSize - DecimalPlacement; i < _Options.m_MinDecimals; ++i)
								fOutput('0');
						}
						else if (_Options.m_MinDigits >= 0)
						{
							for (aint i = NumberSize; i < _Options.m_MinDigits; ++i)
								fOutput('0');
						}
					}
				}
				else
				{
					for (aint i = 0; i < DecimalPlacement; ++i)
						fOutput(pSourceStr[i]);
					if (DecimalPlacement == 0)
						fOutput('0');
					if (_Options.m_MinDecimals > 0)
					{
						fOutput('.');
						for (aint i= DecimalPlacement; i < NumberSize; ++i)
							fOutput(pSourceStr[i]);
						for (aint i= NumberSize - DecimalPlacement; i < _Options.m_MinDecimals; ++i)
							fOutput('0');
					}
					else if (_Options.m_MinDigits> 0)
					{
						if (NumberSize > DecimalPlacement || _Options.m_MinDigits > NumberSize)
						{
							fOutput('.');
							for (aint i= DecimalPlacement; i < NumberSize; ++i)
								fOutput(pSourceStr[i]);
							for (aint i = NumberSize; i < _Options.m_MinDigits; ++i)
								fOutput('0');
						}
					}
					else
					{
						if (DecimalPlacement == NumberSize)
						{
								if (_Options.m_MinDecimals < 0 && _Options.m_MinDigits < 0)
								{
								fOutput('.');
								fOutput('0');
								}
						}
						else
						{
							fOutput('.');
							for (aint i = DecimalPlacement; i < NumberSize; ++i)
								fOutput(pSourceStr[i]);
						}
					}
				}

				if (_Options.m_bFractionOnly)
				{
					// Parse away fraction
					while (*pDestStart && *pDestStart != '.')
						++pDestStart;
					if (*pDestStart == '.')
						++pDestStart;
				}

			}

			if (_Options.m_bShowDenormalized && Number.f_IsDenormalized())
			{
				fOutput('#');
				fOutput('d');
				fOutput('e');
				fOutput('n');
				fOutput('o');
				fOutput('r');
				fOutput('m');
			}
			umint nOutput = pDest - pDestStartConst;
			(void)nOutput;
			DMibFastCheck(nRealNeeded >= nOutput);

			if (_Options.m_bSimpleAlign)
				CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, pDestStart, pDest-pDestStart);
			else
				CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, pDestStart, pDest-pDestStart, SubStrStart);
		}
	}

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
	void TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_AddToStr(CString &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const
	{
		COptionsFloat Options;

		CFloat Number = mp_Value;

		if (_pFormat)
		{
			TICStrFormatType_ParseOptionsArgs<CFloat, TCStrFormatType_Float, COptionsFloat> Args(Number, *this, _String, _CurrentStrLen, Options, _ArgData);
			CSuper::fs_ParseOptions(Args, _pFormat);
		}

		fp_AddToStr(_String, _CurrentStrLen, Options, Number);
	}

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
	void TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::fs_AddToStrStatic(CString &_String, aint &_CurrentStrLen, CFloat const &_Value)
	{
		COptionsFloat Options;
		fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
	}

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
	void TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::fs_AddToStrStatic(CString &_String, aint &_CurrentStrLen, CFloat const &_Value, COptionsFloat &_Options)
	{
		fp_AddToStr(_String, _CurrentStrLen, _Options, _Value);
	}

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
	aint TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_Get_aint() const
	{
		return fg_Convert<aint>(mp_Value.f_ToInt());
	}

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
	fp32 TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_Get_fp32() const
	{
		return fp32(mp_Value);
	}

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
	fp64 TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_Get_fp64() const
	{
		return fp64(mp_Value);
	}

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
	void TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_Visit(CVisitor &_Extractor) const
	{
		if (sizeof(mp_Value) > sizeof(fp32))
			_Extractor(fp64(mp_Value));
		else
			_Extractor(fp32(mp_Value));
	}

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
	void const *TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_GetTypeID() const
	{
		return &mcp_TypeID;
	}

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
	bool TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage, t_bReference>
		::f_IsSame(void const *_pRight) const
	{
		auto pRight = static_cast<TCStrFormatType_Float const *>(_pRight);
		return mp_Value == pRight->mp_Value;
	}

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
	>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter
		<
			t_CFormatter
			, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>
		>::fs_CreateFormat(t_CFormatter &_Formatter, CFloat const&_Data) -> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(_Data);
		return typename CFormatType::CStrFormatTypeClassifier();
	}

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
	>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter
	<
		t_CFormatter
		, TCByValue<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
	>::fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<CFloat> const &_Data) -> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(*_Data);
		return typename CFormatType::CStrFormatTypeClassifier();
	}

#ifdef DMibPCanDo_fp32
	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, pfp32>::fs_CreateFormat(t_CFormatter &_Formatter, pfp32 const &_Data)
		-> decltype(TCStringFormatter<t_CFormatter, fp32>::template fs_CreateFormat<fp32>(_Formatter, _Data))
	{
		return TCStringFormatter<t_CFormatter, fp32>::template fs_CreateFormat<fp32>(_Formatter, reinterpret_cast<fp32 const &>(_Data));
	}

	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, TCByValue<pfp32>>::fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<pfp32> const &_Data)
	{
		return TCStringFormatter<t_CFormatter, TCByValue<fp32>>::template fs_CreateFormat<fp32>(_Formatter, reinterpret_cast<TCByValue<fp32> const &>(_Data));
	}
#endif
#ifdef DMibPCanDo_fp64
	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, pfp64>::fs_CreateFormat(t_CFormatter &_Formatter, pfp64 const &_Data)
		-> decltype(TCStringFormatter<t_CFormatter, fp64>::template fs_CreateFormat<fp64>(_Formatter, _Data))
	{
		return TCStringFormatter<t_CFormatter, fp64>::template fs_CreateFormat<fp64>(_Formatter, reinterpret_cast<fp64 const &>(_Data));
	}

	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, TCByValue<pfp64>>::fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<pfp64> const &_Data)
	{
		return TCStringFormatter<t_CFormatter, TCByValue<fp64>>::template fs_CreateFormat<fp64>(_Formatter, reinterpret_cast<TCByValue<fp64> const &>(_Data));
	}
#endif
#ifdef DMibPCanDo_fp80
	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, pfp80>::fs_CreateFormat(t_CFormatter &_Formatter, pfp80 const &_Data)
		-> decltype(TCStringFormatter<t_CFormatter, fp80>::template fs_CreateFormat<fp80>(_Formatter, _Data))
	{
		return TCStringFormatter<t_CFormatter, fp80>::template fs_CreateFormat<fp80>(_Formatter, reinterpret_cast<fp80 const &>(_Data));
	}

	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, TCByValue<pfp80>>::fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<pfp80> const &_Data)
	{
		return TCStringFormatter<t_CFormatter, TCByValue<fp80>>::template fs_CreateFormat<fp80>(_Formatter, reinterpret_cast<TCByValue<fp80> const &>(_Data));
	}
#endif
#ifdef DMibPCanDo_fp128
	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, pfp128>::fs_CreateFormat(t_CFormatter &_Formatter, pfp128 const &_Data)
		-> decltype(TCStringFormatter<t_CFormatter, fp128>::template fs_CreateFormat<fp128>(_Formatter, _Data))
	{
		return TCStringFormatter<t_CFormatter, fp128>::template fs_CreateFormat<fp128>(_Formatter,  reinterpret_cast<fp128 const &>(_Data));
	}

	template <typename t_CFormatter>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, TCByValue<pfp128>>::fs_CreateFormat(t_CFormatter &_Formatter, pfp128 const &_Data)
	{
		return TCStringFormatter<t_CFormatter, TCByValue<fp128>>::template fs_CreateFormat<fp128>(_Formatter,  reinterpret_cast<TCByValue<fp128> const &>(_Data));
	}
#endif
}
