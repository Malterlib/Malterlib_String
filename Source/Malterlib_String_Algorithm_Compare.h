// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

#include "Malterlib_String_Algorithm_Common.h"

namespace NMib
{
	namespace NStr2
	{
		template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToCompare, typename tf_CBackToCompare>
		ECompare fg_StrCompare(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontToCompare, tf_CBackToCompare> const &_rToCompare);

		template 
		<
			typename ...tfp_CTags
			, typename tf_CContainer
			, typename tf_CContainerToCompare
			, typename TCEnableIf
			<
				!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
				|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToCompare>::CType>::mc_Value
			>::CType * = nullptr
		>
		ECompare fg_StrCompare(tf_CContainer &&_Container, tf_CContainerToCompare &&_ContainerToCompare);
	}
}

#include "Malterlib_String_Algorithm_Compare.hpp"
