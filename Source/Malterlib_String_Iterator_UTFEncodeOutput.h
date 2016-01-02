// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>


#include "Malterlib_String_Iterator_UTFEncodeOutput_Private.h"
namespace NMib
{
	namespace NStr
	{
		template <typename t_CRange>
		auto fg_RangeAdaptor_UTFEncodeOutput(t_CRange const &_Range)
			-> decltype
			(
				NPrivate::fg_Private_RangeAdaptor_UTFEncodeOutput
				(
					_Range
					, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
				)
			)
		;
	}
}

#include "Malterlib_String_Iterator_UTFEncodeOutput.hpp"
