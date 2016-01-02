// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/IsEmpty>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;
	
	class CIsEmpty_Tests : public NMib::NTest::CTest
	{
	public:
		void f_DoTests()
		{
			DMibTestCategory("Normal")
			{
				DMibTestSuite("ANSI")
				{
					DMibExpectFalse(fg_StrIsEmpty("Char5Char5Char"));
					DMibExpectTrue(fg_StrIsEmpty(""));
					DMibExpectFalse(fg_StrIsEmpty((ch8 const *)"Char5Char5Char"));
					DMibExpectTrue(fg_StrIsEmpty((ch8 const *)""));
				};
				DMibTestSuite("UTF8")
				{
					DMibExpectFalse(fg_StrIsEmpty(str_utf8("Char𠀀Char𠀀Char")));
					DMibExpectTrue(fg_StrIsEmpty(str_utf8("")));
					DMibExpectFalse(fg_StrIsEmpty((ch8 const *)str_utf8("Char𠀀Char𠀀Char")));
					DMibExpectTrue(fg_StrIsEmpty((ch8 const *)str_utf8("")));
				};
				DMibTestSuite("UTF16")
				{
					DMibExpectFalse(fg_StrIsEmpty(str_utf16("Char𠀀Char𠀀Char")));
					DMibExpectTrue(fg_StrIsEmpty(str_utf16("")));
					DMibExpectFalse(fg_StrIsEmpty((ch16 const *)str_utf16("Char𠀀Char𠀀Char")));
					DMibExpectTrue(fg_StrIsEmpty((ch16 const *)str_utf16("")));
				};
				DMibTestSuite("UTF32")
				{
					DMibExpectFalse(fg_StrIsEmpty(str_utf32("Char𠀀Char𠀀Char")));
					DMibExpectTrue(fg_StrIsEmpty(str_utf32("")));
					DMibExpectFalse(fg_StrIsEmpty((ch32 const *)str_utf32("Char𠀀Char𠀀Char")));
					DMibExpectTrue(fg_StrIsEmpty((ch32 const *)str_utf32("")));
				};
			};
		}
	};

	DMibTestRegister(CIsEmpty_Tests, Malterlib::String::Algorithm);
}
