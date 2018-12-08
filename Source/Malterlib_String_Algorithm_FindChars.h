// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToFind, typename tf_CBackToFind>
	auto fg_StrFindChars(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontToFind, tf_CBackToFind> const &_rToFind);

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerToFind
		, typename TCEnableIf
		<
			!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
			|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToFind>::CType>::mc_Value
		>::CType * = nullptr
	>
	auto fg_StrFindChars(tf_CContainer &&_Container, tf_CContainerToFind &&_ContainerToFind);
}

#include "Malterlib_String_Algorithm_FindChars.hpp"
