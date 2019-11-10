// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/HashMurmur3>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;
	using namespace NMib::NIterator;
	using namespace NMib::NTraits;
	
	static_assert
		(
			TCIsSame<TCRemoveTags<TCTags<CIteratorDistance_Supported, CIteratorTraversal_Forward>, CIteratorTraversal_None>::CType, TCTags<CIteratorDistance_Supported>>::mc_Value
			, ""
		)
	;
	static_assert
		(
			TCIsSame
			<
				TCRemoveTags<TCTags<CIteratorDistance_Supported, CIteratorTraversal_Forward, CIteratorAccess_ConstLValueArray>, CIteratorTraversal_None>::CType
				, TCTags<CIteratorDistance_Supported, CIteratorAccess_ConstLValueArray>
			>::mc_Value
			, ""
		)
	;
	static_assert
		(
			TCIsSame
			<
				TCRemoveTags<TCTags<CIteratorDistance_Supported, CIteratorTraversal_Forward, CIteratorAccess_ConstLValueArray>, CIteratorTraversal_None, CIteratorAccess_None>::CType
				, TCTags<CIteratorDistance_Supported>
			>::mc_Value
			, ""
		)
	;
	
	class CHashMurmur3_Tests : public NMib::NTest::CTest
	{
	public:
		void f_DoTests()
		{
			DMibTestSuite("TestVectors")
			{
				DMibExpect(fg_StrHashMurmur3("The quick brown fox jumps over the lazy dog", 0x9747b28c), ==, 0x2fa826cd);
				DMibExpect(fg_StrHashMurmur3(NStr::fg_RangeAdaptor_UTFDecode(fg_Range("The quick brown fox jumps over the lazy dog")), 0x9747b28c), ==, 0x2fa826cd);
			};
			
			DMibTestSuite("Normal")
			{
				{
					DMibTestPath("ANSI");
					DMibExpect(fg_StrHashMurmur3("The quick brown fox jumps over the lazy dog", 0x9747b28c), ==, 0x2fa826cd);
					DMibExpect(fg_StrHashMurmur3("Char5Char5Char"), ==, 0x75e539cb);
				}
				{
					DMibTestPath("UTF8");
					DMibExpect(fg_StrHashMurmur3(str_utf8("The quick brown fox jumps over the lazy dog"), 0x9747b28c), ==, 0x2fa826cd);
					DMibExpect(fg_StrHashMurmur3(str_utf8("Char5Char5Char")), ==, 0x75e539cb);
					DMibExpect(fg_StrHashMurmur3(str_utf8("Char𠀀Char𠀀Char")), ==, 0xa133d447);
				}
				{
					DMibTestPath("UTF16");
					DMibExpect(fg_StrHashMurmur3(str_utf16("The quick brown fox jumps over the lazy dog"), 0x9747b28c), ==, 0x2fa826cd);
					DMibExpect(fg_StrHashMurmur3(str_utf16("Char5Char5Char")), ==, 0x75e539cb);
					DMibExpect(fg_StrHashMurmur3(str_utf16("Char𠀀Char𠀀Char")), ==, 0xa133d447);
				}
				{
					DMibTestPath("UTF32");
					DMibExpect(fg_StrHashMurmur3(str_utf32("The quick brown fox jumps over the lazy dog"), 0x9747b28c), ==, 0x2fa826cd);
					DMibExpect(fg_StrHashMurmur3(str_utf32("Char5Char5Char")), ==, 0x75e539cb);
					DMibExpect(fg_StrHashMurmur3(str_utf32("Char𠀀Char𠀀Char")), ==, 0xa133d447);
				}
			};
		}
	};

	DMibTestRegister(CHashMurmur3_Tests, Malterlib::String::Algorithm);
}
