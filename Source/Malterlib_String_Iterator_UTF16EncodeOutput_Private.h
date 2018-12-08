// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr::NPrivate
{
	template <typename t_CRange>
	auto fg_Private_RangeAdaptor_UTF16EncodeOutput(t_CRange const &_Range, NIterator::CIteratorAccess_None)
		-> NIterator::TCRange
		<
			NIterator::TCIterator<TCIterator_UTF16EncodeOutput<typename t_CRange::CFront::CImplementation, typename t_CRange::CBack::CImplementation>>
			, typename t_CRange::CBack
		>
	;
}
	
