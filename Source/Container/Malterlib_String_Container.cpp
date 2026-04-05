// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>

namespace NMib::NStr
{
	CStr fg_ReadTextStream(NStream::CBinaryStream &_Stream, bool _bAssumeUTF8)
	{
		CMibFilePos Pos = _Stream.f_GetPosition();
		CMibFilePos Size = _Stream.f_GetLength() - Pos;

		uint8 Signature[4];

		_Stream.f_ConsumeBytes(Signature, fg_Min(Size, 4));

		// 00 00 FE FF  UTF-32, big-endian
		if (Size >= 4 && Signature[0] == 0x00 && Signature[1] == 0x00 && Signature[2] == 0xFE && Signature[3] == 0xFF)
		{
			// UTF-32 encoding
			_Stream.f_SetPosition(Pos + 4);

			umint StrSize = ((Size-4) >> 2);
			CUStr NewStr;
			ch32 *pStr = NewStr.f_GetStr(StrSize + 1);
			_Stream.f_ConsumeBytes(pStr, StrSize << 2);
			pStr[StrSize] = 0; // Null terminate
			NewStr.f_SetStrLen(StrSize);

#ifdef DMibPLittleEndian
			ch32 *pStrTemp = NewStr.f_GetStrUniqueWritable();
			while (*pStrTemp)
			{
				*pStrTemp = fg_ByteSwap(*pStrTemp);
				++pStrTemp;
			}
#endif
			return NewStr;
		}
		// FF FE 00 00	UTF-32, little-endian
		else if (Size >= 4 && Signature[0] == 0xFF && Signature[1] == 0xFE && Signature[2] == 0x00 && Signature[3] == 0x00)
		{
			// UTF-32 encoding
			_Stream.f_SetPosition(Pos + 4);

			umint StrSize = ((Size-4) >> 2);
			CUStr NewStr;
			ch32 *pStr = NewStr.f_GetStr(StrSize + 1);
			_Stream.f_ConsumeBytes(pStr, StrSize << 2);
			pStr[StrSize] = 0; // Null terminate
			NewStr.f_SetStrLen(StrSize);

#ifndef DMibPLittleEndian
			ch32 *pStrTemp = NewStr.f_GetStrUniqueWritable();
			while (*pStrTemp)
			{
				*pStrTemp = fg_ByteSwap(*pStrTemp);
				++pStrTemp;
			}
#endif
			return NewStr;
		}
		// EF BB BF	UTF-8
		else if (Size >= 3 && Signature[0] == 0xEF && Signature[1] == 0xBB && Signature[2] == 0xBF)
		{
			// UTF-8 encoding
			_Stream.f_SetPosition(Pos + 3);
			umint StrSize = Size-3;
			CStr NewStr;
			ch8 *pStr = NewStr.f_GetStr(StrSize + 1);
			_Stream.f_ConsumeBytes(pStr, StrSize);
			pStr[StrSize] = 0; // Null terminate
			NewStr.f_SetStrLen(StrSize);
			return NewStr;
		}
		// FE FF		UTF-16, big-endian
		else if (Size >= 2 && ((Signature[0] == 0xFF && Signature[1] == 0xFE) || (Signature[0] == 0xFE && Signature[1] == 0xFF)))
		{
			// UTF-16 encoding
			_Stream.f_SetPosition(Pos + 2);

			umint StrSize = ((Size-2) >> 1);
			CWStr NewStr;
			ch16 *pStr = NewStr.f_GetStr(StrSize + 1);
			_Stream.f_ConsumeBytes(pStr, StrSize << 1);
			pStr[StrSize] = 0; // Null terminate
			NewStr.f_SetStrLen(StrSize);
			pStr = NewStr.f_GetStrUniqueWritable();

#ifdef DMibPLittleEndian
			if ((Signature[0] == 0xFE && Signature[1] == 0xFF))
			{
				ch16 *pStrTemp = pStr;
				while (*pStrTemp)
				{
					*pStrTemp = fg_ByteSwap(*pStrTemp);
					++pStrTemp;
				}
			}
#else
			if ((Signature[0] == 0xFF && Signature[1] == 0xFE))
			{
				ch16 *pStrTemp = pStr;
				while (*pStrTemp)
				{
					*pStrTemp = fg_ByteSwap(*pStrTemp);
					++pStrTemp;
				}
			}
#endif
			return NewStr;
		}
		else if (_bAssumeUTF8)
		{
			_Stream.f_SetPosition(Pos);

			umint StrSize = Size;
			CStr NewStr;
			ch8 *pStr = NewStr.f_GetStr(StrSize + 1);
			_Stream.f_ConsumeBytes(pStr, StrSize);
			pStr[StrSize] = 0; // Null terminate
			NewStr.f_SetStrLen(StrSize);
			return NewStr;
		}
		else
		{
			// Ansi encoding
			_Stream.f_SetPosition(Pos);

			CAnsiStr NewStr;
			ch8 *pStr = NewStr.f_GetStr(Size + 1);
			_Stream.f_ConsumeBytes(pStr, Size);
			pStr[Size] = 0; // Null terminate
			NewStr.f_SetStrLen(Size);
			return NewStr;
		}
	}
}
