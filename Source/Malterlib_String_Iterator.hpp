// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NStr
{
	template <>
	struct TCGetIteratorUnicodeFromChar<ch8>
	{
		typedef CIteratorStringEncoding_UTF8 CType;
	};

#ifdef DMibPSignedType_ch8
	template <>
	struct TCGetIteratorUnicodeFromChar<uch8>
	{
		typedef CIteratorStringEncoding_UTF8 CType;
	};
#endif

	template <>
	struct TCGetIteratorUnicodeFromChar<ch16>
	{
		typedef CIteratorStringEncoding_UTF16 CType;
	};

#ifdef DMibPSignedType_ch16
	template <>
	struct TCGetIteratorUnicodeFromChar<uch16>
	{
		typedef CIteratorStringEncoding_UTF16 CType;
	};
#endif

	template <>
	struct TCGetIteratorUnicodeFromChar<ch32>
	{
		typedef CIteratorStringEncoding_UTF32 CType;
	};

#ifdef DMibPSignedType_ch32
	template <>
	struct TCGetIteratorUnicodeFromChar<uch32>
	{
		typedef CIteratorStringEncoding_UTF32 CType;
	};
#endif

	namespace NPrivate
	{
		template <typename t_CType>
		struct TCIsCharacter : public NTraits::CCompileTimeFalse
		{
		};

		template <>
		struct TCIsCharacter<ch8> : public NTraits::CCompileTimeTrue
		{

		};

		template <>
		struct TCIsCharacter<ch16> : public NTraits::CCompileTimeTrue
		{

		};

		template <>
		struct TCIsCharacter<ch32> : public NTraits::CCompileTimeTrue
		{

		};
	}

	inline_always CNullTerminatedBackIterator const &CNullTerminatedBackIterator::fp_Base() const
	{
		return *this;
	}
	inline_always void CNullTerminatedBackIterator::fp_ParentIterator() const
	{
	}

	template <typename tf_CLeft>
	inline_always bool operator == (tf_CLeft const *_pLeft, CNullTerminatedBackIterator const &_Right)
	{
		return !_pLeft || *_pLeft == 0;
	}

	template <typename t_CContainer>
	struct TCNullTerminated
	{
		t_CContainer m_Container;
		TCNullTerminated(t_CContainer _Container)
			: m_Container(_Container)
		{
		}
	};

	template <typename tf_CContainer>
	TCNullTerminated<tf_CContainer> fg_NullTerminated(tf_CContainer &&_Container)
	{
		return TCNullTerminated<tf_CContainer>(_Container);
	}

	template <typename tf_CType>
	struct TCRawStringArray
	{
		tf_CType *m_pStart;
		mint m_Len;

		TCRawStringArray(tf_CType *_pStart, mint _Len)
			: m_pStart(_pStart)
			, m_Len(_Len)
		{
		}
	};

	template <typename tf_CType>
	TCRawStringArray<tf_CType> fg_RawStringArray(tf_CType *_pStart, mint _Len)
	{
		return TCRawStringArray<tf_CType>(_pStart, _Len);
	}

	/*
	template <typename t_CContainer>
	struct TC
	{
		t_CContainer m_Container;
		TCNullTerminated(t_CContainer _Container)
			: m_Container(_Container)
		{
		}
	};

	template <typename tf_CContainer>
	TCNullTerminated<tf_CContainer> fg_NullTerminated(tf_CContainer &&_Container)
	{
		return TCNullTerminated<tf_CContainer>(_Container);
	}
	*/

#ifndef DDocumentation_Doxygen
	template <typename t_CIteratorImp>
	auto TCNullTerminatedBackIteratorAdaptor<NIterator::TCIterator<t_CIteratorImp>>::fp_Base() const -> TCNullTerminatedBackIteratorAdaptor const &
	{
		return *this;
	}
	template <typename t_CIteratorImp>
	NIterator::TCIterator<t_CIteratorImp> TCNullTerminatedBackIteratorAdaptor<NIterator::TCIterator<t_CIteratorImp>>::fp_ParentIterator() const
	{
		return (t_CIteratorImp const &)*this;
	}

	template <typename t_CIteratorImp>
	template <typename ...tfp_CConstruct>
	TCNullTerminatedBackIteratorAdaptor<NIterator::TCIterator<t_CIteratorImp>>::TCNullTerminatedBackIteratorAdaptor(tfp_CConstruct && ...p_Construct)
		: t_CIteratorImp(fg_Forward<tfp_CConstruct>(p_Construct)...)
	{
	}

	template <typename t_CIteratorImp>
	t_CIteratorImp const &TCNullTerminatedBackIteratorAdaptor<NIterator::TCIterator<t_CIteratorImp>>::f_Imp() const
	{
		return *this;
	}
#endif


	template <typename tf_CLeft, typename tf_CIteratorImp>
	inline_always bool operator == (tf_CLeft const *_pLeft, TCNullTerminatedBackIteratorAdaptor<NIterator::TCIterator<tf_CIteratorImp>> const &_Right)
	{
		return *_pLeft == 0 || _pLeft == _Right.f_Imp().fp_Base();
	}

}

