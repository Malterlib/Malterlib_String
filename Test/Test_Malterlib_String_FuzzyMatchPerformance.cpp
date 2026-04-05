// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>
#include <Mib/Test/Test>
#include <Mib/Test/Performance>
#include <Mib/String/FuzzyMatch>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;

#if defined(DMibDebug) || defined(DMibSanitizerEnabled)
	static constexpr umint gc_nIterationsShort = 1'000;
	static constexpr umint gc_nIterationsMedium = 500;
	static constexpr umint gc_nIterationsLong = 100;
#else
	static constexpr umint gc_nIterationsShort = 100'000;
	static constexpr umint gc_nIterationsMedium = 50'000;
	static constexpr umint gc_nIterationsLong = 10'000;
#endif

	static constexpr umint gc_nTries = 5;

	volatile bool gs_bSink;

	template <typename tf_FOperation>
	inline_never void fg_Measure(NTest::CTestPerformanceMeasure &_Measure, umint _nIterations, tf_FOperation const &_fOperation)
	{
		auto fMeasure = [&_fOperation, _nIterations]() inline_never
			{
				for (umint i = 0; i < _nIterations; ++i)
					_fOperation();
			}
		;
		for (umint iTry = 0; iTry < gc_nTries; ++iTry)
		{
			DMibTestScopeMeasure(_Measure, _nIterations);
			fMeasure();
		}
	}

	struct CFuzzyMatchPerformance_Tests : public NMib::NTest::CTest
	{
		// Short strings: typical filename/command matching
		void fp_ShortStrings()
		{
			DMibTestSuite(NTest::CTestCategory("ShortStrings") << NTest::CTestGroup("Performance"))
			{
				{
					DMibTestPath("ExactMatch");
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsShort
							, []() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(gc_Str<"hello">.m_Str, gc_Str<"hello">.m_Str);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("SubstringMatch");
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsShort
							, []() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(gc_Str<"hello world">.m_Str, gc_Str<"world">.m_Str);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("PartialMatch");
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsShort
							, []() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(gc_Str<"hello world">.m_Str, gc_Str<"hllo wrd">.m_Str);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("CaseInsensitive");
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsShort
							, []() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(gc_Str<"Hello World">.m_Str, gc_Str<"hello world">.m_Str);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("NoMatch");
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsShort
							, []() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(gc_Str<"abcdef">.m_Str, gc_Str<"xyz">.m_Str);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}
			};
		}

		// Medium strings: typical file path matching
		void fp_MediumStrings()
		{
			DMibTestSuite(NTest::CTestCategory("MediumStrings") << NTest::CTestGroup("Performance"))
			{
				CStr Candidate = "/opt/Source/Malterlib/Malterlib/String/Source/Malterlib_String_FuzzyMatch.cpp";
				CStr Query = "FuzzyMatch.cpp";

				{
					DMibTestPath("PathSubstring");
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsMedium
							, [&]() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(Candidate, Query);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("PathPartial");
					CStr PartialQuery = "strfzy";
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsMedium
							, [&]() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(Candidate, PartialQuery);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("PathNoMatch");
					CStr NoMatchQuery = "zzzzzzz";
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsMedium
							, [&]() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(Candidate, NoMatchQuery);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}
			};
		}

		// Long strings: stress test with repeated patterns
		void fp_LongStrings()
		{
			DMibTestSuite(NTest::CTestCategory("LongStrings") << NTest::CTestGroup("Performance"))
			{
				// Build a long candidate with repeated patterns
				CStr LongCandidate;
				for (umint i = 0; i < 20; ++i)
					LongCandidate += "/opt/Source/Malterlib/Malterlib/String/Source/Malterlib_String_FuzzyMatch.cpp";

				{
					DMibTestPath("LongCandidateSubstring");
					CStr Query = "FuzzyMatch.cpp";
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsLong
							, [&]() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(LongCandidate, Query);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("LongCandidatePartial");
					CStr PartialQuery = "strfzymtch";
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsLong
							, [&]() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(LongCandidate, PartialQuery);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("LongBothStrings");
					CStr LongQuery;
					for (umint i = 0; i < 5; ++i)
						LongQuery += "Malterlib_String_FuzzyMatch";
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsLong
							, [&]() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(LongCandidate, LongQuery);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}
			};
		}

		// Worst case: many repeated characters causing lots of partial matches
		void fp_WorstCase()
		{
			DMibTestSuite(NTest::CTestCategory("WorstCase") << NTest::CTestGroup("Performance"))
			{
				{
					DMibTestPath("RepeatedCharacters");
					CStr Candidate;
					for (umint i = 0; i < 200; ++i)
						Candidate += "a";
					CStr Query;
					for (umint i = 0; i < 20; ++i)
						Query += "a";
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsLong
							, [&]() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(Candidate, Query);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}

				{
					DMibTestPath("OverlappingPatterns");
					CStr Candidate;
					for (umint i = 0; i < 50; ++i)
						Candidate += "abab";
					CStr Query = "ababababab";
					NTest::CTestPerformanceMeasure Measure("FuzzyMatch");
					fg_Measure
						(
							Measure
							, gc_nIterationsLong
							, [&]() inline_always_lambda
							{
								auto Result = fg_FuzzyMatchString(Candidate, Query);
								gs_bSink = bool(Result);
							}
						)
					;
					NTest::CTestPerformance PerfTest(0.0, false);
					PerfTest.f_Add(Measure);
					DMibExpectTrue(PerfTest);
				}
			};
		}

		void f_DoTests()
		{
			fp_ShortStrings();
			fp_MediumStrings();
			fp_LongStrings();
			fp_WorstCase();
		}
	};

	DMibTestRegister(CFuzzyMatchPerformance_Tests, Malterlib::String::Algorithm);
}
