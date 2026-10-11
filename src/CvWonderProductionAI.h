#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"

class CvBuildingEntry;

class CvWonderProductionAI
{
public:
	BuildingTypes ChooseWonder(bool bUseAsyncRandom, bool bAdjustForOtherPlayers, int& iWeight);
	bool IsWonder(const CvBuildingEntry& building) const;
};
