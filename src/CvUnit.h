#pragma once

class CvPlot;
class CvUnitEntry;
class FAutoArchive;
struct MissionData;

class CvUnit
{
public:
	int GetID() const;
	PlayerTypes getOwner() const;
	int getDamage() const;
	int getMoves() const;
	bool IsSelected() const;
	int GetMaxHitPoints() const;
	CivilizationTypes getCivilizationType() const;
	TeamTypes getTeam() const;
	DomainTypes getDomainType() const;
	bool IsCombatUnit() const;
	bool isAlien() const;
	bool IsHoveringUnit() const;
	bool IsAmphibiousUnit() const;
	bool isInvisible(TeamTypes eTeam, bool bDebug, bool bCheckCargo) const;
	bool IsOrbitalUnit() const;
	bool IsInOrbit() const;
	bool canMoveImpassable() const;
	DirectionTypes getFacingDirection(bool bCheckLineOfSightProperty) const;
	CvPlot* plot() const;
	CvUnitEntry& getUnitInfo() const;
	bool isEmbarked() const;
	bool IsGarrisoned() const;
	const MissionData* GetHeadMissionData();
	UnitCombatTypes getUnitCombatType() const;
	int getX() const;
	int getY() const;
	bool CanSwapWithUnitHere(CvPlot& kPlot) const;
	bool canEmbarkOnto(const CvPlot& kOriginPlot, const CvPlot& kTargetPlot, bool bOverrideEmbarkedCheck, bool bIgnoreStacking) const;
	bool canDisembarkOnto(const CvPlot& kOriginPlot, const CvPlot& kTargetPlot, bool bOverrideEmbarkedCheck, bool bIgnoreStacking) const;
	bool IsFirstTimeSelected() const;
	UnitTypes getUnitType() const;
	bool isDelayedDeathExported() const;
	bool IsBusy() const;
	void setupGraphical(bool bForce, int iState);
	void resetGraphical(int iState);
	CvString getName() const;
	const char* getNameKey() const;
	void doCommand(CommandTypes eCommand, int iData1, int iData2);
	bool CanDoInterfaceMode(InterfaceModeTypes eInterfaceMode, bool bTestVisibility);
	IDInfo GetIDInfo() const;
	int movesLeft() const;
	bool canMoveInto(const CvPlot& kPlot, byte bMoveFlags) const;
	TeamTypes GetDeclareWarMove(const CvPlot& kPlot) const;
	bool ReadyToSelect() const;
	bool isFound() const;
	bool IsWork() const;
	bool isTrade() const;
	bool IsWorker() const;
	FAutoArchive& getSyncArchive();
};
