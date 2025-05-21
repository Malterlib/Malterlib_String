// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/String/Algorithms/Compare>
#include <Mib/String/Algorithms/Copy>

#if 0
TCMetaObject<const TCIterator_UTF16EncodeOutput<[2 * ...]>>
TCMetaObject<TCIterator_UTF16EncodeOutput<[2 * ...]>>
#endif

namespace
{
	using namespace NMib;
	using namespace NMib::NStr2;
	using namespace NMib::NIterator;

	struct CSegmentedString
	{
		NContainer::TCLinkedList<NStr::CStr> m_Segments;

		struct CIterator;
		
		struct CIteratorSegmented
		{
			using CTags = TCTags
				<
					CIteratorStep_OneStep
					, CIteratorTraversal_Forward
					, CIteratorValueLifeTime_AfterIteratorExists
					, CIteratorCopy_Copy
					, CIteratorConstruct_Default
					, CIteratorAccess_Readable
					, NStr::CIteratorStringEncoding_UTF8
					, CIteratorSegmentation_Segmented
				>
			;
			
			NContainer::TCLinkedList<NStr::CStr>::CIteratorConst m_Iterator;
			TCIterator<TCArrayIterator<ch8 const, uch8 const>> m_Segment;
			TCIterator<TCArrayIterator<ch8 const, uch8 const>> m_SegmentEnd;
			bool m_bEnd;
			
			CIteratorSegmented(CIterator const &_Iterator);

			CIteratorSegmented
				(
					NContainer::TCLinkedList<NStr::CStr>::CIteratorConst _Iterator
					, TCArrayIterator<ch8 const, uch8 const> const &_Segment
					, TCArrayIterator<ch8 const, uch8 const> const &_SegmentEnd
					, bool _bEnd
				)
				: m_Iterator(_Iterator)
				, m_Segment(_Segment)
				, m_SegmentEnd(_SegmentEnd)
				, m_bEnd(_bEnd)
			{
			}
			
			CIteratorSegmented const &fp_Base() const
			{
				return *this;
			}
			
			void fp_ParentIterator() const
			{
			}

			void fp_StepForward()
			{
				++m_Iterator;
				if (m_Iterator)
				{
					m_Segment = TCArrayIterator<ch8 const, uch8 const>(m_Iterator->f_GetStr());
					m_SegmentEnd = TCArrayIterator<ch8 const, uch8 const>(m_Iterator->f_GetStr() + m_Iterator->f_GetLen());
				}
				else
				{
					m_Segment = TCArrayIterator<ch8 const, uch8 const>(nullptr);
					m_SegmentEnd = TCArrayIterator<ch8 const, uch8 const>(nullptr);
				}
			}

			TCRange<TCIterator<TCArrayIterator<ch8 const, uch8 const>>, TCIterator<TCArrayIterator<ch8 const, uch8 const>>>
			fp_GetValue() const
			{
				return fg_Range(m_Segment, m_SegmentEnd);
			}

			template <typename tf_CIterator>
			bool fp_Equal(tf_CIterator const &_Other) const
			{
				return fp_Base() == fg_Base(_Other);
			}
			
			bool operator == (CIteratorSegmented const &_Other) const
			{
				return !m_Iterator;
			}
			
			TCRange<TCIterator<CIteratorSegmented>, TCIterator<CIteratorSegmented>> 
			fp_ToSegmented(CIteratorSegmented const &_Back, TCRange<TCIterator<TCArrayIterator<ch8 const, uch8 const>>, TCIterator<TCArrayIterator<ch8 const, uch8 const>>> const &_Range) const
			{
				return fg_Range
					(
						TCIterator<CIteratorSegmented>(m_Iterator, _Range.f_Front(), m_SegmentEnd, m_bEnd)
						, TCIterator<CIteratorSegmented>(_Back.m_Iterator, _Range.f_Back(), _Back.m_SegmentEnd, _Back.m_bEnd)
					)
				;
			}
		};
		
		struct CIterator
		{
			using CTags = TCTags
				<
					CIteratorStep_OneStep
					, CIteratorTraversal_Forward
					, CIteratorValueLifeTime_AfterIteratorExists
					, CIteratorCopy_Copy
					, CIteratorConstruct_Default
					, CIteratorAccess_Readable
					, NStr::CIteratorStringEncoding_UTF8
					, CIteratorSegmentation_Supported
				>
			;
			
