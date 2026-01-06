// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CChar>
	auto fg_StrFindChar(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, tf_CChar _Character);

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CChar
		, TCEnableIf
		<
			!NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>>
		> * = nullptr
	>
	auto fg_StrFindChar(tf_CContainer &_Container, tf_CChar _Character);
}

#include "Malterlib_String_Algorithm_FindChar.hpp"
