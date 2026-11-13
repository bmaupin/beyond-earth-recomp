#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"

// Partial Beyond Earth declaration; native affinity queries remain external.
class CvPlayerAffinities
{
public:
	AffinityType GetDominantAffinityType() const;
	int GetAffinityPercentTowardsMaxLevel(AffinityType eAffinity) const;
	int GetAffinityLevel(AffinityType eAffinity) const;
	// TODO: CvPlayerAffinities (remaining methods and members).
};
