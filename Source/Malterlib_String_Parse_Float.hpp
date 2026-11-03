// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <bool tf_bUseMaxLen, typename tf_CData, typename tf_CReturn, typename tf_CTerm, typename tf_CPoints>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail, tf_CPoints const *_pPoints)
	{
		tf_CReturn DestNumber = tf_CReturn::fs_Zero();
		tf_CReturn DestDecimals = tf_CReturn::fs_Zero();
		tf_CReturn DestExponent = tf_CReturn::fs_Zero();
		tf_CReturn DecimalPlace = tf_CReturn::fs_One();

		using CData = NTraits::TCUnsigned<tf_CData>;
		using CTerm = NTraits::TCUnsigned<tf_CTerm>;

		CData const *pParseStr = (CData const *)_pStr;
		CData const *pEndStr = nullptr;
		if constexpr (tf_bUseMaxLen)
			pEndStr = pParseStr + _MaxLen;
		static tf_CReturn const Ten = fg_Convert<tf_CReturn>(10);

		aint SearchMode = 0;
		tf_CReturn Sign = tf_CReturn::fs_One();
		tf_CReturn ExponentSign = tf_CReturn::fs_One();
		aint bFoundNum = false;

		// Parse for characters, and end if str terminator is found
		while ((!tf_bUseMaxLen || pParseStr < pEndStr) && (tf_bUseMaxLen || (*pParseStr)))
		{
			if (_pStrTerminators)
			{
				CTerm const *pStrTerminators = (CTerm const *)_pStrTerminators;

				while (*pStrTerminators)
				{
					if ((*pParseStr) == (*pStrTerminators))
						goto Return;

					++pStrTerminators;
				}
			}

			switch (SearchMode)
			{
			case 0:
				{
					if ((*pParseStr) == '+')
						Sign = tf_CReturn::fs_One();
					else if ((*pParseStr) == '-')
						Sign = -tf_CReturn::fs_One();
					else if ((*pParseStr) == 'e' || (*pParseStr) == 'E')
					{
						SearchMode = 3;
						DestNumber = tf_CReturn::fs_One();
					}
					else if (fg_CharIsNumber((*pParseStr)))
					{
						SearchMode = 1;
						--pParseStr;
					}
					else
					{
						if (_pPoints)
						{
							CTerm const *pStrPoints = (CTerm const *)_pPoints;

							while (*pStrPoints)
							{
								if ((*pParseStr) == (*pStrPoints))
								{
									SearchMode = 2;
									break;
								}

								++pStrPoints;
							}
						}
						else
						{
							if ((*pParseStr) == '.')
								SearchMode = 2;
						}
						if (SearchMode == 0) // Nothing valid found, lets return
							goto Return;
					}
				}
				break;
			case 1:
				// Search Pre number
				{
					if ((*pParseStr) >= '0' && (*pParseStr) <= '9')
					{
						DestNumber *= Ten;
						DestNumber += fg_Convert<tf_CReturn>((*pParseStr) - '0');
						bFoundNum = true;
					}
					else if ((*pParseStr) == 'e' || (*pParseStr) == 'E')
					{
						bFoundNum = false;
						SearchMode = 3;
					}
					else if (fg_CharIsWhiteSpace((*pParseStr)))
						goto Return;
					else
					{
						if (_pPoints)
						{
							CTerm const *pStrPoints = (CTerm const *)_pPoints;

							while (*pStrPoints)
							{
								if ((*pParseStr) == (*pStrPoints))
								{
									SearchMode = 2;
									break;
								}

								++pStrPoints;
							}
						}
						else
						{
							if ((*pParseStr) == '.')
								SearchMode = 2;
						}

						if (SearchMode != 2)
						{
							if (_bDontFail)
								goto Return;
							return _FailValue;
						}
					}
				}
				break;
			case 2:
				// Post
				{
					if ((*pParseStr) >= '0' && (*pParseStr) <= '9')
					{
						DecimalPlace *= Ten;
						DestDecimals += (fg_Convert<tf_CReturn>((*pParseStr) - '0')) / DecimalPlace;
						bFoundNum = true;
					}
					else if ((*pParseStr) == 'e' || (*pParseStr) == 'E')
						SearchMode = 3;
					else if (fg_CharIsWhiteSpace((*pParseStr)))
						goto Return;
					else
					{
						if (_bDontFail)
							goto Return;
						return _FailValue;
					}
				}
				break;
			case 3:
				// Exponent
				{
					if ((*pParseStr) >= '0' && (*pParseStr) <= '9')
					{
						DestExponent *= Ten;
						DestExponent += fg_Convert<tf_CReturn>((*pParseStr) - '0');
						bFoundNum = true;
					}
					else if ((*pParseStr) == '-')
						ExponentSign = -tf_CReturn::fs_One();
					else if ((*pParseStr) == '+')
						ExponentSign = tf_CReturn::fs_One();
					else if (fg_CharIsWhiteSpace((*pParseStr)))
						goto Return;
					else
					{
						if (_bDontFail)
							goto Return;
						return _FailValue;
					}
				}
				break;

			case 5:
				// The end
				{
					if (!_bDontFail && !fg_CharIsWhiteSpace((*pParseStr)))
						DestNumber = _FailValue;
				}
				break;
			}

			++pParseStr;
		}

	Return:

		_pStr = (tf_CData const *)pParseStr;

		if (bFoundNum)
			return (DestNumber + DestDecimals) * Ten.f_Pow(DestExponent * ExponentSign) * Sign;
		else
			return _FailValue;
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm, typename tf_CPoints>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail, tf_CPoints const *_pPoints)
	{
		return fg_StrToFloatParse<false>(_pStr, 0, _FailValue, _pStrTerminators, _bDontFail, _pPoints);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm, typename tf_CPoints>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail, tf_CPoints const *_pPoints)
	{
		return fg_StrToFloatParse<true>(_pStr, _MaxLen, _FailValue, _pStrTerminators, _bDontFail, _pPoints);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloat(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, _bDontFail, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloat(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, true, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloat(tf_CData const *_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _MaxLen, _FailValue, _pStrTerminators, true, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToFloat(tf_CData const *_pStr, tf_CReturn _FailValue)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, (ch8 const *)nullptr, true, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators, bool _bDontFail)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, _bDontFail, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, true, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToFloatParse(tf_CData const * &_pStr, tf_CReturn _FailValue)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, (ch8 const *)nullptr, true, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatExact(tf_CData const *_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, false, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatExact(tf_CData const *_pStr, umint _MaxLen, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _MaxLen, _FailValue, _pStrTerminators, false, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToFloatExact(tf_CData const *_pStr, tf_CReturn _FailValue)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, (ch8 const *)nullptr, false, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn, typename tf_CTerm>
	tf_CReturn fg_StrToFloatParseExact(tf_CData const * &_pStr, tf_CReturn _FailValue, tf_CTerm const *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, false, (ch8 const *)nullptr);
	}

	template <typename tf_CData, typename tf_CReturn>
	tf_CReturn fg_StrToFloatParseExact(tf_CData const * &_pStr, tf_CReturn _FailValue)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, (ch8 const *)nullptr, false, (ch8 const *)nullptr);
	}
}
