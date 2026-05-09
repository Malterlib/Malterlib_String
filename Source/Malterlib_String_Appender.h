// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CString>
	struct TCStringAppender
	{
		using CString = t_CString;

		TCStringAppender(t_CString &_String);
		~TCStringAppender();

		struct CCommitted
		{
			t_CString &m_String;

			CCommitted(TCStringAppender &_Appender);
			~CCommitted();

			void f_Abort();

		private:
			TCStringAppender *mp_pAppender;
		};

		void operator += (typename t_CString::CUnsignedChar _Character);
		void operator += (t_CString const &_String);
		template <umint tf_ArrayLength>
		void operator += (typename t_CString::CChar const (&_Array)[tf_ArrayLength]);
		template <typename tf_CStrTraits>
		void operator += (NStr::TCStr<tf_CStrTraits> const &_String);

		template <typename tf_CPointer>
		requires
		(
			NTraits::cIsPointer<NTraits::TCRemoveReferenceAndQualifiers<tf_CPointer>>
			&& NTraits::cIsSame
			<
				NTraits::TCRemoveReferenceAndQualifiers
				<
					NTraits::TCRemovePointer<NTraits::TCRemoveReferenceAndQualifiers<tf_CPointer>>
				>
				, typename t_CString::CChar
			>
		)
		void operator += (tf_CPointer const &_pString);

		void f_AddUnicodeChar(ch32 _Character);
		void f_AddChar(typename t_CString::CUnsignedChar _Character);
		void f_AddString(typename t_CString::CChar const *_pString, umint _Len);
		void f_AddNullTerminatedString(typename t_CString::CChar const *_pString);

		CCommitted f_Commit();
		umint f_GetStrLen() const;
		bool f_IsEmpty() const;

	private:
		void fp_Reset();
		void fp_Commit();

		t_CString &mp_String;
		umint mp_StrLen;
		umint mp_MaxLen;
		typename t_CString::CUnsignedChar *mp_pStrOut;
		bool mp_bChanged;
	};
}

#include "Malterlib_String_Appender.hpp"
