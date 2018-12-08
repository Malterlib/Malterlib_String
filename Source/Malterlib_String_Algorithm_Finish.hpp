// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/String/Iterator>

namespace NMib::NStr2::NPrivate
{
	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
	>
	void fg_Private_StrFinishNullTermination
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NStr::CIteratorStringNullTermination_Required
		)
	{
		*_rCharacters = 0;
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
	>
	void fg_Private_StrFinishNullTermination
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, NStr::CIteratorStringNullTermination_None
		)
	{
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
	>
	void fg_Private_StrFinishUTF
		(
			NIterator::TCRange<tf_CFront, tf_CBack> &_rCharacters
			, NIterator::CIteratorTraversal_Both
			, NStr::CIteratorStringEncoding_UTF8
		)
	{
		auto rCharacters = _rCharacters;

		--rCharacters;
		mint nUTF = 0;
		while ((*rCharacters & 0xC0) == 0x80)
		{
			++nUTF;
			--rCharacters;
		}
		if ((*rCharacters & 0xC0) == 0xC0)
		{
			++nUTF;
			smint nChars = 7-fg_GetHighestBitSet((~uint32(*rCharacters))&0xFF);

			if (nChars != nUTF) // Unfinished codepoint
				_rCharacters = rCharacters;
		}
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
	>
	void fg_Private_StrFinishUTF
		(
			NIterator::TCRange<tf_CFront, tf_CBack> &_rCharacters
			, NIterator::CIteratorTraversal_Both
			, NStr::CIteratorStringEncoding_UTF16
		)
	{
		auto rCharacters = _rCharacters;

		--rCharacters;
		if ((*rCharacters & 0xFC00) == 0xD800) // Unfinished codepoint
			_rCharacters = rCharacters;
	}

	template
	<
		typename tf_CTags
		, typename tf_CFront
		, typename tf_CBack
	>
	void fg_Private_StrFinishUTF
		(
			NIterator::TCRange<tf_CFront, tf_CBack> &_rCharacters
			, NIterator::CIteratorTraversal_None
			, NStr::CIteratorStringEncoding_None
		)
	{
	}

}

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
	void fg_StrFinish(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters)
	{
		auto rCharacters = _rCharacters;
		NPrivate::fg_Private_StrFinishUTF<TCTags<tfp_CTags...>>
			(
				rCharacters
				, typename TCGetTag<typename tf_CFront::CTags, NIterator::CIteratorTraversal_None>::CType()
				, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
			)
		;
		NPrivate::fg_Private_StrFinishNullTermination<TCTags<tfp_CTags...>>
			(
				rCharacters
				, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringNullTermination_None>::CType()
			)
		;
	}
}
