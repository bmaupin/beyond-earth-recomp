#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"

class CvMilitaryAI
{
public:
	bool IsUsingStrategy(MilitaryAIStrategyTypes eStrategy) const;
	int GetNumberCivsAtWarWith() const;
};
