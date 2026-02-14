// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	inline_large tf_CData1 *fg_StrReplaceChar(tf_CData1 *_pStr1, tf_CData2 _CharFind, tf_CData3 _CharReplace)
	{
		tf_CData1 *pStr1 = _pStr1;

		while (*pStr1)
		{
			if constexpr (sizeof(tf_CData1) > sizeof(tf_CData2))
			{
				if (*pStr1 - _CharFind == 0)
					*pStr1 = _CharReplace;
			}
			else
			{
				if (_CharFind - *pStr1 == 0)
					*pStr1 = _CharReplace;
			}

			++pStr1;
		}
		return _pStr1;
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	inline_large tf_CData1 *fg_StrReplaceChar(tf_CData1 *_pStr1, tf_CData2 _CharFind, tf_CData3 _CharReplace, mint _MaxLen)
	{
		tf_CData1 *pStr1 = _pStr1;
		tf_CData1 *pStr1End = _pStr1 + _MaxLen;

		while (*pStr1 && (pStr1End - pStr1))
		{
			if constexpr (sizeof(tf_CData1) > sizeof(tf_CData2))
			{
				if (*pStr1 - _CharFind == 0)
					*pStr1 = _CharReplace;
			}
			else
			{
				if (_CharFind - *pStr1 == 0)
					*pStr1 = _CharReplace;
			}

			++pStr1;
		}
		return _pStr1;
	}

	template <bool tf_bNoCase, bool tf_bUseCount = false, typename tf_CData1, typename tf_CData2, typename tf_CData3>
	inline tf_CData1 *fg_StrReplace(tf_CData1 *_pStr1, mint _Len, tf_CData2 const *_pStrFind, mint _LenFind, tf_CData3 const *_pStrReplace, mint _LenReplace, mint _MaxLen, mint _Count = 0)
	{
		--_MaxLen; // Reserve space for null terminator

		if (_LenReplace <= _LenFind)
		{
			tf_CData1 *pWrite = _pStr1;
			tf_CData1 const *pRead = _pStr1;
			tf_CData1 const *pEnd = _pStr1 + _Len;

			bool bFastPath;
			if constexpr (tf_bUseCount)
				bFastPath = _MaxLen + _Count * (_LenFind - _LenReplace) >= _Len;
			else
				bFastPath = _MaxLen >= _Len;

			if (bFastPath)
			{
				for (;;)
				{
					mint SearchLen = pEnd - pRead;
					aint MatchPos = fg_StrFind<tf_bNoCase, true>(pRead, _pStrFind, SearchLen);
					if (MatchPos < 0)
						break;

					tf_CData1 const *pMatch = pRead + MatchPos;

					mint SegLen = pMatch - pRead;
					if (pWrite != pRead)
						NMemory::fg_MemMove(pWrite, pRead, SegLen * sizeof(tf_CData1));
					pWrite += SegLen;

					if constexpr (sizeof(tf_CData1) == sizeof(tf_CData3))
						NMemory::fg_MemCopy(pWrite, _pStrReplace, _LenReplace * sizeof(tf_CData1));
					else
						NMemory::fg_ObjectCopy(pWrite, _pStrReplace, _LenReplace);
					pWrite += _LenReplace;
					pRead = pMatch + _LenFind;
				}

				if (pRead < pEnd)
				{
					mint RemainLen = pEnd - pRead;
					if (pWrite != pRead)
						NMemory::fg_MemMove(pWrite, pRead, RemainLen * sizeof(tf_CData1));
					pWrite += RemainLen;
				}

				*pWrite = 0;
			}
			else
			{
				tf_CData1 *pWriteEnd = _pStr1 + _MaxLen;

				for (;;)
				{
					mint SearchLen = pEnd - pRead;
					if (SearchLen <= 0)
						break;

					aint MatchPos = fg_StrFind<tf_bNoCase, true>(pRead, _pStrFind, SearchLen);
					if (MatchPos < 0)
						break;

					tf_CData1 const *pMatch = pRead + MatchPos;

					mint SegLen = pMatch - pRead;
					mint WriteLen = fg_Min(SegLen, pWriteEnd - pWrite);
					if (WriteLen > 0)
					{
						if (pWrite != pRead)
							NMemory::fg_MemMove(pWrite, pRead, WriteLen * sizeof(tf_CData1));
						pWrite += WriteLen;
					}

					WriteLen = fg_Min(_LenReplace, pWriteEnd - pWrite);
					if (WriteLen > 0)
					{
						if constexpr (sizeof(tf_CData1) == sizeof(tf_CData3))
							NMemory::fg_MemCopy(pWrite, _pStrReplace, WriteLen * sizeof(tf_CData1));
						else
							NMemory::fg_ObjectCopy(pWrite, _pStrReplace, WriteLen);
						pWrite += WriteLen;
					}

					pRead = pMatch + _LenFind;

					if (pWrite >= pWriteEnd)
						break;
				}

				if (pWrite < pWriteEnd && pRead < pEnd)
				{
					mint RemainLen = fg_Min(pEnd - pRead, pWriteEnd - pWrite);
					if (RemainLen > 0 && pWrite != pRead)
						NMemory::fg_MemMove(pWrite, pRead, RemainLen * sizeof(tf_CData1));
					pWrite += RemainLen;
				}

				*pWrite = 0;
			}
		}
		else
		{
			tf_CData1 const *pLenEnd = _pStr1 + _Len;

			mint nCount;
			if constexpr (tf_bUseCount)
				nCount = _Count;
			else
			{
				nCount = 0;
				tf_CData1 const *pScan = _pStr1;
				for (;;)
				{
					mint SearchLen = pLenEnd - pScan;
					if (SearchLen <= 0)
						break;
					aint MatchPos = fg_StrFind<tf_bNoCase, true>(pScan, _pStrFind, SearchLen);
					if (MatchPos < 0)
						break;
					++nCount;
					pScan = pScan + MatchPos + _LenFind;
				}
			}

			if (nCount == 0)
			{
				mint NewLen = fg_Min(_Len, _MaxLen);
				_pStr1[NewLen] = 0;
				return _pStr1;
			}

			mint LenDiff = _LenReplace - _LenFind;
			mint ProcessedNewLen = _Len + nCount * LenDiff;
			mint NewLen = fg_Min(ProcessedNewLen, _MaxLen);
			mint SkipRemaining = ProcessedNewLen - NewLen; // Amount to truncate from right

			tf_CData1 *pWrite = _pStr1 + NewLen;
			*pWrite = 0;

			tf_CData1 const *pReadEnd = pLenEnd;
			mint SearchLen = _Len;
			for
			(
				aint MatchPos = fg_StrFindReverse<tf_bNoCase, true, true>(_pStr1, _pStrFind, SearchLen, _LenFind)
				; MatchPos >= 0
				; MatchPos = fg_StrFindReverse<tf_bNoCase, true, true>(_pStr1, _pStrFind, SearchLen, _LenFind)
			)
			{
				tf_CData1 const *pMatch = _pStr1 + MatchPos;
				tf_CData1 const *pAfterMatch = pMatch + _LenFind;

				if (pReadEnd > pAfterMatch)
				{
					mint SegLen = pReadEnd - pAfterMatch;
					if (SkipRemaining >= SegLen)
						SkipRemaining -= SegLen;
					else
					{
						mint WriteLen = SegLen - SkipRemaining;
						pWrite -= WriteLen;
						NMemory::fg_MemMove(pWrite, pAfterMatch, WriteLen * sizeof(tf_CData1));
						SkipRemaining = 0;
					}
				}

				if (SkipRemaining >= _LenReplace)
					SkipRemaining -= _LenReplace;
				else
				{
					mint WriteLen = _LenReplace - SkipRemaining;
					pWrite -= WriteLen;
					if constexpr (sizeof(tf_CData1) == sizeof(tf_CData3))
						NMemory::fg_MemCopy(pWrite, _pStrReplace, WriteLen * sizeof(tf_CData1));
					else
						NMemory::fg_ObjectCopy(pWrite, _pStrReplace, WriteLen);
					SkipRemaining = 0;
				}

				pReadEnd = pMatch;
				SearchLen = MatchPos;
			}

			if (pReadEnd > _pStr1)
			{
				mint SegLen = pReadEnd - _pStr1;
				if (SkipRemaining < SegLen)
				{
					mint WriteLen = SegLen - SkipRemaining;
					pWrite -= WriteLen;
					if (pWrite != _pStr1)
						NMemory::fg_MemMove(pWrite, _pStr1, WriteLen * sizeof(tf_CData1));
				}
			}
		}

		return _pStr1;
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplace(tf_CData1 *_pStr1, mint _Len, tf_CData2 const *_pStrFind, mint _LenFind, tf_CData3 const *_pStrReplace, mint _LenReplace, mint _MaxLen)
	{
		return fg_StrReplace<false, false>(_pStr1, _Len, _pStrFind, _LenFind, _pStrReplace, _LenReplace, _MaxLen, 0);
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplace(tf_CData1 *_pStr1, tf_CData2 const *_pStrFind, tf_CData3 const *_pStrReplace, mint _MaxLen)
	{
		return fg_StrReplace<false, false>(_pStr1, fg_StrLen(_pStr1, _MaxLen), _pStrFind, fg_StrLen(_pStrFind), _pStrReplace, fg_StrLen(_pStrReplace), _MaxLen, 0);
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplaceNoCase(tf_CData1 *_pStr1, mint _Len, tf_CData2 const *_pStrFind, mint _LenFind, tf_CData3 const *_pStrReplace, mint _LenReplace, mint _MaxLen)
	{
		return fg_StrReplace<true, false>(_pStr1, _Len, _pStrFind, _LenFind, _pStrReplace, _LenReplace, _MaxLen, 0);
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplaceNoCase(tf_CData1 *_pStr1, tf_CData2 const *_pStrFind, tf_CData3 const *_pStrReplace, mint _MaxLen)
	{
		return fg_StrReplace<true, false>(_pStr1, fg_StrLen(_pStr1, _MaxLen), _pStrFind, fg_StrLen(_pStrFind), _pStrReplace, fg_StrLen(_pStrReplace), _MaxLen, 0);
	}

	// Convenience overloads that accept a pre-computed match count
	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplaceWithCount(tf_CData1 *_pStr1, mint _Len, tf_CData2 const *_pStrFind, mint _LenFind, tf_CData3 const *_pStrReplace, mint _LenReplace, mint _MaxLen, mint _Count)
	{
		return fg_StrReplace<false, true>(_pStr1, _Len, _pStrFind, _LenFind, _pStrReplace, _LenReplace, _MaxLen, _Count);
	}

	template <typename tf_CData1, typename tf_CData2, typename tf_CData3>
	tf_CData1 *fg_StrReplaceNoCaseWithCount
		(
			tf_CData1 *_pStr1
			, mint _Len, tf_CData2 const *_pStrFind
			, mint _LenFind
			, tf_CData3 const *_pStrReplace
			, mint _LenReplace
			, mint _MaxLen
			, mint _Count
		)
	{
		return fg_StrReplace<true, true>(_pStr1, _Len, _pStrFind, _LenFind, _pStrReplace, _LenReplace, _MaxLen, _Count);
	}
}
