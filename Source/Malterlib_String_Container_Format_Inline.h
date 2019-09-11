// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
 	namespace NPrivate
	{
		template <typename t_CData, typename t_CFormatter>
		concept cHas_f_GetStringFormatType =
			requires
			(
				t_CData *_pData
				, t_CFormatter &_Formatter
			)
			{
				_pData->f_GetStringFormatType(_Formatter);
			}
		;

		template <typename t_CData, typename t_CFormatter>
		concept cHas_f_CreateStringFormatter =
			requires
			(
				t_CData const *_pData
				, t_CFormatter &_Formatter
			)
			{
				_pData->f_CreateStringFormatter(_Formatter);
			}
		;

		template <typename t_CData>
		concept cHas_f_Format =
			requires (t_CData const *_pData, CStr &o_Str)
			{
				_pData->f_Format(o_Str);
			}
			|| requires (t_CData const *_pData, CStr &o_Str, typename t_CData::CFormatOptions &_Options)
			{
				_pData->f_Format(o_Str, _Options);
			}
		;

		static_assert(cHas_f_Format<NContainer::TCVector<uint32>>);

		template <typename t_CFormatter, typename t_CData>
		struct TCStringFormatterHelper
		{
		public:
			static auto fs_CreateFormatType(t_CFormatter &_Formatter, t_CData &_Data)
			{
				if constexpr (cHas_f_GetStringFormatType<t_CData, t_CFormatter> && cHas_f_CreateStringFormatter<t_CData, t_CFormatter>)
					return fg_GetType<decltype(_Data.f_GetStringFormatType(_Formatter)) const &>();
				else if constexpr (cHas_f_Format<t_CData>)
					return fg_GetType<TCStrFormatType_Inline<t_CFormatter, t_CData, true> const &>();
				else
					return fg_GetType<typename TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>::CFormatType const &>();
			}

			using CFormatType = decltype(fs_CreateFormatType(fg_GetType<t_CFormatter &>(), fg_GetType<t_CData &>()));

			static auto fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data)
			{
				if constexpr (cHas_f_GetStringFormatType<t_CData, t_CFormatter> && cHas_f_CreateStringFormatter<t_CData, t_CFormatter>)
					return _Data.f_CreateStringFormatter(_Formatter);
				else if constexpr (cHas_f_Format<t_CData>)
				{
					using CFormatType = TCStrFormatType_Inline<t_CFormatter, t_CData, true>;
					_Formatter.template f_Alloc<CFormatType>(_Data);
					return typename CFormatType::CStrFormatTypeClassifier();
				}
				else
					return TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>::fs_CreateFormat(_Formatter, _Data);
			}
		};

		template <typename t_CFormatter, typename t_CData>
		struct TCStringFormatterHelper<t_CFormatter, TCByValue<t_CData>>
		{
		public:
			using CFormatType = TCStrFormatType_Inline<t_CFormatter, t_CData, false>;

			static inline_large auto fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<t_CData> const &_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(*_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};
	}

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

		virtual void f_Move(t_CFormatter &_Formatter) override
		{
			DMibFastCheck(!t_bReference); // Not supported
			if constexpr (!t_bReference)
				_Formatter.template f_Alloc<TCStrFormatType_Inline>(fg_Move(m_ToFormat));
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

		inline_small TCStrFormatType_Inline(t_CToFormat const &_ToFormat)
			: m_ToFormat(_ToFormat)
		{
		}

		inline_small TCStrFormatType_Inline(t_CToFormat &&_ToFormat)
			: m_ToFormat(fg_Move(_ToFormat))
		{
		}

		inline_small TCStrFormatType_Inline(t_CToFormat const *_pStr)
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
		static auto fs_GetFormatOptionsType(tf_CType const &_Type)
			requires requires(typename tf_CType::CFormatOptions const &_Options)
			{
				_Options;
			}
		{
			return typename tf_CType::CFormatOptions();
		}

		template <typename tf_CType>
		static auto fs_GetFormatOptionsType(tf_CType const &_Type)
		{
			return int(0);
		}

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
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const
			requires requires
			{
				_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option, _Args);
			}
		{
			if (_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option, _Args))
				return true;

			return CSuper::f_ParseOption(_Args, _Option);
		}

		template <typename t_CData, typename t_CFormatType, typename tf_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const
			requires requires
			{
				_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option);
			}
		{
			if (_Args.m_Data.f_FormatParseOption(_Args.m_Options.m_LocalOptions, _Option))
				return true;

			return CSuper::f_ParseOption(_Args, _Option);
		}

		template <typename t_CData, typename t_CFormatType, typename tf_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, tf_COptions> &_Args, COption &_Option) const
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

		static void fs_AddToStrStatic(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, const t_CToFormat &_Value, CLocalOptions &_Options)
		{
			fp_AddToStr(_String, _CurrentStrLen, _Options, _Value);
		}

		template <typename tf_COptions, typename tf_CToFormat>
		static inline_small void fp_AddToStr(TCStrAggregate<CTStrTraits> &_String, aint &_CurrentStrLen, tf_COptions &_Options, const tf_CToFormat &_Value)
		{
			if (_Options.m_bSimpleAlign && !_Options.f_RestrictLength())
			{
				_String.f_SetStrLen(_CurrentStrLen);
				if constexpr
					(
						requires
						{
							_Value.f_Format(_String, _Options);
						}
					)
				{
					_Value.f_Format(_String, _Options);
				}
				else
					_Value.f_Format(_String);

				_CurrentStrLen = _String.f_GetLen();
			}
			else
			{
				TCStr<CTStrTraits> Temp;

				if constexpr
					(
						requires
						{
							_Value.f_Format(Temp, _Options);
						}
					)
				{
					_Value.f_Format(Temp, _Options);
				}
				else
					_Value.f_Format(Temp);

				mint TempLen = Temp.f_GetLen();

				if (_Options.m_bSimpleAlign)
					CSuper::fs_AddSubStrToStrSimple(_String, _CurrentStrLen, _Options, Temp.f_GetStr(), TempLen);
				else
					CSuper::fs_AddSubStrToStr(_String, _CurrentStrLen, _Options, Temp.f_GetStr(), TempLen, 0);
			}
		}

		template <typename tf_CToFormat>
		static inline_small void fp_FormatInto(TCStrAggregate<CTStrTraits> &_String, const tf_CToFormat &_Value)
		{
			if constexpr
				(
					requires
					{
						_Value.f_Format(_String, fg_GetType<CLocalOptions &>());
					}
				)
			{
				CLocalOptions Options;
				_Value.f_Format(_String, Options);
			}
			else
			{
				_Value.f_Format(_String);
			}
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

		virtual void const *f_GetTypeID() const override
		{
			return &ms_TypeID;
		}

		virtual bool f_IsSame(void const *_pRight) const override
		{
			DMibFastCheck(false); // Not supported
			return false;
		}

		inline static bool const ms_TypeID = false;
	};
}
