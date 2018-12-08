// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
	uint32 fg_StrHashMurmur3(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, uint32 _Seed = 0x11a8742f);

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename TCEnableIf
		<
			!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
		>::CType * = nullptr
	>
	uint32 fg_StrHashMurmur3(tf_CContainer &&_Container, uint32 _Seed = 0x11a8742f);
}

#include "Malterlib_String_Algorithm_HashMurmur3.hpp"
