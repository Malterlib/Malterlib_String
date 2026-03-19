// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CChar>
	struct TCStrIteratorUnicode
	{
		using CUnsignedChar = NTraits::TCUnsigned<t_CChar>;

		TCStrIteratorUnicode(t_CChar const *_pStr, umint _StrLen);

		template <typename tf_CStrTraits>
		TCStrIteratorUnicode(TCStr<tf_CStrTraits> const &_String);

		TCStrIteratorUnicode &f_GetIterator();

		mark_nodebug inline_always ch32 operator *() const;
		mark_nodebug inline_always operator ch32 () const;
		inline_always TCStrIteratorUnicode &operator ++ ();
		inline_always smint operator - (TCStrIteratorUnicode const &_Other) const;

	private:
		ch32 fp_Next();

		CUnsignedChar const *mp_pBegin;
		CUnsignedChar const *mp_pEnd;
		ch32 mp_Current;
	};

	struct CStrIteratorUTF8
	{
		CStrIteratorUTF8(ch8 const *_pStr, umint _StrLen);
		template <typename tf_CStrTraits>
		CStrIteratorUTF8(TCStr<tf_CStrTraits> const &_String);

		umint f_GetLastWholeCodePointPos() const;
		bool f_IsWholeCodePoint() const;
		bool f_IsBroken() const;

		CStrIteratorUTF8 &f_GetIterator();

		mark_nodebug inline_always ch32 operator *() const;
		mark_nodebug inline_always operator ch32 () const;
		inline_always smint operator - (CStrIteratorUTF8 const &_Other) const;
		inline_always CStrIteratorUTF8 &operator ++ ();

	private:
		void fp_ParseBOM();
		ch32 fp_Next();

		uch8 const *mp_pBegin;
		uch8 const *mp_pEnd;
		uch8 const *mp_pInitialBegin;
		uch8 const *mp_pLastValidBegin;
		ch32 mp_Current;
		bool mp_bWholeCodePoint;
		bool mp_bValidCodePoint;
	};

	struct CStrIteratorUTF16
	{
		CStrIteratorUTF16(ch16 const *_pStr, umint _StrLen);
		template <typename tf_CStrTraits>
		CStrIteratorUTF16(TCStr<tf_CStrTraits> const &_String);

		mark_nodebug inline_always operator ch32 () const;
		mark_nodebug inline_always ch32 operator *() const;
		inline_always CStrIteratorUTF16 &operator ++ ();
		inline_always smint operator - (CStrIteratorUTF16 const &_Other) const;

		CStrIteratorUTF16 &f_GetIterator();

	private:
		void fp_ParseBOM();
		ch32 fp_Next();

		uch16 const *mp_pBegin;
		uch16 const *mp_pEnd;
		ch32 mp_Current;
	};

	template <typename tf_CChar, umint tf_Size = sizeof(tf_CChar)>
	TCEnableIf<sizeof(tf_CChar) == 1, CStrIteratorUTF8> fg_GetUnicodeIterator(tf_CChar const *_pStr, umint _Len);

	template <typename tf_CChar, umint tf_Size = sizeof(tf_CChar)>
	TCEnableIf<sizeof(tf_CChar) == 2, CStrIteratorUTF16> fg_GetUnicodeIterator(tf_CChar const *_pStr, umint _Len);

	template <typename tf_CChar, umint tf_Size = sizeof(tf_CChar)>
	TCEnableIf<sizeof(tf_CChar) == 4, TCStrIteratorUnicode<ch32>> fg_GetUnicodeIterator(tf_CChar const *_pStr, umint _Len);

	template <typename t_FOutFunctor>
	bool fg_EncodeUTF8BOM(t_FOutFunctor &&_OutFunctor);

	template <typename t_FOutFunctor>
	bool fg_EncodeUTF16BOM(t_FOutFunctor &&_OutFunctor);

	template <bool t_bCheckLength, typename t_FOutFunctor>
	inline_always bool fg_EncodeUTF8Char(ch32 _Char, t_FOutFunctor &&_OutFunctor);

	template <bool t_bCheckLength, typename t_FOutFunctor>
	inline_always bool fg_EncodeUTF16Char(ch32 _Char, t_FOutFunctor &&_OutFunctor);
}

#include "Malterlib_String_UnicodeConversion.hpp"
