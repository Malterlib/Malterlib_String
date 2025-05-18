// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CIterator, typename t_CBackIterator>
	class TCIterator_UTF16EncodeOutput : public t_CIterator
	{
		typedef typename TCRemoveTags
			<
				typename t_CIterator::CTags
				, NIterator::CIteratorTraversal_None
				, NIterator::CIteratorAccess_None
				, NIterator::CIteratorSegmentation_None
				, NIterator::CIteratorValueLifeTime_None
				, NIterator::CIteratorStep_None
			>::CType CStrippedTags
		;

		t_CBackIterator mp_Back;
		t_CIterator mp_LastValid;

		void fp_EncodeValue(ch32 _Char)
		{

			if (_Char > 0xFFFF)
			{
				_Char -= 0x10000;

				uint32 vh = _Char >> 10;
				uint32 v1 = _Char & 0x3FF;
				uint32 w1 = 0xD800 + vh;
				uint32 w2 = 0xDC00 + v1;

				mp_LastValid = (t_CIterator const &)*this;
				t_CIterator::fp_SetValue(w1);
				auto Prev = (t_CIterator const &)*this;
				t_CIterator::fp_StepForward();
				if (t_CIterator::fp_Equal(mp_Back.fp_Base()))
				{
					(t_CIterator &)(*this) = Prev;
					return;
				}
				t_CIterator::fp_SetValue(w2);
			}
			else
			{
				mp_LastValid = (t_CIterator const &)*this;
				mp_LastValid.fp_StepForward();
				t_CIterator::fp_SetValue(_Char);
			}
		}
	public:

		typedef typename TCAddTags
			<
				CStrippedTags
				, NStr::CIteratorStringEncoding_UTF32
				, NIterator::CIteratorAccess_Writable
				, NIterator::CIteratorTraversal_Forward
				, NIterator::CIteratorStep_OneStep
			>::CType CTags
		;

		typedef uch8 CValueType;


		template <typename tf_CBackIterator>
		TCIterator_UTF16EncodeOutput(t_CIterator const &_Iterator, tf_CBackIterator &&_BackIterator)
			: t_CIterator(_Iterator)
			, mp_LastValid(_Iterator)
			, mp_Back(fg_Forward<tf_CBackIterator>(_BackIterator))
		{
		}

		auto fp_Base() const -> decltype(fg_GetType<t_CIterator const &>().fp_Base())
		{
			return this->t_CIterator::fp_Base();
		}

		NIterator::TCIterator<t_CIterator> fp_ParentIterator() const
		{
			return mp_LastValid;
		}

		void fp_StepForward()
		{
			t_CIterator::fp_StepForward();
		}

		void fp_SetValue(ch32 _Value) const
		{
			fg_RemoveQualifiers(*this).fp_EncodeValue(_Value);
		}
	};
}

namespace NMib::NStr::NPrivate
{
	template <typename t_CRange>
	auto fg_Private_RangeAdaptor_UTF16EncodeOutput(t_CRange const &_Range, NIterator::CIteratorAccess_None)
		-> NIterator::TCRange
		<
			NIterator::TCIterator<TCIterator_UTF16EncodeOutput<typename t_CRange::CFront::CImplementation, typename t_CRange::CBack::CImplementation>>
			, typename t_CRange::CBack
		>
	{
		return NIterator::TCRange
			<
				NIterator::TCIterator<TCIterator_UTF16EncodeOutput<typename t_CRange::CFront::CImplementation, typename t_CRange::CBack::CImplementation>>
				, typename t_CRange::CBack
			>
			(
				NIterator::TCIterator<TCIterator_UTF16EncodeOutput<typename t_CRange::CFront::CImplementation, typename t_CRange::CBack::CImplementation>>(_Range.f_Front().f_Implementation(), _Range.f_Back().f_Implementation())
				, _Range.f_Back()
			)
		;
	}
}

namespace NMib::NStr
{
	template <typename t_CRange>
	auto fg_RangeAdaptor_UTF16EncodeOutput(t_CRange const &_Range)
		-> decltype
		(
			NPrivate::fg_Private_RangeAdaptor_UTF16EncodeOutput
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
			)
		)
	{
//			static_assert(NTraits::cIsConvertible<typename t_CRange::CTagsFront, TCTags<NStr::CIteratorStringEncoding_UTF32>>, "Range must be UTF32 encoded");
		return NPrivate::fg_Private_RangeAdaptor_UTF16EncodeOutput
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
			)
		;
	}
}
