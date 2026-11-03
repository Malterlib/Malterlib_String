// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	void TCStr<t_CTCStrTraits>::f_SetStr(tf_CStrDataType *_pStr)
	{
		if (*_pStr != 0)
		{
			aint Length = 0;
			f_AddFromUnicodeIterator(Length, fg_GetUnicodeIterator(_pStr, fg_StrLen(_pStr)));
			CImp::f_SetStrLen(Length);
		}
		else
			this->f_Clear();
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	void TCStr<t_CTCStrTraits>::f_SetStr(tf_CStrDataType const *_pStr, aint _Len)
	{
		if (_Len && *_pStr != 0)
		{
			aint Length = 0;
			f_AddFromUnicodeIterator(Length, fg_GetUnicodeIterator(_pStr, _Len));
			CImp::f_SetStrLen(Length);
		}
		else
			this->f_Clear();
	}

	template <typename t_CTCStrTraits>
	void TCStr<t_CTCStrTraits>::f_SetStr(CChar const *_pStr)
	{
		if (*_pStr != 0)
		{
			aint Length = 0;
			f_AddStrLengthAware(Length, _pStr);
			CImp::f_SetStrLen(Length);
		}
		else
			this->f_Clear();
	}

	template <typename t_CTCStrTraits>
	void TCStr<t_CTCStrTraits>::f_SetStr(CChar const *_pStr, aint _Len)
	{
		if (_Len && *_pStr != 0)
		{
			aint Length = 0;
			CAddStrAgrs Args(Length, _Len);
			f_AddStrLengthAware(Args, _pStr);
			CImp::f_SetStrLen(Length);
		}
		else
			this->f_Clear();
	}

	template <typename t_CTCStrTraits>
	void TCStr<t_CTCStrTraits>::f_SetStr(CAllowNUL _AllowNUL, CChar const *_pStr, aint _Len)
	{
		if (_Len)
		{
			aint Length = 0;
			CAddStrAgrs Args(Length, _Len);
			f_AddStrLengthAware(Args, _pStr);
			CImp::f_SetStrLen(Length);
		}
		else
			this->f_Clear();
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrTraitsF>
	void TCStr<t_CTCStrTraits>::f_SetStr(TCStr<tf_CStrTraitsF> const &_From)
	{
		if constexpr (tf_CStrTraitsF::CStrTraits::mc_Type == EStrType_Ansi && t_CTCStrTraits::CStrTraits::mc_Type != EStrType_Ansi)
		{
			CTempStr Temp;
			if constexpr (tf_CStrTraitsF::CImp::mc_bIsNullTerminated)
				NStr::NPlatform::fg_SystemDecodeAnsiStr(_From.f_GetStr(), Temp);
			else
			{
				using CTempAnsiStr = TCConditional<NTraits::cIsSame<typename CStrTraits::CAllocator, NMemory::CAllocator_NonTrackedHeap>, CAnsiStrNonTracked, CAnsiStr>;
				CTempAnsiStr Ansi(_From.f_GetStr(), _From.f_GetLen());
				NStr::NPlatform::fg_SystemDecodeAnsiStr(Ansi, Temp);
			}
			f_SetStr(Temp);
		}
		else if constexpr (tf_CStrTraitsF::CStrTraits::mc_Type == EStrType_Ansi && t_CTCStrTraits::CStrTraits::mc_Type == EStrType_Ansi)
		{
			aint Length = 0;
			CAddStrAgrs Args(Length, _From.f_GetLen());
			f_AddStrLengthAware(Args, _From.f_GetStr());
			CImp::f_SetStrLen(Length);
		}
		else if constexpr
		(
			tf_CStrTraitsF::CStrTraits::mc_Type != EStrType_Ansi && (tf_CStrTraitsF::CStrTraits::mc_Type == mc_Type && sizeof(CChar) == sizeof(typename tf_CStrTraitsF::CStrTraits::CChar))
		)
		{
			f_SetStr(_From.f_GetStr(), _From.f_GetLen());
		}
		else if constexpr
		(
			tf_CStrTraitsF::CStrTraits::mc_Type != EStrType_Ansi && !(tf_CStrTraitsF::CStrTraits::mc_Type == mc_Type && sizeof(CChar) == sizeof(typename tf_CStrTraitsF::CStrTraits::CChar))
		)
		{
			if (*_From.f_GetStr() != 0)
			{
				aint Length = 0;
				f_AddFromUnicodeIterator(Length, _From.f_GetUnicodeIterator());
				CImp::f_SetStrLen(Length);
			}
			else
				this->f_Clear();
		}
		else
			static_assert(NTraits::gc_MakeValueDependent<false, tf_CStrTraitsF>, "Unhandled case");
	}
}
