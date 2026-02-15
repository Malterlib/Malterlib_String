// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CStrTraits, aint t_DataLen>
	struct TCStrImp_Fixed
	{
		using CChar = typename t_CStrTraits::CChar;

		inline_small constexpr TCStrImp_Fixed();
		inline_small TCStrImp_Fixed(TCStrImp_Fixed const &_Str);
		inline_small constexpr TCStrImp_Fixed(CChar const *_pString, mint _Len);

		inline_medium void f_Assign(TCStrImp_Fixed const &_Str);
		inline_small constexpr void f_Destroy();
		inline_small void f_Clear();

		inline_small CChar const *f_GetStr() const;
		inline_small CChar *f_GetStrWritable();

		inline_medium aint f_GetStrLen() const;
		inline_small void f_SetStrLen(aint _Len);

		inline_small aint f_GetAllocLength() const;
		static inline_small bool f_FastLen();

		inline_small void f_MakeUnique();
		inline_small aint f_CreateWritableBuffer(aint _Length, bool _bDiscard);

		constexpr static bool mc_bInitConstStr = false;
		constexpr static bool mc_bNothrowAssign = true;
		constexpr static mint mc_InvalidStrLen = ((mint(1) << (sizeof(mint)*8-2))) - 1;
		constexpr static bool mc_AllocatesMemory = false;

		mint m_Len;
		CChar m_lData[t_DataLen];
	};
}

#include "Container/Malterlib_String_Container_ImpFixed.hpp"
