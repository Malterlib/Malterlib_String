// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Core/Tags>

namespace NMib::NStr2
{
	template <typename ...tfp_CTags, typename tf_CFront, typename tf_CBack>
	void fg_StrFinish(NIterator::TCRange<tf_CFront, tf_CBack> const &_rCharacters);
}

#include "Malterlib_String_Algorithm_Finish.hpp"
