// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/Length>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;
	
	class CLength_Tests : public NMib::NTest::CTest
	{
	public:
		void f_DoTests()
		{
			DMibTestCategory("Normal")
			{
				DMibTestSuite("ANSI")
				{
					DMibExpect(fg_StrLength((ch8 const *)"Char5Char5Char"), ==, 14);
					DMibExpect(fg_StrLength("Char5Char5Char"), ==, 14);
				};
				DMibTestSuite("UTF8")
				{
					DMibExpect(fg_StrLength((ch8 const *)str_utf8("Char5Char5Char")), ==, 14);
					DMibExpect(fg_StrLength((ch8 const *)str_utf8("Char𠀀Char𠀀Char")), ==, 20);
					DMibExpect(fg_StrLength<CUnicode>((ch8 const *)str_utf8("Char𠀀Char𠀀Char")), ==, 14);
					DMibExpect(fg_StrLength(str_utf8("Char5Char5Char")), ==, 14);
					DMibExpect(fg_StrLength(str_utf8("Char𠀀Char𠀀Char")), ==, 20);
					DMibExpect(fg_StrLength<CUnicode>(str_utf8("Char𠀀Char𠀀Char")), ==, 14);
				};
				DMibTestSuite("UTF16")
				{
					DMibExpect(fg_StrLength((ch16 const *)str_utf16("Char5Char5Char")), ==, 14);
					DMibExpect(fg_StrLength((ch16 const *)str_utf16("Char𠀀Char𠀀Char")), ==, 16);
					DMibExpect(fg_StrLength<CUnicode>((ch16 const *)str_utf16("Char𠀀Char𠀀Char")), ==, 14);
					DMibExpect(fg_StrLength(str_utf16("Char5Char5Char")), ==, 14);
					DMibExpect(fg_StrLength(str_utf16("Char𠀀Char𠀀Char")), ==, 16);
					DMibExpect(fg_StrLength<CUnicode>(str_utf16("Char𠀀Char𠀀Char")), ==, 14);
				};
				DMibTestSuite("UTF32")
				{
					DMibExpect(fg_StrLength((ch32 const *)str_utf32("Char5Char5Char")), ==, 14);
					DMibExpect(fg_StrLength((ch32 const *)str_utf32("Char𠀀Char𠀀Char")), ==, 14);
					DMibExpect(fg_StrLength<CUnicode>((ch32 const *)str_utf32("Char𠀀Char𠀀Char")), ==, 14);
					DMibExpect(fg_StrLength(str_utf32("Char5Char5Char")), ==, 14);
					DMibExpect(fg_StrLength(str_utf32("Char𠀀Char𠀀Char")), ==, 14);
					DMibExpect(fg_StrLength<CUnicode>(str_utf32("Char𠀀Char𠀀Char")), ==, 14);
				};
			};
		}
	};

	DMibTestRegister(CLength_Tests, Malterlib::String::Algorithm);
}
