// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	struct TCStrSpan;

	template <typename t_CTCStrTraits>
	struct TCStr;

	struct CStrTraits_CStr;
	struct CStrTraits_CWStr;
	struct CStrTraits_CUStr;
	struct CStrTraits_CStrNonTracked;
	struct CStrTraits_CWStrNonTracked;
	struct CStrTraits_CUStrNonTracked;

	using CStr = TCStr<CStrTraits_CStr>;
	using CWStr = TCStr<CStrTraits_CWStr>;
	using CUStr = TCStr<CStrTraits_CUStr>;

	using CStrNonTracked = TCStr<CStrTraits_CStrNonTracked>;
	using CWStrNonTracked = TCStr<CStrTraits_CWStrNonTracked>;
	using CUStrNonTracked = TCStr<CStrTraits_CUStrNonTracked>;

	template <typename t_CData0, typename t_CData1>
	struct TCChooseStrCompareType
	{
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, t_CData1>>>;
	};

	template <typename t_CData0, typename t_CData1>
	struct TCChooseStrCompareType<t_CData0, TCStr<t_CData1>>
	{
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, typename TCStr<t_CData1>::CChar>>>;
	};

	template <typename t_CData0, typename t_CData1>
	struct TCChooseStrCompareType<TCStr<t_CData1>, t_CData0>
	{
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, typename TCStr<t_CData1>::CChar>>>;
	};

	template <typename t_CData0, typename t_CData1>
	struct TCChooseStrCompareType<TCStr<t_CData0>, TCStr<t_CData1>>
	{
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<typename TCStr<t_CData0>::CChar, typename TCStr<t_CData1>::CChar>>>;
	};
}
