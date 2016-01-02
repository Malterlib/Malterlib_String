// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>
#include <Mib/Storage/Tuple>
#include <Mib/String/AnsiConversion>

namespace NMib
{
	namespace NStr
	{

#ifdef DMibSupportExternTemplates
		template TCStr<CStrTraits_CStr>;
		template TCStr<CStrTraits_CWStr>;
		template TCStr<CStrTraits_CUStr>;
		template TCStrAggregate< CStrTraits_CStr>;
		template TCStrAggregate< CStrTraits_CWStr>;
		template TCStrAggregate< CStrTraits_CUStr>;

		template TCStr<CStrTraits_CStrNonTracked>;
		template TCStr<CStrTraits_CWStrNonTracked>;
		template TCStr<CStrTraits_CUStrNonTracked>;
		template TCStrAggregate<CStrTraits_CStr>;
		template TCStrAggregate<CStrTraits_CWStr>;
		template TCStrAggregate<CStrTraits_CUStr>;

		template TCStr<CStrTraits_CStrVMem>;
		template TCStr<CStrTraits_CWStrVMem>;
		template TCStr<CStrTraits_CUStrVMem>;
#endif

#ifdef DMibDebug
		CWStr g_DebugOutputTemp16;
		CStr g_DebugOutputTemp8;
#endif

		ch8 const g_NewLine[] = DMibNewLine;
		void fg_Debug_AccessNewLine()
		{
			NSys::fg_Compiler_MakeActive(0, &g_NewLine);
		}
		
