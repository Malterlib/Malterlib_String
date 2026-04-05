// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	enum struct EValidateUTF8Flag : uint32
	{
		mc_None = 0
		, mc_DisallowNonCharacters = fg_Bit(0)
	};

	bool fg_IsValidUTF8(CStr const &_Str, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None);
	bool fg_IsValidUTF8(ch8 const *_pStr, umint _Len, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None);
	CStr fg_ReplaceCharactersUTF8(CStr const &_Str, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None, uch8 _ReplacementChar = '?');
	CStr fg_ReplaceSequenceUTF8(CStr const &_Str, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None, CStr const &_ReplacementChar = CStr("\xef\xbf\xbd"));
	CStr fg_CleanUTF8(CStr const &_Str, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None);
}
