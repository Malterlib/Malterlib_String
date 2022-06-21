// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include "../../Core/Source/Malterlib_Core_PlatformInterface.h"
#include <Mib/String/UnicodeConversion>
#include <Mib/String/Algorithm>
#include <Mib/Core/EnableIf>

namespace NMib::NStr
{
	template <typename t_CChar, CStrTypeUnderlying t_Type, typename t_CParams>
	class TCStrTraits
	{
	public:
		typedef t_CChar CChar;
		typedef t_CParams CParams;
		typedef typename t_CParams::CAllocator CAllocator;
		static EStrType const mc_Type = (EStrType)t_Type;

		template <typename t_CData>
			static inline_small bool fs_CharIsNumber(const t_CData _Character)
		{
			return fg_CharIsNumber(_Character);
		}

		template <typename t_CData>
			static inline_small t_CData fs_CharUpperCase(t_CData _Character)
		{
			return fg_CharUpperCase(_Character);
		}

		template <typename t_CData>
			static inline_small t_CData fs_CharLowerCase(t_CData _Character)
		{
			return fg_CharLowerCase(_Character);
		}

		template <typename t_CData, typename t_CReturn>
			static inline_small t_CReturn fs_StrToIntBase10ParseNoSign(const t_CData *&_pStr, t_CReturn _FailValue)
		{
			return fg_StrToIntBase10ParseNoSign(_pStr, _FailValue);
		}

		template <typename t_CData, typename t_CReturn>
			static inline_small t_CReturn fs_StrToIntBase10NoSign(const t_CData *_pStr, t_CReturn _FailValue)
		{
			return fg_StrToIntBase10NoSign(_pStr, _FailValue);
		}

		template <typename t_CData, typename t_CReturn>
			static inline_small t_CReturn fs_StrToIntBase10(const t_CData *_pStr, t_CReturn _FailValue)
		{
			return fg_StrToIntBase10(_pStr, _FailValue);
		}

		template <typename t_CData, typename t_CReturn>
		static inline_small t_CReturn fs_StrToIntParse(const t_CData *&_pStr, t_CReturn _FailValue, const t_CData *_pStrTerminators = nullptr, bool _bDontFail = false, int32 _ParseMode = EStrToIntParseMode_Base10)
		{
			return fg_StrToIntParse(_pStr, _FailValue, _pStrTerminators, _bDontFail, _ParseMode);
		}

		template <typename t_CData, typename t_CReturn>
		static inline_small t_CReturn fs_StrToIntParseHex(const t_CData *&_pStr, t_CReturn _FailValue)
		{
			return fg_StrToIntParseHex(_pStr, _FailValue, _FailValue);
		}

		template<typename t_CData, typename t_CReturn>
		static inline_small t_CReturn fs_StrToIntParseHex(const t_CData *&_pStr, t_CReturn _FailValue, t_CData _Terminator)
		{
			return fg_StrToIntParseHex(_pStr, _FailValue);
		}

		template <typename t_CData>
			static inline_small mint fs_StrLen(const t_CData *_pStr)
		{
			return fg_StrLen(_pStr);
		}

		template <typename t_CData1, typename t_CData2>
			static inline_small t_CData1 *fs_StrUpperCase(t_CData1 *_pDest, const t_CData2 *_pSource, aint _SourceLen)
		{
			DMibFastCheck((sizeof(CChar) > 1 || NTraits::TCIsSame<CChar, ch8>::mc_Value && mc_Type == EStrType_UTF));
			return fg_StrUpperCase(_pDest, _pSource, _SourceLen);
		}

		template <typename t_CData1, typename t_CData2>
			static inline_small t_CData1 *fs_StrLowerCase(t_CData1 *_pDest, const t_CData2 *_pSource, aint _SourceLen)
		{
			DMibFastCheck((sizeof(CChar) > 1 || NTraits::TCIsSame<CChar, ch8>::mc_Value && mc_Type == EStrType_UTF));
			return fg_StrLowerCase(_pDest, _pSource, _SourceLen);
		}

		template <typename t_CData, typename t_CReturn>
			static inline_small t_CReturn fs_StrToInt(const t_CData *_pStr, t_CReturn _FailValue, const t_CData *_pStrTerminators = nullptr)
		{
			return fg_StrToInt(_pStr, _FailValue, _pStrTerminators);
		}

		template <typename t_CData, typename t_CReturn>
			static inline_small t_CReturn fs_StrToIntExact(const t_CData *_pStr, t_CReturn _FailValue, const t_CData *_pStrTerminators = nullptr)
		{
			return fg_StrToIntExact(_pStr, _FailValue, _pStrTerminators);
		}

		template <typename t_CData, typename t_CReturn>
			static inline_small t_CReturn fs_StrToFloat(const t_CData *_pStr, t_CReturn _FailValue, const t_CData *_pStrTerminators = nullptr)
		{
			return fg_StrToFloat(_pStr, _FailValue, _pStrTerminators);
		}

		template <typename t_CData, typename t_CReturn>
			static inline_small t_CReturn fs_StrToFloatExact(const t_CData *_pStr, t_CReturn _FailValue, const t_CData *_pStrTerminators = nullptr)
		{
			return fg_StrToFloatExact(_pStr, _FailValue, _pStrTerminators);
		}

		template <typename t_CData, typename t_CReturn>
			static inline_small t_CReturn fs_StrToFloatParse(const t_CData *_pStr, t_CReturn _FailValue, const t_CData *_pStrTerminators, bool _bDontFail = false)
		{
			return fg_StrToFloatParse(_pStr, _FailValue, _pStrTerminators, _bDontFail);
		}
	};


	/*¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯*\
	|	Template:			Short_desscription										|
	|																				|
	|	Parameters:																	|
	|		t_CTCStrTraits:			description										|
	|																				|
	|	Comments:			Longer_description_not_mandatory						|
	\*_____________________________________________________________________________*/

	class CStrFormatBinaryWrapper
	{
		const void *m_pData;
		mint m_Size;
	public:
		template <typename t_CType>
		CStrFormatBinaryWrapper(t_CType const &_Data)
		{
			m_pData = (const void *)&_Data;
			m_Size = sizeof(_Data);
		}

		CStrFormatBinaryWrapper(void const *_pData, mint _Size)
		{
			m_pData = _pData;
			m_Size = _Size;
		}
		void const *f_GetArray() const
		{
			return m_pData;
		}
		mint f_GetSize() const
		{
			return m_Size;
		}
	};

	class CStrFormatBinaryWrapperUntyped : public CStrFormatBinaryWrapper
	{
	public:
		template <typename t_CType>
		CStrFormatBinaryWrapperUntyped(t_CType &_Data)
			: CStrFormatBinaryWrapper(_Data)
		{
		}
	};

	template <typename t_CData>
	CStrFormatBinaryWrapper fg_FormatAsBinary(t_CData const &_Data)
	{
		return CStrFormatBinaryWrapper(_Data);
	}


	template <typename t_CFormatter, typename t_CData>
	class TCStringFormatter;

	template <typename t_CFormatter, typename t_CToFormat, bool t_bByReference>
	class TCStrFormatType_Inline;

	namespace NPrivate
	{
		DMibTypeTraitsImplement_MemberTraits(f_GetStringFormatType);
		DMibTypeTraitsImplement_MemberTraits(f_CreateStringFormatter);
		DMibTypeTraitsImplement_MemberTraits(f_Format);
		DMibTypeTraitsImplement_MemberTraits(f_FormatParseOption);

		template <typename t_CData>
		struct TCWithoutByValue
		{
			using CType = t_CData;
		};

		template <typename t_CData>
		struct TCWithoutByValue<TCByValue<t_CData>>
		{
			using CType = t_CData;
		};

		template
		<
			typename t_CFormatter
			, typename t_CData
			, bool t_bHasInline = TCHasMember_f_GetStringFormatType<t_CData>::mc_Value && NPrivate::TCHasMember_f_CreateStringFormatter<t_CData>::mc_Value
			, bool t_bHasInlineFormatter = TCHasMember_f_Format<typename TCWithoutByValue<t_CData>::CType>::mc_Value
		>
		class TCStringFormatterHelper;

		template <typename t_CFormatter, typename t_CData>
		class TCStringFormatterHelper<t_CFormatter, t_CData, false, true>
		{
			static t_CFormatter &fs_GetFormatter();
			static t_CData &fs_GetData();
		public:

			typedef TCStrFormatType_Inline<t_CFormatter, t_CData, true> CFormatType;
			template <typename tf_CData>
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, tf_CData const &_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

		template <typename t_CFormatter, typename t_CData>
		class TCStringFormatterHelper<t_CFormatter, TCByValue<t_CData>, false, true>
		{
			static t_CFormatter &fs_GetFormatter();
			static t_CData &fs_GetData();
		public:

			typedef TCStrFormatType_Inline<t_CFormatter, t_CData, false> CFormatType;
			template <typename tf_CData>
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, TCByValue<tf_CData> const &_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(*_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

		template <typename t_CFormatter, typename t_CData>
		class TCStringFormatterHelper<t_CFormatter, t_CData, true, false>
		{
			static t_CFormatter &fs_GetFormatter();
			static t_CData &fs_GetData();
		public:

			typedef decltype(fs_GetData().f_GetStringFormatType(fs_GetFormatter())) CFormatType;

			static auto fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data) -> decltype(_Data.f_CreateStringFormatter(_Formatter))
			{
				return _Data.f_CreateStringFormatter(_Formatter);
			}
		};

		template <typename t_CFormatter, typename t_CData>
		class TCStringFormatterHelper<t_CFormatter, t_CData, false, false>
		{
			static t_CFormatter &fs_GetFormatter();
			static t_CData &fs_GetData();
		public:

			typedef typename TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>::CFormatType CFormatType;

			static auto fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data) -> decltype(TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>::fs_CreateFormat(_Formatter, _Data))
			{
				return TCStringFormatter<t_CFormatter, CStrFormatBinaryWrapperUntyped>::fs_CreateFormat(_Formatter, _Data);
			}

		};

	}

	template <typename t_CFormatter, typename t_CData>
	class TCStringFormatter
		: public NPrivate::TCStringFormatterHelper
		<
			t_CFormatter
			, t_CData
		>
	{
	};

	namespace NPrivate
	{
		template <typename t_CFormatter>
		class TCStringFormatterEnum
		{
		public:
			typedef TCStrFormatType_Int<t_CFormatter, uint32> CFormatType;
			template <typename tf_CData>
			static inline_large typename CFormatType::CStrFormatTypeClassifier fs_CreateFormat(t_CFormatter &_Formatter, tf_CData const &_Data)
			{
				_Formatter.template f_Alloc<CFormatType>(_Data);
				return typename CFormatType::CStrFormatTypeClassifier();
			}
		};

		template <typename t_CFormatter, typename t_CData, bool t_bIsEnum = NMib::NTraits::TCIsEnum<t_CData>::mc_Value>
		struct TCDetermineStringFormatter
		{
			typedef TCStringFormatter<t_CFormatter, t_CData> CType;
		};

		template <typename t_CFormatter, typename t_CData>
		struct TCDetermineStringFormatter<t_CFormatter, t_CData, true>
		{
			typedef TCStringFormatterEnum<t_CFormatter> CType;
		};
	}

	template <typename t_CFormatter, typename t_CData>
	struct TCStringFormatterAll
	{
		typedef typename NPrivate::TCDetermineStringFormatter<t_CFormatter, t_CData>::CType CStringFormatter;
		typedef typename CStringFormatter::CFormatType CFormatType;

		static auto fs_CreateFormat(t_CFormatter &_Formatter, t_CData const &_Data) -> decltype(CStringFormatter::fs_CreateFormat(_Formatter, _Data))
		{
			return CStringFormatter::fs_CreateFormat(_Formatter, _Data);
		}
	};

	namespace NPrivate
	{
		template <typename t_CFormatter, typename t_CData>
		struct TCDetermineStringFormatterReturnType
		{
			typedef decltype(TCStringFormatterAll<t_CFormatter, t_CData>::fs_CreateFormat(fg_GetType<t_CFormatter &>(), fg_GetType<t_CData const &>())) CType;
		};
	}

	template <typename t_CFormatter, typename t_CData>
	inline_small typename NPrivate::TCDetermineStringFormatterReturnType<t_CFormatter, t_CData>::CType fg_CreateStringFormatter(t_CFormatter &_Formatter, t_CData const &_Data)
	{
		return TCStringFormatterAll<t_CFormatter, t_CData>::fs_CreateFormat(_Formatter, _Data);
	}

	template <typename t_CFormatter, typename t_CData>
	inline_small typename TCStringFormatterAll<t_CFormatter, t_CData>::CFormatType fg_GetStringFormatType(t_CFormatter &_Formatter, t_CData const &_Data);


	template <typename t_CTCStrTraits>
	class TCStr;

	template <typename t_CTCStrTraits>
	class TCFormat
	{
	public:

		typedef typename t_CTCStrTraits::CStrTraits::CChar CChar;
		typedef typename t_CTCStrTraits::CStrTraits::CAllocator CAllocator;
		typedef TCStrAggregate<t_CTCStrTraits> CStrAggregate;
		typedef TCStr<t_CTCStrTraits> CStr;
		typedef t_CTCStrTraits CTStrTraits;
		static constexpr EStrType mc_Type = t_CTCStrTraits::CStrTraits::mc_Type;

		typedef TICStrFormatType<TCFormat> CFomatArgType;

		void f_MoveFormats(TCFormat &&_Other)
		{
			TICStrFormatType<TCFormat> **pFormatList = _Other.fp_GetFormatList();

			for (uaint i = 0; i < _Other.m_nFormats; ++i)
			{
				TICStrFormatType<TCFormat> *pFormat = (TICStrFormatType<TCFormat> *)((mint)pFormatList[i] & (~((mint)0x3)));
				pFormat->f_Move(*this);
			}
		}

		TCFormat(TCFormat &&_Other)
		{
			m_pFormatStr = _Other.m_pFormatStr;
			m_pFormats = m_plFormats;
			m_nFormats = 0;
			m_iCurrentAlloc = 0;

			f_MoveFormats(fg_Move(_Other));
		}

		TCFormat &operator=(TCFormat &&_Other)
		{
			f_ClearFormats();

			m_pFormatStr = _Other.m_pFormatStr;
			f_MoveFormats(fg_Move(_Other));

			return *this;
		}

