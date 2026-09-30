// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	inline_always CStr::CFormat operator ""_f (char const *_pStr, std::size_t _Len)
	{
		return CStr::CFormat(_pStr);
	}

	inline_always CWStr::CFormat operator ""_f (ch16 const *_pStr, std::size_t _Len)
	{
		return CWStr::CFormat(_pStr);
	}

	inline_always CUStr::CFormat operator ""_f (ch32 const *_pStr, std::size_t _Len)
	{
		return CUStr::CFormat(_pStr);
	}
}