		//template <>
		TCCharEncodingConverter<ECharacterEncoding_Windows_1252>::CTableEntry TCCharEncodingConverter<ECharacterEncoding_Windows_1252>::ms_Table[] = 
		{
			0x0000,	// nullptr
			0x0001,	// START OF HEADING
			0x0002,	// START OF TEXT
			0x0003,	// END OF TEXT
			0x0004,	// END OF TRANSMISSION
			0x0005,	// ENQUIRY
			0x0006,	// ACKNOWLEDGE
			0x0007,	// BELL
			0x0008,	// BACKSPACE
			0x0009,	// HORIZONTAL TABULATION
			0x000A,	// LINE FEED
			0x000B,	// VERTICAL TABULATION
			0x000C,	// FORM FEED
			0x000D,	// CARRIAGE RETURN
			0x000E,	// SHIFT OUT
			0x000F,	// SHIFT IN
			0x0010,	// DATA LINK ESCAPE
			0x0011,	// DEVICE CONTROL ONE
			0x0012,	// DEVICE CONTROL TWO
			0x0013,	// DEVICE CONTROL THREE
			0x0014,	// DEVICE CONTROL FOUR
			0x0015,	// NEGATIVE ACKNOWLEDGE
			0x0016,	// SYNCHRONOUS IDLE
			0x0017,	// END OF TRANSMISSION BLOCK
			0x0018,	// CANCEL
			0x0019,	// END OF MEDIUM
			0x001A,	// SUBSTITUTE
			0x001B,	// ESCAPE
			0x001C,	// FILE SEPARATOR
			0x001D,	// GROUP SEPARATOR
			0x001E,	// RECORD SEPARATOR
			0x001F,	// UNIT SEPARATOR
			0x0020,	// SPACE
			0x0021,	// EXCLAMATION MARK
			0x0022,	// QUOTATION MARK
			0x0023,	// NUMBER SIGN
			0x0024,	// DOLLAR SIGN
			0x0025,	// PERCENT SIGN
			0x0026,	// AMPERSAND
			0x0027,	// APOSTROPHE
			0x0028,	// LEFT PARENTHESIS
			0x0029,	// RIGHT PARENTHESIS
			0x002A,	// ASTERISK
			0x002B,	// PLUS SIGN
			0x002C,	// COMMA
			0x002D,	// HYPHEN-MINUS
			0x002E,	// FULL STOP
			0x002F,	// SOLIDUS
			0x0030,	// DIGIT ZERO
			0x0031,	// DIGIT ONE
			0x0032,	// DIGIT TWO
			0x0033,	// DIGIT THREE
			0x0034,	// DIGIT FOUR
			0x0035,	// DIGIT FIVE
			0x0036,	// DIGIT SIX
			0x0037,	// DIGIT SEVEN
			0x0038,	// DIGIT EIGHT
			0x0039,	// DIGIT NINE
			0x003A,	// COLON
			0x003B,	// SEMICOLON
			0x003C,	// LESS-THAN SIGN
			0x003D,	// EQUALS SIGN
			0x003E,	// GREATER-THAN SIGN
			0x003F,	// QUESTION MARK
			0x0040,	// COMMERCIAL AT
			0x0041,	// LATIN CAPITAL LETTER A
			0x0042,	// LATIN CAPITAL LETTER B
			0x0043,	// LATIN CAPITAL LETTER C
			0x0044,	// LATIN CAPITAL LETTER D
			0x0045,	// LATIN CAPITAL LETTER E
			0x0046,	// LATIN CAPITAL LETTER F
			0x0047,	// LATIN CAPITAL LETTER G
			0x0048,	// LATIN CAPITAL LETTER H
			0x0049,	// LATIN CAPITAL LETTER I
			0x004A,	// LATIN CAPITAL LETTER J
			0x004B,	// LATIN CAPITAL LETTER K
			0x004C,	// LATIN CAPITAL LETTER L
			0x004D,	// LATIN CAPITAL LETTER M
			0x004E,	// LATIN CAPITAL LETTER N
			0x004F,	// LATIN CAPITAL LETTER O
			0x0050,	// LATIN CAPITAL LETTER P
			0x0051,	// LATIN CAPITAL LETTER Q
			0x0052,	// LATIN CAPITAL LETTER R
			0x0053,	// LATIN CAPITAL LETTER S
			0x0054,	// LATIN CAPITAL LETTER T
			0x0055,	// LATIN CAPITAL LETTER U
			0x0056,	// LATIN CAPITAL LETTER V
			0x0057,	// LATIN CAPITAL LETTER W
			0x0058,	// LATIN CAPITAL LETTER X
			0x0059,	// LATIN CAPITAL LETTER Y
			0x005A,	// LATIN CAPITAL LETTER Z
			0x005B,	// LEFT SQUARE BRACKET
			0x005C,	// REVERSE SOLIDUS
			0x005D,	// RIGHT SQUARE BRACKET
			0x005E,	// CIRCUMFLEX ACCENT
			0x005F,	// LOW LINE
			0x0060,	// GRAVE ACCENT
			0x0061,	// LATIN SMALL LETTER A
			0x0062,	// LATIN SMALL LETTER B
			0x0063,	// LATIN SMALL LETTER C
			0x0064,	// LATIN SMALL LETTER D
			0x0065,	// LATIN SMALL LETTER E
			0x0066,	// LATIN SMALL LETTER F
			0x0067,	// LATIN SMALL LETTER G
			0x0068,	// LATIN SMALL LETTER H
			0x0069,	// LATIN SMALL LETTER I
			0x006A,	// LATIN SMALL LETTER J
			0x006B,	// LATIN SMALL LETTER K
			0x006C,	// LATIN SMALL LETTER L
			0x006D,	// LATIN SMALL LETTER M
			0x006E,	// LATIN SMALL LETTER N
			0x006F,	// LATIN SMALL LETTER O
			0x0070,	// LATIN SMALL LETTER P
			0x0071,	// LATIN SMALL LETTER Q
			0x0072,	// LATIN SMALL LETTER R
			0x0073,	// LATIN SMALL LETTER S
			0x0074,	// LATIN SMALL LETTER T
			0x0075,	// LATIN SMALL LETTER U
			0x0076,	// LATIN SMALL LETTER V
			0x0077,	// LATIN SMALL LETTER W
			0x0078,	// LATIN SMALL LETTER X
			0x0079,	// LATIN SMALL LETTER Y
			0x007A,	// LATIN SMALL LETTER Z
			0x007B,	// LEFT CURLY BRACKET
			0x007C,	// VERTICAL LINE
			0x007D,	// RIGHT CURLY BRACKET
			0x007E,	// TILDE
			0x007F,	// DELETE
			0x20AC,	// EURO SIGN
			0xFFFF,	// UNDEFINED
			0x201A,	// SINGLE LOW-9 QUOTATION MARK
			0x0192,	// LATIN SMALL LETTER F WITH HOOK
			0x201E,	// DOUBLE LOW-9 QUOTATION MARK
			0x2026,	// HORIZONTAL ELLIPSIS
			0x2020,	// DAGGER
			0x2021,	// DOUBLE DAGGER
			0x02C6,	// MODIFIER LETTER CIRCUMFLEX ACCENT
			0x2030,	// PER MILLE SIGN
			0x0160,	// LATIN CAPITAL LETTER S WITH CARON
			0x2039,	// SINGLE LEFT-POINTING ANGLE QUOTATION MARK
			0x0152,	// LATIN CAPITAL LIGATURE OE
			0xFFFF,	// UNDEFINED
			0x017D,	// LATIN CAPITAL LETTER Z WITH CARON
			0xFFFF,	// UNDEFINED
			0xFFFF,	// UNDEFINED
			0x2018,	// LEFT SINGLE QUOTATION MARK
			0x2019,	// RIGHT SINGLE QUOTATION MARK
			0x201C,	// LEFT DOUBLE QUOTATION MARK
			0x201D,	// RIGHT DOUBLE QUOTATION MARK
			0x2022,	// BULLET
			0x2013,	// EN DASH
			0x2014,	// EM DASH
			0x02DC,	// SMALL TILDE
			0x2122,	// TRADE MARK SIGN
			0x0161,	// LATIN SMALL LETTER S WITH CARON
			0x203A,	// SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
			0x0153,	// LATIN SMALL LIGATURE OE
			0xFFFF,	// UNDEFINED
			0x017E,	// LATIN SMALL LETTER Z WITH CARON
			0x0178,	// LATIN CAPITAL LETTER Y WITH DIAERESIS
			0x00A0,	// NO-BREAK SPACE
			0x00A1,	// INVERTED EXCLAMATION MARK
			0x00A2,	// CENT SIGN
			0x00A3,	// POUND SIGN
			0x00A4,	// CURRENCY SIGN
			0x00A5,	// YEN SIGN
			0x00A6,	// BROKEN BAR
			0x00A7,	// SECTION SIGN
			0x00A8,	// DIAERESIS
			0x00A9,	// COPYRIGHT SIGN
			0x00AA,	// FEMININE ORDINAL INDICATOR
			0x00AB,	// LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
			0x00AC,	// NOT SIGN
			0x00AD,	// SOFT HYPHEN
			0x00AE,	// REGISTERED SIGN
			0x00AF,	// MACRON
			0x00B0,	// DEGREE SIGN
			0x00B1,	// PLUS-MINUS SIGN
			0x00B2,	// SUPERSCRIPT TWO
			0x00B3,	// SUPERSCRIPT THREE
			0x00B4,	// ACUTE ACCENT
			0x00B5,	// MICRO SIGN
			0x00B6,	// PILCROW SIGN
			0x00B7,	// MIDDLE DOT
			0x00B8,	// CEDILLA
			0x00B9,	// SUPERSCRIPT ONE
			0x00BA,	// MASCULINE ORDINAL INDICATOR
			0x00BB,	// RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
			0x00BC,	// VULGAR FRACTION ONE QUARTER
			0x00BD,	// VULGAR FRACTION ONE HALF
			0x00BE,	// VULGAR FRACTION THREE QUARTERS
			0x00BF,	// INVERTED QUESTION MARK
			0x00C0,	// LATIN CAPITAL LETTER A WITH GRAVE
			0x00C1,	// LATIN CAPITAL LETTER A WITH ACUTE
			0x00C2,	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX
			0x00C3,	// LATIN CAPITAL LETTER A WITH TILDE
			0x00C4,	// LATIN CAPITAL LETTER A WITH DIAERESIS
			0x00C5,	// LATIN CAPITAL LETTER A WITH RING ABOVE
			0x00C6,	// LATIN CAPITAL LETTER AE
			0x00C7,	// LATIN CAPITAL LETTER C WITH CEDILLA
			0x00C8,	// LATIN CAPITAL LETTER E WITH GRAVE
			0x00C9,	// LATIN CAPITAL LETTER E WITH ACUTE
			0x00CA,	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX
			0x00CB,	// LATIN CAPITAL LETTER E WITH DIAERESIS
			0x00CC,	// LATIN CAPITAL LETTER I WITH GRAVE
			0x00CD,	// LATIN CAPITAL LETTER I WITH ACUTE
			0x00CE,	// LATIN CAPITAL LETTER I WITH CIRCUMFLEX
			0x00CF,	// LATIN CAPITAL LETTER I WITH DIAERESIS
			0x00D0,	// LATIN CAPITAL LETTER ETH
			0x00D1,	// LATIN CAPITAL LETTER N WITH TILDE
			0x00D2,	// LATIN CAPITAL LETTER O WITH GRAVE
			0x00D3,	// LATIN CAPITAL LETTER O WITH ACUTE
			0x00D4,	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX
			0x00D5,	// LATIN CAPITAL LETTER O WITH TILDE
			0x00D6,	// LATIN CAPITAL LETTER O WITH DIAERESIS
			0x00D7,	// MULTIPLICATION SIGN
			0x00D8,	// LATIN CAPITAL LETTER O WITH STROKE
			0x00D9,	// LATIN CAPITAL LETTER U WITH GRAVE
			0x00DA,	// LATIN CAPITAL LETTER U WITH ACUTE
			0x00DB,	// LATIN CAPITAL LETTER U WITH CIRCUMFLEX
			0x00DC,	// LATIN CAPITAL LETTER U WITH DIAERESIS
			0x00DD,	// LATIN CAPITAL LETTER Y WITH ACUTE
			0x00DE,	// LATIN CAPITAL LETTER THORN
			0x00DF,	// LATIN SMALL LETTER SHARP S
			0x00E0,	// LATIN SMALL LETTER A WITH GRAVE
			0x00E1,	// LATIN SMALL LETTER A WITH ACUTE
			0x00E2,	// LATIN SMALL LETTER A WITH CIRCUMFLEX
			0x00E3,	// LATIN SMALL LETTER A WITH TILDE
			0x00E4,	// LATIN SMALL LETTER A WITH DIAERESIS
			0x00E5,	// LATIN SMALL LETTER A WITH RING ABOVE
			0x00E6,	// LATIN SMALL LETTER AE
			0x00E7,	// LATIN SMALL LETTER C WITH CEDILLA
			0x00E8,	// LATIN SMALL LETTER E WITH GRAVE
			0x00E9,	// LATIN SMALL LETTER E WITH ACUTE
			0x00EA,	// LATIN SMALL LETTER E WITH CIRCUMFLEX
			0x00EB,	// LATIN SMALL LETTER E WITH DIAERESIS
			0x00EC,	// LATIN SMALL LETTER I WITH GRAVE
			0x00ED,	// LATIN SMALL LETTER I WITH ACUTE
			0x00EE,	// LATIN SMALL LETTER I WITH CIRCUMFLEX
			0x00EF,	// LATIN SMALL LETTER I WITH DIAERESIS
			0x00F0,	// LATIN SMALL LETTER ETH
			0x00F1,	// LATIN SMALL LETTER N WITH TILDE
			0x00F2,	// LATIN SMALL LETTER O WITH GRAVE
			0x00F3,	// LATIN SMALL LETTER O WITH ACUTE
			0x00F4,	// LATIN SMALL LETTER O WITH CIRCUMFLEX
			0x00F5,	// LATIN SMALL LETTER O WITH TILDE
			0x00F6,	// LATIN SMALL LETTER O WITH DIAERESIS
			0x00F7,	// DIVISION SIGN
			0x00F8,	// LATIN SMALL LETTER O WITH STROKE
			0x00F9,	// LATIN SMALL LETTER U WITH GRAVE
			0x00FA,	// LATIN SMALL LETTER U WITH ACUTE
			0x00FB,	// LATIN SMALL LETTER U WITH CIRCUMFLEX
			0x00FC,	// LATIN SMALL LETTER U WITH DIAERESIS
			0x00FD,	// LATIN SMALL LETTER Y WITH ACUTE
			0x00FE,	// LATIN SMALL LETTER THORN
			0x00FF	// LATIN SMALL LETTER Y WITH DIAERESIS		
		};

