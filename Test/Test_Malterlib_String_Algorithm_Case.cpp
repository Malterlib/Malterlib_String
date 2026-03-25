// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/String>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;

	template <typename tf_CChar>
	struct CStrType;

	template <>
	struct CStrType<ch8>
	{
		using CType = CStr;
	};

	template <>
	struct CStrType<ch16>
	{
		using CType = CWStr;
	};

	template <>
	struct CStrType<ch32>
	{
		using CType = CUStr;
	};

	struct CCase_Tests : public NMib::NTest::CTest
	{
		template <typename tf_CChar>
		void fp_StrUpperCaseTests()
		{
			using CString = typename CStrType<tf_CChar>::CType;

			DMibTestCategory("StrUpperCase")
			{
				{
					DMibTestPath("ASCII");
					tf_CChar Buffer[32];
					fg_StrCopy(Buffer, "hello world");
					fg_StrUpperCase(Buffer);
					DMibExpect(CString(Buffer), ==, CString("HELLO WORLD"));
				}
				{
					DMibTestPath("Latin1");
					tf_CChar Buffer[32];
					tf_CChar const Source[] = {(tf_CChar)0xe0, (tf_CChar)0xe1, (tf_CChar)0xe4, (tf_CChar)0xf1, (tf_CChar)0xfe, 0};
					tf_CChar const Expected[] = {(tf_CChar)0xc0, (tf_CChar)0xc1, (tf_CChar)0xc4, (tf_CChar)0xd1, (tf_CChar)0xde, 0};
					fg_StrCopy(Buffer, Source);
					fg_StrUpperCase(Buffer);
					DMibExpect(CString(Buffer), ==, CString(Expected));
				}
				{
					DMibTestPath("DivisionSign_Unchanged");
					tf_CChar Buffer[32];
					tf_CChar const Source[] = {'a', (tf_CChar)0xf7, 'b', 0};
					tf_CChar const Expected[] = {'A', (tf_CChar)0xf7, 'B', 0};
					fg_StrCopy(Buffer, Source);
					fg_StrUpperCase(Buffer);
					DMibExpect(CString(Buffer), ==, CString(Expected));
				}
				{
					DMibTestPath("Mixed");
					tf_CChar const Source[] = {'H', (tf_CChar)0xe9, 'l', 'l', (tf_CChar)0xf6, 0};
					tf_CChar const Expected[] = {'H', (tf_CChar)0xc9, 'L', 'L', (tf_CChar)0xd6, 0};
					tf_CChar Buffer[32];
					fg_StrCopy(Buffer, Source);
					fg_StrUpperCase(Buffer);
					DMibExpect(CString(Buffer), ==, CString(Expected));
				}
			};
		}

		template <typename tf_CChar>
		void fp_StrLowerCaseTests()
		{
			using CString = typename CStrType<tf_CChar>::CType;

			DMibTestCategory("StrLowerCase")
			{
				{
					DMibTestPath("ASCII");
					tf_CChar Buffer[32];
					fg_StrCopy(Buffer, "HELLO WORLD");
					fg_StrLowerCase(Buffer);
					DMibExpect(CString(Buffer), ==, CString("hello world"));
				}
				{
					DMibTestPath("Latin1");
					tf_CChar Buffer[32];
					tf_CChar const Source[] = {(tf_CChar)0xc0, (tf_CChar)0xc1, (tf_CChar)0xc4, (tf_CChar)0xd1, (tf_CChar)0xde, 0};
					tf_CChar const Expected[] = {(tf_CChar)0xe0, (tf_CChar)0xe1, (tf_CChar)0xe4, (tf_CChar)0xf1, (tf_CChar)0xfe, 0};
					fg_StrCopy(Buffer, Source);
					fg_StrLowerCase(Buffer);
					DMibExpect(CString(Buffer), ==, CString(Expected));
				}
				{
					DMibTestPath("MultiplicationSign_Unchanged");
					tf_CChar Buffer[32];
					tf_CChar const Source[] = {'A', (tf_CChar)0xd7, 'B', 0};
					tf_CChar const Expected[] = {'a', (tf_CChar)0xd7, 'b', 0};
					fg_StrCopy(Buffer, Source);
					fg_StrLowerCase(Buffer);
					DMibExpect(CString(Buffer), ==, CString(Expected));
				}
				{
					DMibTestPath("Mixed");
					tf_CChar const Source[] = {'H', (tf_CChar)0xc9, 'L', 'L', (tf_CChar)0xd6, 0};
					tf_CChar const Expected[] = {'h', (tf_CChar)0xe9, 'l', 'l', (tf_CChar)0xf6, 0};
					tf_CChar Buffer[32];
					fg_StrCopy(Buffer, Source);
					fg_StrLowerCase(Buffer);
					DMibExpect(CString(Buffer), ==, CString(Expected));
				}
			};
		}

		template <typename tf_CChar>
		void fp_StrCapitalizeTests()
		{
			using CString = typename CStrType<tf_CChar>::CType;

			DMibTestCategory("StrCapitalize")
			{
				{
					DMibTestPath("ASCII");
					tf_CChar Buffer[32];
					fg_StrCopy(Buffer, "hello");
					fg_StrCapitalize(Buffer);
					DMibExpect(CString(Buffer), ==, CString("Hello"));
				}
				{
					DMibTestPath("Latin1");
					tf_CChar const Source[] = {(tf_CChar)0xe9, 'c', 'o', 'l', 'e', 0};
					tf_CChar const Expected[] = {(tf_CChar)0xc9, 'c', 'o', 'l', 'e', 0};
					tf_CChar Buffer[32];
					fg_StrCopy(Buffer, Source);
					fg_StrCapitalize(Buffer);
					DMibExpect(CString(Buffer), ==, CString(Expected));
				}
				{
					DMibTestPath("DivisionSign_Unchanged");
					tf_CChar const Source[] = {(tf_CChar)0xf7, 'a', 'b', 0};
					tf_CChar Buffer[32];
					fg_StrCopy(Buffer, Source);
					fg_StrCapitalize(Buffer);
					DMibExpect(CString(Buffer), ==, CString(Source));
				}
			};
		}

		void fp_StrUpperCaseUTF8Tests()
		{
			DMibTestCategory("StrUpperCase_UTF8")
			{
				{
					DMibTestPath("ASCII");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, "hello");
					fg_StrUpperCase(Buffer);
					DMibExpect(CStr(Buffer), ==, "HELLO");
				}
				{
					DMibTestPath("Latin1");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, str_utf8("àñþ"));
					fg_StrUpperCase(Buffer);
					DMibExpect(CStr(Buffer), ==, str_utf8("ÀÑÞ"));
				}
				{
					DMibTestPath("DivisionSign_Unchanged");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, str_utf8("a÷b"));
					fg_StrUpperCase(Buffer);
					DMibExpect(CStr(Buffer), ==, str_utf8("A÷B"));
				}
			};
		}

		void fp_StrLowerCaseUTF8Tests()
		{
			DMibTestCategory("StrLowerCase_UTF8")
			{
				{
					DMibTestPath("ASCII");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, "HELLO");
					fg_StrLowerCase(Buffer);
					DMibExpect(CStr(Buffer), ==, "hello");
				}
				{
					DMibTestPath("Latin1");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, str_utf8("ÀÑÞ"));
					fg_StrLowerCase(Buffer);
					DMibExpect(CStr(Buffer), ==, str_utf8("àñþ"));
				}
				{
					DMibTestPath("MultiplicationSign_Unchanged");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, str_utf8("A×B"));
					fg_StrLowerCase(Buffer);
					DMibExpect(CStr(Buffer), ==, str_utf8("a×b"));
				}
			};
		}

		void fp_StrCapitalizeUTF8Tests()
		{
			DMibTestCategory("StrCapitalize_UTF8")
			{
				{
					DMibTestPath("ASCII");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, "hello");
					fg_StrCapitalize(Buffer);
					DMibExpect(CStr(Buffer), ==, "Hello");
				}
				{
					DMibTestPath("Latin1");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, str_utf8("àbc"));
					fg_StrCapitalize(Buffer);
					DMibExpect(CStr(Buffer), ==, str_utf8("Àbc"));
				}
				{
					DMibTestPath("DivisionSign_Unchanged");
					ch8 Buffer[32];
					fg_StrCopy(Buffer, str_utf8("÷ab"));
					fg_StrCapitalize(Buffer);
					DMibExpect(CStr(Buffer), ==, str_utf8("÷ab"));
				}
			};
		}

		void fp_ContainerTests()
		{
			DMibTestCategory("Container")
			{
				DMibTestCategory("CStr")
				{
					{
						DMibTestPath("UpperCase");
						DMibExpect(CStr("hello").f_UpperCase(), ==, "HELLO");
					}
					{
						DMibTestPath("UpperCase_Latin1");
						DMibExpect(CStr(str_utf8("àñþ")).f_UpperCase(), ==, str_utf8("ÀÑÞ"));
					}
					{
						DMibTestPath("UpperCase_DivisionSign");
						DMibExpect(CStr(str_utf8("a÷b")).f_UpperCase(), ==, str_utf8("A÷B"));
					}
					{
						DMibTestPath("LowerCase");
						DMibExpect(CStr("HELLO").f_LowerCase(), ==, "hello");
					}
					{
						DMibTestPath("LowerCase_Latin1");
						DMibExpect(CStr(str_utf8("ÀÑÞ")).f_LowerCase(), ==, str_utf8("àñþ"));
					}
					{
						DMibTestPath("LowerCase_MultiplicationSign");
						DMibExpect(CStr(str_utf8("A×B")).f_LowerCase(), ==, str_utf8("a×b"));
					}
				};
				DMibTestCategory("CWStr")
				{
					{
						DMibTestPath("UpperCase");
						DMibExpect(CWStr("hello").f_UpperCase(), ==, CWStr("HELLO"));
					}
					{
						DMibTestPath("UpperCase_Latin1");
						DMibExpect(CWStr(str_utf16("àñþ")).f_UpperCase(), ==, CWStr(str_utf16("ÀÑÞ")));
					}
					{
						DMibTestPath("UpperCase_DivisionSign");
						DMibExpect(CWStr(str_utf16("a÷b")).f_UpperCase(), ==, CWStr(str_utf16("A÷B")));
					}
					{
						DMibTestPath("LowerCase");
						DMibExpect(CWStr("HELLO").f_LowerCase(), ==, CWStr("hello"));
					}
					{
						DMibTestPath("LowerCase_Latin1");
						DMibExpect(CWStr(str_utf16("ÀÑÞ")).f_LowerCase(), ==, CWStr(str_utf16("àñþ")));
					}
					{
						DMibTestPath("LowerCase_MultiplicationSign");
						DMibExpect(CWStr(str_utf16("A×B")).f_LowerCase(), ==, CWStr(str_utf16("a×b")));
					}
				};
				DMibTestCategory("CUStr")
				{
					{
						DMibTestPath("UpperCase");
						DMibExpect(CUStr("hello").f_UpperCase(), ==, CUStr("HELLO"));
					}
					{
						DMibTestPath("UpperCase_Latin1");
						DMibExpect(CUStr(str_utf32("àñþ")).f_UpperCase(), ==, CUStr(str_utf32("ÀÑÞ")));
					}
					{
						DMibTestPath("UpperCase_DivisionSign");
						DMibExpect(CUStr(str_utf32("a÷b")).f_UpperCase(), ==, CUStr(str_utf32("A÷B")));
					}
					{
						DMibTestPath("LowerCase");
						DMibExpect(CUStr("HELLO").f_LowerCase(), ==, CUStr("hello"));
					}
					{
						DMibTestPath("LowerCase_Latin1");
						DMibExpect(CUStr(str_utf32("ÀÑÞ")).f_LowerCase(), ==, CUStr(str_utf32("àñþ")));
					}
					{
						DMibTestPath("LowerCase_MultiplicationSign");
						DMibExpect(CUStr(str_utf32("A×B")).f_LowerCase(), ==, CUStr(str_utf32("a×b")));
					}
				};
			};
		}

		void f_DoTests()
		{
			DMibTestSuite("Case")
			{
				DMibTestCategory("ch16")
				{
					fp_StrUpperCaseTests<ch16>();
					fp_StrLowerCaseTests<ch16>();
					fp_StrCapitalizeTests<ch16>();
				};
				DMibTestCategory("ch32")
				{
					fp_StrUpperCaseTests<ch32>();
					fp_StrLowerCaseTests<ch32>();
					fp_StrCapitalizeTests<ch32>();
				};
				DMibTestCategory("ch8")
				{
					fp_StrUpperCaseUTF8Tests();
					fp_StrLowerCaseUTF8Tests();
					fp_StrCapitalizeUTF8Tests();
				};
				fp_ContainerTests();
			};
		}
	};

	DMibTestRegister(CCase_Tests, Malterlib::String::Algorithm::Case);
}
