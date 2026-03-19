// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplace
		(
			TCStr<tf_CTCStrTraits> &_Str
			, tf_CData const *_pStrFind
			, umint _LenFind
			, tf_CData2 const *_pStrReplace
			, umint _LenReplace
		)
	{
		using CChar = typename TCStr<tf_CTCStrTraits>::CChar;

		CChar const *pStr1 = _Str.f_GetStr();
		CChar const *pStrFind = fg_StrAdd(pStr1, fg_StrFind(pStr1, _pStrFind));

		if (!pStrFind)
			return _Str;

		umint nReplaces = 0;

		while (pStrFind)
		{
			++nReplaces;
			pStr1 = pStrFind + _LenFind;
			pStrFind = fg_StrAdd(pStr1, fg_StrFind(pStr1, _pStrFind));
		}

		umint Len = fg_StrLen(_Str);

		umint NeededSize = Len;
		if (_LenReplace > _LenFind)
			NeededSize += nReplaces * (_LenReplace - _LenFind);
		else
			NeededSize -= nReplaces * (_LenFind - _LenReplace);

		fg_StrReplaceWithCount(_Str.f_GetStr(NeededSize), Len, _pStrFind, _LenFind, _pStrReplace, _LenReplace, NeededSize + 1, nReplaces);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace)
	{
		return fg_StrReplace(_Str, _pStrFind, fg_StrLen(_pStrFind), _pStrReplace, fg_StrLen(_pStrReplace));
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits2> const &_StrFind, tf_CData2 const *_pStrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplace(_Str, _StrFind.f_GetStr(), _StrFind.f_GetLen(), _pStrReplace, fg_StrLen(_pStrReplace));
	}


	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, TCStr<tf_CTCStrTraits2> const &_StrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplace(_Str, _pStrFind, fg_StrLen(_pStrFind), _StrReplace.f_GetStr(), _StrReplace.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace
		(
			TCStr<tf_CTCStrTraits> &_Str
			, TCStr<tf_CTCStrTraits1> const &_StrFind
			, TCStr<tf_CTCStrTraits2> const &_StrReplace
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits1>::mc_Value && TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplace(_Str, _StrFind.f_GetStr(), _StrFind.f_GetLen(), _StrReplace.f_GetStr(), _StrReplace.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplace
		(
			TCStr<tf_CTCStrTraits> &_Str
			, tf_CData const *_pStrFind
			, umint _LenFind
			, tf_CData2 const *_pStrReplace
			, umint _LenReplace
			, umint _MaxLen
		)
	{
		using CChar = typename TCStr<tf_CTCStrTraits>::CChar;

		CChar const *pStr1 = _Str.f_GetStr();
		CChar const *pStrFind = fg_StrAdd(pStr1, fg_StrFind(pStr1, _pStrFind));

		if (!pStrFind)
			return _Str;

		umint nReplaces = 0;

		while (pStrFind)
		{
			++nReplaces;
			pStr1 = pStrFind + _LenFind;
			pStrFind = fg_StrAdd(pStr1, fg_StrFind(pStr1, _pStrFind));
		}

		umint Len = fg_StrLen(_Str);

		umint NeededSize;
		if (_LenReplace >= _LenFind)
			NeededSize = fg_Min(Len + nReplaces * (_LenReplace - _LenFind), _MaxLen);
		else
			NeededSize = fg_Min(Len - nReplaces * (_LenFind - _LenReplace), _MaxLen);

		fg_StrReplaceWithCount(_Str.f_GetStr(NeededSize), Len, _pStrFind, _LenFind, _pStrReplace, _LenReplace, NeededSize + 1, nReplaces);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplace(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace, umint _MaxLen)
	{
		return fg_StrReplace(_Str, _pStrFind, fg_StrLen(_pStrFind), _pStrReplace, fg_StrLen(_pStrReplace), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace
		(
			TCStr<tf_CTCStrTraits> &_Str
			, TCStr<tf_CTCStrTraits2> const &_StrFind
			, tf_CData const *_pStrReplace
			, umint _MaxLen
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplace(_Str, _StrFind.f_GetStr(), _StrFind.f_GetLen(), _pStrReplace, fg_StrLen(_pStrReplace), _MaxLen);
	}


	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace
		(
			TCStr<tf_CTCStrTraits> &_Str
			, tf_CData const *_pStrFind
			, TCStr<tf_CTCStrTraits2> const &_StrReplace
			, umint _MaxLen
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplace(_Str, _pStrFind, fg_StrLen(_pStrFind), _StrReplace.f_GetStr(), _StrReplace.f_GetLen(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplace
		(
			TCStr<tf_CTCStrTraits> &_Str
			, TCStr<tf_CTCStrTraits1> const &_StrFind
			, TCStr<tf_CTCStrTraits2> const &_StrReplace
			, umint _MaxLen
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits1>::mc_Value && TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplace(_Str, _StrFind.f_GetStr(), _StrFind.f_GetLen(), _StrReplace.f_GetStr(), _StrReplace.f_GetLen(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase
		(
			TCStr<tf_CTCStrTraits> &_Str
			, tf_CData const *_pStrFind
			, umint _LenFind
			, tf_CData2 const *_pStrReplace
			, umint _LenReplace
		)
	{
		using CChar = typename TCStr<tf_CTCStrTraits>::CChar;

		CChar const *pStr1 = _Str.f_GetStr();
		CChar const *pStrFind = fg_StrAdd(pStr1, fg_StrFindNoCase(pStr1, _pStrFind));

		if (!pStrFind)
			return _Str;

		umint nReplaces = 0;

		while (pStrFind)
		{
			++nReplaces;
			pStr1 = pStrFind + _LenFind;
			pStrFind = fg_StrAdd(pStr1, fg_StrFindNoCase(pStr1, _pStrFind));
		}

		umint Len = fg_StrLen(_Str);

		umint NeededSize = Len;
		if (_LenReplace > _LenFind)
			NeededSize += nReplaces * (_LenReplace - _LenFind);
		else
			NeededSize -= nReplaces * (_LenFind - _LenReplace);

		fg_StrReplaceNoCaseWithCount(_Str.f_GetStr(NeededSize), Len, _pStrFind, _LenFind, _pStrReplace, _LenReplace, NeededSize + 1, nReplaces);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace)
	{
		return fg_StrReplaceNoCase(_Str, _pStrFind, fg_StrLen(_pStrFind), _pStrReplace, fg_StrLen(_pStrReplace));
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, TCStr<tf_CTCStrTraits2> const &_StrFind, tf_CData2 const *_pStrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str, _StrFind.f_GetStr(), _StrFind.f_GetLen(), _pStrReplace, fg_StrLen(_pStrReplace));
	}


	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, const TCStr<tf_CTCStrTraits2> &_StrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str, _pStrFind, fg_StrLen(_pStrFind), _StrReplace.f_GetStr(), _StrReplace.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase
		(
			TCStr<tf_CTCStrTraits> &_Str
			, TCStr<tf_CTCStrTraits1> const &_StrFind
			, TCStr<tf_CTCStrTraits2> const &_StrReplace
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits1>::mc_Value && TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str, _StrFind.f_GetStr(), _StrFind.f_GetLen(), _StrReplace.f_GetStr(), _StrReplace.f_GetLen());
	}

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase
		(
			TCStr<tf_CTCStrTraits> &_Str
			, tf_CData const *_pStrFind
			, umint _LenFind
			, tf_CData2 const *_pStrReplace
			, umint _LenReplace
			, umint _MaxLen
		)
	{
		using CChar = typename TCStr<tf_CTCStrTraits>::CChar;

		CChar const *pStr1 = _Str.f_GetStr();
		CChar const *pStrFind = fg_StrAdd(pStr1, fg_StrFindNoCase(pStr1, _pStrFind));

		if (!pStrFind)
			return _Str;

		umint nReplaces = 0;

		while (pStrFind)
		{
			++nReplaces;
			pStr1 = pStrFind + _LenFind;
			pStrFind = fg_StrAdd(pStr1, fg_StrFindNoCase(pStr1, _pStrFind));
		}

		umint Len = fg_StrLen(_Str);

		umint NeededSize;
		if (_LenReplace >= _LenFind)
			NeededSize = fg_Min(Len + nReplaces * (_LenReplace - _LenFind), _MaxLen);
		else
			NeededSize = fg_Min(Len - nReplaces * (_LenFind - _LenReplace), _MaxLen);

		fg_StrReplaceNoCaseWithCount(_Str.f_GetStr(NeededSize), Len, _pStrFind, _LenFind, _pStrReplace, _LenReplace, NeededSize + 1, nReplaces);
		_Str.f_SetModified();
		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_large TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase(TCStr<tf_CTCStrTraits> &_Str, tf_CData const *_pStrFind, tf_CData2 const *_pStrReplace, umint _MaxLen)
	{
		return fg_StrReplaceNoCase(_Str, _pStrFind, fg_StrLen(_pStrFind), _pStrReplace, fg_StrLen(_pStrReplace), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase
		(
			TCStr<tf_CTCStrTraits> &_Str
			, TCStr<tf_CTCStrTraits2> const &_StrFind
			, tf_CData const *_pStrReplace
			, umint _MaxLen
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str, _StrFind.f_GetStr(), _StrFind.f_GetLen(), _pStrReplace, fg_StrLen(_pStrReplace), _MaxLen);
	}


	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits2, typename tf_CData>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase
		(
			TCStr<tf_CTCStrTraits> &_Str
			, tf_CData const *_pStrFind
			, TCStr<tf_CTCStrTraits2> const &_StrReplace
			, umint _MaxLen
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str, _pStrFind, fg_StrLen(_pStrFind), _StrReplace.f_GetStr(), _StrReplace.f_GetLen(), _MaxLen);
	}

	template <typename tf_CTCStrTraits, typename tf_CTCStrTraits1, typename tf_CTCStrTraits2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceNoCase
		(
			TCStr<tf_CTCStrTraits> &_Str
			, TCStr<tf_CTCStrTraits1> const &_StrFind
			, TCStr<tf_CTCStrTraits2> const &_StrReplace
			, umint _MaxLen
		)
	{
		static_assert(TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits1>::mc_Value && TCIsStrCompatibleWrite<tf_CTCStrTraits, tf_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str, _StrFind.f_GetStr(), _StrFind.f_GetLen(), _StrReplace.f_GetStr(), _StrReplace.f_GetLen(), _MaxLen);
	}


	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceChar(TCStr<tf_CTCStrTraits> &_Str, tf_CData _CharFind, tf_CData2 _CharReplace)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1)
			return _Str;

		fg_StrReplaceChar(pStr1, _CharFind, _CharReplace);
		return _Str;
	}

	template <typename tf_CTCStrTraits, typename tf_CData, typename tf_CData2>
	inline_small TCStr<tf_CTCStrTraits> &fg_StrReplaceChar(TCStr<tf_CTCStrTraits> &_Str, tf_CData _CharFind, tf_CData2 _CharReplace, umint _MaxLen)
	{
		typename TCStr<tf_CTCStrTraits>::CChar *pStr1 = _Str.f_GetStrUniqueWritable();
		if (!pStr1)
			return _Str;
		fg_StrReplaceChar(pStr1, _CharFind, _CharReplace, _MaxLen);
		return _Str;
	}
}
