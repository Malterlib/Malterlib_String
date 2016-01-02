// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	namespace NStr
	{
		// TCAutoClearInt String Formatter
		template <typename t_CFormatter, typename t_CInt, t_CInt t_ClearVal>
		class TCStringFormatter<t_CFormatter, NMib::TCAutoClearInt<t_CInt, t_ClearVal> >
		{
		public:
			typedef NMib::TCAutoClearInt<t_CInt, t_ClearVal> CData;

		private:
			static t_CFormatter &fs_GetFormatter();
			static CData &fs_GetData();

		public:

			typedef decltype(fg_GetStringFormatType(fs_GetFormatter(), t_CInt(0))) CFormatType;

			static auto fs_CreateFormat(t_CFormatter &_Formatter, CData const &_Data) -> decltype(fg_CreateStringFormatter(_Formatter, _Data.m_Int))
			{
				return fg_CreateStringFormatter(_Formatter, _Data.m_Int);
			}
		};

	}

} // Namespace NMib
