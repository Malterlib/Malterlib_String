// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	class TICStrFormatType_StaticOptions
	{
	public:
		inline_small static bool f_RestrictLength()
		{
			return false;
		}
		inline_small static mint f_MinLength()
		{
			return 0;
		}
		inline_small static mint f_MaxLength()
		{
			return TCLimitsInt<mint>::mc_Max;
		}
		inline_small static aint f_Align()
		{
			return 0;
		}
		inline_small static bool f_LeftAlign()
		{
			return false;
		}
		inline_small static bool f_SimpleAlign()
		{
			return true;
		}
		inline_small static ch8 f_Fillout()
		{
			return ' ';
		}
	};

	template <mint t_MinLength, typename t_CParent>
	class TICStrFormatType_StaticOptions_MinLength : public t_CParent
	{
	public:

		inline_small TICStrFormatType_StaticOptions_MinLength(const t_CParent &_Parent)
			: t_CParent(_Parent)
		{
		}

		inline_small static mint f_MinLength()
		{
			return t_MinLength;
		}

		inline_small static bool f_RestrictLength()
		{
			return true;
		}
	};

	template <mint t_MaxLength, typename t_CParent>
	class TICStrFormatType_StaticOptions_MaxLength : public t_CParent
	{
	public:

		inline_small TICStrFormatType_StaticOptions_MaxLength(const t_CParent &_Parent)
			: t_CParent(_Parent)
		{
		}

		inline_small static mint f_MaxLength()
		{
			return t_MaxLength;
		}

		inline_small static bool f_RestrictLength()
		{
			return true;
		}
	};

	template <ch32 t_FillOut, typename t_CParent>
	class TICStrFormatType_StaticOptions_FillOut : public t_CParent
	{
	public:

		inline_small TICStrFormatType_StaticOptions_FillOut (const t_CParent &_Parent)
			: t_CParent(_Parent)
		{
		}

		inline_small static ch32 f_Fillout()
		{
			return t_FillOut;
		}
	};

	template <typename t_COptions, typename t_CIntType>
	class TCValueWithOptions : public t_COptions
	{
	public:
		typedef t_COptions COptions;
		const t_CIntType &m_Int;
		inline_small TCValueWithOptions(const t_CIntType &_Int, t_COptions const &_Options)
			: t_COptions(_Options)
			, m_Int(_Int)
		{
		}

		inline_small const t_CIntType & f_GetValue() const
		{
			return m_Int;
		}
		inline_small const COptions & f_GetOptions() const
		{
			return *this;
		}
		inline_small COptions & f_GetOptions()
		{
			return *this;
		}
		inline_small operator const t_CIntType & () const
		{
			return m_Int;
		}
	};

	template <mint t_MinLength, typename t_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_MinLength<t_MinLength, TICStrFormatType_StaticOptions>, t_CValueType> fg_FormatMinLength(const t_CValueType &_Value)
	{
		return TCValueWithOptions
				<
					TICStrFormatType_StaticOptions_MinLength
						<
							t_MinLength,
							TICStrFormatType_StaticOptions
						>,
					t_CValueType
				>
			(_Value, TICStrFormatType_StaticOptions_MinLength<t_MinLength, TICStrFormatType_StaticOptions>(TICStrFormatType_StaticOptions()));
	}

	template <mint t_MinLength, typename t_CValueType, typename t_COldOptions>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_MinLength<t_MinLength, t_COldOptions>, t_CValueType> fg_FormatMinLength(const TCValueWithOptions<t_COldOptions, t_CValueType> &_Value)
	{
		return TCValueWithOptions
				<
					TICStrFormatType_StaticOptions_MinLength
						<
							t_MinLength,
							t_COldOptions
						>,
					t_CValueType
				>
			(_Value.f_GetValue(), TICStrFormatType_StaticOptions_MinLength<t_MinLength, t_COldOptions>(_Value.f_GetOptions()));
	}


	template <mint t_MaxLength, typename t_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, TICStrFormatType_StaticOptions>, t_CValueType> fg_FormatMaxLength(const t_CValueType &_Value)
	{
		return TCValueWithOptions
				<
					TICStrFormatType_StaticOptions_MaxLength
						<
							t_MaxLength,
							TICStrFormatType_StaticOptions
						>,
					t_CValueType
				>
			(_Value, TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, TICStrFormatType_StaticOptions>(TICStrFormatType_StaticOptions()));
	}

	template <mint t_MaxLength, typename t_CValueType, typename t_COldOptions>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, t_COldOptions>, t_CValueType> fg_FormatMaxLength(const TCValueWithOptions<t_COldOptions, t_CValueType> &_Value)
	{
		return TCValueWithOptions
				<
					TICStrFormatType_StaticOptions_MaxLength
						<
							t_MaxLength,
							t_COldOptions
						>,
					t_CValueType
				>
			(_Value.f_GetValue(), TICStrFormatType_StaticOptions_MaxLength<t_MaxLength, t_COldOptions>(_Value.f_GetOptions()));
	}

	template <ch32 t_FillOut, typename t_CValueType>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_FillOut<t_FillOut, TICStrFormatType_StaticOptions>, t_CValueType> fg_FormatFillOut(const t_CValueType &_Value)
	{
		return TCValueWithOptions
				<
					TICStrFormatType_StaticOptions_FillOut
						<
							t_FillOut,
							TICStrFormatType_StaticOptions
						>,
					t_CValueType
				>
			(_Value, TICStrFormatType_StaticOptions_FillOut<t_FillOut, TICStrFormatType_StaticOptions>(TICStrFormatType_StaticOptions()));
	}

	template <ch32 t_FillOut, typename t_CValueType, typename t_COldOptions>
	inline_small TCValueWithOptions<TICStrFormatType_StaticOptions_FillOut<t_FillOut, t_COldOptions>, t_CValueType> fg_FormatFillOut(const TCValueWithOptions<t_COldOptions, t_CValueType> &_Value)
	{
		return TCValueWithOptions
				<
					TICStrFormatType_StaticOptions_FillOut
						<
							t_FillOut,
							t_COldOptions
						>,
					t_CValueType
				>
			(_Value.f_GetValue(), TICStrFormatType_StaticOptions_FillOut<t_FillOut, t_COldOptions>(_Value.f_GetOptions()));
	}




	template <typename t_CChar>
	class TICStrFormatType_Options
	{
	public:
		mint m_MaxLength;
		aint m_Align;
		uint32 m_MinLength:30;
		uint32 m_bLeftAlign:1;
		uint32 m_bSimpleAlign:1;
		t_CChar m_Fillout;

		template <typename t_CInitializer>
		inline_medium TICStrFormatType_Options(t_CInitializer const &_Init)
			: m_MaxLength(_Init.f_MaxLength())
			, m_Align(_Init.f_Align())
			, m_MinLength(_Init.f_MinLength())
			, m_bLeftAlign(_Init.f_LeftAlign())
			, m_bSimpleAlign(_Init.f_SimpleAlign())
			, m_Fillout(_Init.f_Fillout())
		{
		}

		inline_small static bool f_RestrictLength()
		{
			return true;
		}

		inline_small mint f_MinLength() const
		{
			return m_MinLength;
		}
		inline_small mint f_MaxLength() const
		{
			return m_MaxLength;
		}
		inline_small aint f_Align() const
		{
			return m_Align;
		}
		inline_small bool f_LeftAlign() const
		{
			return m_bLeftAlign;
		}
		inline_small bool f_SimpleAlign() const
		{
			return m_bSimpleAlign;
		}
		inline_small t_CChar f_Fillout() const
		{
			return m_Fillout;
		}
	};


	template <typename t_CData, typename t_CFormatType, typename t_COptions>
	class TICStrFormatType_ParseOptionsArgs
	{
	public:
		typedef typename t_CFormatType::CStrAggregate CStrAggregate;
		typedef typename t_CFormatType::CFormatter CFormatter;
		TICStrFormatType_ParseOptionsArgs(t_CData &_Data, const t_CFormatType &_FormatType, CStrAggregate &_String, aint &_CurrentStrLen, t_COptions &_Options, const CFormatter &_Formatter)
			: m_Data(_Data)
			, m_FormatType(_FormatType)
			, m_String(_String)
			, m_CurrentStrLen(_CurrentStrLen)
			, m_Options(_Options)
			, m_Formatter(_Formatter)
		{
		}

		t_CData &m_Data;
		const t_CFormatType &m_FormatType;
		CStrAggregate &m_String;
		aint &m_CurrentStrLen;
		t_COptions &m_Options;
		const CFormatter &m_Formatter;
	};


	template <typename t_CFormatter>
	class TICStrFormatType
	{
	public:
		typedef CDefaultStrFormatTypeClassifier CStrFormatTypeClassifier;
		virtual mint f_Delete() = 0;

		//	virtual void
		typedef t_CFormatter CFormatter;
		typedef typename t_CFormatter::CStrAggregate::CStrTraits::CChar CChar;
		typedef typename t_CFormatter::CStrAggregate CStrAggregate;
		typedef typename t_CFormatter::CStr CStr;
		typedef typename t_CFormatter::CStrAggregate::CStrTraits CStrTraits;

		typedef TICStrFormatType_Options<CChar> COptions;
		typedef TICStrFormatType_StaticOptions COptionsStatic;

		TICStrFormatType *m_pNextFormat;

		const TICStrFormatType *f_GetPtr() const
		{
			return this;
		}


		virtual void f_AddToStr(CStrAggregate &_String, aint &_CurrentStrLen, const CChar *_pFormat, const t_CFormatter & _ArgData) const = 0;

		virtual aint f_Get_aint() const = 0;
		virtual fp32 f_Get_fp32() const = 0;
		virtual fp64 f_Get_fp64() const = 0;

		class CVisitor
		{
		public:
			virtual void operator () (uint32 _Value) = 0;
			virtual void operator () (uint64 _Value) = 0;
			virtual void operator () (int32 _Value) = 0;
			virtual void operator () (int64 _Value) = 0;
			virtual void operator () (fp32 _Value) = 0;
			virtual void operator () (fp64 _Value) = 0;
			virtual void operator () (CChar const *_pValue) = 0;
			virtual void operator () () {}
		};

		class CVisitorInteger : public CVisitor
		{
		public:
			virtual void operator () (fp32 _Value) {}
			virtual void operator () (fp64 _Value) {}
			virtual void operator () (CChar const *_pValue) {}
		};

		class CVisitorFloat : public CVisitor
		{
		public:
			virtual void operator () (uint32 _Value) {}
			virtual void operator () (uint64 _Value) {}
			virtual void operator () (int32 _Value) {}
			virtual void operator () (int64 _Value) {}
			virtual void operator () (CChar const *_pValue) {}
		};

		class CVisitorNumber : public CVisitor
		{
		public:
			virtual void operator () (CChar const *_pValue) {}
		};

		class CVisitorString : public CVisitor
		{
		public:
			virtual void operator () (uint32 _Value) {}
			virtual void operator () (uint64 _Value) {}
			virtual void operator () (int32 _Value) {}
			virtual void operator () (int64 _Value) {}
			virtual void operator () (fp32 _Value) {}
			virtual void operator () (fp64 _Value) {}
		};

		virtual void f_Visit(CVisitor &_Extractor) const = 0;

		class COption
		{
		public:

			const CChar *m_pDataStart;

			class CFormatTypes
			{
			public:
				ch32 m_Format1;
				ch32 m_Format2;
			};

			union
			{
				CFormatTypes m_FormatTypes;
				uint32 m_FormatWhole;
			};

			void f_GetData_Str(CChar *_pDestStr, aint _MaxChars) const
			{
				const CChar *pParseStr = m_pDataStart;

				// Parse for characters, and end if , or } is found
				while ((*pParseStr) && ((*pParseStr) != ',') && ((*pParseStr) != '}') && (_MaxChars > 1))
				{
					*_pDestStr = *pParseStr;
					++pParseStr;
					++_pDestStr;
					--_MaxChars;
				}

				// Null terminate
				if (_MaxChars > 0)
					*_pDestStr = 0;
			}

			aint f_GetData_aint(const t_CFormatter & _ArgData, aint _FailValue) const
			{
				const CChar *pDataStart = m_pDataStart;
				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrFormatType * pFormatVar = _ArgData.f_GetArg(ArgNumber);
					if (pFormatVar)
					{
						return pFormatVar->f_Get_aint();
					}
					else
						return _FailValue;
				}
				else
				{
					return CStrTraits::fs_StrToIntBase10(m_pDataStart, _FailValue);
				}
			}

			aint f_GetData_aint_NotSigned(const t_CFormatter & _ArgData, aint _FailValue) const
			{
				const CChar *pDataStart = m_pDataStart;
				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrFormatType * pFormatVar = _ArgData.f_GetArg(ArgNumber);
					if (pFormatVar)
					{
						return pFormatVar->f_Get_aint();
					}
					else
						return _FailValue;
				}
				else
				{
					return (aint)CStrTraits::fs_StrToIntBase10NoSign(m_pDataStart, (mint)_FailValue);
				}
			}

			fp32 f_GetData_fp32(const t_CFormatter & _ArgData, fp32 _FailValue) const
			{
				const CChar *pDataStart = m_pDataStart;
				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrFormatType * pFormatVar = _ArgData.f_GetArg(ArgNumber);
					if (pFormatVar)
					{
						return pFormatVar->f_Get_fp32();
					}
					else
						return _FailValue;
				}
				else
				{
					static const CChar Terminators[] = {',','}',0};

					return CStrTraits::fs_StrToFloatExact(m_pDataStart, _FailValue, Terminators);
				}
			}

			fp64 f_GetData_fp64(const t_CFormatter & _ArgData, fp64 _FailValue) const
			{
				const CChar *pDataStart = m_pDataStart;
				if (*pDataStart == '*')
				{
					aint ArgNumber;
					if (CStrTraits::fs_CharIsNumber(*(pDataStart + 1)))
						ArgNumber = CStrTraits::fs_StrToIntBase10NoSign(pDataStart + 1, aint(-1));
					else
						ArgNumber = -1;

					const TICStrFormatType * pFormatVar = _ArgData.f_GetArg(ArgNumber);
					if (pFormatVar)
					{
						return pFormatVar->f_Get_fp64();
					}
					else
						return _FailValue;
				}
				else
				{
					static const CChar Terminators[] = {',','}',0};

					return CStrTraits::fs_StrToFloatExact(m_pDataStart, _FailValue, Terminators);
				}
			}

			void f_DisplayUnknownFormat(CStrAggregate &_String, aint &_CurrentStrLen) const
			{
				const ch8 *pTmp = "| format specifier unknown (";
				while (*pTmp)
					_String.fp_AddCharLengthAware(_CurrentStrLen, (CChar)(*(pTmp++)));

				if (m_FormatTypes.m_Format1)
					_String.fp_AddCharLengthAware(_CurrentStrLen, (CChar)m_FormatTypes.m_Format1);
				if (m_FormatTypes.m_Format2)
					_String.fp_AddCharLengthAware(_CurrentStrLen, (CChar)m_FormatTypes.m_Format2);
				_String.fp_AddCharLengthAware(_CurrentStrLen, ')');
				_String.fp_AddCharLengthAware(_CurrentStrLen, ' ');
				_String.fp_AddCharLengthAware(_CurrentStrLen, '|');
			}

		};

		template <typename t_CChar>
		void fp_ReportParseError(CStrAggregate &_String, aint &_CurrentStrLen, const t_CChar *_pStr, mint _MaxLen = TCLimitsInt<mint>::mc_Max) const
		{
			auto pStart = _pStr;
			while (*_pStr && mint(_pStr - pStart) < _MaxLen)
				_String.fp_AddCharLengthAware(_CurrentStrLen, (CChar)(*(_pStr++)));
		}


		inline_small void fp_GetNextFormat(COption &_NewFormat, const CChar * &_pFormat) const
		{
			// Parse for characters, and end if , or } is found
			const CChar * pFormat = _pFormat;
			switch ((*pFormat))
			{
			case ' ':
				++pFormat;
			case '}':
			case 0:
			case ',':
			case '*':
				_NewFormat.m_FormatWhole = 0;
				break;
			default:
				_NewFormat.m_FormatTypes.m_Format1 = (int16)CStrTraits::fs_CharUpperCase((*pFormat));
				++pFormat;
				if ((*pFormat) > '9' || (*pFormat) < '0')
				{
					switch ((*pFormat))
					{
					case ' ':
						++pFormat;
					case '}':
					case 0:
					case ',':
					case '*':
						_NewFormat.m_FormatTypes.m_Format2 = 0;
						break;
					default:
						_NewFormat.m_FormatTypes.m_Format2 = (int16)CStrTraits::fs_CharUpperCase((*pFormat));
						++pFormat;
						break;
					}
				}
				break;
			}

			_NewFormat.m_pDataStart = pFormat;

			while (1)
			{
				switch ((*pFormat))
				{
				case 0:
				case '}':
					pFormat = nullptr;
					break;
				case ',':
					++pFormat;
					break;
				default:
					++pFormat;
					continue;
				}
				break;
			}

			_pFormat = pFormat;
		}

		template <typename t_CData, typename t_CFormatType, typename t_COptions>
		inline_small static void fs_ParseOptions(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, const CChar *_pFormat)
		{
			while (_pFormat)
			{
				COption Option;
				_Args.m_FormatType.fp_GetNextFormat(Option, _pFormat);

				if (Option.m_FormatWhole)
				{
					if (!_Args.m_FormatType.f_ParseOption(_Args, Option))
						Option.f_DisplayUnknownFormat(_Args.m_String, _Args.m_CurrentStrLen);

				}
			}
		}

		template <typename t_CData, typename t_CFormatType, typename t_COptions>
		inline_small aint f_ParseOption(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, COption &_Option) const
		{
			switch (_Option.m_FormatTypes.m_Format1)
			{
				// Format
			case 'L':
				_Args.m_Options.m_MinLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
				break;
			case 'M':
				_Args.m_Options.m_MaxLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, TCLimitsInt<aint>::mc_Max);
				break;
			case 'S':
				{
					switch (_Option.m_FormatTypes.m_Format2)
					{
					case 'J':
					case 'Z':
						_Args.m_Options.m_MaxLength = _Args.m_Options.m_MinLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
						break;
					case 'L':
						_Args.m_Options.m_MinLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
						break;
					case 'M':
						_Args.m_Options.m_MaxLength = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, TCLimitsInt<aint>::mc_Max);
						break;
					case 'F':
						{
							_Args.m_Options.m_Fillout = *_Option.m_pDataStart;
						}
						break;
					default:
						return false;
						break;
					}
				}
				break;
			case 'A':
				{
					switch (_Option.m_FormatTypes.m_Format2)
					{
					case '-':
						_Args.m_Options.m_Align = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
						_Args.m_Options.m_bLeftAlign = true;
						_Args.m_Options.m_bSimpleAlign = false;
						break;
					case '+':
						_Args.m_Options.m_Align = _Option.f_GetData_aint_NotSigned(_Args.m_Formatter, 0);
						_Args.m_Options.m_bSimpleAlign = _Args.m_Options.m_Align == 0;
						break;
					default:
						return false;
						break;
					}
					break;
				}
			default:
				return false;
				break;
			}
			return true;
		}

		template <typename t_COptions>
		static void fs_AddSubStrToStr(CStrAggregate &_String, aint &_CurrentStrLen, const t_COptions &_Options, const CChar *_pSubStr, mint _SubStrLen, aint _SubStrStart)
		{
			aint PreAdd;
			aint PostAdd;
			if (_Options.f_LeftAlign())
			{
				if (_Options.f_Align() >= _SubStrStart)
					PreAdd = _Options.f_Align() - _SubStrStart;
				else
					PreAdd = _Options.f_Align();
				PostAdd = _Options.f_MinLength() - (_SubStrLen + PreAdd);
			}
			else
			{
				PostAdd = _Options.f_Align();
				PreAdd = _Options.f_MinLength() - (_SubStrLen + PostAdd);
			}

			if (PostAdd < 0)
				PostAdd = 0;

			if (PreAdd < 0)
				PreAdd = 0;

			typename CStrAggregate::CAddStrAgrs Args(_CurrentStrLen, _SubStrLen);
			CChar const *pSubStr = _pSubStr;

			if (PreAdd > 0 || PostAdd > 0)
			{
				_String.fp_AddCharsLengthAware(_CurrentStrLen, _Options.f_Fillout(), PreAdd);

				if (_Options.f_LeftAlign())
				{
					if ((_SubStrLen + PreAdd + PostAdd) > _Options.f_MaxLength())
						Args.m_Len = _Options.f_MaxLength() - (PreAdd + PostAdd);
				}
				else
				{
					if ((_SubStrLen + (PreAdd + PostAdd)) > _Options.f_MaxLength())
					{
						Args.m_Len = _Options.f_MaxLength() - (PreAdd + PostAdd);
						pSubStr = _pSubStr + (_SubStrLen - (_Options.f_MaxLength() - (PreAdd + PostAdd)));
					}
				}
			}
			else
			{
				if (_Options.f_LeftAlign())
				{
					if ((_SubStrLen) > _Options.f_MaxLength())
					{
						Args.m_Len = _Options.f_MaxLength();
					}
				}
				else
				{
					if ((_SubStrLen) > _Options.f_MaxLength())
					{
						Args.m_Len = _Options.f_MaxLength();
						pSubStr = _pSubStr + (_SubStrLen - _Options.f_MaxLength());
					}
				}
			}

			_String.fp_AddStrLengthAwareInline(Args, pSubStr);

			if (PostAdd > 0)
				_String.fp_AddCharsLengthAware(_CurrentStrLen, _Options.f_Fillout(), PostAdd);
		}

		template <typename t_COptions>
		static inline_small void fs_AddSubStrToStrSimple(CStrAggregate &_String, aint &_CurrentStrLen, const t_COptions &_Options, const CChar *_pSubStr, mint _SubStrLen)
		{
			typename CStrAggregate::CAddStrAgrs Args(_CurrentStrLen, _SubStrLen);
			CChar const *pSubStr = _pSubStr;
			if (_Options.f_RestrictLength())
			{
				if (_SubStrLen < _Options.f_MinLength())
				{
					_String.fp_AddCharsLengthAware(_CurrentStrLen, _Options.f_Fillout(), _Options.f_MinLength() - _SubStrLen);
				}
				else
				{
					if (_SubStrLen > _Options.f_MaxLength())
					{
						Args.m_Len = _Options.f_MaxLength();
						if (!_Options.f_LeftAlign())
							pSubStr = _pSubStr + (_SubStrLen - _Options.f_MaxLength());
					}
				}
			}
			_String.fp_AddStrLengthAwareInline(Args, pSubStr);
		}


		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| Xpr support																						|
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		enum EFormatXprOperator
		{
			EFormatXprOperator_None = 0,

			EFormatXprOperator_UnaryAdd,
			EFormatXprOperator_UnarySub,
			EFormatXprOperator_BitwiseNot,
			EFormatXprOperator_LogicalNot,

			EFormatXprOperator_Multiply,
			EFormatXprOperator_Divide,
			EFormatXprOperator_Modulus,

			EFormatXprOperator_LessThan,
			EFormatXprOperator_GreaterThan,
			EFormatXprOperator_Equal,
			EFormatXprOperator_LessThanEqual,
			EFormatXprOperator_GreaterThanEqual,

			EFormatXprOperator_LogicalOr,
			EFormatXprOperator_LogicalAnd,

			EFormatXprOperator_BitwiseOr,
			EFormatXprOperator_BitwiseAnd,
			EFormatXprOperator_BitwiseXor,

			EFormatXprOperator_Add,
			EFormatXprOperator_Sub,
		};

		template <typename t_CData, typename t_CImplementation>
		class TCValueData
		{
		public:
			t_CData m_ValuePrec0;
			t_CData m_ValuePrec1;
			EFormatXprOperator m_CurrentOperatorPrec0;
			EFormatXprOperator m_CurrentOperatorPrec1;
			aint m_Precedence;

			TCValueData()
				: m_ValuePrec0(t_CImplementation::fs_DefaultValue())
				, m_ValuePrec1(t_CImplementation::fs_DefaultValue())
				, m_CurrentOperatorPrec0(EFormatXprOperator_None)
				, m_CurrentOperatorPrec1(EFormatXprOperator_None)
				, m_Precedence(0)
			{
			}
			void operator () (t_CData _Value)
			{
				EFormatXprOperator *pOperator;
				t_CData *pValue;
				if (m_Precedence == 0)
				{
					pOperator = &m_CurrentOperatorPrec0;
					pValue = &m_ValuePrec0;
				}
				else
				{
					pOperator = &m_CurrentOperatorPrec1;
					pValue = &m_ValuePrec1;
				}
				auto &Operator = *pOperator;
				auto &Value = *pValue;

				switch (Operator)
				{
				case EFormatXprOperator_None: Value = _Value; break;
				case EFormatXprOperator_Multiply: Value *= _Value; break;
				case EFormatXprOperator_Divide: Value /= _Value; break;
				case EFormatXprOperator_Modulus: Value = t_CImplementation::fs_Modulus(Value, _Value); break;
				case EFormatXprOperator_Add: Value += _Value; break;
				case EFormatXprOperator_Sub: Value -= _Value; break;

				case EFormatXprOperator_LessThan: Value = Value < _Value; break;
				case EFormatXprOperator_GreaterThan: Value = Value > _Value; break;
				case EFormatXprOperator_Equal: Value = Value == _Value; break;
				case EFormatXprOperator_LessThanEqual: Value = Value <= _Value; break;
				case EFormatXprOperator_GreaterThanEqual: Value = Value >= _Value; break;

				case EFormatXprOperator_LogicalOr: Value = !!Value || !!_Value; break;
				case EFormatXprOperator_LogicalAnd: Value = !!Value && !!_Value; break;

				case EFormatXprOperator_BitwiseOr: Value = t_CImplementation::fs_BitwiseOr(Value, _Value); break;
				case EFormatXprOperator_BitwiseAnd: Value = t_CImplementation::fs_BitwiseAnd(Value, _Value); break;
				case EFormatXprOperator_BitwiseXor: Value = t_CImplementation::fs_BitwiseXor(Value, _Value); break;
				}
				Operator = EFormatXprOperator_None;
			};
		};

		template <typename t_CImplementation, typename t_CData, typename t_CFormatType, typename t_COptions>
		inline_never t_CData fpr_EvalExpression(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, const CChar *&_pParse, bool &_bError, bool _bExitAtValue) const
		{
			TCValueData<t_CData, t_CImplementation> ValueData;

			const CChar *pParse = _pParse;
			bool bLastWasValue = false;
			bool bFirst = true;
			bool bEndParenthesis = false;

			while (*pParse)
			{
				// x + y*$+x/z - w
				// x + (y + z) * x
				fg_ParseWhiteSpace(pParse);
				if (!(*pParse))
					break;
				else if (*pParse == '(')
				{
					++pParse;
					if (bLastWasValue)
					{
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Value without operator |");
						_bError = true;
						return t_CImplementation::fs_DefaultValue();
					}
					auto Value = fpr_EvalExpression<t_CImplementation>(_Args, pParse, _bError, false);
					if (_bError)
						return t_CImplementation::fs_DefaultValue();
					ValueData(Value);
					bLastWasValue = true;
					bFirst = false;
					if (_bExitAtValue)
						break;
				}
				else if (*pParse == '!')
				{
					++pParse;
					if (bLastWasValue)
					{
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Value without operator |");
						_bError = true;
						return t_CImplementation::fs_DefaultValue();
					}
					auto Value = fpr_EvalExpression<t_CImplementation>(_Args, pParse, _bError, true);
					if (_bError)
						return t_CImplementation::fs_DefaultValue();
					ValueData(!Value);
					bLastWasValue = true;
					bFirst = false;
					if (_bExitAtValue)
						break;
				}
				else if (*pParse == '~')
				{
					++pParse;
					if (bLastWasValue)
					{
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Value without operator |");
						_bError = true;
						return t_CImplementation::fs_DefaultValue();
					}
					auto Value = fpr_EvalExpression<t_CImplementation>(_Args, pParse, _bError, true);
					if (_bError)
						return t_CImplementation::fs_DefaultValue();
					ValueData(t_CImplementation::fs_BitwiseNot(Value));
					bLastWasValue = true;
					bFirst = false;
					if (_bExitAtValue)
						break;
				}
				else if (*pParse == ')')
				{
					bEndParenthesis = true;
					++pParse;
					break;
				}
				else if (*pParse == '$')
				{
					if (bLastWasValue)
					{
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Value without operator |");
						_bError = true;
						return t_CImplementation::fs_DefaultValue();
					}
					++pParse;
					t_CData Value;
					if (fg_CharIsNumber(*pParse))
					{
						aint iValue = fg_StrToIntBase10ParseNoSign(pParse, aint(0));
						auto pArgument = _Args.m_Formatter.f_GetArg(iValue);
						if (pArgument)
							Value = t_CImplementation::fs_GetArgumentValue(pArgument);
						else
						{
							fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Argument out of range |");
							_bError = true;
							return t_CImplementation::fs_DefaultValue();
						}
					}
					else
						Value = _Args.m_Data;

					ValueData(Value);

					bLastWasValue = true;
					bFirst = false;
					if (_bExitAtValue)
						break;
				}
				else if (fg_CharIsNumber(*pParse))
				{
					if (bLastWasValue)
					{
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Value without operator |");
						_bError = true;
						return t_CImplementation::fs_DefaultValue();
					}
					ValueData(t_CImplementation::fs_StrToData(pParse, t_CImplementation::fs_DefaultValue(), "()+-*/%$<>=^~"));
					bLastWasValue = true;
					bFirst = false;
					if (_bExitAtValue)
						break;
				}
				else if (*pParse == '+')
				{
					++pParse;
					if (bLastWasValue)
					{
						// x + y + z;
						if (ValueData.m_CurrentOperatorPrec0 != EFormatXprOperator_None)
						{
							// Add in old value
							ValueData.m_Precedence = 0;
							ValueData(ValueData.m_ValuePrec1);
						}

						ValueData.m_CurrentOperatorPrec0 = EFormatXprOperator_Add;
						ValueData.m_Precedence = 1;
						bLastWasValue = false;
					}
					else
					{
						auto Ret = fpr_EvalExpression<t_CImplementation>(_Args, pParse, _bError, true);
						if (_bError)
							return t_CImplementation::fs_DefaultValue();
						ValueData(+Ret);
						bLastWasValue = true;
						bFirst = false;
						if (_bExitAtValue)
							break;
					}
				}
				else if (*pParse == '-')
				{
					++pParse;
					if (bLastWasValue)
					{
						// x + y + z;
						if (ValueData.m_CurrentOperatorPrec0 != EFormatXprOperator_None)
						{
							// Add in old value
							ValueData.m_Precedence = 0;
							ValueData(ValueData.m_ValuePrec1);
						}
						ValueData.m_CurrentOperatorPrec0 = EFormatXprOperator_Sub;
						ValueData.m_Precedence = 1;
						bLastWasValue = false;
					}
					else
					{
						auto Value = fpr_EvalExpression<t_CImplementation>(_Args, pParse, _bError, true);
						if (_bError)
							return t_CImplementation::fs_DefaultValue();
						ValueData(-Value);
						bLastWasValue = true;
						bFirst = false;
						if (_bExitAtValue)
							break;
					}
				}
				else
				{
					EFormatXprOperator Operator;
					if (*pParse == '/')
						Operator = EFormatXprOperator_Divide;
					else if (*pParse == '*')
						Operator = EFormatXprOperator_Multiply;
					else if (*pParse == '%')
						Operator = EFormatXprOperator_Modulus;
					else if (*pParse == '>')
					{
						if (pParse[1] == '=')
						{
							++pParse;
							Operator = EFormatXprOperator_GreaterThanEqual;
						}
						else
							Operator = EFormatXprOperator_GreaterThan;
					}
					else if (*pParse == '<')
					{
						if (pParse[1] == '=')
						{
							Operator = EFormatXprOperator_LessThanEqual;
							++pParse;
						}
						else
							Operator = EFormatXprOperator_LessThan;
					}
					else if (*pParse == '|')
					{
						if (pParse[1] == '|')
						{
							++pParse;
							Operator = EFormatXprOperator_LogicalOr;
						}
						else
							Operator = EFormatXprOperator_BitwiseOr;
					}
					else if (*pParse == '&')
					{
						if (pParse[1] == '&')
						{
							++pParse;
							Operator = EFormatXprOperator_LogicalAnd;
						}
						else
							Operator = EFormatXprOperator_BitwiseAnd;
					}
					else if (fg_StrStartsWith(pParse, "=="))
					{
						++pParse;
						Operator = EFormatXprOperator_Equal;
					}
					else if (*pParse == '^')
					{
						Operator = EFormatXprOperator_BitwiseXor;
					}
					else
					{
						_bError = true;
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Unrecognized operator ");
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, pParse, 1);
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, " |");
						++pParse;
						return t_CImplementation::fs_DefaultValue();
					}

					if (!bLastWasValue || bFirst)
					{
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Binary operator without first argument |");
						_bError = true;
						return t_CImplementation::fs_DefaultValue();
					}
					bLastWasValue = false;

					++pParse;

					if (ValueData.m_Precedence == 0)
						ValueData.m_CurrentOperatorPrec0 = Operator;
					else
						ValueData.m_CurrentOperatorPrec1 = Operator;
				}
				bFirst = false;
			}

			if (_bExitAtValue)
			{
				if (!bLastWasValue)
				{
					_bError = true;
					fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Unmatched unary operator |");
					return t_CImplementation::fs_DefaultValue();
				}
			}

			if (bFirst)
			{
				_bError = true;
				fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Empty expression |");
				return t_CImplementation::fs_DefaultValue();
			}

			if ((ValueData.m_CurrentOperatorPrec1 != EFormatXprOperator_None) || (ValueData.m_Precedence == 0 && ValueData.m_CurrentOperatorPrec0 != EFormatXprOperator_None))
			{
				_bError = true;
				fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Binary operator without second argument |");
				return t_CImplementation::fs_DefaultValue();
			}

			if (!_bExitAtValue && !bEndParenthesis)
			{
				_bError = true;
				fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| No end parenthesis |");
				return t_CImplementation::fs_DefaultValue();
			}

			if (ValueData.m_Precedence == 1)
			{
				if (ValueData.m_CurrentOperatorPrec0 != EFormatXprOperator_None)
				{
					// Add in old value
					ValueData.m_Precedence = 0;
					ValueData(ValueData.m_ValuePrec1);
				}
			}

			_pParse = pParse;

			return ValueData.m_ValuePrec0;
		}

		template <typename t_CImplementation, typename t_CData, typename t_CFormatType, typename t_COptions>
		inline_never void fp_EvalExpression(TICStrFormatType_ParseOptionsArgs<t_CData, t_CFormatType, t_COptions> &_Args, const CChar *_pParse) const
		{
			const CChar *pParse = _pParse;
			bool bError = false;
			fg_ParseWhiteSpace(pParse);
			if (*pParse == '(')
			{
				++pParse;
				_Args.m_Data = fpr_EvalExpression<t_CImplementation>(_Args, pParse, bError, false);
				if (!bError)
				{
					fg_ParseWhiteSpace(pParse);
					if (*pParse != '}' && *pParse != ',')
					{
						_Args.m_Data = t_CImplementation::fs_DefaultValue();
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Missing ( or extra characters |");
					}
				}
			}
			else
			{
				_Args.m_Data = t_CImplementation::fs_DefaultValue();
				fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| xpr must be within () |");
			}
		}
	};
}
