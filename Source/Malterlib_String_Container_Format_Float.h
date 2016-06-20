// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#if 1
namespace NMib
{
	namespace NStr
	{

		template <typename t_CFormatter, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		class TCStrFormatType_Float final : public TICStrFormatType<t_CFormatter>
		{
		public:

			typedef TICStrFormatType<t_CFormatter> CSuper;

			typedef CStrFormatTypeClassifier_Float CStrFormatTypeClassifier;

			typedef typename t_CFormatter::CTStrTraits CTStrTraits;
			typedef NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CFloatIn;
			enum
			{
				EMantissaBits = t_MantissaBits + 8,
				EMinExponentBits = TCHighestBitSet<int, EMantissaBits + (EMantissaBits - 1)>::mc_Value + 2,
				EExponentBits = (t_ExponentBits > EMinExponentBits ? t_ExponentBits : EMinExponentBits)
			};
//			typedef NMath::TCFloat<t_SignBits, EExponentBits, EMantissaBits, typename TCChooseType<EExponentBits == t_ExponentBits, t_CImplicitFloat, NMath::CNoImplicit>::CType, t_bDummyOptimize> CFloat;
			typedef CFloatIn CFloat;
			typedef typename CTStrTraits::CStrTraits::CChar CChar;
			typedef typename CFloat::CInteger CInteger;
			typedef typename CFloat::CUnsignedInteger CUnsignedInteger;
			typedef typename CSuper::CStrAggregate CStrAggregate;
			typedef typename CSuper::COptionsStatic COptionsStatic;
			typedef typename CSuper::CVisitor CVisitor;
			

			typedef CFloat CType;

			enum
			{
				mc_bNeedDelete = false
			};

			const CFloat &m_Value;
			inline_small TCStrFormatType_Float(const CFloatIn &_Value):
			m_Value(_Value)
			{
			}

			virtual void f_Delete()
			{
				this->~TCStrFormatType_Float();
			}

			
			typedef typename TICStrFormatType<t_CFormatter> :: COption COption;
			typedef typename TICStrFormatType<t_CFormatter> :: COptions COptions;

			class COptionsFloat : public COptions
			{
			public:
				enum EFloatFormat
				{
					EFloatFormat_Fixed,
					EFloatFormat_Exponent,
					EFloatFormat_ExponentLowerCase,
					EFloatFormat_Shortest,
					EFloatFormat_ShortestLowerCase,
				};

				uint32 m_bSign:1;
				uint32 m_FloatFormat:3;
				uint32 m_bShowInf:1;
				uint32 m_bShowNaN:1;
				uint32 m_bShowDenormalized:1;
				uint32 m_bFractionOnly:1;
				uint32 m_bAutoRemoveDigits:1;
				aint m_MinDigits;
				aint m_MaxDigits;
				aint m_MinDecimals;
				aint m_MaxDecimals;
				CChar m_ThousandSeparator;

				inline_medium COptionsFloat():
					COptions(COptionsStatic()), 
					m_bSign(false),
					m_FloatFormat(EFloatFormat_Fixed),
					m_bShowInf(1),
					m_bShowNaN(1),
					m_bShowDenormalized(0),
					m_bFractionOnly(0),
					m_bAutoRemoveDigits(1),
					m_MinDigits(-1),
					m_MaxDigits(-1),
					m_MinDecimals(-1),
					m_MaxDecimals(-1),
					m_ThousandSeparator(0)
				{
				}
			};

			/*
			unary +
			unary -

			*
			/
			%

			+
			-
			*/

			class CXprImplementation
			{
			public:
				inline_small static CFloat fs_DefaultValue()
				{
					return CFloat(fp32(0.0f));
				}

				inline_small static CFloat fs_Modulus(CFloat const &_Value, CFloat const &_Modulus)
				{
					return _Value.f_Mod(_Modulus);
				}
				
				inline_small static CFloat fs_BitwiseOr(CFloat const &_Left, CFloat const &_Right)
				{
					return _Left;
				}
				
				inline_small static CFloat fs_BitwiseAnd(CFloat const &_Left, CFloat const &_Right)
				{
					return _Left;
				}
				
				inline_small static CFloat fs_BitwiseXor(CFloat const &_Left, CFloat const &_Right)
				{
					return _Left;
				}
				
				inline_small static CFloat fs_BitwiseNot(CFloat const &_Right)
				{
					return _Right;
				}
				
				template <typename t_CData, typename t_CReturn, typename t_CTerm>
				inline_small static t_CReturn fs_StrToData(const t_CData *&_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
				{
					return fg_StrToFloatParseExact(_pStr, _FailValue, _pStrTerminators);
				}

				template <typename t_CArgument>
				inline_small static auto fs_GetArgumentValue(t_CArgument *_pArg) -> decltype(_pArg->f_Get_fp64())
				{
					return _pArg->f_Get_fp64();
				}

			};


			template <typename t_CData, typename t_CFormatType, typename t_COptions>
			inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, COption &_Option) const
			{
				switch (_Option.m_FormatTypes.m_Format1)
				{
				case 'F':
					{
						switch (_Option.m_FormatTypes.m_Format2)
						{
						case 'F':
							{
								const CChar *ToCompare = _Option.m_pDataStart;

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
								const CChar *ToCompare = _Option.m_pDataStart;

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
								const CChar *ToCompare = _Option.m_pDataStart;

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
								const CChar *ToCompare = _Option.m_pDataStart;

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
				ReturnDefault:
				return TICStrFormatType<t_CFormatter>::f_ParseOption(_Args, _Option);
			}
			template <typename t_COptions>
			static inline_small void fp_AddToStr(CStrAggregate &_String, aint &_CurrentStrLen, t_COptions &_Options, const CFloat &_Number) 
			{
				CFloat Number = _Number;
				bint bOptionsSign = _Options.m_bSign;
				aint SubStrStart = 0;
				if (Number.f_GetSignBits() != 0)
				{
					SubStrStart = 1;
					bOptionsSign = true;
					Number = -Number;
				}

				bint bRemoveDigits = _Options.m_bAutoRemoveDigits;
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
				CInteger DecimalDisplacementConstFloat = ((NMib::fg_Convert<CFloat>(aint(CFloat::EMantissaBits)) * CFloat::fs_Log10_2() - CFloat::fs_1())).f_ToInt();// (((CFloat::EStorageBits - 1) * 100) / 302) - 2;

				if (Number != CFloat::fs_0())
				{
					if (nDigits > 0 && NMib::fg_Convert<CInteger>(nDigits-1) < DecimalDisplacementConstFloat)
						DecimalDisplacementConstFloat = NMib::fg_Convert<CInteger>(nDigits - 1);
					else if (nDigits == -2)
						DecimalDisplacementConstFloat = ((NMib::fg_Convert<CFloat>(aint(CFloat::EStorageBits)) * CFloat::fs_Log10_2()).f_Floor() - CFloat::fs_1()).f_ToInt();// (((CFloat::EStorageBits - 1) * 100) / 302) - 2;

#if 1
					if (Number.f_IsInvalid())
					{
						DecimalDisplacementFloat = 0;
					}
					else
					{
						CFloat Logged = Number.f_Log10();
						DecimalDisplacementFloat = -(Logged.f_Floor().f_ToInt());
					}
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
					{
						DecimalDisplacementConstFloat = fg_Min(DecimalDisplacementConstFloat, NMib::fg_Convert<CInteger>(nDecimals) - DecimalDisplacementFloat);
					}

					if (((Exponent < 0) || Mantissa != 0))
					{
						CInteger TempDisplacement = DecimalDisplacementConstFloat + DecimalDisplacementFloat;
						
						// Do this in two stages to be able to multiply up denormalized numbers
						if (Number.f_IsDenormalized())
						{
							CInteger TempDisplacement2 = TempDisplacement >> 1;
							CFloat FloatFormat = (Number * NMib::fg_Convert<CFloat>(TempDisplacement2).f_Exp10());
							FloatFormat *= NMib::fg_Convert<CFloat>(TempDisplacement - TempDisplacement2).f_Exp10();
							FormatNumber = (FloatFormat).f_ToUnsignedIntRound();
						}
						else
						{
							CFloat FloatFormat = Number;
							if (1)
							{
								CFloat Pow = NMib::fg_Convert<CFloat>(TempDisplacement).f_Exp10();
								FloatFormat *= Pow;
							}
							else
							{
								for (CInteger i = TempDisplacement; i < 0; ++i)
									FloatFormat *= CFloat(fp32(0.1f));
								for (CInteger i = 0; i < TempDisplacement; ++i)
									FloatFormat *= CFloat(fp32(10.0f));
							}
							FormatNumber = (FloatFormat).f_ToUnsignedIntRound();
						}
					}
				}
				else
				{
					DecimalDisplacementFloat = 0;
					DecimalDisplacementConstFloat = 0;
				}

				aint DecimalDisplacementConst = NMib::fg_Convert<aint>(DecimalDisplacementConstFloat);
				aint DecimalDisplacement = NMib::fg_Convert<aint>((DecimalDisplacementConstFloat + DecimalDisplacementFloat) - DecimalDisplacementConst);

				{			
					// Make a temporary buffer that can 
					const CChar NumberCharAdd = '0';
					enum {NumTempChar = ((sizeof(FormatNumber) * 8) / 3) + 6};
					CChar TempStr[NumTempChar];
					CChar *pStrPlace = TempStr + NumTempChar - 1;

					//	*(pStrPlace--) = 0;
					if (FormatNumber != 0)
					{
						while (FormatNumber != 0)
						{
							CChar InterNum = NMib::fg_Convert<CChar>(FormatNumber % 10);
							*(pStrPlace--) = NumberCharAdd + InterNum;

							FormatNumber /= 10;
						}		
					}
					else
					{
						*(pStrPlace--) = '0';
					}


					aint nRemoved = 0;
					if (bRemoveDigits && Number != CFloat::fs_0())
					{
						// Automaticly remove digits not needed

						CChar *pZero = TempStr + NumTempChar - 1;

						while (pZero != pStrPlace && *pZero == '0')
						{
							--pZero;
							--DecimalDisplacementConst;
							nRemoved++;
						}
					}

					aint NumberSize = aint(NumTempChar) - ((pStrPlace - TempStr) + 1) - nRemoved;
					aint DecimalPlacement = NumberSize - (DecimalDisplacement + DecimalDisplacementConst);

					enum {RealExpontentBits = CFloat::EExponentBits > 16 ? 16 : CFloat::EExponentBits};
					enum {NumTempChar2 = (NumTempChar+4+(((1<<(RealExpontentBits-1))*100)/301) + 20)};
					enum {NumTempCharReal = NumTempChar2 > 1024 ? 1 : NumTempChar2};


					CChar *pAlloc = nullptr;
					CChar TempStr2[NumTempCharReal];
					CChar *pTemp;
					aint nMaxDecimals = fg_Max(nDecimals, _Options.m_MinDecimals);
					if (nMaxDecimals - (NumberSize - DecimalPlacement) > 12)
						pAlloc = pTemp = DMibNew CChar[NumTempChar2 + (nMaxDecimals - (NumberSize - DecimalPlacement) - 12)];
					else if (NumTempChar2 > 1024)
						pAlloc = pTemp = DMibNew CChar[NumTempChar2];
					else
						pTemp = TempStr2;

					CChar *pSourceStr = pStrPlace + 1;
					CChar *pDest = pTemp;


					if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_Shortest || _Options.m_FloatFormat == COptionsFloat::EFloatFormat_ShortestLowerCase)
					{
						if (DecimalPlacement < 0 || DecimalPlacement > (NumberSize+3))
						{
							_Options.m_FloatFormat -= 2;
						}
					}

					if (bOptionsSign)
					{
						if (SubStrStart)
						{
							*pDest = '-';
							++pDest;
						}
						else
						{
							*pDest = '+';
							++pDest;
						}
					}

					if (Number.f_IsNaN())
					{
						if (_Options.m_bShowNaN)
						{
							if (Number.f_IsQNaN())
							{
								*pDest = 'Q';++pDest;
								*pDest = 'N';++pDest;
								*pDest = 'a';++pDest;
								*pDest = 'N';++pDest;
							}
							else
							{
								*pDest = 'S';++pDest;
								*pDest = 'N';++pDest;
								*pDest = 'a';++pDest;
								*pDest = 'N';++pDest;
							}
						}
						else
						{
							*pDest = '0';++pDest;
							*pDest = '.';++pDest;
							*pDest = '0';++pDest;
						}
					}
					else if (Number.f_IsInfinity())
					{
						if (_Options.m_bShowInf)
						{
							*pDest = 'I';++pDest;
							*pDest = 'n';++pDest;
							*pDest = 'f';++pDest;
						}
						else
						{
							*pDest = '0';++pDest;
							*pDest = '.';++pDest;
							*pDest = '0';++pDest;
						}
					}
					else if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_Exponent || _Options.m_FloatFormat == COptionsFloat::EFloatFormat_ExponentLowerCase)
					{
						*pDest = pSourceStr[0];
						++pDest;

						if (NumberSize > 1)
						{
							*pDest = '.';++pDest;

							for (aint i = 1; i < NumberSize; ++i)
							{
								*pDest = pSourceStr[i];
								++pDest;
							}
							if (NumberSize == 0)
							{
								*pDest = '0';++pDest;
							}
						}
						if (_Options.m_FloatFormat == COptionsFloat::EFloatFormat_ExponentLowerCase)
						{
							*pDest = 'e';++pDest;
						}
						else
						{
							*pDest = 'E';++pDest;
						}

						CInteger Exponent10 = DecimalPlacement - 1;

						if (Exponent10 != 0)
						{
							bint bSigned = false;
							bint bSign = bOptionsSign;
							if (Exponent10 < 0)
							{
								bSign = true;
								bSigned = true;
								Exponent10 = -Exponent10;
							}

							CChar *pStrPlace = TempStr + NumTempChar - 1;
							while (Exponent10 != 0)
							{
								CChar InterNum = fg_Convert<CChar>(Exponent10 % 10);
								*(pStrPlace--) = NumberCharAdd + InterNum;

								Exponent10 /= 10;
							}		
							
							if (bSign)
							{
								if (bSigned)
									*(pStrPlace--) = '-';
								else
									*(pStrPlace--) = '+';
							}

							aint NumberSize = NumTempChar - ((pStrPlace - TempStr) + 1);

							CChar *pSourceStr = pStrPlace + 1;
							for (aint i = 0; i < NumberSize; ++i)
							{
								*pDest = pSourceStr[i];
								++pDest;
							}

						}
						else
						{
							*pDest = '0'; ++pDest;
						}
					}
					else
					{
						if (DecimalPlacement > NumberSize)
						{
							for (aint i = 0; i < NumberSize; ++i)
							{
								*pDest = pSourceStr[i];
								++pDest;
							}
							for (aint i = NumberSize; i < DecimalPlacement; ++i)
							{
								*pDest = '0';++pDest;
							}

							if (_Options.m_MinDecimals > 0)
							{
								*pDest = '.';++pDest;
								for (aint i = 0; i < _Options.m_MinDecimals; ++i)
								{
									*pDest = '0';++pDest;
								}
							}
							else if (_Options.m_MinDigits > 0)
							{
								if (_Options.m_MinDigits > DecimalPlacement)
								{
									*pDest = '.';++pDest;
									for (aint i = DecimalPlacement; i < _Options.m_MinDigits; ++i)
									{
										*pDest = '0';++pDest;
									}
								}
							}
							else if (_Options.m_MinDecimals < 0 && _Options.m_MinDigits < 0)
							{
								*pDest = '.';++pDest;
								*pDest = '0';++pDest;
							}
						}
						else if (DecimalPlacement < 0)
						{
							*pDest = '0';++pDest;
							if (NumberSize == 0) // Can only happen with Min decimals >= 0
							{
								if (_Options.m_MinDecimals > 0)
								{
									*pDest = '.';++pDest;
									for (aint i = 0; i < _Options.m_MinDecimals; ++i)
									{
										*pDest = '0';++pDest;
									}
								}
							}
							else
							{
								*pDest = '.';++pDest;
								for (aint i = DecimalPlacement; i < 0; ++i)
								{
									*pDest = '0';++pDest;
								}
								for (aint i = 0; i < NumberSize; ++i)
								{
									*pDest = pSourceStr[i];
									++pDest;
								}

								if (_Options.m_MinDecimals >= 0)
								{
									for (aint i = NumberSize - DecimalPlacement; i < _Options.m_MinDecimals; ++i)
									{
										*pDest = '0';++pDest;
									}
								}
								else if (_Options.m_MinDigits >= 0)
								{
									for (aint i = NumberSize; i < _Options.m_MinDigits; ++i)
									{
										*pDest = '0';++pDest;
									}
								}
							}
						}
						else
						{
							for (aint i = 0; i < DecimalPlacement; ++i)
							{
								*pDest = pSourceStr[i];
								++pDest;
							}
							if (DecimalPlacement == 0)
							{
								*pDest = '0';++pDest;
							}
							if (_Options.m_MinDecimals > 0)
							{
								*pDest = '.';++pDest;
								for (aint i= DecimalPlacement; i < NumberSize; ++i)
								{
									*pDest = pSourceStr[i];
									++pDest;
								}
								for (aint i= NumberSize - DecimalPlacement; i < _Options.m_MinDecimals; ++i)
								{
									*pDest = '0';++pDest;
								}
							}
							else if (_Options.m_MinDigits> 0)
							{
								if (NumberSize > DecimalPlacement || _Options.m_MinDigits > NumberSize)
								{
									*pDest = '.';++pDest;
									for (aint i= DecimalPlacement; i < NumberSize; ++i)
									{
										*pDest = pSourceStr[i];
										++pDest;
									}
									for (aint i = NumberSize; i < _Options.m_MinDigits; ++i)
									{
										*pDest = '0';++pDest;
									}
								}
							}
							else
							{
								if (DecimalPlacement == NumberSize)
								{
									 if (_Options.m_MinDecimals < 0 && _Options.m_MinDigits < 0)
									 {
										*pDest = '.';++pDest;
										*pDest = '0';++pDest;
									 }
								}
								else
								{
									*pDest = '.';++pDest;
									for (aint i = DecimalPlacement; i < NumberSize; ++i)
									{
										*pDest = pSourceStr[i];
										++pDest;
									}
								}
							}
						}

						if (_Options.m_bFractionOnly)
						{
							// Parse away fraction
							while (*pTemp && *pTemp != '.')
								++pTemp;
							if (*pTemp == '.')
								++pTemp;
						}

					}

					if (_Options.m_bShowDenormalized && Number.f_IsDenormalized())
					{
						*pDest = '#';++pDest;
						*pDest = 'd';++pDest;
						*pDest = 'e';++pDest;
						*pDest = 'n';++pDest;
						*pDest = 'o';++pDest;
						*pDest = 'r';++pDest;
						*pDest = 'm';++pDest;
					}

					if (_Options.m_bSimpleAlign)
						CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, pTemp, pDest-pTemp);
					else
						CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, pTemp, pDest-pTemp, SubStrStart);

					if (pAlloc)
						delete [] pAlloc;
				}
			}

			virtual void f_AddToStr(CStrAggregate &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const
			{
				COptionsFloat Options;

				CFloat Number = m_Value;

				if (_pFormat)
				{
					TICStrFormatType_ParseOptionsArgs<CFloat, TCStrFormatType_Float, COptionsFloat> Args(Number, *this, _String, _CurrentStrLen, Options, _ArgData);
					CSuper::fs_ParseOptions(Args, _pFormat);
				}

				fp_AddToStr(_String, _CurrentStrLen, Options, Number);
			}

			static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const CFloat &_Value)
			{
				COptionsFloat Options;
				fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
			}

			virtual aint f_Get_aint() const
			{
				return fg_Convert<aint>(m_Value.f_ToInt());
			}

			virtual fp32 f_Get_fp32() const
			{
				return fp32(m_Value);
			}

			virtual fp64 f_Get_fp64() const
			{
				return fp64(m_Value);
			}

			virtual void f_Visit(CVisitor &_Extractor) const
			{
				if (sizeof(m_Value) > sizeof(fp32))
					_Extractor(fp64(m_Value));
				else
					_Extractor(fp32(m_Value));
			}
		};			  

