// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CStrTraits, typename t_CImpParams>
	struct TICStrImp_Virtual
	{
	public:
		virtual void f_Destroy() = 0;
		virtual typename t_CStrTraits::CChar *f_GetStr() = 0;
		virtual aint f_CreateWritableBuffer(aint _Length, bool _bDiscard) = 0;
		virtual aint f_GetAllocLength() = 0;

		constexpr static bool mc_AllocatesMemory = true;
	};

	template <typename t_CTStrTraits>
	struct TCStrImp_Virtual_PtrWrapper : public TCStr< TCTCStrTraits<typename t_CTStrTraits::CStrTraits, TICStrImp_Virtual<typename t_CTStrTraits::CStrTraits, umint>>>
	{
		virtual void f_Destroy();
		virtual typename t_CTStrTraits::CStrTraits::CChar const *f_GetStr() const;
		virtual aint f_CreateWritableBuffer(aint _Length, bool _bDiscard);
		virtual aint f_GetAllocLength() const;
		virtual bool f_FastLen();
		virtual void f_Clear();

		constexpr static bool mc_bInitConstStr = false;
		constexpr static bool mc_AllocatesMemory = TCStr< t_CTStrTraits >::mc_AllocatesMemory;

		TCStr<t_CTStrTraits> *m_pStr;
	};

	template <typename t_CTStrTraits>
	struct TCStrImp_Virtual_TStrWrapper : public TCStr< TCTCStrTraits<typename t_CTStrTraits::CStrTraits, TICStrImp_Virtual<typename t_CTStrTraits::CStrTraits, umint>>>
	{
		virtual void f_Destroy();
		virtual typename t_CTStrTraits::CStrTraits::CChar const *f_GetStr() const;
		virtual aint f_CreateWritableBuffer(aint _Length, bool _bDiscard);
		virtual aint f_GetAllocLength() const;
		virtual bool f_FastLen();
		virtual void f_Clear();

		constexpr static bool mc_bInitConstStr = false;
		constexpr static bool mc_AllocatesMemory = TCStr< t_CTStrTraits >::mc_AllocatesMemory;

		TCStr<t_CTStrTraits> m_Str;
	};
}

#include "Malterlib_String_Container_ImpVirtual.hpp"
