// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	// TCAutoClearInt String Formatter
	template <typename t_CFormatter, typename t_CInt, t_CInt t_ClearVal>
	template <typename tf_CTypeWithConst>
	auto TCStringFormatter<t_CFormatter, NMib::TCAutoClearInt<t_CInt, t_ClearVal>>
		::fs_CreateFormat(t_CFormatter &_Formatter, CData const &_Data) -> decltype(fg_CreateStringFormatter(_Formatter, _Data.m_Int))
	{
		return fg_CreateStringFormatter(_Formatter, _Data.m_Int);
	}
}
