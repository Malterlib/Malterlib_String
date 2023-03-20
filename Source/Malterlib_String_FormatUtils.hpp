// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStr>
	TCFormatUtilities<t_CStr>::TCFormatUtilities(typename t_CStr::CAppender &_Appender)
		: mp_Appender(_Appender)
	{
	}

	template <typename t_CStr>
	template <typename tf_CValue>
	void TCFormatUtilities<t_CStr>::f_Value(tf_CValue &&_Value)
	{
		using CType = typename NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>::CType;
		if constexpr (NStorage::cIsOptional<CType>)
			return f_Value(*_Value);

		if constexpr (NContainer::cIsVector<CType>)
		{
			if (_Value.f_IsEmpty())
				return;

			{
				for (auto &Item : _Value)
				{
					typename t_CStr::CDynamicStr Formatted;
					{
						typename t_CStr::CAppender Appender(Formatted);
						TCFormatUtilities Utils(Appender);
						Utils.f_Value(Item);
					}
					mp_Appender += "\n -  ";
					mp_Appender += Formatted.f_Indent("    ", false);
				}
			}


			return;
		}

		if constexpr (NTraits::TCIsSame<CType, bool>::mc_Value)
		{
			if (_Value)
				mp_Appender += "true";
			else
				mp_Appender += "false";
		}
		else
		{
			if constexpr (NTraits::TCIsSame<CType, t_CStr>::mc_Value)
				mp_Appender += _Value;
			else
				mp_Appender.f_Commit().m_String += typename t_CStr::CFormat("{}") << _Value;
		}
	}

	template <typename t_CStr>
	template <typename tf_CName, typename tf_CValue>
	void TCFormatUtilities<t_CStr>::f_TitledValue(tf_CName &&_Name, tf_CValue &&_Value)
	{
		using CType = typename NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>::CType;

		if constexpr (NStorage::cIsOptional<CType>)
		{
			if (!_Value)
				return;
		}

		if (mp_Appender.f_GetStrLen() != 0)
			mp_Appender += "\n";
		
		mp_Appender += _Name;
		mp_Appender += ": ";
		f_Value(_Value);
	}
}
