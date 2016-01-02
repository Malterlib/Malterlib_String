// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NStr
	{


		template <typename t_CStrTraits, aint t_DataLen>
		class TCStrImp_Fixed
		{
		public:
#ifndef DMibNoAggregateConstexpr
			constexpr TCStrImp_Fixed(EAggregateInitialization _Init)
				: m_Len{0}
				, m_lData{}
			{
			}
			TCStrImp_Fixed()
			{
			}
#endif
			typedef typename t_CStrTraits::CChar CChar;

			const static mint mc_InvalidStrLen = ((mint(1) << (sizeof(mint)*8-2))) - 1;

			enum
			{
				mc_AllocatesMemory = false
			};


			mint m_Len;
			CChar m_lData[t_DataLen];

			inline_small void f_Construct()
			{
				m_lData[0] = 0;
				m_Len = 0;
			}

			inline_small void f_Construct(const TCStrImp_Fixed &_Str)
			{
				mint Len = _Str.f_GetStrLen();
				m_Len = Len;
				//NMib::NMem::fg_ObjectCopy((CChar *)m_lData, (CChar const*)_Str.m_lData, Len+1);
				NMib::NMem::fg_MemCopy(m_lData, _Str.m_lData, (Len+1) * sizeof(CChar));
			}

			inline_medium void f_Assign(const TCStrImp_Fixed &_Str)
			{
				mint Len = _Str.f_GetStrLen();
				m_Len = Len;
				//NMib::NMem::fg_ObjectCopy((CChar *)m_lData, (CChar const*)_Str.m_lData, Len+1);
				NMib::NMem::fg_MemCopy(m_lData, _Str.m_lData, (Len+1) * sizeof(CChar));
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

			static inline_small bint f_FastLen()
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

			inline_small aint f_CreateWritableBuffer(aint _Length, bint _bDiscard)
			{
				return t_DataLen;
			}

			inline_small void f_Destroy()
			{
				m_lData[0] = 0;
				m_Len = 0;
			}

			inline_small void f_Clear()
			{
				f_Destroy();
			}

			void f_SafeClear()
			{
				NMem::fg_ObjectSet(m_lData, CChar(0), t_DataLen);
				f_Destroy();
			}


			// Interface
			//=================================
		};


		template <typename t_CStrTraits>
		class TCStrImp_Ptr
		{
		public:
			typedef typename t_CStrTraits::CChar CChar;

			const static mint mc_InvalidStrLen = ((mint(1) << (sizeof(mint)*8-2))) - 1;

			CChar *m_pData;
			mint m_MaxLen;
			mint m_Len;

			inline_small void f_Construct()
			{
				m_pData = nullptr;
				m_MaxLen = 0;
				m_Len = 0;
			}

			inline_small void f_Construct(TCStrImp_Ptr &&_Str)
			{
				m_pData = _Str.m_pData;
				m_MaxLen = _Str.m_MaxLen;
				m_Len = _Str.m_Len;
				_Str.m_MaxLen = 0;
			}

			inline_small void f_Construct(TCStrImp_Ptr const &_Str)
			{
				m_pData = _Str.m_pData;
				m_MaxLen = 0;
				m_Len = _Str.m_Len;
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

			static inline_small bint f_FastLen()
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

			inline_small aint f_CreateWritableBuffer(aint _Length, bint _bDiscard)
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

			void f_SafeClear()
			{
				NMem::fg_ObjectSet(m_pData, CChar(0), m_MaxLen);
				f_Destroy();
			}

			// Interface
			//=================================
		};


	}
}

