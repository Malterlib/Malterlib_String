// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/FindChar>
#include <Mib/String/Algorithms/Copy>
#include <Mib/String/Algorithms/Compare>
#include <Mib/String/Algorithms/Length>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;
	using namespace NMib::NIterator;
	
	class CFindChar_Tests : public NMib::NTest::CTest
	{
	public:
		void f_DoTests()
		{
			ch32 CharacterToFind = 0x00020000; // ch32(str_utf32('𠀀'))
			ch32 CharacterToNotFind = 0x00020001; // ch32(str_utf32('𠀁'))
			DMibTestCategory("Normal")
			{
				DMibTestSuite("ANSI")
				{
					auto rFound = fg_StrFindChar(fg_Const("Char5Char5Char"), '6');
					DMibExpectFalse(rFound);
					
					{
						auto pArray = "Char5Char5Char";
						auto rFound = fg_StrFindChar(pArray, '5');

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
					}
				};
				DMibTestSuite("UTF8")
				{
					{
						auto rFound = fg_StrFindChar(fg_Const(str_utf8("Char𠀀Char𠀀Char")), CharacterToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChar(pArray, CharacterToFind);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
						}
					}
					{
						DMibTestPath("CReturn_Front_ResFront");
						auto rFound = fg_StrFindChar<CReturn_Front_ResFront>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), CharacterToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChar<CReturn_Front_ResFront>(pArray, CharacterToFind);

							ch8 Data[32];
							fg_StrCopy(Data, rFound);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("Char")), ==, ECompare_Equal);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
							DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 4);
						}
					}
					{
						DMibTestPath("CReturn_ResFront_ResBack");
						auto rFound = fg_StrFindChar<CReturn_ResFront_ResBack>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), CharacterToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChar<CReturn_ResFront_ResBack>(pArray, CharacterToFind);

							ch8 Data[32];
							fg_StrCopy(Data, rFound);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("𠀀")), ==, ECompare_Equal);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
							DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 8);
						}
					}
					{
						DMibTestPath("CReturn_ResBack_Back");
						auto rFound = fg_StrFindChar<CReturn_ResBack_Back>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), CharacterToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChar<CReturn_ResBack_Back>(pArray, CharacterToFind);

							ch8 Data[32];
							fg_StrCopy(Data, rFound);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("Char𠀀Char")), ==, ECompare_Equal);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 8);
						}
					}
					{
						DMibTestPath("CReturn_ResFront_Back");
						auto rFound = fg_StrFindChar<CReturn_ResFront_Back>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), CharacterToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChar<CReturn_ResFront_Back>(pArray, CharacterToFind);

							ch8 Data[32];
							fg_StrCopy(Data, rFound);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("𠀀Char𠀀Char")), ==, ECompare_Equal);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
						}
					}
					{
						DMibTestPath("CReturn_Front_ResBack");
						auto rFound = fg_StrFindChar<CReturn_Front_ResBack>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), CharacterToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChar<CReturn_Front_ResBack>(pArray, CharacterToFind);

							ch8 Data[32];
							fg_StrCopy(Data, rFound);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("Char𠀀")), ==, ECompare_Equal);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
							DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 8);
						}
					}
					{
						DMibTestPath("CReturn_Front_Back");
						auto rFound = fg_StrFindChar<CReturn_Front_Back>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), CharacterToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChar<CReturn_Front_Back>(pArray, CharacterToFind);

							ch8 Data[32];
							fg_StrCopy(Data, rFound);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
						}
					}
				};
				DMibTestSuite("UTF16")
				{
					auto rFound = fg_StrFindChar(fg_Const(str_utf16("Char𠀀Char𠀀Char")), CharacterToNotFind);
					DMibExpectFalse(rFound);
					
					{
						auto pArray = str_utf16("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFindChar(pArray, CharacterToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
					}
				};
				DMibTestSuite("UTF32")
				{
					auto rFound = fg_StrFindChar(fg_Const(str_utf32("Char𠀀Char𠀀Char")), CharacterToNotFind);
					DMibExpectFalse(rFound);
					
					{
						auto pArray = str_utf32("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFindChar(pArray, CharacterToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
					}
				};
			};
			DMibTestCategory("NoCase")
			{
				DMibTestSuite("ANSI")
				{
					auto pArray = "CharECharEChar";
					auto rFound = fg_StrFindChar<CNoCase>(pArray, 'e');
					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
				};
				DMibTestSuite("UTF8")
				{
					auto pArray = str_utf8("Char𠀀E𠀀Char");
					auto rFound = fg_StrFindChar<CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 8);
				};
				DMibTestSuite("UTF16")
				{
					auto pArray = str_utf16("Char𠀀E𠀀Char");
					auto rFound = fg_StrFindChar<CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 6);
				};
				DMibTestSuite("UTF32")
				{
					auto pArray = str_utf32("Char𠀀E𠀀Char");
					auto rFound = fg_StrFindChar<CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 5);
				};
			};
			DMibTestCategory("Reverse")
			{
				DMibTestSuite("ANSI")
				{
					auto pArray = "Char5Char5Char";
					auto rFound = fg_StrFindChar<CReverse>(pArray, '5');

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
				};
				DMibTestSuite("UTF8")
				{
					auto pArray = str_utf8("Char𠀀Char𠀀Char");
					auto rFound = fg_StrFindChar<CReverse>(pArray, CharacterToFind);

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 12);
				};
				DMibTestSuite("UTF16")
				{
					auto pArray = str_utf16("Char𠀀Char𠀀Char");
					auto rFound = fg_StrFindChar<CReverse>(pArray, CharacterToFind);

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 10);
				};
				DMibTestSuite("UTF32")
				{
					auto pArray = str_utf32("Char𠀀Char𠀀Char");
					auto rFound = fg_StrFindChar<CReverse>(pArray, CharacterToFind);

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
				};
			};
			DMibTestCategory("ReverseNoCase")
			{
				DMibTestSuite("ANSI")
				{
					auto pArray = "CharECharEChar";
					auto rFound = fg_StrFindChar<CReverse, CNoCase>(pArray, 'e');

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
				};
				DMibTestSuite("UTF8")
				{
					auto pArray = str_utf8("CharE𠀀CharE𠀀Char");
					auto rFound = fg_StrFindChar<CReverse, CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 13);
				};
				DMibTestSuite("UTF16")
				{
					auto pArray = str_utf16("CharE𠀀CharE𠀀Char");
					auto rFound = fg_StrFindChar<CReverse, CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 11);
				};
				DMibTestSuite("UTF32")
				{
					auto pArray = str_utf32("CharE𠀀CharE𠀀Char");
					auto rFound = fg_StrFindChar<CReverse, CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 10);
				};
			};
		}
	};

	DMibTestRegister(CFindChar_Tests, Malterlib::String::Algorithm);
}
