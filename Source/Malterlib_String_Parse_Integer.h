// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NStr
	{


		enum EStrToIntParseMode
		{
			EStrToIntParseMode_Hex = 16,
			EStrToIntParseMode_Base10 = 10,
			EStrToIntParseMode_Binary = 8,
			EStrToIntParseMode_Octal = 2,

		};

		template <typename t_CData, typename t_CReturn, typename t_CTerm>
		t_CReturn fg_StrToIntParse
			(
				const t_CData *&_pStr
				, t_CReturn _FailValue
				, const t_CTerm *_pStrTerminators = nullptr
				, bint _bDontFail = false
				, int32 _ParseMode = EStrToIntParseMode_Base10
				, bool *_pFailed = nullptr
			)
		{
			t_CReturn DestNumber = 0;
			typedef typename NTraits::TCUnsigned<t_CData>::CType CData;
			typedef typename NTraits::TCUnsigned<t_CTerm>::CType CTerm;
			const CData *pParseStr = (const CData *)_pStr;

			uint32 ParseMode;
			if (_ParseMode < 0)
				ParseMode = EStrToIntParseMode_Base10;
			else
				ParseMode = fg_Clamp(_ParseMode, int32(2), int32(36));

			aint SearchMode = 0;
			t_CReturn Sign = 1;

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
							Sign = 1;
						}
						else if ((*pParseStr) == '-')
						{
							Sign = t_CReturn(-1);
						}
						else if (fg_CharIsNumber((*pParseStr)) || (ParseMode == EStrToIntParseMode_Hex && (((*pParseStr) >= 'a' && (*pParseStr) <= 'f') || ((*pParseStr) >= 'A' && (*pParseStr) <= 'F'))))
						{							
							if (fg_CharIsAlphabetical((*(pParseStr+1))))
							{
								if ((*pParseStr) == '0' && (((*(pParseStr + 1)) == 'x') || ((*(pParseStr + 1)) == 'X')))
								{
									// HexString
									SearchMode = 1;
									ParseMode = EStrToIntParseMode_Hex;

									++pParseStr;
								}
								else if ((*pParseStr) == '0' && (((*(pParseStr + 1)) == 'b') || ((*(pParseStr + 1)) == 'B')))
								{
									// Binary
									SearchMode = 1;
									ParseMode = EStrToIntParseMode_Binary;

									++pParseStr;
								}
								else if ((*pParseStr) == '0' && (((*(pParseStr + 1)) == 'o') || ((*(pParseStr + 1)) == 'O')))
								{
									// Octal
									SearchMode = 1;
									ParseMode = EStrToIntParseMode_Octal;

									++pParseStr;
								}
								else
								{
									// Base 10
									SearchMode = 1;

									--pParseStr;
								}
							}
							else
							{
								// Base 10
								SearchMode = 1;

								--pParseStr;
							}
						}
						else
							goto Return;
					}
					break;
				case 1:
					// Base 10
					{
						switch (ParseMode)
						{
						case EStrToIntParseMode_Base10:
							{
								while ((*pParseStr) && (*pParseStr) >= '0' && (*pParseStr) <= '9')
								{
									DestNumber *= 10;
									DestNumber += (*pParseStr) - '0';
									bFoundNum = true;
									++pParseStr;
								}

								SearchMode = 5;
								continue;
							}
							break;
						case EStrToIntParseMode_Hex:
							// Hex
							{
								while ((*pParseStr))
								{
									aint Num;
									if ((*pParseStr) >= '0' && (*pParseStr) <= '9')
										Num = (*pParseStr) - '0';
									else if ((*pParseStr) >= 'a' && (*pParseStr) <= 'f')
										Num = ((*pParseStr) - 'a') + 10;
									else if ((*pParseStr) >= 'A' && (*pParseStr) <= 'F')
										Num = ((*pParseStr) - 'A') + 10;
									else
										break;

									DestNumber <<= 4;
									if (NTraits::TCIsFundamental<t_CReturn>::mc_Value)
										DestNumber |= Num;
									else
									{
										if (Num)
											DestNumber |= Num;
									}
									bFoundNum = true;

									++pParseStr;
								}

								SearchMode = 5;
								continue;
							}
							break;
						case EStrToIntParseMode_Binary:
							// Binary
							{
								while ((*pParseStr))
								{
									if ((*pParseStr) >= '0' && (*pParseStr) <= '1')
									{
										aint Num = (*pParseStr) - '0';

										DestNumber <<= 1;
										if (NTraits::TCIsFundamental<t_CReturn>::mc_Value)
											DestNumber |= Num;
										else
										{
											if (Num)
												DestNumber |= Num;
										}
										bFoundNum = true;
									}
									else
										break;
									++pParseStr;
								}
								SearchMode = 5;
								continue;
							}
							break;
						case EStrToIntParseMode_Octal:
							// Octal
							{
								while ((*pParseStr))
								{
									if ((*pParseStr) >= '0' && (*pParseStr) <= '7')
									{
										aint Num = (*pParseStr) - '0';

										DestNumber <<= 3;
										if (NTraits::TCIsFundamental<t_CReturn>::mc_Value)
											DestNumber |= Num;
										else
										{
											if (Num)
												DestNumber |= Num;
										}
										bFoundNum = true;
									}
									else
										break;
									++pParseStr;
								}
								SearchMode = 5;
								continue;
							}
							break;
						default:
							{
								if (ParseMode <= 10)
								{
									uint8 EndChar = '0' + (ParseMode-1);
									while ((*pParseStr) && (*pParseStr) >= '0' && (*pParseStr) <= EndChar)
									{
										DestNumber *= ParseMode;
										DestNumber += (*pParseStr) - '0';
										bFoundNum = true;
										++pParseStr;
									}
								}
								else
								{
									uint8 EndChar0 = 'a' + (ParseMode - 11);
									uint8 EndChar1 = 'A' + (ParseMode - 11);
									while ((*pParseStr))
									{
										if ((*pParseStr) >= '0' && (*pParseStr) <= '9')
										{
											aint Num = (*pParseStr) - '0';

											DestNumber *= ParseMode;
											DestNumber += Num;
											bFoundNum = true;
										}
										else if ((*pParseStr) >= 'a' && (*pParseStr) <= EndChar0)
										{
											aint Num = ((*pParseStr) - 'a') + 10;

											DestNumber *= ParseMode;
											DestNumber += Num;										  
											bFoundNum = true;
										}
										else if ((*pParseStr) >= 'A' && (*pParseStr) <= EndChar1)
										{
											aint Num = ((*pParseStr) - 'A') + 10;

											DestNumber *= ParseMode;
											DestNumber += Num;										  
											bFoundNum = true;
										}
										else
											break;
										++pParseStr;
									}

								}
								SearchMode = 5;
								continue;
							}
							break;
						}
					}
				case 5:
					// The end
					{
						if (!fg_CharIsWhiteSpace((*pParseStr)))
						{
							if (_bDontFail)
								goto Return;

							_pStr = (const t_CData *)pParseStr;
							if (_pFailed)
								*_pFailed = true;
							return _FailValue;
						}
						else
							goto Return;
					}
					break;
				}

				++pParseStr;

			}	

