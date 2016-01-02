// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/HashSDBM>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;
	
	class CHashSDBM_Tests : public NMib::NTest::CTest
	{
	public:
		void f_DoTests()
		{
			DMibTestCategory("Normal")
			{
				DMibTestSuite("ANSI")
				{
					DMibExpect(fg_StrHashSDBM("Char5Char5Char"), ==, 1661838710);
				};
				DMibTestSuite("UTF8")
				{
					DMibExpect(fg_StrHashSDBM(str_utf8("Char5Char5Char")), ==, 1661838710);
					DMibExpect(fg_StrHashSDBM(str_utf8("Char𠀀Char𠀀Char")), ==, 3265238914);
				};
				DMibTestSuite("UTF16")
				{
					DMibExpect(fg_StrHashSDBM(str_utf16("Char5Char5Char")), ==, 1661838710);
					DMibExpect(fg_StrHashSDBM(str_utf16("Char𠀀Char𠀀Char")), ==, 3265238914);
				};
				DMibTestSuite("UTF32")
				{
					DMibExpect(fg_StrHashSDBM(str_utf32("Char5Char5Char")), ==, 1661838710);
					DMibExpect(fg_StrHashSDBM(str_utf32("Char𠀀Char𠀀Char")), ==, 3265238914);
				};
			};
		}
	};

	DMibTestRegister(CHashSDBM_Tests, Malterlib::String::Algorithm);
}
