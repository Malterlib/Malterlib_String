// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CData>
	struct TCStringParser
	{
		static void f_CreateParse(t_CParser const &_Parse, t_CData &_Data);
	};

	enum class EStringParseTypeFlag : uint8
	{
		mc_None = 0
		, mc_NeedDestruct = fg_Bit(0)
		, mc_NeedDealloc = fg_Bit(1)
	};

	template <typename t_CParser>
	struct TICStrParseType
	{
		using CStrTraits = typename t_CParser::CStrTraits;
		using CChar = typename CStrTraits::CChar;
		struct COption
		{
			struct CParseTypes
			{
				ch32 m_Parse1;
				ch32 m_Parse2;
			};

			void f_GetData_Str(t_CParser const &_ArgData, CChar *_pDestStr, aint _MaxChars) const;
			aint f_GetData_aint(t_CParser const &_ArgData, aint _FailValue) const;
			aint f_GetData_aint_NotSigned(t_CParser const &_ArgData, aint _FailValue) const;
			fp32 f_GetData_fp32(t_CParser const &_ArgData, fp32 _FailValue) const;
			fp64 f_GetData_fp64(t_CParser const &_ArgData, fp64 _FailValue) const;

			CChar const *m_pDataStart;
			CParseTypes m_ParseTypes;
		};

		struct COptions
		{
			COptions() = default;
		};

		TICStrParseType const *f_GetPtr() const;

		virtual umint f_Destruct() = 0;
		virtual aint f_Get_aint() const = 0;
		virtual fp32 f_Get_fp32() const = 0;
		virtual fp64 f_Get_fp64() const = 0;
		virtual aint f_Get_Str(CChar *_pStr, aint _MaxChars) const;
		virtual bool f_ParseData(CChar const * &_pString, CChar const *_pFormat, t_CParser const &_ArgData) const = 0;

		inline_small CChar const *fp_GetNextParse(COption &_NewParse, CChar const * &_pParse) const;

		template <typename t_CParseType, typename t_COptions>
		inline_small static CChar const *fs_ParseOptions(t_CParseType const &_Parser, t_COptions &_Options, CChar const *_pParse, t_CParser const &_ArgData);

		template <typename t_COptions>
		inline_small aint f_ParseOption(COption &_Option, t_COptions &_Options, t_CParser const &_ArgData) const;

		TICStrParseType *m_pNextParse;
	};

	template <typename t_CStrTraits>
	struct TCStrParse
	{
		using CChar = typename t_CStrTraits::CChar;
		using CStrTraits = t_CStrTraits;

		inline_medium const TICStrParseType<TCStrParse> * f_GetArg(aint _iArgument) const;
		inline_medium TCStrParse(CChar const *_pParseStr);

		~TCStrParse();

		void fp_AddParse(TICStrParseType<TCStrParse> *_pParse, EStringParseTypeFlag _Flags);
		inline_medium void *f_AllocSpace(umint _Size, EStringParseTypeFlag &_Flags);
		inline_small CChar const *f_Parse(CChar const *_pToParse, aint &_nParsed, EParseFlag _ParseFlags = EParseFlag_None);
		inline_small CChar const *f_Parse(CChar const *_pToParse, EParseFlag _ParseFlags = EParseFlag_None);

		static CChar const *fs_ParseArgList(CChar const *_pFormat, CChar const *_pParse, TCStrParse const &_DataArgs, EParseFlag _ParseFlags, aint &_nParsed);

		template <typename t_CType>
		inline_small TCStrParse &operator >> (t_CType &_Type);

	private:
		inline_small TICStrParseType<TCStrParse> **fp_GetParseList();
		inline_small TICStrParseType<TCStrParse> const **fp_GetParseList() const;
		inline_small TICStrParseType<TCStrParse> *fp_GetParseEntry(aint _iEntry);
		inline_small TICStrParseType<TCStrParse> const *fp_GetParseEntry(aint _iEntry) const;
		void *fp_AllocSpace(int _Bytes);

		static constexpr umint mcp_StaticParses = 16;
		static constexpr umint mcp_StaticSpace = mcp_StaticParses * 4;

		uaint m_nParses;
		mutable aint m_iCurrentArgument;
		TICStrParseType<TCStrParse> **m_pParses;
		CChar const *m_pParseStr;

		TICStrParseType<TCStrParse> *m_plParses[mcp_StaticParses];
		NContainer::TCVector<TICStrParseType<TCStrParse> *> m_lParses;

		aint m_AllocSpace[mcp_StaticSpace];
		int m_iCurrentAlloc;
	};
}
