// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include "Malterlib_String.h"

namespace NMib
{
	namespace NStr
	{

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| String functions																					|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename t_CData>
			inline_small t_CData *fg_StrAdd(t_CData *_pStr, aint _Add) // Adding a negative value will null the str
		{
			if (_Add < 0)
				return nullptr;
			else
				return _pStr + _Add;
		}


		inline_small aint fg_StrAdd(aint _Offset, aint _Add) // Adding a negative value will null the str
		{
			if (_Add < 0)
				return -1;
			else
				return _Offset + _Add;
		}

			


		// Static functions
		template <typename t_CData>
			inline_medium mint fg_StrLen(const t_CData *_pStr)
		{
			
			const t_CData *pStr = _pStr;

			while (*pStr)
				++pStr;

			return pStr - _pStr;

		}

		// Static functions
		template <typename t_CData>
			inline_medium mint fg_StrLen(const t_CData *_pStr, mint _MaxLen)
		{
			
			const t_CData *pStr = _pStr;
			const t_CData *pEnd = pStr + _MaxLen;

			while (*pStr && pStr < pEnd)
				++pStr;

			return pStr - _pStr;

		}

		template <typename t_CData>
			inline_large uint32 fg_StrHashDJB2(const t_CData *_pStr)
		{
			uint32 Hash = 5381;
			
			const t_CData *pStr = _pStr;

			uint32 Char = *(pStr++);
			while (Char)
			{
				Hash = Hash * 33 + Char;
				Char = *(pStr++);
			}

			return Hash;
		}

		template <typename t_CData>
			inline_large uint32 fg_StrHashSDBM(const t_CData *_pStr)
		{
			uint32 Hash = 0;
			
			const t_CData *pStr = _pStr;

			uint32 Char = *(pStr++);
			while (Char)
			{
				Hash = Char + (Hash << 6) + (Hash << 16) - Hash;
				Char = *(pStr++);
			}

			return Hash;
		}

		template <typename t_CData>
			inline_large uint32 fg_StrHash(const t_CData *_pStr)
		{
			return fg_StrHashDJB2(_pStr);
		}

