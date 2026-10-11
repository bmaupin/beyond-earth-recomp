#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"

class CvPlayer;

enum StageTypes { NO_STAGE = -1 };

class CvPlayerAchievements
{
	const CvPlayer& m_kPlayer;
	bool m_landCityBuilt;
	bool m_warStarted;
	UnitTypes m_eSeigeWorm;
	UnitTypes m_eUltHybridPurityHarmony;
	UnitTypes m_eUltHybridHarmonySupremacy;
	UnitTypes m_eUltHybridSupremacyPurity;
	AffinityType m_eHarmony;
	AffinityType m_ePurity;
	AffinityType m_eSupremacy;
	PolicyTypes m_eTier1FinalKicker;
	PolicyTypes m_eTier2FinalKicker;
	PolicyTypes m_eTier3FinalKicker;
	StageTypes m_eMaxRespectStage;
	StageTypes m_eMaxFearStage;

public:
	CvPlayerAchievements(const CvPlayer&);
	virtual ~CvPlayerAchievements();

private:
	CvPlayerAchievements();
};