		template <typename t_CFormatter, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		class TCStringFormatter<t_CFormatter, NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> >
		{
		public:
			typedef NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CFloat;
			typedef TCStrFormatType_Float<t_CFormatter, t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CFormatType;
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CFloat const&_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};
#ifdef DMibPCanDo_fp32
		template <typename t_CFormatter>
		class TCStringFormatter<t_CFormatter, pfp32>
		{
		public:
			typedef typename TCStringFormatter<t_CFormatter, fp32>::CFormatType CFormatType;
			static auto fs_CreateFormat(t_CFormatter &_Formatter, pfp32 const &_Data) -> decltype(TCStringFormatter<t_CFormatter, fp32>::fs_CreateFormat(_Formatter, _Data))
			{
				return TCStringFormatter<t_CFormatter, fp32>::fs_CreateFormat(_Formatter, reinterpret_cast<fp32 const &>(_Data));
			}
		};
#endif
#ifdef DMibPCanDo_fp64
		template <typename t_CFormatter>
		class TCStringFormatter<t_CFormatter, pfp64>
		{
		public:
			typedef typename TCStringFormatter<t_CFormatter, fp64>::CFormatType CFormatType;
			static auto fs_CreateFormat(t_CFormatter &_Formatter, pfp64 const &_Data) -> decltype(TCStringFormatter<t_CFormatter, fp64>::fs_CreateFormat(_Formatter, _Data))
			{
				return TCStringFormatter<t_CFormatter, fp64>::fs_CreateFormat(_Formatter, reinterpret_cast<fp64 const &>(_Data));
			}
		};
#endif
#ifdef DMibPCanDo_fp128
		template <typename t_CFormatter>
		class TCStringFormatter<t_CFormatter, pfp128>
		{
		public:
			typedef typename TCStringFormatter<t_CFormatter, fp128>::CFormatType CFormatType;
			static auto fs_CreateFormat(t_CFormatter &_Formatter, pfp128 const &_Data) -> decltype(TCStringFormatter<t_CFormatter, fp128>::fs_CreateFormat(_Formatter, _Data))
			{
				return TCStringFormatter<t_CFormatter, fp128>::fs_CreateFormat(_Formatter,  reinterpret_cast<fp128 const &>(_Data));
			}
		};
#endif
	}
}

#endif
