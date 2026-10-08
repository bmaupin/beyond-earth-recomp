#pragma once

// Supporting declaration from CvStructs.h. Beyond Earth's DWARF confirms
// bOption3 between bOption2 and eButtonPopupType, with szText still at 0x18.
struct CvPopupInfo
{
public:
	// TODO: CvPopupInfo::CvPopupInfo (Beyond Earth adds the third bool argument).
	CvPopupInfo(ButtonPopupTypes buttonPopupType, int data1, int data2,
		int data3, int flags, bool option1, bool option2, bool option3);

	int iData1;
	int iData2;
	int iData3;
	int iFlags;
	bool bOption1;
	bool bOption2;
	bool bOption3;
	ButtonPopupTypes eButtonPopupType;
	char szText[512];
};

struct IDInfo
{
	IDInfo(PlayerTypes eOwner=NO_PLAYER, int iID=FFreeList::INVALID_INDEX) : eOwner(eOwner), iID(iID) {}
	PlayerTypes eOwner;
	int iID;

	bool operator== (const IDInfo& info) const
	{
		return (eOwner == info.eOwner && iID == info.iID);
	}

	bool operator !=(const IDInfo& other) const
	{
		return (eOwner != other.eOwner || iID != other.iID);
	}

	void reset()
	{
		eOwner = NO_PLAYER;
		iID = FFreeList::INVALID_INDEX;
	}

	bool isInvalid() const
	{
		return eOwner == NO_PLAYER && iID == FFreeList::INVALID_INDEX;
	}
};

struct CvColorA
{
	CvColorA(float fr, float fg, float fb, float fa) : r(fr), g(fg), b(fb), a(fa) {}
	CvColorA() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
	float r, g, b, a;
};

// TODO: CvStructs.h (remaining SDK structures).