// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/StartsWith>

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

	class CStartsWith_Tests : public NMib::NTest::CTest
	{
	public:
		
		template <typename tf_CChar>
		void fp_DoTests(NStr::CStr const &_Type)
		{
			DMibTestCategory(_Type)
			{
				auto ToCompare = fg_GetToCompare<tf_CChar>(0);
				[[maybe_unused]] auto ToCompare0 = fg_GetToCompare<tf_CChar>(1);
				auto ToCompare1 = fg_GetToCompare<tf_CChar>(2);
				DMibTestCategory("Normal")
				{
					DMibTestSuite("ANSI")
					{
						DMibExpectFalse(fg_StrStartsWith("Char5Char5Char", "Char5Char5Char1"));
						DMibExpectTrue(fg_StrStartsWith("Char5Char5Char1", "Char5Char5Char"));
					};
					DMibTestSuite("UTF8")
					{
						DMibExpectFalse(fg_StrStartsWith(str_utf8("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith(str_utf8("Char𠀀Char𠀀Char1"), ToCompare));
					};
					DMibTestSuite("UTF16")
					{
						DMibExpectFalse(fg_StrStartsWith(str_utf16("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith(str_utf16("Char𠀀Char𠀀Char1"), ToCompare));
					};
					DMibTestSuite("UTF32")
					{
						DMibExpectFalse(fg_StrStartsWith(str_utf32("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith(str_utf32("Char𠀀Char𠀀Char1"), ToCompare));
					};
				};
				DMibTestCategory("NoCase")
				{
					DMibTestSuite("ANSI")
					{
						DMibExpectFalse(fg_StrStartsWith<CNoCase>("char5Char5Char", "Char5Char5Char1"));
						DMibExpectTrue(fg_StrStartsWith<CNoCase>("char5Char5Char1", "Char5Char5Char"));
					};
					DMibTestSuite("UTF8")
					{
						DMibExpectFalse(fg_StrStartsWith<CNoCase>(str_utf8("char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith<CNoCase>(str_utf8("char𠀀Char𠀀Char1"), ToCompare));
					};
					DMibTestSuite("UTF16")
					{
						DMibExpectFalse(fg_StrStartsWith<CNoCase>(str_utf16("char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith<CNoCase>(str_utf16("char𠀀Char𠀀Char1"), ToCompare));
					};
					DMibTestSuite("UTF32")
					{
						DMibExpectFalse(fg_StrStartsWith<CNoCase>(str_utf32("char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith<CNoCase>(str_utf32("char𠀀Char𠀀Char1"), ToCompare));
					};
				};
				DMibTestCategory("Reverse")
				{
					DMibTestSuite("ANSI")
					{
						DMibExpectFalse(fg_StrStartsWith<CReverse>("Char5Char5Char", "Char5Char5Char1"));
						DMibExpectTrue(fg_StrStartsWith<CReverse>("55Char5Char5Char", "Char5Char5Char"));
					};
					DMibTestSuite("UTF8")
					{
						DMibExpectFalse(fg_StrStartsWith<CReverse>(str_utf8("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith<CReverse>(str_utf8("55Char𠀀Char𠀀Char"), ToCompare));
					};
					DMibTestSuite("UTF16")
					{
						DMibExpectFalse(fg_StrStartsWith<CReverse>(str_utf16("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith<CReverse>(str_utf16("55Char𠀀Char𠀀Char"), ToCompare));
					};
					DMibTestSuite("UTF32")
					{
						DMibExpectFalse(fg_StrStartsWith<CReverse>(str_utf32("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrStartsWith<CReverse>(str_utf32("55Char𠀀Char𠀀Char"), ToCompare));
					};
				};
				DMibTestCategory("ReverseNoCase")
				{
					DMibTestSuite("ANSI")
					{
						DMibExpectFalse((fg_StrStartsWith<CReverse, CNoCase>("char5Char5Char", "Char5Char5Char1")));
						DMibExpectTrue((fg_StrStartsWith<CReverse, CNoCase>("55char5Char5Char", "Char5Char5Char")));
					};
					DMibTestSuite("UTF8")
					{
						DMibExpectFalse((fg_StrStartsWith<CReverse, CNoCase>(str_utf8("char𠀀Char𠀀Char"), ToCompare1)));
						DMibExpectTrue((fg_StrStartsWith<CReverse, CNoCase>(str_utf8("55char𠀀Char𠀀Char"), ToCompare)));
					};
					DMibTestSuite("UTF16")
					{
						DMibExpectFalse((fg_StrStartsWith<CReverse, CNoCase>(str_utf16("char𠀀Char𠀀Char"), ToCompare1)));
						DMibExpectTrue((fg_StrStartsWith<CReverse, CNoCase>(str_utf16("55char𠀀Char𠀀Char"), ToCompare)));
					};
					DMibTestSuite("UTF32")
					{
						DMibExpectFalse((fg_StrStartsWith<CReverse, CNoCase>(str_utf32("char𠀀Char𠀀Char"), ToCompare1)));
						DMibExpectTrue((fg_StrStartsWith<CReverse, CNoCase>(str_utf32("55char𠀀Char𠀀Char"), ToCompare)));
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

	DMibTestRegister(CStartsWith_Tests, Malterlib::String::Algorithm);
}
