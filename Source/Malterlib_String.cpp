// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

namespace NMib::NStr
{
	DMibImpErrorClassImplement(CExceptionParse);

	template struct TCStr<CStrTraits_CStr>;
	template struct TCStr<CStrTraits_CWStr>;
	template struct TCStr<CStrTraits_CUStr>;
	template struct TCFormat<CStrTraits_CStr>;
	template struct TCFormat<CStrTraits_CWStr>;
	template struct TCFormat<CStrTraits_CUStr>;

	template struct TCStr<CStrTraits_CStrNonTracked>;
	template struct TCStr<CStrTraits_CWStrNonTracked>;
	template struct TCStr<CStrTraits_CUStrNonTracked>;
	template struct TCFormat<CStrTraits_CStrNonTracked>;
	template struct TCFormat<CStrTraits_CWStrNonTracked>;
	template struct TCFormat<CStrTraits_CUStrNonTracked>;

	template struct TCStr<CStrTraits_CStrVMem>;
	template struct TCStr<CStrTraits_CWStrVMem>;
	template struct TCStr<CStrTraits_CUStrVMem>;

	template struct TCStrImp_Dynamic<CStrTraits_CStr::CStrTraits>;
	template struct TCStrImp_Dynamic<CStrTraits_CWStr::CStrTraits>;
	template struct TCStrImp_Dynamic<CStrTraits_CUStr::CStrTraits>;

	template struct TCStrImp_Dynamic_StringData<ch8>;
	template struct TCStrImp_Dynamic_StringData<ch16>;
	template struct TCStrImp_Dynamic_StringData<ch32>;

	template struct TCStrImp_Dynamic_EmptyStringData<ch8>;
	template struct TCStrImp_Dynamic_EmptyStringData<ch16>;
	template struct TCStrImp_Dynamic_EmptyStringData<ch32>;

	template struct TCStrImp_Dynamic_EmptyStringDataImp<ch8>;
	template struct TCStrImp_Dynamic_EmptyStringDataImp<ch16>;
	template struct TCStrImp_Dynamic_EmptyStringDataImp<ch32>;

	template TCStr<NMib::NStr::CStrTraits_CStrNonTracked> &TCStr<NMib::NStr::CStrTraits_CStrNonTracked>::operator= (TCStr<NMib::NStr::CStrTraits_CStr> const &);
	template void NMib::NStr::TCStr<NMib::NStr::CStrTraits_CStrNonTracked>::f_SetStr(TCStr<NMib::NStr::CStrTraits_CStr> const &);

#ifdef DMibDebug
	CWStr g_DebugOutputTemp16;
	CStr g_DebugOutputTemp8;
#endif
}
