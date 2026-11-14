#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"

enum MilitaryAIStrategyTypes : int;

class CvMilitaryAI
{
public:
	bool IsUsingStrategy(MilitaryAIStrategyTypes eStrategy) const;
	int GetNumberCivsAtWarWith() const;
	void LogPeace(PlayerTypes eOpponent);
};
