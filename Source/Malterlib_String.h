// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

using uch8 = NMib::NTraits::TCUnsigned<ch8>;
using uch16 = NMib::NTraits::TCUnsigned<ch16>;
using uch32 = NMib::NTraits::TCUnsigned<ch32>;

using zuch8 = NMib::TCAutoClear<uch8>;
using zuch16 = NMib::TCAutoClear<uch16>;
using zuch32 = NMib::TCAutoClear<uch32>;

namespace NMib::NStr
{
	void fg_Debug_AccessNewLine();

	extern ch8 g_lWhiteSpaceChars[];

	namespace NPrivate
	{
		template <typename t_CDataToTest, typename t_CClassToTestAgainst>
		class TCHasFormatClassHelper;
	}

	template <typename t_CDataToTest, typename t_CClassToTestAgainst>
	concept cHasFormatClass = NPrivate::TCHasFormatClassHelper<t_CDataToTest, t_CClassToTestAgainst>::mc_bValue;
}

#include "Malterlib_String_Algorithm.hpp"
#include "Malterlib_String_Parse_Integer.h"
#include "Malterlib_String_Parse_Float.h"

#include "Malterlib_String_Container_Format_Shared.h"
#include "Malterlib_String_Container_Parse.h"

#include "Malterlib_String_Container.h"


#include "Malterlib_String_Container_ImpVirtual.h"
#include "Malterlib_String_Container_ImpDynamic.h"
#include "Malterlib_String_Container_ImpFixed.h"

namespace NMib::NStr
{
	extern template struct TCStr<CStrTraits_CStr>;
	extern template struct TCStr<CStrTraits_CWStr>;
	extern template struct TCStr<CStrTraits_CUStr>;
	extern template struct TCFormat<CStrTraits_CStr>;
	extern template struct TCFormat<CStrTraits_CWStr>;
	extern template struct TCFormat<CStrTraits_CUStr>;

	extern template struct TCStr<CStrTraits_CStrNonTracked>;
	extern template struct TCStr<CStrTraits_CWStrNonTracked>;
	extern template struct TCStr<CStrTraits_CUStrNonTracked>;
	extern template struct TCFormat<CStrTraits_CStrNonTracked>;
	extern template struct TCFormat<CStrTraits_CWStrNonTracked>;
	extern template struct TCFormat<CStrTraits_CUStrNonTracked>;

	extern template struct TCStr<CStrTraits_CStrVMem>;
	extern template struct TCStr<CStrTraits_CWStrVMem>;
	extern template struct TCStr<CStrTraits_CUStrVMem>;

	extern template class TCStrImp_Dynamic<CStrTraits_CStr::CStrTraits>;
	extern template class TCStrImp_Dynamic<CStrTraits_CWStr::CStrTraits>;
	extern template class TCStrImp_Dynamic<CStrTraits_CUStr::CStrTraits>;

	extern template TCStr<NMib::NStr::CStrTraits_CStrNonTracked> &TCStr<NMib::NStr::CStrTraits_CStrNonTracked>::operator= (TCStr<NMib::NStr::CStrTraits_CStr> const &);
	extern template void NMib::NStr::TCStr<NMib::NStr::CStrTraits_CStrNonTracked>::f_SetStr(TCStr<NMib::NStr::CStrTraits_CStr> const &);
}

#include "Malterlib_String_Container_Format_String.h"
#include "Malterlib_String_Container_Format_StringContainer.h"
#include "Malterlib_String_Container_Format_Integer.h"
#include "Malterlib_String_Container_Format_Float.h"
#include "Malterlib_String_Container_Format_Binary.h"
#include "Malterlib_String_Container_Format_Inline.h"
#include "Malterlib_String_Container_Format_AutoClear.h"

#include "Malterlib_String_Container_Parse_Integer.h"
#include "Malterlib_String_Container_Parse_Float.h"
#include "Malterlib_String_Container_Parse_StringContainer.h"

#include "Malterlib_String_Container_FormatHelpers.h"

