// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib
{
	namespace NStr
	{
		template <typename t_CIterator>
		class TCIterator_UTF8Encode;
	}
}

#include "Malterlib_String_Iterator_UTF8Encode_Private.h"
namespace NMib
{
	namespace NStr
	{
#ifndef DCompiler_MSVC_Workaround
		template <typename t_CRange>
		auto fg_RangeAdaptor_UTF8Encode(t_CRange const &_Range)
			-> decltype
			(
				NPrivate::fg_Private_RangeAdaptor_UTF8Encode
				(
					_Range
					, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
				)
			)
		;
#endif
	}
}

#include "Malterlib_String_Iterator_UTF8Encode.hpp"
