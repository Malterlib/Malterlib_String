// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	static inline CStrNonTracked::CFormat fg_GetStringFormat(const ch8 *_pFormat);
	static inline CWStrNonTracked::CFormat fg_GetStringFormat(const ch16 *_pFormat);
	static inline CUStrNonTracked::CFormat fg_GetStringFormat(const ch32 *_pFormat);

	template <typename tf_CFormat, typename... tfp_CParams>
	CStr fg_Format(tf_CFormat const &_Format, tfp_CParams &&...p_Params);
}

#include "Malterlib_String_Container_FormatHelpers.hpp"
