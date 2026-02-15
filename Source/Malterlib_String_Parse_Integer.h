// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	enum EStrToIntParseMode
	{
		EStrToIntParseMode_Hex = 16,
		EStrToIntParseMode_Base10 = 10,
		EStrToIntParseMode_Binary = 8,
		EStrToIntParseMode_Octal = 2,
	};

	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToIntParse
		(
			t_CData const * &_pStr
			, t_CReturn _FailValue
			, t_CTerm const *_pStrTerminators = nullptr
			, bool _bDontFail = false
			, int32 _ParseMode = EStrToIntParseMode_Base10
			, bool *_pFailed = nullptr
		)
	;

	template<typename t_CData, typename t_CReturn>
	inline_medium t_CReturn fg_StrToIntParseHex(t_CData const * &_pStr, t_CReturn _FailValue);
	template<typename t_CData, typename t_CReturn>
	inline_medium t_CReturn fg_StrToIntParseHex(t_CData const * &_pStr, t_CReturn _FailValue, t_CData _Terminator);

	template <typename t_CData, typename t_CReturn>
	inline_medium t_CReturn fg_StrToIntParseHexNoSign(t_CData const * &_pStr, t_CReturn _FailValue);
	template <typename t_CData, typename t_CReturn>
	inline_medium t_CReturn fg_StrToIntParseHexNoSign(t_CData const * &_pStr, mint _MaxLen, t_CReturn _FailValue);

	template <typename t_CData, typename t_CReturn>
	inline_small t_CReturn fg_StrToIntBase10(t_CData const *_pStr, t_CReturn _FailValue);

	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToIntBase10Parse(t_CData const * &_pStr, t_CReturn _FailValue);

	template <typename t_CData, typename t_CReturn>
	inline_large t_CReturn fg_StrToIntBase10NoSign(t_CData const *_pStr, t_CReturn _FailValue);
	template <typename t_CData, typename t_CReturn>
	inline_large t_CReturn fg_StrToIntBase10ParseNoSign(t_CData const * &_pStr, t_CReturn _FailValue);

	template <typename t_CData, typename t_CReturn>
	inline_small t_CReturn fg_StrToInt(t_CData const *_pStr, t_CReturn _FailValue);
	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	inline_small t_CReturn fg_StrToInt(t_CData const *_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators);

	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToIntParse(t_CData const * &_pStr, t_CReturn _FailValue);

	template <typename t_CData, typename t_CReturn>
	inline_small t_CReturn fg_StrToIntExact(t_CData const *_pStr, t_CReturn _FailValue);
	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	inline_small t_CReturn fg_StrToIntExact(t_CData const *_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators);

	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToIntParseExact(t_CData const * &_pStr, t_CReturn _FailValue);
	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToIntParseExact(t_CData const * &_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators);
}

#include "Malterlib_String_Parse_Integer.hpp"
