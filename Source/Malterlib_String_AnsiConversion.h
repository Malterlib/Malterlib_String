// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	using CCharacterEncodingUnderlying = int32;
	enum ECharacterEncoding : int32
	{
		ECharacterEncoding_Unicode,
		ECharacterEncoding_UTF8,
		ECharacterEncoding_UTF16,
		ECharacterEncoding_Windows_1252,
	};

	template <CCharacterEncodingUnderlying t_CharacterEncoding>
	class TCCharEncodingConverter
	{
		public:
	};

	template <>
	class TCCharEncodingConverter<ECharacterEncoding_Windows_1252>
	{
		public:

		class CTableEntry
		{
			public:
			ch16 m_UnicodeChar;
		};
		static CTableEntry ms_Table[];

		static ch32 fs_ToUnicode(ch32 _Char)
		{
			NTraits::TCUnsigned<ch32> Temp = _Char;
			if (Temp <= 0xff)
			{
				return NTraits::TCUnsigned<ch32>(NTraits::TCUnsigned<ch16>(ms_Table[_Char].m_UnicodeChar));
			}
			return 0x0020;
		}
	};


	template <CCharacterEncodingUnderlying _Encoding>
	CStr fg_DecodeCharacterEncoding(const ch8 *_pStr, const CAnsiStr *_pCStr = nullptr)
	{
		const uch8 *pStr = (const uch8 *)_pStr;
		if (1)
		{
			CUStr Return;
			const uch8 *pParse = pStr;
			while (*pParse)
			{
				ch32 DestChar = 0;
				uch8 ToTest = *pParse;
				DestChar = TCCharEncodingConverter<_Encoding>::fs_ToUnicode(ToTest);
				Return.f_AddChar(DestChar);
				++pParse;
			}
			return Return;
		}
	}

	template <CCharacterEncodingUnderlying _Encoding>
	CStr fg_DecodeCharacterEncoding(const CAnsiStr &_CStr)
	{
		return fg_DecodeCharacterEncoding<_Encoding>(_CStr, &_CStr);
	}

	template <CCharacterEncodingUnderlying _Encoding>
	CStrNonTracked fg_DecodeCharacterEncodingNonTracked(const ch8 *_pStr, const CAnsiStrNonTracked *_pCStr = nullptr)
	{
		const uch8 *pStr = (const uch8 *)_pStr;
		if (1)
		{
			CUStrNonTracked Return;
			const uch8 *pParse = pStr;
			while (*pParse)
			{
				ch32 DestChar = 0;
				uch8 ToTest = *pParse;
				DestChar = TCCharEncodingConverter<_Encoding>::fs_ToUnicode(ToTest);
				Return.f_AddChar(DestChar);
				++pParse;
			}
			return Return;
		}
	}

	template <CCharacterEncodingUnderlying _Encoding>
	CStrNonTracked fg_DecodeCharacterEncodingNonTracked(const CAnsiStrNonTracked &_CStr)
	{
		return fg_DecodeCharacterEncodingNonTracked<_Encoding>(_CStr, &_CStr);
	}

}
