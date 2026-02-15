// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CStrTraitsIn, bool t_bReference>
	struct TCStrFormatType_TStr final : public TICStrFormatType<t_CFormatter>
	{
		using CStrFormatTypeClassifier = CStrFormatTypeClassifier_String;
		using CTStrTraits = typename t_CFormatter::CTStrTraits;
		using CChar = typename CTStrTraits::CStrTraits::CChar;
		using CStorageType = TCConditional<t_bReference, TCStr<t_CStrTraitsIn> const &, TCStr<t_CStrTraitsIn>>;
		using CReferenceType = TCConditional<t_bReference, TCStr<t_CStrTraitsIn> const &, TCStr<t_CStrTraitsIn> const &>;

		using CType = TCStr<t_CStrTraitsIn> const &;
		using CCharIn = typename t_CStrTraitsIn::CStrTraits::CChar;

		using CSuper = TICStrFormatType<t_CFormatter>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;
		using COptionsStatic = typename CSuper::COptionsStatic;
		using CVisitor = typename CSuper::CVisitor;

		struct COptionsStr : public COptions
		{
			enum ECase
			{
				ECase_Default = 0
				, ECase_Upper
				, ECase_Lower
				, ECase_Capitalize
				, ECase_Decapitalize
			};

			inline_small COptionsStr();

			ECase m_Case = ECase_Default;
		};

		inline_small TCStrFormatType_TStr(TCStr<t_CStrTraitsIn> const &_Str);
		inline_small TCStrFormatType_TStr(TCStr<t_CStrTraitsIn> &&_Str);
		inline_small TCStrFormatType_TStr(TCStr<t_CStrTraitsIn> const *_pStr);

		virtual mint f_Destruct() override;
		virtual void f_Move(t_CFormatter &_Formatter) override;
		virtual void f_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, CChar const *_pFormat, t_CFormatter const &_ArgData) const override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;
		virtual void f_Visit(CVisitor &_Extractor) const override;
		virtual void const *f_GetTypeID() const override;
		virtual bool f_IsSame(void const *_pRight) const override;

		static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, TCStr<t_CStrTraitsIn> const &_Value);
		static void fs_AddToStrStatic(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, TCStr<t_CStrTraitsIn> const &_Value, COptionsStr &_Options);

		template <typename tf_CData, typename tf_CFormatType, typename tf_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, COption &_Option) const;

		constexpr static bool mc_bNeedDestruct = !t_bReference;

	private:
		template <typename tf_COptions>
		static inline_small void fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, TCStr<CTStrTraits> const &_Value);

		template <typename tf_COptions, typename tf_CStrTraitsIn>
		static inline_small void fp_AddToStr(TCStr<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, TCStr<tf_CStrTraitsIn> const &_Value);

		CStorageType mp_TStr;

		inline static bool constexpr mcp_TypeID = false;
	};

	template <typename t_CFormatter, typename t_CStrTraitsIn>
	struct TCStringFormatter<t_CFormatter, TCStr<t_CStrTraitsIn> >
	{
		using CFormatType = TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, true>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCStr<t_CStrTraitsIn> const&_Data);
	};

	template <typename t_CFormatter, typename t_CStrTraitsIn>
	struct TCStringFormatter<t_CFormatter, TCByValue<TCStr<t_CStrTraitsIn>> >
	{
		using CFormatType = TCStrFormatType_TStr<t_CFormatter, t_CStrTraitsIn, false>;

		template <typename tf_CTypeWithConst>
		static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<TCStr<t_CStrTraitsIn>> const&_Data);
	};
}

#include "Malterlib_String_Container_Format_StringContainer.hpp"
