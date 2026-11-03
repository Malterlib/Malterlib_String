// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	enum EStrToIntParseMode
	{
		EStrToIntParseMode_Hex      = 16
		, EStrToIntParseMode_Base10 = 10
		, EStrToIntParseMode_Binary = 8
		, EStrToIntParseMode_Octal  = 2
	};

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	auto fg_StrToIntParse
		(
			tf_CData const * &_pStr
			, tf_CReturn _FailValue
			, tf_CTerm const *_pStrTerminators = nullptr
			, bool _bDontFail = false
			, int32 _ParseMode = EStrToIntParseMode_Base10
			, bool *_pFailed = nullptr
		)
		-> tf_CReturn
	;
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	auto fg_StrToIntParse
		(
			tf_CData const * &_pStr
			, umint _MaxLen
			, tf_CReturn _FailValue
			, tf_CTerm const *_pStrTerminators = nullptr
			, bool _bDontFail = false
			, int32 _ParseMode = EStrToIntParseMode_Base10
			, bool *_pFailed = nullptr
		)
		-> tf_CReturn
	;

	template <typename tf_CData, typename tf_CReturn>
	inline_medium tf_CReturn fg_StrToIntParseHex(tf_CData const * &_pStr, tf_CReturn _FailValue);
	template <typename tf_CData, typename tf_CReturn>
	inline_medium tf_CReturn fg_StrToIntParseHex(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CData _Terminator);

	template <typename tf_CData, typename tf_CReturn>
	inline_medium tf_CReturn fg_StrToIntParseHexNoSign(tf_CData const * &_pStr, tf_CReturn _FailValue);
	template <typename tf_CData, typename tf_CReturn>
	inline_medium tf_CReturn fg_StrToIntParseHexNoSign(tf_CData const * &_pStr, umint _MaxLen, tf_CReturn _FailValue);

	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn fg_StrToIntBase10(tf_CData const *_pStr, tf_CReturn _FailValue);

	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToIntBase10Parse(tf_CData const * &_pStr, tf_CReturn _FailValue);

	template <typename tf_CData, typename tf_CReturn>
	inline_large tf_CReturn fg_StrToIntBase10NoSign(tf_CData const *_pStr, tf_CReturn _FailValue);
	template <typename tf_CData, typename tf_CReturn>
	inline_large tf_CReturn fg_StrToIntBase10ParseNoSign(tf_CData const * &_pStr, tf_CReturn _FailValue);

	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn fg_StrToInt(tf_CData const *_pStr, tf_CReturn _FailValue);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	inline_small tf_CReturn fg_StrToInt(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	inline_small tf_CReturn fg_StrToInt(tf_CData const *_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);

	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToIntParse(tf_CData const * &_pStr, tf_CReturn _FailValue);

	template <typename tf_CData, typename tf_CReturn>
	inline_small tf_CReturn fg_StrToIntExact(tf_CData const *_pStr, tf_CReturn _FailValue);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	inline_small tf_CReturn fg_StrToIntExact(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	inline_small tf_CReturn fg_StrToIntExact(tf_CData const *_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);

	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToIntParseExact(tf_CData const * &_pStr, tf_CReturn _FailValue);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToIntParseExact(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
}

#include "Malterlib_String_Parse_Integer.hpp"
