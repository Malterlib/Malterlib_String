// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CStrTraitsIn>
	class TCStrParseType_TStr final : public TICStrParseType<t_CParser>
	{
	public:
		virtual mint f_Delete() override
		{
			if constexpr (mc_bNeedDelete)
				this->~TCStrParseType_TStr();
			return sizeof(*this);
		}

		typedef typename t_CParser::CStrTraits CStrTraits;
		typedef typename CStrTraits::CChar CChar;

		enum
		{
			mc_bNeedDelete = false
		};

		static_assert(t_CStrTraitsIn::CStrTraits::mc_Type == t_CParser::CStrTraits::mc_Type);

		TCStrAggregate<t_CStrTraitsIn> *m_pTStr;

		inline_small TCStrParseType_TStr(TCStrAggregate<t_CStrTraitsIn> &_Str):
		m_pTStr(&_Str)
		{
		}

		inline_small TCStrParseType_TStr(TCStrAggregate<t_CStrTraitsIn> *_pStr):
		m_pTStr(_pStr)
		{
		}

		typedef TICStrParseType<t_CParser> CSuper;
		typedef typename CSuper :: COption COption;
		typedef typename CSuper :: COptions COptions;

		class COptionsStr : public COptions
		{
		public:
			inline_medium COptionsStr()
				: m_bEscaped(false)
				, m_bRemoveEscape(false)
			{
				m_EscapedChars[0] = '\"';
				m_EscapedChars[1] = '\\';
				m_EscapedChars[2] = 0;
			}
			uint32 m_bEscaped:1;
			uint32 m_bRemoveEscape:1;
			CChar m_EscapedChars[16];
		};

		template <typename t_COptions>
		inline_small aint f_ParseOption(COption &_Option, t_COptions &_Options, const t_CParser & _ArgData) const
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

		virtual bool f_ParseData(const CChar *&_pString, const CChar *_pFormat, const t_CParser & _ArgData) const override
		{
			COptionsStr Options;
			const CChar *pStartNext = CSuper::fs_ParseOptions(*this, Options, _pFormat, _ArgData);

			const CChar *pEndNext = pStartNext;
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

			mint NextLen = pEndNext - pStartNext;

			const CChar *pParse = _pString;
			const CChar *pParseStart = pParse;

			bool bRet = false;
			if (Options.m_bEscaped)
			{
				m_pTStr->f_Clear();
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
								const CChar *pEscaped = Options.m_EscapedChars;
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
								const CChar *pEscaped = Options.m_EscapedChars;
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
							if (fg_StrStartsWith(pParse, pStartNext, TCLimitsInt<mint>::mc_Max, NextLen))
								break;
						}
					}
					++pParse;
				}

				if (!bInEscape)
				{
					Data.f_AddStr(pParseStart, pParse - pParseStart);
					m_pTStr->f_Assign(Data);
					bRet = true;
				}
			}
			else
			{
				if (NextLen)
				{
					while (*pParse)
					{
						if (fg_StrStartsWith(pParse, pStartNext, TCLimitsInt<mint>::mc_Max, NextLen))
							break;
						++pParse;
					}
				}
				else
				{
					while (*pParse)
						++pParse;
				}
				m_pTStr->f_Clear();
				m_pTStr->f_AddStr(pParseStart, pParse - pParseStart);
				bRet = true;
			}

			_pString = pParse;

			return bRet;
		}

		virtual aint f_Get_aint() const override
		{
			return m_pTStr->f_ToInt(aint(0));
		}

		virtual fp32 f_Get_fp32() const override
		{
			return m_pTStr->f_ToFloat((fp32)0.0);
		}

		virtual fp64 f_Get_fp64() const override
		{
			return m_pTStr->f_ToFloat((fp64)0.0);
		}

		virtual aint f_Get_Str(CChar *_pStr, aint _MaxChars) const override
		{
			aint Ret = fg_Min(m_pTStr->f_GetLen(), _MaxChars);

			NStr::fg_StrCopy(_pStr, *m_pTStr, Ret);
			return Ret;
		}

	};

	template <typename t_CParser, typename t_CStrTraitsIn>
	class TCStringParser<t_CParser, TCStrAggregate<t_CStrTraitsIn> >
	{
	public:
		typedef TCStrParseType_TStr<t_CParser, t_CStrTraitsIn> CParseType;
		static inline_large void f_CreateParse(t_CParser &_Formatter, TCStrAggregate<t_CStrTraitsIn> &_Data)
		{
			mint Flags;
			void *pSpace = _Formatter.f_AllocSpace(sizeof(CParseType), Flags);

			CParseType *pNew = new(pSpace) CParseType(_Data);
			Flags |= (CParseType::mc_bNeedDelete ? 2 : 0);

			_Formatter.fp_AddParse(pNew, Flags);
		}
	};

	template <typename t_CParser, typename t_CStrTraitsIn>
	class TCStringParser<t_CParser, TCStr<t_CStrTraitsIn> >
	{
	public:
		typedef TCStrParseType_TStr<t_CParser, t_CStrTraitsIn> CParseType;
		static inline_large void f_CreateParse(t_CParser &_Formatter, TCStr<t_CStrTraitsIn> &_Data)
		{
			mint Flags;
			void *pSpace = _Formatter.f_AllocSpace(sizeof(CParseType), Flags);

			CParseType *pNew = new(pSpace) CParseType(_Data);
			Flags |= (CParseType::mc_bNeedDelete ? 2 : 0);

			_Formatter.fp_AddParse(pNew, Flags);
		}
	};
}
