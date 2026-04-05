// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>
#include <Mib/String/FuzzyMatch>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;

	struct CFuzzyMatch_Tests : public NMib::NTest::CTest
	{
		void fp_BasicTests()
		{
			DMibTestSuite("Basic")
			{
				{
					DMibTestPath("IdenticalStrings");
					auto Result = fg_FuzzyMatchString("hello", "hello");
					DMibExpect(bool(Result), ==, true);
					DMibExpect(Result.m_Score, ==, 0.0);
				}

				{
					DMibTestPath("CaseInsensitive");
					auto Result = fg_FuzzyMatchString("Hello", "hello");
					DMibExpect(bool(Result), ==, true);
					// Case mismatch should produce a small positive score
					DMibExpect(Result.m_Score, >, 0.0);
					DMibExpect(Result.m_Score, <, 0.1);

					auto Result2 = fg_FuzzyMatchString("HELLO WORLD", "hello world");
					DMibExpect(bool(Result2), ==, true);
					DMibExpect(Result2.m_Score, >, 0.0);
					DMibExpect(Result2.m_Score, <, 0.1);
				}

				{
					DMibTestPath("CaseMatch");
					auto Result1 = fg_FuzzyMatchString("HeLLo WoRLd", "hello world");
					auto Result2 = fg_FuzzyMatchString("hello world", "hello world");
					DMibExpect(bool(Result1), ==, true);
					DMibExpect(bool(Result2), ==, true);
					// Exact case should score better (lower) than mismatched case
					DMibExpect(Result2.m_Score, <, Result1.m_Score);
				}

				{
					DMibTestPath("SingleCharacter");
					auto Same = fg_FuzzyMatchString("a", "a");
					DMibExpect(bool(Same), ==, true);
					DMibExpect(Same.m_Score, ==, 0.0);

					auto Different = fg_FuzzyMatchString("a", "b");
					DMibExpect(bool(Different), ==, false);
				}

				{
					DMibTestPath("EmptyStrings");
					auto Result1 = fg_FuzzyMatchString("", "hello");
					DMibExpect(bool(Result1), ==, false);

					auto Result2 = fg_FuzzyMatchString("hello", "");
					DMibExpect(bool(Result2), ==, false);
				}
			};
		}

		void fp_QualityTests()
		{
			DMibTestSuite("Quality")
			{
				{
					DMibTestPath("CompletelyDifferent");
					auto Result = fg_FuzzyMatchString("abcdef", "ghijkl");
					// No characters match, should return invalid
					DMibExpect(bool(Result), ==, false);
				}

				{
					DMibTestPath("PartialMatch");
					auto Result = fg_FuzzyMatchString("hello world", "hello");
					DMibExpect(bool(Result), ==, true);
					DMibExpect(Result.m_Score, >, 0.0);
					DMibExpect(Result.m_Score, <, 1.0);
				}

				{
					DMibTestPath("SimilarBetterThanDissimilar");
					auto Similar = fg_FuzzyMatchString("hello", "hallo");
					auto Dissimilar = fg_FuzzyMatchString("hello", "xyz");
					DMibExpect(bool(Similar), ==, true);
					// Dissimilar may or may not match at all
					if (Dissimilar)
						DMibExpect(Similar.m_Score, <, Dissimilar.m_Score);
				}

				{
					DMibTestPath("SubstringBetterThanDifferent");
					auto Substring = fg_FuzzyMatchString("hello world", "world");
					auto Different = fg_FuzzyMatchString("hello world", "zzzzz");
					DMibExpect(bool(Substring), ==, true);
					// "zzzzz" should not match "hello world" at all
					DMibExpect(bool(Different), ==, false);
				}

				{
					DMibTestPath("LongerMatchIsBetter");
					auto ShortMatch = fg_FuzzyMatchString("abcxyz", "abc");
					auto LongMatch = fg_FuzzyMatchString("abcxyz", "abcxy");
					DMibExpect(bool(ShortMatch), ==, true);
					DMibExpect(bool(LongMatch), ==, true);
					DMibExpect(LongMatch.m_Score, <, ShortMatch.m_Score);
				}

				{
					DMibTestPath("BothDirectionsReasonable");
					auto Result1 = fg_FuzzyMatchString("hello world", "world");
					auto Result2 = fg_FuzzyMatchString("world", "hello world");
					DMibExpect(bool(Result1), ==, true);
					DMibExpect(Result1.m_Score, >, 0.0);
					DMibExpect(Result1.m_Score, <, 1.0);
					DMibExpect(bool(Result2), ==, true);
					DMibExpect(Result2.m_Score, >, 0.0);
					DMibExpect(Result2.m_Score, <, 1.0);
				}

				{
					DMibTestPath("RepeatedSubstrings");
					auto Result = fg_FuzzyMatchString("abcabc", "abc");
					DMibExpect(bool(Result), ==, true);
					DMibExpect(Result.m_Score, >, 0.0);
					DMibExpect(Result.m_Score, <, 1.0);
				}
			};
		}

		void fp_MatchRangeTests()
		{
			DMibTestSuite("MatchRanges")
			{
				{
					DMibTestPath("ExactMatch");
					auto Result = fg_FuzzyMatchString("hello", "hello");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 1u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 0);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 5);
				}

				{
					DMibTestPath("SubstringMatch");
					auto Result = fg_FuzzyMatchString("hello world", "world");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 1u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 6);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 11);
				}

				{
					DMibTestPath("RepeatedSubstringPrefersBestContiguousMatch");
					auto Result = fg_FuzzyMatchString("aaA", "aA");
					DMibExpect(bool(Result), ==, true);
					DMibExpect(Result.m_Score, <, 0.05);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 1u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 1);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 3);
				}

				{
					DMibTestPath("RepeatedSubstringPrefersBestContiguousMatch2");
					auto Result = fg_FuzzyMatchString("aaaAa", "aA");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 1u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 2);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 4);
				}

				{
					DMibTestPath("RepeatedSubstringPrefersBestCase");
					auto Result = fg_FuzzyMatchString("aaaaA", "AaAb");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 1u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 2);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 5);
				}

				{
					DMibTestPath("RepeatedSubstringPrefersBestCase2");
					auto Result = fg_FuzzyMatchString("aaaaAa", "AaAb");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 1u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 2);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 5);
				}

				{
					DMibTestPath("FoundBug1");
					auto Result = fg_FuzzyMatchString("generate", "genee");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 2u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 0);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 4);
					DMibExpect(Result.m_Matches[1].m_iStart, ==, 7);
					DMibExpect(Result.m_Matches[1].m_iEnd, ==, 8);
				}

				{
					DMibTestPath("FoundBug1Reverse");
					auto Result = fg_FuzzyMatchString("generate", "eegen");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 2u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 0);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 4);
					DMibExpect(Result.m_Matches[1].m_iStart, ==, 7);
					DMibExpect(Result.m_Matches[1].m_iEnd, ==, 8);
				}

				{
					DMibTestPath("RepeatedMultiCharMatch2");
					auto Result = fg_FuzzyMatchString("abXab", "abab");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 2u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 0);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 2);
					DMibExpect(Result.m_Matches[1].m_iStart, ==, 3);
					DMibExpect(Result.m_Matches[1].m_iEnd, ==, 5);
				}

				{
					DMibTestPath("RepeatedMultiCharMatch3");
					auto Result = fg_FuzzyMatchString("abcXXabc", "abcabc");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 2u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 0);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 3);
					DMibExpect(Result.m_Matches[1].m_iStart, ==, 5);
					DMibExpect(Result.m_Matches[1].m_iEnd, ==, 8);
				}

				{
					// "generete" has isolated 'e' at positions 5 and 7 (plus 1,3 in "gene").
					// Chain from head 1: 1→5→4→3 (4 nodes). candidate[7] traverses 3 nodes.
					DMibTestPath("ChainLength4");
					auto Result = fg_FuzzyMatchString("generete", "geneee");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 3u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 0);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 4);
					DMibExpect(Result.m_Matches[1].m_iStart, ==, 5);
					DMibExpect(Result.m_Matches[1].m_iEnd, ==, 6);
					DMibExpect(Result.m_Matches[2].m_iStart, ==, 7);
					DMibExpect(Result.m_Matches[2].m_iEnd, ==, 8);
				}

				{
					// "generetexe" has isolated 'e' at positions 5, 7, 9.
					// Chain from head 1: 1→6→5→4→3 (5 nodes). candidate[9] traverses 4 nodes.
					DMibTestPath("ChainLength5");
					auto Result = fg_FuzzyMatchString("generetexe", "geneeee");
					DMibExpect(bool(Result), ==, true);
					DMibAssert(Result.m_Matches.f_GetLen(), ==, 4u);
					DMibExpect(Result.m_Matches[0].m_iStart, ==, 0);
					DMibExpect(Result.m_Matches[0].m_iEnd, ==, 4);
					DMibExpect(Result.m_Matches[1].m_iStart, ==, 5);
					DMibExpect(Result.m_Matches[1].m_iEnd, ==, 6);
					DMibExpect(Result.m_Matches[2].m_iStart, ==, 7);
					DMibExpect(Result.m_Matches[2].m_iEnd, ==, 8);
					DMibExpect(Result.m_Matches[3].m_iStart, ==, 9);
					DMibExpect(Result.m_Matches[3].m_iEnd, ==, 10);
				}
			};
		}

		void f_DoTests()
		{
			fp_BasicTests();
			fp_QualityTests();
			fp_MatchRangeTests();
		}
	};

	DMibTestRegister(CFuzzyMatch_Tests, Malterlib::String::Algorithm);
}
