// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	inline auto TCStr<t_CTCStrTraits>::fs_ToStr(tf_CType const &_Format) -> TCStr
	{
		if constexpr (NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>)
		{
			TCStr Ret;
			(CFormat(nullptr) << _Format).f_FormatArgumentsToStr(Ret);
			return Ret;
		}
		else
		{
			TCStr Ret;

			using CFormatType = typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType;

			aint CurrentLen = 0;
			CFormatType::fs_AddToStrStatic(Ret, CurrentLen, typename CFormatType::CType(_Format));
			Ret.f_SetStrLen(CurrentLen);
			return Ret;
		}
	}

	template <typename t_CTCStrTraits>
	inline auto TCStr<t_CTCStrTraits>::fs_ToStr(CFormat const &_Format) -> TCStr
	{
		return _Format;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	auto TCStr<t_CTCStrTraits>::fs_ToStr(CChar const *_pFormat, tf_CType const& _Format) -> TCStr
	{
		return (CFormat(_pFormat) << _Format).f_GetStr();
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	auto TCStr<t_CTCStrTraits>::fs_Create(tf_CStrDataType const *_pStr) -> TCStr
	{
		TCStr New;
		New.f_SetStr(_pStr);
		return New;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	auto TCStr<t_CTCStrTraits>::fs_Create(tf_CStrDataType const *_pStr, aint _Len) -> TCStr
	{
		TCStr New;
		New.f_SetStr(_pStr, _Len);
		return New;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrTraitsF>
	auto TCStr<t_CTCStrTraits>::fs_Create(TCStr<tf_CStrTraitsF> const &_From) -> TCStr
	{
		TCStr New;
		New.f_SetStr(_From);
		return New;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	inline_medium void TCStr<t_CTCStrTraits>::fs_ToStrInplace
		(
			TCEnableIf<!NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
			, tf_CType const& _Format
		)
	{
		using CFormatType = typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType;
		aint CurrentLen = 0;
		CFormatType::fs_AddToStrStatic(_Destination, CurrentLen, _Format);
		_Destination.f_SetStrLen(CurrentLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	void TCStr<t_CTCStrTraits>::fs_ToStrInplace
		(
			TCEnableIf<NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
			, tf_CType const& _Format
		)
	{
		(CFormat(nullptr) << _Format).f_FormatArgumentsToStr(_Destination);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	void TCStr<t_CTCStrTraits>::fs_ToStrInplace(TCStr &_Destination, CChar const *_pFormat, tf_CType const& _Format)
	{
		return (CFormat(_pFormat) << _Format).f_FormatToStr(_Destination);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	inline_medium void TCStr<t_CTCStrTraits>::fs_ToStrInplaceConcat
		(
			TCEnableIf<!NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
			, tf_CType const& _Format
		)
	{
		using CFormatType = typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType;

		aint CurrentLen = _Destination.f_GetStrLen();
		CFormatType::fs_AddToStrStatic(_Destination, CurrentLen, _Format);
		_Destination.f_SetStrLen(CurrentLen);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	inline_medium void TCStr<t_CTCStrTraits>::fs_ToStrInplaceConcat
		(
			TCEnableIf<!NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
			, tf_CType const& _Format
			, aint &_Len
		)
	{
		using CFormatType = typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType;

		CFormatType::fs_AddToStrStatic(_Destination, _Len, _Format);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	void TCStr<t_CTCStrTraits>::fs_ToStrInplaceConcat
		(
			TCEnableIf<NTraits::cIsSame<typename TCStringFormatterAll<CFormat, tf_CType>::CFormatType, int>, TCStr> &_Destination
			, tf_CType const& _Format
		)
	{
		(CFormat(nullptr) << _Format).f_FormatArgumentsToStrConcat(_Destination);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	void TCStr<t_CTCStrTraits>::fs_ToStrInplaceConcat(TCStr &_Destination, CChar const *_pFormat, tf_CType const& _Format)
	{
		return (CFormat(_pFormat) << _Format).f_FormatToStrConcat(_Destination);
	}

	template <typename t_CTCStrTraits>
	void TCStr<t_CTCStrTraits>::f_ConvertFromType(EStrType _Type)
	{
		fp_ConvertFromType<sizeof(CChar)>(_Type);
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize>
	TCEnableIf<t_CharSize == 1, void> TCStr<t_TCStrTraits>::fp_ConvertFromType(EStrType _Type)
	{
		DMibFastCheck(_Type <= mc_Type);
		if (_Type < mc_Type)
		{
			switch (_Type)
			{
			case EStrType_Ansi:
				{
					CTempStr Decoded;
					NStr::NPlatform::fg_SystemDecodeAnsiStr((ch8 const *)f_GetStr(), Decoded);
					this->f_Clear();
					TCStr<t_TCStrTraits> New;
					aint Len = 0;
					New.f_AddFromUnicodeIterator(Len, Decoded.f_GetUnicodeIterator());
					New.f_SetStrLen(Len);
					this->f_Assign(fg_Move(New));
				}
				break;
			case EStrType_Unicode:
				{
					DMibSafeCheck(mc_Type == EStrType_UTF, "Must convert to UTF");
					TCStr<t_TCStrTraits> New;
					aint Len = 0;
					New.f_AddFromUnicodeIterator(Len, NStr::TCStrIteratorUnicode<ch8>(f_GetStr(), f_GetLen()));
					New.f_SetStrLen(Len);
					this->f_Assign(fg_Move(New));
				}
				break;
			default:
				DMibFastCheck(false);
				break;
			}
		}
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize>
	TCEnableIf<t_CharSize == 2, void> TCStr<t_TCStrTraits>::fp_ConvertFromType(EStrType _Type)
	{
		DMibFastCheck(_Type <= mc_Type);
		if (_Type < mc_Type)
		{
			switch (_Type)
			{
			case EStrType_Unicode:
				{
					TCStr<t_TCStrTraits> New;
					aint Len = 0;
					New.f_AddFromUnicodeIterator(Len, NStr::TCStrIteratorUnicode<ch16>(f_GetStr(), f_GetLen()));
					New.f_SetStrLen(Len);
					this->f_Assign(fg_Move(New));
				}
				break;
			default:
				DMibFastCheck(false);
				break;
			}
		}
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize>
	TCEnableIf<t_CharSize != 1 && t_CharSize != 2, void> TCStr<t_TCStrTraits>::fp_ConvertFromType(EStrType _Type)
	{
		DMibFastCheck(_Type == EStrType_Unicode);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTypeData>
	tf_CTypeData TCStr<t_CTCStrTraits>::f_ToValue(tf_CTypeData const &_Default) const
	{
		tf_CTypeData Return = _Default;
		(CParse(mc_FormatStr) >> Return).f_Parse(*this);
		return Return;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTypeData>
	tf_CTypeData TCStr<t_CTCStrTraits>::f_ToValue(tf_CTypeData const &_Default, CChar const *_pFormat) const
	{
		tf_CTypeData Return = _Default;
		(CParse(_pFormat) >> Return).f_Parse(*this);
		return Return;
	}

	template <typename t_CTCStrTraits>
	int32 TCStr<t_CTCStrTraits>::f_ToInt() const
	{
		return CStrTraits::fs_StrToInt(CImp::f_GetStr(), int32(0));
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CReturn>
	tf_CReturn TCStr<t_CTCStrTraits>::f_ToInt(tf_CReturn _FailValue) const
	{
		return CStrTraits::fs_StrToInt(CImp::f_GetStr(), _FailValue);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CReturn, typename tf_CTerm>
	tf_CReturn TCStr<t_CTCStrTraits>::f_ToInt(tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators) const
	{
		return CStrTraits::fs_StrToInt(CImp::f_GetStr(), _FailValue, _pStrTerminators);
	}

	template <typename t_CTCStrTraits>
	int32 TCStr<t_CTCStrTraits>::f_ToIntExact() const
	{
		return CStrTraits::fs_StrToIntExact(CImp::f_GetStr(), int32(0));
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CReturn>
	tf_CReturn TCStr<t_CTCStrTraits>::f_ToIntExact(tf_CReturn _FailValue) const
	{
		return CStrTraits::fs_StrToIntExact(CImp::f_GetStr(), _FailValue);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CReturn, typename tf_CTerm>
	tf_CReturn TCStr<t_CTCStrTraits>::f_ToIntExact(tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators) const
	{
		return CStrTraits::fs_StrToIntExact(CImp::f_GetStr(), _FailValue, _pStrTerminators);
	}


	template <typename t_CTCStrTraits>
	fp32 TCStr<t_CTCStrTraits>::f_ToFloat() const
	{
		return CStrTraits::fs_StrToFloat(CImp::f_GetStr(), fp32(0.0));
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CReturn>
	tf_CReturn TCStr<t_CTCStrTraits>::f_ToFloat(tf_CReturn _FailValue) const
	{
		return CStrTraits::fs_StrToFloat(CImp::f_GetStr(), _FailValue);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CReturn, typename tf_CTerm>
	tf_CReturn TCStr<t_CTCStrTraits>::f_ToFloat(tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators) const
	{
		return CStrTraits::fs_StrToFloat(CImp::f_GetStr(), _FailValue, _pStrTerminators);
	}

	template <typename t_CTCStrTraits>
	fp32 TCStr<t_CTCStrTraits>::f_ToFloatExact() const
	{
		return CStrTraits::fs_StrToFloatExact(CImp::f_GetStr(), fp32(0.0));
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CReturn>
	tf_CReturn TCStr<t_CTCStrTraits>::f_ToFloatExact(tf_CReturn _FailValue) const
	{
		return CStrTraits::fs_StrToFloatExact(CImp::f_GetStr(), _FailValue);
	}


	template <typename t_CTCStrTraits>
	template <typename tf_CReturn, typename tf_CTerm>
	tf_CReturn TCStr<t_CTCStrTraits>::f_ToFloatExact(tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators) const
	{
		return CStrTraits::fs_StrToFloatExact(CImp::f_GetStr(), _FailValue, _pStrTerminators);
	}
}