		template <typename t_CData1, typename t_CData2>
			inline_medium t_CData1 *fg_StrCopy(t_CData1 *_pTo, const t_CData2 *_pFrom)
		{
			while (*_pFrom)
				*_pTo++ = *_pFrom++;
			*_pTo = 0;

			return _pTo;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrCopy(t_CData1 *_pTo, const t_CData2 *_pFrom, mint _MaxLen)
		{
			const t_CData1 *_pEnd = _pTo + _MaxLen - 1;
			while (*_pFrom && _pTo < _pEnd)
				*_pTo++ = *_pFrom++;
			*_pTo = 0;
			return _pTo;
		}

		template <typename t_CData1, typename t_CData2>
			inline_medium t_CData1 *fg_StrMove(t_CData1 *_pTo, const t_CData2 *_pFrom)
		{
			if (sizeof(t_CData1) == sizeof(t_CData2))
			{
				mint Len = fg_StrLen(_pFrom) + 1;
				NMem::fg_MemMove(_pTo, _pFrom, Len*sizeof(t_CData2));
				return _pTo;
			}
			else
			{
				return fg_StrCopy(_pTo, _pFrom);
			}
		}

		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrMove(t_CData1 *_pTo, const t_CData2 *_pFrom, mint _MaxLen)
		{
			if (sizeof(t_CData1) == sizeof(t_CData2))
			{
				mint Len = fg_Min(fg_StrLen(_pFrom), _MaxLen - 1);
				NMem::fg_MemMove(_pTo, _pFrom, Len*sizeof(t_CData2));
				_pTo[Len] = 0;
				return _pTo;
			}
			else
			{
				return fg_StrCopy(_pTo, _pFrom, _MaxLen);
			}
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Upper case																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		template <typename t_CData1>
			inline_large t_CData1 *fg_StrUpperCase(t_CData1 *_pStr)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			CData1 *pStr = (CData1 *)_pStr;
			CData1 UpperComapre = 0xffu;

			while (*pStr)
			{
				if (*pStr >= 'a' && *pStr <= 'z')
					*pStr -= 'a' - 'A';

				if (*pStr >= 0xe0u && *pStr <= UpperComapre)
					*pStr -= 0xe0u - 0xc0u;

				++pStr;
			}

			return _pStr;
		}

		template <typename t_CData1>
			inline_large t_CData1 *fg_StrUpperCase(t_CData1 *_pStr, mint _MaxLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			CData1 *pStr = (CData1 *)_pStr;
			const CData1 *pStrEnd = pStr + _MaxLen;
			CData1 UpperComapre = 0xffu;

			while (*pStr && pStr < pStrEnd)
			{
				if (*pStr >= 'a' && *pStr <= 'z')
					*pStr -= 'a' - 'A';

				if (*pStr >= 0xe0u && *pStr <= UpperComapre)
					*pStr -= 0xe0u - 0xc0u;

				++pStr;
			}
			return _pStr;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrUpperCase(t_CData1 *_pDest, mint _MaxDestLen, const t_CData2 *_pSource)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;

			CData1 *pDest = (CData1 *)_pDest;
			const CData1 *pDestEnd = pDest + (_MaxDestLen - 1);
			const CData2 *pSource = (const CData2 *)_pSource;
			CData2 UpperComapre = 0xffu;

			while (*pSource && pDest < pDestEnd)
			{
				if (*pSource >= 'a' && *pSource <= 'z')
					*(pDest++) = (t_CData1)(*(pSource++) - ('a' - 'A'));
				else if (*pSource >= 0xe0u && *pSource <= UpperComapre)
					*(pDest++) = (t_CData1)(*(pSource++) - (0xe0u - 0xc0u));
				else
					*(pDest++) = (t_CData1)(*(pSource++));
			}

			*pDest = 0;

			return _pDest;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrUpperCase(t_CData1 *_pDest, mint _MaxDestLen, const t_CData2 *_pSource, mint _SourceLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;

			CData1 *pDest = (CData1 *)_pDest;
			const CData1 *pDestEnd = pDest + (_MaxDestLen - 1);
			const CData2 *pSource = (const CData2 *)_pSource;
			const CData2 *pSourceEnd = pSource + _SourceLen;
			CData2 UpperComapre = 0xffu;

			while (*pSource && pSource < pSourceEnd && pDest < pDestEnd)
			{
				if (*pSource >= 'a' && *pSource <= 'z')
					*(pDest++) = (t_CData1)(*(pSource++) - ('a' - 'A'));
				else if (*pSource >= 0xe0u && *pSource <= UpperComapre)
					*(pDest++) = (t_CData1)(*(pSource++) - (0xe0u - 0xc0u));
				else
					*(pDest++) = (t_CData1)(*(pSource++));
			}

			*pDest = 0;

			return _pDest;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrUpperCase(t_CData1 *_pDest, const t_CData2 *_pSource, mint _SourceLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;

			CData1 *pDest = (CData1 *)_pDest;
			const CData2 *pSource = (const CData2 *)_pSource;
			const CData2 *pSourceEnd = pSource + _SourceLen;
			CData2 UpperComapre = 0xffu;

			while (*pSource && pSource < pSourceEnd)
			{
				if (*pSource >= 'a' && *pSource <= 'z')
					*(pDest++) = (CData1)(*(pSource++) - ('a' - 'A'));
				else if (*pSource >= 0xe0u && *pSource <= UpperComapre)
					*(pDest++) = (CData1)(*(pSource++) - (0xe0u - 0xc0u));
				else
					*(pDest++) = (CData1)*(pSource++);
			}

			*pDest = 0;

			return _pDest;
		}


        /***************************************************************************************************\
        |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
        | Lower case																						|
        |___________________________________________________________________________________________________|
        \***************************************************************************************************/

		template <typename t_CData1>
			inline_large t_CData1 *fg_StrLowerCase(t_CData1 *_pStr)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;

			CData1 *pStr = (CData1 *)_pStr;

			while (*pStr)
			{
				if (*pStr >= 'A' && *pStr <= 'Z')
					*pStr += 'a' - 'A';
				if (*pStr >= 0xc0u && *pStr <= 0xdfu)
					*pStr += 0xe0u - 0xc0u;
				++pStr;
			}

			return _pStr;
		}

		template <typename t_CData1>
			inline_large t_CData1 *fg_StrLowerCase(t_CData1 *_pStr, mint _MaxLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;

			CData1 *pStr = (CData1 *)_pStr;
			const CData1 *pStrEnd = pStr + _MaxLen;

			while (*pStr && pStr < pStrEnd)
			{
				if (*pStr >= 'A' && *pStr <= 'Z')
					*pStr += 'a' - 'A';
				if (*pStr >= 0xc0u && *pStr <= 0xdfu)
					*pStr += 0xe0u - 0xc0u;
				++pStr;
			}

			return _pStr;
		}


		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrLowerCase(t_CData1 *_pDest, mint _MaxDestLen, const t_CData2 *_pSource)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;

			CData1 *pDest = (CData1 *)_pDest;
			const CData1 *pDestEnd = pDest + (_MaxDestLen - 1);
			const CData2 *pSource = (const CData2 *)_pSource;

			while (*pSource && pDest < pDestEnd)
			{
				if (*pSource >= 'A' && *pSource <= 'Z')
					*(pDest++) = (t_CData1)(*(pSource++) + ('a' - 'A'));
				else if (*pSource >= 0xc0u && *pSource <= 0xdfu)
					*(pDest++) = (t_CData1)(*(pSource++) + (0xe0u - 0xc0u));
				else
					*(pDest++) = (t_CData1)(*(pSource++));
			}

			*pDest = 0;

			return _pDest;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrLowerCase(t_CData1 *_pDest, mint _MaxDestLen, const t_CData2 *_pSource, mint _SourceLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;

			CData1 *pDest = (CData1 *)_pDest;
			const CData1 *pDestEnd = pDest + (_MaxDestLen - 1);
			const CData2 *pSource = (const CData2 *)_pSource;
			const CData2 *pSourceEnd = pSource + _SourceLen;

			while (*pSource && pSource < pSourceEnd && pDest < pDestEnd)
			{
				if (*pSource >= 'A' && *pSource <= 'Z')
					*(pDest++) = (t_CData1)(*(pSource++) + ('a' - 'A'));
				else if (*pSource >= 0xc0u && *pSource <= 0xdfu)
					*(pDest++) = (t_CData1)(*(pSource++) + (0xe0u - 0xc0u));
				else
					*(pDest++) = (t_CData1)(*(pSource++));
			}

			*pDest = 0;

			return _pDest;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrLowerCase(t_CData1 *_pDest, const t_CData2 *_pSource, mint _SourceLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;

			CData1 *pDest = (CData1 *)_pDest;
			const CData2 *pSource = (const CData2 *)_pSource;
			const CData2 *pSourceEnd = pSource + _SourceLen;

			while (*pSource && pSource < pSourceEnd)
			{
				if (*pSource >= 'A' && *pSource <= 'Z')
					*(pDest++) = (t_CData1)(*(pSource++) + ('a' - 'A'));
				else if (*pSource >= 0xc0u && *pSource <= 0xdfu)
					*(pDest++) = (t_CData1)(*(pSource++) + (0xe0u - 0xc0u));
				else
					*(pDest++) = (t_CData1)(*(pSource++));
			}

			*pDest = 0;

			return _pDest;
		}


		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Capitalize (Uppercase first char)																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/


		template <typename t_CData1>
			inline_large t_CData1 *fg_StrCapitalize(t_CData1 *_pStr)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			CData1 *pStr = (CData1 *)_pStr;
			CData1 UpperComapre = 0xffu;

			if (*pStr)
			{
				if (*pStr >= 'a' && *pStr <= 'z')
					*pStr -= 'a' - 'A';

				if (*pStr >= 0xe0u && *pStr <= UpperComapre)
					*pStr -= 0xe0u - 0xc0u;

				++pStr;
			}

			return _pStr;
		}


		template <typename t_CData1>
			inline_large t_CData1 *fg_StrCapitalize(t_CData1 *_pStr, mint _MaxLen)
		{
			return fg_StrCapitalize(_pStr);
		}


        /***************************************************************************************************\
        |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
        | Cmp																								|
        |___________________________________________________________________________________________________|
        \***************************************************************************************************/


		template <typename t_CData1, typename t_CData2>
			inline_large typename TCChooseStrCompareType<t_CData1, t_CData2>::CType fg_StrCmp(const t_CData1 *_pStr1, const t_CData2 *_pStr2)
		{
			
			typedef typename TCChooseStrCompareType<t_CData1, t_CData2>::CType CRetType;
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			const CData1 *pStr1 = (const CData1 *)_pStr1;
			const CData2 *pStr2 = (const CData2 *)_pStr2;

			while (*pStr1 && *pStr2)
			{
				CRetType Ret0 = *pStr1;
				CRetType Ret1 = *pStr2;
				if (Ret0 != Ret1)
					return (Ret0 - Ret1) << 1;

				++pStr1;
				++pStr2;
			}

			if ((*pStr1) && !(*pStr2))
				return 1;

			if (!(*pStr1) && (*pStr2))
				return -1;

			return 0;

		}

		template <typename t_CData1, typename t_CData2>
		inline_large aint fg_StrCmpNoCaseIterator(t_CData1 &_Str1, t_CData2 &_Str2)
		{
			while (_Str1 && _Str2)
			{
				aint Ret0 = fg_CharLowerCase(*_Str1);
				aint Ret1 = fg_CharLowerCase(*_Str2);

				if (Ret0 != Ret1)
					return (Ret0 - Ret1) << 1;

				++_Str1;
				++_Str2;
			}

			if ((_Str1) && !(_Str2))
				return 1;

			if (!(_Str1) && (_Str2))
				return -1;

			return 0;

		}

		template <typename t_CData1, typename t_CData2>
		inline_large typename TCChooseStrCompareType<t_CData1, t_CData2>::CType fg_StrCmpNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2)
		{
			typedef typename TCChooseStrCompareType<t_CData1, t_CData2>::CType CRetType;
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			const CData1 *pStr1 = (const CData1 *)_pStr1;
			const CData2 *pStr2 = (const CData2 *)_pStr2;

			while (*pStr1 && *pStr2)
			{
				CRetType Ret0 = fg_CharLowerCase(*pStr1);
				CRetType Ret1 = fg_CharLowerCase(*pStr2);

				if (Ret0 != Ret1)
					return (Ret0 - Ret1) << 1;

				++pStr1;
				++pStr2;
			}

			if ((*pStr1) && !(*pStr2))
				return 1;

			if (!(*pStr1) && (*pStr2))
				return -1;

			return 0;

		}

		template <typename t_CData1, typename t_CData2>
			inline_large typename TCChooseStrCompareType<t_CData1, t_CData2>::CType fg_StrCmp(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen)
		{
			typedef typename TCChooseStrCompareType<t_CData1, t_CData2>::CType CRetType;
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			const CData1 *pStr1 = (const CData1 *)_pStr1;
			const CData2 *pStr2 = (const CData2 *)_pStr2;

			const CData1 *pStr1End = pStr1 + _MaxLen;
			
			while (*pStr1 && *pStr2)
			{
				CRetType Ret0 = *pStr1;
				CRetType Ret1 = *pStr2;
				if (Ret0 != Ret1)
					return (Ret0 - Ret1) << 1;

				++pStr1;
				++pStr2;

				if (pStr1End - pStr1 <= 0)
					return 0;
			}

			if ((*pStr1) && !(*pStr2))
				return 1;

			if (!(*pStr1) && (*pStr2))
				return -1;

			return 0;

		}

		template <typename t_CData1, typename t_CData2>
			inline_large typename TCChooseStrCompareType<t_CData1, t_CData2>::CType fg_StrCmpNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen)
		{
			typedef typename TCChooseStrCompareType<t_CData1, t_CData2>::CType CRetType;
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			const CData1 *pStr1 = (const CData1 *)_pStr1;
			const CData2 *pStr2 = (const CData2 *)_pStr2;
			const CData1 *pStr1End = pStr1 + _MaxLen;

			while (*pStr1 && *pStr2)
			{
				CRetType Ret0 = fg_CharLowerCase(*pStr1);
				CRetType Ret1 = fg_CharLowerCase(*pStr2);

				if (Ret0 != Ret1)
					return (Ret0 - Ret1) << 1;

				++pStr1;
				++pStr2;
				if (pStr1End - pStr1 <= 0)
					return 0;
			}

			if ((*pStr1) && !(*pStr2))
				return 1;

			if (!(*pStr1) && (*pStr2))
				return -1;

			return 0;

		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Searching
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindChar(const t_CData1 *_pStr1, t_CData2 _Char)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CChar1;
			const CChar1 *pStr1 = (const CChar1 *)_pStr1;
			typename NTraits::TCUnsigned<t_CData2>::CType Char = _Char;

			while (*pStr1)
			{
				if (*pStr1 == Char)
					return pStr1 - (const CChar1 *)_pStr1;

				++pStr1;
			}
			return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharNoCase(const t_CData1 *_pStr1, t_CData2 _Char)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CChar1;
			const CChar1 *pStr1 = (const CChar1 *)_pStr1;
			typename NTraits::TCUnsigned<t_CData2>::CType Char = fg_CharLowerCase(_Char);

			while (*pStr1)
			{
				if (fg_CharLowerCase(*pStr1) == Char)
					return pStr1 - (const CChar1 *)_pStr1;

				++pStr1;
			}
			return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharReverse(const t_CData1 *_pStr1, t_CData2 _Char)
		{
			if (!(*_pStr1))
				return -1;

			typedef typename NTraits::TCUnsigned<t_CData1>::CType CChar1;
			const CChar1 *pStr1 = (const CChar1 *)_pStr1;
			typename NTraits::TCUnsigned<t_CData2>::CType Char = _Char;

			// Find end
			while (*pStr1)
			{
				++pStr1;
			}
			--pStr1;

			while (pStr1 >= (const CChar1 *)_pStr1)
			{
				if (*pStr1 == Char)
					return pStr1 - (const CChar1 *)_pStr1;

				--pStr1;
			}
			return -1;
		}


		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharReverseNoCase(const t_CData1 *_pStr1, t_CData2 _Char)
		{
			if (!(*_pStr1))
				return -1;

			typedef typename NTraits::TCUnsigned<t_CData1>::CType CChar1;
			const CChar1 *pStr1 = (const CChar1 *)_pStr1;
			typename NTraits::TCUnsigned<t_CData2>::CType Char = fg_CharLowerCase(_Char);

			// Find end
			while (*pStr1)
			{
				++pStr1;
			}
			--pStr1;

			while (pStr1 >= (const CChar1 *)_pStr1)
			{
				if (fg_CharLowerCase(*pStr1) == Char)
					return pStr1 - (const CChar1 *)_pStr1;

				--pStr1;
			}
			return -1;
		}


		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindChar(const t_CData1 *_pStr1, t_CData2 _Char, mint _MaxLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CChar1;
			const CChar1 *pStr1 = (const CChar1 *)_pStr1;
			typename NTraits::TCUnsigned<t_CData2>::CType Char = _Char;
			const CChar1 *pStr1End = (const CChar1 *)(_pStr1 + _MaxLen);
			
			while (*pStr1 && pStr1End - pStr1 > 0)
			{
				if (*pStr1 == Char)
					return pStr1 - (const CChar1 *)_pStr1;

				++pStr1;
			}
			return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharNoCase(const t_CData1 *_pStr1, t_CData2 _Char, mint _MaxLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CChar1;
			const CChar1 *pStr1 = (const CChar1 *)_pStr1;
			typename NTraits::TCUnsigned<t_CData2>::CType Char = fg_CharLowerCase(_Char);
			const CChar1 *pStr1End = (const CChar1 *)(_pStr1 + _MaxLen);
			
			while (*pStr1 && pStr1End - pStr1 > 0)
			{
				if (fg_CharLowerCase(*pStr1) == Char)
					return pStr1 - (const CChar1 *)_pStr1;

				++pStr1;
			}
			return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharReverse(const t_CData1 *_pStr1, t_CData2 _Char, mint _MaxLen)
		{
			if (!(*_pStr1))
				return -1;

			typedef typename NTraits::TCUnsigned<t_CData1>::CType CChar1;
			typename NTraits::TCUnsigned<t_CData2>::CType Char = _Char;

			const CChar1 *pStartPos = (const CChar1 *)_pStr1;
			const CChar1 *pCurPos = pStartPos;

			// Find end.
			while (*pCurPos)
				++pCurPos;

			mint Len = pCurPos - pStartPos;
			if (Len > _MaxLen)
				pCurPos = pStartPos + _MaxLen;

			--pCurPos;

			for (;pCurPos >= pStartPos; --pCurPos)
			{
				if (*pCurPos == Char)
					return pCurPos - pStartPos;
			}

			return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharReverseNoCase(const t_CData1 *_pStr1, t_CData2 _Char, mint _MaxLen)
		{
			if (!(*_pStr1))
				return -1;

			typedef typename NTraits::TCUnsigned<t_CData1>::CType CChar1;
			typename NTraits::TCUnsigned<t_CData2>::CType Char = _Char;

			const CChar1 *pStartPos = (const CChar1 *)_pStr1;
			const CChar1 *pCurPos = pStartPos;

			Char = fg_CharLowerCase(Char);

			// Find end.
			while (*pCurPos)
				++pCurPos;

			mint Len = pCurPos - pStartPos;
			if (Len > _MaxLen)
				pCurPos = pStartPos + _MaxLen;

			--pCurPos;

			for (;pCurPos >= pStartPos; --pCurPos)
			{
				if (fg_CharLowerCase(*pCurPos) == Char)
					return pCurPos - pStartPos;
			}

			return -1;
		}




		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindChars(const t_CData1 *_pStr1, const t_CData2 *_pChars)
		{
			const t_CData2 *pChar = _pChars;
			aint iBest = TCLimitsInt<aint>::mc_Max;
			while (*pChar)
			{
				aint iRet = fg_StrFindChar(_pStr1, *pChar);
				if (iRet >= 0 && iRet < iBest)
					iBest = iRet;
				++pChar;
			}
			if (iBest != TCLimitsInt<aint>::mc_Max)
				return iBest;
			else
				return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharsNoCase(const t_CData1 *_pStr1, const t_CData2 *_pChars)
		{
			const t_CData2 *pChar = _pChars;
			aint iBest = TCLimitsInt<aint>::mc_Max;
			while (*pChar)
			{
				aint iRet = fg_StrFindCharNoCase(_pStr1, *pChar);
				if (iRet >= 0 && iRet < iBest)
					iBest = iRet;
				++pChar;
			}
			if (iBest != TCLimitsInt<aint>::mc_Max)
				return iBest;
			else
				return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharsReverse(const t_CData1 *_pStr1, const t_CData2 *_pChars)
		{
			const t_CData2 *pChar = _pChars;
			aint iBest = -1;
			while (*pChar)
			{
				aint iRet = fg_StrFindCharReverse(_pStr1, *pChar);
				if (iRet >= 0 && iRet > iBest)
					iBest = iRet;
				++pChar;
			}
			return iBest;
		}


		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharsReverseNoCase(const t_CData1 *_pStr1, const t_CData2 *_pChars)
		{
			const t_CData2 *pChar = _pChars;
			aint iBest = -1;
			while (*pChar)
			{
				aint iRet = fg_StrFindCharReverseNoCase(_pStr1, *pChar);
				if (iRet >= 0 && iRet > iBest)
					iBest = iRet;
				++pChar;
			}
			return iBest;
		}


		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindChars(const t_CData1 *_pStr1, const t_CData2 *_pChars, mint _MaxLen)
		{
			const t_CData2 *pChar = _pChars;
			aint iBest = TCLimitsInt<aint>::mc_Max;
			while (*pChar)
			{
				aint iRet = fg_StrFindChar(_pStr1, *pChar, _MaxLen);
				if (iRet >= 0 && iRet < iBest)
					iBest = iRet;
				++pChar;
			}
			if (iBest != TCLimitsInt<aint>::mc_Max)
				return iBest;
			else
				return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharsNoCase(const t_CData1 *_pStr1, const t_CData2 *_pChars, mint _MaxLen)
		{
			const t_CData2 *pChar = _pChars;
			aint iBest = TCLimitsInt<aint>::mc_Max;
			while (*pChar)
			{
				aint iRet = fg_StrFindCharNoCase(_pStr1, *pChar, _MaxLen);
				if (iRet >= 0 && iRet < iBest)
					iBest = iRet;
				++pChar;
			}
			if (iBest != TCLimitsInt<aint>::mc_Max)
				return iBest;
			else
				return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharsReverse(const t_CData1 *_pStr1, const t_CData2 *_pChars, mint _MaxLen)
		{
			const t_CData2 *pChar = _pChars;
			aint iBest = -1;
			while (*pChar)
			{
				aint iRet = fg_StrFindCharReverse(_pStr1, *pChar, _MaxLen);
				if (iRet >= 0 && iRet > iBest)
					iBest = iRet;
				++pChar;
			}
			return iBest;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindCharsReverseNoCase(const t_CData1 *_pStr1, const t_CData2 *_pChars, mint _MaxLen)
		{
			const t_CData2 *pChar = _pChars;
			aint iBest = -1;
			while (*pChar)
			{
				aint iRet = fg_StrFindCharReverseNoCase(_pStr1, *pChar, _MaxLen);
				if (iRet >= 0 && iRet > iBest)
					iBest = iRet;
				++pChar;
			}
			return iBest;
		}

		template <bint t_bCheckLen, typename t_CData1>
			inline_large bint fg_StrIsAnsi(const t_CData1 *_pStr1, mint _Len)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			const CData1 *pStr1Start = (const CData1 *)_pStr1;
			const CData1 *pStr1 = pStr1Start;
			const CData1 *pStr1End = pStr1Start + _Len;

			while (*pStr1)
			{
				if (t_bCheckLen)
				{
					if (pStr1 >= pStr1End)
						return true;
				}

				if (*pStr1 >= 128)
					return false;

				++pStr1;
			}
			return true;
		}
		template <typename t_CData1>
			inline_small bint fg_StrIsAnsi(const t_CData1 *_pStr1)
		{
				return fg_StrIsAnsi<0>(_pStr1, 0);
		}
		template <typename t_CData1>
			inline_small bint fg_StrIsAnsi(const t_CData1 *_pStr1, mint _Len)
		{
				return fg_StrIsAnsi<1>(_pStr1, _Len);
		}

		template <bint t_bNoCase, typename t_CData1, typename t_CData2>
		inline_large aint fg_StrFindIterator(t_CData1 &_Str1, t_CData2 &_Str2)
		{
			typedef t_CData1 CData1;
			typedef t_CData2 CData2;
			CData1 Str1Start = _Str1;
			CData1 Str1 = Str1Start;
			CData2 Str2 = _Str2;

			while (Str1)
			{
				CData1 Str1Current = Str1;
				CData2 Str2Current = Str2;
				while (1)
				{
					ch32 Data1;
					ch32 Data2;	
					if (t_bNoCase)
					{
						Data1 = fg_CharLowerCase(*Str1Current);
						Data2 = fg_CharLowerCase(*Str2Current);
					}
					else
					{
						Data1 = *Str1Current;
						Data2 = *Str2Current;
					}
					if (Data1 != Data2)
						break;
					++Str1Current;
					++Str2Current;
					if (!(Str2Current))
						return Str1 - Str1Start;
					if (!(Str1Current))
						return -1;
				}

				++Str1;
			}
			return -1;
		}

		template <bint t_bNoCase, bint t_bCheckLen, typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFind(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			const CData1 *pStr1Start = (const CData1 *)_pStr1;
			const CData1 *pStr1 = pStr1Start;
			const CData1 *pStr1End = pStr1Start + _Len;
			const CData2 *pStr2 = (const CData2 *)_pStr2;

			while (*pStr1)
			{
				if (t_bCheckLen)
				{
					if (pStr1 >= pStr1End)
						return -1;
				}

				const CData1 *pStr1Current = pStr1;
				const CData2 *pStr2Current = pStr2;
				while (1)
				{
					CData1 Data1;
					CData2 Data2;
					if (t_bNoCase)
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
						break;
					++pStr1Current;
					++pStr2Current;
					if (!(*pStr2Current))
						return pStr1 - pStr1Start;
					if (t_bCheckLen)
					{
						if (pStr1Current >= pStr1End)
							return -1;
					}
					if (!(*pStr1Current))
						return -1;
				}

				++pStr1;
			}
			return -1;
		}

		template <typename t_CData1, typename t_CData2>
			inline_small aint fg_StrFind(const t_CData1 *_pStr1, const t_CData2 *_pStr2)
		{
			return fg_StrFind<false, false>(_pStr1, _pStr2, 0);
		}

		template <typename t_CData1, typename t_CData2>
			inline_small aint fg_StrFindNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2)
		{
			return fg_StrFind<true, false>(_pStr1, _pStr2, 0);
		}

		template <typename t_CData1, typename t_CData2>
			inline_small aint fg_StrFind(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen)
		{
			return fg_StrFind<false, true>(_pStr1, _pStr2, _MaxLen);
		}

		template <typename t_CData1, typename t_CData2>
			inline_small aint fg_StrFindNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _MaxLen)
		{
			return fg_StrFind<true, true>(_pStr1, _pStr2, _MaxLen);
		}

		template <bint t_bNoCase, bint t_bCheckLen, typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindReverse(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len)
		{
			if (!(*_pStr1) || !(*_pStr2))
				return -1;

			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			const CData1 *pStr1 = (const CData1 *)_pStr1;
			const CData1 *pStr1Start = (const CData1 *)_pStr1;
			const CData2 *pStr2Start = (const CData2 *)_pStr2;
			const CData2 *pStr2End = (const CData2 *)_pStr2;
			const CData1 *pStr1End;

			// Find end
			while (*pStr2End)
			{
				++pStr2End;
			}
			--pStr2End;

			if (t_bCheckLen)
			{
				mint Len = 0;
				// Find end
				while (*pStr1)
				{
					++pStr1;
					++Len;
				}
				--pStr1;


				if (Len > _Len)
					pStr1End = (const CData1 *)_pStr1 + (Len - _Len);
				else
					pStr1End = (const CData1 *)_pStr1;
			}
			else
			{
				// Find end
				while (*pStr1)
				{
					++pStr1;
				}
				--pStr1;
				pStr1End = (const CData1 *)_pStr1;
			}

			while (pStr1 >= pStr1End)
			{
				const CData1 *pStr1Current = pStr1;
				const CData2 *pStr2Current = pStr2End;
				while (1)
				{
					CData1 Data1;
					CData2 Data2;
					if (t_bNoCase)
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
						break;
					if (pStr2Current == pStr2Start)
						return pStr1Current - pStr1Start;
					if (pStr1Current == pStr1End)
						return -1;
					--pStr1Current;
					--pStr2Current;
				}

				--pStr1;
			}

			return -1;
		}

		// Returns first character for searched string
		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindReverse(const t_CData1 *_pStr1, const t_CData2 *_pStr2)
		{
			return fg_StrFindReverse<false, false>(_pStr1, _pStr2, 0);
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindReverseNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2)
		{
			return fg_StrFindReverse<true, false>(_pStr1, _pStr2, 0);
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindReverse(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len)
		{
			return fg_StrFindReverse<false, true>(_pStr1, _pStr2, _Len);
		}

		template <typename t_CData1, typename t_CData2>
			inline_large aint fg_StrFindReverseNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len)
		{
			return fg_StrFindReverse<true, true>(_pStr1, _pStr2, _Len);
		}

		template <typename tf_CData1, typename tf_CData2>
		EMatchWildcardResult fg_StrMatchWildcard(const tf_CData1 *_pStr, const tf_CData2 *_pPattern)
		{
			const tf_CData1 *pParse = _pStr;
			const tf_CData2 *pPattern = _pPattern;

			while (*pParse && *pPattern)
			{
				if (*pPattern == '*')
				{
					while (*pPattern == '*')
						++pPattern;
					aint Max = NStr::fg_StrFindChars(pPattern, "*?");
					if (Max < 0)
						Max = NStr::fg_StrLen(pPattern);
					while (*pParse)
					{
						if (NStr::fg_StrCmp(pParse, pPattern, Max) == 0)
							break;
						++pParse;
					}
				}
				else if (*pPattern == '?')
				{
					++pPattern;
					++pParse;
				}
				else
				{
					if (*pPattern != *pParse)
						break;
					++pPattern;
					++pParse;
				}
			}
			while (*pPattern == '*')
				++pPattern;

			if (*pParse == *pPattern)
				return EMatchWildcardResult_WholeStringMatchedAndPatternExhausted;
			if (!(*pParse))
				return EMatchWildcardResult_WholeStringMatched;

			return EMatchWildcardResult_NotMatched;
		}

		template <typename t_CStr>
		bool fg_StrIsEmpty(t_CStr const *_pStr)
		{
			return *_pStr == 0;
		}
		

		/***************************************************************************************************\
        |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
        | StartsWith																							|
        |___________________________________________________________________________________________________|
        \***************************************************************************************************/

		template <bint t_bNoCase, bint t_bCheckLen, bint t_bCheckLen2, typename t_CData1, typename t_CData2>
			inline_large bint fg_StrStartsWith(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len, mint _Len2)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			const CData1 *pStr1 = (const CData1 *)_pStr1;
			const CData1 *pStr1End = pStr1 + _Len;
			if (_Len == TCLimitsInt<mint>::mc_Max)
				pStr1End = (const CData1 *)TCLimitsInt<mint>::mc_Max;
			const CData2 *pStr2 = (const CData2 *)_pStr2;
			const CData2 *pStr2End = pStr2 + _Len2;
			if (_Len2 == TCLimitsInt<mint>::mc_Max)
				pStr2End = (const CData2 *)TCLimitsInt<mint>::mc_Max;

			while (*pStr1 && *pStr2)
			{
				if (t_bCheckLen)
				{
					if (pStr1 >= pStr1End)
						break;
				}
				if (t_bCheckLen2)
				{
					if (pStr2 >= pStr2End)
						break;
				}

				CData1 Data1;
				CData2 Data2;
				if (t_bNoCase)
				{
					Data1 = fg_CharLowerCase(*pStr1);
					Data2 = fg_CharLowerCase(*pStr2);
				}
				else
				{
					Data1 = *pStr1;
					Data2 = *pStr2;
				}

				if (Data1 != Data2)
					break;

				++pStr1;
				++pStr2;

			}

			if (t_bCheckLen2)
			{
				if (pStr2 >= pStr2End)
					return true;
			}
			return *pStr2 == 0;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large bint fg_StrStartsWith(const t_CData1 *_pStr1, const t_CData2 *_pStr2)
		{
			return fg_StrStartsWith<false, false, false, t_CData1, t_CData2>(_pStr1, _pStr2, 0, 0);
		}

		template <typename t_CData1, typename t_CData2>
			inline_large bint fg_StrStartsWithNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2)
		{
			return fg_StrStartsWith<true, false, false, t_CData1, t_CData2>(_pStr1, _pStr2, 0, 0);
		}

		template <typename t_CData1, typename t_CData2>
			inline_large bint fg_StrStartsWith(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len)
		{
			return fg_StrStartsWith<false, true, false, t_CData1, t_CData2>(_pStr1, _pStr2, _Len, 0);
		}

		template <typename t_CData1, typename t_CData2>
			inline_large bint fg_StrStartsWith(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len, mint _Len2)
		{
			return fg_StrStartsWith<false, true, true, t_CData1, t_CData2>(_pStr1, _pStr2, _Len, _Len2);
		}

		template <typename t_CData1, typename t_CData2>
			inline_large bint fg_StrStartsWithNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len)
		{
			return fg_StrStartsWith<true, true, false, t_CData1, t_CData2>(_pStr1, _pStr2, _Len, 0);
		}

		template <typename t_CData1, typename t_CData2>
			inline_large bint fg_StrStartsWithNoCase(const t_CData1 *_pStr1, const t_CData2 *_pStr2, mint _Len, mint _Len2)
		{
			return fg_StrStartsWith<true, true, true, t_CData1, t_CData2>(_pStr1, _pStr2, _Len, _Len2);
		}

		/***************************************************************************************************\
        |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
        | Replacing																							|
        |___________________________________________________________________________________________________|
        \***************************************************************************************************/


		template <typename t_CData1, typename t_CData2, typename t_CData3>
			inline_large t_CData1 *fg_StrReplaceChar(t_CData1 *_pStr1, t_CData2 _CharFind, t_CData3 _CharReplace)
		{
			t_CData1 *pStr1 = _pStr1;

			while (*pStr1)
			{
				if (sizeof(t_CData1) > sizeof(t_CData2))
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


		template <typename t_CData1, typename t_CData2, typename t_CData3>
			inline_large t_CData1 *fg_StrReplace(t_CData1 *_pStr1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace)
		{
			t_CData1 *pStr1 = _pStr1;

			mint LenFind = fg_StrLen(_pStrFind);
			mint LenReplace = fg_StrLen(_pStrReplace);
			mint Len = fg_StrLen(_pStr1);

			while (t_CData1 *pStrFind = fg_StrAdd(pStr1, fg_StrFind(pStr1, _pStrFind)))
			{
				Len = Len - ((pStrFind + LenFind) - pStr1);
				NMem::fg_MemMove(pStrFind + LenReplace, pStrFind + LenFind, (Len + 1) * sizeof(t_CData1));
				NMem::fg_ObjectCopy(pStrFind, _pStrReplace, LenReplace);
				pStr1 = pStrFind + LenReplace;
			}
			return _pStr1;
		}

		template <typename t_CData1, typename t_CData2, typename t_CData3>
			inline_large t_CData1 *fg_StrReplaceChar(t_CData1 *_pStr1, t_CData2 _CharFind, t_CData3 _CharReplace, mint _MaxLen)
		{
			t_CData1 *pStr1 = _pStr1;
			t_CData1 *pStr1End = _pStr1 + _MaxLen;

			while (*pStr1 && (pStr1End - pStr1))
			{
				if (sizeof(t_CData1) > sizeof(t_CData2))
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


		template <typename t_CData1, typename t_CData2, typename t_CData3>
			inline_large t_CData1 *fg_StrReplace(t_CData1 *_pStr1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace, mint _MaxLen)
		{
			t_CData1 *pStr1 = _pStr1;
			--_MaxLen; // Null charater

			mint LenFind = fg_StrLen(_pStrFind);
			mint LenReplace = fg_StrLen(_pStrReplace);
			mint Len = fg_StrLen(_pStr1);
			aint LenLeft = _MaxLen - Len;
			aint Diff = LenReplace - LenFind;

			while (t_CData1 *pStrFind = fg_StrAdd(pStr1, fg_StrFind(pStr1, _pStrFind)))
			{
				if (LenLeft < Diff)
				{
					Len = _MaxLen - ((pStrFind + LenFind) - _pStr1);
					NMem::fg_MemMove(pStrFind + LenReplace, pStrFind + LenFind, Len * sizeof(t_CData1));
					_pStr1[_MaxLen]  = 0;
					mint Len2 = fg_Min((_MaxLen - (pStrFind - _pStr1)), LenReplace);
					NMem::fg_MemCopy(pStrFind, _pStrReplace, Len2 * sizeof(t_CData1));
					pStr1 = pStrFind + Len2;
				}
				else
				{
					Len = Len - ((pStrFind + LenFind) - pStr1);
					NMem::fg_MemMove(pStrFind + LenReplace, pStrFind + LenFind, (Len + 1) * sizeof(t_CData1));
					NMem::fg_MemCopy(pStrFind, _pStrReplace, LenReplace * sizeof(t_CData1));
					pStr1 = pStrFind + LenReplace;
				}
			}
			return _pStr1;
		}


		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Insert
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		// Insert
		template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrInsert(t_CData1 *_pStr1, aint _StartChar, const t_CData2 *_pStr2)
		{
			if (_StartChar < 0)
				return _pStr1;
			t_CData1 *pStr1 = _pStr1;
			while (_StartChar)
			{
				if (!(*pStr1))
					break;
				++pStr1;
				--_StartChar;
			}

			mint Str2Len = fg_StrLen(_pStr2);			
			fg_StrMove(pStr1 + Str2Len, pStr1);
			NMem::fg_MemCopy(pStr1, _pStr2, Str2Len * sizeof(t_CData1));
			return _pStr1;
		}

		template <typename t_CData1, typename t_CData2>
		inline_large t_CData1 *fg_StrInsert(t_CData1 *_pStr1, aint _StartChar, const t_CData2 *_pStr2, mint _MaxLen)
		{
			if (_StartChar < 0)
				return _pStr1;
			--_MaxLen;
			t_CData1 *pStr1 = _pStr1;
			while (_StartChar)
			{
				if (!(*pStr1))
					break;
				++pStr1;
				--_StartChar;
			}

			mint Str2Len = fg_StrLen(_pStr2);
			aint MaxLen = _MaxLen - ((pStr1 + Str2Len) - _pStr1) + 1;
			if (MaxLen > 0)
				fg_StrMove(pStr1 + Str2Len, pStr1, MaxLen);
			mint MaxLen2 = fg_Min(Str2Len, _MaxLen - (pStr1 - _pStr1));
			NMem::fg_MemCopy(pStr1, _pStr2, MaxLen2 * sizeof(t_CData1));
			pStr1[fg_Max(MaxLen2, (MaxLen + Str2Len))] = 0;
			return _pStr1;
		}

        /***************************************************************************************************\
        |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
        | Shortening
        |___________________________________________________________________________________________________|
        \***************************************************************************************************/

		// Shortening
		template <typename t_CData1>
		inline_large t_CData1 *fg_StrDelete(t_CData1 *_pStr1, aint _StartChar, mint _nChars)
		{
			if (_StartChar < 0)
				return _pStr1;
			t_CData1 *pStr1 = _pStr1;
			while (_StartChar)
			{
				if (!(*pStr1))
					return _pStr1;
				++pStr1;
				--_StartChar;
			}

			t_CData1 *pStr2 = pStr1;

			while (_nChars) 
			{
				if (!(*pStr2))
					break;
				
				++pStr2;
				--_nChars;
			}

			while (*pStr2)
			{
				*pStr1 = *pStr2;
				++pStr1;
				++pStr2;
			}
			*pStr1 = 0;
			return _pStr1;
		}

		template <typename t_CData1>
		inline_large t_CData1 *fg_StrLeft(t_CData1 *_pStr1, mint _nChars)
		{
			t_CData1 *pStr1 = _pStr1;
			while (_nChars)
			{
				if (!(*pStr1))
					return _pStr1;
				++pStr1;
				--_nChars;
			}

			*pStr1 = 0;

			return _pStr1;
		}

		template <typename t_CData1>
		inline_large t_CData1 *fg_StrExtract(t_CData1 *_pStr1, aint _StartChar, mint _nChars)
		{
			if (_StartChar < 0)
				return _pStr1;
			t_CData1 *pStr1 = _pStr1;
			while (_StartChar)
			{
				if (!(*pStr1))
				{
					*_pStr1 = 0;
					return _pStr1;
				}
				++pStr1;
				--_StartChar;
			}
			fg_StrMove(_pStr1, pStr1, _nChars + 1);
			return _pStr1;
		}

		template <typename t_CData1>
		inline_large t_CData1 *fg_StrExtract(t_CData1 *_pStr1, aint _StartChar)
		{
			if (_StartChar < 0)
				return _pStr1;
			t_CData1 *pStr1 = _pStr1;
			while (_StartChar)
			{
				if (!(*pStr1))
				{
					*_pStr1 = 0;
					return _pStr1;
				}
				++pStr1;
				--_StartChar;
			}
			fg_StrMove(_pStr1, pStr1);
			return _pStr1;
		}

		template <typename t_CData1>
		inline_large t_CData1 *fg_StrReverse(t_CData1 *_pStr1)
		{
			t_CData1 *pStr1 = _pStr1;
			t_CData1 *pStr1End = _pStr1;
			while (*pStr1End)
				++pStr1End;
			--pStr1End;

			while (pStr1 < pStr1End)
			{
				t_CData1 Temp = *pStr1;
				*pStr1 = *pStr1End;
				*pStr1End = Temp;
				++pStr1;
				--pStr1End;
			}
			return _pStr1;
		}

		
		template <typename t_CData1>
		inline_large t_CData1 *fg_StrRight(t_CData1 *_pStr1, mint _nChars)
		{
			return fg_StrExtract(_pStr1, fg_StrLen(_pStr1) - _nChars);
		}


		template <typename t_CData1, typename t_CData2>
		inline_small t_CData1 *fg_StrTrimLeft(t_CData1 *_pStr1, const t_CData2 *_pCharsToTrim)
		{
			t_CData1 *pStr1 = _pStr1;
			while (*pStr1)
			{
				const t_CData2 *pCharsToTrim = _pCharsToTrim;

				while (*pCharsToTrim)
				{
					if (sizeof(t_CData1) > sizeof(t_CData2))
					{
						if (*pStr1 - *pCharsToTrim == 0)
						{
							break;
						}
					}
					else
					{
						if (*pCharsToTrim - *pStr1  == 0)
						{
							break;
						}
					}
					++pCharsToTrim;
				}

				if (!(*pCharsToTrim))
					break;

				++pStr1;
			}
			
			return fg_StrExtract(_pStr1, pStr1 - _pStr1);
		}

		template <typename t_CData1>
		inline_small t_CData1 *fg_StrTrimLeft(t_CData1 *_pStr1)
		{
			return fg_StrTrimLeft(_pStr1, g_lWhiteSpaceChars);
		}

		template <typename t_CData1, typename t_CData2>
		inline_small t_CData1 *fg_StrTrimRight(t_CData1 *_pStr1, const t_CData2 *_pCharsToTrim)
		{
			t_CData1 *pStr1 = _pStr1;
			while (*pStr1)
			{
				++pStr1;
			}
			--pStr1;
			while (pStr1 >= _pStr1)
			{
				const t_CData2 *pCharsToTrim = _pCharsToTrim;

				while (*pCharsToTrim)
				{
					if (sizeof(t_CData1) > sizeof(t_CData2))
					{
						if (*pStr1 - *pCharsToTrim == 0)
						{
							break;
						}
					}
					else
					{
						if (*pCharsToTrim - *pStr1  == 0)
						{
							break;
						}
					}
					++pCharsToTrim;
				}

				if (!(*pCharsToTrim))
					break;
				*pStr1 = 0;

				--pStr1;
			}
			
			return _pStr1;
		}

		template <typename t_CData1>
		inline_small t_CData1 *fg_StrTrimRight(t_CData1 *_pStr1)
		{
			return fg_StrTrimRight(_pStr1, g_lWhiteSpaceChars);
		}

		template <typename t_CData1, typename t_CData2>
		inline_small t_CData1 *fg_StrTrim(t_CData1 *_pStr1, const t_CData2 *_pCharsToTrim)
		{
			return fg_StrTrimLeft(fg_StrTrimRight(_pStr1, _pCharsToTrim), _pCharsToTrim);
		}

		template <typename t_CData1>
		inline_small t_CData1 *fg_StrTrim(t_CData1 *_pStr1)
		{
			return fg_StrTrim(_pStr1, g_lWhiteSpaceChars);
		}


        /***************************************************************************************************\
        |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
        | Misc
        |___________________________________________________________________________________________________|
        \***************************************************************************************************/
		template <typename t_CData1>
		inline_small t_CData1 *fg_StrClear(t_CData1 *_pStr1)
		{
			*_pStr1 = 0;
		}

		template <typename t_CData1, typename t_CData2>
		inline_small t_CData1 *fg_StrSetAt(t_CData1 *_pStr1, aint _Index, t_CData2 _Character)
		{
			_pStr1[_Index] = t_CData1(_Character);
			return _pStr1;
		}

		template <typename t_CData1>
		inline_small typename NTraits::TCUnsigned<t_CData1>::CType fg_StrLargestChar(const t_CData1 *_pStr1)
		{
			typename NTraits::TCUnsigned<t_CData1>::CType Largest = 0;
			const typename NTraits::TCUnsigned<t_CData1>::CType *pStr1 = (const typename NTraits::TCUnsigned<t_CData1>::CType *)_pStr1;
			while (*pStr1) 
			{
				if (*pStr1 > Largest)
				{
					Largest = *pStr1;
				}
				++pStr1;
			}
			return Largest;
		}
		
		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, mint _MaxLen)
		{
			t_CData1 *pDest = _pStrDest;
			if (_MaxLen < 3)
			{
				*pDest = 0;
				return _pStrDest;
			}
			_MaxLen -= 2; // Null charater and one '"'

			t_CData1 *pMaxDest = pDest + _MaxLen;
			*(pDest++) = '\"';
			const t_CData2 *pParse = _pStrSource;

			while (*pParse && pDest < pMaxDest)
			{
				if (*pParse == '\"' || *pParse == '\\')
				{
					if (pDest + 1 >= pMaxDest)
						break;
					*(pDest++) = '\\';
					*(pDest++) = *pParse;
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = '\"';
			*(pDest++) = 0;
			return _pStrDest;
		}

		template <typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource)
		{
			t_CData1 *pDest = _pStrDest;

			*(pDest++) = '\"';
			const t_CData2 *pParse = _pStrSource;

			while (*pParse)
			{
				if (*pParse == '\"' || *pParse == '\\')
				{
					*(pDest++) = '\\';
					*(pDest++) = *pParse;
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = '\"';
			*(pDest++) = 0;
			return _pStrDest;
		}

		template <typename t_CData1, typename t_CData2, typename t_CEscapeChar>
			inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars, mint _MaxLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;
			CData1 *pDest = (CData1 *)_pStrDest;
			if (_MaxLen < 3)
			{
				*pDest = 0;
				return _pStrDest;
			}
			_MaxLen -= 2; // Null charater and one '"'

			CData1 *pMaxDest = (CData1 *)pDest + _MaxLen;
			*(pDest++) = (CEscapeChar)('"');
			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse && pDest < pMaxDest)
			{
				const CEscapeChar *pEscape = (const CEscapeChar *)_pEscapeChars;
				while (*pEscape)
				{
					if (*pParse == *pEscape)
						break;
					++pEscape;
				}
				if (*pEscape)
				{
					if (pDest + 1 >= pMaxDest)
						break;
					*(pDest++) = (CEscapeChar)('\\');
					*(pDest++) = *pParse;
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = (CEscapeChar)('"');
			*(pDest++) = 0;
			return _pStrDest;
		}

		template <typename t_CData1, typename t_CData2, typename t_CEscapeChar>
			inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;
			CData1 *pDest = (CData1 *)_pStrDest;

			*(pDest++) = (CEscapeChar)('"');
			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse)
			{
				const CEscapeChar *pEscape = (const CEscapeChar *)_pEscapeChars;
				while (*pEscape)
				{
					if (*pParse == *pEscape)
						break;
					++pEscape;
				}
				if (*pEscape)
				{
					*(pDest++) = (CEscapeChar)('\\');
					*(pDest++) = *pParse;
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = (CEscapeChar)('"');
			*(pDest++) = 0;
			return _pStrDest;
		}

		template <typename t_CData1, typename t_CData2, typename t_CEscapeChar, typename t_CReplaceChar>
			inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars, const t_CReplaceChar *_pReplaceChars, mint _MaxLen)
		{
			DMibFastCheck(fg_StrLen(_pEscapeChars) == fg_StrLen(_pReplaceChars));
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;
			typedef typename NTraits::TCUnsigned<t_CReplaceChar>::CType CReplaceChar;

			CData1 *pDest = (CData1 *)_pStrDest;
			if (_MaxLen < 3)
			{
				*pDest = 0;
				return _pStrDest;
			}
			_MaxLen -= 2; // Null charater and one '"'

			CData1 *pMaxDest = (CData1 *)pDest + _MaxLen;
			*(pDest++) = (CEscapeChar)('"');
			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse && pDest < pMaxDest)
			{
				mint iEscape = 0;
				while (((const CEscapeChar *)_pEscapeChars)[iEscape])
				{
					if (*pParse == ((const CEscapeChar *)_pEscapeChars)[iEscape])
						break;
					++iEscape;
				}
				if (_pEscapeChars[iEscape])
				{
					if (pDest + 1 >= pMaxDest)
						break;
					*(pDest++) = (CEscapeChar)('\\');
					*(pDest++) = ((const CReplaceChar *)_pReplaceChars)[iEscape];
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = (CEscapeChar)('"');
			*(pDest++) = 0;
			return _pStrDest;
		}

		template <typename t_CData1, typename t_CData2, typename t_CEscapeChar, typename t_CReplaceChar>
			inline_large t_CData1 *fg_StrEscapeStr(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars, const t_CReplaceChar *_pReplaceChars)
		{
			DMibFastCheck(fg_StrLen(_pEscapeChars) == fg_StrLen(_pReplaceChars));
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;
			typedef typename NTraits::TCUnsigned<t_CReplaceChar>::CType CReplaceChar;

			CData1 *pDest = (CData1 *)_pStrDest;

			*(pDest++) = (CEscapeChar)('"');
			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse)
			{
				mint iEscape = 0;
				while (((CEscapeChar const *)_pEscapeChars)[iEscape])
				{
					if (*pParse == ((CEscapeChar const *)_pEscapeChars)[iEscape])
						break;
					++iEscape;
				}
				if (_pEscapeChars[iEscape])
				{
					*(pDest++) = (CEscapeChar)('\\');
					*(pDest++) = ((CReplaceChar const *)_pReplaceChars)[iEscape];
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = (CEscapeChar)('"');
			*(pDest++) = 0;
			return _pStrDest;
		}

		template<typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, mint _MaxLen)
		{
			t_CData1 *pDest = _pStrDest;
			if (_MaxLen < 1)
			{
				*pDest = 0;
				return _pStrDest;
			}
			_MaxLen -= 1; // Null charater

			t_CData1 *pMaxDest = pDest + _MaxLen;
			const t_CData2 *pParse = _pStrSource;

			while (*pParse && pDest < pMaxDest)
			{
				if (*pParse == '\"' || *pParse == '\\')
				{
					if (pDest + 1 >= pMaxDest)
						break;
					*(pDest++) = '\\';
					*(pDest++) = *pParse;
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = 0;
			return _pStrDest;
		}

		template<typename t_CData1, typename t_CData2>
			inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource)
		{
			t_CData1 *pDest = _pStrDest;

			const t_CData2 *pParse = _pStrSource;

			while (*pParse)
			{
				if (*pParse == '\"' || *pParse == '\\')
				{
					*(pDest++) = '\\';
					*(pDest++) = *pParse;
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = 0;
			return _pStrDest;
		}

		template<typename t_CData1, typename t_CData2, typename t_CEscapeChar>
			inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars, mint _MaxLen)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;
			CData1 *pDest = (CData1 *)_pStrDest;
			if (_MaxLen < 1)
			{
				*pDest = 0;
				return _pStrDest;
			}
			_MaxLen -= 1; // Null charater

			CData1 *pMaxDest = (CData1 *)pDest + _MaxLen;
			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse && pDest < pMaxDest)
			{
				const CEscapeChar *pEscape = (const CEscapeChar *)_pEscapeChars;
				while (*pEscape)
				{
					if (*pParse == *pEscape)
						break;
					++pEscape;
				}
				if (*pEscape)
				{
					if (pDest + 1 >= pMaxDest)
						break;
					*(pDest++) = (CEscapeChar)('\\');
					*(pDest++) = *pParse;
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = 0;
			return _pStrDest;
		}

		template<typename t_CData1, typename t_CData2, typename t_CEscapeChar>
			inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars)
		{
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;
			CData1 *pDest = (CData1 *)_pStrDest;

			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse)
			{
				const CEscapeChar *pEscape = (const CEscapeChar *)_pEscapeChars;
				while (*pEscape)
				{
					if (*pParse == *pEscape)
						break;
					++pEscape;
				}
				if (*pEscape)
				{
					*(pDest++) = (CEscapeChar)('\\');
					*(pDest++) = *pParse;
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = 0;
			return _pStrDest;
		}

		template<typename t_CData1, typename t_CData2, typename t_CEscapeChar, typename t_CReplaceChar>
			inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars, const t_CReplaceChar *_pReplaceChars, mint _MaxLen)
		{
			DMibFastCheck(fg_StrLen(_pEscapeChars) == fg_StrLen(_pReplaceChars));
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;
			typedef typename NTraits::TCUnsigned<t_CReplaceChar>::CType CReplaceChar;

			CData1 *pDest = (CData1 *)_pStrDest;
			if (_MaxLen < 1)
			{
				*pDest = 0;
				return _pStrDest;
			}
			_MaxLen -= 1; // Null charater

			CData1 *pMaxDest = (CData1 *)pDest + _MaxLen;
			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse && pDest < pMaxDest)
			{
				mint iEscape = 0;
				while (((const CEscapeChar *)_pEscapeChars)[iEscape])
				{
					if (*pParse == ((const CEscapeChar *)_pEscapeChars)[iEscape])
						break;
					++iEscape;
				}
				if (_pEscapeChars[iEscape])
				{
					if (pDest + 1 >= pMaxDest)
						break;
					*(pDest++) = (CEscapeChar)('\\');
					*(pDest++) = ((const CReplaceChar *)_pReplaceChars)[iEscape];
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = 0;
			return _pStrDest;
		}

		template<typename t_CData1, typename t_CData2, typename t_CEscapeChar, typename t_CReplaceChar>
			inline_large t_CData1 *fg_StrEscapeStrNoQuotes(t_CData1 *_pStrDest, const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars, const t_CReplaceChar *_pReplaceChars)
		{
			DMibFastCheck(fg_StrLen(_pEscapeChars) == fg_StrLen(_pReplaceChars));
			typedef typename NTraits::TCUnsigned<t_CData1>::CType CData1;
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;
			typedef typename NTraits::TCUnsigned<t_CReplaceChar>::CType CReplaceChar;

			CData1 *pDest = (CData1 *)_pStrDest;

			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse)
			{
				mint iEscape = 0;
				while (((CEscapeChar const *)_pEscapeChars)[iEscape])
				{
					if (*pParse == ((CEscapeChar const *)_pEscapeChars)[iEscape])
						break;
					++iEscape;
				}
				if (_pEscapeChars[iEscape])
				{
					*(pDest++) = (CEscapeChar)('\\');
					*(pDest++) = ((CReplaceChar const *)_pReplaceChars)[iEscape];
					++pParse;
					continue;
				}
				*(pDest++) = *(pParse++);
			}
			*(pDest++) = 0;
			return _pStrDest;
		}


		// Size in chars required for escaped string, EXCLUDING null.
		template<typename t_CData2>
		inline_large mint fg_StrEscapedLength(const t_CData2 *_pStrSource)
		{
			mint nEscapedChars = 0;

			++nEscapedChars;	// '"'
			const t_CData2 *pParse = _pStrSource;

			while (*pParse)
			{
				if (*pParse == '\"' || *pParse == '\\')
				{
					++nEscapedChars;	// '\\'
					++nEscapedChars;	// '<char>'
					++pParse;
					continue;
				}
				++nEscapedChars;	// Char copy
			}
			++nEscapedChars;	// '"'
			//++nEscapedChars;	// Null
			return nEscapedChars;
		}

		// Size in chars required for escaped string, EXCLUDING null.
		template<typename t_CData2, typename t_CEscapeChar>
		inline_large mint fg_StrEscapedLength(const t_CData2 *_pStrSource, const t_CEscapeChar *_pEscapeChars)
		{
			typedef typename NTraits::TCUnsigned<t_CData2>::CType CData2;
			typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CEscapeChar;

			mint nEscapedChars = 0;

			++nEscapedChars;	// '"'
			const CData2 *pParse = (const CData2 *)_pStrSource;

			while (*pParse)
			{
				mint iEscape = 0;
				while (((CEscapeChar const *)_pEscapeChars)[iEscape])
				{
					if (*pParse == ((CEscapeChar const *)_pEscapeChars)[iEscape])
						break;
					++iEscape;
				}
				if (_pEscapeChars[iEscape])
				{
					++nEscapedChars;	// '\\'
					++nEscapedChars;	// '<char>'

					++pParse;
					continue;
				}
				++nEscapedChars;	// Char Copy
				++pParse;
			}
			++nEscapedChars;	// '"'
			// Don't include null.
			// ++nEscapedBytes;	// 0
			return nEscapedChars;
		}

		template <typename t_CStrType0, typename t_CStrType1, typename t_CStrType2>
		static void fg_StrAddWithSeparator(t_CStrType0 &_Str, const t_CStrType1 &_ToAdd, const t_CStrType2 &_Separator)
		{
			if (!_Str.f_IsEmpty())
				_Str += _Separator;
			_Str += _ToAdd;
		}
		
        /***************************************************************************************************\
        |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
        | Character functions																				|
        |___________________________________________________________________________________________________|
        \***************************************************************************************************/


		template <typename t_CData>
			inline_medium t_CData fg_CharUpperCase(t_CData _Character)
		{
			typedef typename NTraits::TCUnsigned<t_CData>::CType CData;
			CData Char = (CData) _Character;
			CData UpperComapre = 0xffu;
			if (Char >= 'a' && Char <= 'z')
				Char -= 'a' - 'A';
			if (Char >= 0xe0 && Char <= UpperComapre)
				Char -= 0xe0 - 0xc0;

			return (t_CData)Char;
		}

		template <typename t_CData>
			inline_medium t_CData fg_CharLowerCase(t_CData _Character)
		{
			typedef typename NTraits::TCUnsigned<t_CData>::CType CData;
			CData Char = (CData) _Character;
			
			if (Char >= 'A' && Char <= 'Z')
				Char += 'a' - 'A';

			if (Char >= 0xc0 && Char <= 0xdf)
				Char += 0xe0 - 0xc0;
			return (t_CData)Char;
		}

		template <typename t_CData>
			inline_medium bint fg_CharIsWhiteSpace(const t_CData _Character)
		{
			switch (_Character)
			{
			case 32 : return true;
			case 8 : return true;
			case 9 : return true;
			case 10 : return true;
			case 13 : return true;
			}
			return false;			
		}

		template<typename t_CData>
			inline_medium bint fg_CharIsWhiteSpaceNoLines(const t_CData _Character)
		{
			switch (_Character)
			{
			case 32 : return true;
			case 8 : return true;
			case 9 : return true;
			}
			return false;			
		}

		template<typename t_CData>
			inline_large bint fg_CharIsAlphabetical(const t_CData _Character)
		{
			typedef typename NTraits::TCUnsigned<t_CData>::CType CData;
			CData Char = (CData) _Character;

			if (Char >= 'A' && Char <= 'Z')
				return true;
			if (Char >= 'a' && Char <= 'z')
				return true;

			if (Char >= 0x7fu)
				return true;

			return false;

		}

		template <typename t_CData>
			inline_large bint fg_CharIsAnsiAlphabetical(const t_CData _Character)
		{
			if (_Character >= 'A' && _Character <= 'Z')
				return true;
			if (_Character >= 'a' && _Character <= 'z')
				return true;

			return false;

		}

		template <typename t_CData>
			inline_medium bint fg_CharIsNumber(const t_CData _Character)
		{
			if (_Character >= '0' && _Character <= '9')
				return true;

			return false;
		}

		template <typename t_CData>
			inline_medium bint fg_CharIsOctalNumber(const t_CData _Character)
		{
			if (_Character >= '0' && _Character <= '7')
				return true;

			return false;
		}

		template <typename t_CData>
			inline_medium bint fg_CharIsHexNumber(const t_CData _Character)
		{
			if ((_Character >= '0' && _Character <= '9') || 
				(_Character >= 'a' && _Character <= 'f') ||
				(_Character >= 'A' && _Character <= 'F')
				)
				return true;

			return false;
		}
		
        /***************************************************************************************************\
        |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
        | Parse Functions																					|
        |___________________________________________________________________________________________________|
        \***************************************************************************************************/
		
		template <typename t_CChar>
		static void fg_ParseWhiteSpace(const t_CChar * &_pParse)
		{
			while (*_pParse && NStr::fg_CharIsWhiteSpace(*_pParse))
				++_pParse;
		}

		template <typename t_CChar>
		static void fg_ParseWhiteSpaceNoLines(const t_CChar * &_pParse)
		{
			while (*_pParse && NStr::fg_CharIsWhiteSpaceNoLines(*_pParse))
				++_pParse;
		}

		template <typename t_CChar>
		static void fg_ParseToEndOfLine(const t_CChar *&_pParse)
		{
			const t_CChar *pParse = _pParse;
			while (*pParse)
			{
				if (*pParse == '\n' || *pParse == '\r')
					break;
				++pParse;
			}
			_pParse = pParse;
		}

		template <typename t_CChar>
		bint fg_ParseEndOfLine(const t_CChar *&_pParse)
		{
			bint bRet = false;
			const t_CChar *pParse = _pParse;
			if (*pParse == '\r')
			{
				bRet = true;
				++pParse;
				if (*pParse == '\n')
					++pParse;
			}
			else if (*pParse == '\n')
			{
				bRet = true;
				++pParse;
			}
			_pParse = pParse;
			return bRet;
		}

		template <typename t_CChar>
		static void fg_ParseWhiteSpace(t_CChar * &_pParse)
		{
			while (*_pParse && NStr::fg_CharIsWhiteSpace(*_pParse))
				++_pParse;
		}

		template <typename t_CChar>
		static void fg_ParseToEndOfLine(t_CChar *&_pParse)
		{
			t_CChar *pParse = _pParse;
			while (*pParse)
			{
				if (*pParse == '\n' || *pParse == '\r')
					break;
				++pParse;
			}
			_pParse = pParse;
		}

		template <typename t_CChar>
		bint fg_ParseEndOfLine(t_CChar *&_pParse)
		{
			bint bRet = false;
			t_CChar *pParse = _pParse;
			if (*pParse == '\r')
			{
				bRet = true;
				++pParse;
				if (*pParse == '\n')
					++pParse;
			}
			else if (*pParse == '\n')
			{
				bRet = true;
				++pParse;
			}
			_pParse = pParse;
			return bRet;
		}

		template <typename t_CChar, typename t_CSeparators>
		void fg_ParseNonWhiteSpaceAndSeparators(const t_CChar * &_pParse, const t_CSeparators *_pSeparators)
		{
			const t_CChar *pParse = _pParse;
			while (*pParse && !NStr::fg_CharIsWhiteSpace(*pParse))
			{
				const t_CSeparators *pSeparators = _pSeparators;
				while (*pSeparators && *pParse != *pSeparators)
					++pSeparators;
				if (*pSeparators)
					break;
				++pParse;
			}

			_pParse = pParse;
		}

		template <typename t_CChar>
		void fg_ParseAlpha(const t_CChar * &_pParse)
		{
			const typename NTraits::TCUnsigned<t_CChar>::CType *pParse = (const typename NTraits::TCUnsigned<t_CChar>::CType *)_pParse;
			while (*pParse)
			{
				if (*pParse >= 'a' && *pParse <= 'z')
					;
				else if (*pParse >= 'A' && *pParse <= 'Z')
					;
				else if (*pParse >= 0xc0)
					;
				else
					break;
				++pParse;
			}

			_pParse = (const t_CChar * )pParse;
		}

		template <typename t_CChar>
		void fg_ParseAlphaNumeric(const t_CChar * &_pParse)
		{
			const typename NTraits::TCUnsigned<t_CChar>::CType *pParse = (const typename NTraits::TCUnsigned<t_CChar>::CType *)_pParse;
			while (*pParse)
			{
				if (!fg_CharIsAlphabetical(*pParse) && !fg_CharIsNumber(*pParse))
					break;
				++pParse;
			}

			_pParse = (const t_CChar * )pParse;
		}

		template <typename t_CChar, typename t_CChar1>
		void fg_ParseAlphaNumericAndChars(const t_CChar * &_pParse, const t_CChar1 * _pChars)
		{
			const typename NTraits::TCUnsigned<t_CChar>::CType *pParse = (const typename NTraits::TCUnsigned<t_CChar>::CType *)_pParse;
			while (*pParse)
			{
				const typename NTraits::TCUnsigned<t_CChar1>::CType *pCharsParse = (const typename NTraits::TCUnsigned<t_CChar1>::CType *)_pChars;
				while (*pCharsParse)
				{
					if (*pParse == *pCharsParse)
						break;
					++pCharsParse;
				}

				if (!(*pCharsParse) && !fg_CharIsAlphabetical(*pParse) && !fg_CharIsNumber(*pParse))
					break;
				++pParse;
			}

			_pParse = (const t_CChar * )pParse;
		}

		template <typename t_CChar, typename t_CSeparators>
		void fg_ParseWhiteSpaceAndSeparators(const t_CChar * &_pParse, const t_CSeparators *_pSeparators)
		{
			const t_CChar *pParse = _pParse;
			while (*pParse)
			{
				const t_CSeparators *pSeparators = _pSeparators;
				while (*pSeparators && *pParse != *pSeparators)
					++pSeparators;
				if (*pSeparators)
				{
					++pParse;
					continue;
				}
				if (NStr::fg_CharIsWhiteSpace(*pParse))
				{
					++pParse;
					continue;
				}
				break;
			}

			_pParse = pParse;
		}

		template <typename t_CStrType>
		t_CStrType fg_GetStrSep(t_CStrType &_Str, const ch8 *_pSep)
		{
			t_CStrType Ret;
			aint iFind = _Str.f_Find(_pSep);
			if (iFind >= 0)
			{
				Ret = _Str.f_Left(iFind);
				_Str = _Str.f_Extract(iFind + fg_StrLen(_pSep));
			}
			else
			{
				Ret = _Str;
				_Str = "";
			}
			Ret = Ret.f_TrimLeft();
			Ret = Ret.f_TrimRight();
			return Ret;
		}

		template <typename t_CStrType>
		t_CStrType fg_GetStrSepNoTrim(t_CStrType &_Str, const ch8 *_pSep)
		{
			t_CStrType Ret;
			aint iFind = _Str.f_Find(_pSep);
			if (iFind >= 0)
			{
				Ret = _Str.f_Left(iFind);
				_Str = _Str.f_Extract(iFind + fg_StrLen(_pSep));
			}
			else
			{
				Ret = _Str;
				_Str = "";
			}
			return Ret;
		}

		template <typename t_CStrType>
		t_CStrType fg_GetStrLineSep(t_CStrType &_Str)
		{
			t_CStrType Ret;
			aint iFind = _Str.f_FindChars("\r\n");
			if (iFind >= 0)
			{
				Ret = _Str.f_Left(iFind);
				if (_Str.f_GetAt(iFind) == '\r')
					++iFind;
				if (_Str.f_GetAt(iFind) == '\n')
					++iFind;
				_Str = _Str.f_Extract(iFind);
			}
			else
			{
				Ret = _Str;
				_Str = "";
			}
			return Ret;
		}
		
		template <typename t_CStrType, typename t_CSeparators>
		t_CStrType fg_GetStrSeparators(t_CStrType &_Str, const t_CSeparators *_pSeparators)
		{
			t_CStrType Ret;
			aint iFind = _Str.f_FindChars(_pSeparators);
			if (iFind >= 0)
			{
				Ret = _Str.f_Left(iFind);
				_Str = _Str.f_Extract(iFind + 1);
			}
			else
			{
				Ret = _Str;
				_Str = "";
			}
			Ret = Ret.f_TrimLeft();
			Ret = Ret.f_TrimRight();
			return Ret;
		}

		template <typename t_CStrType0, typename t_CStrType1>
		void fg_AddStrSepEscaped(t_CStrType0 &_Str, const t_CStrType1 &_ToAdd, ch8 _Sep, ch8 const *_pNeedEscapeChars = "\"\\")
		{
			if (!_Str.f_IsEmpty())
				_Str.f_AddChar(_Sep);
			if (fg_StrIsEmpty(_ToAdd) || fg_StrFindChar(_ToAdd, _Sep) >= 0 || fg_StrFindChars(_ToAdd, _pNeedEscapeChars) >= 0)
				_Str += t_CStrType0(_ToAdd).f_EscapeStr();
			else
				_Str += _ToAdd;
		}


		template <typename t_CStrType0, typename t_CStrType1, typename t_CStrType2>
		void fg_AddStrSep(t_CStrType0 &_Str, const t_CStrType1 &_ToAdd, const t_CStrType2 &_Separator)
		{
			if (!_Str.f_IsEmpty())
				_Str += _Separator;
			_Str += _ToAdd;
		}

		template <ch8 tf_EscapeChar, typename tf_CChar>
		void fg_ParseEscape(const tf_CChar *&_pParse, tf_CChar _Abort)
		{
			auto pParse = _pParse;
			int Mode = 0;
			if (*pParse == '\"')
			{
				++pParse;
				Mode = 1;
			}
			while (*pParse)
			{
				if (Mode == 0)
				{
					if (*pParse == _Abort)
						break;
					else if (*pParse == tf_EscapeChar)
					{
						Mode = 1;
						++pParse;
						continue;
					}
				}
				else if (Mode == 1)
				{
					if (*pParse == tf_EscapeChar)
					{
						Mode = 0;
						++pParse;
						if (_Abort == tf_EscapeChar)
							break;
						continue;
					}
					if (*pParse == '\\')
					{
						++pParse;
						if (*pParse)
							++pParse;
						continue;
					}
				}
				++pParse;
			}

			_pParse = pParse;
		}


		template <ch8 tf_EscapeChar, typename tf_CStrType>
		tf_CStrType fg_RemoveEscape(const tf_CStrType &_Str)
		{
			tf_CStrType Ret;
			const typename tf_CStrType::CChar *pParse = _Str;
			int Mode = 0;
			while (*pParse)
			{
				if (Mode == 0)
				{
					if (*pParse == tf_EscapeChar)
					{
						Mode = 1;
						++pParse;
						continue;
					}
				}
				else if (Mode == 1)
				{
					if (*pParse == tf_EscapeChar)
					{
						Mode = 0;
						++pParse;
						continue;
					}
					if (*pParse == '\\')
					{
						++pParse;
						if (*pParse)
						{
							Ret.f_AddChar(*pParse);
							++pParse;
						}
						continue;
					}
				}
				Ret.f_AddChar(*pParse);
				++pParse;
			}

			return Ret;
		}

		template <typename tf_CStrType>
		tf_CStrType fg_RemoveEscape(const tf_CStrType &_Str)
		{
			return fg_RemoveEscape<'\"'>(_Str);
		}

		template <ch8 tf_EscapeChar, typename tf_CStrType>
		tf_CStrType fg_GetStrSepEscaped(tf_CStrType &_Str, const ch8 *_pSep)
		{
			const typename tf_CStrType::CChar *pParse = _Str;
			int Mode = 0;

			while (*pParse)
			{
				if (Mode == 0)
				{
					if (*pParse == tf_EscapeChar)
					{
						Mode = 1;
						++pParse;
						continue;
					}

					if (fg_StrStartsWith(pParse, _pSep))
					{
						break;
					}

				}
				else if (Mode == 1)
				{
					if (*pParse == tf_EscapeChar)
					{
						Mode = 0;
						++pParse;
						continue;
					}
					if (*pParse == '\\')
					{
						++pParse;
						if (*pParse)
						{
							++pParse;
						}
						continue;
					}
				}
				++pParse;
			}

			const typename tf_CStrType::CChar *pStart = _Str;
			tf_CStrType Ret = tf_CStrType(pStart, pParse - pStart); 
			
			Ret = Ret.f_TrimLeft();
			Ret = Ret.f_TrimRight();
			Ret = fg_RemoveEscape<tf_EscapeChar>(Ret);

			pParse += fg_StrLen(_pSep);

			_Str = _Str.f_Extract(pParse - pStart);

			return Ret;
/*

			tf_CStrType Ret;
			const typename tf_CStrType::CChar *pParse = _Str;
			int32 Pos = 0;
			if (pParse[Pos] == tf_EscapeChar)
			{
				Pos++;
				while (pParse[Pos])
				{		
					if (pParse[Pos] == '\\')
					{
						++Pos;
						if (pParse[Pos])
							++Pos;
						continue;
					}
					if (pParse[Pos] == tf_EscapeChar)
						break;
					Pos++;
				}
			}

			aint iFind = fg_StrFind(pParse + Pos, _pSep);
			if (iFind >= 0)
			{
				Ret = _Str.f_Left(iFind + Pos);
				_Str = _Str.f_Extract(iFind + 1 + Pos);
			}
			else
			{
				Ret = _Str;
				_Str = "";
			}
			Ret = Ret.f_TrimLeft();
			Ret = Ret.f_TrimRight();
			if (Ret[0] == tf_EscapeChar)
				Ret = fg_RemoveEscape<tf_EscapeChar>(Ret);
			return Ret;
			*/
		}


		template <typename tf_CStrType>
		tf_CStrType fg_GetStrSepEscaped(tf_CStrType &_Str, const ch8 *_pSep)
		{
			return fg_GetStrSepEscaped<'\"'>(_Str, _pSep);
		}

		template<typename t_CStr>
		bool fg_StrEscapeBashQuotesNeeded(t_CStr const& _Str)
		{
			auto const *pParseSigned = _Str.f_GetStr();
			typedef typename NTraits::TCUnsigned<typename NTraits::TCRemoveReferenceAndQualifiers<decltype(*pParseSigned)>::CType>::CType CUnsignedChar;
			CUnsignedChar const *pParse = (CUnsignedChar const *)pParseSigned;

			while (*pParse)
			{
				if (*pParse <= 32)
					return true;
				
				switch (*pParse)
				{
				case '*': // Prevent globbing
				case '?': // Prevent globbing
				case '~': // Prevent globbing
				case '#':
				case '$':
				case '`':
				case '\\':
				case ';':
				case '\"':
				case '\'':
				case ',':
				case ':': // Possibly if string starts with this
				case '!': // Sometimes only
				case '(': // Command group
				case ')': // Command group
				case '{': // Brace expansion
				case '}': // Brace expansion
				case '[': // Test
				case ']': // Test
				case '&': // Redirection
				case '<': // Redirection
				case '>': // Redirection
				case '|': // Pipe
				case '-': // Option
				case '=':
				case '+':
				case '%':
				case '^':
					return true;
					break;
				}

				++pParse;
			}

			return false;
		}
		
		template<typename t_CStr>
		t_CStr fg_StrEscapeBashSingleQuotes(t_CStr const& _Str)
		{
			t_CStr Return;

			Return.f_AddStr("'");

			auto const* pParse = _Str.f_GetStr();

			while (*pParse)
			{
				if (*pParse == '\'')
					Return.f_AddStr("'\\''");
				else
					Return.f_AddStr(pParse, 1);

				++pParse;
			}

			Return.f_AddStr("'");

			return Return;
		}

		template<typename t_CStr>
		t_CStr fg_StrEscapeBashDoubleQuotes(t_CStr const& _Str)
		{
			t_CStr Return;

			Return.f_AddStr("\"");

			auto const* pParse = _Str.f_GetStr();

			while (*pParse)
			{
				if (*pParse == '\"')
					Return.f_AddStr("\\\"");
				else if (*pParse == '$')
					Return.f_AddStr("\\$");
				else if (*pParse == '`')
					Return.f_AddStr("\\`");
				else if (*pParse == '\\')
					Return.f_AddStr("\\\\");
				else
					Return.f_AddStr(pParse, 1);

				++pParse;
			}

			Return.f_AddStr("\"");

			return Return;
		}

		template<typename tf_CStr>
		tf_CStr fg_StrSanitizeOneLine(tf_CStr const &_Str)
		{
			typedef TCStr <typename TCStrTraits_ReplaceParams<ch32, EStrType_Unicode, tf_CStr::CTraits::CStrTraits::mc_Type, typename tf_CStr::CImp, typename tf_CStr::CTraits::CStrTraits::CParams>::CType> CUnicodeStr;

			if (_Str.f_IsEmpty())
				return CUnicodeStr();

			static_assert(tf_CStr::mc_Type == NStr::EStrType_UTF, "");

			auto iUTF = _Str.f_GetUnicodeIterator();
			CUnicodeStr Return;
			while (*iUTF)
			{
				switch (*iUTF)
				{
				case 0x000A: //	Line feed
				case 0x000B: //	Vertical Tab
				case 0x000C: //	Form feed
				case 0x000D: //	Carriage return
				case 0x0085: //	Next line
				case 0x2028: //	line separator
				case 0x2029: //	paragraph separator

				/* Regular whitespaces will be added as usual 
				case 0x0009: // Horizontal Tab
				case 0x0020: //	Space
				case 0x00A0: //	no-break space
				case 0x1680: //	ogham space mark
				case 0x180E: //	mongolian vowel separator
				case 0x2000: //	en quad
				case 0x2001: //	em quad
				case 0x2002: //	en space
				case 0x2003: //	em space
				case 0x2004: //	three-per-em space
				case 0x2005: //	four-per-em space
				case 0x2006: //	six-per-em space
				case 0x2007: //	figure space
				case 0x2008: //	punctuation space
				case 0x2009: //	thin space
				case 0x200A: //	hair space
				case 0x202F: //	narrow no-break space
				case 0x205F: //	medium mathematical space
				case 0x3000: //	ideographic space
				*/
					Return.f_AddChar(0x0020);
					break;
				default:
					Return.f_AddChar(*iUTF);
					break;
				}

				++iUTF;
			}

			return Return;
		}
	}
}

