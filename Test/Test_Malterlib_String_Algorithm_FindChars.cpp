// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/FindChars>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;

	template <typename tf_CChar>
	tf_CChar const *fg_GetToFind();

	template <>
	ch8 const *fg_GetToFind<ch8>()
	{
		return str_utf8("7𠀀");
	}
	template <>
	ch16 const *fg_GetToFind<ch16>()
	{
		return str_utf16("7𠀀");
	}
	template <>
	ch32 const *fg_GetToFind<ch32>()
	{
		return str_utf32("7𠀀");
	}
	template <typename tf_CChar>
	tf_CChar const *fg_GetToNotFind();

	template <>
	ch8 const *fg_GetToNotFind<ch8>()
	{
		return str_utf8("7𠀁");
	}
	template <>
	ch16 const *fg_GetToNotFind<ch16>()
	{
		return str_utf16("7𠀁");
	}
	template <>
	ch32 const *fg_GetToNotFind<ch32>()
	{
		return str_utf32("7𠀁");
	}

	template <typename tf_CChar>
	tf_CChar const *fg_GetToFindLower();

	template <>
	ch8 const *fg_GetToFindLower<ch8>()
	{
		return str_utf8("de");
	}
	template <>
	ch16 const *fg_GetToFindLower<ch16>()
	{
		return str_utf16("de");
	}
	template <>
	ch32 const *fg_GetToFindLower<ch32>()
	{
		return str_utf32("de");
	}
	
	
	class CFindChars_Tests : public NMib::NTest::CTest
	{
	public:
		
		template <typename tf_CChar>
		void fp_DoTests(NStr::CStr const &_Type)
		{
			DMibTestCategory(_Type)
			{
				auto ToFind = fg_GetToFind<tf_CChar>();
				auto ToNotFind = fg_GetToNotFind<tf_CChar>();
				DMibTestCategory("Normal")
				{
					DMibTestSuite("ANSI")
					{
						auto rFound = fg_StrFindChars(fg_Const("Char5Char5Char"), "67");
						DMibExpectFalse(rFound);
						
						{
							auto pArray = "Char5Char5Char";
							auto rFound = fg_StrFindChars(pArray, "65");

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
						}
					};
					DMibTestSuite("UTF8")
					{
						auto rFound = fg_StrFindChars(fg_Const(str_utf8("Char𠀀Char𠀀Char")), ToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf8("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChars(pArray, ToFind);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
						}
					};
					DMibTestSuite("UTF16")
					{
						auto rFound = fg_StrFindChars(fg_Const(str_utf16("Char𠀀Char𠀀Char")), ToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf16("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChars(pArray, ToFind);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
						}
					};
					DMibTestSuite("UTF32")
					{
						auto rFound = fg_StrFindChars(fg_Const(str_utf32("Char𠀀Char𠀀Char")), ToNotFind);
						DMibExpectFalse(rFound);
						
						{
							auto pArray = str_utf32("Char𠀀Char𠀀Char");
							auto rFound = fg_StrFindChars(pArray, ToFind);

							DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
						}
					};
				};
				DMibTestCategory("NoCase")
				{
					DMibTestSuite("ANSI")
					{
						auto pArray = "CharECharEChar";
						auto rFound = fg_StrFindChars<CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());
						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 4);
					};
					DMibTestSuite("UTF8")
					{
						auto pArray = str_utf8("Char𠀀E𠀀Char");
						auto rFound = fg_StrFindChars<CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 8);
					};
					DMibTestSuite("UTF16")
					{
						auto pArray = str_utf16("Char𠀀E𠀀Char");
						auto rFound = fg_StrFindChars<CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 6);
					};
					DMibTestSuite("UTF32")
					{
						auto pArray = str_utf32("Char𠀀E𠀀Char");
						auto rFound = fg_StrFindChars<CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 5);
					};
				};
				DMibTestCategory("Reverse")
				{
					DMibTestSuite("ANSI")
					{
						auto pArray = "Char5Char5Char";
						auto rFound = fg_StrFindChars<CReverse>(pArray, "65");

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
					};
					DMibTestSuite("UTF8")
					{
						auto pArray = str_utf8("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFindChars<CReverse>(pArray, ToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 12);
					};
					DMibTestSuite("UTF16")
					{
						auto pArray = str_utf16("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFindChars<CReverse>(pArray, ToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 10);
					};
					DMibTestSuite("UTF32")
					{
						auto pArray = str_utf32("Char𠀀Char𠀀Char");
						auto rFound = fg_StrFindChars<CReverse>(pArray, ToFind);

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
					};
				};
				DMibTestCategory("ReverseNoCase")
				{
					DMibTestSuite("ANSI")
					{
						auto pArray = "CharECharEChar";
						auto rFound = fg_StrFindChars<CReverse, CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 9);
					};
					DMibTestSuite("UTF8")
					{
						auto pArray = str_utf8("CharE𠀀CharE𠀀Char");
						auto rFound = fg_StrFindChars<CReverse, CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 13);
					};
					DMibTestSuite("UTF16")
					{
						auto pArray = str_utf16("CharE𠀀CharE𠀀Char");
						auto rFound = fg_StrFindChars<CReverse, CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 11);
					};
					DMibTestSuite("UTF32")
					{
						auto pArray = str_utf32("CharE𠀀CharE𠀀Char");
						auto rFound = fg_StrFindChars<CReverse, CNoCase>(pArray, fg_GetToFindLower<tf_CChar>());

						DMibExpect(rFound.f_Front().f_Base(), ==, pArray + 10);
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

	DMibTestRegister(CFindChars_Tests, Malterlib::String::Algorithm);
}
