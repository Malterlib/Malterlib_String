// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include <Mib/Iterator/Iterator>
#include <Mib/Iterator/Range>
#include <Mib/Iterator/Array>

namespace NMib
{
	namespace NStr
	{
		struct CIteratorStringEncoding_None
		{
			void f_GetBaseHelper()
			{
			}
		};

		struct CIteratorStringEncoding_UTF32 : public virtual CIteratorStringEncoding_None
		{
		};
		
		struct CIteratorStringEncoding_UTF16 : public virtual CIteratorStringEncoding_None
		{
		};
		
		struct CIteratorStringEncoding_UTF8 : public virtual CIteratorStringEncoding_None
		{
		};
		
		
		struct CIteratorStringNullTermination_None
		{
			void f_GetBaseHelper()
			{
			}
		};

		struct CIteratorStringNullTermination_Required : public virtual CIteratorStringNullTermination_None
		{
		};
		
		template <typename tf_CChar>
		struct TCGetIteratorUnicodeFromChar;

		struct CNullTerminatedBackIterator
		{
			typedef TCTags
				<
					NIterator::CIteratorCopy_Copy
					, NIterator::CIteratorConstruct_Default
				>
				CTags
			;
			
			CNullTerminatedBackIterator const &fp_Base() const;
			void fp_ParentIterator() const;
		};

		
		template <typename t_CIterator>
		class TCNullTerminatedBackIteratorAdaptor;
		
		template <typename t_CIteratorImp>
		class TCNullTerminatedBackIteratorAdaptor<NIterator::TCIterator<t_CIteratorImp>> : public t_CIteratorImp
		{
		public:
			TCNullTerminatedBackIteratorAdaptor const &fp_Base() const;
			NIterator::TCIterator<t_CIteratorImp> fp_ParentIterator() const;
			
			template <typename ...tfp_CConstruct>
			TCNullTerminatedBackIteratorAdaptor(tfp_CConstruct && ...p_Construct);
			
			t_CIteratorImp const &f_Imp() const;
			
		};
		
		template <typename tf_CLeft>
		bool operator == (tf_CLeft const *_pLeft, CNullTerminatedBackIterator const &_Right);

		template <typename tf_CLeft, typename tf_CIteratorImp>
		bool operator == (tf_CLeft const *_pLeft, TCNullTerminatedBackIteratorAdaptor<NIterator::TCIterator<tf_CIteratorImp>> const &_Right);
		
		
	}
}

#include "Malterlib_String_Iterator.hpp"

