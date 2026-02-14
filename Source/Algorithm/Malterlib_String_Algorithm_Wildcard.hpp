// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1, typename tf_CData2>
	constexpr EMatchWildcardResult fg_StrMatchWildcardParse(tf_CData1 const * &_pStr, tf_CData2 const *_pPattern)
	{
		tf_CData1 const *pParse = _pStr;
		tf_CData2 const *pPattern = _pPattern;

		while (*pParse && *pPattern)
		{
			if (*pPattern == '*')
			{
				while (*pPattern == '*')
					++pPattern;
				aint Max = NStr::fg_StrFindChars(pPattern, "*?");
				if (Max < 0)
					Max = NStr::fg_StrLen(pPattern);
				while (*pParse)
				{
					if (Max && NStr::fg_StrCmp(pParse, pPattern, Max) == 0)
						break;
					++pParse;
				}
			}
			else if (*pPattern == '?')
			{
				++pPattern;
				++pParse;
			}
			else
			{
				if (*pPattern != *pParse)
					break;
				++pPattern;
				++pParse;
			}
		}

		while (*pPattern == '*')
			++pPattern;

		_pStr = pParse;

		if (*pParse == *pPattern && *pParse == 0)
			return EMatchWildcardResult_WholeStringMatchedAndPatternExhausted;
		if (*pParse == 0)
			return EMatchWildcardResult_WholeStringMatched;
		if (*pPattern == 0)
			return EMatchWildcardResult_PatternExhausted;

		return EMatchWildcardResult_NotMatched;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr EMatchWildcardResult fg_StrMatchWildcard(tf_CData1 const *_pStr, tf_CData2 const *_pPattern)
	{
		return fg_StrMatchWildcardParse(_pStr, _pPattern);
	}

	template <EMatchWildcardResult tf_Result, typename tf_CStr, typename tf_CContainer>
	bool fg_StrMatchesAnyWildcardInContainerKeys(tf_CStr const &_String, tf_CContainer const &_Container)
	{
		for (auto &Wildcard : _Container.f_Keys())
		{
			if (fg_StrMatchWildcard(_String.f_GetStr(), Wildcard.f_GetStr()) == tf_Result)
				return true;
		}

		return false;
	}

	template <EMatchWildcardResult tf_Result, typename tf_CStr, typename tf_CContainer>
	bool fg_StrMatchesAnyWildcardInContainer(tf_CStr const &_String, tf_CContainer const &_Container)
	{
		for (auto &Wildcard : _Container)
		{
			if (fg_StrMatchWildcard(_String.f_GetStr(), Wildcard.f_GetStr()) == tf_Result)
				return true;
		}

		return false;
	}
}
