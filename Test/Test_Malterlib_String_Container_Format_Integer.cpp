// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

DMibStaticCheck((!NMib::NStr::TCHasFormatClass<int32, NMib::NStr::EStrTypeClass_Float>::mc_Value));
DMibStaticCheck((NMib::NStr::TCHasFormatClass<int32, NMib::NStr::EStrTypeClass_Integer>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<int32, NMib::NStr::EStrTypeClass_String>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<int32, NMib::NStr::EStrTypeClass_Other>::mc_Value));


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


