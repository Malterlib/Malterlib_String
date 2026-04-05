// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Test/Exception>
#include <Mib/String/Mixed>

#ifdef DCompiler_MSVC
#	pragma warning(disable:4828)
#endif

#include "Test_Malterlib_String_Container2.h"

using namespace NMib::NStr;

#if DMibConfig_Tests_Enable

namespace NMib
{
	namespace NStr
	{


	}
}

CStr const &fg_GetTestStringInAnotherTranslationUnit();

namespace
{

	static uch8 const gc_AnsiTestStringSource[] = { 'a', 'b', 'c', 'd', 0xc6, 0xc5, 0xd6, 0xe6, 0xe5, 0xf6, 0 };

	char const* gc_AnsiTestString = (char const*)gc_AnsiTestStringSource;
	char const* gc_AnsiTestStringUTF = str_utf8("abcdÆÅÖæåö");

	struct CGlobalFunctions_Tests : public NMib::NTest::CTest
	{
	private:
		template <typename t_CStr>
		static void fsp_FindCharTestsTyped()
		{
			t_CStr AlphabetLowerStr("abcdefghijklmnopqrstuvwxyz");
			t_CStr AlphabetUpperStr("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
			t_CStr AlphabetMixedStr("aBcDeFgHiJkLmNoPqRsTuVwXyZ");

			t_CStr AlphabetX2LowerStr("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
			t_CStr AlphabetX2UpperStr("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ");
			t_CStr AlphabetX2MixedStr("aBcDeFgHiJkLmNoPqRsTuVwXyZaBcDeFgHiJkLmNoPqRsTuVwXyZ");

			DMibTest(DMibExpr(fg_StrFindChar(AlphabetX2LowerStr, 'a')) == DMibExpr(0));
			DMibTest(DMibExpr(fg_StrFindChar(AlphabetX2LowerStr, 'A')) == DMibExpr(-1));

			DMibTest(DMibExpr(fg_StrFindChar(AlphabetX2LowerStr, 'm')) == DMibExpr(12));
			DMibTest(DMibExpr(fg_StrFindChar(AlphabetX2LowerStr, 'M')) == DMibExpr(-1));

			DMibTest(DMibExpr(fg_StrFindChar(AlphabetX2LowerStr, 'z')) == DMibExpr(25));
			DMibTest(DMibExpr(fg_StrFindChar(AlphabetX2LowerStr, 'Z')) == DMibExpr(-1));

			DMibTest(DMibExpr(fg_StrFindCharNoCase(AlphabetX2LowerStr, 'a')) == DMibExpr(0));
			DMibTest(DMibExpr(fg_StrFindCharNoCase(AlphabetX2LowerStr, 'A')) == DMibExpr(0));
			DMibTest(DMibExpr(fg_StrFindCharNoCase(AlphabetX2UpperStr, 'a')) == DMibExpr(0));
			DMibTest(DMibExpr(fg_StrFindCharNoCase(AlphabetX2UpperStr, 'A')) == DMibExpr(0));

			DMibTest(DMibExpr(fg_StrFindCharNoCase(AlphabetX2LowerStr, 'z')) == DMibExpr(25));
			DMibTest(DMibExpr(fg_StrFindCharNoCase(AlphabetX2LowerStr, 'Z')) == DMibExpr(25));
			DMibTest(DMibExpr(fg_StrFindCharNoCase(AlphabetX2UpperStr, 'z')) == DMibExpr(25));
			DMibTest(DMibExpr(fg_StrFindCharNoCase(AlphabetX2UpperStr, 'Z')) == DMibExpr(25));

			DMibTest(DMibExpr(fg_StrFindCharReverse(AlphabetX2LowerStr, 'z')) == DMibExpr(51));
			DMibTest(DMibExpr(fg_StrFindCharReverse(AlphabetX2LowerStr, 'Z')) == DMibExpr(-1));
			DMibTest(DMibExpr(fg_StrFindCharReverse(AlphabetX2LowerStr, 'a')) == DMibExpr(26));
			DMibTest(DMibExpr(fg_StrFindCharReverse(AlphabetX2LowerStr, 'A')) == DMibExpr(-1));

			DMibTest(DMibExpr(fg_StrFindCharReverseNoCase(AlphabetX2LowerStr, 'z')) == DMibExpr(51));
			DMibTest(DMibExpr(fg_StrFindCharReverseNoCase(AlphabetX2LowerStr, 'Z')) == DMibExpr(51));
			DMibTest(DMibExpr(fg_StrFindCharReverseNoCase(AlphabetX2LowerStr, 'a')) == DMibExpr(26));
			DMibTest(DMibExpr(fg_StrFindCharReverseNoCase(AlphabetX2LowerStr, 'A')) == DMibExpr(26));

			DMibTest(DMibExpr(fg_StrFindCharReverse(AlphabetX2LowerStr, 'z', 26)) == DMibExpr(25));
			DMibTest(DMibExpr(fg_StrFindCharReverse(AlphabetX2LowerStr, 'Z', 26)) == DMibExpr(-1));
			DMibTest(DMibExpr(fg_StrFindCharReverse(AlphabetX2LowerStr, 'a', 26)) == DMibExpr(0));
			DMibTest(DMibExpr(fg_StrFindCharReverse(AlphabetX2LowerStr, 'A', 26)) == DMibExpr(-1));

			DMibTest(DMibExpr(fg_StrFindCharReverseNoCase(AlphabetX2LowerStr, 'z', 26)) == DMibExpr(25));
			DMibTest(DMibExpr(fg_StrFindCharReverseNoCase(AlphabetX2LowerStr, 'Z', 26)) == DMibExpr(25));
			DMibTest(DMibExpr(fg_StrFindCharReverseNoCase(AlphabetX2LowerStr, 'a', 26)) == DMibExpr(0));
			DMibTest(DMibExpr(fg_StrFindCharReverseNoCase(AlphabetX2LowerStr, 'A', 26)) == DMibExpr(0));
		}

		void fp_FindCharTests()
		{
			DMibTestSuite("FindChar")
			{
				{
					DMibTestPath("CMStrDeprecated");
					CGlobalFunctions_Tests::fsp_FindCharTestsTyped<CMStrDeprecated>();
				}
				{
					DMibTestPath("CStr");
					CGlobalFunctions_Tests::fsp_FindCharTestsTyped<CStr>();
				}
				{
					DMibTestPath("CWStr");
					CGlobalFunctions_Tests::fsp_FindCharTestsTyped<CWStr>();
				}
				{
					DMibTestPath("CUStr");
					CGlobalFunctions_Tests::fsp_FindCharTestsTyped<CUStr>();
				}
			};
		}

		template <typename tf_CStr>
		static void fsp_CaseTestsTyped()
		{
			tf_CStr StringLower_0_127(CStr(str_utf8("abcd")));
			tf_CStr StringLower_0_255(CStr(str_utf8("åäöabcd")));
			tf_CStr StringLower_0_65535(CStr(str_utf8("亜哀姐飴åäöabcd")));
			tf_CStr StringLower_0_10ffff(CStr(str_utf8("𠀀亜哀姐飴åäöabcd")));

			tf_CStr StringUpper_0_127(CStr(str_utf8("ABCD")));
			tf_CStr StringUpper_0_255(CStr(str_utf8("ÅÄÖABCD")));
			tf_CStr StringUpper_0_65535(CStr(str_utf8("亜哀姐飴ÅÄÖABCD")));
			tf_CStr StringUpper_0_10ffff(CStr(str_utf8("𠀀亜哀姐飴ÅÄÖABCD")));

			tf_CStr StringCapitalized_0_127(CStr(str_utf8("Abcd")));
			tf_CStr StringCapitalized_0_255(CStr(str_utf8("Åäöabcd")));
			tf_CStr StringCapitalized_0_65535(CStr(str_utf8("亜哀姐飴åäöabcd")));
			tf_CStr StringCapitalized_0_10ffff(CStr(str_utf8("𠀀亜哀姐飴åäöabcd")));

			auto fCapitalize = [](auto &_String)
				{
					tf_CStr String = _String;
					fg_StrCapitalize(String);
					return String;
				}
			;

			auto fLowerCaseMaxLen = [](auto &_String)
				{
					tf_CStr Output;
					umint Len = _String.f_GetLen();
					fg_StrLowerCase(Output.f_GetStr(Len + 1), Len + 1, _String.f_GetStr(), Len);
					return Output;
				}
			;

			auto fUpperCaseMaxLen = [](auto &_String)
				{
					tf_CStr Output;
					umint Len = _String.f_GetLen();
					fg_StrUpperCase(Output.f_GetStr(Len + 1), Len + 1, _String.f_GetStr(), Len);
					return Output;
				}
			;

			DMibExpect(StringLower_0_127.f_LowerCase(), ==, StringLower_0_127);
			DMibExpect(StringLower_0_255.f_LowerCase(), ==, StringLower_0_255);
			DMibExpect(StringLower_0_65535.f_LowerCase(), ==, StringLower_0_65535);
			DMibExpect(StringLower_0_10ffff.f_LowerCase(), ==, StringLower_0_10ffff);

			DMibExpect(StringUpper_0_127.f_LowerCase(), ==, StringLower_0_127);
			DMibExpect(StringUpper_0_255.f_LowerCase(), ==, StringLower_0_255);
			DMibExpect(StringUpper_0_65535.f_LowerCase(), ==, StringLower_0_65535);
			DMibExpect(StringUpper_0_10ffff.f_LowerCase(), ==, StringLower_0_10ffff);

			DMibExpect(StringCapitalized_0_127.f_LowerCase(), ==, StringLower_0_127);
			DMibExpect(StringCapitalized_0_255.f_LowerCase(), ==, StringLower_0_255);
			DMibExpect(StringCapitalized_0_65535.f_LowerCase(), ==, StringLower_0_65535);
			DMibExpect(StringCapitalized_0_10ffff.f_LowerCase(), ==, StringLower_0_10ffff);


			DMibExpect(fLowerCaseMaxLen(StringLower_0_127), ==, StringLower_0_127);
			DMibExpect(fLowerCaseMaxLen(StringLower_0_255), ==, StringLower_0_255);
			DMibExpect(fLowerCaseMaxLen(StringLower_0_65535), ==, StringLower_0_65535);
			DMibExpect(fLowerCaseMaxLen(StringLower_0_10ffff), ==, StringLower_0_10ffff);

			DMibExpect(fLowerCaseMaxLen(StringUpper_0_127), ==, StringLower_0_127);
			DMibExpect(fLowerCaseMaxLen(StringUpper_0_255), ==, StringLower_0_255);
			DMibExpect(fLowerCaseMaxLen(StringUpper_0_65535), ==, StringLower_0_65535);
			DMibExpect(fLowerCaseMaxLen(StringUpper_0_10ffff), ==, StringLower_0_10ffff);

			DMibExpect(fLowerCaseMaxLen(StringCapitalized_0_127), ==, StringLower_0_127);
			DMibExpect(fLowerCaseMaxLen(StringCapitalized_0_255), ==, StringLower_0_255);
			DMibExpect(fLowerCaseMaxLen(StringCapitalized_0_65535), ==, StringLower_0_65535);
			DMibExpect(fLowerCaseMaxLen(StringCapitalized_0_10ffff), ==, StringLower_0_10ffff);


			DMibExpect(StringLower_0_127.f_UpperCase(), ==, StringUpper_0_127);
			DMibExpect(StringLower_0_255.f_UpperCase(), ==, StringUpper_0_255);
			DMibExpect(StringLower_0_65535.f_UpperCase(), ==, StringUpper_0_65535);
			DMibExpect(StringLower_0_10ffff.f_UpperCase(), ==, StringUpper_0_10ffff);

			DMibExpect(StringUpper_0_127.f_UpperCase(), ==, StringUpper_0_127);
			DMibExpect(StringUpper_0_255.f_UpperCase(), ==, StringUpper_0_255);
			DMibExpect(StringUpper_0_65535.f_UpperCase(), ==, StringUpper_0_65535);
			DMibExpect(StringUpper_0_10ffff.f_UpperCase(), ==, StringUpper_0_10ffff);

			DMibExpect(StringCapitalized_0_127.f_UpperCase(), ==, StringUpper_0_127);
			DMibExpect(StringCapitalized_0_255.f_UpperCase(), ==, StringUpper_0_255);
			DMibExpect(StringCapitalized_0_65535.f_UpperCase(), ==, StringUpper_0_65535);
			DMibExpect(StringCapitalized_0_10ffff.f_UpperCase(), ==, StringUpper_0_10ffff);


			DMibExpect(fUpperCaseMaxLen(StringLower_0_127), ==, StringUpper_0_127);
			DMibExpect(fUpperCaseMaxLen(StringLower_0_255), ==, StringUpper_0_255);
			DMibExpect(fUpperCaseMaxLen(StringLower_0_65535), ==, StringUpper_0_65535);
			DMibExpect(fUpperCaseMaxLen(StringLower_0_10ffff), ==, StringUpper_0_10ffff);

			DMibExpect(fUpperCaseMaxLen(StringUpper_0_127), ==, StringUpper_0_127);
			DMibExpect(fUpperCaseMaxLen(StringUpper_0_255), ==, StringUpper_0_255);
			DMibExpect(fUpperCaseMaxLen(StringUpper_0_65535), ==, StringUpper_0_65535);
			DMibExpect(fUpperCaseMaxLen(StringUpper_0_10ffff), ==, StringUpper_0_10ffff);

			DMibExpect(fUpperCaseMaxLen(StringCapitalized_0_127), ==, StringUpper_0_127);
			DMibExpect(fUpperCaseMaxLen(StringCapitalized_0_255), ==, StringUpper_0_255);
			DMibExpect(fUpperCaseMaxLen(StringCapitalized_0_65535), ==, StringUpper_0_65535);
			DMibExpect(fUpperCaseMaxLen(StringCapitalized_0_10ffff), ==, StringUpper_0_10ffff);


			DMibExpect(fCapitalize(StringLower_0_127), ==, StringCapitalized_0_127);
			DMibExpect(fCapitalize(StringLower_0_255), ==, StringCapitalized_0_255);
			DMibExpect(fCapitalize(StringLower_0_65535), ==, StringCapitalized_0_65535);
			DMibExpect(fCapitalize(StringLower_0_10ffff), ==, StringCapitalized_0_10ffff);

			DMibExpect(fCapitalize(StringUpper_0_127), ==, StringUpper_0_127);
			DMibExpect(fCapitalize(StringUpper_0_255), ==, StringUpper_0_255);
			DMibExpect(fCapitalize(StringUpper_0_65535), ==, StringUpper_0_65535);
			DMibExpect(fCapitalize(StringUpper_0_10ffff), ==, StringUpper_0_10ffff);

			DMibExpect(fCapitalize(StringCapitalized_0_127), ==, StringCapitalized_0_127);
			DMibExpect(fCapitalize(StringCapitalized_0_255), ==, StringCapitalized_0_255);
			DMibExpect(fCapitalize(StringCapitalized_0_65535), ==, StringCapitalized_0_65535);
			DMibExpect(fCapitalize(StringCapitalized_0_10ffff), ==, StringCapitalized_0_10ffff);
		}

		void fp_CaseTests()
		{
			DMibTestSuite("Case")
			{
				{
					DMibTestPath("CStr");
					CGlobalFunctions_Tests::fsp_CaseTestsTyped<CStr>();
				}
				{
					DMibTestPath("CWStr");
					CGlobalFunctions_Tests::fsp_CaseTestsTyped<CWStr>();
				}
				{
					DMibTestPath("CUStr");
					CGlobalFunctions_Tests::fsp_CaseTestsTyped<CUStr>();
				}
			};
		}

		void fp_StrCmpNoCaseTest()
		{
			DMibTestSuite("StrCmpNoCase")
			{

				CStr UniqueStrings[] =
				{
					"Hello", "ch8 Hello",
					"Hell", "ch8 Hell",
					"", "ch8 Empty",
					CStr("Hello"), "CStr Hello",
					CStr("Hell"), "CStr Hell",
					CStr(""), "CStr Empty",
				};
				int siz = (sizeof(UniqueStrings) / sizeof(CStr)) / 2;
				for(int i=0;i<siz;++i)
				{
					DMibTestPath(UniqueStrings[i*2+1]);
					for(int j=0;j<siz;++j)
					{
						DMibTestPath(UniqueStrings[j*2+1]);
						CStr const &Left = UniqueStrings[i*2];
						CStr const &Right = UniqueStrings[j*2];
						if(i%3==j%3)
						{
							DMibTest(DMibExpr(fg_StrCmpNoCase(Left, Right) == 0));
							DMibTest(DMibExpr(fg_StrCmpNoCase(Right, Left) == 0));
						}
						else
						{
							auto cmp1 = fg_StrCmpNoCase(Left, Right);
							DMibTest(DMibExpr(cmp1 != 0));
							auto cmp2 = fg_StrCmpNoCase(Right, Left);
							DMibTest(DMibExpr(cmp2 != 0));
							DMibTest(DMibExpr(cmp2 == -cmp1));
						}
					}
				}
			};
		}

		void fp_FindTests()
		{
			CStr AlphabetLowerStr("abcdefghijklmnopqrstuvwxyz");
			CStr AlphabetUpperStr("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
			CStr AlphabetMixedStr("aBcDeFgHiJkLmNoPqRsTuVwXyZ");

			CStr AlphabetX2LowerStr("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
			CStr AlphabetX2UpperStr("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ");
			CStr AlphabetX2MixedStr("aBcDeFgHiJkLmNoPqRsTuVwXyZaBcDeFgHiJkLmNoPqRsTuVwXyZ");

			CStr StringLowerZ = "z";
			CStr StringUpperZ = "Z";

			DMibTestSuite("fg_StrFindIterator")
			{
				{
					CStrIteratorUTF8 IterA(AlphabetX2LowerStr.f_GetStr(), AlphabetX2LowerStr.f_GetLen());
					CStrIteratorUTF8 IterB(StringLowerZ.f_GetStr(), StringLowerZ.f_GetLen());
					DMibTest(DMibExpr(fg_StrFindIterator<false>(IterA, IterB)) == DMibExpr(25));
				}
				{
					CStrIteratorUTF8 IterA(AlphabetX2LowerStr.f_GetStr(), AlphabetX2LowerStr.f_GetLen());
					CStrIteratorUTF8 IterB(StringUpperZ.f_GetStr(), StringUpperZ.f_GetLen());
					DMibTest(DMibExpr(fg_StrFindIterator<false>(IterA, IterB)) == DMibExpr(-1));
				}
				{
					CStrIteratorUTF8 IterA2(AlphabetX2LowerStr.f_GetStr(), AlphabetX2LowerStr.f_GetLen());
					CStrIteratorUTF8 IterB2(StringUpperZ.f_GetStr(), StringUpperZ.f_GetLen());
					DMibTest(DMibExpr(fg_StrFindIterator<true>(IterA2, IterB2)) == DMibExpr(25));
				}

				{
					CStr FindThis = "xyzw";

					CStrIteratorUTF8 IterA3(AlphabetLowerStr.f_GetStr(), AlphabetLowerStr.f_GetLen());
					CStrIteratorUTF8 IterB3(FindThis.f_GetStr(), FindThis.f_GetLen());
					DMibTest(DMibExpr(fg_StrFindIterator<true>(IterA3, IterB3)) == DMibExpr(-1));
				}
				{
					CStr InThis = "abcabc";
					CStr FindThis = "abcabcd";

					CStrIteratorUTF8 IterA4(InThis.f_GetStr(), InThis.f_GetLen());
					CStrIteratorUTF8 IterB4(FindThis.f_GetStr(), FindThis.f_GetLen());
					DMibTest(DMibExpr(fg_StrFindIterator<true>(IterA4, IterB4)) == DMibExpr(-1));
				}
			};
		}

		void fp_UnicodeTests()
		{
			CStr TestStringFull(CWStr(str_utf16("abcdÅÄÖåöä亜哀姐飴𠀀")));
			CStr TestUnicode8(CWStr(str_utf16("abcdåäÖ")));

			DMibTestSuite("Unicode coding")
			{
				CStr TestString = TestStringFull;
				{
					DMibTestPath("UTF8");
					CStr TestConvert = TestString;
					CUStr UTF32;

					{
						CStrIteratorUTF8 Iterator(TestConvert);

						while (Iterator)
						{
							UTF32.f_AddChar(Iterator);
							++Iterator;
						}

						CMStrDeprecated Decoded = UTF32;

						DMibTest(DMibExpr(Decoded) == DMibExpr(TestString));
					}

					{

						CStr Out;
						umint Len = 0;
						auto fl_AddChars
							= [&](umint _nChars) -> ch8 *
							{
								umint OutLen = Out.f_CreateWritableBuffer(Len + _nChars + 1, false);
								if (OutLen < Len + _nChars)
									return nullptr;
								ch8 *pOut = Out.f_GetStrWritable() + Len;
								Len += _nChars;
								return pOut;
							}
						;

						ch32 const *pParse = UTF32.f_GetStr();
						while (*pParse)
						{
							if (!fg_EncodeUTF8Char<true>(*pParse, fl_AddChars))
								break;
							++pParse;
						}
						ch8 *pOut = Out.f_GetStrWritable() + Len;
						*pOut = 0;
						Out.f_SetStrLen(Len);

						CStr Encoded = Out;
						DMibTest(DMibExpr(Encoded) == DMibExpr(TestString));
					}
				}
				{
					DMibTestPath("UTF16");
					CWStr TestConvert = TestString;
					CUStr UTF32;

					{
						CStrIteratorUTF16 Iterator(TestConvert);

						while (Iterator)
						{
							UTF32.f_AddChar(*Iterator);
							++Iterator;
						}

						CMStrDeprecated Decoded = UTF32;

						DMibTest(DMibExpr(Decoded) == DMibExpr(TestString));
					}

					{

						CWStr Out;
						umint Len = 0;
						auto fl_AddChars
							= [&](umint _nChars) -> ch16 *
							{
								umint OutLen = Out.f_CreateWritableBuffer(Len + _nChars + 1, false);
								if (OutLen < Len + _nChars)
									return nullptr;
								ch16 *pOut = Out.f_GetStrWritable() + Len;
								Len += _nChars;
								return pOut;
							}
						;

						ch32 const *pParse = UTF32.f_GetStr();
						while (*pParse)
						{
							if (!fg_EncodeUTF16Char<true>(*pParse, fl_AddChars))
								break;
							++pParse;
						}
						ch16 *pOut = Out.f_GetStrWritable() + Len;
						*pOut = 0;
						Out.f_SetStrLen(Len);

						CMStrDeprecated Encoded = Out;
						DMibTest(DMibExpr(Encoded) == DMibExpr(TestString));

					}
				};
			};
			DMibTestSuite("Up conversion")
			{
				{
					DMibTestPath("ch8");
					{
						DMibTestPath("ANSI");
						CAnsiStr TestString(gc_AnsiTestString);
						CStr TestConvert = TestString;
						CStr MixedFrom = TestString;
						CStr MixedTo = TestConvert;

						DMibTest(DMibExpr(MixedFrom) == DMibExpr(MixedTo));

					}
					{
						DMibTestPath("ANSI not tracked");
						CAnsiStrNonTracked TestString(gc_AnsiTestString);
						CStrNonTracked TestConvert = TestString;
						CStr MixedFrom = TestString;
						CStr MixedTo = TestConvert;

						DMibTest(DMibExpr(MixedFrom) == DMibExpr(MixedTo));

					}
					{
						DMibTestPath("Unicode");
						CStr TestString(TestUnicode8);
						CStr TestConvert = TestString;
						CStr MixedFrom = TestString;
						CStr MixedTo = TestConvert;

						DMibTest(DMibExpr(MixedFrom) == DMibExpr(MixedTo));

					}
					{
						DMibTestPath("Unicode not tracked");
						CStrNonTracked TestString(TestUnicode8);
						CStrNonTracked TestConvert = TestString;
						CStr MixedFrom = TestString;
						CStr MixedTo = TestConvert;

						DMibTest(DMibExpr(MixedFrom) == DMibExpr(MixedTo));
					}
				}
				{
					DMibTestPath("ch16");
					{
						DMibTestPath("Unicode");
						CWStr TestString(str_utf16("abcdÅÄÖåöä亜哀姐飴"));
						CWStr TestConvert = TestString;
						CStr MixedFrom = TestString;
						CStr MixedTo = TestConvert;

						DMibTest(DMibExpr(MixedFrom) == DMibExpr(MixedTo));
					}
					{
						DMibTestPath("Unicode not tracked");
						CWStrNonTracked TestString(str_utf16("abcdÅÄÖåöä亜哀姐飴"));
						CWStrNonTracked TestConvert = TestString;
						CStr MixedFrom = TestString;
						CStr MixedTo = TestConvert;

						DMibTest(DMibExpr(MixedFrom) == DMibExpr(MixedTo));
					}
				}
			};

			DMibTestSuite("Type conversion")
			{
				{
					DMibTestPath("From ch8");
					{
						DMibTestPath("ANSI");
						CAnsiStr TestFrom(gc_AnsiTestString);
						{
							DMibTestPath("To ch8");
							{
								DMibTestPath("ANSI");
								CAnsiStr TestTo(gc_AnsiTestString);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
					}
					{
						DMibTestPath("Unicode");
						CStr TestFrom(TestUnicode8);
						{
							DMibTestPath("To ch8");
							{
								DMibTestPath("ANSI");
								CAnsiStr TestTo(gc_AnsiTestString);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("Unicode");
								CStr TestTo(TestUnicode8);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							};
						}
						{
							DMibTestPath("To ch16");
							{
								DMibTestPath("Unicode");
								CWStr TestTo(str_utf16("abcd\xc6\xc5\xd6\xe6\xe5\xf6亜哀姐飴"));
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CWStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch32");
							{
								DMibTestPath("Unicode");
								CUStr TestTo(TestStringFull);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
					}
					{
						DMibTestPath("UTF");
						CStr TestFrom(TestStringFull);
						{
							DMibTestPath("To ch8");
							{
								DMibTestPath("ANSI");
								CAnsiStr TestTo(gc_AnsiTestString);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("Unicode");
								CStr TestTo(TestUnicode8);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch16");
							{
								DMibTestPath("Unicode");
								CWStr TestTo(str_utf16("abcdÅÄÖåöä亜哀姐飴"));
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CWStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch32");
							{
								DMibTestPath("Unicode");
								CUStr TestTo(TestStringFull);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
					}
				}
				{
					DMibTestPath("ch16");
					{
						DMibTestPath("Unicode");
						CWStr TestFrom(str_utf16("abcdÅÄÖåöä亜哀姐飴"));
						{
							DMibTestPath("To ch8");
							{
								DMibTestPath("ANSI");
								CAnsiStr TestTo("abcdÅÄÖåöä");
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("Unicode");
								CStr TestTo(TestUnicode8);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch16");
							{
								DMibTestPath("Unicode");
								CWStr TestTo(str_utf16("abcdÅÄÖåöä亜哀姐飴"));
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CWStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch32");
							{
								DMibTestPath("Unicode");
								CUStr TestTo(TestStringFull);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
					}
					{
						DMibTestPath("UTF");
						CWStr TestFrom(TestStringFull);
						{
							DMibTestPath("To ch8");
							{
								DMibTestPath("ANSI");
								CAnsiStr TestTo("abcdÅÄÖåöä");
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("Unicode");
								CStr TestTo(TestUnicode8);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch16");
							{
								DMibTestPath("Unicode");
								CWStr TestTo(str_utf16("abcdÅÄÖåöä亜哀姐飴"));
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CWStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch32");
							{
								DMibTestPath("Unicode");
								CUStr TestTo(TestStringFull);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
					}
				}
				{
					DMibTestPath("ch32");
					{
						DMibTestPath("UTF");
						CUStr TestFrom(TestStringFull);
						{
							DMibTestPath("To ch8");
							{
								DMibTestPath("ANSI");
								CAnsiStr TestTo("abcdÅÄÖåöä");
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("Unicode");
								CStr TestTo(TestUnicode8);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch16");
							{
								DMibTestPath("Unicode");
								CWStr TestTo(str_utf16("abcdÅÄÖåöä亜哀姐飴"));
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
							{
								DMibTestPath("UTF");
								CWStr TestTo = TestStringFull;
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
						{
							DMibTestPath("To ch32");
							{
								DMibTestPath("Unicode");
								CUStr TestTo(TestStringFull);
								auto TestResult = TestFrom;
								TestResult += TestTo;
								CStr ReferenceResult = CStr(TestFrom) + CStr(TestTo);
								CStr MixedResult = TestResult;
								DMibTest(DMibExpr(MixedResult) == DMibExpr(ReferenceResult));
							}
						}
					}
				}
			};

			DMibTestSuite("ANSI conversion")
			{
				{
					DMibTestPath("From ch8");
					{
						DMibTestPath("ANSI");
						{
							DMibTestPath("To CStr");
							{
								DMibTestPath("UTF");
								CStr TestTo;
								NMib::NStr::NPlatform::fg_SystemDecodeAnsiStr(gc_AnsiTestString, TestTo);
								CStr FromResult(gc_AnsiTestStringUTF);
								CStr ToResult = TestTo;
								DMibTest(DMibExpr(FromResult) == DMibExpr(ToResult));
							}
						}
						{
							DMibTestPath("To CStrNonTracked");
							{
								DMibTestPath("UTF");
								CStrNonTracked TestTo;
								NMib::NStr::NPlatform::fg_SystemDecodeAnsiStr(gc_AnsiTestString, TestTo);
								CStr TestFrom(gc_AnsiTestStringUTF);
								DMibTest(DMibExpr(TestFrom) == DMibExpr(TestTo));
							}
						}
					}
				}
				{
					DMibTestPath("From CStr");
					{
						DMibTestPath("ANSI");
						{
							DMibTestPath("To CStr");
							{
								DMibTestPath("UTF");
								CStr TestTo;
								CAnsiStr TestFrom(gc_AnsiTestString);
								NMib::NStr::NPlatform::fg_SystemDecodeAnsiStr(TestFrom, TestTo);
								CMStrDeprecated FromResult = CMStrDeprecated(TestFrom);
								CMStrDeprecated ToResult = CMStrDeprecated(TestTo);
								DMibTest(DMibExpr(FromResult) == DMibExpr(ToResult));
							}
						}
					}
				}
				{
					DMibTestPath("From CStrNonTracked");
					{
						DMibTestPath("ANSI");
						{
							DMibTestPath("To CStrNonTracked");
							{
								DMibTestPath("UTF");
								CStrNonTracked TestTo;
								CAnsiStrNonTracked TestFrom(gc_AnsiTestString);
								NMib::NStr::NPlatform::fg_SystemDecodeAnsiStr(TestFrom, TestTo);
								CStr ToResult = TestTo;
								CStr FromResult = TestFrom;
								DMibTest(DMibExpr(FromResult) == DMibExpr(ToResult));
							}
						}
					}
				}
				{
					DMibTestPath("From CStr");
					{
						DMibTestPath("UTF");
						{
							DMibTestPath("To CStr");
							{
								DMibTestPath("ANSI");
								CAnsiStr TestTo;
								CStr TestString(CWStr(str_utf16("abcdÅÄÖåöä")));
								CStr TestFrom = TestString;

								NMib::NStr::NPlatform::fg_SystemEncodeAnsiStr(TestFrom, TestTo, '?');
								CStr FromResult = TestFrom;
								CStr ToResult = TestTo;
								DMibTest(DMibExpr(FromResult) == DMibExpr(ToResult));
							}
							{
								DMibTestPath("ANSI - non translatable");
								CAnsiStr TestTo;
								CStr TestString(CWStr(str_utf16("abcdÅÄÖåöä亜哀姐飴")));
								CStr TestFrom = TestString;
								NMib::NStr::NPlatform::fg_SystemEncodeAnsiStr(TestFrom, TestTo, '?');
								CStr FromResultWithError(CWStr(str_utf16("abcdÅÄÖåöä????")));
								CStr ToResult = TestTo;
								DMibTest(DMibExpr(FromResultWithError) == DMibExpr(ToResult));
							}
						}
					}
				}
				{
					DMibTestPath("From CStrNonTracked");
					{
						DMibTestPath("UTF");
						{
							DMibTestPath("To CStrNonTracked");
							{
								DMibTestPath("ANSI");
								CAnsiStr TestTo;
								CStr TestString(CWStr(str_utf16("abcdÅÄÖåöä")));
								CStrNonTracked TestFrom = TestString;
								NMib::NStr::NPlatform::fg_SystemEncodeAnsiStr(TestFrom, TestTo, '?');
								CStr FromResult = TestFrom;
								CStr ToResult = TestTo;
								DMibTest(DMibExpr(FromResult) == DMibExpr(ToResult));
							}
						}
						{
							DMibTestPath("ANSI - non translatable");
							CAnsiStr TestTo;
							CStr TestString(CWStr(str_utf16("abcdÅÄÖåöä亜哀姐飴")));
							CStrNonTracked TestFrom = TestString;
							NMib::NStr::NPlatform::fg_SystemEncodeAnsiStr(TestFrom, TestTo, '?');
							CStr FromResultWithError(CWStr(str_utf16("abcdÅÄÖåöä????")));
							CStr ToResult = TestTo;
							DMibTest(DMibExpr(FromResultWithError) == DMibExpr(ToResult));
						}
					}
				}
			};

			DMibTestSuite("Validation")
			{
				{
					DMibTestPath("Valid UTF8");
					{
						DMibTestPath("Boundaries");
						// Byte order mark
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("\0xef\0xbb\0xbfx"))));
						// First possible sequences
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xc2\x80x"))));
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xe0\xa0\x80x"))));
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xf0\x90\x80\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf8\x88\x80\x80\x80x"))));	// Beyond U-10FFFF
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfc\x84\x80\x80\x80\x80x")))); // Beyond U-10FFFF
						// Last possible sequences
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xdf\xbfx"))));
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xef\xbf\xbfx"))));	// Invalid codepoint
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xef\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)));	// Invalid codepoint
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf7\xbf\xbf\xbfx"))));	// Beyond U-10FFFF
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfb\xbf\xbf\xbf\xbfx"))));	// Beyond U-10FFFF
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfd\xbf\xbf\xbf\xbf\xbfx"))));	// Beyond U-10FFFF
						// Others
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xed\x9f\xbfx"))));
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xee\x80\x80x"))));	// Private use area
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xef\xbf\xbdx"))));	// ReplacementChar character
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xf4\x8f\xbf\xbfx"))));	// Non-character codepoint
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf4\x8f\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)));	// Non-character codepoint
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf4\x90\x80\x80x"))));  // Beyond U-10FFFF
					}
					{
						DMibTestPath("Invalid Bytes");
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\x80\xbfx"))));	// Unexpected continuation bytes
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfe\xfe\xff\xffx"))));	// Impossible bytes
					}
					{
						DMibTestPath("Lonely start characters");
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xc0x\xdfx"))));	// Lonely start characters from 2-byte sequence
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xe0x\xefx"))));	// Lonely start characters from 3-byte sequence
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf0x\xf7x"))));	// Lonely start characters from 4-byte sequence
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf8x\xfbx"))));	// Lonely start characters from 5-byte sequence
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfcx\xfdx"))));	// Lonely start characters from 6-byte sequence
					}
					{
						DMibTestPath("Last character missing");
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xe0\x80x"))));	// 3-byte sequence with last byte missing
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf0\x80\x80x"))));	// 4-byte sequence with last byte missing
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf8\x80\x80\x80x"))));	// 5-byte sequence with last byte missing
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfc\x80\x80\x80\x80x"))));	// 6-byte sequence with last byte missing
					}
					{
						DMibTestPath("Overlong sequences");
						// Overlong ASCII
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xc0\xafx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xe0\x80\xafx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf0\x80\x80\xafx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf8\x80\x80\x80\xafx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfc\x80\x80\x80\x80\xafx"))));
						// Overlong codepoints
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xc1\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xe0\x9f\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf0\x8f\xbf\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf8\x87\xbf\xbf\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfc\x83\xbf\xbf\xbf\xbfx"))));
						// Overlong NUL
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xc1\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xe0\x80\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf0\x80\x80\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xf8\x80\x80\x80\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xfc\x80\x80\x80\x80\x80x"))));
					}
					{
						DMibTestPath("Illegal code positions");
						// Single UTF-16 Surrogates
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xa0\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xad\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xae\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xaf\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xb0\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xbe\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xbf\xbfx"))));
						// Paired UTF-16 surrogates
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xa0\x80\xed\xb0\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xa0\x80\xed\xbf\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xad\xbf\xed\xb0\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xad\xbf\xed\xbf\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xae\x80\xed\xb0\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xae\x80\xed\xbf\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xaf\xbf\xed\xb0\x80x"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xed\xaf\xbf\xed\xbf\xbfx"))));
						// Invalid code positions
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xef\xbf\xbex")))) ;
						DMibTest(DMibExpr(fg_IsValidUTF8(CStr("x\xef\xbf\xbfx"))));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xef\xbf\xbex"), EValidateUTF8Flag::mc_DisallowNonCharacters)));
						DMibTest(DMibExpr(!fg_IsValidUTF8(CStr("x\xef\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)));
					}
				}
				{
					DMibTestPath("Replace characters UTF8");
					{
						DMibTestPath("Boundaries");
						// Byte order mark
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("\0xef\0xbb\0xbfx"))) == DMibExpr(CStr("\0xef\0xbb\0xbfx")));
						// First possible sequences
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xc2\x80x"))) == DMibExpr(CStr("x\xc2\x80x")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xe0\xa0\x80x"))) == DMibExpr(CStr("x\xe0\xa0\x80x")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf0\x90\x80\x80x"))) == DMibExpr(CStr("x\xf0\x90\x80\x80x")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf8\x88\x80\x80\x80x"))) == DMibExpr(CStr("x?????x")));	// Beyond U-10FFFF
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfc\x84\x80\x80\x80\x80x"))) == DMibExpr(CStr("x??????x"))); // Beyond U-10FFFF
						// Last possible sequences
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xdf\xbfx"))) == DMibExpr(CStr("x\xdf\xbfx")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xef\xbf\xbfx"))) == DMibExpr(CStr("x\xef\xbf\xbfx")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xef\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)) == DMibExpr(CStr("x???x")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf7\xbf\xbf\xbfx"))) == DMibExpr(CStr("x????x")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfb\xbf\xbf\xbf\xbfx"))) == DMibExpr(CStr("x?????x")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfd\xbf\xbf\xbf\xbf\xbfx"))) == DMibExpr(CStr("x??????x")));
						// Others
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\x9f\xbfx"))) == DMibExpr(CStr("x\xed\x9f\xbfx")));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xee\x80\x80x"))) == DMibExpr(CStr("x\xee\x80\x80x")));	// Private use area
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xef\xbf\xbdx"))) == DMibExpr(CStr("x\xef\xbf\xbdx")));	// ReplacementChar character
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf4\x8f\xbf\xbfx"))) == DMibExpr(CStr("x\xf4\x8f\xbf\xbfx")));	//Non-character codepoint
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf4\x8f\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)) == DMibExpr(CStr("x????x")));	//Non-character codepoint
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf4\x90\x80\x80x"))) == DMibExpr(CStr("x????x")));
					}
					{
						DMibTestPath("Invalid Bytes");
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\x80\xbfx"))) == DMibExpr("x??x"));	// Unexpected continuation bytes
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfe\xfe\xff\xffx"))) == DMibExpr("x????x"));	// Impossible bytes
					}
					{
						DMibTestPath("Lonely start characters");
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xc0\xdfx"))) == DMibExpr("x??x"));	// Lonely start characters from 2-byte sequence
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xe0\xefx"))) == DMibExpr("x??x"));	// Lonely start characters from 3-byte sequence
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf0\xf7x"))) == DMibExpr("x??x"));	// Lonely start characters from 4-byte sequence
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf8\xfbx"))) == DMibExpr("x??x"));	// Lonely start characters from 5-byte sequence
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfc\xfdx"))) == DMibExpr("x??x"));	// Lonely start characters from 6-byte sequence
					}
					{
						DMibTestPath("Last character missing");
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xe0\x80x"))) == DMibExpr("x??x"));	// 3-byte sequence with last byte missing
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf0\x80\x80x"))) == DMibExpr("x???x"));	// 4-byte sequence with last byte missing
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf8\x80\x80\x80x"))) == DMibExpr("x????x"));	// 5-byte sequence with last byte missing
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfc\x80\x80\x80\x80x"))) == DMibExpr("x?????x"));	// 6-byte sequence with last byte missing
					}
					{
						DMibTestPath("Overlong sequences");
						// Overlong ASCII
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xc0\xafx"))) == DMibExpr("x??x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xe0\x80\xafx"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf0\x80\x80\xafx"))) == DMibExpr("x????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf8\x80\x80\x80\xafx"))) == DMibExpr("x?????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfc\x80\x80\x80\x80\xafx"))) == DMibExpr("x??????x"));
						// Overlong codepoints
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xc1\xbfx"))) == DMibExpr("x??x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xe0\x9f\xbfx"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf0\x8f\xbf\xbfx"))) == DMibExpr("x????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf8\x87\xbf\xbf\xbfx"))) == DMibExpr("x?????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfc\x83\xbf\xbf\xbf\xbfx"))) == DMibExpr("x??????x"));
						// Overlong NUL
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xc1\x80x"))) == DMibExpr("x??x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xe0\x80\x80x"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf0\x80\x80\x80x"))) == DMibExpr("x????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xf8\x80\x80\x80\x80x"))) == DMibExpr("x?????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xfc\x80\x80\x80\x80\x80x"))) == DMibExpr("x??????x"));
					}
					{
						DMibTestPath("Illegal code positions");
						// Single UTF-16 Surrogates
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xa0\x80x"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xad\xbfx"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xae\x80x"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xaf\xbfx"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xb0\x80x"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xbe\x80x"))) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xbf\xbfx"))) == DMibExpr("x???x"));
						// Paired UTF-16 surrogates
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xa0\x80\xed\xb0\x80x"))) == DMibExpr("x??????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xa0\x80\xed\xbf\xbfx"))) == DMibExpr("x??????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xad\xbf\xed\xb0\x80x"))) == DMibExpr("x??????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xad\xbf\xed\xbf\xbfx"))) == DMibExpr("x??????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xae\x80\xed\xb0\x80x"))) == DMibExpr("x??????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xae\x80\xed\xbf\xbfx"))) == DMibExpr("x??????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xaf\xbf\xed\xb0\x80x"))) == DMibExpr("x??????x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xed\xaf\xbf\xed\xbf\xbfx"))) == DMibExpr("x??????x"));
						// Invalid code positions
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xef\xbf\xbex"))) == DMibExpr("x\xef\xbf\xbex"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xef\xbf\xbfx"))) == DMibExpr("x\xef\xbf\xbfx"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xef\xbf\xbex"), EValidateUTF8Flag::mc_DisallowNonCharacters)) == DMibExpr("x???x"));
						DMibTest(DMibExpr(fg_ReplaceCharactersUTF8(CStr("x\xef\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)) == DMibExpr("x???x"));
					}
				}
				{
					DMibTestPath("Replace sequence UTF8");
					CStr ReplacementChar("x\xef\xbf\xbdx");
					CStr DoubleReplacementChar("x\xef\xbf\xbd\xef\xbf\xbdx");
					CStr QuadReplacementChar("x\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbdx");
					{
						DMibTestPath("Boundaries");
						// Byte order mark
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("\0xef\0xbb\0xbfx"))) == DMibExpr(CStr("\0xef\0xbb\0xbfx")));
						// First possible sequences
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xc2\x80x"))) == DMibExpr(CStr("x\xc2\x80x")));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xe0\xa0\x80x"))) == DMibExpr(CStr("x\xe0\xa0\x80x")));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf0\x90\x80\x80x"))) == DMibExpr(CStr("x\xf0\x90\x80\x80x")));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf8\x88\x80\x80\x80x"))) == DMibExpr(ReplacementChar));	// Beyond U-10FFFF
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfc\x84\x80\x80\x80\x80x"))) == DMibExpr(ReplacementChar)); // Beyond U-10FFFF
						// Last possible sequences
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xdf\xbfx"))) == DMibExpr(CStr("x\xdf\xbfx")));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xef\xbf\xbfx"))) == DMibExpr(CStr("x\xef\xbf\xbfx")));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xef\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf7\xbf\xbf\xbfx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfb\xbf\xbf\xbf\xbfx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfd\xbf\xbf\xbf\xbf\xbfx"))) == DMibExpr(ReplacementChar));
						// Others
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\x9f\xbfx"))) == DMibExpr(CStr("x\xed\x9f\xbfx")));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xee\x80\x80x"))) == DMibExpr(CStr("x\xee\x80\x80x")));	// Private use area
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xef\xbf\xbdx"))) == DMibExpr(ReplacementChar));	// ReplacementChar character
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf4\x8f\xbf\xbfx"))) == DMibExpr(CStr("x\xf4\x8f\xbf\xbfx")));	// Non-character codepoint
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf4\x8f\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)) == DMibExpr(ReplacementChar));	// Non-character codepoint
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf4\x90\x80\x80x"))) == DMibExpr(ReplacementChar));
					}
					{
						DMibTestPath("Invalid Bytes");
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\x80\xbfx"))) == DMibExpr(DoubleReplacementChar));	// Unexpected continuation bytes
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfe\xfe\xff\xffx"))) == DMibExpr(QuadReplacementChar));	// Impossible bytes
					}
					{
						DMibTestPath("Lonely start characters");
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xc0\xdfx"))) == DMibExpr(DoubleReplacementChar));	// Lonely start characters 2-byte sequence
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xe0\xefx"))) == DMibExpr(DoubleReplacementChar));	// Lonely start characters 3-byte sequence
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf0\xf7x"))) == DMibExpr(DoubleReplacementChar));	// Lonely start characters 4-byte sequence
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf8\xfbx"))) == DMibExpr(DoubleReplacementChar));	// Lonely start characters 5-byte sequence
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfc\xfdx"))) == DMibExpr(DoubleReplacementChar));	// Lonely start characters 6-byte sequence
					}
					{
						DMibTestPath("Last character missing");
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xe0\x80x"))) == DMibExpr(ReplacementChar));	// 3-byte sequence last byte missing
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf0\x80\x80x"))) == DMibExpr(ReplacementChar));	// 4-byte sequence last byte missing
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf8\x80\x80\x80x"))) == DMibExpr(ReplacementChar));	// 5-byte sequence last byte missing
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfc\x80\x80\x80\x80x"))) == DMibExpr(ReplacementChar));	// 6-byte sequence last byte missing
					}
					{
						DMibTestPath("Overlong sequences");
						// Overlong ASCII
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xc0\xafx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xe0\x80\xafx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf0\x80\x80\xafx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf8\x80\x80\x80\xafx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfc\x80\x80\x80\x80\xafx"))) == DMibExpr(ReplacementChar));
						// Overlong codepoints
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xc1\xbfx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xe0\x9f\xbfx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf0\x8f\xbf\xbfx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf8\x87\xbf\xbf\xbfx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfc\x83\xbf\xbf\xbf\xbfx"))) == DMibExpr(ReplacementChar));
						// Overlong NUL
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xc1\x80x"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xe0\x80\x80x"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf0\x80\x80\x80x"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xf8\x80\x80\x80\x80x"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xfc\x80\x80\x80\x80\x80x"))) == DMibExpr(ReplacementChar));
					}
					{
						DMibTestPath("Illegal code positions");
						// Single UTF-16 Surrogates
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xa0\x80x"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xad\xbfx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xae\x80x"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xaf\xbfx"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xb0\x80x"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xbe\x80x"))) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xbf\xbfx"))) == DMibExpr(ReplacementChar));
						// Paired UTF-16 surrogates
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xa0\x80\xed\xb0\x80x"))) == DMibExpr(DoubleReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xa0\x80\xed\xbf\xbfx"))) == DMibExpr(DoubleReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xad\xbf\xed\xb0\x80x"))) == DMibExpr(DoubleReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xad\xbf\xed\xbf\xbfx"))) == DMibExpr(DoubleReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xae\x80\xed\xb0\x80x"))) == DMibExpr(DoubleReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xae\x80\xed\xbf\xbfx"))) == DMibExpr(DoubleReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xaf\xbf\xed\xb0\x80x"))) == DMibExpr(DoubleReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xed\xaf\xbf\xed\xbf\xbfx"))) == DMibExpr(DoubleReplacementChar));
						// Invalid code positions
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xef\xbf\xbex"))) == DMibExpr(CStr("x\xef\xbf\xbex")));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xef\xbf\xbfx"))) == DMibExpr(CStr("x\xef\xbf\xbfx")));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xef\xbf\xbex"), EValidateUTF8Flag::mc_DisallowNonCharacters)) == DMibExpr(ReplacementChar));
						DMibTest(DMibExpr(fg_ReplaceSequenceUTF8(CStr("x\xef\xbf\xbfx"), EValidateUTF8Flag::mc_DisallowNonCharacters)) == DMibExpr(ReplacementChar));
					}
				}
				{
					DMibTestPath("Conditional replacement");
					{
						DMibTestPath("String replacement");
						CStr InvalidData("x\xed\xa0\x80x");
						CStr ValidData("x\xf0\x90\x80\x80x");

						DMibTest(DMibExpr(fg_CleanUTF8(ValidData).m_pData) == DMibExpr(ValidData.m_pData));
						DMibTest(DMibExpr(fg_CleanUTF8(InvalidData).m_pData) != DMibExpr(InvalidData.m_pData));
					}
				}
				{
					DMibTestPath("CStrIteratorUTF8");
					{
						DMibTestPath("Valid string");
						CStr ValidString("abc\xc3\xa5\xc3\xa4\xc3\xb6\n");
						auto iUTF = ValidString.f_GetUnicodeIterator();

						auto fCheckCharacter =
							[&](ch32 _Char)
							{
								DMibTestPath(CStr::CFormat("{}") << _Char);
								DMibTest(DMibExpr(*iUTF) == DMibExpr(_Char));
								DMibTest(DMibExpr(iUTF.f_IsWholeCodePoint()));
								DMibTest(DMibExpr(!iUTF.f_IsBroken()));
								++iUTF;
							}
						;

						fCheckCharacter('a');
						fCheckCharacter('b');
						fCheckCharacter('c');
						fCheckCharacter(229);
						fCheckCharacter(228);
						fCheckCharacter(246);
						fCheckCharacter('\n');
						fCheckCharacter('\0');
					}
					{
						DMibTestPath("Range based for loop");
						CStr ValidString("abc\xc3\xa5\xc3\xa4\xc3\xb6\n");

						ch32 ExpectedChars[] = {'a', 'b', 'c', 229, 228, 246, '\n'};
						ch32 const *pExpectedChar = ExpectedChars;

						for (auto Char : ValidString.f_GetUnicodeIterator())
						{
							DMibTestPath(CStr::CFormat("{}") << *pExpectedChar);
							DMibTest(DMibExpr(Char) == DMibExpr(*pExpectedChar));
							++pExpectedChar;
						}
					}
					{
						DMibTestPath("Range based for loop (ch8)");
						CStr ValidString("abc\xc3\xa5\n");

						ch8 ExpectedChars[] = {'a', 'b', 'c', '\xc3', '\xa5', '\n'};
						ch8 const *pExpectedChar = ExpectedChars;

						for (ch8 Char : ValidString)
						{
							DMibTestPath(CStr::CFormat("{}") << *pExpectedChar);
							DMibTest(DMibExpr(Char) == DMibExpr(*pExpectedChar));
							++pExpectedChar;
						}
					}
					{
						DMibTestPath("Incomplete string");
						CStr IncompleteString("a\xc3");
						auto iUTF = IncompleteString.f_GetUnicodeIterator();

						auto fCheckCharacter =
							[&](bool _bExpectFail)
							{
								DMibTestPath(CStr::CFormat("{}") << *iUTF);
								if (_bExpectFail)
								{
									DMibTest(DMibExpr(!iUTF.f_IsWholeCodePoint()));
									DMibTest(DMibExpr(!iUTF.f_IsBroken()));
								}
								else
								{
									DMibTest(DMibExpr(iUTF.f_IsWholeCodePoint()));
									DMibTest(DMibExpr(!iUTF.f_IsBroken()));
								}
								++iUTF;
							}
						;

						fCheckCharacter(false);
						fCheckCharacter(true);

						DMibExpectFalse(fg_IsValidUTF8(CStr("a\xc3")));
					}
					{
						DMibTestPath("Incomplete string stack");
						ch8 Temp[2];
						Temp[0] = 'a';
						Temp[1] = '\xc3';

						CStrIteratorUTF8 iUTF(Temp, 2);

						auto fCheckCharacter =
							[&](bool _bExpectFail)
							{
								DMibTestPath(CStr::CFormat("{}") << *iUTF);
								if (_bExpectFail)
								{
									DMibTest(DMibExpr(!iUTF.f_IsWholeCodePoint()));
									DMibTest(DMibExpr(!iUTF.f_IsBroken()));
								}
								else
								{
									DMibTest(DMibExpr(iUTF.f_IsWholeCodePoint()));
									DMibTest(DMibExpr(!iUTF.f_IsBroken()));
								}
								++iUTF;
							}
						;

						fCheckCharacter(false);
						fCheckCharacter(true);
					}
					{
						DMibTestPath("Invalid string");
						CStr InvalidString("a\xc3" "b");
						auto iUTF = InvalidString.f_GetUnicodeIterator();

						auto fCheckCharacter =
							[&](bool _bExpectFail)
						{
							DMibTestPath(CStr::CFormat("{}") << *iUTF);
							if (_bExpectFail)
							{
								DMibTest(DMibExpr(iUTF.f_IsWholeCodePoint()));
								DMibTest(DMibExpr(iUTF.f_IsBroken()));
							}
							else
							{
								DMibTest(DMibExpr(iUTF.f_IsWholeCodePoint()));
								DMibTest(DMibExpr(!iUTF.f_IsBroken()));
							}
							++iUTF;
						}
						;

						fCheckCharacter(false);
						fCheckCharacter(true);
						fCheckCharacter(false);
					}
				}
				{
					DMibTestPath("fg_StrSanitizeOneLine");
					{
						DMibTestPath("Horizontal whitespaces");
						DMibTest(DMibExpr(fg_StrSanitizeOneLine(CStr("x\tx"))) == DMibExpr("x\tx")); // Horizontal Tab
						DMibTest(DMibExpr(fg_StrSanitizeOneLine(CStr("x x"))) == DMibExpr("x x")); //	Space
						DMibTest(DMibExpr(fg_StrSanitizeOneLine(CStr("x\xC2\xA0x"))) == DMibExpr("x\xC2\xA0x")); //	no-break space
						DMibTest(DMibExpr(fg_StrSanitizeOneLine(CStr("x\xE2\x80\x80x"))) == DMibExpr("x\xE2\x80\x80x")); // en quad
					}
					{
						DMibTestPath("Vertical whitespaces");
						DMibTest(DMibExpr(fg_StrSanitizeOneLine(CStr("x\nx"))) == DMibExpr("x x")); // Line feed
						DMibTest(DMibExpr(fg_StrSanitizeOneLine(CStr("x\rx"))) == DMibExpr("x x")); // Carriage return
						DMibTest(DMibExpr(fg_StrSanitizeOneLine(CStr("x\xE2\x80\xA9x"))) == DMibExpr("x x")); // Paragraph Separator
					}
				}
			};
		}

		void fp_SeparatorTests()
		{
			DMibTestSuite("StrSep")
			{
				{
					DMibTestPath("GetStrSep");
					CStr Str1 = "One,Two, Three , Four";

					DMibTest(DMibExpr(CStr("One")) == DMibExpr(fg_GetStrSep(Str1, ",")));
					DMibTest(DMibExpr(CStr("Two")) == DMibExpr(fg_GetStrSep(Str1, ",")));
					DMibTest(DMibExpr(CStr("Three")) == DMibExpr(fg_GetStrSep(Str1, ",")));
					DMibTest(DMibExpr(CStr("Four")) == DMibExpr(fg_GetStrSep(Str1, ",")));
					DMibTest(DMibExpr((bool)Str1.f_IsEmpty()));
				}
				{
					DMibTestPath("GetStrSepEscaped");
					{
						CStr Str1 = "One,Two, Three , Four";

						DMibTest(DMibExpr(CStr("One")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str1, ",")));
						DMibTest(DMibExpr(CStr("Two")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str1, ",")));
						DMibTest(DMibExpr(CStr("Three")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str1, ",")));
						DMibTest(DMibExpr(CStr("Four")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str1, ",")));
						DMibTest(DMibExpr(true) == DMibExpr((bool)Str1.f_IsEmpty()));
					}
					{
						CStr Str2 = "'One,Two', Three , Four";

						DMibTest(DMibExpr(CStr("One,Two")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str2, ",")));
						DMibTest(DMibExpr(CStr("Three")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str2, ",")));
						DMibTest(DMibExpr(CStr("Four")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str2, ",")));
						DMibTest(DMibExpr(true) == DMibExpr((bool)Str2.f_IsEmpty()));
					}
					{
						CStr Str3 = "Zero,'One,Two', Three , Four";

						DMibTest(DMibExpr(CStr("Zero")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str3, ",")));
						DMibTest(DMibExpr(CStr("One,Two")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str3, ",")));
						DMibTest(DMibExpr(CStr("Three")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str3, ",")));
						DMibTest(DMibExpr(CStr("Four")) == DMibExpr(fg_GetStrSepEscaped<'\''>(Str3, ",")));
						DMibTest(DMibExpr(true) == DMibExpr((bool)Str3.f_IsEmpty()));
					}
				};


			};
		}

		void fp_IndentTests()
		{
			DMibTestSuite("Indent")
			{
				DMibExpect(CStr("").f_Indent("i"), ==, "");
				DMibExpect(CStr("").f_Indent("i", false, false), ==, "");
				DMibExpect(CStr("").f_Indent("i", true, false), ==, "");
				DMibExpect(CStr("").f_Indent("i", false, true), ==, "");

				DMibExpect(CStr("\n").f_Indent("i"), ==, "i\ni");
				DMibExpect(CStr("\n").f_Indent("i", false, false), ==, "\n");
				DMibExpect(CStr("\n").f_Indent("i", true, false), ==, "i\n");
				DMibExpect(CStr("\n").f_Indent("i", false, true), ==, "\ni");

				DMibExpect(CStr("Test").f_Indent("i"), ==, "iTest");
				DMibExpect(CStr("Test").f_Indent("i", false, false), ==, "Test");
				DMibExpect(CStr("Test").f_Indent("i", true, false), ==, "iTest");
				DMibExpect(CStr("Test").f_Indent("i", false, true), ==, "Test");

				DMibExpect(CStr("Test\n").f_Indent("i"), ==, "iTest\ni");
				DMibExpect(CStr("Test\n").f_Indent("i", false, false), ==, "Test\n");
				DMibExpect(CStr("Test\n").f_Indent("i", true, false), ==, "iTest\n");
				DMibExpect(CStr("Test\n").f_Indent("i", false, true), ==, "Test\ni");

				DMibExpect(CStr("Test\nTest").f_Indent("i"), ==, "iTest\niTest");
				DMibExpect(CStr("Test\nTest").f_Indent("i", false, false), ==, "Test\niTest");
				DMibExpect(CStr("Test\nTest").f_Indent("i", true, false), ==, "iTest\niTest");
				DMibExpect(CStr("Test\nTest").f_Indent("i", false, true), ==, "Test\niTest");
			};
		}

		void fp_TestUserData()
		{
			DMibTestSuite("UserData")
			{
				for (umint i = 0; i < 2; ++i)
				{
					DMibTestPath(i == 0 ? "Non-Empty" : "Empty");

					for (umint TestValue = 0; TestValue < 4; ++TestValue)
					{
						DMibTestPath("{}"_f << TestValue);

						CStr TestString;
						if (i == 0)
							TestString = "Test";

						TestString.f_SetUserData(TestValue);
						DMibExpect(TestString.f_GetUserData(), ==, TestValue);

						CStr TestString2{TestString};
						DMibExpect(TestString2.f_GetUserData(), ==, TestValue);

						CStr TestString3;
						TestString3 = TestString;
						DMibExpect(TestString3.f_GetUserData(), ==, TestValue);

						CStr TestString4(NMib::fg_Move(TestString2));
						DMibExpect(TestString4.f_GetUserData(), ==, TestValue);

						CStr TestString5;
						TestString5 = NMib::fg_Move(TestString3);
						DMibExpect(TestString5.f_GetUserData(), ==, TestValue);

						CStr TestString6 = TestString5;
						TestString6 += "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
						DMibExpect(TestString6.f_GetUserData(), ==, TestValue);

						CStr TestString7(TestString5);
						TestString7 = "";
						DMibExpect(TestString7.f_GetUserData(), ==, 0);

						CStr TestString8(TestString5);
						TestString8.f_Clear();
						DMibExpect(TestString8.f_GetUserData(), ==, 0);

						CStr TestString9(TestString5);
						TestString9.f_CreateWritableBuffer(2, false);
						TestString9.f_GetStrWritable()[0] = 0;
						TestString9.f_SetStrLen(0);
						DMibExpect(TestString9.f_GetUserData(), ==, TestValue);

						CStr TestString10(TestString5);
						TestString10.f_CreateWritableBuffer(2, true);
						TestString10.f_GetStrWritable()[0] = 0;
						TestString10.f_SetStrLen(0);
						DMibExpect(TestString10.f_GetUserData(), ==, TestValue);
					}
				}
			};
		}

		void fp_Constant()
		{
			DMibTestSuite("Constant")
			{
				static_assert(NMib::NTraits::cIsSame<decltype(gc_Str<"TestString">.m_Str), CStr const>);
				static_assert(NMib::NTraits::cIsSame<decltype(gc_Str<str_utf16("TestString")>.m_Str), CWStr const>);
				static_assert(NMib::NTraits::cIsSame<decltype(gc_Str<str_utf32("TestString")>.m_Str), CUStr const>);

				DMibExpect(gc_Str<"TestString">.m_Str, ==, CStr("TestString"));
				DMibExpect(&gc_Str<"TestString">.m_Str, ==, &gc_Str<"TestString">.m_Str);
#ifndef DCompiler_MSVC
				DMibExpect(&gc_Str<"TestString">.m_Str, ==, &fg_GetTestStringInAnotherTranslationUnit());
#endif
				DMibExpect(gc_Str<str_utf16("TestString")>.m_Str, ==, CWStr(str_utf16("TestString")));
				DMibExpect(&gc_Str<str_utf16("TestString")>.m_Str, ==, &gc_Str<str_utf16("TestString")>.m_Str);

				DMibExpect(gc_Str<str_utf32("TestString")>.m_Str, ==, CUStr(str_utf32("TestString")));
				DMibExpect(&gc_Str<str_utf32("TestString")>.m_Str, ==, &gc_Str<str_utf32("TestString")>.m_Str);
			};
		}

	public:
		void f_DoTests()
		{
			fp_CaseTests();
			fp_FindCharTests();
			fp_StrCmpNoCaseTest();
			fp_UnicodeTests();
			fp_SeparatorTests();
			fp_FindTests();
			fp_IndentTests();
			fp_TestUserData();
			fp_Constant();
		}
	};

	 DMibTestRegister(CGlobalFunctions_Tests, Malterlib::String::Container);

	struct CFormat_Tests : public NMib::NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("CFormat Visitor")
			{
				struct CTesting
				{
				};

				struct CTestExtractor : public CStr::CFormatArgVisitor
				{
					CTestExtractor()
						: m_Extracted(0)
					{
					}
					uint32 m_Extracted;

					virtual void operator () (uint32 _Value)
					{
						DMibTest(DMibExpr(_Value) == DMibExpr(6u));
						m_Extracted |= DMibBit(0);
					}

					virtual void operator () (uint64 _Value)
					{
						DMibTest(DMibExpr(_Value) == DMibExpr(8u));
						m_Extracted |= DMibBit(1);
					}

					virtual void operator () (int32 _Value)
					{
						DMibTest(DMibExpr(_Value) == DMibExpr(5));
						m_Extracted |= DMibBit(2);
					}

					virtual void operator () (int64 _Value)
					{
						DMibTest(DMibExpr(_Value) == DMibExpr(7));
						m_Extracted |= DMibBit(3);
					}

					virtual void operator () (fp32 _Value)
					{
						DMibTest(DMibExpr(_Value) == DMibExpr(9.5f));
						m_Extracted |= DMibBit(4);
					}

					virtual void operator () (fp64 _Value)
					{
						DMibTest(DMibExpr(_Value) == DMibExpr(10.5));
						m_Extracted |= DMibBit(5);
					}

					virtual void operator () (const ch8 *_pValue)
					{
						DMibTest(DMibExpr(fg_StrCmp(_pValue, "String") == 0));
						m_Extracted |= DMibBit(6);
					}

					virtual void operator () ()
					{
						m_Extracted |= DMibBit(7);
					}
				};

				CTestExtractor Extractor;

				auto fl_Test = [&](CStr::CFormat const &_Format)
				{
					DMibTest(DMibExpr(_Format.f_GetNumArgs()) == DMibExpr(8u)) (ETest_FailAndStop);
					_Format.f_GetArg(0)->f_Visit(Extractor);
					_Format.f_GetArg(1)->f_Visit(Extractor);
					_Format.f_GetArg(2)->f_Visit(Extractor);
					_Format.f_GetArg(3)->f_Visit(Extractor);
					_Format.f_GetArg(4)->f_Visit(Extractor);
					_Format.f_GetArg(5)->f_Visit(Extractor);
					_Format.f_GetArg(6)->f_Visit(Extractor);
					_Format.f_GetArg(7)->f_Visit(Extractor);
				};

				CStr::CFormat Test("");
				fl_Test(Test << int32(5) << uint32(6) << int64(7) << uint64(8) << fp32(9.5) << fp64(10.5) << "String" << fg_FormatAsBinary(CTesting()));

				DMibTest(DMibExpr(Extractor.m_Extracted) == DMibExpr((uint32(DMibBitRange(0 ,7)))));
			};

			DMibTestSuite("Any formats")
			{
				struct CData
				{
					CData()
					{
						mp_Test[0] = 0xff;
						mp_Test[1] = 0xee;
						mp_Test[2] = 0xbb;
						mp_Test[3] = 0x00;
					}
				private:
					uint8 mp_Test[4];
				};

				CData Data;

				DMibTest(DMibExpr(CStr::fs_ToStr(Data)) == DMibExpr("ffeebb00"));
			};

			DMibTestSuite("Escaping")
			{
				{
					DMibTestPath("Bash");
					CWStr TestStringSQStart(str_utf16("abcdÅÄÖåöä '亜哀姐飴'"));
					CWStr TestStringSQEnd(str_utf16("'abcdÅÄÖåöä '\\''亜哀姐飴'\\'''"));


					DMibTest(DMibExpr(fg_StrEscapeBashQuotesNeeded(CStr("Fred"))) == DMibExpr(false));
					DMibTest(DMibExpr(fg_StrEscapeBashQuotesNeeded(CStr("Fred/Stone.test"))) == DMibExpr(false));
					DMibTest(DMibExpr(fg_StrEscapeBashQuotesNeeded(CStr("Bam Bam"))) == DMibExpr(true));
					DMibTest(DMibExpr(fg_StrEscapeBashQuotesNeeded(CStr("Bam	Bam"))) == DMibExpr(true));
					DMibTest(DMibExpr(fg_StrEscapeBashQuotesNeeded(CStr("Fred's"))) == DMibExpr(true));
					DMibTest(DMibExpr(fg_StrEscapeBashQuotesNeeded(CStr("'Bam' 'Bam'"))) == DMibExpr(true));
					DMibTest(DMibExpr(fg_StrEscapeBashQuotesNeeded(CStr("\\"))) == DMibExpr(true));
					DMibTest(DMibExpr(fg_StrEscapeBashQuotesNeeded(TestStringSQStart)) == DMibExpr(true));

					DMibTest(DMibExpr(fg_StrEscapeBashSingleQuotes(CStr("Fred"))) == DMibExpr(CStr("'Fred'")));
					DMibTest(DMibExpr(fg_StrEscapeBashSingleQuotes(CStr("Bam Bam"))) == DMibExpr(CStr("'Bam Bam'")));
					DMibTest(DMibExpr(fg_StrEscapeBashSingleQuotes(CStr("Fred's"))) == DMibExpr(CStr("'Fred'\\''s'")));
					DMibTest(DMibExpr(fg_StrEscapeBashSingleQuotes(CStr("'Bam' 'Bam'"))) == DMibExpr(CStr("''\\''Bam'\\'' '\\''Bam'\\'''")));
					DMibTest(DMibExpr(fg_StrEscapeBashSingleQuotes(TestStringSQStart)) == DMibExpr(TestStringSQEnd));

					CWStr TestStringDQStart(str_utf16("abcdÅÄÖåöä \"亜哀姐飴\""));
					CWStr TestStringDQEnd(str_utf16("\"abcdÅÄÖåöä \\\"亜哀姐飴\\\"\""));

					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("Fred"))) == DMibExpr(CStr("\"Fred\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("$Fred"))) == DMibExpr(CStr("\"\\$Fred\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("$Fred`"))) == DMibExpr(CStr("\"\\$Fred\\`\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("$* ` ``"))) == DMibExpr(CStr("\"\\$* \\` \\`\\`\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("\\$x"))) == DMibExpr(CStr("\"\\\\\\$x\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("\\`x"))) == DMibExpr(CStr("\"\\\\\\`x\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("\\x"))) == DMibExpr(CStr("\"\\\\x\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("\"\""))) == DMibExpr(CStr("\"\\\"\\\"\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("Bam Bam"))) == DMibExpr(CStr("\"Bam Bam\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("\"Fred\""))) == DMibExpr(CStr("\"\\\"Fred\\\"\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(CStr("\"Bam\" \"Bam\""))) == DMibExpr(CStr("\"\\\"Bam\\\" \\\"Bam\\\"\"")));
					DMibTest(DMibExpr(fg_StrEscapeBashDoubleQuotes(TestStringDQStart)) == DMibExpr(TestStringDQEnd));

				}
			};
			DMibTestSuite("Recursive Format")
			{
				DMibExpect(CStr(CStr::CFormat("Test {} Test") << (CStr::CFormat("{}") << 55)), ==, "Test 55 Test");
				DMibExpect(CStr(CStr::CFormat("Test {sj10} Test") << (CStr::CFormat("{}") << 55)), ==, "Test         55 Test");
				DMibExpect(CStr(CStr::CFormat("Test {a-,sj10} Test") << (CStr::CFormat("{}") << 55)), ==, "Test 55         Test");
			};
			DMibTestSuite("ByValue")
			{
				{
					DMibTestPath("Move");
					auto fMoveFormat = [](auto _Value) -> CStr::CFormat
						{
							CStr::CFormat Format("{}");
							Format << NMib::fg_ByValue(_Value);
							return NMib::fg_Move(Format);
						}
					;

					DMibExpect(CStr(fMoveFormat(55)), ==, "55");
					DMibExpect(CStr(fMoveFormat(55.5)), ==, "55.5");
					DMibExpect(CStr(fMoveFormat("Test")), ==, "Test");
					DMibExpect(CStr(fMoveFormat(CStr("Test"))), ==, "Test");

					ch8 const *pTest = "Test";
					DMibExpect(CStr(fMoveFormat(pTest)), ==, "Test");

					struct CInlineFormat
					{
						void f_Format(CStr &o_String) const
						{
							o_String += CStr::CFormat("{} {}") << m_Integer << m_String;
						}

						uint32 m_Integer = 44;
						CStr m_String = "Test";
					};

					DMibExpect(CStr(fMoveFormat(CInlineFormat())), ==, "44 Test");
				}
			};
			DMibTestSuite("Expressions")
			{
				{
					DMibTestPath("Logical operators");
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2<3)}") << 0)) == DMibExpr("1"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2<2)}") << 0)) == DMibExpr("0"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(3<2)}") << 0)) == DMibExpr("0"));

					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2<=3)}") << 0)) == DMibExpr("1"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2<=2)}") << 0)) == DMibExpr("1"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(3<=2)}") << 0)) == DMibExpr("0"));

					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(3>2)}") << 0)) == DMibExpr("1"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2>2)}") << 0)) == DMibExpr("0"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2>3)}") << 0)) == DMibExpr("0"));

					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(3>=2)}") << 0)) == DMibExpr("1"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2>=2)}") << 0)) == DMibExpr("1"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2>=3)}") << 0)) == DMibExpr("0"));

					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(3==3)}") << 0)) == DMibExpr("1"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(2==3)}") << 0)) == DMibExpr("0"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(3==2)}") << 0)) == DMibExpr("0"));

					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(!(3>2))}") << 0)) == DMibExpr("0"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("{xpr(!!(3>2))}") << 0)) == DMibExpr("1"));

				}
				{
					DMibTestPath("Bitwise operators");
					DMibTest(DMibExpr(CStr(CStr::CFormat("0b{xpr(0b0010 | 0b0101),nfb,sj4,sf0}") << 0)) == DMibExpr("0b0111"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("0b{xpr(0b0011 & 0b0101),nfb,sj4,sf0}") << 0)) == DMibExpr("0b0001"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("0b{xpr(0b0011 ^ 0b0101),nfb,sj4,sf0}") << 0)) == DMibExpr("0b0110"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("0b{xpr(~(0b0011 ^ 0b0101)),nfb,sj8,sf0}") << uint8(0))) == DMibExpr("0b11111001"));
					DMibTest(DMibExpr(CStr(CStr::CFormat("0b{xpr(~0b0011),nfb,sj8,sf0}") << uint8(0))) == DMibExpr("0b11111100"));
				}
				{
					DMibTestPath("Integer");
					{
						DMibTestPath("Argument lookup");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2)}") << 4)) == DMibExpr("2"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($0/2)}") << 4)) == DMibExpr("2"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($1/2)}") << 4 << 8)) == DMibExpr("4"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($1/$0)}") << 4 << 8)) == DMibExpr("2"));
					}
					{
						DMibTestPath("Errors");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(5 ! 5)}") << 4)) == DMibExpr("| Value without operator |0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($1/2.0)}") << 4)) == DMibExpr("| Argument out of range |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr()}") << 4)) == DMibExpr("| Empty expression |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(}") << 4)) == DMibExpr("| Unrecognized operator } |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(1:4)}") << 4)) == DMibExpr("| Unrecognized operator : |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr}") << 4)) == DMibExpr("| xpr must be within () |0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(($)))}") << 4)) == DMibExpr("| Missing ( or extra characters |0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(/$)}") << 4)) == DMibExpr("| Binary operator without first argument |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(+/$)}") << 4)) == DMibExpr("| Binary operator without first argument |0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(+)}") << 4)) == DMibExpr("| Unmatched unary operator |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/+)}") << 4)) == DMibExpr("| Unmatched unary operator |0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/)}") << 4)) == DMibExpr("| Binary operator without second argument |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(($+$*))}") << 4)) == DMibExpr("| Binary operator without second argument |0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($ $)}") << 4)) == DMibExpr("| Value without operator |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(1 $)}") << 4)) == DMibExpr("| Value without operator |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($ 1)}") << 4)) == DMibExpr("| Value without operator |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($ ($))}") << 4)) == DMibExpr("| Value without operator |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(($) ($))}") << 4)) == DMibExpr("| Value without operator |0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(($) $)}") << 4)) == DMibExpr("| Value without operator |0"));
					}
					{
						DMibTestPath("Whitespace");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr ( $ / 2 * (2 * 2 ) ) }") << 4)) == DMibExpr("8"));
					}
					{
						DMibTestPath("Operators");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($+2)}") << 4)) == DMibExpr("6"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($-2)}") << 4)) == DMibExpr("2"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($*2)}") << 4)) == DMibExpr("8"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2)}") << 4)) == DMibExpr("2"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($%2)}") << 3)) == DMibExpr("1"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(-$)}") << 4)) == DMibExpr("-4"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($+-2)}") << 4)) == DMibExpr("2"));
					}
					{
						DMibTestPath("Complex");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2+($1*2))}") << 4 << 3.0)) == DMibExpr("8"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2+($1*2)-($1*1))}") << 4 << 3.0)) == DMibExpr("5"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2+$1*2-$1*1)}") << 4 << 3.0)) == DMibExpr("5"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2+$1/2%1-$1*1)}") << 4 << 3.0)) == DMibExpr("-1"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($+($+($+($+1))))}") << 4)) == DMibExpr("17"));
					}
					{
						DMibTestPath("FoundInWild");
						{
							CStr A = "Result";
							DMibTest(DMibExpr(fg_ViolatesSafeCheck("reinterpret_cast<void const*>(&_String) != reinterpret_cast<void const*>(&_Value) 'You cannot assign a format to string that is used by reference as an argument.'")) == DMibLExpr( (A = CStr::CFormat("{}{}") << A << "Value")));
						}
					}
				}
				{
					DMibTestPath("Float");
					{
						DMibTestPath("Argument lookup");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2.0)}") << 4.0)) == DMibExpr("2.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($0/2.0)}") << 4.0)) == DMibExpr("2.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($1/2.0)}") << 4.0 << 8.0)) == DMibExpr("4.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($1/$0)}") << 4.0 << 8.0)) == DMibExpr("2.0"));
					}
					{
						DMibTestPath("Errors");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($1/2.0)}") << 4.0)) == DMibExpr("| Argument out of range |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr()}") << 4.0)) == DMibExpr("| Empty expression |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(}") << 4.0)) == DMibExpr("| Unrecognized operator } |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr}") << 4.0)) == DMibExpr("| xpr must be within () |0.0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(($)))}") << 4.0)) == DMibExpr("| Missing ( or extra characters |0.0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(/$)}") << 4.0)) == DMibExpr("| Binary operator without first argument |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(+/$)}") << 4.0)) == DMibExpr("| Binary operator without first argument |0.0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(+)}") << 4.0)) == DMibExpr("| Unmatched unary operator |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/+)}") << 4.0)) == DMibExpr("| Unmatched unary operator |0.0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/)}") << 4.0)) == DMibExpr("| Binary operator without second argument |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(($+$*))}") << 4.0)) == DMibExpr("| Binary operator without second argument |0.0"));

						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($ $)}") << 4.0)) == DMibExpr("| Value without operator |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(1 $)}") << 4.0)) == DMibExpr("| Value without operator |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($ 1)}") << 4.0)) == DMibExpr("| Value without operator |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($ ($))}") << 4.0)) == DMibExpr("| Value without operator |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(($) ($))}") << 4.0)) == DMibExpr("| Value without operator |0.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(($) $)}") << 4.0)) == DMibExpr("| Value without operator |0.0"));
					}
					{
						DMibTestPath("Whitespace");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr ( $ / 2.0 * (2.0 * 2.0 ) ) }") << 4.0)) == DMibExpr("8.0"));
					}
					{
						DMibTestPath("Operators");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($+2.0)}") << 4.0)) == DMibExpr("6.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($-2.0)}") << 4.0)) == DMibExpr("2.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($*2.0)}") << 4.0)) == DMibExpr("8.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2.0)}") << 4.0)) == DMibExpr("2.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($%2.0)}") << 4.5)) == DMibExpr("0.5"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr(-$)}") << 4.0)) == DMibExpr("-4.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($+-2.0)}") << 4.0)) == DMibExpr("2.0"));
					}
					{
						DMibTestPath("Complex");
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2.0+($1*2.0))}") << 4.0 << 3)) == DMibExpr("8.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2.0+($1*2.0)-($1*0.5))}") << 4.0 << 3)) == DMibExpr("6.5"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2.0+$1*2.0-$1*0.5)}") << 4.0 << 3)) == DMibExpr("6.5"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($/2.0+$1/2.0%1.0-$1*0.5)}") << 4.0 << 3)) == DMibExpr("1.0"));
						DMibTest(DMibExpr(CStr(CStr::CFormat("{0,xpr($+($+($+($+1))))}") << 4.0)) == DMibExpr("17.0"));
					}
				}
			};
		}
	};

	DMibTestRegister(CFormat_Tests, Malterlib::String::Container);
}

#endif
