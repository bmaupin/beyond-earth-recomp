#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvDiplomacyAIEnums.h"

class CvCity;
class CvPlayerAffinities;
class CvHandicapInfo;
class CvPlayerDiplomacy;
class CvPlayerPersonality;
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
	void AddPerk(PlayerPerkTypes ePerk, int iCount = 1, CvCity* pCity = NULL);
	void RemovePerk(PlayerPerkTypes ePerk);
	int GetCityMoveCostMod(const CvCity& city) const;
	// TODO: Inline after restoring authentic members through m_aquaticCityMoveCostMod (target offset 0x44).
	int GetAquaticCityMoveCostMod() const;
};

class CvPlayer
{
public:
	PlayerTypes GetID() const;
	int getPersonalityType() const;
	bool canSendTelemetry() const;
	bool isHuman() const;
	bool isMinorCiv() const;
	bool IsAITeammateOfHuman() const;
	bool isAlien() const;
	bool isNeutralProxy() const;
	// TODO: Inline after restoring authentic members through m_pPlayerPerks (target offset 0xf4bc).
	CvPlayerPerks* GetPlayerPerks() const;
	CvPlayerDiplomacy* GetPlayerDiplomacy() const;
	int GetDiplomaticCapital() const;
	void ChangeDiplomaticCapital(int iChange);
	CvHandicapInfo& getHandicapInfo() const;
	CvPlayerPersonality* GetPlayerPersonality() const
	{
		return *reinterpret_cast<CvPlayerPersonality* const*>(reinterpret_cast<const char*>(this) + 0x1060);
	}
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