// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NStr
{
	template <typename tf_CType>
	CStrFormatBinaryWrapper::CStrFormatBinaryWrapper(tf_CType const &_Data)
		: mp_pData((const void *)&_Data)
		, mp_Size(sizeof(_Data))
	{
	}

	template <typename tf_CType>
	CStrFormatBinaryWrapperUntyped::CStrFormatBinaryWrapperUntyped(tf_CType &_Data)
		: CStrFormatBinaryWrapper(_Data)
	{
	}

	template <typename tf_CData>
	CStrFormatBinaryWrapper fg_FormatAsBinary(tf_CData const &_Data)
	{
		return CStrFormatBinaryWrapper(_Data);
	}

	template <typename t_CFormatter, typename t_CData, typename t_CTypeWithConst>
	auto TCStringFormatterAll<t_CFormatter, t_CData, t_CTypeWithConst>::fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data)
		-> decltype(CStringFormatter::template fs_CreateFormat<t_CTypeWithConst>(_Formatter, _Data))
	{
		return CStringFormatter::template fs_CreateFormat<t_CTypeWithConst>(_Formatter, _Data);
	}

	template <typename tf_CFormatter, typename tf_CData>
	inline_small typename NPrivate::TCDetermineStringFormatterReturnType<tf_CFormatter, tf_CData>::CType fg_CreateStringFormatter(tf_CFormatter &_Formatter, tf_CData const &_Data)
	{
		return TCStringFormatterAll<tf_CFormatter, tf_CData>::fs_CreateFormat(_Formatter, _Data);
	}

	template <typename t_CTCStrTraits>
	TCFormat<t_CTCStrTraits>::TCFormat(TCFormat &&_Other)
	{
		m_pFormatStr = _Other.m_pFormatStr;
		m_pFormats = m_plFormats;
		m_nFormats = 0;
		m_iCurrentAlloc = 0;

		f_MoveFormats(fg_Move(_Other));
	}

	template <typename t_CTCStrTraits>
	TCFormat<t_CTCStrTraits>::~TCFormat()
	{
		f_ClearFormats();
	}

	template <typename t_CTCStrTraits>
	void TCFormat<t_CTCStrTraits>::f_MoveFormats(TCFormat &&_Other)
	{
		TICStrFormatType<TCFormat> **pFormatList = _Other.fp_GetFormatList();

		for (uaint i = 0; i < _Other.m_nFormats; ++i)
		{
			TICStrFormatType<TCFormat> *pFormat = (TICStrFormatType<TCFormat> *)((umint)pFormatList[i] & (~((umint)0x3)));
			pFormat->f_Move(*this);
		}
	}

	template <typename t_CTCStrTraits>
	auto TCFormat<t_CTCStrTraits>::operator=(TCFormat &&_Other) -> TCFormat &
	{
		f_ClearFormats();

		m_pFormatStr = _Other.m_pFormatStr;
		f_MoveFormats(fg_Move(_Other));

		return *this;
	}

	template <typename t_CTCStrTraits>
	void TCFormat<t_CTCStrTraits>::fp_AddFormat(TICStrFormatType<TCFormat> *_pFormat, EStringFormatTypeFlag _Flags)
	{
		TICStrFormatType<TCFormat> *pFormat = (TICStrFormatType<TCFormat> *)((umint)_pFormat | static_cast<umint>(_Flags));
		if (m_nFormats < mcp_StaticFormats)
		{
			m_plFormats[m_nFormats] = pFormat;
			++m_nFormats;
			return;
		}

		if (m_nFormats >= m_lFormats.f_GetLen())
		{
			if (!m_lFormats.f_GetLen())
			{
				m_lFormats.f_SetLen(m_nFormats*2);
				NMemory::fg_MemCopy(m_lFormats.f_GetArray(), m_plFormats, m_nFormats * sizeof(void *));
			}
			else
				m_lFormats.f_SetLen(m_nFormats*2);
		}
		m_pFormats = m_lFormats.f_GetArray();
		m_pFormats[m_nFormats] = pFormat;
		++m_nFormats;
	}

	template <typename t_CTCStrTraits>
	inline_medium void *TCFormat<t_CTCStrTraits>::f_AllocSpace(umint _Size, EStringFormatTypeFlag &_Flags)
	{
		umint nNeeded = _Size;
		_Flags = EStringFormatTypeFlag::mc_None;

		void *pSpace = fp_AllocSpace(nNeeded);
		if (!pSpace)
		{
			pSpace = t_CTCStrTraits::CStrTraits::CAllocator::f_Alloc(nNeeded);
			_Flags = EStringFormatTypeFlag::mc_NeedDealloc;
		}

		return pSpace;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType, typename ...tfp_CParams>
	inline_medium tf_CType *TCFormat<t_CTCStrTraits>::f_Alloc(tfp_CParams && ...p_Params)
	{
		EStringFormatTypeFlag Flags;
		void *pSpace = f_AllocSpace(sizeof(tf_CType), Flags);
		tf_CType *pNew = new(pSpace) tf_CType(fg_Forward<tfp_CParams>(p_Params)...);
		Flags |= (tf_CType::mc_bNeedDestruct ? EStringFormatTypeFlag::mc_NeedDestruct : EStringFormatTypeFlag::mc_None);
		fp_AddFormat(pNew, Flags);
		return pNew;
	}

	template <typename t_CTCStrTraits>
	inline_medium auto TCFormat<t_CTCStrTraits>::f_GetArg(aint _iArgument) const -> TICStrFormatType<TCFormat> const *
	{
		if (_iArgument < 0)
			_iArgument = m_iCurrentArgument++;

		if (_iArgument >= (aint)m_nFormats)
			return nullptr;

		return fp_GetFormatEntry(_iArgument);
	}

	template <typename t_CTCStrTraits>
	umint TCFormat<t_CTCStrTraits>::f_GetNumArgs() const
	{
		return m_nFormats;
	}

	template <typename t_CTCStrTraits>
	inline_medium TCFormat<t_CTCStrTraits>::TCFormat(const CChar *_pFormatStr)
	{
		m_pFormatStr = _pFormatStr;
		m_pFormats = m_plFormats;;
		m_nFormats = 0;
		m_iCurrentAlloc = 0;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CTCStrTraits>
	inline_medium TCFormat<t_CTCStrTraits>::TCFormat(TCStr<tf_CTCStrTraits> const &_Format)
	{
		m_pFormatStr = _Format;
		m_pFormats = m_plFormats;
		m_nFormats = 0;
		m_iCurrentAlloc = 0;
	}

	template <typename t_CTCStrTraits>
	bool TCFormat<t_CTCStrTraits>::f_IsEmpty() const
	{
		return *m_pFormatStr == 0;
	}

	template <typename t_CTCStrTraits>
	void TCFormat<t_CTCStrTraits>::f_ClearFormats()
	{
		TICStrFormatType<TCFormat> **pFormatList = fp_GetFormatList();

		for (uaint i = 0; i < m_nFormats; ++i)
		{
			EStringFormatTypeFlag Flags = static_cast<EStringFormatTypeFlag>((umint)pFormatList[i] & 0x3);
			TICStrFormatType<TCFormat> *pFormat = (TICStrFormatType<TCFormat> *)((umint)pFormatList[i] & (~((umint)0x3)));

			if (fg_IsSet(Flags, EStringFormatTypeFlag::mc_NeedDealloc))
			{
				umint Size = pFormat->f_Destruct();
				t_CTCStrTraits::CStrTraits::CAllocator::f_Free(pFormat, Size);
			}
			else if (fg_IsSet(Flags, EStringFormatTypeFlag::mc_NeedDestruct))
				pFormat->f_Destruct();
		}

		m_pFormats = m_plFormats;
		m_nFormats = 0;
		m_iCurrentAlloc = 0;
	}

	template <typename t_CTCStrTraits>
	bool TCFormat<t_CTCStrTraits>::operator == (TCFormat const &_Right) const noexcept
	{
		if (fg_StrCmp(m_pFormatStr, _Right.m_pFormatStr) != 0)
			return false;

		if (m_nFormats != _Right.m_nFormats)
			return false;

		TICStrFormatType<TCFormat> **pFormatList = fp_GetFormatList();
		TICStrFormatType<TCFormat> **pFormatListRight = _Right.fp_GetFormatList();

		for (uaint i = 0; i < m_nFormats; ++i)
		{
			TICStrFormatType<TCFormat> *pFormat = (TICStrFormatType<TCFormat> *)((umint)pFormatList[i] & (~((umint)0x3)));
			TICStrFormatType<TCFormat> *pFormatRight = (TICStrFormatType<TCFormat> *)((umint)pFormatListRight[i] & (~((umint)0x3)));

			if (pFormat->f_GetTypeID() != pFormatRight->f_GetTypeID())
				return false;

			if (!pFormat->f_IsSame(pFormatRight))
				return false;
		}

		return true;
	}

	template <typename t_CTCStrTraits>
	inline_small void TCFormat<t_CTCStrTraits>::f_FormatToStr(TCStr<t_CTCStrTraits> &_Str) const
	{
		m_iCurrentArgument = 0;
		fp_FormatArgList<0>(*this, m_pFormatStr, _Str);
	}

	template <typename t_CTCStrTraits>
	inline_small void TCFormat<t_CTCStrTraits>::f_FormatToStrConcat(TCStr<t_CTCStrTraits> &_Str) const
	{
		m_iCurrentArgument = 0;
		fp_FormatArgList<1>(*this, m_pFormatStr, _Str);
	}

	template <typename t_CTCStrTraits>
	inline_small void TCFormat<t_CTCStrTraits>::f_FormatArgumentsToStr(TCStr<t_CTCStrTraits> &_Str) const
	{
		m_iCurrentArgument = 0;
		fp_FormatArguments<0>(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	inline_small void TCFormat<t_CTCStrTraits>::f_FormatArgumentsToStrConcat(TCStr<t_CTCStrTraits> &_Str) const
	{
		m_iCurrentArgument = 0;
		fp_FormatArguments<1>(*this, _Str);
	}

	template <typename t_CTCStrTraits>
	void TCFormat<t_CTCStrTraits>::f_SetFormatStr(const CChar *_pFormatStr)
	{
		m_pFormatStr = _pFormatStr;
	}

	template <typename t_CTCStrTraits>
	TCStr<t_CTCStrTraits> TCFormat<t_CTCStrTraits>::f_GetStr() const
	{
		TCStr<t_CTCStrTraits> Temp;
		f_FormatToStr(Temp);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	TCStr<t_CTCStrTraits> TCFormat<t_CTCStrTraits>::operator ^ (umint _nCopies) const
	{
		if (!_nCopies)
			return {};

		TCStr<t_CTCStrTraits> Temp = *this;
		--_nCopies;

		for (; _nCopies; --_nCopies)
			Temp += *this;

		return Temp;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CStr>
	void TCFormat<t_CTCStrTraits>::f_Format(tf_CStr &o_FormatInto) const
	{
		o_FormatInto += *this;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	inline_small auto TCFormat<t_CTCStrTraits>::operator << (tf_CType const &_Type) & -> TCFormat &
		requires
		( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
			!cHasFormatClass<tf_CType, EStrTypeClass_Untyped>
		)
	{
		TCStringFormatterAll<TCFormat, tf_CType, tf_CType const>::fs_CreateFormat(*this, _Type);
		return *this;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	inline_small auto TCFormat<t_CTCStrTraits>::operator << (tf_CType &_Type) & -> TCFormat &
		requires
		( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
			!cHasFormatClass<tf_CType, EStrTypeClass_Untyped>
		)
	{
		TCStringFormatterAll<TCFormat, tf_CType, tf_CType>::fs_CreateFormat(*this, _Type);
		return *this;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	inline_small auto TCFormat<t_CTCStrTraits>::operator << (tf_CType const &_Type) && -> TCFormat &&
		requires
		( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
			!cHasFormatClass<tf_CType, EStrTypeClass_Untyped>
		)
	{
		TCStringFormatterAll<TCFormat, tf_CType, tf_CType const>::fs_CreateFormat(*this, _Type);
		return fg_Move(*this);
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CType>
	inline_small auto TCFormat<t_CTCStrTraits>::operator << (tf_CType &_Type) && -> TCFormat &&
		requires
		( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
			!cHasFormatClass<tf_CType, EStrTypeClass_Untyped>
		)
	{
		TCStringFormatterAll<TCFormat, tf_CType, tf_CType>::fs_CreateFormat(*this, _Type);
		return fg_Move(*this);
	}

	template <typename t_CTCStrTraits>
	template <bool tf_bConcat>
	void TCFormat<t_CTCStrTraits>::fp_FormatArguments(const TCFormat &_Format, TCStr<t_CTCStrTraits> &_ToStr)
	{
		aint CurrentStrLen;
		aint MaxLen;
		if constexpr (tf_bConcat)
		{
			CurrentStrLen = _ToStr.f_GetLen();
			MaxLen = _ToStr.f_CreateWritableBuffer(CurrentStrLen + 1, false);
		}
		else
		{
			CurrentStrLen = 0;
			MaxLen = _ToStr.f_CreateWritableBuffer(1, true);
			if (MaxLen < 1)
				return;
			*(_ToStr.f_GetStrWritable()) = 0;
		}

		umint nFormats = _Format.m_nFormats;
		for (umint i = 0; i < nFormats; ++i)
		{
			const TICStrFormatType<TCFormat> *pFormatVar = _Format.fp_GetFormatEntry(i);
			pFormatVar->f_AddToStr(_ToStr, CurrentStrLen, nullptr, _Format);
		}

		_ToStr.f_SetStrLen(CurrentStrLen);
	}

	template <typename t_CTCStrTraits>
	template <bool tf_bConcat>
	void TCFormat<t_CTCStrTraits>::fp_FormatArgList(const TCFormat &_Format, const CChar *_pFormat, TCStr<t_CTCStrTraits> &_ToStr)
	{
		aint CurrentStrLen;
		aint MaxLen;
		if constexpr (tf_bConcat)
		{
			CurrentStrLen = _ToStr.f_GetLen();
			MaxLen = _ToStr.f_CreateWritableBuffer(CurrentStrLen + 1, false);
		}
		else
		{
			CurrentStrLen = 0;
			MaxLen = _ToStr.f_CreateWritableBuffer(1, true);
			if (MaxLen < 1)
				return;
			*(_ToStr.f_GetStrWritable()) = 0;
		}

		// Start by getting all parameters

		const CChar *pFormat = _pFormat;

		aint SearchMode = 0;
		while (*pFormat)
		{
			switch (SearchMode)
			{
			case 0:
				{
					// Copy text and search for variables
					aint MaxLen = _ToStr.f_CreateWritableBuffer(CurrentStrLen + 32, false) - 1;
					if (MaxLen <= CurrentStrLen)
					{
						_ToStr.f_SetStrLen(CurrentStrLen);
						return;
					}

					CChar *pWritePtr = _ToStr.f_GetStrWritable();
					CChar *pWritePtrStart = pWritePtr;
					const CChar *pWritePtrEnd = pWritePtr + MaxLen;
					pWritePtr += CurrentStrLen;
					const CChar *pAdd = pFormat;

					while (pWritePtrEnd - pWritePtr)
					{
						CChar CurrentFormat = (*pAdd);
						switch(CurrentFormat)
						{
						case '{':
							SearchMode = 1;
							++pAdd;
							break;
						case 0:
							break;
						default:
							*(pWritePtr++) = CurrentFormat;
							++pAdd;
							continue;
						}
						break;
					}
					pFormat = pAdd;

					*pWritePtr = 0;
					CurrentStrLen = (pWritePtr - pWritePtrStart);


				}
				break;
			case 1:
				{
					if ((*pFormat) == '{')
					{
						_ToStr.f_AddCharLengthAware(CurrentStrLen, *pFormat);
						SearchMode = 0;
						++pFormat;
						break;
					}
					else
					{
						//						static const CChar Terminators[] = {' ', '}', ','};
						// Parse a variable
						aint Variable = -1;
						if (*pFormat == '*')
						{
							++pFormat;
							aint ArgNumber;
							if (t_CTCStrTraits::CStrTraits::fs_CharIsNumber(*(pFormat)))
								ArgNumber = t_CTCStrTraits::CStrTraits::fs_StrToIntBase10ParseNoSign(pFormat, -1);
							else
								ArgNumber = -1;

							while ((*pFormat) == ' ')
								++pFormat;

							if ((*pFormat) == ',')
								++pFormat;
							const TICStrFormatType<TCFormat> * pFormatVar = _Format.f_GetArg(ArgNumber);
							if (pFormatVar)
							{
								Variable = pFormatVar->f_Get_aint();
							}
							else
							{
								const ch8 *pTmp = "###format var out of range###";
								while (*pTmp)
									_ToStr.f_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
								goto EndArgSearch;
							}

						}
						else if (t_CTCStrTraits::CStrTraits::fs_CharIsNumber(*pFormat))
						{
							Variable = t_CTCStrTraits::CStrTraits::fs_StrToIntBase10ParseNoSign(pFormat, (aint)-16324);

							while ((*pFormat) == ' ')
								++pFormat;

							if ((*pFormat) == ',')
								++pFormat;
							if (Variable == -16324)
							{
								const ch8 *pTmp = "###format var parse error###";
								while (*pTmp)
									_ToStr.f_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
								goto EndArgSearch;
							}
							else if (Variable < 0)
							{
								const ch8 *pTmp = "###format var out of range###";
								while (*pTmp)
									_ToStr.f_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
								goto EndArgSearch;
							}
						}
						else if (*pFormat == '\n')
						{
							const ch8 *pTmp = DMibNewLine;
							while (*pTmp)
								_ToStr.f_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
							goto EndArgSearch;
						}

						{
							const TICStrFormatType<TCFormat> * pFormatVar = _Format.f_GetArg(Variable);
							if (pFormatVar)
							{
								pFormatVar->f_AddToStr(_ToStr, CurrentStrLen, pFormat, _Format);
							}
							else
							{
								const ch8 *pTmp = "###format var out of range###";
								while (*pTmp)
									_ToStr.f_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
							}
						}

EndArgSearch:

						while ((*pFormat) && (*pFormat) != '}')
						{
							++pFormat;
						}

						if (*pFormat)
							++pFormat;

						SearchMode = 0;
					}

				}
				break;
			}

		}

		_ToStr.f_SetStrLen(CurrentStrLen);
	}

	template <typename t_CTCStrTraits>
	inline_small auto TCFormat<t_CTCStrTraits>::fp_GetFormatList() const -> TICStrFormatType<TCFormat> **
	{
		return m_pFormats;
	}

	template <typename t_CTCStrTraits>
	inline_small auto TCFormat<t_CTCStrTraits>::fp_GetFormatEntry(aint _iEntry) const -> TICStrFormatType<TCFormat> const *
	{
		return (TICStrFormatType<TCFormat> const *)((umint)m_pFormats[_iEntry] & (~((umint)0x3)));
	}

	template <typename t_CTCStrTraits>
	void *TCFormat<t_CTCStrTraits>::fp_AllocSpace(int _Bytes)
	{
		umint Needed = (_Bytes + sizeof(aint) - 1) / sizeof(aint);
		if (m_iCurrentAlloc + Needed > mcp_StaticSpace)
			return nullptr;

		void *pSpace = (void *)(m_AllocSpace + m_iCurrentAlloc);

		m_iCurrentAlloc += Needed;

		return pSpace;
	}

	template <typename tf_CFormat>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format)
	{
	}

	template <typename tf_CFormat, typename tf_CFirst, typename... tfp_CParams>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format, tf_CFirst &&_First)
	{
		_Format << fg_Forward<tf_CFirst>(_First);
	}

	template <typename tf_CFormat, typename tf_CFirst, typename... tfp_CParams>
	inline_always void fg_AddFormatParams(tf_CFormat &_Format, tf_CFirst &&_First, tfp_CParams &&...p_Params)
	{
		_Format << fg_Forward<tf_CFirst>(_First);
		fg_AddFormatParams(_Format, fg_Forward<tfp_CParams>(p_Params)...);
	}


	template <typename tf_CReturnString, typename tf_CFormat, typename... tfp_CParams>
	tf_CReturnString fg_Format(tf_CFormat const &_Format, tfp_CParams &&...p_Params)
	{
		typename tf_CReturnString::CFormat Formatter(_Format);

		fg_AddFormatParams(Formatter, fg_Forward<tfp_CParams>(p_Params)...);

		return Formatter;
	}

	template <typename tf_CReturnString, typename tf_CFormat, typename... tfp_CParams>
	void fg_AppendFormat(tf_CReturnString &_String, tf_CFormat const &_Format, tfp_CParams &&...p_Params)
	{
		typename tf_CReturnString::CFormat Formatter(_Format);

		fg_AddFormatParams(Formatter, fg_Forward<tfp_CParams>(p_Params)...);

		_String += Formatter;
	}
}
