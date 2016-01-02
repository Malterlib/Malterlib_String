// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/Compare>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;

	template <typename tf_CChar>
	tf_CChar const *fg_GetToCompare(mint _Type);

	template <>
	ch8 const *fg_GetToCompare<ch8>(mint _Type)
	{
		switch (_Type)
		{
		case 0: return str_utf8("Char𠀀Char𠀀Char");
		case 1: return str_utf8("Char𠀀Char𠀀Char0");
		case 2: return str_utf8("Char𠀀Char𠀀Char1");
		}
		return str_utf8("");
	}
	template <>
	ch16 const *fg_GetToCompare<ch16>(mint _Type)
	{
		switch (_Type)
		{
		case 0: return str_utf16("Char𠀀Char𠀀Char");
		case 1: return str_utf16("Char𠀀Char𠀀Char0");
		case 2: return str_utf16("Char𠀀Char𠀀Char1");
		}
		return str_utf16("");
	}
	template <>
	ch32 const *fg_GetToCompare<ch32>(mint _Type)
	{
		switch (_Type)
		{
		case 0: return str_utf32("Char𠀀Char𠀀Char");
		case 1: return str_utf32("Char𠀀Char𠀀Char0");
		case 2: return str_utf32("Char𠀀Char𠀀Char1");
		}
		return str_utf32("");
	}

	class CCompare_Tests : public NMib::NTest::CTest
	{
	public:
		
		template <typename tf_CChar>
		void fp_DoTests(NStr::CStr const &_Type)
		{
			DMibTestCategory(_Type)
			{
				auto ToCompare = fg_GetToCompare<tf_CChar>(0);
				auto ToCompare0 = fg_GetToCompare<tf_CChar>(1);
				auto ToCompare1 = fg_GetToCompare<tf_CChar>(2);
				DMibTestCategory("Normal")
				{
					DMibTestSuite("ANSI")
					{
						DMibExpect(fg_StrCompare("Char5Char5Char", "Char5Char5Char1"), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare("Char5Char5Char1", "Char5Char5Char"), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare("Char5Char5Char0", "Char5Char5Char1"), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare("Char5Char5Char1", "Char5Char5Char0"), ==, ECompare_GreaterThan);
						
						{
							auto pArray = "Char65Char5Char";
							DMibExpect(fg_StrCompare(pArray, "Char65Char5Char"), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF8")
					{
						DMibExpect(fg_StrCompare(str_utf8("Char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare(str_utf8("Char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare(str_utf8("Char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare(str_utf8("Char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							DMibExpect(fg_StrCompare(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF16")
					{
						DMibExpect(fg_StrCompare(str_utf16("Char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare(str_utf16("Char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare(str_utf16("Char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare(str_utf16("Char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf16("Char𠀀Char𠀀Char");

							DMibExpect(fg_StrCompare(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF32")
					{
						DMibExpect(fg_StrCompare(str_utf32("Char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare(str_utf32("Char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare(str_utf32("Char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare(str_utf32("Char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf32("Char𠀀Char𠀀Char");

							DMibExpect(fg_StrCompare(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
				};
				DMibTestCategory("NoCase")
				{
					DMibTestSuite("ANSI")
					{
						DMibExpect(fg_StrCompare<CNoCase>("char5Char5Char", "Char5Char5Char1"), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CNoCase>("char5Char5Char1", "Char5Char5Char"), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare<CNoCase>("char5Char5Char0", "Char5Char5Char1"), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CNoCase>("char5Char5Char1", "Char5Char5Char0"), ==, ECompare_GreaterThan);
						
						{
							auto pArray = "char65Char5Char";
							DMibExpect(fg_StrCompare<CNoCase>(pArray, "Char65Char5Char"), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF8")
					{
						DMibExpect(fg_StrCompare<CNoCase>(str_utf8("char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf8("char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf8("char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf8("char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf8("char𠀀Char𠀀Char");
							DMibExpect(fg_StrCompare<CNoCase>(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF16")
					{
						DMibExpect(fg_StrCompare<CNoCase>(str_utf16("char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf16("char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf16("char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf16("char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf16("char𠀀Char𠀀Char");
							DMibExpect(fg_StrCompare<CNoCase>(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF32")
					{
						DMibExpect(fg_StrCompare<CNoCase>(str_utf32("char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf32("char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf32("char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CNoCase>(str_utf32("char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf32("char𠀀Char𠀀Char");
							DMibExpect(fg_StrCompare<CNoCase>(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
				};
				DMibTestCategory("Reverse")
				{
					DMibTestSuite("ANSI")
					{
						DMibExpect(fg_StrCompare<CReverse>("Char5Char5Char", "Char5Char5Char1"), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare<CReverse>("Char5Char5Char1", "Char5Char5Char"), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CReverse>("Char5Char5Char0", "Char5Char5Char1"), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CReverse>("Char5Char5Char1", "Char5Char5Char0"), ==, ECompare_GreaterThan);
						
						{
							auto pArray = "Char65Char5Char";
							DMibExpect(fg_StrCompare<CReverse>(pArray, "Char65Char5Char"), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF8")
					{
						DMibExpect(fg_StrCompare<CReverse>(str_utf8("Char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf8("Char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf8("Char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf8("Char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							DMibExpect(fg_StrCompare<CReverse>(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF16")
					{
						DMibExpect(fg_StrCompare<CReverse>(str_utf16("Char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf16("Char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf16("Char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf16("Char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf16("Char𠀀Char𠀀Char");

							DMibExpect(fg_StrCompare<CReverse>(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF32")
					{
						DMibExpect(fg_StrCompare<CReverse>(str_utf32("Char𠀀Char𠀀Char"), ToCompare1), ==, ECompare_GreaterThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf32("Char𠀀Char𠀀Char1"), ToCompare), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf32("Char𠀀Char𠀀Char0"), ToCompare1), ==, ECompare_LessThan);
						DMibExpect(fg_StrCompare<CReverse>(str_utf32("Char𠀀Char𠀀Char1"), ToCompare0), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf32("Char𠀀Char𠀀Char");

							DMibExpect(fg_StrCompare<CReverse>(pArray, ToCompare), ==, ECompare_Equal);
						}
					};
				};
				DMibTestCategory("ReverseNoCase")
				{
					DMibTestSuite("ANSI")
					{
						DMibExpect((fg_StrCompare<CReverse, CNoCase>("char5Char5Char", "Char5Char5Char1")), ==, ECompare_GreaterThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>("char5Char5Char1", "Char5Char5Char")), ==, ECompare_LessThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>("char5Char5Char0", "Char5Char5Char1")), ==, ECompare_LessThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>("char5Char5Char1", "Char5Char5Char0")), ==, ECompare_GreaterThan);
						
						{
							auto pArray = "char65Char5Char";
							DMibExpect((fg_StrCompare<CReverse, CNoCase>(pArray, "Char65Char5Char")), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF8")
					{
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf8("char𠀀Char𠀀Char"), ToCompare1)), ==, ECompare_GreaterThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf8("char𠀀Char𠀀Char1"), ToCompare)), ==, ECompare_LessThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf8("char𠀀Char𠀀Char0"), ToCompare1)), ==, ECompare_LessThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf8("char𠀀Char𠀀Char1"), ToCompare0)), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf8("char𠀀Char𠀀Char");
							DMibExpect((fg_StrCompare<CReverse, CNoCase>(pArray, ToCompare)), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF16")
					{
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf16("char𠀀Char𠀀Char"), ToCompare1)), ==, ECompare_GreaterThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf16("char𠀀Char𠀀Char1"), ToCompare)), ==, ECompare_LessThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf16("char𠀀Char𠀀Char0"), ToCompare1)), ==, ECompare_LessThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf16("char𠀀Char𠀀Char1"), ToCompare0)), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf16("char𠀀Char𠀀Char");
							DMibExpect((fg_StrCompare<CReverse, CNoCase>(pArray, ToCompare)), ==, ECompare_Equal);
						}
					};
					DMibTestSuite("UTF32")
					{
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf32("char𠀀Char𠀀Char"), ToCompare1)), ==, ECompare_GreaterThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf32("char𠀀Char𠀀Char1"), ToCompare)), ==, ECompare_LessThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf32("char𠀀Char𠀀Char0"), ToCompare1)), ==, ECompare_LessThan);
						DMibExpect((fg_StrCompare<CReverse, CNoCase>(str_utf32("char𠀀Char𠀀Char1"), ToCompare0)), ==, ECompare_GreaterThan);
						
						{
							auto pArray = str_utf32("char𠀀Char𠀀Char");
							DMibExpect((fg_StrCompare<CReverse, CNoCase>(pArray, ToCompare)), ==, ECompare_Equal);
						}
					};
				};
			};
		}
		void f_DoTests()
		{
			fp_DoTests<ch8>("UTF8");
			fp_DoTests<ch16>("UTF16");
			fp_DoTests<ch32>("UTF32");
		}
	};

	DMibTestRegister(CCompare_Tests, Malterlib::String::Algorithm);
}