			NContainer::TCLinkedList<NStr::CStr>::CIteratorConst m_Iterator;
			TCIterator<TCArrayIterator<ch8 const, uch8 const>> m_Segment;
			TCIterator<TCArrayIterator<ch8 const, uch8 const>> m_SegmentEnd;
			bool m_bEnd;
			
			CIterator()
				: m_bEnd(false)
				, m_Segment(nullptr)
				, m_SegmentEnd(nullptr)
			{
			}
			
			CIterator(NContainer::TCLinkedList<NStr::CStr>::CIteratorConst _Iterator, bool _bEnd)
				: m_Iterator(_Iterator)
				, m_bEnd(_bEnd)
			{
				if (_Iterator && !_bEnd)
				{
					m_Segment = TCArrayIterator<ch8 const, uch8 const>(_Iterator->f_GetStr());
					m_SegmentEnd = TCArrayIterator<ch8 const, uch8 const>(_Iterator->f_GetStr() + _Iterator->f_GetLen());
				}
				else
				{
					m_Segment = nullptr;
					m_SegmentEnd = nullptr;
				}
			}

			CIterator
				(
					NContainer::TCLinkedList<NStr::CStr>::CIteratorConst _Iterator
					, TCArrayIterator<ch8 const, uch8 const> const &_Segment
					, TCArrayIterator<ch8 const, uch8 const> const &_SegmentEnd
					, bool _bEnd
				)
				: m_Iterator(_Iterator)
				, m_Segment(_Segment)
				, m_SegmentEnd(_SegmentEnd)
				, m_bEnd(_bEnd)
			{
			}
			
			CIterator const &fp_Base() const
			{
				return *this;
			}
			
			void fp_ParentIterator() const
			{
			}

			void fp_StepForward()
			{
				++m_Segment;
				if (m_Segment == m_SegmentEnd)
				{
					++m_Iterator;
					m_Segment = TCArrayIterator<ch8 const, uch8 const>(m_Iterator->f_GetStr());
					m_SegmentEnd = TCArrayIterator<ch8 const, uch8 const>(m_Iterator->f_GetStr() + m_Iterator->f_GetLen());
				}
			}

			uch8 fp_GetValue() const
			{
				return *m_Segment;
			}

			template <typename tf_CIterator>
			bool fp_Equal(tf_CIterator const &_Other) const
			{
				return fp_Base() == fg_Base(_Other);
			}
			
			bool operator == (CIterator const &_Other) const
			{
				if (m_Segment != _Other.m_Segment)
					return false;
				
				return !m_Iterator;
			}
			
			TCRange<TCIterator<CIteratorSegmented>, TCIterator<CIteratorSegmented>> fp_Segmented(CIterator const &_Other) const
			{
				return fg_Range(TCIterator<CIteratorSegmented>(*this), TCIterator<CIteratorSegmented>(_Other));
			}
			
			static TCRange<TCIterator<CIterator>, TCIterator<CIterator>> 
			fsp_FromSegmented(TCRange<TCIterator<CIteratorSegmented>, TCIterator<CIteratorSegmented>>  const &_Range)
			{
				return fg_Range
					(
						TCIterator<CIterator>(_Range.f_Front().m_Iterator, _Range.f_Front().m_Segment, _Range.f_Front().m_SegmentEnd, _Range.f_Front().m_bEnd)
						, TCIterator<CIterator>(_Range.f_Back().m_Iterator, _Range.f_Back().m_Segment, _Range.f_Back().m_SegmentEnd, _Range.f_Back().m_bEnd)
					)
				;
			}
			
		};
		
		template <typename tf_CTags>
		TCRange<TCIterator<CIterator>, TCIterator<CIterator>> f_Range() const
		{
			return {CIterator(m_Segments.f_GetIterator(), false), CIterator(m_Segments.f_GetIterator(), true)};
		}
		
	};
	
	CSegmentedString::CIteratorSegmented::CIteratorSegmented(CIterator const &_Iterator)
		: m_Iterator(_Iterator.m_Iterator)
		, m_Segment(_Iterator.m_Segment)
		, m_SegmentEnd(_Iterator.m_SegmentEnd)
		, m_bEnd(_Iterator.m_bEnd)
	{
	}


