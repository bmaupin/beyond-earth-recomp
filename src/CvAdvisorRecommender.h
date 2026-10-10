#pragma once

#include "CvGameCoreDLLUtil/include/CvWeightedVector.h"
#include <stdint.h>

struct CvCityBuildable
{
	enum BuildableType { NOT_A_CITY_BUILDABLE, CITY_BUILDABLE_BUILDING, CITY_BUILDABLE_UNIT, CITY_BUILDABLE_PROJECT };
	CvCityBuildable() : m_eBuildableType(NOT_A_CITY_BUILDABLE), m_iIndex(-1), m_iTurnsToConstruct(-1) {}
	BuildableType m_eBuildableType;
	int m_iIndex;
	int m_iTurnsToConstruct;
};

class CvAdvisorRecommender
{
public:
	CvAdvisorRecommender();
	~CvAdvisorRecommender();
	void Init();
	void Uninit();
	void Reset();
	void ResetCity();
	void UpdateCityRecommendations(CvCity* pCity);
	bool IsUnitRecommended(UnitTypes eUnit, AdvisorTypes eAdvisor);
	bool IsBuildingRecommended(BuildingTypes eBuilding, AdvisorTypes eAdvisor);
	bool IsProjectRecommended(ProjectTypes eProject, AdvisorTypes eAdvisor);
	void ResetTechs();
	void UpdateTechRecommendations(PlayerTypes ePlayer);
	int AdvisorScoreForTech(AdvisorTypes eAdvisor, TechTypes eTech);
	bool IsTechRecommended(TechTypes eTech, AdvisorTypes eAdvisor);
	int AdvisorInterestInFlavor(AdvisorTypes eAdvisor, FlavorTypes eFlavor);
	AdvisorTypes FindUnassignedAdvisorForTech(PlayerTypes ePlayer, TechTypes eTech);
	AdvisorTypes FindUnassignedAdvisorForBuildable(PlayerTypes ePlayer, CvCityBuildable& buildable);

	CvCityBuildable m_aRecommendedBuilds[NUM_ADVISOR_TYPES];
	TechTypes m_aRecommendedTechs[NUM_ADVISOR_TYPES];
	CvWeightedVector<int, 80, true> m_aResearchableTechs;
	CvWeightedVector<int, NUM_ADVISOR_TYPES, true> m_aFinalRoundTechs;
	CvWeightedVector<CvCityBuildable, 50, true> m_aCityBuildables;
	CvWeightedVector<CvCityBuildable, NUM_ADVISOR_TYPES, true> m_aFinalRoundBuildables;
};
