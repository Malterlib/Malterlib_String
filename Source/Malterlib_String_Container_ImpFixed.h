// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CStrTraits, aint t_DataLen>
	class TCStrImp_Fixed
	{
	public:
		constexpr const static bool mc_bInitConstStr = false;
		constexpr const static bool mc_bNothrowAssign = true;

		typedef typename t_CStrTraits::CChar CChar;

		const static mint mc_InvalidStrLen = ((mint(1) << (sizeof(mint)*8-2))) - 1;

		enum
		{
			mc_AllocatesMemory = false
		};


		mint m_Len;
		CChar m_lData[t_DataLen];

		inline_small constexpr TCStrImp_Fixed()
			: m_lData{0}
			, m_Len(0)
		{
		}

		inline_small TCStrImp_Fixed(TCStrImp_Fixed const &_Str)
		{
			mint Len = _Str.f_GetStrLen();
			m_Len = Len;
			//NMib::NMemory::fg_ObjectCopy((CChar *)m_lData, (CChar const*)_Str.m_lData, Len+1);
			NMib::NMemory::fg_MemCopy(m_lData, _Str.m_lData, (Len+1) * sizeof(CChar));
		}

		inline_small constexpr TCStrImp_Fixed(CChar const *_pString, mint _Len)
		{
			mint nChars = fg_Min(t_DataLen - 1, _Len);
			for (mint i = 0; i < nChars; ++i)
				m_lData[i] = _pString[i];
			m_Len = nChars;
		}

		inline_medium void f_Assign(TCStrImp_Fixed const &_Str)
		{
			mint Len = _Str.f_GetStrLen();
			m_Len = Len;
			//NMib::NMemory::fg_ObjectCopy((CChar *)m_lData, (CChar const*)_Str.m_lData, Len+1);
			NMib::NMemory::fg_MemCopy(m_lData, _Str.m_lData, (Len+1) * sizeof(CChar));
		}
		//=================================
		// Interface

		inline_small CChar *f_GetStrWritable()
		{
			return m_lData;
		}


		inline_small const CChar *f_GetStr() const
		{
			return (const CChar *)m_lData;
		}

		inline_small aint f_GetLength() const
		{
			return t_DataLen;
		}

		inline_medium aint f_GetStrLen() const
		{
			if (m_Len == mc_InvalidStrLen)
			{
				const_cast<TCStrImp_Fixed*>(this)->m_Len = t_CStrTraits::fs_StrLen(m_lData);
			}

			return m_Len;
		}

		static inline_small bool f_FastLen()
		{
			return true;
		}

		inline_small void f_MakeUnique()
		{
		}


		inline_small void f_SetStrLen(aint _Len)
		{
			if (_Len < 0)
				m_Len = mc_InvalidStrLen;
			else
				m_Len = _Len;
		}

		inline_small aint f_CreateWritableBuffer(aint _Length, bool _bDiscard)
		{
			return t_DataLen;
		}

		inline_small constexpr void f_Destroy()
		{
			m_lData[0] = 0;
			m_Len = 0;
		}

		inline_small void f_Clear()
		{
			f_Destroy();
		}

		// Interface
		//=================================
	};


	template <typename t_CStrTraits>
	class TCStrImp_Ptr
	{
	public:
		constexpr const static bool mc_bInitConstStr = true;
		constexpr const static bool mc_bNothrowAssign = true;

		typedef typename t_CStrTraits::CChar CChar;

		const static mint mc_InvalidStrLen = ((mint(1) << (sizeof(mint)*8-2))) - 1;

		CChar *m_pData;
		mint m_MaxLen;
		mint m_Len;

		inline_small TCStrImp_Ptr()
		{
			m_pData = nullptr;
			m_MaxLen = 0;
			m_Len = 0;
		}

		inline_small TCStrImp_Ptr(TCStrImp_Ptr &&_Str)
			: m_pData(_Str.m_pData)
			, m_MaxLen(fg_Exchange(_Str.m_MaxLen, 0))
			, m_Len(_Str.m_Len)
		{
		}

		inline_small TCStrImp_Ptr(TCStrImp_Ptr const &_Str)
			: m_pData(_Str.m_pData)
			, m_MaxLen(0)
			, m_Len(_Str.m_Len)
		{
		}

		inline_small TCStrImp_Ptr(CChar *_pString, mint _Len)
		{
			f_SetPtr(_pString, _Len);
		}

		inline_small TCStrImp_Ptr(CChar const *_pString, mint _Len)
		{
			f_SetConstPtr(_pString, _Len);
		}

		inline_small void f_Assign(TCStrImp_Ptr &&_Str)
		{
			m_pData = _Str.m_pData;
			m_MaxLen = _Str.m_MaxLen;
			m_Len = _Str.m_Len;
			_Str.m_MaxLen = 0;
		}

		inline_small void f_Assign(TCStrImp_Ptr const &_Str)
		{
			m_pData = _Str.m_pData;
			m_MaxLen = 0;
			m_Len = _Str.m_Len;
		}

		inline_small void f_SetPtr(CChar *_pString, mint _Len)
		{
			m_pData = _pString;
			m_MaxLen = _Len;
			m_Len = 0;
			m_pData[0] = 0;
		}

		inline_small void f_SetConstPtr(CChar const *_pString, mint _Len)
		{
			m_pData = (CChar *)_pString;
			m_MaxLen = 0;
			m_Len = _Len;
		}

		//=================================
		// Interface

		inline_small CChar *f_GetStrWritable()
		{
			return m_pData;
		}


		inline_small const CChar *f_GetStr() const
		{
			return m_pData;
		}

		inline_small aint f_GetLength() const
		{
			return m_MaxLen;
		}

		inline_medium aint f_GetStrLen() const
		{
			if (m_Len == mc_InvalidStrLen)
			{
				const_cast<TCStrImp_Ptr*>(this)->m_Len = t_CStrTraits::fs_StrLen(m_pData);
			}
			return m_Len;
		}

		static inline_small bool f_FastLen()
		{
			return true;
		}

		inline_small void f_MakeUnique()
		{
		}

		inline_small void f_SetStrLen(aint _Len)
		{
			if (_Len < 0)
				m_Len = mc_InvalidStrLen;
			else
				m_Len = _Len;
		}

		inline_small aint f_CreateWritableBuffer(aint _Length, bool _bDiscard)
		{
			return m_MaxLen;
		}

		inline_small void f_Destroy()
		{
			if (m_MaxLen > 0)
			{
				m_pData[0] = 0;
			}
			m_Len = 0;
		}

		inline_small void f_Clear()
		{
			f_Destroy();
		}

		// Interface
		//=================================
	};
}
