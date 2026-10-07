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

// TODO: CvStructs.h (remaining SDK structures).