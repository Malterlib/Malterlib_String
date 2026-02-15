// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <typename tf_CValue>
	CMStrPreserve::CMStrPreserve(tf_CValue &&_Other)
		: CMStrDeprecated(fg_Forward<tf_CValue>(_Other))
	{
	}

	template <typename tf_CValue>
	CMStrPreserve &CMStrPreserve::operator =(tf_CValue &&_Other)
	{
		(CMStrDeprecated &)*this = fg_Forward<tf_CValue>(_Other);
		return *this;
	}
}

namespace NMib::NStream
{
	template <typename t_CStream>
	class TCBinaryStreamTypeReference<t_CStream, NStr::CMStrPreserve>
	{
	public:
		static void fs_Feed(t_CStream &_Stream, NStr::CMStrPreserve const &_Data)
		{
			uint64 Len = _Data.f_GetLen();
			uint64 LenStream = Len;
			NStr::EStrType StrType = _Data.m_OriginalType;
			fg_StrEncodeLenType(LenStream, _Stream.f_LengthSize(), StrType);
			fg_FeedLenToStream(_Stream, LenStream);
			uint32 Type = _Data.m_MixedType;
			_Stream.f_Feed(Type);
			switch (Type)
			{
			case NStr::EMStr_Type_CStr:
				{
					switch (StrType)
					{
					case NStr::EStrType_Ansi:
					case NStr::EStrType_Unicode:
						{
							NStr::CStr Unicode;
							for (auto iUnicode = _Data.f_GetUnicodeIterator(); iUnicode; ++iUnicode)
								Unicode.f_AddChar(*iUnicode);

							mint UnicodeLen = Unicode.f_GetLen();
							if (UnicodeLen != 0)
								_Stream.f_FeedBytes(Unicode.f_GetStr(), UnicodeLen * sizeof(ch8));
						}
						break;
					case NStr::EStrType_UTF:
					default:
						{
							if (Len != 0)
								_Stream.f_FeedBytes(_Data.f_GetStr(), Len * sizeof(ch8));
						}
						break;
					}
				}
				break;
			case NStr::EMStr_Type_CWStr:
				{
					switch (StrType)
					{
					case NStr::EStrType_Unicode:
						{
							NStr::CWStr String = _Data;

							NStr::CWStr Unicode;
							for (auto iUnicode = String.f_GetUnicodeIterator(); iUnicode; ++iUnicode)
								Unicode.f_AddChar(*iUnicode);

							mint UnicodeLen = Unicode.f_GetLen();
							if (UnicodeLen != 0)
								_Stream.f_FeedBytes(Unicode.f_GetStr(), UnicodeLen * sizeof(ch16));
						}
						break;
					case NStr::EStrType_UTF:
					default:
						{
							NStr::CWStr String = _Data;
							mint StringLen = String.f_GetLen();
							if (StringLen != 0)
								_Stream.f_FeedBytes(String.f_GetStr(), StringLen * sizeof(ch16));
						}
						break;
					}
				}
				break;
			case NStr::EMStr_Type_CUStr:
				{
					switch (StrType)
					{
					case NStr::EStrType_Unicode:
					default:
						{
							NStr::CUStr String = _Data;
							mint StringLen = String.f_GetLen();
							if (StringLen != 0)
								_Stream.f_FeedBytes(String.f_GetStr(), StringLen * sizeof(ch32));
						}
						break;
					}
				}
				break;
			}
		}

		static constexpr void fs_Consume(t_CStream &_Stream, NStr::CMStrPreserve &_Data)
		{
			uint64 Len;
			fg_ConsumeLenFromStream(_Stream, Len);
			NStr::EStrType StrType = NStr::EStrType_Ansi;
			fg_StrDecodeLenType(Len, _Stream.f_LengthSize(), StrType);
			fg_CheckLengthLimit(_Stream, Len);
			uint32 Type;
			_Stream.f_Consume(Type);
			_Data.f_Clear();

			_Data.m_MixedType = (NStr::EMStr_Type)Type;
			_Data.m_OriginalType = StrType;

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
						NSys::NStr::fg_SystemDecodeAnsiStr(NewStr.f_GetStr(), _Data);
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
