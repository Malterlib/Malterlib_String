// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/AlgorithmModifiers>

namespace NMib::NStr2::NPrivate
{
	template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
	bool fg_Private_StrIsEmpty(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters)
	{
		return !_rCharacters;
	}
}

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
	bool fg_StrIsEmpty(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters)
	{
		return NPrivate::fg_Private_StrIsEmpty<TCTags<tfp_CTags...>>(_rCharacters);
	}

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, TCEnableIf
		<
			!NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>>
		> *
	>
	bool fg_StrIsEmpty(tf_CContainer &&_Container)
	{
		auto rCharacters = NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>
			(
				fg_Forward<tf_CContainer>(_Container)
			)
		;
		return NStr2::fg_StrIsEmpty<tfp_CTags...>(rCharacters);
	}
}
