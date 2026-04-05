// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NStr
{
	using CStrTypeUnderlying = int32;

	enum EStrType : int32
	{
		EStrType_Ansi,
		EStrType_Unicode,
		EStrType_UTF,
		EStrType_Undefined,
	};

	enum EParseFlag
	{
		EParseFlag_None		= 0,
		EParseFlag_NoCase	= DMibBit(0),
		EParseFlag_ExtendedWhitespace = DMibBit(1),	// Whitespace in the format will match zero or more consecutive whitespace characters in the source.
	};

	template <typename t_CChar, CStrTypeUnderlying t_Type>
	struct TCStrTraitsTypes;

	template <typename t_CCharType, CStrTypeUnderlying t_Type, template <typename> class t_TImpl, typename t_CParams>
	struct TCStrTraits_Eval
	{
		using CType = TCTCStrTraits<TCStrTraits<t_CCharType, t_Type, t_CParams>, t_TImpl<TCStrTraits<t_CCharType , t_Type, t_CParams>>>;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_DesiredType, CStrTypeUnderlying t_Type, class t_CImpl, typename t_CParams>
	struct TCStrTraits_ReplaceParams;

	template <typename t_CCharType, CStrTypeUnderlying t_DesiredType, CStrTypeUnderlying t_Type, template <typename> class t_TImpl, typename t_CParams, typename t_CCharType2, typename t_CParams2>
	struct TCStrTraits_ReplaceParams<t_CCharType, t_DesiredType, t_Type, t_TImpl<TCStrTraits<t_CCharType2, t_Type, t_CParams2>>, t_CParams>
	{
		using CType = TCTCStrTraits<TCStrTraits<t_CCharType, t_DesiredType, t_CParams>, t_TImpl<TCStrTraits<t_CCharType, t_DesiredType, t_CParams>>>;
	};

	struct CStrTraits_CStr : public TCStrTraits_Eval<ch8, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsDeflauts>::CType {};
	struct CStrTraits_CStrAnsi : public TCStrTraits_Eval<ch8, EStrType_Ansi, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsDeflauts>::CType {};
	struct CStrTraits_CWStr : public TCStrTraits_Eval<ch16, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsDeflauts>::CType {};
	struct CStrTraits_CUStr : public TCStrTraits_Eval<ch32, EStrType_Unicode, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsDeflauts>::CType {};

	struct CStrTraits_CStrNonTracked : public TCStrTraits_Eval<ch8, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsNonTracked>::CType {};
	struct CStrTraits_CStrAnsiNonTracked : public TCStrTraits_Eval<ch8, EStrType_Ansi, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsNonTracked>::CType {};
	struct CStrTraits_CWStrNonTracked : public TCStrTraits_Eval<ch16, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsNonTracked>::CType {};
	struct CStrTraits_CUStrNonTracked : public TCStrTraits_Eval<ch32, EStrType_Unicode, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsNonTracked>::CType {};

	struct CStrTraits_CStrSecure : public TCStrTraits_Eval<ch8, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsSecure>::CType {};
	struct CStrTraits_CWStrSecure : public TCStrTraits_Eval<ch16, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsSecure>::CType {};
	struct CStrTraits_CUStrSecure : public TCStrTraits_Eval<ch32, EStrType_Unicode, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsSecure>::CType {};

	template <typename t_CCharType, CStrTypeUnderlying t_Type>
	struct TCStrTraits_ReplaceParams<ch32, EStrType_Unicode, t_Type, TCStrImp_Dynamic<TCStrTraits<t_CCharType, t_Type, CStrImp_Dynamic_ParamsDeflauts>>, CStrImp_Dynamic_ParamsDeflauts>
	{
		using CType = CStrTraits_CUStr;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_Type>
	struct TCStrTraits_ReplaceParams<ch32, EStrType_Unicode, t_Type, TCStrImp_Dynamic<TCStrTraits<t_CCharType, t_Type, CStrImp_Dynamic_ParamsNonTracked>>, CStrImp_Dynamic_ParamsNonTracked>
	{
		using CType = CStrTraits_CUStrNonTracked;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_Type>
	struct TCStrTraits_ReplaceParams<ch32, EStrType_Unicode, t_Type, TCStrImp_Dynamic<TCStrTraits<t_CCharType, t_Type, CStrImp_Dynamic_ParamsSecure>>, CStrImp_Dynamic_ParamsSecure>
	{
		using CType = CStrTraits_CUStrSecure;
	};

	using CStrSpan = TCStrSpan<TCStrTraitsTypes<ch8, EStrType_UTF>>;
	using CAnsiStrSpan = TCStrSpan<TCStrTraitsTypes<ch8, EStrType_Ansi>>;
	using CWStrSpan = TCStrSpan<TCStrTraitsTypes<ch16, EStrType_UTF>>;
	using CUStrSpan = TCStrSpan<TCStrTraitsTypes<ch32, EStrType_Unicode>>;

	using CStr = TCStr<CStrTraits_CStr>;
	using CAnsiStr = TCStr<CStrTraits_CStrAnsi>;
	using CWStr = TCStr<CStrTraits_CWStr>;
	using CUStr = TCStr<CStrTraits_CUStr>;

	using CStrNonTracked = TCStr<CStrTraits_CStrNonTracked>;
	using CAnsiStrNonTracked = TCStr<CStrTraits_CStrAnsiNonTracked>;
	using CWStrNonTracked = TCStr<CStrTraits_CWStrNonTracked>;
	using CUStrNonTracked = TCStr<CStrTraits_CUStrNonTracked>;

	using CStrSecure = TCStr<CStrTraits_CStrSecure>;
	using CWStrSecure = TCStr<CStrTraits_CWStrSecure>;
	using CUStrSecure = TCStr<CStrTraits_CUStrSecure>;

#ifdef DMibSecureClearIOBuffers_Enable
	using CStrIO = CStrSecure;
	using CWStrIO = CWStrSecure;
	using CUStrIO = CUStrSecure;
#else
	using CStrIO = CStr;
	using CWStrIO = CWStr;
	using CUStrIO = CUStr;
#endif

	struct CDefaultStrParams
	{
		using CAllocator = NMemory::CDefaultAllocator;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_Type>
	struct TCStrTraitsPtr
	{
		using CType = TCTCStrTraits<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>, TCStrImp_Ptr<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>>>;
	};

	struct CStrTraitsPtr_CStr : public TCStrTraitsPtr<ch8, EStrType_UTF>::CType {};
	struct CStrTraitsPtr_CWStr : public TCStrTraitsPtr<ch16, EStrType_UTF>::CType {};
	struct CStrTraitsPtr_CUStr : public TCStrTraitsPtr<ch32, EStrType_Unicode>::CType {};

	using CStrPtr = TCStr<CStrTraitsPtr_CStr>;
	using CWStrPtr = TCStr<CStrTraitsPtr_CWStr>;
	using CUStrPtr = TCStr<CStrTraitsPtr_CUStr>;

	template <typename t_CCharType>
	struct TCStrPtrFromCharType
	{
	};

	template <>
	struct TCStrPtrFromCharType<ch8>
	{
		using CType = CStrPtr;
	};
	template <>
	struct TCStrPtrFromCharType<ch16>
	{
		using CType = CWStrPtr;
	};
	template <>
	struct TCStrPtrFromCharType<ch32>
	{
		using CType = CUStrPtr;
	};

	struct CStrTraits_CStrVMem : public TCStrTraits_Eval<ch8, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsVirtual>::CType {};
	struct CStrTraits_CWStrVMem : public TCStrTraits_Eval<ch16, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsVirtual>::CType {};
	struct CStrTraits_CUStrVMem : public TCStrTraits_Eval<ch32, EStrType_Unicode, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsVirtual>::CType {};

	using CStrVMem = TCStr<CStrTraits_CStrVMem>;
	using CWStrVMem = TCStr<CStrTraits_CWStrVMem>;
	using CUStrVMem = TCStr<CStrTraits_CUStrVMem>;
	using CStrVp = TCStrImp_Virtual_PtrWrapper<CStrTraits_CStr>;
	using CWStrVp = TCStrImp_Virtual_PtrWrapper<CStrTraits_CWStr>;
	using CUStrVp = TCStrImp_Virtual_PtrWrapper<CStrTraits_CUStr>;
	using CStrV = TCStrImp_Virtual_TStrWrapper<CStrTraits_CStr>;
	using CWStrV = TCStrImp_Virtual_TStrWrapper<CStrTraits_CWStr>;
	using CUStrV = TCStrImp_Virtual_TStrWrapper<CStrTraits_CUStr>;

	template <typename t_CCharType, aint t_NumChar, CStrTypeUnderlying t_Type>
	struct TCFStr
	{
		using CType = TCStr<TCTCStrTraits<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>, TCStrImp_Fixed<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>, t_NumChar>>>;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_DesiredType, CStrTypeUnderlying t_Type, template <typename, aint t_DataLen> class t_TImpl, typename t_CParams, typename t_CCharType2, typename t_CParams2, aint t_DataLen>
	struct TCStrTraits_ReplaceParams<t_CCharType, t_DesiredType, t_Type, t_TImpl<TCStrTraits<t_CCharType2, t_Type, t_CParams2>, t_DataLen>, t_CParams>
	{
		using CType = TCTCStrTraits<TCStrTraits<t_CCharType, t_DesiredType, t_CParams>, t_TImpl<TCStrTraits<t_CCharType, t_DesiredType, t_CParams>, t_DataLen>>;
	};

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| 8 bit																								|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	using CFStr16 = TCFStr<ch8, 16, EStrType_UTF>::CType;
	using CFStr16V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 16, EStrType_UTF>::CType>;
	using CFStr16Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 16, EStrType_UTF>::CType>;

	using CFStr24 = TCFStr<ch8, 24, EStrType_UTF>::CType;
	using CFStr24V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 24, EStrType_UTF>::CType>;
	using CFStr24Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 24, EStrType_UTF>::CType>;

	using CFStr32 = TCFStr<ch8, 32, EStrType_UTF>::CType;
	using CFStr32V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 32, EStrType_UTF>::CType >;
	using CFStr32Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 32, EStrType_UTF>::CType>;

	using CFStr64 = TCFStr<ch8, 64, EStrType_UTF>::CType;
	using CFStr64V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 64, EStrType_UTF>::CType >;
	using CFStr64Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 64, EStrType_UTF>::CType>;

	using CFStr128 = TCFStr<ch8, 128, EStrType_UTF>::CType;
	using CFStr128V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 128, EStrType_UTF>::CType >;
	using CFStr128Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 128, EStrType_UTF>::CType>;

	using CFStr256 = TCFStr<ch8, 256, EStrType_UTF>::CType;
	using CFStr256V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 256, EStrType_UTF>::CType >;
	using CFStr256Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 256, EStrType_UTF>::CType>;

	using CFStr512 = TCFStr<ch8, 512, EStrType_UTF>::CType;
	using CFStr512V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 512, EStrType_UTF>::CType >;
	using CFStr512Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 512, EStrType_UTF>::CType>;

	using CFStr1024 = TCFStr<ch8, 1024, EStrType_UTF>::CType;
	using CFStr1024V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 1024, EStrType_UTF>::CType >;
	using CFStr1024Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 1024, EStrType_UTF>::CType>;

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| 16 bit																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	using CFWStr16 = TCFStr<ch16, 16, EStrType_UTF>::CType;
	using CFWStr16V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 16, EStrType_UTF>::CType >;
	using CFWStr16Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 16, EStrType_UTF>::CType>;

	using CFWStr24 = TCFStr<ch16, 24, EStrType_UTF>::CType;
	using CFWStr24V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 24, EStrType_UTF>::CType >;
	using CFWStr24Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 24, EStrType_UTF>::CType>;

	using CFWStr32 = TCFStr<ch16, 32, EStrType_UTF>::CType;
	using CFWStr32V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 32, EStrType_UTF>::CType >;
	using CFWStr32Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 32, EStrType_UTF>::CType>;

	using CFWStr64 = TCFStr<ch16, 64, EStrType_UTF>::CType;
	using CFWStr64V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 64, EStrType_UTF>::CType >;
	using CFWStr64Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 64, EStrType_UTF>::CType>;

	using CFWStr128 = TCFStr<ch16, 128, EStrType_UTF>::CType;
	using CFWStr128V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 128, EStrType_UTF>::CType >;
	using CFWStr128Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 128, EStrType_UTF>::CType>;

	using CFWStr256 = TCFStr<ch16, 256, EStrType_UTF>::CType;
	using CFWStr256V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 256, EStrType_UTF>::CType >;
	using CFWStr256Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 256, EStrType_UTF>::CType>;

	using CFWStr512 = TCFStr<ch16, 512, EStrType_UTF>::CType;
	using CFWStr512V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 512, EStrType_UTF>::CType >;
	using CFWStr512Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 512, EStrType_UTF>::CType>;

	using CFWStr1024 = TCFStr<ch16, 1024, EStrType_UTF>::CType;
	using CFWStr1024V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 1024, EStrType_UTF>::CType >;
	using CFWStr1024Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 1024, EStrType_UTF>::CType>;

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| 32 bit																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	using CFUStr16 = TCFStr<ch32, 16, EStrType_Unicode>::CType;
	using CFUStr16V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 16, EStrType_Unicode>::CType >;
	using CFUStr16Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 16, EStrType_Unicode>::CType>;

	using CFUStr24 = TCFStr<ch32, 24, EStrType_Unicode>::CType;
	using CFUStr24V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 24, EStrType_Unicode>::CType >;
	using CFUStr24Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 24, EStrType_Unicode>::CType>;

	using CFUStr32 = TCFStr<ch32, 32, EStrType_Unicode>::CType;
	using CFUStr32V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 32, EStrType_Unicode>::CType >;
	using CFUStr32Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 32, EStrType_Unicode>::CType>;

	using CFUStr64 = TCFStr<ch32, 64, EStrType_Unicode>::CType;
	using CFUStr64V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 64, EStrType_Unicode>::CType >;
	using CFUStr64Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 64, EStrType_Unicode>::CType>;

	using CFUStr128 = TCFStr<ch32, 128, EStrType_Unicode>::CType;
	using CFUStr128V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 128, EStrType_Unicode>::CType >;
	using CFUStr128Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 128, EStrType_Unicode>::CType>;

	using CFUStr256 = TCFStr<ch32, 256, EStrType_Unicode>::CType;
	using CFUStr256V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 256, EStrType_Unicode>::CType >;
	using CFUStr256Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 256, EStrType_Unicode>::CType>;

	using CFUStr512 = TCFStr<ch32, 512, EStrType_Unicode>::CType;
	using CFUStr512V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 512, EStrType_Unicode>::CType >;
	using CFUStr512Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 512, EStrType_Unicode>::CType>;

	using CFUStr1024 = TCFStr<ch32, 1024, EStrType_Unicode>::CType;
	using CFUStr1024V = TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 1024, EStrType_Unicode>::CType >;
	using CFUStr1024Vp = TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 1024, EStrType_Unicode>::CType>;

#ifdef DMibDebug
	extern CWStr g_DebugOutputTemp16;
	extern CStr g_DebugOutputTemp8;
#endif
}