	struct CSegmentedString2
	{
		NContainer::TCLinkedList<CSegmentedString> m_Segments;
		struct CIterator;
		
		struct CIteratorSegmented
		{
			using CTags = TCTags
				<
					CIteratorStep_OneStep
					, CIteratorTraversal_Forward
					, CIteratorValueLifeTime_AfterIteratorExists
					, CIteratorCopy_Copy
					, CIteratorConstruct_Default
					, CIteratorAccess_Readable
					, NStr::CIteratorStringEncoding_UTF8
					, CIteratorSegmentation_Segmented
				>
			;
			
			NContainer::TCLinkedList<CSegmentedString>::CIteratorConst m_Iterator;
			TCRange<TCIterator<CSegmentedString::CIterator>, TCIterator<CSegmentedString::CIterator>> m_Range;
			bool m_bEnd;
			
			CIteratorSegmented(CIterator const &_Iterator);
			
			
			CIteratorSegmented()
				: m_bEnd(false)
			{
			}

			CIteratorSegmented
				(
					NContainer::TCLinkedList<CSegmentedString>::CIteratorConst _Iterator
					, TCRange<TCIterator<CSegmentedString::CIterator>, TCIterator<CSegmentedString::CIterator>> const &_Range
					, bool _bEnd
				)
				: m_Iterator(_Iterator)
				, m_Range(_Range)
				, m_bEnd(_bEnd)
			{
			}
			
			CIteratorSegmented const &fp_Base() const
			{
				return *this;
			}
			
			void fp_ParentIterator() const
			{
			}

			void fp_StepForward()
			{
				++m_Iterator;
				if (m_Iterator)
				{
					m_Range = fg_Range(*m_Iterator);
				}
				else
					m_Range = fg_Default();
			}

			TCRange<TCIterator<CSegmentedString::CIterator>, TCIterator<CSegmentedString::CIterator>>
			fp_GetValue() const
			{
				return m_Range;
			}

			template <typename tf_CIterator>
			bool fp_Equal(tf_CIterator const &_Other) const
			{
				return fp_Base() == fg_Base(_Other);
			}
			
			bool operator == (CIteratorSegmented const &_Other) const
			{
				return !m_Iterator;
			}
			
			TCRange<TCIterator<CIteratorSegmented>, TCIterator<CIteratorSegmented>> 
			fp_ToSegmented(CIteratorSegmented const &_Back, TCRange<TCIterator<CSegmentedString::CIterator>, TCIterator<CSegmentedString::CIterator>> const &_Range) const
			{
				return fg_Range
					(
						TCIterator<CIteratorSegmented>(m_Iterator, _Range, m_bEnd)
						, TCIterator<CIteratorSegmented>(_Back)
					)
				;
			}
		};
		
		struct CIterator
		{
			using CTags = TCTags
				<
					CIteratorStep_OneStep
					, CIteratorTraversal_Forward
					, CIteratorValueLifeTime_AfterIteratorExists
					, CIteratorCopy_Copy
					, CIteratorConstruct_Default
					, CIteratorAccess_Readable
					, NStr::CIteratorStringEncoding_UTF8
					, CIteratorSegmentation_Supported
				>
			;
			
			NContainer::TCLinkedList<CSegmentedString>::CIteratorConst m_Iterator;
			TCRange<TCIterator<CSegmentedString::CIterator>, TCIterator<CSegmentedString::CIterator>> m_Range;
			bool m_bEnd;
			
			CIterator(NContainer::TCLinkedList<CSegmentedString>::CIteratorConst _Iterator, bool _bEnd)
				: m_Iterator(_Iterator)
				, m_bEnd(_bEnd)
			{
				if (_Iterator)
					m_Range = fg_Range(*_Iterator);
			}

			CIterator
				(
					NContainer::TCLinkedList<CSegmentedString>::CIteratorConst _Iterator
					, TCRange<TCIterator<CSegmentedString::CIterator>, TCIterator<CSegmentedString::CIterator>> const &_Range
					, bool _bEnd
				)
				: m_Iterator(_Iterator)
				, m_Range(_Range)
				, m_bEnd(_bEnd)
			{
			}
			
