// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
	uint32 fg_StrHashDJB2(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters);

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename TCEnableIf
		<
			!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
		>::CType * = nullptr
	>
	uint32 fg_StrHashDJB2(tf_CContainer &&_Container);
}

#include "Malterlib_String_Algorithm_HashDJB2.hpp"
