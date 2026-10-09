#pragma once

struct MissionData
{
	MissionData()
		: eMissionType(NO_MISSION)
		, iData1(0)
		, iData2(0)
		, iFlags(0)
		, iPushTurn(0)
	{
	}

	MissionTypes eMissionType;
	int iData1;
	int iData2;
	int iFlags;
	int iPushTurn;
};

// TODO: CvStructs.h (remaining SDK structures).
