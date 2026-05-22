// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>
#include "Malterlib_String_FuzzyMatch.h"

namespace NMib::NStr
{
	namespace
	{
		template <typename t_CIndex>
		struct TCFuzzyMatching
		{
			t_CIndex m_nMatched{0};
			t_CIndex m_iQuery{0};
			t_CIndex m_iCandidate{0};
		};

		constexpr static fp64 gc_WeightUnmatchedQuery = 0.5;
		constexpr static fp64 gc_WeightUnmatched = 0.1;
		constexpr static fp64 gc_WeightMatchPercent = 1.0 - (gc_WeightUnmatchedQuery.f_Get() + gc_WeightUnmatched.f_Get());

		auto fg_BuildContiguousMatchResult(aint _CandidateLen, aint _QueryLen, aint _iStart, aint _nCaseMismatches) -> CFuzzyMatchResult
		{
			CFuzzyMatchResult Result;
			Result.m_Matches.f_Reserve(1);
			auto &Range = Result.m_Matches.f_Insert();
			Range.m_iStart = _iStart;
			Range.m_iEnd = _iStart + _QueryLen;

			fp64 MatchedPercentQuery = fp64(_nCaseMismatches) * 0.5 / fp64(_QueryLen * _QueryLen);
			fp64 UnmatchedPercent = fp64(_CandidateLen - _QueryLen) / fp64(_CandidateLen);

			Result.m_Score
				= MatchedPercentQuery * gc_WeightMatchPercent
				+ UnmatchedPercent * gc_WeightUnmatched
			;
			return Result;
		}

