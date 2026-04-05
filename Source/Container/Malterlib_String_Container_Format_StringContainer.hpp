// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	inline_small TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::COptionsStr::COptionsStr()
		: COptions(COptionsStatic())
	{
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	inline_small TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::TCStrFormatType_TStr(TCStr<t_CStrTraitsIn> const &_Str)
		: mp_TStr(_Str)
	{
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	inline_small TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::TCStrFormatType_TStr(TCStr<t_CStrTraitsIn> &&_Str)
		: mp_TStr(fg_Move(_Str))
	{
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	inline_small TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::TCStrFormatType_TStr(TCStr<t_CStrTraitsIn> const *_pStr)
		: mp_TStr(*_pStr)
	{
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	umint TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::f_Destruct()
	{
		if constexpr (mc_bNeedDestruct)
			this->~TCStrFormatType_TStr();
		return sizeof(*this);
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	void TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::f_Move(t_CFormatter &_Formatter)
	{
		DMibFastCheck(!t_bReference); // Not supported
		if constexpr (!t_bReference)
			_Formatter.template f_Alloc<TCStrFormatType_TStr>(fg_Move(mp_TStr));
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	void TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>
		::f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const
	{
		COptionsStr Options;

		if (_pFormat)
		{
			TICStrFormatType_ParseOptionsArgs<CReferenceType, TCStrFormatType_TStr, COptionsStr> Args(mp_TStr, *this, _String, _CurrentStrLen, Options, _ArgData);
			CSuper::fs_ParseOptions(Args, _pFormat);
		}

		fp_AddToStr(_String, _CurrentStrLen, Options, mp_TStr);
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	aint TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::f_Get_aint() const
	{
		return CTStrTraits::CStrTraits::fs_StrToInt(mp_TStr.f_GetStr(), (aint)0);
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	fp32 TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::f_Get_fp32() const
	{
		return CTStrTraits::CStrTraits::fs_StrToFloatExact(mp_TStr.f_GetStr(), (fp32)0);
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	fp64 TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::f_Get_fp64() const
	{
		return CTStrTraits::CStrTraits::fs_StrToFloatExact(mp_TStr.f_GetStr(), (fp64)0);
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	void TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::f_Visit(CVisitor &_Extractor) const
	{
		if constexpr (sizeof(CCharIn) == sizeof(CChar))
		{
			_Extractor((CChar const *)(mp_TStr.f_GetStr()));
		}
		else
		{
			TCStr<CTStrTraits> Temp = mp_TStr;

			_Extractor(Temp.f_GetStr());
		}
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	void const *TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::f_GetTypeID() const
	{
		return &mcp_TypeID;
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	bool TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::f_IsSame(void const *_pRight) const
	{
		auto pRight = static_cast<TCStrFormatType_TStr const *>(_pRight);
		return mp_TStr == pRight->mp_TStr;
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_small aint TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>
		::f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const
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

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	void TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, const TCStr<t_CStrTraitsIn> &_Value)
	{
		COptionsStr Options;
		fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	void TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>
		::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, const TCStr<t_CStrTraitsIn> &_Value, COptionsStr &_Options)
	{
		fp_AddToStr(_String, _CurrentStrLen, _Options, _Value);
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	template <typename tf_COptions>
	inline_small void TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>
		::fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, const TCStr<CTStrTraits> &_Value)
	{
		DMibSafeCheck(reinterpret_cast<void const*>(&_String) != reinterpret_cast<void const*>(&_Value), "You cannot assign a format to string that is used by reference as an argument.");

		umint TempLen = _Value.f_GetLen();

		if (_Options.m_Case && TempLen > 0)
		{
			if constexpr (TCStr<CTStrTraits>::mc_Type == EStrType_Unicode || TCStr<CTStrTraits>::mc_Type == EStrType_Ansi)
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
					umint AllocLen = sizeof(CChar) * (TempLen + 1);
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
						, TCStr<t_CStrTraitsIn>::CTraits::CStrTraits::mc_Type
						, typename TCStr<t_CStrTraitsIn>::CImp
						, typename TCStr<t_CStrTraitsIn>::CTraits::CStrTraits::CParams>::CType
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

	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	template <typename tf_COptions, typename tf_CStrTraitsIn>
	inline_small void TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, t_bReference>
		::fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, const TCStr<tf_CStrTraitsIn> &_Value)
	{
		TCStr<CTStrTraits> Value(_Value);
		fp_AddToStr(_String, _CurrentStrLen, _Options, Value);
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, TCStr<t_CStrTraitsIn>>::fs_CreateFormat(t_CFormatter &_Formatter, TCStr<t_CStrTraitsIn> const&_Data)
		-> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(_Data);
		return typename CFormatType::CStrFormatTypeClassifier();
	}

	template <typename t_CFormatter, typename t_CStrTraitsIn>
	template <typename tf_CTypeWithConst>
	inline_large auto TCStringFormatter<t_CFormatter, TCByValue<TCStr<t_CStrTraitsIn>>>::fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<TCStr<t_CStrTraitsIn>> const&_Data)
		-> typename CFormatType::CStrFormatTypeClassifier
	{
		_Formatter.template f_Alloc<CFormatType>(*_Data);
		return typename CFormatType::CStrFormatTypeClassifier();
	}
}
