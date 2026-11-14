#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvDiplomacyAIEnums.h"

class CvCity;
class CvPlayerAffinities;
class CvLeaderHeadInfo;
class CvMilitaryAI;
class CvGrandStrategyAI
{
public:
	AIGrandStrategyTypes GetActiveGrandStrategy() const;
	AIGrandStrategyTypes GetGuessOtherPlayerActiveGrandStrategy(PlayerTypes ePlayer) const;
	GuessConfidenceTypes GetGuessOtherPlayerActiveGrandStrategyConfidence(PlayerTypes ePlayer) const;
};
class CvFlavorManager
{
public:
	int GetPersonalityIndividualFlavor(FlavorTypes eFlavor);
};
class CvPlayerPerks
{
public:
	int GetCityMoveCostMod(const CvCity& city) const;
	// TODO: Inline after restoring authentic members through m_aquaticCityMoveCostMod (target offset 0x44).
	int GetAquaticCityMoveCostMod() const;
};

class CvPlayer
{
public:
	bool isHuman() const;
	bool isMinorCiv() const;
	bool IsAITeammateOfHuman() const;
	bool isAlien() const;
	bool isNeutralProxy() const;
	// TODO: Inline after restoring authentic members through m_pPlayerPerks (target offset 0xf4bc).
	CvPlayerPerks* GetPlayerPerks() const;
	// TODO: Reimplement using m_pAffinities after restoring the authentic CvPlayer layout; DWARF offset 0xf4b4.
	CvPlayerAffinities* GetPlayerAffinities() const
	{
		return *reinterpret_cast<CvPlayerAffinities* const*>(reinterpret_cast<const char*>(this) + 0xf4b4);
	}
	CvLeaderHeadInfo& getLeaderInfo() const;
	const char* getCivilizationShortDescription() const;
	CvMilitaryAI* GetMilitaryAI() const;
	CvGrandStrategyAI* GetGrandStrategyAI() const;
	CvFlavorManager* GetFlavorManager() const;
	const CvCity* firstCity(int* pIterIdx, bool bRev = false) const;
	const CvCity* nextCity(int* pIterIdx, bool bRev = false) const;
	// TODO: CvPlayer (remaining members).
};