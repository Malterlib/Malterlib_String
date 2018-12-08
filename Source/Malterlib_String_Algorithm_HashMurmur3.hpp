// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>

#include <Mib/String/Iterator>
#include <Mib/String/IteratorUnicode>
#include <Mib/String/IteratorUTF8Encode>
#include <Mib/String/AlgorithmModifiers>
#include <Mib/Bit/Rotate>

namespace NMib::NStr2::NPrivate
{
	class CMurmurHash3
	{
		mint mp_Length;
		uint32 mp_Hash;
		union
		{
			uint8 mp_Block[4];
			uint32 mp_Block32;
		};

		static uint32 const mcp_Constant1 = 0xcc9e2d51;
		static uint32 const mcp_Constant2 = 0x1b873593;

		void fp_AddBlock(uint32 _Block);
	public:
		CMurmurHash3(uint32 _Seed);
		uint32 f_GetHash() const;
		inline_always void f_AddByte(uint8 _Byte)
		{
			mp_Block[mp_Length & 0x3] = _Byte;
			++mp_Length;
			if ((mp_Length & 0x3) == 0)
				fp_AddBlock(NMib::fg_ByteSwapLE(mp_Block32));
		}
	};

	uint32 fg_MurmurHash3_x86_32(const void * _pData, mint _Length, uint32 _Seed);

	template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
	uint32 fg_Private_StrHashMurmur3
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, uint32 _Seed
			, NStr::CIteratorStringEncoding_UTF8
			, NIterator::CIteratorAccess_Readable
			, NIterator::CIteratorStep_OneStep
			, NIterator::CIteratorDistance_None
			, NIterator::CIteratorDistance_None
		)
	{
		CMurmurHash3 Hash(_Seed);

		auto rCharacters = _rCharacters;
		while (rCharacters)
		{
			Hash.f_AddByte(*rCharacters);
			++rCharacters;
		}
		return Hash.f_GetHash();
	}

	template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
	uint32 fg_Private_StrHashMurmur3
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, uint32 _Seed
			, NStr::CIteratorStringEncoding_None
			, NIterator::CIteratorAccess_Readable
			, NIterator::CIteratorStep_OneStep
			, NIterator::CIteratorDistance_None
			, NIterator::CIteratorDistance_None
		)
	{
		// Need to convert to UTF8
		auto rUTF8Chars = fg_RangeAdaptor_UTF8Encode(fg_RangeAdaptor_UTFDecode(_rCharacters));
		return fg_Private_StrHashMurmur3<tf_CTags>
			(
				rUTF8Chars
				, _Seed
				, NStr::CIteratorStringEncoding_UTF8()
				, NIterator::CIteratorAccess_Readable()
				, NIterator::CIteratorStep_OneStep()
				, NIterator::CIteratorDistance_None()
				, NIterator::CIteratorDistance_None()
			)
		;
	}

	template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
	uint32 fg_Private_StrHashMurmur3
		(
			NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters
			, uint32 _Seed
			, NStr::CIteratorStringEncoding_UTF8
			, NIterator::CIteratorAccess_ConstLValueArray
			, NIterator::CIteratorStep_Random
			, NIterator::CIteratorDistance_Supported
			, NIterator::CIteratorDistance_Supported
		)
	{
		return fg_MurmurHash3_x86_32(&(*_rCharacters), _rCharacters.f_Distance(), _Seed);
	}
}
		
namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
	uint32 fg_StrHashMurmur3(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, uint32 _Seed)
	{
		return NPrivate::fg_Private_StrHashMurmur3<TCTags<tfp_CTags...>>
			(
				_rCharacters
				, _Seed
				, typename TCGetTag<typename tf_CFront::CTags, NStr::CIteratorStringEncoding_None>::CType()
				, typename TCGetTag<typename tf_CFront::CTags, NIterator::CIteratorAccess_None>::CType()
				, typename TCGetTag<typename tf_CFront::CTags, NIterator::CIteratorStep_None>::CType()
				, typename TCGetTag<typename tf_CFront::CTags, NIterator::CIteratorDistance_None>::CType()
				, typename TCGetTag<typename tf_CBack::CTags, NIterator::CIteratorDistance_None>::CType()
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
	uint32 fg_StrHashMurmur3(tf_CContainer &&_Container, uint32 _Seed)
	{
		auto rCharacters = NIterator::fg_Range
			<
				NMeta::TCTypeList
				<
					TCTags<NStr::CIteratorStringEncoding_UTF8, NIterator::CIteratorAccess_ConstLValueArray, NIterator::CIteratorStep_Random, NIterator::CIteratorDistance_Supported>
					, TCTags<NIterator::CIteratorTraversal_Forward, NIterator::CIteratorAccess_Readable>
				>
				, NMeta::TCTypeList
				<
					TCTags<NIterator::CIteratorDistance_Supported>
					, TCTags<>
				>
			>
			(
				fg_Forward<tf_CContainer>(_Container)
			)
		;
		return NStr2::fg_StrHashMurmur3<tfp_CTags...>(rCharacters, _Seed);
	}
}
