// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;

	template <typename tf_CChar>
	tf_CChar const *fg_GetToWildcardMatch(mint _Type);

	template <>
	ch8 const *fg_GetToWildcardMatch<ch8>(mint _Type)
	{
		switch (_Type)
		{
		case 0: return str_utf8("?????Ch*c*ar");
		case 1: return str_utf8("?????Ch*c*ar1");
		case 2: return str_utf8("?????Ch*c*ar");
		}
		return str_utf8("");
	}
	template <>
	ch16 const *fg_GetToWildcardMatch<ch16>(mint _Type)
	{
		switch (_Type)
		{
		case 0: return str_utf16("?????Ch*ȼ*ar");
		case 1: return str_utf16("?????Ch*ȼ*ar1");
		case 2: return str_utf16("?????Ch*ȼ*ar");
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

	class CMatchWildcard_Tests : public NMib::NTest::CTest
	{
	public:
		
		template <typename tf_CChar>
		void fp_DoTests(NStr::CStr const &_Type)
		{
			DMibTestCategory(_Type)
			{
				auto ToWildcardMatch0 = fg_GetToWildcardMatch<tf_CChar>(0);
				auto ToWildcardMatch1 = fg_GetToWildcardMatch<tf_CChar>(1);
				auto ToWildcardMatch2 = fg_GetToWildcardMatch<tf_CChar>(2);
				DMibTestCategory("Normal")
				{
					if constexpr (sizeof(tf_CChar) == 1)
					{
						DMibTestSuite("ANSI")
						{
							DMibExpect(fg_StrMatchWildcard("Char5Char5Char", "?????Ch*5*ar"), ==, EMatchWildcardResult_WholeStringMatchedAndPatternExhausted);
							DMibExpect(fg_StrMatchWildcard("Char5Char5Char", "?????Ch*5*ar1"), ==, EMatchWildcardResult_WholeStringMatched);
							DMibExpect(fg_StrMatchWildcard("Char5Char5Char1", "?????Ch*5*ar"), ==, EMatchWildcardResult_PatternExhausted);
							DMibExpect(fg_StrMatchWildcard("Char5Char5Char13", "?????Ch*5*ar?2"), ==, EMatchWildcardResult_NotMatched);
						};
						DMibTestSuite("UTF8")
						{
							DMibExpect(fg_StrMatchWildcard(str_utf8("CharcCharcChar"), ToWildcardMatch0), ==, EMatchWildcardResult_WholeStringMatchedAndPatternExhausted);
							DMibExpect(fg_StrMatchWildcard(str_utf8("CharcCharcChar"), ToWildcardMatch1), ==, EMatchWildcardResult_WholeStringMatched);
							DMibExpect(fg_StrMatchWildcard(str_utf8("CharcCharcChar1"), ToWildcardMatch2), ==, EMatchWildcardResult_PatternExhausted);
						};
					}
					if constexpr (sizeof(tf_CChar) == 2)
					{
						DMibTestSuite("UTF16")
						{
							DMibExpect(fg_StrMatchWildcard(str_utf16("CharȼCharȼChar"), ToWildcardMatch0), ==, EMatchWildcardResult_WholeStringMatchedAndPatternExhausted);
							DMibExpect(fg_StrMatchWildcard(str_utf16("CharȼCharȼChar"), ToWildcardMatch1), ==, EMatchWildcardResult_WholeStringMatched);
							DMibExpect(fg_StrMatchWildcard(str_utf16("CharȼCharȼChar1"), ToWildcardMatch2), ==, EMatchWildcardResult_PatternExhausted);
						};
					}
					if constexpr (sizeof(tf_CChar) == 4)
					{
						DMibTestSuite("UTF32")
						{
							DMibExpect(fg_StrMatchWildcard(str_utf32("Char𠀀Char𠀀Char"), ToWildcardMatch0), ==, EMatchWildcardResult_WholeStringMatchedAndPatternExhausted);
							DMibExpect(fg_StrMatchWildcard(str_utf32("Char𠀀Char𠀀Char"), ToWildcardMatch1), ==, EMatchWildcardResult_WholeStringMatched);
							DMibExpect(fg_StrMatchWildcard(str_utf32("Char𠀀Char𠀀Char1"), ToWildcardMatch2), ==, EMatchWildcardResult_PatternExhausted);
						};
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

	DMibTestRegister(CMatchWildcard_Tests, Malterlib::String::Algorithm);
}