		template <typename tf_CIndex>
		inline_never CFuzzyMatchResult fg_FuzzyMatchStringImpl(ch8 const *_pCandidate, ch8 const *_pQuery, tf_CIndex _CandidateLen, tf_CIndex _QueryLen)
		{
			using CMatching = TCFuzzyMatching<tf_CIndex>;
			constexpr tf_CIndex c_Unset = TCLimitsInt<tf_CIndex>::mc_Max;
			struct CMatchRun
			{
				tf_CIndex m_nMatched{0};
				tf_CIndex m_iQuery{0};
				tf_CIndex m_iCandidate{0};
				tf_CIndex m_nCaseMismatches{0};
				umint m_iNextRun{0};
			};

			// Single aligned allocation for all temporary buffers
			// Layout: [pLowerBuf | padding | pQueryNext | pQueryMatchings | pBucketHeads | pBucketTails | pSelectedRuns]
			constexpr umint c_Align = alignof(CMatchRun);

			umint LowerBufSize = umint(_CandidateLen) + umint(_QueryLen);
			umint BucketStride = umint(_QueryLen) + 1;
			umint BucketLen = BucketStride * BucketStride;
			umint QueryNextOffset = fg_AlignUp(LowerBufSize, c_Align);
			umint QueryMatchingsOffset = QueryNextOffset + fg_AlignUp(umint(_QueryLen) * sizeof(tf_CIndex), c_Align);
			umint BucketHeadsOffset = QueryMatchingsOffset + fg_AlignUp(umint(_QueryLen) * sizeof(CMatching), c_Align);
			umint BucketTailsOffset = BucketHeadsOffset + fg_AlignUp(BucketLen * sizeof(umint), c_Align);
			umint SelectedRunsOffset = BucketTailsOffset + fg_AlignUp(BucketLen * sizeof(umint), c_Align);
			umint TotalSize = SelectedRunsOffset + umint(_QueryLen) * sizeof(CMatchRun);

			// Use stack buffer for small allocations, heap for large ones
			constexpr umint c_StackBufSize = 4096;
			alignas(c_Align) uch8 StackBuf[c_StackBufSize];

			uch8 *pScratch;
			umint AllocSize = 0;
			if (TotalSize <= c_StackBufSize)
				pScratch = StackBuf;
			else
			{
				pScratch = (uch8 *)NMemory::fg_AllocAligned(TotalSize, c_Align);
				AllocSize = TotalSize;
			}
			auto ScratchCleanup = g_OnScopeExit / [pScratch, AllocSize]
				{
					if (AllocSize)
						NMemory::fg_Free(pScratch, AllocSize);
				}
			;

			uch8 *pLowerBuf = pScratch;

			for (tf_CIndex iQuery = 0; iQuery < _QueryLen; ++iQuery)
				pLowerBuf[umint(_CandidateLen) + umint(iQuery)] = (uch8)fg_CharLowerCase((uch8)_pQuery[iQuery]);

			bool bCaseInsensitiveExact = _CandidateLen == _QueryLen;
			aint nExactCaseMismatches = 0;

			for (tf_CIndex iCandidate = 0; iCandidate < _CandidateLen; ++iCandidate)
			{
				uch8 LowerChar = (uch8)fg_CharLowerCase((uch8)_pCandidate[iCandidate]);
				pLowerBuf[iCandidate] = LowerChar;

				if (iCandidate < _QueryLen)
				{
					if (_pCandidate[iCandidate] != _pQuery[iCandidate])
						++nExactCaseMismatches;

					if (LowerChar != pLowerBuf[umint(_CandidateLen) + umint(iCandidate)])
						bCaseInsensitiveExact = false;
				}
			}

			if (bCaseInsensitiveExact)
				return fg_BuildContiguousMatchResult(aint(_CandidateLen), aint(_QueryLen), 0, nExactCaseMismatches);

			if (_CandidateLen > _QueryLen)
			{
				tf_CIndex iBestContiguous = c_Unset;
				int nBestContiguousMismatches = int(_QueryLen) + 1;
				for (tf_CIndex iStart = 0; iStart <= _CandidateLen - _QueryLen; ++iStart)
				{
					if (pLowerBuf[iStart] != pLowerBuf[umint(_CandidateLen)])
						continue;

					tf_CIndex Found = 1;
					while (Found < _QueryLen && pLowerBuf[iStart + Found] == pLowerBuf[umint(_CandidateLen) + umint(Found)])
						++Found;

					if (Found != _QueryLen)
						continue;

					int nMismatches = 0;
					for (tf_CIndex iChar = 0; iChar < _QueryLen; ++iChar)
					{
						if (_pCandidate[iStart + iChar] != _pQuery[iChar])
							++nMismatches;
					}

					if (nMismatches == 0)
						return fg_BuildContiguousMatchResult(aint(_CandidateLen), aint(_QueryLen), aint(iStart), 0);

					if (nMismatches < nBestContiguousMismatches)
					{
						iBestContiguous = iStart;
						nBestContiguousMismatches = nMismatches;
					}
				}

				if (iBestContiguous != c_Unset)
					return fg_BuildContiguousMatchResult(aint(_CandidateLen), aint(_QueryLen), aint(iBestContiguous), nBestContiguousMismatches);
			}

			// Construct matching structures within the scratch buffer
			tf_CIndex *pQueryNext = reinterpret_cast<tf_CIndex *>(pScratch + QueryNextOffset);
			umint *pBucketHeads = reinterpret_cast<umint *>(pScratch + BucketHeadsOffset);
			umint *pBucketTails = reinterpret_cast<umint *>(pScratch + BucketTailsOffset);
			CMatchRun *pSelectedRuns = reinterpret_cast<CMatchRun *>(pScratch + SelectedRunsOffset);

			// Build query character position index: linked list per lowercase character
			tf_CIndex QueryHead[256];
			NMemory::fg_ObjectSet(QueryHead, TCLimitsInt<tf_CIndex>::mc_Max, 256);

			for (tf_CIndex iQuery = _QueryLen - 1; ; --iQuery)
			{
				pQueryNext[iQuery] = QueryHead[pLowerBuf[umint(_CandidateLen) + umint(iQuery)]];
				QueryHead[pLowerBuf[umint(_CandidateLen) + umint(iQuery)]] = iQuery;
				if (iQuery == 0)
					break;
			}

			// Early exit: if no candidate character exists in the query, no match is possible
			{
				bool bAnyCandidateCharExists = false;
				for (tf_CIndex iCandidate = 0; iCandidate < _CandidateLen; ++iCandidate)
				{
					if (QueryHead[pLowerBuf[iCandidate]] != c_Unset)
					{
						bAnyCandidateCharExists = true;
						break;
					}
				}
				if (!bAnyCandidateCharExists)
					return {};
			}

			NContainer::TCVector<CMatchRun> MatchRuns;
			MatchRuns.f_Reserve(fg_Min(umint(_CandidateLen) * umint(_QueryLen), umint(1024)));
			constexpr umint c_UnsetRun = TCLimitsInt<umint>::mc_Max;
			for (umint iBucket = 0; iBucket < BucketLen; ++iBucket)
			{
				pBucketHeads[iBucket] = c_UnsetRun;
				pBucketTails[iBucket] = c_UnsetRun;
			}
			auto fAddMatchRun = [&](tf_CIndex _iCandidate, tf_CIndex _iQuery, tf_CIndex _nMatched, tf_CIndex _nCaseMismatches)
				{
					umint iBucket = umint(_nMatched) * BucketStride + umint(_nCaseMismatches);
					umint iRun = MatchRuns.f_GetLen();
					auto &MatchRun = MatchRuns.f_Insert();
					MatchRun.m_nMatched = _nMatched;
					MatchRun.m_iQuery = _iQuery;
					MatchRun.m_iCandidate = _iCandidate;
					MatchRun.m_nCaseMismatches = _nCaseMismatches;
					MatchRun.m_iNextRun = c_UnsetRun;

					if (pBucketHeads[iBucket] == c_UnsetRun)
						pBucketHeads[iBucket] = iRun;
					else
						MatchRuns.f_GetArray()[pBucketTails[iBucket]].m_iNextRun = iRun;

					pBucketTails[iBucket] = iRun;
				}
			;

			for (tf_CIndex iStart = 0; iStart < _CandidateLen; ++iStart)
			{
				tf_CIndex iQueryPos = QueryHead[pLowerBuf[iStart]];
				while (iQueryPos != c_Unset)
				{
					// Extend match from candidate[iStart] against query[iQueryPos]
					// First char already matches by construction, so start from second
					// Precompute max extent so the inner loop has a single bound check
					tf_CIndex nMaxExtent = fg_Min(tf_CIndex(_CandidateLen - iStart), tf_CIndex(_QueryLen - iQueryPos));
					tf_CIndex Found = 1;
					while (Found < nMaxExtent && pLowerBuf[iStart + Found] == pLowerBuf[umint(_CandidateLen) + umint(iQueryPos) + umint(Found)])
						++Found;

					tf_CIndex nCaseMismatches = 0;
					for (tf_CIndex iOffset = 0; iOffset < Found; ++iOffset)
					{
						if (_pCandidate[iStart + iOffset] != _pQuery[iQueryPos + iOffset])
							++nCaseMismatches;
					}

					fAddMatchRun(iStart, iQueryPos, Found, nCaseMismatches);

					if (Found > 1)
						fAddMatchRun(iStart, iQueryPos, tf_CIndex(1), _pCandidate[iStart] != _pQuery[iQueryPos] ? tf_CIndex(1) : tf_CIndex(0));

					iQueryPos = pQueryNext[iQueryPos];
				}
			}
			// Phase 3: Resolve unordered, non-overlapping runs into pQueryMatchings
			CMatching *pQueryMatchings = reinterpret_cast<CMatching *>(pScratch + QueryMatchingsOffset);
			NMemory::fg_MemClear(pQueryMatchings, umint(_QueryLen) * sizeof(CMatching));
			NMemory::fg_MemClear(pLowerBuf, LowerBufSize);

			uch8 *pCandidateUsed = pLowerBuf;
			uch8 *pQueryUsed = pLowerBuf + _CandidateLen;
			umint nSelectedRuns = 0;
			auto fAcceptRun = [&](CMatchRun const &_MatchRun)
				{
					pSelectedRuns[nSelectedRuns] = _MatchRun;
					++nSelectedRuns;
					for (tf_CIndex iOffset = 0; iOffset < _MatchRun.m_nMatched; ++iOffset)
					{
						pCandidateUsed[_MatchRun.m_iCandidate + iOffset] = true;
						pQueryUsed[_MatchRun.m_iQuery + iOffset] = true;

						auto &QueryMatching = pQueryMatchings[_MatchRun.m_iQuery + iOffset];
						QueryMatching.m_nMatched = _MatchRun.m_nMatched;
						QueryMatching.m_iQuery = _MatchRun.m_iQuery;
						QueryMatching.m_iCandidate = _MatchRun.m_iCandidate;
					}
				}
			;

			auto pMatchRuns = MatchRuns.f_GetArray();

			for (tf_CIndex nMatched = _QueryLen; nMatched > 0; --nMatched)
			{
				for (tf_CIndex nCaseMismatches = 0; nCaseMismatches <= nMatched; ++nCaseMismatches)
				{
					umint iRun = pBucketHeads[umint(nMatched) * BucketStride + umint(nCaseMismatches)];
					while (iRun != c_UnsetRun)
					{
						CMatchRun MatchRun = pMatchRuns[iRun];
						umint iNextRun = MatchRun.m_iNextRun;
						tf_CIndex iOffset = 0;
						while (iOffset < MatchRun.m_nMatched)
						{
							while
							(
								iOffset < MatchRun.m_nMatched
								&& (pCandidateUsed[MatchRun.m_iCandidate + iOffset] || pQueryUsed[MatchRun.m_iQuery + iOffset])
							)
							{
								++iOffset;
							}

							tf_CIndex iStartOffset = iOffset;
							tf_CIndex nSegmentCaseMismatches = 0;
							while
							(
								iOffset < MatchRun.m_nMatched
								&& !pCandidateUsed[MatchRun.m_iCandidate + iOffset]
								&& !pQueryUsed[MatchRun.m_iQuery + iOffset]
							)
							{
								if (_pCandidate[MatchRun.m_iCandidate + iOffset] != _pQuery[MatchRun.m_iQuery + iOffset])
									++nSegmentCaseMismatches;

								++iOffset;
							}

							tf_CIndex nSegmentMatched = iOffset - iStartOffset;
							if (nSegmentMatched == 0)
								continue;

							if (nSegmentMatched == MatchRun.m_nMatched)
								fAcceptRun(MatchRun);
							else
								fAddMatchRun(MatchRun.m_iCandidate + iStartOffset, MatchRun.m_iQuery + iStartOffset, nSegmentMatched, nSegmentCaseMismatches);
						}
						iRun = iNextRun;
					}
				}
			}

			// Phase 4: Count unmatched and compute score
			int32 nUnmatchedQuery = 0;
			fp64 MatchPenalty = 0.0;
			for (tf_CIndex iQuery = 0; iQuery < _QueryLen; ++iQuery)
			{
				auto &QueryMatching = pQueryMatchings[iQuery];
				if (QueryMatching.m_nMatched == 0)
				{
					++nUnmatchedQuery;
					MatchPenalty += fp64(_QueryLen);
				}
				else
				{
					tf_CIndex iCandidatePos = QueryMatching.m_iCandidate + (iQuery - QueryMatching.m_iQuery);
					MatchPenalty += fp64(_QueryLen - QueryMatching.m_nMatched);
					// Penalize case mismatches
					if (_pCandidate[iCandidatePos] != _pQuery[iQuery])
						MatchPenalty += 0.5;
				}
			}

			// If no characters from the query matched at all, return no result
			if (nUnmatchedQuery == _QueryLen)
				return {};

			aint nMatched = 0;
			NContainer::TCVector<CFuzzyMatchRange> MatchRanges;
			if (nSelectedRuns > 1)
			{
				NMemory::fg_QSort
					(
						pSelectedRuns
						, nSelectedRuns
						, [](CMatchRun const &_Left, CMatchRun const &_Right)
						{
							if (auto Compare = _Left.m_iCandidate <=> _Right.m_iCandidate; Compare != 0)
								return Compare;

							return _Left.m_iQuery <=> _Right.m_iQuery;
						}
					)
				;
			}

			for (umint iSelectedRun = 0; iSelectedRun < nSelectedRuns; ++iSelectedRun)
			{
				auto const &MatchRun = pSelectedRuns[iSelectedRun];
				auto &Range = MatchRanges.f_Insert();
				Range.m_iStart = aint(MatchRun.m_iCandidate);
				Range.m_iEnd = aint(MatchRun.m_iCandidate + MatchRun.m_nMatched);
				nMatched += aint(MatchRun.m_nMatched);
			}

			fp64 MatchedPercentQuery = MatchPenalty / fp64(aint(_QueryLen) * aint(_QueryLen));
			fp64 UnmatchedPercent = fp64(aint(_CandidateLen) - nMatched) / fp64(_CandidateLen);
			fp64 UnmatchedPercentQuery = fp64(nUnmatchedQuery) / fp64(_QueryLen);

			CFuzzyMatchResult Result;
			Result.m_Score
				= MatchedPercentQuery * gc_WeightMatchPercent
				+ UnmatchedPercent * gc_WeightUnmatched
				+ UnmatchedPercentQuery * gc_WeightUnmatchedQuery
			;
			Result.m_Matches = fg_Move(MatchRanges);
			return Result;
		}
	}

