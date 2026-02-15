// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
namespace NMib::NStr
{
	template <typename t_CData, typename t_CReturn, typename t_CTerm, typename t_CPoints>
	t_CReturn fg_StrToFloatParse(t_CData const * &_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators, bool _bDontFail = false, t_CPoints const *_pPoints = nullptr);

	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloat(t_CData const *_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators, bool _bDontFail);
	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloat(t_CData const *_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators);
	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToFloat(t_CData const *_pStr, t_CReturn _FailValue);

	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloatParse(t_CData const * &_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators, bool _bDontFail);
	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloatParse(t_CData const * &_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators);
	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToFloatParse(t_CData const * &_pStr, t_CReturn _FailValue);

	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloatExact(t_CData const *_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators);
	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToFloatExact(t_CData const *_pStr, t_CReturn _FailValue);

	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloatParseExact(t_CData const * &_pStr, t_CReturn _FailValue, t_CTerm const *_pStrTerminators);
	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToFloatParseExact(t_CData const * &_pStr, t_CReturn _FailValue);
}

#include "Malterlib_String_Parse_Float.hpp"
