// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CStrTraits, typename t_CImpParams>
	class TICStrImp_Virtual
	{
	public:
		virtual void f_Destroy() = 0;
		virtual typename t_CStrTraits::CChar *f_GetStr() = 0;
		virtual aint f_CreateWritableBuffer(aint _Length, bool _bDiscard) = 0;
		virtual aint f_GetLength() = 0;
		enum
		{
			mc_AllocatesMemory = true
		};
	};


	template <typename t_CTStrTraits, typename t_CPointerHolder>
	class TCStrImp_Virtual_PtrWrapper : public TCStrAggregate< TCTCStrTraits<typename t_CTStrTraits::CStrTraits, TICStrImp_Virtual<typename t_CTStrTraits::CStrTraits, mint> > >
	{
		constexpr const static bool mc_bInitConstStr = false;

		TCDynamicPtr<t_CPointerHolder, TCStrAggregate< t_CTStrTraits > > m_pStr;

		enum
		{
			mc_AllocatesMemory = TCStrAggregate< t_CTStrTraits >::mc_AllocatesMemory
		};

		virtual void f_Destroy()
		{
			m_pStr->f_Destroy();
		}

		virtual typename t_CTStrTraits::CStrTraits::CChar const*f_GetStr() const
		{
			return m_pStr->f_GetStr();
		}

		virtual aint f_CreateWritableBuffer(aint _Length, bool _bDiscard)
		{
			return m_pStr->f_CreateWritableBuffer(_Length, _bDiscard);
		}

		virtual aint f_GetLength() const
		{
			return m_pStr->f_GetLength();
		}

		virtual bool f_FastLen()
		{
			return m_pStr->f_FastLen();
		}

		virtual void f_Clear()
		{
			return m_pStr->f_Clear();
		}

		virtual void f_SafeClear()
		{
			return m_pStr->f_SafeClear();
		}
	};

	template <typename t_CTStrTraits>
	class TCStrImp_Virtual_TStrWrapper : public TCStr< TCTCStrTraits<typename t_CTStrTraits::CStrTraits, TICStrImp_Virtual<typename t_CTStrTraits::CStrTraits, mint> > >
	{
		constexpr const static bool mc_bInitConstStr = false;

		TCStr< t_CTStrTraits > m_Str;

		enum
		{
			mc_AllocatesMemory = TCStr< t_CTStrTraits >::mc_AllocatesMemory
		};

		virtual void f_Destroy()
		{
			m_Str.f_Destroy();
		}

		virtual typename t_CTStrTraits::CStrTraits::CChar const*f_GetStr() const
		{
			return m_Str.f_GetStr();
		}

		virtual aint f_CreateWritableBuffer(aint _Length, bool _bDiscard)
		{
			return m_Str.f_CreateWritableBuffer(_Length, _bDiscard);
		}

		virtual aint f_GetLength() const
		{
			return m_Str.f_GetLength();
		}

		virtual bool f_FastLen()
		{
			return m_Str.f_FastLen();
		}

		virtual void f_Clear()
		{
			return m_Str.f_Clear();
		}

		virtual void f_SafeClear()
		{
			return m_Str.f_SafeClear();
		}

	};
}
