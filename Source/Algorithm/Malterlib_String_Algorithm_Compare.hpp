// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCaseImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen) noexcept;

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpConstExpr(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2) noexcept
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
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2) noexcept
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
	constexpr inline_always typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmp(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2) noexcept
	{
		if constexpr (NTraits::cIsSame<tf_CData1, tf_CData2>)
		{
			if (_pStr1 == _pStr2)
				return 0;
		}

		return fg_StrCmpImpl(_pStr1, _pStr2);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large aint fg_StrCmpNoCaseIterator(tf_CData1 &_Str1, tf_CData2 &_Str2) noexcept
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
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCaseImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2) noexcept
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
	constexpr inline_always typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2) noexcept
	{
		if constexpr (NTraits::cIsSame<tf_CData1, tf_CData2>)
		{
			if (_pStr1 == _pStr2)
				return 0;
		}

		return fg_StrCmpNoCaseImpl(_pStr1, _pStr2);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen) noexcept
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
	constexpr inline_always typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmp(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen) noexcept
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

	template <bool t_bNoCase, bool t_bUseLen1, bool t_bUseLen2, typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpLengthAware(tf_CData1 const *_pStr1, umint _Len1, tf_CData2 const *_pStr2, umint _Len2) noexcept
	{
		using CRetType = typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType;
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		CData1 const *pStr1 = (CData1 const *)_pStr1;
		CData2 const *pStr2 = (CData2 const *)_pStr2;
		umint iCompare = 0;

		while (true)
		{
			if constexpr (t_bUseLen1)
			{
				if (iCompare >= _Len1)
					break;
			}
			else if (pStr1[iCompare] == 0)
				break;

			if constexpr (t_bUseLen2)
			{
				if (iCompare >= _Len2)
					break;
			}
			else if (pStr2[iCompare] == 0)
				break;

			CRetType Ret0;
			CRetType Ret1;
			if constexpr (t_bNoCase)
			{
				Ret0 = fg_CharLowerCase(pStr1[iCompare]);
				Ret1 = fg_CharLowerCase(pStr2[iCompare]);
			}
			else
			{
				Ret0 = pStr1[iCompare];
				Ret1 = pStr2[iCompare];
			}

			if (Ret0 != Ret1)
				return (Ret0 - Ret1) << 1;

			++iCompare;
		}

		bool bStr1Ended;
		if constexpr (t_bUseLen1)
			bStr1Ended = iCompare >= _Len1;
		else
			bStr1Ended = pStr1[iCompare] == 0;

		bool bStr2Ended;
		if constexpr (t_bUseLen2)
			bStr2Ended = iCompare >= _Len2;
		else
			bStr2Ended = pStr2[iCompare] == 0;

		if (!bStr1Ended && bStr2Ended)
			return 1;
		if (bStr1Ended && !bStr2Ended)
			return -1;

		return 0;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmp(tf_CData1 const *_pStr1, umint _Len1, tf_CData2 const *_pStr2, umint _Len2) noexcept
	{
		return fg_StrCmpLengthAware<false, true, true>(_pStr1, _Len1, _pStr2, _Len2);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmp(tf_CData1 const *_pStr1, umint _Len1, tf_CData2 const *_pStr2) noexcept
	{
		return fg_StrCmpLengthAware<false, true, false>(_pStr1, _Len1, _pStr2, 0);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCase(tf_CData1 const *_pStr1, umint _Len1, tf_CData2 const *_pStr2, umint _Len2) noexcept
	{
		return fg_StrCmpLengthAware<true, true, true>(_pStr1, _Len1, _pStr2, _Len2);
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCase(tf_CData1 const *_pStr1, umint _Len1, tf_CData2 const *_pStr2) noexcept
	{
		return fg_StrCmpLengthAware<true, true, false>(_pStr1, _Len1, _pStr2, 0);
	}

	template <bool t_bNoCase, bool t_bUseLen1, bool t_bUseLen2, typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpMaxLengthAware(tf_CData1 const *_pStr1, umint _Len1, tf_CData2 const *_pStr2, umint _Len2, umint _MaxLen) noexcept
	{
		using CRetType = typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType;
		using CData1 = NTraits::TCUnsigned<tf_CData1>;
		using CData2 = NTraits::TCUnsigned<tf_CData2>;
		CData1 const *pStr1 = (CData1 const *)_pStr1;
		CData2 const *pStr2 = (CData2 const *)_pStr2;

		umint iCompare = 0;

		while (iCompare < _MaxLen)
		{
			if constexpr (t_bUseLen1)
			{
				if (iCompare >= _Len1)
					break;
			}
			else if (pStr1[iCompare] == 0)
				break;

			if constexpr (t_bUseLen2)
			{
				if (iCompare >= _Len2)
					break;
			}
			else if (pStr2[iCompare] == 0)
				break;

			CRetType Ret0;
			CRetType Ret1;
			if constexpr (t_bNoCase)
			{
				Ret0 = fg_CharLowerCase(pStr1[iCompare]);
				Ret1 = fg_CharLowerCase(pStr2[iCompare]);
			}
			else
			{
				Ret0 = pStr1[iCompare];
				Ret1 = pStr2[iCompare];
			}

			if (Ret0 != Ret1)
				return (Ret0 - Ret1) << 1;

			++iCompare;
		}

		if (iCompare >= _MaxLen)
			return 0;

		bool bStr1Ended;
		if constexpr (t_bUseLen1)
			bStr1Ended = iCompare >= _Len1;
		else
			bStr1Ended = pStr1[iCompare] == 0;

		bool bStr2Ended;
		if constexpr (t_bUseLen2)
			bStr2Ended = iCompare >= _Len2;
		else
			bStr2Ended = pStr2[iCompare] == 0;

		if (!bStr1Ended && bStr2Ended)
			return 1;
		if (bStr1Ended && !bStr2Ended)
			return -1;

		return 0;
	}

	template <typename tf_CData1, typename tf_CData2>
	constexpr inline_large typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCaseImpl(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen) noexcept
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
	constexpr inline_always typename TCChooseStrCompareType<tf_CData1, tf_CData2>::CType fg_StrCmpNoCase(tf_CData1 const *_pStr1, tf_CData2 const *_pStr2, umint _MaxLen) noexcept
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
