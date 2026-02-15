// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

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
		inline_small TCStrImp_Ptr(CChar *_pString, mint _Len);
		inline_small TCStrImp_Ptr(CChar const *_pString, mint _Len);

		inline_small void f_Assign(TCStrImp_Ptr &&_Str);
		inline_small void f_Assign(TCStrImp_Ptr const &_Str);

		inline_small void f_SetPtr(CChar *_pString, mint _Len);
		inline_small void f_SetConstPtr(CChar const *_pString, mint _Len);

		inline_small CChar const *f_GetStr() const;
		inline_small CChar *f_GetStrWritable();

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
		constexpr static mint mc_InvalidStrLen = ((mint(1) << (sizeof(mint)*8-2))) - 1;

		CChar *m_pData;
		mint m_MaxLen;
		mint m_Len;
	};
}

#include "Container/Malterlib_String_Container_ImpPtr.hpp"
