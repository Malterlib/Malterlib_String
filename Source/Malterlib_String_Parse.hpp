// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CStream>
	void CParseError::f_Stream(tf_CStream &_Stream) const
	{
		_Stream % m_Error;
		_Stream % m_Location;
		_Stream % m_IndentDepth;
		_Stream % m_bSeparator;
	}

	template <typename t_CStr, bool t_bIncludeExtra>
	template <typename tf_CStr>
	void TCParseLocation<t_CStr, t_bIncludeExtra>::f_Format(tf_CStr &o_FormatInto) const
	{
		o_FormatInto
			+= typename tf_CStr::CFormat(DMibPFileLineColumnFormat)
			<< m_File
			<< m_Line
			<< m_Column
		;
	}

	template <typename t_CStr, bool t_bIncludeExtra>
	template <typename tf_CStream>
	void TCParseLocation<t_CStr, t_bIncludeExtra>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << m_File;
		_Stream << m_Character;
		_Stream << m_Line;
		_Stream << m_Column;
	}

	template <typename t_CStr, bool t_bIncludeExtra>
	template <typename tf_CStream>
	void TCParseLocation<t_CStr, t_bIncludeExtra>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> m_File;
		_Stream >> m_Character;
		_Stream >> m_Line;
		_Stream >> m_Column;
	}

	template <typename t_CStr, bool t_bIncludeExtra>
	bool TCParseLocation<t_CStr, t_bIncludeExtra>::f_IsValid() const
	{
		return m_File && m_Line;
	}

	template <typename t_CStr>
	template <typename tf_CStr>
	void TCParseLocation<t_CStr, false>::f_Format(tf_CStr &o_FormatInto) const
	{
		o_FormatInto
			+= typename tf_CStr::CFormat(DMibPFileLineFormat)
			<< m_File
			<< m_Line
		;
	}

	template <typename t_CStr>
	template <typename tf_CStream>
	void TCParseLocation<t_CStr, false>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << m_File;
		_Stream << m_Line;
	}

	template <typename t_CStr>
	template <typename tf_CStream>
	void TCParseLocation<t_CStr, false>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> m_File;
		_Stream >> m_Line;
	}

	template <typename t_CStr>
	bool TCParseLocation<t_CStr, false>::f_IsValid() const
	{
		return m_File && m_Line;
	}
}
