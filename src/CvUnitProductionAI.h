#pragma once

#ifndef CIV5_UNIT_PRODUCTION_AI_H
#define CIV5_UNIT_PRODUCTION_AI_H

#include "CvWeightedVector.h"

#define SAFE_ESTIMATE_NUM_UNITS 90

class CvCity;
class CvUnitXMLEntries;

class CvUnitProductionAI
{
public:
// TODO(Phase1 audit): CvUnitProductionAI::CvUnitProductionAI UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=14; Civ5 changed/new=UNVERIFIED.
	CvUnitProductionAI(CvCity* pCity, CvUnitXMLEntries* pUnits);
// TODO(Phase1 audit): CvUnitProductionAI::~CvUnitProductionAI UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	~CvUnitProductionAI(void);

// TODO(Phase1 audit): CvUnitProductionAI::Reset UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=37; Civ5 changed/new=UNVERIFIED.
	void Reset();
// TODO(Phase1 audit): CvUnitProductionAI::Read UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=107; Civ5 changed/new=UNVERIFIED.
	void Read(FDataStream& kStream);
// TODO(Phase1 audit): CvUnitProductionAI::Write UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=109; Civ5 changed/new=UNVERIFIED.
	void Write(FDataStream& kStream) const;

// TODO(Phase1 audit): CvUnitProductionAI::AddFlavorWeights UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=40; Civ5 changed/new=UNVERIFIED.
	void AddFlavorWeights(FlavorTypes eFlavor, int iWeight);
// TODO(Phase1 audit): CvUnitProductionAI::AddQuestWeights UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=53; Civ5 changed/new=UNVERIFIED.
	void AddQuestWeights();
// TODO(Phase1 audit): CvUnitProductionAI::GetWeight UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=5; Civ5 changed/new=UNVERIFIED.
	int GetWeight(UnitTypes eUnit);
// TODO(Phase1 audit): CvUnitProductionAI::RecommendUnit UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=101; Civ5 changed/new=UNVERIFIED.
	UnitTypes RecommendUnit(UnitAITypes eUnitAIType = NO_UNITAI);
// TODO(Phase1 audit): CvUnitProductionAI::LogPossibleBuilds UNVERIFIED: CURRENT translation unit fails compilation: CvQuest redefinition and incompatible GetTechAIWeight declaration; no current object; BE instructions=419; Civ5 changed/new=UNVERIFIED.
	void LogPossibleBuilds(UnitAITypes eUnitAIType = NO_UNITAI);

private:
	CvCity* m_pCity;
	CvUnitXMLEntries* m_pUnits;
	CvWeightedVector<int, SAFE_ESTIMATE_NUM_UNITS, true> m_UnitAIWeights;
	CvWeightedVector<int, SAFE_ESTIMATE_NUM_UNITS, true> m_Buildables;
};

#endif // CIV5_UNIT_PRODUCTION_AI_H