		ch8 g_lWhiteSpaceChars[] = {32, 8, 9, 10, 13, 0};

		CWStr fg_ForceStrUTF16(const CWStr &_Str)
		{
			return _Str;
		}
		CStr fg_ForceStrUTF8(const CStr &_Str)
		{
			return _Str;
		}
		CStr fg_ForceStrUTF8(const CWStr &_Str)
		{
			return _Str;
		}
		CStr fg_ForceStrUTF8(const CUStr &_Str)
		{
			return _Str;
		}

		bint fg_GetExpectedUTF8SequenceLength( uch8 _Char )
		{
			bint CalculatedLength = 7-fg_GetHighestBitSet((~uint32(_Char))&0xFF);
			return CalculatedLength < 7 ? CalculatedLength : -1;
		}

		bint fg_GetRequiredUTF8SequenceLength(ch32 _Codepoint)
		{

			if (_Codepoint > 0x3FFFFFF)
				return 6;
			else if (_Codepoint > 0x1FFFFF)
				return 5;
			else if (_Codepoint > 0xFFFF)
				return 4;
			else if (_Codepoint > 0x7FF)
				return 3;
			else if (_Codepoint > 0x7F)
				return 2;
			return 1;
		}

		bint fg_IsUTF16Surrogate(ch32 _Codepoint)
		{
			return (_Codepoint >= 0xD800) && (_Codepoint <= 0xDFFF);
		}

