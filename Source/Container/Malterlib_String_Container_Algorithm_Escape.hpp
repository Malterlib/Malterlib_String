// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits0, typename tf_CTCStrTraits1>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStr(TCStr<tf_CTCStrTraits0> &_StrDest, TCStr<tf_CTCStrTraits1> const &_StrSource)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits0, tf_CTCStrTraits1>::mc_Value, "Not supported");
		using CUnsignedChar = NTraits::TCUnsigned<typename tf_CTCStrTraits1::CStrTraits::CChar>;

		CUnsignedChar const *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		CUnsignedChar const *pParse = (CUnsignedChar const *)pSource;

		umint NeededSize = 3;
		while (*pParse)
		{
			if (*pParse == '\"' || *pParse == '\\')
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename tf_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStr(pDest, pSource, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template <typename tf_CTCStrTraits0, typename tf_CTCStrTraits1, typename tf_CEscapeChar>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStr(TCStr<tf_CTCStrTraits0> &_StrDest, TCStr<tf_CTCStrTraits1> const &_StrSource, tf_CEscapeChar const *_pEscapedChars)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits0, tf_CTCStrTraits1>::mc_Value, "Not supported");

		using CUnsignedChar = NTraits::TCUnsigned<typename tf_CTCStrTraits1::CStrTraits::CChar>;
		using CUnsignedEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;

		CUnsignedChar const *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		CUnsignedChar const *pParse = (CUnsignedChar const *)pSource;

		umint NeededSize = 3;
		while (*pParse)
		{
			CUnsignedEscapeChar const *pEscape = (CUnsignedEscapeChar const *)_pEscapedChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename tf_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStr(pDest, pSource, _pEscapedChars, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template <typename tf_CTCStrTraits0, typename tf_CTCStrTraits1, typename tf_CEscapeChar, typename tf_CReplaceChars>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStr
		(
			TCStr<tf_CTCStrTraits0> &_StrDest
			, TCStr<tf_CTCStrTraits1> const &_StrSource
			, tf_CEscapeChar const *_pEscapedChars
			, tf_CReplaceChars const *_pReplaceChars
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits0, tf_CTCStrTraits1>::mc_Value, "Not supported");

		using CUnsignedChar = NTraits::TCUnsigned<typename tf_CTCStrTraits1::CStrTraits::CChar>;
		using CUnsignedEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;

		CUnsignedChar const *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		CUnsignedChar const *pParse = (CUnsignedChar const *)pSource;

		umint NeededSize = 3;
		while (*pParse)
		{
			CUnsignedEscapeChar const *pEscape = (CUnsignedEscapeChar const *)_pEscapedChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename tf_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStr(pDest, pSource, _pEscapedChars, _pReplaceChars, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template<typename tf_CTCStrTraits0, typename tf_CTCStrTraits1>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStrNoQuotes(TCStr<tf_CTCStrTraits0> &_StrDest, TCStr<tf_CTCStrTraits1> const &_StrSource)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits0, tf_CTCStrTraits1>::mc_Value, "Not supported");

		using CUnsignedChar = NTraits::TCUnsigned<typename tf_CTCStrTraits1::CStrTraits::CChar>;

		CUnsignedChar const *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		CUnsignedChar const *pParse = (CUnsignedChar const *)pSource;

		umint NeededSize = 1;
		while (*pParse)
		{
			if (*pParse == '\"' || *pParse == '\\')
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename tf_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStrNoQuotes(pDest, pSource, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template<typename tf_CTCStrTraits0, typename tf_CTCStrTraits1, typename tf_CEscapeChar>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStrNoQuotes(TCStr<tf_CTCStrTraits0> &_StrDest, TCStr<tf_CTCStrTraits1> const &_StrSource, tf_CEscapeChar const *_pEscapedChars)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits0, tf_CTCStrTraits1>::mc_Value, "Not supported");

		using CUnsignedChar = NTraits::TCUnsigned<typename tf_CTCStrTraits1::CStrTraits::CChar>;
		using CUnsignedEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;

		CUnsignedChar const *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		CUnsignedChar const *pParse = (CUnsignedChar const *)pSource;

		umint NeededSize = 1;
		while (*pParse)
		{
			CUnsignedEscapeChar const *pEscape = (CUnsignedEscapeChar const *)_pEscapedChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename tf_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStrNoQuotes(pDest, pSource, _pEscapedChars, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template<typename tf_CTCStrTraits0, typename tf_CTCStrTraits1, typename tf_CEscapeChar, typename tf_CReplaceChars>
	inline_small TCStr<tf_CTCStrTraits0> &fg_StrEscapeStrNoQuotes
		(
			TCStr<tf_CTCStrTraits0> &_StrDest
			, TCStr<tf_CTCStrTraits1> const &_StrSource
			, tf_CEscapeChar const *_pEscapedChars
			, tf_CReplaceChars const *_pReplaceChars
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits0, tf_CTCStrTraits1>::mc_Value, "Not supported");

		using CUnsignedChar = NTraits::TCUnsigned<typename tf_CTCStrTraits1::CStrTraits::CChar>;
		using CUnsignedEscapeChar = NTraits::TCUnsigned<tf_CEscapeChar>;

		CUnsignedChar const *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		CUnsignedChar const *pParse = (CUnsignedChar const *)pSource;

		umint NeededSize = 1;
		while (*pParse)
		{
			CUnsignedEscapeChar const *pEscape = (CUnsignedEscapeChar const *)_pEscapedChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename tf_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStrNoQuotes(pDest, pSource, _pEscapedChars, _pReplaceChars, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}
}
