// Copyright © 2021 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <bool t_bCaseSensitive>
	struct TCMultiReplace
	{
		using COrdering = TCConditional<t_bCaseSensitive, COrdering_Strong, COrdering_Weak>;
		class CSort_Reverse
		{
		public:
			template <typename tf_CLeft, typename tf_CRight>
			inline_small COrdering operator()(tf_CLeft &&_Left, tf_CRight &&_Right) const;
		};

		using CStringMap = NContainer::TCMap<CStr, CStr, CSort_Reverse>;

		TCMultiReplace(CStringMap &&_StringMap);

		template <typename tf_CLeft, typename tf_CRight>
		static bool fs_StartsWith(tf_CLeft &&_String, tf_CRight &&_StartsWith);

		template <typename tf_FOnReplace>
		CStr f_Replace(CStr const &_String, tf_FOnReplace &&_fOnReplace);
		CStr f_Replace(CStr const &_String);

		bool f_IsEmpty() const;

		template <typename tf_FCheckFound>
		bool f_StringMatches(ch8 const *_pString, tf_FCheckFound &&_fCheckFound);
		bool f_StringMatches(ch8 const *_pString);

	private:
		CStringMap mp_Replace;
		NContainer::TCMap<CStr, NContainer::TCLinkedList<CStr const *>, CSort_Reverse> mp_SearchList;
		NContainer::TCLinkedList<CStr const *> const *mp_pSearchListFirst = nullptr;
		bool mp_bPrepared = false;
	};
}

#include "Malterlib_String_MultiReplace.hpp"
