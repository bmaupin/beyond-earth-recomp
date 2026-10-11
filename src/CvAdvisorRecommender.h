#pragma once

#include "CvGameCoreDLLUtil/include/CvWeightedVector.h"
#include <stdint.h>

struct CvCityBuildable
{
	enum BuildableType { NOT_A_CITY_BUILDABLE, CITY_BUILDABLE_BUILDING, CITY_BUILDABLE_UNIT, CITY_BUILDABLE_PROJECT };
// TODO(Phase1 audit): CvCityBuildable::CvCityBuildable UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	CvCityBuildable() : m_eBuildableType(NOT_A_CITY_BUILDABLE), m_iIndex(-1), m_iTurnsToConstruct(-1) {}
	BuildableType m_eBuildableType;
	int m_iIndex;
	int m_iTurnsToConstruct;
};

class CvAdvisorRecommender
{
public:
// TODO(Phase1 audit): CvAdvisorRecommender::CvAdvisorRecommender MISMATCH: Instruction 5 differs before first target reference: object [movl   $0xffffffff,0x4(%edx)] vs BE [movl   $0x0,0x4(%edx)]; BE instructions=41; Civ5 changed/new=UNVERIFIED.
	CvAdvisorRecommender();
// TODO(Phase1 audit): CvAdvisorRecommender::~CvAdvisorRecommender UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=23; Civ5 changed/new=UNVERIFIED.
	~CvAdvisorRecommender();
// TODO(Phase1 audit): CvAdvisorRecommender::Init MISMATCH: Instruction 1 differs before first target reference: object [mov    $0x8,%ecx] vs BE [mov    0x4(%esp),%eax]; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	void Init();
	void Uninit();
// TODO(Phase1 audit): CvAdvisorRecommender::Reset MISMATCH: Instruction 1 differs before first target reference: object [mov    $0x8,%ecx] vs BE [mov    0x4(%esp),%eax]; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	void Reset();
// TODO(Phase1 audit): CvAdvisorRecommender::ResetCity MISMATCH: Instruction 1 differs before first target reference: object [mov    $0x8,%ecx] vs BE [mov    0x4(%esp),%eax]; BE instructions=11; Civ5 changed/new=UNVERIFIED.
	void ResetCity();
// TODO(Phase1 audit): CvAdvisorRecommender::UpdateCityRecommendations UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=273; Civ5 changed/new=UNVERIFIED.
	void UpdateCityRecommendations(CvCity* pCity);
// TODO(Phase1 audit): CvAdvisorRecommender::IsUnitRecommended UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=12; Civ5 changed/new=UNVERIFIED.
	bool IsUnitRecommended(UnitTypes eUnit, AdvisorTypes eAdvisor);
// TODO(Phase1 audit): CvAdvisorRecommender::IsBuildingRecommended UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=12; Civ5 changed/new=UNVERIFIED.
	bool IsBuildingRecommended(BuildingTypes eBuilding, AdvisorTypes eAdvisor);
// TODO(Phase1 audit): CvAdvisorRecommender::IsProjectRecommended UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=12; Civ5 changed/new=UNVERIFIED.
	bool IsProjectRecommended(ProjectTypes eProject, AdvisorTypes eAdvisor);
	void ResetTechs();
// TODO(Phase1 audit): CvAdvisorRecommender::UpdateTechRecommendations MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x18c,%esp] vs BE [sub    $0x1403c,%esp]; BE instructions=196; Civ5 changed/new=UNVERIFIED.
	void UpdateTechRecommendations(PlayerTypes ePlayer);
// TODO(Phase1 audit): CvAdvisorRecommender::AdvisorScoreForTech UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=46; Civ5 changed/new=UNVERIFIED.
	int AdvisorScoreForTech(AdvisorTypes eAdvisor, TechTypes eTech);
	bool IsTechRecommended(TechTypes eTech, AdvisorTypes eAdvisor);
// TODO(Phase1 audit): CvAdvisorRecommender::AdvisorInterestInFlavor MISMATCH: Instruction 4 differs before first target reference: object [sub    $0x10,%esp] vs BE [sub    $0x20,%esp]; BE instructions=32; Civ5 changed/new=UNVERIFIED.
	int AdvisorInterestInFlavor(AdvisorTypes eAdvisor, FlavorTypes eFlavor);
// TODO(Phase1 audit): CvAdvisorRecommender::FindUnassignedAdvisorForTech UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=70; Civ5 changed/new=UNVERIFIED.
	AdvisorTypes FindUnassignedAdvisorForTech(PlayerTypes ePlayer, TechTypes eTech);
// TODO(Phase1 audit): CvAdvisorRecommender::FindUnassignedAdvisorForBuildable MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x2c,%esp] vs BE [sub    $0x3c,%esp]; BE instructions=112; Civ5 changed/new=UNVERIFIED.
	AdvisorTypes FindUnassignedAdvisorForBuildable(PlayerTypes ePlayer, CvCityBuildable& buildable);

	CvCityBuildable m_aRecommendedBuilds[NUM_ADVISOR_TYPES];
	TechTypes m_aRecommendedTechs[NUM_ADVISOR_TYPES];
	CvWeightedVector<int, 80, true> m_aResearchableTechs;
	CvWeightedVector<int, NUM_ADVISOR_TYPES, true> m_aFinalRoundTechs;
	CvWeightedVector<CvCityBuildable, 50, true> m_aCityBuildables;
	CvWeightedVector<CvCityBuildable, NUM_ADVISOR_TYPES, true> m_aFinalRoundBuildables;
};
