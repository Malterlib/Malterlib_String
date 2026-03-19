// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData>
	inline_small bool TCStrTraits<t_CChar, t_Type, t_CParams>::fs_CharIsNumber(tf_CData const _Character)
	{
		return fg_CharIsNumber(_Character);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData>
	inline_small tf_CData TCStrTraits<t_CChar, t_Type, t_CParams>::fs_CharUpperCase(tf_CData _Character)
	{
		return fg_CharUpperCase(_Character);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData>
	inline_small tf_CData TCStrTraits<t_CChar, t_Type, t_CParams>::fs_CharLowerCase(tf_CData _Character)
	{
		return fg_CharLowerCase(_Character);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToIntBase10ParseNoSign(tf_CData const * &_pStr, tf_CReturn _FailValue)
	{
		return fg_StrToIntBase10ParseNoSign(_pStr, _FailValue);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToIntBase10NoSign(tf_CData const *_pStr, tf_CReturn _FailValue)
	{
		return fg_StrToIntBase10NoSign(_pStr, _FailValue);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToIntBase10(tf_CData const *_pStr, tf_CReturn _FailValue)
	{
		return fg_StrToIntBase10(_pStr, _FailValue);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToIntParse
		(
			tf_CData const * &_pStr
			, tf_CReturn _FailValue
			, tf_CData const *_pStrTerminators
			, bool _bDontFail
			, int32 _ParseMode
		)
	{
		return fg_StrToIntParse(_pStr, _FailValue, _pStrTerminators, _bDontFail, _ParseMode);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToIntParseHex(tf_CData const * &_pStr, tf_CReturn _FailValue)
	{
		return fg_StrToIntParseHex(_pStr, _FailValue, _FailValue);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template<typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToIntParseHex(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CData _Terminator)
	{
		return fg_StrToIntParseHex(_pStr, _FailValue);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData>
	inline_small umint TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrLen(tf_CData const *_pStr)
	{
		return fg_StrLen(_pStr);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData>
	inline_small umint TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrLen(tf_CData const *_pStr, umint _MaxLen)
	{
		return fg_StrLen(_pStr, _MaxLen);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrUpperCase(tf_CData1 *_pDest, tf_CData2 const *_pSource, aint _SourceLen)
	{
		DMibFastCheck((sizeof(CChar) > 1 || NTraits::cIsSame<CChar, ch8> && mc_Type == EStrType_UTF));
		return fg_StrUpperCase(_pDest, _pSource, _SourceLen);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData1, typename tf_CData2>
	inline_small tf_CData1 *TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrLowerCase(tf_CData1 *_pDest, tf_CData2 const *_pSource, aint _SourceLen)
	{
		DMibFastCheck((sizeof(CChar) > 1 || NTraits::cIsSame<CChar, ch8> && mc_Type == EStrType_UTF));
		return fg_StrLowerCase(_pDest, _pSource, _SourceLen);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToInt(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators)
	{
		return fg_StrToInt(_pStr, _FailValue, _pStrTerminators);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToIntExact(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators)
	{
		return fg_StrToIntExact(_pStr, _FailValue, _pStrTerminators);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToFloat(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators)
	{
		return fg_StrToFloat(_pStr, _FailValue, _pStrTerminators);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToFloatExact(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators)
	{
		return fg_StrToFloatExact(_pStr, _FailValue, _pStrTerminators);
	}

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn TCStrTraits<t_CChar, t_Type, t_CParams>::fs_StrToFloatParse(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators, bool _bDontFail)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, _bDontFail);
	}
}
