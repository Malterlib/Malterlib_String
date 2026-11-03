// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraitsTypes>
	struct TCStrSpan
	{
		using CStrTraitsTypes = t_CStrTraitsTypes;
		using CChar = typename t_CStrTraitsTypes::CChar;
		using CUnsignedChar = NTraits::TCUnsigned<typename t_CStrTraitsTypes::CChar>;

		TCStrSpan() = default;
		TCStrSpan(TCStrSpan const &_Other) = default;
		TCStrSpan(TCStrSpan &&_Other) = default;
		TCStrSpan(CChar const *_pStr, umint _Length);

		TCStrSpan &operator = (TCStrSpan const &_Other) = default;
		TCStrSpan &operator = (TCStrSpan &&_Other) = default;

		CChar const *f_GetStr() const;
		umint f_GetLen() const;

	private:
		static constexpr CChar const mcp_EmptyStr[1] = {0};

		CChar const *mp_pStr = mcp_EmptyStr;
		umint mp_Length = 0;
	};
}

#include "Malterlib_String_Container_Span.hpp"
