// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr::NPrivate
{
	template <typename tf_CRange>
	void fg_Private_RangeAdaptor_UTFDecode
		(
			tf_CRange &&_rCharacters
			, NStr::CIteratorStringEncoding_None
			, NIterator::CIteratorTraversal_None
			, NStr::CIteratorStringEncoding_None
			, NIterator::CIteratorTraversal_None
		)
	{
		static_assert(NTraits::cIsVoid<tf_CRange>, "This encoding is not supported");
	}
}
