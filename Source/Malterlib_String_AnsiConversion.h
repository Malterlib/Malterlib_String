// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	enum ECharacterEncoding : int32
	{
		ECharacterEncoding_Unicode,
		ECharacterEncoding_UTF8,
		ECharacterEncoding_UTF16,
		ECharacterEncoding_Windows_1252,
	};

	template <ECharacterEncoding t_CharacterEncoding>
	struct TCCharEncodingConverter
	{
	};

	template <>
	struct TCCharEncodingConverter<ECharacterEncoding_Windows_1252>
	{
		struct CTableEntry
		{
			ch16 m_UnicodeChar;
		};

		static ch32 fs_ToUnicode(ch32 _Char);

		static CTableEntry const ms_Table[];
	};


	template <ECharacterEncoding _Encoding>
	CStr fg_DecodeCharacterEncoding(ch8 const *_pStr, CAnsiStr const *_pCStr = nullptr);

	template <ECharacterEncoding _Encoding>
	CStr fg_DecodeCharacterEncoding(CAnsiStr const &_CStr);

	template <ECharacterEncoding _Encoding>
	CStrNonTracked fg_DecodeCharacterEncodingNonTracked(ch8 const *_pStr, CAnsiStrNonTracked const *_pCStr = nullptr);

	template <ECharacterEncoding _Encoding>
	CStrNonTracked fg_DecodeCharacterEncodingNonTracked(CAnsiStrNonTracked const &_CStr);
}

#include "Malterlib_String_AnsiConversion.hpp"
