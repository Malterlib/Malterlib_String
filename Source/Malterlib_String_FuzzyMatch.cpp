// Copyright © 2015 Hansof
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>
#include "Malterlib_String_FuzzyMatch.h"

namespace NMib::NStr
{
	namespace
	{
		struct CFuzzyMatching
		{
			aint m_MatichID = -1;
			aint m_nMatched = 0;
			aint m_iSource = -1;
		};

		template <bool tf_bNoCase, bool tf_bCheckLen, typename tf_CData1, typename tf_CData2>
		aint fg_StrFindPartial(const tf_CData1 *_pStr1, const tf_CData2 *_pStr2, mint _Len, mint &_Found)
		{
			using CData1 = NTraits::TCUnsigned<tf_CData1>;
			using CData2 = NTraits::TCUnsigned<tf_CData2>;

			const CData1 *pStr1Start = (const CData1 *)_pStr1;
			const CData1 *pStr1 = pStr1Start;
			const CData1 *pStr1End = pStr1Start + _Len;
			const CData2 *pStr2 = (const CData2 *)_pStr2;

			while (*pStr1)
			{
				if constexpr (tf_bCheckLen)
				{
					if (pStr1 >= pStr1End)
					{
						_Found = 0;
						return -1;
					}
				}

				const CData1 *pStr1Current = pStr1;
				const CData2 *pStr2Current = pStr2;
				while (1)
				{
					CData1 Data1;
					CData2 Data2;
					if constexpr (tf_bNoCase)
					{
						Data1 = fg_CharLowerCase(*pStr1Current);
						Data2 = fg_CharLowerCase(*pStr2Current);
					}
					else
					{
						Data1 = *pStr1Current;
						Data2 = *pStr2Current;
					}
					if (Data1 != Data2)
					{
						if (pStr2Current != pStr2)
						{
							_Found = pStr2Current - pStr2 ;
							return pStr1 - pStr1Start;
						}
						break;
					}
					++pStr1Current;
					++pStr2Current;
					if (!(*pStr2Current))
					{
						_Found = pStr2Current - pStr2;
						return pStr1 - pStr1Start;
					}
					if constexpr (tf_bCheckLen)
					{
						if (pStr1Current >= pStr1End)
						{
							if (pStr2Current != pStr2)
							{
								_Found = pStr2Current - pStr2;
								return pStr1 - pStr1Start;
							}
							_Found = 0;
							return -1;
						}
					}
					if (!(*pStr1Current))
					{
						if (pStr2Current != pStr2)
						{
							_Found = pStr2Current - pStr2;
							return pStr1 - pStr1Start;
						}
						_Found = 0;
						return -1;
					}
				}

				++pStr1;
			}
			_Found = 0;
			return -1;
		}
	}

