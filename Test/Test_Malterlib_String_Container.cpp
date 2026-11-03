// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifdef DCompiler_MSVC
#	pragma warning(disable:4459)
#	pragma warning(disable:4828)
#endif

#include <Mib/Test/Memory>
#include <Mib/Test/Performance>

#include <Mib/String/String>

#include <vector>
#include <memory>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/stl.hpp>
#include <boost/algorithm/string/find.hpp>
#include <sstream>

#include <Mib/Test/Memory>
#include <Mib/Test/Test>
#include <Mib/Time/PerfTimeMeasure>

using namespace NMib;
using namespace NMib::NTime;
using namespace NMib::NContainer;
using namespace NMib::NTest;
using namespace NMib::NTraits;

NStr::CStr const &fg_GetTestStringInAnotherTranslationUnit()
{
	return NStr::gc_Str<"TestString">.m_Str;
}

namespace
{
	using namespace NMib::NStr;
	using namespace NMib::NStorage;
	namespace NQi = boost::spirit::qi;
	namespace NKarma = boost::spirit::karma;

	struct CStr_Tests : public CTest
	{
		template <bool t_bMemoryTests>
		struct TCTests
		{
			using CMeasureType = TCConditional<t_bMemoryTests, CTestMemoryMeasure, CTestPerformanceMeasure>;
			using CTestType = TCConditional<t_bMemoryTests, CTestMemoryNumAllocations, CTestPerformance>;

