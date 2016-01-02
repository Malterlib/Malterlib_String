// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Bit/Rotate>
#include "Malterlib_String_Algorithm_HashMurmur3.h"

namespace NMib
{
	namespace NStr2
	{
		namespace NPrivate		
		{
			
			//-----------------------------------------------------------------------------
			// Block read - if your platform needs to do endian-swapping or can only
			// handle aligned reads, do the conversion here
			static inline_always uint32 fg_GetBlock32 ( const uint32 * _pPointer)
			{
				#ifdef DMibPAlignedDataAccess
					uint32 Value;
					NMib::NMem::fg_MemCopy(&Value, _pPointer, 4);
					return NMib::fg_ByteSwapLE(Value);
				#else
					return NMib::fg_ByteSwapLE(*_pPointer);
				#endif
			}


			//-----------------------------------------------------------------------------
			// Finalization mix - force all bits of a hash block to avalanche
			static inline_always uint32 fg_Mix32 ( uint32 _Value )
			{
				_Value ^= _Value >> 16;
				_Value *= uint32(0x85ebca6b);
				_Value ^= _Value >> 13;
				_Value *= uint32(0xc2b2ae35);
				_Value ^= _Value >> 16;
				
				return _Value;
			}
			
			static inline_always uint32 fg_MergeLength(mint _Length)
			{
#				if DMibPPtrBits == 64
					uint32 Length = (uint32(_Length) & 0xffffffff) ^ (uint32(_Length >> 32) & 0xffffffff);
#				elif DMibPPtrBits == 32
					uint32 Length = _Length;
#				else
#					error "Implement this"
#				endif
				
				return Length;
			}

			CMurmurHash3::CMurmurHash3(uint32 _Seed)
				: mp_Hash(_Seed)
				, mp_Length(0)
			{
			}
			
			uint32 CMurmurHash3::f_GetHash() const
			{
				uint32 Hash = mp_Hash;
				mint Length = mp_Length;

				if (Length & 3)
				{
					const uint8 *pTail = (uint8 const *)mp_Block;
					uint32 Temp = 0;
					
					switch (Length & 3)
					{
					case 3: 
						Temp ^= pTail[2] << 16;
					case 2: 
						Temp ^= pTail[1] << 8;
					case 1:
						Temp ^= pTail[0];
						Temp *= mcp_Constant1;
						Temp = fg_RotateLeft(Temp,15);
						Temp *= mcp_Constant2;
						
						Hash ^= Temp;
					}
				}
				
				Hash ^= fg_MergeLength(Length);
				Hash = fg_Mix32(Hash);
				
				return Hash;
			}
			
			void CMurmurHash3::fp_AddBlock(uint32 _Block)
			{
				uint32 Temp = _Block;
				Temp *= mcp_Constant1;
				Temp = NMib::fg_RotateLeft(Temp,15);
				Temp *= mcp_Constant2;
				
				uint32 Hash = mp_Hash;
				Hash ^= Temp;
				Hash = NMib::fg_RotateLeft(Hash,13); 
				Hash = Hash*5 + 0xe6546b64;
				mp_Hash = Hash;
			}
			
			//-----------------------------------------------------------------------------
			uint32 fg_MurmurHash3_x86_32 ( const void * _pData, mint _Length, uint32 _Seed)
			{
				uint8 const *pData = (uint8 const *)_pData;
				mint const nBlocks = _Length / 4;
				
				uint32 Hash = _Seed;
				
				uint32 const Constant1 = 0xcc9e2d51;
				uint32 const Constant2 = 0x1b873593;
				
				//----------
				// Body
				uint32 const *pBlock = (uint32 const *)pData;
				uint32 const *pBlockEnd = pBlock + nBlocks;
				
				for (; pBlock != pBlockEnd; ++pBlock)
				{
					uint32 Temp = fg_GetBlock32(pBlock);
					
					Temp *= Constant1;
					Temp = NMib::fg_RotateLeft(Temp,15);
					Temp *= Constant2;
					
					Hash ^= Temp;
					Hash = NMib::fg_RotateLeft(Hash,13); 
					Hash = Hash*5 + 0xe6546b64;
				}
				
				//----------
				// Tail
				{
					const uint8 *pTail = (const uint8*)(pData + nBlocks*4);
					uint32 Temp = 0;
					
					switch (_Length & 3)
					{
					case 3: 
						Temp ^= pTail[2] << 16;
					case 2: 
						Temp ^= pTail[1] << 8;
					case 1:
						Temp ^= pTail[0];
						Temp *= Constant1;
						Temp = fg_RotateLeft(Temp,15);
						Temp *= Constant2;
							
						Hash ^= Temp;
					}
				};
				
				//----------
				// Finalization
				
				Hash ^= fg_MergeLength(_Length);
				Hash = fg_Mix32(Hash);
				
				return Hash;
			}
		}
	}
}
