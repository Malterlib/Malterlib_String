// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CString>
	TCStringAppender<t_CString>::TCStringAppender(t_CString &_String)
		: mp_String(_String)
	{
		f_Reset();
	}

	template <typename t_CString>
	TCStringAppender<t_CString>::~TCStringAppender()
	{
		mp_String.f_Reserve(0);
		mp_bChanged = true;
		f_Commit();
	}

	template <typename t_CString>
	void TCStringAppender<t_CString>::operator += (typename t_CString::CUnsignedChar _Character)
	{
		DMibFastCheck(((typename t_CString::CUnsignedChar *)mp_String.f_GetStrWritable() + mp_StrLen) == mp_pStrOut);

		if (mp_StrLen >= mp_MaxLen)
		{
			f_Commit();
			mp_String.f_Reserve(mp_StrLen + 1);
			mp_pStrOut = (typename t_CString::CUnsignedChar *)(mp_String.f_GetStrWritable() + mp_StrLen);
			mp_MaxLen = mp_String.f_GetLength() - 1;
		}

		*mp_pStrOut = _Character;
		++mp_pStrOut;
		++mp_StrLen;
		mp_bChanged = true;
	}

	template <typename t_CString>
	void TCStringAppender<t_CString>::f_Reset()
	{
		mp_StrLen = mp_String.f_GetStrLen();
		mp_String.f_Reserve(mp_StrLen + 1);
		mp_pStrOut = (typename t_CString::CUnsignedChar *)(mp_String.f_GetStrWritable() + mp_StrLen);
		mp_MaxLen = mp_String.f_GetLength() - 1;
		mp_bChanged = false;
	}

	template <typename t_CString>
	void TCStringAppender<t_CString>::f_Commit()
	{
		*mp_pStrOut = 0;

		if (mp_bChanged)
		{
			mp_String.f_SetStrLen(mp_StrLen);
			mp_bChanged = false;
		}
	}

	template <typename t_CString>
	mint TCStringAppender<t_CString>::f_GetStrLen() const
	{
		return mp_StrLen;
	}
}
