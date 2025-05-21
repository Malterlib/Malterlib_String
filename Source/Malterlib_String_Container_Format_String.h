// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	||
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <typename t_CFormatter, typename t_CStrDataType, CStrTypeUnderlying t_Type>
	class TCStrFormatType_String final : public TICStrFormatType<t_CFormatter>
	{
	public:
		static_assert(t_Type != EStrType_Ansi);

		using CStrFormatTypeClassifier = CStrFormatTypeClassifier_String;

		virtual mint f_Delete() override
		{
			if constexpr (mc_bNeedDelete)
				this->~TCStrFormatType_String();
			return sizeof(*this);
		}

		virtual void f_Move(t_CFormatter &_Formatter) override
		{
			_Formatter.template f_Alloc<TCStrFormatType_String>(m_pStr, m_StrLen);
		}

		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CChar = typename CTStrTraits::CStrTraits::CChar;

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
			DMibFastCheck(CTStrTraits::CStrTraits::fs_StrLen(_pStr, _StrLen) == _StrLen);
		}

		inline_small TCStrFormatType_String(t_CStrDataType const *_pStr, aint _StrLen, bool _bCheckSize)
			: m_pStr(_pStr)
			, m_StrLen(CTStrTraits::CStrTraits::fs_StrLen(_pStr, _StrLen))
		{
		}

		using CType = t_CStrDataType const *;
		using CSuper = TICStrFormatType<t_CFormatter>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;
		using COptionsStatic = typename CSuper::COptionsStatic;
		using CVisitor = typename CSuper::CVisitor;

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

		virtual void f_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const override
		{
			COptionsStr Options;

			if (_pFormat)
			{
				using CStrType = decltype((m_pStr));

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

		static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_CStrDataType const *_pValue, COptionsStr &_Options)
		{
			fp_AddToStr<CTStrTraits::CStrTraits::mc_Type, t_Type>(_String, _CurrentStrLen, _Options, _pValue, CTStrTraits::CStrTraits::fs_StrLen(_pValue));
		}

		template <CStrTypeUnderlying tf_DestinationType, CStrTypeUnderlying tf_SourceType, typename t_COptions>
		static inline_small auto fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, CChar const *_pValue, mint _StrLen)
			-> TCEnableIf<tf_DestinationType == tf_SourceType, void>
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
							NMemory::fg_ObjectCopy(_pTemp+1, _pValue+1, _StrLen-1);
							break;
						case COptionsStr::ECase_Decapitalize:
							CTStrTraits::CStrTraits::fs_StrLowerCase(_pTemp, _pValue, 1);
							NMemory::fg_ObjectCopy(_pTemp+1, _pValue+1, _StrLen-1);
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
					CTStrTraits::CStrTraits::CAllocator::f_Free(pTempStr, AllocLen);
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

		template <CStrTypeUnderlying tf_DestinationType, CStrTypeUnderlying tf_SourceType, typename t_COptions, typename tf_CStrDataType>
		static inline_small void fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, tf_CStrDataType const *_pValue, mint _StrLen)
		{
			TCStr<CTStrTraits> Converted;

			aint Size = 0;
			Converted.f_AddFromUnicodeIterator(Size, fg_GetUnicodeIterator(_pValue, _StrLen));
			Converted.f_SetStrLen(Size);

			fp_AddToStr<tf_DestinationType, tf_DestinationType>(_String, _CurrentStrLen, _Options, Converted.f_GetStr(), Converted.f_GetLen());

			//t_Type;
		}

		virtual aint f_Get_aint() const override
		{
			return CTStrTraits::CStrTraits::fs_StrToInt(m_pStr, (aint)0);
		}

		virtual fp32 f_Get_fp32() const override
		{
			return CTStrTraits::CStrTraits::fs_StrToFloatExact(m_pStr, fp32::fs_0());
		}

		virtual fp64 f_Get_fp64() const override
		{
			return CTStrTraits::CStrTraits::fs_StrToFloatExact(m_pStr, fp64::fs_0());
		}

		virtual void f_Visit(CVisitor &_Extractor) const override
		{
			if constexpr (sizeof(t_CStrDataType) == sizeof(CChar))
			{
				_Extractor((CChar const *)m_pStr);
			}
			else
			{
				TCStr<CTStrTraits> Temp = m_pStr;

				_Extractor(Temp.f_GetStr());
			}
		}

		virtual void const *f_GetTypeID() const override
		{
			return &ms_TypeID;
		}

		virtual bool f_IsSame(void const *_pRight) const override
		{
			auto pRight = static_cast<TCStrFormatType_String const *>(_pRight);

			if (m_StrLen != pRight->m_StrLen)
				return false;

			if (fg_StrCmp(m_pStr, pRight->m_pStr, m_StrLen) != 0)
				return false;
			
			return true;
		}

		inline static bool const ms_TypeID = false;
	};

	class CNullClass
	{
		public:

	};

