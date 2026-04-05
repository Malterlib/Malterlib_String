// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <umint t_nChars, typename t_CChar>
	constexpr TCStrConstData<t_nChars, t_CChar>::TCStrConstData(t_CChar const (&_String)[t_nChars], uint8 _UserData)
		: TCStrImp_Dynamic_StringData<t_CChar>
		{
			.m_RefCount = {TCLimitsInt<umint>::mc_Max}
			, .m_Len = t_nChars
			, .m_bConstant = true
			, .m_StrLen = t_nChars - 1
			, .m_UserData = _UserData
		}
	{
		for (umint i = 0; i < t_nChars; ++i)
			m_Data[i] = _String[i];
	}

	template <umint t_nChars, typename t_CChar>
	inline_always constexpr auto TCStrConstData<t_nChars, t_CChar>::f_SetUserData(uint8 _UserData) -> TCStrConstData &
	{
		this->m_UserData = _UserData;

		return *this;
	}

	template <typename t_CChar>
	constexpr TCStrImp_Dynamic_EmptyStringData<t_CChar>::TCStrImp_Dynamic_EmptyStringData()
		: TCStrImp_Dynamic_StringData<t_CChar>
		{
			.m_RefCount = {TCLimitsInt<umint>::mc_Max}
			, .m_Len = 1
			, .m_bConstant = true
			, .m_StrLen = 0
			, .m_UserData = 0
		}
	{
	}

	template <typename t_CChar>
	inline_always constexpr TCStrImp_Dynamic_StringData<t_CChar> *TCStrImp_Dynamic_EmptyStringData<t_CChar>::f_MutableData() const
	{
		return const_cast<TCStrImp_Dynamic_StringData<t_CChar> *>(static_cast<TCStrImp_Dynamic_StringData<t_CChar> const *>(this));
	}

	template <typename t_CChar>
	inline_small auto TCStrImp_Dynamic_StringData<t_CChar>::f_GetData() const -> t_CChar *
	{
		return (t_CChar *)(this+1);
	}

	template <typename t_CChar>
	inline_small void TCStrImp_Dynamic_StringData<t_CChar>::f_SetLength(umint _MemoryLen)
	{
		m_Len = (_MemoryLen - sizeof(*this)) / sizeof(t_CChar);
	}

	template <typename t_CChar>
	inline_small umint TCStrImp_Dynamic_StringData<t_CChar>::f_GetMemorySize() const
	{
		return m_Len * sizeof(t_CChar) + sizeof(*this);
	}

	template <typename t_CChar>
	inline_small void TCStrImp_Dynamic_StringData<t_CChar>::f_RefCountIncrease()
	{
		if (m_bConstant)
			return;

		m_RefCount.f_FetchAdd(1, NAtomic::gc_MemoryOrder_Release);
	}

	template <typename t_CChar>
	inline_small bool TCStrImp_Dynamic_StringData<t_CChar>::f_RefCountDecrease()
	{
		if (m_bConstant)
			return false;

		return m_RefCount.f_FetchSub(1, NAtomic::gc_MemoryOrder_AcquireRelease) == 1;
	}

	template <typename t_CStrTraits>
	constexpr TCStrImp_Dynamic<t_CStrTraits>::~TCStrImp_Dynamic()
	{
		if_consteval
		{
			return;
		}
		else
		{
			if (m_pData->f_RefCountDecrease())
				CAllocator::f_Free(m_pData, m_pData->f_GetMemorySize());
		}
	}

	template <typename t_CStrTraits>
	inline_medium constexpr TCStrImp_Dynamic<t_CStrTraits>::TCStrImp_Dynamic(TCStrImp_Dynamic const &_From)
		: m_pData(_From.m_pData)
	{
		if_not_consteval
		{
			m_pData->f_RefCountIncrease();
		}
	}

	template <typename t_CStrTraits>
	constexpr TCStrImp_Dynamic<t_CStrTraits>::TCStrImp_Dynamic(CData const &_Data)
		: m_pData(const_cast<CData *>(&_Data))
	{
	}

	template <typename t_CStrTraits>
	inline_medium TCStrImp_Dynamic<t_CStrTraits>::TCStrImp_Dynamic(TCStrImp_Dynamic &&_From)
		: m_pData(fg_Exchange(_From.m_pData, const_cast<CData *>(static_cast<CData const *>(&TCStrImp_Dynamic_EmptyStringDataImp<CChar>::mc_Instance))))
	{
	}

	template <typename t_CStrTraits>
	inline_small constexpr void TCStrImp_Dynamic<t_CStrTraits>::f_SetDefault()
	{
		m_pData = const_cast<CData *>(static_cast<CData const *>(&TCStrImp_Dynamic_EmptyStringDataImp<CChar>::mc_Instance));
	}

	template <typename t_CStrTraits>
	inline_small constexpr bool TCStrImp_Dynamic<t_CStrTraits>::f_IsDefault()
	{
		return m_pData == const_cast<CData *>(static_cast<CData const *>(&TCStrImp_Dynamic_EmptyStringDataImp<CChar>::mc_Instance));
	}

	template <typename t_CStrTraits>
	inline_always bool TCStrImp_Dynamic<t_CStrTraits>::f_IsSameWeak(TCStrImp_Dynamic const &_Right) const
	{
		return m_pData == _Right.m_pData;
	}

	template <typename t_CStrTraits>
	inline_always bool TCStrImp_Dynamic<t_CStrTraits>::f_IsConstant() const
	{
		return m_pData->m_bConstant;
	}

	template <typename t_CStrTraits>
	inline_medium void TCStrImp_Dynamic<t_CStrTraits>::f_Assign(TCStrImp_Dynamic const &_From)
	{
		_From.m_pData->f_RefCountIncrease();
		if (m_pData->f_RefCountDecrease())
			CAllocator::f_Free(m_pData, m_pData->f_GetMemorySize());
		m_pData = _From.m_pData;
	}

	template <typename t_CStrTraits>
	inline_medium void TCStrImp_Dynamic<t_CStrTraits>::f_Assign(TCStrImp_Dynamic &&_From)
	{
		if (m_pData->f_RefCountDecrease())
			CAllocator::f_Free(m_pData, m_pData->f_GetMemorySize());
		m_pData = _From.m_pData;
		_From.f_SetDefault();
	}

	template <typename t_CStrTraits>
	constexpr inline_medium void TCStrImp_Dynamic<t_CStrTraits>::f_Destroy()
	{
		if_consteval
		{
			f_SetDefault();
		}
		else
		{
			if (m_pData->f_RefCountDecrease())
				CAllocator::f_Free(m_pData, m_pData->f_GetMemorySize());

			f_SetDefault();
		}
	}

	template <typename t_CStrTraits>
	constexpr inline_small void TCStrImp_Dynamic<t_CStrTraits>::f_Clear()
	{
		f_Destroy();
	}

	template <typename t_CStrTraits>
	void TCStrImp_Dynamic<t_CStrTraits>::f_SetUserData(uint8 _Data)
	{
		DMibSafeCheck(_Data < 4, "Only 2 bits available");

		if (m_pData->m_UserData == _Data)
			return;

		if (_Data == 0 && (*f_GetStr()) == 0)
		{
			if (m_pData->f_RefCountDecrease())
				CAllocator::f_Free(m_pData, m_pData->f_GetMemorySize());
			f_SetDefault();
			return;
		}

		if (m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) > 1 || m_pData->m_bConstant)
		{
			umint StrLen = f_GetStrLen();
			umint Length = fg_Max(umint(m_pData->m_Len), umint(2));
			f_CreateWritableBuffer(Length, false);
			f_GetStrWritable()[StrLen] = 0;
			DMibFastCheck(!m_pData->m_bConstant);
			DMibFastCheck(m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) == 1);
		}

		m_pData->m_UserData = _Data;
	}

	template <typename t_CStrTraits>
	uint8 TCStrImp_Dynamic<t_CStrTraits>::f_GetUserData() const
	{
		return m_pData->m_UserData;
	}

	template <typename t_CStrTraits>
	inline_small auto TCStrImp_Dynamic<t_CStrTraits>::f_GetStrWritable() const ->CChar *
	{
		DMibSafeCheck(m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) == 1, "Must own str");
		return m_pData->f_GetData(); // Return a const value if string is empty this will make application crash if it writes to this data
	}

	template <typename t_CStrTraits>
	constexpr inline_small auto TCStrImp_Dynamic<t_CStrTraits>::f_GetStr() const -> CChar const *
	{
		return m_pData->f_GetData();
	}

	template <typename t_CStrTraits>
	inline_small umint TCStrImp_Dynamic<t_CStrTraits>::f_GetRefCount() const
	{
		return m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed);
	}

	template <typename t_CStrTraits>
	constexpr inline_small aint TCStrImp_Dynamic<t_CStrTraits>::f_GetAllocLength() const
	{
		return m_pData->m_Len;
	}

	template <typename t_CStrTraits>
	constexpr inline_medium aint TCStrImp_Dynamic<t_CStrTraits>::f_GetStrLen() const
	{
		umint Len = m_pData->m_StrLen;
		if (Len == CData::mc_InvalidStrLen)
			m_pData->m_StrLen = Len = t_CStrTraits::fs_StrLen(m_pData->f_GetData());
		return Len;
	}

	template <typename t_CStrTraits>
	constexpr inline_small bool TCStrImp_Dynamic<t_CStrTraits>::f_FastLen()
	{
		return true;
	}

	template <typename t_CStrTraits>
	inline_medium void TCStrImp_Dynamic<t_CStrTraits>::f_SetStrLen(aint _Len)
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
			DMibSafeCheck(!m_pData->m_bConstant && m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) == 1, "Must be no other having access to this data");
			f_TrimSize(NewLen);
		}
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Dynamic<t_CStrTraits>::f_MakeUnique()
	{
		if (m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) > 1)
			f_CreateWritableBuffer(f_GetStrLen()+1, false);
	}

	template <typename t_CStrTraits>
	inline_never void TCStrImp_Dynamic<t_CStrTraits>::fs_ThrowLengthException()
	{
		DMibError("String size would exceed maximum size that can be held in a umint");
	}

	template <typename t_CStrTraits>
	umint TCStrImp_Dynamic<t_CStrTraits>::fp_CalcNewSize(umint _Length)
	{
		if (_Length >= mc_MaxStrLen)
			fs_ThrowLengthException();

		_Length = fg_Max(_Length, fg_Max(sizeof(CData) / (2u * sizeof(CChar)), umint(2u)));

		umint Size = sizeof(CData) + _Length * sizeof(CChar);

		Size = CAllocator::f_SizePadded(umint(2) << NMib::fg_GetHighestBitSetNoZero(Size - 1));

#			if DMibEnableSafeCheck > 0
			umint nChars = (Size - sizeof(CData)) / sizeof(CChar);
			DMibFastCheck(nChars >= _Length);
#			endif

		return Size;
	}

	template <typename t_CStrTraits>
	umint TCStrImp_Dynamic<t_CStrTraits>::fp_GetOldAllocSize()
	{
		return m_pData->m_Len * sizeof(CChar) + sizeof(CData);
	}

	template <typename t_CStrTraits>
	aint TCStrImp_Dynamic<t_CStrTraits>::fp_CreateWritableBuffer(aint _Length, bool _bDiscard)
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
				if (!f_IsDefault())
				{
					if (m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) == 1)
					{
						umint CurrentSize = m_pData->f_GetMemorySize();

						if (_bDiscard)
						{
							umint Len = fp_CalcNewSize(_Length);
							auto OldReserved = m_pData->m_bReserved;
							auto OldUserData = m_pData->m_UserData;
							m_pData = new(CAllocator::f_Realloc(m_pData, Len, CurrentSize, EAllocationFlag_SizeNotNeeded)) CData();
							m_pData->f_SetLength(Len);
							m_pData->m_bReserved = OldReserved;
							m_pData->m_UserData = OldUserData;
						}
						else
						{
							umint Len = fp_CalcNewSize(_Length);
							m_pData = (CData *)(CAllocator::f_Resize(m_pData, Len, CurrentSize, EAllocationFlag_SizeNotNeeded));
							m_pData->f_SetLength(Len);
						}
						CurLen = m_pData->m_Len;
					}
					else
					{
						aint OldLen = CurLen;
						umint NewLen = fp_CalcNewSize(_Length);
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
							umint CopyLen = fg_Min(CurLen, OldLen);
							if (pNew->m_StrLen != CData::mc_InvalidStrLen)
								CopyLen = fg_Min(CurLen, (aint)pNew->m_StrLen + 1);

							NMemory::fg_MemCopy(m_pData->f_GetData(), pOld->f_GetData(), CopyLen * sizeof(CChar));
						}
						if (pOld->f_RefCountDecrease())
							CAllocator::f_Free(pOld, pOld->f_GetMemorySize());
					}
				}
				else
				{
					umint NewLen = fp_CalcNewSize(_Length);
					m_pData = new(CAllocator::f_Alloc(NewLen)) CData();
					DMibFastCheck(m_pData);
					m_pData->f_SetLength(NewLen);
					CurLen = m_pData->m_Len;
					m_pData->f_GetData()[0] = 0;
				}
			}
			else
			{
				if (m_pData->f_RefCountDecrease())
					CAllocator::f_Free(m_pData, m_pData->f_GetMemorySize());

				f_SetDefault();
				CurLen = m_pData->m_Len;
			}
		}
		else if (m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) > 1)
		{
			umint NewLen = fp_CalcNewSize(_Length);
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
				umint CopyLen = fg_Min(CurLen, OldLen);
				if (pNew->m_StrLen != CData::mc_InvalidStrLen)
					CopyLen = fg_Min(CurLen, (aint)pNew->m_StrLen + 1);
				NMemory::fg_MemCopy(m_pData->f_GetData(), pOld->f_GetData(), CopyLen * sizeof(CChar));
			}
			if (pOld->f_RefCountDecrease())
				CAllocator::f_Free(pOld, pOld->f_GetMemorySize());
		}

		return CurLen;

	}

	template <typename t_CStrTraits>
	inline aint TCStrImp_Dynamic<t_CStrTraits>::f_CreateWritableBuffer(aint _Length, bool _bDiscard)
	{
		aint CurLen = m_pData->m_Len;
		if (CurLen >= _Length && m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) == 1)
			return CurLen;

		return fp_CreateWritableBuffer(_Length, _bDiscard);
	}

	template <typename t_CStrTraits>
	void TCStrImp_Dynamic<t_CStrTraits>::f_Reserve(umint _Len)
	{
		if (_Len)
		{
			f_CreateWritableBuffer(_Len+1, false);
			DMibFastCheck(!f_IsDefault());
			m_pData->m_bReserved = true;
		}
		else
		{
			if (m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) == 1)
				m_pData->m_bReserved = false;
		}
	}

	template <typename t_CStrTraits>
	void TCStrImp_Dynamic<t_CStrTraits>::fp_TrimSize(umint _Length, umint _NeededSize)
	{
		DMibSafeCheck(_Length > 0, "Have to have place for a nullptr character");
		if (_Length == 1 && m_pData->m_UserData == 0)
		{
			if (m_pData->f_RefCountDecrease())
				CAllocator::f_Free(m_pData, m_pData->f_GetMemorySize());

			f_SetDefault();
			return;
		}

		DMibSafeCheck(!m_pData->m_bConstant, "Must be allocated here or something is wrong");
		if (m_pData->m_RefCount.f_Load(NAtomic::gc_MemoryOrder_Relaxed) == 1)
		{
			m_pData = (CData *)(CAllocator::f_Resize(m_pData, _NeededSize, m_pData->f_GetMemorySize()));
			m_pData->f_SetLength(_NeededSize);
		}
		else
		{
			CData *pNewData = new(CAllocator::f_Alloc(_NeededSize)) CData();
			pNewData->f_SetLength(_NeededSize);
			NMemory::fg_MemCopy(pNewData->f_GetData(), m_pData->f_GetData(), _Length * sizeof(CChar));
			if (m_pData->f_RefCountDecrease())
				CAllocator::f_Free(m_pData, m_pData->f_GetMemorySize());
			m_pData = pNewData;
		}
	}

	template <typename t_CStrTraits>
	inline_small void TCStrImp_Dynamic<t_CStrTraits>::f_TrimSize(umint _Length, umint _MaxExtraChars)
	{
		DMibSafeCheck(_Length > 0, "Have to have place for a nullptr character");

		if (m_pData->m_bReserved || m_pData->m_bConstant)
			return;

		if (_Length == 1)
			return fp_TrimSize(_Length, _MaxExtraChars);

		// Threshold
		umint NewSize = fp_CalcNewSize(_Length + _MaxExtraChars + 1);
		umint OldSize = fp_GetOldAllocSize();

		if (NewSize < OldSize)
			fp_TrimSize(_Length, NewSize);
	}

	template <umint t_nChars>
	constexpr TCStrConstDataAndStr<t_nChars, ch8>::operator NStr::CStr const &() const
	{
		return m_Str;
	}

	template <umint t_nChars>
	constexpr TCStrConstDataAndStr<t_nChars, ch8>::operator TCStrConst<NStr::CStr> () const
	{
		return {.m_Str = m_Str, .m_pStr = m_StrData.m_Data};
	}

	template <umint t_nChars>
	constexpr TCStrConstDataAndStr<t_nChars, ch16>::operator NStr::CWStr const &() const
	{
		return m_Str;
	}

	template <umint t_nChars>
	constexpr TCStrConstDataAndStr<t_nChars, ch16>::operator TCStrConst<NStr::CWStr> () const
	{
		return {.m_Str = m_Str, .m_pStr = m_StrData.m_Data};
	}

	template <umint t_nChars>
	constexpr TCStrConstDataAndStr<t_nChars, ch32>::operator NStr::CUStr const &() const
	{
		return m_Str;
	}

	template <umint t_nChars>
	constexpr TCStrConstDataAndStr<t_nChars, ch32>::operator TCStrConst<NStr::CUStr> () const
	{
		return {.m_Str = m_Str, .m_pStr = m_StrData.m_Data};
	}
}
