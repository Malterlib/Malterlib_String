#include <Mib/Core/Core>

namespace NMib::NStr
{
	CStrFormatBinaryWrapper::CStrFormatBinaryWrapper(void const *_pData, mint _Size)
		: mp_pData(_pData)
		, mp_Size(_Size)
	{
	}

	void const *CStrFormatBinaryWrapper::f_GetArray() const
	{
		return mp_pData;
	}

	mint CStrFormatBinaryWrapper::f_GetSize() const
	{
		return mp_Size;
	}
}
