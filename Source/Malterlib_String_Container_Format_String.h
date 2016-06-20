// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NStr
	{
		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| 
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <typename t_CFormatter, typename t_CStrDataType, CStrTypeUnderlaying t_Type>
		class TCStrFormatType_String final : public TICStrFormatType<t_CFormatter>
		{
		public:
			static_assert(t_Type != EStrType_Ansi, "");

			typedef CStrFormatTypeClassifier_String CStrFormatTypeClassifier;

			virtual void f_Delete()
			{
				this->~TCStrFormatType_String();
			}

			typedef typename t_CFormatter::CTStrTraits CTStrTraits;
			typedef typename CTStrTraits::CStrTraits::CChar CChar;

			enum
			{
				mc_bNeedDelete = false
			};

			t_CStrDataType const *m_pStr;
			mint m_StrLen;

			inline_medium TCStrFormatType_String(t_CStrDataType const *_pStr)
				: m_pStr(_pStr)
				, m_StrLen(_pStr ? CTStrTraits::CStrTraits::fs_StrLen(_pStr) : 0)
			{
			}

			inline_small TCStrFormatType_String(t_CStrDataType const *_pStr, aint _StrLen)
				: m_pStr(_pStr)
				, m_StrLen(_StrLen)
			{
			}

			typedef t_CStrDataType const *CType;

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
					, ECase_Upper
					, ECase_Lower
					, ECase_Capitalize
					, ECase_Decapitalize
				};

				aint m_Case;

				inline_small COptionsStr()
					: COptions(COptionsStatic())
					, m_Case(ECase_Default)
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

			virtual void f_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const
			{
				COptionsStr Options;

				if (_pFormat)
				{
					typedef decltype((m_pStr)) CStrType;
					TICStrFormatType_ParseOptionsArgs<CStrType, TCStrFormatType_String, COptionsStr> Args(m_pStr, *this, _String, _CurrentStrLen, Options, _ArgData);
					CSuper::fs_ParseOptions(Args, _pFormat);
				}
				fp_AddToStr<CTStrTraits::CStrTraits::mc_Type, t_Type>(_String, _CurrentStrLen, Options, m_pStr, m_StrLen);
			}

			static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_CStrDataType const *_pValue)
			{
				COptionsStr Options;
				fp_AddToStr<CTStrTraits::CStrTraits::mc_Type, t_Type>(_String, _CurrentStrLen, Options, _pValue, CTStrTraits::CStrTraits::fs_StrLen(_pValue));
			}

			template <CStrTypeUnderlaying tf_DestinationType, CStrTypeUnderlaying tf_SourceType, typename t_COptions>
			static inline_small typename TCEnableIf<tf_DestinationType == tf_SourceType, void>::CType fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, CChar const *_pValue, mint _StrLen)
			{
				if (_Options.m_Case)
				{
					auto fAddStr = [&](CChar *_pTemp)
						{
							switch (_Options.m_Case)
							{
							case COptionsStr::ECase_Upper:
								CTStrTraits::CStrTraits::fs_StrUpperCase(_pTemp, _pValue, _StrLen);
								break;
							case COptionsStr::ECase_Lower:
								CTStrTraits::CStrTraits::fs_StrLowerCase(_pTemp, _pValue, _StrLen);
								break;
							case COptionsStr::ECase_Capitalize:
								CTStrTraits::CStrTraits::fs_StrUpperCase(_pTemp, _pValue, 1);
								NMem::fg_ObjectCopy(_pTemp+1, _pValue+1, _StrLen-1);
								break;
							case COptionsStr::ECase_Decapitalize:
								CTStrTraits::CStrTraits::fs_StrLowerCase(_pTemp, _pValue, 1);
								NMem::fg_ObjectCopy(_pTemp+1, _pValue+1, _StrLen-1);
								break;
							default:
								DMibSafeCheck(0, "Case is wrong");
								break;
							}

							if (_Options.m_bSimpleAlign)
								CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, _pTemp, _StrLen);
							else
								CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, _pTemp, _StrLen, 0);
						}
					;
					if ((_StrLen + 1) < (512 / sizeof(CChar)))
					{
						CChar TempStr[512 / sizeof(CChar)];
						fAddStr(TempStr);
					}
					else
					{
						mint AllocLen = sizeof(CChar) * (_StrLen + 1);
						CChar *pTempStr = (CChar *)CTStrTraits::CStrTraits::CAllocator::f_Alloc(AllocLen);
						if (!pTempStr)
							return;
						fAddStr(pTempStr);
						CTStrTraits::CStrTraits::CAllocator::f_Free(pTempStr);
					}
				}
				else
				{
					if (_Options.m_bSimpleAlign)
						CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, _pValue, _StrLen);
					else
						CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, _pValue, _StrLen, 0);
				}
			}
			
			template <CStrTypeUnderlaying tf_DestinationType, CStrTypeUnderlaying tf_SourceType, typename t_COptions, typename tf_CStrDataType>
			static inline_small void fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, tf_CStrDataType const *_pValue, mint _StrLen)
			{
				TCStr<CTStrTraits> Converted;
				
				aint Size = 0;
				Converted.f_AddFromUnicodeIterator(Size, fg_GetUnicodeIterator(_pValue, _StrLen));
				Converted.f_SetStrLen(Size);
				
				fp_AddToStr<tf_DestinationType, tf_DestinationType>(_String, _CurrentStrLen, _Options, Converted.f_GetStr(), Converted.f_GetLen());
				
				//t_Type;
			}

			virtual aint f_Get_aint() const
			{
				return CTStrTraits::CStrTraits::fs_StrToInt(m_pStr, (aint)0);
			}

			virtual fp32 f_Get_fp32() const
			{
				return CTStrTraits::CStrTraits::fs_StrToFloatExact(m_pStr, fp32::fs_0());
			}

			virtual fp64 f_Get_fp64() const
			{
				return CTStrTraits::CStrTraits::fs_StrToFloatExact(m_pStr, fp64::fs_0());
			}

			virtual void f_Visit(CVisitor &_Extractor) const
			{
				if (sizeof(t_CStrDataType) == sizeof(CChar))
				{
					_Extractor((CChar const *)m_pStr);
				}
				else
				{
					TCStr<CTStrTraits> Temp = m_pStr;

					_Extractor(Temp.f_GetStr());
				}
			}

		};			  

		class CNullClass
		{
			public:

		};
		
