// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NStr
	{

		template <typename t_CFormatter, typename t_CStrTraitsIn, bint t_bReference>
		class TCStrFormatType_TStr : public TICStrFormatType<t_CFormatter>
		{
		public:

			typedef CStrFormatTypeClassifier_String CStrFormatTypeClassifier;

			virtual void f_Delete()
			{
				this->~TCStrFormatType_TStr();
			}

			typedef typename t_CFormatter::CTStrTraits CTStrTraits;
			typedef typename CTStrTraits::CStrTraits::CChar CChar;

			typedef typename TCChooseType<t_bReference, const TCStrAggregate<t_CStrTraitsIn> &, TCStr<t_CStrTraitsIn>>::CType CStorageType;
			typedef typename TCChooseType<t_bReference, const TCStrAggregate<t_CStrTraitsIn> &, const TCStr<t_CStrTraitsIn> &>::CType CReferenceType;

			enum
			{
				mc_bNeedDelete = !t_bReference
			};

			CStorageType m_TStr;

			typedef const TCStrAggregate<t_CStrTraitsIn> & CType;
			typedef typename t_CStrTraitsIn::CStrTraits::CChar CCharIn;

			inline_small TCStrFormatType_TStr(const TCStrAggregate<t_CStrTraitsIn> &_Str)
				: m_TStr(_Str)
			{
			}

			inline_small TCStrFormatType_TStr(const TCStrAggregate<t_CStrTraitsIn> *_pStr)
				: m_TStr(*_pStr)
			{
			}

			typedef TICStrFormatType<t_CFormatter> CSuper;
			typedef typename CSuper::COption COption;
			typedef typename CSuper::COptions COptions;
			typedef typename CSuper::COptionsStatic COptionsStatic;
			typedef typename CSuper::CVisitor CVisitor;
			
			class COptionsStr : public COptions
			{
			public:
				enum ECase
				{
					 ECase_Default = 0
					,ECase_Upper
					,ECase_Lower
					,ECase_Capitalize
					,ECase_Decapitalize
				};

				aint m_Case;

				inline_small COptionsStr():
				COptions(COptionsStatic()),
				m_Case(ECase_Default)
				{
				}

			};

			template <typename t_CData, typename t_CFormatType, typename t_COptions>
			inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, COption &_Option) const
			{
				switch (_Option.m_FormatTypes.m_Format1)
				{
				case 'C':
					{
						switch (_Option.m_FormatTypes.m_Format2)
						{
						case 'U':
							_Args.m_Options.m_Case = COptionsStr::ECase_Upper;
							break;
						case 'L':
							_Args.m_Options.m_Case = COptionsStr::ECase_Lower;
							break;
						case 'C':
							_Args.m_Options.m_Case = COptionsStr::ECase_Capitalize;
							break;
						case 'D':
							_Args.m_Options.m_Case = COptionsStr::ECase_Decapitalize;
							break;
						default:
							return CSuper::f_ParseOption(_Args, _Option);
							break;
						}
						return true;
					}
					break;
				}
				return CSuper::f_ParseOption(_Args, _Option);
			}

			virtual void f_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const
			{
				COptionsStr Options;

				if (_pFormat)
				{
					TICStrFormatType_ParseOptionsArgs<CReferenceType, TCStrFormatType_TStr, COptionsStr> Args(m_TStr, *this, _String, _CurrentStrLen, Options, _ArgData);
					CSuper::fs_ParseOptions(Args, _pFormat);
				}
				fp_AddToStr(_String, _CurrentStrLen, Options, m_TStr);
			}
			static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const TCStrAggregate<t_CStrTraitsIn> &_Value)
			{
				COptionsStr Options;
				fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
			}

			template <typename t_COptions>
			static inline_small void fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, const TCStrAggregate<CTStrTraits> &_Value)
			{
				DMibSafeCheck(reinterpret_cast<void const*>(&_String) != reinterpret_cast<void const*>(&_Value), "You cannot assign a format to string that is used by reference as an argument.");

				mint TempLen = _Value.f_GetLen();

				if (_Options.m_Case &&  TempLen > 0)
				{
					if (_String.mc_Type == EStrType_Unicode || _String.mc_Type == EStrType_Ansi)
					{
						auto fAddStr = [&](CChar *_pTemp)
							{
								switch (_Options.m_Case)
								{
								case COptionsStr::ECase_Upper:
									CTStrTraits::CStrTraits::fs_StrUpperCase(_pTemp, _Value.f_GetStr(), TempLen);
									break;
								case COptionsStr::ECase_Lower:
									CTStrTraits::CStrTraits::fs_StrLowerCase(_pTemp, _Value.f_GetStr(), TempLen);
									break;
								case COptionsStr::ECase_Capitalize:
									CTStrTraits::CStrTraits::fs_StrUpperCase(_pTemp, _Value.f_GetStr(), 1);
									NMem::fg_ObjectCopy(_pTemp+1, _Value.f_GetStr()+1, TempLen-1);
									break;
								case COptionsStr::ECase_Decapitalize:
									CTStrTraits::CStrTraits::fs_StrLowerCase(_pTemp, _Value.f_GetStr(), 1);
									NMem::fg_ObjectCopy(_pTemp+1, _Value.f_GetStr()+1, TempLen-1);
									break;
								default:
									DMibSafeCheck(0,"Case is wrong");
									break;
								}
								if (_Options.m_bSimpleAlign)
									CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, _pTemp, TempLen);
								else
									CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, _pTemp, TempLen, 0);
							}
						;
						
						if ((TempLen + 1) < (512 / sizeof(CChar)))
						{
							CChar TempStr[512 / sizeof(CChar)];
							fAddStr(TempStr);
						}
						else
						{
							mint AllocLen = sizeof(CChar) * (TempLen + 1);
							CChar *pTempStr = (CChar *)CTStrTraits::CStrTraits::CAllocator::f_Alloc(AllocLen);

							if (!pTempStr)
								return;

							fAddStr(pTempStr);
							CTStrTraits::CStrTraits::CAllocator::f_Free(pTempStr);
						}
					}
					else
					{
						// TODO: Support for UTF with new string algorithm
						
						typedef TCStr
							<
								typename TCStrTraits_ReplaceParams<ch32
								, EStrType_Unicode
								, TCStrAggregate<t_CStrTraitsIn>::CTraits::CStrTraits::mc_Type
								, typename TCStrAggregate<t_CStrTraitsIn>::CImp
								, typename TCStrAggregate<t_CStrTraitsIn>::CTraits::CStrTraits::CParams>::CType
							> CUnicodeStr
						;
						
						CUnicodeStr UnicodeStr = _Value;
						
						switch (_Options.m_Case)
						{
						case COptionsStr::ECase_Upper:
							UnicodeStr = UnicodeStr.f_UpperCase();
							break;
						case COptionsStr::ECase_Lower:
							UnicodeStr = UnicodeStr.f_LowerCase();
							break;
						case COptionsStr::ECase_Capitalize:
							UnicodeStr[0] = CTStrTraits::CStrTraits::fs_CharUpperCase(UnicodeStr[0]);
							break;
						case COptionsStr::ECase_Decapitalize:
							UnicodeStr[0] = CTStrTraits::CStrTraits::fs_CharLowerCase(UnicodeStr[0]);
							break;
						default:
							DMibSafeCheck(0,"Case is wrong");
							break;
						}
						
						TCStr<CTStrTraits> ProcessedStr = UnicodeStr;
						
						if (_Options.m_bSimpleAlign)
							CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, ProcessedStr.f_GetStr(), ProcessedStr.f_GetLen());
						else
							CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, ProcessedStr.f_GetStr(), ProcessedStr.f_GetLen(), 0);
					}
				}
				else
				{
					if (_Options.m_bSimpleAlign)
						CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, _Value.f_GetStr(), TempLen);
					else
						CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, _Value.f_GetStr(), TempLen, 0);
				}
			}
			
			template <typename t_COptions, typename tf_CStrTraitsIn>
			static inline_small void fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, const TCStrAggregate<tf_CStrTraitsIn> &_Value)
			{
				TCStr<CTStrTraits> Value(_Value);
				fp_AddToStr(_String, _CurrentStrLen, _Options, Value);
			}

			virtual aint f_Get_aint() const
			{
				return CTStrTraits::CStrTraits::fs_StrToInt(m_TStr.f_GetStr(), (aint)0);
			}

			virtual fp32 f_Get_fp32() const
			{
				return CTStrTraits::CStrTraits::fs_StrToFloatExact(m_TStr.f_GetStr(), (fp32)0);
			}

			virtual fp64 f_Get_fp64() const
			{
				return CTStrTraits::CStrTraits::fs_StrToFloatExact(m_TStr.f_GetStr(), (fp64)0);
			}

			virtual void f_Visit(CVisitor &_Extractor) const
			{
				if (sizeof(CCharIn) == sizeof(CChar))
				{
					_Extractor((CChar const *)(m_TStr.f_GetStr()));
				}
				else
				{
					TCStr<CTStrTraits> Temp = m_TStr;

					_Extractor(Temp.f_GetStr());
				}
			}
		};			  

		
		template <typename t_CFormatter, typename t_CStrTraitsIn>
		class TCStringFormatter<t_CFormatter, TCStrAggregate<t_CStrTraitsIn> >
		{
		public:
			typedef TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, true> CFormatType;
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCStrAggregate<t_CStrTraitsIn> const&_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

		template <typename t_CFormatter, typename t_CStrTraitsIn>
		class TCStringFormatter<t_CFormatter, TCStr<t_CStrTraitsIn> >
		{
		public:
			typedef TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, true> CFormatType;
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCStr<t_CStrTraitsIn> const&_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

		
		template <typename t_CFormatter, typename t_CStrTraitsIn>
		class TCStringFormatter<t_CFormatter, TCByValue<TCStrAggregate<t_CStrTraitsIn>> >
		{
		public:
			typedef TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, false> CFormatType;
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat
			(
				t_CFormatter &_Formatter
				, TCByValue<TCStrAggregate<t_CStrTraitsIn>> const&_Data
			)
			{
				_Formatter.template f_Alloc<CFormatType>(*_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

		template <typename t_CFormatter, typename t_CStrTraitsIn>
		class TCStringFormatter<t_CFormatter, TCByValue<TCStr<t_CStrTraitsIn>> >
		{
		public:
			typedef TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, false> CFormatType;
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat
			(
				t_CFormatter &_Formatter, TCByValue<TCStr<t_CStrTraitsIn>> const&_Data
			)
			{
				_Formatter.template f_Alloc<CFormatType>(*_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

	}
}

