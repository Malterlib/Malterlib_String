// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	struct CFuzzyMatchRange
	{
		aint m_iStart = 0;
		aint m_iEnd = 0;
	};

	struct CFuzzyMatchResult
	{
		fp64 m_Score = -1.0;
		NContainer::TCVector<CFuzzyMatchRange> m_Matches;

		explicit operator bool() const { return m_Score >= 0.0; }
	};

	CFuzzyMatchResult fg_FuzzyMatchString(CStr const &_Str0, CStr const &_Str1);
}
