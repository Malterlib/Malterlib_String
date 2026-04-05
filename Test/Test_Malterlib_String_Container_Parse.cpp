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
		}
	};

	DMibTestRegister(CGeneral_Tests, Malterlib::String::Parse);
}