#define DMibStrStringFormatterImplementStr(_Type, _StrType) \
		template <typename t_CFormatter> \
		class TCStringFormatter<t_CFormatter, _Type *> \
		{ \
		public: \
			typedef TCStrFormatType_String<t_CFormatter, _Type, _StrType> CFormatType;\
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, _Type * const &_Data) \
			{ \
				_Formatter.template f_Alloc<CFormatType>(_Data);\
				return typename CFormatType::CStrFormatTypeClassifier();\
			} \
		};

		DMibStrStringFormatterImplementStr(ch8, EStrType_UTF);
		#ifdef DMibPUniqueType_ch16
		DMibStrStringFormatterImplementStr(ch16, EStrType_UTF);
		#endif
		DMibStrStringFormatterImplementStr(ch32, EStrType_Unicode);

		DMibStrStringFormatterImplementStr(uint16, EStrType_UTF);

		DMibStrStringFormatterImplementStr(const ch8, EStrType_UTF);
		#ifdef DMibPUniqueType_ch16
		DMibStrStringFormatterImplementStr(const ch16, EStrType_UTF);
		#endif
		DMibStrStringFormatterImplementStr(const ch32, EStrType_Unicode);

		DMibStrStringFormatterImplementStr(const uint16, EStrType_UTF);

#define DMibStrStringFormatterImplementStrArray(_Type, _StrType) \
		template <typename t_CFormatter, aint _Size> \
		class TCStringFormatter<t_CFormatter, _Type [_Size] > \
		{ \
		public: \
			typedef _Type CData[_Size];\
			typedef TCStrFormatType_String<t_CFormatter, _Type, _StrType> CFormatType;\
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CData const&_Data) \
			{ \
				_Formatter.template f_Alloc<CFormatType>(_Data);\
				return typename CFormatType::CStrFormatTypeClassifier();\
			} \
		};

		DMibStrStringFormatterImplementStrArray(ch8, EStrType_UTF);
		#ifdef DMibPUniqueType_ch16
		DMibStrStringFormatterImplementStrArray(ch16, EStrType_UTF);
		#endif
		DMibStrStringFormatterImplementStrArray(ch32, EStrType_Unicode);

		DMibStrStringFormatterImplementStrArray(uint16, EStrType_UTF);

		DMibStrStringFormatterImplementStrArray(const ch8, EStrType_UTF);
		#ifdef DMibPUniqueType_ch16
		DMibStrStringFormatterImplementStrArray(const ch16, EStrType_UTF);
		#endif
		DMibStrStringFormatterImplementStrArray(const ch32, EStrType_Unicode);

		DMibStrStringFormatterImplementStrArray(const uint16, EStrType_UTF);
	}
}
