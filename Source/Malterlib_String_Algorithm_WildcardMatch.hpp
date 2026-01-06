// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/AlgorithmModifiers>
#include <Mib/String/Algorithms/FindChars>
#include <Mib/String/Algorithms/StartsWith>
#include <Mib/Iterator/RangeSet>

namespace NMib::NStr2::NPrivate
{
	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToMatch
		, typename tf_CBackToMatch
	>
	auto fg_Private_StrWildcardMatch_Algorithm
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NIterator::TCRange<tf_CFrontToMatch, tf_CBackToMatch> const &_rToMatch
		)
	{
		auto rParse = _rCharacters;
		auto rPattern = _rToMatch;

		while (rParse && rPattern)
		{
			if (*rPattern == '*')
			{
				while (*rPattern == '*')
					++rPattern;
				auto rMax = fg_StrFindChars(rPattern, "*?");
				if (rMax)
				{
					auto rCompare = NIterator::fg_RangeDifferenceAB(rPattern, rMax);
					while (rParse)
					{
						if (NStr2::fg_StrStartsWith<tf_CTags>(rParse, rCompare))
							break;
						++rParse;
					}
				}
				else
				{
					while (rParse)
					{
						if (NStr2::fg_StrStartsWith<tf_CTags>(rParse, rPattern))
							break;
						++rParse;
					}
				}
			}
			else if (*rPattern == '?')
			{
				++rPattern;
				++rParse;
			}
			else
			{
				if (!fg_CharIsSame<tf_CTags>(*rPattern, *rParse))
					break;
				++rPattern;
				++rParse;
			}
		}
		while (*rPattern == '*')
			++rPattern;

		EWildcardMatch Match;

		if (!rParse && !rPattern)
			Match = EWildcardMatch_WholeStringMatchedAndPatternExhausted;
		else if (!rPattern)
			Match = EWildcardMatch_PatternExhausted;
		else if (!rParse)
			Match = EWildcardMatch_WholeStringMatched;
		else
			Match = EWildcardMatch_NotMatched;

		return NIterator::fg_RangeReturn<tf_CTags, NIterator::CReturn_ResBack_Back>(_rCharacters, fg_Range(_rCharacters.f_Front(), rParse.f_Front()), Match);
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
		, typename tf_CFrontToMatch
		, typename tf_CBackToMatch
	>
	auto fg_Private_StrWildcardMatch
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NIterator::TCRange<tf_CFrontToMatch, tf_CBackToMatch> const &_rToMatch
		)
	{
		using CReturnType = typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CFront, tf_CBack, tf_CFront, tf_CTags>::CType;
		// We always need to use unicode to handle ? correctly
		auto rUTFCharacters = fg_RangeAdaptor_UTFDecode(_rCharacters);
		auto rUTFToMatch = fg_RangeAdaptor_UTFDecode(_rToMatch);
		auto Found = fg_Private_StrWildcardMatch_Algorithm<tf_CTags>(rUTFCharacters, rUTFToMatch);
		return fg_RangeReturn
			(
				fg_Range
				(
					NIterator::fg_ParentIteratorOfType<typename CReturnType::CFront>(Found.m_Range.f_Front())
					, NIterator::fg_ParentIteratorOfType<typename CReturnType::CBack>(Found.m_Range.f_Back())
				)
				, Found.m_Value
			)
		;
	}
}

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToMatch, typename tf_CBackToMatch>
	auto fg_StrWildcardMatch(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontToMatch, tf_CBackToMatch> const &_rToMatch)
	{
		return NPrivate::fg_Private_StrWildcardMatch<TCTags<tfp_CTags...>>
			(
				_rCharacters
				, _rToMatch
			)
		;
	}

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerToMatch
		, TCEnableIf
		<
			!NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>>
			|| !NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToMatch>>
		> *
	>
	auto fg_StrWildcardMatch(tf_CContainer &&_Container, tf_CContainerToMatch &&_ContainerToMatch)
	{
		return NStr2::fg_StrWildcardMatch<tfp_CTags...>
			(
				NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_Container)
				, NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_ContainerToMatch)
			)
		;
	}
}
