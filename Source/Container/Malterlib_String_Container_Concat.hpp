// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	inline_small void TCStr<t_CTCStrTraits>::f_AddChar(tf_CStrDataType _Char)
	{
		aint Length = f_GetLen();
		f_AddCharLengthAware(Length, _Char);
		CImp::f_SetStrLen(Length);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	void TCStr<t_CTCStrTraits>::f_AddChars(tf_CStrDataType _Char, aint _Count)
	{
		aint Length = f_GetLen();
		f_AddCharsLengthAware(Length, _Char, _Count);
		CImp::f_SetStrLen(Length);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	void TCStr<t_CTCStrTraits>::f_AddStr(tf_CStrDataType *_pStr)
	{
		if (*_pStr != 0)
		{
			aint Length = f_GetLen();
			f_AddFromUnicodeIterator(Length, fg_GetUnicodeIterator(_pStr, fg_StrLen(_pStr)));
			CImp::f_SetStrLen(Length);
		}
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	void TCStr<t_CTCStrTraits>::f_AddStr(tf_CStrDataType const *_pStr, aint _Len)
	{
		if (_Len && *_pStr != 0)
		{
			aint Length = f_GetLen();
			f_AddFromUnicodeIterator(Length, fg_GetUnicodeIterator(_pStr, _Len));
			CImp::f_SetStrLen(Length);
		}
	}

	template <typename t_CTCStrTraits>
	void TCStr<t_CTCStrTraits>::f_AddStr(CChar const *_pStr)
	{
		if (*_pStr != 0)
		{
			aint Length = f_GetLen();
			f_AddStrLengthAware(Length, _pStr);
			CImp::f_SetStrLen(Length);
		}
	}

	template <typename t_CTCStrTraits>
	void TCStr<t_CTCStrTraits>::f_AddStr(CChar const *_pStr, aint _Len)
	{
		if (_Len && *_pStr != 0)
		{
			aint Length = f_GetLen();
			CAddStrAgrs Args(Length, _Len);
			f_AddStrLengthAware(Args, _pStr);
			CImp::f_SetStrLen(Length);
		}
	}

	template <typename t_TCStrTraits>
	template <typename t_CStrTraitsF>
	void TCStr<t_TCStrTraits>::f_AddStr(TCStr<t_CStrTraitsF> const &_From)
	{
		if constexpr (t_CStrTraitsF::CStrTraits::mc_Type == EStrType_Ansi && t_TCStrTraits::CStrTraits::mc_Type != EStrType_Ansi)
		{
			CTempStr Temp;
			NSys::NStr::fg_SystemDecodeAnsiStr(_From.f_GetStr(), Temp);
			f_AddStr(Temp);
		}
		else if constexpr (t_CStrTraitsF::CStrTraits::mc_Type == EStrType_Ansi && t_TCStrTraits::CStrTraits::mc_Type == EStrType_Ansi)
		{
			aint Length = f_GetLen();
			CAddStrAgrs Args(Length, _From.f_GetLen());
			f_AddStrLengthAware(Args, _From.f_GetStr());
			CImp::f_SetStrLen(Length);
		}
		else if constexpr
			(
				t_CStrTraitsF::CStrTraits::mc_Type != EStrType_Ansi && (t_CStrTraitsF::CStrTraits::mc_Type == mc_Type && sizeof(CChar) == sizeof(typename t_CStrTraitsF::CStrTraits::CChar))
			)
		{
			f_AddStr(_From.f_GetStr(), _From.f_GetLen());
		}
		else if constexpr
			(
				t_CStrTraitsF::CStrTraits::mc_Type != EStrType_Ansi && !(t_CStrTraitsF::CStrTraits::mc_Type == mc_Type && sizeof(CChar) == sizeof(typename t_CStrTraitsF::CStrTraits::CChar))
			)
		{
			if (*_From.f_GetStr() != 0)
			{
				aint Length = f_GetLen();
				f_AddFromUnicodeIterator(Length, _From.f_GetUnicodeIterator());
				CImp::f_SetStrLen(Length);
			}
		}
		else
		{
			static_assert(NTraits::gc_MakeValueDependent<false, t_CStrTraitsF>, "Unhandled case");
		}
	}

	template <typename t_TCStrTraits>
	template <typename tf_CStrIterator>
	void TCStr<t_TCStrTraits>::f_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From)
	{
		fp_AddFromUnicodeIterator<sizeof(CChar)>(_StrLen, _From);
	}

	template <typename t_TCStrTraits>
	void TCStr<t_TCStrTraits>::f_AddUnicodeChar(ch32 _Character)
	{
		if constexpr (sizeof(CChar) == 1)
		{
			static_assert( mc_Type == EStrType_UTF, "Lossy conversion");

			aint CurrentLength = f_GetLen();

			bool bSuccess = fg_EncodeUTF8Char<true>
				(
					_Character
					, [&](mint _nChars) inline_always_lambda -> CChar *
					{
						mint NeededLen = CurrentLength + _nChars + 1;
						mint MaxLen = CImp::f_CreateWritableBuffer(NeededLen, false);

						if (MaxLen < NeededLen)
							return nullptr;

						auto pOut = CImp::f_GetStrWritable() + CurrentLength;
						pOut[_nChars] = 0;

						CurrentLength += _nChars;

						return pOut;
					}
				)
			;

			if (bSuccess)
				CImp::f_SetStrLen(CurrentLength);
		}
		else if constexpr (sizeof(CChar) == 2)
		{
			static_assert(mc_Type == EStrType_UTF, "Lossy conversion");

			aint CurrentLength = f_GetLen();

			bool bSuccess = fg_EncodeUTF16Char<true>
				(
					_Character
					, [&](mint _nChars) inline_always_lambda -> CChar *
					{
						mint NeededLen = CurrentLength + _nChars + 1;
						mint MaxLen = CImp::f_CreateWritableBuffer(NeededLen, false);

						if (MaxLen < NeededLen)
							return nullptr;

						auto pOut = CImp::f_GetStrWritable() + CurrentLength;
						pOut[_nChars] = 0;

						CurrentLength += _nChars;

						return pOut;
					}
				)
			;

			if (bSuccess)
				CImp::f_SetStrLen(CurrentLength);
		}
		else
			f_AddChar(_Character);
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize, typename tf_CStrIterator>
	TCEnableIf<t_CharSize == 1, void> TCStr<t_TCStrTraits>::fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From)
	{
		static_assert(sizeof(CChar) == 1 && mc_Type == EStrType_UTF, "Lossy conversion");

		mint LenNeeded = _StrLen;
		auto fCalcLen = [&](mint _nChars) inline_always_lambda -> ch8 *
			{
				LenNeeded += _nChars;
				return nullptr;
			}
		;
		auto Iter = _From;
		while (Iter)
		{
			fg_EncodeUTF8Char<true>(*Iter, fCalcLen);
			++Iter;
		}
		mint MaxLen = CImp::f_CreateWritableBuffer(LenNeeded + 1, false);
		auto *pOut = CImp::f_GetStrWritable();
		auto *pOutStart = pOut;
		auto *pOutMax = pOut + MaxLen - 1;

		pOut += _StrLen;

		auto fAddChars = [&](mint _nChars) inline_always_lambda -> ch8 *
			{
				if (pOut + _nChars > pOutMax)
					return nullptr;
				auto *pRet = pOut;
				pOut += _nChars;
				return (ch8 *)pRet;
			}
		;

		Iter = _From;
		while (Iter)
		{
			if (!fg_EncodeUTF8Char<true>(*Iter, fAddChars))
				break;
			++Iter;
		}

		*pOut = 0;
		_StrLen = pOut - pOutStart;
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize, typename tf_CStrIterator>
	TCEnableIf<t_CharSize == 2, void> TCStr<t_TCStrTraits>::fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From)
	{
		static_assert(sizeof(CChar) == 2 && mc_Type == EStrType_UTF, "Lossy conversion");
		mint LenNeeded = _StrLen;
		auto fCalcLen = [&](mint _nChars) inline_always_lambda -> ch16 *
			{
				LenNeeded += _nChars;
				return nullptr;
			}
		;
		auto Iter = _From;
		while (Iter)
		{
			fg_EncodeUTF16Char<true>(*Iter, fCalcLen);
			++Iter;
		}
		mint MaxLen = CImp::f_CreateWritableBuffer(LenNeeded + 1, false);
		auto *pOut = CImp::f_GetStrWritable();
		auto *pOutStart = pOut;
		auto *pOutMax = pOut + MaxLen - 1;

		pOut += _StrLen;

		auto fAddChars = [&](mint _nChars) inline_always_lambda -> ch16 *
			{
				if (pOut + _nChars > pOutMax)
					return nullptr;
				auto *pRet = pOut;
				pOut += _nChars;
				return (ch16 *)pRet;
			}
		;

		Iter = _From;
		while (Iter)
		{
			if (!fg_EncodeUTF16Char<true>(*Iter, fAddChars))
				break;
			++Iter;
		}

		*pOut = 0;
		_StrLen = pOut - pOutStart;
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize, typename tf_CStrIterator>
	TCEnableIf<t_CharSize != 1 && t_CharSize != 2, void> TCStr<t_TCStrTraits>::fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From)
	{
		static_assert(sizeof(CChar) == 4 && mc_Type == EStrType_Unicode, "Lossy conversion");
		mint LenNeeded = _StrLen;
		auto Iter = _From;
		while (Iter)
		{
			++LenNeeded;
			++Iter;
		}
		mint MaxLen = CImp::f_CreateWritableBuffer(LenNeeded + 1, false);
		auto *pOut = CImp::f_GetStrWritable();
		auto *pOutStart = pOut;
		auto *pOutMax = pOut + MaxLen - 1;

		pOut += _StrLen;

		Iter = _From;
		while (Iter)
		{
			if (pOut >= pOutMax)
				break;

			*pOut = *Iter;
			++pOut;
			++Iter;
		}

		*pOut = 0;
		_StrLen = pOut - pOutStart;
	}

	template <typename t_TCStrTraits>
	template <typename tf_CStrDataType>
	inline_medium void TCStr<t_TCStrTraits>::f_AddCharLengthAware(aint &_StrLen, tf_CStrDataType _Char)
	{
		aint MaxLen = CImp::f_CreateWritableBuffer(_StrLen + 2, false);
		if (MaxLen >= (_StrLen + 2))
		{
			CUnsignedChar *pStr = (CUnsignedChar *)CImp::f_GetStrWritable();
			pStr[_StrLen++] = (CUnsignedChar)(NTraits::TCUnsigned<tf_CStrDataType>)_Char;
			pStr[_StrLen] = 0;
		}
	}

	template <typename t_TCStrTraits>
	inline_small void TCStr<t_TCStrTraits>::f_AddStrLengthAwareInline(CAddStrAgrs const &_Args, CChar const *_pStr)
	{
		aint WantLen = _Args.m_StrLen + _Args.m_Len + 1;
		aint MaxLen = fg_Min(CImp::f_CreateWritableBuffer(WantLen, false), WantLen) - 1;

		CUnsignedChar *pWritable = (CUnsignedChar *)CImp::f_GetStrWritable();

		CUnsignedChar const *pStr = (CUnsignedChar const *)_pStr;
		CUnsignedChar *pWrite = pWritable + _Args.m_StrLen;
		mint AddLen = MaxLen - _Args.m_StrLen;
		CUnsignedChar *pEnd = pWrite + AddLen;
		DMibFastCheck(AddLen <= _Args.m_Len);
		while (pWrite < pEnd)
			*(pWrite++) = *(pStr++);

		*pWrite = 0;
		_Args.m_StrLen = MaxLen;
	}

	template <typename t_TCStrTraits>
	template <typename tf_CStrDataType>
	inline_large void TCStr<t_TCStrTraits>::f_AddCharsLengthAware(aint &_StrLen, tf_CStrDataType _Char, aint _Count)
	{
		aint WantLen = _StrLen + _Count + 1;
		aint MaxLen = fg_Min(CImp::f_CreateWritableBuffer(WantLen, false), WantLen) - 1;
		CUnsignedChar *pStartPtr = (CUnsignedChar *)CImp::f_GetStrWritable();
		CUnsignedChar *pWritePtr = pStartPtr + _StrLen;
		CUnsignedChar const *pEndPtr;
		pEndPtr = pWritePtr + (MaxLen - _StrLen);

		while (pWritePtr < pEndPtr)
			*(pWritePtr++) = (CUnsignedChar)(NTraits::TCUnsigned<tf_CStrDataType>)_Char;

		*pWritePtr = 0;
		_StrLen = pWritePtr - pStartPtr;
	}

	template <typename t_TCStrTraits>
	inline_large void TCStr<t_TCStrTraits>::f_AddStrLengthAware(aint &_StrLen, CChar const *_pStr)
	{
		CChar const *pReadPtr = _pStr;
		aint Grow = 32;
		while (*pReadPtr)
		{
			aint MaxLen = CImp::f_CreateWritableBuffer(_StrLen + Grow, false) - 1;
			if (MaxLen <= (_StrLen)) // No more room in str
				return;

			CUnsignedChar *pWritePtr = (CUnsignedChar *)CImp::f_GetStrWritable();
			CUnsignedChar const *pWritePtrEnd = pWritePtr + MaxLen;
			pWritePtr += _StrLen;

			while (*pReadPtr && pWritePtr < pWritePtrEnd)
			{
				*(pWritePtr++) = (CUnsignedChar)(*(pReadPtr++));
			}

			*pWritePtr = 0;
			_StrLen = (pWritePtr - (CUnsignedChar const *)f_GetStr());
			Grow <<= 1;
		}
	}

	template <typename t_TCStrTraits>
	inline_extralarge void TCStr<t_TCStrTraits>::f_AddStrLengthAware(CAddStrAgrs const &_Args, CChar const *_pStr)
	{
		aint WantLen = _Args.m_StrLen + _Args.m_Len + 1;
		aint MaxLen = fg_Min(CImp::f_CreateWritableBuffer(WantLen, false), WantLen) - 1;

		CUnsignedChar *pWritable = (CUnsignedChar *)CImp::f_GetStrWritable();

		if (_Args.m_Len <= (8/sizeof(CChar)))
		{
			CUnsignedChar const *pStr = (CUnsignedChar const *)_pStr;
			CUnsignedChar *pWrite = pWritable + _Args.m_StrLen;
			CUnsignedChar *pEnd = pWrite + (MaxLen - _Args.m_StrLen);
			while (pWrite < pEnd)
			{
				*(pWrite++) = *(pStr++);
			}

			*pWrite = 0;
			_Args.m_StrLen = MaxLen;

			//			CChar *pWrite = f_GetStr() + _StrLen;
			//			*(pWrite++) = *(_pStr);
			//			*pWrite = 0;
			//			_StrLen = MaxLen;
		}
		else
		{
			NMib::NMemory::fg_MemCopy((pWritable + _Args.m_StrLen), _pStr, (MaxLen - _Args.m_StrLen) * sizeof(CChar));
			_Args.m_StrLen = MaxLen;
			pWritable[MaxLen] = 0;

		}
	}
}
