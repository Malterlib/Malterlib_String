// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	inline_small auto TCStrParse<t_CStrTraits>::fp_GetParseList() -> TICStrParseType<TCStrParse> **
	{
		return m_pParses;
	}

	template <typename t_CStrTraits>
	inline_small auto TCStrParse<t_CStrTraits>::fp_GetParseList() const -> TICStrParseType<TCStrParse> const **
	{
		return m_pParses;
	}

	template <typename t_CStrTraits>
	inline_small auto TCStrParse<t_CStrTraits>::fp_GetParseEntry(aint _iEntry) -> TICStrParseType<TCStrParse> *
	{
		return (TICStrParseType<TCStrParse> *)((mint)m_pParses[_iEntry] & (~((mint)0x3)));
	}

	template <typename t_CStrTraits>
	inline_small auto TCStrParse<t_CStrTraits>::fp_GetParseEntry(aint _iEntry) const -> TICStrParseType<TCStrParse> const *
	{
		return (TICStrParseType<TCStrParse> const *)((mint)m_pParses[_iEntry] & (~((mint)0x3)));
	}

	template <typename t_CStrTraits>
	void *TCStrParse<t_CStrTraits>::fp_AllocSpace(int _Bytes)
	{
		mint Needed = (_Bytes + sizeof(aint) - 1) / sizeof(aint);
		if (m_iCurrentAlloc + Needed > mcp_StaticSpace)
			return nullptr;

		void *pSpace = (void *)(m_AllocSpace + m_iCurrentAlloc);

		m_iCurrentAlloc += Needed;

		return pSpace;
	}

	template <typename t_CStrTraits>
	void TCStrParse<t_CStrTraits>::fp_AddParse(TICStrParseType<TCStrParse> *_pParse, EStringParseTypeFlag _Flags)
	{
		TICStrParseType<TCStrParse> *pParse = (TICStrParseType<TCStrParse> *)((mint)_pParse | static_cast<mint>(_Flags));
		if (m_nParses < mcp_StaticParses)
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

	template <typename t_CStrTraits>
	inline_medium void *TCStrParse<t_CStrTraits>::f_AllocSpace(mint _Size, EStringParseTypeFlag &_Flags)
	{
		mint nNeeded = _Size;
		_Flags = EStringParseTypeFlag::mc_None;

		void *pSpace = fp_AllocSpace(nNeeded);
		if (!pSpace)
		{
			pSpace = CStrTraits::CAllocator::f_Alloc(nNeeded);
			_Flags = EStringParseTypeFlag::mc_NeedDealloc;
		}

		return pSpace;
	}

	template <typename t_CStrTraits>
	inline_medium auto TCStrParse<t_CStrTraits>::f_GetArg(aint _iArgument) const -> TICStrParseType<TCStrParse> const *
	{
		if (_iArgument < 0)
		{
			_iArgument = m_iCurrentArgument++;
		}

		if (_iArgument >= (aint)m_nParses)
			return nullptr;

		return fp_GetParseEntry(_iArgument);
	}

	template <typename t_CStrTraits>
	inline_medium TCStrParse<t_CStrTraits>::TCStrParse(CChar const *_pParseStr)
	{
		m_pParseStr = _pParseStr;
		m_pParses = m_plParses;;
		m_nParses = 0;
		m_iCurrentAlloc = 0;
	}

	template <typename t_CStrTraits>
	TCStrParse<t_CStrTraits>::~TCStrParse()
	{
		TICStrParseType<TCStrParse> **pParseList = fp_GetParseList();

		for (uaint i = 0; i < m_nParses; ++i)
		{
			EStringParseTypeFlag Flags = static_cast<EStringParseTypeFlag>(((mint)pParseList[i] & 0x3));
			TICStrParseType<TCStrParse> *pParse = (TICStrParseType<TCStrParse> *)((mint)pParseList[i] & (~((mint)0x3)));

			if (fg_IsSet(Flags, EStringParseTypeFlag::mc_NeedDealloc))
			{
				mint Size = pParse->f_Destruct();
				CStrTraits::CAllocator::f_Free(pParse, Size);
			}
			else if (fg_IsSet(Flags, EStringParseTypeFlag::mc_NeedDestruct))
				pParse->f_Destruct();
		}
	}

	template <typename t_CStrTraits>
	inline_small auto TCStrParse<t_CStrTraits>::f_Parse(CChar const *_pToParse, aint &_nParsed, EParseFlag _ParseFlags) -> CChar const *
	{
		m_iCurrentArgument = 0;
		return fs_ParseArgList(m_pParseStr, _pToParse, *this, _ParseFlags, _nParsed);
	}

	template <typename t_CStrTraits>
	inline_small auto TCStrParse<t_CStrTraits>::f_Parse(CChar const *_pToParse, EParseFlag _ParseFlags) -> CChar const *
	{
		m_iCurrentArgument = 0;
		aint nParsed;
		return fs_ParseArgList(m_pParseStr, _pToParse, *this, _ParseFlags, nParsed);
	}

	template <typename t_CStrTraits>
	template <typename t_CType>
	inline_small auto TCStrParse<t_CStrTraits>::operator >> (t_CType &_Type) -> TCStrParse &
	{
		TCStringParser<TCStrParse, t_CType>::f_CreateParse(*this, _Type);
		return *this;
	}

	template <typename t_CStrTraits>
	auto TCStrParse<t_CStrTraits>::fs_ParseArgList(CChar const *_pFormat, CChar const *_pParse, TCStrParse const &_DataArgs, EParseFlag _ParseFlags, aint &_nParsed) -> CChar const *
	{
		CChar const *pFormat = _pFormat;
		CChar const *pParse = _pParse;
		_nParsed = 0;

		aint SearchMode = 0;
		while (*pFormat)
		{
			switch (SearchMode)
			{
			case 0:
				{
					// Copy text and search for variables
					CChar const *pAdd = pFormat;
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
							TICStrParseType<TCStrParse> const *pFormatVar = _DataArgs.f_GetArg(ArgNumber);
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
							TICStrParseType<TCStrParse> const *pFormatVar = _DataArgs.f_GetArg(Variable);
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
}
