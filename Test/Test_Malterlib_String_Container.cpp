// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#ifdef DCompiler_clang
	// Fastformat and stlsoft do not like libcpp
	#undef DMalterlibEnableThirdPartyComparisonTests
#endif

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
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/algorithm/string/find.hpp>

#ifdef DMalterlibEnableThirdPartyComparisonTests

#define FASTFORMAT_NO_VERSION_NAG

#include <fastformat/fastformat.hpp>
#include <fastformat/inserters/to_x.hpp>
#include <fastformat/sinks/auto_buffer.hpp>
#include <fastformat/sinks/char_buffer.hpp>
#include <fastformat/sinks/c_string.hpp>

#ifdef FASTFORMAT_USE_WIDE_STRINGS
typedef std::wstring CFastFormatString;
#define DFastFormatStr(d_Str) L##d_Str
#else
typedef std::string CFastFormatString;
#define DFastFormatStr(d_Str) d_Str
#endif

#endif

#include <Mib/Test/Test>
#include <Mib/Test/Memory>

using namespace NMib;
using namespace NMib::NTime;
using namespace NMib::NContainer;
using namespace NMib::NTest;
using namespace NMib::NTraits;


namespace
{
	using namespace NMib::NStr;
	using namespace NMib::NStorage;
	namespace qi = boost::spirit::qi;
	namespace karma = boost::spirit::karma;
	namespace ascii = boost::spirit::ascii;

	class CStr_Tests : public CTest
	{
		template <bool t_bMemoryTests>
		struct TCTests
		{
			typedef typename TCChooseType<t_bMemoryTests, CTestMemoryMeasure, CTestPerformanceMeasure>::CType CMeasureType;
			typedef typename TCChooseType<t_bMemoryTests, CTestMemoryNumAllocations, CTestPerformance>::CType CTestType;

			const static mint VectorSize = 512;
			static CStr fs_GenerateHexList()
			{
				typedef int32 CValue;
				using karma::hex;


				std::vector<CValue> const vec(VectorSize,12345);

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

#ifdef DMalterlibEnableThirdPartyComparisonTests
				CMeasureType FastFormatAllocTime("Fast Format");
				CMeasureType FastFormatAllocReserveTime("Fast Format");
				CMeasureType FastFormatNoAllocTime("Fast Format");
				CMeasureType FastFormatStaticAllocReserveTime("Fast Format");
				CMeasureType FastFormatStaticAllocTime("Fast Format");
				CMeasureType FastFormatStaticNoAllocTime("Fast Format");
#endif

				// Test 100 times and pick the fastest

				mint NeededCharSize = VectorSize * 5 + 3;
				CStr MalterlibAllocResult;
				CStr MalterlibAllocReserveResult;
				CStr MalterlibStaticAllocResult;
				CStr MalterlibStaticAllocReserveResult;
				std::string KarmaResult;
				std::string KarmaReserveResult;
				std::string KarmaManualStaticAllocResult;
				std::string KarmaManualStaticAllocReserveResult;
#ifdef DMalterlibEnableThirdPartyComparisonTests
				CFastFormatString FastFormatAllocReserveResult;
				CFastFormatString FastFormatAllocResult;
				CFastFormatString FastFormatStaticAllocReserveResult;
				CFastFormatString FastFormatStaticAllocResult;
#endif
				TCUniquePointer<ch8> KarmaCharResult = NMib::fg_Explicit(DMibNew ch8 [NeededCharSize]);
				TCUniquePointer<ch8> MalterlibNoAllocResultData = NMib::fg_Explicit(DMibNew ch8 [NeededCharSize]);
				TCUniquePointer<ch8> MalterlibStaticNoAllocResultData = NMib::fg_Explicit(DMibNew ch8 [NeededCharSize]);
				TCUniquePointer<ch8> KarmaManualStaticNoAllocResult = NMib::fg_Explicit(DMibNew ch8 [NeededCharSize]);
#ifdef DMalterlibEnableThirdPartyComparisonTests
				TCUniquePointer<fastformat::ff_char_t> FastFormatStaticNoAllocResult = NMib::fg_Explicit(DMibNew fastformat::ff_char_t [NeededCharSize]);
				TCUniquePointer<fastformat::ff_char_t> FastFormatNoAllocResult = NMib::fg_Explicit(DMibNew fastformat::ff_char_t [NeededCharSize]);
#endif

				CStrPtr MalterlibNoAllocResult;
				MalterlibNoAllocResult.f_SetPtr(MalterlibNoAllocResultData.f_Get(), NeededCharSize);
				CStrPtr MalterlibStaticNoAllocResult;
				MalterlibStaticNoAllocResult.f_SetPtr(MalterlibStaticNoAllocResultData.f_Get(), NeededCharSize);

	#ifdef DMibDebug
				const static int nTests = 100;
	#else
				const static int nTests = 100;
	#endif
				auto Karma = [&] ()
				{
					KarmaResult = std::string();
					{ // Timing boost.spirit
						KarmaStaticAllocTime.f_Start();
						std::back_insert_iterator<std::string> iter(KarmaResult);
						karma::generate(iter
							, '[' << hex % ',' << ']'
							, vec);
						KarmaStaticAllocTime.f_Stop(VectorSize);
					}
				};
				auto KarmaReserve = [&] ()
				{
					KarmaReserveResult = std::string();
					KarmaReserveResult.reserve(NeededCharSize);
					{ // Timing boost.spirit
						KarmaStaticAllocReserveTime.f_Start();
						std::back_insert_iterator<std::string> iter(KarmaReserveResult);
						karma::generate(iter
							, '[' << hex % ',' << ']'
							, vec);
						KarmaStaticAllocReserveTime.f_Stop(VectorSize);
					}
				};
				auto KarmaChar = [&] ()
				{
					{ // Timing boost.spirit
						KarmaStaticNoAllocTime.f_Start();
						ch8 *pGenerate = KarmaCharResult.f_Get();
						karma::generate(pGenerate
							, '[' << hex % ',' << ']'
							, vec);
						*pGenerate = 0;
						KarmaStaticNoAllocTime.f_Stop(VectorSize);
					}
				};
				auto KarmaManualStaticAlloc = [&] ()
				{
					KarmaManualStaticAllocResult = std::string();
					{ // Timing boost.spirit
						KarmaManualStaticAllocTime.f_Start();

						std::back_insert_iterator<std::string> OutIter(KarmaManualStaticAllocResult);

						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						*OutIter = '[';++OutIter;
						if (Iter != IterEnd)
						{
							karma::generate(OutIter, hex, *Iter);
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								karma::generate(OutIter, ',' << hex, *Iter);
							}
						}
						*OutIter = ']';++OutIter;

						KarmaManualStaticAllocTime.f_Stop(VectorSize);
					}
				};
				auto KarmaManualStaticAllocReserve = [&] ()
				{
					KarmaManualStaticAllocReserveResult = std::string();
					KarmaManualStaticAllocReserveResult.reserve(NeededCharSize);
					KarmaManualStaticAllocReserveTime.f_Start();
					{ // Timing boost.spirit

						std::back_insert_iterator<std::string> OutIter(KarmaManualStaticAllocReserveResult);

						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						*OutIter = '[';++OutIter;
						if (Iter != IterEnd)
						{
							karma::generate(OutIter, hex, *Iter);
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								karma::generate(OutIter, ',' << hex, *Iter);
							}
						}
						*OutIter = ']';++OutIter;

					}
					KarmaManualStaticAllocReserveTime.f_Stop(VectorSize);
				};
				auto KarmaManualStaticNoAlloc = [&] ()
				{
					KarmaManualStaticNoAllocTime.f_Start();
					{ // Timing boost.spirit

						ch8 *pGenerate = KarmaManualStaticNoAllocResult.f_Get();

						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						*pGenerate = '[';++pGenerate;
						if (Iter != IterEnd)
						{
							karma::generate(pGenerate, hex, *Iter);
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								karma::generate(pGenerate, ',' << hex, *Iter);
							}
						}
						*pGenerate = ']';++pGenerate;
						*pGenerate = 0;

					}
					KarmaManualStaticNoAllocTime.f_Stop(VectorSize);
				};

