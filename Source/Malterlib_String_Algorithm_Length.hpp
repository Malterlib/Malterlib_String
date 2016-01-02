// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/AlgorithmModifiers>

namespace NMib
{
	namespace NStr2
	{
		namespace NPrivate
		{
			template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
			mint fg_Private_StrLength_Algorithm(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::CIteratorDistance_Supported, NIterator::CIteratorDistance_Supported)
			{
				return _rCharacters.f_Distance();
			}
			template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
			mint fg_Private_StrLength_Algorithm(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::CIteratorDistance_None, NIterator::CIteratorDistance_None)
			{
				auto rCharacters = _rCharacters;
				mint Len = 0;
				while (rCharacters)
				{
					++Len;
					++rCharacters;
				}
				return Len;
			}

			template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
			mint fg_Private_StrLength1(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters)
			{
				return fg_Private_StrLength_Algorithm<tf_CTags>
					(
						_rCharacters
						, typename TCGetTag<typename tf_CFront::CTags, NIterator::CIteratorDistance_None>::CType()
						, typename TCGetTag<typename tf_CBack::CTags, NIterator::CIteratorDistance_None>::CType()
					)
				;
			}
			
			template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
			mint fg_Private_StrLength(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, CUnicode)
			{
				auto rCharacters = fg_RangeAdaptor_UTFDecode(_rCharacters);
				return fg_Private_StrLength1<tf_CTags>(rCharacters);
			}
			template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
			mint fg_Private_StrLength(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, CUnicodeBase)
			{
				return fg_Private_StrLength1<tf_CTags>(_rCharacters);
			}
		}
		
		template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
		mint fg_StrLength(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters)
		{
			return NPrivate::fg_Private_StrLength<TCTags<tfp_CTags...>>(_rCharacters, typename TCGetTag<TCTags<tfp_CTags...>, CUnicodeBase>::CType());
		}

		template
		<
			typename ...tfp_CTags
			, typename tf_CContainer
			, typename TCEnableIf
			<
				!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
			>::CType *
		>
		mint fg_StrLength(tf_CContainer &&_Container)
		{
			auto rCharacters = NIterator::fg_Range
				<
					NMeta::TCTypeList
					<
						TCTags<NIterator::CIteratorDistance_Supported, NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>
						, TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>
					>
					, NMeta::TCTypeList
					<
						TCTags<NIterator::CIteratorDistance_Supported, NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>
						, TCTags<>
					>
				>
				(
					fg_Forward<tf_CContainer>(_Container)
				)
			;
			return NStr2::fg_StrLength<tfp_CTags...>(rCharacters);
		}
	}
}
