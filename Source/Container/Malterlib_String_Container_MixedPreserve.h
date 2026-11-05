// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_String_Container_Mixed.h"

namespace NMib::NStr
{
	DMibDeprecatedSuppressStart;

	struct CMStrPreserve : public CMStrDeprecated
	{
		CMStrPreserve();
		CMStrPreserve(CMStrPreserve const &_Other);
		CMStrPreserve(CMStrPreserve &&_Other);
		template <typename tf_CValue>
		CMStrPreserve(tf_CValue &&_Other);

		CMStrPreserve &operator = (CMStrPreserve const &_Other);
		CMStrPreserve &operator = (CMStrPreserve &&_Other);
		template <typename tf_CValue>
		CMStrPreserve &operator = (tf_CValue &&_Other);

		EMStrType m_MixedType = EMStrType_CStr;
		EStrType m_OriginalType = EStrType_UTF;
	};

	DMibDeprecatedSuppressStop;
}

#include "Malterlib_String_Container_MixedPreserve.hpp"