		void fp_AddFormat(TICStrFormatType<TCFormat> *_pFormat, mint _Flags)
		{
			TICStrFormatType<TCFormat> *pFormat = (TICStrFormatType<TCFormat> *)((mint)_pFormat | _Flags);
			if (m_nFormats < EStaticFormats)
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

		inline_medium void *f_AllocSpace(mint _Size, mint &_Flags)
		{
			mint nNeeded = _Size;
			_Flags = 0;

			void *pSpace = fp_AllocSpace(nNeeded);
			if (!pSpace)
			{
				pSpace = t_CTCStrTraits::CStrTraits::CAllocator::f_Alloc(nNeeded);
				_Flags = 1;
			}

			return pSpace;
		}

		template <typename tf_CType, typename ...tfp_CParams>
		inline_medium tf_CType *f_Alloc(tfp_CParams && ...p_Params)
		{
			mint Flags;
			void *pSpace = f_AllocSpace(sizeof(tf_CType), Flags);
			tf_CType *pNew = new(pSpace) tf_CType(fg_Forward<tfp_CParams>(p_Params)...);
			Flags |= (tf_CType::mc_bNeedDelete ? 2 : 0);
			fp_AddFormat(pNew, Flags);
			return pNew;
		}

		inline_medium const TICStrFormatType<TCFormat> *f_GetArg(aint _iArgument) const
		{
			if (_iArgument < 0)
				_iArgument = m_iCurrentArgument++;

			if (_iArgument >= (aint)m_nFormats)
				return nullptr;

			return fp_GetFormatEntry(_iArgument);
		}

		mint f_GetNumArgs() const
		{
			return m_nFormats;
		}

		explicit inline_medium TCFormat(const CChar *_pFormatStr)
		{
			m_pFormatStr = _pFormatStr;
			m_pFormats = m_plFormats;;
			m_nFormats = 0;
			m_iCurrentAlloc = 0;
		}

		template <typename t_CTCStrTraits2>
		explicit inline_medium TCFormat(TCStrAggregate<t_CTCStrTraits2> const &_Format)
		{
			m_pFormatStr = _Format;
			m_pFormats = m_plFormats;
			m_nFormats = 0;
			m_iCurrentAlloc = 0;
		}

		bool f_IsEmpty() const
		{
			return *m_pFormatStr == 0;
		}

		void f_ClearFormats()
		{
			TICStrFormatType<TCFormat> **pFormatList = fp_GetFormatList();

			for (uaint i = 0; i < m_nFormats; ++i)
			{
				mint Flags = (mint)pFormatList[i] & 0x3;
				TICStrFormatType<TCFormat> *pFormat = (TICStrFormatType<TCFormat> *)((mint)pFormatList[i] & (~((mint)0x3)));

				if (Flags & 1)
				{
					mint Size = pFormat->f_Delete();
					t_CTCStrTraits::CStrTraits::CAllocator::f_Free(pFormat, Size);
				}
				else if (Flags & 2)
					pFormat->f_Delete();
			}

			m_pFormats = m_plFormats;
			m_nFormats = 0;
			m_iCurrentAlloc = 0;
		}

		~TCFormat()
		{
			f_ClearFormats();
		}

		inline_small void f_FormatToStr(TCStrAggregate<t_CTCStrTraits> &_Str) const
		{
			m_iCurrentArgument = 0;
			fp_FormatArgList<0>(*this, m_pFormatStr, _Str);
		}

		inline_small void f_FormatToStrConcat(TCStrAggregate<t_CTCStrTraits> &_Str) const
		{
			m_iCurrentArgument = 0;
			fp_FormatArgList<1>(*this, m_pFormatStr, _Str);
		}

		inline_small void f_FormatArgumentsToStr(TCStrAggregate<t_CTCStrTraits> &_Str) const
		{
			m_iCurrentArgument = 0;
			fp_FormatArguments<0>(*this, _Str);
		}

		inline_small void f_FormatArgumentsToStrConcat(TCStrAggregate<t_CTCStrTraits> &_Str) const
		{
			m_iCurrentArgument = 0;
			fp_FormatArguments<1>(*this, _Str);
		}

		void f_SetFormatStr(const CChar *_pFormatStr)
		{
			m_pFormatStr = _pFormatStr;
		}
		TCStr<t_CTCStrTraits> f_GetStr() const;
		TCStr<t_CTCStrTraits> operator ^ (mint _nCopies) const;

		template <typename tf_CStr>
		void f_Format(tf_CStr &o_FormatInto) const
		{
			o_FormatInto += *this;
		}

		template <typename t_CType>
		inline_small TCFormat &operator << (t_CType const &_Type) &
			requires
			( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
				!TCHasFormatClass<t_CType, EStrTypeClass_Untyped>::mc_Value
			)
		{
			TCStringFormatterAll<TCFormat, t_CType>::fs_CreateFormat(*this, _Type);
			return *this;
		}

		template <typename t_CType>
		inline_small TCFormat &&operator << (t_CType const &_Type) &&
			requires
			( // This type has no formatter defined for it. If you want to use the binary formatter use fg_FormatAsBinary wrapper.
				!TCHasFormatClass<t_CType, EStrTypeClass_Untyped>::mc_Value
			)
		{
			TCStringFormatterAll<TCFormat, t_CType>::fs_CreateFormat(*this, _Type);
			return fg_Move(*this);
		}

		template <typename t_CType>
		static auto fs_GetFormatClassifier(t_CType const &_Type) -> decltype(TCStringFormatterAll<TCFormat, t_CType>::fs_CreateFormat(*((TCFormat *)0), _Type)); // Only used compile time

		template <bool t_bConcat>
		static void fp_FormatArguments(const TCFormat &_Format, TCStrAggregate<t_CTCStrTraits> &_ToStr)
		{
			aint CurrentStrLen;
			aint MaxLen;
			if constexpr (t_bConcat)
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

			mint nFormats = _Format.m_nFormats;
			for (mint i = 0; i < nFormats; ++i)
			{
				const TICStrFormatType<TCFormat> *pFormatVar = _Format.fp_GetFormatEntry(i);
				pFormatVar->f_AddToStr(_ToStr, CurrentStrLen, nullptr, _Format);
			}

			_ToStr.f_SetStrLen(CurrentStrLen);
		}

		template <bool t_bConcat>
		static void fp_FormatArgList(const TCFormat &_Format, const CChar *_pFormat, TCStrAggregate<t_CTCStrTraits> &_ToStr)
		{
			aint CurrentStrLen;
			aint MaxLen;
			if constexpr (t_bConcat)
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
							_ToStr.fp_AddCharLengthAware(CurrentStrLen, *pFormat);
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
										_ToStr.fp_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
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
										_ToStr.fp_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
									goto EndArgSearch;
								}
								else if (Variable < 0)
								{
									const ch8 *pTmp = "###format var out of range###";
									while (*pTmp)
										_ToStr.fp_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
									goto EndArgSearch;
								}
							}
							else if (*pFormat == '\n')
							{
								const ch8 *pTmp = DMibNewLine;
								while (*pTmp)
									_ToStr.fp_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
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
										_ToStr.fp_AddCharLengthAware(CurrentStrLen, (CChar)(*(pTmp++)));
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

	private:
		enum
		{
			EStaticFormats = 16,
			EStaticSpace = EStaticFormats*4
		};

		uaint m_nFormats;
		mutable aint m_iCurrentArgument;
		TICStrFormatType<TCFormat> **m_pFormats;
		const CChar *m_pFormatStr;

		TICStrFormatType<TCFormat> *m_plFormats[EStaticFormats];
		NContainer::TCVector<TICStrFormatType<TCFormat> *, CAllocator> m_lFormats;

		inline_small TICStrFormatType<TCFormat> **fp_GetFormatList()
		{
			return m_pFormats;
		}

		inline_small TICStrFormatType<TCFormat> const *fp_GetFormatEntry(aint _iEntry) const
		{
			return (TICStrFormatType<TCFormat> const *)((mint)m_pFormats[_iEntry] & (~((mint)0x3)));
		}

		aint m_AllocSpace[EStaticSpace];
		int m_iCurrentAlloc;

		void *fp_AllocSpace(int _Bytes)
		{
			mint Needed = (_Bytes + sizeof(aint) - 1) / sizeof(aint);
			if (m_iCurrentAlloc + Needed > EStaticSpace)
				return nullptr;

			void *pSpace = (void *)(m_AllocSpace + m_iCurrentAlloc);

			m_iCurrentAlloc += Needed;

			return pSpace;
		}

		TCFormat(const TCFormat &_Other) = delete;
		TCFormat& operator=(TCFormat const& _Other) = delete;


	};

#ifdef DMibDebuggerHelpers
	template <int t_Type>
	struct TCStrAggregateTypeHelper
	{
	};
#endif

	template <typename t_CString>
	struct TCStringAppender;

	template <typename t_CTCStrTraits>
	class TCStrAggregate : public t_CTCStrTraits::CImp
	{
	public:
		typedef t_CTCStrTraits CTraits;
		typedef typename t_CTCStrTraits::CStrTraits CStrTraits;
		typedef typename t_CTCStrTraits::CStrTraits::CChar CChar;
		typedef typename NTraits::TCUnsigned<typename t_CTCStrTraits::CStrTraits::CChar>::CType CUnsignedChar;
		typedef typename t_CTCStrTraits::CImp CImp;
		typedef TCStrAggregate CAggregate;
		typedef typename CStrTraits::CAllocator CAllocator;
		typedef CChar CMaxChar;
		static constexpr EStrType mc_Type = t_CTCStrTraits::CStrTraits::mc_Type;
		using CDynamicStr = TCStr<t_CTCStrTraits>;

#ifdef DMibDebuggerHelpers
		static TCStrAggregateTypeHelper<t_CTCStrTraits::CStrTraits::mc_Type> fs_TypeDebugHelper();
#endif

		static const CChar ms_FormatStr[];
		static const CChar ms_FormatConcatStr[];

		static_assert(sizeof(CChar) != 1 || mc_Type == EStrType_Ansi || mc_Type == EStrType_Unicode || mc_Type == EStrType_UTF);
		static_assert(sizeof(CChar) != 2 || mc_Type == EStrType_Unicode || mc_Type == EStrType_UTF);
		static_assert(sizeof(CChar) < 4 || mc_Type == EStrType_Unicode);

		typedef typename TCChooseType
			<
				sizeof(CChar) == 1
				, typename TCChooseType
				<
					mc_Type == EStrType_UTF
					, CStrIteratorUTF8
					, TCStrIteratorUnicode<CChar>
				>::CType
				, typename TCChooseType
				<
					sizeof(CChar) == 2
					, typename TCChooseType
					<
						mc_Type == EStrType_UTF
						, CStrIteratorUTF16
						, TCStrIteratorUnicode<CChar>
					>::CType
					, TCStrIteratorUnicode<CChar>
				>::CType
			>::CType CUnicodeIterator
		;

	private:
		enum
		{
			EDebug_CharSize = sizeof(CChar)
			, EDebug_Type = t_CTCStrTraits::CStrTraits::mc_Type
		};

		typedef typename TCChooseType
			<
				NTraits::TCIsSame<typename CStrTraits::CAllocator, NMemory::CAllocator_NonTrackedHeap>::mc_Value
				, CStrNonTracked
				, CStr
			>::CType CTempStr
		;

	public:

		constexpr TCStrAggregate(EAggregateInitialization _Init)
			: t_CTCStrTraits::CImp{_Init}
		{
#ifdef DMibDebuggerHelpers
			static_assert(TCInstantiateValue<&fs_TypeDebugHelper>::mc_Value);
#endif
		}
		TCStrAggregate()
		{
#ifdef DMibDebuggerHelpers
			static_assert(TCInstantiateValue<&fs_TypeDebugHelper>::mc_Value);
#endif
		}
		TCStrAggregate & operator = (TCStrAggregate const &_From) = delete;
		TCStrAggregate(TCStrAggregate const &_From) = delete;
		TCStrAggregate & operator = (TCStrAggregate &&_From) = delete;
		TCStrAggregate(TCStrAggregate &&_From) = delete;

		CUnicodeIterator f_GetUnicodeIterator() const
			requires (mc_Type != EStrType_Ansi)
		{
			return CUnicodeIterator(*this);
		}

		inline_small void f_Destroy()
		{
			CImp::f_Destroy();
		}
		inline_small void f_Construct()
		{
#ifdef DMibDebuggerHelpers
			static_assert(TCInstantiateValue<&fs_TypeDebugHelper>::mc_Value);
#endif
			CImp::f_Construct();
		}

		inline_small void f_Construct(const TCStrAggregate &_Src)
		{
#ifdef DMibDebuggerHelpers
			static_assert(TCInstantiateValue<&fs_TypeDebugHelper>::mc_Value);
#endif
			CImp::f_Construct(_Src);
		}

		inline_small void f_Construct(TCStrAggregate &&_Src)
		{
#ifdef DMibDebuggerHelpers
			static_assert(TCInstantiateValue<&fs_TypeDebugHelper>::mc_Value);
#endif
			CImp::f_Construct(fg_Move(_Src));
		}

		template <typename ...tfp_CParams>
		inline_small void f_Construct(tfp_CParams &&...p_Params)
		{
#ifdef DMibDebuggerHelpers
			static_assert(TCInstantiateValue<&fs_TypeDebugHelper>::mc_Value);
#endif
			CImp::f_Construct(fg_Forward<tfp_CParams>(p_Params)...);
		}

		inline_small void f_Assign(const TCStrAggregate &_Src)
		{
			CImp::f_Assign(_Src);
		}

		inline_small void f_Assign(TCStrAggregate &&_Src)
		{
			CImp::f_Assign(fg_Move(_Src));
		}

		inline_small void f_SetModified()
		{
			CImp::f_SetStrLen(-1);
		}

		inline_small const CChar *f_GetStr() const
		{
			return CImp::f_GetStr();
		}

		inline_small CChar *f_GetStrUniqueWritable()
		{
			CImp::f_MakeUnique();
			return CImp::f_GetStrWritable();
		}

		inline_small operator const CChar * () const
		{
			return CImp::f_GetStr();
		}

		inline_small explicit operator bool () const
		{
			return !f_IsEmpty();
		}

		inline_small bool f_IsEmpty () const
		{
			return (*CImp::f_GetStr()) == 0;
		}

		inline_small CChar &operator [] (aint _Index)
		{
#ifdef DMibDebug
			// Only do range checking in debug because f_GetStrLen might be a fg_StrLen
			if (_Index < 0)
				DMibError("Range check error");
#endif
			CImp::f_MakeUnique();

			int MaxLen = CImp::f_CreateWritableBuffer(_Index + 1, false);
			if (_Index >= MaxLen)
			{
				static CChar SafeWrite;
				return SafeWrite;
			}

			return CImp::f_GetStrWritable()[_Index];
		}

		inline_small const CChar &operator [] (aint _Index) const
		{
#ifdef DMibDebug
			// Only do range checking in debug because f_GetStrLen might be a fg_StrLen
			if (_Index < 0 || _Index >= CImp::f_GetStrLen())
				DMibError("Range check error");
#endif

			return CImp::f_GetStr()[_Index];

		}

		inline_large CChar *f_GetStr(mint _MaxLength)
		{
			mint CurrentLen = f_GetLen();
			mint MaxLen = CImp::f_CreateWritableBuffer((CurrentLen + 1) > (_MaxLength + 1) ? (CurrentLen + 1) : (_MaxLength + 1), false);
			if (MaxLen < _MaxLength)
				return nullptr;
			else
			{
				// Invalidate fg_StrLen
				CImp::f_SetStrLen(-2);
				CChar *pStr = CImp::f_GetStrWritable();
				return pStr;
			}
		}

		void f_TrimSize()
		{
			CImp::f_TrimSize(f_GetLen()+1, 0);
		}

		inline_small aint f_GetLen() const
		{
			return CImp::f_GetStrLen();
		}

		/*¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯*\
		|	Function:			Returns the memory size needed to save the				|
		|						string and its null terminator character in				|
		|						memory													|
		\*_____________________________________________________________________________*/
		inline_small mint f_GetSize() const
		{
			return (f_GetLen() + 1) * sizeof(CChar);
		}

		inline_small CChar f_LargestChar()
		{
			return fg_StrLargestChar(f_GetStr());
		}

		template <typename t_CStrDataType>
			inline_small void f_AddChar(t_CStrDataType _Char)
		{
			aint Length = f_GetLen();
			fp_AddCharLengthAware(Length, _Char);
			CImp::f_SetStrLen(Length);
		}

		template <typename t_CStrDataType>
		void f_AddChars(t_CStrDataType _Char, aint _Count)
		{
			aint Length = f_GetLen();
			fp_AddCharsLengthAware(Length, _Char, _Count);
			CImp::f_SetStrLen(Length);
		}

		using CAppender = TCStringAppender<TCStrAggregate>;

		template <typename t_CStrDataType>
		void f_AddStr(t_CStrDataType *_pStr)
		{
			if (*_pStr != 0)
			{
				aint Length = f_GetLen();
				f_AddFromUnicodeIterator(Length, fg_GetUnicodeIterator(_pStr, fg_StrLen(_pStr)));
				CImp::f_SetStrLen(Length);
			}
		}

		template <typename t_CStrDataType>
		void f_AddStr(const t_CStrDataType *_pStr, aint _Len)
		{
			if (_Len && *_pStr != 0)
			{
				aint Length = f_GetLen();
				f_AddFromUnicodeIterator(Length, fg_GetUnicodeIterator(_pStr, _Len));
				CImp::f_SetStrLen(Length);
			}
		}

		void f_AddStr(CChar const *_pStr)
		{
			if (*_pStr != 0)
			{
				aint Length = f_GetLen();
				fp_AddStrLengthAware(Length, _pStr);
				CImp::f_SetStrLen(Length);
			}
		}

		void f_AddStr(CChar const *_pStr, aint _Len)
		{
			if (_Len && *_pStr != 0)
			{
				aint Length = f_GetLen();
				CAddStrAgrs Args(Length, _Len);
				fp_AddStrLengthAware(Args, _pStr);
				CImp::f_SetStrLen(Length);
			}
		}

		template <typename t_CStrTraitsF>
		void f_AddStr(TCStrAggregate<t_CStrTraitsF> const &_From);


		// //

		template <typename t_CStrDataType>
		void f_SetStr(t_CStrDataType *_pStr)
		{
			if (*_pStr != 0)
			{
				aint Length = 0;
				f_AddFromUnicodeIterator(Length, fg_GetUnicodeIterator(_pStr, fg_StrLen(_pStr)));
				CImp::f_SetStrLen(Length);
			}
			else
				this->f_Clear();
		}

		template <typename t_CStrDataType>
		void f_SetStr(const t_CStrDataType *_pStr, aint _Len)
		{
			if (_Len && *_pStr != 0)
			{
				aint Length = 0;
				f_AddFromUnicodeIterator(Length, fg_GetUnicodeIterator(_pStr, _Len));
				CImp::f_SetStrLen(Length);
			}
			else
				this->f_Clear();
		}

		void f_SetStr(CChar const *_pStr)
		{
			if (*_pStr != 0)
			{
				aint Length = 0;
				fp_AddStrLengthAware(Length, _pStr);
				CImp::f_SetStrLen(Length);
			}
			else
				this->f_Clear();
		}