		bint fg_IsOverlongUTF8Sequence(ch32 _Codepoint, bint _Length)
		{
			return _Length > fg_GetRequiredUTF8SequenceLength(_Codepoint);
		}

		bint fg_IsInvalidCodepoint(ch32 _Codepoint)
		{
			if (_Codepoint > 0x10FFFF)
				return true;

			if (_Codepoint == 0xFFFE || _Codepoint == 0xFFFF)
				return true;

			// Treat internal non-character codepoints as invalid?
			if ((_Codepoint & 0xFFFF) == 0xFFFE || (_Codepoint & 0xFFFF) == 0xFFFF)
				return true;

			return false;
		}

		bint fg_IsValidSequence(ch32 _CodePoint, bint _Length)
		{
			if (fg_IsUTF16Surrogate(_CodePoint))
				return false;

			if (fg_IsInvalidCodepoint(_CodePoint))
				return false;

			if (fg_IsOverlongUTF8Sequence(_CodePoint, _Length))
				return false;

			return true;
		}

		template<typename tf_FProcess, typename tf_CString>
		bint fg_ProcessUTF8(tf_FProcess &&_fFunctor, tf_CString *_pStr)
		{
			// BOM
			if (_pStr[0] == 0xEF && _pStr[1] == 0xBB && _pStr[2] == 0xBF)
			{
				if (fg_Forward<tf_FProcess>(_fFunctor)(_pStr, 3, true))
					return false;
				_pStr += 3;
			}
			mint nOneByteCodepointsProcessed = 0;
			tf_CString *pOneByteCodepoints = nullptr;

			while (*_pStr)
			{
				uch8 ToTest = *_pStr;
				if (ToTest & 0x80)
				{
					if (nOneByteCodepointsProcessed)
					{
						if (fg_Forward<tf_FProcess>(_fFunctor)(pOneByteCodepoints, nOneByteCodepointsProcessed, true))
							return false;
						pOneByteCodepoints = nullptr;
						nOneByteCodepointsProcessed = 0;
					}

					if (ToTest & 0x40)
					{
						bint SequenceLengthExpected = fg_GetExpectedUTF8SequenceLength(ToTest);
						if (SequenceLengthExpected<2)
						{
							if (fg_Forward<tf_FProcess>(_fFunctor)(_pStr, 1, false))
								return false;
							++_pStr;
						}
						else
						{
							tf_CString *pSequenceStart = _pStr;
							bint SequenceLengthParsed = 1;
							++_pStr;

							ch32 CodePoint = ToTest & ((1 << (8-(SequenceLengthExpected+1))) - 1);
							while (SequenceLengthParsed < SequenceLengthExpected)
							{
								ToTest = *_pStr;
								if ((ToTest & 0xC0) == 0x80)
								{
									CodePoint = (CodePoint << 6) | (ToTest & 0x3F);
									++SequenceLengthParsed;
									++_pStr;
								}
								else
								{
									if (fg_Forward<tf_FProcess>(_fFunctor)(pSequenceStart, SequenceLengthParsed, false))
										return false;
									break;
								}
							}
							if (SequenceLengthParsed == SequenceLengthExpected)
							{
								bint bValidSequence = fg_IsValidSequence(CodePoint, SequenceLengthParsed);
								if (fg_Forward<tf_FProcess>(_fFunctor)(pSequenceStart, SequenceLengthParsed, bValidSequence))
									return false;
							}
						}
					}
					else
					{
						if (fg_Forward<tf_FProcess>(_fFunctor)(_pStr, 1, false))
							return false;
						++_pStr;
					}
				}
				else
				{
					if (!pOneByteCodepoints)
						pOneByteCodepoints = _pStr;
					++nOneByteCodepointsProcessed;
					++_pStr;
				}
			}

			if (nOneByteCodepointsProcessed)
			{
				if (fg_Forward<tf_FProcess>(_fFunctor)(pOneByteCodepoints, nOneByteCodepointsProcessed, true))
					return false;
			}

			return true;
		}

