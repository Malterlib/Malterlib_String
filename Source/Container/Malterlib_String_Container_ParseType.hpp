// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CData>
	void TCStringParser<t_CParser, t_CData>::f_CreateParse(t_CParser const &_Parse, t_CData &_Data)
	{
		static_assert(NTraits::cIsSame<t_CParser, CVoidTag>, "You need to implement a parser for this type");
	}

	template <typename t_CParser>
	auto TICStrParseType<t_CParser>::f_GetPtr() const -> TICStrParseType const *
	{
		return this;
	}

	template <typename t_CParser>
	aint TICStrParseType<t_CParser>::f_Get_Str(CChar *_pStr, aint _MaxChars) const
	{
		if (_MaxChars > 0)
		{
			*_pStr = 0;
			return 1;
		}
		return 0;
	}

	template <typename t_CParser>
	void TICStrParseType<t_CParser>::COption::f_GetData_Str(t_CParser const &_ArgData, CChar *_pDestStr, aint _MaxChars) const
	{
		CChar const *pDataStart = m_pDataStart;

		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrParseType const *pParseVar = _ArgData.f_GetArg(ArgNumber);
			if (pParseVar)
			{
				pParseVar->f_Get_Str(_pDestStr, _MaxChars);
			}
		}
		else
		{
			// Parse for characters, and end if , or } is found
			while ((*pDataStart) && ((*pDataStart) != ',') && ((*pDataStart) != '}') && (_MaxChars > 1))
			{
				if (*pDataStart == '\\')
				{
					++pDataStart;
					*_pDestStr = *pDataStart;
					if (*pDataStart)
						++pDataStart;
					++_pDestStr;
					--_MaxChars;
					continue;
				}
				*_pDestStr = *pDataStart;
				++pDataStart;
				++_pDestStr;
				--_MaxChars;
			}
		}

		// Null terminate
		if (_MaxChars > 0)
			*_pDestStr = 0;
	}

	template <typename t_CParser>
	aint TICStrParseType<t_CParser>::COption::f_GetData_aint(t_CParser const &_ArgData, aint _FailValue) const
	{
		CChar const *pDataStart = m_pDataStart;
		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrParseType const *pParseVar = _ArgData.f_GetArg(ArgNumber);
			if (pParseVar)
			{
				return pParseVar->f_Get_aint();
			}
			else
				return _FailValue;
		}
		else
		{
			return CStrTraits::fs_StrToIntBase10(m_pDataStart, _FailValue);
		}
	}

	template <typename t_CParser>
	aint TICStrParseType<t_CParser>::COption::f_GetData_aint_NotSigned(t_CParser const &_ArgData, aint _FailValue) const
	{
		CChar const *pDataStart = m_pDataStart;
		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrParseType const *pParseVar = _ArgData.f_GetArg(ArgNumber);
			if (pParseVar)
			{
				return pParseVar->f_Get_aint();
			}
			else
				return _FailValue;
		}
		else
		{
			return (aint)CStrTraits::fs_StrToIntBase10NoSign(m_pDataStart, (umint)_FailValue);
		}
	}

	template <typename t_CParser>
	fp32 TICStrParseType<t_CParser>::COption::f_GetData_fp32(t_CParser const &_ArgData, fp32 _FailValue) const
	{
		CChar const *pDataStart = m_pDataStart;
		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrParseType const *pParseVar = _ArgData.f_GetArg(ArgNumber);
			if (pParseVar)
			{
				return pParseVar->f_Get_fp32();
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

	template <typename t_CParser>
	fp64 TICStrParseType<t_CParser>::COption::f_GetData_fp64(t_CParser const &_ArgData, fp64 _FailValue) const
	{
		CChar const *pDataStart = m_pDataStart;
		if (*pDataStart == '*')
		{
			aint ArgNumber;
			if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
				ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
			else
				ArgNumber = -1;

			TICStrParseType const *pParseVar = _ArgData.f_GetArg(ArgNumber);
			if (pParseVar)
			{
				return pParseVar->f_Get_fp64();
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

	template <typename t_CParser>
	inline_small auto TICStrParseType<t_CParser>::fp_GetNextParse(COption &_NewParse, CChar const * &_pParse) const -> CChar const *
	{
		// Parse for characters, and end if , or } is found
		CChar const *pParse = _pParse;
		switch ((*pParse))
		{
		case ' ':
			++pParse;
		case '}':
		case 0:
		case ',':
		case '*':
			_NewParse.m_ParseTypes.m_Parse1 = 0;
			_NewParse.m_ParseTypes.m_Parse2 = 0;
			break;
		default:
			_NewParse.m_ParseTypes.m_Parse1 = CStrTraits::fs_CharUpperCase((*pParse));
			++pParse;
			if ((*pParse) > '9' || (*pParse) < '0')
			{
				switch ((*pParse))
				{
				case ' ':
					++pParse;
				case '}':
				case 0:
				case ',':
				case '*':
					_NewParse.m_ParseTypes.m_Parse2 = 0;
					break;
				default:
					_NewParse.m_ParseTypes.m_Parse2 = CStrTraits::fs_CharUpperCase((*pParse));
					++pParse;
					break;
				}
			}
			else
				_NewParse.m_ParseTypes.m_Parse2 = 0;
			break;
		}

		_NewParse.m_pDataStart = pParse;
		CChar const *pRet = pParse;
		while (1)
		{
			switch ((*pParse))
			{
			case 0:
			case '}':
				pRet = pParse;
				if (*pRet == '}')
					++pRet;
				pParse = nullptr;
				break;
			case ',':
				++pParse;
				break;
			default:
				++pParse;
				continue;
			}
			break;
		}

		_pParse = pParse;
		if (pParse)
			return pParse;
		else
			return pRet;
	}

	template <typename t_CParser>
	template <typename t_CParseType, typename t_COptions>
	inline_small auto TICStrParseType<t_CParser>::fs_ParseOptions(t_CParseType const &_Parser, t_COptions &_Options, CChar const *_pParse, t_CParser const &_ArgData) -> const CChar *
	{
		CChar const *pRet = _pParse;
		while (_pParse)
		{
			COption Option;
			pRet = _Parser.fp_GetNextParse(Option, _pParse);

			if (Option.m_ParseTypes.m_Parse1)
			{
				if (!_Parser.f_ParseOption(Option, _Options, _ArgData))
				{
				//	ch8 const pStr[] = {Option.m_ParseTypes.m_Parse1, Option.m_ParseTypes.m_Parse2, 0};
				//	DMibDTrace("Unknown option: {}" DMibNewLine, pStr);

				}

			}
		}
		return pRet;
	}

	template <typename t_CParser>
	template <typename t_COptions>
	inline_small aint TICStrParseType<t_CParser>::f_ParseOption(COption &_Option, t_COptions &_Options, t_CParser const &_ArgData) const
	{
		return false;
	}
}
