#pragma once

#include "CvUnitProductionAI.h"

class CvBuildingProductionAI { public: int GetWeight(BuildingTypes eBuilding) const; };
class CvProjectProductionAI { public: int GetWeight(ProjectTypes eProject) const; };

class CvCityStrategyAI
{
public:
	CvString GetLogFileName(CvString& playerName, CvString& cityName) const;
	CvBuildingProductionAI* GetBuildingProductionAI() const;
	CvUnitProductionAI* GetUnitProductionAI() const;
	CvProjectProductionAI* GetProjectProductionAI() const;
	bool IsUsingCityStrategy(int eStrategy) const;
	// TODO: CvCityStrategyAI (remaining members).
};

namespace CityStrategyAIHelpers
{
	int ReweightByTurnsLeft(int iOriginalWeight, int iTurnsLeft);
	// TODO: CityStrategyAIHelpers (remaining functions).
}