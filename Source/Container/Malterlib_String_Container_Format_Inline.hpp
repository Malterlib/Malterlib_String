// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	mint TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::f_Destruct()
	{
		if constexpr (mc_bNeedDestruct)
			this->~TCStrFormatType_Inline();
		return sizeof(*this);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	void TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::f_Move(t_CFormatter &_Formatter)
	{
		DMibFastCheck(!t_bReference); // Not supported
		if constexpr (!t_bReference)
			_Formatter.template f_Alloc<TCStrFormatType_Inline>(fg_Move(mp_ToFormat));
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	inline_small TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::TCStrFormatType_Inline(t_CToFormat const &_ToFormat)
		: mp_ToFormat(_ToFormat)
	{
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	inline_small TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::TCStrFormatType_Inline(t_CToFormat &&_ToFormat)
		: mp_ToFormat(fg_Move(_ToFormat))
	{
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	inline_small TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::TCStrFormatType_Inline(t_CToFormat const *_pStr)
		: mp_ToFormat(*_pStr)
	{
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	template <typename tf_CType>
	auto TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::fsp_GetFormatOptionsType(tf_CType const &_Type)
		requires requires(typename tf_CType::CFormatOptions const &_Options)
		{
			_Options;
		}
	{
		return typename tf_CType::CFormatOptions();
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	template <typename tf_CType>
	auto TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::fsp_GetFormatOptionsType(tf_CType const &_Type)
	{
		return int(0);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::CLocalOptions::CLocalOptions()
		: COptions(COptionsStatic())
	{
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_small aint TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>
		::f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const
		requires requires
		{
			_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option, _Args);
		}
	{
		if (_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option, _Args))
			return true;

		return CSuper::f_ParseOption(_Args, _Option);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_small aint TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>
		::f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const
		requires requires
		{
			_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option);
		}
	{
		if (_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option))
			return true;

		return CSuper::f_ParseOption(_Args, _Option);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_small aint TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>
		::f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const
	{
		return CSuper::f_ParseOption(_Args, _Option);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	void TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>
		::f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const
	{
		CLocalOptions Options;

		if (_pFormat)
		{
			TICStrFormatType_ParseOptionsArgs<CReferenceType, TCStrFormatType_Inline, CLocalOptions> Args(mp_ToFormat, *this, _String, _CurrentStrLen, Options, _ArgData);
			CSuper::fs_ParseOptions(Args, _pFormat);
		}

		fp_AddToStr(_String, _CurrentStrLen, Options, mp_ToFormat);

	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	void TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, t_CToFormat const &_Value)
	{
		CLocalOptions Options;
		fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	void TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>
		::fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, t_CToFormat const &_Value, CLocalOptions &_Options)
	{
		fp_AddToStr(_String, _CurrentStrLen, _Options, _Value);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	template <typename tf_COptions, typename tf_CToFormat>
	inline_small void TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>
		::fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, tf_CToFormat const &_Value)
	{
		if (_Options.m_bSimpleAlign && !_Options.f_RestrictLength())
		{
			_String.f_SetStrLen(_CurrentStrLen);
			if constexpr
				(
					requires
					{
						_Value.f_Format(_String, _Options);
					}
				)
			{
				_Value.f_Format(_String, _Options);
			}
			else
				_Value.f_Format(_String);

			_CurrentStrLen = _String.f_GetLen();
		}
		else
		{
			TCStr<CTStrTraits> Temp;

			if constexpr
				(
					requires
					{
						_Value.f_Format(Temp, _Options);
					}
				)
			{
				_Value.f_Format(Temp, _Options);
			}
			else
				_Value.f_Format(Temp);

			mint TempLen = Temp.f_GetLen();

			if (_Options.m_bSimpleAlign)
				CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, Temp.f_GetStr(), TempLen);
			else
				CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, Temp.f_GetStr(), TempLen, 0);
		}
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	template <typename tf_CToFormat>
	inline_small void TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::fp_FormatInto(TCStr<CTStrTraits> &_String, tf_CToFormat const &_Value)
	{
		if constexpr
			(
				requires
				{
					_Value.f_Format(_String, fg_GetType<CLocalOptions &>());
				}
			)
		{
			CLocalOptions Options;
			_Value.f_Format(_String, Options);
		}
		else
		{
			_Value.f_Format(_String);
		}
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	aint TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::f_Get_aint() const
	{
		TCStr<CTStrTraits> Temp;
		fp_FormatInto(Temp, mp_ToFormat);
		return CTStrTraits::CStrTraits::fs_StrToInt(Temp.f_GetStr(), (aint)0);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	fp32 TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::f_Get_fp32() const
	{
		TCStr<CTStrTraits> Temp;
		fp_FormatInto(Temp, mp_ToFormat);
		return CTStrTraits::CStrTraits::fs_StrToFloatExact(Temp.f_GetStr(), (fp32)0);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	fp64 TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::f_Get_fp64() const
	{
		TCStr<CTStrTraits> Temp;
		fp_FormatInto(Temp, mp_ToFormat);
		return CTStrTraits::CStrTraits::fs_StrToFloatExact(Temp.f_GetStr(), (fp64)0);
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	void TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::f_Visit(CVisitor &_Extractor) const
	{
		TCStr<CTStrTraits> Temp;
		fp_FormatInto(Temp, mp_ToFormat);
		_Extractor(Temp.f_GetStr());
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	void const *TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::f_GetTypeID() const
	{
		return &mcp_TypeID;
	}

	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	bool TCStrFormatType_Inline<t_CFormatter, t_CToFormat, t_bReference>::f_IsSame(void const *_pRight) const
	{
		DMibFastCheck(false); // Not supported
		return false;
	}
}
