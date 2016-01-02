// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib
{
	namespace NStr2
	{
#if DMib_Cxx14
		template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToCopy, typename tf_CBackToCopy>
		auto fg_StrCopy(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontToCopy, tf_CBackToCopy> const &_rToCopy);

		template
		<
			typename ...tfp_CTags
			, typename tf_CContainer
			, typename tf_CContainerToCopy
			, typename TCEnableIf
			<
				!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
				|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToCopy>::CType>::mc_Value
			>::CType * = nullptr
		>
		auto fg_StrCopy(tf_CContainer &&_Container, tf_CContainerToCopy &&_ContainerToCopy);
#endif
	}
}

#include "Malterlib_String_Algorithm_Copy.hpp"
