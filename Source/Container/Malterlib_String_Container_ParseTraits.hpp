// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CTCStrTraits>
	struct TCStr<t_CTCStrTraits>::CParse : public TCStrParse<CStrTraits>
	{
		TCStrParse<CStrTraits> &f_ByPointer()
		{
			return *this;
		}

		inline_medium CParse(typename TCStr<t_CTCStrTraits>::CChar const *_pParseStr) : TCStrParse<CStrTraits>(_pParseStr)
		{
		}
		inline_small aint f_Parse(TCStr<t_CTCStrTraits> const &_Str, aint &_nParsed, EParseFlag _ParseFlags)
		{
			CChar const *pParse = _Str.f_GetStr();
			return TCStrParse<CStrTraits>::f_Parse(pParse, _nParsed, _ParseFlags) - pParse;
		}
		inline_small aint f_Parse(TCStr<t_CTCStrTraits> const &_Str, aint &_nParsed)
		{
			CChar const *pParse = _Str.f_GetStr();
			return TCStrParse<CStrTraits>::f_Parse(pParse, _nParsed, EParseFlag_None) - pParse;
		}
		inline_small aint f_Parse(TCStr<t_CTCStrTraits> const &_Str, EParseFlag _ParseFlags = EParseFlag_None)
		{
			CChar const *pParse = _Str.f_GetStr();
			return TCStrParse<CStrTraits>::f_Parse(pParse, _ParseFlags) - pParse;
		}

		inline_small aint f_Parse(CChar const *_pStr, aint &_nParsed, EParseFlag _ParseFlags = EParseFlag_None)
		{
			CChar const *pParse = _pStr;
			return TCStrParse<CStrTraits>::f_Parse(pParse, _nParsed, _ParseFlags) - pParse;
		}
		inline_small aint f_Parse(CChar const *_pStr, EParseFlag _ParseFlags = EParseFlag_None)
		{
			CChar const *pParse = _pStr;
			return TCStrParse<CStrTraits>::f_Parse(pParse, _ParseFlags) - pParse;
		}

		inline_small CParseResult f_Execute(TCStr<t_CTCStrTraits> const &_Str, EParseFlag _ParseFlags = EParseFlag_None)
		{
			CChar const *pParse = _Str.f_GetStr();

			aint nParsed = 0;
			aint nCharsParsed = TCStrParse<CStrTraits>::f_Parse(pParse, nParsed, _ParseFlags) - pParse;

			return
				{
					.m_nCharsParsed = umint(nCharsParsed)
					, .m_nVariablesParsed = umint(nParsed)
				}
			;
		}

		template <typename tf_CType>
		inline_small CParse &operator >> (tf_CType &_Type)
		{
			TCStringParser<TCStrParse<CStrTraits>, tf_CType>::f_CreateParse(*this, _Type);
			return *this;
		}
	};
}
