// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CString>
	struct TCStringAppender
	{
		TCStringAppender(t_CString &_String);
		~TCStringAppender();

		void operator += (typename t_CString::CUnsignedChar _Character);

		void f_Reset();
		void f_Commit();
		mint f_GetStrLen() const;

	private:
		t_CString &mp_String;
		mint mp_StrLen;
		mint mp_MaxLen;
		typename t_CString::CUnsignedChar *mp_pStrOut;
		bool mp_bChanged;
	};
}

#include "Malterlib_String_Appender.hpp"
