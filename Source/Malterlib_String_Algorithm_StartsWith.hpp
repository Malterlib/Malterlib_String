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
			template 
			<
				typename tf_CTags
				, typename tf_CFront
				, typename tf_CBack
				, typename tf_CFrontStartsWith
				, typename tf_CBackStartsWith
			>
			auto fg_Private_StrStartsWith_Algorithm
				(
					NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
					, NIterator::TCRange<tf_CFrontStartsWith, tf_CBackStartsWith> const &_rStartsWith
				) 
#if !DMib_Cxx14
				-> NIterator::TCRangeReturn<bool, typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CBack, tf_CFront, tf_CFront, tf_CTags, NIterator::CReturn_ResBack_Back>::CType>
#endif
			{
				auto rCharacters = fg_GetStringRange<tf_CTags>(_rCharacters);
				auto rCharactersOriginal = rCharacters;
				auto rStartsWith = fg_GetStringRange<tf_CTags>(_rStartsWith);
				
				while (rCharacters && rStartsWith)
				{
					if (!fg_CharIsSame<tf_CTags>(*rCharacters, *rStartsWith))
						break;
					++rCharacters;
					++rStartsWith;
				}
				
				auto iFront = NIterator::fg_ParentIteratorOfType<tf_CFront>(rCharactersOriginal.f_Front());
				auto iBack = NIterator::fg_ParentIteratorOfType<tf_CFront>(rCharacters.f_Front());
				if (TCHasTag<tf_CTags, CReverse>::mc_Value)
				{
					fg_Swap(iFront, iBack);
					++iFront;
					++iBack;
				}
				return NIterator::fg_RangeReturn<tf_CTags, NIterator::CReturn_ResBack_Back>(_rCharacters, fg_Range(iFront, iBack), !rStartsWith);
			}

			template 
			<
				typename tf_CTags
				, typename tf_CFront
				, typename tf_CBack
				, typename tf_CFrontStartsWith
				, typename tf_CBackStartsWith
				, typename tf_CUnicodeTag
			>
			auto fg_Private_StrStartsWith
				(
					NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
					, NIterator::TCRange<tf_CFrontStartsWith, tf_CBackStartsWith> const &_rStartsWith
					, tf_CUnicodeTag // Same
					, tf_CUnicodeTag
				)
#if !DMib_Cxx14
				-> NIterator::TCRangeReturn<bool, typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CBack, tf_CFront, tf_CFront, tf_CTags, NIterator::CReturn_ResBack_Back>::CType>
#endif
			{
				return fg_Private_StrStartsWith_Algorithm<tf_CTags>(_rCharacters, _rStartsWith);
			}

			template 
			<
				typename tf_CTags
				, typename tf_CFront
				, typename tf_CBack
				, typename tf_CFrontStartsWith
				, typename tf_CBackStartsWith
				, typename tf_CUnicodeTag
				, typename tf_CUnicodeTagStartsWith
			>
			auto fg_Private_StrStartsWith
				(
					NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
					, NIterator::TCRange<tf_CFrontStartsWith, tf_CBackStartsWith> const &_rStartsWith
					, tf_CUnicodeTag // Different, need to use unicode
					, tf_CUnicodeTagStartsWith
				)
#if !DMib_Cxx14
				-> NIterator::TCRangeReturn<bool, typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CBack, tf_CFront, tf_CFront, tf_CTags, NIterator::CReturn_ResBack_Back>::CType>
#endif
			{
				using CReturnType = typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CFront, tf_CBack, tf_CFront, tf_CTags>::CType;
				auto rUTFCharacters = fg_RangeAdaptor_UTFDecode(_rCharacters);
				auto rUTFStartsWith = fg_RangeAdaptor_UTFDecode(_rStartsWith);
				auto rFound = fg_Private_StrStartsWith_Algorithm<tf_CTags>(rUTFCharacters, rUTFStartsWith);
				return fg_RangeReturn
					(
						fg_Range
						(
							NIterator::fg_ParentIteratorOfType<typename CReturnType::CFront>(rFound.m_Range.f_Front())
							, NIterator::fg_ParentIteratorOfType<typename CReturnType::CBack>(rFound.m_Range.f_Back())
						)
						, rFound.m_Value
					)
				;
			}
		}
		
		template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontStartsWith, typename tf_CBackStartsWith>
		auto fg_StrStartsWith(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontStartsWith, tf_CBackStartsWith> const &_rStartsWith)
#if !DMib_Cxx14
			-> decltype
			(
				NPrivate::fg_Private_StrStartsWith<TCTags<tfp_CTags...>>
				(
					_rCharacters
					, _rStartsWith
					, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
					, typename TCGetTag<typename tf_CFrontStartsWith::CTags, NStr::CIteratorStringEncoding_None>::CType()
				)		
			)
#endif
		{
			return NPrivate::fg_Private_StrStartsWith<TCTags<tfp_CTags...>>
				(
					_rCharacters
					, _rStartsWith
					, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
					, typename TCGetTag<typename tf_CFrontStartsWith::CTags, NStr::CIteratorStringEncoding_None>::CType()
				)
			;
		}

		template 
		<
			typename ...tfp_CTags
			, typename tf_CContainer
			, typename tf_CContainerStartsWith
			, typename TCEnableIf
			<
				!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
				|| !NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerStartsWith>::CType>::mc_Value
			>::CType * DMib_EnableIfDefault
		>
		auto fg_StrStartsWith(tf_CContainer &&_Container, tf_CContainerStartsWith &&_ContainerStartsWith)
#if !DMib_Cxx14
			-> decltype
			(
				NStr2::fg_StrStartsWith<tfp_CTags...>
				(
					NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_Container)
					, NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_ContainerStartsWith)
				)		
			)
#endif
		{
			return NStr2::fg_StrStartsWith<tfp_CTags...>
				(
					NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_Container)
					, NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_ContainerStartsWith)
				)
			;
		}
	}
}