		bint fg_IsValidUTF8( CStr const &_Str)
		{
			return fg_ProcessUTF8
				(
				[&](uch8 const *, bint, bint _bValid) -> bint
			{
				return !_bValid;
			}
			, (uch8*)_Str.f_GetStr()
				)
				;
		}

		CStr fg_ReplaceCharactersUTF8(CStr const &_Str, uch8 _ReplacementChar)
		{
			CStr StringCopy = _Str;
			uch8* pStr = (uch8*)StringCopy.f_GetStrUniqueWritable();

			fg_ProcessUTF8
				(
				[&](uch8* pStr, mint _Length, bint _bValid) -> bint
			{
				if (!_bValid)
				{
					while (_Length)
					{
						*pStr = _ReplacementChar;
						++pStr;
						--_Length;
					}
				}
				return false;
			}
			, pStr
				)
				;
			return StringCopy;
		}

		CStr fg_ReplaceSequenceUTF8(CStr const &_Str, CStr const &_ReplacementChar)
		{
			CStr Replacement = _ReplacementChar;

			CStr Destination;
			aint Length = 0;
			Destination.f_CreateWritableBuffer(_Str.f_GetStrLen(), true);

			fg_ProcessUTF8
				(
					[&](uch8* _pStr, mint _Length, bint _bValid) -> bint
					{
						if (_bValid)
						{
							CStr::CAddStrAgrs Args(Length, _Length);
							Destination.fp_AddStrLengthAware(Args, (ch8 const *)_pStr);
						}
						else
						{
							CStr::CAddStrAgrs Args(Length, Replacement.f_GetLen());
							Destination.fp_AddStrLengthAware(Args, Replacement.f_GetStr());
						}
						return false;
					}	
					, (uch8*)_Str.f_GetStr()
				)
			;
			Destination.f_SetStrLen(Length);
			return Destination;
		}

