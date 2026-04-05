// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	extern template struct TCStr<CStrTraits_CStr>;
	extern template struct TCStr<CStrTraits_CWStr>;
	extern template struct TCStr<CStrTraits_CUStr>;
	extern template struct TCFormat<CStrTraits_CStr>;
	extern template struct TCFormat<CStrTraits_CWStr>;
	extern template struct TCFormat<CStrTraits_CUStr>;

	extern template struct TCStr<CStrTraits_CStrNonTracked>;
	extern template struct TCStr<CStrTraits_CWStrNonTracked>;
	extern template struct TCStr<CStrTraits_CUStrNonTracked>;
	extern template struct TCFormat<CStrTraits_CStrNonTracked>;
	extern template struct TCFormat<CStrTraits_CWStrNonTracked>;
	extern template struct TCFormat<CStrTraits_CUStrNonTracked>;

	extern template struct TCStr<CStrTraits_CStrVMem>;
	extern template struct TCStr<CStrTraits_CWStrVMem>;
	extern template struct TCStr<CStrTraits_CUStrVMem>;

	extern template struct TCStrImp_Dynamic<CStrTraits_CStr::CStrTraits>;
	extern template struct TCStrImp_Dynamic<CStrTraits_CWStr::CStrTraits>;
	extern template struct TCStrImp_Dynamic<CStrTraits_CUStr::CStrTraits>;

	extern template TCStr<NMib::NStr::CStrTraits_CStrNonTracked> &TCStr<NMib::NStr::CStrTraits_CStrNonTracked>::operator= (TCStr<NMib::NStr::CStrTraits_CStr> const &);
	extern template void NMib::NStr::TCStr<NMib::NStr::CStrTraits_CStrNonTracked>::f_SetStr(TCStr<NMib::NStr::CStrTraits_CStr> const &);
}
