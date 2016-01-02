// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib
{
	namespace NStr
	{
		template <typename t_CIterator, typename t_CBackIterator>
		class TCIterator_UTF8EncodeOutput;
	}
}

#include "Malterlib_String_Iterator_UTF8EncodeOutput_Private.h"
namespace NMib
{
	namespace NStr
	{
		template <typename t_CRange>
		auto fg_RangeAdaptor_UTF8EncodeOutput(t_CRange const &_Range)
			-> decltype
			(
				NPrivate::fg_Private_RangeAdaptor_UTF8EncodeOutput
				(
					_Range
					, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
				)
			)
		;
	}
}

#include "Malterlib_String_Iterator_UTF8EncodeOutput.hpp"
