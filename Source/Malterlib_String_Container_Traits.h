// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CChar, CStrTypeUnderlying t_Type>
	struct TCStrTraitsTypes
	{
		using CChar = t_CChar;
		constexpr static EStrType const mc_Type = (EStrType)t_Type;
	};

	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	struct TCStrTraits
	{
		using CChar = t_CChar;
		constexpr static EStrType mc_Type = (EStrType)t_Type;
		using CTypes = TCStrTraitsTypes<t_CChar, t_Type>;
		using CParams = t_CParams;
		using CAllocator = typename t_CParams::CAllocator;

		template <typename tf_CData>
		static inline_small bool fs_CharIsNumber(tf_CData const _Character);
		template <typename tf_CData>
		static inline_small tf_CData fs_CharUpperCase(tf_CData _Character);
		template <typename tf_CData>
		static inline_small tf_CData fs_CharLowerCase(tf_CData _Character);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToIntBase10ParseNoSign(tf_CData const * &_pStr, tf_CReturn _FailValue);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToIntBase10NoSign(tf_CData const *_pStr, tf_CReturn _FailValue);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToIntBase10(tf_CData const *_pStr, tf_CReturn _FailValue);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToIntParse
			(
				tf_CData const * &_pStr
				, tf_CReturn _FailValue
				, tf_CData const *_pStrTerminators = nullptr
				, bool _bDontFail = false
				, int32 _ParseMode = EStrToIntParseMode_Base10
			)
		;
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToIntParseHex(tf_CData const * &_pStr, tf_CReturn _FailValue);
		template<typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToIntParseHex(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CData _Terminator);
		template <typename tf_CData>
		static inline_small mint fs_StrLen(tf_CData const *_pStr);
		template <typename tf_CData>
		static inline_small mint fs_StrLen(tf_CData const *_pStr, mint _MaxLen);
		template <typename tf_CData1, typename tf_CData2>
		static inline_small tf_CData1 *fs_StrUpperCase(tf_CData1 *_pDest, tf_CData2 const *_pSource, aint _SourceLen);
		template <typename tf_CData1, typename tf_CData2>
		static inline_small tf_CData1 *fs_StrLowerCase(tf_CData1 *_pDest, tf_CData2 const *_pSource, aint _SourceLen);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToInt(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators = nullptr);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToIntExact(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators = nullptr);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToFloat(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators = nullptr);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToFloatExact(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators = nullptr);
		template <typename tf_CData, typename tf_CReturn>
		static inline_small tf_CReturn fs_StrToFloatParse(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CData const *_pStrTerminators, bool _bDontFail = false);
	};
}

#include "Container/Malterlib_String_Container_Traits.hpp"
