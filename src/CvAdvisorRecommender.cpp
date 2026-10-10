#include "CvGameCoreDLLPCH.h"
#include "CvAdvisorRecommender.h"
#include <math.h>

CvAdvisorRecommender::CvAdvisorRecommender()
{
	Init();
}

CvAdvisorRecommender::~CvAdvisorRecommender()
{
	Uninit();
}

void CvAdvisorRecommender::Init()
{
	Reset();
}

void CvAdvisorRecommender::Uninit()
{
}

void CvAdvisorRecommender::Reset()
{
	ResetCity();
	ResetTechs();
}

void CvAdvisorRecommender::ResetCity()
{
	for (int i = 0; i < NUM_ADVISOR_TYPES; ++i)
		m_aRecommendedBuilds[i] = CvCityBuildable();
	m_aCityBuildables.clear();
	m_aFinalRoundBuildables.clear();
}

void CvAdvisorRecommender::ResetTechs()
{
	for (int i = 0; i < NUM_ADVISOR_TYPES; ++i)
		m_aRecommendedTechs[i] = NO_TECH;
	m_aResearchableTechs.clear();
	m_aFinalRoundTechs.clear();
}

void CvAdvisorRecommender::UpdateCityRecommendations(CvCity* pCity)
{
	ResetCity();
	CvCityStrategyAI* pStrategy = pCity->GetCityStrategyAI();
	CvCityBuildable buildable;
	for (int i = 0; i < GC.GetGameBuildings()->GetNumBuildings(); ++i)
	{
		if (!pCity->canConstruct((BuildingTypes)i)) continue;
		buildable.m_eBuildableType = CvCityBuildable::CITY_BUILDABLE_BUILDING;
		buildable.m_iIndex = i;
		buildable.m_iTurnsToConstruct = pCity->getProductionTurnsLeft((BuildingTypes)i, 0);
		m_aCityBuildables.push_back(buildable, pStrategy->GetBuildingProductionAI()->GetWeight((BuildingTypes)i));
	}
	for (int i = 0; i < GC.GetGameUnits()->GetNumUnits(); ++i)
	{
		if (!pCity->canTrain((UnitTypes)i)) continue;
		buildable.m_eBuildableType = CvCityBuildable::CITY_BUILDABLE_UNIT;
		buildable.m_iIndex = i;
		buildable.m_iTurnsToConstruct = pCity->getProductionTurnsLeft((UnitTypes)i, 0);
		m_aCityBuildables.push_back(buildable, pStrategy->GetUnitProductionAI()->GetWeight((UnitTypes)i));
	}
	for (int i = 0; i < GC.GetGameProjects()->GetNumProjects(); ++i)
	{
		if (!pCity->canCreate((ProjectTypes)i)) continue;
		buildable.m_eBuildableType = CvCityBuildable::CITY_BUILDABLE_PROJECT;
		buildable.m_iIndex = i;
		buildable.m_iTurnsToConstruct = pCity->getProductionTurnsLeft((ProjectTypes)i, 0);
		m_aCityBuildables.push_back(buildable, pStrategy->GetProjectProductionAI()->GetWeight((ProjectTypes)i));
	}
	for (int i = 0; i < m_aCityBuildables.size(); ++i)
	{
		buildable = m_aCityBuildables.GetElement(i);
		m_aCityBuildables.SetWeight(i, CityStrategyAIHelpers::ReweightByTurnsLeft(m_aCityBuildables.GetWeight(i), buildable.m_iTurnsToConstruct));
	}
	m_aCityBuildables.SortItems();
	for (int i = 0; i < NUM_ADVISOR_TYPES && i < m_aCityBuildables.size(); ++i)
		m_aFinalRoundBuildables.push_back(m_aCityBuildables.GetElement(i), m_aCityBuildables.GetWeight(i));
	for (int i = 0; i < m_aFinalRoundBuildables.size(); ++i)
	{
		m_aFinalRoundBuildables.SortItems();
		buildable = m_aFinalRoundBuildables.GetElement(0);
		const int score = m_aFinalRoundBuildables.GetWeight(0);
		const AdvisorTypes advisor = FindUnassignedAdvisorForBuildable(pCity->getOwner(), buildable);
		if (advisor != NO_ADVISOR_TYPE) m_aRecommendedBuilds[advisor] = buildable;
		m_aFinalRoundBuildables.SetWeight(0, score / 2);
	}
}