namespace NMib::NSys::NStr
{
	void fg_SystemEncodeAnsiStr(NMib::NStr::CStr const &_In, NMib::NStr::CAnsiStr &_Out, ch8 _ErrorChar);
	void fg_SystemDecodeAnsiStr(NMib::NStr::CAnsiStr const &_In, NMib::NStr::CStr &_Out);
	void fg_SystemDecodeAnsiStr(ch8 const *_pIn, NMib::NStr::CStr &_Out);
	void fg_SystemEncodeCodePageStr(NMib::NStr::CStr const &_In, NMib::NStr::CAnsiStr &_Out, uint32 _CodePage, ch8 _ErrorChar);
	void fg_SystemDecodeCodePageStr(NMib::NStr::CAnsiStr const &_In, NMib::NStr::CStr &_Out, uint32 _CodePage);
	void fg_SystemDecodeCodePageStr(ch8 const *_pIn, NMib::NStr::CStr &_Out, uint32 _CodePage);
	void fg_SystemEncodeAnsiStr(NMib::NStr::CStrNonTracked const &_In, NMib::NStr::CAnsiStrNonTracked &_Out, ch8 _ErrorChar);
	void fg_SystemDecodeAnsiStr(NMib::NStr::CAnsiStrNonTracked const &_In, NMib::NStr::CStrNonTracked &_Out);
	void fg_SystemDecodeAnsiStr(ch8 const *_pIn, NMib::NStr::CStrNonTracked &_Out);
	void fg_SystemEncodeCodePageStr(NMib::NStr::CStrNonTracked const &_In, NMib::NStr::CAnsiStrNonTracked &_Out, uint32 _CodePage, ch8 _ErrorChar);
	void fg_SystemDecodeCodePageStr(NMib::NStr::CAnsiStrNonTracked const &_In, NMib::NStr::CStrNonTracked &_Out, uint32 _CodePage);
	void fg_SystemDecodeCodePageStr(ch8 const *_pIn, NMib::NStr::CStrNonTracked &_Out, uint32 _CodePage);
}

#include "Malterlib_String_Compare.h"
#include "Malterlib_String_Container.hpp"
#include "Malterlib_String_Container_ImpDynamic.hpp"

namespace NMib::NStr
{
	CStr fg_ForceStrUTF8(const CStr &_Str);
	CStr fg_ForceStrUTF8(const CWStr &_Str);
	CStr fg_ForceStrUTF8(const CUStr &_Str);

	enum class EValidateUTF8Flag : uint32
	{
		mc_None = 0
		, mc_DisallowNonCharacters = fg_Bit(0)
	};

	bool fg_IsValidUTF8(CStr const &_Str, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None);
	bool fg_IsValidUTF8(ch8 const *_pStr, mint _Len, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None);
	CWStr fg_ForceStrUTF16(const CWStr &_Str);
	CStr fg_ReplaceCharactersUTF8(CStr const &_Str, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None, uch8 _ReplacementChar = '?');
	CStr fg_ReplaceSequenceUTF8(CStr const &_Str, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None, CStr const &_ReplacementChar = CStr("\xef\xbf\xbd"));
	CStr fg_CleanUTF8(CStr const &_Str, EValidateUTF8Flag _Flags = EValidateUTF8Flag::mc_None);

	inline_always CStr::CFormat operator ""_f (const char *_pStr, std::size_t _Len)
	{
		return CStr::CFormat(_pStr);
	}

	inline_always CWStr::CFormat operator ""_f (const ch16 *_pStr, std::size_t _Len)
	{
		return CWStr::CFormat(_pStr);
	}

	inline_always CUStr::CFormat operator ""_f (const ch32 *_pStr, std::size_t _Len)
	{
		return CUStr::CFormat(_pStr);
	}

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

		template <typename tf_CStream>
		void f_Stream(tf_CStream &_Stream) const
		{
			_Stream % m_Error;
			_Stream % m_Location;
			_Stream % m_IndentDepth;
			_Stream % m_bSeparator;
		}

		bool f_IsSeparator() const
		{
			return m_bSeparator;
		}

		CParseError &f_SetSeparator(CStr const &_Separator)
		{
			m_bSeparator = true;
			m_Error = _Separator;

			return *this;
		}

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

#ifndef DMibPNoShortCuts
	using namespace NMib::NStr;
#endif

#include "Malterlib_String.hpp"
