// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/Find>
#include <Mib/String/Algorithms/Copy>
#include <Mib/String/Algorithms/Compare>
#include <Mib/String/Algorithms/Length>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;
	using namespace NMib::NIterator;

	template <typename tf_CChar>
	tf_CChar const *fg_GetToFind();

	template <>
	ch8 const *fg_GetToFind<ch8>()
	{
		return str_utf8("𠀀C");
	}
	template <>
	ch16 const *fg_GetToFind<ch16>()
	{
		return str_utf16("𠀀C");
	}
	template <>
	ch32 const *fg_GetToFind<ch32>()
	{
		return str_utf32("𠀀C");
	}
	template <typename tf_CChar>
	tf_CChar const *fg_GetToNotFind();

	template <>
	ch8 const *fg_GetToNotFind<ch8>()
	{
		return str_utf8("𠀁C");
	}
	template <>
	ch16 const *fg_GetToNotFind<ch16>()
	{
		return str_utf16("𠀁C");
	}
	template <>
	ch32 const *fg_GetToNotFind<ch32>()
	{
		return str_utf32("𠀁C");
	}

	template <typename tf_CChar>
	tf_CChar const *fg_GetToFindLower();

	template <>
	ch8 const *fg_GetToFindLower<ch8>()
	{
		return str_utf8("e𠀀");
	}
	template <>
	ch16 const *fg_GetToFindLower<ch16>()
	{
		return str_utf16("e𠀀");
	}
	template <>
	ch32 const *fg_GetToFindLower<ch32>()
	{
		return str_utf32("e𠀀");
	}
	
	
	class CFind_Tests : public NMib::NTest::CTest
	{
	public:
		
		template <typename tf_CChar>
		void fp_DoTests(NStr::CStr const &_Type)
		{
			DMibTestSuite(_Type)
			{
				auto ToFind = fg_GetToFind<tf_CChar>();
				auto ToNotFind = fg_GetToNotFind<tf_CChar>();
				{
					DMibTestPath("Normal");
					{
						DMibTestPath("ANSI");
						auto rFound = fg_StrFind(fg_Const("Char5Char5Char"), "67");
						DMibExpectFalse(rFound);
						
						{
							auto pArray = "Char65Char5Char";
							auto rFound = fg_StrFind(pArray, "65");

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
						}
					}
					{
						DMibTestPath("UTF8");
						{
							DMibTestPath("Default");
							auto rFound = fg_StrFind(fg_Const(str_utf8("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf8("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind(pArray, ToFind);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_Front_ResFront");
							auto rFound = fg_StrFind<CReturn_Front_ResFront>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf8("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_ResFront>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_ResFront_ResBack");
							auto rFound = fg_StrFind<CReturn_ResFront_ResBack>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf8("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResFront_ResBack>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("𠀀C")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 4 + 5);
							}
						}
						{
							DMibTestPath("CReturn_ResBack_Back");
							auto rFound = fg_StrFind<CReturn_ResBack_Back>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf8("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResBack_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("har𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4 + 5);
							}
						}
						{
							DMibTestPath("CReturn_ResFront_Back");
							auto rFound = fg_StrFind<CReturn_ResFront_Back>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf8("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResFront_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("𠀀Char𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_Front_ResBack");
							auto rFound = fg_StrFind<CReturn_Front_ResBack>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf8("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_ResBack>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("Char𠀀C")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 9);
							}
						}
						{
							DMibTestPath("CReturn_Front_Back");
							auto rFound = fg_StrFind<CReturn_Front_Back>(fg_Const(str_utf8("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf8("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
							}
						}
					}
					{
						DMibTestPath("UTF16");
						{
							DMibTestPath("Default");
							auto rFound = fg_StrFind(fg_Const(str_utf16("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf16("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind(pArray, ToFind);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_Front_ResFront");
							auto rFound = fg_StrFind<CReturn_Front_ResFront>(fg_Const(str_utf16("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf16("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_ResFront>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf16("Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_ResFront_ResBack");
							auto rFound = fg_StrFind<CReturn_ResFront_ResBack>(fg_Const(str_utf16("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf16("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResFront_ResBack>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf16("𠀀C")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 4 + 3);
							}
						}
						{
							DMibTestPath("CReturn_ResBack_Back");
							auto rFound = fg_StrFind<CReturn_ResBack_Back>(fg_Const(str_utf16("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf16("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResBack_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf16("har𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4 + 3);
							}
						}
						{
							DMibTestPath("CReturn_ResFront_Back");
							auto rFound = fg_StrFind<CReturn_ResFront_Back>(fg_Const(str_utf16("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf16("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResFront_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf16("𠀀Char𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_Front_ResBack");
							auto rFound = fg_StrFind<CReturn_Front_ResBack>(fg_Const(str_utf16("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf16("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_ResBack>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf16("Char𠀀C")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 7);
							}
						}
						{
							DMibTestPath("CReturn_Front_Back");
							auto rFound = fg_StrFind<CReturn_Front_Back>(fg_Const(str_utf16("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf16("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf16("Char𠀀Char𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
							}
						}
					}
					{
						DMibTestPath("UTF32");
						{
							DMibTestPath("Default");
							auto rFound = fg_StrFind(fg_Const(str_utf32("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf32("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind(pArray, ToFind);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_Front_ResFront");
							auto rFound = fg_StrFind<CReturn_Front_ResFront>(fg_Const(str_utf32("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf32("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_ResFront>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf32("Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_ResFront_ResBack");
							auto rFound = fg_StrFind<CReturn_ResFront_ResBack>(fg_Const(str_utf32("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf32("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResFront_ResBack>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf32("𠀀C")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 4 + 2);
							}
						}
						{
							DMibTestPath("CReturn_ResBack_Back");
							auto rFound = fg_StrFind<CReturn_ResBack_Back>(fg_Const(str_utf32("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf32("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResBack_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf32("har𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 6);
							}
						}
						{
							DMibTestPath("CReturn_ResFront_Back");
							auto rFound = fg_StrFind<CReturn_ResFront_Back>(fg_Const(str_utf32("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf32("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_ResFront_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf32("𠀀Char𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
							}
						}
						{
							DMibTestPath("CReturn_Front_ResBack");
							auto rFound = fg_StrFind<CReturn_Front_ResBack>(fg_Const(str_utf32("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf32("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_ResBack>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf32("Char𠀀C")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
								DMibExpect(rFound.f_Back().f_Base(), ==, pArray + 6);
							}
						}
						{
							DMibTestPath("CReturn_Front_Back");
							auto rFound = fg_StrFind<CReturn_Front_Back>(fg_Const(str_utf32("Char𠀀Char𠀀Char")), ToNotFind);
							DMibExpectFalse(rFound);
							
							{
								auto pArray = str_utf32("Char𠀀Char𠀀Char");
								auto rFound = fg_StrFind<CReturn_Front_Back>(pArray, ToFind);

								ch8 Data[32];
								fg_StrCopy(Data, rFound);
								
								DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(Data), str_utf32("Char𠀀Char𠀀Char")), ==, ECompare_Equal);

								DMibExpect(rFound.f_Front().f_Base(), ==, pArray);
							}
						}
					}
				}
				{
					DMibTestPath("NoCase");
					{
						DMibTestPath("ANSI");
						auto pArray = "CharECharEChar";
						auto rFound = fg_StrFind<CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());
						DMibExpectFalse(rFound);
					}
					{
						DMibTestPath("UTF8");
						auto pArray = str_utf8("Char𠀀E𠀀Char");
						auto rFound = fg_StrFind<CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 8);
					}
					{
						DMibTestPath("UTF16");
						auto pArray = str_utf16("Char𠀀E𠀀Char");
						auto rFound = fg_StrFind<CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 6);
					}
					{
						DMibTestPath("UTF32");
						auto pArray = str_utf32("Char𠀀E𠀀Char");
						auto rFound = fg_StrFind<CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 5);
					}
				}
				{
					DMibTestPath("Reverse");
					{
						DMibTestPath("ANSI");
						auto pArray = "Char5Char5Char";
						auto rFound = fg_StrFind<CReverse>(pArray, "5C");

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
					}
 					{
						DMibTestPath("UTF8");
						auto pArray = str_utf8("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFind<CReverse>(pArray, ToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 12);
					}
					{
						DMibTestPath("UTF16");
						auto pArray = str_utf16("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFind<CReverse>(pArray, ToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 10);
					}
					{
						DMibTestPath("UTF32");
						auto pArray = str_utf32("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFind<CReverse>(pArray, ToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
					}
				}
				{
					DMibTestPath("ReverseNoCase");
					{
						DMibTestPath("ANSI");
						auto pArray = "CharECharEChar";
						auto rFound = fg_StrFind<CReverse, CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpectFalse(rFound);
					}
					{
						DMibTestPath("UTF8");
						auto pArray = str_utf8("CharE𠀀CharE𠀀Char");
						auto rFound = fg_StrFind<CReverse, CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 13);
					}
					{
						DMibTestPath("UTF16");
						auto pArray = str_utf16("CharE𠀀CharE𠀀Char");
						auto rFound = fg_StrFind<CReverse, CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 11);
					}
					{
						DMibTestPath("UTF32");
						auto pArray = str_utf32("CharE𠀀CharE𠀀Char");
						auto rFound = fg_StrFind<CReverse, CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 10);
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

	DMibTestRegister(CFind_Tests, Malterlib::String::Algorithm);
}
