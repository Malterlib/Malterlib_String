// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Algorithm/Advance>

namespace NMib
{
	namespace NStr
	{

		///
		/// UTF8
		/// ====
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		NIterator::TCRange<t_CBaseIterator, t_CBaseIteratorBack> TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_TempRange()
		{
			return NIterator::TCRange<t_CBaseIterator, t_CBaseIteratorBack>(mp_iCurrent, mp_iBack);
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		void TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_ParseBOM()
		{
			auto rChars = fp_TempRange();
			
			if (rChars && *rChars == 0xEF)
			{
				++rChars;
				if (rChars && *rChars == 0xBB)
				{
					++rChars;
					if (rChars && *rChars == 0xBF)
					{
						// Found BOM
						NAlgorithm::fg_Advance(mp_iCurrent, 3);
						mp_iNext = mp_iCurrent;
					}
				}
			}
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorFront, typename t_CBaseIteratorBack>
		ch32 TCIterator_UTF8AdaptorWithBackward<t_CBaseIterator, t_CBaseIteratorFront, t_CBaseIteratorBack>::fp_Prev()
		{
			auto iParse = this->mp_iCurrent;
			if (iParse != mp_iFront)
			{
				--iParse;
				uch8 ToTest = *iParse;
				while (iParse != mp_iFront && (ToTest & 0xC0) == 0x80)
				{
					--iParse;
					ToTest = *iParse;
				}
			}
			this->mp_iNext = iParse;
			return this->fp_Next();
		}
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		ch32 TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_Next()
		{
			ch32 DestChar = 0;
			auto iParse = mp_iCurrent = mp_iNext;
			while (1)
			{
				if (iParse == mp_iBack)
					break;

				uch8 ToTest = *iParse;
				if (ToTest & 0x80)
				{
					if ((ToTest & 0xC0) == 0xC0)
					{
						++iParse;
						smint nChars = 7-fg_GetHighestBitSet((~uint32(ToTest))&0xFF);
						DestChar = ToTest & ((1 << (8-(nChars+1))) - 1);
						--nChars;
						while (iParse != mp_iBack && (*iParse & 0xC0) == 0x80)
						{
							DestChar = (DestChar << 6) | ((*iParse) & 0x3F);
							++iParse;
							--nChars;
						}
						if (nChars)
						{
							if (iParse == mp_iBack)
								DestChar = g_IncompleteCodepoint;
							else
							{
								DestChar = g_InvalidCodepoint;
								break;
							}
						}
						break;
					}
					else
					{
						DestChar = g_InvalidCodepoint;
						++iParse;
						break;
					}
				}
				else
				{
					DestChar = ToTest;
					++iParse;
					break;
				}
			}

			mp_iNext = iParse;

			return DestChar;
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::TCIterator_UTF8Adaptor(t_CBaseIterator const &_iCurrent, t_CBaseIteratorBack const &_iBack)
			: mp_iCurrent(_iCurrent)
			, mp_iNext(_iCurrent)
			, mp_iBack(_iBack)
		{
			fp_ParseBOM();
			mp_Current = fp_Next();
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorFront, typename t_CBaseIteratorBack>
		TCIterator_UTF8AdaptorWithBackward<t_CBaseIterator, t_CBaseIteratorFront, t_CBaseIteratorBack>
			::TCIterator_UTF8AdaptorWithBackward(t_CBaseIterator const &_iCurrent, t_CBaseIteratorFront const &_iFront, t_CBaseIteratorBack const &_iBack)
			: TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>(_iCurrent, _iBack)
			, mp_iFront(_iFront)
		{
		}
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		bool TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::f_IsBroken() const
		{
			return mp_Current == g_InvalidCodepoint;
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		bool TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::f_IsComplete() const
		{
			return mp_Current != g_IncompleteCodepoint;
		}
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		auto TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_Base() const -> decltype(fg_GetType<t_CBaseIterator const &>().f_Base())
		{
			return mp_iCurrent.f_Base();
		}
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		t_CBaseIterator const &TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_ParentIterator() const
		{
			return mp_iCurrent;
		}
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		void TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_StepForward()
		{
			mp_Current = fp_Next();
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorFront, typename t_CBaseIteratorBack>
		void TCIterator_UTF8AdaptorWithBackward<t_CBaseIterator, t_CBaseIteratorFront, t_CBaseIteratorBack>::fp_StepBackward()
		{
			this->mp_Current = fp_Prev();
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		ch32 TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_GetValue() const
		{
			return mp_Current;
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		template <typename tf_CIterator>
		bool TCIterator_UTF8Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_Equal(tf_CIterator const &_Other) const
		{
			return fp_Base() == fg_Base(_Other);
		}

		///
		/// UTF16
		/// =====
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		void TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_ParseBOM()
		{
			if (*mp_iCurrent == 0xFFFE)
			{
				++mp_iCurrent;
				mp_iNext = mp_iCurrent;
			}
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorFront, typename t_CBaseIteratorBack>
		ch32 TCIterator_UTF16AdaptorWithBackward<t_CBaseIterator, t_CBaseIteratorFront, t_CBaseIteratorBack>::fp_Prev()
		{
			auto iParse = this->mp_iCurrent;
			if (iParse != mp_iFront)
			{
				--iParse;
				uch16 ToTest = *iParse;
				if (iParse != mp_iFront && (ToTest & 0xFC00) == 0xDC00)
				{
					--iParse;
					ToTest = *iParse;
					if ((ToTest & 0xFC00) != 0xD800)
						++iParse; // Not valid, undo
				}
			}
			this->mp_iNext = iParse;
			return this->fp_Next();
		}
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		ch32 TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_Next()
		{
			ch32 DestChar = 0;
			auto iParse = mp_iCurrent = mp_iNext;
			while (1)
			{
				if (iParse == mp_iBack)
					break;

				if ((*iParse & 0xFC00) == 0xD800)
				{
					ch32 Str0 = *iParse;
					++iParse;
					if (iParse == mp_iBack)
					{
						DestChar = g_IncompleteCodepoint;
						break;
					}
					ch32 Str1 = *iParse;
					if ((Str1 & 0xFC00) != 0xDC00)
					{
						DestChar = g_InvalidCodepoint;
						continue;
					}
					++iParse;
						
					ch32 X = ((Str0 & ((1<<6) -1)) << 10) | (Str1 & ((1<<10) -1));
					ch32 W = (Str0 >> 6) & ((1<<5) - 1);
					ch32 U = W + 1 ;

					DestChar = U << 16 | X;
					break;
				}
				DestChar = *iParse;
				++iParse;
				break;
			}

			mp_iNext = iParse;

			return DestChar;
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::TCIterator_UTF16Adaptor(t_CBaseIterator const &_iCurrent, t_CBaseIteratorBack const &_iBack)
			: mp_iCurrent(_iCurrent)
			, mp_iNext(_iCurrent)
			, mp_iBack(_iBack)
		{
			fp_ParseBOM();
			mp_Current = fp_Next();
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorFront, typename t_CBaseIteratorBack>
		TCIterator_UTF16AdaptorWithBackward<t_CBaseIterator, t_CBaseIteratorFront, t_CBaseIteratorBack>
			::TCIterator_UTF16AdaptorWithBackward(t_CBaseIterator const &_iCurrent, t_CBaseIteratorFront const &_iFront, t_CBaseIteratorBack const &_iBack)
			: TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>(_iCurrent, _iBack)
			, mp_iFront(_iFront)
		{
		}
		
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		bool TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::f_IsBroken() const
		{
			return mp_Current == g_InvalidCodepoint;
		}
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		bool TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::f_IsComplete() const
		{
			return mp_Current != g_IncompleteCodepoint;
		}
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		auto TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_Base() const -> decltype(fg_GetType<t_CBaseIterator const &>().f_Base())
		{
			return mp_iCurrent.f_Base();
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		t_CBaseIterator const &TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_ParentIterator() const
		{
			return mp_iCurrent;
		}
		
			
		
		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		void TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_StepForward()
		{
			mp_Current = fp_Next();
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorFront, typename t_CBaseIteratorBack>
		void TCIterator_UTF16AdaptorWithBackward<t_CBaseIterator, t_CBaseIteratorFront, t_CBaseIteratorBack>::fp_StepBackward()
		{
			this->mp_Current = fp_Prev();
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		ch32 TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_GetValue() const
		{
			return mp_Current;
		}

		template <typename t_CBaseIterator, typename t_CBaseIteratorBack>
		template <typename tf_CIterator>
		bool TCIterator_UTF16Adaptor<t_CBaseIterator, t_CBaseIteratorBack>::fp_Equal(tf_CIterator const &_Other) const
		{
			return fp_Base() == fg_Base(_Other);
		}
		
		namespace NPrivate
		{
			template <typename tf_CRange, typename tf_CIterator>
			auto fg_Private_IteratorAdaptor_UTFDecode
				(
					tf_CRange &&_rCharacters
					, tf_CIterator const &_Iterator
					, NStr::CIteratorStringEncoding_None
					, NIterator::CIteratorTraversal_None
				)
				-> tf_CIterator
			{
				return _Iterator;
			}
			
			template <typename tf_CRange, typename tf_CIterator>
			auto fg_Private_IteratorAdaptor_UTFDecode
				(
					tf_CRange &&_rCharacters
					, tf_CIterator const &_Iterator
					, NStr::CIteratorStringEncoding_UTF16
					, NIterator::CIteratorTraversal_Both
				)
				-> NIterator::TCIterator
				<
					TCIterator_UTF16AdaptorWithBackward
					<
						tf_CIterator
						, typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType::CFront
						, typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType::CBack
					>
				>
			{
				typedef typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType CRange;
				typedef NIterator::TCIterator<TCIterator_UTF16AdaptorWithBackward<tf_CIterator, typename CRange::CFront, typename CRange::CBack>> CIterator;
				auto iFront = _rCharacters.f_Front();
				--iFront;
				return CIterator(_Iterator, iFront, _rCharacters.f_Back());
			}

			template <typename tf_CRange, typename tf_CIterator>
			auto fg_Private_IteratorAdaptor_UTFDecode
				(
					tf_CRange &&_rCharacters
					, tf_CIterator const &_Iterator
					, NStr::CIteratorStringEncoding_UTF16
					, NIterator::CIteratorTraversal_Forward
				)
				-> NIterator::TCIterator
				<
					TCIterator_UTF16Adaptor
					<
						tf_CIterator
						, typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType::CBack
					>
				>
			{
				typedef typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType CRange;
				typedef NIterator::TCIterator<TCIterator_UTF16Adaptor<tf_CIterator, typename CRange::CBack>> CIterator;
				return CIterator(_Iterator, _rCharacters.f_Back());
			}

			template <typename tf_CRange, typename tf_CIterator>
			auto fg_Private_IteratorAdaptor_UTFDecode
				(
					tf_CRange &&_rCharacters
					, tf_CIterator const &_Iterator
					, NStr::CIteratorStringEncoding_UTF8
					, NIterator::CIteratorTraversal_Both
				)
				-> NIterator::TCIterator
				<
					TCIterator_UTF8AdaptorWithBackward
					<
						tf_CIterator
						, typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType::CFront
						, typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType::CBack
					>
				>
			{
				typedef typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType CRange;
				typedef NIterator::TCIterator<TCIterator_UTF8AdaptorWithBackward<tf_CIterator, typename CRange::CFront, typename CRange::CBack>> CIterator;
				auto iFront = _rCharacters.f_Front();
				--iFront;
				return CIterator(_Iterator, iFront, _rCharacters.f_Back());
			}
			template <typename tf_CRange, typename tf_CIterator>
			auto fg_Private_IteratorAdaptor_UTFDecode
				(
					tf_CRange &&_rCharacters
					, tf_CIterator const &_Iterator
					, NStr::CIteratorStringEncoding_UTF8
					, NIterator::CIteratorTraversal_Forward
				)
				-> NIterator::TCIterator
				<
					TCIterator_UTF8Adaptor
					<
						tf_CIterator
						, typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType::CBack
					>
				>
			{
				typedef typename NTraits::TCRemoveReferenceAndQualifiers<tf_CRange>::CType CRange;
				typedef NIterator::TCIterator<TCIterator_UTF8Adaptor<tf_CIterator, typename CRange::CBack>> CIterator;
				return CIterator(_Iterator, _rCharacters.f_Back());
			}

			template <typename tf_CRange, typename tf_CFrontEncoding, typename tf_CFrontTraversal, typename tf_CBackEncoding, typename tf_CBackTraversal>
			auto fg_Private_RangeAdaptor_UTFDecode
				(
					tf_CRange &&_rCharacters
					, tf_CFrontEncoding
					, tf_CFrontTraversal
					, tf_CBackEncoding
					, tf_CBackTraversal
				)
				-> NIterator::TCRange
				<
					decltype(fg_Private_IteratorAdaptor_UTFDecode(_rCharacters, _rCharacters.f_Front(), tf_CFrontEncoding(), tf_CFrontTraversal()))
					, decltype(fg_Private_IteratorAdaptor_UTFDecode(_rCharacters, _rCharacters.f_Back(), tf_CBackEncoding(), tf_CBackTraversal()))
				>
			{
				return NIterator::TCRange
					<
						decltype(fg_Private_IteratorAdaptor_UTFDecode(_rCharacters, _rCharacters.f_Front(), tf_CFrontEncoding(), tf_CFrontTraversal()))
						, decltype(fg_Private_IteratorAdaptor_UTFDecode(_rCharacters, _rCharacters.f_Back(), tf_CBackEncoding(), tf_CBackTraversal()))
					>
					(
						fg_Private_IteratorAdaptor_UTFDecode(_rCharacters, _rCharacters.f_Front(), tf_CFrontEncoding(), tf_CFrontTraversal())
						, fg_Private_IteratorAdaptor_UTFDecode(_rCharacters, _rCharacters.f_Back(), tf_CBackEncoding(), tf_CBackTraversal())
					)
				;
			}
		};

		template <typename tf_CFrontIterator, typename tf_CBackIterator>
		auto fg_RangeAdaptor_UTFDecode(NIterator::TCRange<tf_CFrontIterator, tf_CBackIterator> const &_Range) -> 
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
		{
			return NPrivate::fg_Private_RangeAdaptor_UTFDecode
				(
					_Range
					, typename TCGetTag<typename tf_CFrontIterator::CTags, NStr::CIteratorStringEncoding_None>::CType()
					, typename TCGetTag<typename tf_CFrontIterator::CTags, NIterator::CIteratorTraversal_None>::CType()
					, typename TCGetTag<typename tf_CBackIterator::CTags, NStr::CIteratorStringEncoding_None>::CType()
					, typename TCGetTag<typename tf_CBackIterator::CTags, NIterator::CIteratorTraversal_None>::CType()
				)
			;
		}
	}
}
	
