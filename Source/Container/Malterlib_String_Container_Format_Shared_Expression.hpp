// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CFormatter>
	template <typename tf_CData, typename tf_CImplementation>
	TICStrFormatType<t_CFormatter>::TCValueData<tf_CData, tf_CImplementation>::TCValueData()
		: m_ValuePrec0(tf_CImplementation::fs_DefaultValue())
		, m_ValuePrec1(tf_CImplementation::fs_DefaultValue())
		, m_CurrentOperatorPrec0(EFormatXprOperator_None)
		, m_CurrentOperatorPrec1(EFormatXprOperator_None)
		, m_Precedence(0)
	{
	}

	template <typename t_CFormatter>
	template <typename tf_CData, typename tf_CImplementation>
	void TICStrFormatType<t_CFormatter>::TCValueData<tf_CData, tf_CImplementation>::operator () (tf_CData _Value)
	{
		EFormatXprOperator *pOperator;
		tf_CData *pValue;

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
		case EFormatXprOperator_Modulus: Value = tf_CImplementation::fs_Modulus(Value, _Value); break;
		case EFormatXprOperator_Add: Value += _Value; break;
		case EFormatXprOperator_Sub: Value -= _Value; break;

		case EFormatXprOperator_LessThan: Value = Value < _Value; break;
		case EFormatXprOperator_GreaterThan: Value = Value > _Value; break;
		case EFormatXprOperator_Equal: Value = Value == _Value; break;
		case EFormatXprOperator_LessThanEqual: Value = Value <= _Value; break;
		case EFormatXprOperator_GreaterThanEqual: Value = Value >= _Value; break;

		case EFormatXprOperator_LogicalOr: Value = !!Value || !!_Value; break;
		case EFormatXprOperator_LogicalAnd: Value = !!Value && !!_Value; break;

		case EFormatXprOperator_BitwiseOr: Value = tf_CImplementation::fs_BitwiseOr(Value, _Value); break;
		case EFormatXprOperator_BitwiseAnd: Value = tf_CImplementation::fs_BitwiseAnd(Value, _Value); break;
		case EFormatXprOperator_BitwiseXor: Value = tf_CImplementation::fs_BitwiseXor(Value, _Value); break;
		}

		Operator = EFormatXprOperator_None;
	};

	template <typename t_CFormatter>
	template <typename tf_CImplementation, typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_never void TICStrFormatType<t_CFormatter>::fp_EvalExpression(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, CChar const *_pParse) const
	{
		CChar const *pParse = _pParse;
		bool bError = false;
		fg_ParseWhiteSpace(pParse);
		if (*pParse == '(')
		{
			++pParse;
			_Args.m_Data = fpr_EvalExpression<tf_CImplementation>(_Args, pParse, bError, false);
			if (!bError)
			{
				fg_ParseWhiteSpace(pParse);
				if (*pParse != '}' && *pParse != ',')
				{
					_Args.m_Data = tf_CImplementation::fs_DefaultValue();
					fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Missing ( or extra characters |");
				}
			}
		}
		else
		{
			_Args.m_Data = tf_CImplementation::fs_DefaultValue();
			fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| xpr must be within () |");
		}
	}

	template <typename t_CFormatter>
	template <typename tf_CImplementation, typename tf_CData, typename tf_CFormatType, typename tf_COptions>
	inline_never tf_CData TICStrFormatType<t_CFormatter>
		::fpr_EvalExpression(TICStrFormatType_ParseOptionsArgs<tf_CData, tf_CFormatType, tf_COptions> &_Args, CChar const * &_pParse, bool &_bError, bool _bExitAtValue) const
	{
		TCValueData<tf_CData, tf_CImplementation> ValueData;

		CChar const *pParse = _pParse;
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
					return tf_CImplementation::fs_DefaultValue();
				}
				auto Value = fpr_EvalExpression<tf_CImplementation>(_Args, pParse, _bError, false);
				if (_bError)
					return tf_CImplementation::fs_DefaultValue();
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
					return tf_CImplementation::fs_DefaultValue();
				}
				auto Value = fpr_EvalExpression<tf_CImplementation>(_Args, pParse, _bError, true);
				if (_bError)
					return tf_CImplementation::fs_DefaultValue();
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
					return tf_CImplementation::fs_DefaultValue();
				}
				auto Value = fpr_EvalExpression<tf_CImplementation>(_Args, pParse, _bError, true);
				if (_bError)
					return tf_CImplementation::fs_DefaultValue();
				ValueData(tf_CImplementation::fs_BitwiseNot(Value));
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
					return tf_CImplementation::fs_DefaultValue();
				}
				++pParse;
				tf_CData Value;
				if (fg_CharIsNumber(*pParse))
				{
					aint iValue = fg_StrToIntBase10ParseNoSign(pParse, aint(0));
					auto pArgument = _Args.m_Formatter.f_GetArg(iValue);
					if (pArgument)
						Value = tf_CImplementation::fs_GetArgumentValue(pArgument);
					else
					{
						fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Argument out of range |");
						_bError = true;
						return tf_CImplementation::fs_DefaultValue();
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
					return tf_CImplementation::fs_DefaultValue();
				}
				ValueData(tf_CImplementation::fs_StrToData(pParse, tf_CImplementation::fs_DefaultValue(), "()+-*/%$<>=^~"));
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
					auto Ret = fpr_EvalExpression<tf_CImplementation>(_Args, pParse, _bError, true);
					if (_bError)
						return tf_CImplementation::fs_DefaultValue();
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
					auto Value = fpr_EvalExpression<tf_CImplementation>(_Args, pParse, _bError, true);
					if (_bError)
						return tf_CImplementation::fs_DefaultValue();
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
					return tf_CImplementation::fs_DefaultValue();
				}

				if (!bLastWasValue || bFirst)
				{
					fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Binary operator without first argument |");
					_bError = true;
					return tf_CImplementation::fs_DefaultValue();
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
				return tf_CImplementation::fs_DefaultValue();
			}
		}

		if (bFirst)
		{
			_bError = true;
			fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Empty expression |");
			return tf_CImplementation::fs_DefaultValue();
		}

		if ((ValueData.m_CurrentOperatorPrec1 != EFormatXprOperator_None) || (ValueData.m_Precedence == 0 && ValueData.m_CurrentOperatorPrec0 != EFormatXprOperator_None))
		{
			_bError = true;
			fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| Binary operator without second argument |");
			return tf_CImplementation::fs_DefaultValue();
		}

		if (!_bExitAtValue && !bEndParenthesis)
		{
			_bError = true;
			fp_ReportParseError(_Args.m_String, _Args.m_CurrentStrLen, "| No end parenthesis |");
			return tf_CImplementation::fs_DefaultValue();
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
}
