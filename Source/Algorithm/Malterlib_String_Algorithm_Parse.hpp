// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CChar>
	constexpr void fg_ParseWhiteSpace(tf_CChar const * &_pParse)
	{
		while (*_pParse && NStr::fg_CharIsWhiteSpace(*_pParse))
			++_pParse;
	}

	template <typename tf_CChar>
	constexpr void fg_ParseWhiteSpaceNoLines(tf_CChar const * &_pParse)
	{
		while (*_pParse && NStr::fg_CharIsWhiteSpaceNoLines(*_pParse))
			++_pParse;
	}

	template <typename tf_CChar>
	constexpr void fg_ParseToEndOfLine(tf_CChar const * &_pParse)
	{
		tf_CChar const *pParse = _pParse;
		while (*pParse)
		{
			if (*pParse == '\n' || *pParse == '\r')
				break;
			++pParse;
		}
		_pParse = pParse;
	}

	template <typename tf_CChar>
	constexpr bool fg_ParseEndOfLine(tf_CChar const * &_pParse)
	{
		bool bRet = false;
		tf_CChar const *pParse = _pParse;
		if (*pParse == '\r')
		{
			bRet = true;
			++pParse;
			if (*pParse == '\n')
				++pParse;
		}
		else if (*pParse == '\n')
		{
			bRet = true;
			++pParse;
		}
		_pParse = pParse;
		return bRet;
	}

	template <typename tf_CChar>
	constexpr void fg_ParseWhiteSpace(tf_CChar * &_pParse)
	{
		while (*_pParse && NStr::fg_CharIsWhiteSpace(*_pParse))
			++_pParse;
	}

	template <typename tf_CChar>
	constexpr void fg_ParseToEndOfLine(tf_CChar * &_pParse)
	{
		tf_CChar *pParse = _pParse;
		while (*pParse)
		{
			if (*pParse == '\n' || *pParse == '\r')
				break;
			++pParse;
		}
		_pParse = pParse;
	}

	template <typename tf_CChar>
	constexpr bool fg_ParseEndOfLine(tf_CChar * &_pParse)
	{
		bool bRet = false;
		tf_CChar *pParse = _pParse;
		if (*pParse == '\r')
		{
			bRet = true;
			++pParse;
			if (*pParse == '\n')
				++pParse;
		}
		else if (*pParse == '\n')
		{
			bRet = true;
			++pParse;
		}
		_pParse = pParse;
		return bRet;
	}

	template <typename tf_CChar, typename tf_CSeparators>
	constexpr void fg_ParseNonWhiteSpaceAndSeparators(tf_CChar const * &_pParse, tf_CSeparators const *_pSeparators)
	{
		tf_CChar const *pParse = _pParse;
		while (*pParse && !NStr::fg_CharIsWhiteSpace(*pParse))
		{
			tf_CSeparators const *pSeparators = _pSeparators;
			while (*pSeparators && *pParse != *pSeparators)
				++pSeparators;
			if (*pSeparators)
				break;
			++pParse;
		}

		_pParse = pParse;
	}

	template <typename tf_CChar>
	constexpr void fg_ParseAlpha(tf_CChar const * &_pParse)
	{
		auto *pParse = (NTraits::TCUnsigned<tf_CChar> const *)_pParse;
		while (*pParse)
		{
			if (*pParse >= 'a' && *pParse <= 'z')
				;
			else if (*pParse >= 'A' && *pParse <= 'Z')
				;
			else if (*pParse >= 0xc0)
				;
			else
				break;
			++pParse;
		}

		_pParse = (tf_CChar const * )pParse;
	}

	template <typename tf_CChar>
	constexpr void fg_ParseAlphaNumeric(tf_CChar const * &_pParse)
	{
		auto *pParse = (NTraits::TCUnsigned<tf_CChar> const *)_pParse;
		while (*pParse)
		{
			if (!fg_CharIsAlphabetical(*pParse) && !fg_CharIsNumber(*pParse))
				break;
			++pParse;
		}

		_pParse = (tf_CChar const *)pParse;
	}

	template <typename tf_CChar>
	constexpr void fg_ParseNumeric(tf_CChar const * &_pParse)
	{
		auto *pParse = (NTraits::TCUnsigned<tf_CChar> const *)_pParse;
		while (*pParse)
		{
			if (!fg_CharIsNumber(*pParse))
				break;
			++pParse;
		}

		_pParse = (tf_CChar const *)pParse;
	}

	template <typename tf_CChar, typename tf_CChar1>
	constexpr void fg_ParseAlphaNumericAndChars(tf_CChar const * &_pParse, tf_CChar1 const *_pChars)
	{
		auto *pParse = (NTraits::TCUnsigned<tf_CChar> const *)_pParse;
		while (*pParse)
		{
			auto *pCharsParse = (NTraits::TCUnsigned<tf_CChar1> const *)_pChars;
			while (*pCharsParse)
			{
				if (*pParse == *pCharsParse)
					break;
				++pCharsParse;
			}

			if (!(*pCharsParse) && !fg_CharIsAlphabetical(*pParse) && !fg_CharIsNumber(*pParse))
				break;
			++pParse;
		}

		_pParse = (tf_CChar const *)pParse;
	}

	template <typename tf_CChar, typename tf_CSeparators>
	constexpr void fg_ParseWhiteSpaceAndSeparators(tf_CChar const * &_pParse, tf_CSeparators const *_pSeparators)
	{
		tf_CChar const *pParse = _pParse;
		while (*pParse)
		{
			tf_CSeparators const *pSeparators = _pSeparators;
			while (*pSeparators && *pParse != *pSeparators)
				++pSeparators;
			if (*pSeparators)
			{
				++pParse;
				continue;
			}
			if (NStr::fg_CharIsWhiteSpace(*pParse))
			{
				++pParse;
				continue;
			}
			break;
		}

		_pParse = pParse;
	}
}