	CFuzzyMatchResult fg_FuzzyMatchString(CStr const &_Candidate, CStr const &_Query)
	{
		if (_Candidate.f_GetLen() == 0 || _Query.f_GetLen() == 0)
			return {};

		umint CandidateLen = _Candidate.f_GetLen();
		umint QueryLen = _Query.f_GetLen();
		umint MaxLen = fg_Max(CandidateLen, QueryLen);

		ch8 const *pCandidate = _Candidate;
		ch8 const *pQuery = _Query;

		// Dispatch to the smallest index type that fits (mc_Max reserved as sentinel)
		if (MaxLen < umint(TCLimitsInt<uint8>::mc_Max))
			return fg_FuzzyMatchStringImpl<uint8>(pCandidate, pQuery, uint8(CandidateLen), uint8(QueryLen));
		else if (MaxLen < umint(TCLimitsInt<uint16>::mc_Max))
			return fg_FuzzyMatchStringImpl<uint16>(pCandidate, pQuery, uint16(CandidateLen), uint16(QueryLen));
		else if (MaxLen < umint(TCLimitsInt<uint32>::mc_Max))
			return fg_FuzzyMatchStringImpl<uint32>(pCandidate, pQuery, uint32(CandidateLen), uint32(QueryLen));
		else
			return fg_FuzzyMatchStringImpl<umint>(pCandidate, pQuery, umint(CandidateLen), umint(QueryLen));
	}
}
