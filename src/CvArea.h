#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvStructs.h"

class CvCity;

// TODO: CvArea: reconstruct remaining native methods; only GetID is implemented here.
class CvArea
{
public:
	int getTotalFoundValue() const;
	void setTotalFoundValue(int iValue);
	CvAreaBoundaries getAreaBoundaries() const;
	int calculateTotalBestNatureYield() const;
	int countCoastalLand() const;
	int countNumUniqueResourceTypes() const;
	int GetID() const { return m_iID; }
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
	virtual void read(FDataStream&);
	virtual void write(FDataStream&) const;

protected:
	int m_iID;
	int m_iNumTiles;
	int m_iNumOwnedTiles;
	int m_iNumRiverEdges;
	int m_iNumUnits;
	int m_iNumCities;
	int m_iTotalPopulation;
	int m_iNumStartingPlots;
	unsigned int m_iTotalFoundValue;
	int m_aiUnitsPerPlayer[REALLY_MAX_PLAYERS];
	int m_aiCitiesPerPlayer[REALLY_MAX_PLAYERS];
	int m_aiPopulationPerPlayer[REALLY_MAX_PLAYERS];
	int m_aiFreeSpecialist[REALLY_MAX_PLAYERS];
	int m_aiNumRevealedTiles[REALLY_MAX_TEAMS];
	IDInfo m_aTargetCities[REALLY_MAX_TEAMS];
	int m_aaiYieldRateModifier[REALLY_MAX_PLAYERS][NUM_YIELD_TYPES];
	int* m_paiNumResources;
	int* m_paiNumImprovements;
	CvAreaBoundaries m_Boundaries;
	bool m_bWater;
	// Beyond Earth replaces natural wonders with mountain/canyon area flags.
	bool m_bMountains;
	bool m_bCanyons;
};
