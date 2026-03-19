#include <Mib/Core/Core>

namespace NMib::NStr
{
	CStrFormatBinaryWrapper::CStrFormatBinaryWrapper(void const *_pData, umint _Size)
		: mp_pData(_pData)
		, mp_Size(_Size)
	{
	}

	void const *CStrFormatBinaryWrapper::f_GetArray() const
	{
		return mp_pData;
	}

	umint CStrFormatBinaryWrapper::f_GetSize() const
	{
		return mp_Size;
	}
}
