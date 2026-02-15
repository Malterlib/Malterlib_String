// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <ECharacterEncoding _Encoding>
	CStr fg_DecodeCharacterEncoding(ch8 const *_pStr, CAnsiStr const *_pCStr)
	{
		uch8 const *pStr = (uch8 const *)_pStr;
		if (1)
		{
			CUStr Return;
			uch8 const *pParse = pStr;
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

	template <ECharacterEncoding _Encoding>
	CStr fg_DecodeCharacterEncoding(CAnsiStr const &_CStr)
	{
		return fg_DecodeCharacterEncoding<_Encoding>(_CStr, &_CStr);
	}

	template <ECharacterEncoding _Encoding>
	CStrNonTracked fg_DecodeCharacterEncodingNonTracked(ch8 const *_pStr, CAnsiStrNonTracked const *_pCStr)
	{
		uch8 const *pStr = (uch8 const *)_pStr;
		if (1)
		{
			CUStrNonTracked Return;

			uch8 const *pParse = pStr;
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

	template <ECharacterEncoding _Encoding>
	CStrNonTracked fg_DecodeCharacterEncodingNonTracked(CAnsiStrNonTracked const &_CStr)
	{
		return fg_DecodeCharacterEncodingNonTracked<_Encoding>(_CStr, &_CStr);
	}
}
