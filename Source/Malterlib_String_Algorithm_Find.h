// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToFind, typename tf_CBackToFind>
	auto fg_StrFind(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontToFind, tf_CBackToFind> const &_rToFind);

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerToFind
		, TCEnableIf
		<
			!NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>>
			|| !NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToFind>>
		> * = nullptr
	>
	auto fg_StrFind(tf_CContainer &&_Container, tf_CContainerToFind &&_ContainerToFind);
}

#include "Malterlib_String_Algorithm_Find.hpp"
