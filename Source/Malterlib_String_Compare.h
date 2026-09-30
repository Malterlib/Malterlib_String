// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	struct CCompareNoCase
	{
		template <typename tf_CLeft, typename tf_CRight>
		COrdering_Weak operator () (tf_CLeft const &_Left, tf_CRight const &_Right) const;
	};
}

#include "Malterlib_String_Compare.hpp"