Return:
			_pStr = (const t_CData *)pParseStr;

			if (bFoundNum)			
				return DestNumber * Sign;
			else
			{
				if (_pFailed)
					*_pFailed = true;
				return _FailValue;
			}
		}

		template<typename t_CData, typename t_CReturn>
			inline_medium t_CReturn fg_StrToIntParseHex(const t_CData *&_pStr, t_CReturn _FailValue, t_CData _Terminator)
		{
			t_CReturn DestNumber = 0;
			typedef typename NTraits::TCUnsigned<t_CData>::CType CData;
			const CData *pParseStr = (const CData *)_pStr;

			t_CReturn Sign = 1;

			aint bFoundNum = false;

			// Parse for characters, and end if str terminator is found
			while ((*pParseStr))
			{
				if ((*pParseStr) == _Terminator)
					break;
				else if ((*pParseStr) == '+')
				{
					Sign = 1;
				}
				else if ((*pParseStr) == '-')
				{
					Sign = t_CReturn(-1);
				}
				else if (fg_CharIsHexNumber(*pParseStr))
				{							
					while ((*pParseStr))
					{
						aint Num;
						if ((*pParseStr) >= '0' && (*pParseStr) <= '9')
							Num = (*pParseStr) - '0';
						else if ((*pParseStr) >= 'a' && (*pParseStr) <= 'f')
							Num = ((*pParseStr) - 'a') + 10;
						else if ((*pParseStr) >= 'A' && (*pParseStr) <= 'F')
							Num = ((*pParseStr) - 'A') + 10;
						else
							break;

						DestNumber <<= 4;
						if (NTraits::TCIsFundamental<t_CReturn>::mc_Value)
							DestNumber |= Num;
						else
						{
							if (Num)
								DestNumber |= Num;
						}
						bFoundNum = true;

						++pParseStr;
					}

					break;
				}
				else
					break;

				++pParseStr;
			}	

			_pStr = (const t_CData *)pParseStr;

			if (bFoundNum)			
				return DestNumber * Sign;
			else
				return _FailValue;
		}


		template<typename t_CData, typename t_CReturn>
			inline_medium t_CReturn fg_StrToIntParseHex(const t_CData *&_pStr, t_CReturn _FailValue)
		{
			t_CReturn DestNumber = 0;
			typedef typename NTraits::TCUnsigned<t_CData>::CType CData;
			const CData *pParseStr = (const CData *)_pStr;

			t_CReturn Sign = 1;

			aint bFoundNum = false;

			// Parse for characters, and end if str terminator is found
			while ((*pParseStr))
			{
				if ((*pParseStr) == '+')
				{
					Sign = 1;
				}
				else if ((*pParseStr) == '-')
				{
					Sign = t_CReturn(-1);
				}
				else if (fg_CharIsHexNumber(*pParseStr))
				{							
					while ((*pParseStr))
					{
						aint Num;
						if ((*pParseStr) >= '0' && (*pParseStr) <= '9')
							Num = (*pParseStr) - '0';
						else if ((*pParseStr) >= 'a' && (*pParseStr) <= 'f')
							Num = ((*pParseStr) - 'a') + 10;
						else if ((*pParseStr) >= 'A' && (*pParseStr) <= 'F')
							Num = ((*pParseStr) - 'A') + 10;
						else
							break;

						DestNumber <<= 4;
						if (NTraits::TCIsFundamental<t_CReturn>::mc_Value)
							DestNumber |= Num;
						else
						{
							if (Num)
								DestNumber |= Num;
						}
						bFoundNum = true;

						++pParseStr;
					}

					break;
				}
				else
					break;

				++pParseStr;
			}	

			_pStr = (const t_CData *)pParseStr;

			if (bFoundNum)			
				return DestNumber * Sign;
			else
				return _FailValue;
		}

		template <typename t_CData, typename t_CReturn>
			inline_medium t_CReturn fg_StrToIntParseHexNoSign(const t_CData *&_pStr, t_CReturn _FailValue)
		{
			t_CReturn DestNumber = 0;
			typedef typename NTraits::TCUnsigned<t_CData>::CType CData;
			const CData *pParseStr = (const CData *)_pStr;
			aint bFoundNum = false;
			// Parse for characters, and end if str terminator is found
			while ((*pParseStr))
			{
				while ((*pParseStr))
				{
					aint Num;
					if ((*pParseStr) >= '0' && (*pParseStr) <= '9')
						Num = (*pParseStr) - '0';
					else if ((*pParseStr) >= 'a' && (*pParseStr) <= 'f')
						Num = ((*pParseStr) - 'a') + 10;
					else if ((*pParseStr) >= 'A' && (*pParseStr) <= 'F')
						Num = ((*pParseStr) - 'A') + 10;
					else
						break;

					DestNumber <<= 4;
					if (NTraits::TCIsFundamental<t_CReturn>::mc_Value)
						DestNumber |= Num;
					else
					{
						if (Num)
							DestNumber |= Num;
					}
					bFoundNum = true;

					++pParseStr;
				}
				break;
				++pParseStr;
			}	

			_pStr = (const t_CData *)pParseStr;

			if (bFoundNum)			
				return DestNumber;
			else
				return _FailValue;
		}

		template <typename t_CData, typename t_CReturn>
			inline_small t_CReturn fg_StrToIntBase10(const t_CData *_pStr, t_CReturn _FailValue)
		{
			const t_CData *pStr = _pStr;
			return fg_StrToIntBase10Parse(pStr, _FailValue);
		}


		template <typename t_CData, typename t_CReturn>
			t_CReturn fg_StrToIntBase10Parse(const t_CData *&_pStr, t_CReturn _FailValue)
		{
			t_CReturn DestNumber = 0;
			const t_CData *pParseStr = _pStr;

			t_CReturn Sign = 1;

			aint bFoundNum = false;

			if ((*pParseStr) == '-')
			{
				++pParseStr;
				Sign = -1;
			}

			// Parse for characters, and end if str terminator is found
			while ((*pParseStr))
			{
				if ((*pParseStr) < '0' || (*pParseStr) > '9')
					break;

				DestNumber *= 10;
				DestNumber += (*pParseStr) - '0';
				bFoundNum = true;
				++pParseStr;
			}	

			_pStr = pParseStr;

			if (bFoundNum)			
				return DestNumber * Sign;
			else
				return _FailValue;
		}


		template <typename t_CData, typename t_CReturn>
			inline_large t_CReturn fg_StrToIntBase10NoSign(const t_CData *_pStr, t_CReturn _FailValue)
		{
			t_CReturn DestNumber = 0;
			//	const t_CData *pParseStr = _pStr;

			// Parse for characters, and end if str terminator is found
			while ((*_pStr) >= '0' && (*_pStr) <= '9')
			{
				DestNumber *= 10;
				DestNumber += (*(_pStr++)) - '0';
			}	

			//	_pStr = pParseStr;

			return DestNumber;
		}


		template <typename t_CData, typename t_CReturn>
			inline_large t_CReturn fg_StrToIntBase10ParseNoSign(const t_CData *&_pStr, t_CReturn _FailValue)
		{
			t_CReturn DestNumber = 0;
			const t_CData *pParseStr = _pStr;

			// Parse for characters, and end if str terminator is found
			while ((*pParseStr) >= '0' && (*pParseStr) <= '9')
			{
				DestNumber *= 10;
				DestNumber += (*(pParseStr++)) - '0';
			}	

			_pStr = pParseStr;

			return DestNumber;
		}
		
		template <typename t_CData, typename t_CReturn, typename t_CTerm>
			inline_small t_CReturn fg_StrToInt(const t_CData *_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
		{
			const t_CData *pStr = _pStr;
			return fg_StrToIntParse(pStr, _FailValue, _pStrTerminators, true);
		}

		template <typename t_CData, typename t_CReturn>
			inline_small t_CReturn fg_StrToInt(const t_CData *_pStr, t_CReturn _FailValue)
		{
			const t_CData *pStr = _pStr;
			return fg_StrToIntParse(pStr, _FailValue, (const ch8 *)nullptr, true);
		}

		template <typename t_CData, typename t_CReturn>
		t_CReturn fg_StrToIntParse(const t_CData *&_pStr, t_CReturn _FailValue)
		{
			return fg_StrToIntParse(_pStr, _FailValue, (const ch8 *)nullptr, true);
		}

		template <typename t_CData, typename t_CReturn, typename t_CTerm>
			inline_small t_CReturn fg_StrToIntExact(const t_CData *_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
		{
			const t_CData *pStr = _pStr;
			return fg_StrToIntParse(pStr, _FailValue, _pStrTerminators, false);
		}

		template <typename t_CData, typename t_CReturn>
			inline_small t_CReturn fg_StrToIntExact(const t_CData *_pStr, t_CReturn _FailValue)
		{
			const t_CData *pStr = _pStr;
			return fg_StrToIntParse(pStr, _FailValue, (const ch8 *)nullptr, false);
		}

		template <typename t_CData, typename t_CReturn>
		t_CReturn fg_StrToIntParseExact(const t_CData *&_pStr, t_CReturn _FailValue)
		{
			return fg_StrToIntParse(_pStr, _FailValue, (const ch8 *)nullptr, false);
		}
		
		template <typename t_CData, typename t_CReturn, typename t_CTerm>
		t_CReturn fg_StrToIntParseExact(const t_CData *&_pStr, t_CReturn _FailValue, const t_CTerm *_pStrTerminators)
		{
			return fg_StrToIntParse(_pStr, _FailValue, _pStrTerminators, false);
		}
		

	}
}

