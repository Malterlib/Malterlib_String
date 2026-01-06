// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontStartsWith, typename tf_CBackStartsWith>
	auto fg_StrEndsWith(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontStartsWith, tf_CBackStartsWith> const &_rStartsWith);

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerEndsWith
		, TCEnableIf
		<
			!NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>>
			|| !NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerEndsWith>>
		> * = nullptr
	>
	auto fg_StrEndsWith(tf_CContainer &&_Container, tf_CContainerEndsWith &&_ContainerStartsWith);
}

#include "Malterlib_String_Algorithm_EndsWith.hpp"
