// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStr, bool t_bIncludeExtra>
	struct TCParseLocation
	{
		auto operator <=> (TCParseLocation const &_Right) const = default;

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_FormatInto) const;
		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
		bool f_IsValid() const;

		t_CStr m_File;
		uint32 m_Character = 0;
		uint32 m_Line = 0;
		uint32 m_Column = 0;
	};

	template <typename t_CStr>
	struct TCParseLocation<t_CStr, false>
	{
		auto operator <=> (TCParseLocation const &_Right) const = default;

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_FormatInto) const;
		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
		bool f_IsValid() const;

		t_CStr m_File;
		uint32 m_Line = 0;
	};

	using CParseLocation = TCParseLocation<CStr, true>;

	struct CParseError
	{
		auto operator <=> (CParseError const &_Right) const = default;

		void f_Format(NStr::CStr &o_FormatInto) const;
		bool f_IsSeparator() const;
		CParseError &f_SetSeparator(CStr const &_Separator);

		template <typename tf_CStream>
		void f_Stream(tf_CStream &_Stream) const;

		static NStr::CStr fs_ToString(NContainer::TCVector<CParseError> const &_Errors);

		NStr::CStr m_Error;
		CParseLocation m_Location;
		uint32 m_IndentDepth = 0;
		bool m_bSeparator = false;
	};

	DMibImpErrorSpecificClassDefine(CExceptionParse, NMib::NException::CException, NContainer::TCVector<CParseError>);

#	define DMibErrorParse(d_Description, d_Specific) DMibImpErrorSpecific(NMib::NStr::CExceptionParse, d_Description, d_Specific)
#	define DMibExceptionInstanceParse(d_Description, d_Specific) DMibImpExceptionInstance(NMib::NStr::CExceptionParse, d_Description, d_Specific)

#	ifndef DMibPNoShortCuts
#		define DErrorParse(d_Description, d_Specific) DMibErrorParse(d_Description, d_Specific)
#	endif
}

#include "Malterlib_String_Parse.hpp"
