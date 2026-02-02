// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CString>
	struct TCStringAppender
	{
		using CString = t_CString;
		using CDynamicStr = t_CString;

		TCStringAppender(t_CString &_String);
		~TCStringAppender();

		struct CCommitted
		{
			t_CString &m_String;

			CCommitted(TCStringAppender &_Appender);
			~CCommitted();
			void f_Abort();
		private:
			TCStringAppender *mp_pAppender;
		};

		void operator += (typename t_CString::CUnsignedChar _Character);

		template <typename tf_CChar, mint tf_ArrayLength>
		void operator += (tf_CChar const (&_Array)[tf_ArrayLength]);

		void operator += (t_CString const &_String);

		template <typename tf_CStrTraits>
		void operator += (NStr::TCStr<tf_CStrTraits> const &_String);

		void f_AddUnicodeChar(ch32 _Character);
		void f_AddChar(typename t_CString::CUnsignedChar _Character);

		void f_AddString(typename t_CString::CChar const *_pString, mint _Len);

		CCommitted f_Commit();
		mint f_GetStrLen() const;
		bool f_IsEmpty() const;

	private:
		void fp_Reset();
		void fp_Commit();

		t_CString &mp_String;
		mint mp_StrLen;
		mint mp_MaxLen;
		typename t_CString::CUnsignedChar *mp_pStrOut;
		bool mp_bChanged;
	};
}

#include "Malterlib_String_Appender.hpp"
