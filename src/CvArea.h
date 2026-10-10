#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvStructs.h"

class CvCity;

class CvArea
{
public:
	int getTotalFoundValue() const;
	void setTotalFoundValue(int iValue);
	CvAreaBoundaries getAreaBoundaries() const;
	int calculateTotalBestNatureYield() const;
	int countCoastalLand() const;
	int countNumUniqueResourceTypes() const;
	int GetID() const;
	int getNumTiles() const;
	int getNumOwnedTiles() const;
	int getNumUnownedTiles() const;
	int getNumRiverEdges() const;
	int getNumCities() const;
	int getNumUnits() const;
	int getTotalPopulation() const;
	int getNumStartingPlots() const;
	bool isWater() const;
	int getUnitsPerPlayer(PlayerTypes ePlayer) const;
	int getCitiesPerPlayer(PlayerTypes ePlayer) const;
	int getPopulationPerPlayer(PlayerTypes ePlayer) const;
	int getFreeSpecialist(PlayerTypes ePlayer) const;
	int getNumRevealedTiles(TeamTypes eTeam) const;
	int getNumUnrevealedTiles(TeamTypes eTeam) const;
	CvCity* getTargetCity(PlayerTypes ePlayer) const;
	int getYieldRateModifier(PlayerTypes ePlayer, YieldTypes eYield) const;
	int getNumResources(ResourceTypes eResource) const;
	int getNumTotalResources() const;
	int getNumImprovements(ImprovementTypes eImprovement) const;
};
