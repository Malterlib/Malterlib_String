// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

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
		TCStrSpan(TCStrSpan const &) = default;
		TCStrSpan(TCStrSpan &&) = default;
		TCStrSpan(CChar const *_pStr, mint _Length);

		TCStrSpan &operator = (TCStrSpan const &) = default;
		TCStrSpan &operator = (TCStrSpan &&) = default;

		CChar const *f_GetStr() const;
		mint f_GetLen() const;

	private:
		static constexpr CChar const mc_EmptyStr[1] = {0};

		CChar const *m_pStr = mc_EmptyStr;
		mint m_Length = 0;
	};
}

#include "Malterlib_String_Container_Span.hpp"