				auto MalterlibAlloc = [&] ()
				{
					MalterlibAllocResult.f_Clear();
					{ // Timing CStr::Parse
						MalterlibAllocTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						MalterlibAllocResult += '[';
						if (Iter != IterEnd)
						{
							MalterlibAllocResult += (CStr::CFormat("{nh}") << *Iter);
							++Iter;
							CValue Value;
							CStr::CFormat Format(",{nh}");
							Format << Value;
							for(; Iter != IterEnd;++Iter)
							{
								Value = *Iter;
								MalterlibAllocResult += Format;
							}
						}
						MalterlibAllocResult += ']';
						MalterlibAllocTime.f_Stop(VectorSize);
					}
				};
				auto MalterlibAllocReserve = [&] ()
				{
					MalterlibAllocReserveResult.f_Clear();
					MalterlibAllocReserveResult.f_Reserve(NeededCharSize);
					{ // Timing CStr::Parse
						MalterlibAllocReserveTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						MalterlibAllocReserveResult += '[';
						if (Iter != IterEnd)
						{
							MalterlibAllocReserveResult += (CStr::CFormat("{nh}") << *Iter);
							++Iter;
							CValue Value;
							CStr::CFormat Format(",{nh}");
							Format << Value;
							for(; Iter != IterEnd;++Iter)
							{
								Value = *Iter;
								MalterlibAllocReserveResult += Format;
							}
						}
						MalterlibAllocReserveResult += ']';
						MalterlibAllocReserveTime.f_Stop(VectorSize);
					}
				};
				auto MalterlibNoAlloc = [&] ()
				{
					MalterlibNoAllocResult.f_Clear();
					{ // Timing CStr::Parse
						MalterlibNoAllocTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						MalterlibNoAllocResult += '[';
						if (Iter != IterEnd)
						{
							MalterlibNoAllocResult += (CStrPtr::CFormat("{nh}") << *Iter);
							++Iter;
							CValue Value;
							CStrPtr::CFormat Format(",{nh}");
							Format << Value;
							for(; Iter != IterEnd;++Iter)
							{
								Value = *Iter;
								MalterlibNoAllocResult += Format;
							}
						}
						MalterlibNoAllocResult += ']';
						MalterlibNoAllocTime.f_Stop(VectorSize);
					}
				};
				auto MalterlibStaticNoAlloc = [&] ()
				{
					MalterlibStaticNoAllocResult.f_Clear();
					{ // Timing CStr::Parse
						MalterlibStaticNoAllocTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						aint StrLen = 0;
						MalterlibStaticNoAllocResult.fp_AddCharLengthAware(StrLen, '[');
						if (Iter != IterEnd)
						{
							CStrPtr::fs_ToStrInplaceConcat(MalterlibStaticNoAllocResult, fg_FormatIntFormat<16>(*Iter), StrLen);
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								MalterlibStaticNoAllocResult.fp_AddCharLengthAware(StrLen, ',');
								CStrPtr::fs_ToStrInplaceConcat(MalterlibStaticNoAllocResult, fg_FormatIntFormat<16>(*Iter), StrLen);
							}
						}
						MalterlibStaticNoAllocResult.fp_AddCharLengthAware(StrLen, ']');
						MalterlibStaticNoAllocResult.f_SetStrLen(StrLen);
						MalterlibStaticNoAllocTime.f_Stop(VectorSize);
					}
				};
				auto MalterlibStaticAlloc = [&] ()
				{
					MalterlibStaticAllocResult.f_Clear();
					{ // Timing CStr::Parse
						MalterlibStaticAllocTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						aint StrLen = 0;
						MalterlibStaticAllocResult.fp_AddCharLengthAware(StrLen, '[');
						if (Iter != IterEnd)
						{
							CStr::fs_ToStrInplaceConcat(MalterlibStaticAllocResult, fg_FormatIntFormat<16>(*Iter), StrLen);
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								MalterlibStaticAllocResult.fp_AddCharLengthAware(StrLen, ',');
								CStr::fs_ToStrInplaceConcat(MalterlibStaticAllocResult, fg_FormatIntFormat<16>(*Iter), StrLen);
							}
						}
						MalterlibStaticAllocResult.fp_AddCharLengthAware(StrLen, ']');
						MalterlibStaticAllocResult.f_SetStrLen(StrLen);
						MalterlibStaticAllocTime.f_Stop(VectorSize);
					}
				};
				auto MalterlibStaticAllocReserve = [&] ()
				{
					MalterlibStaticAllocReserveResult.f_Clear();
					MalterlibStaticAllocReserveResult.f_Reserve(NeededCharSize);
					{ // Timing CStr::Parse
						MalterlibStaticAllocReserveTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						aint StrLen = 0;
						MalterlibStaticAllocReserveResult.fp_AddCharLengthAware(StrLen, '[');
						if (Iter != IterEnd)
						{
							CStr::fs_ToStrInplaceConcat(MalterlibStaticAllocReserveResult, fg_FormatIntFormat<16>(*Iter), StrLen);
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								MalterlibStaticAllocReserveResult.fp_AddCharLengthAware(StrLen, ',');
								CStr::fs_ToStrInplaceConcat(MalterlibStaticAllocReserveResult, fg_FormatIntFormat<16>(*Iter), StrLen);
							}
						}
						MalterlibStaticAllocReserveResult.fp_AddCharLengthAware(StrLen, ']');
						MalterlibStaticAllocReserveResult.f_SetStrLen(StrLen);
						MalterlibStaticAllocReserveTime.f_Stop(VectorSize);
					}
				};
