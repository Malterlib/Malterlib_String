// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	namespace NStr
	{
		namespace NPrivate
		{
			template <typename t_CRange>
			auto fg_Private_RangeAdaptor_UTF8Encode(t_CRange const &_Range, NIterator::CIteratorAccess_None)
				-> NIterator::TCRange
				<
					NIterator::TCIterator<TCIterator_UTF8Encode<typename t_CRange::CFront::CImplementation>>
					, typename t_CRange::CBack
				>
			;
		}
	}
}
	