			CIterator const &fp_Base() const
			{
				return *this;
			}
			
			void fp_ParentIterator() const
			{
			}

			void fp_StepForward()
			{
				++m_Range;
				if (m_Range)
				{
					++m_Iterator;
					m_Range = fg_Range(*m_Iterator);
				}
			}

			uch8 fp_GetValue() const
			{
				return *m_Range;
			}

			template <typename tf_CIterator>
			bool fp_Equal(tf_CIterator const &_Other) const
			{
				return fp_Base() == fg_Base(_Other);
			}
			
			bool operator == (CIterator const &_Other) const
			{
				if (!m_Range)
					return false;
				
				return !m_Iterator;
			}
			
			TCRange<TCIterator<CIteratorSegmented>, TCIterator<CIteratorSegmented>> fp_Segmented(CIterator const &_Other) const
			{
				return fg_Range(TCIterator<CIteratorSegmented>(*this), TCIterator<CIteratorSegmented>(_Other));
			}
			
			static TCRange<TCIterator<CIterator>, TCIterator<CIterator>> 
			fsp_FromSegmented(TCRange<TCIterator<CIteratorSegmented>, TCIterator<CIteratorSegmented>>  const &_Range)
			{
				return fg_Range
					(
						TCIterator<CIterator>(_Range.f_Front().m_Iterator, _Range.f_Front().m_Range, _Range.f_Front().m_bEnd)
						, TCIterator<CIterator>(_Range.f_Back().m_Iterator, _Range.f_Back().m_Range, _Range.f_Back().m_bEnd)
					)
				;
			}
			
		};
		
		template <typename tf_CTags>
		TCRange<TCIterator<CIterator>, TCIterator<CIterator>> f_Range() const
		{
			return {CIterator(m_Segments.f_GetIterator(), false), CIterator(m_Segments.f_GetIterator(), true)};
		}
		
	};

	
	CSegmentedString2::CIteratorSegmented::CIteratorSegmented(CIterator const &_Iterator)
		: m_Iterator(_Iterator.m_Iterator)
		, m_Range(_Iterator.m_Range)
		, m_bEnd(_Iterator.m_bEnd)
	{
	}

	template <typename tf_CChar>
	tf_CChar const *fg_GetToCopy();

	template <>
	ch8 const *fg_GetToCopy<ch8>()
	{
		return str_utf8("Char𠀀Char𠀀Char");
	}
	template <>
	ch16 const *fg_GetToCopy<ch16>()
	{
		return str_utf16("Char𠀀Char𠀀Char");
	}
	template <>
	ch32 const *fg_GetToCopy<ch32>()
	{
		return str_utf32("Char𠀀Char𠀀Char");
	}
	
	class CCopy_Tests : public NMib::NTest::CTest
	{
	public:
		
