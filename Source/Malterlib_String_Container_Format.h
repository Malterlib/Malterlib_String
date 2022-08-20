// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	static inline CStrNonTracked::CFormat fg_GetStringFormat(const ch8 *_pFormat)
	{
		return CStrNonTracked::CFormat(_pFormat);
	}

	static inline CWStrNonTracked::CFormat fg_GetStringFormat(const ch16 *_pFormat)
	{
		return CWStrNonTracked::CFormat(_pFormat);
	}

	static inline CUStrNonTracked::CFormat fg_GetStringFormat(const ch32 *_pFormat)
	{
		return CUStrNonTracked::CFormat(_pFormat);
	}

	template <typename tf_CFormat, typename... tfp_CParams>
	CStr fg_Format(tf_CFormat const &_Format, tfp_CParams &&...p_Params)
	{
		return fg_Format<CStr>(_Format, fg_Forward<tfp_CParams>(p_Params)...);
	}

	class CCompare_TStrNoCase
	{
	public:
		template <typename t_CKey0, typename t_CKey1>
		inline_small COrdering_Weak operator () (const t_CKey0 &_Left, const t_CKey1 &_Right) const
		{
			return fg_StrCmpNoCase(_Left, _Right) <=> 0;
		}
	};

	namespace NPrivate
	{
		template <typename t_CDataToTest, typename t_CClassToTestAgainst>
		class TCHasFormatClassHelper
		{
			static t_CDataToTest const &fs_GetData();
			static t_CClassToTestAgainst &fs_GetFormatClass();
			template <typename tf_CData>
			static auto fs_CheckFormat(tf_CData const& data) -> decltype(CStr::CFormat::fs_GetFormatClassifier(data).f_ClassifiedAs(fs_GetFormatClass()));
			template <typename tf_CData>
			static auto fs_CheckFormat(tf_CData &&) -> NTraits::CFalseBySize;
		public:
			enum
			{
				EValue = sizeof(fs_CheckFormat(fs_GetData())) == sizeof(NTraits::CTrueBySize)
			};
		};

	}

	template <typename t_CDataToTest, typename t_CClassToTestAgainst>
	class TCHasFormatClass : public NTraits::TCCompileTimeConstant<bool, NPrivate::TCHasFormatClassHelper<t_CDataToTest, t_CClassToTestAgainst>::EValue >
	{
	public:
	};
}
