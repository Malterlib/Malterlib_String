// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/Algorithm/Count>
#include <Mib/Algorithm/Advance>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/AlgorithmModifiers>
#include <Mib/String/Algorithms/Finish>

namespace NMib::NStr2::NPrivate
{
	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToMove
		, typename tf_CBackToMove
	>
	auto fg_Private_StrMove_Algorithm
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rDestination
			, NIterator::TCRange<tf_CFrontToMove, tf_CBackToMove> const &_rSource
		)
	{
		auto rCharacters = _rDestination;
		auto rToMove = _rSource;

		while (rCharacters && rToMove)
		{
			*rCharacters = *rToMove;
			++rCharacters;
			++rToMove;
		}
		return rCharacters;
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToMove
		, typename tf_CBackToMove
	>
	auto fg_Private_StrMove
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rDestination
			, NIterator::TCRange<tf_CFrontToMove, tf_CBackToMove> const &_rSource
			, NIterator::CIteratorTraversal_Backward
		)
	{
		if (_rSource.f_Front() < _rDestination.f_Front())
		{
			mint Length = NAlgorithm::fg_Count(_rSource);
			auto rDestination = _rDestination;
			NAlgorithm::fg_Advance(rDestination, Length);
			auto rDestinationReversible = fg_Range(_rDestination.f_Front(), rDestination.f_Front());
			auto rDestinationReversed = fg_RangeReverse(rDestinationReversible);
			fg_Private_StrMove_Algorithm<tf_CTags>(rDestinationReversed, fg_RangeReverse(_rSource));
			return NIterator::fg_RangeReturn<tf_CTags>(_rDestination, rDestination);
		}
		else
		{
			return NIterator::fg_RangeReturn<tf_CTags>(_rDestination, fg_Private_StrMove_Algorithm<tf_CTags>(_rDestination, _rSource));
		}
	}
}
		
namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToMove, typename tf_CBackToMove>
	auto fg_StrMove(NIterator::TCRange<tf_CFront, tf_CBack> const &_rDestination, NIterator::TCRange<tf_CFrontToMove, tf_CBackToMove> const &_rSource)
	{
		return NPrivate::fg_Private_StrMove<TCTags<tfp_CTags...>>
			(
				_rDestination
				, _rSource
				, typename TCGetTag<typename tf_CFront::CTags, NIterator::CIteratorTraversal_None>::CType()
			)
		;
	}

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerToMove
		, typename TCEnableIf
		<
			!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
			|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToMove>::CType>::mc_Value
		>::CType *
	>
	auto fg_StrMove(tf_CContainer &&_Destination, tf_CContainerToMove &&_Source)
	{
		return NStr2::fg_StrMove<tfp_CTags...>
			(
				NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Writable>>>(_Destination)
				, NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_Source)
			)
		;
	}
}