#define DMibStrStringFormatterImplementStr(d_Type, d_StrType) \
	template <typename t_CFormatter> \
	class TCStringFormatter<t_CFormatter, d_Type *> \
	{ \
	public: \
		using CFormatType = TCStrFormatType_String<t_CFormatter, d_Type, d_StrType>; \
		template <typename tf_CTypeWithConst> \
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, d_Type * const &_Data) \
		{ \
			_Formatter.template f_Alloc<CFormatType>(_Data);\
			return typename CFormatType::CStrFormatTypeClassifier();\
		} \
	};\
	template <typename t_CFormatter> \
	class TCStringFormatter<t_CFormatter, TCByValue<d_Type *>> \
	{ \
	public: \
		using CFormatType = TCStrFormatType_String<t_CFormatter, d_Type, d_StrType>; \
		template <typename tf_CTypeWithConst> \
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<d_Type *> const &_Data) \
		{ \
			_Formatter.template f_Alloc<CFormatType>(*_Data);\
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

#define DMibStrStringFormatterImplementStrArray(d_Type, d_StrType) \
	template <typename t_CFormatter, aint t_Size> \
	class TCStringFormatter<t_CFormatter, d_Type [t_Size] > \
	{ \
	public: \
		using CData = d_Type[t_Size];\
		using CFormatType = TCStrFormatType_String<t_CFormatter, d_Type, d_StrType>; \
		template <typename tf_CTypeWithConst> \
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CData const&_Data) \
		{ \
			if constexpr (NMib::NTraits::cIsConst<tf_CTypeWithConst>) \
				_Formatter.template f_Alloc<CFormatType>(_Data, t_Size - 1); \
			else \
				_Formatter.template f_Alloc<CFormatType>(_Data, t_Size - 1, true); \
			return typename CFormatType::CStrFormatTypeClassifier(); \
		} \
	};\
	template <typename t_CFormatter, aint t_Size> \
	class TCStringFormatter<t_CFormatter, TCByValue<d_Type [t_Size]> > \
	{ \
	public: \
		using CData = d_Type[t_Size];\
		using CFormatType = TCStrFormatType_String<t_CFormatter, d_Type, d_StrType>; \
		template <typename tf_CTypeWithConst> \
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<CData> const&_Data) \
		{ \
			_Formatter.template f_Alloc<CFormatType>(*_Data, t_Size - 1, true); \
			return typename CFormatType::CStrFormatTypeClassifier();\
		} \
	};\
	template <typename t_CFormatter> \
	class TCStringFormatter<t_CFormatter, d_Type [] > \
	{ \
	public: \
		using CData = d_Type[];\
		using CFormatType = TCStrFormatType_String<t_CFormatter, d_Type, d_StrType>; \
		template <typename tf_CTypeWithConst> \
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, CData const&_Data) \
		{ \
			_Formatter.template f_Alloc<CFormatType>(_Data);\
			return typename CFormatType::CStrFormatTypeClassifier();\
		} \
	}; \
	template <typename t_CFormatter> \
	class TCStringFormatter<t_CFormatter, TCByValue<d_Type []> > \
	{ \
	public: \
		using CData = d_Type[];\
		using CFormatType = TCStrFormatType_String<t_CFormatter, d_Type, d_StrType>; \
		template <typename tf_CTypeWithConst> \
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<CData> const&_Data) \
		{ \
			_Formatter.template f_Alloc<CFormatType>(*_Data);\
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
