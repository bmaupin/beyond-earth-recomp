#pragma once

#include <list>

class CvCity;
class CvPlayerTechs;
class CvMinorCivAI;

enum PlayerPerkTypes
{
	NO_PLAYER_PERK = -1
};

struct PlayerPerkHandle
{
	PlayerPerkTypes m_type;
	int m_cityID;
	int m_turnExpiration;
};

class CvQuest
{
public:
	int GetTechAIWeight(TechTypes eTech) const;
};

class CvPlayerAffinities
{
public:
	int GetAffinityLevel(AffinityType eAffinity) const;
	AffinityType GetDominantAffinityType() const;
	int GetAffinityPercentTowardsMaxLevel(AffinityType eAffinity) const;
};

class CvGrandStrategyAI
{
public:
	const CvQuest* GetActiveGrandStrategyQuest() const;
	AIGrandStrategyTypes GetActiveGrandStrategy() const;
	AffinityType GetVictoryAffinityNeed(int* piNeed) const;
};

class CvPlayer;
class CvPlayerPerks
{
public:
	virtual ~CvPlayerPerks();

	int GetCityMoveCostMod(const CvCity& city) const;
	int GetAquaticCityMoveCostMod() const
	{
		return m_aquaticCityMoveCostMod;
	}
	int GetGlobalYieldPerTurnTimes100(YieldTypes eYield) const;

private:
	CvPlayer& m_player;
	std::list<PlayerPerkHandle> m_activePerks;
	int m_covertAgentRankRateChange;
	int m_expeditionSpeedMod;
	int m_unitVisibilityRangeChange;
	int m_navalMovementChange;
	int m_orbitalStrikeRangeChange;
	int m_outpostOrbitalCoverageChange;
	int m_stationOrbitalCoverageChange;
	int m_alienOpinionRecoveryMod;
	int m_orbitalCoverageCombatMod;
	int m_orbitalProductionModPerLaunchedUnit;
	int m_orbitalResourceCostChange;
	int m_orbitalUnitDurationMod;
	int m_aquaticCityMoveCostMod;
};

class CvOutpost;
class CvUnit;
class CvPlot;
class CvTreasury;
class CvDiplomacyAI;
class CvDealAI;
class CvNotifications;
class CvPlayerTraits;
class CvPlayerLoadout;
class CvPlayerCovertOps;
class CvDiplomacyRequests;
class CvPlayerUnitUpgrades;

class CvPlayer
{
public:
	virtual ~CvPlayer();
	virtual void Read(FDataStream& kStream);
	virtual void Write(FDataStream& kStream) const;
	int GetID() const;
	bool isHuman() const;
	bool isEverAlive() const;
	bool isBarbarian() const;
	bool isMinorCiv() const;
	int getPersonalityType() const;
	CvMinorCivAI* GetMinorCivAI() const;
	bool IsAITeammateOfHuman() const;
	bool isAlien() const;
	bool isNeutralProxy() const;
	// TODO: Inline after restoring authentic members through m_pPlayerPerks (target offset 0xf4bc).
	CvPlayerPerks* GetPlayerPerks() const;
	int GetRouteEnergyMaintenanceMod() const;
	const char* getCivilizationShortDescription() const;
	const CvCity* firstCity(int* pIterIdx, bool bRev = false) const;
	const CvCity* nextCity(int* pIterIdx, bool bRev = false) const;
	const CvCity* getCapitalCity() const;
	CvPlayerTechs* GetPlayerTechs() const;
	class CvPlayerPolicies* GetPlayerPolicies() const;
	int GetNumFreeTenets() const;
	CvCivilizationInfo& getCivilizationInfo() const;
	CvCity* firstCity(int* pIterIdx, bool bRev = false);
	CvCity* nextCity(int* pIterIdx, bool bRev = false);
	CvGrandStrategyAI* GetGrandStrategyAI() const;
	CvPlayerAffinities* GetAffinities() const;
	int GetGameProgress() const;
	int GetNumFreeTechs() const;
	void init(PlayerTypes eID);
	void setupGraphical();
	void InitAffinityValues();
	void gameStartInit();
	void uninit();
	bool isObserver() const;
	const char* getName() const;
	const char* getNickName() const;
	ArtStyleTypes getArtStyleType() const;
	CvUnit* GetFirstReadyUnit() const;
	bool hasBusyUnit() const;
	bool hasBusyUnitOrCity() const;
	int GetScore(bool bFinal, bool bVictory) const;
	CvPlot* getStartingPlot() const;
	void setStartingPlot(CvPlot* pPlot);
	CvCity* getCapitalCity();
	bool IsHasLostCapital() const;
	void setStartTime(unsigned int uiStartTime);
	bool isTurnActive() const;
	void setTurnActive(bool bNewValue, bool bDoTurn);
	HandicapTypes getHandicapType() const;
	CivilizationTypes getCivilizationType() const;
	LeaderHeadTypes getLeaderType() const;
	const char* getLeaderTypeKey() const;
	EraTypes GetCurrentEra() const;
	PlayerColorTypes getPlayerColor() const;
	bool isOption(PlayerOptionTypes eOption) const;
	int getNumCities() const;
	CvOutpost* FirstOutpost(int* pIterIdx, bool bRev);
	CvOutpost* NextOutpost(int* pIterIdx, bool bRev);
	int GetNumOutposts() const;
	CvOutpost* GetOutpost(int iID);
	CvCity* getCity(int iID);
	CvUnit* firstUnit(int* pIterIdx, bool bRev);
	CvUnit* nextUnit(int* pIterIdx, bool bRev);
	CvUnit* getUnit(int iID);
	int GetPlotDanger(CvPlot& plot) const;
	int GetCityDistanceHighwaterMark() const;
	void disconnected();
	void reconnected();
	void setBusyUnitUpdatesRemaining(int iUpdateCount);
	bool hasUnitsThatNeedAIUpdate() const;
	CvTreasury* GetTreasury() const;
	FAutoArchive& getSyncArchive();
	CvDiplomacyAI* GetDiplomacyAI() const;
	CvDealAI* GetDealAI() const;
	CvPlayerTraits* GetPlayerTraits() const;
	CvPlayerLoadout* GetPlayerLoadout() const;
	CvDiplomacyRequests* GetDiplomacyRequests() const;
	CvNotifications* GetNotifications() const;
	bool isSimultaneousTurns() const;
	bool hasTurnTimerExpired();
	void WaitForEffect(bool bWait);
	CvPlayerCovertOps* GetPlayerCovertOps() const;
	bool hasMadePlanetfall() const;
	// TODO: CvPlayer (remaining members).
};