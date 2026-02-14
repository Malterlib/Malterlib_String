// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	struct TCStrFormatType_Inline final : public TICStrFormatType<t_CFormatter>
	{
		using CStrFormatTypeClassifier = CStrFormatTypeClassifier_String;
		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CChar = typename CTStrTraits::CStrTraits::CChar;
		using CStorageType = TCConditional<t_bReference, t_CToFormat const &, t_CToFormat>;
		using CReferenceType = TCConditional<t_bReference, t_CToFormat const &, t_CToFormat const &>;
		using CSuper = TICStrFormatType<t_CFormatter>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;
		using COptionsStatic = typename CSuper::COptionsStatic;
		using CVisitor = typename CSuper::CVisitor;
		using CType = t_CToFormat const &;

	private:
		template <typename tf_CType>
		static auto fsp_GetFormatOptionsType(tf_CType const &_Type)
			requires requires(typename tf_CType::CFormatOptions const &_Options)
			{
				_Options;
			}
		;

		template <typename tf_CType>
		static auto fsp_GetFormatOptionsType(tf_CType const &_Type);

	public:

		struct CLocalOptions : public COptions
		{
			using COptionsType = decltype(fsp_GetFormatOptionsType(fg_GetReference<t_CToFormat>()));

			CLocalOptions();

			COptionsType m_LocalOptions;
		};

		inline_small TCStrFormatType_Inline(t_CToFormat const &_ToFormat);
		inline_small TCStrFormatType_Inline(t_CToFormat &&_ToFormat);
		inline_small TCStrFormatType_Inline(t_CToFormat const *_pStr);

		virtual mint f_Destruct() override;
		virtual void f_Move(t_CFormatter &_Formatter) override;
		virtual void f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;
		virtual void f_Visit(CVisitor &_Extractor) const override;
		virtual void const *f_GetTypeID() const override;
		virtual bool f_IsSame(void const *_pRight) const override;

		static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, t_CToFormat const &_Value);
		static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, t_CToFormat const &_Value, CLocalOptions &_Options);

		template <typename t_CData, typename t_CFormatType, typename tf_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const
			requires requires
			{
				_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option, _Args);
			}
		;

		template <typename t_CData, typename t_CFormatType, typename tf_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const
			requires requires
			{
				_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option);
			}
		;

		template <typename t_CData, typename t_CFormatType, typename tf_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const;

		constexpr static bool mc_bNeedDestruct = !t_bReference;

	private:
		template <typename tf_COptions, typename tf_CToFormat>
		static inline_small void fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, tf_CToFormat const &_Value);

		template <typename tf_CToFormat>
		static inline_small void fp_FormatInto(TCStr<CTStrTraits> &_String, tf_CToFormat const &_Value);

		CStorageType mp_ToFormat;

		inline static bool constexpr mcp_TypeID = false;
	};
}

#include "Container/Malterlib_String_Container_Format_Inline.hpp"
