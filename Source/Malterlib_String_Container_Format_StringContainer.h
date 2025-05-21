// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	class TCStrFormatType_TStr final : public TICStrFormatType<t_CFormatter>
	{
	public:
		using CStrFormatTypeClassifier = CStrFormatTypeClassifier_String;

		virtual mint f_Delete() override
		{
			if constexpr (mc_bNeedDelete)
				this->~TCStrFormatType_TStr();
			return sizeof(*this);
		}

		virtual void f_Move(t_CFormatter &_Formatter) override
		{
			DMibFastCheck(!t_bReference); // Not supported
			if constexpr (!t_bReference)
				_Formatter.template f_Alloc<TCStrFormatType_TStr>(fg_Move(m_TStr));
		}

		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CChar = typename CTStrTraits::CStrTraits::CChar;
		using CStorageType = TCConditional<t_bReference, const TCStrAggregate<t_CStrTraitsIn> &, TCStr<t_CStrTraitsIn>>;
		using CReferenceType = TCConditional<t_bReference, const TCStrAggregate<t_CStrTraitsIn> &, const TCStr<t_CStrTraitsIn> &>;

		enum
		{
			mc_bNeedDelete = !t_bReference
		};

		CStorageType m_TStr;

		using CType = TCStrAggregate<t_CStrTraitsIn> const &;
		using CCharIn = typename t_CStrTraitsIn::CStrTraits::CChar;

		inline_small TCStrFormatType_TStr(TCStrAggregate<t_CStrTraitsIn> const &_Str)
			: m_TStr(_Str)
		{
		}

		inline_small TCStrFormatType_TStr(TCStrAggregate<t_CStrTraitsIn> &&_Str)
			: m_TStr(fg_Move(_Str))
		{
		}

		inline_small TCStrFormatType_TStr(TCStrAggregate<t_CStrTraitsIn> const *_pStr)
			: m_TStr(*_pStr)
		{
		}

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

		virtual void f_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const override
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

		static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const TCStrAggregate<t_CStrTraitsIn> &_Value, COptionsStr &_Options)
		{
			fp_AddToStr(_String, _CurrentStrLen, _Options, _Value);
		}

		template <typename t_COptions>
		static inline_small void fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, const TCStrAggregate<CTStrTraits> &_Value)
		{
			DMibSafeCheck(reinterpret_cast<void const*>(&_String) != reinterpret_cast<void const*>(&_Value), "You cannot assign a format to string that is used by reference as an argument.");

			mint TempLen = _Value.f_GetLen();

			if (_Options.m_Case && TempLen > 0)
			{
				if constexpr (TCStrAggregate<CTStrTraits>::mc_Type == EStrType_Unicode || TCStrAggregate<CTStrTraits>::mc_Type == EStrType_Ansi)
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
								NMemory::fg_ObjectCopy(_pTemp+1, _Value.f_GetStr()+1, TempLen-1);
								break;
							case COptionsStr::ECase_Decapitalize:
								CTStrTraits::CStrTraits::fs_StrLowerCase(_pTemp, _Value.f_GetStr(), 1);
								NMemory::fg_ObjectCopy(_pTemp+1, _Value.f_GetStr()+1, TempLen-1);
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
						CTStrTraits::CStrTraits::CAllocator::f_Free(pTempStr, AllocLen);
					}
				}
				else
				{
					// TODO: Support for UTF with new string algorithm

					using CUnicodeStr = TCStr
						<
							typename TCStrTraits_ReplaceParams<ch32
							, EStrType_Unicode
							, TCStrAggregate<t_CStrTraitsIn>::CTraits::CStrTraits::mc_Type
							, typename TCStrAggregate<t_CStrTraitsIn>::CImp
							, typename TCStrAggregate<t_CStrTraitsIn>::CTraits::CStrTraits::CParams>::CType
						>
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

		virtual aint f_Get_aint() const override
		{
			return CTStrTraits::CStrTraits::fs_StrToInt(m_TStr.f_GetStr(), (aint)0);
		}

		virtual fp32 f_Get_fp32() const override
		{
			return CTStrTraits::CStrTraits::fs_StrToFloatExact(m_TStr.f_GetStr(), (fp32)0);
		}

		virtual fp64 f_Get_fp64() const override
		{
			return CTStrTraits::CStrTraits::fs_StrToFloatExact(m_TStr.f_GetStr(), (fp64)0);
		}

		virtual void f_Visit(CVisitor &_Extractor) const override
		{
			if constexpr (sizeof(CCharIn) == sizeof(CChar))
			{
				_Extractor((CChar const *)(m_TStr.f_GetStr()));
			}
			else
			{
				TCStr<CTStrTraits> Temp = m_TStr;

				_Extractor(Temp.f_GetStr());
			}
		}

		virtual void const *f_GetTypeID() const override
		{
			return &ms_TypeID;
		}

		virtual bool f_IsSame(void const *_pRight) const override
		{
			auto pRight = static_cast<TCStrFormatType_TStr const *>(_pRight);
			return m_TStr == pRight->m_TStr;
		}

		inline static bool const ms_TypeID = false;
	};

	template <typename t_CFormatter, typename t_CStrTraitsIn>
	class TCStringFormatter<t_CFormatter, TCStrAggregate<t_CStrTraitsIn> >
	{
	public:
		using CFormatType = TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, true>;

		template <typename tf_CTypeWithConst>
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
		using CFormatType = TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, true>;

		template <typename tf_CTypeWithConst>
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
		using CFormatType = TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, false>;

		template <typename tf_CTypeWithConst>
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
		using CFormatType = TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, false>;

		template <typename tf_CTypeWithConst>
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