#ifdef DMalterlibEnableThirdPartyComparisonTests
				auto FastFormatAllocReserve = [&] ()
				{
					FastFormatAllocReserveResult = CFastFormatString();
					FastFormatAllocReserveResult.reserve(NeededCharSize);
					{ // Timing boost.spirit
						FastFormatAllocReserveTime.f_Start();

						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						fastformat::fmt(FastFormatAllocReserveResult, DFastFormatStr("{0}"), DFastFormatStr("["));
						if (Iter != IterEnd)
						{
							fastformat::fmt(FastFormatAllocReserveResult, DFastFormatStr("{0}"), fastformat::to_x(*Iter));
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								fastformat::fmt(FastFormatAllocReserveResult, DFastFormatStr(",{0}"), fastformat::to_x(*Iter));
							}
						}
						fastformat::fmt(FastFormatAllocReserveResult, DFastFormatStr("{0}"), DFastFormatStr("]"));

						FastFormatAllocReserveTime.f_Stop(VectorSize);
					}
				};
				auto FastFormatNoAlloc = [&] ()
				{
					fastformat::sinks::char_buffer_sink sink(NeededCharSize, FastFormatNoAllocResult.f_Get());
					{ // Timing boost.spirit
						FastFormatNoAllocTime.f_Start();

						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						fastformat::fmt(sink, DFastFormatStr("{0}"), DFastFormatStr("["));
						if (Iter != IterEnd)
						{
							fastformat::fmt(sink, DFastFormatStr("{0}"), fastformat::to_x(*Iter));
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								fastformat::fmt(sink, DFastFormatStr(",{0}"), fastformat::to_x(*Iter));
							}
						}
						fastformat::fmt(sink, DFastFormatStr("{0}"), DFastFormatStr("]"));
						FastFormatNoAllocResult.f_Get()[sink.size()] = 0;

						FastFormatNoAllocTime.f_Stop(VectorSize);
					}
				};
				auto FastFormatAlloc = [&] ()
				{
					FastFormatAllocResult = CFastFormatString();
					{ // Timing boost.spirit
						FastFormatAllocTime.f_Start();

						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						fastformat::fmt(FastFormatAllocResult, DFastFormatStr("{0}"), DFastFormatStr("["));
						if (Iter != IterEnd)
						{
							fastformat::fmt(FastFormatAllocResult, DFastFormatStr("{0}"), fastformat::to_x(*Iter));
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								fastformat::fmt(FastFormatAllocResult, DFastFormatStr(",{0}"), fastformat::to_x(*Iter));
							}
						}
						fastformat::fmt(FastFormatAllocResult, DFastFormatStr("{0}"), DFastFormatStr("]"));

						FastFormatAllocTime.f_Stop(VectorSize);
					}
				};
				auto FastFormatStaticAllocReserve = [&] ()
				{
					FastFormatStaticAllocReserveResult = CFastFormatString();
					FastFormatStaticAllocReserveResult.reserve(NeededCharSize);
					{ // Timing boost.spirit
						FastFormatStaticAllocReserveTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						fastformat::write(FastFormatStaticAllocReserveResult, DFastFormatStr("["));
						if (Iter != IterEnd)
						{
							fastformat::write(FastFormatStaticAllocReserveResult, fastformat::to_x(*Iter));
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								fastformat::write(FastFormatStaticAllocReserveResult, DFastFormatStr(","), fastformat::to_x(*Iter));
							}
						}
						fastformat::write(FastFormatStaticAllocReserveResult, DFastFormatStr("]"));

						FastFormatStaticAllocReserveTime.f_Stop(VectorSize);
					}
				};
				auto FastFormatStaticAlloc = [&] ()
				{
					FastFormatStaticAllocResult = CFastFormatString();
					{ // Timing boost.spirit
						FastFormatStaticAllocTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						fastformat::write(FastFormatStaticAllocResult, DFastFormatStr("["));
						if (Iter != IterEnd)
						{
							fastformat::write(FastFormatStaticAllocResult, fastformat::to_x(*Iter));
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								fastformat::write(FastFormatStaticAllocResult, DFastFormatStr(","), fastformat::to_x(*Iter));
							}
						}
						fastformat::write(FastFormatStaticAllocResult, DFastFormatStr("]"));

						FastFormatStaticAllocTime.f_Stop(VectorSize);
					}
				};
				auto FastFormatStaticNoAlloc = [&] ()
				{
					fastformat::sinks::char_buffer_sink sink(NeededCharSize, FastFormatStaticNoAllocResult.f_Get());
					{ // Timing boost.spirit
						FastFormatStaticNoAllocTime.f_Start();
						auto Iter = vec.begin();
						auto IterEnd = vec.end();
						fastformat::write(sink, DFastFormatStr("["));
						if (Iter != IterEnd)
						{
							fastformat::write(sink, fastformat::to_x(*Iter));
							++Iter;
							for(; Iter != IterEnd;++Iter)
							{
								fastformat::write(sink, DFastFormatStr(","), fastformat::to_x(*Iter));
							}
						}
						fastformat::write(sink, DFastFormatStr("]"));
						FastFormatStaticNoAllocResult.f_Get()[sink.size()] = 0;

						FastFormatStaticNoAllocTime.f_Stop(VectorSize);
					}
				};
