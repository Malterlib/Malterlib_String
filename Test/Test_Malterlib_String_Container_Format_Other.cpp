// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/String/Formatters/AutoClear>

static_assert(!NMib::NStr::cHasFormatClass<NMib::TCAutoClearInt<int32>, NMib::NStr::EStrTypeClass_String>);

namespace
{
	struct COther_Tests : public NMib::NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("General")
			{

				{
					NMib::TCAutoClearInt<int32> ACInt = 5;
					DMibTest(DMibExpr(NMib::NStr::CStr("5")) == DMibExpr( NMib::NStr::CStr( NMib::NStr::CStr::CFormat("{}") << ACInt ) ));
				}

				DMibTest(DMibExpr(0) == DMibExpr(0));
			};
		}
	};

	DMibTestRegister(COther_Tests, Malterlib::String::Format);
}
