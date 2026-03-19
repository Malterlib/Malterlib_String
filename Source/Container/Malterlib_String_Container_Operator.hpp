// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_TCStrTraits>
	inline_large TCStr<t_TCStrTraits> &TCStr<t_TCStrTraits>::operator += (ch32 _ToAdd)
	{
		f_AddChar(_ToAdd);
		return *this;
	}

	template <typename t_TCStrTraits>
	template <typename t_CStrDataType>
	inline_large TCStr<t_TCStrTraits> &TCStr<t_TCStrTraits>::operator += (t_CStrDataType const *_pToAdd)
	{
		f_AddStr(_pToAdd);
		return *this;
	}

	template <typename t_TCStrTraits>
	inline_large TCStr<t_TCStrTraits> &TCStr<t_TCStrTraits>::operator += (CFormat const &_Format)
	{
		_Format.f_FormatToStrConcat(*this);
		return *this;
	}

	template <typename t_TCStrTraits>
	template <typename t_CStrTraitsF>
	inline_large TCStr<t_TCStrTraits> & TCStr<t_TCStrTraits>::operator += (TCStr<t_CStrTraitsF> const &_Str)
	{
		if (f_IsEmpty())
			f_SetStr(_Str);
		else
			f_AddStr(_Str);

		return *this;
	}

	template <typename t_CTCStrTraits>
	inline_small auto TCStr<t_CTCStrTraits>::operator [] (aint _Index) -> CChar &
	{
#ifdef DMibDebug
		// Only do range checking in debug because f_GetStrLen might be a fg_StrLen
		if (_Index < 0)
			DMibError("Range check error");
#endif
		CImp::f_MakeUnique();

		int MaxLen = CImp::f_CreateWritableBuffer(_Index + 1, false);
		if (_Index >= MaxLen)
		{
			static CChar SafeWrite;
			return SafeWrite;
		}

		return CImp::f_GetStrWritable()[_Index];
	}

	template <typename t_CTCStrTraits>
	inline_small auto TCStr<t_CTCStrTraits>::operator [] (aint _Index) const -> CChar const &
	{
#ifdef DMibDebug
		// Only do range checking in debug because f_GetStrLen might be a fg_StrLen
		if (_Index < 0 || _Index >= CImp::f_GetStrLen())
			DMibError("Range check error");
#endif

		return CImp::f_GetStr()[_Index];
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrTraitsF>
	inline_large auto TCStr<t_CTCStrTraits>::operator += (TCStr<tf_CStrTraitsF> &&_Str) -> TCStr &
	{
		if (this->f_IsEmpty())
			*this = fg_Move(_Str);
		else
			f_AddStr(_Str);

		return *this;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrTraitsF>
	auto TCStr<t_CTCStrTraits>::operator + (TCStr<tf_CStrTraitsF> const &_Str) const -> TCStr
	{
		if (this->f_IsEmpty())
			return _Str;
		else if (_Str.f_IsEmpty())
			return *this;

		TCStr Temp = *this;
		Temp.f_AddStr(_Str);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStrDataType>
	auto TCStr<t_CTCStrTraits>::operator + (tf_CStrDataType const *_pToAdd) const -> TCStr
	{
		TCStr Temp = *this;
		Temp.f_AddStr(_pToAdd);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	auto TCStr<t_CTCStrTraits>::operator ^ (umint _nCopies) const -> TCStr
	{
		if (!_nCopies)
			return {};

		TCStr Temp = *this;
		--_nCopies;

		for (; _nCopies; --_nCopies)
			Temp += *this;

		return Temp;
	}

	template <typename tf_CTCStrTraits, typename tf_CCharData>
	TCStr<tf_CTCStrTraits> operator + (tf_CCharData const *_pToAdd, TCStr<tf_CTCStrTraits> const &_Second)
	{
		TCStr<tf_CTCStrTraits> Temp;
		Temp.f_SetStr(_pToAdd);
		Temp.f_AddStr(_Second);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	bool TCStr<t_CTCStrTraits>::operator ! ()
	{
		return this->f_IsEmpty();
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	bool TCStr<t_CTCStrTraits>::operator == (TCStr<tf_CTCStrTraits> const &_Right) const noexcept
	{
		if (f_GetLen() != _Right.f_GetLen())
			return false;

		return fg_StrCmp(*this, _Right, f_GetLen()) == 0;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	bool TCStr<t_CTCStrTraits>::operator == (tf_CData const *_pRight) const noexcept
	{
		return fg_StrCmp(this->f_GetStr(), _pRight) == 0;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	COrdering_Strong TCStr<t_CTCStrTraits>::operator <=> (TCStr<tf_CTCStrTraits> const &_Right) const noexcept
	{
		return fg_StrCmp(this->f_GetStr(), _Right.f_GetStr()) <=> 0;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	COrdering_Strong TCStr<t_CTCStrTraits>::operator <=> (tf_CData const *_pRight) const noexcept
	{
		return fg_StrCmp(this->f_GetStr(), _pRight) <=> 0;
	}

}
