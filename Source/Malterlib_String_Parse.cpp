// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

namespace NMib::NStr
{
	void CParseError::f_Format(NStr::CStr &o_FormatInto) const
	{
		o_FormatInto += CStr::CFormat("{} Error '{}'") << m_Location << m_Error;
	}

	NStr::CStr CParseError::fs_ToString(NContainer::TCVector<CParseError> const &_Errors)
	{
		NStr::CStr ErrorString;

		for (auto &Error : _Errors)
		{
			CStr Indent;
			for (umint i = 0; i < Error.m_IndentDepth; ++i)
				Indent += DMibPFileLineFormatIndent;
			if (Error.f_IsSeparator())
			{
				if (Error.m_Error)
					fg_AddStrSep(ErrorString, NStr::CStr::CFormat("{}--- {} ---") << Indent << Error.m_Error, "\n");
				else
					fg_AddStrSep(ErrorString, NStr::CStr::CFormat("{}----------") << Indent << Error.m_Error, "\n");
			}
			else
			{
				if (Error.m_Location.f_IsValid())
					fg_AddStrSep(ErrorString, NStr::CStr::CFormat("{}{} {}") << Indent << Error.m_Location << Error.m_Error.f_Indent(Indent, false), "\n");
				else
					fg_AddStrSep(ErrorString, NStr::CStr::CFormat("{}{}") << Indent << Error.m_Error.f_Indent(Indent, false), "\n");
			}
		}

		return ErrorString;
	}

	bool CParseError::f_IsSeparator() const
	{
		return m_bSeparator;
	}

	CParseError &CParseError::f_SetSeparator(CStr const &_Separator)
	{
		m_bSeparator = true;
		m_Error = _Separator;

		return *this;
	}
}
