// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/String/String>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;

	struct CCharacter_Tests : public NMib::NTest::CTest
	{
		template <typename tf_CChar>
		void fp_LowerCaseTests()
		{
			DMibTestCategory("LowerCase")
			{
				DMibTestCategory("ASCII")
				{
					{
						DMibTestPath("A");
						DMibExpect(fg_CharLowerCase((tf_CChar)'A'), ==, (tf_CChar)'a');
					}
					{
						DMibTestPath("Z");
						DMibExpect(fg_CharLowerCase((tf_CChar)'Z'), ==, (tf_CChar)'z');
					}
					{
						DMibTestPath("M");
						DMibExpect(fg_CharLowerCase((tf_CChar)'M'), ==, (tf_CChar)'m');
					}
					{
						DMibTestPath("AlreadyLower");
						DMibExpect(fg_CharLowerCase((tf_CChar)'a'), ==, (tf_CChar)'a');
					}
					{
						DMibTestPath("Number");
						DMibExpect(fg_CharLowerCase((tf_CChar)'5'), ==, (tf_CChar)'5');
					}
					{
						DMibTestPath("Space");
						DMibExpect(fg_CharLowerCase((tf_CChar)' '), ==, (tf_CChar)' ');
					}
				};

				DMibTestCategory("Latin1")
				{
					{
						DMibTestPath("AGrave_0xC0");
						DMibExpect(fg_CharLowerCase((tf_CChar)0xc0), ==, (tf_CChar)0xe0);
					}
					{
						DMibTestPath("AUmlaut_0xC4");
						DMibExpect(fg_CharLowerCase((tf_CChar)0xc4), ==, (tf_CChar)0xe4);
					}
					{
						DMibTestPath("Ntilde_0xD1");
						DMibExpect(fg_CharLowerCase((tf_CChar)0xd1), ==, (tf_CChar)0xf1);
					}
					{
						DMibTestPath("Thorn_0xDE");
						DMibExpect(fg_CharLowerCase((tf_CChar)0xde), ==, (tf_CChar)0xfe);
					}
					{
						DMibTestPath("MultiplicationSign_0xD7_Unchanged");
						DMibExpect(fg_CharLowerCase((tf_CChar)0xd7), ==, (tf_CChar)0xd7);
					}
					{
						DMibTestPath("AlreadyLower_0xE0");
						DMibExpect(fg_CharLowerCase((tf_CChar)0xe0), ==, (tf_CChar)0xe0);
					}
				};
			};
		}

		template <typename tf_CChar>
		void fp_UpperCaseTests()
		{
			DMibTestCategory("UpperCase")
			{
				DMibTestCategory("ASCII")
				{
					{
						DMibTestPath("a");
						DMibExpect(fg_CharUpperCase((tf_CChar)'a'), ==, (tf_CChar)'A');
					}
					{
						DMibTestPath("z");
						DMibExpect(fg_CharUpperCase((tf_CChar)'z'), ==, (tf_CChar)'Z');
					}
					{
						DMibTestPath("m");
						DMibExpect(fg_CharUpperCase((tf_CChar)'m'), ==, (tf_CChar)'M');
					}
					{
						DMibTestPath("AlreadyUpper");
						DMibExpect(fg_CharUpperCase((tf_CChar)'A'), ==, (tf_CChar)'A');
					}
					{
						DMibTestPath("Number");
						DMibExpect(fg_CharUpperCase((tf_CChar)'5'), ==, (tf_CChar)'5');
					}
					{
						DMibTestPath("Space");
						DMibExpect(fg_CharUpperCase((tf_CChar)' '), ==, (tf_CChar)' ');
					}
				};

				DMibTestCategory("Latin1")
				{
					{
						DMibTestPath("aGrave_0xE0");
						DMibExpect(fg_CharUpperCase((tf_CChar)0xe0), ==, (tf_CChar)0xc0);
					}
					{
						DMibTestPath("aUmlaut_0xE4");
						DMibExpect(fg_CharUpperCase((tf_CChar)0xe4), ==, (tf_CChar)0xc4);
					}
					{
						DMibTestPath("nTilde_0xF1");
						DMibExpect(fg_CharUpperCase((tf_CChar)0xf1), ==, (tf_CChar)0xd1);
					}
					{
						DMibTestPath("thorn_0xFE");
						DMibExpect(fg_CharUpperCase((tf_CChar)0xfe), ==, (tf_CChar)0xde);
					}
					{
						DMibTestPath("DivisionSign_0xF7_Unchanged");
						DMibExpect(fg_CharUpperCase((tf_CChar)0xf7), ==, (tf_CChar)0xf7);
					}
					{
						DMibTestPath("AlreadyUpper_0xC0");
						DMibExpect(fg_CharUpperCase((tf_CChar)0xc0), ==, (tf_CChar)0xc0);
					}
				};
			};
		}

		template <typename tf_CChar>
		void fp_RoundtripTests()
		{
			DMibTestCategory("Roundtrip")
			{
				{
					DMibTestPath("ASCII_a");
					DMibExpect(fg_CharLowerCase(fg_CharUpperCase((tf_CChar)'a')), ==, (tf_CChar)'a');
				}
				{
					DMibTestPath("ASCII_Z");
					DMibExpect(fg_CharUpperCase(fg_CharLowerCase((tf_CChar)'Z')), ==, (tf_CChar)'Z');
				}
				{
					DMibTestPath("Latin1_0xE0");
					DMibExpect(fg_CharLowerCase(fg_CharUpperCase((tf_CChar)0xe0)), ==, (tf_CChar)0xe0);
				}
				{
					DMibTestPath("Latin1_0xDE");
					DMibExpect(fg_CharUpperCase(fg_CharLowerCase((tf_CChar)0xde)), ==, (tf_CChar)0xde);
				}
			};
		}

		void f_DoTests()
		{
			DMibTestSuite("Character")
			{
				DMibTestCategory("ch16")
				{
					fp_LowerCaseTests<ch16>();
					fp_UpperCaseTests<ch16>();
					fp_RoundtripTests<ch16>();
				};
				DMibTestCategory("ch32")
				{
					fp_LowerCaseTests<ch32>();
					fp_UpperCaseTests<ch32>();
					fp_RoundtripTests<ch32>();
				};
			};
		}
	};

	DMibTestRegister(CCharacter_Tests, Malterlib::String::Algorithm::Character);
}
