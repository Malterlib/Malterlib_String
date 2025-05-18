// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/String/IteratorUTF8EncodeOutput>
#include <Mib/String/IteratorUTF16EncodeOutput>

namespace NMib::NStr::NPrivate
{
	template <typename t_CRange>
	t_CRange fg_Private_RangeAdaptor_UTFEncodeOutput(t_CRange const &_Range, NStr::CIteratorStringEncoding_UTF32)
	{
		return _Range;
	}

	template <typename t_CRange>
	auto fg_Private_RangeAdaptor_UTFEncodeOutput(t_CRange const &_Range, NStr::CIteratorStringEncoding_UTF16)
		-> decltype(fg_RangeAdaptor_UTF16EncodeOutput(_Range))
	{
		return fg_RangeAdaptor_UTF16EncodeOutput(_Range);
	}

	template <typename t_CRange>
	auto fg_Private_RangeAdaptor_UTFEncodeOutput(t_CRange const &_Range, NStr::CIteratorStringEncoding_UTF8)
		-> decltype(fg_RangeAdaptor_UTF8EncodeOutput(_Range))
	{
		return fg_RangeAdaptor_UTF8EncodeOutput(_Range);
	}
}

namespace NMib::NStr
{
	template <typename t_CRange>
	auto fg_RangeAdaptor_UTFEncodeOutput(t_CRange const &_Range)
		-> decltype
		(
			NPrivate::fg_Private_RangeAdaptor_UTFEncodeOutput
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsFront, NStr::CIteratorStringEncoding_None>::CType()
			)
		)
	{
//			static_assert(NTraits::cIsConvertible<typename t_CRange::CTagsFront, TCTags<NStr::CIteratorStringEncoding_UTF32>>, "Range must be UTF32 encoded");
		return NPrivate::fg_Private_RangeAdaptor_UTFEncodeOutput
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsFront, NStr::CIteratorStringEncoding_None>::CType()
			)
		;
	}
}
