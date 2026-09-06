// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/String/String>
#include <Mib/String/Appender>
#include <Mib/File/File>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;
	using namespace NMib::NContainer;
	using namespace NMib::NFile;

	struct CUnicodeBOM_Tests : NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("General")
			{
				DMibTestCategory("Iteration")
				{
					CStr Text("\xEF\xBB\xBF" "\xEF\xBF\xBE" "A");
					CStrIteratorUTF8 UTF8(Text);

					DMibExpect(*UTF8, ==, ch32(0xFEFF));
					DMibExpect(UTF8.f_GetLastWholeCodePointPos(), ==, 3);
					++UTF8;
					DMibExpect(*UTF8, ==, ch32(0xFFFE));
					++UTF8;
					DMibExpect(*UTF8, ==, ch32('A'));

					ch16 Units[] = {ch16(0xFEFF), ch16(0xFFFE), ch16('A')};
					CStrIteratorUTF16 UTF16(Units, fg_ArraySize(Units));

					DMibExpect(*UTF16, ==, ch32(0xFEFF));
					++UTF16;
					DMibExpect(*UTF16, ==, ch32(0xFFFE));
					++UTF16;
					DMibExpect(*UTF16, ==, ch32('A'));

					CStrIteratorUTF16 Noncharacter(Units + 1, 1);
					DMibExpect(*Noncharacter, ==, ch32(0xFFFE));
				};

				DMibTestCategory("BoundedInput")
				{
					ch8 Bytes[] = {ch8(0xEF), ch8(0xBB), ch8(0xBF), 'A', ch8(0x80), ch8(0x80), ch8(0x80)};
					for (umint Len : {0, 1, 2, 3})
					{
						DMibTestPath(CStr("Length{}"_f << Len));
						CStrIteratorUTF8 Iterator(Bytes, Len);

						DMibExpect(Iterator.f_IsWholeCodePoint(), ==, Len == 0 || Len == 3);
						DMibExpect(Iterator.f_GetLastWholeCodePointPos(), <=, Len);
						if (Len == 3)
							DMibExpect(*Iterator, ==, ch32(0xFEFF));
					}

					DMibExpectTrue(fg_IsValidUTF8(Bytes, 3));
					DMibExpectTrue(fg_IsValidUTF8(Bytes, 4));
					DMibExpectFalse(fg_IsValidUTF8(Bytes, 5));
					DMibExpectTrue(fg_IsValidUTF8(Bytes, 3, EValidateUTF8Flag::mc_DisallowNonCharacters));
					DMibExpectFalse(fg_IsValidUTF8(CStr("\xEF\xBF\xBE"), EValidateUTF8Flag::mc_DisallowNonCharacters));

					ch16 Unit = ch16(0xFFFE);
					CStrIteratorUTF16 Empty(&Unit, 0);
					DMibExpect(*Empty, ==, ch32(0));
				};

				DMibTestCategory("ConversionAndFormatting")
				{
					CStr Text("\xEF\xBB\xBF" "a" "\xEF\xBF\xBE" "b");
					CUStr Expected;
					for (auto Char : {ch32(0xFEFF), ch32('a'), ch32(0xFFFE), ch32('b')})
						Expected.f_AddChar(Char);

					CWStr Wide(Text);
					CUStr Unicode(Text);
					CUStr Assigned;
					Assigned = Text;
					CUStr Appended("prefix");
					Appended += Text;
					CUStr Formatted(CUStr::CFormat(str_utf32("{}")) << Text);
					CUStr Builder("prefix");
					{
						TCStringAppender<CUStr> Appender(Builder);
						Appender += Text;
					}

					DMibExpect(Unicode, ==, Expected);
					DMibExpect(Assigned, ==, Expected);
					DMibExpect(CStr(Wide), ==, Text);
					DMibExpect(CUStr(Wide), ==, Expected);
					DMibExpect(Appended, ==, CUStr("prefix") + Expected);
					DMibExpect(Formatted, ==, Expected);
					DMibExpect(Builder, ==, CUStr("prefix") + Expected);
					DMibExpect(fg_CleanUTF8(Text), ==, Text);
				};

				DMibTestCategory("FileDecoding")
				{
					uint8 UTF8[] = {0xEF, 0xBB, 0xBF, 0xEF, 0xBB, 0xBF, 0xEF, 0xBF, 0xBE, 'A'};
					uint8 UTF16LE[] = {0xFF, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 'A', 0};
					uint8 UTF16BE[] = {0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFE, 0, 'A'};
					uint8 UTF32LE[] = {0xFF, 0xFE, 0, 0, 0xFF, 0xFE, 0, 0, 0xFE, 0xFF, 0, 0, 'A', 0, 0, 0};
					uint8 UTF32BE[] = {0, 0, 0xFE, 0xFF, 0, 0, 0xFE, 0xFF, 0, 0, 0xFF, 0xFE, 0, 0, 0, 'A'};
					auto fCheck = [&](CStr const &_Name, auto const &_Bytes)
						{
							DMibTestPath(_Name);
							CByteVector Data;
							Data.f_Insert(_Bytes, fg_ArraySize(_Bytes));
							auto Text = CFile::fs_ReadStringFromVector(Data, true);

							DMibExpect(Text, ==, CStr("\xEF\xBB\xBF" "\xEF\xBF\xBE" "A"));
						}
					;

					fCheck("UTF8", UTF8);
					fCheck("UTF16LE", UTF16LE);
					fCheck("UTF16BE", UTF16BE);
					fCheck("UTF32LE", UTF32LE);
					fCheck("UTF32BE", UTF32BE);
				};
			};
		}
	};
}

DMibTestRegister(CUnicodeBOM_Tests, Malterlib::String);