bool CvAdvisorRecommender::IsUnitRecommended(UnitTypes eUnit, AdvisorTypes eAdvisor)
{
	return m_aRecommendedBuilds[eAdvisor].m_eBuildableType == CvCityBuildable::CITY_BUILDABLE_UNIT && m_aRecommendedBuilds[eAdvisor].m_iIndex == eUnit;
}

bool CvAdvisorRecommender::IsBuildingRecommended(BuildingTypes eBuilding, AdvisorTypes eAdvisor)
{
	return m_aRecommendedBuilds[eAdvisor].m_eBuildableType == CvCityBuildable::CITY_BUILDABLE_BUILDING && m_aRecommendedBuilds[eAdvisor].m_iIndex == eBuilding;
}

bool CvAdvisorRecommender::IsProjectRecommended(ProjectTypes eProject, AdvisorTypes eAdvisor)
{
	return m_aRecommendedBuilds[eAdvisor].m_eBuildableType == CvCityBuildable::CITY_BUILDABLE_PROJECT && m_aRecommendedBuilds[eAdvisor].m_iIndex == eProject;
}

void CvAdvisorRecommender::UpdateTechRecommendations(PlayerTypes ePlayer)
{
	ResetTechs();
	CvPlayerTechs* pTechs = GET_PLAYER(ePlayer).GetPlayerTechs();
	CvTechAI* pTechAI = pTechs->GetTechAI();
	for (int i = 0; i < pTechs->GetTechs()->GetNumTechs(); ++i)
		if (pTechs->CanResearch((TechTypes)i)) m_aResearchableTechs.push_back(i, pTechAI->GetWeight((TechTypes)i));
	for (int i = 0; i < m_aResearchableTechs.size(); ++i)
	{
		const TechTypes tech = (TechTypes)m_aResearchableTechs.GetElement(i);
		const int turns = pTechs->GetResearchTurnsLeft(tech, true);
		int weight = m_aResearchableTechs.GetWeight(i);
		if (GET_PLAYER(ePlayer).GetNumFreeTechs() == 0)
			weight = (int)((double)weight / pow((double)turns, GC.getAI_RESEARCH_WEIGHT_BASE_MOD() + GC.getAI_RESEARCH_WEIGHT_MOD_PER_TURN_LEFT() * turns));
		else
			weight *= (turns / 2 > 0 ? turns / 2 : 1);
		m_aResearchableTechs.SetWeight(i, weight);
	}

	// The target assigns the four advisor slots globally, maximizing each advisor's
	// flavor-adjusted recommendation score rather than selecting them greedily.
	int scores[1 << NUM_ADVISOR_TYPES];
	int assignments[1 << NUM_ADVISOR_TYPES][NUM_ADVISOR_TYPES];
	for (int mask = 0; mask < (1 << NUM_ADVISOR_TYPES); ++mask)
	{
		scores[mask] = mask == 0 ? 0 : -1;
		for (int advisor = 0; advisor < NUM_ADVISOR_TYPES; ++advisor) assignments[mask][advisor] = -1;
	}
	for (int candidate = 0; candidate < m_aResearchableTechs.size(); ++candidate)
	{
		const TechTypes tech = (TechTypes)m_aResearchableTechs.GetElement(candidate);
		for (int mask = (1 << NUM_ADVISOR_TYPES) - 1; mask >= 0; --mask)
		{
			if (scores[mask] < 0) continue;
			for (int advisor = 0; advisor < NUM_ADVISOR_TYPES; ++advisor)
			{
				const int bit = 1 << advisor;
				if (mask & bit) continue;
				const int next = mask | bit;
				const int score = scores[mask] + AdvisorScoreForTech((AdvisorTypes)advisor, tech) + m_aResearchableTechs.GetWeight(candidate);
				if (score <= scores[next]) continue;
				scores[next] = score;
				for (int i = 0; i < NUM_ADVISOR_TYPES; ++i) assignments[next][i] = assignments[mask][i];
				assignments[next][advisor] = candidate;
			}
		}
	}
	int bestMask = 0;
	for (int mask = 1; mask < (1 << NUM_ADVISOR_TYPES); ++mask) if (scores[mask] > scores[bestMask]) bestMask = mask;
	for (int advisor = 0; advisor < NUM_ADVISOR_TYPES; ++advisor)
		if (assignments[bestMask][advisor] >= 0) m_aRecommendedTechs[advisor] = (TechTypes)m_aResearchableTechs.GetElement(assignments[bestMask][advisor]);
}

