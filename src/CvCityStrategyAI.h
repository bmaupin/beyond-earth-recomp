#pragma once

#include "CvUnitProductionAI.h"
#include "CvBuildingProductionAI.h"
#include "CvFlavorManager.h"

class CvCity;
class CvAICityStrategies;

class CvProjectProductionAI { public: int GetWeight(ProjectTypes eProject) const; };

class CvCityStrategyAI : public CvFlavorRecipient
{
public:
	CvString GetLogFileName(CvString& playerName, CvString& cityName) const;
	CvBuildingProductionAI* GetBuildingProductionAI() const;
	CvUnitProductionAI* GetUnitProductionAI() const;
	CvProjectProductionAI* GetProjectProductionAI() const;
	bool IsUsingCityStrategy(AICityStrategyTypes eStrategy);
	bool IsUsingCityStrategy(int eStrategy) { return IsUsingCityStrategy(static_cast<AICityStrategyTypes>(eStrategy)); }
	CitySpecializationTypes GetDefaultSpecialization() const { return m_eDefaultSpecialization; }
	CitySpecializationTypes GetSpecialization() const { return m_eSpecialization; }
	bool SetSpecialization(CitySpecializationTypes eSpecialization);
	bool IsYieldDeficient(YieldTypes eYield);
private:
	CvCity* m_pCity;
	CvAICityStrategies* m_pAICityStrategies;
	CitySpecializationTypes m_eSpecialization;
	CitySpecializationTypes m_eDefaultSpecialization;
	// TODO: CvCityStrategyAI (remaining members).
};

namespace CityStrategyAIHelpers
{
	int ReweightByTurnsLeft(int iOriginalWeight, int iTurnsLeft);
	// TODO: CityStrategyAIHelpers (remaining functions).
}