// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

using uch8 = NMib::NTraits::TCUnsigned<ch8>;
using uch16 = NMib::NTraits::TCUnsigned<ch16>;
using uch32 = NMib::NTraits::TCUnsigned<ch32>;

using zuch8 = NMib::TCAutoClear<uch8>;
using zuch16 = NMib::TCAutoClear<uch16>;
using zuch32 = NMib::TCAutoClear<uch32>;

#include "Malterlib_String_Constants.h"

#include "Algorithm/Malterlib_String_Algorithm.hpp"
#include "Malterlib_String_Parse_Integer.h"
#include "Malterlib_String_Parse_Float.h"
#include "Container/Malterlib_String_Container_Format_Shared.h"
#include "Container/Malterlib_String_Container_Parse.h"
#include "Container/Malterlib_String_Container.h"
#include "Container/Malterlib_String_Container_ImpVirtual.h"
#include "Container/Malterlib_String_Container_ImpDynamic.h"
#include "Container/Malterlib_String_Container_ImpFixed.h"
#include "Container/Malterlib_String_Container_ImpPtr.h"
#include "Container/Malterlib_String_Container_Format_String.h"
#include "Container/Malterlib_String_Container_Format_StringContainer.h"
#include "Container/Malterlib_String_Container_Format_Integer.h"
#include "Container/Malterlib_String_Container_Format_Float.h"
#include "Container/Malterlib_String_Container_Format_Binary.h"
#include "Container/Malterlib_String_Container_Format_Inline.h"
#include "Container/Malterlib_String_Container_Format_AutoClear.h"
#include "Container/Malterlib_String_Container_Parse_Integer.h"
#include "Container/Malterlib_String_Container_Parse_Float.h"
#include "Container/Malterlib_String_Container_Parse_StringContainer.h"
#include "Container/Malterlib_String_Container_FormatHelpers.h"
#include "Malterlib_String_Platform.h"
#include "Malterlib_String_Compare.h"
#include "Container/Malterlib_String_Container.hpp"
#include "Malterlib_String_FormatLiteral.h"
#include "Malterlib_String_Parse.h"
#include "Malterlib_String_UTF8.h"
#include "Malterlib_String_Instantiated.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NStr;
#endif
