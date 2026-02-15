// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	inline_always CStr::CFormat operator ""_f (const char *_pStr, std::size_t _Len)
	{
		return CStr::CFormat(_pStr);
	}

	inline_always CWStr::CFormat operator ""_f (const ch16 *_pStr, std::size_t _Len)
	{
		return CWStr::CFormat(_pStr);
	}

	inline_always CUStr::CFormat operator ""_f (const ch32 *_pStr, std::size_t _Len)
	{
		return CUStr::CFormat(_pStr);
	}
}
