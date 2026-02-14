// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpConstExpr(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		using CRetType = typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType;
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;

		tf_CData1 const *pStr1 = _pStr1;
		tf_CData2 const *pStr2 = _pStr2;

		while (*pStr1 && *pStr2)
		{
			CRetType Ret0 = CData1(*pStr1);
			CRetType Ret1 = CData2(*pStr2);
			if (Ret0 != Ret1)
				return (Ret0 - Ret1) << 1;

			++pStr1;
			++pStr2;
		}

		if ((*pStr1) && !(*pStr2))
			return 1;

		if (!(*pStr1) && (*pStr2))
			return -1;

		return 0;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		using CRetType = typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType;
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;

		CData1 const *pStr1 = (CData1 const *)_pStr1;
		CData2 const *pStr2 = (CData2 const *)_pStr2;

		while (*pStr1 && *pStr2)
		{
			CRetType Ret0 = *pStr1;
			CRetType Ret1 = *pStr2;
			if (Ret0 != Ret1)
				return (Ret0 - Ret1) << 1;

			++pStr1;
			++pStr2;
		}

		if ((*pStr1) && !(*pStr2))
			return 1;

		if (!(*pStr1) && (*pStr2))
			return -1;

		return 0;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_always typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmp(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		if constexpr (NTraits::cIsSame<tf_CData1, tf_CData2>)
		{
			if (_pStr1 == _pStr2)
				return 0;
		}

		return fg_StrCmpImpl(_pStr1, _pStr2);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrCmpNoCaseIterator(tf_CData1 &_Str1, tf_CData2 &_Str2)
	{
		while (_Str1 && _Str2)
		{
			aint Ret0 = fg_CharLowerCase(*_Str1);
			aint Ret1 = fg_CharLowerCase(*_Str2);

			if (Ret0 != Ret1)
				return (Ret0 - Ret1) << 1;

			++_Str1;
			++_Str2;
		}

		if ((_Str1) && !(_Str2))
			return 1;

		if (!(_Str1) && (_Str2))
			return -1;

		return 0;

	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCaseImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		using CRetType = typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType;
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		CData1 const *pStr1 = (CData1 const *)_pStr1;
		CData2 const *pStr2 = (CData2 const *)_pStr2;

		while (*pStr1 && *pStr2)
		{
			CRetType Ret0 = fg_CharLowerCase(*pStr1);
			CRetType Ret1 = fg_CharLowerCase(*pStr2);

			if (Ret0 != Ret1)
				return (Ret0 - Ret1) << 1;

			++pStr1;
			++pStr2;
		}

		if ((*pStr1) && !(*pStr2))
			return 1;

		if (!(*pStr1) && (*pStr2))
			return -1;

		return 0;

	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_always typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2)
	{
		if constexpr (NTraits::cIsSame<tf_CData1, tf_CData2>)
		{
			if (_pStr1 == _pStr2)
				return 0;
		}

		return fg_StrCmpNoCaseImpl(_pStr1, _pStr2);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, mint _MaxLen)
	{
		using CRetType = typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType;
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		CData1 const *pStr1 = (CData1 const *)_pStr1;
		CData2 const *pStr2 = (CData2 const *)_pStr2;

		CData1 const *pStr1End = pStr1 + _MaxLen;

		while (*pStr1 && *pStr2)
		{
			CRetType Ret0 = *pStr1;
			CRetType Ret1 = *pStr2;
			if (Ret0 != Ret1)
				return (Ret0 - Ret1) << 1;

			++pStr1;
			++pStr2;

			if (pStr1End - pStr1 <= 0)
				return 0;
		}

		if ((*pStr1) && !(*pStr2))
			return 1;

		if (!(*pStr1) && (*pStr2))
			return -1;

		return 0;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_always typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmp(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, mint _MaxLen)
	{
		if (_MaxLen == 0)
			return 0;

		if constexpr (NTraits::cIsSame<tf_CData1, tf_CData2>)
		{
			if (_pStr1 == _pStr2)
				return 0;
		}

		return fg_StrCmpImpl(_pStr1, _pStr2, _MaxLen);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCaseImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, mint _MaxLen)
	{
		using CRetType = typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType;
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		CData1 const *pStr1 = (CData1 const *)_pStr1;
		CData2 const *pStr2 = (CData2 const *)_pStr2;
		CData1 const *pStr1End = pStr1 + _MaxLen;

		while (*pStr1 && *pStr2)
		{
			CRetType Ret0 = fg_CharLowerCase(*pStr1);
			CRetType Ret1 = fg_CharLowerCase(*pStr2);

			if (Ret0 != Ret1)
				return (Ret0 - Ret1) << 1;

			++pStr1;
			++pStr2;
			if (pStr1End - pStr1 <= 0)
				return 0;
		}

		if ((*pStr1) && !(*pStr2))
			return 1;

		if (!(*pStr1) && (*pStr2))
			return -1;

		return 0;

	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_always typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, mint _MaxLen)
	{
		if (_MaxLen == 0)
			return 0;

		if constexpr (NTraits::cIsSame<tf_CData1, tf_CData2>)
		{
			if (_pStr1 == _pStr2)
				return 0;
		}

		return fg_StrCmpNoCaseImpl(_pStr1, _pStr2, _MaxLen);
	}
}
