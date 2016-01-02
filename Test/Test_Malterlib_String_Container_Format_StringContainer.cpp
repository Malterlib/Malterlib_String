// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Mixed>

DMibStaticCheck((!NMib::NStr::TCHasFormatClass<NMib::NStr::CStr, NMib::NStr::EStrTypeClass_Float>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<NMib::NStr::CStr, NMib::NStr::EStrTypeClass_Integer>::mc_Value));
DMibStaticCheck((NMib::NStr::TCHasFormatClass<NMib::NStr::CStr, NMib::NStr::EStrTypeClass_String>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<NMib::NStr::CStr, NMib::NStr::EStrTypeClass_Other>::mc_Value));

DMibStaticCheck((!NMib::NStr::TCHasFormatClass<NMib::NStr::CMStrDeprecated, NMib::NStr::EStrTypeClass_Float>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<NMib::NStr::CMStrDeprecated, NMib::NStr::EStrTypeClass_Integer>::mc_Value));
DMibStaticCheck((NMib::NStr::TCHasFormatClass<NMib::NStr::CMStrDeprecated, NMib::NStr::EStrTypeClass_String>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<NMib::NStr::CMStrDeprecated, NMib::NStr::EStrTypeClass_Other>::mc_Value));

DMibStaticCheck((!NMib::NStr::TCHasFormatClass<const ch8 *, NMib::NStr::EStrTypeClass_Float>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<const ch8 *, NMib::NStr::EStrTypeClass_Integer>::mc_Value));
DMibStaticCheck((NMib::NStr::TCHasFormatClass<const ch8 *, NMib::NStr::EStrTypeClass_String>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<const ch8 *, NMib::NStr::EStrTypeClass_Other>::mc_Value));

using namespace NMib::NStr;

namespace
{
	class CStr_Tests : public NMib::NTest::CTest
	{
	public:

		int m_Test;

		template <typename tf_CFormatFrom>
		void fp_DoCapitalizeTestSource(ch8 const *_pFromName, tf_CFormatFrom const &_From)
		{
			DMibTestPath(_pFromName);
			DMibExpect(fg_Format<CStr>("{cc}", _From), ==, "Test");
		}

		template <typename tf_CFormatTo>
		void fp_DoCapitalizeTest(ch8 const *_pName)
		{
			DMibTestPath(_pName);
			fp_DoCapitalizeTestSource("ch8 const *", "test");
			fp_DoCapitalizeTestSource("CStr", CStr("test"));
			fp_DoCapitalizeTestSource("CWStr", CWStr("test"));
			fp_DoCapitalizeTestSource("CUStr", CUStr("test"));
		}

		void f_DoTests()
		{
			DMibTestSuite("Capitalize")
			{
				fp_DoCapitalizeTest<CStr>("CStr");
				fp_DoCapitalizeTest<CWStr>("CWStr");
				fp_DoCapitalizeTest<CUStr>("CUStr");
			};
		}
			
	};

	DMibTestRegister(CStr_Tests, Malterlib::String::Format);
}



