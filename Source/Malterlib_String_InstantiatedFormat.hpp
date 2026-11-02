// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

// The format types of the arguments formatted the most, whose virtual functions would otherwise be instantiated in each file that formats one

namespace NMib::NStr
{
	extern template struct TCStrFormatType_TStr<TCFormat<CStrTraits_CStr>, CStrTraits_CStr, true>;
	extern template struct TCStrFormatType_TStr<TCFormat<CStrTraits_CStrNonTracked>, CStrTraits_CStr, true>;

	extern template struct TCStrFormatType_String<TCFormat<CStrTraits_CStr>, ch8, EStrType_UTF>;
	extern template struct TCStrFormatType_String<TCFormat<CStrTraits_CStr>, ch8 const, EStrType_UTF>;
	extern template struct TCStrFormatType_String<TCFormat<CStrTraits_CStrNonTracked>, ch8, EStrType_UTF>;
	extern template struct TCStrFormatType_String<TCFormat<CStrTraits_CStrNonTracked>, ch8 const, EStrType_UTF>;

	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, int8 const &>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint8 const &>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, int32 const &>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint32 const &>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, int64 const &>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint64 const &>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint8>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint32>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, int8, TCStringFormatter<TCFormat<CStrTraits_CStr>, bool>::CBoolOptions>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStrNonTracked>, int32 const &>;
#ifdef DMibPUniqueType_mint
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, umint const &>;
	extern template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStrNonTracked>, umint const &>;
#endif

	extern template struct TCStrFormatType_Float<TCFormat<CStrTraits_CStr>, 1, 11, 52, 0, fp64::CImplicitFloat, true, NTraits::TCIntFromSizeLarger<8>, true>;
}
