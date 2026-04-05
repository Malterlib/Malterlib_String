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

		auto fg_BuildContiguousMatchResult(ch8 const *_pCandidate, ch8 const *_pQuery, aint _CandidateLen, aint _QueryLen, aint _iStart) -> CFuzzyMatchResult
		{
			aint nCaseMismatches = 0;
			for (aint iChar = 0; iChar < _QueryLen; ++iChar)
			{
				if (_pCandidate[_iStart + iChar] != _pQuery[iChar])
					++nCaseMismatches;
			}

			CFuzzyMatchResult Result;
			Result.m_Matches.f_Reserve(1);
			auto &Range = Result.m_Matches.f_Insert();
			Range.m_iStart = _iStart;
			Range.m_iEnd = _iStart + _QueryLen;

			fp64 MatchedPercentQuery = fp64(nCaseMismatches) * 0.5 / fp64(_QueryLen * _QueryLen);
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

			// Single aligned allocation for all temporary buffers
			// Layout: [pLowerBuf | padding | pMatchings | pNextPos | pQueryMatchings | pQueryChainNext]
			constexpr umint c_Align = alignof(CMatching);

			umint LowerBufSize = umint(_CandidateLen) + umint(_QueryLen);
			umint MatchingsOffset = fg_AlignUp(LowerBufSize, c_Align);
			umint NextPosOffset = MatchingsOffset + fg_AlignUp(umint(_CandidateLen) * sizeof(CMatching), c_Align);
			umint QueryMatchingsOffset = NextPosOffset + fg_AlignUp(umint(_CandidateLen) * sizeof(tf_CIndex), c_Align);
			umint QueryChainOffset = QueryMatchingsOffset + fg_AlignUp(umint(_QueryLen) * sizeof(CMatching), c_Align);
			umint TotalSize = QueryChainOffset + umint(_QueryLen) * sizeof(tf_CIndex);

			// Use stack buffer for small allocations, heap for large ones
			constexpr umint c_StackBufSize = 4096;
			alignas(alignof(CMatching)) uch8 StackBuf[c_StackBufSize];

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

			bool bCaseSensitiveExact = _CandidateLen == _QueryLen;
			bool bCaseInsensitiveExact = _CandidateLen == _QueryLen;

			for (tf_CIndex iCandidate = 0; iCandidate < _CandidateLen; ++iCandidate)
			{
				uch8 LowerChar = (uch8)fg_CharLowerCase((uch8)_pCandidate[iCandidate]);
				pLowerBuf[iCandidate] = LowerChar;

				if (iCandidate < _QueryLen)
				{
					if (_pCandidate[iCandidate] != _pQuery[iCandidate])
						bCaseSensitiveExact = false;

					if (LowerChar != pLowerBuf[umint(_CandidateLen) + umint(iCandidate)])
						bCaseInsensitiveExact = false;
				}
			}

			if (bCaseSensitiveExact)
				return fg_BuildContiguousMatchResult(_pCandidate, _pQuery, aint(_CandidateLen), aint(_QueryLen), 0);

			if (bCaseInsensitiveExact)
				return fg_BuildContiguousMatchResult(_pCandidate, _pQuery, aint(_CandidateLen), aint(_QueryLen), 0);

			// Construct matching structures within the scratch buffer
			CMatching *pMatchings = reinterpret_cast<CMatching *>(pScratch + MatchingsOffset);
			tf_CIndex *pNextPos = reinterpret_cast<tf_CIndex *>(pScratch + NextPosOffset);
			tf_CIndex *pQueryChainNext = reinterpret_cast<tf_CIndex *>(pScratch + QueryChainOffset);

			// Build character position index: linked list per lowercase character
			tf_CIndex CharHead[256];
			NMemory::fg_ObjectSet(CharHead, TCLimitsInt<tf_CIndex>::mc_Max, 256);

			for (tf_CIndex iCandidate = _CandidateLen - 1; ; --iCandidate)
			{
				pNextPos[iCandidate] = CharHead[pLowerBuf[iCandidate]];
				CharHead[pLowerBuf[iCandidate]] = iCandidate;
				if (iCandidate == 0)
					break;
			}

			// Early exit: if no query character exists in the candidate, no match is possible
			{
				bool bAnyQueryCharExists = false;
				for (tf_CIndex iQuery = 0; iQuery < _QueryLen; ++iQuery)
				{
					if (CharHead[pLowerBuf[umint(_CandidateLen) + umint(iQuery)]] != c_Unset)
					{
						bAnyQueryCharExists = true;
						break;
					}
				}
				if (!bAnyQueryCharExists)
					return {};
			}

			// Zero-init matchings via memset (deferred past early exit; m_nMatched==0 means unset)
			NMemory::fg_MemClear(pMatchings, umint(_CandidateLen) * sizeof(CMatching));

			tf_CIndex iBestContiguous = c_Unset;
			int nBestContiguousMismatches = int(_QueryLen) + 1;

			tf_CIndex iQueryPos = 0;
			while (iQueryPos < _QueryLen)
			{
				pQueryChainNext[iQueryPos] = c_Unset;
				tf_CIndex iStart = CharHead[pLowerBuf[umint(_CandidateLen) + umint(iQueryPos)]];
				bool bQueryPosChained = false;
				while (iStart != c_Unset)
				{
					// Extend match from candidate[iStart] against query[iQueryPos]
					// First char already matches by construction, so start from second
					// Precompute max extent so the inner loop has a single bound check
					tf_CIndex nMaxExtent = fg_Min(tf_CIndex(_CandidateLen - iStart), tf_CIndex(_QueryLen - iQueryPos));
					tf_CIndex Found = 1;
					while (Found < nMaxExtent && pLowerBuf[iStart + Found] == pLowerBuf[umint(_CandidateLen) + umint(iQueryPos) + umint(Found)])
						++Found;

					if (iQueryPos == 0 && Found == _QueryLen) [[unlikely]]
					{
						// Track the contiguous match with best case quality
						int nMismatches = 0;
						for (tf_CIndex iChar = 0; iChar < _QueryLen; ++iChar)
						{
							if (_pCandidate[iStart + iChar] != _pQuery[iChar])
								++nMismatches;
						}
						if (nMismatches == 0)
							return fg_BuildContiguousMatchResult(_pCandidate, _pQuery, aint(_CandidateLen), aint(_QueryLen), aint(iStart));
						if (nMismatches < nBestContiguousMismatches)
						{
							iBestContiguous = iStart;
							nBestContiguousMismatches = nMismatches;
						}
						iStart = pNextPos[iStart];
						continue;
					}

					bool bLarger = true;
					for (tf_CIndex iOffset = 0; iOffset < Found; ++iOffset)
					{
						if (Found < pMatchings[iStart + iOffset].m_nMatched)
						{
							bLarger = false;
							break;
						}
					}

					// When the new match is the same length as an existing one at iStart, prefer better case quality
					if (bLarger && pMatchings[iStart].m_nMatched == Found)
					{
						auto &Existing = pMatchings[iStart];
						int nNewMismatches = 0;
						int nOldMismatches = 0;
						for (tf_CIndex iOffset = 0; iOffset < Found; ++iOffset)
						{
							if (_pCandidate[iStart + iOffset] != _pQuery[iQueryPos + iOffset])
								++nNewMismatches;
							if (_pCandidate[Existing.m_iCandidate + iOffset] != _pQuery[Existing.m_iQuery + iOffset])
								++nOldMismatches;
						}
						if (nNewMismatches > nOldMismatches)
							bLarger = false;
						else if (nNewMismatches == nOldMismatches)
						{
							bLarger = false;
							// Chain this query position as an alternative. Only insert once per
							// iQueryPos since multiple candidates with the same head share the chain.
							if (!bQueryPosChained)
							{
								pQueryChainNext[iQueryPos] = pQueryChainNext[pMatchings[iStart].m_iQuery];
								pQueryChainNext[pMatchings[iStart].m_iQuery] = iQueryPos;
								bQueryPosChained = true;
							}
						}
					}

					if (bLarger)
					{
						// Clear old matching that extends before the new match's start
						if (pMatchings[iStart].m_nMatched > 0)
						{
							tf_CIndex OldStart = pMatchings[iStart].m_iCandidate;
							for (tf_CIndex iClear = OldStart; iClear < iStart; ++iClear)
								pMatchings[iClear] = {};
						}

						// Clear old matching that extends after the new match's end
						if (pMatchings[iStart + Found - 1].m_nMatched > 0)
						{
							auto &EndMatch = pMatchings[iStart + Found - 1];
							tf_CIndex OldEnd = EndMatch.m_iCandidate + EndMatch.m_nMatched;
							for (tf_CIndex iClear = iStart + Found; iClear < OldEnd; ++iClear)
								pMatchings[iClear] = {};
						}

						// Record the new matching
						for (tf_CIndex iRecord = iStart; iRecord < iStart + Found; ++iRecord)
						{
							auto &Matching = pMatchings[iRecord];
							Matching.m_nMatched = Found;
							Matching.m_iQuery = iQueryPos;
							Matching.m_iCandidate = iStart;
						}
					}

					iStart = pNextPos[iStart];
				}

				if (iBestContiguous != c_Unset)
					return fg_BuildContiguousMatchResult(_pCandidate, _pQuery, aint(_CandidateLen), aint(_QueryLen), aint(iBestContiguous));

				++iQueryPos;
			}

			// Phase 3: Build pQueryMatchings (reverse mapping for query coverage)
			CMatching *pQueryMatchings = reinterpret_cast<CMatching *>(pScratch + QueryMatchingsOffset);
			NMemory::fg_MemClear(pQueryMatchings, umint(_QueryLen) * sizeof(CMatching));

			tf_CIndex LastMatch = c_Unset;

			for (tf_CIndex iCandidate = 0; iCandidate < _CandidateLen; ++iCandidate)
			{
				auto &Matching = pMatchings[iCandidate];
				if (Matching.m_iCandidate != LastMatch && Matching.m_nMatched != 0)
				{
					tf_CIndex iQueryAlt = Matching.m_iQuery;
					bool bWritten = false;
					while (!bWritten && iQueryAlt != c_Unset)
					{
						for (tf_CIndex iQuery = iQueryAlt; iQuery < iQueryAlt + Matching.m_nMatched; ++iQuery)
						{
							if (Matching.m_nMatched > pQueryMatchings[iQuery].m_nMatched)
							{
								pQueryMatchings[iQuery].m_nMatched = Matching.m_nMatched;
								pQueryMatchings[iQuery].m_iQuery = iQueryAlt;
								pQueryMatchings[iQuery].m_iCandidate = Matching.m_iCandidate;
								bWritten = true;
							}
						}
						if (!bWritten)
							iQueryAlt = pQueryChainNext[iQueryAlt];
					}
				}
				LastMatch = Matching.m_iCandidate;
			}

			// Phase 4: Count unmatched, mark candidate positions, and compute score in one pass
			// Reuse pLowerBuf for pCandidateMatched (no longer needed after main matching loop)
			uch8 *pCandidateMatched = pLowerBuf;
			NMemory::fg_MemClear(pCandidateMatched, umint(_CandidateLen));

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
					pCandidateMatched[iCandidatePos] = true;
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
			for (tf_CIndex iCandidate = 0; iCandidate < _CandidateLen;)
			{
				if (!pCandidateMatched[iCandidate])
				{
					++iCandidate;
					continue;
				}

				tf_CIndex iRangeStart = iCandidate;
				while (iCandidate < _CandidateLen && pCandidateMatched[iCandidate])
					++iCandidate;

				tf_CIndex iRangeEnd = iCandidate;

				auto &Range = MatchRanges.f_Insert();
				Range.m_iStart = aint(iRangeStart);
				Range.m_iEnd = aint(iRangeEnd);
				nMatched += aint(iRangeEnd) - aint(iRangeStart);
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
