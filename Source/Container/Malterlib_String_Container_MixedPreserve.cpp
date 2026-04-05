// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_String_Container_MixedPreserve.h"

namespace NMib::NStr
{
	CMStrPreserve::CMStrPreserve()
	{
	}

	CMStrPreserve::CMStrPreserve(CMStrPreserve const &_Other)
		: CMStrDeprecated((CMStrDeprecated const &)_Other)
	{
	}

	CMStrPreserve::CMStrPreserve(CMStrPreserve &&_Other)
		: CMStrDeprecated(fg_Move((CMStrDeprecated &)_Other))
	{
	}

	CMStrPreserve &CMStrPreserve::operator =(CMStrPreserve const &_Other)
	{
		(CMStrDeprecated &)*this = (CMStrDeprecated const &)_Other;
		return *this;
	}

	CMStrPreserve &CMStrPreserve::operator =(CMStrPreserve &&_Other)
	{
		(CMStrDeprecated &)*this = fg_Move((CMStrDeprecated &)_Other);
		return *this;
	}
}
