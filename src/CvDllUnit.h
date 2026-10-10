#pragma once

#include "CvDllInterfaces.h"

class CvDllUnit : public ICvUnit1
{
public:
	CvDllUnit(CvUnit* pUnit);
	~CvDllUnit();

	void* DLLCALL QueryInterface(GUID guidInterface);
	unsigned int IncrementReference();
	unsigned int DecrementReference();
	unsigned int GetReferenceCount();

	static void operator delete(void* p);
	static void* operator new(size_t bytes);

	CvUnit* GetInstance();
	int DLLCALL GetID() const;
	PlayerTypes DLLCALL GetOwner() const;
	int DLLCALL GetDamage() const;
	int DLLCALL GetMoves() const;
	bool DLLCALL IsSelected() const;
	int DLLCALL GetMaxHitPoints() const;
	CivilizationTypes DLLCALL GetCivilizationType() const;
	TeamTypes DLLCALL GetTeam() const;
	DomainTypes DLLCALL GetDomainType() const;
	bool DLLCALL IsCombatUnit() const;
	bool DLLCALL IsAlien() const;
	bool DLLCALL IsHoveringUnit() const;
	bool DLLCALL IsAmphibiousUnit() const;
	bool DLLCALL IsInvisible(TeamTypes eTeam, bool bDebug) const;
	bool DLLCALL IsOrbitalUnit() const;
	bool DLLCALL IsInOrbit() const;
	bool DLLCALL CanMoveImpassable() const;
	DirectionTypes DLLCALL GetFacingDirection(bool checkLineOfSightProperty) const;
	ICvPlot1* DLLCALL GetPlot() const;
	ICvUnitInfo1* DLLCALL GetUnitInfo() const;
	bool DLLCALL IsEmbarked() const;
	bool DLLCALL IsGarrisoned() const;
	ICvMissionData1* DLLCALL GetHeadMissionData() const;
	UnitCombatTypes DLLCALL GetUnitCombatType();
	int DLLCALL GetX() const;
	int DLLCALL GetY() const;
	void DLLCALL GetPosition(int& iX, int& iY) const;
	bool DLLCALL CanSwapWithUnitHere(ICvPlot1* pPlot) const;
	bool DLLCALL CanEmbarkOnto(ICvPlot1* pOriginPlot, ICvPlot1* pTargetPlot, bool bOverrideEmbarkedCheck = false) const;
	bool DLLCALL CanDisembarkOnto(ICvPlot1* pOriginPlot, ICvPlot1* pTargetPlot, bool bOverrideEmbarkedCheck = false) const;
	bool DLLCALL IsFirstTimeSelected() const;
	UnitTypes DLLCALL GetUnitType() const;
	bool DLLCALL IsDelayedDeathExported() const;
	bool DLLCALL IsBusy() const;
	void DLLCALL SetupGraphical();
	void DLLCALL ResetGraphical(int iState);
	CvString DLLCALL GetName() const;
	CvString DLLCALL GetNameTextKey() const;
	void DLLCALL DoCommand(CommandTypes eCommand, int iData1, int iData2);
	bool DLLCALL CanDoInterfaceMode(InterfaceModeTypes eInterfaceMode, bool bTestVisibility = false);
	IDInfo DLLCALL GetIDInfo() const;
	int DLLCALL MovesLeft() const;
	bool DLLCALL CanMoveInto(ICvPlot1* pPlot, byte bMoveFlags = 0) const;
	TeamTypes DLLCALL GetDeclareWarMove(ICvPlot1* pPlot) const;
	bool DLLCALL ReadyToSelect() const;
	bool DLLCALL CanWork() const;
	bool DLLCALL CanFound() const;
	FAutoArchive& DLLCALL GetSyncArchive();
	bool DLLCALL IsTrade() const;
	bool DLLCALL IsWorker() const;

private:
	void DLLCALL Destroy();

	unsigned int m_uiRefCount;
	CvUnit* m_pUnit;
};
