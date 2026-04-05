// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CLeft, typename tf_CRight>
	COrdering_Weak CCompareNoCase::operator()(const tf_CLeft &_Left, const tf_CRight &_Right) const
	{
		return fg_StrCmpNoCase(_Left, _Right) <=> 0;
	}
}
