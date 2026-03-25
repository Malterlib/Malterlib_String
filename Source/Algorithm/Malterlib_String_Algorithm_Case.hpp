// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrUpperCase(tf_CData1 *_pStr)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		CData1 *pStr = (CData1 *)_pStr;

		while (*pStr)
		{
			if (*pStr >= 'a' && *pStr <= 'z')
				*pStr -= 0x20;

			if (*pStr >= 0xe0u && *pStr <= 0xfeu && *pStr != 0xf7u)
				*pStr -= 0x20;

			++pStr;
		}

		return _pStr;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrUpperCase(tf_CData1 *_pStr, umint _MaxLen)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		CData1 *pStr = (CData1 *)_pStr;
		CData1 const *pStrEnd = pStr + _MaxLen;

		while (*pStr && pStr < pStrEnd)
		{
			if (*pStr >= 'a' && *pStr <= 'z')
				*pStr -= 0x20;

			if (*pStr >= 0xe0u && *pStr <= 0xfeu && *pStr != 0xf7u)
				*pStr -= 0x20;

			++pStr;
		}
		return _pStr;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrUpperCase(tf_CData1 *_pDest, umint _MaxDestLen, tf_CData2 const *_pSource)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;

		CData1 *pDest = (CData1 *)_pDest;
		CData1 const *pDestEnd = pDest + (_MaxDestLen - 1);
		CData2 const *pSource = (CData2 const *)_pSource;

		while (*pSource && pDest < pDestEnd)
		{
			if (*pSource >= 'a' && *pSource <= 'z')
				*(pDest++) = (tf_CData1)(*(pSource++) - 0x20);
			else if (*pSource >= 0xe0u && *pSource <= 0xfeu && *pSource != 0xf7u)
				*(pDest++) = (tf_CData1)(*(pSource++) - 0x20);
			else
				*(pDest++) = (tf_CData1)(*(pSource++));
		}

		*pDest = 0;

		return _pDest;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrUpperCase(tf_CData1 *_pDest, umint _MaxDestLen, tf_CData2 const *_pSource, umint _SourceLen)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;

		CData1 *pDest = (CData1 *)_pDest;
		CData1 const *pDestEnd = pDest + (_MaxDestLen - 1);
		CData2 const *pSource = (CData2 const *)_pSource;
		CData2 const *pSourceEnd = pSource + _SourceLen;

		while (*pSource && pSource < pSourceEnd && pDest < pDestEnd)
		{
			if (*pSource >= 'a' && *pSource <= 'z')
				*(pDest++) = (tf_CData1)(*(pSource++) - 0x20);
			else if (*pSource >= 0xe0u && *pSource <= 0xfeu && *pSource != 0xf7u)
				*(pDest++) = (tf_CData1)(*(pSource++) - 0x20);
			else
				*(pDest++) = (tf_CData1)(*(pSource++));
		}

		*pDest = 0;

		return _pDest;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrUpperCase(tf_CData1 *_pDest, tf_CData2 const *_pSource, umint _SourceLen)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;

		CData1 *pDest = (CData1 *)_pDest;
		CData2 const *pSource = (CData2 const *)_pSource;
		CData2 const *pSourceEnd = pSource + _SourceLen;

		while (*pSource && pSource < pSourceEnd)
		{
			if (*pSource >= 'a' && *pSource <= 'z')
				*(pDest++) = (CData1)(*(pSource++) - 0x20);
			else if (*pSource >= 0xe0u && *pSource <= 0xfeu && *pSource != 0xf7u)
				*(pDest++) = (CData1)(*(pSource++) - 0x20);
			else
				*(pDest++) = (CData1)*(pSource++);
		}

		*pDest = 0;

		return _pDest;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrLowerCase(tf_CData1 *_pStr)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;

		CData1 *pStr = (CData1 *)_pStr;

		while (*pStr)
		{
			if (*pStr >= 'A' && *pStr <= 'Z')
				*pStr += 'a' - 'A';
			if (*pStr >= 0xc0u && *pStr <= 0xdeu && *pStr != 0xd7u)
				*pStr += 0xe0u - 0xc0u;
			++pStr;
		}

		return _pStr;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrLowerCase(tf_CData1 *_pStr, umint _MaxLen)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;

		CData1 *pStr = (CData1 *)_pStr;
		CData1 const *pStrEnd = pStr + _MaxLen;

		while (*pStr && pStr < pStrEnd)
		{
			if (*pStr >= 'A' && *pStr <= 'Z')
				*pStr += 'a' - 'A';
			if (*pStr >= 0xc0u && *pStr <= 0xdeu && *pStr != 0xd7u)
				*pStr += 0xe0u - 0xc0u;
			++pStr;
		}

		return _pStr;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrLowerCase(tf_CData1 *_pDest, umint _MaxDestLen, tf_CData2 const *_pSource)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;

		CData1 *pDest = (CData1 *)_pDest;
		CData1 const *pDestEnd = pDest + (_MaxDestLen - 1);
		CData2 const *pSource = (CData2 const *)_pSource;

		while (*pSource && pDest < pDestEnd)
		{
			if (*pSource >= 'A' && *pSource <= 'Z')
				*(pDest++) = (tf_CData1)(*(pSource++) + ('a' - 'A'));
			else if (*pSource >= 0xc0u && *pSource <= 0xdeu && *pSource != 0xd7u)
				*(pDest++) = (tf_CData1)(*(pSource++) + (0xe0u - 0xc0u));
			else
				*(pDest++) = (tf_CData1)(*(pSource++));
		}

		*pDest = 0;

		return _pDest;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrLowerCase(tf_CData1 *_pDest, umint _MaxDestLen, tf_CData2 const *_pSource, umint _SourceLen)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;

		CData1 *pDest = (CData1 *)_pDest;
		CData1 const *pDestEnd = pDest + (_MaxDestLen - 1);
		CData2 const *pSource = (CData2 const *)_pSource;
		CData2 const *pSourceEnd = pSource + _SourceLen;

		while (*pSource && pSource < pSourceEnd && pDest < pDestEnd)
		{
			if (*pSource >= 'A' && *pSource <= 'Z')
				*(pDest++) = (tf_CData1)(*(pSource++) + ('a' - 'A'));
			else if (*pSource >= 0xc0u && *pSource <= 0xdeu && *pSource != 0xd7u)
				*(pDest++) = (tf_CData1)(*(pSource++) + (0xe0u - 0xc0u));
			else
				*(pDest++) = (tf_CData1)(*(pSource++));
		}

		*pDest = 0;

		return _pDest;
	}

	template <typename tf_CData1, typename tf_CData2>
	inline_large tf_CData1 *fg_StrLowerCase(tf_CData1 *_pDest, tf_CData2 const *_pSource, umint _SourceLen)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;

		CData1 *pDest = (CData1 *)_pDest;
		CData2 const *pSource = (CData2 const *)_pSource;
		CData2 const *pSourceEnd = pSource + _SourceLen;

		while (*pSource && pSource < pSourceEnd)
		{
			if (*pSource >= 'A' && *pSource <= 'Z')
				*(pDest++) = (tf_CData1)(*(pSource++) + ('a' - 'A'));
			else if (*pSource >= 0xc0u && *pSource <= 0xdeu && *pSource != 0xd7u)
				*(pDest++) = (tf_CData1)(*(pSource++) + (0xe0u - 0xc0u));
			else
				*(pDest++) = (tf_CData1)(*(pSource++));
		}

		*pDest = 0;

		return _pDest;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrCapitalize(tf_CData1 *_pStr)
	{
		using CData1 = NTraits::TCUnsigned<tf_CData1>;

		CData1 *pStr = (CData1 *)_pStr;

		if (*pStr)
		{
			if (*pStr >= 'a' && *pStr <= 'z')
				*pStr -= 0x20;

			if (*pStr >= 0xe0u && *pStr <= 0xfeu && *pStr != 0xf7u)
				*pStr -= 0x20;

			++pStr;
		}

		return _pStr;
	}

	template <typename tf_CData1>
	inline_large tf_CData1 *fg_StrCapitalize(tf_CData1 *_pStr, umint _MaxLen)
	{
		return fg_StrCapitalize(_pStr);
	}
}
