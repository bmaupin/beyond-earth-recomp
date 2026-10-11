#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"

class CvCity;
class CvPlayer;
class CvPlot;
class CvBuildingEntry;
class FDataStream;
enum SpecialistTypes : int;
enum UnitClassTypes : int;

class CvCityCitizens
{
public:
	CvCityCitizens();
	~CvCityCitizens();
	void Init(CvCity* pCity);
	void Uninit();
	void Reset();
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream);
	CvCity* GetCity();
	CvPlayer* GetPlayer();
	PlayerTypes GetOwner() const;
	TeamTypes GetTeam() const;
	void DoFoundCity();
	void DoTurn();
	int GetPlotValue(CvPlot* pPlot, bool bUseAllowGrowthFlag);
	bool IsAutomated() const;
	void SetAutomated(bool bValue);
	bool IsNoAutoAssignSpecialists() const;
	void SetNoAutoAssignSpecialists(bool bValue);
	bool IsAvoidGrowth();
	bool IsForcedAvoidGrowth();
	void SetForcedAvoidGrowth(bool bAvoidGrowth);
	CityAIFocusTypes GetFocusType() const;
	void SetFocusType(CityAIFocusTypes eFocus);
	bool IsAIWantSpecialistRightNow();
	BuildingTypes GetAIBestSpecialistBuilding(int& iSpecialistValue);
	int GetSpecialistValue(SpecialistTypes eSpecialist);
	bool IsBetterThanDefaultSpecialist(SpecialistTypes eSpecialist);
	int GetNumUnassignedCitizens() const;
	void ChangeNumUnassignedCitizens(int iChange);
	int GetNumCitizensWorkingPlots() const;
	void ChangeNumCitizensWorkingPlots(int iChange);
	bool DoAddBestCitizenFromUnassigned();
	bool DoRemoveWorstCitizen(bool bRemoveForcedStatus = false, SpecialistTypes eDontChangeSpecialist = static_cast<SpecialistTypes>(-1), int iCurrentCityPopulation = -1);
	void DoReallocateCitizens();
	CvPlot* GetBestCityPlotWithValue(int& iValue, bool bWantBest, bool bWantWorked);
	bool IsWorkingPlot(const CvPlot* pPlot) const;
	void SetWorkingPlot(CvPlot* pPlot, bool bNewValue, bool bUseUnassignedPool = true);
	void DoAlterWorkingPlot(int iIndex);
	void ClearWorkingPlots();
	bool IsForcedWorkingPlot(const CvPlot* pPlot) const;
	void SetForcedWorkingPlot(CvPlot* pPlot, bool bNewValue);
	void DoValidateForcedWorkingPlots();
	void DoDemoteWorstForcedWorkingPlot();
	int GetNumForcedWorkingPlots() const;
	void ChangeNumForcedWorkingPlots(int iChange);
	bool IsCanWork(CvPlot* pPlot) const;
	bool IsAnyPlotBlockaded() const;
	void DoVerifyWorkingPlot(CvPlot* pPlot);
	void DoVerifyWorkingPlots();
	int GetCityIndexFromPlot(const CvPlot* pPlot) const;
	CvPlot* GetCityPlotFromIndex(int iIndex) const;
	void DoSpecialists();
	bool IsCanAddSpecialistToBuilding(BuildingTypes eBuilding);
	void DoAddSpecialistToBuilding(BuildingTypes eBuilding, bool bForced);
	void DoRemoveSpecialistFromBuilding(BuildingTypes eBuilding, bool bForced, bool bEliminatePopulation = false);
	void DoRemoveAllSpecialistsFromBuilding(BuildingTypes eBuilding, bool bEliminatePopulation = false);
	bool DoRemoveWorstSpecialist(SpecialistTypes eDontChangeSpecialist, BuildingTypes eDontRemoveFromBuilding = NO_BUILDING);
	int GetNumDefaultSpecialists() const;
	void ChangeNumDefaultSpecialists(int iChange);
	int GetNumForcedDefaultSpecialists() const;
	void ChangeNumForcedDefaultSpecialists(int iChange);
	int GetSpecialistCount(SpecialistTypes eIndex) const;
	int GetTotalSpecialistCount() const;
	int GetNumSpecialistsInBuilding(BuildingTypes eBuilding) const;
	int GetNumForcedSpecialistsInBuilding(BuildingTypes eBuilding) const;
	void DoClearForcedSpecialists();
	int GetNumSpecialistsAllowedByBuilding(const CvBuildingEntry& kBuilding);
	int GetSpecialistUpgradeThreshold(UnitClassTypes eUnitClass);

private:
	CvCity* m_pCity;
	bool m_bAutomated;
	bool m_bNoAutoAssignSpecialists;
	int m_iNumUnassignedCitizens;
	int m_iNumCitizensWorkingPlots;
	int m_iNumForcedWorkingPlots;
	CityAIFocusTypes m_eCityAIFocusTypes;
	bool m_bForceAvoidGrowth;
	bool m_pabWorkingPlot[37];
	bool m_pabForcedWorkingPlot[37];
	int m_iNumDefaultSpecialists;
	int m_iNumForcedDefaultSpecialists;
	int* m_aiSpecialistCounts;
	int* m_aiNumSpecialistsInBuilding;
	int* m_aiNumForcedSpecialistsInBuilding;
	bool m_bInited;
};

static_assert(sizeof(CvCityCitizens) == 124, "Beyond Earth i386 citizen layout");