#endif
				for(int i=0;i<nTests;++i)
					Karma();
				for(int i=0;i<nTests;++i)
					KarmaChar();
				for(int i=0;i<nTests;++i)
					KarmaReserve();

				for(int i=0;i<nTests;++i)
					KarmaManualStaticAlloc();
				for(int i=0;i<nTests;++i)
					KarmaManualStaticAllocReserve();
				for(int i=0;i<nTests;++i)
					KarmaManualStaticNoAlloc();

				for(int i=0;i<nTests;++i)
					MalterlibAlloc();
				for(int i=0;i<nTests;++i)
					MalterlibAllocReserve();
				for(int i=0;i<nTests;++i)
					MalterlibNoAlloc();
				for(int i=0;i<nTests;++i)
					MalterlibStaticNoAlloc();
				for(int i=0;i<nTests;++i)
					MalterlibStaticAlloc();
				for(int i=0;i<nTests;++i)
					MalterlibStaticAllocReserve();

#ifdef DMalterlibEnableThirdPartyComparisonTests
				for(int i=0;i<nTests;++i)
					FastFormatAllocReserve();
				for(int i=0;i<nTests;++i)
					FastFormatNoAlloc();
				for(int i=0;i<nTests;++i)
					FastFormatAlloc();
				for(int i=0;i<nTests;++i)
					FastFormatStaticAllocReserve();
				for(int i=0;i<nTests;++i)
					FastFormatStaticAlloc();
				for(int i=0;i<nTests;++i)
					FastFormatStaticNoAlloc();
#endif

				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaResult.c_str())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaCharResult.f_Get())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaReserveResult.c_str())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaManualStaticAllocResult.c_str())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaManualStaticNoAllocResult.f_Get())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(KarmaManualStaticAllocReserveResult.c_str())) (ETestFlag_NoValues);
