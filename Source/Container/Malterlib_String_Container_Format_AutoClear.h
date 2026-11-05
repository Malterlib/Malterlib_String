// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	// TCAutoClearInt String Formatter
	template <typename t_CFormatter, typename t_CInt, t_CInt t_ClearVal>
	struct TCStringFormatter<t_CFormatter, NMib::TCAutoClearInt<t_CInt, t_ClearVal>>
	{
		using CData = NMib::TCAutoClearInt<t_CInt, t_ClearVal>;
		using CFormatType = decltype(fg_GetStringFormatType(fg_GetType<t_CFormatter &>(), t_CInt(0)));

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, CData const &_Data) -> decltype(fg_CreateStringFormatter(_Formatter, _Data.m_Int));
	};
}

#include "Malterlib_String_Container_Format_AutoClear.hpp"
