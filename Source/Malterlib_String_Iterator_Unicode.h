// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/String/Iterator>

#include "Private/Malterlib_String_Iterator_Unicode_Private.h"

namespace NMib::NStr
{
	static constexpr ch32 g_InvalidCodepoint = TCLimitsInt<ch32>::mc_Max;
	static constexpr ch32 g_IncompleteCodepoint = TCLimitsInt<ch32>::mc_Max - 1;

	template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
	class TCIterator_UTF8Adaptor
	{
	public:
		using CTags = TCTags
			<
				NIterator::CIteratorStep_OneStep
				, NIterator::CIteratorTraversal_Forward
				, NIterator::CIteratorValueLifeTime_None
				, NIterator::CIteratorCopy_Copy
				, NIterator::CIteratorConstruct_None
				, NIterator::CIteratorAccess_Readable
				, NStr::CIteratorStringEncoding_UTF32
			>
		;

		using CValueType = ch32;

		TCIterator_UTF8Adaptor(t_CBaseIterator const &_iCurrent, t_CBaseIteratorBack const &_iBack);

		bool f_IsBroken() const;
		bool f_IsComplete() const;

		TCIterator_UTF8Adaptor f_Invalid() const
		{
			return TCIterator_UTF8Adaptor(this->mp_iCurrent.f_Invalid(), this->mp_iBack.f_Invalid());
		}

	public:
		void fp_StepForward();
		ch32 fp_GetValue() const;
		template <typename tf_CIterator>
		bool fp_Equal(tf_CIterator const &_Right) const;
		t_CBaseIterator const &fp_ParentIterator() const;

		NIterator::TCRange<t_CBaseIterator, t_CBaseIteratorBack> fp_TempRange();
		void fp_ParseBOM();
		ch32 fp_Next();


	protected:
		t_CBaseIterator mp_iCurrent;
		t_CBaseIterator mp_iNext;

		t_CBaseIteratorBack mp_iBack;

		ch32 mp_Current;

	public:
		auto fp_Base() const -> decltype(fg_GetType<t_CBaseIterator const &>().f_Base());
	};

	template <typename t_CBaseIterator, typename t_CBaseIteratorFront, typename t_CBaseIteratorBack>
	class TCIterator_UTF8AdaptorWithBackward : public TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>
	{
	public:
		using CTags = TCTags
			<
				NIterator::CIteratorStep_OneStep
				, NIterator::CIteratorTraversal_Both
				, NIterator::CIteratorValueLifeTime_None
				, NIterator::CIteratorCopy_Copy
				, NIterator::CIteratorConstruct_None
				, NIterator::CIteratorAccess_Readable
				, NStr::CIteratorStringEncoding_UTF32
			>
		;

		TCIterator_UTF8AdaptorWithBackward(t_CBaseIterator const &_iCurrent, t_CBaseIteratorFront const &_iFront, t_CBaseIteratorBack const &_iBack);

		TCIterator_UTF8AdaptorWithBackward f_Invalid() const
		{
			return TCIterator_UTF8AdaptorWithBackward(this->mp_iCurrent.f_Invalid(), mp_iFront.f_Invalid(), this->mp_iBack.f_Invalid());
		}
	public:
		void fp_StepBackward();
		ch32 fp_Prev();

	private:
		t_CBaseIteratorFront mp_iFront;

	};

	template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
	class TCIterator_UTF16Adaptor
	{
	public:
		using CTags = TCTags
			<
				NIterator::CIteratorStep_OneStep
				, NIterator::CIteratorTraversal_Both
				, NIterator::CIteratorValueLifeTime_None
				, NIterator::CIteratorCopy_Copy
				, NIterator::CIteratorConstruct_None
				, NIterator::CIteratorAccess_Readable
				, NStr::CIteratorStringEncoding_UTF32
			>
		;

		using CValueType = ch32;

		/// Functions

		TCIterator_UTF16Adaptor(t_CBaseIterator const &_iFront, t_CBaseIteratorBack const &_iBack);

		bool f_IsBroken() const;
		bool f_IsComplete() const;

		TCIterator_UTF16Adaptor f_Invalid() const
		{
			return TCIterator_UTF16Adaptor(this->mp_iCurrent.f_Invalid(), this->mp_iBack.f_Invalid());
		}

	public:
		void fp_StepForward();
		ch32 fp_GetValue() const;
		template <typename tf_CIterator>
		bool fp_Equal(tf_CIterator const &_Right) const;
		t_CBaseIterator const &fp_ParentIterator() const;

		void fp_ParseBOM();
		ch32 fp_Next();

	protected:
		t_CBaseIterator mp_iCurrent;
		t_CBaseIterator mp_iNext;
		t_CBaseIteratorBack mp_iBack;

		ch32 mp_Current;

	public:
		auto fp_Base() const -> decltype(fg_GetType<t_CBaseIterator const &>().f_Base());
	};

	template <typename t_CBaseIterator, typename t_CBaseIteratorFront, typename t_CBaseIteratorBack>
	class TCIterator_UTF16AdaptorWithBackward : public TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>
	{
	public:
		using CTags = TCTags
			<
				NIterator::CIteratorStep_OneStep
				, NIterator::CIteratorTraversal_Both
				, NIterator::CIteratorValueLifeTime_None
				, NIterator::CIteratorCopy_Copy
				, NIterator::CIteratorConstruct_None
				, NIterator::CIteratorAccess_Readable
				, NStr::CIteratorStringEncoding_UTF32
			>
		;

		TCIterator_UTF16AdaptorWithBackward f_Invalid() const
		{
			return TCIterator_UTF16AdaptorWithBackward(this->mp_iCurrent.f_Invalid(), mp_iFront.f_Invalid(), this->mp_iBack.f_Invalid());
		}

		TCIterator_UTF16AdaptorWithBackward(t_CBaseIterator const &_iCurrent, t_CBaseIteratorFront const &_iFront, t_CBaseIteratorBack const &_iBack);
	public:
		void fp_StepBackward();
		ch32 fp_Prev();

	private:
		t_CBaseIteratorFront mp_iFront;

	};


	template <typename tf_CFrontIterator, typename tf_CBackIterator>
	auto fg_RangeAdaptor_UTFDecode(NIterator::TCRange<tf_CFrontIterator, tf_CBackIterator> &_Range) ->
		decltype
		(
			NPrivate::fg_Private_RangeAdaptor_UTFDecode
			(
				_Range
				, typename TCGetTag<typename tf_CFrontIterator::CTags, NStr::CIteratorStringEncoding_None>::CType()
				, typename TCGetTag<typename tf_CFrontIterator::CTags, NIterator::CIteratorTraversal_None>::CType()
				, typename TCGetTag<typename tf_CBackIterator::CTags, NStr::CIteratorStringEncoding_None>::CType()
				, typename TCGetTag<typename tf_CBackIterator::CTags, NIterator::CIteratorTraversal_None>::CType()
			)
		)
	;
}

#include "Malterlib_String_Iterator_Unicode.hpp"
