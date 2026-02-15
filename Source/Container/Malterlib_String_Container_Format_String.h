// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CStrDataType, CStrTypeUnderlying t_Type>
	struct TCStrFormatType_String final : public TICStrFormatType<t_CFormatter>
	{
	public:
		static_assert(t_Type != EStrType_Ansi);

		using CStrFormatTypeClassifier = CStrFormatTypeClassifier_String;
		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CChar = typename CTStrTraits::CStrTraits::CChar;
		using CType = t_CStrDataType const *;
		using CSuper = TICStrFormatType<t_CFormatter>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;
		using COptionsStatic = typename CSuper::COptionsStatic;
		using CVisitor = typename CSuper::CVisitor;

		class COptionsStr : public COptions
		{
		public:
			enum ECase
			{
				ECase_Default = 0
				, ECase_Upper
				, ECase_Lower
				, ECase_Capitalize
				, ECase_Decapitalize
			};

			aint m_Case;

			inline_small COptionsStr();
		};

		inline_medium TCStrFormatType_String(t_CStrDataType const *_pStr);
		inline_small TCStrFormatType_String(t_CStrDataType const *_pStr, aint _StrLen);
		inline_small TCStrFormatType_String(t_CStrDataType const *_pStr, aint _StrLen, bool _bCheckSize);

		virtual mint f_Destruct() override;
		virtual void f_Move(t_CFormatter &_Formatter) override;
		virtual void f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;
		virtual void f_Visit(CVisitor &_Extractor) const override;
		virtual void const *f_GetTypeID() const override;
		virtual bool f_IsSame(void const *_pRight) const override;

		static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, t_CStrDataType const *_pValue);
		static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, t_CStrDataType const *_pValue, COptionsStr &_Options);

		template <typename t_CData, typename t_CFormatType, typename t_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, COption &_Option) const;

		constexpr static bool mc_bNeedDestruct = false;

	private:
		template <CStrTypeUnderlying tf_DestinationType, CStrTypeUnderlying tf_SourceType, typename t_COptions>
		static inline_small auto fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, CChar const *_pValue, mint _StrLen)
			-> TCEnableIf<tf_DestinationType == tf_SourceType, void>
		;

		template <CStrTypeUnderlying tf_DestinationType, CStrTypeUnderlying tf_SourceType, typename t_COptions, typename tf_CStrDataType>
		static inline_small void fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, t_COptions &_Options, tf_CStrDataType const *_pValue, mint _StrLen);

		inline static bool constexpr mcp_TypeID = false;

		t_CStrDataType const *mp_pStr;
		mint mp_StrLen;
	};

}

#include "Malterlib_String_Container_Format_String.hpp"

namespace NMib::NStr
{
	DMibStrStringFormatterImplementStr(ch8, EStrType_UTF);
#ifdef DMibPUniqueType_ch16
	DMibStrStringFormatterImplementStr(ch16, EStrType_UTF);
#endif
	DMibStrStringFormatterImplementStr(ch32, EStrType_Unicode);
	DMibStrStringFormatterImplementStr(uint16, EStrType_UTF);
	DMibStrStringFormatterImplementStr(const ch8, EStrType_UTF);
#ifdef DMibPUniqueType_ch16
	DMibStrStringFormatterImplementStr(const ch16, EStrType_UTF);
#endif
	DMibStrStringFormatterImplementStr(const ch32, EStrType_Unicode);
	DMibStrStringFormatterImplementStr(const uint16, EStrType_UTF);

	DMibStrStringFormatterImplementStrArray(ch8, EStrType_UTF);
#ifdef DMibPUniqueType_ch16
	DMibStrStringFormatterImplementStrArray(ch16, EStrType_UTF);
#endif
	DMibStrStringFormatterImplementStrArray(ch32, EStrType_Unicode);
	DMibStrStringFormatterImplementStrArray(uint16, EStrType_UTF);
	DMibStrStringFormatterImplementStrArray(const ch8, EStrType_UTF);
#ifdef DMibPUniqueType_ch16
	DMibStrStringFormatterImplementStrArray(const ch16, EStrType_UTF);
#endif
	DMibStrStringFormatterImplementStrArray(const ch32, EStrType_Unicode);
	DMibStrStringFormatterImplementStrArray(const uint16, EStrType_UTF);
}