		template <typename tf_CChar>
		void fp_DoTests(NStr::CStr const &_Type)
		{
			DMibTestSuite(_Type)
			{
				auto ToCopy = fg_GetToCopy<tf_CChar>();
				{
					DMibTestPath("Normal");
					{
						DMibTestPath("ANSI");
						ch8 OutArray[100];
						NMemory::fg_ObjectSet(OutArray, 0xff, 100);
						auto rDestination = fg_StrCopy(OutArray, "Char65Char5Char");
						
						DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), "Char65Char5Char"), ==, ECompare_Equal);
					}
					{
						DMibTestPath("UTF8");
						{
							DMibTestPath("Default");
							ch8 OutArray[100];
							NMemory::fg_ObjectSet(OutArray, 0xff, 100);
							auto rDestination = fg_StrCopy(OutArray, ToCopy);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
						}
						{
							DMibTestPath("CReturn_Front_ResFront");
							ch8 OutArray[100];
							NMemory::fg_ObjectSet(OutArray, 0xff, 100);
							auto rDestination = fg_StrCopy(OutArray, ToCopy);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
						}
						{
							DMibTestPath("CReturn_ResFront_ResBack");
							ch8 OutArray[100];
							NMemory::fg_ObjectSet(OutArray, 0xff, 100);
							auto rDestination = fg_StrCopy(OutArray, ToCopy);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
						}
						{
							DMibTestPath("CReturn_ResBack_Back");
							ch8 OutArray[100];
							NMemory::fg_ObjectSet(OutArray, 0xff, 100);
							auto rDestination = fg_StrCopy(OutArray, ToCopy);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
						}
						{
							DMibTestPath("CReturn_ResFront_Back");
							ch8 OutArray[100];
							NMemory::fg_ObjectSet(OutArray, 0xff, 100);
							auto rDestination = fg_StrCopy(OutArray, ToCopy);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
						}
						{
							DMibTestPath("CReturn_Front_ResBack");
							ch8 OutArray[100];
							NMemory::fg_ObjectSet(OutArray, 0xff, 100);
							auto rDestination = fg_StrCopy(OutArray, ToCopy);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
						}
						{
							DMibTestPath("CReturn_Front_Back");
							ch8 OutArray[100];
							NMemory::fg_ObjectSet(OutArray, 0xff, 100);
							auto rDestination = fg_StrCopy(OutArray, ToCopy);
							
							DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
						}
					}
					{
						DMibTestPath("UTF16");
						ch16 OutArray[100];
						NMemory::fg_ObjectSet(OutArray, 0xff, 100);
						auto rDestination = fg_StrCopy(OutArray, ToCopy);
						
						DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
					}
					{
						DMibTestPath("UTF32");
						ch32 OutArray[100];
						NMemory::fg_ObjectSet(OutArray, 0xff, 100);
						auto rDestination = fg_StrCopy(OutArray, ToCopy);
						DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀Char𠀀Char")), ==, ECompare_Equal);
					}
				}
				{
					DMibTestPath("Too short");
					{
						DMibTestPath("ANSI");
						ch8 OutArray[6];
						NMemory::fg_ObjectSet(OutArray, 0xff, 6);
						auto rDestination = fg_StrCopy(OutArray, "Char65Char5Char");
						
						DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), "Char6"), ==, ECompare_Equal);
					}
					{
						DMibTestPath("UTF8");
						ch8 OutArray[6];
						NMemory::fg_ObjectSet(OutArray, 0xff, 6);
						auto rDestination = fg_StrCopy(OutArray, ToCopy);
						
						DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char")), ==, ECompare_Equal);
					}
					{
						DMibTestPath("UTF16");
						ch16 OutArray[6];
						NMemory::fg_ObjectSet(OutArray, 0xff, 6);
						auto rDestination = fg_StrCopy(OutArray, ToCopy);
						
						DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char")), ==, ECompare_Equal);
					}
					{
						DMibTestPath("UTF32");
						ch32 OutArray[6];
						NMemory::fg_ObjectSet(OutArray, 0xff, 6);
						auto rDestination = fg_StrCopy(OutArray, ToCopy);
						DMibExpect(fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Char𠀀")), ==, ECompare_Equal);
					}
				}
			};
		}
		
		void fp_DoSegmentedTest()
		{
			DMibTestSuite("Segmented")
			{
				CSegmentedString2 ToCopy;
				{
					auto &Segment = ToCopy.m_Segments.f_Insert();
					
					auto &Segment0 = Segment.m_Segments.f_Insert();
					
					Segment0 += "Segment00";
					
					auto &Segment1 = Segment.m_Segments.f_Insert();

					Segment1 += "Segment01";
				}
				{
					auto &Segment = ToCopy.m_Segments.f_Insert();
					
					auto &Segment0 = Segment.m_Segments.f_Insert();
					
					Segment0 += "Segment10";
					
					auto &Segment1 = Segment.m_Segments.f_Insert();

					Segment1 += "Segment11";
				}
				
				ch8 OutArray[256];
				NMemory::fg_ObjectSet(OutArray, 0xff, 256);
				auto rDestination = fg_StrCopy(OutArray, ToCopy);
				DMibExpect
					(
						fg_StrCompare(NStr::fg_NullTerminated(OutArray), str_utf8("Segment00Segment01Segment10Segment11"))
						, ==
						, ECompare_Equal
					)
				;
			};
		}
		
		void f_DoTests()
		{
			fp_DoTests<ch8>("UTF8");
			fp_DoTests<ch16>("UTF16");
			fp_DoTests<ch32>("UTF32");
			
			fp_DoSegmentedTest();
		}
	};

	DMibTestRegister(CCopy_Tests, Malterlib::String::Algorithm);
}
