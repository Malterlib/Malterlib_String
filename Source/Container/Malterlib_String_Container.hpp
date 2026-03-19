// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CTCStrTraits>
	template <typename tf_CData>
	inline_small void TCStr<t_CTCStrTraits>::f_SetAt(aint _Index, tf_CData _Character)
	{
		fg_StrSetAt(*this, _Index, _Character);
	}

	template <typename t_CTCStrTraits>
	ch32 TCStr<t_CTCStrTraits>::f_GetAt(aint _Index) const
	{
		DMibFastCheck(_Index <= CImp::f_GetStrLen());
		return f_GetStr()[_Index];
	}
#ifdef DMibDebuggerHelpers
	template <typename t_CTCStrTraits>
	TCStrTypeHelper<t_CTCStrTraits::CStrTraits::mc_Type> TCStr<t_CTCStrTraits>::fs_TypeDebugHelper()
	{
		return {};
	}
#endif

	template <typename t_TCStrTraits>
	TCStr<t_TCStrTraits>::CAddStrAgrs::CAddStrAgrs(aint &_StrLen, umint _Len)
		: m_StrLen(_StrLen)
		, m_Len(_Len)
	{
	}

	template <typename t_TCStrTraits>
	TCStr<t_TCStrTraits>::CAutoDestroy::CAutoDestroy(TCStr *_pThis)
		: mp_pThis(_pThis)
	{
	}

	template <typename t_TCStrTraits>
	TCStr<t_TCStrTraits>::CAutoDestroy::~CAutoDestroy()
	{
		if (mp_pThis)
			mp_pThis->f_Destroy();
	}

	template <typename t_TCStrTraits>
	void TCStr<t_TCStrTraits>::CAutoDestroy::f_Clear()
	{
		mp_pThis = nullptr;
	}

	template <typename t_TCStrTraits>
	inline_small void TCStr<t_TCStrTraits>::f_SetModified()
	{
		CImp::f_SetStrLen(-1);
	}

	template <typename t_TCStrTraits>
	inline_small auto TCStr<t_TCStrTraits>::f_GetStr() const -> CChar const *
	{
		return CImp::f_GetStr();
	}

	template <typename t_TCStrTraits>
	inline_small auto TCStr<t_TCStrTraits>::f_GetStrUniqueWritable() -> CChar *
	{
		CImp::f_MakeUnique();
		return CImp::f_GetStrWritable();
	}

	template <typename t_TCStrTraits>
	inline_small TCStr<t_TCStrTraits>::operator CChar const * () const
	{
		return CImp::f_GetStr();
	}

	template <typename t_TCStrTraits>
	inline_small TCStr<t_TCStrTraits>::operator bool () const
	{
		return !f_IsEmpty();
	}

	template <typename t_TCStrTraits>
	inline_small bool TCStr<t_TCStrTraits>::f_IsEmpty () const
	{
		return (*CImp::f_GetStr()) == 0;
	}

	template <typename t_TCStrTraits>
	auto TCStr<t_TCStrTraits>::f_Span() const -> TCStrSpan<typename CStrTraits::CTypes>
	{
		return TCStrSpan<typename CStrTraits::CTypes>(f_GetStr(), f_GetLen());
	};

	template <typename t_TCStrTraits>
	inline_large auto TCStr<t_TCStrTraits>::f_GetStr(umint _MaxLength) -> CChar *
	{
		umint CurrentLen = f_GetLen();
		umint MaxLen = CImp::f_CreateWritableBuffer((CurrentLen + 1) > (_MaxLength + 1) ? (CurrentLen + 1) : (_MaxLength + 1), false);
		if (MaxLen < _MaxLength)
			return nullptr;
		else
		{
			// Invalidate fg_StrLen
			CImp::f_SetStrLen(-2);
			CChar *pStr = CImp::f_GetStrWritable();
			return pStr;
		}
	}

	template <typename t_TCStrTraits>
	void TCStr<t_TCStrTraits>::f_TrimSize()
	{
		CImp::f_TrimSize(f_GetLen() + 1, 0);
	}

	template <typename t_TCStrTraits>
	inline_small aint TCStr<t_TCStrTraits>::f_GetLen() const
	{
		return CImp::f_GetStrLen();
	}

	template <typename t_TCStrTraits>
	inline_small umint TCStr<t_TCStrTraits>::f_GetSize() const /// Returns the memory size needed to save the string and its null terminator character in memory
	{
		return (f_GetLen() + 1) * sizeof(CChar);
	}

	template <typename t_TCStrTraits>
	TCStr<t_TCStrTraits> TCStr<t_TCStrTraits>::fs_ReadTextStream(NStream::CBinaryStream &_Stream, bool _bAssumeUTF8)
	{
		CStr Temp = fg_ReadTextStream(_Stream, _bAssumeUTF8);

		return TCStr<t_TCStrTraits>(Temp);
	}

	template <typename t_TCStrTraits>
	auto TCStr<t_TCStrTraits>::f_GetUnicodeIterator() const -> CUnicodeIterator
		requires (mc_Type != EStrType_Ansi)
	{
		return CUnicodeIterator(*this);
	}
}

#include "Malterlib_String_Container_Stream.hpp"
#include "Malterlib_String_Container_ParseType.hpp"
#include "Malterlib_String_Container_Parse.hpp"
#include "Malterlib_String_Container_Conversion.hpp"
#include "Malterlib_String_Container_Lifetime.hpp"
#include "Malterlib_String_Container_AlgorithmMethods.hpp"
#include "Malterlib_String_Container_ParseTraits.hpp"
#include "Malterlib_String_Container_Algorithm.hpp"
#include "Malterlib_String_Container_AlgorithmMethods.hpp"
#include "Malterlib_String_Container_Assign.hpp"
#include "Malterlib_String_Container_Concat.hpp"
#include "Malterlib_String_Container_Operator.hpp"
#include "Malterlib_String_Container_ImpDynamic.hpp"