int CvAdvisorRecommender::AdvisorScoreForTech(AdvisorTypes eAdvisor, TechTypes eTech)
{
	CvTechEntry* pTech = GC.getTechInfo(eTech);
	int score = 0;
	if (pTech)
		for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
			if (pTech->GetFlavorValue(i) > 0) score += pTech->GetFlavorValue(i) * AdvisorInterestInFlavor(eAdvisor, (FlavorTypes)i);
	return score;
}

bool CvAdvisorRecommender::IsTechRecommended(TechTypes eTech, AdvisorTypes eAdvisor)
{
	return m_aRecommendedTechs[eAdvisor] == eTech;
}

int CvAdvisorRecommender::AdvisorInterestInFlavor(AdvisorTypes eAdvisor, FlavorTypes eFlavor)
{
	const char* name = GC.getFlavorTypes(eFlavor);
	if (!name) return 0;
	if (eAdvisor == ADVISOR_MILITARY)
	{
		if (!strcmp(name, "FLAVOR_OFFENSE") || !strcmp(name, "FLAVOR_DEFENSE") || !strcmp(name, "FLAVOR_RANGED") || !strcmp(name, "FLAVOR_NAVAL") || !strcmp(name, "FLAVOR_AIR") || !strcmp(name, "FLAVOR_NUKE")) return 10;
		if (!strcmp(name, "FLAVOR_MILITARY_TRAINING") || !strcmp(name, "FLAVOR_MOBILE")) return 7;
		if (!strcmp(name, "FLAVOR_CITY_DEFENSE")) return 5;
		if (!strcmp(name, "FLAVOR_RECON") || !strcmp(name, "FLAVOR_NAVAL_RECON")) return 3;
		if (!strcmp(name, "FLAVOR_INFRASTRUCTURE") || !strcmp(name, "FLAVOR_PRODUCTION")) return 1;
	}
	else if (eAdvisor == ADVISOR_ECONOMIC)
	{
		if (!strcmp(name, "FLAVOR_NAVAL_GROWTH") || !strcmp(name, "FLAVOR_NAVAL_TILE_IMPROVEMENT") || !strcmp(name, "FLAVOR_GROWTH") || !strcmp(name, "FLAVOR_TILE_IMPROVEMENT") || !strcmp(name, "FLAVOR_PRODUCTION") || !strcmp(name, "FLAVOR_ENERGY") || !strcmp(name, "FLAVOR_CULTURE") || !strcmp(name, "FLAVOR_HEALTH")) return 10;
		if (!strcmp(name, "FLAVOR_INFRASTRUCTURE")) return 5;
		if (!strcmp(name, "FLAVOR_CITY_DEFENSE")) return 1;
	}
	else if (eAdvisor == ADVISOR_FOREIGN)
	{
		if (!strcmp(name, "FLAVOR_RECON") || !strcmp(name, "FLAVOR_NAVAL_RECON") || !strcmp(name, "FLAVOR_DIPLOMACY")) return 10;
		if (!strcmp(name, "FLAVOR_GREAT_PEOPLE")) return 5;
		if (!strcmp(name, "FLAVOR_CITY_DEFENSE")) return 1;
	}
	else if (eAdvisor == ADVISOR_SCIENCE)
	{
		if (!strcmp(name, "FLAVOR_AIR")) return 5;
		if (!strcmp(name, "FLAVOR_RECON") || !strcmp(name, "FLAVOR_NAVAL_RECON") || !strcmp(name, "FLAVOR_NUKE")) return 3;
		if (!strcmp(name, "FLAVOR_CITY_DEFENSE") || !strcmp(name, "FLAVOR_NAVAL_TILE_IMPROVEMENT") || !strcmp(name, "FLAVOR_TILE_IMPROVEMENT")) return 1;
	}
	return 0;
}

