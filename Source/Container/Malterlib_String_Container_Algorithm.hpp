// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	// Static functions
	template <typename tf_CTCStrTraits>
	inline_small umint fg_StrLen(TCStr<tf_CTCStrTraits> const &_Str)
	{
		return _Str.f_GetLen();
	}

	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrHashDJB2(TCStr<tf_CTCStrTraits> const &_Str)
	{
		return _Str.f_HashDJB2();
	}

	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrHashSDBM(TCStr<tf_CTCStrTraits> const &_Str)
	{
		return _Str.f_HashSDBM();
	}

	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrHash(TCStr<tf_CTCStrTraits> const &_Str)
	{
		return _Str.f_Hash();
	}


	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrIsAnsi(TCStr<tf_CTCStrTraits> const &_Str)
	{
		return fg_StrIsAnsi(_Str.f_GetStr());
	}

	template <typename tf_CTCStrTraits>
	inline_small uint32 fg_StrIsAnsi(TCStr<tf_CTCStrTraits> const &_Str, umint _MaxLen)
	{
		return fg_StrIsAnsi(_Str.f_GetStr(), _MaxLen);
	}


	template <typename tf_CTCStrTraits>
	bool fg_StrIsEmpty(TCStr<tf_CTCStrTraits> const &_Str)
	{
		return _Str.f_IsEmpty();
	}

	template <typename tf_CTCStrTraits>
	bool fg_StrIsEmpty(TCFormat<tf_CTCStrTraits> const &_Str)
	{
		return _Str.f_IsEmpty();
	}

	template <typename tf_CTCStrTraits>
	inline_small NTraits::TCUnsigned<typename TCStr<tf_CTCStrTraits>::CMaxChar> fg_StrLargestChar(TCStr<tf_CTCStrTraits> const &_Str)
	{
		return fg_StrLargestChar(_Str.f_GetStr());
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrCopy(TCStr<tf_CTCStrTraits> &_To, tf_CData const *_pFrom)
	{
		_To.f_Clear();
		_To.f_AddStr(_pFrom);
		return _To;
	}

	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small tf_CData *fg_StrCopy(tf_CData *_pTo, TCStr<tf_CTCStrTraits> const &_From)
	{
		fg_StrCopy(_pTo, _From.f_GetStr());
		return _pTo;
	}

	template <typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrCopy(TCStr<tf_CTCStrTraits1> &_To, TCStr<tf_CTCStrTraits2> const &_From)
	{
		_To = _From;
		return _To;
	}

	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small tf_CData *fg_StrCopy(tf_CData *_pTo, TCStr<tf_CTCStrTraits1> const &_From, umint _MaxLen)
	{
		fg_StrCopy(_pTo, _From.f_GetStr(), _MaxLen);
		return _pTo;
	}

	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrCopy(TCStr<tf_CTCStrTraits1> &_To, tf_CData const *_pFrom, umint _MaxLen)
	{
		_To.f_Clear();
		_To.f_AddStr(_pFrom, fg_Min(_MaxLen, fg_StrLen(_pFrom, _MaxLen)));
		return _To;
	}

	template <typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrCopy(TCStr<tf_CTCStrTraits1> &_To, TCStr<tf_CTCStrTraits2> const &_From, umint _MaxLen)
	{
		_To.f_Clear();
		_To.f_AddStr(_From.f_GetStr(), fg_Min(_MaxLen, fg_StrLen(_From)));
		return _To;
	}

	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrMove(TCStr<tf_CTCStrTraits1> &_To, tf_CData const *_pFrom)
	{
		TCStr<tf_CTCStrTraits1> Temp;
		fg_StrCopy(Temp, _pFrom);
		_To = Temp;
		return Temp;
	}

	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small tf_CData *fg_StrMove(tf_CData *_pTo, TCStr<tf_CTCStrTraits1> const &_From)
	{
		return fg_StrCopy(_pTo, _From);
	}

	template <typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrMove(TCStr<tf_CTCStrTraits1> &_To, TCStr<tf_CTCStrTraits2> const &_From)
	{
		return fg_StrCopy(_To, _From);
	}

	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small tf_CData *fg_StrMove(tf_CData *_pTo, TCStr<tf_CTCStrTraits1> const &_From, umint _MaxLen)
	{
		return fg_StrCopy(_pTo, _From, _MaxLen);
	}

	template <typename tf_CTCStrTraits1, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrMove(TCStr<tf_CTCStrTraits1> &_To, tf_CData const *_pFrom, umint _MaxLen)
	{
		TCStr<tf_CTCStrTraits1> Temp;
		fg_StrCopy(Temp, _pFrom, _MaxLen);
		_To = Temp;
		return _To;
	}

	template <typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits1> &fg_StrMove(TCStr<tf_CTCStrTraits1> &_To, TCStr<tf_CTCStrTraits2> const &_From, umint _MaxLen)
	{
		return fg_StrCopy(_To, _From, _MaxLen);
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReverse(TCStr<tf_CTCStrTraits> &_Str)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str;
		fg_StrReverse(pStr1);
		_Str.f_SetModified();
		return _Str;
	}


	template <typename tf_CTCStrTraits, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrSetAt(TCStr<tf_CTCStrTraits> &_Str, aint _Index, tf_CData _Character)
	{
		_Str.f_MakeUnique();
		int MaxLen = _Str.f_CreateWritableBuffer(_Index + 1, false);
		if (_Index >= MaxLen)
			return _Str;

		((typename TCStr<tf_CTCStrTraits>::CUnsignedChar *)_Str.f_GetStrWritable())[_Index] = (typename TCStr<tf_CTCStrTraits>::CUnsignedChar)(NTraits::TCUnsigned<tf_CData>)(_Character);
		if (_Character == 0)
			_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CChar>
	constexpr typename TCFStr<tf_CChar, 2, sizeof(tf_CChar) >= 4 ? EStrType_Unicode : EStrType_UTF>::CType fg_CharToString(tf_CChar const &_Char)
	{
		tf_CChar const Characters[2] = {_Char, 0};
		return typename TCFStr<tf_CChar, 2, sizeof(tf_CChar) >= 4 ? EStrType_Unicode : EStrType_UTF>::CType(NMib::NStr::CStrInitGeneral(), Characters, 2);
	}

	template <typename tf_CTCStrTraits>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrUntabify(TCStr<tf_CTCStrTraits> &_Str, umint _TabSize)
	{
		using CChar = typename TCStr<tf_CTCStrTraits>::CChar;

		TCStr<tf_CTCStrTraits> Temp(_Str);
		CChar const *pStr1 = Temp.f_GetStr();
		umint NeededLen = 0;
		umint Column = 0;

		while (*pStr1)
		{
			CChar Char = *pStr1;

			if (Char == '\t')
			{
				umint OldColumn = Column;
				Column = ((Column + _TabSize) / _TabSize) * _TabSize;
				NeededLen += Column - OldColumn;
			}
			else if (Char == '\r')
			{
				++NeededLen;
				Column = 0;
				++pStr1;
				if (*pStr1 == '\n')
				{
					++NeededLen;
					++pStr1;
				}
				continue;
			}
			else if (*pStr1 == '\n')
			{
				++NeededLen;
				Column = 0;
			}
			else
			{
				++NeededLen;
				++Column;
			}

			++pStr1;
		}

		uint32 MaxLen = NeededLen+1;
		CChar *pWrite = _Str.f_GetStr(MaxLen);
#			if DMibEnableSafeCheck > 0
			CChar *pWriteStart = pWrite;
#			endif

		pStr1 = Temp.f_GetStr();
		Column = 0;
		while (*pStr1)
		{
			CChar Char = *pStr1;
			if (Char == '\t')
			{
				umint OldColumn = Column;
				Column = ((Column + _TabSize) / _TabSize) * _TabSize;
				umint nFill = Column - OldColumn;
				for (umint i = 0; i < nFill; ++i)
					*(pWrite++) = ' ';
			}
			else if (Char == '\r')
			{
				*(pWrite++) = Char;
				Column = 0;
				++pStr1;
				if (*pStr1 == '\n')
				{
					*(pWrite++) = *pStr1;

					++pStr1;
				}
				continue;
			}
			else if (Char == '\n')
			{
				*(pWrite++) = Char;
				Column = 0;
			}
			else
			{
				++Column;
				*(pWrite++) = Char;
			}

			++pStr1;
		}
		*(pWrite++) = 0;

		DMibSafeCheck((umint(pWrite - pWriteStart) <= MaxLen), "Memory overwritten");


		_Str.f_SetModified();
		return _Str;
	}
}

#include "Malterlib_String_Container_Algorithm_Case.hpp"
#include "Malterlib_String_Container_Algorithm_Compare.hpp"
#include "Malterlib_String_Container_Algorithm_Escape.hpp"
#include "Malterlib_String_Container_Algorithm_Find.hpp"
#include "Malterlib_String_Container_Algorithm_Manipulate.hpp"
#include "Malterlib_String_Container_Algorithm_Replace.hpp"
#include "Malterlib_String_Container_Algorithm_Trim.hpp"
