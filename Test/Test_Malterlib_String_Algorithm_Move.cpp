// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/Compare>
#include <Mib/String/Algorithms/Move>
#include <Mib/String/Algorithms/Copy>
#include <Mib/String/Algorithms/Length>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;

	template <typename tf_CChar>
	tf_CChar const *fg_GetToMove();

	template <>
	ch8 const *fg_GetToMove<ch8>()
	{
		return str_utf8("Char𠀀Char𠀀Char");
	}
	template <>
	[[maybe_unused]] ch16 const *fg_GetToMove<ch16>()
	{
		return str_utf16("Char𠀀Char𠀀Char");
	}
	template <>
	[[maybe_unused]] ch32 const *fg_GetToMove<ch32>()
	{
		return str_utf32("Char𠀀Char𠀀Char");
	}

	class CMove_Tests : public NMib::NTest::CTest
	{
	public:
		
		void fp_TestOverlap()
		{
			auto ToMove = fg_GetToMove<ch8>();
			DMibTestCategory("Overlap left")
			{
				DMibTestSuite("ANSI")
				{
					ch8 OutArray[100];
					NMem::fg_ObjectSet(OutArray + 0, 0xff, 100);
					auto rDestination = fg_StrCopy(OutArray, "Char65Char5Char");
					
					fg_StrMove(NStr::fg_NullTerminated(OutArray), NStr::fg_RawStringArray(OutArray + 4, 6));
					DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), "65CharChar5Char"), ==, ECompare_Equal);
				};
				DMibTestSuite("UTF8")
				{
					ch8 OutArray[100];
					NMem::fg_ObjectSet(OutArray, 0xff, 100);
					auto rDestination = fg_StrCopy(OutArray, ToMove);
					
					fg_StrMove(OutArray + 0, NStr::fg_RawStringArray(OutArray + 4, 8));
					DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("𠀀CharChar𠀀Char")), ==, ECompare_Equal);
				};
				DMibTestSuite("UTF16")
				{
					ch16 OutArray[100];
					NMem::fg_ObjectSet(OutArray, 0xff, 100);
					auto rDestination = fg_StrCopy(OutArray, ToMove);

					fg_StrMove(OutArray + 0, NStr::fg_RawStringArray(OutArray + 4, 6));
					DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("𠀀CharChar𠀀Char")), ==, ECompare_Equal);
				};
				DMibTestSuite("UTF32")
				{
					ch32 OutArray[100];
					NMem::fg_ObjectSet(OutArray, 0xff, 100);
					auto rDestination = fg_StrCopy(OutArray, ToMove);
					fg_StrMove(OutArray + 0, NStr::fg_RawStringArray(OutArray + 4, 5));
					DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("𠀀CharChar𠀀Char")), ==, ECompare_Equal);
				};
			};
			DMibTestCategory("Overlap right")
			{
				DMibTestSuite("ANSI")
				{
					ch8 OutArray[100];
					NMem::fg_ObjectSet(OutArray, 0xff, 100);
					auto rDestination = fg_StrCopy(OutArray, "Char65Char5Char");
					
					fg_StrMove(OutArray + 6, NStr::fg_RawStringArray(OutArray + 4, 6));
					DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), "Char6565Charhar"), ==, ECompare_Equal);
				};
				DMibTestSuite("UTF8")
				{
					ch8 OutArray[100];
					NMem::fg_ObjectSet(OutArray, 0xff, 100);
					auto rDestination = fg_StrCopy(OutArray, ToMove);

					fg_StrMove(OutArray + 8, NStr::fg_RawStringArray(OutArray + 4, 8));
					DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀𠀀CharChar")), ==, ECompare_Equal);
				};
				DMibTestSuite("UTF16")
				{
					ch16 OutArray[100];
					NMem::fg_ObjectSet(OutArray, 0xff, 100);
					auto rDestination = fg_StrCopy(OutArray, ToMove);

					fg_StrMove(OutArray + 6, NStr::fg_RawStringArray(OutArray + 4, 6));
					DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀𠀀CharChar")), ==, ECompare_Equal);
				};
				DMibTestSuite("UTF32")
				{
					ch32 OutArray[100];
					NMem::fg_ObjectSet(OutArray, 0xff, 100);
					auto rDestination = fg_StrCopy(OutArray, ToMove);
					fg_StrMove(OutArray + 5, NStr::fg_RawStringArray(OutArray + 4, 5));
					DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀𠀀CharChar")), ==, ECompare_Equal);
				};
			};
		}
		void f_DoTests()
		{
			fp_TestOverlap();
		}
	};

	DMibTestRegister(CMove_Tests, Malterlib::String::Algorithm);
}
