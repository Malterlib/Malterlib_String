// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr::NPlatform
{
	void fg_SystemDecodeAnsiStr(ch8 const *_pIn, NMib::NStr::CStr &_Out);
	void fg_SystemDecodeAnsiStr(ch8 const *_pIn, NMib::NStr::CStrNonTracked &_Out);
	void fg_SystemDecodeAnsiStr(NMib::NStr::CAnsiStr const &_In, NMib::NStr::CStr &_Out);
	void fg_SystemDecodeAnsiStr(NMib::NStr::CAnsiStrNonTracked const &_In, NMib::NStr::CStrNonTracked &_Out);

	void fg_SystemEncodeAnsiStr(NMib::NStr::CStr const &_In, NMib::NStr::CAnsiStr &_Out, ch8 _ErrorChar);
	void fg_SystemEncodeAnsiStr(NMib::NStr::CStrNonTracked const &_In, NMib::NStr::CAnsiStrNonTracked &_Out, ch8 _ErrorChar);

	void fg_SystemDecodeCodePageStr(ch8 const *_pIn, NMib::NStr::CStr &_Out, uint32 _CodePage);
	void fg_SystemDecodeCodePageStr(ch8 const *_pIn, NMib::NStr::CStrNonTracked &_Out, uint32 _CodePage);
	void fg_SystemDecodeCodePageStr(NMib::NStr::CAnsiStr const &_In, NMib::NStr::CStr &_Out, uint32 _CodePage);
	void fg_SystemDecodeCodePageStr(NMib::NStr::CAnsiStrNonTracked const &_In, NMib::NStr::CStrNonTracked &_Out, uint32 _CodePage);

	void fg_SystemEncodeCodePageStr(NMib::NStr::CStr const &_In, NMib::NStr::CAnsiStr &_Out, uint32 _CodePage, ch8 _ErrorChar);
	void fg_SystemEncodeCodePageStr(NMib::NStr::CStrNonTracked const &_In, NMib::NStr::CAnsiStrNonTracked &_Out, uint32 _CodePage, ch8 _ErrorChar);
}
