// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr2
{
#if 0
	// Done
	fg_StrIsAnsi
	fg_StrFindChar
	fg_StrFindChars
	fg_StrFind
	fg_StrLen
	fg_StrCmp
	fg_StrIsEmpty
	fg_StrMatchWildcard
	fg_StrStartsWith
	fg_StrEndsWith
	fg_StrHashDJB2
	fg_StrHashSDBM

	fg_StrCopy
	fg_StrMove

	// Mutable

		// Only copy
		fg_StrReplace
		fg_StrEscapeStr
		fg_StrEscapeStrNoQuotes
		fg_StrUpperCase
		fg_StrLowerCase
		fg_StrCapitalize

		// Needs copy unless replace from asci -> asci
		fg_StrReplaceChar

		// Needs copy variant
		fg_StrReverse
		fg_StrTrimLeft
		fg_StrTrimRight
		fg_StrTrim

			// Container + Index = range variant
			fg_StrInsert
			fg_StrDelete
			fg_StrLeft
			fg_StrExtract
			fg_StrRight

		// Other
		fg_StrClear
		fg_StrSetAt

	// Character
	fg_CharUpperCase
	fg_CharLowerCase
	fg_CharIsWhiteSpace
	fg_CharIsAlphabetical
	fg_CharIsAnsiAlphabetical
	fg_CharIsNumber

#endif
}
