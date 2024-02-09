// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	class TCStrImp_Dynamic
	{
	public:
		constexpr const static bool mc_bInitConstStr = false;

		typedef typename t_CStrTraits::CChar CChar;
		typedef typename t_CStrTraits::CParams CImpParams;
		typedef typename CImpParams::CAllocator CAllocator;

		TCStrImp_Dynamic() = default;
		constexpr TCStrImp_Dynamic(EAggregateInitialization _Init)
			: m_pData(const_cast<CData *>((CData const *)&mc_EmptyStringData))
		{
		}

		enum
		{
			EMaxExtraChars = CImpParams::EMaxExtraChars
		};

		enum
		{
			mc_AllocatesMemory = true
		};

		struct CData
		{
			inline_small CChar *f_GetData() const;
			inline_small mint f_GetMemorySize() const;
			inline_small void f_SetLength(mint _MemoryLen);
			inline_small void f_RefCountIncrease();
			inline_small void f_RefCountDecrease();

			NAtomic::TCAtomicAggregate<mint> m_RefCount{1};
			mint m_Len:sizeof(mint)*8-2 = 0;
			mint m_bReserved:1 = 0;
			mint m_bConstant:1 = 0;
			mint m_StrLen:sizeof(mint)*8-2 = mc_InvalidStrLen;
			mint m_UserData:2 = 0;

			const static mint mc_InvalidStrLen = ((mint(1) << (sizeof(mint)*8-2))) - 1;
		};

		struct CDataEmpty : public CData
		{
			constexpr CDataEmpty()
				: CData{.m_RefCount = {TCLimitsInt<mint>::mc_Max}, .m_Len = 1, .m_bConstant = true, .m_StrLen = 0}
			{
			}

			CChar m_StringData[1] = {0};
		};

		constexpr static CDataEmpty mc_EmptyStringData = {};

		constexpr static mint mc_MaxAllocChars = (TCLimitsInt<mint>::mc_Max - sizeof(CData)) / sizeof(CChar);
		constexpr static mint mc_MaxStrLen = mc_MaxAllocChars < CData::mc_InvalidStrLen ? mc_MaxAllocChars : CData::mc_InvalidStrLen;
		constexpr static bool mc_bNoThrowConstruct = true;
		constexpr static bool mc_bNoThrowAssign = true;

		CData *m_pData;

		inline_small constexpr void f_Construct()
		{
			m_pData = const_cast<CData *>((CData const *)&mc_EmptyStringData);
		}

		inline_always bool f_IsSameWeak(const TCStrImp_Dynamic &_Right) const
		{
			return m_pData == _Right.m_pData;
		}

		inline_always bool f_IsConstant() const
		{
			return m_pData->m_bConstant;
		}

		inline_medium constexpr void f_Construct(const TCStrImp_Dynamic &_From)
		{
			m_pData = _From.m_pData;

			if_not_consteval
			{
				m_pData->f_RefCountIncrease();
			}
		}

		constexpr void f_Construct(CData const &_Data)
		{
			m_pData = const_cast<CData *>(&_Data);
		}

		inline_medium void f_Construct(TCStrImp_Dynamic &&_From)
		{
			m_pData = _From.m_pData;
			_From.m_pData = const_cast<CData *>((CData const *)&mc_EmptyStringData);
		}

		inline_medium void f_Assign(const TCStrImp_Dynamic &_From)
		{
			_From.m_pData->f_RefCountIncrease();
			m_pData->f_RefCountDecrease();
			m_pData = _From.m_pData;
		}

		inline_medium void f_Assign(TCStrImp_Dynamic &&_From)
		{
			m_pData->f_RefCountDecrease();
			m_pData = _From.m_pData;
			_From.m_pData = const_cast<CData *>((CData const *)&mc_EmptyStringData);
		}

		//=================================
		// Interface

		constexpr inline_medium void f_Destroy()
		{
			if_consteval
			{
				return;
			}
			else
			{
				m_pData->f_RefCountDecrease();
				m_pData = const_cast<CData *>((CData const *)&mc_EmptyStringData);
			}
		}

		inline_small void f_Clear()
		{
			f_Destroy();
		}

		void f_SetUserData(uint8 _Data)
		{
			DMibSafeCheck(_Data < 4, "Only 2 bits available");

			if (m_pData->m_UserData == _Data)
				return;

			if (_Data == 0 && (*f_GetStr()) == 0)
			{
				m_pData->f_RefCountDecrease();
				m_pData = const_cast<CData *>((CData const *)&mc_EmptyStringData);
				return;
			}

			if (m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) > 1 || m_pData->m_bConstant)
			{
				mint StrLen = f_GetStrLen();
				mint Length = fg_Max(mint(m_pData->m_Len), mint(2));
				f_CreateWritableBuffer(Length, false);
				f_GetStrWritable()[StrLen] = 0;
				DMibFastCheck(!m_pData->m_bConstant);
				DMibFastCheck(m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) == 1);
			}

			m_pData->m_UserData = _Data;
		}

		uint8 f_GetUserData() const
		{
			return m_pData->m_UserData;
		}

		inline_small CChar *f_GetStrWritable() const
		{
			DMibSafeCheck(m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) == 1, "Must own str");
			return m_pData->f_GetData(); // Return a const value if string is empty this will make application crash if it writes to this data
		}

		constexpr inline_small const CChar *f_GetStr() const
		{
			return m_pData->f_GetData();
		}

		inline_small mint f_GetRefCount() const
		{
			return m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed);
		}

		constexpr inline_small aint f_GetLength() const
		{
			return m_pData->m_Len;
		}

		constexpr inline_medium aint f_GetStrLen() const
		{
			mint Len = m_pData->m_StrLen;
			if (Len == CData::mc_InvalidStrLen)
				m_pData->m_StrLen = Len = t_CStrTraits::fs_StrLen(m_pData->f_GetData());
			return Len;
		}

		constexpr static inline_small bool f_FastLen()
		{
			return true;
		}

		inline_medium void f_SetStrLen(aint _Len)
		{
			if (!_Len && m_pData->m_UserData == 0)
			{
				if (m_pData->m_bConstant || !m_pData->m_bReserved)
				{
					f_Destroy();
					return;
				}
			}

			aint NewLen;
			aint CurLen = NewLen = m_pData->m_Len;
			m_pData->m_StrLen = _Len < 0 ? CData::mc_InvalidStrLen : _Len;
			if (_Len == -1)
				NewLen = f_GetStrLen() + 1;
			else if (_Len > 0)
				NewLen = _Len+1;

			if (NewLen != CurLen)
			{
				DMibSafeCheck(!m_pData->m_bConstant && m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) == 1, "Must be no other having access to this data");
				f_TrimSize(NewLen);
			}
		}

		inline_small void f_MakeUnique()
		{
			if (m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) > 1)
				f_CreateWritableBuffer(f_GetStrLen()+1, false);
		}

		inline_never static void fs_ThrowLengthException()
		{
			DMibError("String size would exceed maximum size that can be held in a mint");
		}
		mint fp_CalcNewSize(mint _Length)
		{
			if (_Length >= mc_MaxStrLen)
				fs_ThrowLengthException();

			_Length = fg_Max(_Length, fg_Max(sizeof(CData) / (2u * sizeof(CChar)), mint(2u)));

			mint Size = sizeof(CData) + _Length * sizeof(CChar);

			Size = CAllocator::f_SizePadded(mint(2) << NMib::fg_GetHighestBitSetNoZero(Size - 1));

#			if DMibEnableSafeCheck > 0
				mint nChars = (Size - sizeof(CData)) / sizeof(CChar);
				DMibFastCheck(nChars >= _Length);
#			endif

			return Size;
		}

		mint fp_GetOldAllocSize()
		{
			return m_pData->m_Len * sizeof(CChar) + sizeof(CData);
		}

		aint fp_CreateWritableBuffer(aint _Length, bool _bDiscard)
		{
#ifdef DMibDebug
			{
				f_GetRefCount(); // Make sure GetRef() gets linked in in debug build
			}
#endif
			aint CurLen = m_pData->m_Len;
			if (CurLen < _Length)
			{
				if (_Length > 1 || m_pData->m_UserData != 0)
				{
					if (m_pData != &mc_EmptyStringData)
					{
						if (m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) == 1)
						{
							mint CurrentSize = m_pData->f_GetMemorySize();

							if (_bDiscard)
							{
								mint Len = fp_CalcNewSize(_Length);
								auto OldReserved = m_pData->m_bReserved;
								auto OldUserData = m_pData->m_UserData;
								m_pData = new(CAllocator::f_Realloc(m_pData, Len, CurrentSize, EAllocationFlag_SizeNotNeeded)) CData();
								m_pData->f_SetLength(Len);
								m_pData->m_bReserved = OldReserved;
								m_pData->m_UserData = OldUserData;
							}
							else
							{
								mint Len = fp_CalcNewSize(_Length);
								m_pData = (CData *)(CAllocator::f_Resize(m_pData, Len, CurrentSize, EAllocationFlag_SizeNotNeeded));
								m_pData->f_SetLength(Len);
							}
							CurLen = m_pData->m_Len;
						}
						else
						{
							aint OldLen = CurLen;
							mint NewLen = fp_CalcNewSize(_Length);
							CData *pNew = new(CAllocator::f_Alloc(NewLen)) CData();
							pNew->m_StrLen = m_pData->m_StrLen;
							pNew->m_bReserved = m_pData->m_bReserved;
							pNew->m_UserData = m_pData->m_UserData;
							pNew->f_SetLength(NewLen);
							// Remove self from data ref
							CData *pOld = m_pData;
							m_pData = pNew;
							CurLen = m_pData->m_Len;
							if (!_bDiscard)
							{
								mint CopyLen = fg_Min(CurLen, OldLen);
								if (pNew->m_StrLen != CData::mc_InvalidStrLen)
									CopyLen = fg_Min(CurLen, (aint)pNew->m_StrLen + 1);

								NMemory::fg_MemCopy(m_pData->f_GetData(), pOld->f_GetData(), CopyLen * sizeof(CChar));
							}
							pOld->f_RefCountDecrease();
						}
					}
					else
					{
						mint NewLen = fp_CalcNewSize(_Length);
						m_pData = new(CAllocator::f_Alloc(NewLen)) CData();
						DMibFastCheck(m_pData);
						m_pData->f_SetLength(NewLen);
						CurLen = m_pData->m_Len;
						m_pData->f_GetData()[0] = 0;
					}
				}
				else
				{
					m_pData->f_RefCountDecrease();
					m_pData = const_cast<CData *>((CData const *)&mc_EmptyStringData);
					CurLen = m_pData->m_Len;
				}
			}
			else if (m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) > 1)
			{
				mint NewLen = fp_CalcNewSize(_Length);
				CData *pNew = new(CAllocator::f_Alloc(NewLen)) CData();
				pNew->m_StrLen = m_pData->m_StrLen;
				pNew->m_bReserved = m_pData->m_bReserved;
				pNew->m_UserData = m_pData->m_UserData;
				pNew->f_SetLength(NewLen);
				// Remove self from data ref
				aint OldLen = m_pData->m_Len;
				CurLen = pNew->m_Len;
				CData *pOld = m_pData;
				m_pData = pNew;

				if (!_bDiscard)
				{
					mint CopyLen = fg_Min(CurLen, OldLen);
					if (pNew->m_StrLen != CData::mc_InvalidStrLen)
						CopyLen = fg_Min(CurLen, (aint)pNew->m_StrLen + 1);
					NMemory::fg_MemCopy(m_pData->f_GetData(), pOld->f_GetData(), CopyLen * sizeof(CChar));
				}
				pOld->f_RefCountDecrease();
			}

			return CurLen;

		}
		inline aint f_CreateWritableBuffer(aint _Length, bool _bDiscard)
		{
			aint CurLen = m_pData->m_Len;
			if (CurLen >= _Length && m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) == 1)
				return CurLen;

			return fp_CreateWritableBuffer(_Length, _bDiscard);
		}

		void f_Reserve(mint _Len)
		{
			if (_Len)
			{
				f_CreateWritableBuffer(_Len+1, false);
				DMibFastCheck(m_pData != &mc_EmptyStringData);
				m_pData->m_bReserved = true;
			}
			else
			{
				if (m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) == 1)
					m_pData->m_bReserved = false;
			}
		}

		void fp_TrimSize(mint _Length, mint _NeededSize)
		{
			DMibSafeCheck(_Length > 0, "Have to have place for a nullptr character");
			if (_Length == 1 && m_pData->m_UserData == 0)
			{
				m_pData->f_RefCountDecrease();
				m_pData = const_cast<CData *>((CData const *)&mc_EmptyStringData);
				return;
			}

			DMibSafeCheck(!m_pData->m_bConstant, "Must be allocated here or something is wrong");
			if (m_pData->m_RefCount.f_Load(NAtomic::EMemoryOrder_Relaxed) == 1)
			{
				m_pData = (CData *)(CAllocator::f_Resize(m_pData, _NeededSize, m_pData->f_GetMemorySize()));
				m_pData->f_SetLength(_NeededSize);
			}
			else
			{
				CData *pNewData = new(CAllocator::f_Alloc(_NeededSize)) CData();
				pNewData->f_SetLength(_NeededSize);
				NMemory::fg_MemCopy(pNewData->f_GetData(), m_pData->f_GetData(), _Length * sizeof(CChar));
				m_pData->f_RefCountDecrease();
				m_pData = pNewData;
			}
		}

		inline_small void f_TrimSize(mint _Length, mint _MaxExtraChars = EMaxExtraChars)
		{
			DMibSafeCheck(_Length > 0, "Have to have place for a nullptr character");

			if (m_pData->m_bReserved || m_pData->m_bConstant)
				return;

			if (_Length == 1)
				return fp_TrimSize(_Length, _MaxExtraChars);

			// Threshold
			mint NewSize = fp_CalcNewSize(_Length + _MaxExtraChars + 1);
			mint OldSize = fp_GetOldAllocSize();

			if (NewSize < OldSize)
				fp_TrimSize(_Length, NewSize);
		}

		// Interface
		//=================================

	};

	template <mint t_nChars>
	struct TCStrConstData : public TCStrImp_Dynamic<CStr::CTraits::CStrTraits>::CData
	{
		constexpr TCStrConstData(ch8 const (&_String)[t_nChars], uint8 _UserData = 0)
			: TCStrImp_Dynamic<CStr::CTraits::CStrTraits>::CData
			{
				.m_RefCount = {TCLimitsInt<mint>::mc_Max}
				, .m_Len = t_nChars
				, .m_bConstant = true
				, .m_StrLen = t_nChars - 1
				, .m_UserData = _UserData
			}
		{
			for (mint i = 0; i < t_nChars; ++i)
				m_Data[i] = _String[i];
		}

		inline_always constexpr TCStrConstData &f_SetUserData(uint8 _UserData)
		{
			m_UserData = _UserData;

			return *this;
		}

		static constexpr mint mc_nChars = t_nChars;
		ch8 m_Data[t_nChars];
	};

	template <mint t_nChars>
	struct TCStrConstDataAndStr
	{
		constexpr operator NStr::CStr const &() const
		{
			return m_Str;
		}

		TCStrConstData<t_nChars> const m_StrData;
		CStr const m_Str{CStrInitGeneral(), m_StrData};
	};

	template <TCStrConstData t_Data>
	constexpr TCStrConstDataAndStr<decltype(t_Data)::mc_nChars> gc_Str{t_Data};
}