		CStr fg_CleanUTF8(CStr const &_CStr)
		{
			if (fg_IsValidUTF8(_CStr))
				return _CStr;
			else
				return fg_ReplaceSequenceUTF8(_CStr);
		}
		
		bool CParseLocation::operator ==(CParseLocation const &_Right) const
		{
			return NContainer::fg_TupleReferences(m_File, m_Character, m_Line, m_Column) == NContainer::fg_TupleReferences(_Right.m_File, _Right.m_Character, _Right.m_Line, _Right.m_Column);
		}
		bool CParseError::operator ==(CParseError const &_Right) const
		{
			return NContainer::fg_TupleReferences(m_Error, m_Location) == NContainer::fg_TupleReferences(_Right.m_Error, _Right.m_Location);
		}
		
		void CParseLocation::f_Format(NStr::CStrAggregate &o_FormatInto) const
		{
			o_FormatInto
				+= NStr::CStr::CFormat(DMibPFileLineColumnFormat " Char {}") 
				<< m_File
				<< m_Line
				<< m_Column
				<< m_Character
			;
		}
		void CParseError::f_Format(NStr::CStrAggregate &o_FormatInto) const
		{
			o_FormatInto += CStr::CFormat("{} Error '{}'") << m_Location << m_Error;
		}
		
		
	}
}

