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
			t_CRange fg_Private_RangeAdaptor_UTFEncodeOutput(t_CRange const &_Range, NStr::CIteratorStringEncoding_None)
			{
				static_assert(NTraits::TCIsVoid<t_CRange>::mc_Value, "Output range has no encoding");
				return _Range;				
			}
		}
	}
}
	
