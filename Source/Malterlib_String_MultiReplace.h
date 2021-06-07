// Copyright © 2021 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <bool t_bCaseSensitive>
	struct TCMultiReplace
	{
		class CSort_Reverse
		{
		public:
			template <typename tf_CLeft, typename tf_CRight>
			inline_small bool operator()(tf_CLeft &&_Left, tf_CRight &&_Right) const;
		};

		template <typename tf_CLeft, typename tf_CRight>
		static bool fs_StartsWith(tf_CLeft &&_String, tf_CRight &&_StartsWith);

		void f_Prepare();

		template <typename tf_FOnReplace>
		CStr f_Replace(CStr const &_String, tf_FOnReplace &&_fOnReplace);
		CStr f_Replace(CStr const &_String);

		NContainer::TCMap<CStr, CStr, CSort_Reverse> m_Replace;
		NContainer::TCMap<CStr, NContainer::TCLinkedList<CStr const *>, CSort_Reverse> m_SearchList;
		bool m_bPrepared = false;
	};
}

#include "Malterlib_String_MultiReplace.hpp"
