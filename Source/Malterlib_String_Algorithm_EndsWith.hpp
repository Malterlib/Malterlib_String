// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_String_Algorithm_Common.h"
#include "Malterlib_String_Algorithm_StartsWith.h"

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack, typename tf_CFrontEndWith, typename tf_CBackEndsWith>
	auto fg_StrEndsWith(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, NIterator::TCRange<tf_CFrontEndWith, tf_CBackEndsWith> const &_rEndsWith)
	{
		return NPrivate::fg_Private_StrStartsWith
			<
				TCConditional
				<
					TCHasTag<TCTags<tfp_CTags...>, CReverse>::mc_Value
					, typename TCRemoveTags<TCTags<tfp_CTags...>, CReverseBase>::CType
					, TCTags<CReverse, tfp_CTags...>
				>
			>
			(
				_rCharacters
				, _rEndsWith
				, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
				, typename TCGetTag<typename tf_CFrontEndWith::CTags, NStr::CIteratorStringEncoding_None>::CType()
			)
		;
	}

	template
	<
		typename ...tfp_CTags
		, typename tf_CContainer
		, typename tf_CContainerEndsWith
		, TCEnableIf
		<
			!NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainer>>
			|| !NIterator::cIsRange<NTraits::TCRemoveReferenceAndQualifiers<tf_CContainerEndsWith>>
		> *
	>
	auto fg_StrEndsWith(tf_CContainer &&_Container, tf_CContainerEndsWith &&_ContainerStartsWith)
	{
		return NStr2::fg_StrEndsWith<tfp_CTags...>
			(
				NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_Container)
				, NIterator::fg_Range<NMeta::TCTypeList<TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>>>(_ContainerStartsWith)
			)
		;
	}
}