AdvisorTypes CvAdvisorRecommender::FindUnassignedAdvisorForTech(PlayerTypes ePlayer, TechTypes eTech)
{
	CvTechEntry* pTech = GET_PLAYER(ePlayer).GetPlayerTechs()->GetTechs()->GetEntry(eTech);
	if (!pTech) return NO_ADVISOR_TYPE;
	int scores[NUM_ADVISOR_TYPES] = {0};
	for (int flavor = 0; flavor < GC.getNumFlavorTypes(); ++flavor)
		if (pTech->GetFlavorValue(flavor) > 0) for (int advisor = 0; advisor < NUM_ADVISOR_TYPES; ++advisor) scores[advisor] += pTech->GetFlavorValue(flavor) * AdvisorInterestInFlavor((AdvisorTypes)advisor, (FlavorTypes)flavor);
	AdvisorTypes result = NO_ADVISOR_TYPE; int highest = 0;
	for (int i = 0; i < NUM_ADVISOR_TYPES; ++i) if (m_aRecommendedTechs[i] == NO_TECH && scores[i] > highest) { result = (AdvisorTypes)i; highest = scores[i]; }
	return result;
}

AdvisorTypes CvAdvisorRecommender::FindUnassignedAdvisorForBuildable(PlayerTypes, CvCityBuildable& buildable)
{
	int scores[NUM_ADVISOR_TYPES] = {0};
	for (int flavor = 0; flavor < GC.getNumFlavorTypes(); ++flavor)
	{
		int value = 0;
		switch (buildable.m_eBuildableType) { case CvCityBuildable::CITY_BUILDABLE_BUILDING: value=GC.getBuildingInfo((BuildingTypes)buildable.m_iIndex)->GetFlavorValue(flavor); break; case CvCityBuildable::CITY_BUILDABLE_UNIT: value=GC.getUnitInfo((UnitTypes)buildable.m_iIndex)->GetFlavorValue(flavor); break; case CvCityBuildable::CITY_BUILDABLE_PROJECT: value=GC.getProjectInfo((ProjectTypes)buildable.m_iIndex)->GetFlavorValue(flavor); break; default: break; }
		if (value > 0) for (int advisor=0; advisor<NUM_ADVISOR_TYPES; ++advisor) scores[advisor] += value * AdvisorInterestInFlavor((AdvisorTypes)advisor, (FlavorTypes)flavor);
	}
	AdvisorTypes result = NO_ADVISOR_TYPE; int highest = 0;
	for (int i=0; i<NUM_ADVISOR_TYPES; ++i) if (m_aRecommendedBuilds[i].m_eBuildableType == CvCityBuildable::NOT_A_CITY_BUILDABLE && scores[i] > highest) { result=(AdvisorTypes)i; highest=scores[i]; }
	return result;
}
