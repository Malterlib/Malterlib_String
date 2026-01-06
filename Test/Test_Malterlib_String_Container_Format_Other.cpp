// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Formatters/AutoClear>

static_assert(!NMib::NStr::cHasFormatClass<NMib::TCAutoClearInt<int32>, NMib::NStr::EStrTypeClass_String>);

namespace
{
	class COther_Tests : public NMib::NTest::CTest
	{
	public:

		int m_Test;

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


