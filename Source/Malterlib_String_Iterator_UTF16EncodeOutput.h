// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib::NStr
{
	template <typename t_CIterator, typename t_CBackIterator>
	class TCIterator_UTF16EncodeOutput;
}

#include "Malterlib_String_Iterator_UTF16EncodeOutput_Private.h"
namespace NMib::NStr
{
	template <typename t_CRange>
	auto fg_RangeAdaptor_UTF16EncodeOutput(t_CRange const &_Range)
		-> decltype
		(
			NPrivate::fg_Private_RangeAdaptor_UTF16EncodeOutput
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
			)
		)
	;
}

#include "Malterlib_String_Iterator_UTF16EncodeOutput.hpp"
