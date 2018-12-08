// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CFormatter, typename t_CToFormat, bool t_bReference>
	class TCStrFormatType_Inline final : public TICStrFormatType<t_CFormatter>
	{
	public:

		typedef CStrFormatTypeClassifier_String CStrFormatTypeClassifier;

		virtual mint f_Delete() override
		{
			if constexpr (mc_bNeedDelete)
				this->~TCStrFormatType_Inline();
			return sizeof(*this);
		}

		typedef typename t_CFormatter::CTStrTraits CTStrTraits;
		typedef typename CTStrTraits::CStrTraits::CChar CChar;

		typedef typename TCChooseType<t_bReference, const t_CToFormat &, t_CToFormat>::CType CStorageType;
		typedef typename TCChooseType<t_bReference, const t_CToFormat &, const t_CToFormat &>::CType CReferenceType;

		enum
		{
			mc_bNeedDelete = !t_bReference
		};

		CStorageType m_ToFormat;

		inline_small TCStrFormatType_Inline(const t_CToFormat &_ToFormat)
			: m_ToFormat(_ToFormat)
		{
		}

		inline_small TCStrFormatType_Inline(const t_CToFormat *_pStr)
			: m_ToFormat(*_pStr)
		{
		}

		typedef TICStrFormatType<t_CFormatter> CSuper;
		typedef typename CSuper::COption COption;
		typedef typename CSuper::COptions COptions;
		typedef typename CSuper::COptionsStatic COptionsStatic;
		typedef typename CSuper::CVisitor CVisitor;

		typedef const t_CToFormat &CType;

		template <typename tf_CType>
		static typename TCEnableIf
			<
				NPrivate::TCHasMember_f_FormatParseOption<tf_CType>::mc_Value
				, typename tf_CType::CFormatOptions
			>::CType fs_GetFormatOptionsType(tf_CType const &_Type)
		;

		template <typename tf_CType>
		static typename TCEnableIf
			<
				!NPrivate::TCHasMember_f_FormatParseOption<tf_CType>::mc_Value
				, int
			>::CType fs_GetFormatOptionsType(tf_CType const &_Type)
		;


		struct CLocalOptions : public COptions
		{
			using COptionsType = decltype(fs_GetFormatOptionsType(fg_GetReference<t_CToFormat>()));
			COptionsType m_LocalOptions;

			CLocalOptions()
				: COptions(COptionsStatic())
			{
			}
		};

		template <typename t_CData, typename t_CFormatType, typename tf_COptions>
		inline_small auto f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const
			-> typename TCEnableIf
			<
				NPrivate::TCHasMember_f_FormatParseOption<t_CData>::mc_Value
				&& !NTraits::TCIsVoid<decltype(_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option, _Args))>::mc_Value
				, aint
			>::CType
		{
			if (_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option, _Args))
				return true;

			return CSuper::f_ParseOption(_Args, _Option);
		}

		template <typename t_CData, typename t_CFormatType, typename tf_COptions>
		inline_small auto f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const
			-> typename TCEnableIf
			<
				NPrivate::TCHasMember_f_FormatParseOption<t_CData>::mc_Value
				&& !NTraits::TCIsVoid<decltype(_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option))>::mc_Value
				, aint
			>::CType
		{
			if (_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option))
				return true;

			return CSuper::f_ParseOption(_Args, _Option);
		}

		template <typename t_CData, typename t_CFormatType, typename tf_COptions>
		inline_small typename TCEnableIf<!NPrivate::TCHasMember_f_FormatParseOption<t_CData>::mc_Value, aint>::CType f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const
		{
			return CSuper::f_ParseOption(_Args, _Option);
		}

		virtual void f_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const override
		{
			CLocalOptions Options;

			if (_pFormat)
			{
				TICStrFormatType_ParseOptionsArgs<CReferenceType, TCStrFormatType_Inline, CLocalOptions> Args(m_ToFormat, *this, _String, _CurrentStrLen, Options, _ArgData);
				CSuper::fs_ParseOptions(Args, _pFormat);
			}

			fp_AddToStr(_String, _CurrentStrLen, Options, m_ToFormat);

		}
		static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const t_CToFormat &_Value)
		{
			CLocalOptions Options;
			fp_AddToStr(_String, _CurrentStrLen, Options, _Value);
		}

		template <typename tf_COptions, typename tf_CToFormat>
		static inline_small typename TCEnableIf<NPrivate::TCHasMember_f_FormatParseOption<tf_CToFormat>::mc_Value, void>::CType
		fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, const tf_CToFormat &_Value)
		{
			if (_Options.m_bSimpleAlign && !_Options.f_RestrictLength())
			{
				_String.f_SetStrLen(_CurrentStrLen);
				_Value.f_Format(_String, _Options);
				_CurrentStrLen = _String.f_GetLen();
			}
			else
			{
				TCStr<CTStrTraits> Temp;

				_Value.f_Format(Temp, _Options);

				mint TempLen = Temp.f_GetLen();

				if (_Options.m_bSimpleAlign)
					CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, Temp.f_GetStr(), TempLen);
				else
					CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, Temp.f_GetStr(), TempLen, 0);
			}
		}

		template <typename tf_COptions, typename tf_CToFormat>
		static inline_small typename TCEnableIf<!NPrivate::TCHasMember_f_FormatParseOption<tf_CToFormat>::mc_Value, void>::CType
		fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, const tf_CToFormat &_Value)
		{
			if (_Options.m_bSimpleAlign && !_Options.f_RestrictLength())
			{
				_String.f_SetStrLen(_CurrentStrLen);
				_Value.f_Format(_String);
				_CurrentStrLen = _String.f_GetLen();
			}
			else
			{
				TCStr<CTStrTraits> Temp;

				_Value.f_Format(Temp);

				mint TempLen = Temp.f_GetLen();

				if (_Options.m_bSimpleAlign)
					CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, Temp.f_GetStr(), TempLen);
				else
					CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, Temp.f_GetStr(), TempLen, 0);
			}
		}

		template <typename tf_CToFormat>
		static inline_small typename TCEnableIf<!NPrivate::TCHasMember_f_FormatParseOption<tf_CToFormat>::mc_Value, void>::CType
		fp_FormatInto(TCStrAggregate<CTStrTraits> &_String, const tf_CToFormat &_Value)
		{
			_Value.f_Format(_String);
		}



		template <typename tf_CToFormat>
		static inline_small typename TCEnableIf<NPrivate::TCHasMember_f_FormatParseOption<tf_CToFormat>::mc_Value, void>::CType
		fp_FormatInto(TCStrAggregate<CTStrTraits> &_String, const tf_CToFormat &_Value)
		{
			CLocalOptions Options;
			_Value.f_Format(_String, Options);
		}

		virtual aint f_Get_aint() const override
		{
			TCStr<CTStrTraits> Temp;
			fp_FormatInto(Temp, m_ToFormat);
			return CTStrTraits::CStrTraits::fs_StrToInt(Temp.f_GetStr(), (aint)0);
		}

		virtual fp32 f_Get_fp32() const override
		{
			TCStr<CTStrTraits> Temp;
			fp_FormatInto(Temp, m_ToFormat);
			return CTStrTraits::CStrTraits::fs_StrToFloatExact(Temp.f_GetStr(), (fp32)0);
		}

		virtual fp64 f_Get_fp64() const override
		{
			TCStr<CTStrTraits> Temp;
			fp_FormatInto(Temp, m_ToFormat);
			return CTStrTraits::CStrTraits::fs_StrToFloatExact(Temp.f_GetStr(), (fp64)0);
		}

		virtual void f_Visit(CVisitor &_Extractor) const override
		{
			TCStr<CTStrTraits> Temp;
			fp_FormatInto(Temp, m_ToFormat);
			_Extractor(Temp.f_GetStr());
		}
	};
}