#ifdef DMalterlibEnableThirdPartyComparisonTests
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(FastFormatAllocReserveResult.c_str())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(FastFormatNoAllocResult.f_Get())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(FastFormatAllocResult.c_str())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(FastFormatStaticAllocReserveResult.c_str())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(FastFormatStaticAllocResult.c_str())) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(FastFormatStaticNoAllocResult.f_Get())) (ETestFlag_NoValues);
#endif
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibAllocReserveResult)) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibNoAllocResult)) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibStaticNoAllocResult)) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibStaticAllocResult)) (ETestFlag_NoValues);
				DMibTest(DMibExpr(MalterlibAllocResult) == DMibExpr(MalterlibStaticAllocReserveResult)) (ETestFlag_NoValues);

				CTestType DynamicAlloc(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
				DynamicAlloc.f_AddReference(FastFormatAllocTime);
#endif
				DynamicAlloc.f_Add(MalterlibAllocTime);
				DMibTest(DMibExpr(DynamicAlloc));

				CTestType DynamicAllocReserve(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
				DynamicAllocReserve.f_AddReference(FastFormatAllocReserveTime);
#endif
				DynamicAllocReserve.f_Add(MalterlibAllocReserveTime);
				DMibTest(DMibExpr(DynamicAllocReserve));

				CTestType DynamicNoAlloc(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
				DynamicNoAlloc.f_AddReference(FastFormatNoAllocTime);
#endif
				DynamicNoAlloc.f_Add(MalterlibNoAllocTime);
				DMibTest(DMibExpr(DynamicNoAlloc));

				CTestType StaticAlloc(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
				StaticAlloc.f_AddReference(FastFormatStaticAllocTime);
#endif
				StaticAlloc.f_AddReference(KarmaStaticAllocTime);
				StaticAlloc.f_AddReference(KarmaManualStaticAllocTime);
				StaticAlloc.f_Add(MalterlibStaticAllocTime);
				DMibTest(DMibExpr(StaticAlloc));

				CTestType StaticAllocReserve(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
				StaticAllocReserve.f_AddReference(FastFormatStaticAllocReserveTime);
#endif
				StaticAllocReserve.f_AddReference(KarmaStaticAllocReserveTime);
				StaticAllocReserve.f_AddReference(KarmaManualStaticAllocReserveTime);
				StaticAllocReserve.f_Add(MalterlibStaticAllocReserveTime);
				DMibTest(DMibExpr(StaticAllocReserve));

				CTestType StaticNoAlloc(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
				StaticNoAlloc.f_AddReference(FastFormatStaticNoAllocTime);
#endif
				StaticNoAlloc.f_AddReference(KarmaStaticNoAllocTime);
				StaticNoAlloc.f_AddReference(KarmaManualStaticNoAllocTime);
				StaticNoAlloc.f_Add(MalterlibStaticNoAllocTime);
				DMibTest(DMibExpr(StaticNoAlloc));

				return MalterlibAllocResult;
			}
			static void fs_DecodeHexList(const CStr &_HexList)
			{
				using qi::hex;
				typedef int32 CValue;

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
				const static int nTests = 100;
	#else
				const static int nTests = 100;
	#endif
				// Test 100 times and pick the fastest
				for(int i=0;i<nTests;++i)
				{
					std::string in1(_HexList.f_GetStr());
					SpiritVector.clear();
					{ // Timing boost.spirit
						SpiritTimer.f_Start();
						std::string::iterator beg = in1.begin();
						qi::parse(
							beg,in1.end(),
							(
							'[' >> hex % ',' >> ']'
							)
							,SpiritVector);
						SpiritTimer.f_Stop(VectorSize);
					}
				}
				for(int i=0;i<nTests;++i)
				{
					std::string in1(_HexList.f_GetStr());
					SpiritSemanticVector.clear();
					{ // Timing boost.spirit
						SpiritSemanticTimer.f_Start();
						std::string::iterator beg = in1.begin();
						auto Lamba = [&SpiritSemanticVector] (const CValue &_Value, boost::spirit::unused_type, bool) {SpiritSemanticVector.push_back(_Value);};
						qi::parse(
							beg,in1.end(),
							(
							'[' >> hex[ Lamba ] % ',' >> ']'
							));
						SpiritSemanticTimer.f_Stop(VectorSize);
					}
				}
				for(int i=0;i<nTests;++i)
				{
					MalterlibVector.clear();
					{  // Timing CStr::Parse
						CValue val;
						MalterlibTimer.f_Start();
						const CStr::CChar *pParse = _HexList;
						pParse = (TCStrParse<CStr::CStrTraits>("[{nh}") >> val).f_Parse(pParse);
						MalterlibVector.push_back(val);
						TCStrParse<CStr::CStrTraits> Parser(",{nh}");
						Parser >> val;
						while(*pParse != ']')
						{
							pParse = Parser.f_Parse(pParse);
							MalterlibVector.push_back(val);
						}
						MalterlibTimer.f_Stop(VectorSize);
					}
				}
				for(int i=0;i<nTests;++i)
				{
					ManualVector.clear();
					{  // Timing Manual
						ManualTimer.f_Start();
						CValue val;
						const CStr::CChar *pParse = _HexList;
						if (*pParse == '[')
							++pParse;
						while (*pParse && *pParse != ']')
						{
							val = fg_StrToIntParse(pParse, CValue(-1), (const CStr::CChar *)nullptr, true, EStrToIntParseMode_Hex);
							ManualVector.push_back(val);
							if (*pParse == ',')
								++pParse;
						}
						ManualTimer.f_Stop(VectorSize);
					}
				}
				for(int i=0;i<nTests;++i)
				{
					ManualHexOnlyVector.clear();
					{  // Timing manual hex only
						ManualHexOnlyTimer.f_Start();
						CValue val;
						const CStr::CChar *pParse = _HexList;
						if (*pParse == '[')
							++pParse;
						while (*pParse && *pParse != ']')
						{
							val = fg_StrToIntParseHexNoSign(pParse, CValue(-1));
							ManualHexOnlyVector.push_back(val);
							if (*pParse == ',')
								++pParse;
						}
						ManualHexOnlyTimer.f_Stop(VectorSize);
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

	/*		CStr::CFormat f_GenerateFormatStr()
			{
				CStr fmtstr = "{} ";
				fmtstr += "{}";
				return CStr::CFormat(fmtstr);
			}*/

			void f_FormatInt()
			{
	#ifdef DMibDebug
				const static mint nTestsGlobal = 10;
	#else
				const static mint nTestsGlobal = 1000;
	#endif
				const static int32 nLoopsGlobal = 10000;
				// Do

				DMibTestSuite("Static")
				{
					const static mint nTestsPropagate = nTestsGlobal;
					const static int32 nLoopsPropagate = nLoopsGlobal;
					{
						const static mint nTests = nTestsPropagate;
						const static int32 nLoops = nLoopsPropagate;
						CMeasureType MalterlibTime("Malterlib CFStr16");
						CFStr16 MalterlibResult;

						CMeasureType MalterlibCFStr16InplaceTime("Malterlib CFStr16 inplace");
						{
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCFStr16InplaceTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									CFStr16::fs_ToStrInplace(MalterlibResult, i);
								}
								MalterlibCFStr16InplaceTime.f_Stop(nLoops);
							}
						};

						CMeasureType KarmaTime("Karma");
						{
							using karma::int_;
							ch8 Result[16];
							for(mint j = 0; j < nTests; ++j)
							{
								KarmaTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									ch8 *pGenerate = Result;
									karma::generate(pGenerate, int_, i);
									*pGenerate = 0;
								}
								KarmaTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
#ifdef DMalterlibEnableThirdPartyComparisonTests
						CMeasureType FastFormatTime("Fast Format");
						{
							fastformat::ff_char_t Result[16];
							for(mint j = 0; j < nTests; ++j)
							{
								FastFormatTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									fastformat::sinks::char_buffer_sink sink(Result);
									fastformat::write(sink, i);
									Result[sink.size()] = 0;
								}
								FastFormatTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
#endif
						CMeasureType MalterlibCStrPtrTime("Malterlib CStrPtr");
						{
							CCyclesMin Time;
							CStrPtr Result;
							ch8 ResultData[12];
							Result.f_SetPtr(ResultData, 12);
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCStrPtrTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									CStrPtr::fs_ToStrInplace(Result, i);
								}
								MalterlibCStrPtrTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType MalterlibCFStr16Time("Malterlib CFStr16");
						{
							CFStr16 Result;
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCFStr16Time.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result = CFStr16::fs_ToStr(i);;
								}
								MalterlibCFStr16Time.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
	#if defined(DPlatformFamily_Windows)
						CMeasureType ItoaTime("itoa");
						{
							CCyclesMin Time;
							char Result[12];
							for(mint j = 0; j < nTests; ++j)
							{
								ItoaTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									_itoa(i,Result,10);
								}
								ItoaTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
	#endif
						CTestType NoAlloc(1.0);
						NoAlloc.f_AddReference(KarmaTime);
#ifdef DMalterlibEnableThirdPartyComparisonTests
						NoAlloc.f_AddReference(FastFormatTime);
#endif
	#if defined(DPlatformFamily_Windows)
						NoAlloc.f_AddReference(ItoaTime);
	#endif
						NoAlloc.f_Add(MalterlibCFStr16InplaceTime);
						NoAlloc.f_Add(MalterlibCStrPtrTime);
						NoAlloc.f_Add(MalterlibCFStr16Time);
						DMibTest(DMibExpr(NoAlloc));
					};

					{
						const static mint nTests = nTestsPropagate;
						const static int32 nLoops = nLoopsPropagate;
						CStr MalterlibResult;
						CMeasureType MalterlibCStrInplaceTime("Malterlib CStr inplace");
						{
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCStrInplaceTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									MalterlibResult.f_Clear();
									CStr::fs_ToStrInplace(MalterlibResult, i);
								}
								MalterlibCStrInplaceTime.f_Stop(nLoops);
							}
						};
#ifdef DMalterlibEnableThirdPartyComparisonTests
						CMeasureType FastFormatTime("Fast Format");
						{
							CFastFormatString Result;
							for(mint j = 0; j < nTests; ++j)
							{
								FastFormatTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result = CFastFormatString();
									fastformat::write(Result, i);
								}
								FastFormatTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
#endif
						CMeasureType KarmaTime("Karma");
						{
							using karma::int_;
							CCyclesMin Time;
							std::string Result;
							for(mint j = 0; j < nTests; ++j)
							{
								KarmaTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result = std::string();
									std::back_insert_iterator<std::string> iter(Result);
									karma::generate(iter, int_, i);
								}
								KarmaTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
						CMeasureType MalterlibCStrTime("Malterlib CStr");
						{
							CCyclesMin Time;
							CStr Result;
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCStrTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result = CStr::fs_ToStr(i);;
								}
								MalterlibCStrTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType StringStreamTime("stringstream");
						{
							CCyclesMin Time;
							std::string Result;
							std::stringstream Stream;
							for(mint j = 0; j < nTests/10; ++j)
							{
								StringStreamTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Stream.str("");
									Stream.clear();
									Stream << i;
									Result = Stream.str();
								}
								StringStreamTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
						CTestType Alloc(1.0);
						Alloc.f_AddReference(KarmaTime);
#ifdef DMalterlibEnableThirdPartyComparisonTests
						Alloc.f_AddReference(FastFormatTime);
#endif
						Alloc.f_AddReference(StringStreamTime);
						Alloc.f_Add(MalterlibCStrInplaceTime);
						Alloc.f_Add(MalterlibCStrTime);
						DMibTest(DMibExpr(Alloc)) (ETest_ExpectFail); // We need a CStr that has storage interally when possible
					};
					{
						const static mint nTests = nTestsPropagate;
						const static int32 nLoops = nLoopsPropagate;
						CStr MalterlibResult;
						CMeasureType MalterlibCStrInplaceTime("Malterlib CStr inplace");
						{
							MalterlibResult.f_Reserve(12);
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCStrInplaceTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									CStr::fs_ToStrInplace(MalterlibResult, i);
								}
								MalterlibCStrInplaceTime.f_Stop(nLoops);
							}
						};
#ifdef DMalterlibEnableThirdPartyComparisonTests
						CMeasureType FastFormatTime("Fast Format");
						{
							CFastFormatString Result;
							Result.reserve(12);
							for(mint j = 0; j < nTests; ++j)
							{
								FastFormatTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result.clear();
									fastformat::write(Result, i);
								}
								FastFormatTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
#endif
						CMeasureType KarmaTime("Karma");
						{
							using karma::int_;
							CCyclesMin Time;
							std::string Result;
							Result.reserve(12);
							for(mint j = 0; j < nTests; ++j)
							{
								KarmaTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result.clear();
									std::back_insert_iterator<std::string> iter(Result);
									karma::generate(iter, int_, i);
								}
								KarmaTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
						CMeasureType MalterlibCStrTime("Malterlib CStr");
						{
							CCyclesMin Time;
							CStr Result;
							Result.f_Reserve(12);
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCStrTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result = CStr::fs_ToStr(i);;
								}
								MalterlibCStrTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType StringStreamTime("stringstream");
						{
							CCyclesMin Time;
							std::string Result;
							Result.reserve(12);
							std::stringstream Stream;
							for(mint j = 0; j < nTests/10; ++j)
							{
								StringStreamTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Stream.str("");
									Stream.clear();
									Stream << i;
									Result = Stream.str();
								}
								StringStreamTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
						CTestType AllocReserve(1.0);
						AllocReserve.f_AddReference(KarmaTime);
#ifdef DMalterlibEnableThirdPartyComparisonTests
						AllocReserve.f_AddReference(FastFormatTime);
#endif
						AllocReserve.f_AddReference(StringStreamTime);
						AllocReserve.f_Add(MalterlibCStrInplaceTime);
						AllocReserve.f_Add(MalterlibCStrTime);
						DMibTest(DMibExpr(AllocReserve));
					};
				};

				DMibTestSuite("Dynamic")
				{
					const static mint nTestsPropagate = nTestsGlobal;
					const static int32 nLoopsPropagate = nLoopsGlobal;
					{
						const static mint nTests = nTestsPropagate;
						const static int32 nLoops = nLoopsPropagate;
						CFStr16 MalterlibResult;
						CMeasureType MalterlibCFStrOptTime("Malterlib CFStr16 Opt");
						{
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCFStrOptTime.f_Start();
								CFStr16::CFormat Format("{}");
								int Value;
								Format << Value;
								for(int i=0;i<nLoops;++i)
								{
									Value = i;
									MalterlibResult = Format;
								}
								MalterlibCFStrOptTime.f_Stop(nLoops);
							}
						};
						CMeasureType MalterlibCStrPtrOptTime("Malterlib CStrPtr Opt");
						{
							CStrPtr Result;
							ch8 ResultData[12];
							Result.f_SetPtr(ResultData, 12);
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCStrPtrOptTime.f_Start();
								CStrPtr::CFormat Format("{}");
								int Value;
								Format << Value;
								for(int i=0;i<nLoops;++i)
								{
									Value = i;
									Result = Format;
								}
								MalterlibCStrPtrOptTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
						CMeasureType MalterlibCFStr16Time("Malterlib CFStr16");
						{
							CFStr16 Result;
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibCFStr16Time.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result = CFStr16::CFormat("{}") << i;
								}
								MalterlibCFStr16Time.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
#ifdef DMalterlibEnableThirdPartyComparisonTests
						CMeasureType FastFormatTimer("Fast Format");
						{
							CCyclesMin Time;
							fastformat::ff_char_t Result[16];
							for(mint j = 0; j < nTests; ++j)
							{
								FastFormatTimer.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									fastformat::sinks::char_buffer_sink sink(Result);
									fastformat::fmt(sink, DFastFormatStr("{0}"), i);
									Result[sink.size()] = 0;
								}
								FastFormatTimer.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult) == DMibExpr(Result)) (ETestFlag_NoValues);
						};
#endif
						CMeasureType SprintfTime("sprintf");
						{
							CCyclesMin Time;
							char Result[12];
							for(mint j = 0; j < nTests; ++j)
							{
								SprintfTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									sprintf(Result,"%i",i);
								}
								SprintfTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};

						CTestType NoAlloc(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
						NoAlloc.f_AddReference(FastFormatTimer);
#endif
						NoAlloc.f_AddReference(SprintfTime);
						NoAlloc.f_Add(MalterlibCFStrOptTime);
						NoAlloc.f_Add(MalterlibCStrPtrOptTime);
						NoAlloc.f_Add(MalterlibCFStr16Time);
						DMibTest(DMibExpr(NoAlloc));
					};

					{
						const static mint nTests = nTestsPropagate;
						const static int32 nLoops = nLoopsPropagate;
						CMeasureType MalterlibOptTime("Malterlib Opt");
						CStr MalterlibResult;
						{
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibOptTime.f_Start();
								CStr::CFormat Format("{}");
								int Value;
								Format << Value;
								for(int i=0;i<nLoops;++i)
								{
									Value = i;
									MalterlibResult.f_Clear();
									MalterlibResult = Format;
								}
								MalterlibOptTime.f_Stop(nLoops);
							}
						};
						CMeasureType MalterlibTime("Malterlib");
						{
							CStr Result;
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibTime.f_Start();
								for (int i=0; i < nLoops; ++i)
								{
									Result.f_Clear();
									Result = CStr::CFormat("{}") << i;
								}
								MalterlibTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
#ifdef DMalterlibEnableThirdPartyComparisonTests
						CMeasureType FastFormatTime("Fast Format");
						{
							CFastFormatString Result;
							for(mint j = 0; j < nTests; ++j)
							{
								FastFormatTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result = CFastFormatString();
									fastformat::fmt(Result, DFastFormatStr("{0}"), i);
								}
								FastFormatTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
#endif
						CTestType Alloc(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
						Alloc.f_AddReference(FastFormatTime);
#endif
						Alloc.f_Add(MalterlibOptTime);
						Alloc.f_Add(MalterlibTime);
#ifdef DMalterlibEnableThirdPartyComparisonTests
						DMibTest(DMibExpr(Alloc)) (ETest_ExpectFail); // We need a CStr that has storage interally when possible
#else
						DMibTest(DMibExpr(Alloc));
#endif
					}
					{
						const static mint nTests = nTestsPropagate;
						const static int32 nLoops = nLoopsPropagate;
						CMeasureType MalterlibOptTime("Malterlib Opt");
						CStr MalterlibResult;
						{
							MalterlibResult.f_Reserve(12);
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibOptTime.f_Start();
								CStr::CFormat Format("{}");
								int Value;
								Format << Value;
								for(int i=0;i<nLoops;++i)
								{
									Value = i;
									MalterlibResult = Format;
								}
								MalterlibOptTime.f_Stop(nLoops);
							}
						};
						CMeasureType MalterlibTime("Malterlib");
						{
							CStr Result;
							Result.f_Reserve(12);
							for(mint j = 0; j < nTests; ++j)
							{
								MalterlibTime.f_Start();
								for (int i=0; i < nLoops; ++i)
								{
									Result = CStr::CFormat("{}") << i;
								}
								MalterlibTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result)
								DMibTest(DMibExpr(MalterlibResult == Result));
						};
#ifdef DMalterlibEnableThirdPartyComparisonTests
						CMeasureType FastFormatTime("Fast Format");
						{
							CFastFormatString Result;
							Result.reserve(12);
							for(mint j = 0; j < nTests; ++j)
							{
								FastFormatTime.f_Start();
								for(int i=0;i<nLoops;++i)
								{
									Result.clear();
									fastformat::fmt(Result, DFastFormatStr("{0}"), i);
								}
								FastFormatTime.f_Stop(nLoops);
							}
							if (MalterlibResult != Result.c_str())
								DMibTest(DMibExpr(MalterlibResult == Result.c_str()));
						};
#endif
						CTestType AllocReserve(1.0);
#ifdef DMalterlibEnableThirdPartyComparisonTests
						AllocReserve.f_AddReference(FastFormatTime);
#endif
						AllocReserve.f_Add(MalterlibOptTime);
						AllocReserve.f_Add(MalterlibTime);
						DMibTest(DMibExpr(AllocReserve));
					}
				};

			}
		};


		void f_TestCFormat()
		{
			DMibTestSuite("CFormat rvalue args")
			{
				CStrVMem fmtstr = "{} {}";
				CStrVMem::CFormat format(fmtstr);
				DMibTest(DMibExpr((format << CStrVMem("Hello") << CStr("World")).f_GetStr()) == DMibExpr("Hello World"));
			};
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

			DMibTrace("{nfh} {nfh} {nfh} {nfh} {nfh} {nfh} {nfh} {nfh}\r\n", Test << Test2 << Test3 << Test4 << Test5 << Test6 << Test7 << Test8);

			{
				uint32 Test = NMib::TCLimitsInt<uint32>::mc_Max;
				int32 TestS = NMib::TCLimitsInt<int32>::mc_Max;
				uint32 TestM = NMib::TCLimitsInt<uint32>::mc_Min;
				int32 TestMS = NMib::TCLimitsInt<int32>::mc_Min;
				int32 TestMS1 = NMib::TCLimitsInt<int32>::mc_Min + 10;
				DMibTrace("{} {} {} {}\r\n", Test << TestS << TestM << TestMS);

				DMibTrace("{}\r\n", TestMS);
				DMibTrace("{}\r\n", TestMS1);
			}
#endif

			DMibTestCategory("CFormat")
			{
				this->f_TestCFormat();
			};
			DMibTestCategory(CTestCategory("Performance") << CTestGroup("Performance"))
			{
				CStr_Tests::TCTests<false> Tests;
				CStr HexList;
				DMibTestSuite("Format hex list")
				{
					HexList = Tests.fs_GenerateHexList();
				};
				DMibTestSuite("Parse hex list")
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
				DMibTestSuite("Format hex list")
				{
					HexList = Tests.fs_GenerateHexList();
				};
				DMibTestSuite("Parse hex list")
				{
					Tests.fs_DecodeHexList(HexList);
				};

				DMibTestCategory("Format int")
				{
					Tests.f_FormatInt();
				};
			};
		}

	};

	DMibTestRegister(CStr_Tests, Malterlib::String::Container);

}

