// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_String_Container_Mixed.h"

namespace NMib::NStr
{
	CMStrDeprecated::CMStrDeprecated()
	{
	}

	CMStrDeprecated::CMStrDeprecated(CMStrDeprecated const &_Other)
		: CStr((CStr const &)_Other)
	{
	}

	CMStrDeprecated::CMStrDeprecated(CMStrDeprecated &&_Other)
		: CStr(fg_Move((CStr &)_Other))
	{
	}

	CMStrDeprecated &CMStrDeprecated::operator =(CMStrDeprecated const &_Other)
	{
		(CStr &)*this = (CStr const &)_Other;
		return *this;
	}

	CMStrDeprecated &CMStrDeprecated::operator =(CMStrDeprecated &&_Other)
	{
		(CStr &)*this = fg_Move((CStr &)_Other);
		return *this;
	}
}
