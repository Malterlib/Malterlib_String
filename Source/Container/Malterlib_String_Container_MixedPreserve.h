// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_String_Container_Mixed.h"

namespace NMib::NStr
{
	DMibDeprecatedSuppressStart;

	struct CMStrPreserve : public CMStrDeprecated
	{
		EMStr_Type m_MixedType = EMStr_Type_CStr;
		EStrType m_OriginalType = EStrType_UTF;

		CMStrPreserve();
		CMStrPreserve(CMStrPreserve const &_Other);
		CMStrPreserve(CMStrPreserve &&_Other);
		template <typename tf_CValue>
		CMStrPreserve(tf_CValue &&_Other);

		CMStrPreserve &operator =(CMStrPreserve const &_Other);
		CMStrPreserve &operator =(CMStrPreserve &&_Other);
		template <typename tf_CValue>
		CMStrPreserve &operator =(tf_CValue &&_Other);
	};

	DMibDeprecatedSuppressStop;
}

#include "Malterlib_String_Container_MixedPreserve.hpp"
