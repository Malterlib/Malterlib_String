// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CIterator, typename t_CBackIterator>
	class TCIterator_UTF8EncodeOutput : public t_CIterator
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
			uch8 Data[6];
			uch8 *pRet = Data;
			mint nValues = 6;
			if (_Char >= 0x4000000)
			{
				nValues = 6;
				*pRet = 0xFC | ((_Char >> 30) & 0x01); ++pRet;
				*pRet = 0x80 | ((_Char >> 24) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 18) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else if (_Char >= 0x200000)
			{
				nValues = 5;
				*pRet = 0xF8 | ((_Char >> 24) & 0x03); ++pRet;
				*pRet = 0x80 | ((_Char >> 18) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else if (_Char >= 0x10000)
			{
				nValues = 4;
				*pRet = 0xF0 | ((_Char >> 18) & 0x07); ++pRet;
				*pRet = 0x80 | ((_Char >> 12) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else if (_Char >= 0x800)
			{
				nValues = 3;
				*pRet = 0xE0 | ((_Char >> 12) & 0x0F); ++pRet;
				*pRet = 0x80 | ((_Char >> 6 ) & 0x3F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else if (_Char >= 0x80)
			{
				nValues = 2;
				*pRet = 0xC0 | ((_Char >> 6 ) & 0x1F); ++pRet;
				*pRet = 0x80 | ((_Char >> 0 ) & 0x3F); ++pRet;
			}
			else
			{
				mp_LastValid = (t_CIterator const &)*this;
				mp_LastValid.fp_StepForward();
				t_CIterator::fp_SetValue(_Char);
				return;
			}

			mp_LastValid = (t_CIterator const &)*this;
			for (mint i = 0; i < nValues - 1; ++i)
			{
				t_CIterator::fp_SetValue(Data[i]);
				auto Prev = (t_CIterator const &)*this;
				t_CIterator::fp_StepForward();
				if (t_CIterator::fp_Equal(mp_Back.fp_Base()))
				{
					(t_CIterator &)(*this) = Prev;
					return;
				}
			}
			t_CIterator::fp_SetValue(Data[nValues - 1]);
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
		TCIterator_UTF8EncodeOutput(t_CIterator const &_Iterator, tf_CBackIterator &&_BackIterator)
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
	auto fg_Private_RangeAdaptor_UTF8EncodeOutput(t_CRange const &_Range, NIterator::CIteratorAccess_None)
		-> NIterator::TCRange
		<
			NIterator::TCIterator<TCIterator_UTF8EncodeOutput<typename t_CRange::CFront::CImplementation, typename t_CRange::CBack::CImplementation>>
			, typename t_CRange::CBack
		>
	{
		return NIterator::TCRange
			<
				NIterator::TCIterator<TCIterator_UTF8EncodeOutput<typename t_CRange::CFront::CImplementation, typename t_CRange::CBack::CImplementation>>
				, typename t_CRange::CBack
			>
			(
				NIterator::TCIterator<TCIterator_UTF8EncodeOutput<typename t_CRange::CFront::CImplementation, typename t_CRange::CBack::CImplementation>>(_Range.f_Front().f_Implementation(), _Range.f_Back().f_Implementation())
				, _Range.f_Back()
			)
		;
	}
}

namespace NMib::NStr
{
	template <typename t_CRange>
	auto fg_RangeAdaptor_UTF8EncodeOutput(t_CRange const &_Range)
		-> decltype
		(
			NPrivate::fg_Private_RangeAdaptor_UTF8EncodeOutput
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
			)
		)
	{
//			static_assert(NTraits::TCIsConvertible<typename t_CRange::CTagsFront, TCTags<NStr::CIteratorStringEncoding_UTF32>>::mc_Value, "Range must be UTF32 encoded");
		return NPrivate::fg_Private_RangeAdaptor_UTF8EncodeOutput
			(
				_Range
				, typename TCGetTag<typename t_CRange::CTagsBack, NIterator::CIteratorAccess_None>::CType()
			)
		;
	}
}
