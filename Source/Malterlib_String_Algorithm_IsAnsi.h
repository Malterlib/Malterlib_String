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
		template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
		bool fg_StrIsAnsi(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters);
		
		template 
		<
			typename ...tfp_CTags
			, typename tf_CContainer
			, typename TCEnableIf
			<
				!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
			>::CType * = nullptr
		>
		bool fg_StrIsAnsi(tf_CContainer &&_Container);
	}
}

#include "Malterlib_String_Algorithm_IsAnsi.hpp"
