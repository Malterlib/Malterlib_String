// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, umint _MaxLen)
	{
		tf_CData1 *pDest = _pStrDest;
		if (_MaxLen < 3)
		{
			*pDest = 0;
			return _pStrDest;
		}
		_MaxLen -= 2; // Null charater and one '"'

		tf_CData1 *pMaxDest = pDest + _MaxLen;
		*(pDest++) = '\"';
		tf_CData2 const *pParse = _pStrSource;

		while (*pParse && pDest < pMaxDest)
		{
			if (*pParse == '\"' || *pParse == '\\')
			{
				if (pDest + 1 >= pMaxDest)
					break;
				*(pDest++) = '\\';
				*(pDest++) = *pParse;
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = '\"';
		*(pDest++) = 0;
		return _pStrDest;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource)
	{
		tf_CData1 *pDest = _pStrDest;

		*(pDest++) = '\"';
		tf_CData2 const *pParse = _pStrSource;

		while (*pParse)
		{
			if (*pParse == '\"' || *pParse == '\\')
			{
				*(pDest++) = '\\';
				*(pDest++) = *pParse;
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = '\"';
		*(pDest++) = 0;
		return _pStrDest;
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars, umint _MaxLen)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;

		CData1 *pDest = (CData1 *)_pStrDest;
		if (_MaxLen < 3)
		{
			*pDest = 0;
			return _pStrDest;
		}
		_MaxLen -= 2; // Null charater and one '"'

		CData1 *pMaxDest = (CData1 *)pDest + _MaxLen;
		*(pDest++) = (CEscapeChar)('"');
		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse && pDest < pMaxDest)
		{
			CEscapeChar const *pEscape = (CEscapeChar const *)_pEscapeChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
			{
				if (pDest + 1 >= pMaxDest)
					break;
				*(pDest++) = (CEscapeChar)('\\');
				*(pDest++) = *pParse;
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = (CEscapeChar)('"');
		*(pDest++) = 0;
		return _pStrDest;
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;
		CData1 *pDest = (CData1 *)_pStrDest;

		*(pDest++) = (CEscapeChar)('"');
		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse)
		{
			CEscapeChar const *pEscape = (CEscapeChar const *)_pEscapeChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
			{
				*(pDest++) = (CEscapeChar)('\\');
				*(pDest++) = *pParse;
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = (CEscapeChar)('"');
		*(pDest++) = 0;
		return _pStrDest;
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar, typename tf_CReplaceChar>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars, tf_CReplaceChar const *_pReplaceChars, umint _MaxLen)
	{
		DMibFastCheck(fg_StrLen(_pEscapeChars) == fg_StrLen(_pReplaceChars));
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;
		using CReplaceChar = NTraits::TCUnsigned<tf_CReplaceChar>;

		CData1 *pDest = (CData1 *)_pStrDest;
		if (_MaxLen < 3)
		{
			*pDest = 0;
			return _pStrDest;
		}
		_MaxLen -= 2; // Null charater and one '"'

		CData1 *pMaxDest = (CData1 *)pDest + _MaxLen;
		*(pDest++) = (CEscapeChar)('"');
		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse && pDest < pMaxDest)
		{
			umint iEscape = 0;
			while (((CEscapeChar const *)_pEscapeChars)[iEscape])
			{
				if (*pParse == ((CEscapeChar const *)_pEscapeChars)[iEscape])
					break;
				++iEscape;
			}
			if (_pEscapeChars[iEscape])
			{
				if (pDest + 1 >= pMaxDest)
					break;
				*(pDest++) = (CEscapeChar)('\\');
				*(pDest++) = ((CReplaceChar const *)_pReplaceChars)[iEscape];
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = (CEscapeChar)('"');
		*(pDest++) = 0;
		return _pStrDest;
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar, typename tf_CReplaceChar>
	inline_large tf_CData1 *fg_StrEscapeStr(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars, tf_CReplaceChar const *_pReplaceChars)
	{
		DMibFastCheck(fg_StrLen(_pEscapeChars) == fg_StrLen(_pReplaceChars));
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;
		using CReplaceChar = NTraits::TCUnsigned<tf_CReplaceChar>;

		CData1 *pDest = (CData1 *)_pStrDest;

		*(pDest++) = (CEscapeChar)('"');
		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse)
		{
			umint iEscape = 0;
			while (((CEscapeChar const *)_pEscapeChars)[iEscape])
			{
				if (*pParse == ((CEscapeChar const *)_pEscapeChars)[iEscape])
					break;
				++iEscape;
			}
			if (_pEscapeChars[iEscape])
			{
				*(pDest++) = (CEscapeChar)('\\');
				*(pDest++) = ((CReplaceChar const *)_pReplaceChars)[iEscape];
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = (CEscapeChar)('"');
		*(pDest++) = 0;
		return _pStrDest;
	}

	template<typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, umint _MaxLen)
	{
		tf_CData1 *pDest = _pStrDest;
		if (_MaxLen < 1)
		{
			*pDest = 0;
			return _pStrDest;
		}
		_MaxLen -= 1; // Null charater

		tf_CData1 *pMaxDest = pDest + _MaxLen;
		tf_CData2 const *pParse = _pStrSource;

		while (*pParse && pDest < pMaxDest)
		{
			if (*pParse == '\"' || *pParse == '\\')
			{
				if (pDest + 1 >= pMaxDest)
					break;
				*(pDest++) = '\\';
				*(pDest++) = *pParse;
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = 0;
		return _pStrDest;
	}

	template<typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource)
	{
		tf_CData1 *pDest = _pStrDest;

		tf_CData2 const *pParse = _pStrSource;

		while (*pParse)
		{
			if (*pParse == '\"' || *pParse == '\\')
			{
				*(pDest++) = '\\';
				*(pDest++) = *pParse;
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = 0;
		return _pStrDest;
	}

	template<typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars, umint _MaxLen)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;
		CData1 *pDest = (CData1 *)_pStrDest;
		if (_MaxLen < 1)
		{
			*pDest = 0;
			return _pStrDest;
		}
		_MaxLen -= 1; // Null charater

		CData1 *pMaxDest = (CData1 *)pDest + _MaxLen;
		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse && pDest < pMaxDest)
		{
			CEscapeChar const *pEscape = (CEscapeChar const *)_pEscapeChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
			{
				if (pDest + 1 >= pMaxDest)
					break;
				*(pDest++) = (CEscapeChar)('\\');
				*(pDest++) = *pParse;
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = 0;
		return _pStrDest;
	}

	template<typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;
		CData1 *pDest = (CData1 *)_pStrDest;

		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse)
		{
			CEscapeChar const *pEscape = (CEscapeChar const *)_pEscapeChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
			{
				*(pDest++) = (CEscapeChar)('\\');
				*(pDest++) = *pParse;
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = 0;
		return _pStrDest;
	}

	template<typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar, typename tf_CReplaceChar>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes
		(
			tf_CData1 *_pStrDest
			, tf_CData2 const *_pStrSource
			, tf_CEscapeChar const *_pEscapeChars
			, tf_CReplaceChar const *_pReplaceChars
			, umint _MaxLen
		)
	{
		DMibFastCheck(fg_StrLen(_pEscapeChars) == fg_StrLen(_pReplaceChars));
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;
		using CReplaceChar = NTraits::TCUnsigned<tf_CReplaceChar>;

		CData1 *pDest = (CData1 *)_pStrDest;
		if (_MaxLen < 1)
		{
			*pDest = 0;
			return _pStrDest;
		}
		_MaxLen -= 1; // Null charater

		CData1 *pMaxDest = (CData1 *)pDest + _MaxLen;
		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse && pDest < pMaxDest)
		{
			umint iEscape = 0;
			while (((CEscapeChar const *)_pEscapeChars)[iEscape])
			{
				if (*pParse == ((CEscapeChar const *)_pEscapeChars)[iEscape])
					break;
				++iEscape;
			}
			if (_pEscapeChars[iEscape])
			{
				if (pDest + 1 >= pMaxDest)
					break;
				*(pDest++) = (CEscapeChar)('\\');
				*(pDest++) = ((CReplaceChar const *)_pReplaceChars)[iEscape];
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = 0;
		return _pStrDest;
	}

	template<typename tf_CData1, typename tf_CData2, typename tf_CEscapeChar, typename tf_CReplaceChar>
	inline_large tf_CData1 *fg_StrEscapeStrNoQuotes(tf_CData1 *_pStrDest, tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars, tf_CReplaceChar const *_pReplaceChars)
	{
		DMibFastCheck(fg_StrLen(_pEscapeChars) == fg_StrLen(_pReplaceChars));
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;
		using CReplaceChar = NTraits::TCUnsigned<tf_CReplaceChar>;

		CData1 *pDest = (CData1 *)_pStrDest;

		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse)
		{
			umint iEscape = 0;
			while (((CEscapeChar const *)_pEscapeChars)[iEscape])
			{
				if (*pParse == ((CEscapeChar const *)_pEscapeChars)[iEscape])
					break;
				++iEscape;
			}
			if (_pEscapeChars[iEscape])
			{
				*(pDest++) = (CEscapeChar)('\\');
				*(pDest++) = ((CReplaceChar const *)_pReplaceChars)[iEscape];
				++pParse;
				continue;
			}
			*(pDest++) = *(pParse++);
		}
		*(pDest++) = 0;
		return _pStrDest;
	}

	// Size in chars required for escaped string, EXCLUDING null.
	template<typename tf_CData2>
	inline_large umint fg_StrEscapedLength(tf_CData2 const *_pStrSource)
	{
		umint nEscapedChars = 0;

		++nEscapedChars;	// '"'
		tf_CData2 const *pParse = _pStrSource;

		while (*pParse)
		{
			if (*pParse == '\"' || *pParse == '\\')
			{
				++nEscapedChars;	// '\\'
				++nEscapedChars;	// '<char>'
				++pParse;
				continue;
			}
			++nEscapedChars;	// Char copy
		}
		++nEscapedChars;	// '"'
		//++nEscapedChars;	// Null
		return nEscapedChars;
	}

	// Size in chars required for escaped string, EXCLUDING null.
	template<typename tf_CData2, typename tf_CEscapeChar>
	inline_large umint fg_StrEscapedLength(tf_CData2 const *_pStrSource, tf_CEscapeChar const *_pEscapeChars)
	{
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		using CEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;

		umint nEscapedChars = 0;

		++nEscapedChars;	// '"'
		CData2 const *pParse = (CData2 const *)_pStrSource;

		while (*pParse)
		{
			umint iEscape = 0;
			while (((CEscapeChar const *)_pEscapeChars)[iEscape])
			{
				if (*pParse == ((CEscapeChar const *)_pEscapeChars)[iEscape])
					break;
				++iEscape;
			}
			if (_pEscapeChars[iEscape])
			{
				++nEscapedChars;	// '\\'
				++nEscapedChars;	// '<char>'

				++pParse;
				continue;
			}
			++nEscapedChars;	// Char Copy
			++pParse;
		}
		++nEscapedChars;	// '"'
		// Don't include null.
		// ++nEscapedBytes;	// 0
		return nEscapedChars;
	}

	template <ch8 tf_EscapeChar, typename tf_CChar>
	constexpr bool fg_ParseEscape(tf_CChar const * &_pParse, tf_CChar _Abort)
	{
		auto *pParse = _pParse;
		bool bRet = false;

		int Mode = 0;
		if (*pParse == '\"')
		{
			++pParse;
			Mode = 1;
		}
		while (*pParse)
		{
			if (Mode == 0)
			{
				if (*pParse == _Abort)
				{
					bRet = true;
					break;
				}
				else if (*pParse == tf_EscapeChar)
				{
					Mode = 1;
					++pParse;
					continue;
				}
			}
			else if (Mode == 1)
			{
				if (*pParse == tf_EscapeChar)
				{
					Mode = 0;
					++pParse;
					if (_Abort == tf_EscapeChar)
					{
						bRet = true;
						break;
					}

					continue;
				}
				if (*pParse == '\\')
				{
					++pParse;
					if (*pParse)
						++pParse;
					continue;
				}
			}
			++pParse;
		}

		_pParse = pParse;
		return bRet;
	}

	template <ch8 tf_EscapeChar, typename tf_CStrType>
	tf_CStrType fg_RemoveEscape(tf_CStrType const &_Str)
	{
		tf_CStrType Ret;
		typename tf_CStrType::CChar const *pParse = _Str;
		int Mode = 0;
		while (*pParse)
		{
			if (Mode == 0)
			{
				if (*pParse == tf_EscapeChar)
				{
					Mode = 1;
					++pParse;
					continue;
				}
			}
			else if (Mode == 1)
			{
				if (*pParse == tf_EscapeChar)
				{
					Mode = 0;
					++pParse;
					continue;
				}
				if (*pParse == '\\')
				{
					++pParse;
					if (*pParse)
					{
						Ret.f_AddChar(*pParse);
						++pParse;
					}
					continue;
				}
			}
			Ret.f_AddChar(*pParse);
			++pParse;
		}

		return Ret;
	}

	template <typename tf_CStrType>
	tf_CStrType fg_RemoveEscape(tf_CStrType const &_Str)
	{
		return fg_RemoveEscape<'\"'>(_Str);
	}

	template <ch8 tf_EscapeChar, typename tf_CStrType>
	tf_CStrType fg_GetStrSepEscaped(tf_CStrType &_Str, ch8 const *_pSep)
	{
		typename tf_CStrType::CChar const *pParse = _Str;
		int Mode = 0;

		while (*pParse)
		{
			if (Mode == 0)
			{
				if (*pParse == tf_EscapeChar)
				{
					Mode = 1;
					++pParse;
					continue;
				}

				if (fg_StrStartsWith(pParse, _pSep))
				{
					break;
				}

			}
			else if (Mode == 1)
			{
				if (*pParse == tf_EscapeChar)
				{
					Mode = 0;
					++pParse;
					continue;
				}
				if (*pParse == '\\')
				{
					++pParse;
					if (*pParse)
					{
						++pParse;
					}
					continue;
				}
			}
			++pParse;
		}

		typename tf_CStrType::CChar const *pStart = _Str;
		tf_CStrType Ret = tf_CStrType(pStart, pParse - pStart);

		Ret = Ret.f_TrimLeft();
		Ret = Ret.f_TrimRight();
		Ret = fg_RemoveEscape<tf_EscapeChar>(Ret);

		pParse += fg_StrLen(_pSep);

		_Str = _Str.f_Extract(pParse - pStart);

		return Ret;
	}

	template <typename tf_CStrType>
	tf_CStrType fg_GetStrSepEscaped(tf_CStrType &_Str, ch8 const *_pSep)
	{
		return fg_GetStrSepEscaped<'\"'>(_Str, _pSep);
	}

	template <typename tf_CStr>
	bool fg_StrEscapeBashQuotesNeeded(tf_CStr const &_Str)
	{
		auto const *pParseSigned = _Str.f_GetStr();
		using CUnsignedChar = NTraits::TCUnsigned<NTraits::TCRemoveReferenceAndQualifiers<decltype(*pParseSigned)>>;
		CUnsignedChar const *pParse = (CUnsignedChar const *)pParseSigned;

		while (*pParse)
		{
			if (*pParse <= 32)
				return true;

			switch (*pParse)
			{
			case '*': // Prevent globbing
			case '?': // Prevent globbing
			case '~': // Prevent globbing
			case '#':
			case '$':
			case '`':
			case '\\':
			case ';':
			case '\"':
			case '\'':
			case ',':
			case ':': // Possibly if string starts with this
			case '!': // Sometimes only
			case '(': // Command group
			case ')': // Command group
			case '{': // Brace expansion
			case '}': // Brace expansion
			case '[': // Test
			case ']': // Test
			case '&': // Redirection
			case '<': // Redirection
			case '>': // Redirection
			case '|': // Pipe
			case '-': // Option
			case '=':
			case '+':
			case '%':
			case '^':
				return true;
				break;
			}

			++pParse;
		}

		return false;
	}

	template<typename tf_CStr>
	tf_CStr fg_StrEscapeBashSingleQuotes(tf_CStr const &_Str)
	{
		tf_CStr Return;

		Return.f_AddStr("'");

		auto const* pParse = _Str.f_GetStr();

		while (*pParse)
		{
			if (*pParse == '\'')
				Return.f_AddStr("'\\''");
			else
				Return.f_AddStr(pParse, 1);

			++pParse;
		}

		Return.f_AddStr("'");

		return Return;
	}

	template<typename tf_CStr>
	tf_CStr fg_StrEscapeBashDoubleQuotes(tf_CStr const &_Str)
	{
		tf_CStr Return;

		Return.f_AddStr("\"");

		auto const* pParse = _Str.f_GetStr();

		while (*pParse)
		{
			if (*pParse == '\"')
				Return.f_AddStr("\\\"");
			else if (*pParse == '$')
				Return.f_AddStr("\\$");
			else if (*pParse == '`')
				Return.f_AddStr("\\`");
			else if (*pParse == '\\')
				Return.f_AddStr("\\\\");
			else
				Return.f_AddStr(pParse, 1);

			++pParse;
		}

		Return.f_AddStr("\"");

		return Return;
	}
}
