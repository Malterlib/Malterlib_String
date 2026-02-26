// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CChar>
	struct TCStrImp_Dynamic_StringData
	{
		inline_small t_CChar *f_GetData() const;
		inline_small mint f_GetMemorySize() const;
		inline_small void f_SetLength(mint _MemoryLen);
		inline_small void f_RefCountIncrease();
		inline_small bool f_RefCountDecrease();

		NAtomic::TCAtomicIndeterminate<mint> m_RefCount{1};
		mint m_Len:sizeof(mint)*8-2 = 0;
		mint m_bReserved:1 = 0;
		mint m_bConstant:1 = 0;
		mint m_StrLen:sizeof(mint)*8-2 = mc_InvalidStrLen;
		mint m_UserData:2 = 0;

		constexpr static mint mc_InvalidStrLen = ((mint(1) << (sizeof(mint)*8-2))) - 1;
	};

	template <mint t_nChars, typename t_CChar>
	struct TCStrConstData : public TCStrImp_Dynamic_StringData<t_CChar>
	{
		using CChar = t_CChar;

		constexpr TCStrConstData(t_CChar const (&_String)[t_nChars], uint8 _UserData = 0);

		inline_always constexpr TCStrConstData &f_SetUserData(uint8 _UserData);

		constexpr static mint mc_nChars = t_nChars;

		t_CChar m_Data[t_nChars];
	};

	template <typename t_CChar>
	struct TCStrImp_Dynamic_EmptyStringData : public TCStrImp_Dynamic_StringData<t_CChar>
	{
		constexpr TCStrImp_Dynamic_EmptyStringData();

		inline_always constexpr TCStrImp_Dynamic_StringData<t_CChar> *f_MutableData() const;

		t_CChar m_StringData[1] = {0};
	};

	template <typename t_CChar>
	struct TCStrImp_Dynamic_EmptyStringDataImp
	{
		constexpr static TCStrImp_Dynamic_EmptyStringData<t_CChar> const mc_Instance = {};
	};

	extern template struct TCStrImp_Dynamic_StringData<ch8>;
	extern template struct TCStrImp_Dynamic_StringData<ch16>;
	extern template struct TCStrImp_Dynamic_StringData<ch32>;

	extern template struct TCStrImp_Dynamic_EmptyStringData<ch8>;
	extern template struct TCStrImp_Dynamic_EmptyStringData<ch16>;
	extern template struct TCStrImp_Dynamic_EmptyStringData<ch32>;

	extern template struct TCStrImp_Dynamic_EmptyStringDataImp<ch8>;
	extern template struct TCStrImp_Dynamic_EmptyStringDataImp<ch16>;
	extern template struct TCStrImp_Dynamic_EmptyStringDataImp<ch32>;

	template <typename t_CStrTraits>
	struct TCStrImp_Dynamic
	{
	public:
		using CChar = typename t_CStrTraits::CChar;
		using CImpParams = typename t_CStrTraits::CParams;
		using CAllocator = typename CImpParams::CAllocator;

		using CData = TCStrImp_Dynamic_StringData<CChar>;

		constexpr TCStrImp_Dynamic() = default;
		inline_medium constexpr TCStrImp_Dynamic(TCStrImp_Dynamic const &_From);
		constexpr TCStrImp_Dynamic(CData const &_Data);
		inline_medium TCStrImp_Dynamic(TCStrImp_Dynamic &&_From);

		constexpr ~TCStrImp_Dynamic();

		inline_medium void f_Assign(TCStrImp_Dynamic const &_From);
		inline_medium void f_Assign(TCStrImp_Dynamic &&_From);
		constexpr inline_medium void f_Destroy();
		constexpr inline_small void f_Clear();

		inline_small constexpr void f_SetDefault();
		inline_small constexpr bool f_IsDefault();

		inline_always bool f_IsSameWeak(TCStrImp_Dynamic const &_Right) const;
		inline_always bool f_IsConstant() const;

		void f_SetUserData(uint8 _Data);
		uint8 f_GetUserData() const;

		constexpr inline_small CChar const *f_GetStr() const;
		inline_small CChar *f_GetStrWritable() const;

		inline_small mint f_GetRefCount() const;

		constexpr inline_medium aint f_GetStrLen() const;
		inline_medium void f_SetStrLen(aint _Len);

		constexpr inline_small aint f_GetAllocLength() const;
		constexpr static inline_small bool f_FastLen();

		void f_Reserve(mint _Len);
		inline_small void f_MakeUnique();
		aint fp_CreateWritableBuffer(aint _Length, bool _bDiscard);
		inline aint f_CreateWritableBuffer(aint _Length, bool _bDiscard);
		inline_small void f_TrimSize(mint _Length, mint _MaxExtraChars = mc_MaxExtraChars);

		inline_never static void fs_ThrowLengthException();

		constexpr static mint mc_MaxAllocChars = (TCLimitsInt<mint>::mc_Max - sizeof(CData)) / sizeof(CChar);
		constexpr static mint mc_MaxStrLen = mc_MaxAllocChars < CData::mc_InvalidStrLen ? mc_MaxAllocChars : CData::mc_InvalidStrLen;
		constexpr static bool mc_bNothrowAssign = true;
		constexpr static bool mc_AllocatesMemory = true;
		constexpr static bool mc_bInitConstStr = false;
		constexpr static mint mc_MaxExtraChars = CImpParams::mc_MaxExtraChars;

		CData *m_pData = const_cast<CData *>(static_cast<CData const *>(&TCStrImp_Dynamic_EmptyStringDataImp<CChar>::mc_Instance));

	private:
		mint fp_CalcNewSize(mint _Length);
		mint fp_GetOldAllocSize();
		void fp_TrimSize(mint _Length, mint _NeededSize);
	};

	template <typename t_CStr>
	struct TCStrConst
	{
		t_CStr const &m_Str;
		t_CStr::CChar const *m_pStr;
	};

	template <mint t_nChars, typename t_CChar>
	struct TCStrConstDataAndStr;

	template <mint t_nChars>
	struct TCStrConstDataAndStr<t_nChars, ch8>
	{
		constexpr operator NStr::CStr const &() const;
		constexpr operator TCStrConst<NStr::CStr> () const;

		TCStrConstData<t_nChars, ch8> const m_StrData;
		CStr const m_Str{CStrInitGeneral(), m_StrData};
	};

	template <mint t_nChars>
	struct TCStrConstDataAndStr<t_nChars, ch16>
	{
		constexpr operator NStr::CWStr const &() const;
		constexpr operator TCStrConst<NStr::CWStr> () const;

		TCStrConstData<t_nChars, ch16> const m_StrData;
		CWStr const m_Str{CStrInitGeneral(), m_StrData};
	};

	template <mint t_nChars>
	struct TCStrConstDataAndStr<t_nChars, ch32>
	{
		constexpr operator NStr::CUStr const &() const;
		constexpr operator TCStrConst<NStr::CUStr> () const;

		TCStrConstData<t_nChars, ch32> const m_StrData;
		CUStr const m_Str{CStrInitGeneral(), m_StrData};
	};

	template <TCStrConstData t_Data>
	constexpr TCStrConstDataAndStr<decltype(t_Data)::mc_nChars, typename decltype(t_Data)::CChar> gc_Str{t_Data};
}
