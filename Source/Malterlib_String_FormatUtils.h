// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include <Mib/String/Appender>

namespace NMib::NStr
{
	template <typename t_CStr>
	struct TCFormatUtilities
	{
		TCFormatUtilities(typename t_CStr::CAppender &_Appender);

		template <typename tf_CValue>
		void f_Value(tf_CValue &&_Value);
		template <typename tf_CName, typename tf_CValue>
		void f_TitledValue(tf_CName &&_Name, tf_CValue &&_Value);

	private:
		typename t_CStr::CAppender &mp_Appender;
	};
}

#include "Malterlib_String_FormatUtils.hpp"
