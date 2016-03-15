// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

typedef NMib::NTraits::TCUnsigned<ch8>::CType uch8;
typedef NMib::NTraits::TCUnsigned<ch16>::CType uch16;
typedef NMib::NTraits::TCUnsigned<ch32>::CType uch32;

typedef NMib::TCAutoClear<uch8> zuch8;
typedef NMib::TCAutoClear<uch16> zuch16;
typedef NMib::TCAutoClear<uch32> zuch32;

namespace NMib
{
	namespace NStr
	{
		void fg_Debug_AccessNewLine();
	}

	namespace NStr
	{

		extern ch8 g_lWhiteSpaceChars[];

		template <typename t_CDataToTest, typename t_CClassToTestAgainst>
		class TCHasFormatClass;
		
	}
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

namespace NMib
{
	namespace NStr
	{

#ifdef DMibSupportExternTemplates
		extern template TCStr<CStrTraits_CStr>;
		extern template TCStr<CStrTraits_CWStr>;
		extern template TCStr<CStrTraits_CUStr>;
		extern template TCStrAggregate< CStrTraits_CStr>;
		extern template TCStrAggregate< CStrTraits_CWStr>;
		extern template TCStrAggregate< CStrTraits_CUStr>;

		extern template TCStr<CStrTraits_CStrNonTracked>;
		extern template TCStr<CStrTraits_CWStrNonTracked>;
		extern template TCStr<CStrTraits_CUStrNonTracked>;
		extern template TCStrAggregate<CStrTraits_CStr>;
		extern template TCStrAggregate<CStrTraits_CWStr>;
		extern template TCStrAggregate<CStrTraits_CUStr>;

		extern template TCStr<CStrTraits_CStrVMem>;
		extern template TCStr<CStrTraits_CWStrVMem>;
		extern template TCStr<CStrTraits_CUStrVMem>;
#endif

	}
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

#include "Malterlib_String_Container_Format.h"

namespace NMib
{
	namespace NSys
	{
		namespace NStr
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
	}
}


#include "Malterlib_String_Container.hpp"
#include "Malterlib_String_Container_ImpDynamic.hpp"

namespace NMib
{
	namespace NStr
	{
		CStr fg_ForceStrUTF8(const CStr &_Str);
		CStr fg_ForceStrUTF8(const CWStr &_Str);
		CStr fg_ForceStrUTF8(const CUStr &_Str);
		bint fg_IsValidUTF8(CStr const &_Str);
		CWStr fg_ForceStrUTF16(const CWStr &_Str);
		CStr fg_ReplaceCharactersUTF8(CStr const &_Str, uch8 _ReplacementChar = '?');
		CStr fg_ReplaceSequenceUTF8(CStr const &_Str, CStr const &_ReplacementChar = CStr("\xef\xbf\xbd"));
		CStr fg_CleanUTF8(CStr const &_Str);
	}
	namespace NStr
	{
		struct CParseLocation
		{
			bool operator ==(CParseLocation const &_Right) const;
			void f_Format(NStr::CStrAggregate &o_FormatInto) const;
			
			template <typename tf_CStream>
			void f_Feed(tf_CStream &_Stream) const
			{
				_Stream << m_File;
				_Stream << m_Character;
				_Stream << m_Line;
				_Stream << m_Column;
			}
			
			template <typename tf_CStream>
			void f_Consume(tf_CStream &_Stream)
			{
				_Stream >> m_File;
				_Stream >> m_Character;
				_Stream >> m_Line;
				_Stream >> m_Column;
			}
			
			NStr::CStr m_File;
			zuint32 m_Character;
			zuint32 m_Line;
			zuint32 m_Column;
		};

		struct CParseError
		{
			bool operator ==(CParseError const &_Right) const;

			void f_Format(NStr::CStrAggregate &o_FormatInto) const;

			template <typename tf_CStream>
			void f_Feed(tf_CStream &_Stream) const
			{
				_Stream << m_Error;
				_Stream << m_Location;
			}

			template <typename tf_CStream>
			void f_Consume(tf_CStream &_Stream)
			{
				_Stream >> m_Error;
				_Stream >> m_Location;
			}
			
			CStr m_Error;
			CParseLocation m_Location;
		};
		
		DMibImpErrorSpecificClass(CExceptionParse, NMib::NException::CException, NContainer::TCVector<CParseError>);

#		define DMibErrorParse(d_Description, d_Specific) DMibImpErrorSpecific(NMib::NStr::CExceptionParse, d_Description, d_Specific)

#		ifndef DMibPNoShortCuts
#			define DErrorParse(d_Description, d_Specific) DMibErrorParse(d_Description, d_Specific)
#		endif

	}
}

