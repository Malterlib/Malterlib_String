// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/AlgorithmModifiers>

namespace NMib::NStr2::NPrivate
{
	template <typename tf_CTags, typename tf_CFront, typename tf_CBack, typename tf_CChar, typename tf_CUnicodeTag>
	auto fg_Private_StrFindChar(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, tf_CChar _Character, tf_CUnicodeTag, tf_CUnicodeTag) // Same tags, no conversion
	{
		typename NTraits::TCUnsigned<tf_CChar>::CType Character = _Character;
		auto rCharacters = fg_GetStringRange<tf_CTags>(_rCharacters);
		while (rCharacters)
		{
			if (fg_CharIsSame<tf_CTags>(*rCharacters, Character))
				break;
			++rCharacters;
		}
		if (rCharacters)
		{
			auto iFoundEnd = rCharacters.f_Front();
			++iFoundEnd;
			return NIterator::fg_RangeReturn<tf_CTags>
				(
					_rCharacters
					, fg_Range
					(
						NIterator::fg_ParentIteratorOfType<tf_CFront>(rCharacters.f_Front())
						, NIterator::fg_ParentIteratorOfType<tf_CFront>(iFoundEnd)
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
		, typename tf_CChar
		, typename tf_CUnicodeTag
		, typename TCEnableIf<!NTraits::TCIsSame<tf_CUnicodeTag, NMib::NStr::CIteratorStringEncoding_UTF32>::mc_Value>::CType * = nullptr
	>
	auto fg_Private_StrFindChar
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, tf_CChar _Character
			, tf_CUnicodeTag
			, NMib::NStr::CIteratorStringEncoding_UTF32 // Need conversion to UTF32
		)
	{
		using CReturnType = typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CBack, tf_CFront, tf_CFront, tf_CTags>::CType;
		auto rUTFCharacters = fg_RangeAdaptor_UTFDecode(_rCharacters);
		auto rFound = fg_Private_StrFindChar<tf_CTags>(rUTFCharacters, _Character, NMib::NStr::CIteratorStringEncoding_UTF32(), NMib::NStr::CIteratorStringEncoding_UTF32());
		return fg_Range
			(
				NIterator::fg_ParentIteratorOfType<typename CReturnType::CFront>(rFound.f_Front())
				, NIterator::fg_ParentIteratorOfType<typename CReturnType::CBack>(rFound.f_Back())
			)
		;
	}

	template <typename tf_CTags, typename tf_CFront, typename tf_CBack, typename tf_CChar, typename tf_CUnicodeTag0, typename tf_CUnicodeTag1>
	auto fg_Private_StrFindChar(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, tf_CChar _Character, tf_CUnicodeTag0, tf_CUnicodeTag1) // Not a valid conversion
		-> typename NIterator::TCGetRangeReturnType<tf_CFront, tf_CBack, tf_CFront, tf_CFront, tf_CTags>::CType
	{
		static_assert
			(
				NTraits::TCIsVoid<tf_CFront>::mc_Value
				, "This character type does not make sense to search for in this container. "
				"You either need to search for the same character type as the container, or search for a UTF32 character (ch32)"
			)
		;
	}
}
		
namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CChar>
	auto fg_StrFindChar(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, tf_CChar _Character)
	{
		return NPrivate::fg_Private_StrFindChar<TCTags<tfp_CTags...>>
			(
				_rCharacters
				, _Character
				, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
				, typename NStr::TCGetIteratorUnicodeFromChar<tf_CChar>::CType()
			)
		;
	}

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CChar
		, typename TCEnableIf
		<
			!NIterator::TCIsRange<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>::CType>::mc_Value
		>::CType *
	>
	auto fg_StrFindChar(tf_CContainer &_Container, tf_CChar _Character)
	{
		return NStr2::fg_StrFindChar<tfp_CTags...>
			(
				NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_Container)
				, _Character
			)
		;
	}
}
