// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
namespace NMib::NStr
{
	template <typename t_CData, typename t_CReturn, typename t_CTerm, typename t_CPoints>
		t_CReturn fg_StrToFloatParse(const t_CData *&_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators, bool _bDontFail = false, const t_CPoints *_pPoints = nullptr)
	{
		t_CReturn DestNumber = t_CReturn::fs_0();
		t_CReturn DestDecimals = t_CReturn::fs_0();
		t_CReturn DestExponent = t_CReturn::fs_0();
		t_CReturn DecimalPlace = t_CReturn::fs_1();

		using CData = NTraits::TCUnsigned<t_CData>;
		using CTerm = NTraits::TCUnsigned<t_CTerm>;

		const CData *pParseStr = (const CData *)_pStr;
		static const t_CReturn Ten = fg_Convert<t_CReturn>(10);

		aint SearchMode = 0;
		t_CReturn Sign = t_CReturn::fs_1();
		t_CReturn ExponentSign = t_CReturn::fs_1();
		aint bFoundNum = false;

		// Parse for characters, and end if str terminator is found
		while ((*pParseStr))
		{
			if (_pStrTerminators)
			{
				const CTerm *pStrTerminators = (const CTerm *)_pStrTerminators;

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
					{
						Sign = t_CReturn::fs_1();
					}
					else if ((*pParseStr) == '-')
					{
						Sign = -t_CReturn::fs_1();
					}
					else if ((*pParseStr) == 'e' || (*pParseStr) == 'E')
					{
						SearchMode = 3;
						DestNumber = t_CReturn::fs_1();
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
							const CTerm *pStrPoints = (const CTerm *)_pPoints;

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
							{
								SearchMode = 2;
							}
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
						DestNumber += fg_Convert<t_CReturn>((*pParseStr) - '0');
						bFoundNum = true;
					}
					else if ((*pParseStr) == 'e' || (*pParseStr) == 'E')
					{
						bFoundNum = false;
						SearchMode = 3;
					}
					else if (fg_CharIsWhiteSpace((*pParseStr)))
					{
						goto Return;
					}
					else
					{
						if (_pPoints)
						{
							const CTerm *pStrPoints = (const CTerm *)_pPoints;

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
							{
								SearchMode = 2;
							}
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
						DestDecimals += (fg_Convert<t_CReturn>((*pParseStr) - '0')) / DecimalPlace;
						bFoundNum = true;
					}
					else if ((*pParseStr) == 'e' || (*pParseStr) == 'E')
					{
						SearchMode = 3;
					}
					else if (fg_CharIsWhiteSpace((*pParseStr)))
					{
						goto Return;
					}
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
						DestExponent += fg_Convert<t_CReturn>((*pParseStr) - '0');
						bFoundNum = true;
					}
					else if ((*pParseStr) == '-')
					{
						ExponentSign = -t_CReturn::fs_1();
					}
					else if ((*pParseStr) == '+')
					{
						ExponentSign = t_CReturn::fs_1();
					}
					else if (fg_CharIsWhiteSpace((*pParseStr)))
					{
						goto Return;
					}
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

		_pStr = (const t_CData *)pParseStr;

		if (bFoundNum)
		{
			return (DestNumber + DestDecimals) * Ten.f_Pow(DestExponent * ExponentSign) * Sign;
		}
		else
		{
			return _FailValue;
		}
	}

	template <typename t_CData, typename t_CReturn, typename t_CTerm>
		t_CReturn fg_StrToFloat(const t_CData *_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators, bool _bDontFail)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, _bDontFail, (const ch8 *)nullptr);
	}
	template <typename t_CData, typename t_CReturn, typename t_CTerm>
		t_CReturn fg_StrToFloat(const t_CData *_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, true, (const ch8 *)nullptr);
	}

	template <typename t_CData, typename t_CReturn>
		t_CReturn fg_StrToFloat(const t_CData *_pStr, t_CReturn _FailValue)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, (const ch8 *)nullptr, true, (const ch8 *)nullptr);
	}


	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloatParse(const t_CData *&_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators, bool _bDontFail)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, _bDontFail, (const ch8 *)nullptr);
	}

	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloatParse(const t_CData *&_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, true, (const ch8 *)nullptr);
	}

	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToFloatParse(const t_CData *&_pStr, t_CReturn _FailValue)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, (const ch8 *)nullptr, true, (const ch8 *)nullptr);
	}


	template <typename t_CData, typename t_CReturn, typename t_CTerm>
		t_CReturn fg_StrToFloatExact(const t_CData *_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, false, (const ch8 *)nullptr);
	}

	template <typename t_CData, typename t_CReturn>
		t_CReturn fg_StrToFloatExact(const t_CData *_pStr, t_CReturn _FailValue)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, (const ch8 *)nullptr, false, (const ch8 *)nullptr);
	}


	template <typename t_CData, typename t_CReturn, typename t_CTerm>
	t_CReturn fg_StrToFloatParseExact(const t_CData *&_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, false, (const ch8 *)nullptr);
	}

	template <typename t_CData, typename t_CReturn>
	t_CReturn fg_StrToFloatParseExact(const t_CData *&_pStr, t_CReturn _FailValue)
	{
		return fg_StrToFloatParse(_pStr, _FailValue, (const ch8 *)nullptr, false, (const ch8 *)nullptr);
	}
}
