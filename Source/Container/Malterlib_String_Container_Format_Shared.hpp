// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	constexpr inline_small bool CStrFormatType_StaticOptions::f_RestrictLength()
	{
		return false;
	}

	constexpr inline_small umint CStrFormatType_StaticOptions::f_MinLength()
	{
		return 0;
	}

	constexpr inline_small umint CStrFormatType_StaticOptions::f_MaxLength()
	{
		return TCLimitsInt<umint>::mc_Max;
	}

	constexpr inline_small aint CStrFormatType_StaticOptions::f_Align()
	{
		return 0;
	}

	constexpr inline_small bool CStrFormatType_StaticOptions::f_LeftAlign()
	{
		return false;
	}

	constexpr inline_small bool CStrFormatType_StaticOptions::f_SimpleAlign()
	{
		return true;
	}

	constexpr inline_small ch8 CStrFormatType_StaticOptions::f_Fillout()
	{
		return ' ';
	}

	template <umint t_MinLength, typename t_CParent>
	inline_small TICStrFormatType_StaticOptions_MinLength<t_MinLength, t_CParent>::TICStrFormatType_StaticOptions_MinLength(t_CParent const &_Parent)
		: t_CParent(_Parent)
	{
	}

	template <umint t_MinLength, typename t_CParent>
	constexpr inline_small umint TICStrFormatType_StaticOptions_MinLength<t_MinLength, t_CParent>::f_MinLength()
	{
		return t_MinLength;
	}

	template <umint t_MinLength, typename t_CParent>
	constexpr inline_small bool TICStrFormatType_StaticOptions_MinLength<t_MinLength, t_CParent>::f_RestrictLength()
	{
		return true;
	}

	template <umint t_MaxLength, typename t_CParent>
	inline_small TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, t_CParent>::TICStrFormatType_StaticOptions_MaxLength(t_CParent const &_Parent)
		: t_CParent(_Parent)
	{
	}

	template <umint t_MaxLength, typename t_CParent>
	constexpr inline_small umint TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, t_CParent>::f_MaxLength()
	{
		return t_MaxLength;
	}

	template <umint t_MaxLength, typename t_CParent>
	constexpr inline_small bool TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, t_CParent>::f_RestrictLength()
	{
		return true;
	}

	template <ch32 t_FillOut, typename t_CParent>
	inline_small TICStrFormatType_StaticOptions_FillOut<t_FillOut, t_CParent>::TICStrFormatType_StaticOptions_FillOut (t_CParent const &_Parent)
		: t_CParent(_Parent)
	{
	}

	template <ch32 t_FillOut, typename t_CParent>
	constexpr inline_small ch32 TICStrFormatType_StaticOptions_FillOut<t_FillOut, t_CParent>::f_Fillout()
	{
		return t_FillOut;
	}

	template <typename t_COptions, typename t_CIntType>
	inline_small TCValueWithOptions<t_COptions, t_CIntType>::TCValueWithOptions(t_CIntType const &_Int, t_COptions const &_Options)
		: t_COptions(_Options)
		, m_Int(_Int)
	{
	}

	template <typename t_COptions, typename t_CIntType>
	inline_small t_CIntType const &TCValueWithOptions<t_COptions, t_CIntType>::f_GetValue() const
	{
		return m_Int;
	}

	template <typename t_COptions, typename t_CIntType>
	inline_small auto TCValueWithOptions<t_COptions, t_CIntType>::f_GetOptions() const -> COptions const &
	{
		return *this;
	}

	template <typename t_COptions, typename t_CIntType>
	inline_small auto TCValueWithOptions<t_COptions, t_CIntType>::f_GetOptions() -> COptions &
	{
		return *this;
	}

	template <typename t_COptions, typename t_CIntType>
	inline_small TCValueWithOptions<t_COptions, t_CIntType>::operator t_CIntType const & () const
	{
		return m_Int;
	}

	template <umint t_MinLength, typename t_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_MinLength<t_MinLength, CStrFormatType_StaticOptions>, t_CValueType> fg_FormatMinLength(t_CValueType const &_Value)
	{
		return TCValueWithOptions
			<
				TICStrFormatType_StaticOptions_MinLength
					<
						t_MinLength,
						CStrFormatType_StaticOptions
					>,
				t_CValueType
			>
			(_Value, TICStrFormatType_StaticOptions_MinLength<t_MinLength, CStrFormatType_StaticOptions>(CStrFormatType_StaticOptions()))
		;
	}

	template <umint t_MinLength, typename t_CValueType, typename t_COldOptions>
	inline_small auto fg_FormatMinLength(TCValueWithOptions<t_COldOptions, t_CValueType> const &_Value)
		-> TCValueWithOptions<TICStrFormatType_StaticOptions_MinLength<t_MinLength, t_COldOptions>, t_CValueType>
	{
		return TCValueWithOptions
			<
				TICStrFormatType_StaticOptions_MinLength
					<
						t_MinLength,
						t_COldOptions
					>,
				t_CValueType
			>
			(_Value.f_GetValue(), TICStrFormatType_StaticOptions_MinLength<t_MinLength, t_COldOptions>(_Value.f_GetOptions()))
		;
	}


	template <umint t_MaxLength, typename t_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, CStrFormatType_StaticOptions>, t_CValueType> fg_FormatMaxLength(t_CValueType const &_Value)
	{
		return TCValueWithOptions
			<
				TICStrFormatType_StaticOptions_MaxLength
					<
						t_MaxLength,
						CStrFormatType_StaticOptions
					>,
				t_CValueType
			>
			(_Value, TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, CStrFormatType_StaticOptions>(CStrFormatType_StaticOptions()))
		;
	}

	template <umint t_MaxLength, typename t_CValueType, typename t_COldOptions>
	inline_small auto fg_FormatMaxLength(TCValueWithOptions<t_COldOptions, t_CValueType> const &_Value)
		-> TCValueWithOptions<TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, t_COldOptions>, t_CValueType>
	{
		return TCValueWithOptions
			<
				TICStrFormatType_StaticOptions_MaxLength
					<
						t_MaxLength,
						t_COldOptions
					>,
				t_CValueType
			>
			(_Value.f_GetValue(), TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, t_COldOptions>(_Value.f_GetOptions()))
		;
	}

	template <ch32 t_FillOut, typename t_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_FillOut<t_FillOut, CStrFormatType_StaticOptions>, t_CValueType> fg_FormatFillOut(t_CValueType const &_Value)
	{
		return TCValueWithOptions
			<
				TICStrFormatType_StaticOptions_FillOut
					<
						t_FillOut,
						CStrFormatType_StaticOptions
					>,
				t_CValueType
			>
			(_Value, TICStrFormatType_StaticOptions_FillOut<t_FillOut, CStrFormatType_StaticOptions>(CStrFormatType_StaticOptions()))
		;
	}

	template <ch32 t_FillOut, typename t_CValueType, typename t_COldOptions>
	inline_small auto fg_FormatFillOut(TCValueWithOptions<t_COldOptions, t_CValueType> const &_Value)
		-> TCValueWithOptions<TICStrFormatType_StaticOptions_FillOut<t_FillOut, t_COldOptions>, t_CValueType>
	{
		return TCValueWithOptions
			<
				TICStrFormatType_StaticOptions_FillOut
					<
						t_FillOut,
						t_COldOptions
					>,
				t_CValueType
			>
			(_Value.f_GetValue(), TICStrFormatType_StaticOptions_FillOut<t_FillOut, t_COldOptions>(_Value.f_GetOptions()))
		;
	}

	template <typename t_CChar>
	template <typename tf_CInitializer>
	inline_medium TICStrFormatType_Options<t_CChar>::TICStrFormatType_Options(tf_CInitializer const &_Init)
		: m_MaxLength(_Init.f_MaxLength())
		, m_Align(_Init.f_Align())
		, m_MinLength(_Init.f_MinLength())
		, m_bLeftAlign(_Init.f_LeftAlign())
		, m_bSimpleAlign(_Init.f_SimpleAlign())
		, m_Fillout(_Init.f_Fillout())
	{
	}

	template <typename t_CChar>
	constexpr inline_small bool TICStrFormatType_Options<t_CChar>::f_RestrictLength() const
	{
		return m_MinLength != 0 || m_MaxLength != TCLimitsInt<umint>::mc_Max;
	}

	template <typename t_CChar>
	constexpr inline_small umint TICStrFormatType_Options<t_CChar>::f_MinLength() const
	{
		return m_MinLength;
	}

	template <typename t_CChar>
	constexpr inline_small umint TICStrFormatType_Options<t_CChar>::f_MaxLength() const
	{
		return m_MaxLength;
	}

	template <typename t_CChar>
	constexpr inline_small aint TICStrFormatType_Options<t_CChar>::f_Align() const
	{
		return m_Align;
	}

	template <typename t_CChar>
	constexpr inline_small bool TICStrFormatType_Options<t_CChar>::f_LeftAlign() const
	{
		return m_bLeftAlign;
	}

	template <typename t_CChar>
	constexpr inline_small bool TICStrFormatType_Options<t_CChar>::f_SimpleAlign() const
	{
		return m_bSimpleAlign;
	}

	template <typename t_CChar>
	constexpr inline_small t_CChar TICStrFormatType_Options<t_CChar>::f_Fillout() const
	{
		return m_Fillout;
	}

	template <typename t_CData, typename t_CFormatType, typename t_COptions>
	TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions>
		::TICStrFormatType_ParseOptionsArgs(t_CData &_Data, t_CFormatType const &_FormatType, CString &_String, aint &_CurrentStrLen, t_COptions &_Options, CFormatter const &_Formatter)
		: m_Data(_Data)
		, m_FormatType(_FormatType)
		, m_String(_String)
		, m_CurrentStrLen(_CurrentStrLen)
		, m_Options(_Options)
		, m_Formatter(_Formatter)
	{
	}

	template <typename t_CFormatter>
	void TICStrFormatType<t_CFormatter>::COption::f_GetData_Str(CChar *_pDestStr, aint _MaxChars) const
	{
		CChar const *pParseStr = m_pDataStart;

		// Parse for characters, and end if , or } is found
		while ((*pParseStr) && ((*pParseStr) != ',') && ((*pParseStr) != '}') && (_MaxChars > 1))
		{
			*_pDestStr = *pParseStr;
			++pParseStr;
			++_pDestStr;
			--_MaxChars;
		}

		// Null terminate
		if (_MaxChars > 0)
			*_pDestStr = 0;
	}

	template <typename t_CFormatter>
	aint TICStrFormatType<t_CFormatter>::COption::f_GetData_aint(t_CFormatter const &_ArgData, aint _FailValue) const
	{
		CChar const *pDataStart = m_pDataStart;
		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrFormatType const *pFormatVar = _ArgData.f_GetArg(ArgNumber);
			if (pFormatVar)
			{
				return pFormatVar->f_Get_aint();
			}
			else
				return _FailValue;
		}
		else
		{
			return CStrTraits::fs_StrToIntBase10(m_pDataStart, _FailValue);
		}
	}

	template <typename t_CFormatter>
	aint TICStrFormatType<t_CFormatter>::COption::f_GetData_aint_NotSigned(t_CFormatter const &_ArgData, aint _FailValue) const
	{
		CChar const *pDataStart = m_pDataStart;
		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrFormatType const *pFormatVar = _ArgData.f_GetArg(ArgNumber);
			if (pFormatVar)
			{
				return pFormatVar->f_Get_aint();
			}
			else
				return _FailValue;
		}
		else
		{
			return (aint)CStrTraits::fs_StrToIntBase10NoSign(m_pDataStart, (umint)_FailValue);
		}
	}

	template <typename t_CFormatter>
	fp32 TICStrFormatType<t_CFormatter>::COption::f_GetData_fp32(t_CFormatter const &_ArgData, fp32 _FailValue) const
	{
		CChar const *pDataStart = m_pDataStart;
		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrFormatType const *pFormatVar = _ArgData.f_GetArg(ArgNumber);
			if (pFormatVar)
			{
				return pFormatVar->f_Get_fp32();
			}
			else
				return _FailValue;
		}
		else
		{
			static CChar const Terminators[] = {',','}',0};

			return CStrTraits::fs_StrToFloatExact(m_pDataStart, _FailValue, Terminators);
		}
	}

	template <typename t_CFormatter>
	fp64 TICStrFormatType<t_CFormatter>::COption::f_GetData_fp64(t_CFormatter const &_ArgData, fp64 _FailValue) const
	{
		CChar const *pDataStart = m_pDataStart;
		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrFormatType const *pFormatVar = _ArgData.f_GetArg(ArgNumber);
			if (pFormatVar)
			{
				return pFormatVar->f_Get_fp64();
			}
			else
				return _FailValue;
		}
		else
		{
			static CChar const Terminators[] = {',','}',0};

			return CStrTraits::fs_StrToFloatExact(m_pDataStart, _FailValue, Terminators);
		}
	}

	template <typename t_CFormatter>
	void TICStrFormatType<t_CFormatter>::COption::f_DisplayUnknownFormat(CString &_String, aint &_CurrentStrLen) const
	{
		ch8 const *pTmp = "| format specifier unknown (";
		while (*pTmp)
			_String.f_AddCharLengthAware(_CurrentStrLen, (CChar)(*(pTmp++)));

		if (m_FormatTypes.m_Format1)
			_String.f_AddCharLengthAware(_CurrentStrLen, (CChar)m_FormatTypes.m_Format1);
		if (m_FormatTypes.m_Format2)
			_String.f_AddCharLengthAware(_CurrentStrLen, (CChar)m_FormatTypes.m_Format2);
		_String.f_AddCharLengthAware(_CurrentStrLen, ')');
		_String.f_AddCharLengthAware(_CurrentStrLen, ' ');
		_String.f_AddCharLengthAware(_CurrentStrLen, '|');
	}

	template <typename t_CFormatter>
	auto TICStrFormatType<t_CFormatter>::f_GetPtr() const -> TICStrFormatType const *
	{
		return this;
	}

	template <typename t_CFormatter>
	template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_small void TICStrFormatType<t_CFormatter>::fs_ParseOptions(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, CChar const *_pFormat)
	{
		while (_pFormat)
		{
			COption Option;
			_Args.m_FormatType.fp_GetNextFormat(Option, _pFormat);

			if (Option.m_FormatTypes.m_Format1)
			{
				if (!_Args.m_FormatType.f_ParseOption(_Args, Option))
					Option.f_DisplayUnknownFormat(_Args.m_String, _Args.m_CurrentStrLen);

			}
		}
	}

	template <typename t_CFormatter>
	template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_small aint TICStrFormatType<t_CFormatter>::f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const
	{
		switch (_Option.m_FormatTypes.m_Format1)
		{
			// Format
		case 'L':
			_Args.m_Options.m_MinLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
			break;
		case 'M':
			_Args.m_Options.m_MaxLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, TCLimitsInt<aint>::mc_Max);
			break;
		case 'S':
			{
				switch (_Option.m_FormatTypes.m_Format2)
				{
				case 'J':
				case 'Z':
					_Args.m_Options.m_MaxLength = _Args.m_Options.m_MinLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
					break;
				case 'L':
					_Args.m_Options.m_MinLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
					break;
				case 'M':
					_Args.m_Options.m_MaxLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, TCLimitsInt<aint>::mc_Max);
					break;
				case 'F':
					{
						_Args.m_Options.m_Fillout = *_Option.m_pDataStart;
					}
					break;
				default:
					return false;
					break;
				}
			}
			break;
		case 'A':
			{
				switch (_Option.m_FormatTypes.m_Format2)
				{
				case '-':
					_Args.m_Options.m_Align = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
					_Args.m_Options.m_bLeftAlign = true;
					_Args.m_Options.m_bSimpleAlign = false;
					break;
				case '+':
					_Args.m_Options.m_Align = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
					_Args.m_Options.m_bSimpleAlign = _Args.m_Options.m_Align == 0;
					break;
				default:
					return false;
					break;
				}
				break;
			}
		default:
			return false;
			break;
		}
		return true;
	}

	template <typename t_CFormatter>
	template <typename tf_COptions>
	void TICStrFormatType<t_CFormatter>::fs_AddSubStrToStr(CString &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CChar const *_pSubStr, umint _SubStrLen, aint _SubStrStart)
	{
		aint PreAdd;
		aint PostAdd;
		if (_Options.f_LeftAlign())
		{
			if (_Options.f_Align() >= _SubStrStart)
				PreAdd = _Options.f_Align() - _SubStrStart;
			else
				PreAdd = _Options.f_Align();
			PostAdd = _Options.f_MinLength() - (_SubStrLen + PreAdd);
		}
		else
		{
			PostAdd = _Options.f_Align();
			PreAdd = _Options.f_MinLength() - (_SubStrLen + PostAdd);
		}

		if (PostAdd < 0)
			PostAdd = 0;

		if (PreAdd < 0)
			PreAdd = 0;

		typename CString::CAddStrAgrs Args(_CurrentStrLen, _SubStrLen);
		CChar const *pSubStr = _pSubStr;

		if (PreAdd > 0 || PostAdd > 0)
		{
			_String.f_AddCharsLengthAware(_CurrentStrLen, _Options.f_Fillout(), PreAdd);

			if (_Options.f_LeftAlign())
			{
				if ((_SubStrLen + PreAdd + PostAdd) > _Options.f_MaxLength())
					Args.m_Len = _Options.f_MaxLength() - (PreAdd + PostAdd);
			}
			else
			{
				if ((_SubStrLen + (PreAdd + PostAdd)) > _Options.f_MaxLength())
				{
					Args.m_Len = _Options.f_MaxLength() - (PreAdd + PostAdd);
					pSubStr = _pSubStr + (_SubStrLen - (_Options.f_MaxLength() - (PreAdd + PostAdd)));
				}
			}
		}
		else
		{
			if (_Options.f_LeftAlign())
			{
				if ((_SubStrLen) > _Options.f_MaxLength())
				{
					Args.m_Len = _Options.f_MaxLength();
				}
			}
			else
			{
				if ((_SubStrLen) > _Options.f_MaxLength())
				{
					Args.m_Len = _Options.f_MaxLength();
					pSubStr = _pSubStr + (_SubStrLen - _Options.f_MaxLength());
				}
			}
		}

		_String.f_AddStrLengthAwareInline(Args, pSubStr);

		if (PostAdd > 0)
			_String.f_AddCharsLengthAware(_CurrentStrLen, _Options.f_Fillout(), PostAdd);
	}

	template <typename t_CFormatter>
	template <typename tf_COptions>
	inline_small void TICStrFormatType<t_CFormatter>::fs_AddSubStrToStrSimple(CString &_String, aint &_CurrentStrLen, tf_COptions const &_Options, CChar const *_pSubStr, umint _SubStrLen)
	{
		typename CString::CAddStrAgrs Args(_CurrentStrLen, _SubStrLen);
		CChar const *pSubStr = _pSubStr;
		if (_Options.f_RestrictLength())
		{
			if (_SubStrLen < _Options.f_MinLength())
			{
				_String.f_AddCharsLengthAware(_CurrentStrLen, _Options.f_Fillout(), _Options.f_MinLength() - _SubStrLen);
			}
			else
			{
				if (_SubStrLen > _Options.f_MaxLength())
				{
					Args.m_Len = _Options.f_MaxLength();
					if (!_Options.f_LeftAlign())
						pSubStr = _pSubStr + (_SubStrLen - _Options.f_MaxLength());
				}
			}
		}
		_String.f_AddStrLengthAwareInline(Args, pSubStr);
	}

	template <typename t_CFormatter>
	template <typename tf_CChar>
	void TICStrFormatType<t_CFormatter>::fp_ReportParseError(CString &_String, aint &_CurrentStrLen, tf_CChar const *_pStr, umint _MaxLen) const
	{
		auto pStart = _pStr;
		while (*_pStr && umint(_pStr - pStart) < _MaxLen)
			_String.f_AddCharLengthAware(_CurrentStrLen, (CChar)(*(_pStr++)));
	}

	template <typename t_CFormatter>
	inline_small void TICStrFormatType<t_CFormatter>::fp_GetNextFormat(COption &_NewFormat, CChar const * &_pFormat) const
	{
		// Parse for characters, and end if , or } is found
		CChar const *pFormat = _pFormat;
		switch ((*pFormat))
		{
		case ' ':
			++pFormat;
		case '}':
		case 0:
		case ',':
		case '*':
			_NewFormat.m_FormatTypes.m_Format1 = 0;
			_NewFormat.m_FormatTypes.m_Format2 = 0;
			break;
		default:
			_NewFormat.m_FormatTypes.m_Format1 = CStrTraits::fs_CharUpperCase((*pFormat));
			++pFormat;
			if ((*pFormat) > '9' || (*pFormat) < '0')
			{
				switch ((*pFormat))
				{
				case ' ':
					++pFormat;
				case '}':
				case 0:
				case ',':
				case '*':
					_NewFormat.m_FormatTypes.m_Format2 = 0;
					break;
				default:
					_NewFormat.m_FormatTypes.m_Format2 = CStrTraits::fs_CharUpperCase((*pFormat));
					++pFormat;
					break;
				}
			}
			else
				_NewFormat.m_FormatTypes.m_Format2 = 0;
			break;
		}

		_NewFormat.m_pDataStart = pFormat;

		while (1)
		{
			switch ((*pFormat))
			{
			case 0:
			case '}':
				pFormat = nullptr;
				break;
			case ',':
				++pFormat;
				break;
			default:
				++pFormat;
				continue;
			}
			break;
		}

		_pFormat = pFormat;
	}
}
