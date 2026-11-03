// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>

static_assert(NMib::NStr::cHasFormatClass<fp32, NMib::NStr::EStrTypeClassFloat>);
static_assert(!NMib::NStr::cHasFormatClass<fp32, NMib::NStr::EStrTypeClassInteger>);
static_assert(!NMib::NStr::cHasFormatClass<fp32, NMib::NStr::EStrTypeClassString>);
static_assert(!NMib::NStr::cHasFormatClass<fp32, NMib::NStr::EStrTypeClassOther>);

namespace
{
	template <typename tf_CTest>
	auto fg_TestValue(tf_CTest _Test) -> tf_CTest
	{
		return _Test;
	}

	template <typename t_CTest>
	struct TCTest
	{
		static constexpr aint mc_Test = sizeof(fg_TestValue(t_CTest()) * 1) == 4;
	};

	using namespace NMib::NStr;
	struct CFloat_Tests : public NMib::NTest::CTest
	{
		int m_Test;

		void f_DoTests()
		{
			DMibTestSuite("General")
			{
				DMibTest(DMibExpr(1) == DMibExpr(1))(ETest_FailAndStop);
			};
		}
	};

	DMibTestRegister(CFloat_Tests, Malterlib::String::Format);
}
