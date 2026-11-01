// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	static inline CStrNonTracked::CFormat fg_GetStringFormat(ch8 const *_pFormat);
	static inline CWStrNonTracked::CFormat fg_GetStringFormat(ch16 const *_pFormat);
	static inline CUStrNonTracked::CFormat fg_GetStringFormat(ch32 const *_pFormat);

	template <typename tf_CFormat, typename ...tfp_CParams>
	CStr fg_Format(tf_CFormat const &_Format, tfp_CParams && ...p_Params);
}

#include "Malterlib_String_Container_FormatHelpers.hpp"