	fp64 fg_FuzzyMatchString(CStr _Str0, CStr _Str1)
	{
		if (_Str1.f_GetLen() > _Str0.f_GetLen())
			fg_Swap(_Str0, _Str1);

		aint MaxLen = _Str0.f_GetLen();

		NContainer::TCVector<CFuzzyMatching> MatchingsArray;
		MatchingsArray.f_SetLen(MaxLen);
#ifdef DMibDebug
		auto &Matchings = MatchingsArray;
#else
		auto *Matchings = MatchingsArray.f_GetArray();
#endif
		//CFuzzyMatching *pMatchings = Matchings.f_GetArray();
		aint iMatchingID = -1;

		const ch8 *pParse0Start = _Str0;
		const ch8 *pParse1Start = _Str1;
		const ch8 *pParse1 = pParse1Start;
		while (*pParse1)
		{
			const ch8 *pParse0 = pParse0Start;

			mint Found;
			aint iFind = fg_StrFindPartial<true, false>(pParse0, pParse1, 0, Found);
			while (iFind >= 0 && Found > 0)
			{
				++iMatchingID;
				aint iStart = (pParse0 - pParse0Start) + iFind;
				bool bLarger = true;
				for (mint i = 0; i < Found; ++i)
				{
					if (aint(Found) < Matchings[iStart + i].m_nMatched)
					{
						bLarger = false;
						break;
					}
				}
				if (bLarger)
				{
					// Clear Matchings
					aint MatchingID = Matchings[iStart].m_MatichID;
					for (aint i = iStart - 1; i >= 0; --i)
					{
						if (Matchings[i].m_MatichID != MatchingID)
							break;
						Matchings[i] = CFuzzyMatching();
					}
					MatchingID = Matchings[iStart + Found - 1].m_MatichID;
					for (aint i = iStart + Found; i < MaxLen; ++i)
					{
						if (Matchings[i].m_MatichID != MatchingID)
							break;
						Matchings[i] = CFuzzyMatching();
					}
					// Add Mapping
					for (aint i = iStart; i < aint(iStart + Found); ++i)
					{
						auto &Matching = Matchings[i];
						Matching.m_MatichID = iMatchingID;
						Matching.m_nMatched = Found;
						Matching.m_iSource = pParse1 - pParse1Start;
					}
				}
				pParse0 += iFind + 1;
				iFind = fg_StrFindPartial<true, false>(pParse0, pParse1, 0, Found);
			}
			++pParse1;
		}

		aint nUnmatched = 0;
		aint LastMatched = -1;
		aint nSource = _Str1.f_GetLen();

		NContainer::TCVector<CFuzzyMatching> SourceMatchingsArray;
		SourceMatchingsArray.f_SetLen(nSource);
#ifdef DMibDebug
		auto &SourceMatchings = SourceMatchingsArray;
#else
		auto *SourceMatchings = SourceMatchingsArray.f_GetArray();
#endif
		//auto *pSourceMatchings = SourceMatchings.f_GetArray();

		for (aint i = 0; i < MaxLen; ++i)
		{
			auto &Matching = Matchings[i];
			if (Matching.m_nMatched == 0)
				++nUnmatched;
			if (Matching.m_MatichID != LastMatched && Matching.m_nMatched != 0)
			{
				aint iStart = Matching.m_iSource;
				bool bLarger = true;
				for (aint i = 0; i < Matching.m_nMatched; ++i)
				{
					if (aint(Matching.m_nMatched) < SourceMatchings[iStart + i].m_nMatched)
					{
						bLarger = false;
						break;
					}
				}
				if (bLarger)
				{
					aint MatchingID = SourceMatchings[iStart].m_MatichID;
					for (aint i = iStart - 1; i >= 0; --i)
					{
						if (SourceMatchings[i].m_MatichID != MatchingID)
							break;
						SourceMatchings[i] = CFuzzyMatching();
					}
					MatchingID = SourceMatchings[iStart + Matching.m_nMatched - 1].m_MatichID;
					for (aint i = iStart + Matching.m_nMatched; i < nSource; ++i)
					{
						if (SourceMatchings[i].m_MatichID != MatchingID)
							break;
						SourceMatchings[i] = CFuzzyMatching();
					}
					for (aint i = iStart; i < aint(iStart + Matching.m_nMatched); ++i)
						SourceMatchings[i] = Matching;
				}
			}
			LastMatched = Matching.m_MatichID;
		}

		mint nUnmatchedSource = 0;
		for (aint i = 0; i < nSource; ++i)
		{
			auto &Matching = SourceMatchings[i];
			if (Matching.m_nMatched == 0)
				++nUnmatchedSource;
		}

		int64 Ret0 = 0;
		for (aint i = 0; i < MaxLen; ++i)
			Ret0 += MaxLen - Matchings[i].m_nMatched;
		int64 Ret1 = 0;
		for (aint i = 0; i < nSource; ++i)
			Ret1 += nSource - SourceMatchings[i].m_nMatched;

		return
			(fp64(Ret0) / fp64(MaxLen).f_Sqr()) * 0.25
			+ (fp64(Ret1) / fp64(nSource).f_Sqr()) * 0.25
			+ (fp64(nUnmatched) / fp64(MaxLen) * 0.25)
			+ (fp64(nUnmatchedSource) / fp64(nSource) * 0.25)
		;
	}
}