		void f_SetStr(CChar const *_pStr, aint _Len)
		{
			if (_Len && *_pStr != 0)
			{
				aint Length = 0;
				CAddStrAgrs Args(Length, _Len);
				fp_AddStrLengthAware(Args, _pStr);
				CImp::f_SetStrLen(Length);
			}
			else
				this->f_Clear();
		}

		template <typename t_CStrTraitsF>
		void f_SetStr(TCStrAggregate<t_CStrTraitsF> const &_From);

		void fp_ConvertFromType(EStrType _Type)
		{
			fp_ConvertFromType<sizeof(CChar)>(_Type);
		}

		template <int t_CharSize>
		typename TCEnableIf<t_CharSize == 1, void>::CType fp_ConvertFromType(EStrType _Type);

		template <int t_CharSize>
		typename TCEnableIf<t_CharSize == 2, void>::CType fp_ConvertFromType(EStrType _Type);

		template <int t_CharSize>
		typename TCEnableIf<t_CharSize != 1 && t_CharSize != 2, void>::CType fp_ConvertFromType(EStrType _Type);


		template <typename t_CStrDataType>
		inline_medium void fp_AddCharLengthAware(aint &_StrLen, t_CStrDataType _Char)
		{
			aint MaxLen = CImp::f_CreateWritableBuffer(_StrLen + 2, false);
			if (MaxLen >= (_StrLen + 2))
			{
				CUnsignedChar *pStr = (CUnsignedChar *)CImp::f_GetStrWritable();
				pStr[_StrLen++] = (CUnsignedChar)(typename NTraits::TCUnsigned<t_CStrDataType>::CType)_Char;
				pStr[_StrLen] = 0;
			}
		}

		template <typename t_CStrDataType>
		inline_large void fp_AddCharsLengthAware(aint &_StrLen, t_CStrDataType _Char, aint _Count)
		{
			aint WantLen = _StrLen + _Count + 1;
			aint MaxLen = fg_Min(CImp::f_CreateWritableBuffer(WantLen, false), WantLen) - 1;
			CUnsignedChar *pStartPtr = (CUnsignedChar *)CImp::f_GetStrWritable();
			CUnsignedChar *pWritePtr = pStartPtr + _StrLen;
			const CUnsignedChar *pEndPtr;
			pEndPtr = pWritePtr + (MaxLen - _StrLen);

			while (pWritePtr < pEndPtr)
				*(pWritePtr++) = (CUnsignedChar)(typename NTraits::TCUnsigned<t_CStrDataType>::CType)_Char;

			*pWritePtr = 0;
			_StrLen = pWritePtr - pStartPtr;
		}


		inline_large void fp_AddStrLengthAware(aint &_StrLen, CChar const *_pStr)
		{
			CChar const *pReadPtr = _pStr;
			aint Grow = 32;
			while (*pReadPtr)
			{
				aint MaxLen = CImp::f_CreateWritableBuffer(_StrLen + Grow, false) - 1;
				if (MaxLen <= (_StrLen)) // No more room in str
					return;

				CUnsignedChar *pWritePtr = (CUnsignedChar *)CImp::f_GetStrWritable();
				const CUnsignedChar *pWritePtrEnd = pWritePtr + MaxLen;
				pWritePtr += _StrLen;

				while (*pReadPtr && pWritePtr < pWritePtrEnd)
				{
					*(pWritePtr++) = (CUnsignedChar)(*(pReadPtr++));
				}

				*pWritePtr = 0;
				_StrLen = (pWritePtr - (const CUnsignedChar *)f_GetStr());
				Grow <<= 1;
			}
		}

		class CAddStrAgrs
		{
		public:
			CAddStrAgrs(aint &_StrLen, mint _Len)
				: m_StrLen(_StrLen)
				, m_Len(_Len)
			{
			}
			aint &m_StrLen;
			mint m_Len;
		};

		inline_extralarge void fp_AddStrLengthAware(const CAddStrAgrs &_Args, CChar const *_pStr)
		{
			aint WantLen = _Args.m_StrLen + _Args.m_Len + 1;
			aint MaxLen = fg_Min(CImp::f_CreateWritableBuffer(WantLen, false), WantLen) - 1;

			CUnsignedChar *pWritable = (CUnsignedChar *)CImp::f_GetStrWritable();

			if (_Args.m_Len <= (8/sizeof(CChar)))
			{
				const CUnsignedChar *pStr = (const CUnsignedChar *)_pStr;
				CUnsignedChar *pWrite = pWritable + _Args.m_StrLen;
				CUnsignedChar *pEnd = pWrite + (MaxLen - _Args.m_StrLen);
				while (pWrite < pEnd)
				{
					*(pWrite++) = *(pStr++);
				}

				*pWrite = 0;
				_Args.m_StrLen = MaxLen;

				//			CChar *pWrite = f_GetStr() + _StrLen;
				//			*(pWrite++) = *(_pStr);
				//			*pWrite = 0;
				//			_StrLen = MaxLen;
			}
			else
			{
				NMib::NMemory::fg_MemCopy((pWritable + _Args.m_StrLen), _pStr, (MaxLen - _Args.m_StrLen) * sizeof(CChar));
				_Args.m_StrLen = MaxLen;
				pWritable[MaxLen] = 0;

			}
		}

		inline_small void fp_AddStrLengthAwareInline(const CAddStrAgrs &_Args, const CChar *_pStr)
		{
			aint WantLen = _Args.m_StrLen + _Args.m_Len + 1;
			aint MaxLen = fg_Min(CImp::f_CreateWritableBuffer(WantLen, false), WantLen) - 1;

			CUnsignedChar *pWritable = (CUnsignedChar *)CImp::f_GetStrWritable();

			const CUnsignedChar *pStr = (const CUnsignedChar *)_pStr;
			CUnsignedChar *pWrite = pWritable + _Args.m_StrLen;
			CUnsignedChar *pEnd = pWrite + (MaxLen - _Args.m_StrLen);
/*				while (pWrite+4 <= pEnd)
			{
				*(pWrite++) = *(pStr++);
				*(pWrite++) = *(pStr++);
				*(pWrite++) = *(pStr++);
				*(pWrite++) = *(pStr++);
			}*/
			while (pWrite < pEnd)
			{
				*(pWrite++) = *(pStr++);
			}

			*pWrite = 0;
			_Args.m_StrLen = MaxLen;
		}

		template <typename tf_CStrIterator>
		void f_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From)
		{
			fp_AddFromUnicodeIterator<sizeof(CChar)>(_StrLen, _From);
		}

		template <int t_CharSize, typename tf_CStrIterator>
		typename TCEnableIf<t_CharSize == 1, void>::CType fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From);

		template <int t_CharSize, typename tf_CStrIterator>
		typename TCEnableIf<t_CharSize == 2, void>::CType fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From);

		template <int t_CharSize, typename tf_CStrIterator>
		typename TCEnableIf<t_CharSize != 1 && t_CharSize != 2, void>::CType fp_AddFromUnicodeIterator(aint &_StrLen, tf_CStrIterator const &_From);

		enum
		{
			mc_NumSavedArgs = 16
		};

		class CParse : public TCStrParse<CStrTraits>
		{
		public:
			inline_medium CParse(const typename TCStrAggregate<t_CTCStrTraits>::CChar *_pParseStr) : TCStrParse<CStrTraits>(_pParseStr)
			{
			}
			inline_small aint f_Parse(const TCStrAggregate<t_CTCStrTraits> &_Str, aint &_nParsed, EParseFlag _ParseFlags)
			{
				const CChar *pParse = _Str.f_GetStr();
				return TCStrParse<CStrTraits>::f_Parse(pParse, _nParsed, _ParseFlags) - pParse;
			}
			inline_small aint f_Parse(const TCStrAggregate<t_CTCStrTraits> &_Str, aint &_nParsed)
			{
				const CChar *pParse = _Str.f_GetStr();
				return TCStrParse<CStrTraits>::f_Parse(pParse, _nParsed, EParseFlag_None) - pParse;
			}
			inline_small aint f_Parse(const TCStrAggregate<t_CTCStrTraits> &_Str, EParseFlag _ParseFlags = EParseFlag_None)
			{
				const CChar *pParse = _Str.f_GetStr();
				return TCStrParse<CStrTraits>::f_Parse(pParse, _ParseFlags) - pParse;
			}

			inline_small aint f_Parse(const CChar *_pStr, aint &_nParsed, EParseFlag _ParseFlags = EParseFlag_None)
			{
				const CChar *pParse = _pStr;
				return TCStrParse<CStrTraits>::f_Parse(pParse, _nParsed, _ParseFlags) - pParse;
			}
			inline_small aint f_Parse(const CChar *_pStr, EParseFlag _ParseFlags = EParseFlag_None)
			{
				const CChar *pParse = _pStr;
				return TCStrParse<CStrTraits>::f_Parse(pParse, _ParseFlags) - pParse;
			}

			template <typename t_CType>
			inline_small CParse &operator >> (t_CType &_Type)
			{
				TCStringParser<TCStrParse<CStrTraits>, t_CType>::f_CreateParse(*this, _Type);
				return *this;
			}

		};

		typedef TCFormat<t_CTCStrTraits> CFormat;
		typedef typename CFormat::CFomatArgType::CVisitor CFormatArgVisitor;
		typedef typename CFormat::CFomatArgType::CVisitorInteger CFormatArgVisitorInteger;
		typedef typename CFormat::CFomatArgType::CVisitorFloat CFormatArgVisitorFloat;
		typedef typename CFormat::CFomatArgType::CVisitorNumber CFormatArgVisitorNumber;
		typedef typename CFormat::CFomatArgType::CVisitorString CFormatArgVisitorString;

		template <typename t_CType>
		inline_medium static void fs_ToStrInplace(typename TCEnableIf<!NTraits::TCIsSame<typename TCStringFormatterAll<CFormat, t_CType>::CFormatType, int>::mc_Value, TCStrAggregate>::CType &_Destination, t_CType const& _Format)
		{
			typedef typename TCStringFormatterAll<CFormat, t_CType>::CFormatType CFormatType;
			aint CurrentLen = 0;
			CFormatType::fs_AddToStrStatic(_Destination, CurrentLen, _Format);
			_Destination.f_SetStrLen(CurrentLen);
		}

		template <typename t_CType>
		static void fs_ToStrInplace(typename TCEnableIf<NTraits::TCIsSame<typename TCStringFormatterAll<CFormat, t_CType>::CFormatType, int>::mc_Value, TCStrAggregate>::CType &_Destination, t_CType const& _Format)
		{
			(CFormat(nullptr) << _Format).f_FormatArgumentsToStr(_Destination);
		}

		template <typename t_CType>
		static void fs_ToStrInplace(TCStrAggregate &_Destination, const CChar *_pFormat, t_CType const& _Format)
		{
			return (CFormat(_pFormat) << _Format).f_FormatToStr(_Destination);
		}

		template <typename t_CType>
		inline_medium static void fs_ToStrInplaceConcat(typename TCEnableIf<!NTraits::TCIsSame<typename TCStringFormatterAll<CFormat, t_CType>::CFormatType, int>::mc_Value, TCStrAggregate>::CType &_Destination, t_CType const& _Format)
		{
			typedef typename TCStringFormatterAll<CFormat, t_CType>::CFormatType CFormatType;
			aint CurrentLen = _Destination.f_GetStrLen();
			CFormatType::fs_AddToStrStatic(_Destination, CurrentLen, _Format);
			_Destination.f_SetStrLen(CurrentLen);
		}

		template <typename t_CType>
		inline_medium static void fs_ToStrInplaceConcat(typename TCEnableIf<!NTraits::TCIsSame<typename TCStringFormatterAll<CFormat, t_CType>::CFormatType, int>::mc_Value, TCStrAggregate>::CType &_Destination, t_CType const& _Format, aint &_Len)
		{
			typedef typename TCStringFormatterAll<CFormat, t_CType>::CFormatType CFormatType;
			CFormatType::fs_AddToStrStatic(_Destination, _Len, _Format);
		}

		template <typename t_CType>
		static void fs_ToStrInplaceConcat(typename TCEnableIf<NTraits::TCIsSame<typename TCStringFormatterAll<CFormat, t_CType>::CFormatType, int>::mc_Value, TCStrAggregate>::CType &_Destination, t_CType const& _Format)
		{
			(CFormat(nullptr) << _Format).f_FormatArgumentsToStrConcat(_Destination);
		}


