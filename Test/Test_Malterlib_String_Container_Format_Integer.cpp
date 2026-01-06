// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

static_assert(!NMib::NStr::cHasFormatClass<int32, NMib::NStr::EStrTypeClass_Float>);
static_assert(NMib::NStr::cHasFormatClass<int32, NMib::NStr::EStrTypeClass_Integer>);
static_assert(!NMib::NStr::cHasFormatClass<int32, NMib::NStr::EStrTypeClass_String>);
static_assert(!NMib::NStr::cHasFormatClass<int32, NMib::NStr::EStrTypeClass_Other>);


namespace
{
	class CInt_Tests : public NMib::NTest::CTest
	{
	public:

		int m_Test;

		void f_DoTests()
		{
			DMibTestSuite("General")
			{
				DMibTest(DMibExpr(0) == DMibExpr(0));
			};
		}

	};

	DMibTestRegister(CInt_Tests, Malterlib::String::Format);
}


