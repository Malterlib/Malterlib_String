// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/EndsWith>

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

	class CEndsWith_Tests : public NMib::NTest::CTest
	{
	public:

		template <typename tf_CChar>
		void fp_DoTests(NStr::CStr const &_Type)
		{
			DMibTestSuite(_Type)
			{
				auto ToCompare = fg_GetToCompare<tf_CChar>(0);
				[[maybe_unused]] auto ToCompare0 = fg_GetToCompare<tf_CChar>(1);
				auto ToCompare1 = fg_GetToCompare<tf_CChar>(2);
				{
					DMibTestPath("Normal");
					{
						DMibTestPath("ANSI");
						DMibExpectFalse(fg_StrEndsWith("Char5Char5Char", "Char5Char5Char1"));
						DMibExpectTrue(fg_StrEndsWith("55Char5Char5Char", "Char5Char5Char"));
					}
					{
						DMibTestPath("UTF8");
						DMibExpectFalse(fg_StrEndsWith(str_utf8("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith(str_utf8("55Char𠀀Char𠀀Char"), ToCompare));
					}
					{
						DMibTestPath("UTF16");
						DMibExpectFalse(fg_StrEndsWith(str_utf16("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith(str_utf16("55Char𠀀Char𠀀Char"), ToCompare));
					}
					{
						DMibTestPath("UTF32");
						DMibExpectFalse(fg_StrEndsWith(str_utf32("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith(str_utf32("55Char𠀀Char𠀀Char"), ToCompare));
					}
				}
				{
					DMibTestPath("NoCase");
					{
						DMibTestPath("ANSI");
						DMibExpectFalse(fg_StrEndsWith<CNoCase>("char5Char5Char", "Char5Char5Char1"));
						DMibExpectTrue(fg_StrEndsWith<CNoCase>("55char5Char5Char", "Char5Char5Char"));
					}
					{
						DMibTestPath("UTF8");
						DMibExpectFalse(fg_StrEndsWith<CNoCase>(str_utf8("char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith<CNoCase>(str_utf8("55char𠀀Char𠀀Char"), ToCompare));
					}
					{
						DMibTestPath("UTF16");
						DMibExpectFalse(fg_StrEndsWith<CNoCase>(str_utf16("char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith<CNoCase>(str_utf16("55char𠀀Char𠀀Char"), ToCompare));
					}
					{
						DMibTestPath("UTF32");
						DMibExpectFalse(fg_StrEndsWith<CNoCase>(str_utf32("char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith<CNoCase>(str_utf32("55char𠀀Char𠀀Char"), ToCompare));
					}
				}
				{
					DMibTestPath("Reverse");
					{
						DMibTestPath("ANSI");
						DMibExpectFalse(fg_StrEndsWith<CReverse>("Char5Char5Char", "Char5Char5Char1"));
						DMibExpectTrue(fg_StrEndsWith<CReverse>("Char5Char5Char1", "Char5Char5Char"));
					}
					{
						DMibTestPath("UTF8");
						DMibExpectFalse(fg_StrEndsWith<CReverse>(str_utf8("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith<CReverse>(str_utf8("Char𠀀Char𠀀Char1"), ToCompare));
					}
					{
						DMibTestPath("UTF16");
						DMibExpectFalse(fg_StrEndsWith<CReverse>(str_utf16("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith<CReverse>(str_utf16("Char𠀀Char𠀀Char1"), ToCompare));
					}
					{
						DMibTestPath("UTF32");
						DMibExpectFalse(fg_StrEndsWith<CReverse>(str_utf32("Char𠀀Char𠀀Char"), ToCompare1));
						DMibExpectTrue(fg_StrEndsWith<CReverse>(str_utf32("Char𠀀Char𠀀Char1"), ToCompare));
					}
				}
				{
					DMibTestPath("ReverseNoCase");
					{
						DMibTestPath("ANSI");
						DMibExpectFalse((fg_StrEndsWith<CReverse, CNoCase>("char5Char5Char", "Char5Char5Char1")));
						DMibExpectTrue((fg_StrEndsWith<CReverse, CNoCase>("char5Char5Char11", "Char5Char5Char")));
					}
					{
						DMibTestPath("UTF8");
						DMibExpectFalse((fg_StrEndsWith<CReverse, CNoCase>(str_utf8("char𠀀Char𠀀Char"), ToCompare1)));
						DMibExpectTrue((fg_StrEndsWith<CReverse, CNoCase>(str_utf8("char𠀀Char𠀀Char1"), ToCompare)));
					}
					{
						DMibTestPath("UTF16");
						DMibExpectFalse((fg_StrEndsWith<CReverse, CNoCase>(str_utf16("char𠀀Char𠀀Char"), ToCompare1)));
						DMibExpectTrue((fg_StrEndsWith<CReverse, CNoCase>(str_utf16("char𠀀Char𠀀Char1"), ToCompare)));
					}
					{
						DMibTestPath("UTF32");
						DMibExpectFalse((fg_StrEndsWith<CReverse, CNoCase>(str_utf32("char𠀀Char𠀀Char"), ToCompare1)));
						DMibExpectTrue((fg_StrEndsWith<CReverse, CNoCase>(str_utf32("char𠀀Char𠀀Char1"), ToCompare)));
					}
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

	DMibTestRegister(CEndsWith_Tests, Malterlib::String::Algorithm);
}
