// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	namespace NStr
	{
		namespace NPrivate
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
				static_assert(NTraits::TCIsVoid<tf_CRange>::mc_Value, "This encoding is not supported");
			}
		};
	}
}
	
