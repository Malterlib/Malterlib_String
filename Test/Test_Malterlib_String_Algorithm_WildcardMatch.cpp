// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/WildcardMatch>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;

	template <typename tf_CChar>
	tf_CChar const *fg_GetToWildcardMatch(mint _Type);

	template <>
	ch8 const *fg_GetToWildcardMatch<ch8>(mint _Type)
	{
		switch (_Type)
		{
		case 0: return str_utf8("?????Ch*𠀀*ar");
		case 1: return str_utf8("?????Ch*𠀀*ar1");
		case 2: return str_utf8("?????Ch*𠀀*ar");
		}
		return str_utf8("");
	}
	template <>
	ch16 const *fg_GetToWildcardMatch<ch16>(mint _Type)
	{
		switch (_Type)
		{
		case 0: return str_utf16("?????Ch*𠀀*ar");
		case 1: return str_utf16("?????Ch*𠀀*ar1");
		case 2: return str_utf16("?????Ch*𠀀*ar");
		}
		return str_utf16("");
	}
	template <>
	ch32 const *fg_GetToWildcardMatch<ch32>(mint _Type)
	{
		switch (_Type)
		{
		case 0: return str_utf32("?????Ch*𠀀*ar");
		case 1: return str_utf32("?????Ch*𠀀*ar1");
		case 2: return str_utf32("?????Ch*𠀀*ar");
		}
		return str_utf32("");
	}

	class CWildcardMatch_Tests : public NMib::NTest::CTest
	{
	public:

		template <typename tf_CChar>
		void fp_DoTests(NStr::CStr const &_Type)
		{
			DMibTestSuite(_Type)
			{
				auto ToWildcardMatch0 = fg_GetToWildcardMatch<tf_CChar>(0);
				auto ToWildcardMatch1 = fg_GetToWildcardMatch<tf_CChar>(1);
				auto ToWildcardMatch2 = fg_GetToWildcardMatch<tf_CChar>(2);
				{
					DMibTestPath("Normal");
					{
						DMibTestPath("ANSI");
						DMibExpect(fg_StrWildcardMatch("Char5Char5Char", "?????Ch*5*ar"), ==, EWildcardMatch_WholeStringMatchedAndPatternExhausted);
						DMibExpect(fg_StrWildcardMatch("Char5Char5Char", "?????Ch*5*ar1"), ==, EWildcardMatch_WholeStringMatched);
						DMibExpect(fg_StrWildcardMatch("Char5Char5Char1", "?????Ch*5*ar"), ==, EWildcardMatch_PatternExhausted);
						DMibExpect(fg_StrWildcardMatch("Char5Char5Char13", "?????Ch*5*ar?2"), ==, EWildcardMatch_NotMatched);
					}
					{
						DMibTestPath("UTF8");
						DMibExpect(fg_StrWildcardMatch(str_utf8("Char𠀀Char𠀀Char"), ToWildcardMatch0), ==, EWildcardMatch_WholeStringMatchedAndPatternExhausted);
						DMibExpect(fg_StrWildcardMatch(str_utf8("Char𠀀Char𠀀Char"), ToWildcardMatch1), ==, EWildcardMatch_WholeStringMatched);
						DMibExpect(fg_StrWildcardMatch(str_utf8("Char𠀀Char𠀀Char1"), ToWildcardMatch2), ==, EWildcardMatch_PatternExhausted);
					}
					{
						DMibTestPath("UTF16");
						DMibExpect(fg_StrWildcardMatch(str_utf16("Char𠀀Char𠀀Char"), ToWildcardMatch0), ==, EWildcardMatch_WholeStringMatchedAndPatternExhausted);
						DMibExpect(fg_StrWildcardMatch(str_utf16("Char𠀀Char𠀀Char"), ToWildcardMatch1), ==, EWildcardMatch_WholeStringMatched);
						DMibExpect(fg_StrWildcardMatch(str_utf16("Char𠀀Char𠀀Char1"), ToWildcardMatch2), ==, EWildcardMatch_PatternExhausted);
					}
					{
						DMibTestPath("UTF32");
						DMibExpect(fg_StrWildcardMatch(str_utf32("Char𠀀Char𠀀Char"), ToWildcardMatch0), ==, EWildcardMatch_WholeStringMatchedAndPatternExhausted);
						DMibExpect(fg_StrWildcardMatch(str_utf32("Char𠀀Char𠀀Char"), ToWildcardMatch1), ==, EWildcardMatch_WholeStringMatched);
						DMibExpect(fg_StrWildcardMatch(str_utf32("Char𠀀Char𠀀Char1"), ToWildcardMatch2), ==, EWildcardMatch_PatternExhausted);
					}
				}
				{
					DMibTestPath("NoCase");
					{
						DMibTestPath("ANSI");
						DMibExpect(fg_StrWildcardMatch<CNoCase>("char5char5Char", "?????Ch*5*ar"), ==, EWildcardMatch_WholeStringMatchedAndPatternExhausted);
						DMibExpect(fg_StrWildcardMatch<CNoCase>("char5char5Char", "?????Ch*5*ar1"), ==, EWildcardMatch_WholeStringMatched);
						DMibExpect(fg_StrWildcardMatch<CNoCase>("Char5char5Char1", "?????Ch*5*ar"), ==, EWildcardMatch_PatternExhausted);
					}
					{
						DMibTestPath("UTF8");
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf8("char𠀀char𠀀Char"), ToWildcardMatch0), ==, EWildcardMatch_WholeStringMatchedAndPatternExhausted);
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf8("char𠀀char𠀀Char"), ToWildcardMatch1), ==, EWildcardMatch_WholeStringMatched);
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf8("char𠀀char𠀀Char1"), ToWildcardMatch2), ==, EWildcardMatch_PatternExhausted);
					}
					{
						DMibTestPath("UTF16");
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf16("char𠀀char𠀀Char"), ToWildcardMatch0), ==, EWildcardMatch_WholeStringMatchedAndPatternExhausted);
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf16("char𠀀char𠀀Char"), ToWildcardMatch1), ==, EWildcardMatch_WholeStringMatched);
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf16("char𠀀char𠀀Char1"), ToWildcardMatch2), ==, EWildcardMatch_PatternExhausted);
					}
					{
						DMibTestPath("UTF32");
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf32("char𠀀char𠀀Char"), ToWildcardMatch0), ==, EWildcardMatch_WholeStringMatchedAndPatternExhausted);
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf32("char𠀀char𠀀Char"), ToWildcardMatch1), ==, EWildcardMatch_WholeStringMatched);
						DMibExpect(fg_StrWildcardMatch<CNoCase>(str_utf32("char𠀀char𠀀Char1"), ToWildcardMatch2), ==, EWildcardMatch_PatternExhausted);
					}
				}
			};
		}
		void f_DoTests()
		{
			fp_DoTests<ch8>("UTF8");
			fp_DoTests<ch16>("UTF16");
			fp_DoTests<ch32>("UTF32");
		}
	};

	DMibTestRegister(CWildcardMatch_Tests, Malterlib::String::Algorithm);
}
