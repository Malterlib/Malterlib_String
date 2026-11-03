// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <ECharacterEncoding tf_Encoding>
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
				DestChar = TCCharEncodingConverter<tf_Encoding>::fs_ToUnicode(ToTest);
				Return.f_AddChar(DestChar);
				++pParse;
			}
			return Return;
		}
	}

	template <ECharacterEncoding tf_Encoding>
	CStr fg_DecodeCharacterEncoding(CAnsiStr const &_CStr)
	{
		return fg_DecodeCharacterEncoding<tf_Encoding>(_CStr, &_CStr);
	}

	template <ECharacterEncoding tf_Encoding>
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
				DestChar = TCCharEncodingConverter<tf_Encoding>::fs_ToUnicode(ToTest);
				Return.f_AddChar(DestChar);
				++pParse;
			}

			return Return;
		}
	}

	template <ECharacterEncoding tf_Encoding>
	CStrNonTracked fg_DecodeCharacterEncodingNonTracked(CAnsiStrNonTracked const &_CStr)
	{
		return fg_DecodeCharacterEncodingNonTracked<tf_Encoding>(_CStr, &_CStr);
	}
}
