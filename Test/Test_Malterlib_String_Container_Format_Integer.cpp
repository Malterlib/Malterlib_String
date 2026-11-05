// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

static_assert(!NMib::NStr::cHasFormatClass<int32, NMib::NStr::EStrTypeClassFloat>);
static_assert(NMib::NStr::cHasFormatClass<int32, NMib::NStr::EStrTypeClassInteger>);
static_assert(!NMib::NStr::cHasFormatClass<int32, NMib::NStr::EStrTypeClassString>);
static_assert(!NMib::NStr::cHasFormatClass<int32, NMib::NStr::EStrTypeClassOther>);

namespace
{
	struct CInt_Tests : public NMib::NTest::CTest
	{
		void f_DoTests();
	};

	void CInt_Tests::f_DoTests()
	{
		DMibTestSuite("General")
		{
			DMibTest(DMibExpr(0) == DMibExpr(0));
		};
	}

	DMibTestRegister(CInt_Tests, Malterlib::String::Format);
}
