// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CStr, bool t_bIncludeExtra>
	bool TCParseLocation<t_CStr, t_bIncludeExtra>::operator == (TCParseLocation const &_Right) const
	{
		if (m_File != _Right.m_File)
			return false;
		if (m_Character != _Right.m_Character)
			return false;
		if (m_Line != _Right.m_Line)
			return false;
		if (m_Column != _Right.m_Column)
			return false;
		return true;
	}

	template <typename t_CStr, bool t_bIncludeExtra>
	bool TCParseLocation<t_CStr, t_bIncludeExtra>::operator < (TCParseLocation const &_Right) const
	{
		if (m_File < _Right.m_File)
			return true;
		else if (m_File > _Right.m_File)
			return false;

		if (m_Character < _Right.m_Character)
			return true;
		else if (m_Character > _Right.m_Character)
			return false;

		if (m_Line < _Right.m_Line)
			return true;
		else if (m_Line > _Right.m_Line)
			return false;

		if (m_Column < _Right.m_Column)
			return true;
		else if (m_Column > _Right.m_Column)
			return false;

		return false;
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
	bool TCParseLocation<t_CStr, false>::operator ==(TCParseLocation const &_Right) const
	{
		if (m_File != _Right.m_File)
			return false;
		if (m_Line != _Right.m_Line)
			return false;
		return true;
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
