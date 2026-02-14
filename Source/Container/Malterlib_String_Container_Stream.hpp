// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

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
	class TCBinaryStreamTypeReference<t_CStream, NStr::TCStr<t_TCStrTraitsIn> >
	{
	public:
		static constexpr void fs_Feed(t_CStream &_Stream, NStr::TCStr<t_TCStrTraitsIn> const &_Data)
		{
			uint64 Len = _Data.f_GetLen();
			uint64 LenStream = Len;
			fg_StrEncodeLenType(LenStream, _Stream.f_LengthSize(), _Data.mc_Type);
			fg_FeedLenToStream(_Stream, LenStream);
			if (Len != 0)
				_Stream.f_FeedBytes(_Data.f_GetStr(), Len * sizeof(typename NStr::TCStr<t_TCStrTraitsIn>::CChar));
		}

		static constexpr void fs_Consume(t_CStream &_Stream, NStr::TCStr<t_TCStrTraitsIn> &_Data)
		{
			uint64 Len;
			fg_ConsumeLenFromStream(_Stream, Len);
			NStr::EStrType Type = NStr::EStrType_Ansi;
			fg_StrDecodeLenType(Len, _Stream.f_LengthSize(), Type);
			fg_CheckLengthLimit(_Stream, Len);

			//NStr::TCStr<t_TCStrTraitsIn>

			typename NStr::TCStr<t_TCStrTraitsIn>::CChar *pStr = _Data.f_GetStr(Len + 1);
			auto Cleanup = g_OnScopeExit / [&]
				{
					_Data.f_Clear();
				}
			;

			if (Len != 0)
				_Stream.f_ConsumeBytes(pStr, Len * sizeof(typename NStr::TCStr<t_TCStrTraitsIn>::CChar));
			Cleanup.f_Clear();
			pStr[Len] = 0;
			_Data.f_SetStrLen(Len);
			_Data.f_ConvertFromType(Type);
		}
	};
}
