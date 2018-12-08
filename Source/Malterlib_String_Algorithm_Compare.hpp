// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/AlgorithmModifiers>

namespace NMib::NStr2::NPrivate
{
	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToCompare
		, typename tf_CBackToCompare
	>
	ECompare fg_Private_StrCompare_Algorithm
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NIterator::TCRange<tf_CFrontToCompare, tf_CBackToCompare> const &_rToCompare
		)
	{
		auto rCharacters = fg_GetStringRange<tf_CTags>(_rCharacters);
		auto rToCompare = fg_GetStringRange<tf_CTags>(_rToCompare);

		while (rCharacters && rToCompare)
		{
			ECompare Compare = fg_CharCompare<tf_CTags>(*rCharacters, *rToCompare);
			if (unlikely(Compare != ECompare_Equal))
				return Compare;
			++rCharacters;
			++rToCompare;
		}
		if (rCharacters)
		{
			if (!rToCompare)
				return ECompare_GreaterThan;
		}
		else if (rToCompare)
			return ECompare_LessThan;
		return ECompare_Equal;
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToCompare
		, typename tf_CBackToCompare
		, typename tf_CUnicodeTag
	>
	ECompare fg_Private_StrCompare
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NIterator::TCRange<tf_CFrontToCompare, tf_CBackToCompare> const &_rToCompare
			, tf_CUnicodeTag // Same
			, tf_CUnicodeTag
		)
	{
		return fg_Private_StrCompare_Algorithm<tf_CTags>(_rCharacters, _rToCompare);
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToCompare
		, typename tf_CBackToCompare
		, typename tf_CUnicodeTag
		, typename tf_CUnicodeTagToCompare
	>
	ECompare fg_Private_StrCompare
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NIterator::TCRange<tf_CFrontToCompare, tf_CBackToCompare> const &_rToCompare
			, tf_CUnicodeTag // Different, need to use unicode
			, tf_CUnicodeTagToCompare
		)
	{
		auto rUTFCharacters = fg_RangeAdaptor_UTFDecode(_rCharacters);
		auto rUTFToCompare = fg_RangeAdaptor_UTFDecode(_rToCompare);
		return fg_Private_StrCompare_Algorithm<tf_CTags>(rUTFCharacters, rUTFToCompare);
	}
}

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToCompare, typename tf_CBackToCompare>
	ECompare fg_StrCompare(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontToCompare, tf_CBackToCompare> const &_rToCompare)
	{
		return NPrivate::fg_Private_StrCompare<TCTags<tfp_CTags...>>
			(
				_rCharacters
				, _rToCompare
				, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
				, typename TCGetTag<typename tf_CFrontToCompare::CTags, NStr::CIteratorStringEncoding_None>::CType()
			)
		;
	}

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerToCompare
		, typename TCEnableIf
		<
			!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
			|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToCompare>::CType>::mc_Value
		>::CType *
	>
	ECompare fg_StrCompare(tf_CContainer &&_Container, tf_CContainerToCompare &&_ContainerToCompare)
	{
		auto rCharacters = NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_Container);
		auto rToCompare = NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_ContainerToCompare);
		return NStr2::fg_StrCompare<tfp_CTags...>(rCharacters, rToCompare);
	}
}
