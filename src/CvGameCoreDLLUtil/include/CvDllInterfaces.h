#pragma once

// The Linux port uses the default calling convention for these interfaces.
#define DLLCALL

// Beyond Earth uses different interface IDs from the Civ V SDK.
// {D70014AE-D960-4668-BD97-88A9C5B36B9A}
static const GUID guidICvUnknown =
{0xd70014ae, 0xd960, 0x4668, {0xbd, 0x97, 0x88, 0xa9, 0xc5, 0xb3, 0x6b, 0x9a}};

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

// {E8414191-00BB-47A1-9933-D6BC9DF7D889}
static const GUID guidICvColorInfo1 =
{0xe8414191, 0x00bb, 0x47a1, {0x99, 0x33, 0xd6, 0xbc, 0x9d, 0xf7, 0xd8, 0x89}};

struct CvColorA;
class ICvColorInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvColorInfo1; }
	virtual const char* DLLCALL GetType() = 0;
	virtual const CvColorA& DLLCALL GetColor() = 0;
};

// {4057ACD7-50C1-4598-AFF6-0FC21598CA5E}
static const GUID guidICvPlayerOptionInfo1 =
{0x4057acd7, 0x50c1, 0x4598, {0xaf, 0xf6, 0x0f, 0xc2, 0x15, 0x98, 0xca, 0x5e}};

class ICvPlayerOptionInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvPlayerOptionInfo1; }

	virtual bool DLLCALL GetDefault() = 0;
};

class ICvInterfaceModeInfo1 : public ICvUnknown
{
public:
	// TODO: ICvInterfaceModeInfo1::GetInterfaceId (Beyond Earth GUID).
	virtual int DLLCALL GetMissionType() = 0;
};

// {F7C7CC11-394D-4EC5-BB3A-399FC7405459}
static const GUID guidICvUnit1 =
{0xf7c7cc11, 0x394d, 0x4ec5, {0xbb, 0x3a, 0x39, 0x9f, 0xc7, 0x40, 0x54, 0x59}};

class ICvUnit1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvUnit1; }
	// TODO: ICvUnit1 (remaining SDK methods and Beyond Earth changes).
};

// {92D85D44-7102-4093-941E-5A99849FFE7B}
static const GUID guidICvPolicyInfo1 =
{0x92d85d44, 0x7102, 0x4093, {0x94, 0x1e, 0x5a, 0x99, 0x84, 0x9f, 0xfe, 0x7b}};

class ICvPolicyInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvPolicyInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	// Beyond Earth adds this slot after the SDK's description getter.
	virtual bool DLLCALL IsKickerPolicy() = 0;
};

// TODO: CvDllInterfaces.h (remaining SDK interfaces).