		template <typename t_CType>
		static void fs_ToStrInplaceConcat(TCStrAggregate &_Destination, const CChar *_pFormat, t_CType const& _Format)
		{
			return (CFormat(_pFormat) << _Format).f_FormatToStrConcat(_Destination);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////
		//////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////

		/************************************************************************************************\
		||||
		|| Cmp
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <typename t_CData2>
			inline_small typename TCChooseStrCompareType<CChar, t_CData2>::CType f_Cmp(const t_CData2 *_pStr2) const
		{
			return fg_StrCmp(*this, _pStr2);
		}

		template <typename t_CTCStrTraits2>
			inline_small typename TCChooseStrCompareType<CChar, TCStrAggregate<t_CTCStrTraits2> >::CType f_Cmp(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrCmp(*this, _Str1);
		}

		template <typename t_CData2>
			inline_small typename TCChooseStrCompareType<CChar, t_CData2>::CType f_CmpNoCase(const t_CData2 *_pStr2) const
		{
			return fg_StrCmpNoCase(*this, _pStr2);
		}

		template <typename t_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<CChar, TCStrAggregate<t_CTCStrTraits2> >::CType f_CmpNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrCmpNoCase(*this, _Str1);
		}

		template <typename t_CData2>
			inline_small typename TCChooseStrCompareType<CChar, t_CData2>::CType f_Cmp(const t_CData2 *_pStr2, mint _MaxLen) const
		{
			return fg_StrCmp(*this, _pStr2, _MaxLen);
		}

		template <typename t_CTCStrTraits2>
			inline_small typename TCChooseStrCompareType<CChar, TCStrAggregate<t_CTCStrTraits2> >::CType f_Cmp(const TCStrAggregate<t_CTCStrTraits2> &_Str1, mint _MaxLen) const
		{
			return fg_StrCmp(*this, _Str1, _MaxLen);
		}

		template <typename t_CData2>
			inline_small typename TCChooseStrCompareType<CChar, t_CData2>::CType f_CmpNoCase(const t_CData2 *_pStr2, mint _MaxLen) const
		{
			return fg_StrCmpNoCase(*this, _pStr2, _MaxLen);
		}

		template <typename t_CTCStrTraits2>
			inline_small typename TCChooseStrCompareType<CChar, TCStrAggregate<t_CTCStrTraits2> >::CType f_CmpNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Str1, mint _MaxLen) const
		{
			return fg_StrCmpNoCase(*this, _Str1, _MaxLen);
		}

		/************************************************************************************************\
		||||
		|| Searching
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <typename t_CData2>
			inline_small aint f_FindChar(t_CData2 _Char) const
		{
			return fg_StrFindChar(*this, _Char);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharOffset(aint _Start, t_CData2 _Char) const
		{
			return fg_StrFindChar(_Start, *this, _Char);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharNoCase(t_CData2 _Char) const
		{
			return fg_StrFindCharNoCase(*this, _Char);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharNoCaseOffset(aint _Start, t_CData2 _Char) const
		{
			return fg_StrFindCharNoCase(_Start, *this, _Char);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharReverse(t_CData2 _Char) const
		{
			return fg_StrFindCharReverse(*this, _Char);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharReverseNoCase(t_CData2 _Char) const
		{
			return fg_StrFindCharReverseNoCase(*this, _Char);
		}
		template <typename t_CData2>
			inline_small aint f_FindChar(t_CData2 _Char, mint _MaxLen) const
		{
			return fg_StrFindChar(*this, _Char, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharOffset(aint _Start, t_CData2 _Char, mint _MaxLen) const
		{
			return fg_StrFindChar(_Start, *this, _Char, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharNoCase(t_CData2 _Char, mint _MaxLen) const
		{
			return fg_StrFindCharNoCase(*this, _Char, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharNoCaseOffset(aint _Start, t_CData2 _Char, mint _MaxLen) const
		{
			return fg_StrFindCharNoCase(_Start, *this, _Char, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharReverse(t_CData2 _Char, mint _MaxLen) const
		{
			return fg_StrFindCharReverse(*this, _Char, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharReverseNoCase(t_CData2 _Char, mint _MaxLen) const
		{
			return fg_StrFindCharReverseNoCase(*this, _Char, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindChars(const t_CData2 *_pChars) const
		{
			return fg_StrFindChars(*this, _pChars);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharsNoCase(const t_CData2 *_pChars) const
		{
			return fg_StrFindCharsNoCase(*this, _pChars);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharsReverse(const t_CData2 *_pChars) const
		{
			return fg_StrFindCharsReverse(*this, _pChars);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharsReverseNoCase(const t_CData2 *_pChars) const
		{
			return fg_StrFindCharsReverseNoCase(*this, _pChars);
		}
		template <typename t_CData2>
			inline_small aint f_FindChars(const t_CData2 *_pChars, mint _MaxLen) const
		{
			return fg_StrFindChars(*this, _pChars, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharsNoCase(const t_CData2 *_pChars, mint _MaxLen) const
		{
			return fg_StrFindCharsNoCase(*this, _pChars, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharsReverse(const t_CData2 *_pChars, mint _MaxLen) const
		{
			return fg_StrFindCharsReverse(*this, _pChars, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindCharsReverseNoCase(const t_CData2 *_pChars, mint _MaxLen) const
		{
			return fg_StrFindCharsReverseNoCase(*this, _pChars, _MaxLen);
		}


		template <typename t_CTCStrTraits2>
			inline_small aint f_FindChars(const TCStrAggregate<t_CTCStrTraits2> &_Chars) const
		{
			return fg_StrFindChars(*this, _Chars);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindCharsNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Chars) const
		{
			return fg_StrFindCharsNoCase(*this, _Chars);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindCharsReverse(const TCStrAggregate<t_CTCStrTraits2> &_Chars) const
		{
			return fg_StrFindCharsReverse(*this, _Chars);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindCharsReverseNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Chars) const
		{
			return fg_StrFindCharsReverseNoCase(*this, _Chars);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindChars(const TCStrAggregate<t_CTCStrTraits2> &_Chars, mint _MaxLen) const
		{
			return fg_StrFindChars(*this, _Chars, _MaxLen);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindCharsNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Chars, mint _MaxLen) const
		{
			return fg_StrFindCharsNoCase(*this, _Chars, _MaxLen);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindCharsReverse(const TCStrAggregate<t_CTCStrTraits2> &_Chars, mint _MaxLen) const
		{
			return fg_StrFindCharsReverse(*this, _Chars, _MaxLen);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindCharsReverseNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Chars, mint _MaxLen) const
		{
			return fg_StrFindCharsReverseNoCase(*this, _Chars, _MaxLen);
		}


		template <typename t_CData2>
			inline_small aint f_Find(const t_CData2 *_pStr2) const
		{
			return fg_StrFind(*this, _pStr2);
		}
		template <typename t_CData2>
			inline_small aint f_Find(aint _Start, const t_CData2 *_pStr2) const
		{
			return fg_StrFind(_Start, *this, _pStr2);
		}
		template <typename t_CData2>
			inline_small aint f_FindNoCase(const t_CData2 *_pStr2) const
		{
			return fg_StrFindNoCase(*this, _pStr2);
		}
		template <typename t_CData2>
			inline_small aint f_FindNoCase(aint _Start, const t_CData2 *_pStr2) const
		{
			return fg_StrFindNoCase(_Start, *this, _pStr2);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_Find(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrFind(*this, _Str1);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_Find(aint _Start, const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrFind(_Start, *this, _Str1);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_FindNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrFindNoCase(*this, _Str1);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindNoCase(aint _Start, const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrFindNoCase(_Start, *this, _Str1);
		}

		template <typename t_CData2>
			inline_small aint f_FindReverse(const t_CData2 *_pStr1) const
		{
			return fg_StrFindReverse(*this, _pStr1);
		}

		template <typename t_CData2>
			inline_small aint f_FindReverseNoCase(const t_CData2 *_pStr1) const
		{
			return fg_StrFindReverseNoCase(*this, _pStr1);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_FindReverse(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrFindReverse(*this, _Str1);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_FindReverseNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrFindReverseNoCase(*this, _Str1);
		}

		/////////

		template <typename t_CData2>
			inline_small aint f_Find(const t_CData2 *_pStr2, mint _MaxLen) const
		{
			return fg_StrFind(*this, _pStr2, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_Find(aint _Start, const t_CData2 *_pStr2, mint _MaxLen) const
		{
			return fg_StrFind(_Start, *this, _pStr2, _MaxLen);
		}

		template <typename t_CData2>
			inline_small aint f_FindNoCase(const t_CData2 *_pStr2, mint _MaxLen) const
		{
			return fg_StrFindNoCase(*this, _pStr2, _MaxLen);
		}
		template <typename t_CData2>
			inline_small aint f_FindNoCase(aint _Start, const t_CData2 *_pStr2, mint _MaxLen) const
		{
			return fg_StrFindNoCase(_Start, *this, _pStr2, _MaxLen);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_Find(const TCStrAggregate<t_CTCStrTraits2> &_Str1, mint _MaxLen) const
		{
			return fg_StrFind(*this, _Str1, _MaxLen);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_Find(aint _Start, const TCStrAggregate<t_CTCStrTraits2> &_Str1, mint _MaxLen) const
		{
			return fg_StrFind(_Start, *this, _Str1, _MaxLen);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_FindNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Str1, mint _MaxLen) const
		{
			return fg_StrFindNoCase(*this, _Str1, _MaxLen);
		}
		template <typename t_CTCStrTraits2>
			inline_small aint f_FindNoCase(aint _Start, const TCStrAggregate<t_CTCStrTraits2> &_Str1, mint _MaxLen) const
		{
			return fg_StrFindNoCase(_Start, *this, _Str1, _MaxLen);
		}

		template <typename t_CData2>
			inline_small aint f_FindReverse(const t_CData2 *_pStr1, mint _MaxLen) const
		{
			return fg_StrFindReverse(*this, _pStr1, _MaxLen);
		}

		template <typename t_CData2>
			inline_small aint f_FindReverseNoCase(const t_CData2 *_pStr1, mint _MaxLen) const
		{
			return fg_StrFindReverseNoCase(*this, _pStr1, _MaxLen);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_FindReverse(const TCStrAggregate<t_CTCStrTraits2> &_Str1, mint _MaxLen) const
		{
			return fg_StrFindReverse(*this, _Str1, _MaxLen);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_FindReverseNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Str1, mint _MaxLen) const
		{
			return fg_StrFindReverseNoCase(*this, _Str1, _MaxLen);
		}


		template <typename t_CData2>
			inline_small aint f_StartsWith(const t_CData2 *_pStr2) const
		{
			return fg_StrStartsWith(*this, _pStr2);
		}

		template <typename t_CData2>
			inline_small aint f_StartsWithNoCase(const t_CData2 *_pStr2) const
		{
			return fg_StrStartsWithNoCase(*this, _pStr2);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_StartsWith(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrStartsWith(*this, _Str1);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_StartsWithNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrStartsWithNoCase(*this, _Str1);
		}


		template <typename t_CData2>
			inline_small aint f_EndsWith(const t_CData2 *_pStr2) const
		{
			return fg_StrEndsWith(*this, _pStr2);
		}

		template <typename t_CData2>
			inline_small aint f_EndsWithNoCase(const t_CData2 *_pStr2) const
		{
			return fg_StrEndsWithNoCase(*this, _pStr2);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_EndsWith(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrEndsWith(*this, _Str1);
		}

		template <typename t_CTCStrTraits2>
			inline_small aint f_EndsWithNoCase(const TCStrAggregate<t_CTCStrTraits2> &_Str1) const
		{
			return fg_StrEndsWithNoCase(*this, _Str1);
		}

		/***************************************************************************************************\
		||
		| Misc
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/


		inline_small bool f_IsAnsi() const
		{
			return fg_StrIsAnsi(f_GetStr());
		}


		inline_small bool f_IsAlphaNumeric() const
		{
			const CChar *pStr = *this;
			while (*pStr)
			{
				if (!fg_CharIsAlphabetical(*pStr) && !fg_CharIsNumber(*pStr))
					return false;
				++pStr;
			}
			return true;
		}

		inline_small bool f_IsAnsiAlphaNumeric() const
		{
			const CChar *pStr = *this;
			while (*pStr)
			{
				if (!fg_CharIsAnsiAlphabetical(*pStr) && !fg_CharIsNumber(*pStr))
					return false;
				++pStr;
			}
			return true;
		}

		inline_small bool f_IsNumeric() const
		{
			if (f_IsEmpty())
				return false;

			const CChar *pStr = *this;
			while (*pStr)
			{
				if (!fg_CharIsNumber(*pStr))
					return false;
				++pStr;
			}
			return true;
		}

		inline_small bool f_IsIdentifierStatement() const
		{
			const CChar *pStr = *this;
			if (!(fg_CharIsAlphabetical(*pStr) || *pStr == '_'))
				return false;
			while (*pStr)
			{
				if (!fg_CharIsAlphabetical(*pStr) && !fg_CharIsNumber(*pStr) && *pStr != '_')
					return false;
				++pStr;
			}
			return true;
		}

		inline_small bool f_IsAlphaNumericStatement() const
		{
			const CChar *pStr = *this;
			if (!fg_CharIsAlphabetical(*pStr))
				return false;
			while (*pStr)
			{
				if (!fg_CharIsAlphabetical(*pStr) && !fg_CharIsNumber(*pStr))
					return false;
				++pStr;
			}
			return true;
		}


		template <typename t_CData2>
			inline_small void f_SetAt(aint _Index, t_CData2 _Character)
		{
			fg_StrSetAt(*this, _Index, _Character);
		}

		ch32 f_GetAt(aint _Index) const
		{
			return f_GetStr()[_Index];
		}

		mint f_GetCharSize() const
		{
			return sizeof(CChar);
		}

		template <typename t_CTypeData>
		t_CTypeData f_ToValue(t_CTypeData const &_Default) const
		{
			t_CTypeData Return = _Default;
			(CParse(ms_FormatStr) >> Return).f_Parse(*this);
			return Return;
		}

		template <typename t_CTypeData>
		t_CTypeData f_ToValue(t_CTypeData const &_Default, const CChar *_pFormat) const
		{
			t_CTypeData Return = _Default;
			(CParse("_pFormat") >> Return).f_Parse(*this);
			return Return;
		}

		int32 f_ToInt() const
		{
			return CStrTraits::fs_StrToInt(CImp::f_GetStr(), int32(0));
		}

		template <typename t_CReturn>
		t_CReturn f_ToInt(t_CReturn _FailValue) const
		{
			return CStrTraits::fs_StrToInt(CImp::f_GetStr(), _FailValue);
		}

		template <typename t_CReturn, typename t_CTerm>
		t_CReturn f_ToInt(t_CReturn _FailValue, const t_CTerm *_pStrTerminators) const
		{
			return CStrTraits::fs_StrToInt(CImp::f_GetStr(), _FailValue, _pStrTerminators);
		}

		int32 f_ToIntExact() const
		{
			return CStrTraits::fs_StrToIntExact(CImp::f_GetStr(), int32(0));
		}

		template <typename t_CReturn>
		t_CReturn f_ToIntExact(t_CReturn _FailValue) const
		{
			return CStrTraits::fs_StrToIntExact(CImp::f_GetStr(), _FailValue);
		}

		template <typename t_CReturn, typename t_CTerm>
		t_CReturn f_ToIntExact(t_CReturn _FailValue, const t_CTerm *_pStrTerminators) const
		{
			return CStrTraits::fs_StrToIntExact(CImp::f_GetStr(), _FailValue, _pStrTerminators);
		}


		fp32 f_ToFloat() const
		{
			return CStrTraits::fs_StrToFloat(CImp::f_GetStr(), fp32(0.0));
		}

		fp32 f_ToFloatExact() const
		{
			return CStrTraits::fs_StrToFloatExact(CImp::f_GetStr(), fp32(0.0));
		}

		template <typename t_CReturn>
		t_CReturn f_ToFloat(t_CReturn _FailValue) const
		{
			return CStrTraits::fs_StrToFloat(CImp::f_GetStr(), _FailValue);
		}

		template <typename t_CReturn>
		t_CReturn f_ToFloatExact(t_CReturn _FailValue) const
		{
			return CStrTraits::fs_StrToFloatExact(CImp::f_GetStr(), _FailValue);
		}

		template <typename t_CReturn, typename t_CTerm>
		t_CReturn f_ToFloat(t_CReturn _FailValue, const t_CTerm *_pStrTerminators) const
		{
			return CStrTraits::fs_StrToFloat(CImp::f_GetStr(), _FailValue, _pStrTerminators);
		}

		template <typename t_CReturn, typename t_CTerm>
		t_CReturn f_ToFloatExact(t_CReturn _FailValue, const t_CTerm *_pStrTerminators) const
		{
			return CStrTraits::fs_StrToFloatExact(CImp::f_GetStr(), _FailValue, _pStrTerminators);
		}

		uint32 f_Hash() const
		{
			return fg_StrHash(CImp::f_GetStr());
		}

		uint32 f_HashDJB2() const
		{
			return fg_StrHashDJB2(CImp::f_GetStr());
		}

		uint32 f_HashSDBM() const
		{
			return fg_StrHashSDBM(CImp::f_GetStr());
		}

		CDynamicStr f_Indent(ch8 const *_pIndent, bool _bIndentFirst = true) const
		{
			auto const *pParse = this->f_GetStr();
			auto const *pParseEnd = pParse + this->f_GetLen();

			CDynamicStr Return;

			while (pParse < pParseEnd)
			{
				auto iSplitPoint = fg_StrFindChars(pParse, "\r\n", pParseEnd - pParse);
				if (iSplitPoint < 0)
				{
					if (Return.f_IsEmpty() && !_bIndentFirst)
						return *this;

					Return.f_AddStr(_pIndent);
					Return.f_AddStr(pParse, pParseEnd - pParse);
					return Return;
				}

				auto pParseStart = pParse;

				pParse += iSplitPoint;

				if (*pParse == '\r')
					++pParse;

				if (*pParse == '\n')
					++pParse;

				if (_bIndentFirst || !Return.f_IsEmpty())
					Return.f_AddStr(_pIndent);
				Return.f_AddStr(pParseStart, pParse - pParseStart);
			}

			return Return;
		}

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
		| Split/Join
		|____________________________________________________________________________________________________
		\***************************************************************************************************/

		template <bool tf_bRemoveEmpty = false, typename tf_CStrSeparator>
		NContainer::TCVector<CDynamicStr> f_Split(tf_CStrSeparator const &_Separator) const;

		template <bool tf_bRemoveEmpty = false>
		NContainer::TCVector<CDynamicStr> f_SplitEscaped(CChar _Separator) const;

		template <bool tf_bRemoveEmpty = false>
		NContainer::TCVector<CDynamicStr> f_SplitLine() const;

		template <typename tf_CContainer, typename tf_CStrSeparator>
		static CDynamicStr fs_Join(tf_CContainer &&_Strings, tf_CStrSeparator const &_Separator = "");

		template <typename tf_CContainer>
		static CDynamicStr fs_JoinEscaped(tf_CContainer &&_Strings, CChar _Separator);

		/***************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
		| Concat
		|____________________________________________________________________________________________________
		\***************************************************************************************************/

		template <typename t_CStrTraitsF>
		inline_large TCStrAggregate & operator += (const TCStrAggregate<t_CStrTraitsF> &_Str);
		template <typename t_CStrTraitsF>
		inline_large TCStrAggregate & operator += (const TCStr<t_CStrTraitsF> &_Str);
		template <typename t_CStrDataType>
		inline_large TCStrAggregate & operator += (const t_CStrDataType *_pToAdd);
		inline_large TCStrAggregate & operator += (CFormat const &_Format);
		inline_large TCStrAggregate & operator += (ch32 _ToAdd);

		/************************************************************************************************\
		||||
		|| Upper case
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		CDynamicStr f_UpperCase() const
		{
			CDynamicStr Temp = *this;
			fg_StrUpperCase(Temp);
			return Temp;
		}

		CDynamicStr f_UpperCase(mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrUpperCase(Temp, _MaxLen);
			return Temp;
		}

		/************************************************************************************************\
		||||
		|| Lower case
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		CDynamicStr f_LowerCase() const
		{
			CDynamicStr Temp = *this;
			fg_StrLowerCase(Temp);
			return Temp;
		}

		CDynamicStr f_LowerCase(mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrLowerCase(Temp, _MaxLen);
			return Temp;
		}

		/************************************************************************************************\
		||||
		|| Tab
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		CDynamicStr f_Untabify(mint _TabLength) const
		{
			CDynamicStr Temp = *this;
			fg_StrUntabify(Temp, _TabLength);
			return Temp;
		}

		/************************************************************************************************\
		||||
		|| Replace
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <typename t_CData2, typename t_CData3>
			CDynamicStr f_Replace(const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplace(Temp, _pStrFind, _pStrReplace);
			return Temp;
		}

		template <typename t_CTCStrTraits1, typename t_CData3>
			CDynamicStr f_Replace(const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const t_CData3 *_pStrReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplace(Temp, _StrFind, _pStrReplace);
			return Temp;
		}


		template <typename t_CTCStrTraits1, typename t_CData3>
			CDynamicStr f_Replace(const t_CData3 *_pStrFind, const TCStrAggregate<t_CTCStrTraits1> &_StrReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplace(Temp, _pStrFind, _StrReplace);
			return Temp;
		}

		template <typename t_CTCStrTraits1, typename t_CTCStrTraits2>
			CDynamicStr f_Replace(const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const TCStrAggregate<t_CTCStrTraits2> &_StrReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplace(Temp, _StrFind, _StrReplace);
			return Temp;
		}


		template <typename t_CData2, typename t_CData3>
			CDynamicStr f_ReplaceNoCase(const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceNoCase(Temp, _pStrFind, _pStrReplace);
			return Temp;
		}

		template <typename t_CTCStrTraits1, typename t_CData3>
			CDynamicStr f_ReplaceNoCase(const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const t_CData3 *_pStrReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceNoCase(Temp, _StrFind, _pStrReplace);
			return Temp;
		}


		template <typename t_CTCStrTraits1, typename t_CData3>
			CDynamicStr f_ReplaceNoCase(const t_CData3 *_pStrFind, const TCStrAggregate<t_CTCStrTraits1> &_StrReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceNoCase(Temp, _pStrFind, _StrReplace);
			return Temp;
		}

		template <typename t_CTCStrTraits1, typename t_CTCStrTraits2>
			CDynamicStr f_ReplaceNoCase(const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const TCStrAggregate<t_CTCStrTraits2> &_StrReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceNoCase(Temp, _StrFind, _StrReplace);
			return Temp;
		}


		template <typename t_CData2, typename t_CData3>
			CDynamicStr f_ReplaceChar(t_CData2 _CharFind, t_CData3 _CharReplace) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceChar(Temp, _CharFind, _CharReplace);
			return Temp;
		}


		template <typename t_CData2, typename t_CData3>
			CDynamicStr f_Replace(const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplace(Temp, _pStrFind, _pStrReplace, _MaxLen);
			return Temp;
		}

		template <typename t_CTCStrTraits1, typename t_CData3>
			CDynamicStr f_Replace(const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const t_CData3 *_pStrReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplace(Temp, _StrFind, _pStrReplace, _MaxLen);
			return Temp;
		}


		template <typename t_CTCStrTraits1, typename t_CData3>
			CDynamicStr f_Replace(const t_CData3 *_pStrFind, const TCStrAggregate<t_CTCStrTraits1> &_StrReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplace(Temp, _pStrFind, _StrReplace, _MaxLen);
			return Temp;
		}

		template <typename t_CTCStrTraits1, typename t_CTCStrTraits2>
			CDynamicStr f_Replace(const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const TCStrAggregate<t_CTCStrTraits2> &_StrReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplace(Temp, _StrFind, _StrReplace, _MaxLen);
			return Temp;
		}


		template <typename t_CData2, typename t_CData3>
			CDynamicStr f_ReplaceNoCase(const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceNoCase(Temp, _pStrFind, _pStrReplace, _MaxLen);
			return Temp;
		}

		template <typename t_CTCStrTraits1, typename t_CData3>
			CDynamicStr f_ReplaceNoCase(const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const t_CData3 *_pStrReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceNoCase(Temp, _StrFind, _pStrReplace, _MaxLen);
			return Temp;
		}


		template <typename t_CTCStrTraits1, typename t_CData3>
			CDynamicStr f_ReplaceNoCase(const t_CData3 *_pStrFind, const TCStrAggregate<t_CTCStrTraits1> &_StrReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceNoCase(Temp, _pStrFind, _StrReplace, _MaxLen);
			return Temp;
		}

		template <typename t_CTCStrTraits1, typename t_CTCStrTraits2>
			CDynamicStr f_ReplaceNoCase(const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const TCStrAggregate<t_CTCStrTraits2> &_StrReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceNoCase(Temp, _StrFind, _StrReplace, _MaxLen);
			return Temp;
		}

		template <typename t_CData2, typename t_CData3>
			CDynamicStr f_ReplaceChar(t_CData2 _CharFind, t_CData3 _CharReplace, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrReplaceChar(Temp, _CharFind, _CharReplace, _MaxLen);
			return Temp;
		}


		/************************************************************************************************\
		||||
		|| Insert
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <typename t_CData3>
			CDynamicStr f_Insert(aint _StartChar, const t_CData3 *_pStrInsert) const
		{
			CDynamicStr Temp = *this;
			fg_StrInsert(Temp, _StartChar, _pStrInsert);
			return Temp;
		}

		template <typename t_CTCStrTraits2>
			CDynamicStr f_Insert(aint _StartChar, const TCStrAggregate<t_CTCStrTraits2> &_StrInsert) const
		{
			CDynamicStr Temp = *this;
			fg_StrInsert(Temp, _StartChar, _StrInsert);
			return Temp;
		}

		template <typename t_CData3>
			CDynamicStr f_Insert(aint _StartChar, const t_CData3 *_pStrInsert, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrInsert(Temp, _StartChar, _pStrInsert, _MaxLen);
			return Temp;
		}

		template <typename t_CTCStrTraits2>
			CDynamicStr f_Insert(aint _StartChar, const TCStrAggregate<t_CTCStrTraits2> &_StrInsert, mint _MaxLen) const
		{
			CDynamicStr Temp = *this;
			fg_StrInsert(Temp, _StartChar, _StrInsert, _MaxLen);
			return Temp;
		}

		CDynamicStr f_EscapeStr() const
		{
			CDynamicStr Temp = *this;
			fg_StrEscapeStr(Temp, *this);
			return Temp;
		}

		template <typename t_CEscapeChar>
		CDynamicStr f_EscapeStr(const t_CEscapeChar *_pEscapeChars) const
		{
			CDynamicStr Temp = *this;
			fg_StrEscapeStr(Temp, *this, _pEscapeChars);
			return Temp;
		}

		template <typename t_CEscapeChar, typename t_CReplaceChars>
		CDynamicStr f_EscapeStr(const t_CEscapeChar *_pEscapeChars, const t_CReplaceChars *_pReplaceChars) const
		{
			CDynamicStr Temp = *this;
			fg_StrEscapeStr(Temp, *this, _pEscapeChars, _pReplaceChars);
			return Temp;
		}

		CDynamicStr f_EscapeStrNoQuotes() const
		{
			CDynamicStr Temp = *this;
			fg_StrEscapeStrNoQuotes(Temp, *this);
			return Temp;
		}

		template <typename t_CEscapeChar>
		CDynamicStr f_EscapeStrNoQuotes(const t_CEscapeChar *_pEscapeChars) const
		{
			CDynamicStr Temp = *this;
			fg_StrEscapeStrNoQuotes(Temp, *this, _pEscapeChars);
			return Temp;
		}

		template <typename t_CEscapeChar, typename t_CReplaceChars>
		CDynamicStr f_EscapeStrNoQuotes(const t_CEscapeChar *_pEscapeChars, const t_CReplaceChars *_pReplaceChars) const
		{
			CDynamicStr Temp = *this;
			fg_StrEscapeStrNoQuotes(Temp, *this, _pEscapeChars, _pReplaceChars);
			return Temp;
		}


		/***************************************************************************************************\
		||
		| Shortening
		|___________________________________________________________________________________________________|
		\***************************************************************************************************/

		CDynamicStr f_Delete(aint _StartChar, mint _nChars) const
		{
			CDynamicStr Temp = *this;
			fg_StrDelete(Temp, _StartChar, _nChars);
			return Temp;
		}

		CDynamicStr f_Left(mint _nChars) const
		{
			CDynamicStr Temp;
			mint Length = this->f_GetLen();
			mint nChars = fg_Min(_nChars, Length);
			if (nChars == Length)
				return *this;
			Temp.f_AddStr(this->f_GetStr(), nChars);
			return Temp;
		}

		CDynamicStr f_Extract(aint _StartChar, mint _nChars) const
		{
			if (_StartChar < 0)
				return *this;
			CDynamicStr Temp;
			mint Length = this->f_GetLen();
			if (_StartChar == 0 && _nChars == Length)
				return *this;
			mint Start = fg_Min(mint(_StartChar), Length);
			mint nChars = fg_Min(Length - Start, _nChars);
			Temp.f_AddStr(this->f_GetStr() + Start, nChars);
			return Temp;
		}

		CDynamicStr f_Extract(aint _StartChar) const
		{
			if (_StartChar <= 0)
				return *this;
			CDynamicStr Temp;
			mint Length = this->f_GetLen();
			mint Start = fg_Min(mint(_StartChar), Length);
			Temp.f_AddStr(this->f_GetStr() + Start, Length - Start);
			return Temp;
		}

		/*
		CDynamicStr f_Slice(aint _iStart, aint _iEnd) const

			Returns the substring from unit _iStart -> _iEnd
			(Not including unit _iEnd)

			If _Start or _End is < 0 they are used as offsets from the end of the string.

			(ala Python slice)
		*/
		CDynamicStr f_Slice(aint _iStart, aint _iEnd) const
		{
			mint Length = this->f_GetLen();
			mint Start;
			mint End;

			// Find first & last unit in slice
			if (_iStart < 0)
				Start = Length + _iStart;
			else
				Start = _iStart;

			if (_iEnd < 0)
				End = Length + _iEnd;
			else
				End = _iEnd;

			if (End > Length)
				End = Length;

			// No units in slice
			if (Start > End)
				return CDynamicStr();

			// Slice is whole string
			if (Start == 0 && End == Length)
				return *this;

			CDynamicStr Temp;
			mint nChars = End - Start;
			Temp.f_AddStr(this->f_GetStr() + Start, nChars);
			return Temp;
		}


		CDynamicStr f_Reverse() const
		{
			CDynamicStr Temp = *this;
			fg_StrReverse(Temp);
			return Temp;
		}

		CDynamicStr f_Right(mint _nChars) const
		{
			CDynamicStr Temp;
			mint Length = this->f_GetLen();
			mint nChars = fg_Min(Length, _nChars);
			Temp.f_AddStr(this->f_GetStr() + (Length - nChars), nChars);
			return Temp;
		}

		template <typename t_CData2>
		CDynamicStr f_TrimLeft(const t_CData2 *_pCharsToTrim) const
		{
			CDynamicStr Temp = *this;
			fg_StrTrimLeft(Temp, _pCharsToTrim);
			return Temp;
		}

		CDynamicStr f_TrimLeft() const
		{
			CDynamicStr Temp = *this;
			fg_StrTrimLeft(Temp);
			return Temp;
		}

		template <typename t_CData2>
		CDynamicStr f_TrimRight(const t_CData2 *_pCharsToTrim) const
		{
			CDynamicStr Temp = *this;
			fg_StrTrimRight(Temp, _pCharsToTrim);
			return Temp;
		}

		CDynamicStr f_TrimRight() const
		{
			CDynamicStr Temp = *this;
			fg_StrTrimRight(Temp);
			return Temp;
		}

		template <typename t_CData2>
		CDynamicStr f_Trim(const t_CData2 *_pCharsToTrim) const
		{
			CDynamicStr Temp = *this;
			fg_StrTrim(Temp, _pCharsToTrim);
			return Temp;
		}

		CDynamicStr f_Trim() const
		{
			CDynamicStr Temp = *this;
			fg_StrTrim(Temp);
			return Temp;
		}

		template <typename tf_CStr>
		CDynamicStr f_RemovePrefix(tf_CStr const &_ToFind) const
		{
			if (!f_StartsWith(_ToFind))
				return *this;
			return f_Extract(fg_StrLen(_ToFind));
		}

		template <typename tf_CStr>
		CDynamicStr f_RemoveSuffix(tf_CStr const &_ToFind) const
		{
			if (!f_EndsWith(_ToFind))
				return *this;
			return f_Left(f_GetLen() - fg_StrLen(_ToFind));
		}

		/************************************************************************************************\
		||||
		|| Operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		// Operator +
		template <typename tf_CCharData>
		friend CDynamicStr operator + (const tf_CCharData *_pToAdd, const TCStrAggregate &_Second)
		{
			CDynamicStr Temp;
			Temp.f_SetStr(_pToAdd);
			Temp.f_AddStr(_Second);
			return Temp;
		}

		// Operator !
		bool operator ! ()
		{
			return this->f_IsEmpty();
		}

		// Operator ==
		template <typename tf_CTCStrTraits>
		bool operator == (TCStrAggregate<tf_CTCStrTraits> const &_Right) const
		{
			if (f_GetLen() != _Right.f_GetLen())
				return false;
			return fg_StrCmp(*this, _Right, f_GetLen()) == 0;
		}

		template <typename tf_CData>
		bool operator == (tf_CData const *_pRight) const
		{
			return fg_StrCmp(*this, _pRight) == 0;
		}

		// Operator <=>
		template <typename tf_CTCStrTraits>
		COrdering_Weak operator <=> (TCStrAggregate<tf_CTCStrTraits> const &_Right) const
		{
			return fg_StrCmp(*this, _Right) <=> 0;
		}

		template <typename tf_CData>
		COrdering_Weak operator <=> (tf_CData const *_pRight) const
		{
			return fg_StrCmp(*this, _pRight) <=> 0;
		}
	};

	template <typename t_CTCStrTraits>
	class TCStr : public TCStrAggregate<t_CTCStrTraits>
	{
	public:

		typedef typename t_CTCStrTraits::CImp CImp;
		typedef t_CTCStrTraits CTraits;
		typedef typename t_CTCStrTraits::CStrTraits::CChar CChar;
		typedef TCStrAggregate<t_CTCStrTraits> CSuper;
		typedef typename CSuper::CFormat CFormat;
		typedef typename CSuper::CAddStrAgrs CAddStrAgrs;

		struct CAutoDestroy
		{
			CAutoDestroy(TCStr *_pThis)
				: mp_pThis(_pThis)
			{
			}
			~CAutoDestroy()
			{
				if (mp_pThis)
					mp_pThis->CSuper::f_Destroy();
			}
			void f_Clear()
			{
				mp_pThis = nullptr;
			}
		private:
			TCStr *mp_pThis;
		};

		inline_small TCStr() noexcept
		{
			CSuper::f_Construct();
		}

		inline_small ~TCStr()
		{
			CSuper::f_Destroy();
		}

		inline_large TCStr(CFormat const &_Format)
		{
			CSuper::f_Construct();
			CAutoDestroy Cleanup{this};
			_Format.f_FormatToStr(*this);
			Cleanup.f_Clear();
		}

		template <typename t_CStrDataType>
		inline_large TCStr(t_CStrDataType const *_pStr)
		{
			CSuper::f_Construct();
			CAutoDestroy Cleanup{this};
			CSuper::f_SetStr(_pStr);
			Cleanup.f_Clear();
		}

		template <typename t_CStrDataType, TCEnableIfType<CSuper::mc_bInitConstStr, t_CStrDataType *> = nullptr>
		inline_large TCStr(t_CStrDataType const *_pStr, mint _Len)
		{
			CSuper::f_Construct(_pStr, _Len);
		}

		template <typename t_CStrDataType, TCEnableIfType<!CSuper::mc_bInitConstStr, t_CStrDataType *> = nullptr>
		inline_large TCStr(t_CStrDataType const *_pStr, mint _Len)
		{
			CSuper::f_Construct();
			CAutoDestroy Cleanup{this};
			CSuper::f_SetStr(_pStr, _Len);
			Cleanup.f_Clear();
		}

		template <typename t_CStrDataType, typename ...tfp_CParams, TCEnableIfType<true, decltype(fg_GetType<CSuper>().f_Construct(fg_GetType<tfp_CParams>()...))> * = nullptr>
		inline_large TCStr(tfp_CParams &&...p_Params)
		{
			CSuper::f_Construct(fg_Forward<tfp_CParams>(p_Params)...);
		}

		inline_small TCStr(CSuper const &_Str)
		{
			CAutoDestroy Cleanup{this};
			CSuper::f_Construct(_Str);
			Cleanup.f_Clear();
		}

		inline_small TCStr(TCStr const &_Str)
		{
			CAutoDestroy Cleanup{this};
			CSuper::f_Construct((CSuper const &)_Str);
			Cleanup.f_Clear();
		}

		inline_small TCStr(CSuper &&_Str)
		{
			CAutoDestroy Cleanup{this};
			CSuper::f_Construct(fg_Move(_Str));
			Cleanup.f_Clear();
		}

		inline_small TCStr(TCStr &&_Str)
		{
			CAutoDestroy Cleanup{this};
			CSuper::f_Construct(fg_Move(_Str));
			Cleanup.f_Clear();
		}

		template <typename t_CStrTraitsF>
		inline_large TCStr(TCStrAggregate<t_CStrTraitsF> const &_From)
		{
			CImp::f_Construct();
			CAutoDestroy Cleanup{this};
			CSuper::f_SetStr(_From);
			Cleanup.f_Clear();
		}

		template <typename t_CStrTraitsF>
		inline_large TCStr & operator = (const TCStrAggregate<t_CStrTraitsF> &_From)
		{
			if (!(*_From.f_GetStr()))
			{
				this->f_Clear();
				return *this;
			}
			CSuper::f_SetStr(_From);
			return *this;
		}

		inline_large TCStr & operator = (const CSuper &_From)
		{
			CImp::f_Assign(_From);
			return *this;
		}

		inline_large TCStr & operator = (const TCStr &_From)
		{
			CImp::f_Assign((CSuper const &)_From);
			return *this;
		}

		inline_large TCStr & operator = (CSuper &&_From)
		{
			DMibFastCheck(this != &_From);
			CImp::f_Assign(fg_Move(_From));
			return *this;
		}

		inline_large TCStr & operator = (TCStr &&_From)
		{
			DMibFastCheck(this != &_From);
			CImp::f_Assign(fg_Move(_From));
			return *this;
		}

		template <typename t_CDataF>
			inline_large TCStr & operator = (const t_CDataF *_pFrom)
		{
			CSuper::f_SetStr(_pFrom);
			return *this;
		}

		inline_large TCStr & operator = (CFormat const &_Format)
		{
			_Format.f_FormatToStr(*this);
			return *this;
		}


		template <typename t_CStrTraitsF>
			inline_large TCStr & operator += (const TCStrAggregate<t_CStrTraitsF> &_Str)
		{
			CSuper::f_AddStr(_Str);
			return *this;
		}
		template <typename t_CStrTraitsF>
		inline_large TCStr & operator += (const TCStr<t_CStrTraitsF> &_Str)
		{
			CSuper::f_AddStr(_Str);
			return *this;
		}

		template <typename t_CStrDataType>
			inline_large TCStr & operator += (const t_CStrDataType *_pToAdd)
		{
			CSuper::f_AddStr(_pToAdd);
			return *this;
		}

		inline_large TCStr & operator += (CFormat const &_Format)
		{
			_Format.f_FormatToStrConcat(*this);
			return *this;
		}

		inline_large TCStr & operator += (ch32 _ToAdd)
		{
			this->f_AddChar(_ToAdd);
			return *this;
		}


		template <typename t_CStrTraitsF>
			TCStr operator + (const TCStrAggregate<t_CStrTraitsF> &_Str)  const
		{
			TCStr Temp = *this;
			Temp.f_AddStr(_Str);
			return Temp;
		}

		template <typename t_CStrDataType>
			TCStr operator + (const t_CStrDataType *_pToAdd) const
		{
			TCStr Temp = *this;
			Temp.f_AddStr(_pToAdd);
			return Temp;
		}

		TCStr operator ^ (mint _nCopies) const
		{
			if (!_nCopies)
				return {};

			TCStr Temp = *this;
			--_nCopies;

			for (; _nCopies; --_nCopies)
				Temp += *this;

			return Temp;
		}

		template <typename t_CType>
		inline static TCStr fs_ToStr(t_CType const &_Format)
		{
			if constexpr (NTraits::TCIsSame<typename TCStringFormatterAll<CFormat, t_CType>::CFormatType, int>::mc_Value)
			{
				TCStr Ret;
				(CFormat(nullptr) << _Format).f_FormatArgumentsToStr(Ret);
				return Ret;
			}
			else
			{
				TCStr Ret;
				typedef typename TCStringFormatterAll<CFormat, t_CType>::CFormatType CFormatType;
				aint CurrentLen = 0;
				CFormatType::fs_AddToStrStatic(Ret, CurrentLen, typename CFormatType::CType(_Format));
				Ret.f_SetStrLen(CurrentLen);
				return Ret;
			}
		}

		inline static TCStr fs_ToStr(CFormat const &_Format)
		{
			return _Format;
		}

		template <typename t_CType>
		static TCStr fs_ToStr(const CChar *_pFormat, t_CType const& _Format)
		{
			return (CFormat(_pFormat) << _Format).f_GetStr();
		}

		template <typename t_CStrDataType>
			static TCStr fs_Create(const t_CStrDataType *_pStr)
		{
			TCStr New;
			New.f_SetStr(_pStr);
			return New;
		}

		template <typename t_CStrDataType>
			static TCStr fs_Create(const t_CStrDataType *_pStr, aint _Len)
		{
			TCStr New;
			New.f_SetStr(_pStr, _Len);
			return New;
		}

		template <typename t_CStrTraitsF>
			static TCStr fs_Create(const TCStrAggregate<t_CStrTraitsF> &_From)
		{
			TCStr New;
			New.f_SetStr(_From);
			return New;
		}

		static TCStr fs_ReadTextStream(NStream::CBinaryStream &_Stream, bool _bAssumeUTF8 = false);
	};

	template <typename t_CTCStrTraits> const typename TCStrAggregate<t_CTCStrTraits>::CChar TCStrAggregate<t_CTCStrTraits>::ms_FormatStr[] = {'{', '}', 0};

	template <typename t_CTCStrTraits> const typename TCStrAggregate<t_CTCStrTraits>::CChar TCStrAggregate<t_CTCStrTraits>::ms_FormatConcatStr[] = {'{', '}', '{', '}', 0};


	template <typename t_CTCStrTraits>
	TCStr<t_CTCStrTraits> TCFormat<t_CTCStrTraits>::f_GetStr() const
	{
		TCStr<t_CTCStrTraits> Temp;
		f_FormatToStr(Temp);
		return Temp;
	}

	template <typename t_CTCStrTraits>
	TCStr<t_CTCStrTraits> TCFormat<t_CTCStrTraits>::operator ^ (mint _nCopies) const
	{
		if (!_nCopies)
			return {};

		TCStr<t_CTCStrTraits> Temp = *this;
		--_nCopies;

		for (; _nCopies; --_nCopies)
			Temp += *this;

		return Temp;
	}

	/************************************************************************************************\
	||||
	|| String functions
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <typename t_TCStr0, typename t_TCStr1>
	struct TCIsStrCompatible
	{
		enum
		{
			mc_Value =
				(
					sizeof(typename t_TCStr0::CStrTraits::CChar) == sizeof(typename t_TCStr0::CStrTraits::CChar)
					&& t_TCStr0::CStrTraits::mc_Type == t_TCStr1::CStrTraits::mc_Type
				)
				||
				(
					t_TCStr0::CStrTraits::mc_Type == EStrType_Unicode
					&& t_TCStr1::CStrTraits::mc_Type == EStrType_Unicode
				)
		};
	};

	template <typename t_TCStr0, typename t_TCStr1>
	struct TCIsStrCompatibleWrite
	{
		enum
		{
			mc_Value =
				(
					sizeof(typename t_TCStr0::CStrTraits::CChar) == sizeof(typename t_TCStr0::CStrTraits::CChar)
					&& t_TCStr0::CStrTraits::mc_Type == t_TCStr1::CStrTraits::mc_Type
				)
				||
				(
					sizeof(typename t_TCStr0::CStrTraits::CChar) >= sizeof(typename t_TCStr0::CStrTraits::CChar)
					&& t_TCStr0::CStrTraits::mc_Type == EStrType_Unicode
					&& t_TCStr1::CStrTraits::mc_Type == EStrType_Unicode
				)
		};
	};

	// Static functions
	template <typename t_CTCStrTraits2>
		inline_small mint fg_StrLen(const TCStrAggregate<t_CTCStrTraits2> &_Str)
	{
		return _Str.f_GetLen();
	}

	template <typename t_CTCStrTraits2>
		inline_small uint32 fg_StrHashDJB2(const TCStrAggregate<t_CTCStrTraits2> &_Str)
	{
		return _Str.f_HashDJB2();
	}

	template <typename t_CTCStrTraits2>
		inline_small uint32 fg_StrHashSDBM(const TCStrAggregate<t_CTCStrTraits2> &_Str)
	{
		return _Str.f_HashSDBM();
	}

	template <typename t_CTCStrTraits2>
		inline_small uint32 fg_StrHash(const TCStrAggregate<t_CTCStrTraits2> &_Str)
	{
		return _Str.f_Hash();
	}


	template <typename t_CTCStrTraits2>
		inline_small uint32 fg_StrIsAnsi(const TCStrAggregate<t_CTCStrTraits2> &_Str)
	{
		return fg_StrIsAnsi(_Str.f_GetStr());
	}

	template <typename t_CTCStrTraits2>
		inline_small uint32 fg_StrIsAnsi(const TCStrAggregate<t_CTCStrTraits2> &_Str, mint _MaxLen)
	{
		return fg_StrIsAnsi(_Str.f_GetStr(), _MaxLen);
	}


	template <typename t_CTCStrTraits2>
	bool fg_StrIsEmpty(const TCStrAggregate<t_CTCStrTraits2> &_Str)
	{
		return _Str.f_IsEmpty();
	}

	template <typename t_CTCStrTraits2>
	bool fg_StrIsEmpty(const TCFormat<t_CTCStrTraits2> &_Str)
	{
		return _Str.f_IsEmpty();
	}

	template <typename t_CTCStrTraits2>
		inline_small typename NTraits::TCUnsigned<typename TCStrAggregate<t_CTCStrTraits2>::CMaxChar >::CType fg_StrLargestChar(const TCStrAggregate<t_CTCStrTraits2> &_Str)
	{
		return fg_StrLargestChar(_Str.f_GetStr());
	}


	template <typename t_CTCStrTraits2, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits2> &fg_StrCopy(TCStrAggregate<t_CTCStrTraits2> &_To, const t_CData2 *_pFrom)
	{
		_To.f_Clear();
		_To.f_AddStr(_pFrom);
		return _To;
	}

	template <typename t_CTCStrTraits2, typename t_CData2>
		inline_small t_CData2 *fg_StrCopy(t_CData2 *_pTo, const TCStrAggregate<t_CTCStrTraits2> &_From)
	{
		fg_StrCopy(_pTo, _From.f_GetStr());
		return _pTo;
	}

	template <typename t_CTCStrTraits3, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits3> &fg_StrCopy(TCStrAggregate<t_CTCStrTraits3> &_To, const TCStrAggregate<t_CTCStrTraits2> &_From)
	{
		_To = _From;
		return _To;
	}

	template <typename t_CTCStrTraits3, typename t_CData2>
		inline_small t_CData2 *fg_StrCopy(t_CData2 *_pTo, const TCStrAggregate<t_CTCStrTraits3> &_From, mint _MaxLen)
	{
		fg_StrCopy(_pTo, _From.f_GetStr(), _MaxLen);
		return _pTo;
	}

	template <typename t_CTCStrTraits3, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits3> &fg_StrCopy(TCStrAggregate<t_CTCStrTraits3> &_To, const t_CData2 *_pFrom, mint _MaxLen)
	{
		_To.f_Clear();
		_To.f_AddStr(_pFrom, fg_Min(_MaxLen, fg_StrLen(_pFrom)));
		return _To;
	}

	template <typename t_CTCStrTraits3, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits3> &fg_StrCopy(TCStrAggregate<t_CTCStrTraits3> &_To, const TCStrAggregate<t_CTCStrTraits2> &_From, mint _MaxLen)
	{
		_To.f_Clear();
		_To.f_AddStr(_From.f_GetStr(), fg_Min(_MaxLen, fg_StrLen(_From)));
		return _To;
	}

	///////////////////////////

	template <typename t_CTCStrTraits3, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits3> &fg_StrMove(TCStrAggregate<t_CTCStrTraits3> &_To, const t_CData2 *_pFrom)
	{
		TCStrAggregate<t_CTCStrTraits3> Temp;
		fg_StrCopy(Temp, _pFrom);
		_To = Temp;
		return Temp;
	}

	template <typename t_CTCStrTraits3, typename t_CData2>
		inline_small t_CData2 *fg_StrMove(t_CData2 *_pTo, const TCStrAggregate<t_CTCStrTraits3> &_From)
	{
		return fg_StrCopy(_pTo, _From);
	}

	template <typename t_CTCStrTraits3, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits3> &fg_StrMove(TCStrAggregate<t_CTCStrTraits3> &_To, const TCStrAggregate<t_CTCStrTraits2> &_From)
	{
		return fg_StrCopy(_To, _From);
	}

	template <typename t_CTCStrTraits3, typename t_CData2>
		inline_small t_CData2 *fg_StrMove(t_CData2 *_pTo, const TCStrAggregate<t_CTCStrTraits3> &_From, mint _MaxLen)
	{
		return fg_StrCopy(_pTo, _From, _MaxLen);
	}

	template <typename t_CTCStrTraits3, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits3> &fg_StrMove(TCStrAggregate<t_CTCStrTraits3> &_To, const t_CData2 *_pFrom, mint _MaxLen)
	{
		TCStrAggregate<t_CTCStrTraits3> Temp;
		fg_StrCopy(Temp, _pFrom, _MaxLen);
		_To = Temp;
		return _To;
	}

	template <typename t_CTCStrTraits3, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits3> &fg_StrMove(TCStrAggregate<t_CTCStrTraits3> &_To, const TCStrAggregate<t_CTCStrTraits2> &_From, mint _MaxLen)
	{
		return fg_StrCopy(_To, _From, _MaxLen);
	}



	/************************************************************************************************\
	||																								||
	|| Upper case
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	template <typename t_CTCStrTraits>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrUpperCase(TCStrAggregate<t_CTCStrTraits> &_To)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;

		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");

		fg_StrUpperCase(pStr1, _To.f_GetLen());
		return _To;
	}

	template <typename t_CTCStrTraits3, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits3> &fg_StrUpperCase(TCStrAggregate<t_CTCStrTraits3> &_To, const t_CData2 *_pSource)
	{
		_To = _pSource;
		fg_StrUpperCase(_To);
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrUpperCase(TCStrAggregate<t_CTCStrTraits> &_To, const TCStrAggregate<t_CTCStrTraits2> &_Source)
	{
		_To = _Source;
		fg_StrUpperCase(_To);
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small t_CData2 *fg_StrUpperCase(t_CData2 *_pTo, const TCStrAggregate<t_CTCStrTraits> &_Source)
	{
		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");
		static_assert(NTraits::TCIsSame<t_CData2, typename TCStrAggregate<t_CTCStrTraits>::CChar>::mc_Value, "Unsupported");
		fg_StrUpperCase(_pTo, _Source.f_GetStr());
		return _pTo;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small t_CData2 *fg_StrUpperCase(t_CData2 *_pTo, const TCStrAggregate<t_CTCStrTraits> &_Source, mint _MaxLen)
	{
		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");
		static_assert(NTraits::TCIsSame<t_CData2, typename TCStrAggregate<t_CTCStrTraits>::CChar>::mc_Value, "Unsupported");
		fg_StrUpperCase(_pTo, _MaxLen, _Source.f_GetStr());
		return _pTo;
	}

	template <typename t_CTCStrTraits>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrUpperCase(TCStrAggregate<t_CTCStrTraits> &_To, mint _MaxLen)
	{
		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;
		fg_StrUpperCase(pStr1, _MaxLen);
		_To.f_SetModified();
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrUpperCase(TCStrAggregate<t_CTCStrTraits> &_To, const t_CData2 *_pSource, mint _MaxLen)
	{
		_To = _pSource;
		fg_StrUpperCase(_To, _MaxLen);
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrUpperCase(TCStrAggregate<t_CTCStrTraits> &_To, const TCStrAggregate<t_CTCStrTraits2> &_Source, mint _MaxLen)
	{
		_To = _Source;
		fg_StrUpperCase(_To, _MaxLen);
		return _To;
	}

	/************************************************************************************************\
	||||
	|| Lower case
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	template <typename t_CTCStrTraits>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrLowerCase(TCStrAggregate<t_CTCStrTraits> &_To)
	{
		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;
		fg_StrLowerCase(pStr1, _To.f_GetLen());
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrLowerCase(TCStrAggregate<t_CTCStrTraits> &_To, const t_CData2 *_pSource)
	{
		_To = _pSource;
		fg_StrLowerCase(_To);
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrLowerCase(TCStrAggregate<t_CTCStrTraits> &_To, const TCStrAggregate<t_CTCStrTraits2> &_Source)
	{
		_To = _Source;
		fg_StrLowerCase(_To);
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small t_CData2 *fg_StrLowerCase(t_CData2 *_pTo, const TCStrAggregate<t_CTCStrTraits> &_Source)
	{
		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");
		static_assert(NTraits::TCIsSame<t_CData2, typename TCStrAggregate<t_CTCStrTraits>::CChar>::mc_Value, "Unsupported");
		fg_StrLowerCase(_pTo, _Source.f_GetStr());
		return _pTo;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small t_CData2 *fg_StrLowerCase(t_CData2 *_pTo, const TCStrAggregate<t_CTCStrTraits> &_Source, mint _MaxLen)
	{
		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");
		static_assert(NTraits::TCIsSame<t_CData2, typename TCStrAggregate<t_CTCStrTraits>::CChar>::mc_Value, "Unsupported");
		fg_StrLowerCase(_pTo, _Source.f_GetStr(), _MaxLen);
		return _pTo;
	}

	template <typename t_CTCStrTraits>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrLowerCase(TCStrAggregate<t_CTCStrTraits> &_To, mint _MaxLen)
	{
		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;
		fg_StrLowerCase(pStr1, _MaxLen);
		_To.f_SetModified();
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrLowerCase(TCStrAggregate<t_CTCStrTraits> &_To, const t_CData2 *_pSource, mint _MaxLen)
	{
		_To = _pSource;
		fg_StrLowerCase(_To, _MaxLen);
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrLowerCase(TCStrAggregate<t_CTCStrTraits> &_To, const TCStrAggregate<t_CTCStrTraits2> &_Source, mint _MaxLen)
	{
		_To = _Source;
		fg_StrLowerCase(_To, _MaxLen);
		return _To;
	}

	/************************************************************************************************\
	||																								||
	|| Capitalize
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	template <typename t_CTCStrTraits>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrCapitalize(TCStrAggregate<t_CTCStrTraits> &_To)
	{
		static_assert(sizeof(typename TCStrAggregate<t_CTCStrTraits>::CChar) > 1 || (NTraits::TCIsSame<typename TCStrAggregate<t_CTCStrTraits>::CChar, ch8>::mc_Value && TCStrAggregate<t_CTCStrTraits>::mc_Type == EStrType_UTF), "Unsupported");
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _To.f_GetStrUniqueWritable();
		if (!pStr1)
			return _To;

		fg_StrCapitalize(pStr1, _To.f_GetLen());
		return _To;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrCapitalize(TCStrAggregate<t_CTCStrTraits> &_To, const TCStrAggregate<t_CTCStrTraits2> &_Source)
	{
		_To = _Source;
		fg_StrCapitalize(_To);
		return _To;
	}


	/************************************************************************************************\
	||||
	|| Cmp
	||______________________________________________________________________________________________||
	\************************************************************************************************/



	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, t_CData2>::CType fg_StrCmp(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrCmp(_Str1.f_GetStr(), _pStr2);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, t_CData2>::CType fg_StrCmp(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrCmp(_pStr1, _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, TCStrAggregate<t_CTCStrTraits2> >::CType fg_StrCmp(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmp(_Str1.f_GetStr(), _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CData2>
	inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, t_CData2>::CType fg_StrCmpNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrCmpNoCase(_Str1.f_GetStr(), _pStr2);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, t_CData2>::CType fg_StrCmpNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrCmpNoCase(_pStr1, _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, TCStrAggregate<t_CTCStrTraits2> >::CType fg_StrCmpNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmpNoCase(_Str1.f_GetStr(), _Str2.f_GetStr());
	}

	////

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, t_CData2>::CType fg_StrCmp(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2, mint _MaxLen)
	{
		return fg_StrCmp(_Str1.f_GetStr(), _pStr2, _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, t_CData2>::CType fg_StrCmp(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2, mint _MaxLen)
	{
		return fg_StrCmp(_pStr1, _Str2.f_GetStr(), _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, TCStrAggregate<t_CTCStrTraits2> >::CType fg_StrCmp(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmp(_Str1.f_GetStr(), _Str2.f_GetStr(), _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, t_CData2>::CType fg_StrCmpNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2, mint _MaxLen)
	{
		return fg_StrCmpNoCase(_Str1.f_GetStr(), _pStr2, _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, t_CData2>::CType fg_StrCmpNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2, mint _MaxLen)
	{
		return fg_StrCmpNoCase(_pStr1, _Str2.f_GetStr(), _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small typename TCChooseStrCompareType<TCStrAggregate<t_CTCStrTraits>, TCStrAggregate<t_CTCStrTraits2> >::CType fg_StrCmpNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrCmpNoCase(_Str1.f_GetStr(), _Str2.f_GetStr(), _MaxLen);
	}

	/************************************************************************************************\
	||||
	|| Searching
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindChar(const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char)
	{
		return fg_StrFindChar(_Str1.f_GetStr(), _Char);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindChar(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char)
	{
		return fg_StrAdd(_Start, fg_StrFindChar(_Str1.f_GetStr() + fg_Min(_Start, _Str1.f_GetLen()), _Char));
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char)
	{
		return fg_StrFindCharNoCase(_Str1.f_GetStr(), _Char);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharNoCase(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char)
	{
		return fg_StrAdd(_Start, fg_StrFindCharNoCase(_Str1.f_GetStr() + fg_Min(_Start, _Str1.f_GetLen()), _Char));
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char)
	{
		return fg_StrFindCharReverse(_Str1.f_GetStr(), _Char);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char)
	{
		return fg_StrFindCharReverseNoCase(_Str1.f_GetStr(), _Char);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindChar(const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char, mint _MaxLen)
	{
		return fg_StrFindChar(_Str1.f_GetStr(), _Char, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindChar(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char, mint _MaxLen)
	{
		return fg_StrAdd(_Start, fg_StrFindChar(_Str1.f_GetStr() + fg_Min(_Start, _Str1.f_GetLen()), _Char, _MaxLen));
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char, mint _MaxLen)
	{
		return fg_StrFindCharNoCase(_Str1.f_GetStr(), _Char, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharNoCase(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char, mint _MaxLen)
	{
		return fg_StrAdd(_Start, fg_StrFindCharNoCase(_Str1.f_GetStr() + fg_Min(_Start, _Str1.f_GetLen()), _Char, _MaxLen));
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char, mint _MaxLen)
	{
		return fg_StrFindCharReverse(_Str1.f_GetStr(), _Char, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _Char, mint _MaxLen)
	{
		return fg_StrFindCharReverseNoCase(_Str1.f_GetStr(), _Char, _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindChars(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pChars)
	{
		return fg_StrFindChars(_Str1.f_GetStr(), _pChars);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pChars)
	{
		return fg_StrFindCharsNoCase(_Str1.f_GetStr(), _pChars);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pChars)
	{
		return fg_StrFindCharsReverse(_Str1.f_GetStr(), _pChars);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pChars)
	{
		return fg_StrFindCharsReverseNoCase(_Str1.f_GetStr(), _pChars);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindChars(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pChars, mint _MaxLen)
	{
		return fg_StrFindChars(_Str1.f_GetStr(), _pChars, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pChars, mint _MaxLen)
	{
		return fg_StrFindCharsNoCase(_Str1.f_GetStr(), _pChars, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pChars, mint _MaxLen)
	{
		return fg_StrFindCharsReverse(_Str1.f_GetStr(), _pChars, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pChars, mint _MaxLen)
	{
		return fg_StrFindCharsReverseNoCase(_Str1.f_GetStr(), _pChars, _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindChars(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Chars)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindChars(_Str1.f_GetStr(), _Chars.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindCharsNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Chars)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsNoCase(_Str1.f_GetStr(), _Chars.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindCharsReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Chars)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverse(_Str1.f_GetStr(), _Chars.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindCharsReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Chars)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverseNoCase(_Str1.f_GetStr(), _Chars.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindChars(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Chars, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindChars(_Str1.f_GetStr(), _Chars.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindCharsNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Chars, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsNoCase(_Str1.f_GetStr(), _Chars.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindCharsReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Chars, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverse(_Str1.f_GetStr(), _Chars.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindCharsReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Chars, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindCharsReverseNoCase(_Str1.f_GetStr(), _Chars.f_GetStr(), _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindChars(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Chars)
	{
		return fg_StrFindChars(_pStr1, _Chars.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Chars)
	{
		return fg_StrFindCharsNoCase(_pStr1, _Chars.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsReverse(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Chars)
	{
		return fg_StrFindCharsReverse(_pStr1, _Chars.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsReverseNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Chars)
	{
		return fg_StrFindCharsReverseNoCase(_pStr1, _Chars.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindChars(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Chars, mint _MaxLen)
	{
		return fg_StrFindChars(_pStr1, _Chars.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Chars, mint _MaxLen)
	{
		return fg_StrFindCharsNoCase(_pStr1, _Chars.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsReverse(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Chars, mint _MaxLen)
	{
		return fg_StrFindCharsReverse(_pStr1, _Chars.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindCharsReverseNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Chars, mint _MaxLen)
	{
		return fg_StrFindCharsReverseNoCase(_pStr1, _Chars.f_GetStr(), _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFind(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrFind(_Str1.f_GetStr(), _pStr2);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFind(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrAdd(_Start, fg_StrFind(_Str1.f_GetStr() + fg_Min(_Start, _Str1.f_GetLen()), _pStr2));
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrFindNoCase(_Str1.f_GetStr(), _pStr2);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindNoCase(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrAdd(_Start, fg_StrFindNoCase(_Str1.f_GetStr() + fg_Min(_Start, _Str1.f_GetLen()), _pStr2));
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFind(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrFind(_pStr1, _Str2.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrFindNoCase(_pStr1, _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFind(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Str1.f_GetStr(), _Str2.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFind(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Start, _Str1, _Str2.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Str1.f_GetStr(), _Str2.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindNoCase(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Start, _Str1, _Str2.f_GetStr());
	}


	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrFindReverse(_Str1.f_GetStr(), _pStr2);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrFindReverseNoCase(_Str1.f_GetStr(), _pStr2);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindReverse(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrFindReverse(_pStr1, _Str2.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindReverseNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrFindReverseNoCase(_pStr1, _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse(_Str1.f_GetStr(), _Str2.f_GetStr());
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverseNoCase(_Str1.f_GetStr(), _Str2.f_GetStr());
	}

	/////////

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFind(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2, mint _MaxLen)
	{
		return fg_StrFind(_Str1.f_GetStr(), _pStr2, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFind(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2, mint _MaxLen)
	{
		return fg_StrAdd(_Start, fg_StrFind(_Str1.f_GetStr() + fg_Min(_Start, _Str1.f_GetLen()), _pStr2, _MaxLen));
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2, mint _MaxLen)
	{
		return fg_StrFindNoCase(_Str1.f_GetStr(), _pStr2, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindNoCase(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2, mint _MaxLen)
	{
		return fg_StrAdd(_Start, fg_StrFindNoCase(_Str1.f_GetStr() + fg_Min(_Start, _Str1.f_GetLen()), _pStr2, _MaxLen));
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFind(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2, mint _MaxLen)
	{
		return fg_StrFind(_pStr1, _Str2.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2, mint _MaxLen)
	{
		return fg_StrFindNoCase(_pStr1, _Str2.f_GetStr(), _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFind(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Str1.f_GetStr(), _Str2.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFind(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFind(_Start, _Str1, _Str2.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Str1.f_GetStr(), _Str2.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindNoCase(aint _Start, const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindNoCase(_Start, _Str1, _Str2.f_GetStr(), _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2, mint _MaxLen)
	{
		return fg_StrFindReverse(_Str1.f_GetStr(), _pStr2, _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2, mint _MaxLen)
	{
		return fg_StrFindReverseNoCase(_Str1.f_GetStr(), _pStr2, _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindReverse(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2, mint _MaxLen)
	{
		return fg_StrFindReverse(_pStr1, _Str2.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrFindReverseNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2, mint _MaxLen)
	{
		return fg_StrFindReverseNoCase(_pStr1, _Str2.f_GetStr(), _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindReverse(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverse(_Str1.f_GetStr(), _Str2.f_GetStr(), _MaxLen);
	}
	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrFindReverseNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2, mint _MaxLen)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrFindReverseNoCase(_Str1.f_GetStr(), _Str2.f_GetStr(), _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrStartsWith(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrStartsWith(_Str1.f_GetStr(), _pStr2);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrStartsWithNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrStartsWithNoCase(_Str1.f_GetStr(), _pStr2);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrStartsWith(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrStartsWith(_pStr1, _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrStartsWithNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrStartsWithNoCase(_pStr1, _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrStartsWith(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrStartsWith(_Str1.f_GetStr(), _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrStartsWithNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrStartsWithNoCase(_Str1.f_GetStr(), _Str2.f_GetStr());
	}


	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrEndsWith(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrEndsWith(_Str1.f_GetStr(), _pStr2);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrEndsWithNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStr2)
	{
		return fg_StrEndsWithNoCase(_Str1.f_GetStr(), _pStr2);
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrEndsWith(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrEndsWith(_pStr1, _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small aint fg_StrEndsWithNoCase(const t_CData2 *_pStr1, const TCStrAggregate<t_CTCStrTraits> &_Str2)
	{
		return fg_StrEndsWithNoCase(_pStr1, _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrEndsWith(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrEndsWith(_Str1.f_GetStr(), _Str2.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small aint fg_StrEndsWithNoCase(const TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits2> &_Str2)
	{
		static_assert(TCIsStrCompatible<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrEndsWithNoCase(_Str1.f_GetStr(), _Str2.f_GetStr());
	}

	/************************************************************************************************\
	||||
	|| Tabs
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrUntabify(TCStrAggregate<t_CTCStrTraits> &_Str1, mint _TabSize)
	{
		typedef typename TCStrAggregate<t_CTCStrTraits>::CChar CChar;
		TCStrAggregate<t_CTCStrTraits> Temp;
		Temp.f_Construct(_Str1);
		const CChar *pStr1 = Temp.f_GetStr();
		mint NeededLen = 0;
		mint Column = 0;

		while (*pStr1)
		{
			CChar Char = *pStr1;

			if (Char == '\t')
			{
				mint OldColumn = Column;
				Column = ((Column + _TabSize) / _TabSize) * _TabSize;
				NeededLen += Column - OldColumn;
			}
			else if (Char == '\r')
			{
				++NeededLen;
				Column = 0;
				++pStr1;
				if (*pStr1 == '\n')
				{
					++NeededLen;
					++pStr1;
				}
				continue;
			}
			else if (*pStr1 == '\n')
			{
				++NeededLen;
				Column = 0;
			}
			else
			{
				++NeededLen;
				++Column;
			}

			++pStr1;
		}

		uint32 MaxLen = NeededLen+1;
		CChar *pWrite = _Str1.f_GetStr(MaxLen);
#			if DMibEnableSafeCheck > 0
			CChar *pWriteStart = pWrite;
#			endif

		pStr1 = Temp.f_GetStr();
		Column = 0;
		while (*pStr1)
		{
			CChar Char = *pStr1;
			if (Char == '\t')
			{
				mint OldColumn = Column;
				Column = ((Column + _TabSize) / _TabSize) * _TabSize;
				mint nFill = Column - OldColumn;
				for (mint i = 0; i < nFill; ++i)
					*(pWrite++) = ' ';
			}
			else if (Char == '\r')
			{
				*(pWrite++) = Char;
				Column = 0;
				++pStr1;
				if (*pStr1 == '\n')
				{
					*(pWrite++) = *pStr1;

					++pStr1;
				}
				continue;
			}
			else if (Char == '\n')
			{
				*(pWrite++) = Char;
				Column = 0;
			}
			else
			{
				++Column;
				*(pWrite++) = Char;
			}

			++pStr1;
		}
		*(pWrite++) = 0;

		DMibSafeCheck((mint(pWrite - pWriteStart) <= MaxLen), "Memory overwritten");


		_Str1.f_SetModified();
		return _Str1;
	}

	/************************************************************************************************\
	||||
	|| Replace
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <typename t_CTCStrTraits, typename t_CData2, typename t_CData3>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrReplace(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace)
	{
		typedef typename TCStrAggregate<t_CTCStrTraits>::CChar CChar;
		const CChar *pStr1 = _Str1.f_GetStr();
		mint LenFind = fg_StrLen(_pStrFind);
		mint LenReplace = fg_StrLen(_pStrReplace);
		mint Len = fg_StrLen(_Str1);
		mint nReplaces = 0;

		while (const CChar *pStrFind = fg_StrAdd(pStr1, fg_StrFind(pStr1, _pStrFind)))
		{
			++nReplaces;
			pStr1 = pStrFind + LenFind;
		}

		mint NeededSize = Len;
		if (LenReplace > LenFind)
			NeededSize += nReplaces * (LenReplace - LenFind);

		fg_StrReplace(_Str1.f_GetStr(NeededSize), _pStrFind, _pStrReplace);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplace(TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const t_CData3 *_pStrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value, "Not supported");
		return fg_StrReplace(_Str1, _StrFind.f_GetStr(), _pStrReplace);
	}


	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplace(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData3 *_pStrFind, const TCStrAggregate<t_CTCStrTraits1> &_StrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value, "Not supported");
		return fg_StrReplace(_Str1, _pStrFind, _StrReplace.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplace(TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const TCStrAggregate<t_CTCStrTraits2> &_StrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value && TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplace(_Str1, _StrFind.f_GetStr(), _StrReplace.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CData2, typename t_CData3>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrReplace(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace, mint _MaxLen)
	{
		typedef typename TCStrAggregate<t_CTCStrTraits>::CChar CChar;
		const CChar *pStr1 = _Str1.f_GetStr();
		mint LenFind = fg_StrLen(_pStrFind);
		mint LenReplace = fg_StrLen(_pStrReplace);
		mint Len = fg_StrLen(_Str1);
		mint nReplaces = 0;

		while (const CChar *pStrFind = fg_StrAdd(pStr1, fg_StrFind(pStr1, _pStrFind)))
		{
			++nReplaces;
			pStr1 = pStrFind + LenFind;
		}

		mint NeededSize = fg_Min((Len + nReplaces * (LenReplace - LenFind)), _MaxLen);
		fg_StrReplace(_Str1.f_GetStr(NeededSize), _pStrFind, _pStrReplace, _MaxLen);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplace(TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const t_CData3 *_pStrReplace, mint _MaxLen)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value, "Not supported");
		return fg_StrReplace(_Str1, _StrFind.f_GetStr(), _pStrReplace, _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplace(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData3 *_pStrFind, const TCStrAggregate<t_CTCStrTraits1> &_StrReplace, mint _MaxLen)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value, "Not supported");
		return fg_StrReplace(_Str1, _pStrFind, _StrReplace.f_GetStr(), _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplace(TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const TCStrAggregate<t_CTCStrTraits2> &_StrReplace, mint _MaxLen)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value && TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplace(_Str1, _StrFind.f_GetStr(), _StrReplace.f_GetStr(), _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CData2, typename t_CData3>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceNoCase(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace)
	{
		typedef typename TCStrAggregate<t_CTCStrTraits>::CChar CChar;
		const CChar *pStr1 = _Str1.f_GetStr();
		mint LenFind = fg_StrLen(_pStrFind);
		mint LenReplace = fg_StrLen(_pStrReplace);
		mint Len = fg_StrLen(_Str1);
		mint nReplaces = 0;

		while (const CChar *pStrFind = fg_StrAdd(pStr1, fg_StrFindNoCase(pStr1, _pStrFind)))
		{
			++nReplaces;
			pStr1 = pStrFind + LenFind;
		}

		mint NeededSize = Len;
		if (LenReplace > LenFind)
			NeededSize += nReplaces * (LenReplace - LenFind);

		fg_StrReplaceNoCase(_Str1.f_GetStr(NeededSize), _pStrFind, _pStrReplace);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceNoCase(TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const t_CData3 *_pStrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str1, _StrFind.f_GetStr(), _pStrReplace);
	}


	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceNoCase(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData3 *_pStrFind, const TCStrAggregate<t_CTCStrTraits1> &_StrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str1, _pStrFind, _StrReplace.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceNoCase(TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const TCStrAggregate<t_CTCStrTraits2> &_StrReplace)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value && TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str1, _StrFind.f_GetStr(), _StrReplace.f_GetStr());
	}

	template <typename t_CTCStrTraits, typename t_CData2, typename t_CData3>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceNoCase(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pStrFind, const t_CData3 *_pStrReplace, mint _MaxLen)
	{
		typedef typename TCStrAggregate<t_CTCStrTraits>::CChar CChar;
		const CChar *pStr1 = _Str1.f_GetStr();
		mint LenFind = fg_StrLen(_pStrFind);
		mint LenReplace = fg_StrLen(_pStrReplace);
		mint Len = fg_StrLen(_Str1);
		mint nReplaces = 0;

		while (const CChar *pStrFind = fg_StrAdd(pStr1, fg_StrFindNoCase(pStr1, _pStrFind)))
		{
			++nReplaces;
			pStr1 = pStrFind + LenFind;
		}

		mint NeededSize = fg_Min((Len + nReplaces * (LenReplace - LenFind)), _MaxLen);
		fg_StrReplaceNoCase(_Str1.f_GetStr(NeededSize), _pStrFind, _pStrReplace, _MaxLen);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceNoCase(TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const t_CData3 *_pStrReplace, mint _MaxLen)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str1, _StrFind.f_GetStr(), _pStrReplace, _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceNoCase(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData3 *_pStrFind, const TCStrAggregate<t_CTCStrTraits1> &_StrReplace, mint _MaxLen)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str1, _pStrFind, _StrReplace.f_GetStr(), _MaxLen);
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits1, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceNoCase(TCStrAggregate<t_CTCStrTraits> &_Str1, const TCStrAggregate<t_CTCStrTraits1> &_StrFind, const TCStrAggregate<t_CTCStrTraits2> &_StrReplace, mint _MaxLen)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits1>::mc_Value && TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		return fg_StrReplaceNoCase(_Str1, _StrFind.f_GetStr(), _StrReplace.f_GetStr(), _MaxLen);
	}


	template <typename t_CTCStrTraits, typename t_CData2, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceChar(TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _CharFind, t_CData3 _CharReplace)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1)
			return _Str1;

		fg_StrReplaceChar(pStr1, _CharFind, _CharReplace);
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CData2, typename t_CData3>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrReplaceChar(TCStrAggregate<t_CTCStrTraits> &_Str1, t_CData2 _CharFind, t_CData3 _CharReplace, mint _MaxLen)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1)
			return _Str1;
		fg_StrReplaceChar(pStr1, _CharFind, _CharReplace, _MaxLen);
		return _Str1;
	}

	/************************************************************************************************\
	||||
	|| Insert
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <typename t_CTCStrTraits, typename t_CData3>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrInsert(TCStrAggregate<t_CTCStrTraits> &_Str1, aint _StartChar, const t_CData3 *_pStrInsert)
	{
		mint NeededSize = fg_StrLen(_Str1) + fg_StrLen(_pStrInsert);;
		fg_StrInsert(_Str1.f_GetStr(NeededSize), _StartChar, _pStrInsert);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrInsert(TCStrAggregate<t_CTCStrTraits> &_Str1, aint _StartChar, const TCStrAggregate<t_CTCStrTraits2> &_StrInsert)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		mint NeededSize = fg_StrLen(_Str1) + fg_StrLen(_StrInsert);;
		fg_StrInsert(_Str1.f_GetStr(NeededSize), _StartChar, _StrInsert.f_GetStr());
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CData3>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrInsert(TCStrAggregate<t_CTCStrTraits> &_Str1, aint _StartChar, const t_CData3 *_pStrInsert, mint _MaxLen)
	{
		mint NeededSize = fg_Min(fg_StrLen(_Str1) + fg_StrLen(_pStrInsert), _MaxLen);
		fg_StrInsert(_Str1.f_GetStr(NeededSize), _StartChar, _pStrInsert, _MaxLen);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CTCStrTraits2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrInsert(TCStrAggregate<t_CTCStrTraits> &_Str1, aint _StartChar, const TCStrAggregate<t_CTCStrTraits2> &_StrInsert, mint _MaxLen)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits, t_CTCStrTraits2>::mc_Value, "Not supported");
		mint NeededSize = fg_Min(fg_StrLen(_Str1) + fg_StrLen(_StrInsert), _MaxLen);
		fg_StrInsert(_Str1.f_GetStr(NeededSize), _StartChar, _StrInsert.f_GetStr(), _MaxLen);
		_Str1.f_SetModified();
		return _Str1;
	}

	/***************************************************************************************************\
	||
	| Shortening
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrDelete(TCStrAggregate<t_CTCStrTraits> &_Str1, aint _StartChar, mint _nChars)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;

		fg_StrDelete(pStr1, _StartChar, _nChars);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrLeft(TCStrAggregate<t_CTCStrTraits> &_Str1, mint _nChars)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrLeft(pStr1, _nChars);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrExtract(TCStrAggregate<t_CTCStrTraits> &_Str1, aint _StartChar, mint _nChars)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrExtract(pStr1, _StartChar, _nChars);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrExtract(TCStrAggregate<t_CTCStrTraits> &_Str1, aint _StartChar)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrExtract(pStr1, _StartChar);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrReverse(TCStrAggregate<t_CTCStrTraits> &_Str1)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrReverse(pStr1);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrRight(TCStrAggregate<t_CTCStrTraits> &_Str1, mint _nChars)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrRight(pStr1, _nChars);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrTrimLeft(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pCharsToTrim)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrTrimLeft(pStr1, _pCharsToTrim);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrTrimLeft(TCStrAggregate<t_CTCStrTraits> &_Str1)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrTrimLeft(pStr1, g_lWhiteSpaceChars);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrTrimRight(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pCharsToTrim)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrTrimRight(pStr1, _pCharsToTrim);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrTrimRight(TCStrAggregate<t_CTCStrTraits> &_Str1)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrTrimRight(pStr1, g_lWhiteSpaceChars);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrTrim(TCStrAggregate<t_CTCStrTraits> &_Str1, const t_CData2 *_pCharsToTrim)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrTrim(pStr1, _pCharsToTrim);
		_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits>
		inline_large TCStrAggregate<t_CTCStrTraits> &fg_StrTrim(TCStrAggregate<t_CTCStrTraits> &_Str1)
	{
		typename TCStrAggregate<t_CTCStrTraits>::CChar *pStr1 = _Str1.f_GetStrUniqueWritable();
		if (!pStr1 || !*pStr1)
			return _Str1;
		fg_StrTrim(pStr1, g_lWhiteSpaceChars);
		_Str1.f_SetModified();
		return _Str1;
	}


	/***************************************************************************************************\
	||
	| Misc
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	template <typename t_CTCStrTraits>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrClear(TCStrAggregate<t_CTCStrTraits> &_Str1)
	{
		_Str1.f_Clear();
		return _Str1;
	}

	template <typename t_CTCStrTraits, typename t_CData2>
		inline_small TCStrAggregate<t_CTCStrTraits> &fg_StrSetAt(TCStrAggregate<t_CTCStrTraits> &_Str1, aint _Index, t_CData2 _Character)
	{
		_Str1.f_MakeUnique();
		int MaxLen = _Str1.f_CreateWritableBuffer(_Index + 1, false);
		if (_Index >= MaxLen)
			return _Str1;

		((typename TCStrAggregate<t_CTCStrTraits>::CUnsignedChar *)_Str1.f_GetStrWritable())[_Index] = (typename TCStrAggregate<t_CTCStrTraits>::CUnsignedChar)(typename NTraits::TCUnsigned<t_CData2>::CType)(_Character);
		if (_Character == 0)
			_Str1.f_SetModified();
		return _Str1;
	}

	template <typename t_CTCStrTraits0, typename t_CTCStrTraits1>
		inline_small TCStrAggregate<t_CTCStrTraits0> &fg_StrEscapeStr(TCStrAggregate<t_CTCStrTraits0> &_StrDest, const TCStrAggregate<t_CTCStrTraits1> &_StrSource)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits0, t_CTCStrTraits1>::mc_Value, "Not supported");
		typedef typename NTraits::TCUnsigned<typename t_CTCStrTraits1::CStrTraits::CChar>::CType CUnsignedChar;
		const CUnsignedChar *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		const CUnsignedChar *pParse = (CUnsignedChar const *)pSource;
		mint NeededSize = 3;
		while (*pParse)
		{
			if (*pParse == '\"' || *pParse == '\\')
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename t_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStr(pDest, pSource, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template <typename t_CTCStrTraits0, typename t_CTCStrTraits1, typename t_CEscapeChar>
		inline_small TCStrAggregate<t_CTCStrTraits0> &fg_StrEscapeStr(TCStrAggregate<t_CTCStrTraits0> &_StrDest, const TCStrAggregate<t_CTCStrTraits1> &_StrSource, const t_CEscapeChar *_pEscapedChars)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits0, t_CTCStrTraits1>::mc_Value, "Not supported");
		typedef typename NTraits::TCUnsigned<typename t_CTCStrTraits1::CStrTraits::CChar>::CType CUnsignedChar;
		typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CUnsignedEscapeChar;
		const CUnsignedChar *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		const CUnsignedChar *pParse = (CUnsignedChar const *)pSource;
		mint NeededSize = 3;
		while (*pParse)
		{
			const CUnsignedEscapeChar *pEscape = (const CUnsignedEscapeChar *)_pEscapedChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename t_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStr(pDest, pSource, _pEscapedChars, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template <typename t_CTCStrTraits0, typename t_CTCStrTraits1, typename t_CEscapeChar, typename t_CReplaceChars>
		inline_small TCStrAggregate<t_CTCStrTraits0> &fg_StrEscapeStr(TCStrAggregate<t_CTCStrTraits0> &_StrDest, const TCStrAggregate<t_CTCStrTraits1> &_StrSource, const t_CEscapeChar *_pEscapedChars, const t_CReplaceChars *_pReplaceChars)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits0, t_CTCStrTraits1>::mc_Value, "Not supported");
		typedef typename NTraits::TCUnsigned<typename t_CTCStrTraits1::CStrTraits::CChar>::CType CUnsignedChar;
		typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CUnsignedEscapeChar;
		const CUnsignedChar *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		const CUnsignedChar *pParse = (CUnsignedChar const *)pSource;
		mint NeededSize = 3;
		while (*pParse)
		{
			const CUnsignedEscapeChar *pEscape = (const CUnsignedEscapeChar *)_pEscapedChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename t_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStr(pDest, pSource, _pEscapedChars, _pReplaceChars, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template<typename t_CTCStrTraits0, typename t_CTCStrTraits1>
		inline_small TCStrAggregate<t_CTCStrTraits0> &fg_StrEscapeStrNoQuotes(TCStrAggregate<t_CTCStrTraits0> &_StrDest, const TCStrAggregate<t_CTCStrTraits1> &_StrSource)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits0, t_CTCStrTraits1>::mc_Value, "Not supported");
		typedef typename NTraits::TCUnsigned<typename t_CTCStrTraits1::CStrTraits::CChar>::CType CUnsignedChar;
		const CUnsignedChar *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		const CUnsignedChar *pParse = (CUnsignedChar const *)pSource;
		mint NeededSize = 1;
		while (*pParse)
		{
			if (*pParse == '\"' || *pParse == '\\')
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename t_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStrNoQuotes(pDest, pSource, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template<typename t_CTCStrTraits0, typename t_CTCStrTraits1, typename t_CEscapeChar>
		inline_small TCStrAggregate<t_CTCStrTraits0> &fg_StrEscapeStrNoQuotes(TCStrAggregate<t_CTCStrTraits0> &_StrDest, const TCStrAggregate<t_CTCStrTraits1> &_StrSource, const t_CEscapeChar *_pEscapedChars)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits0, t_CTCStrTraits1>::mc_Value, "Not supported");
		typedef typename NTraits::TCUnsigned<typename t_CTCStrTraits1::CStrTraits::CChar>::CType CUnsignedChar;
		typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CUnsignedEscapeChar;
		const CUnsignedChar *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		const CUnsignedChar *pParse = (CUnsignedChar const *)pSource;
		mint NeededSize = 1;
		while (*pParse)
		{
			const CUnsignedEscapeChar *pEscape = (const CUnsignedEscapeChar *)_pEscapedChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename t_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStrNoQuotes(pDest, pSource, _pEscapedChars, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	template<typename t_CTCStrTraits0, typename t_CTCStrTraits1, typename t_CEscapeChar, typename t_CReplaceChars>
		inline_small TCStrAggregate<t_CTCStrTraits0> &fg_StrEscapeStrNoQuotes(TCStrAggregate<t_CTCStrTraits0> &_StrDest, const TCStrAggregate<t_CTCStrTraits1> &_StrSource, const t_CEscapeChar *_pEscapedChars, const t_CReplaceChars *_pReplaceChars)
	{
		static_assert(TCIsStrCompatibleWrite<t_CTCStrTraits0, t_CTCStrTraits1>::mc_Value, "Not supported");
		typedef typename NTraits::TCUnsigned<typename t_CTCStrTraits1::CStrTraits::CChar>::CType CUnsignedChar;
		typedef typename NTraits::TCUnsigned<t_CEscapeChar>::CType CUnsignedEscapeChar;
		const CUnsignedChar *pSource = (CUnsignedChar const *)_StrSource.f_GetStr();
		const CUnsignedChar *pParse = (CUnsignedChar const *)pSource;
		mint NeededSize = 1;
		while (*pParse)
		{
			const CUnsignedEscapeChar *pEscape = (const CUnsignedEscapeChar *)_pEscapedChars;
			while (*pEscape)
			{
				if (*pParse == *pEscape)
					break;
				++pEscape;
			}
			if (*pEscape)
				NeededSize += 2;
			else
				++NeededSize;

			++pParse;
		}

		aint Max = _StrDest.f_CreateWritableBuffer(NeededSize, true);
		typename t_CTCStrTraits0::CStrTraits::CChar *pDest = _StrDest.f_GetStrWritable();
		fg_StrEscapeStrNoQuotes(pDest, pSource, _pEscapedChars, _pReplaceChars, Max);
		_StrDest.f_SetStrLen(-1);
		return _StrDest;
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	|| Formatting function
	||________________________________________________________________________________________________
	\************************************************************************************************/

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
