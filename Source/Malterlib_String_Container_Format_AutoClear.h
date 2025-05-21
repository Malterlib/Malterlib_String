// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	// TCAutoClearInt String Formatter
	template <typename t_CFormatter, typename t_CInt, t_CInt t_ClearVal>
	class TCStringFormatter<t_CFormatter, NMib::TCAutoClearInt<t_CInt, t_ClearVal> >
	{
	public:
		using CData = NMib::TCAutoClearInt<t_CInt, t_ClearVal>;

	private:
		static t_CFormatter &fs_GetFormatter();
		static CData &fs_GetData();

	public:
		using CFormatType = decltype(fg_GetStringFormatType(fs_GetFormatter(), t_CInt(0)));

		template <typename tf_CTypeWithConst>
		static auto fs_CreateFormat(t_CFormatter &_Formatter, CData const &_Data) -> decltype(fg_CreateStringFormatter(_Formatter, _Data.m_Int))
		{
			return fg_CreateStringFormatter(_Formatter, _Data.m_Int);
		}
	};
}
