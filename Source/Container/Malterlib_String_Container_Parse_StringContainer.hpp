// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CStrTraitsIn>
	umint TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::f_Destruct()
	{
		if constexpr (mc_bNeedDestruct)
			this->~TCStrParseType_TStr();
		return sizeof(*this);
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	inline_small TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::TCStrParseType_TStr(TCStr<t_CStrTraitsIn> &_Str)
		: mp_pTStr(&_Str)
	{
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	inline_small TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::TCStrParseType_TStr(TCStr<t_CStrTraitsIn> *_pStr)
		: mp_pTStr(_pStr)
	{
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	template <typename tf_COptions>
	inline_small aint TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::f_ParseOption(COption &_Option, tf_COptions &_Options, t_CParser const &_ArgData) const
	{
		switch (_Option.m_ParseTypes.m_Parse1)
		{
			case 'S':
			{
				switch (_Option.m_ParseTypes.m_Parse2)
				{
				case 'E':
					{
						_Options.m_bEscaped = true;
					}
					break;
				case 'R':
					{
						_Options.m_bRemoveEscape = true;
					}
					break;
				case 'C':
					{
						_Option.f_GetData_Str(_ArgData, _Options.m_EscapedChars, 16);
					}
					break;
				}
				break;
			}
		}
		return CSuper::f_ParseOption(_Option, _Options, _ArgData);
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	bool TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::f_ParseData(CChar const * &_pString, CChar const *_pFormat, t_CParser const &_ArgData) const
	{
		COptionsStr Options;
		CChar const *pStartNext = CSuper::fs_ParseOptions(*this, Options, _pFormat, _ArgData);

		CChar const *pEndNext = pStartNext;
		while (*pEndNext)
		{
			if (*pEndNext == '{')
			{
				if (pEndNext[1] == '{')
				{
					pEndNext += 2;
					continue;
				}
				break; // Done
			}
			++pEndNext;
		}

		umint NextLen = pEndNext - pStartNext;

		CChar const *pParse = _pString;
		CChar const *pParseStart = pParse;

		bool bRet = false;
		if (Options.m_bEscaped)
		{
			mp_pTStr->f_Clear();
			TCStr<t_CStrTraitsIn> Data;
			bool bInEscape = false;
			while (*pParse)
			{
				if (bInEscape)
				{
					if (*pParse == '\\')
					{
						if (Options.m_bRemoveEscape)
						{
							CChar const *pEscaped = Options.m_EscapedChars;
							while (*pEscaped)
							{
								if (*pEscaped == pParse[1])
								{
									if (pParse - pParseStart)
										Data.f_AddStr(pParseStart, pParse - pParseStart);
									++pParse;
									Data.f_AddChar(*pParse);
									++pParse;
									pParseStart = pParse;
									break;
								}
								++pEscaped;
							}
							if (*pEscaped)
								continue;
						}
						else
						{
							++pParse;
							CChar const *pEscaped = Options.m_EscapedChars;
							while (*pEscaped)
							{
								if (*pEscaped == *pParse)
								{
									++pParse;
									break;
								}
								++pEscaped;
							}
							continue;
						}
					}

					if (*pParse == Options.m_EscapedChars[0])
					{
						if (Options.m_bRemoveEscape)
						{
							if (pParse - pParseStart)
								Data.f_AddStr(pParseStart, pParse - pParseStart);
							++pParse;
							pParseStart = pParse;
						}
						else
							++pParse;
						bInEscape = false;
						continue;
					}
				}
				else
				{
					if (*pParse == Options.m_EscapedChars[0])
					{
						if (Options.m_bRemoveEscape)
						{
							if (pParse - pParseStart)
								Data.f_AddStr(pParseStart, pParse - pParseStart);
							++pParse;
							pParseStart = pParse;
						}
						else
							++pParse;
						bInEscape = true;
						continue;
					}
					if (NextLen)
					{
						if (fg_StrStartsWith(pParse, pStartNext, TCLimitsInt<umint>::mc_Max, NextLen))
							break;
					}
				}
				++pParse;
			}

			if (!bInEscape)
			{
				Data.f_AddStr(pParseStart, pParse - pParseStart);
				mp_pTStr->f_Assign(Data);
				bRet = true;
			}
		}
		else
		{
			if (NextLen)
			{
				while (*pParse)
				{
					if (fg_StrStartsWith(pParse, pStartNext, TCLimitsInt<umint>::mc_Max, NextLen))
						break;
					++pParse;
				}
			}
			else
			{
				while (*pParse)
					++pParse;
			}
			mp_pTStr->f_Clear();
			mp_pTStr->f_AddStr(pParseStart, pParse - pParseStart);
			bRet = true;
		}

		_pString = pParse;

		return bRet;
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	aint TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::f_Get_aint() const
	{
		return mp_pTStr->f_ToInt(aint(0));
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	fp32 TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::f_Get_fp32() const
	{
		return mp_pTStr->f_ToFloat((fp32)0.0);
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	fp64 TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::f_Get_fp64() const
	{
		return mp_pTStr->f_ToFloat((fp64)0.0);
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	aint TCStrParseType_TStr<t_CParser, t_CStrTraitsIn>::f_Get_Str(CChar *_pStr, aint _MaxChars) const
	{
		aint Ret = fg_Min(mp_pTStr->f_GetLen(), _MaxChars);

		NStr::fg_StrCopy(_pStr, *mp_pTStr, Ret);
		return Ret;
	}

	template <typename t_CParser, typename t_CStrTraitsIn>
	inline_large void TCStringParser<t_CParser, TCStr<t_CStrTraitsIn>>::f_CreateParse(t_CParser &_Formatter, TCStr<t_CStrTraitsIn> &_Data)
	{
		EStringParseTypeFlag Flags;
		void *pSpace = _Formatter.f_AllocSpace(sizeof(CParseType), Flags);

		CParseType *pNew = new(pSpace) CParseType(_Data);
		Flags |= (CParseType::mc_bNeedDestruct ? EStringParseTypeFlag::mc_NeedDestruct : EStringParseTypeFlag::mc_None);

		_Formatter.fp_AddParse(pNew, Flags);
	}
}
