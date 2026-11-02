// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template struct TCStrFormatType_TStr<TCFormat<CStrTraits_CStr>, CStrTraits_CStr, true>;
	template struct TCStrFormatType_TStr<TCFormat<CStrTraits_CStrNonTracked>, CStrTraits_CStr, true>;

	template struct TCStrFormatType_String<TCFormat<CStrTraits_CStr>, ch8, EStrType_UTF>;
	template struct TCStrFormatType_String<TCFormat<CStrTraits_CStr>, ch8 const, EStrType_UTF>;
	template struct TCStrFormatType_String<TCFormat<CStrTraits_CStrNonTracked>, ch8, EStrType_UTF>;
	template struct TCStrFormatType_String<TCFormat<CStrTraits_CStrNonTracked>, ch8 const, EStrType_UTF>;

	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, int8 const &>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint8 const &>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, int32 const &>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint32 const &>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, int64 const &>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint64 const &>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint8>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, uint32>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, int8, TCStringFormatter<TCFormat<CStrTraits_CStr>, bool>::CBoolOptions>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStrNonTracked>, int32 const &>;
#ifdef DMibPUniqueType_mint
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStr>, umint const &>;
	template struct TCStrFormatType_Int<TCFormat<CStrTraits_CStrNonTracked>, umint const &>;
#endif

	template struct TCStrFormatType_Float<TCFormat<CStrTraits_CStr>, 1, 11, 52, 0, fp64::CImplicitFloat, true, NTraits::TCIntFromSizeLarger<8>, true>;
}
