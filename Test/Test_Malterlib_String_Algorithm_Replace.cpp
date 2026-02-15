// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/String>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;

	struct CReplace_Tests : public NMib::NTest::CTest
	{
		void fp_ShrinkingTests()
		{
			// Tests for shrinking replacement (_LenReplace < _LenFind)
			// Uses forward pass optimization
			DMibTestSuite("Shrinking")
			{
				{
					DMibTestPath("SingleMatch");
					ch8 Buffer[14];  // "HelloXXXWorld" (13) + null
					fg_StrCopy(Buffer, "HelloXXXWorld");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XXX", 3, "Y", 1, 14);
					DMibExpect(CStr(Buffer), ==, "HelloYWorld");
				}
				{
					DMibTestPath("MultipleMatches");
					ch8 Buffer[14];  // "aXXXbXXXcXXXd" (13) + null
					fg_StrCopy(Buffer, "aXXXbXXXcXXXd");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XXX", 3, "Y", 1, 14);
					DMibExpect(CStr(Buffer), ==, "aYbYcYd");
				}
				{
					DMibTestPath("AdjacentMatches");
					ch8 Buffer[7];  // "XXXXXX" (6) + null
					fg_StrCopy(Buffer, "XXXXXX");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XX", 2, "Y", 1, 7);
					DMibExpect(CStr(Buffer), ==, "YYY");
				}
				{
					DMibTestPath("MatchAtStart");
					ch8 Buffer[9];  // "XXXHello" (8) + null
					fg_StrCopy(Buffer, "XXXHello");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XXX", 3, "Y", 1, 9);
					DMibExpect(CStr(Buffer), ==, "YHello");
				}
				{
					DMibTestPath("MatchAtEnd");
					ch8 Buffer[9];  // "HelloXXX" (8) + null
					fg_StrCopy(Buffer, "HelloXXX");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XXX", 3, "Y", 1, 9);
					DMibExpect(CStr(Buffer), ==, "HelloY");
				}
				{
					DMibTestPath("NoMatch");
					ch8 Buffer[11];  // "HelloWorld" (10) + null
					fg_StrCopy(Buffer, "HelloWorld");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XXX", 3, "Y", 1, 11);
					DMibExpect(CStr(Buffer), ==, "HelloWorld");
				}
				{
					DMibTestPath("ReplaceToEmpty");
					ch8 Buffer[8];  // "aXXbXXc" (7) + null
					fg_StrCopy(Buffer, "aXXbXXc");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XX", 2, "", 0, 8);
					DMibExpect(CStr(Buffer), ==, "abc");
				}
			};
		}

		void fp_SameSizeTests()
		{
			// Tests for same-size replacement (_LenReplace == _LenFind)
			// Uses forward pass optimization
			DMibTestSuite("SameSize")
			{
				{
					DMibTestPath("SingleMatch");
					ch8 Buffer[14];  // "HelloXXXWorld" (13) + null
					fg_StrCopy(Buffer, "HelloXXXWorld");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XXX", 3, "YYY", 3, 14);
					DMibExpect(CStr(Buffer), ==, "HelloYYYWorld");
				}
				{
					DMibTestPath("MultipleMatches");
					ch8 Buffer[11];  // "aXXbXXcXXd" (10) + null
					fg_StrCopy(Buffer, "aXXbXXcXXd");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "XX", 2, "YY", 2, 11);
					DMibExpect(CStr(Buffer), ==, "aYYbYYcYYd");
				}
			};
		}

		void fp_GrowingTests()
		{
			// Tests for growing replacement (_LenReplace > _LenFind)
			// Uses backward pass optimization with fg_StrFindReverse
			DMibTestSuite("Growing")
			{
				{
					DMibTestPath("SingleMatch");
					ch8 Buffer[14];  // "HelloYYYWorld" (13) + null
					fg_StrCopy(Buffer, "HelloXWorld");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "X", 1, "YYY", 3, 14);
					DMibExpect(CStr(Buffer), ==, "HelloYYYWorld");
				}
				{
					DMibTestPath("MultipleMatches");
					ch8 Buffer[14];  // "aYYYbYYYcYYYd" (13) + null
					fg_StrCopy(Buffer, "aXbXcXd");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "X", 1, "YYY", 3, 14);
					DMibExpect(CStr(Buffer), ==, "aYYYbYYYcYYYd");
				}
				{
					DMibTestPath("MatchAtStart");
					ch8 Buffer[9];  // "YYYHello" (8) + null
					fg_StrCopy(Buffer, "XHello");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "X", 1, "YYY", 3, 9);
					DMibExpect(CStr(Buffer), ==, "YYYHello");
				}
				{
					DMibTestPath("MatchAtEnd");
					ch8 Buffer[9];  // "HelloYYY" (8) + null
					fg_StrCopy(Buffer, "HelloX");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "X", 1, "YYY", 3, 9);
					DMibExpect(CStr(Buffer), ==, "HelloYYY");
				}
				{
					DMibTestPath("AdjacentMatches");
					ch8 Buffer[7];  // "YYYYYY" (6) + null
					fg_StrCopy(Buffer, "XXX");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "X", 1, "YY", 2, 7);
					DMibExpect(CStr(Buffer), ==, "YYYYYY");
				}
				{
					DMibTestPath("NoMatch");
					ch8 Buffer[11];  // "HelloWorld" (10) + null
					fg_StrCopy(Buffer, "HelloWorld");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplace(Buffer, Len, "X", 1, "YYY", 3, 11);
					DMibExpect(CStr(Buffer), ==, "HelloWorld");
				}
			};
		}

		void fp_RoundtripTests()
		{
			// Tests that verify growing then shrinking then growing produces correct result
			DMibTestSuite("Roundtrip")
			{
				{
					DMibTestPath("GrowShrinkGrow");
					// "MegaFegaMegaFugaLugaLega" (24), "ega" appears 5 times
					// After "ega"->"Muhha": 24 + 5*2 = 34 chars
					ch8 Buffer[35];  // max size (34) + null
					fg_StrCopy(Buffer, "MegaFegaMegaFugaLugaLega");
					fg_StrReplace(Buffer, "ega", "Muhha", 35);  // Growing: 3 -> 5
					fg_StrReplace(Buffer, "Muhha", "11", 35);   // Shrinking: 5 -> 2
					fg_StrReplace(Buffer, "11", "ega", 35);     // Growing: 2 -> 3
					DMibExpect(CStr(Buffer), ==, "MegaFegaMegaFugaLugaLega");
				}
			};
		}

		void fp_NoCaseTests()
		{
			DMibTestSuite("NoCase")
			{
				{
					DMibTestPath("Shrinking");
					ch8 Buffer[14];  // "HelloXxXWorld" (13) + null
					fg_StrCopy(Buffer, "HelloXxXWorld");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplaceNoCase(Buffer, Len, "XXX", 3, "Y", 1, 14);
					DMibExpect(CStr(Buffer), ==, "HelloYWorld");
				}
				{
					DMibTestPath("SameSize");
					ch8 Buffer[14];  // "HelloXxXWorld" (13) + null
					fg_StrCopy(Buffer, "HelloXxXWorld");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplaceNoCase(Buffer, Len, "xxx", 3, "YYY", 3, 14);
					DMibExpect(CStr(Buffer), ==, "HelloYYYWorld");
				}
				{
					DMibTestPath("Growing");
					ch8 Buffer[14];  // "aYYYbYYYCYYYD" (13) + null
					fg_StrCopy(Buffer, "aXbxCxD");
					mint Len = fg_StrLen(Buffer);
					fg_StrReplaceNoCase(Buffer, Len, "X", 1, "YYY", 3, 14);
					DMibExpect(CStr(Buffer), ==, "aYYYbYYYCYYYD");
				}
			};
		}

		void fp_TruncationTests()
		{
			// Tests for _MaxLen truncation behavior
			// Buffer sizes are set to exactly what's needed for ASAN to catch overflows
			DMibTestSuite("Truncation")
			{
				// Growing case truncation (result exceeds _MaxLen)
				{
					DMibTestPath("Growing/TruncateResult");
					ch8 Buffer[10];  // _MaxLen = 10
					fg_StrCopy(Buffer, "aXbXcXd");  // Length 7, 3 X's
					mint Len = fg_StrLen(Buffer);
					// Replace X with YYY: result would be "aYYYbYYYcYYYd" (13 chars)
					// But _MaxLen = 10, so should truncate from right
					fg_StrReplace(Buffer, Len, "X", 1, "YYY", 3, 10);
					DMibExpect(CStr(Buffer), ==, "aYYYbYYYc");  // 9 chars + null
				}
				{
					DMibTestPath("Growing/TruncateInMiddleOfReplacement");
					ch8 Buffer[8];  // _MaxLen = 8
					fg_StrCopy(Buffer, "aXbXc");  // Length 5, 2 X's
					mint Len = fg_StrLen(Buffer);
					// Replace X with YYYY: result would be "aYYYYbYYYYc" (11 chars)
					// But _MaxLen = 8, should truncate
					fg_StrReplace(Buffer, Len, "X", 1, "YYYY", 4, 8);
					DMibExpect(CStr(Buffer), ==, "aYYYYbY");  // 7 chars + null
				}

				// Shrinking case with truncation
				{
					DMibTestPath("Shrinking/NormalFit");
					ch8 Buffer[10];  // "aXXXbXXXc" (9) + null
					fg_StrCopy(Buffer, "aXXXbXXXc");  // Length 9
					mint Len = fg_StrLen(Buffer);
					// Replace XXX with Y: result is "aYbYc" (5 chars)
					fg_StrReplace(Buffer, Len, "XXX", 3, "Y", 1, 10);
					DMibExpect(CStr(Buffer), ==, "aYbYc");
				}
				{
					DMibTestPath("Shrinking/TruncateResult");
					ch8 Buffer[14];  // "aXXXbXXXcXXXd" (13) + null
					fg_StrCopy(Buffer, "aXXXbXXXcXXXd");  // Length 13
					mint Len = fg_StrLen(Buffer);
					// Replace XXX with Y: full result would be "aYbYcYd" (7 chars)
					// But _MaxLen = 5, so truncate to "aYbY" (4 chars + null)
					fg_StrReplace(Buffer, Len, "XXX", 3, "Y", 1, 5);
					DMibExpect(CStr(Buffer), ==, "aYbY");
				}
				{
					DMibTestPath("Shrinking/TruncateInSegment");
					ch8 Buffer[16];  // "abcXXXdefXXXghi" (15) + null
					fg_StrCopy(Buffer, "abcXXXdefXXXghi");  // Length 15
					mint Len = fg_StrLen(Buffer);
					// Replace XXX with Y: full result would be "abcYdefYghi" (11 chars)
					// But _MaxLen = 7, truncate to "abcYde" (6 chars + null)
					fg_StrReplace(Buffer, Len, "XXX", 3, "Y", 1, 7);
					DMibExpect(CStr(Buffer), ==, "abcYde");
				}

				// Same-size case - output equals input size
				{
					DMibTestPath("SameSize/ExactFit");
					ch8 Buffer[8];  // "aXXbXXc" (7) + null
					fg_StrCopy(Buffer, "aXXbXXc");  // Length 7
					mint Len = fg_StrLen(Buffer);
					// Replace XX with YY: result is "aYYbYYc" (7 chars)
					fg_StrReplace(Buffer, Len, "XX", 2, "YY", 2, 8);
					DMibExpect(CStr(Buffer), ==, "aYYbYYc");
				}

				// Growing with exact fit
				{
					DMibTestPath("Growing/ExactFit");
					ch8 Buffer[6];  // _MaxLen = 6, result "aYYYb" (5) + null
					fg_StrCopy(Buffer, "aXb");  // Length 3
					mint Len = fg_StrLen(Buffer);
					// Replace X with YYY: result is "aYYYb" (5 chars)
					// _MaxLen = 6 allows exactly 5 chars + null
					fg_StrReplace(Buffer, Len, "X", 1, "YYY", 3, 6);
					DMibExpect(CStr(Buffer), ==, "aYYYb");
				}

				// Growing truncates entire last replacement
				{
					DMibTestPath("Growing/TruncateLastReplacement");
					ch8 Buffer[5];  // _MaxLen = 5, result "aYYY" (4) + null
					fg_StrCopy(Buffer, "aXbX");  // Length 4, 2 X's
					mint Len = fg_StrLen(Buffer);
					// Replace X with YYY: result would be "aYYYbYYY" (8 chars)
					// _MaxLen = 5, should get "aYYY" (4 chars + null)
					fg_StrReplace(Buffer, Len, "X", 1, "YYY", 3, 5);
					DMibExpect(CStr(Buffer), ==, "aYYY");
				}

				// Tests with _Len smaller than actual string length
				// _Len specifies total input length - we never read past it
				// Match exists after _Len boundary - should not be replaced, and rest of string is truncated
				{
					DMibTestPath("LenLimit/Shrinking/MatchAfterLen");
					ch8 Buffer[14];  // "aXXXbXXXcXXXd" (13) + null
					fg_StrCopy(Buffer, "aXXXbXXXcXXXd");  // Length 13, XXX at positions 1, 5, 9
					// Only process first 8 chars: "aXXXbXXX"
					// Result: "aYbY" (4 chars) - rest of string NOT preserved
					fg_StrReplace(Buffer, 8, "XXX", 3, "Y", 1, 14);
					DMibExpect(CStr(Buffer), ==, "aYbY");
				}
				{
					DMibTestPath("LenLimit/Shrinking/NoMatchInLen");
					ch8 Buffer[10];  // "abcXXXdef" (9) + null
					fg_StrCopy(Buffer, "abcXXXdef");  // Length 9, XXX at position 3
					// Only process first 3 chars: "abc", no XXX there
					// Result: "abc" (3 chars) - rest of string NOT preserved
					fg_StrReplace(Buffer, 3, "XXX", 3, "Y", 1, 10);
					DMibExpect(CStr(Buffer), ==, "abc");
				}
				{
					DMibTestPath("LenLimit/Growing/MatchAfterLen");
					ch8 Buffer[9];  // result "aYYYbYYY" (8) + null
					fg_StrCopy(Buffer, "aXbXcXd");  // Length 7, X at positions 1, 3, 5
					// Only process first 4 chars: "aXbX"
					// Replace X with YYY: "aYYYbYYY" (8 chars) - rest of string NOT preserved
					fg_StrReplace(Buffer, 4, "X", 1, "YYY", 3, 9);
					DMibExpect(CStr(Buffer), ==, "aYYYbYYY");
				}
				{
					DMibTestPath("LenLimit/Growing/NoMatchInLen");
					ch8 Buffer[8];  // "abcXdef" (7) + null
					fg_StrCopy(Buffer, "abcXdef");  // Length 7, X at position 3
					// Only process first 3 chars: "abc", no X there
					// Result: "abc" (3 chars) - rest of string NOT preserved
					fg_StrReplace(Buffer, 3, "X", 1, "YYY", 3, 8);
					DMibExpect(CStr(Buffer), ==, "abc");
				}
				{
					DMibTestPath("LenLimit/SameSize/MatchAfterLen");
					ch8 Buffer[11];  // "aXXbXXcXXd" (10) + null
					fg_StrCopy(Buffer, "aXXbXXcXXd");  // Length 10, XX at positions 1, 4, 7
					// Only process first 6 chars: "aXXbXX"
					// Replace XX with YY: "aYYbYY" (6 chars) - rest of string NOT preserved
					fg_StrReplace(Buffer, 6, "XX", 2, "YY", 2, 11);
					DMibExpect(CStr(Buffer), ==, "aYYbYY");
				}

				// Combined _Len and _MaxLen limiting
				{
					DMibTestPath("LenAndMaxLen/Shrinking/TruncateResult");
					ch8 Buffer[14];  // "aXXXbXXXcXXXd" (13) + null
					fg_StrCopy(Buffer, "aXXXbXXXcXXXd");  // Length 13, XXX at 1, 5, 9
					// _Len=8: process "aXXXbXXX", result "aYbY" (4 chars)
					// _MaxLen=3: truncate to "aY" (2 chars + null)
					fg_StrReplace(Buffer, 8, "XXX", 3, "Y", 1, 3);
					DMibExpect(CStr(Buffer), ==, "aY");
				}
				{
					DMibTestPath("LenAndMaxLen/Growing/TruncateResult");
					ch8 Buffer[8];  // _MaxLen = 8, result "aYYYbYY" (7) + null
					fg_StrCopy(Buffer, "aXbXcXd");  // Length 7, X at 1, 3, 5
					// _Len=4: process "aXbX", result "aYYYbYYY" (8 chars)
					// _MaxLen=8: truncate to "aYYYbYY" (7 chars + null)
					fg_StrReplace(Buffer, 4, "X", 1, "YYY", 3, 8);
					DMibExpect(CStr(Buffer), ==, "aYYYbYY");
				}
				{
					DMibTestPath("LenAndMaxLen/Growing/TruncateMore");
					ch8 Buffer[8];  // "aXbXcXd" (7) + null
					fg_StrCopy(Buffer, "aXbXcXd");  // Length 7, X at 1, 3, 5
					// _Len=4: process "aXbX", result "aYYYbYYY" (8 chars)
					// _MaxLen=5: truncate to "aYYY" (4 chars + null)
					fg_StrReplace(Buffer, 4, "X", 1, "YYY", 3, 5);
					DMibExpect(CStr(Buffer), ==, "aYYY");
				}
				{
					DMibTestPath("LenAndMaxLen/SameSize/TruncateResult");
					ch8 Buffer[13];  // "aXXbXXcXXdXX" (12) + null
					fg_StrCopy(Buffer, "aXXbXXcXXdXX");  // Length 12, XX at 1, 4, 7, 10
					// _Len=6: process "aXXbXX", result "aYYbYY" (6 chars)
					// _MaxLen=5: truncate to "aYYb" (4 chars + null)
					fg_StrReplace(Buffer, 6, "XX", 2, "YY", 2, 5);
					DMibExpect(CStr(Buffer), ==, "aYYb");
				}
			};
		}

		void fp_FindReverseTests()
		{
			// Tests for fg_StrFindReverse with _Len parameter
			// _Len specifies "search within first _Len characters" (positions 0 to _Len-1)
			DMibTestSuite("FindReverse")
			{
				// Basic tests without _Len parameter
				{
					DMibTestPath("Basic/SingleMatch");
					// "aXbXcXd" - X at positions 1, 3, 5
					// Should find the LAST occurrence (rightmost)
					aint Result = fg_StrFindReverse("aXbXcXd", "X");
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("Basic/NoMatch");
					aint Result = fg_StrFindReverse("abcdef", "X");
					DMibExpect(Result, ==, -1);
				}
				{
					DMibTestPath("Basic/MatchAtStart");
					aint Result = fg_StrFindReverse("Xabc", "X");
					DMibExpect(Result, ==, 0);
				}
				{
					DMibTestPath("Basic/MatchAtEnd");
					aint Result = fg_StrFindReverse("abcX", "X");
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("Basic/MultiCharPattern");
					// "aXXbXXcXXd" - XX at positions 1, 4, 7
					aint Result = fg_StrFindReverse("aXXbXXcXXd", "XX");
					DMibExpect(Result, ==, 7);
				}

				// Tests WITH _Len parameter
				// String "aXbXcXd" has length 7, X at positions 1, 3, 5
				// _Len means "search within first _Len characters"
				{
					DMibTestPath("WithLen/Len7");
					// _Len = 7: search positions 0-6, finds X at 5
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 7);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("WithLen/Len6");
					// _Len = 6: search positions 0-5, finds X at 5
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 6);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("WithLen/Len5");
					// _Len = 5: search positions 0-4, finds X at 3
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 5);
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("WithLen/Len4");
					// _Len = 4: search positions 0-3, finds X at 3
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 4);
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("WithLen/Len3");
					// _Len = 3: search positions 0-2, finds X at 1
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 3);
					DMibExpect(Result, ==, 1);
				}
				{
					DMibTestPath("WithLen/Len2");
					// _Len = 2: search positions 0-1, finds X at 1
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 2);
					DMibExpect(Result, ==, 1);
				}
				{
					DMibTestPath("WithLen/Len1");
					// _Len = 1: search position 0 only, no X there
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 1);
					DMibExpect(Result, ==, -1);
				}
				{
					DMibTestPath("WithLen/Len0");
					// _Len = 0: no search range, should return -1
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 0);
					DMibExpect(Result, ==, -1);
				}

				// Case-insensitive tests without _Len parameter
				{
					DMibTestPath("NoCase/Basic");
					// "aXbxCxD" - x/X at positions 1, 3, 5 (mixed case)
					aint Result = fg_StrFindReverseNoCase("aXbxCxD", "X");
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("NoCase/LowerPattern");
					aint Result = fg_StrFindReverseNoCase("aXbXcXd", "x");
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("NoCase/MixedCase");
					aint Result = fg_StrFindReverseNoCase("AbCdEf", "cd");
					DMibExpect(Result, ==, 2);
				}
				{
					DMibTestPath("NoCase/NoMatch");
					aint Result = fg_StrFindReverseNoCase("abcdef", "XY");
					DMibExpect(Result, ==, -1);
				}

				// Case-insensitive tests WITH _Len parameter
				// String "aXbxCxD" has length 7, x/X at positions 1, 3, 5
				{
					DMibTestPath("NoCaseWithLen/Len7");
					// _Len = 7: search positions 0-6, finds x at 5
					aint Result = fg_StrFindReverseNoCase("aXbxCxD", "x", 7);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("NoCaseWithLen/Len5");
					// _Len = 5: search positions 0-4, finds x at 3
					aint Result = fg_StrFindReverseNoCase("aXbxCxD", "x", 5);
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("NoCaseWithLen/Len3");
					// _Len = 3: search positions 0-2, finds X at 1
					aint Result = fg_StrFindReverseNoCase("aXbxCxD", "x", 3);
					DMibExpect(Result, ==, 1);
				}
				{
					DMibTestPath("NoCaseWithLen/Len1");
					// _Len = 1: search position 0 only, no x there
					aint Result = fg_StrFindReverseNoCase("aXbxCxD", "x", 1);
					DMibExpect(Result, ==, -1);
				}

				// Tests WITH both _Len and _FindLen parameters (new 4-parameter overload)
				// This tests the optimized path where both lengths are known
				{
					DMibTestPath("WithBothLens/Basic");
					// "aXbXcXd" len=7, "X" findLen=1
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 7, 1);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("WithBothLens/Len5");
					// _Len = 5: search positions 0-4, finds X at 3
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 5, 1);
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("WithBothLens/MultiCharPattern");
					// "aXXbXXcXXd" len=10, "XX" findLen=2
					aint Result = fg_StrFindReverse("aXXbXXcXXd", "XX", 10, 2);
					DMibExpect(Result, ==, 7);
				}
				{
					DMibTestPath("WithBothLens/MultiCharPatternLimited");
					// "aXXbXXcXXd" with _Len=6 should find XX at position 4
					aint Result = fg_StrFindReverse("aXXbXXcXXd", "XX", 6, 2);
					DMibExpect(Result, ==, 4);
				}
				{
					DMibTestPath("WithBothLens/NoMatch");
					aint Result = fg_StrFindReverse("abcdef", "XY", 6, 2);
					DMibExpect(Result, ==, -1);
				}
				{
					DMibTestPath("WithBothLens/ZeroLen");
					aint Result = fg_StrFindReverse("aXbXcXd", "X", 0, 1);
					DMibExpect(Result, ==, -1);
				}

				// Case-insensitive tests with both lengths
				{
					DMibTestPath("NoCaseWithBothLens/Basic");
					aint Result = fg_StrFindReverseNoCase("aXbxCxD", "x", 7, 1);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("NoCaseWithBothLens/MultiChar");
					aint Result = fg_StrFindReverseNoCase("aXxBxXcXxD", "Xx", 10, 2);
					DMibExpect(Result, ==, 7);
				}

				// Tests with CStr containers (verifies optimized path uses lengths)
				{
					DMibTestPath("CStr/Basic");
					CStr Haystack("aXbXcXd");
					CStr Needle("X");
					aint Result = fg_StrFindReverse(Haystack, Needle);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("CStr/MultiChar");
					CStr Haystack("aXXbXXcXXd");
					CStr Needle("XX");
					aint Result = fg_StrFindReverse(Haystack, Needle);
					DMibExpect(Result, ==, 7);
				}
				{
					DMibTestPath("CStr/WithMaxLen");
					CStr Haystack("aXbXcXd");
					CStr Needle("X");
					aint Result = fg_StrFindReverse(Haystack, Needle, 5);
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("CStr/NoCase");
					CStr Haystack("aXbxCxD");
					CStr Needle("x");
					aint Result = fg_StrFindReverseNoCase(Haystack, Needle);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("CStr/NoCaseWithMaxLen");
					CStr Haystack("aXbxCxD");
					CStr Needle("x");
					aint Result = fg_StrFindReverseNoCase(Haystack, Needle, 5);
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("CStr/MemberFunction");
					CStr Haystack("aXbXcXd");
					aint Result = Haystack.f_FindReverse("X");
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("CStr/MemberFunctionWithMaxLen");
					CStr Haystack("aXbXcXd");
					aint Result = Haystack.f_FindReverse("X", 5);
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("CStr/MemberFunctionCStr");
					CStr Haystack("aXXbXXcXXd");
					CStr Needle("XX");
					aint Result = Haystack.f_FindReverse(Needle);
					DMibExpect(Result, ==, 7);
				}

				// Test with pointer + CStr combination
				{
					DMibTestPath("Mixed/PtrHaystackCStrNeedle");
					CStr Needle("X");
					aint Result = fg_StrFindReverse("aXbXcXd", Needle);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("Mixed/CStrHaystackPtrNeedle");
					CStr Haystack("aXbXcXd");
					aint Result = fg_StrFindReverse(Haystack, "X");
					DMibExpect(Result, ==, 5);
				}

				// Tests for member functions with _FindLen parameter
				{
					DMibTestPath("MemberWithFindLen/Basic");
					CStr Haystack("aXbXcXd");
					aint Result = Haystack.f_FindReverse("X", 7, 1);
					DMibExpect(Result, ==, 5);
				}
				{
					DMibTestPath("MemberWithFindLen/Limited");
					CStr Haystack("aXbXcXd");
					aint Result = Haystack.f_FindReverse("X", 5, 1);
					DMibExpect(Result, ==, 3);
				}
				{
					DMibTestPath("MemberWithFindLen/MultiChar");
					CStr Haystack("aXXbXXcXXd");
					aint Result = Haystack.f_FindReverse("XX", 10, 2);
					DMibExpect(Result, ==, 7);
				}
				{
					DMibTestPath("MemberWithFindLen/NoCase");
					CStr Haystack("aXbxCxD");
					aint Result = Haystack.f_FindReverseNoCase("x", 7, 1);
					DMibExpect(Result, ==, 5);
				}

				// Tests for global functions with _FindLen parameter
				{
					DMibTestPath("GlobalWithFindLen/CStrHaystack");
					CStr Haystack("aXXbXXcXXd");
					aint Result = fg_StrFindReverse(Haystack, "XX", 10, 2);
					DMibExpect(Result, ==, 7);
				}
				{
					DMibTestPath("GlobalWithFindLen/CStrHaystackLimited");
					CStr Haystack("aXXbXXcXXd");
					aint Result = fg_StrFindReverse(Haystack, "XX", 6, 2);
					DMibExpect(Result, ==, 4);
				}
				{
					DMibTestPath("GlobalWithFindLen/NoCase");
					CStr Haystack("aXxBxXcXxD");
					aint Result = fg_StrFindReverseNoCase(Haystack, "Xx", 10, 2);
					DMibExpect(Result, ==, 7);
				}

				// Tests for container-to-container with _FindLen parameter
				{
					DMibTestPath("CStrToCStrWithFindLen/Basic");
					CStr Haystack("aXXbXXcXXd");
					CStr Needle("XX");
					aint Result = fg_StrFindReverse(Haystack, Needle, 10, 2);
					DMibExpect(Result, ==, 7);
				}
				{
					DMibTestPath("CStrToCStrWithFindLen/Limited");
					CStr Haystack("aXXbXXcXXd");
					CStr Needle("XX");
					aint Result = fg_StrFindReverse(Haystack, Needle, 6, 2);
					DMibExpect(Result, ==, 4);
				}
				{
					DMibTestPath("CStrToCStrWithFindLen/PartialNeedle");
					// Search for only first char of needle
					CStr Haystack("aXYbXYcXYd");
					CStr Needle("XY");
					aint Result = fg_StrFindReverse(Haystack, Needle, 10, 1);
					DMibExpect(Result, ==, 7);
				}
				{
					DMibTestPath("CStrToCStrWithFindLen/NoCase");
					CStr Haystack("aXxBxXcXxD");
					CStr Needle("Xx");
					aint Result = fg_StrFindReverseNoCase(Haystack, Needle, 10, 2);
					DMibExpect(Result, ==, 7);
				}
				{
					DMibTestPath("CStrToCStrWithFindLen/MemberFunction");
					CStr Haystack("aXXbXXcXXd");
					CStr Needle("XX");
					aint Result = Haystack.f_FindReverse(Needle, 10, 2);
					DMibExpect(Result, ==, 7);
				}
				{
					DMibTestPath("CStrToCStrWithFindLen/MemberFunctionNoCase");
					CStr Haystack("aXxBxXcXxD");
					CStr Needle("Xx");
					aint Result = Haystack.f_FindReverseNoCase(Needle, 10, 2);
					DMibExpect(Result, ==, 7);
				}

				// Tests where _FindLen is less than needle length (verifies limiting works)
				{
					DMibTestPath("LimitedFindLen/SingleCharFromMulti");
					// Needle is "XYZ" but we only search for "X" (findLen=1)
					// "aXbXYcXYZd" has X at 1, XY at 3, XYZ at 6
					// With findLen=1, should find last X at position 6
					aint Result = fg_StrFindReverse("aXbXYcXYZd", "XYZ", 10, 1);
					DMibExpect(Result, ==, 6);
				}
				{
					DMibTestPath("LimitedFindLen/TwoCharsFromThree");
					// Needle is "XYZ" but we only search for "XY" (findLen=2)
					// "aXbXYcXYZd" has XY at 3 and 6
					// With findLen=2, should find last XY at position 6
					aint Result = fg_StrFindReverse("aXbXYcXYZd", "XYZ", 10, 2);
					DMibExpect(Result, ==, 6);
				}
				{
					DMibTestPath("LimitedFindLen/FullMatch");
					// Needle is "XYZ" with full length (findLen=3)
					// "aXbXYcXYZd" has XYZ at 6 only
					aint Result = fg_StrFindReverse("aXbXYcXYZd", "XYZ", 10, 3);
					DMibExpect(Result, ==, 6);
				}
				{
					DMibTestPath("LimitedFindLen/NoMatchWithFullLen");
					// "aXbXYcXYd" has XY but no XYZ
					// With full needle "XYZ", no match
					aint Result = fg_StrFindReverse("aXbXYcXYd", "XYZ", 9, 3);
					DMibExpect(Result, ==, -1);
				}
				{
					DMibTestPath("LimitedFindLen/MatchWithLimitedLen");
					// Same string, but with findLen=2, should find XY
					aint Result = fg_StrFindReverse("aXbXYcXYd", "XYZ", 9, 2);
					DMibExpect(Result, ==, 6);
				}
				{
					DMibTestPath("LimitedFindLen/CStrNeedleLimited");
					// Test with CStr needle and limited findLen
					CStr Needle("XYZ");
					aint Result = fg_StrFindReverse("aXbXYcXYd", Needle, 9, 2);
					DMibExpect(Result, ==, 6);
				}
				{
					DMibTestPath("LimitedFindLen/BothCStrLimited");
					// Test with both CStr and limited findLen
					CStr Haystack("aXbXYcXYZd");
					CStr Needle("XYZ");
					aint Result = fg_StrFindReverse(Haystack, Needle, 10, 2);
					DMibExpect(Result, ==, 6);
				}
				{
					DMibTestPath("LimitedFindLen/MemberFunctionLimited");
					CStr Haystack("aXbXYcXYd");
					aint Result = Haystack.f_FindReverse("XYZ", 9, 2);
					DMibExpect(Result, ==, 6);
				}
				{
					DMibTestPath("LimitedFindLen/NoCaseLimited");
					// Case-insensitive with limited findLen
					aint Result = fg_StrFindReverseNoCase("aXbXycXyZd", "xyz", 10, 2);
					DMibExpect(Result, ==, 6);
				}
				{
					DMibTestPath("LimitedFindLen/FindLenExceedsNeedle");
					// _FindLen greater than actual needle length - should be capped
					CStr Haystack("aXXbXXcXXd");
					CStr Needle("XX");
					// findLen=5 but needle is only 2, should still work (capped to 2)
					aint Result = fg_StrFindReverse(Haystack, Needle, 10, 5);
					DMibExpect(Result, ==, 7);
				}
			};
		}

		void fp_CStrReplaceTests()
		{
			// Tests for CStr::f_Replace which uses fg_StrReplaceWithCount internally
			// This exercises the t_bUseCount optimization path
			DMibTestSuite("CStr")
			{
				// Growing case - uses backward pass with pre-computed count
				{
					DMibTestPath("Growing/SingleMatch");
					DMibExpect(CStr("HelloXWorld").f_Replace("X", "YYY"), ==, "HelloYYYWorld");
				}
				{
					DMibTestPath("Growing/MultipleMatches");
					DMibExpect(CStr("aXbXcXd").f_Replace("X", "YYY"), ==, "aYYYbYYYcYYYd");
				}
				{
					DMibTestPath("Growing/AdjacentMatches");
					DMibExpect(CStr("XXX").f_Replace("X", "YY"), ==, "YYYYYY");
				}
				{
					DMibTestPath("Growing/MatchAtStart");
					DMibExpect(CStr("XHello").f_Replace("X", "YYY"), ==, "YYYHello");
				}
				{
					DMibTestPath("Growing/MatchAtEnd");
					DMibExpect(CStr("HelloX").f_Replace("X", "YYY"), ==, "HelloYYY");
				}
				{
					DMibTestPath("Growing/NoMatch");
					DMibExpect(CStr("HelloWorld").f_Replace("X", "YYY"), ==, "HelloWorld");
				}
				{
					DMibTestPath("Growing/ManyMatches");
					DMibExpect(CStr("aXbXcXdXeXfXgXhXiXj").f_Replace("X", "YYY"), ==, "aYYYbYYYcYYYdYYYeYYYfYYYgYYYhYYYiYYYj");
				}

				// Shrinking case - uses forward pass with pre-computed count for fast path optimization
				{
					DMibTestPath("Shrinking/SingleMatch");
					DMibExpect(CStr("HelloXXXWorld").f_Replace("XXX", "Y"), ==, "HelloYWorld");
				}
				{
					DMibTestPath("Shrinking/MultipleMatches");
					DMibExpect(CStr("aXXXbXXXcXXXd").f_Replace("XXX", "Y"), ==, "aYbYcYd");
				}
				{
					DMibTestPath("Shrinking/ReplaceToEmpty");
					DMibExpect(CStr("aXXbXXc").f_Replace("XX", ""), ==, "abc");
				}
				{
					DMibTestPath("Shrinking/NoMatch");
					DMibExpect(CStr("HelloWorld").f_Replace("XXX", "Y"), ==, "HelloWorld");
				}

				// Same size case
				{
					DMibTestPath("SameSize/SingleMatch");
					DMibExpect(CStr("HelloXXXWorld").f_Replace("XXX", "YYY"), ==, "HelloYYYWorld");
				}
				{
					DMibTestPath("SameSize/MultipleMatches");
					DMibExpect(CStr("aXXbXXcXXd").f_Replace("XX", "YY"), ==, "aYYbYYcYYd");
				}

				// Case-insensitive tests (uses fg_StrReplaceNoCaseWithCount)
				{
					DMibTestPath("NoCase/Growing");
					DMibExpect(CStr("aXbxCxD").f_ReplaceNoCase("X", "YYY"), ==, "aYYYbYYYCYYYD");
				}
				{
					DMibTestPath("NoCase/Shrinking");
					DMibExpect(CStr("HelloXxXWorld").f_ReplaceNoCase("XXX", "Y"), ==, "HelloYWorld");
				}
				{
					DMibTestPath("NoCase/SameSize");
					DMibExpect(CStr("HelloXxXWorld").f_ReplaceNoCase("xxx", "YYY"), ==, "HelloYYYWorld");
				}

				// Roundtrip test
				{
					DMibTestPath("Roundtrip/GrowShrinkGrow");
					DMibExpect(CStr("MegaFegaMegaFugaLugaLega").f_Replace("ega", "Muhha").f_Replace("Muhha", "11").f_Replace("11", "ega"), ==, "MegaFegaMegaFugaLugaLega");
				}
			};
		}

		void fp_MixedCharSizeTests()
		{
			// Tests for replacement with different character sizes using global fg_StrReplace
			// Verifies that fg_ObjectCopy is used correctly when sizes differ
			// Container methods enforce compatible types at compile time, so we use global functions
			DMibTestSuite("MixedCharSize")
			{
				// ch8 buffer with ch16 find/replace strings (shrinking - replace shorter than find)
				{
					DMibTestPath("ch8WithCh16/Shrinking");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "\\Device\\HarddiskVolume3/path");
					ch16 const *pFind = str_utf16("\\Device\\HarddiskVolume3");
					ch16 const *pReplace = str_utf16("C:");
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "C:/path");
				}
				{
					DMibTestPath("ch8WithCh16/SameSize");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "Hello World");
					ch16 const *pFind = str_utf16("World");
					ch16 const *pReplace = str_utf16("Earth");
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "Hello Earth");
				}
				{
					DMibTestPath("ch8WithCh16/MultipleMatches");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "aXXbXXcXXd");
					ch16 const *pFind = str_utf16("XX");
					ch16 const *pReplace = str_utf16("Y");
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "aYbYcYd");
				}
				{
					DMibTestPath("ch8WithCh16/NoMatch");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "HelloWorld");
					ch16 const *pFind = str_utf16("XXX");
					ch16 const *pReplace = str_utf16("Y");
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "HelloWorld");
				}
				{
					DMibTestPath("ch8WithCh16/ReplaceToEmpty");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "aXXbXXc");
					ch16 const *pFind = str_utf16("XX");
					ch16 const *pReplace = str_utf16("");
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "abc");
				}

				// ch8 buffer with ch16 find/replace strings (growing - replace longer than find)
				{
					DMibTestPath("ch8WithCh16/Growing");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "c:/path/to/file");
					ch16 const *pFind = str_utf16("c:");
					ch16 const *pReplace = str_utf16("\\Device\\HarddiskVolume3");
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "\\Device\\HarddiskVolume3/path/to/file");
				}
				{
					DMibTestPath("ch8WithCh16/GrowingMultiple");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "aXbXcXd");
					ch16 const *pFind = str_utf16("X");
					ch16 const *pReplace = str_utf16("YYY");
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "aYYYbYYYcYYYd");
				}

				// ch16 buffer with ch8 find/replace strings (shrinking)
				{
					DMibTestPath("ch16WithCh8/Shrinking");
					ch16 Buffer[256];
					fg_StrCopy(Buffer, str_utf16("\\Device\\HarddiskVolume3/path"));
					ch8 const *pFind = "\\Device\\HarddiskVolume3";
					ch8 const *pReplace = "C:";
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CWStr(Buffer), ==, str_utf16("C:/path"));
				}
				{
					DMibTestPath("ch16WithCh8/SameSize");
					ch16 Buffer[256];
					fg_StrCopy(Buffer, str_utf16("Hello World"));
					ch8 const *pFind = "World";
					ch8 const *pReplace = "Earth";
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CWStr(Buffer), ==, str_utf16("Hello Earth"));
				}
				{
					DMibTestPath("ch16WithCh8/MultipleMatches");
					ch16 Buffer[256];
					fg_StrCopy(Buffer, str_utf16("aXXbXXcXXd"));
					ch8 const *pFind = "XX";
					ch8 const *pReplace = "Y";
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CWStr(Buffer), ==, str_utf16("aYbYcYd"));
				}

				// ch16 buffer with ch8 find/replace strings (growing)
				{
					DMibTestPath("ch16WithCh8/Growing");
					ch16 Buffer[256];
					fg_StrCopy(Buffer, str_utf16("c:/path/to/file"));
					ch8 const *pFind = "c:";
					ch8 const *pReplace = "\\Device\\HarddiskVolume3";
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CWStr(Buffer), ==, str_utf16("\\Device\\HarddiskVolume3/path/to/file"));
				}
				{
					DMibTestPath("ch16WithCh8/GrowingMultiple");
					ch16 Buffer[256];
					fg_StrCopy(Buffer, str_utf16("aXbXcXd"));
					ch8 const *pFind = "X";
					ch8 const *pReplace = "YYY";
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CWStr(Buffer), ==, str_utf16("aYYYbYYYcYYYd"));
				}

				// Mixed find/replace character sizes (ch8 find with ch16 replace into ch8 buffer)
				{
					DMibTestPath("MixedFindReplace/ch8Find_ch16Replace");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "Hello X World");
					ch8 const *pFind = "X";
					ch16 const *pReplace = str_utf16("Beautiful");
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "Hello Beautiful World");
				}
				{
					DMibTestPath("MixedFindReplace/ch16Find_ch8Replace");
					ch8 Buffer[256];
					fg_StrCopy(Buffer, "Hello Beautiful World");
					ch16 const *pFind = str_utf16("Beautiful");
					ch8 const *pReplace = "X";
					fg_StrReplace<false>(Buffer, fg_StrLen(Buffer), pFind, fg_StrLen(pFind), pReplace, fg_StrLen(pReplace), 256);
					DMibExpect(CStr(Buffer), ==, "Hello X World");
				}
			};
		}

		void f_DoTests()
		{
			fp_FindReverseTests();
			fp_ShrinkingTests();
			fp_SameSizeTests();
			fp_GrowingTests();
			fp_RoundtripTests();
			fp_NoCaseTests();
			fp_TruncationTests();
			fp_CStrReplaceTests();
			fp_MixedCharSizeTests();
		}
	};

	DMibTestRegister(CReplace_Tests, Malterlib::String::Algorithm);
}
