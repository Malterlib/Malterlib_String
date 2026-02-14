// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	template <typename t_CParser, typename t_CIntType>
	struct TCStrParseType_Int final : public TICStrParseType<t_CParser>
	{
		using CTStrTraits = typename t_CParser::CStrTraits;
		using CChar = typename CTStrTraits::CChar;
		using CSuper = TICStrParseType<t_CParser>;
		using COption = typename CSuper::COption;
		using COptions = typename CSuper::COptions;

		class COptionsInt : public COptions
		{
		public:
			enum ENumberFormat
			{
				ENumberFormat_Base16 = 16
				, ENumberFormat_Base10 = 10
				, ENumberFormat_Base8 = 8
				, ENumberFormat_Base2 = 2
			};

			aint m_NumberFormat = -1;
		};

		inline_small TCStrParseType_Int(t_CIntType &_Value);
		TCStrParseType_Int(TCStrParseType_Int const &_Value) = delete;
		TCStrParseType_Int &operator = (TCStrParseType_Int const &_Value) = delete;

		virtual mint f_Destruct() override;
		virtual bool f_ParseData(const CChar *&_pString, const CChar *_pFormat, const t_CParser & _ArgData) const override;
		virtual aint f_Get_aint() const override;
		virtual fp32 f_Get_fp32() const override;
		virtual fp64 f_Get_fp64() const override;

		template <typename tf_COptions>
		inline_small aint f_ParseOption(COption &_Option, tf_COptions &_Options, const t_CParser & _ArgData) const;

		constexpr static bool mc_bNeedDestruct = false;

	private:
		t_CIntType &mp_Value;
	};
}

#include "Container/Malterlib_String_Container_Parse_Integer.hpp"

DMibStrStringParserImplementInt(uint8);
DMibStrStringParserImplementInt(int8);
DMibStrStringParserImplementInt(uint16);
DMibStrStringParserImplementInt(int16);
DMibStrStringParserImplementInt(uint32);
DMibStrStringParserImplementInt(int32);
DMibStrStringParserImplementInt(uint64);
DMibStrStringParserImplementInt(int64);
DMibStrStringParserImplementInt(uint80);
DMibStrStringParserImplementInt(int80);
DMibStrStringParserImplementInt(uint96);
DMibStrStringParserImplementInt(int96);
DMibStrStringParserImplementInt(uint128);
DMibStrStringParserImplementInt(int128);
DMibStrStringParserImplementInt(uint160);
DMibStrStringParserImplementInt(int160);
DMibStrStringParserImplementInt(uint192);
DMibStrStringParserImplementInt(int192);
DMibStrStringParserImplementInt(uint256);
DMibStrStringParserImplementInt(int256);
DMibStrStringParserImplementInt(uint320);
DMibStrStringParserImplementInt(int320);
DMibStrStringParserImplementInt(uint384);
DMibStrStringParserImplementInt(int384);
DMibStrStringParserImplementInt(uint512);
DMibStrStringParserImplementInt(int512);
DMibStrStringParserImplementInt(uint1024);
DMibStrStringParserImplementInt(int1024);
DMibStrStringParserImplementInt(uint2048);
DMibStrStringParserImplementInt(int2048);
DMibStrStringParserImplementInt(uint4096);
DMibStrStringParserImplementInt(int4096);
DMibStrStringParserImplementInt(uint8192);
DMibStrStringParserImplementInt(int8192);
DMibStrStringParserImplementInt(uint16384);
DMibStrStringParserImplementInt(int16384);

#ifdef DMibPUniqueType_mint
DMibStrStringParserImplementInt(mint);
#endif
#ifdef DMibPUniqueType_smint
DMibStrStringParserImplementInt(smint);
#endif
#ifdef DMibPUniqueType_int
DMibStrStringParserImplementInt(int);
#endif
#ifdef DMibPUniqueType_uint
DMibStrStringParserImplementInt(unsigned int);
#endif
#ifdef DMibPUniqueType_aint
DMibStrStringParserImplementInt(aint);
#endif

#ifdef DMibPUniqueType_uaint
DMibStrStringParserImplementInt(uaint);
#endif

#ifdef DMibPUniqueType_ch8
DMibStrStringParserImplementInt(ch8);
#endif
#ifdef DMibPUniqueType_ch16
DMibStrStringParserImplementInt(ch16);
#endif
#ifdef DMibPUniqueType_ch32
DMibStrStringParserImplementInt(ch32);
#endif
