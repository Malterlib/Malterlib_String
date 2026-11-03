// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/String/Mixed>

static_assert(!NMib::NStr::cHasFormatClass<NMib::NStr::CStr, NMib::NStr::EStrTypeClassFloat>);
static_assert(!NMib::NStr::cHasFormatClass<NMib::NStr::CStr, NMib::NStr::EStrTypeClassInteger>);
static_assert(NMib::NStr::cHasFormatClass<NMib::NStr::CStr, NMib::NStr::EStrTypeClassString>);
static_assert(!NMib::NStr::cHasFormatClass<NMib::NStr::CStr, NMib::NStr::EStrTypeClassOther>);

static_assert(!NMib::NStr::cHasFormatClass<NMib::NStr::CMStrDeprecated, NMib::NStr::EStrTypeClassFloat>);
static_assert(!NMib::NStr::cHasFormatClass<NMib::NStr::CMStrDeprecated, NMib::NStr::EStrTypeClassInteger>);
static_assert(NMib::NStr::cHasFormatClass<NMib::NStr::CMStrDeprecated, NMib::NStr::EStrTypeClassString>);
static_assert(!NMib::NStr::cHasFormatClass<NMib::NStr::CMStrDeprecated, NMib::NStr::EStrTypeClassOther>);

static_assert(!NMib::NStr::cHasFormatClass<ch8 const *, NMib::NStr::EStrTypeClassFloat>);
static_assert(!NMib::NStr::cHasFormatClass<ch8 const *, NMib::NStr::EStrTypeClassInteger>);
static_assert(NMib::NStr::cHasFormatClass<ch8 const *, NMib::NStr::EStrTypeClassString>);
static_assert(!NMib::NStr::cHasFormatClass<ch8 const *, NMib::NStr::EStrTypeClassOther>);

using namespace NMib::NStr;

namespace
{
	struct CStr_Tests : public NMib::NTest::CTest
	{
	private:
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

	public:
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