			static constexpr umint mc_VectorSize = 512;
			static CStr fs_GenerateHexList()
			{
				using CValue = int32;
				using NKarma::hex;

				std::vector<CValue> const Vector(mc_VectorSize, 12345);

				CMeasureType MalterlibAllocTime("Malterlib");
				CMeasureType MalterlibAllocReserveTime("Malterlib");
				CMeasureType MalterlibNoAllocTime("Malterlib");

				CMeasureType MalterlibStaticNoAllocTime("Malterlib");
				CMeasureType MalterlibStaticAllocTime("Malterlib");
				CMeasureType MalterlibStaticAllocReserveTime("Malterlib");

				CMeasureType KarmaStaticAllocTime("Karma");
				CMeasureType KarmaStaticAllocReserveTime("Karma");
				CMeasureType KarmaStaticNoAllocTime("Karma");

				CMeasureType KarmaManualStaticAllocTime("Karma Manual");
				CMeasureType KarmaManualStaticNoAllocTime("Karma Manual");
				CMeasureType KarmaManualStaticAllocReserveTime("Karma Manual");

				// Test 100 times and pick the fastest

				umint NeededCharSize = mc_VectorSize * 5 + 3;
				CStr MalterlibAllocResult;
				CStr MalterlibAllocReserveResult;
				CStr MalterlibStaticAllocResult;
				CStr MalterlibStaticAllocReserveResult;
				std::string KarmaResult;
				std::string KarmaReserveResult;
				std::string KarmaManualStaticAllocResult;
				std::string KarmaManualStaticAllocReserveResult;
				TCVector<ch8> KarmaCharResult;
				KarmaCharResult.f_SetLen(NeededCharSize);
				TCVector<ch8> MalterlibNoAllocResultData;
				MalterlibNoAllocResultData.f_SetLen(NeededCharSize);
				TCVector<ch8> MalterlibStaticNoAllocResultData;
				MalterlibStaticNoAllocResultData.f_SetLen(NeededCharSize);
				TCVector<ch8> KarmaManualStaticNoAllocResult;
				KarmaManualStaticNoAllocResult.f_SetLen(NeededCharSize);

				CStrPtr MalterlibNoAllocResult;
				MalterlibNoAllocResult.f_SetPtr(MalterlibNoAllocResultData.f_GetArray(), NeededCharSize);
				CStrPtr MalterlibStaticNoAllocResult;
				MalterlibStaticNoAllocResult.f_SetPtr(MalterlibStaticNoAllocResultData.f_GetArray(), NeededCharSize);

#ifdef DMibDebug
				static int const s_nTests = 100;
#else
				static int const s_nTests = 100;
#endif
				auto Karma = [&]()
					{
						KarmaResult = std::string();
						{ // Timing boost.spirit
							KarmaStaticAllocTime.f_Start();

							std::back_insert_iterator<std::string> iInserter(KarmaResult);
							NKarma::generate(iInserter, '[' << hex % ',' << ']', Vector);

							KarmaStaticAllocTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto KarmaReserve = [&]()
					{
						KarmaReserveResult = std::string();
						KarmaReserveResult.reserve(NeededCharSize);
						{ // Timing boost.spirit
							KarmaStaticAllocReserveTime.f_Start();

							std::back_insert_iterator<std::string> iInserter(KarmaReserveResult);
							NKarma::generate(iInserter, '[' << hex % ',' << ']', Vector);

							KarmaStaticAllocReserveTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto KarmaChar = [&]()
					{
						{ // Timing boost.spirit
							KarmaStaticNoAllocTime.f_Start();

							ch8 *pGenerate = KarmaCharResult.f_GetArray();
							NKarma::generate(pGenerate, '[' << hex % ',' << ']', Vector);
							*pGenerate = 0;

							KarmaStaticNoAllocTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto KarmaManualStaticAlloc = [&]()
					{
						KarmaManualStaticAllocResult = std::string();
						{ // Timing boost.spirit
							KarmaManualStaticAllocTime.f_Start();

							std::back_insert_iterator<std::string> OutIter(KarmaManualStaticAllocResult);

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							*OutIter = '[';
							++OutIter;
							if (Iter != IterEnd)
							{
								NKarma::generate(OutIter, hex, *Iter);
								++Iter;
								for (; Iter != IterEnd; ++Iter)
									NKarma::generate(OutIter, ',' << hex, *Iter);
							}
							*OutIter = ']';
							++OutIter;

							KarmaManualStaticAllocTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto KarmaManualStaticAllocReserve = [&]()
					{
						KarmaManualStaticAllocReserveResult = std::string();
						KarmaManualStaticAllocReserveResult.reserve(NeededCharSize);
						KarmaManualStaticAllocReserveTime.f_Start();
						{ // Timing boost.spirit

							std::back_insert_iterator<std::string> OutIter(KarmaManualStaticAllocReserveResult);

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							*OutIter = '[';
							++OutIter;
							if (Iter != IterEnd)
							{
								NKarma::generate(OutIter, hex, *Iter);
								++Iter;
								for (; Iter != IterEnd; ++Iter)
									NKarma::generate(OutIter, ',' << hex, *Iter);
							}
							*OutIter = ']';
							++OutIter;
						}
						KarmaManualStaticAllocReserveTime.f_Stop(mc_VectorSize);
					}
				;
				auto KarmaManualStaticNoAlloc = [&]()
					{
						KarmaManualStaticNoAllocTime.f_Start();
						{ // Timing boost.spirit

							ch8 *pGenerate = KarmaManualStaticNoAllocResult.f_GetArray();

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							*pGenerate = '[';
							++pGenerate;
							if (Iter != IterEnd)
							{
								NKarma::generate(pGenerate, hex, *Iter);
								++Iter;
								for (; Iter != IterEnd; ++Iter)
									NKarma::generate(pGenerate, ',' << hex, *Iter);
							}
							*pGenerate = ']';
							++pGenerate;
							*pGenerate = 0;
						}
						KarmaManualStaticNoAllocTime.f_Stop(mc_VectorSize);
					}
				;

				auto MalterlibAlloc = [&]()
					{
						MalterlibAllocResult.f_Clear();
						{ // Timing CStr::Parse
							MalterlibAllocTime.f_Start();

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							MalterlibAllocResult += '[';

							if (Iter != IterEnd)
							{
								MalterlibAllocResult += (CStr::CFormat("{nh}") << *Iter);
								++Iter;
								CValue Value;
								CStr::CFormat Format(",{nh}");
								Format << Value;
								for (; Iter != IterEnd; ++Iter)
								{
									Value = *Iter;
									MalterlibAllocResult += Format;
								}
							}

							MalterlibAllocResult += ']';

							MalterlibAllocTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto MalterlibAllocReserve = [&]()
					{
						MalterlibAllocReserveResult.f_Clear();
						MalterlibAllocReserveResult.f_Reserve(NeededCharSize);
						{ // Timing CStr::Parse
							MalterlibAllocReserveTime.f_Start();

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							MalterlibAllocReserveResult += '[';
							if (Iter != IterEnd)
							{
								MalterlibAllocReserveResult += (CStr::CFormat("{nh}") << *Iter);
								++Iter;
								CValue Value;
								CStr::CFormat Format(",{nh}");
								Format << Value;
								for (; Iter != IterEnd; ++Iter)
								{
									Value = *Iter;
									MalterlibAllocReserveResult += Format;
								}
							}
							MalterlibAllocReserveResult += ']';

							MalterlibAllocReserveTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto MalterlibNoAlloc = [&]()
					{
						MalterlibNoAllocResult.f_Clear();
						{ // Timing CStr::Parse
							MalterlibNoAllocTime.f_Start();

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							MalterlibNoAllocResult += '[';
							if (Iter != IterEnd)
							{
								MalterlibNoAllocResult += (CStrPtr::CFormat("{nh}") << *Iter);
								++Iter;
								CValue Value;
								CStrPtr::CFormat Format(",{nh}");
								Format << Value;
								for (; Iter != IterEnd; ++Iter)
								{
									Value = *Iter;
									MalterlibNoAllocResult += Format;
								}
							}
							MalterlibNoAllocResult += ']';

							MalterlibNoAllocTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto MalterlibStaticNoAlloc = [&]()
					{
						MalterlibStaticNoAllocResult.f_Clear();
						{ // Timing CStr::Parse
							MalterlibStaticNoAllocTime.f_Start();

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							aint StrLen = 0;
							MalterlibStaticNoAllocResult.f_AddCharLengthAware(StrLen, '[');
							if (Iter != IterEnd)
							{
								CStrPtr::fs_ToStrInplaceConcat(MalterlibStaticNoAllocResult, fg_FormatIntFormat<16>(*Iter), StrLen);
								++Iter;
								for (; Iter != IterEnd; ++Iter)
								{
									MalterlibStaticNoAllocResult.f_AddCharLengthAware(StrLen, ',');
									CStrPtr::fs_ToStrInplaceConcat(MalterlibStaticNoAllocResult, fg_FormatIntFormat<16>(*Iter), StrLen);
								}
							}
							MalterlibStaticNoAllocResult.f_AddCharLengthAware(StrLen, ']');
							MalterlibStaticNoAllocResult.f_SetStrLen(StrLen);

							MalterlibStaticNoAllocTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto MalterlibStaticAlloc = [&]()
					{
						MalterlibStaticAllocResult.f_Clear();
						{ // Timing CStr::Parse
							MalterlibStaticAllocTime.f_Start();

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							aint StrLen = 0;
							MalterlibStaticAllocResult.f_AddCharLengthAware(StrLen, '[');
							if (Iter != IterEnd)
							{
								CStr::fs_ToStrInplaceConcat(MalterlibStaticAllocResult, fg_FormatIntFormat<16>(*Iter), StrLen);
								++Iter;
								for (; Iter != IterEnd; ++Iter)
								{
									MalterlibStaticAllocResult.f_AddCharLengthAware(StrLen, ',');
									CStr::fs_ToStrInplaceConcat(MalterlibStaticAllocResult, fg_FormatIntFormat<16>(*Iter), StrLen);
								}
							}
							MalterlibStaticAllocResult.f_AddCharLengthAware(StrLen, ']');
							MalterlibStaticAllocResult.f_SetStrLen(StrLen);

							MalterlibStaticAllocTime.f_Stop(mc_VectorSize);
						}
					}
				;
				auto MalterlibStaticAllocReserve = [&]()
					{
						MalterlibStaticAllocReserveResult.f_Clear();
						MalterlibStaticAllocReserveResult.f_Reserve(NeededCharSize);
						{ // Timing CStr::Parse
							MalterlibStaticAllocReserveTime.f_Start();

							auto Iter = Vector.begin();
							auto IterEnd = Vector.end();
							aint StrLen = 0;
							MalterlibStaticAllocReserveResult.f_AddCharLengthAware(StrLen, '[');
							if (Iter != IterEnd)
							{
								CStr::fs_ToStrInplaceConcat(MalterlibStaticAllocReserveResult, fg_FormatIntFormat<16>(*Iter), StrLen);
								++Iter;
								for (; Iter != IterEnd; ++Iter)
								{
									MalterlibStaticAllocReserveResult.f_AddCharLengthAware(StrLen, ',');
									CStr::fs_ToStrInplaceConcat(MalterlibStaticAllocReserveResult, fg_FormatIntFormat<16>(*Iter), StrLen);
								}
							}
							MalterlibStaticAllocReserveResult.f_AddCharLengthAware(StrLen, ']');
							MalterlibStaticAllocReserveResult.f_SetStrLen(StrLen);

							MalterlibStaticAllocReserveTime.f_Stop(mc_VectorSize);
						}
					}
				;

				for (int iTest = 0; iTest < s_nTests; ++iTest)
					Karma();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					KarmaChar();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					KarmaReserve();

				for (int iTest = 0; iTest < s_nTests; ++iTest)
					KarmaManualStaticAlloc();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					KarmaManualStaticAllocReserve();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					KarmaManualStaticNoAlloc();

				for (int iTest = 0; iTest < s_nTests; ++iTest)
					MalterlibAlloc();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					MalterlibAllocReserve();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					MalterlibNoAlloc();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					MalterlibStaticNoAlloc();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					MalterlibStaticAlloc();
				for (int iTest = 0; iTest < s_nTests; ++iTest)
					MalterlibStaticAllocReserve();

				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaResult.c_str()))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaCharResult.f_GetArray()))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaReserveResult.c_str()))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaManualStaticAllocResult.c_str()))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaManualStaticNoAllocResult.f_GetArray()))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaManualStaticAllocReserveResult.c_str()))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibAllocReserveResult))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibNoAllocResult))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibStaticNoAllocResult))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibStaticAllocResult))(ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibStaticAllocReserveResult))(ETestFlag_NoValues);

				CTestType DynamicAlloc(1.0);
				DynamicAlloc.f_Add(MalterlibAllocTime);
				DMibTest(DMibExpr(DynamicAlloc));

				CTestType DynamicAllocReserve(1.0);
				DynamicAllocReserve.f_Add(MalterlibAllocReserveTime);
				DMibTest(DMibExpr(DynamicAllocReserve));

				CTestType DynamicNoAlloc(1.0);
				DynamicNoAlloc.f_Add(MalterlibNoAllocTime);
				DMibTest(DMibExpr(DynamicNoAlloc));

				CTestType StaticAlloc(1.0);
				StaticAlloc.f_AddReference(KarmaStaticAllocTime);
				StaticAlloc.f_AddReference(KarmaManualStaticAllocTime);
				StaticAlloc.f_Add(MalterlibStaticAllocTime);
				DMibTest(DMibExpr(StaticAlloc));

				CTestType StaticAllocReserve(1.0);
				StaticAllocReserve.f_AddReference(KarmaStaticAllocReserveTime);
				StaticAllocReserve.f_AddReference(KarmaManualStaticAllocReserveTime);
				StaticAllocReserve.f_Add(MalterlibStaticAllocReserveTime);
				DMibTest(DMibExpr(StaticAllocReserve));

				CTestType StaticNoAlloc(1.0);
				StaticNoAlloc.f_AddReference(KarmaStaticNoAllocTime);
				StaticNoAlloc.f_AddReference(KarmaManualStaticNoAllocTime);
				StaticNoAlloc.f_Add(MalterlibStaticNoAllocTime);
				DMibTest(DMibExpr(StaticNoAlloc));

				return MalterlibAllocResult;
			}

			static void fs_DecodeHexList(CStr const &_HexList)
			{
				using NQi::hex;
				using CValue = int32;

				// Generate test data

				CMeasureType MalterlibTimer("Malterlib");
				CMeasureType ManualTimer("Malterlib Parse");
				CMeasureType ManualHexOnlyTimer("Malterlib Parse Hex");
				CMeasureType SpiritTimer("Spirit");
				CMeasureType SpiritSemanticTimer("Spirit Lambda");
				std::vector<CValue> MalterlibVector;
				std::vector<CValue> SpiritVector;
				std::vector<CValue> SpiritSemanticVector;
				std::vector<CValue> ManualVector;
				std::vector<CValue> ManualHexOnlyVector;
#ifdef DMibDebug
				static int const s_nTests = 100;
#else
				static int const s_nTests = 100;
#endif
				// Test 100 times and pick the fastest
				for (int iTest = 0; iTest < s_nTests; ++iTest)
				{
					std::string HexListStdStr(_HexList.f_GetStr());
					SpiritVector.clear();
					{ // Timing boost.spirit
						SpiritTimer.f_Start();

						std::string::iterator iBegin = HexListStdStr.begin();
						NQi::parse(iBegin, HexListStdStr.end(), ('[' >> hex % ',' >> ']'), SpiritVector);

						SpiritTimer.f_Stop(mc_VectorSize);
					}
				}
				for (int iTest = 0; iTest < s_nTests; ++iTest)
				{
					std::string HexListStdStr(_HexList.f_GetStr());
					SpiritSemanticVector.clear();
					{ // Timing boost.spirit
						SpiritSemanticTimer.f_Start();

						std::string::iterator iBegin = HexListStdStr.begin();
						auto Lamba = [&SpiritSemanticVector](CValue const &_Value, boost::spirit::unused_type _Context, bool _bPass)
							{
								SpiritSemanticVector.push_back(_Value);
							}
						;
						NQi::parse(iBegin, HexListStdStr.end(), ('[' >> hex[Lamba] % ',' >> ']'));

						SpiritSemanticTimer.f_Stop(mc_VectorSize);
					}
				}
				for (int iTest = 0; iTest < s_nTests; ++iTest)
				{
					MalterlibVector.clear();
					{ // Timing CStr::Parse
						CValue Value;
						MalterlibTimer.f_Start();

						CStr::CChar const *pParse = _HexList;
						pParse = (TCStrParse<CStr::CStrTraits>("[{nh}") >> Value).f_Parse(pParse);
						MalterlibVector.push_back(Value);
						TCStrParse<CStr::CStrTraits> Parser(",{nh}");
						Parser >> Value;
						while (*pParse != ']')
						{
							pParse = Parser.f_Parse(pParse);
							MalterlibVector.push_back(Value);
						}

						MalterlibTimer.f_Stop(mc_VectorSize);
					}
				}
				for (int iTest = 0; iTest < s_nTests; ++iTest)
				{
					ManualVector.clear();
					{ // Timing Manual
						ManualTimer.f_Start();

						CValue Value;
						CStr::CChar const *pParse = _HexList;
						if (*pParse == '[')
							++pParse;
						while (*pParse && *pParse != ']')
						{
							Value = fg_StrToIntParse(pParse, CValue(-1), (CStr::CChar const *)nullptr, true, EStrToIntParseMode_Hex);
							ManualVector.push_back(Value);
							if (*pParse == ',')
								++pParse;
						}

						ManualTimer.f_Stop(mc_VectorSize);
					}
				}
				for (int iTest = 0; iTest < s_nTests; ++iTest)
				{
					ManualHexOnlyVector.clear();
					{ // Timing manual hex only
						ManualHexOnlyTimer.f_Start();

						CValue Value;
						CStr::CChar const *pParse = _HexList;
						if (*pParse == '[')
							++pParse;
						while (*pParse && *pParse != ']')
						{
							Value = fg_StrToIntParseHexNoSign(pParse, CValue(-1));
							ManualHexOnlyVector.push_back(Value);
							if (*pParse == ',')
								++pParse;
						}

						ManualHexOnlyTimer.f_Stop(mc_VectorSize);
					}
				}
				DMibTest(DMibExpr(MalterlibVector == SpiritVector));
				DMibTest(DMibExpr(SpiritSemanticVector == SpiritVector));
				DMibTest(DMibExpr(ManualVector == SpiritVector));
				DMibTest(DMibExpr(ManualHexOnlyVector == SpiritVector));

				CTestType ParsePerformance(1.0);

				ParsePerformance.f_AddReference(SpiritTimer);
				ParsePerformance.f_AddReference(SpiritSemanticTimer);
				ParsePerformance.f_Add(MalterlibTimer);
				ParsePerformance.f_Add(ManualTimer);
				ParsePerformance.f_Add(ManualHexOnlyTimer);

				DMibTest(DMibExpr(ParsePerformance));
			}

			/*
			CStr::CFormat f_GenerateFormatStr()
			{
				CStr fmtstr = "{} ";
				fmtstr += "{}";
				return CStr::CFormat(fmtstr);
			}*/

			void f_FormatInt()
			{
#ifdef DMibDebug
				static umint const s_nTestsGlobal = 10;
#else
				static umint const s_nTestsGlobal = 1000;
#endif
				static int32 const s_nLoopsGlobal = 10000;
				// Do

				DMibTestCategory("Static")
				{
					static umint const s_nTestsPropagate = s_nTestsGlobal;
					static int32 const s_nLoopsPropagate = s_nLoopsGlobal;
					{
						static umint const s_nTests = s_nTestsPropagate;
						static int32 const s_nLoops = s_nLoopsPropagate;
						CMeasureType MalterlibTime("Malterlib CFStr16");
						CFStr16 MalterlibResult;

						CMeasureType MalterlibCFStr16InplaceTime("Malterlib CFStr16 inplace");
						{
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCFStr16InplaceTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									CFStr16::fs_ToStrInplace(MalterlibResult, iLoop);

								MalterlibCFStr16InplaceTime.f_Stop(s_nLoops);
							}
						};

						CMeasureType KarmaTime("Karma");
						{
							using NKarma::int_;
							ch8 Result[16];
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								KarmaTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									ch8 *pGenerate = Result;
									NKarma::generate(pGenerate, int_, iLoop);
									*pGenerate = 0;
								}

								KarmaTime.f_Stop(s_nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType MalterlibCStrPtrTime("Malterlib CStrPtr");
						{
							CPrefCyclesTimeMeasureMin Time;
							ch8 ResultData[12];
							CStrPtr Result;
							Result.f_SetPtr(ResultData, 12);
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCStrPtrTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									CStrPtr::fs_ToStrInplace(Result, iLoop);

								MalterlibCStrPtrTime.f_Stop(s_nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType MalterlibCFStr16Time("Malterlib CFStr16");
						{
							CFStr16 Result;
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCFStr16Time.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									Result = CFStr16::fs_ToStr(iLoop);

								MalterlibCFStr16Time.f_Stop(s_nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
#if defined(DPlatformFamily_Windows)
						CMeasureType ItoaTime("itoa");
						{
							CPrefCyclesTimeMeasureMin Time;
							char Result[12];
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								ItoaTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									_itoa(iLoop, Result, 10);

								ItoaTime.f_Stop(s_nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
#endif
						CTestType NoAlloc(1.0);
						NoAlloc.f_AddReference(KarmaTime);
#if defined(DPlatformFamily_Windows)
						NoAlloc.f_AddReference(ItoaTime);
#endif
						NoAlloc.f_Add(MalterlibCFStr16InplaceTime);
						NoAlloc.f_Add(MalterlibCStrPtrTime);
						NoAlloc.f_Add(MalterlibCFStr16Time);
						DMibTest(DMibExpr(NoAlloc));
					};

					{
						static umint const s_nTests = s_nTestsPropagate;
						static int32 const s_nLoops = s_nLoopsPropagate;
						CStr MalterlibResult;
						CMeasureType MalterlibCStrInplaceTime("Malterlib CStr inplace");
						{
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCStrInplaceTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									MalterlibResult.f_Clear();
									CStr::fs_ToStrInplace(MalterlibResult, iLoop);
								}

								MalterlibCStrInplaceTime.f_Stop(s_nLoops);
							}
						};
						CMeasureType KarmaTime("Karma");
						{
							using NKarma::int_;
							CPrefCyclesTimeMeasureMin Time;
							std::string Result;
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								KarmaTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Result = std::string();
									std::back_insert_iterator<std::string> iInserter(Result);
									NKarma::generate(iInserter, int_, iLoop);
								}

								KarmaTime.f_Stop(s_nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
						CMeasureType MalterlibCStrTime("Malterlib CStr");
						{
							CPrefCyclesTimeMeasureMin Time;
							CStr Result;
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCStrTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									Result = CStr::fs_ToStr(iLoop);

								MalterlibCStrTime.f_Stop(s_nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType StringStreamTime("stringstream");
						{
							CPrefCyclesTimeMeasureMin Time;
							std::string Result;
							std::stringstream Stream;
							for (umint iTest = 0; iTest < s_nTests / 10; ++iTest)
							{
								StringStreamTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Stream.str("");
									Stream.clear();
									Stream << iLoop;
									Result = Stream.str();
								}

								StringStreamTime.f_Stop(s_nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
						CTestType Alloc(1.0);
						Alloc.f_AddReference(KarmaTime);
						Alloc.f_AddReference(StringStreamTime);
						Alloc.f_Add(MalterlibCStrInplaceTime);
						Alloc.f_Add(MalterlibCStrTime);
						DMibTest(DMibExpr(Alloc))(ETest_ExpectFail); // We need a CStr that has storage interally when possible
					};
					{
						static umint const s_nTests = s_nTestsPropagate;
						static int32 const s_nLoops = s_nLoopsPropagate;
						CStr MalterlibResult;
						CMeasureType MalterlibCStrInplaceTime("Malterlib CStr inplace");
						{
							MalterlibResult.f_Reserve(12);
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCStrInplaceTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									CStr::fs_ToStrInplace(MalterlibResult, iLoop);

								MalterlibCStrInplaceTime.f_Stop(s_nLoops);
							}
						};
						CMeasureType KarmaTime("Karma");
						{
							using NKarma::int_;
							CPrefCyclesTimeMeasureMin Time;
							std::string Result;
							Result.reserve(12);
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								KarmaTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Result.clear();
									std::back_insert_iterator<std::string> iInserter(Result);
									NKarma::generate(iInserter, int_, iLoop);
								}

								KarmaTime.f_Stop(s_nLoops);
							}

							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
						CMeasureType MalterlibCStrTime("Malterlib CStr");
						{
							CPrefCyclesTimeMeasureMin Time;
							CStr Result;
							Result.f_Reserve(12);
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCStrTime.f_Start();
								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									Result = CStr::fs_ToStr(iLoop);
								MalterlibCStrTime.f_Stop(s_nLoops);
							}

							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType StringStreamTime("stringstream");
						{
							CPrefCyclesTimeMeasureMin Time;
							std::string Result;
							Result.reserve(12);
							std::stringstream Stream;
							for (umint iTest = 0; iTest < s_nTests / 10; ++iTest)
							{
								StringStreamTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Stream.str("");
									Stream.clear();
									Stream << iLoop;
									Result = Stream.str();
								}

								StringStreamTime.f_Stop(s_nLoops);
							}

							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
						CTestType AllocReserve(1.0);
						AllocReserve.f_AddReference(KarmaTime);
						AllocReserve.f_AddReference(StringStreamTime);
						AllocReserve.f_Add(MalterlibCStrInplaceTime);
						AllocReserve.f_Add(MalterlibCStrTime);
						DMibTest(DMibExpr(AllocReserve));
					};
				};

				DMibTestCategory("Dynamic")
				{
					static umint const s_nTestsPropagate = s_nTestsGlobal;
					static int32 const s_nLoopsPropagate = s_nLoopsGlobal;
					{
						static umint const s_nTests = s_nTestsPropagate;
						static int32 const s_nLoops = s_nLoopsPropagate;
						CFStr16 MalterlibResult;
						CMeasureType MalterlibCFStrOptTime("Malterlib CFStr16 Opt");
						{
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCFStrOptTime.f_Start();

								CFStr16::CFormat Format("{}");
								int Value;
								Format << Value;
								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Value = iLoop;
									MalterlibResult = Format;
								}

								MalterlibCFStrOptTime.f_Stop(s_nLoops);
							}
						};
						CMeasureType MalterlibCStrPtrOptTime("Malterlib CStrPtr Opt");
						{
							ch8 ResultData[12];
							CStrPtr Result;
							Result.f_SetPtr(ResultData, 12);
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCStrPtrOptTime.f_Start();

								CStrPtr::CFormat Format("{}");
								int Value;
								Format << Value;
								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Value = iLoop;
									Result = Format;
								}

								MalterlibCStrPtrOptTime.f_Stop(s_nLoops);
							}

							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType MalterlibCFStr16Time("Malterlib CFStr16");
						{
							CFStr16 Result;
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibCFStr16Time.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									Result = CFStr16::CFormat("{}") << iLoop;

								MalterlibCFStr16Time.f_Stop(s_nLoops);
							}

							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType SprintfTime("sprintf");
						{
							CPrefCyclesTimeMeasureMin Time;
							char Result[12];
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								SprintfTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									snprintf(Result, 12, "%i", iLoop);

								SprintfTime.f_Stop(s_nLoops);
							}

							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};

						CTestType NoAlloc(1.0);
						NoAlloc.f_AddReference(SprintfTime);
						NoAlloc.f_Add(MalterlibCFStrOptTime);
						NoAlloc.f_Add(MalterlibCStrPtrOptTime);
						NoAlloc.f_Add(MalterlibCFStr16Time);
						DMibTest(DMibExpr(NoAlloc));
					};

					{
						static umint const s_nTests = s_nTestsPropagate;
						static int32 const s_nLoops = s_nLoopsPropagate;
						CMeasureType MalterlibOptTime("Malterlib Opt");
						CStr MalterlibResult;
						{
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibOptTime.f_Start();

								CStr::CFormat Format("{}");
								int Value;
								Format << Value;
								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Value = iLoop;
									MalterlibResult.f_Clear();
									MalterlibResult = Format;
								}

								MalterlibOptTime.f_Stop(s_nLoops);
							}
						};
						CMeasureType MalterlibTime("Malterlib");
						{
							CStr Result;
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Result.f_Clear();
									Result = CStr::CFormat("{}") << iLoop;
								}

								MalterlibTime.f_Stop(s_nLoops);
							}

							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CTestType Alloc(1.0);
						Alloc.f_Add(MalterlibOptTime);
						Alloc.f_Add(MalterlibTime);
						DMibTest(DMibExpr(Alloc));
					}
					{
						static umint const s_nTests = s_nTestsPropagate;
						static int32 const s_nLoops = s_nLoopsPropagate;
						CMeasureType MalterlibOptTime("Malterlib Opt");
						CStr MalterlibResult;
						{
							MalterlibResult.f_Reserve(12);
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibOptTime.f_Start();

								CStr::CFormat Format("{}");
								int Value;
								Format << Value;
								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
								{
									Value = iLoop;
									MalterlibResult = Format;
								}

								MalterlibOptTime.f_Stop(s_nLoops);
							}
						};
						CMeasureType MalterlibTime("Malterlib");
						{
							CStr Result;
							Result.f_Reserve(12);
							for (umint iTest = 0; iTest < s_nTests; ++iTest)
							{
								MalterlibTime.f_Start();

								for (int iLoop = 0; iLoop < s_nLoops; ++iLoop)
									Result = CStr::CFormat("{}") << iLoop;

								MalterlibTime.f_Stop(s_nLoops);
							}

							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CTestType AllocReserve(1.0);
						AllocReserve.f_Add(MalterlibOptTime);
						AllocReserve.f_Add(MalterlibTime);
						DMibTest(DMibExpr(AllocReserve));
					}
				};
			}
		};

		void f_TestCFormat()
		{
			{
				DMibTestPath("CFormat rvalue args");
				CStrVMem FormatString = "{} {}";
				CStrVMem::CFormat Format(FormatString);
				DMibTest(DMibExpr((Format << CStrVMem("Hello") << CStr("World")).f_GetStr()) == DMibExpr("Hello World"));
			}
		}

	public: // Define test suite
		void f_DoTests()
		{
#if 0
			// TODO: add this as unit test
			uint32 Test = 0x44444444;
			Test = NMib::fg_RoundPowerOfTwoUp(Test);

			int32 Test2 = 0x44444444;
			Test2 = NMib::fg_RoundPowerOfTwoUp(Test2);

			uint64 Test3 = 0x4444444444444444ll;
			Test3 = NMib::fg_RoundPowerOfTwoUp(Test3);

			int64 Test4 = 0x4444444444444444ll;
			Test4 = NMib::fg_RoundPowerOfTwoUp(Test4);

			uint32 Test5 = 0x44444444;
			Test5 = NMib::fg_RoundPowerOfTwoDown(Test5);

			int32 Test6 = 0x44444444;
			Test6 = NMib::fg_RoundPowerOfTwoDown(Test6);

			uint64 Test7 = 0x4444444444444444ll;
			Test7 = NMib::fg_RoundPowerOfTwoDown(Test7);

			int64 Test8 = 0x4444444444444444ll;
			Test8 = NMib::fg_RoundPowerOfTwoDown(Test8);

			DMibTrace("{nfh} {nfh} {nfh} {nfh} {nfh} {nfh} {nfh} {nfh}\r\n", Test, Test2, Test3, Test4, Test5, Test6, Test7, Test8);

			{
				uint32 Test = NMib::TCLimitsInt<uint32>::mc_Max;
				int32 TestS = NMib::TCLimitsInt<int32>::mc_Max;
				uint32 TestM = NMib::TCLimitsInt<uint32>::mc_Min;
				int32 TestMS = NMib::TCLimitsInt<int32>::mc_Min;
				int32 TestMS1 = NMib::TCLimitsInt<int32>::mc_Min + 10;
				DMibTrace("{} {} {} {}\r\n", Test, TestS, TestM, TestMS);

				DMibTrace("{}\r\n", TestMS);
				DMibTrace("{}\r\n", TestMS1);
			}
#endif

			DMibTestSuite("CFormat")
			{
				this->f_TestCFormat();
			};
			DMibTestSuite(CTestCategory("Performance") << CTestGroup("Performance"))
			{
				CStr_Tests::TCTests<false> Tests;
				CStr HexList;
				DMibTestCategory("Format hex list")
				{
					HexList = Tests.fs_GenerateHexList();
				};
				DMibTestCategory("Parse hex list")
				{
					Tests.fs_DecodeHexList(HexList);
				};

				DMibTestCategory("Format int")
				{
					Tests.f_FormatInt();
				};
			};
			DMibTestCategory(CTestCategory("Memory") << CTestGroup("Memory"))
			{
				CStr_Tests::TCTests<true> Tests;
				CStr HexList;
				DMibTestCategory("Format hex list")
				{
					HexList = Tests.fs_GenerateHexList();
				};
				DMibTestCategory("Parse hex list")
				{
					Tests.fs_DecodeHexList(HexList);
				};

				DMibTestCategory("Format int")
				{
					Tests.f_FormatInt();
				};
			};
			DMibTestSuite("Split")
			{
				{
					DMibTestPath("Empty");
					DMibExpect(CStr("Test;Test2;Test3").f_Split(";"), ==, (TCVector<CStr>{"Test", "Test2", "Test3"}));
					DMibExpect(CStr(";Test2;").f_Split(";"), ==, (TCVector<CStr>{"", "Test2", ""}));
					DMibExpect(CStr(";;").f_Split(";"), ==, (TCVector<CStr>{"", "", ""}));
					DMibExpect(CStr(";").f_Split(";"), ==, (TCVector<CStr>{"", ""}));
					DMibExpect(CStr("").f_Split(";"), ==, (TCVector<CStr>{""}));

					DMibExpect(CStr::fs_Join(TCVector<CStr>{"Test", "Test2", "Test3"}, ";"), ==, "Test;Test2;Test3");
					DMibExpect(CStr::fs_Join(TCVector<CStr>{"", "Test2", ""}, ";"), ==, ";Test2;");
					DMibExpect(CStr::fs_Join(TCVector<CStr>{"", "", ""}, ";"), ==, ";;");
					DMibExpect(CStr::fs_Join(TCVector<CStr>{"", ""}, ";"), ==, ";");
					DMibExpect(CStr::fs_Join(TCVector<CStr>{""}, ";"), ==, "");
					DMibExpect(CStr::fs_Join(TCVector<CStr>{}, ";"), ==, "");
				}
				{
					DMibTestPath("NonEmpty");
					DMibExpect(CStr("Test;Test2;Test3").f_Split<true>(";"), ==, (TCVector<CStr>{"Test", "Test2", "Test3"}));
					DMibExpect(CStr(";Test2;").f_Split<true>(";"), ==, (TCVector<CStr>{"Test2"}));
					DMibExpect(CStr(";;").f_Split<true>(";"), ==, (TCVector<CStr>{}));
					DMibExpect(CStr(";").f_Split<true>(";"), ==, (TCVector<CStr>{}));
					DMibExpect(CStr("").f_Split<true>(";"), ==, (TCVector<CStr>{}));
				}
				{
					DMibTestPath("Line");
					DMibExpect(CStr("Test\nTest2\nTest3").f_SplitLine(), ==, (TCVector<CStr>{"Test", "Test2", "Test3"}));
					DMibExpect(CStr("\nTest2\n").f_SplitLine(), ==, (TCVector<CStr>{"", "Test2", ""}));
					DMibExpect(CStr("\n\n").f_SplitLine(), ==, (TCVector<CStr>{"", "", ""}));
					DMibExpect(CStr("\n").f_SplitLine(), ==, (TCVector<CStr>{"", ""}));
					DMibExpect(CStr("").f_SplitLine(), ==, (TCVector<CStr>{""}));
				}
				{
					DMibTestPath("Line NonEmpty");
					DMibExpect(CStr("Test\nTest2\nTest3").f_SplitLine<true>(), ==, (TCVector<CStr>{"Test", "Test2", "Test3"}));
					DMibExpect(CStr("\nTest2\n").f_SplitLine<true>(), ==, (TCVector<CStr>{"Test2"}));
					DMibExpect(CStr("\n\n").f_SplitLine<true>(), ==, (TCVector<CStr>{}));
					DMibExpect(CStr("\n").f_SplitLine<true>(), ==, (TCVector<CStr>{}));
					DMibExpect(CStr("").f_SplitLine<true>(), ==, (TCVector<CStr>{}));
				}
				{
					DMibTestPath("Escaped");
					DMibExpect(CStr("Test;Test2;Test3").f_SplitEscaped(';'), ==, (TCVector<CStr>{"Test", "Test2", "Test3"}));
					DMibExpect(CStr(";Test2;").f_SplitEscaped(';'), ==, (TCVector<CStr>{"", "Test2", ""}));
					DMibExpect(CStr(";;").f_SplitEscaped(';'), ==, (TCVector<CStr>{"", "", ""}));
					DMibExpect(CStr(";").f_SplitEscaped(';'), ==, (TCVector<CStr>{"", ""}));
					DMibExpect(CStr("").f_SplitEscaped(';'), ==, (TCVector<CStr>{""}));

					DMibExpect(CStr("Te\\\\st;Te\\;st2;Test3").f_SplitEscaped(';'), ==, (TCVector<CStr>{"Te\\st", "Te;st2", "Test3"}));
					DMibExpect(CStr("\\\\;\\;").f_SplitEscaped(';'), ==, (TCVector<CStr>{"\\", ";"}));
					DMibExpect(CStr("\\\\").f_SplitEscaped(';'), ==, (TCVector<CStr>{"\\"}));
					DMibExpect(CStr("\\;").f_SplitEscaped(';'), ==, (TCVector<CStr>{";"}));

					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{"Test", "Test2", "Test3"}, ';'), ==, "Test;Test2;Test3");
					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{"", "Test2", ""}, ';'), ==, ";Test2;");
					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{"", "", ""}, ';'), ==, ";;");
					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{"", ""}, ';'), ==, ";");
					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{""}, ';'), ==, "");

					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{"Te\\st", "Te;st2", "Test3"}, ';'), ==, "Te\\\\st;Te\\;st2;Test3");
					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{"\\", ";"}, ';'), ==, "\\\\;\\;");
					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{"\\"}, ';'), ==, "\\\\");
					DMibExpect(CStr::fs_JoinEscaped(TCVector<CStr>{";"}, ';'), ==, "\\;");
				}
				{
					DMibTestPath("Escaped NonEmpty");
					DMibExpect(CStr("Test;Test2;Test3").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{"Test", "Test2", "Test3"}));
					DMibExpect(CStr(";Test2;").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{"Test2"}));
					DMibExpect(CStr(";;").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{}));
					DMibExpect(CStr(";").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{}));
					DMibExpect(CStr("").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{}));

					DMibExpect(CStr("Te\\\\st;Te\\;st2;Test3").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{"Te\\st", "Te;st2", "Test3"}));
					DMibExpect(CStr("\\\\;\\;").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{"\\", ";"}));
					DMibExpect(CStr("\\\\").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{"\\"}));
					DMibExpect(CStr("\\;").f_SplitEscaped<true>(';'), ==, (TCVector<CStr>{";"}));
				}
			};
			DMibTestSuite("Bugs")
			{
				{
					DMibTestPath("Doesn't check null terminator");
					ch8 Test0[16] = "Test";
					ch8 Test1[16] = "Test2";
					CStr Formatted = CStr::CFormat("{}{}") << Test0 << Test1;
					DMibExpect(Formatted, ==, "TestTest2");
				}
				{
					DMibTestPath("Doesn't check null terminator by value");
					ch8 Test0[16] = "Test";
					ch8 Test1[16] = "Test2";
					CStr Formatted = CStr::CFormat("{}{}") << fg_ByValue(Test0) << fg_ByValue(Test1);
					DMibExpect(Formatted, ==, "TestTest2");
				}
				{
					DMibTestPath("Doesn't check null terminator const");
					CStr Formatted = CStr::CFormat("{}{}") << "Test" << "Test2";
					DMibExpect(Formatted, ==, "TestTest2");
				}
				{
					DMibTestPath("Doesn't check null terminator const by value");
					CStr Formatted = CStr::CFormat("{}{}") << fg_ByValue("Test") << fg_ByValue("Test2");
					DMibExpect(Formatted, ==, "TestTest2");
				}
			};
		}
	};

	DMibTestRegister(CStr_Tests, Malterlib::String::Container);
}
