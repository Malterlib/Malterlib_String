// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CStrTraits>
	CStrIteratorUTF8::CStrIteratorUTF8(TCStr<tf_CStrTraits> const &_String)
		: mp_pBegin((uch8 const *)_String.f_GetStr())
		, mp_pEnd((uch8 const *)_String.f_GetStr() + _String.f_GetStrLen())
		, mp_pInitialBegin((uch8 const *)_String.f_GetStr())
		, mp_pLastValidBegin((uch8 const *)_String.f_GetStr())
		, mp_bWholeCodePoint(true)
		, mp_bValidCodePoint(true)
	{
		static_assert(sizeof(typename tf_CStrTraits::CStrTraits::CChar) == 1, "Incorrectly sized char for UTC8");
		fp_ParseBOM();
		mp_Current = fp_Next();
	}

	mark_nodebug inline_always ch32 CStrIteratorUTF8::operator *() const
	{
		return mp_Current;
	}

	mark_nodebug inline_always CStrIteratorUTF8::operator ch32 () const
	{
		return mp_Current;
	}

	inline_always smint CStrIteratorUTF8::operator - (CStrIteratorUTF8 const &_Other) const
	{
		return mp_pBegin - _Other.mp_pBegin;
	}

	inline_always CStrIteratorUTF8 &CStrIteratorUTF8::operator ++ ()
	{
		mp_Current = fp_Next();
		return *this;
	}

	template <typename tf_CStrTraits>
	CStrIteratorUTF16::CStrIteratorUTF16(TCStr<tf_CStrTraits> const &_String)
		: mp_pBegin((uch16 const *)_String.f_GetStr())
		, mp_pEnd((uch16 const *)_String.f_GetStr() + _String.f_GetStrLen())
	{
		static_assert(sizeof(typename tf_CStrTraits::CStrTraits::CChar) == 2, "Incorrectly sized char for UTC8");
		fp_ParseBOM();
		mp_Current = fp_Next();
	}

	mark_nodebug inline_always CStrIteratorUTF16::operator ch32 () const
	{
		return mp_Current;
	}

	mark_nodebug inline_always ch32 CStrIteratorUTF16::operator *() const
	{
		return mp_Current;
	}

	inline_always CStrIteratorUTF16 &CStrIteratorUTF16::operator ++ ()
	{
		mp_Current = fp_Next();
		return *this;
	}

	inline_always smint CStrIteratorUTF16::operator - (CStrIteratorUTF16 const &_Other) const
	{
		return mp_pBegin - _Other.mp_pBegin;
	}

	template <typename t_CChar>
	ch32 TCStrIteratorUnicode<t_CChar>::fp_Next()
	{
		if (mp_pBegin >= mp_pEnd)
			return 0;

		ch32 Ret = *mp_pBegin;
		++mp_pBegin;

		return Ret;
	}

	template <typename t_CChar>
	TCStrIteratorUnicode<t_CChar>::TCStrIteratorUnicode(t_CChar const *_pStr, umint _StrLen)
		: mp_pBegin((CUnsignedChar const *)_pStr)
		, mp_pEnd((CUnsignedChar const *)_pStr + _StrLen)
	{
		mp_Current = fp_Next();
	}

	template <typename t_CChar>
	template <typename tf_CStrTraits>
	TCStrIteratorUnicode<t_CChar>::TCStrIteratorUnicode(TCStr<tf_CStrTraits> const &_String)
		: mp_pBegin((CUnsignedChar const *)_String.f_GetStr())
		, mp_pEnd((CUnsignedChar const *)_String.f_GetStr() + _String.f_GetStrLen())
	{
		static_assert(sizeof(typename tf_CStrTraits::CStrTraits::CChar) == sizeof(CUnsignedChar), "Incorrectly sized char for UTC8");
		mp_Current = fp_Next();
	}

	template <typename t_CChar>
	mark_nodebug inline_always ch32 TCStrIteratorUnicode<t_CChar>::operator *() const
	{
		return mp_Current;
	}

	template <typename t_CChar>
	mark_nodebug inline_always TCStrIteratorUnicode<t_CChar>::operator ch32 () const
	{
		return mp_Current;
	}

	template <typename t_CChar>
	inline_always auto TCStrIteratorUnicode<t_CChar>::operator ++ () -> TCStrIteratorUnicode &
	{
		mp_Current = fp_Next();
		return *this;
	}

	template <typename t_CChar>
	inline_always smint TCStrIteratorUnicode<t_CChar>::operator - (TCStrIteratorUnicode const &_Other) const
	{
		return mp_pBegin - _Other.mp_pBegin;
	}

	template <typename t_CChar>
	auto TCStrIteratorUnicode<t_CChar>::f_GetIterator() -> TCStrIteratorUnicode &
	{
		return *this;
	}

	template <typename tf_CChar, umint tf_Size>
	TCEnableIf<sizeof(tf_CChar) == 1, CStrIteratorUTF8> fg_GetUnicodeIterator(tf_CChar const *_pStr, umint _Len)
	{
		return CStrIteratorUTF8((ch8 const *)_pStr, _Len);
	}

	template <typename tf_CChar, umint tf_Size>
	TCEnableIf<sizeof(tf_CChar) == 2, CStrIteratorUTF16> fg_GetUnicodeIterator(tf_CChar const *_pStr, umint _Len)
	{
		return CStrIteratorUTF16((ch16 const *)_pStr, _Len);
	}

	template <typename tf_CChar, umint tf_Size>
	TCEnableIf<sizeof(tf_CChar) == 4, TCStrIteratorUnicode<ch32>> fg_GetUnicodeIterator(tf_CChar const *_pStr, umint _Len)
	{
		return TCStrIteratorUnicode<ch32>((ch32 const *)_pStr, _Len);
	}

	template <bool t_bCheckLength, typename t_FOutFunctor>
	inline_always bool fg_EncodeUTF8Char(ch32 _Char, t_FOutFunctor &&_OutFunctor)
	{
		if (_Char >= 0x4000000)
		{
			auto *pRet = _OutFunctor(6);
			if constexpr (t_bCheckLength)
			{
				if (!pRet)
					return false;
			}

			*pRet = 0xFC | ((_Char >> 30) & 0x01); ++pRet;
			*pRet = 0x80 | ((_Char >> 24) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 18) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
		}
		else if (_Char >= 0x200000)
		{
			auto *pRet = _OutFunctor(5);
			if constexpr (t_bCheckLength)
			{
				if (!pRet)
					return false;
			}
			*pRet = 0xF8 | ((_Char >> 24) & 0x03); ++pRet;
			*pRet = 0x80 | ((_Char >> 18) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
		}
		else if (_Char >= 0x10000)
		{
			auto *pRet = _OutFunctor(4);
			if constexpr (t_bCheckLength)
			{
				if (!pRet)
					return false;
			}
			*pRet = 0xF0 | ((_Char >> 18) & 0x07); ++pRet;
			*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
		}
		else if (_Char >= 0x800)
		{
			auto *pRet = _OutFunctor(3);
			if constexpr (t_bCheckLength)
			{
				if (!pRet)
					return false;
			}
			*pRet = 0xE0 | ((_Char >> 12) & 0x0F); ++pRet;
			*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
			*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
		}
		else if (_Char >= 0x80)
		{
			auto *pRet = _OutFunctor(2);
			if constexpr (t_bCheckLength)
			{
				if (!pRet)
					return false;
			}
			*pRet = 0xC0 | ((_Char >> 6 ) & 0x1F); ++pRet;
			*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
		}
		else
		{
			auto *pRet = _OutFunctor(1);
			if constexpr (t_bCheckLength)
			{
				if (!pRet)
					return false;
			}
			*pRet = _Char;
		}
		return true;
	}

	template <typename t_FOutFunctor>
	bool fg_EncodeUTF8BOM(t_FOutFunctor &&_OutFunctor)
	{
		auto *pRet = _OutFunctor(3);
		if (pRet)
		{
			*pRet = ch8(0xEF); ++pRet;
			*pRet = ch8(0xBB); ++pRet;
			*pRet = ch8(0xBF); ++pRet;
			return true;
		}
		return false;
	}

	template <bool t_bCheckLength, typename t_FOutFunctor>
	inline_always bool fg_EncodeUTF16Char(ch32 _Char, t_FOutFunctor &&_OutFunctor)
	{
		if (_Char > 0xFFFF)
		{
			auto *pRet = _OutFunctor(2);
			if constexpr (t_bCheckLength)
			{
				if (!pRet)
					return false;
			}

			_Char -= 0x10000;

			uint32 vh = _Char >> 10;
			uint32 v1 = _Char & 0x3FF;
			uint32 w1 = 0xD800 + vh;
			uint32 w2 = 0xDC00 + v1;

			*pRet = ch16(w1);++pRet;
			*pRet = ch16(w2);
		}
		else
		{
			auto *pRet = _OutFunctor(1);
			if constexpr (t_bCheckLength)
			{
				if (!pRet)
					return false;
			}

			*pRet = ch16(_Char);
		}
		return true;
	}

	template <typename t_FOutFunctor>
	bool fg_EncodeUTF16BOM(t_FOutFunctor &&_OutFunctor)
	{
		auto *pRet = _OutFunctor(1);
		if (pRet)
		{
			*pRet = ch16(0xFFFE);
			return true;
		}
		return false;
	}
}
