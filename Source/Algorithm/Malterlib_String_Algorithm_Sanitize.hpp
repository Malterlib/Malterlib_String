// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CStr>
	tf_CStr fg_StrSanitizeOneLine(tf_CStr const &_Str)
	{
		using CUnicodeStr = TCStr
			<
				typename TCStrTraits_ReplaceParams
				<
					ch32
					, EStrType_Unicode
					, tf_CStr::CTraits::CStrTraits::mc_Type
					, typename tf_CStr::CImp
					, typename tf_CStr::CTraits::CStrTraits::CParams
				>::CType
			>
		;

		if (_Str.f_IsEmpty())
			return CUnicodeStr();

		static_assert(tf_CStr::mc_Type == NStr::EStrType_UTF);

		auto iUTF = _Str.f_GetUnicodeIterator();
		CUnicodeStr Return;
		while (*iUTF)
		{
			switch (*iUTF)
			{
			case 0x000A: //	Line feed
			case 0x000B: //	Vertical Tab
			case 0x000C: //	Form feed
			case 0x000D: //	Carriage return
			case 0x0085: //	Next line
			case 0x2028: //	line separator
			case 0x2029: //	paragraph separator

			/* Regular whitespaces will be added as usual
			case 0x0009: // Horizontal Tab
			case 0x0020: //	Space
			case 0x00A0: //	no-break space
			case 0x1680: //	ogham space mark
			case 0x180E: //	mongolian vowel separator
			case 0x2000: //	en quad
			case 0x2001: //	em quad
			case 0x2002: //	en space
			case 0x2003: //	em space
			case 0x2004: //	three-per-em space
			case 0x2005: //	four-per-em space
			case 0x2006: //	six-per-em space
			case 0x2007: //	figure space
			case 0x2008: //	punctuation space
			case 0x2009: //	thin space
			case 0x200A: //	hair space
			case 0x202F: //	narrow no-break space
			case 0x205F: //	medium mathematical space
			case 0x3000: //	ideographic space
			*/
				Return.f_AddChar(0x0020);
				break;
			default:
				Return.f_AddChar(*iUTF);
				break;
			}

			++iUTF;
		}

		return Return;
	}
}
