// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/Algorithm/ForEachAbortable>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/AlgorithmModifiers>
#include <Mib/String/IteratorUTFEncodeOutput>
#include <Mib/String/Algorithms/Finish>

namespace NMib::NStr2::NPrivate
{
	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToCopy
		, typename tf_CBackToCopy
	>
	auto fg_Private_StrCopy_Algorithm
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NIterator::TCRange<tf_CFrontToCopy, tf_CBackToCopy> const &_rToCopy
		)
	{
		auto rCharacters = _rCharacters;
		auto rToCopy = fg_GetStringRange<tf_CTags>(_rToCopy);

		NAlgorithm::fg_ForEachAbortable
			(
				rToCopy
				, [&](decltype(*rToCopy) _Value)
				{
					*rCharacters = _Value;
					++rCharacters;
					if (!rCharacters)
						return false;
					return true;
				}
			)
		;
		return NIterator::fg_RangeReturn<tf_CTags>(_rCharacters, rCharacters);
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToCopy
		, typename tf_CBackToCopy
		, typename tf_CUnicodeTag
	>
	auto fg_Private_StrCopy
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NIterator::TCRange<tf_CFrontToCopy, tf_CBackToCopy> const &_rToCopy
			, tf_CUnicodeTag // Same
			, tf_CUnicodeTag
			, NIterator::CIteratorTraversal_Backward
		)
	{
		return fg_Private_StrCopy_Algorithm<tf_CTags>(_rCharacters, _rToCopy);
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToCopy
		, typename tf_CBackToCopy
		, typename tf_CUnicodeTag
		, typename tf_CUnicodeTagToCopy
	>
	auto fg_Private_StrCopy
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NIterator::TCRange<tf_CFrontToCopy, tf_CBackToCopy> const &_rToCopy
			, tf_CUnicodeTag // Different, need to use unicode
			, tf_CUnicodeTagToCopy
			, NIterator::CIteratorTraversal_None // We always need to do whole code point encoding when iterator cannot go backwards
		)
	{
		using CReturnType = typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CBack, tf_CFront, tf_CFront, tf_CTags>::CType;
		auto rUTFToCopy = fg_RangeAdaptor_UTFDecode(_rToCopy);
		auto rDestination = fg_RangeAdaptor_UTFEncodeOutput(_rCharacters);
		auto rFound = fg_Private_StrCopy_Algorithm<tf_CTags>(rDestination, rUTFToCopy);
		return fg_Range
			(
				NIterator::fg_ParentIteratorOfType<typename CReturnType::CFront>(rFound.f_Front())
				, NIterator::fg_ParentIteratorOfType<typename CReturnType::CBack>(rFound.f_Back())
			)
		;
	}
}
		
namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToCopy, typename tf_CBackToCopy>
	auto fg_StrCopy(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontToCopy, tf_CBackToCopy> const &_rToCopy)
	{
		return NPrivate::fg_Private_StrCopy<TCTags<tfp_CTags...>>
			(
				_rCharacters
				, _rToCopy
				, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
				, typename TCGetTag<typename tf_CFrontToCopy::CTags, NStr::CIteratorStringEncoding_None>::CType()
				, typename TCGetTag<typename tf_CFront::CTags, NIterator::CIteratorTraversal_None>::CType()
			)
		;
	}

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerToCopy
		, TCEnableIf
		<
			!NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>>
			|| !NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToCopy>>
		> *
	>
	auto fg_StrCopy(tf_CContainer &&_Container, tf_CContainerToCopy &&_ContainerToCopy)
	{
		auto rReturn = NStr2::fg_StrCopy<tfp_CTags...>
			(
				NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Writable>>>(_Container)
				, NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_ContainerToCopy)
			)
		;

		fg_StrFinish(rReturn);

		return rReturn;
	}
}
