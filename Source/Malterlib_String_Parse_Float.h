// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
namespace NMib::NStr
{
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm, typename tf_CPoints>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail = false, tf_CPoints const *_pPoints = nullptr);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm, typename tf_CPoints>
	auto fg_StrToFloatParse(tf_CData const * &_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail = false, tf_CPoints const *_pPoints = nullptr)
		-> tf_CReturn
	;

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloat(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloat(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloat(tf_CData const *_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToFloat(tf_CData const *_pStr, tf_CReturn _FailValue);

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, tf_CReturn _FailValue);

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatExact(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatExact(tf_CData const *_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToFloatExact(tf_CData const *_pStr, tf_CReturn _FailValue);

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatParseExact(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators);
	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToFloatParseExact(tf_CData const * &_pStr, tf_CReturn _FailValue);
}

#include "Malterlib_String_Parse_Float.hpp"
