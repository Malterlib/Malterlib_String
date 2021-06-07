// Copyright © 2021 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <bool t_bCaseSensitive>
	template <typename tf_CLeft, typename tf_CRight>
	inline_small bool TCMultiReplace<t_bCaseSensitive>::CSort_Reverse::operator()(tf_CLeft &&_Left, tf_CRight &&_Right) const
	{
		if constexpr (t_bCaseSensitive)
			return fg_StrCmp(_Right, _Left) < 0;
		else
			return fg_StrCmpNoCase(_Right, _Left) < 0;
	}

	template <bool t_bCaseSensitive>
	template <typename tf_CLeft, typename tf_CRight>
	bool TCMultiReplace<t_bCaseSensitive>::fs_StartsWith(tf_CLeft &&_String, tf_CRight &&_StartsWith)
	{
		if constexpr (t_bCaseSensitive)
			return fg_StrStartsWith(_String, _StartsWith);
		else
			return fg_StrStartsWithNoCase(_String, _StartsWith);
	}

	template <bool t_bCaseSensitive>
	void TCMultiReplace<t_bCaseSensitive>::f_Prepare()
	{
		if (m_Replace.f_IsEmpty())
			return;

		m_SearchList.f_Clear();
		{
			CStr const *pLast = nullptr;
			NContainer::TCLinkedList<NContainer::TCLinkedList<CStr const *> *> ToAdd;
			NContainer::TCLinkedList<CStr const *> AddResults;
			for (auto &Replace : m_Replace)
			{
				auto &Key = m_Replace.fs_GetKey(Replace);
				if (pLast && fs_StartsWith(m_Replace.fs_GetKey(*pLast), Key))
					;
				else
				{
					if (pLast)
					{
						for (auto &pAddTo : ToAdd)
							pAddTo->f_Insert(fg_Move(AddResults));
					}

					ToAdd.f_Clear();
					AddResults.f_Clear();
					pLast = &Replace;
				}

				AddResults.f_Insert(&Replace);
				auto &SearchListEntry = m_SearchList[Key];
				ToAdd.f_Insert(&SearchListEntry);
			}

			if (pLast)
			{
				for (auto &pAddTo : ToAdd)
					pAddTo->f_Insert(fg_Move(AddResults));
			}
		}
		m_bPrepared = true;
	}

	template <bool t_bCaseSensitive>
	template <typename tf_FOnReplace>
	CStr TCMultiReplace<t_bCaseSensitive>::f_Replace(CStr const &_String, tf_FOnReplace &&_fOnReplace)
	{
		if (!m_bPrepared)
			f_Prepare();

		if (m_Replace.f_IsEmpty())
			return _String;

		auto pFirst = m_SearchList.f_FindSmallest();

		CStr NewContents;
		ch8 const *pParse = _String.f_GetStr();
		while (*pParse)
		{
			auto iFound = m_SearchList.f_GetIterator_LargestLessThanEqual(pParse);

			NContainer::TCLinkedList<CStr const *> const *pFoundEntries = nullptr;
			if (!iFound)
				pFoundEntries = pFirst;
			else if (!fs_StartsWith(pParse, iFound.f_GetKey()))
			{
				++iFound;
				pFoundEntries = iFound;
			}
			else
				pFoundEntries = iFound;

			if (pFoundEntries)
			{
				bool bShouldContinue = false;
				for (auto &pFoundEntry : *pFoundEntries)
				{
					auto &ToFind = m_Replace.fs_GetKey(*pFoundEntry);

					if (fs_StartsWith(pParse, ToFind))
					{
						if (_fOnReplace(NewContents, pParse, ToFind, *pFoundEntry))
						{
							bShouldContinue = true;
							break;
						}
					}
				}
				if (bShouldContinue)
					continue;
			}

			NewContents.f_AddChar(*pParse);
			++pParse;
		}

		return NewContents;
	}

	template <bool t_bCaseSensitive>
	CStr TCMultiReplace<t_bCaseSensitive>::f_Replace(CStr const &_String)
	{
		return f_Replace
			(
				_String
				, [](CStr &o_String, ch8 const * &o_pParse, CStr const &_ToFind, CStr const &_ReplaceWith) -> bool
				{
					o_pParse += _ToFind.f_GetLen();
					o_String += _ReplaceWith;
					return true;
				}
			)
		;
	}
}
