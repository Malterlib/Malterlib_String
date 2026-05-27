// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/String/String>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;

	struct CCompare_Tests : public NMib::NTest::CTest
	{
		void fp_UnsignedOrderingTests()
		{
			// ch8 is a signed character type on most platforms, so a byte with
			// the high bit set reads back as negative. fg_StrCmp must still
			// order bytes as unsigned values, otherwise non-ASCII (UTF-8) text
			// sorts incorrectly. This is a regression guard for the signed-byte
			// comparison bug.
			ch8 const High[] = {(ch8)0xff, 0};
			ch8 const HighCopy[] = {(ch8)0xff, 0};
			ch8 const Low[] = {(ch8)0x01, 0};

			DMibTestCategory("UnsignedOrdering")
			{
				{
					DMibTestPath("HighByteGreaterThanLow");
					DMibExpect(fg_StrCmp(High, Low), >, 0);
				}
				{
					DMibTestPath("LowByteLessThanHigh");
					DMibExpect(fg_StrCmp(Low, High), <, 0);
				}
				{
					DMibTestPath("HighByteEqual");
					DMibExpect(fg_StrCmp(High, HighCopy), ==, 0);
				}
			};
		}

		void fp_Utf8OrderingTests()
		{
			DMibTestCategory("Utf8Ordering")
			{
				// "é" (U+00E9) encodes as the bytes 0xC3 0xA9 in UTF-8. Its
				// leading byte is greater than 'A' (0x41) as an unsigned value,
				// so the accented string must sort after the ASCII one.
				ch8 const Accented[] = {(ch8)0xc3, (ch8)0xa9, 0};
				ch8 const Ascii[] = {(ch8)0x41, 0};

				{
					DMibTestPath("AccentedAfterAscii");
					DMibExpect(fg_StrCmp(Accented, Ascii), >, 0);
				}
				{
					DMibTestPath("AsciiBeforeAccented");
					DMibExpect(fg_StrCmp(Ascii, Accented), <, 0);
				}
			};
		}

		void f_DoTests()
		{
			DMibTestSuite("Compare")
			{
				fp_UnsignedOrderingTests();
				fp_Utf8OrderingTests();
			};
		}
	};

	DMibTestRegister(CCompare_Tests, Malterlib::String::Algorithm::Compare);
}
