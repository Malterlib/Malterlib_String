// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

DMibStaticCheck((NMib::NStr::TCHasFormatClass<fp32, NMib::NStr::EStrTypeClass_Float>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<fp32, NMib::NStr::EStrTypeClass_Integer>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<fp32, NMib::NStr::EStrTypeClass_String>::mc_Value));
DMibStaticCheck((!NMib::NStr::TCHasFormatClass<fp32, NMib::NStr::EStrTypeClass_Other>::mc_Value));


namespace 
{

	template <typename t_CTest>
	auto fg_TestValue(t_CTest _Test) -> t_CTest
	{
		return _Test;
	}

	template <typename t_CTest>
	class TCTest
	{
	public:
		enum
		{
			ETest = sizeof(fg_TestValue(t_CTest())*1) == 4
		};
	};

	using namespace NMib::NStr;
	class CFloat_Tests : public NMib::NTest::CTest
	{
	public:
		int m_Test;

		void f_DoTests()
		{
			DMibTestSuite("General")
			{
				DMibTest(DMibExpr(1) == DMibExpr(1)) (ETest_FailAndStop);
			};
		}
	};

	DMibTestRegister(CFloat_Tests, Malterlib::String::Format);
}



