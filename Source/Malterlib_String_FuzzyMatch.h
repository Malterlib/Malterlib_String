// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	struct CFuzzyMatchRange
	{
		template <typename tf_CStr>
		void f_Format(tf_CStr &o_Str) const
		{
			o_Str += typename tf_CStr::CFormat("{} -> {}") << m_iStart << m_iEnd;
		}

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
