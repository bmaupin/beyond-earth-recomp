#pragma once

class CvCityStrategyAI
{
public:
	CvString GetLogFileName(CvString& playerName, CvString& cityName) const;
	// TODO: CvCityStrategyAI (remaining members).
};

namespace CityStrategyAIHelpers
{
	int ReweightByTurnsLeft(int iOriginalWeight, int iTurnsLeft);
	// TODO: CityStrategyAIHelpers (remaining functions).
}