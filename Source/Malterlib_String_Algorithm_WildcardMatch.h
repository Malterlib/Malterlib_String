// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

#include "Malterlib_String_Algorithm_Common.h"

namespace NMib::NStr2
{
	enum EWildcardMatch
	{
		EWildcardMatch_NotMatched = 0
		, EWildcardMatch_WholeStringMatched = 1
		, EWildcardMatch_PatternExhausted = 2
		, EWildcardMatch_WholeStringMatchedAndPatternExhausted = 3
	};

	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontStartsWith, typename tf_CBackStartsWith>
	auto fg_StrStartsWith(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontStartsWith, tf_CBackStartsWith> const &_rStartsWith);

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerToMatch
		, typename TCEnableIf
		<
			!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
			|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToMatch>::CType>::mc_Value
		>::CType * = nullptr
	>
	auto fg_StrWildcardMatch(tf_CContainer &&_Container, tf_CContainerToMatch &&_ContainerToMatch);
}

#include "Malterlib_String_Algorithm_WildcardMatch.hpp"
