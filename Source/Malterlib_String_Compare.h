// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	struct CCompareNoCase
	{
		template <typename tf_CLeft, typename tf_CRight>
		COrdering_Weak operator()(const tf_CLeft &_Left, const tf_CRight &_Right) const;
	};
}

#include "Malterlib_String_Compare.hpp"
