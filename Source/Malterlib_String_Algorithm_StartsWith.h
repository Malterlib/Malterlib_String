// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

#include "Malterlib_String_Algorithm_Common.h"

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontStartsWith, typename tf_CBackStartsWith>
	auto fg_StrStartsWith(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontStartsWith, tf_CBackStartsWith> const &_rStartsWith);

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerStartsWith
		, typename TCEnableIf
		<
			!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
			|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerStartsWith>::CType>::mc_Value
		>::CType * = nullptr
	>
	auto fg_StrStartsWith(tf_CContainer &&_Container, tf_CContainerStartsWith &&_ContainerStartsWith);
}

#include "Malterlib_String_Algorithm_StartsWith.hpp"
