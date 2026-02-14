// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStrTraits>
	struct TCStrSpan;

	template <typename t_CTCStrTraits>
	struct TCStr;

	class CStrTraits_CStr;
	class CStrTraits_CWStr;
	class CStrTraits_CUStr;
	class CStrTraits_CStrNonTracked;
	class CStrTraits_CWStrNonTracked;
	class CStrTraits_CUStrNonTracked;

	using CStr = TCStr<CStrTraits_CStr>;
	using CWStr = TCStr<CStrTraits_CWStr>;
	using CUStr = TCStr<CStrTraits_CUStr>;

	using CStrNonTracked = TCStr<CStrTraits_CStrNonTracked>;
	using CWStrNonTracked = TCStr<CStrTraits_CWStrNonTracked>;
	using CUStrNonTracked = TCStr<CStrTraits_CUStrNonTracked>;

	template <typename t_CData0, typename t_CData1>
	struct TCChooseStrCompareType
	{
	public:

		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, t_CData1>>>;
	};

	template <typename t_CData0, typename t_CData1>
	struct TCChooseStrCompareType<t_CData0, TCStr<t_CData1>>
	{
	public:

		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, typename TCStr<t_CData1>::CChar>>>;
	};

	template <typename t_CData0, typename t_CData1>
	struct TCChooseStrCompareType<TCStr<t_CData1>, t_CData0>
	{
	public:

		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, typename TCStr<t_CData1>::CChar>>>;
	};

	template <typename t_CData0, typename t_CData1>
	struct TCChooseStrCompareType<TCStr<t_CData0>, TCStr<t_CData1>>
	{
	public:

		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<typename TCStr<t_CData0>::CChar, typename TCStr<t_CData1>::CChar>>>;
	};
}
