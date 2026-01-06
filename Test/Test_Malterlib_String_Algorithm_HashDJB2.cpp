// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/HashDJB2>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;

	class CHashDJB2_Tests : public NMib::NTest::CTest
	{
	public:
		void f_DoTests()
		{
			DMibTestSuite("Normal")
			{
				{
					DMibTestPath("ANSI");
					DMibExpect(fg_StrHashDJB2("Char5Char5Char"), ==, 1114821321);
				}
				{
					DMibTestPath("UTF8");
					DMibExpect(fg_StrHashDJB2(str_utf8("Char5Char5Char")), ==, 1114821321);
					DMibExpect(fg_StrHashDJB2(str_utf8("Char𠀀Char𠀀Char")), ==, 2297850591);
				}
				{
					DMibTestPath("UTF16");
					DMibExpect(fg_StrHashDJB2(str_utf16("Char5Char5Char")), ==, 1114821321);
					DMibExpect(fg_StrHashDJB2(str_utf16("Char𠀀Char𠀀Char")), ==, 2297850591);
				}
				{
					DMibTestPath("UTF32");
					DMibExpect(fg_StrHashDJB2(str_utf32("Char5Char5Char")), ==, 1114821321);
					DMibExpect(fg_StrHashDJB2(str_utf32("Char𠀀Char𠀀Char")), ==, 2297850591);
				}
			};
		}
	};

	DMibTestRegister(CHashDJB2_Tests, Malterlib::String::Algorithm);
}
