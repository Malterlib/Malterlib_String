// Copyright © 2021 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <bool t_bCaseSensitive>
	template <typename tf_CLeft, typename tf_CRight>
	inline_small auto TCMultiReplace<t_bCaseSensitive>::CSort_Reverse::operator()(tf_CLeft &&_Left, tf_CRight &&_Right) const -> COrdering
	{
		if constexpr (t_bCaseSensitive)
			return fg_StrCmp(_Right, _Left) <=> 0;
		else
			return fg_StrCmpNoCase(_Right, _Left) <=> 0;
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
	TCMultiReplace<t_bCaseSensitive>::TCMultiReplace(CStringMap &&_StringMap)
	{
		mp_Replace = fg_Move(_StringMap);
		mp_SearchList.f_Clear();
		{
			typename CStringMap::CNode const *pLast = nullptr;
			NContainer::TCLinkedList<NContainer::TCLinkedList<CStr const *> *> ToAdd;
			NContainer::TCLinkedList<CStr const *> AddResults;

			for (auto &ReplaceEntry : mp_Replace.f_Entries().f_GetIteratorReverse())
			{
				auto &Key = ReplaceEntry.f_Key();
				auto &Replace = ReplaceEntry.f_Value();

				if (pLast && !fs_StartsWith(Key, pLast->f_Key()))
				{
					for (auto &pAddTo : ToAdd)
						pAddTo->f_Insert(fg_Move(AddResults));

					ToAdd.f_Clear();
					AddResults.f_Clear();
					pLast = &ReplaceEntry;
				}
				else if (!pLast)
					pLast = &ReplaceEntry;

				AddResults.f_InsertFirst(&Replace);
				auto &SearchListEntry = mp_SearchList[Key];
				ToAdd.f_Insert(&SearchListEntry);
			}

			if (pLast)
			{
				for (auto &pAddTo : ToAdd)
					pAddTo->f_Insert(fg_Move(AddResults));
			}
		}
		mp_pSearchListFirst = mp_SearchList.f_FindSmallest();
		mp_bPrepared = true;
	}

	template <bool t_bCaseSensitive>
	bool TCMultiReplace<t_bCaseSensitive>::f_IsEmpty() const
	{
		return mp_SearchList.f_IsEmpty();
	}

	template <bool t_bCaseSensitive>
	bool TCMultiReplace<t_bCaseSensitive>::f_StringMatches(ch8 const *_pString)
	{
		return f_StringMatches(_pString, [](CStr const &_ToFind, CStr const &_FoundEntry) { return true; });
	}

	template <bool t_bCaseSensitive>
	template <typename tf_FCheckFound>
	bool TCMultiReplace<t_bCaseSensitive>::f_StringMatches(ch8 const *_pString, tf_FCheckFound &&_fCheckFound)
	{
		auto iFound = mp_SearchList.f_GetIterator_LargestLessThanEqual(_pString);

		NContainer::TCLinkedList<CStr const *> const *pFoundEntries = nullptr;
		if (!iFound)
			pFoundEntries = mp_pSearchListFirst;
		else if (!fs_StartsWith(_pString, iFound.f_GetKey()))
		{
			++iFound;
			pFoundEntries = iFound;
		}
		else
			pFoundEntries = iFound;

		if (!pFoundEntries)
			return false;

		for (auto &pFoundEntry : *pFoundEntries)
		{
			auto &ToFind = mp_Replace.fs_GetKey(*pFoundEntry);

			if (fs_StartsWith(_pString, ToFind))
			{
				if (_fCheckFound(ToFind, *pFoundEntry))
					return true;
			}
		}

		return false;
	}

	template <bool t_bCaseSensitive>
	template <typename tf_FOnReplace>
	CStr TCMultiReplace<t_bCaseSensitive>::f_Replace(CStr const &_String, tf_FOnReplace &&_fOnReplace)
	{
		if (mp_SearchList.f_IsEmpty())
			return _String;

		CStr NewContents;
		ch8 const *pParse = _String.f_GetStr();
		auto fReplace = [&](auto &&_ToFind, auto &&_FoundEntry) -> bool
			{
				return _fOnReplace(NewContents, pParse, _ToFind, _FoundEntry);
			}
		;

		while (*pParse)
		{
			if (f_StringMatches(pParse, fReplace))
				continue;

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
