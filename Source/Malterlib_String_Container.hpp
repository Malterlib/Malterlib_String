// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
#ifdef DMibDebuggerHelpers
	template <typename t_CTCStrTraits>
	TCStrAggregateTypeHelper<t_CTCStrTraits::CStrTraits::mc_Type> TCStrAggregate<t_CTCStrTraits>::fs_TypeDebugHelper()
	{
		return {};
	}
#endif

	CStr fg_ReadTextStream(NStream::CBinaryStream &_Stream, bool _bAssumeUTF8 = false);

	template <typename t_TCStrTraits>
	inline_large TCStrAggregate<t_TCStrTraits> &TCStrAggregate<t_TCStrTraits>::operator +=(ch32 _ToAdd)
	{
		f_AddChar(_ToAdd);
		return *this;
	}

	template <typename t_CTCStrTraits>
	template <bool tf_bRemoveEmpty>
	NContainer::TCVector<TCStr<t_CTCStrTraits>> TCStrAggregate<t_CTCStrTraits>::f_SplitEscaped(CChar _Separator) const
	{
		NContainer::TCVector<TCStr<t_CTCStrTraits>> Result;

		auto const *pParse = this->f_GetStr();
		auto const *pParseEnd = pParse + this->f_GetLen();
		auto const *pParseStart = pParse;

		TCStr<t_CTCStrTraits> Next;

		while (pParse < pParseEnd)
		{
			if (*pParse == _Separator)
			{
				Next.f_AddStr(pParseStart, pParse - pParseStart);
				if constexpr (tf_bRemoveEmpty)
				{
					if (Next)
						Result.f_Insert(fg_Move(Next));
				}
				else
					Result.f_Insert(fg_Move(Next));
				++pParse;
				pParseStart = pParse;
				continue;
			}
			else if (*pParse == '\\')
			{
				Next.f_AddStr(pParseStart, pParse - pParseStart);
				++pParse;
				pParseStart = pParse;
				if (*pParse)
					++pParse;
				continue;
			}
			else
				++pParse;
		}

		if (pParse - pParseStart)
			Next.f_AddStr(pParseStart, pParse - pParseStart);

		if constexpr (tf_bRemoveEmpty)
		{
			if (Next)
				Result.f_Insert(fg_Move(Next));
		}
		else
			Result.f_Insert(fg_Move(Next));

		return Result;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CContainer>
	TCStr<t_CTCStrTraits> TCStrAggregate<t_CTCStrTraits>::fs_JoinEscaped(tf_CContainer &&_Strings, CChar _Separator)
	{
		CChar EscapeChars[] = {'\\', _Separator, 0};
		TCStr<t_CTCStrTraits> Return;
		bool bFirst = true;
		for (auto &Str : _Strings)
		{
			if (!bFirst)
				Return.f_AddChar(_Separator);
			bFirst = false;
			Return += Str.f_EscapeStrNoQuotes(EscapeChars);
		}
		return Return;
	}

	template <typename t_CTCStrTraits>
	template <bool tf_bRemoveEmpty, typename tf_CStrSeparator>
	NContainer::TCVector<TCStr<t_CTCStrTraits>> TCStrAggregate<t_CTCStrTraits>::f_Split(tf_CStrSeparator const &_Separator) const
	{
		NContainer::TCVector<TCStr<t_CTCStrTraits>> Result;

		auto const *pParse = this->f_GetStr();
		auto const *pParseEnd = pParse + this->f_GetLen();
		mint SeparatorLen = fg_StrLen(_Separator);

		while (pParse < pParseEnd)
		{
			auto iSplitPoint = fg_StrFind(pParse, _Separator, pParseEnd - pParse);
			if (iSplitPoint < 0)
			{
				if constexpr (tf_bRemoveEmpty)
				{
					if (pParseEnd != pParse)
						Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, pParseEnd - pParse));
				}
				else
					Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, pParseEnd - pParse));
				return Result;
			}
			if constexpr (tf_bRemoveEmpty)
			{
				if (iSplitPoint)
					Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, iSplitPoint));
			}
			else
				Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, iSplitPoint));
			pParse += iSplitPoint + SeparatorLen;
		}

		if constexpr (!tf_bRemoveEmpty)
			Result.f_Insert();

		return Result;
	}

	template <typename t_CTCStrTraits>
	template <bool tf_bRemoveEmpty>
	NContainer::TCVector<TCStr<t_CTCStrTraits>> TCStrAggregate<t_CTCStrTraits>::f_SplitLine() const
	{
		NContainer::TCVector<TCStr<t_CTCStrTraits>> Result;

		auto const *pParse = this->f_GetStr();
		auto const *pParseEnd = pParse + this->f_GetLen();

		while (pParse < pParseEnd)
		{
			auto iSplitPoint = fg_StrFindChars(pParse, "\r\n", pParseEnd - pParse);
			if (iSplitPoint < 0)
			{
				if constexpr (tf_bRemoveEmpty)
				{
					if (pParseEnd != pParse)
						Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, pParseEnd - pParse));
				}
				else
					Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, pParseEnd - pParse));
				return Result;
			}
			if constexpr (tf_bRemoveEmpty)
			{
				if (iSplitPoint)
					Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, iSplitPoint));
			}
			else
				Result.f_Insert(TCStr<t_CTCStrTraits>(pParse, iSplitPoint));

			pParse += iSplitPoint;
			if (*pParse == '\r')
				++pParse;
			if (*pParse == '\n')
				++pParse;
		}

		if constexpr (!tf_bRemoveEmpty)
			Result.f_Insert();

		return Result;
	}

	template <typename t_CTCStrTraits>
	template <typename tf_CContainer, typename tf_CStrSeparator>
	TCStr<t_CTCStrTraits> TCStrAggregate<t_CTCStrTraits>::fs_Join(tf_CContainer &&_Strings, tf_CStrSeparator const &_Separator)
	{
		TCStr<t_CTCStrTraits> Return;
		bool bFirst = true;
		for (auto &Str : _Strings)
		{
			if (!bFirst)
				Return += _Separator;
			bFirst = false;
			Return += Str;
		}
		return Return;
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize, typename tf_CStrIterator>
	typename TCEnableIf<t_CharSize == 1, void>::CType TCStrAggregate<t_TCStrTraits>::fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From)
	{
		static_assert(sizeof(CChar) == 1 && mc_Type == EStrType_UTF, "Lossy conversion");

		mint LenNeeded = _StrLen;
		auto fl_CalcLen
			= [&](mint _nChars) -> ch8 *
			{
				LenNeeded += _nChars;
				return nullptr;
			}
		;
		auto Iter = _From;
		while (Iter)
		{
			fg_EncodeUTF8Char(*Iter, fl_CalcLen);
			++Iter;
		}
		mint MaxLen = CImp::f_CreateWritableBuffer(LenNeeded + 1, false);
		auto *pOut = CImp::f_GetStrWritable();
		auto *pOutStart = pOut;
		auto *pOutMax = pOut + MaxLen - 1;

		pOut += _StrLen;

		auto fl_AddChars
			= [&](mint _nChars) -> ch8 *
			{
				if (pOut + _nChars > pOutMax)
					return nullptr;
				auto *pRet = pOut;
				pOut += _nChars;
				return (ch8 *)pRet;
			}
		;

		Iter = _From;
		while (Iter)
		{
			if (!fg_EncodeUTF8Char(*Iter, fl_AddChars))
				break;
			++Iter;
		}

		*pOut = 0;
		_StrLen = pOut - pOutStart;
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize, typename tf_CStrIterator>
	typename TCEnableIf<t_CharSize == 2, void>::CType TCStrAggregate<t_TCStrTraits>::fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From)
	{
		static_assert(sizeof(CChar) == 2 && mc_Type == EStrType_UTF, "Lossy conversion");
		mint LenNeeded = _StrLen;
		auto fl_CalcLen
			= [&](mint _nChars) -> ch16 *
			{
				LenNeeded += _nChars;
				return nullptr;
			}
		;
		auto Iter = _From;
		while (Iter)
		{
			fg_EncodeUTF16Char(*Iter, fl_CalcLen);
			++Iter;
		}
		mint MaxLen = CImp::f_CreateWritableBuffer(LenNeeded + 1, false);
		auto *pOut = CImp::f_GetStrWritable();
		auto *pOutStart = pOut;
		auto *pOutMax = pOut + MaxLen - 1;

		pOut += _StrLen;

		auto fl_AddChars
			= [&](mint _nChars) -> ch16 *
			{
				if (pOut + _nChars > pOutMax)
					return nullptr;
				auto *pRet = pOut;
				pOut += _nChars;
				return (ch16 *)pRet;
			}
		;

		Iter = _From;
		while (Iter)
		{
			if (!fg_EncodeUTF16Char(*Iter, fl_AddChars))
				break;
			++Iter;
		}

		*pOut = 0;
		_StrLen = pOut - pOutStart;
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize, typename tf_CStrIterator>
	typename TCEnableIf<t_CharSize != 1 && t_CharSize != 2, void>::CType TCStrAggregate<t_TCStrTraits>::fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From)
	{
		static_assert(sizeof(CChar) == 4 && mc_Type == EStrType_Unicode, "Lossy conversion");
		mint LenNeeded = _StrLen;
		auto Iter = _From;
		while (Iter)
		{
			++LenNeeded;
			++Iter;
		}
		mint MaxLen = CImp::f_CreateWritableBuffer(LenNeeded + 1, false);
		auto *pOut = CImp::f_GetStrWritable();
		auto *pOutStart = pOut;
		auto *pOutMax = pOut + MaxLen - 1;

		pOut += _StrLen;

		Iter = _From;
		while (Iter)
		{
			if (pOut >= pOutMax)
				break;

			*pOut = *Iter;
			++pOut;
			++Iter;
		}

		*pOut = 0;
		_StrLen = pOut - pOutStart;
	}

	template <typename t_TCStrTraits>
	TCStr<t_TCStrTraits> TCStr<t_TCStrTraits>::fs_ReadTextStream(NStream::CBinaryStream &_Stream, bool _bAssumeUTF8)
	{
		CStr Temp = fg_ReadTextStream(_Stream, _bAssumeUTF8);

		return TCStr<t_TCStrTraits>(Temp);
	}

	template <typename t_TCStrTraits>
	template <typename t_CStrTraitsF>
	inline_large TCStrAggregate<t_TCStrTraits> & TCStrAggregate<t_TCStrTraits>::operator += (const TCStrAggregate<t_CStrTraitsF> &_Str)
	{
		f_AddStr(_Str);
		return *this;
	}

	template <typename t_TCStrTraits>
	template <typename t_CStrTraitsF>
	inline_large TCStrAggregate<t_TCStrTraits> &TCStrAggregate<t_TCStrTraits>::operator +=(const TCStr<t_CStrTraitsF> &_Str)
	{
		return operator += ((const TCStrAggregate<t_CStrTraitsF>&)_Str);
	}

	template <typename t_TCStrTraits>
	template <typename t_CStrTraitsF>
	void TCStrAggregate<t_TCStrTraits>::f_AddStr(TCStrAggregate<t_CStrTraitsF> const &_From)
	{
		if constexpr (t_CStrTraitsF::CStrTraits::mc_Type == EStrType_Ansi && t_TCStrTraits::CStrTraits::mc_Type != EStrType_Ansi)
		{
			CTempStr Temp;
			NSys::NStr::fg_SystemDecodeAnsiStr(_From.f_GetStr(), Temp);
			f_AddStr(Temp);
		}
		else if constexpr (t_CStrTraitsF::CStrTraits::mc_Type == EStrType_Ansi && t_TCStrTraits::CStrTraits::mc_Type == EStrType_Ansi)
		{
			aint Length = f_GetLen();
			CAddStrAgrs Args(Length, _From.f_GetLen());
			fp_AddStrLengthAware(Args, _From.f_GetStr());
			CImp::f_SetStrLen(Length);
		}
		else if constexpr
			(
				t_CStrTraitsF::CStrTraits::mc_Type != EStrType_Ansi && (t_CStrTraitsF::CStrTraits::mc_Type == mc_Type && sizeof(CChar) == sizeof(typename t_CStrTraitsF::CStrTraits::CChar))
			)
		{
			f_AddStr(_From.f_GetStr(), _From.f_GetLen());
		}
		else if constexpr
			(
				t_CStrTraitsF::CStrTraits::mc_Type != EStrType_Ansi && !(t_CStrTraitsF::CStrTraits::mc_Type == mc_Type && sizeof(CChar) == sizeof(typename t_CStrTraitsF::CStrTraits::CChar))
			)
		{
			if (*_From.f_GetStr() != 0)
			{
				aint Length = f_GetLen();
				f_AddFromUnicodeIterator(Length, _From.f_GetUnicodeIterator());
				CImp::f_SetStrLen(Length);
			}
		}
		else
		{
			static_assert(NTraits::gc_MakeValueDependent<false, t_CStrTraitsF>, "Unhandled case");
		}
	}

	template <typename t_TCStrTraits>
	template <typename t_CStrTraitsF>
	void TCStrAggregate<t_TCStrTraits>::f_SetStr(TCStrAggregate<t_CStrTraitsF> const &_From)
	{
		if constexpr (t_CStrTraitsF::CStrTraits::mc_Type == EStrType_Ansi && t_TCStrTraits::CStrTraits::mc_Type != EStrType_Ansi)
		{
			CTempStr Temp;
			NSys::NStr::fg_SystemDecodeAnsiStr(_From.f_GetStr(), Temp);
			f_SetStr(Temp);
		}
		else if constexpr (t_CStrTraitsF::CStrTraits::mc_Type == EStrType_Ansi && t_TCStrTraits::CStrTraits::mc_Type == EStrType_Ansi)
		{
			aint Length = 0;
			CAddStrAgrs Args(Length, _From.f_GetLen());
			fp_AddStrLengthAware(Args, _From.f_GetStr());
			CImp::f_SetStrLen(Length);
		}
		else if constexpr
			(
				t_CStrTraitsF::CStrTraits::mc_Type != EStrType_Ansi && (t_CStrTraitsF::CStrTraits::mc_Type == mc_Type && sizeof(CChar) == sizeof(typename t_CStrTraitsF::CStrTraits::CChar))
			)
		{
			f_SetStr(_From.f_GetStr(), _From.f_GetLen());
		}
		else if constexpr
			(
				t_CStrTraitsF::CStrTraits::mc_Type != EStrType_Ansi && !(t_CStrTraitsF::CStrTraits::mc_Type == mc_Type && sizeof(CChar) == sizeof(typename t_CStrTraitsF::CStrTraits::CChar))
			)
		{
			if (*_From.f_GetStr() != 0)
			{
				aint Length = 0;
				f_AddFromUnicodeIterator(Length, _From.f_GetUnicodeIterator());
				CImp::f_SetStrLen(Length);
			}
			else
				this->f_Clear();
		}
		else
		{
			static_assert(NTraits::gc_MakeValueDependent<false, t_CStrTraitsF>, "Unhandled case");
		}
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize>
	typename TCEnableIf<t_CharSize == 1, void>::CType TCStrAggregate<t_TCStrTraits>::fp_ConvertFromType(EStrType _Type)
	{
		DMibFastCheck(_Type <= mc_Type);
		if (_Type < mc_Type)
		{
			switch (_Type)
			{
			case EStrType_Ansi:
				{
					CTempStr Decoded;
					NSys::NStr::fg_SystemDecodeAnsiStr((ch8 const *)f_GetStr(), Decoded);
					this->f_Clear();
					TCStr<t_TCStrTraits> New;
					aint Len = 0;
					New.f_AddFromUnicodeIterator(Len, Decoded.f_GetUnicodeIterator());
					New.f_SetStrLen(Len);
					this->f_Assign(fg_Move(New));
				}
				break;
			case EStrType_Unicode:
				{
					DMibSafeCheck(mc_Type == EStrType_UTF, "Must convert to UTF");
					TCStr<t_TCStrTraits> New;
					aint Len = 0;
					New.f_AddFromUnicodeIterator(Len, NStr::TCStrIteratorUnicode<ch8>(f_GetStr(), f_GetLen()));
					New.f_SetStrLen(Len);
					this->f_Assign(fg_Move(New));
				}
				break;
			default:
				DMibFastCheck(false);
				break;
			}
		}
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize>
	typename TCEnableIf<t_CharSize == 2, void>::CType TCStrAggregate<t_TCStrTraits>::fp_ConvertFromType(EStrType _Type)
	{
		DMibFastCheck(_Type <= mc_Type);
		if (_Type < mc_Type)
		{
			switch (_Type)
			{
			case EStrType_Unicode:
				{
					TCStr<t_TCStrTraits> New;
					aint Len = 0;
					New.f_AddFromUnicodeIterator(Len, NStr::TCStrIteratorUnicode<ch16>(f_GetStr(), f_GetLen()));
					New.f_SetStrLen(Len);
					this->f_Assign(fg_Move(New));
				}
				break;
			default:
				DMibFastCheck(false);
				break;
			}
		}
	}

	template <typename t_TCStrTraits>
	template <int t_CharSize>
	typename TCEnableIf<t_CharSize != 1 && t_CharSize != 2, void>::CType TCStrAggregate<t_TCStrTraits>::fp_ConvertFromType(EStrType _Type)
	{
		DMibFastCheck(_Type == EStrType_Unicode);
	}


	template <typename t_TCStrTraits>
	template <typename t_CStrDataType>
	inline_large TCStrAggregate<t_TCStrTraits> &TCStrAggregate<t_TCStrTraits>::operator +=(const t_CStrDataType *_pToAdd)
	{
		f_AddStr(_pToAdd);
		return *this;
	}

	template <typename t_TCStrTraits>
	inline_large TCStrAggregate<t_TCStrTraits> &TCStrAggregate<t_TCStrTraits>::operator +=(CFormat const &_Format)
	{
		_Format.f_FormatToStrConcat(*this);
		return *this;
	}

	class CCompareNoCase
	{
	public:
		template <typename tf_CLeft, typename tf_CRight>
		COrdering_Weak operator()(const tf_CLeft &_Left, const tf_CRight &_Right) const
		{
			return fg_StrCmpNoCase(_Left, _Right) <=> 0;
		}
	};
}
namespace NMib::NStream
{
	inline_always void fg_StrDecodeLenType(uint64 &_Len, uint32 _StreamSize, NStr::EStrType &_Type)
	{
		_Type = NStr::EStrType_Ansi;
		switch (_StreamSize)
		{
		case 1:
			{
				_Type = (NStr::EStrType)(_Len >> (sizeof(uint8) * 8-2));
				_Len = uint8(_Len) & ((uint8(1) << (sizeof(uint8) * 8-2)) - 1);
			}
			break;
		case 2:
			{
				_Type = (NStr::EStrType)(_Len >> (sizeof(uint16) * 8-2));
				_Len = uint16(_Len) & ((uint16(1) << (sizeof(uint16) * 8-2)) - 1);
			}
			break;
		case 4:
			{
				_Type = (NStr::EStrType)(_Len >> (sizeof(uint32) * 8-2));
				_Len = uint32(_Len) & ((uint32(1) << (sizeof(uint32) * 8-2)) - 1);
			}
			break;
		case 8:
			{
				_Type = (NStr::EStrType)(_Len >> (sizeof(uint64) * 8-2));
				_Len = uint64(_Len) & ((uint64(1) << (sizeof(uint64) * 8-2)) - 1);
			}
			break;
		}
	}

	inline_always void fg_StrEncodeLenType(uint64 &_Len, uint32 _StreamSize, NStr::EStrType _Type)
	{
		switch (_StreamSize)
		{
		case 1:
			{
				_Len = uint8(fg_Clamp(_Len, uint8(0), uint8((uint8(1) << (sizeof(uint8)*8-2)) - uint8(1))) | (uint8(_Type) << (sizeof(uint8) * 8-2)));
			}
			break;
		case 2:
			{
				_Len = uint16(fg_Clamp(_Len, uint16(0), uint16((uint16(1) << (sizeof(uint16)*8-2)) - uint16(1))) | (uint16(_Type) << (sizeof(uint16) * 8-2)));
			}
			break;
		case 4:
			{
				_Len = uint32(fg_Clamp(_Len, uint32(0), uint32((uint32(1) << (sizeof(uint32)*8-2)) - uint32(1))) | (uint32(_Type) << (sizeof(uint32) * 8-2)));
			}
			break;
		case 8:
			{
				_Len = uint64(fg_Clamp(_Len, uint64(0), uint64((uint64(1) << (sizeof(uint64)*8-2)) - uint64(1))) | (uint64(_Type) << (sizeof(uint64) * 8-2)));
			}
			break;
		}
	}

	template <typename t_CStream, typename t_TCStrTraitsIn>
	class TCBinaryStreamTypeReference<t_CStream, NStr::TCStrAggregate<t_TCStrTraitsIn> >
	{
	public:
		static void fs_Feed(t_CStream &_Stream, NStr::TCStrAggregate<t_TCStrTraitsIn> const &_Data)
		{
			uint64 Len = _Data.f_GetLen();
			uint64 LenStream = Len;
			fg_StrEncodeLenType(LenStream, _Stream.f_LengthSize(), _Data.mc_Type);
			fg_FeedLenToStream(_Stream, LenStream);
			if (Len != 0)
				_Stream.f_FeedBytes(_Data.f_GetStr(), Len * sizeof(typename NStr::TCStrAggregate<t_TCStrTraitsIn>::CChar));
		}

		static void fs_Consume(t_CStream &_Stream, NStr::TCStrAggregate<t_TCStrTraitsIn> &_Data)
		{
			uint64 Len;
			fg_ConsumeLenFromStream(_Stream, Len);
			NStr::EStrType Type = NStr::EStrType_Ansi;
			fg_StrDecodeLenType(Len, _Stream.f_LengthSize(), Type);
			fg_CheckLengthLimit(_Stream, Len);

			//NStr::TCStr<t_TCStrTraitsIn>

			typename NStr::TCStrAggregate<t_TCStrTraitsIn>::CChar *pStr = _Data.f_GetStr(Len + 1);
			auto Cleanup = g_OnScopeExit / [&]
				{
					_Data.f_Clear();
				}
			;

			if (Len != 0)
				_Stream.f_ConsumeBytes(pStr, Len * sizeof(typename NStr::TCStrAggregate<t_TCStrTraitsIn>::CChar));
			Cleanup.f_Clear();
			pStr[Len] = 0;
			_Data.f_SetStrLen(Len);
			_Data.fp_ConvertFromType(Type);
		}
	};

	template <typename t_CStream, typename t_TCStrTraitsIn>
	class TCBinaryStreamTypeReference<t_CStream, NStr::TCStr<t_TCStrTraitsIn> > : public TCBinaryStreamTypeReference<t_CStream, NStr::TCStrAggregate<t_TCStrTraitsIn> >
	{
	};
}
