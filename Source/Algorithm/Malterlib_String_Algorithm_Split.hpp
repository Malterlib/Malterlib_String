// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CStrType>
	tf_CStrType fg_GetStrSep(tf_CStrType &_Str, ch8 const *_pSep)
	{
		tf_CStrType Ret;
		aint iFind = _Str.f_Find(_pSep);
		if (iFind >= 0)
		{
			Ret = _Str.f_Left(iFind);
			_Str = _Str.f_Extract(iFind + fg_StrLen(_pSep));
		}
		else
		{
			Ret = _Str;
			_Str = "";
		}
		Ret = Ret.f_TrimLeft();
		Ret = Ret.f_TrimRight();
		return Ret;
	}

	template <typename tf_CStrType>
	tf_CStrType fg_GetStrSepNoTrim(tf_CStrType &_Str, ch8 const *_pSep)
	{
		tf_CStrType Ret;
		aint iFind = _Str.f_Find(_pSep);
		if (iFind >= 0)
		{
			Ret = _Str.f_Left(iFind);
			_Str = _Str.f_Extract(iFind + fg_StrLen(_pSep));
		}
		else
		{
			Ret = _Str;
			_Str = "";
		}
		return Ret;
	}

	template <typename tf_CStrType>
	tf_CStrType fg_GetStrLineSep(tf_CStrType &_Str)
	{
		tf_CStrType Ret;
		aint iFind = _Str.f_FindChars("\r\n");
		if (iFind >= 0)
		{
			Ret = _Str.f_Left(iFind);
			if (_Str.f_GetAt(iFind) == '\r')
				++iFind;
			if (_Str.f_GetAt(iFind) == '\n')
				++iFind;
			_Str = _Str.f_Extract(iFind);
		}
		else
		{
			Ret = _Str;
			_Str = "";
		}
		return Ret;
	}

	template <typename tf_CStrType, typename tf_CSeparators>
	tf_CStrType fg_GetStrSeparators(tf_CStrType &_Str, tf_CSeparators const *_pSeparators)
	{
		tf_CStrType Ret;
		aint iFind = _Str.f_FindChars(_pSeparators);
		if (iFind >= 0)
		{
			Ret = _Str.f_Left(iFind);
			_Str = _Str.f_Extract(iFind + 1);
		}
		else
		{
			Ret = _Str;
			_Str = "";
		}
		Ret = Ret.f_TrimLeft();
		Ret = Ret.f_TrimRight();
		return Ret;
	}
}
