// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>
#include <Mib/Iterator/RangeReverse>

#include "Malterlib_String_Algorithm_Common.h"

namespace NMib::NStr2
{
	struct CNoCaseBase
	{
		void f_GetBaseHelper()
		{
		}
	};

	struct CNoCase : public virtual CNoCaseBase
	{
	};

	struct CReverseBase
	{
		void f_GetBaseHelper()
		{
		}
	};

	struct CReverse : public virtual CReverseBase
	{
	};

	struct CUnicodeBase
	{
		void f_GetBaseHelper()
		{
		}
	};

	struct CUnicode : public virtual CUnicodeBase
	{
	};

	namespace NPrivate
	{
		template <typename tf_CCharLeft, typename tf_CCharRight>
		inline_always bool fg_Private_CharIsSame(tf_CCharLeft _Left, tf_CCharRight _Right, CNoCase)
		{
			return NStr::fg_CharLowerCase(_Left) == NStr::fg_CharLowerCase(_Right);
		}

		template <typename tf_CCharLeft, typename tf_CCharRight>
		inline_always bool fg_Private_CharIsSame(tf_CCharLeft _Left, tf_CCharRight _Right, CNoCaseBase)
		{
			return _Left == _Right;
		}
	}

	template <typename tf_CTags, typename tf_CCharLeft, typename tf_CCharRight>
	inline_always bool fg_CharIsSame(tf_CCharLeft _Left, tf_CCharRight _Right)
	{
		return NPrivate::fg_Private_CharIsSame(_Left, _Right, typename TCGetTag<tf_CTags, CNoCaseBase>::CType());
	}


	namespace NPrivate
	{
		template <typename tf_CCharLeft, typename tf_CCharRight>
		inline_always ECompare fg_Private_CharCompare(tf_CCharLeft _Left, tf_CCharRight _Right, CNoCase)
		{
			auto Left = NStr::fg_CharLowerCase(_Left);
			auto Right = NStr::fg_CharLowerCase(_Right);
			if (Left > Right)
				return ECompare_GreaterThan;
			else if (Left < Right)
				return ECompare_LessThan;
			return ECompare_Equal;
		}

		template <typename tf_CCharLeft, typename tf_CCharRight>
		inline_always ECompare fg_Private_CharCompare(tf_CCharLeft _Left, tf_CCharRight _Right, CNoCaseBase)
		{
			if (_Left > _Right)
				return ECompare_GreaterThan;
			else if (_Left < _Right)
				return ECompare_LessThan;
			return ECompare_Equal;
		}
	}

	template <typename tf_CTags, typename tf_CCharLeft, typename tf_CCharRight>
	ECompare fg_CharCompare(tf_CCharLeft _Left, tf_CCharRight _Right)
	{
		return NPrivate::fg_Private_CharCompare(_Left, _Right, typename TCGetTag<tf_CTags, CNoCaseBase>::CType());
	}

	namespace NPrivate
	{
		struct CDummyBase
		{
		};

		struct CDummyDerived : public virtual CDummyBase
		{
		};

		template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
		NIterator::TCRange<tf_CFront, tf_CBack> fg_GetStringRangeHelper(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, CReverseBase, CDummyBase)
		{
			return _rCharacters;
		}

		template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
		auto fg_GetStringRangeHelper(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, CReverse, CDummyDerived)
			-> decltype(NIterator::fg_RangeReverse(_rCharacters))
		{
			return NIterator::fg_RangeReverse(_rCharacters);
		}

		template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
		NIterator::TCRange<tf_CFront, tf_CBack> fg_GetStringRangeHelper(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters, CReverse, CDummyBase)
		{
			static_assert(NTraits::cIsVoid<tf_CTags>, "Range does not support reversing");
		}
	}

	template <typename tf_CTags, typename tf_CFront, typename tf_CBack>
	auto fg_GetStringRange(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters)
		-> decltype(NPrivate::fg_GetStringRangeHelper<tf_CTags>(_rCharacters, typename TCGetTag<tf_CTags, CReverseBase>::CType(), NPrivate::CDummyDerived()))
	{
		return NPrivate::fg_GetStringRangeHelper<tf_CTags>(_rCharacters, typename TCGetTag<tf_CTags, CReverseBase>::CType(), NPrivate::CDummyDerived());
	}
}
