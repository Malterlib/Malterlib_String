// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	// TCAutoClearInt String Formatter
	template <typename t_CFormatter, typename t_CInt, t_CInt t_ClearVal>
	struct TCStringFormatter<t_CFormatter, NMib::TCAutoClearInt<t_CInt, t_ClearVal>>
	{
		using CData = NMib::TCAutoClearInt<t_CInt, t_ClearVal>;

	private:
		static t_CFormatter &fsp_GetFormatter();

	public:
		using CFormatType = decltype(fg_GetStringFormatType(fsp_GetFormatter(), t_CInt(0)));

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, CData const &_Data) -> decltype(fg_CreateStringFormatter(_Formatter, _Data.m_Int));
	};
}

#include "Container/Malterlib_String_Container_Format_AutoClear.hpp"
