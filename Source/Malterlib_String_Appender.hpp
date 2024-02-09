// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CString>
	TCStringAppender<t_CString>::CCommitted::~CCommitted()
	{
		if (mp_pAppender)
			mp_pAppender->fp_Reset();
	}

	template <typename t_CString>
	TCStringAppender<t_CString>::CCommitted::CCommitted(TCStringAppender &_Appender)
		: mp_pAppender(&_Appender)
		, m_String(_Appender.mp_String)
	{
	}

	template <typename t_CString>
	void TCStringAppender<t_CString>::CCommitted::f_Abort()
	{
		mp_pAppender = nullptr;
	}

	template <typename t_CString>
	TCStringAppender<t_CString>::TCStringAppender(t_CString &_String)
		: mp_String(_String)
	{
		fp_Reset();
	}

	template <typename t_CString>
	TCStringAppender<t_CString>::~TCStringAppender()
	{
		mp_String.f_Reserve(0);
		mp_bChanged = true;
		fp_Commit();
	}

	template <typename t_CString>
	void TCStringAppender<t_CString>::f_AddString(typename t_CString::CChar const *_pString, mint _Len)
	{
		if (mp_StrLen + _Len > mp_MaxLen)
		{
			fp_Commit();
			mp_String.f_AddStr(_pString, _Len);
			mp_StrLen = mp_String.f_GetStrLen();
			mp_String.f_Reserve(mp_StrLen + 1);
			mp_pStrOut = (typename t_CString::CUnsignedChar *)(mp_String.f_GetStrWritable() + mp_StrLen);
			mp_MaxLen = mp_String.f_GetLength() - 1;
			mp_bChanged = false;

			return;
		}

		{
			auto pFrom = _pString;
			auto pTo = mp_pStrOut;
			auto pEnd = mp_pStrOut + _Len;
			while (pTo < pEnd)
				*pTo++ = *pFrom++;
			mp_pStrOut = pTo;
		}
		mp_StrLen += _Len;
		mp_bChanged = true;
	}

	template <typename t_CString>
	template <typename tf_CChar, mint tf_ArrayLength>
	void TCStringAppender<t_CString>::operator += (tf_CChar const (&_Array)[tf_ArrayLength])
	{
		f_AddString(_Array, tf_ArrayLength - 1);
	}

	template <typename t_CString>
	void TCStringAppender<t_CString>::operator += (t_CString const &_String)
	{
		f_AddString(_String.f_GetStr(), _String.f_GetLen());
	}

	template <typename t_CString>
	template <typename tf_CStrTraits>
	void TCStringAppender<t_CString>::operator += (NStr::TCStr<tf_CStrTraits> const &_String)
	{
		f_AddString(_String.f_GetStr(), _String.f_GetLen());
	}

	template <typename t_CString>
	void TCStringAppender<t_CString>::f_AddUnicodeChar(ch32 _Character)
	{
		if constexpr (sizeof(typename t_CString::CChar) == 1)
		{
			static_assert(t_CString::mc_Type == EStrType_UTF, "Lossy conversion");

			fg_EncodeUTF8Char<true>
				(
					_Character
					, [&](mint _nChars) inline_always_lambda ->typename t_CString::CUnsignedChar *
					{
						mint NeededLen = mp_StrLen + _nChars;
						if (NeededLen > mp_MaxLen)
						{
							fp_Commit();
							mp_String.f_Reserve(NeededLen);
							mp_pStrOut = (typename t_CString::CUnsignedChar *)(mp_String.f_GetStrWritable() + mp_StrLen);
							mp_MaxLen = mp_String.f_GetLength() - 1;
							if (mp_MaxLen < NeededLen)
								return nullptr; // Overflow
						}

						auto *pReturn = mp_pStrOut;

						mp_StrLen += _nChars;
						mp_pStrOut += _nChars;
						mp_bChanged = true;

						return pReturn;
					}
				)
			;
		}
		else if constexpr (sizeof(typename t_CString::CChar) == 2)
		{
			static_assert(t_CString::mc_Type == EStrType_UTF, "Lossy conversion");

			fg_EncodeUTF16Char<true>
				(
					_Character
					, [&](mint _nChars) inline_always_lambda -> typename t_CString::CUnsignedChar *
					{
						mint NeededLen = mp_StrLen + _nChars;
						if (mp_MaxLen < NeededLen)
						{
							fp_Commit();
							mp_String.f_Reserve(NeededLen);
							mp_pStrOut = (typename t_CString::CUnsignedChar *)(mp_String.f_GetStrWritable() + mp_StrLen);
							mp_MaxLen = mp_String.f_GetLength() - 1;
							if (mp_MaxLen < NeededLen)
								return nullptr; // Overflow
						}

						auto *pReturn = mp_pStrOut;

						mp_StrLen += _nChars;
						mp_pStrOut += _nChars;
						mp_bChanged = true;

						return pReturn;
					}
				)
			;
		}
		else
			*this += _Character;
	}
	

	template <typename t_CString>
	void TCStringAppender<t_CString>::operator += (typename t_CString::CUnsignedChar _Character)
	{
		DMibFastCheck(((typename t_CString::CUnsignedChar *)mp_String.f_GetStrWritable() + mp_StrLen) == mp_pStrOut);

		if (mp_StrLen >= mp_MaxLen)
		{
			fp_Commit();
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
	void TCStringAppender<t_CString>::fp_Reset()
	{
		mp_StrLen = mp_String.f_GetStrLen();
		mp_String.f_Reserve(mp_StrLen + 1);
		mp_pStrOut = (typename t_CString::CUnsignedChar *)(mp_String.f_GetStrWritable() + mp_StrLen);
		mp_MaxLen = mp_String.f_GetLength() - 1;
		mp_bChanged = false;
	}

	template <typename t_CString>
	void TCStringAppender<t_CString>::fp_Commit()
	{
		*mp_pStrOut = 0;

		if (mp_bChanged)
		{
			mp_String.f_SetStrLen(mp_StrLen);
			mp_bChanged = false;
		}
	}

	template <typename t_CString>
	auto TCStringAppender<t_CString>::f_Commit() -> CCommitted
	{
		fp_Commit();

		return *this;
	}

	template <typename t_CString>
	mint TCStringAppender<t_CString>::f_GetStrLen() const
	{
		return mp_StrLen;
	}
}
