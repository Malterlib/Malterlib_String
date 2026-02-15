// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

DMibDeprecatedSuppressStart;

namespace NMib::NStr
{
	// Combines CStr, CWStr and CUStr to create a string class supporting all of the above character types as needed.

	enum EMStr_Type
	{
		EMStr_Type_None = 0
		, EMStr_Type_CStr = 1
		, EMStr_Type_CWStr = 2
		, EMStr_Type_CUStr = 3
	};

	struct CMStrDeprecated : public CStr
	{
		CMStrDeprecated();
		CMStrDeprecated(CMStrDeprecated const &_Other);
		CMStrDeprecated(CMStrDeprecated &&_Other);
		template <typename tf_CValue>
		CMStrDeprecated(tf_CValue &&_Other);

		CMStrDeprecated &operator =(CMStrDeprecated const &_Other);
		CMStrDeprecated &operator =(CMStrDeprecated &&_Other);
		template <typename tf_CValue>
		CMStrDeprecated &operator =(tf_CValue &&_Other);
	};

	template <typename tf_CStrTraits>
	inline_large TCStr<tf_CStrTraits> &operator += (TCStr<tf_CStrTraits> &_Dest, CMStrDeprecated const &_String);
}

DMibTypeID(NMib::NStr::CMStrDeprecated, DMibCurrentTypeID + 27);

DMibDeprecatedSuppressStop;

#include "Malterlib_String_Container_Mixed.hpp"