namespace NMib::NIterator
{
	template <typename t_CTags, mint t_Extent, typename t_CType>
	class TCMakeRange
		<
			t_CType [t_Extent]
			, t_CTags
			, TCEnableIf<NStr::NPrivate::TCIsCharacter<NTraits::TCRemoveQualifiers<t_CType>>::mc_Value>
		> : public CValidMakeRange
	{
		typedef TCArrayIterator
			<
				t_CType
				, NTraits::TCUnsigned<t_CType>
				, typename NStr::TCGetIteratorUnicodeFromChar<NTraits::TCRemoveQualifiers<t_CType>>::CType
				, NStr::CIteratorStringNullTermination_Required
			>
			CArrayIterator
		;
	public:
		typedef TCRange<TCIterator<CArrayIterator>, TCIterator<CArrayIterator>> CRange;

		template <typename t_CType2>
		static CRange fs_Range(t_CType2 &&_Container)
		{
			// -1 to remove null termination
			return CRange(_Container, _Container + (t_Extent - 1));
		}
	};

	template <typename t_CTags, typename t_CType>
	class TCMakeRange
		<
			NStr::TCRawStringArray<t_CType>
			, t_CTags
			, void
		> : public CValidMakeRange
	{
		typedef TCArrayIterator
			<
				t_CType
				, NTraits::TCUnsigned<t_CType>
				, typename NStr::TCGetIteratorUnicodeFromChar<NTraits::TCRemoveQualifiers<t_CType>>::CType
			>
			CArrayIterator
		;
	public:
		typedef TCRange<TCIterator<CArrayIterator>, TCIterator<CArrayIterator>> CRange;

		template <typename t_CType2>
		static CRange fs_Range(t_CType2 &&_Container)
		{
			// -1 to remove null termination
			return CRange(_Container.m_pStart, _Container.m_pStart + _Container.m_Len);
		}
	};

	template <typename t_CPointer, typename t_CTags>
	class TCMakeRange
		<
			t_CPointer
			, t_CTags
			, TCEnableIf<NStr::NPrivate::TCIsCharacter<NTraits::TCRemoveQualifiers<NTraits::TCRemovePointer<t_CPointer>>>::mc_Value>
		>
		: public CValidMakeRange
	{
		using CCharType = NTraits::TCRemovePointer<t_CPointer>;
	public:
		typedef TCRange
			<
				TCIterator
				<
					TCArrayIterator
					<
						CCharType
						, NTraits::TCUnsigned<CCharType>
						, typename NStr::TCGetIteratorUnicodeFromChar<NTraits::TCRemoveQualifiers<CCharType>>::CType
					>
				>
				, TCIterator<NStr::CNullTerminatedBackIterator>
			>
			CRange
		;

		template <typename t_CType2>
		static CRange fs_Range(t_CType2 &&_Container)
		{
			// -1 to remove null termination
			return CRange(_Container, NStr::CNullTerminatedBackIterator());
		}
	};

	template <typename t_CContainer, typename t_CTags>
	class TCMakeRange
		<
			NStr::TCNullTerminated<t_CContainer>
			, t_CTags
			, void
		>
		: public CValidMakeRange
	{
	public:
		using CMakeRange = TCMakeRange<NTraits::TCRemoveReference<t_CContainer>, t_CTags>;
		typedef TCRange
			<
				typename CMakeRange::CRange::CFront
				, TCIterator<NStr::TCNullTerminatedBackIteratorAdaptor<typename CMakeRange::CRange::CBack>>
			>
			CRange
		;

		template <typename t_CType2>
		static CRange fs_Range(NStr::TCNullTerminated<t_CType2> const &_Container)
		{
			auto Range = CMakeRange::fs_Range(_Container.m_Container);
			return CRange(Range.f_Front(), NStr::TCNullTerminatedBackIteratorAdaptor<typename CMakeRange::CRange::CBack>(Range.f_Back()));
		}
	};
}
