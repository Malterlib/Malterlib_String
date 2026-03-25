// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData>
	constexpr inline_medium tf_CData fg_CharUpperCase(tf_CData _Character)
	{
		using CData = NTraits::TCUnsigned<tf_CData>;

		CData Char = (CData) _Character;

		if (Char >= 'a' && Char <= 'z')
			Char -= 0x20;

		// Latin-1 Supplement: only safe for ch16/ch32 where codepoints map 1:1.
		// For ch8 (UTF-8) these byte values are lead bytes, not codepoints.
		if constexpr (sizeof(tf_CData) > 1)
		{
			if (Char >= 0xe0 && Char <= 0xfe && Char != 0xf7)
				Char -= 0x20;
		}

		return (tf_CData)Char;
	}

	template <typename tf_CData>
	constexpr inline_medium tf_CData fg_CharLowerCase(tf_CData _Character)
	{
		using CData = NTraits::TCUnsigned<tf_CData>;

		CData Char = (CData) _Character;

		if (Char >= 'A' && Char <= 'Z')
			Char += 0x20;

		// Latin-1 Supplement: only safe for ch16/ch32 where codepoints map 1:1.
		// For ch8 (UTF-8) these byte values are lead bytes, not codepoints.
		if constexpr (sizeof(tf_CData) > 1)
		{
			if (Char >= 0xc0 && Char <= 0xde && Char != 0xd7)
				Char += 0x20;
		}

		return (tf_CData)Char;
	}

	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsWhiteSpace(tf_CData const _Character)
	{
		switch (_Character)
		{
		case 32 : return true;
		case 8 : return true;
		case 9 : return true;
		case 10 : return true;
		case 13 : return true;
		}
		return false;
	}

	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsNewLine(tf_CData const _Character)
	{
		switch (_Character)
		{
		case 10 : return true;
		case 13 : return true;
		}
		return false;
	}

	template<typename tf_CData>
	constexpr inline_medium bool fg_CharIsWhiteSpaceNoLines(tf_CData const _Character)
	{
		switch (_Character)
		{
		case 32 : return true;
		case 8 : return true;
		case 9 : return true;
		}
		return false;
	}

	template<typename tf_CData>
	constexpr inline_large bool fg_CharIsAlphabetical(tf_CData const _Character)
	{
		using CData = NTraits::TCUnsigned<tf_CData>;
		CData Char = (CData) _Character;

		if (Char >= 'A' && Char <= 'Z')
			return true;
		if (Char >= 'a' && Char <= 'z')
			return true;

		if (Char >= 0x80u)
			return true;

		return false;

	}

	template <typename tf_CData>
	constexpr inline_large bool fg_CharIsAnsiAlphabetical(tf_CData const _Character)
	{
		if (_Character >= 'A' && _Character <= 'Z')
			return true;
		if (_Character >= 'a' && _Character <= 'z')
			return true;

		return false;

	}

	template <typename tf_CData>
	constexpr inline_large bool fg_CharIsLowerCaseAnsiAlphabetical(tf_CData const _Character)
	{
		if (_Character >= 'a' && _Character <= 'z')
			return true;

		return false;

	}

	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsNumber(tf_CData const _Character)
	{
		if (_Character >= '0' && _Character <= '9')
			return true;

		return false;
	}

	constexpr inline_medium bool fg_CharIsCombining(ch32 const _Character)
	{
		// Combining Diacritical Marks (0300–036F), since version 1.0, with modifications in subsequent versions down to 4.1
		// Combining Diacritical Marks Extended (1AB0–1AFF), version 7.0
		// Combining Diacritical Marks Supplement (1DC0–1DFF), versions 4.1 to 5.2
		// Combining Diacritical Marks for Symbols (20D0–20FF), since version 1.0, with modifications in subsequent versions down to 5.1
		// Combining Half Marks (FE20–FE2F), versions 1.0, with modifications in subsequent versions down to 8.0

		if
		(
			(_Character >= 0x0300 && _Character <= 0x036F)
			|| (_Character >= 0x1AB0 && _Character <= 0x1AFF)
			|| (_Character >= 0x1DC0 && _Character <= 0x1DFF)
			|| (_Character >= 0x20D0 && _Character <= 0x20FF)
			|| (_Character >= 0xFE20 && _Character <= 0xFE2F)
		)
		{
			return true;
		}

		return false;
	}

	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsOctalNumber(tf_CData const _Character)
	{
		if (_Character >= '0' && _Character <= '7')
			return true;

		return false;
	}

	template <typename tf_CData>
	constexpr inline_medium bool fg_CharIsHexNumber(tf_CData const _Character)
	{
		if
		(
			(_Character >= '0' && _Character <= '9')
			|| (_Character >= 'a' && _Character <= 'f')
			|| (_Character >= 'A' && _Character <= 'F')
		)
		{
			return true;
		}

		return false;
	}
}
