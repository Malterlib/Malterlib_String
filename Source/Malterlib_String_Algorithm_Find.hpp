// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/Algorithm/ForEachAbortable>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/AlgorithmModifiers>

namespace NMib
{
	namespace NStr2
	{
		namespace NPrivate
		{
			template 
			<
				typename tf_CTags
				, typename tf_CFront
				, typename tf_CBack
				, typename tf_CFrontToFind
				, typename tf_CBackToFind
			>
			auto fg_Private_StrFind_Algorithm
				(
					NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
					, NIterator::TCRange<tf_CFrontToFind, tf_CBackToFind> const &_rToFind
				) 
			{
				auto rCharacters = fg_GetStringRange<tf_CTags>(_rCharacters);
				auto rLastFoundEnd = rCharacters;
				auto rToFind = fg_GetStringRange<tf_CTags>(_rToFind);
				bool bFound = false;

				while (rCharacters)
				{
					auto rToFindCurrent = rToFind;

					rLastFoundEnd = NAlgorithm::fg_ForEachAbortable
						(
							rCharacters
							, [&](decltype(*rCharacters) _Value) 
							{
								if (!fg_CharIsSame<tf_CTags>(_Value, *rToFindCurrent))
									return false;
								++rToFindCurrent;
								if (!rToFindCurrent)
								{
									bFound = true;
									return false;
								}
								return true;
							}
						)
					;
					
					if (bFound)
						break;
					
					++rCharacters;
				}

				if (bFound)
				{
					if (TCHasTag<tf_CTags, CReverse>::mc_Value)
						fg_Swap(rCharacters, rLastFoundEnd);
					++rLastFoundEnd;
					return NIterator::fg_RangeReturn<tf_CTags>
						(
							_rCharacters
							, fg_Range
							(
								NIterator::fg_ParentIteratorOfType<tf_CFront>(rCharacters.f_Front())
								, NIterator::fg_ParentIteratorOfType<tf_CFront>(rLastFoundEnd.f_Front())
							)
						)
					;
				}
				else
				{
					return NIterator::fg_RangeReturn<tf_CTags>
						(
							fg_Range
							(
								NIterator::fg_ParentIteratorOfType<tf_CFront>(rCharacters.f_Front())
								, _rCharacters.f_Back()
							)
							, fg_Range
							(
								NIterator::fg_ParentIteratorOfType<tf_CFront>(rCharacters.f_Front())
								, NIterator::fg_ParentIteratorOfType<tf_CFront>(rCharacters.f_Front())
							)
						)
					;
				}
			}

			template 
			<
				typename tf_CTags
				, typename tf_CFront
				, typename tf_CBack
				, typename tf_CFrontToFind
				, typename tf_CBackToFind
				, typename tf_CUnicodeTag
			>
			auto fg_Private_StrFind
				(
					NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
					, NIterator::TCRange<tf_CFrontToFind, tf_CBackToFind> const &_rToFind
					, tf_CUnicodeTag // Same
					, tf_CUnicodeTag
				)
			{
				return fg_Private_StrFind_Algorithm<tf_CTags>(_rCharacters, _rToFind);
			}

			template 
			<
				typename tf_CTags
				, typename tf_CFront
				, typename tf_CBack
				, typename tf_CFrontToFind
				, typename tf_CBackToFind
				, typename tf_CUnicodeTag
				, typename tf_CUnicodeTagToFind
			>
			auto fg_Private_StrFind
				(
					NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
					, NIterator::TCRange<tf_CFrontToFind, tf_CBackToFind> const &_rToFind
					, tf_CUnicodeTag // Different, need to use unicode
					, tf_CUnicodeTagToFind
				)
			{
				using CReturnType = typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CBack, tf_CFront, tf_CFront, tf_CTags>::CType;
				auto rUTFCharacters = fg_RangeAdaptor_UTFDecode(_rCharacters);
				auto rUTFToFind = fg_RangeAdaptor_UTFDecode(_rToFind);
				auto rFound = fg_Private_StrFind_Algorithm<tf_CTags>(rUTFCharacters, rUTFToFind);
				return fg_Range
					(
						NIterator::fg_ParentIteratorOfType<typename CReturnType::CFront>(rFound.f_Front())
						, NIterator::fg_ParentIteratorOfType<typename CReturnType::CBack>(rFound.f_Back())
					)
				;
			}
		}
		
		template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontToFind, typename tf_CBackToFind>
		auto fg_StrFind(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontToFind, tf_CBackToFind> const &_rToFind)
		{
			return NPrivate::fg_Private_StrFind<TCTags<tfp_CTags...>>
				(
					_rCharacters
					, _rToFind
					, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
					, typename TCGetTag<typename tf_CFrontToFind::CTags, NStr::CIteratorStringEncoding_None>::CType()
				)
			;
		}

		template
		<
			typename ...tfp_CTags
			, typename tf_CContainer
			, typename tf_CContainerToFind
			, typename TCEnableIf
			<
				!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
				|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerToFind>::CType>::mc_Value
			>::CType *
		>
		auto fg_StrFind(tf_CContainer &&_Container, tf_CContainerToFind &&_ContainerToFind)
		{
			return NStr2::fg_StrFind<tfp_CTags...>
				(
					NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_Container)
					, NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_ContainerToFind)
				)
			;
		}
	}
}

