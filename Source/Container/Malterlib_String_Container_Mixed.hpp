// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename t_CFormatter>
	struct TCStringFormatter<t_CFormatter, CMStrDeprecated> : public TCStringFormatter<t_CFormatter, CStr>
	{
	};

	template <typename t_CData0>
	struct TCChooseStrCompareType<CMStrDeprecated, TCStr<t_CData0>>
	{
	public:
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<typename TCStr<t_CData0>::CChar, ch32>>>;
	};

	template <typename t_CData0>
	struct TCChooseStrCompareType<TCStr<t_CData0>, CMStrDeprecated>
	{
	public:
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<typename TCStr<t_CData0>::CChar, ch32>>>;
	};

	template <typename t_CData0>
	struct TCChooseStrCompareType<CMStrDeprecated, t_CData0>
	{
	public:
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, ch32>>>;
	};

	template <typename t_CData0>
	struct TCChooseStrCompareType<t_CData0, CMStrDeprecated>
	{
	public:
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<t_CData0, ch32>>>;
	};

	template <>
	struct TCChooseStrCompareType<CMStrDeprecated, CMStrDeprecated>
	{
	public:
		using CType = NTraits::TCSigned<NTraits::TCLargerType<NTraits::TCLargestType<ch32, ch32>>>;
	};

	template <typename tf_CValue>
	CMStrDeprecated::CMStrDeprecated(tf_CValue &&_Other)
		: CStr(fg_Forward<tf_CValue>(_Other))
	{
	}

	template <typename tf_CValue>
	CMStrDeprecated &CMStrDeprecated::operator =(tf_CValue &&_Other)
	{
		(CStr &)*this = fg_Forward<tf_CValue>(_Other);
		return *this;
	}

	template <typename tf_CStrTraits>
	inline_large TCStr<tf_CStrTraits> &operator += (TCStr<tf_CStrTraits> &_Dest, CMStrDeprecated const &_String)
	{
		_Dest += (CStr const &)_String;
		return _Dest;
	}
}

namespace NMib::NStream
{
	template <typename t_CStream>
	class TCBinaryStreamTypeReference<t_CStream, NStr::CMStrDeprecated>
	{
	public:
		static constexpr void fs_Feed(t_CStream &_Stream, NStr::CMStrDeprecated const &_Data)
		{
			uint64 Len = _Data.f_GetLen();
			uint64 LenStream = Len;
			NStr::EStrType StrType = NStr::EStrType_Undefined;
			fg_StrEncodeLenType(LenStream, _Stream.f_LengthSize(), StrType);
			fg_FeedLenToStream(_Stream, LenStream);
			if (Len != 0)
				_Stream.f_FeedBytes(_Data.f_GetStr(), Len * sizeof(ch8));
		}

		static constexpr void fs_Consume(t_CStream &_Stream, NStr::CMStrDeprecated &_Data)
		{
			uint64 Len;
			fg_ConsumeLenFromStream(_Stream, Len);
			NStr::EStrType StrType = NStr::EStrType_Ansi;
			fg_StrDecodeLenType(Len, _Stream.f_LengthSize(), StrType);
			fg_CheckLengthLimit(_Stream, Len);

			uint32 Type;
			if (StrType == NStr::EStrType_Undefined)
			{
				StrType = NStr::EStrType_UTF;
				Type = NStr::EMStr_Type_CStr;
			}
			else
				_Stream.f_Consume(Type);
			_Data.f_Clear();

			switch (Type)
			{
			case NStr::EMStr_Type_CStr:
				{
					NStr::CStr NewStr;
					ch8 *pStr = NewStr.f_GetStr(Len + 1);
					if (Len != 0)
						_Stream.f_ConsumeBytes(pStr, Len * sizeof(ch8));
					pStr[Len] = 0;
					NewStr.f_SetStrLen(Len);
					switch (StrType)
					{
					case NStr::EStrType_Ansi:
						NStr::NPlatform::fg_SystemDecodeAnsiStr(NewStr.f_GetStr(), _Data);
						break;
					case NStr::EStrType_Unicode:
						{
							aint StrLen = 0;
							_Data.f_AddFromUnicodeIterator(StrLen, NStr::TCStrIteratorUnicode<ch8>(NewStr.f_GetStr(), NewStr.f_GetLen()));
							_Data.f_SetStrLen(StrLen);
							_Data.f_TrimSize();
						}
						break;
					default:
						_Data = fg_Move(NewStr);
						break;
					}

				}
				break;
			case NStr::EMStr_Type_CWStr:
				{
					NStr::CWStr NewStr;
					ch16 *pStr = NewStr.f_GetStr(Len + 1);
					if (Len != 0)
						_Stream.f_ConsumeBytes(pStr, Len * sizeof(ch16));
					pStr[Len] = 0;
					NewStr.f_SetStrLen(Len);
					switch (StrType)
					{
					case NStr::EStrType_Unicode:
						{
							aint StrLen = 0;
							_Data.f_AddFromUnicodeIterator(StrLen, NStr::TCStrIteratorUnicode<ch16>(NewStr.f_GetStr(), NewStr.f_GetLen()));
							_Data.f_SetStrLen(StrLen);
							_Data.f_TrimSize();
						}
						break;
					default:
						_Data = NewStr;
						break;
					}
				}
				break;
			case NStr::EMStr_Type_CUStr:
				{
					NStr::CUStr NewStr;
					ch32 *pStr = NewStr.f_GetStr(Len + 1);
					if (Len != 0)
						_Stream.f_ConsumeBytes(pStr, Len * sizeof(ch32));
					pStr[Len] = 0;
					NewStr.f_SetStrLen(Len);
					_Data = NewStr;
				}
				break;
			default:
				{
					_Data.f_Clear();
				}
				break;
			}
		}
	};
}
