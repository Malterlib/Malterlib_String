// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

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


	template <typename t_CCharType, CStrTypeUnderlying t_Type, template <typename> class t_TImpl, typename t_CParams>
	struct TCStrTraits_Eval
	{
		typedef TCTCStrTraits<TCStrTraits<t_CCharType, t_Type, t_CParams>, t_TImpl<TCStrTraits<t_CCharType , t_Type, t_CParams>>> CType;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_DesiredType, CStrTypeUnderlying t_Type, class t_CImpl, typename t_CParams>
	struct TCStrTraits_ReplaceParams;

	template <typename t_CCharType, CStrTypeUnderlying t_DesiredType, CStrTypeUnderlying t_Type, template <typename> class t_TImpl, typename t_CParams, typename t_CCharType2, typename t_CParams2>
	struct TCStrTraits_ReplaceParams<t_CCharType, t_DesiredType, t_Type, t_TImpl<TCStrTraits<t_CCharType2, t_Type, t_CParams2>>, t_CParams>
	{
		typedef TCTCStrTraits<TCStrTraits<t_CCharType, t_DesiredType, t_CParams>, t_TImpl<TCStrTraits<t_CCharType, t_DesiredType, t_CParams>>> CType;
	};

	class CStrTraits_CStr : public TCStrTraits_Eval<ch8, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsDeflauts>::CType {};
	class CStrTraits_CStrAnsi : public TCStrTraits_Eval<ch8, EStrType_Ansi, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsDeflauts>::CType {};
	class CStrTraits_CWStr : public TCStrTraits_Eval<ch16, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsDeflauts>::CType {};
	class CStrTraits_CUStr : public TCStrTraits_Eval<ch32, EStrType_Unicode, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsDeflauts>::CType {};

	class CStrTraits_CStrNonTracked : public TCStrTraits_Eval<ch8, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsNonTracked>::CType {};
	class CStrTraits_CStrAnsiNonTracked : public TCStrTraits_Eval<ch8, EStrType_Ansi, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsNonTracked>::CType {};
	class CStrTraits_CWStrNonTracked : public TCStrTraits_Eval<ch16, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsNonTracked>::CType {};
	class CStrTraits_CUStrNonTracked : public TCStrTraits_Eval<ch32, EStrType_Unicode, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsNonTracked>::CType {};

	class CStrTraits_CStrSecure : public TCStrTraits_Eval<ch8, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsSecure>::CType {};
	class CStrTraits_CWStrSecure : public TCStrTraits_Eval<ch16, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsSecure>::CType {};
	class CStrTraits_CUStrSecure : public TCStrTraits_Eval<ch32, EStrType_Unicode, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsSecure>::CType {};

	template <typename t_CCharType, CStrTypeUnderlying t_Type>
	struct TCStrTraits_ReplaceParams<ch32, EStrType_Unicode, t_Type, TCStrImp_Dynamic<TCStrTraits<t_CCharType, t_Type, CStrImp_Dynamic_ParamsDeflauts>>, CStrImp_Dynamic_ParamsDeflauts>
	{
		typedef CStrTraits_CUStr CType;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_Type>
	struct TCStrTraits_ReplaceParams<ch32, EStrType_Unicode, t_Type, TCStrImp_Dynamic<TCStrTraits<t_CCharType, t_Type, CStrImp_Dynamic_ParamsNonTracked>>, CStrImp_Dynamic_ParamsNonTracked>
	{
		typedef CStrTraits_CUStrNonTracked CType;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_Type>
	struct TCStrTraits_ReplaceParams<ch32, EStrType_Unicode, t_Type, TCStrImp_Dynamic<TCStrTraits<t_CCharType, t_Type, CStrImp_Dynamic_ParamsSecure>>, CStrImp_Dynamic_ParamsSecure>
	{
		typedef CStrTraits_CUStrSecure CType;
	};

	typedef TCStr<CStrTraits_CStr> CStr;
	typedef TCStr<CStrTraits_CStrAnsi> CAnsiStr;
	typedef TCStr<CStrTraits_CWStr> CWStr;
	typedef TCStr<CStrTraits_CUStr> CUStr;

	typedef TCStrAggregate<CStrTraits_CStr> CStrAggregate;
	typedef TCStrAggregate<CStrTraits_CStrAnsi> CAnsiStrAggregate;
	typedef TCStrAggregate<CStrTraits_CWStr> CWStrAggregate;
	typedef TCStrAggregate<CStrTraits_CUStr> CUStrAggregate;

	typedef TCStr<CStrTraits_CStrNonTracked> CStrNonTracked;
	typedef TCStr<CStrTraits_CStrAnsiNonTracked> CAnsiStrNonTracked;
	typedef TCStr<CStrTraits_CWStrNonTracked> CWStrNonTracked;
	typedef TCStr<CStrTraits_CUStrNonTracked> CUStrNonTracked;

	typedef TCStrAggregate<CStrTraits_CStrNonTracked> CStrAggregateNonTracked;
	typedef TCStrAggregate<CStrTraits_CStrAnsiNonTracked> CAnsiStrAggregateNonTracked;
	typedef TCStrAggregate<CStrTraits_CWStrNonTracked> CWStrAggregateNonTracked;
	typedef TCStrAggregate<CStrTraits_CUStrNonTracked> CUStrAggregateNonTracked;

	typedef TCStr<CStrTraits_CStrSecure> CStrSecure;
	typedef TCStr<CStrTraits_CWStrSecure> CWStrSecure;
	typedef TCStr<CStrTraits_CUStrSecure> CUStrSecure;
	typedef TCStrAggregate<CStrTraits_CStrSecure> CStrSecureAggregate;
	typedef TCStrAggregate<CStrTraits_CWStrSecure> CWStrSecureAggregate;
	typedef TCStrAggregate<CStrTraits_CUStrSecure> CUStrSecureAggregate;

	struct CDefaultStrParams
	{
		typedef NMemory::CDefaultAllocator CAllocator;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_Type>
	struct TCStrTraitsPtr
	{
		typedef TCTCStrTraits<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>, TCStrImp_Ptr<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>>> CType;
	};

	class CStrTraitsPtr_CStr : public TCStrTraitsPtr<ch8, EStrType_UTF>::CType {};
	class CStrTraitsPtr_CWStr : public TCStrTraitsPtr<ch16, EStrType_UTF>::CType {};
	class CStrTraitsPtr_CUStr : public TCStrTraitsPtr<ch32, EStrType_Unicode>::CType {};

	typedef TCStr<CStrTraitsPtr_CStr> CStrPtr;
	typedef TCStr<CStrTraitsPtr_CWStr> CWStrPtr;
	typedef TCStr<CStrTraitsPtr_CUStr> CUStrPtr;

	template <typename t_CCharType>
	struct TCStrPtrFromCharType
	{
	};

	template <>
	struct TCStrPtrFromCharType<ch8>
	{
		typedef CStrPtr CType;
	};
	template <>
	struct TCStrPtrFromCharType<ch16>
	{
		typedef CWStrPtr CType;
	};
	template <>
	struct TCStrPtrFromCharType<ch32>
	{
		typedef CUStrPtr CType;
	};



	class CStrTraits_CStrVMem : public TCStrTraits_Eval<ch8, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsVirtual>::CType {};
	class CStrTraits_CWStrVMem : public TCStrTraits_Eval<ch16, EStrType_UTF, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsVirtual>::CType {};
	class CStrTraits_CUStrVMem : public TCStrTraits_Eval<ch32, EStrType_Unicode, TCStrImp_Dynamic, CStrImp_Dynamic_ParamsVirtual>::CType {};

	typedef TCStr<CStrTraits_CStrVMem> CStrVMem;
	typedef TCStr<CStrTraits_CWStrVMem> CWStrVMem;
	typedef TCStr<CStrTraits_CUStrVMem> CUStrVMem;

	typedef TCStrImp_Virtual_PtrWrapper<CStrTraits_CStr> CStrVp;
	typedef TCStrImp_Virtual_PtrWrapper<CStrTraits_CWStr> CWStrVp;
	typedef TCStrImp_Virtual_PtrWrapper<CStrTraits_CUStr> CUStrVp;

	typedef TCStrImp_Virtual_TStrWrapper<CStrTraits_CStr> CStrV;
	typedef TCStrImp_Virtual_TStrWrapper<CStrTraits_CWStr> CWStrV;
	typedef TCStrImp_Virtual_TStrWrapper<CStrTraits_CUStr> CUStrV;


	template <typename t_CCharType, aint t_NumChar, CStrTypeUnderlying t_Type>
	struct TCFStr
	{
		typedef TCStr<TCTCStrTraits<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>, TCStrImp_Fixed<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>, t_NumChar>>> CType;
	};

	template <typename t_CCharType, aint t_NumChar, CStrTypeUnderlying t_Type>
	struct TCFStrAggregate
	{
		typedef TCStrAggregate<TCTCStrTraits<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>, TCStrImp_Fixed<TCStrTraits<t_CCharType, t_Type, CDefaultStrParams>, t_NumChar>>> CType;
	};

	template <typename t_CCharType, CStrTypeUnderlying t_DesiredType, CStrTypeUnderlying t_Type, template <typename, aint t_DataLen> class t_TImpl, typename t_CParams, typename t_CCharType2, typename t_CParams2, aint t_DataLen>
	struct TCStrTraits_ReplaceParams<t_CCharType, t_DesiredType, t_Type, t_TImpl<TCStrTraits<t_CCharType2, t_Type, t_CParams2>, t_DataLen>, t_CParams>
	{
		typedef TCTCStrTraits<TCStrTraits<t_CCharType, t_DesiredType, t_CParams>, t_TImpl<TCStrTraits<t_CCharType, t_DesiredType, t_CParams>, t_DataLen>> CType;
	};


	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| 8 bit																								|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	typedef TCFStr<ch8, 16, EStrType_UTF>::CType CFStr16;
	typedef TCFStrAggregate<ch8, 16, EStrType_UTF>::CType CFStrAggregate16;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 16, EStrType_UTF>::CType> CFStr16V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 16, EStrType_UTF>::CType> CFStr16Vp;

	typedef TCFStr<ch8, 32, EStrType_UTF>::CType CFStr32;
	typedef TCFStrAggregate<ch8, 32, EStrType_UTF>::CType CFStrAggregate32;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 32, EStrType_UTF>::CType > CFStr32V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 32, EStrType_UTF>::CType> CFStr32Vp;

	typedef TCFStr<ch8, 64, EStrType_UTF>::CType CFStr64;
	typedef TCFStrAggregate<ch8, 64, EStrType_UTF>::CType CFStrAggregate64;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 64, EStrType_UTF>::CType > CFStr64V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 64, EStrType_UTF>::CType> CFStr64Vp;

	typedef TCFStr<ch8, 128, EStrType_UTF>::CType CFStr128;
	typedef TCFStrAggregate<ch8, 128, EStrType_UTF>::CType CFStrAggregate128;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 128, EStrType_UTF>::CType > CFStr128V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 128, EStrType_UTF>::CType> CFStr128Vp;

	typedef TCFStr<ch8, 256, EStrType_UTF>::CType CFStr256;
	typedef TCFStrAggregate<ch8, 256, EStrType_UTF>::CType CFStrAggregate256;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 256, EStrType_UTF>::CType > CFStr256V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 256, EStrType_UTF>::CType> CFStr256Vp;

	typedef TCFStr<ch8, 512, EStrType_UTF>::CType CFStr512;
	typedef TCFStrAggregate<ch8, 512, EStrType_UTF>::CType CFStrAggregate512;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 512, EStrType_UTF>::CType > CFStr512V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 512, EStrType_UTF>::CType> CFStr512Vp;

	typedef TCFStr<ch8, 1024, EStrType_UTF>::CType CFStr1024;
	typedef TCFStrAggregate<ch8, 1024, EStrType_UTF>::CType CFStrAggregate1024;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch8, 1024, EStrType_UTF>::CType > CFStr1024V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch8, 1024, EStrType_UTF>::CType> CFStr1024Vp;

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| 16 bit																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	typedef TCFStr<ch16, 16, EStrType_UTF>::CType CFWStr16;
	typedef TCFStrAggregate<ch16, 16, EStrType_UTF>::CType CFWStrAggregate16;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 16, EStrType_UTF>::CType > CFWStr16V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 16, EStrType_UTF>::CType> CFWStr16Vp;

	typedef TCFStr<ch16, 32, EStrType_UTF>::CType CFWStr32;
	typedef TCFStrAggregate<ch16, 32, EStrType_UTF>::CType CFWStrAggregate32;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 32, EStrType_UTF>::CType > CFWStr32V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 32, EStrType_UTF>::CType> CFWStr32Vp;

	typedef TCFStr<ch16, 64, EStrType_UTF>::CType CFWStr64;
	typedef TCFStrAggregate<ch16, 64, EStrType_UTF>::CType CFWStrAggregate64;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 64, EStrType_UTF>::CType > CFWStr64V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 64, EStrType_UTF>::CType> CFWStr64Vp;

	typedef TCFStr<ch16, 128, EStrType_UTF>::CType CFWStr128;
	typedef TCFStrAggregate<ch16, 128, EStrType_UTF>::CType CFWStrAggregate128;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 128, EStrType_UTF>::CType > CFWStr128V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 128, EStrType_UTF>::CType> CFWStr128Vp;

	typedef TCFStr<ch16, 256, EStrType_UTF>::CType CFWStr256;
	typedef TCFStrAggregate<ch16, 256, EStrType_UTF>::CType CFWStrAggregate256;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 256, EStrType_UTF>::CType > CFWStr256V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 256, EStrType_UTF>::CType> CFWStr256Vp;

	typedef TCFStr<ch16, 512, EStrType_UTF>::CType CFWStr512;
	typedef TCFStrAggregate<ch16, 512, EStrType_UTF>::CType CFWStrAggregate512;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 512, EStrType_UTF>::CType > CFWStr512V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 512, EStrType_UTF>::CType> CFWStr512Vp;

	typedef TCFStr<ch16, 1024, EStrType_UTF>::CType CFWStr1024;
	typedef TCFStrAggregate<ch16, 1024, EStrType_UTF>::CType CFWStrAggregate1024;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch16, 1024, EStrType_UTF>::CType > CFWStr1024V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch16, 1024, EStrType_UTF>::CType> CFWStr1024Vp;

	/***************************************************************************************************\
	|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
	| 32 bit																							|
	|___________________________________________________________________________________________________|
	\***************************************************************************************************/

	typedef TCFStr<ch32, 16, EStrType_Unicode>::CType CFUStr16;
	typedef TCFStrAggregate<ch32, 16, EStrType_Unicode>::CType CFUStrAggregate16;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 16, EStrType_Unicode>::CType > CFUStr16V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 16, EStrType_Unicode>::CType> CFUStr16Vp;

	typedef TCFStr<ch32, 32, EStrType_Unicode>::CType CFUStr32;
	typedef TCFStrAggregate<ch32, 32, EStrType_Unicode>::CType CFUStrAggregate32;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 32, EStrType_Unicode>::CType > CFUStr32V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 32, EStrType_Unicode>::CType> CFUStr32Vp;

	typedef TCFStr<ch32, 64, EStrType_Unicode>::CType CFUStr64;
	typedef TCFStrAggregate<ch32, 64, EStrType_Unicode>::CType CFUStrAggregate64;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 64, EStrType_Unicode>::CType > CFUStr64V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 64, EStrType_Unicode>::CType> CFUStr64Vp;

	typedef TCFStr<ch32, 128, EStrType_Unicode>::CType CFUStr128;
	typedef TCFStrAggregate<ch32, 128, EStrType_Unicode>::CType CFUStrAggregate128;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 128, EStrType_Unicode>::CType > CFUStr128V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 128, EStrType_Unicode>::CType> CFUStr128Vp;

	typedef TCFStr<ch32, 256, EStrType_Unicode>::CType CFUStr256;
	typedef TCFStrAggregate<ch32, 256, EStrType_Unicode>::CType CFUStrAggregate256;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 256, EStrType_Unicode>::CType > CFUStr256V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 256, EStrType_Unicode>::CType> CFUStr256Vp;

	typedef TCFStr<ch32, 512, EStrType_Unicode>::CType CFUStr512;
	typedef TCFStrAggregate<ch32, 512, EStrType_Unicode>::CType CFUStrAggregate512;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 512, EStrType_Unicode>::CType > CFUStr512V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 512, EStrType_Unicode>::CType> CFUStr512Vp;

	typedef TCFStr<ch32, 1024, EStrType_Unicode>::CType CFUStr1024;
	typedef TCFStrAggregate<ch32, 1024, EStrType_Unicode>::CType CFUStrAggregate1024;
	typedef TCStrImp_Virtual_TStrWrapper< TCFStr<ch32, 1024, EStrType_Unicode>::CType > CFUStr1024V;
	typedef TCStrImp_Virtual_PtrWrapper< TCFStr<ch32, 1024, EStrType_Unicode>::CType> CFUStr1024Vp;

#ifdef DMibDebug
	extern CWStr g_DebugOutputTemp16;
	extern CStr g_DebugOutputTemp8;
#endif
}
