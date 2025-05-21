// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	class TCStrParse;

	template <typename t_CParser, typename t_CData>
	class TCStringParser
	{
	public:
		static void f_CreateParse(const t_CParser &_Parse, t_CData &_Data)
		{
			t_CParser::Error(); // You need to implement a parser for this type
		}
	};

	template <typename t_CParser>
	class TICStrParseType
	{
	public:
		virtual mint f_Delete() = 0;

		using CStrTraits = typename t_CParser::CStrTraits;
		using CChar = typename CStrTraits::CChar;

		TICStrParseType *m_pNextParse;

		const TICStrParseType *f_GetPtr() const
		{
			return this;
		}

		virtual aint f_Get_aint() const = 0;
		virtual fp32 f_Get_fp32() const = 0;
		virtual fp64 f_Get_fp64() const = 0;
		virtual aint f_Get_Str(CChar *_pStr, aint _MaxChars) const
		{
			if (_MaxChars > 0)
			{
				*_pStr = 0;
				return 1;
			}
			return 0;
		}

		class COption
		{
		public:

			const CChar *m_pDataStart;

			class CParseTypes
			{
			public:
				ch32 m_Parse1;
				ch32 m_Parse2;
			};

			union
			{
				CParseTypes m_ParseTypes;
				uint32 m_ParseWhole;
			};

			void f_GetData_Str(const t_CParser & _ArgData, CChar *_pDestStr, aint _MaxChars) const
			{
				const CChar *pDataStart = m_pDataStart;

				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrParseType * pParseVar = _ArgData.f_GetArg(ArgNumber);
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

			aint f_GetData_aint(const t_CParser & _ArgData, aint _FailValue) const
			{
				const CChar *pDataStart = m_pDataStart;
				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrParseType * pParseVar = _ArgData.f_GetArg(ArgNumber);
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

			aint f_GetData_aint_NotSigned(const t_CParser & _ArgData, aint _FailValue) const
			{
				const CChar *pDataStart = m_pDataStart;
				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrParseType * pParseVar = _ArgData.f_GetArg(ArgNumber);
					if (pParseVar)
					{
						return pParseVar->f_Get_aint();
					}
					else
						return _FailValue;
				}
				else
				{
					return (aint)CStrTraits::fs_StrToIntBase10NoSign(m_pDataStart, (mint)_FailValue);
				}
			}

			fp32 f_GetData_fp32(const t_CParser & _ArgData, fp32 _FailValue) const
			{
				const CChar *pDataStart = m_pDataStart;
				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrParseType * pParseVar = _ArgData.f_GetArg(ArgNumber);
					if (pParseVar)
					{
						return pParseVar->f_Get_fp32();
					}
					else
						return _FailValue;
				}
				else
				{
					static const CChar Terminators[] = {',','}',0};

					return CStrTraits::fs_StrToFloatExact(m_pDataStart, _FailValue, Terminators);
				}
			}

			fp64 f_GetData_fp64(const t_CParser & _ArgData, fp64 _FailValue) const
			{
				const CChar *pDataStart = m_pDataStart;
				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrParseType * pParseVar = _ArgData.f_GetArg(ArgNumber);
					if (pParseVar)
					{
						return pParseVar->f_Get_fp64();
					}
					else
						return _FailValue;
				}
				else
				{
					static const CChar Terminators[] = {',','}',0};

					return CStrTraits::fs_StrToFloatExact(m_pDataStart, _FailValue, Terminators);
				}
			}

		};

		inline_small const CChar *fp_GetNextParse(COption &_NewParse, const CChar * &_pParse) const
		{
			// Parse for characters, and end if , or } is found
			const CChar * pParse = _pParse;
			switch ((*pParse))
			{
			case ' ':
				++pParse;
			case '}':
			case 0:
			case ',':
			case '*':
				_NewParse.m_ParseWhole = 0;
				break;
			default:
				_NewParse.m_ParseTypes.m_Parse1 = (int16)CStrTraits::fs_CharUpperCase((*pParse));
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
						_NewParse.m_ParseTypes.m_Parse2 = (int16)CStrTraits::fs_CharUpperCase((*pParse));
						++pParse;
						break;
					}
				}
				break;
			}

			_NewParse.m_pDataStart = pParse;
			const CChar *pRet = pParse;
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

		class COptions
		{
		public:
			inline_medium COptions()
			{
			}
		};


		template <typename t_CParseType, typename t_COptions>
		inline_small static const CChar *fs_ParseOptions(const t_CParseType &_Parser, t_COptions &_Options, const CChar *_pParse, const t_CParser & _ArgData)
		{
			const CChar *pRet = _pParse;
			while (_pParse)
			{
				COption Option;
				pRet = _Parser.fp_GetNextParse(Option, _pParse);

				if (Option.m_ParseWhole)
				{
					if (!_Parser.f_ParseOption(Option, _Options, _ArgData))
					{
					//	const ch8 pStr[] = {Option.m_ParseTypes.m_Parse1, Option.m_ParseTypes.m_Parse2, 0};
					//	DMibDTrace("Unknown option: {}" DMibNewLine, pStr);

					}

				}
			}
			return pRet;
		}

		template <typename t_COptions>
		inline_small aint f_ParseOption(COption &_Option, t_COptions &_Options, const t_CParser & _ArgData) const
		{
#if 0
			switch (_Option.m_ParseTypes.m_Parse1)
			{
				// Parse
			default:
				return false;
				break;
			}
			return true;
#endif
			return false;
		}

		virtual bool f_ParseData(const CChar *&_pString, const CChar *_pFormat, const t_CParser & _ArgData) const = 0;


	};

	template <typename t_CStrTraits>
	class TCStrParse
	{
	public:
		using CChar = typename t_CStrTraits::CChar;
		using CStrTraits = t_CStrTraits;

	private:
		enum
		{
			EStaticParses = 16,
			EStaticSpace = EStaticParses*4
		};


		uaint m_nParses;
		mutable aint m_iCurrentArgument;
		TICStrParseType<TCStrParse> **m_pParses;
		const CChar *m_pParseStr;

		TICStrParseType<TCStrParse> *m_plParses[EStaticParses];
		NContainer::TCVector<TICStrParseType<TCStrParse> *> m_lParses;

		inline_small TICStrParseType<TCStrParse> **fp_GetParseList()
		{
			return m_pParses;
		}

		inline_small const TICStrParseType<TCStrParse> **fp_GetParseList() const
		{
			return m_pParses;
		}

		inline_small TICStrParseType<TCStrParse> *fp_GetParseEntry(aint _iEntry)
		{
			return (TICStrParseType<TCStrParse> *)((mint)m_pParses[_iEntry] & (~((mint)0x3)));
		}

		inline_small const TICStrParseType<TCStrParse> *fp_GetParseEntry(aint _iEntry) const
		{
			return (const TICStrParseType<TCStrParse> *)((mint)m_pParses[_iEntry] & (~((mint)0x3)));
		}

		aint m_AllocSpace[EStaticSpace];
		int m_iCurrentAlloc;

		void *fp_AllocSpace(int _Bytes)
		{
			mint Needed = (_Bytes + sizeof(aint) - 1) / sizeof(aint);
			if (m_iCurrentAlloc + Needed > EStaticSpace)
				return nullptr;

			void *pSpace = (void *)(m_AllocSpace + m_iCurrentAlloc);

			m_iCurrentAlloc += Needed;

			return pSpace;
		}


	public:

		void fp_AddParse(TICStrParseType<TCStrParse> *_pParse, mint _Flags)
		{
			TICStrParseType<TCStrParse> *pParse = (TICStrParseType<TCStrParse> *)((mint)_pParse | _Flags);
			if (m_nParses < EStaticParses)
			{
				m_plParses[m_nParses] = pParse;
				++m_nParses;
				return;
			}

			if (m_nParses >= m_lParses.f_GetLen())
			{
				if (!m_lParses.f_GetLen())
				{
					m_lParses.f_SetLen(m_nParses*2);
					NMemory::fg_MemCopy(m_lParses.f_GetArray(), m_plParses, m_nParses * sizeof(void *));
				}
				else
					m_lParses.f_SetLen(m_nParses*2);
			}
			m_pParses = m_lParses.f_GetArray();
			m_pParses[m_nParses] = pParse;
			++m_nParses;
		}

		inline_medium void *f_AllocSpace(mint _Size, mint &_Flags)
		{
			mint nNeeded = _Size;
			_Flags = 0;

			void *pSpace = fp_AllocSpace(nNeeded);
			if (!pSpace)
			{
				pSpace = CStrTraits::CAllocator::f_Alloc(nNeeded);
				_Flags = 1;
			}

			return pSpace;
		}

		inline_medium const TICStrParseType<TCStrParse> * f_GetArg(aint _iArgument) const
		{
			if (_iArgument < 0)
			{
				_iArgument = m_iCurrentArgument++;
			}
			if (_iArgument >= (aint)m_nParses)
				return nullptr;

			return fp_GetParseEntry(_iArgument);
		}

		inline_medium TCStrParse(const CChar *_pParseStr)
		{
			m_pParseStr = _pParseStr;
			m_pParses = m_plParses;;
			m_nParses = 0;
			m_iCurrentAlloc = 0;
		}

		~TCStrParse()
		{
			TICStrParseType<TCStrParse> **pParseList = fp_GetParseList();

			for (uaint i = 0; i < m_nParses; ++i)
			{
				mint Flags = (mint)pParseList[i] & 0x3;
				TICStrParseType<TCStrParse> *pParse = (TICStrParseType<TCStrParse> *)((mint)pParseList[i] & (~((mint)0x3)));

				if (Flags & 1)
				{
					mint Size = pParse->f_Delete();
					CStrTraits::CAllocator::f_Free(pParse, Size);
				}
				else if (Flags & 2)
					pParse->f_Delete();
			}
		}

		inline_small const CChar *f_Parse(const CChar *_pToParse, aint &_nParsed, EParseFlag _ParseFlags = EParseFlag_None)
		{
			m_iCurrentArgument = 0;
			return fp_ParseArgList(m_pParseStr, _pToParse, *this, _ParseFlags, _nParsed);
		}

		inline_small const CChar *f_Parse(const CChar *_pToParse, EParseFlag _ParseFlags = EParseFlag_None)
		{
			m_iCurrentArgument = 0;
			aint nParsed;
			return fp_ParseArgList(m_pParseStr, _pToParse, *this, _ParseFlags, nParsed);
		}

		template <typename t_CType>
		inline_small TCStrParse &operator >> (t_CType &_Type)
		{
			TCStringParser<TCStrParse, t_CType>::f_CreateParse(*this, _Type);
			return *this;
		}

//			inline_large 
		static const CChar *fp_ParseArgList(const CChar *_pFormat, const CChar *_pParse, const TCStrParse &_DataArgs, EParseFlag _ParseFlags, aint &_nParsed)
		{
			const CChar *pFormat = _pFormat;
			const CChar *pParse = _pParse;
			_nParsed = 0;

			aint SearchMode = 0;
			while (*pFormat)
			{
				switch (SearchMode)
				{
				case 0:
					{
						// Copy text and search for variables
						const CChar *pAdd = pFormat;
						while (1)
						{
							CChar CurrentFormat = (*pAdd);
							switch(CurrentFormat)
							{
							case '{':
								SearchMode = 1;
								++pAdd;
								break;
							case 0:
								break;

							case ' ':
							case '\t':
								if (_ParseFlags & EParseFlag_ExtendedWhitespace)
								{
									if (*pParse == ' ' || *pParse == '\t')
									{
										++pParse;
										continue;
									}
									else
									{
										++pAdd;
										continue;
									}
								}
								// Deliberate fall through.

							default:
								if (_ParseFlags & EParseFlag_NoCase)
								{
									if (fg_CharLowerCase(*pParse) != fg_CharLowerCase(*pAdd))
										return pParse;
								}
								else if (*pParse != *pAdd)
									return pParse;
								++pParse;
								++pAdd;
								continue;
							}
							break;
						}
						pFormat = pAdd;
					}
					break;
				case 1:
					{
						if ((*pFormat) == '{')
						{
							SearchMode = 0;
							if (*pParse != *pFormat)
								return pParse;
							++pParse;
							++pFormat;
							break;
						}
						else
						{
							//						static const CChar Terminators[] = {' ', '}', ','};
							// Parse a variable
							aint Variable = -1;
							if (*pFormat == '*')
							{
								++pFormat;
								aint ArgNumber;
								if (CStrTraits::fs_CharIsNumber(*(pFormat)))
									ArgNumber = CStrTraits::fs_StrToIntBase10ParseNoSign(pFormat, -1);
								else
									ArgNumber = -1;

								while ((*pFormat) == ' ')
									++pFormat;

								if ((*pFormat) == ',')
									++pFormat;
								const TICStrParseType<TCStrParse> * pFormatVar = _DataArgs.f_GetArg(ArgNumber);
								if (pFormatVar)
								{
									Variable = pFormatVar->f_Get_aint();
								}
								else
								{
									return pParse;
								}

							}
							else if (CStrTraits::fs_CharIsNumber(*pFormat))
							{
								Variable = CStrTraits::fs_StrToIntBase10ParseNoSign(pFormat, (aint)-16324);

								while ((*pFormat) == ' ')
									++pFormat;

								if ((*pFormat) == ',')
									++pFormat;
								if (Variable == -16324)
								{
									return pParse;
								}
								else if (Variable < 0)
								{
									return pParse;
								}
							}

							{
								const TICStrParseType<TCStrParse> * pFormatVar = _DataArgs.f_GetArg(Variable);
								if (pFormatVar)
								{
									if (pFormatVar->f_ParseData(pParse, pFormat, _DataArgs))
										++_nParsed;
								}
								else
								{
									return pParse;
								}
							}

//EndArgSearch:

							while ((*pFormat) && (*pFormat) != '}')
							{
								++pFormat;
							}

							if (*pFormat)
								++pFormat;

							SearchMode = 0;
						}

					}
					break;
				}

			}
			return pParse;
		}

	};
}
