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
		template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToMove, typename tf_CBackToMove>
		auto fg_StrMove(NIterator::TCRange<tf_CFront, tf_CBack> const &_rDestination, NIterator::TCRange<tf_CFrontToMove, tf_CBackToMove> const &_rSource);

		template 
		<
			typename ...tfp_CTags
			, typename tf_CContainer
			, typename tf_CContainerToMove
			, typename TCEnableIf
			<
				!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
				|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToMove>::CType>::mc_Value
			>::CType * = nullptr
		>
		auto fg_StrMove(tf_CContainer &&_Destination, tf_CContainerToMove &&_Source);
#endif
	}
}

#include "Malterlib_String_Algorithm_Move.hpp"
