// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/IsAnsi>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;
	
	class CIsAnsi_Tests : public NMib::NTest::CTest
	{
	public:
		void f_DoTests()
		{
			DMibTestCategory("Normal")
			{
				DMibTestSuite("ANSI")
				{
					DMibExpectTrue(fg_StrIsAnsi(fg_Const("Char5Char5Char")));
				};
				DMibTestSuite("UTF8")
				{
					DMibExpectTrue(fg_StrIsAnsi(fg_Const(str_utf8("Char5Char5Char"))));
					DMibExpectFalse(fg_StrIsAnsi(fg_Const(str_utf8("Char𠀀Char𠀀Char"))));
				};
				DMibTestSuite("UTF16")
				{
					DMibExpectTrue(fg_StrIsAnsi(fg_Const(str_utf16("Char5Char5Char"))));
					DMibExpectFalse(fg_StrIsAnsi(fg_Const(str_utf16("Char𠀀Char𠀀Char"))));
				};
				DMibTestSuite("UTF32")
				{
					DMibExpectTrue(fg_StrIsAnsi(fg_Const(str_utf32("Char5Char5Char"))));
					DMibExpectFalse(fg_StrIsAnsi(fg_Const(str_utf32("Char𠀀Char𠀀Char"))));
				};
			};
		}
	};

	DMibTestRegister(CIsAnsi_Tests, Malterlib::String::Algorithm);
}
