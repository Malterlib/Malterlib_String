// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/IteratorUTF8Encode>
#include <Mib/String/AlgorithmModifiers>

namespace NMib
{
	namespace NStr2
	{
		namespace NPrivate
		{
			template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
			uint32 fg_Private_StrHashDJB2(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NStr::CIteratorStringEncoding_UTF8) // Same tags, no conversion
			{
				uint32 Hash = 5381;
				
				auto rCharacters = _rCharacters;
				while (rCharacters)
				{
					Hash = Hash * 33 + *rCharacters;
					++rCharacters;
				}
				return Hash;
			}
			template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
			uint32 fg_Private_StrHashDJB2(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NStr::CIteratorStringEncoding_None)
			{
				// Need to convert to UTF8
				auto rUTF8Chars = fg_RangeAdaptor_UTF8Encode(fg_RangeAdaptor_UTFDecode(_rCharacters));
				return fg_Private_StrHashDJB2<tf_CTags>(rUTF8Chars, NStr::CIteratorStringEncoding_UTF8());
			}
		}
		
		template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
		uint32 fg_StrHashDJB2(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters)
		{
			return NPrivate::fg_Private_StrHashDJB2<TCTags<tfp_CTags...>>
				(
					_rCharacters
					, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
				)
			;
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
		uint32 fg_StrHashDJB2(tf_CContainer &&_Container)
		{
			auto rCharacters = NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>
				(
					fg_Forward<tf_CContainer>(_Container)
				)
			;
			return NStr2::fg_StrHashDJB2<tfp_CTags...>(rCharacters);
		}
	}
}
