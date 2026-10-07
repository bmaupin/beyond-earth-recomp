#pragma once

// The Linux port uses the default calling convention for these interfaces.
#define DLLCALL

// {D89BA82F-9FA3-4696-B3F4-52BDB101CFB2}
static const GUID guidICvUnknown =
{0xd89ba82f, 0x9fa3, 0x4696, {0xb3, 0xf4, 0x52, 0xbd, 0xb1, 0x1, 0xcf, 0xb2}};

//------------------------------------------------------------------------------
// Base Interfaces
//------------------------------------------------------------------------------
class ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId(){ return guidICvUnknown; }

	void DLLCALL operator delete(void* p)
	{
		if (p)
		{
			ICvUnknown* inst = (ICvUnknown*)(p);
			inst->Destroy();
		}
	}

	virtual void* DLLCALL QueryInterface(GUID guidInterface) = 0;

	template<typename T>
	T* DLLCALL QueryInterface()
	{
		return static_cast<T*>(QueryInterface(T::GetInterfaceId()));
	}

protected:
	virtual void DLLCALL Destroy() = 0;
};

// TODO: CvDllInterfaces.h (remaining SDK interfaces).