// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	struct TCStrImp_Ptr
	{
		using CChar = typename t_CStrTraits::CChar;

		inline_small TCStrImp_Ptr();
		inline_small TCStrImp_Ptr(TCStrImp_Ptr &&_Str);
		inline_small TCStrImp_Ptr(TCStrImp_Ptr const &_Str);
		inline_small TCStrImp_Ptr(CChar *_pString, umint _Len);
		inline_small TCStrImp_Ptr(CChar const *_pString, umint _Len);

		inline_small void f_Assign(TCStrImp_Ptr &&_Str);
		inline_small void f_Assign(TCStrImp_Ptr const &_Str);

		inline_small void f_SetPtr(CChar *_pString, umint _Len);
		inline_small void f_SetConstPtr(CChar const *_pString, umint _Len);

		inline_small CChar const *f_GetStr() const;
		inline_small CChar *f_GetStrWritable();
		constexpr inline_small bool f_IsEmpty() const;

		inline_medium aint f_GetStrLen() const;
		static inline_small bool f_FastLen();
		inline_small void f_SetStrLen(aint _Len);

		inline_small aint f_GetAllocLength() const;

		inline_small void f_MakeUnique();
		inline_small aint f_CreateWritableBuffer(aint _Length, bool _bDiscard);
		inline_small void f_Destroy();

		inline_small void f_Clear();

		constexpr static bool mc_bInitConstStr = true;
		constexpr static bool mc_bNothrowAssign = true;
		constexpr static bool mc_bIsNullTerminated = false;
		constexpr static umint mc_InvalidStrLen = ((umint(1) << (sizeof(umint)*8-2))) - 1;

		CChar *m_pData;
		umint m_MaxLen;
		umint m_Len;
	};
}

#include "Malterlib_String_Container_ImpPtr.hpp"
