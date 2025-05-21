// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CIterator>
	class TCIterator_UTF8Encode : public t_CIterator
	{
		using CStrippedTags = typename TCRemoveTags
			<
				typename t_CIterator::CTags
				, NIterator::CIteratorTraversal_None
				, NIterator::CIteratorAccess_None
				, NIterator::CIteratorSegmentation_None
				, NIterator::CIteratorValueLifeTime_None
				, NIterator::CIteratorStep_None
			>::CType
		;

		uch8 mp_Values[6];
		uint8 mp_iValue;
		uint8 mp_nValues;
		void fp_EncodeValue(ch32 _Char)
		{
			uch8 *pRet = mp_Values;
			mp_iValue = 0;
			if (_Char >= 0x4000000)
			{
				mp_nValues = 6;
				*pRet = 0xFC | ((_Char >> 30) & 0x01); ++pRet;
				*pRet = 0x80 | ((_Char >> 24) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 18) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else if (_Char >= 0x200000)
			{
				mp_nValues = 5;
				*pRet = 0xF8 | ((_Char >> 24) & 0x03); ++pRet;
				*pRet = 0x80 | ((_Char >> 18) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else if (_Char >= 0x10000)
			{
				mp_nValues = 4;
				*pRet = 0xF0 | ((_Char >> 18) & 0x07); ++pRet;
				*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else if (_Char >= 0x800)
			{
				mp_nValues = 3;
				*pRet = 0xE0 | ((_Char >> 12) & 0x0F); ++pRet;
				*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else if (_Char >= 0x80)
			{
				mp_nValues = 2;
				*pRet = 0xC0 | ((_Char >> 6 ) & 0x1F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else
			{
				mp_nValues = 1;
				*pRet = _Char;
			}
		}
	public:

		using CTags = typename TCAddTags
			<
				CStrippedTags
				, NStr::CIteratorStringEncoding_UTF8
				, NIterator::CIteratorAccess_Readable
				, NIterator::CIteratorTraversal_Forward
				, NIterator::CIteratorStep_OneStep
			>::CType
		;

		using CValueType = uch8;

		template <typename tf_CIterator>
		TCIterator_UTF8Encode(tf_CIterator &&_Iterator)
			: t_CIterator(fg_Forward<tf_CIterator>(_Iterator))
		{
			fp_EncodeValue(t_CIterator::fp_GetValue());
		}

		auto fp_Base() const -> decltype(fg_GetType<t_CIterator const &>().fp_Base())
		{
			return this->t_CIterator::fp_Base();
		}

		NIterator::TCIterator<t_CIterator> fp_ParentIterator() const
		{
			return (t_CIterator const &)(*this);
		}

		void fp_StepForward()
		{
			++mp_iValue;
			if (mp_iValue == mp_nValues)
			{
				t_CIterator::fp_StepForward();
				fp_EncodeValue(t_CIterator::fp_GetValue());
			}
		}

		uch8 fp_GetValue() const
		{
			return mp_Values[mp_iValue];
		}
	};

	namespace NPrivate
	{
		template <typename t_CRange>
		auto fg_Private_RangeAdaptor_UTF8Encode(t_CRange const &_Range, NIterator::CIteratorAccess_Readable)
			-> NIterator::TCRange
			<
				NIterator::TCIterator<TCIterator_UTF8Encode<typename t_CRange::CFront::CImplementation>>
				, NIterator::TCIterator<TCIterator_UTF8Encode<typename t_CRange::CBack::CImplementation>>
			>
		{
			return NIterator::TCRange
				<
					NIterator::TCIterator<TCIterator_UTF8Encode<typename t_CRange::CFront::CImplementation>>
					, NIterator::TCIterator<TCIterator_UTF8Encode<typename t_CRange::CBack::CImplementation>>
				>
				(
					_Range.f_Front().f_Implementation()
					, _Range.f_Back().f_Implementation()
				)
			;
		}

		template <typename t_CRange>
		auto fg_Private_RangeAdaptor_UTF8Encode(t_CRange const &_Range, NIterator::CIteratorAccess_None)
			-> NIterator::TCRange
			<
				NIterator::TCIterator<TCIterator_UTF8Encode<typename t_CRange::CFront::CImplementation>>
				, typename t_CRange::CBack
			>
		{
			return NIterator::TCRange
				<
					NIterator::TCIterator<TCIterator_UTF8Encode<typename t_CRange::CFront::CImplementation>>
					, typename t_CRange::CBack
				>
				(
					_Range.f_Front().f_Implementation()
					, _Range.f_Back()
				)
			;
		}
	}

	template <typename t_CRange>
	auto fg_RangeAdaptor_UTF8Encode(t_CRange const &_Range)
		-> decltype
		(
			NPrivate::fg_Private_RangeAdaptor_UTF8Encode
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
			)
		)
	{
		static_assert(NTraits::cIsConvertible<typename t_CRange::CTagsFront, TCTags<NStr::CIteratorStringEncoding_UTF32>>, "Range must be UTF32 encoded");
		return NPrivate::fg_Private_RangeAdaptor_UTF8Encode
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
			)
		;
	}

}
