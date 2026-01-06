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
			DMibTestSuite("Normal")
			{
				{
					DMibTestPath("ANSI");
					auto rFound = fg_StrFindChar(fg_Const("Char5Char5Char"), '6');
					DMibExpectFalse(rFound);

					{
						auto pArray = "Char5Char5Char";
						auto rFound = fg_StrFindChar(pArray, '5');

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
					}
				}
				{
					DMibTestPath("UTF8");
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

							ch8 Data[32] = {0};
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

							ch8 Data[32] = {0};
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

							ch8 Data[32] = {0};
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

							ch8 Data[32] = {0};
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

							ch8 Data[32] = {0};
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

							ch8 Data[32] = {0};
							fg_StrCopy(Data, rFound);

							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
						}
					}
				}
				{
					DMibTestPath("UTF16");
					auto rFound = fg_StrFindChar(fg_Const(str_utf16("Char𠀀Char𠀀Char")), CharacterToNotFind);
					DMibExpectFalse(rFound);

					{
						auto pArray = str_utf16("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFindChar(pArray, CharacterToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
					}
				}
				{
					DMibTestPath("UTF32");
					auto rFound = fg_StrFindChar(fg_Const(str_utf32("Char𠀀Char𠀀Char")), CharacterToNotFind);
					DMibExpectFalse(rFound);

					{
						auto pArray = str_utf32("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFindChar(pArray, CharacterToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
					}
				}
			};
			DMibTestSuite("NoCase")
			{
				{
					DMibTestPath("ANSI");
					auto pArray = "CharECharEChar";
					auto rFound = fg_StrFindChar<CNoCase>(pArray, 'e');
					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
				}
				{
					DMibTestPath("UTF8");
					auto pArray = str_utf8("Char𠀀E𠀀Char");
					auto rFound = fg_StrFindChar<CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 8);
				}
				{
					DMibTestPath("UTF16");
					auto pArray = str_utf16("Char𠀀E𠀀Char");
					auto rFound = fg_StrFindChar<CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 6);
				}
				{
					DMibTestPath("UTF32");
					auto pArray = str_utf32("Char𠀀E𠀀Char");
					auto rFound = fg_StrFindChar<CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 5);
				}
			};
#ifndef DMibClangAnalyzerWorkaround
			// This is broken.
			DMibTestSuite("Reverse")
			{
				{
					DMibTestPath("ANSI NotFound");
					auto pArray = "Char5Char5Char";
					auto rFound = fg_StrFindChar<CReverse>(pArray, '6');
					DMibExpectFalse(rFound);
				}
				{
					DMibTestPath("ANSI");
					auto pArray = "Char5Char5Char";
					auto rFound = fg_StrFindChar<CReverse>(pArray, '5');
					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
				}
				{
					DMibTestPath("ANSI32 NotFound");
					auto pArray = "Char5Char5Char";
					auto rFound = fg_StrFindChar<CReverse>(pArray, ch32('6'));

					DMibExpectFalse(rFound);
				}
				{
					DMibTestPath("ANSI32");
					auto pArray = "Char5Char5Char";
					auto rFound = fg_StrFindChar<CReverse>(pArray, ch32('5'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
				}
				{
					DMibTestPath("UTF8");
					auto pArray = str_utf8("Char𠀀Char𠀀Char");
					auto rFound = fg_StrFindChar<CReverse>(pArray, CharacterToFind);

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 12);
				}
				{
					DMibTestPath("UTF16");
					auto pArray = str_utf16("Char𠀀Char𠀀Char");
					auto rFound = fg_StrFindChar<CReverse>(pArray, CharacterToFind);

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 10);
				}
				{
					DMibTestPath("UTF32");
					auto pArray = str_utf32("Char𠀀Char𠀀Char");
					auto rFound = fg_StrFindChar<CReverse>(pArray, CharacterToFind);

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
				}
			};
			DMibTestSuite("ReverseNoCase")
			{
				{
					DMibTestPath("ANSI");
					auto pArray = "CharECharEChar";
					auto rFound = fg_StrFindChar<CReverse, CNoCase>(pArray, 'e');

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
				}
				{
					DMibTestPath("UTF8");
					auto pArray = str_utf8("CharE𠀀CharE𠀀Char");
					auto rFound = fg_StrFindChar<CReverse, CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 13);
				}
				{
					DMibTestPath("UTF16");
					auto pArray = str_utf16("CharE𠀀CharE𠀀Char");
					auto rFound = fg_StrFindChar<CReverse, CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 11);
				}
				{
					DMibTestPath("UTF32");
					auto pArray = str_utf32("CharE𠀀CharE𠀀Char");
					auto rFound = fg_StrFindChar<CReverse, CNoCase>(pArray, ch32('e'));

					DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 10);
				}
			};
#endif
		}
	};

	DMibTestRegister(CFindChar_Tests, Malterlib::String::Algorithm);
}
