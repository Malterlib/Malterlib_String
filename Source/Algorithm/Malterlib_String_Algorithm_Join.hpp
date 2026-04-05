// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CStrType0, typename tf_CStrType1, typename tf_CStrType2>
	void fg_StrAddWithSeparator(tf_CStrType0 &_Str, tf_CStrType1 const &_ToAdd, tf_CStrType2 const &_Separator)
	{
		if (!_Str.f_IsEmpty())
			_Str += _Separator;
		_Str += _ToAdd;
	}

	template <typename tf_CStrType0, typename tf_CStrType1>
	void fg_AddStrSepEscaped(tf_CStrType0 &_Str, tf_CStrType1 const &_ToAdd, ch8 _Sep, ch8 const *_pNeedEscapeChars)
	{
		if (!_Str.f_IsEmpty())
			_Str.f_AddChar(_Sep);
		if (fg_StrIsEmpty(_ToAdd) || fg_StrFindChar(_ToAdd, _Sep) >= 0 || fg_StrFindChars(_ToAdd, _pNeedEscapeChars) >= 0)
			_Str += typename tf_CStrType0::CString(_ToAdd).f_EscapeStr();
		else
			_Str += _ToAdd;
	}

	template <typename tf_CStrType0, typename tf_CStrType1, typename tf_CStrType2>
	void fg_AddStrSep(tf_CStrType0 &_Str, tf_CStrType1 const &_ToAdd, tf_CStrType2 const &_Separator)
	{
		if (!_Str.f_IsEmpty())
			_Str += _Separator;
		_Str += _ToAdd;
	}
}
