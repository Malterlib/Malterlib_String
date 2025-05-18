// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CChar>
	class TCStrIteratorUnicode
	{
		using CUnsignedChar = NTraits::TCUnsigned<t_CChar>;

		CUnsignedChar const *m_pBegin;
		CUnsignedChar const *m_pEnd;
		ch32 m_Current;

		ch32 fp_Next()
		{
			if (m_pBegin >= m_pEnd)
				return 0;
			ch32 Ret = *m_pBegin;
			++m_pBegin;
			return Ret;
		}
	public:
		TCStrIteratorUnicode(t_CChar const *_pStr, mint _StrLen)
			: m_pBegin((CUnsignedChar const *)_pStr)
			, m_pEnd((CUnsignedChar const *)_pStr + _StrLen)
		{
			m_Current = fp_Next();
		}
		template <typename t_CStrTraits>
		TCStrIteratorUnicode(TCStrAggregate<t_CStrTraits> const &_String)
			: m_pBegin((CUnsignedChar const *)_String.f_GetStr())
			, m_pEnd((CUnsignedChar const *)_String.f_GetStr() + _String.f_GetStrLen())
		{
			static_assert(sizeof(typename t_CStrTraits::CStrTraits::CChar) == sizeof(CUnsignedChar), "Uncorrectly sized char for UTC8");
			m_Current = fp_Next();
		}

		mark_nodebug inline_always ch32 operator *() const
		{
			return m_Current;
		}

		mark_nodebug inline_always operator ch32 () const
		{
			return m_Current;
		}

		inline_always TCStrIteratorUnicode &operator ++ ()
		{
			m_Current = fp_Next();
			return *this;
		}

		inline_always smint operator - (TCStrIteratorUnicode const &_Other) const
		{
			return m_pBegin - _Other.m_pBegin;
		}

		TCStrIteratorUnicode &f_GetIterator()
		{
			return *this;
		}
	};

	class CStrIteratorUTF8
	{
		uch8 const *m_pBegin;
		uch8 const *m_pEnd;
		uch8 const *m_pInitialBegin;
		uch8 const *m_pLastValidBegin;
		ch32 m_Current;
		bool m_bWholeCodePoint;
		bool m_bValidCodePoint;

		void fp_ParseBOM()
		{
			// Remove BOM
			if (m_pBegin[0] == 0xEF && m_pBegin[1] == 0xBB && m_pBegin[2] == 0xBF)
			{
				m_pBegin += 3;
			}
		}

		ch32 fp_Next()
		{
			ch32 DestChar = 0;
			uch8 const *pParse = m_pBegin;
			uch8 const *pLastValid = m_pLastValidBegin;
			m_bWholeCodePoint = true;
			m_bValidCodePoint = true;
			while (1)
			{
				if (pParse >= m_pEnd)
					break;

				uch8 ToTest = *pParse;
				if (ToTest & 0x80)
				{
					if ((ToTest & 0xC0) == 0xC0)
					{
						++pParse;
						mint nChars = 7 - fg_GetHighestBitSetNoZero(((~uint32(ToTest)) & 0xFF) | 1u);
						DestChar = ToTest & ((1 << (8 - (nChars + 1))) - 1);
						--nChars;
						while (pParse < m_pEnd && *pParse && nChars && (*pParse & 0xC0) == 0x80)
						{
							DestChar = (DestChar << 6) | ((*pParse) & 0x3F);
							++pParse;
							--nChars;
						}

						if (nChars)
						{
							if (pParse >= m_pEnd || !*pParse)
								m_bWholeCodePoint = false;
							else
							{
								m_bValidCodePoint = false;
								pLastValid = pParse;
								break;
							}
						}
						else
							pLastValid = pParse;
						break;
					}
					else
					{
						DestChar = ToTest;
						m_bValidCodePoint = false;
						pLastValid = pParse;
						++pParse;
						break;
					}
				}
				else
				{
					DestChar = ToTest;
					++pParse;
					pLastValid = pParse;
					break;
				}
			}

			m_pLastValidBegin = pLastValid;
			m_pBegin = pParse;

			return DestChar;
		}
	public:
		CStrIteratorUTF8(ch8 const *_pStr, mint _StrLen)
			: m_pBegin((uch8 const *)_pStr)
			, m_pInitialBegin((uch8 const *)_pStr)
			, m_pLastValidBegin((uch8 const *)_pStr)
			, m_pEnd((uch8 const *)_pStr + _StrLen)
			, m_bWholeCodePoint(true)
			, m_bValidCodePoint(true)
		{
			fp_ParseBOM();
			m_Current = fp_Next();
		}
		template <typename t_CStrTraits>
		CStrIteratorUTF8(TCStrAggregate<t_CStrTraits> const &_String)
			: m_pBegin((uch8 const *)_String.f_GetStr())
			, m_pInitialBegin((uch8 const *)_String.f_GetStr())
			, m_pLastValidBegin((uch8 const *)_String.f_GetStr())
			, m_pEnd((uch8 const *)_String.f_GetStr() + _String.f_GetStrLen())
			, m_bWholeCodePoint(true)
			, m_bValidCodePoint(true)
		{
			static_assert(sizeof(typename t_CStrTraits::CStrTraits::CChar) == 1, "Uncorrectly sized char for UTC8");
			fp_ParseBOM();
			m_Current = fp_Next();
		}

		mint f_GetLastWholeCodePointPos() const
		{
			return m_pLastValidBegin - m_pInitialBegin;
		}

		bool f_IsWholeCodePoint() const
		{
			return m_bWholeCodePoint;
		}

		bool f_IsBroken() const
		{
			return !m_bValidCodePoint;
		}

		mark_nodebug inline_always ch32 operator *() const
		{
			return m_Current;
		}

		mark_nodebug inline_always operator ch32 () const
		{
			return m_Current;
		}

		inline_always smint operator - (CStrIteratorUTF8 const &_Other) const
		{
			return m_pBegin - _Other.m_pBegin;
		}

		inline_always CStrIteratorUTF8 &operator ++ ()
		{
			m_Current = fp_Next();
			return *this;
		}

		CStrIteratorUTF8 &f_GetIterator()
		{
			return *this;
		}
	};


	class CStrIteratorUTF16
	{
		uch16 const *m_pBegin;
		uch16 const *m_pEnd;
		ch32 m_Current;
		void fp_ParseBOM()
		{
			// Remove BOM
			if (m_pBegin[0] == 0xFFFE)
			{
				++m_pBegin;
			}
		}
		ch32 fp_Next()
		{
			ch32 DestChar = 0;
			uch16 const *pParse = m_pBegin;
			while (1)
			{
				if (pParse >= m_pEnd)
				{
					m_pBegin = pParse;
					return DestChar;
				}

				if ((*pParse & 0xFC00) == 0xD800)
				{
					ch32 Str0 = *pParse;
					++pParse;
					ch32 Str1 = *pParse;
					if ((Str1 & 0xFC00) != 0xDC00)
						continue;
					++pParse;

					ch32 X = ((Str0 & ((1<<6) -1)) << 10) | (Str1 & ((1<<10) -1));
					ch32 W = (Str0 >> 6) & ((1<<5) - 1);
					ch32 U = W + 1 ;

					DestChar = U << 16 | X;
					break;
				}
				DestChar = (*(pParse++));
				break;
			}

			m_pBegin = pParse;

			return DestChar;
		}
	public:
		CStrIteratorUTF16(ch16 const *_pStr, mint _StrLen)
			: m_pBegin((uch16 const *)_pStr)
			, m_pEnd((uch16 const *)_pStr + _StrLen)
		{
			fp_ParseBOM();
			m_Current = fp_Next();
		}
		template <typename t_CStrTraits>
		CStrIteratorUTF16(TCStrAggregate<t_CStrTraits> const &_String)
			: m_pBegin((uch16 const *)_String.f_GetStr())
			, m_pEnd((uch16 const *)_String.f_GetStr() + _String.f_GetStrLen())
		{
			static_assert(sizeof(typename t_CStrTraits::CStrTraits::CChar) == 2, "Uncorrectly sized char for UTC8");
			fp_ParseBOM();
			m_Current = fp_Next();
		}

		mark_nodebug inline_always operator ch32 () const
		{
			return m_Current;
		}

		mark_nodebug inline_always ch32 operator *() const
		{
			return m_Current;
		}

		inline_always CStrIteratorUTF16 &operator ++ ()
		{
			m_Current = fp_Next();
			return *this;
		}

		inline_always smint operator - (CStrIteratorUTF16 const &_Other) const
		{
			return m_pBegin - _Other.m_pBegin;
		}

		CStrIteratorUTF16 &f_GetIterator()
		{
			return *this;
		}
	};

	template <typename tf_CChar, mint tf_Size = sizeof(tf_CChar)>
	TCEnableIf<sizeof(tf_CChar) == 1, CStrIteratorUTF8> fg_GetUnicodeIterator(tf_CChar const *_pStr, mint _Len)
	{
		return CStrIteratorUTF8((ch8 const *)_pStr, _Len);
	}

	template <typename tf_CChar, mint tf_Size = sizeof(tf_CChar)>
	TCEnableIf<sizeof(tf_CChar) == 2, CStrIteratorUTF16> fg_GetUnicodeIterator(tf_CChar const *_pStr, mint _Len)
	{
		return CStrIteratorUTF16((ch16 const *)_pStr, _Len);
	}

	template <typename tf_CChar, mint tf_Size = sizeof(tf_CChar)>
	TCEnableIf<sizeof(tf_CChar) == 4, TCStrIteratorUnicode<ch32>> fg_GetUnicodeIterator(tf_CChar const *_pStr, mint _Len)
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

			*pRet = w1;++pRet;
			*pRet = w2;
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
