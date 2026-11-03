// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>

namespace
{
	struct CGeneral_Tests : public NMib::NTest::CTest
	{
		int m_Test;

		void f_DoTests()
		{
			using namespace NMib::NStr;
			DMibTestSuite("String")
			{
				{
					DMibTestPath("Simple");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{}...{}...{}") >> String1 >> String2 >> String3).f_Parse("Test1...Test2...Test3", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "Test2");
					DMibExpect(String3, ==, "Test3");
				}
				{
					DMibTestPath("FindWhole");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{}...{}...{}") >> String1 >> String2 >> String3).f_Parse("Test1..-...Test2...Test3...", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1..-");
					DMibExpect(String2, ==, "Test2");
					DMibExpect(String3, ==, "Test3...");
				}
				{
					DMibTestPath("MissingArguments");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{}...{}...{}") >> String1 >> String2 >> String3).f_Parse("Test1...Test2", nParsed);

					DMibExpect(nParsed, ==, 2);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "Test2");
					DMibExpect(String3, ==, "");
				}
				{
					DMibTestPath("EmptyLast");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{}...{}...{}") >> String1 >> String2 >> String3).f_Parse("Test1...Test2...", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "Test2");
					DMibExpect(String3, ==, "");
				}
				{
					DMibTestPath("EmptyAll");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{}...{}...{}") >> String1 >> String2 >> String3).f_Parse("......", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "");
					DMibExpect(String2, ==, "");
					DMibExpect(String3, ==, "");
				}
			};
			DMibTestSuite("Escaped String")
			{
				{
					DMibTestPath("Simple");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se}...{se}...{se}") >> String1 >> String2 >> String3).f_Parse("Test1...\"Test2\"...Test3", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "\"Test2\"");
					DMibExpect(String3, ==, "Test3");
				}
				{
					DMibTestPath("FindWhole");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se}...{se}...{se}") >> String1 >> String2 >> String3).f_Parse("Test1..-...\"Te\\\"st2\"...Test3...", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1..-");
					DMibExpect(String2, ==, "\"Te\\\"st2\"");
					DMibExpect(String3, ==, "Test3...");
				}
				{
					DMibTestPath("MissingArguments");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se}...{se}...{se}") >> String1 >> String2 >> String3).f_Parse("Test1...\"Test2\"", nParsed);

					DMibExpect(nParsed, ==, 2);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "\"Test2\"");
					DMibExpect(String3, ==, "");
				}
				{
					DMibTestPath("EmptyLast");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se}...{se}...{se}") >> String1 >> String2 >> String3).f_Parse("Test1...\"Test2...5\"...", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "\"Test2...5\"");
					DMibExpect(String3, ==, "");
				}
				{
					DMibTestPath("EmptyAll");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se}...{se}...{se}") >> String1 >> String2 >> String3).f_Parse("...\"\"...", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "");
					DMibExpect(String2, ==, "\"\"");
					DMibExpect(String3, ==, "");
				}
			};
			DMibTestSuite("Remove Escape")
			{
				{
					DMibTestPath("Simple");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se,sr}...{se,sr}...{se,sr}") >> String1 >> String2 >> String3).f_Parse("Test1...\"Test2\"...Test3", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "Test2");
					DMibExpect(String3, ==, "Test3");
				}
				{
					DMibTestPath("FindWhole");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se,sr}...{se,sr}...{se,sr}") >> String1 >> String2 >> String3).f_Parse("Test1..-...\"Te\\\"st2\"...Test3...", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1..-");
					DMibExpect(String2, ==, "Te\"st2");
					DMibExpect(String3, ==, "Test3...");
				}
				{
					DMibTestPath("MissingArguments");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se,sr}...{se,sr}...{se,sr}") >> String1 >> String2 >> String3).f_Parse("Test1...\"Test2\"", nParsed);

					DMibExpect(nParsed, ==, 2);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "Test2");
					DMibExpect(String3, ==, "");
				}
				{
					DMibTestPath("EmptyLast");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se,sr}...{se,sr}...{se,sr}") >> String1 >> String2 >> String3).f_Parse("Test1...\"Test2...5\"...", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "Test1");
					DMibExpect(String2, ==, "Test2...5");
					DMibExpect(String3, ==, "");
				}
				{
					DMibTestPath("EmptyAll");
					CStr String1;
					CStr String2;
					CStr String3;

					aint nParsed = 0;
					(CStr::CParse("{se,sr}...{se,sr}...{se,sr}") >> String1 >> String2 >> String3).f_Parse("...\"\"...", nParsed);

					DMibExpect(nParsed, ==, 3);
					DMibExpect(String1, ==, "");
					DMibExpect(String2, ==, "");
					DMibExpect(String3, ==, "");
				}
			};
			DMibTestSuite("Pointer Conversion")
			{
				{
					DMibTestPath("IntLengthLimited");
					ch8 const Buffer[] = {'1', '2', '3', '4'};
					CStrPtr String(Buffer, 2);

					DMibExpect(String.f_ToInt(-1), ==, 12);
				}
				{
					DMibTestPath("IntExactLengthLimited");
					ch8 const Buffer[] = {'1', '2', 'x'};
					CStrPtr String(Buffer, 2);

					DMibExpect(String.f_ToIntExact(-1), ==, 12);
				}
				{
					DMibTestPath("IntExactEmbeddedNullFails");
					ch8 const Buffer[] = {'1', '2', 0, 'x'};
					CStrPtr String(Buffer, 4);

					DMibExpect(String.f_ToIntExact(-1), ==, -1);
				}
				{
					DMibTestPath("FloatLengthLimited");
					ch8 const Buffer[] = {'1', '.', '2', '3', '4'};
					CStrPtr String(Buffer, 3);

					DMibExpect(String.f_ToFloat(fp32(-1.0)), ==, fp32(1.2));
				}
				{
					DMibTestPath("FloatExactLengthLimited");
					ch8 const Buffer[] = {'1', '.', '2', 'x'};
					CStrPtr String(Buffer, 3);

					DMibExpect(String.f_ToFloatExact(fp32(-1.0)), ==, fp32(1.2));
				}
				{
					DMibTestPath("FloatExactEmbeddedNullFails");
					ch8 const Buffer[] = {'1', '.', '2', 0, 'x'};
					CStrPtr String(Buffer, 5);

					DMibExpect(String.f_ToFloatExact(fp32(-1.0)), ==, fp32(-1.0));
				}
			};
			DMibTestSuite("Pointer Length Limited Algorithms")
			{
				{
					DMibTestPath("Compare");
					ch8 const LeftData[] = {'a', 'b', 'x'};
					ch8 const RightData[] = {'a', 'b', 'y'};
					CStrPtr Left(LeftData, 2);
					CStrPtr Right(RightData, 2);

					DMibExpect(Left == Right, ==, true);
					DMibExpect(Left.f_Cmp(Right), ==, 0);
					DMibExpect((Left <=> Right) == 0, ==, true);
				}
				{
					DMibTestPath("CompareEmbeddedNull");
					ch8 const LeftData[] = {'a', 0, 'b'};
					ch8 const RightData[] = {'a', 0, 'c'};
					CStrPtr Left(LeftData, 3);
					CStrPtr Right(RightData, 3);

					DMibExpect(Left.f_Cmp(Right), <, 0);
					DMibExpect(Left.f_CmpNoCase(Right), <, 0);
					DMibExpect(Left.f_Cmp(Right, 2), ==, 0);
					DMibExpect(Left.f_Cmp("a"), >, 0);
				}
				{
					DMibTestPath("Find");
					ch8 const NeedleData[] = {'b', 'c', 'x'};
					CStr Haystack("abcd");
					CStrPtr Needle(NeedleData, 2);

					DMibExpect(Haystack.f_Find(Needle), ==, 1);
					DMibExpect(Haystack.f_FindNoCase(Needle), ==, 1);
				}
				{
					DMibTestPath("FindHaystackEmbeddedNull");
					ch8 const HaystackData[] = {'a', 0, 'b', 'c'};
					CStrPtr Haystack(HaystackData, 4);

					DMibExpect(Haystack.f_FindChar('b'), ==, 2);
					DMibExpect(Haystack.f_FindCharNoCase('B'), ==, 2);
					DMibExpect(Haystack.f_Find("bc"), ==, 2);
					DMibExpect(Haystack.f_FindNoCase("BC"), ==, 2);
				}
				{
					DMibTestPath("FindNeedleEmbeddedNull");
					ch8 const HaystackData[] = {'a', 0, 'b', 'c'};
					ch8 const NeedleData[] = {0, 'b'};
					CStrPtr Haystack(HaystackData, 4);
					CStrPtr Needle(NeedleData, 2);

					DMibExpect(Haystack.f_Find(Needle), ==, 1);
					DMibExpect(Haystack.f_FindReverse(Needle), ==, 1);
					DMibExpect(Haystack.f_FindCharOffset(2, 'c'), ==, 3);
					DMibExpect(Haystack.f_FindCharNoCaseOffset(2, 'C'), ==, 3);
				}
				{
					DMibTestPath("StartsEndsWith");
					ch8 const PrefixData[] = {'a', 'b', 'x'};
					ch8 const SuffixData[] = {'c', 'd', 'x'};
					CStr Haystack("abcd");
					CStrPtr Prefix(PrefixData, 2);
					CStrPtr Suffix(SuffixData, 2);

					DMibExpect(Haystack.f_StartsWith(Prefix), ==, true);
					DMibExpect(Haystack.f_EndsWith(Suffix), ==, true);
				}
				{
					DMibTestPath("StartsEndsWithEmbeddedNull");
					ch8 const HaystackData[] = {'a', 0, 'b', 'c'};
					ch8 const PrefixData[] = {'a', 0, 'b'};
					ch8 const SuffixData[] = {0, 'b', 'c'};
					CStrPtr Haystack(HaystackData, 4);
					CStrPtr Prefix(PrefixData, 3);
					CStrPtr Suffix(SuffixData, 3);

					DMibExpect(Haystack.f_StartsWith(Prefix), ==, true);
					DMibExpect(Haystack.f_StartsWithNoCase(Prefix), ==, true);
					DMibExpect(Haystack.f_EndsWith(Suffix), ==, true);
					DMibExpect(Haystack.f_EndsWithNoCase(Suffix), ==, true);
				}
				{
					DMibTestPath("FindChars");
					ch8 const CharsData[] = {'x', 'd'};
					CStr Haystack("abcd");
					CStrPtr Chars(CharsData, 1);

					DMibExpect(Haystack.f_FindChars(Chars), ==, -1);
					DMibExpect(Haystack.f_FindCharsReverse(Chars), ==, -1);
				}
				{
					DMibTestPath("FindCharsHaystackEmbeddedNull");
					ch8 const HaystackData[] = {'a', 0, 'b', 'c'};
					CStrPtr Haystack(HaystackData, 4);

					DMibExpect(Haystack.f_FindChars("c"), ==, 3);
					DMibExpect(Haystack.f_FindCharsNoCase("C"), ==, 3);
					DMibExpect(Haystack.f_FindCharsReverse("b"), ==, 2);
					DMibExpect(Haystack.f_FindCharsReverseNoCase("B"), ==, 2);
				}
				{
					DMibTestPath("FindCharsNeedleEmbeddedNull");
					ch8 const HaystackData[] = {'a', 0, 'b', 'c'};
					ch8 const CharsData[] = {0, 'x'};
					CStrPtr Haystack(HaystackData, 4);
					CStrPtr Chars(CharsData, 1);

					DMibExpect(Haystack.f_FindChars(Chars), ==, 1);
					DMibExpect(Haystack.f_FindCharsReverse(Chars), ==, 1);
				}
				{
					DMibTestPath("Classifiers");
					ch8 const NumberData[] = {'1', '2', 'x'};
					ch8 const IdentifierData[] = {'a', '_', 'x', '!'};
					CStrPtr Number(NumberData, 2);
					CStrPtr Identifier(IdentifierData, 3);

					DMibExpect(Number.f_IsNumeric(), ==, true);
					DMibExpect(Identifier.f_IsIdentifierStatement(), ==, true);
				}
				{
					DMibTestPath("ClassifiersEmbeddedNull");
					ch8 const ValueData[] = {'a', 0, 'b'};
					CStrPtr Value(ValueData, 3);

					DMibExpect(Value.f_IsAlphaNumeric(), ==, false);
					DMibExpect(Value.f_IsAnsiAlphaNumeric(), ==, false);
					DMibExpect(Value.f_IsIdentifierStatement(), ==, false);
					DMibExpect(Value.f_IsAlphaNumericStatement(), ==, false);
				}
				{
					DMibTestPath("HashLargestAnsi");
					ch8 const ValueData[] = {'a', 'b', 'z'};
					CStrPtr Value(ValueData, 2);
					CStr Expected("ab");

					DMibExpect(Value.f_Hash(), ==, Expected.f_Hash());
					DMibExpect(Value.f_HashSDBM(), ==, Expected.f_HashSDBM());
					DMibExpect(Value.f_LargestChar(), ==, 'b');
					DMibExpect(Value.f_IsAnsi(), ==, true);
				}
				{
					DMibTestPath("HashLargestAnsiEmbeddedNull");
					ch8 const ValueData[] = {'a', 0, 'z'};
					ch8 const NonAnsiData[] = {'a', 0, ch8(0x80)};
					CStrPtr Value(ValueData, 3);
					CStr Expected(ValueData, 3);
					CStrPtr NonAnsi(NonAnsiData, 3);

					DMibExpect(Value.f_Hash(), ==, Expected.f_Hash());
					DMibExpect(Value.f_HashDJB2(), ==, Expected.f_HashDJB2());
					DMibExpect(Value.f_HashSDBM(), ==, Expected.f_HashSDBM());
					DMibExpect(Value.f_LargestChar(), ==, 'z');
					DMibExpect(NonAnsi.f_IsAnsi(), ==, false);
					DMibExpect(fg_StrIsAnsi(NonAnsiData, 3), ==, true);
				}
				{
					DMibTestPath("SplitEmbeddedNull");
					ch8 const ValueData[] = {'a', 0, '|', 'b'};
					CStrPtr Value(ValueData, 4);
					auto Parts = Value.f_Split("|");

					DMibExpect(Parts.f_GetLen(), ==, 2);
					DMibExpect(Parts[0].f_GetLen(), ==, 2);
					DMibExpect(Parts[0].f_FindChar(0), ==, 1);
					DMibExpect(Parts[1], ==, "b");
				}
				{
					DMibTestPath("SplitLineEmbeddedNull");
					ch8 const ValueData[] = {'a', 0, '\n', 'b'};
					CStrPtr Value(ValueData, 4);
					auto Parts = Value.f_SplitLine();

					DMibExpect(Parts.f_GetLen(), ==, 2);
					DMibExpect(Parts[0].f_GetLen(), ==, 2);
					DMibExpect(Parts[0].f_FindChar(0), ==, 1);
					DMibExpect(Parts[1], ==, "b");
				}
			};
		}
	};

	DMibTestRegister(CGeneral_Tests, Malterlib::String::Parse);
}
