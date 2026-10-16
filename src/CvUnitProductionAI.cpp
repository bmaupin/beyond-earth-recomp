/*	-------------------------------------------------------------------------------------------------------
	� 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#include "CvGameCoreDLLPCH.h"
#include "CvGameCoreDLLUtil.h"
#include "CvUnitProductionAI.h"
#include "CvGameCoreUtils.h"
// include this after all other headers
#include "LintFree.h"

// TODO: ScaleFlavorWeightByTime(FlavorTypes) (63 total instructions)
// ScaleFlavorWeightByTime(FlavorTypes eFlavor)

/// Constructor
CvUnitProductionAI::CvUnitProductionAI(CvCity* pCity,  CvUnitXMLEntries* pUnits):
	m_pCity(pCity),
	m_pUnits(pUnits)
{
}

/// Destructor
CvUnitProductionAI::~CvUnitProductionAI(void)
{
}

/// Clear out AI local variables
void CvUnitProductionAI::Reset()
{
	CvAssertMsg(m_pUnits != NULL, "Unit Production AI init failure: unit entries are NULL");

	m_UnitAIWeights.clear();

	// Loop through reading each one and add an entry with 0 weight to our vector
	if(m_pUnits)
	{
		for(int i = 0; i < m_pUnits->GetNumUnits(); i++)
		{
			m_UnitAIWeights.push_back(i, 0);
		}
	}
}

// TODO: CvUnitProductionAI::Read(FDataStream&) (111 total instructions); the fixed-buffer string support required to compile this source is incomplete.
// void CvUnitProductionAI::Read(FDataStream& kStream)

// TODO: CvUnitProductionAI::Write(FDataStream&) const (113 total instructions); the fixed-buffer string support required to compile this source is incomplete.
// void CvUnitProductionAI::Write(FDataStream& kStream) const

/// Establish weights for one flavor; can be called multiple times to layer strategies
void CvUnitProductionAI::AddFlavorWeights(FlavorTypes eFlavor, int iWeight)
{
	// Loop through all units
	for(int iUnit = 0; iUnit < m_pUnits->GetNumUnits(); iUnit++)
	{
		CvUnitEntry* entry = m_pUnits->GetEntry(iUnit);
		if(entry)
		{
			// Set its weight by looking at unit's weight for this flavor and using iWeight multiplier passed in
			m_UnitAIWeights.IncreaseWeight(iUnit, entry->GetFlavorValue(eFlavor) * iWeight);
		}
	}
}

// TODO: CvUnitProductionAI::GetWeight(UnitTypes) (5 total instructions, 4 differ)
// int CvUnitProductionAI::GetWeight(UnitTypes eUnit)

// TODO: CvUnitProductionAI::RecommendUnit(UnitAITypes) (101 total instructions, 28 differ)
// UnitTypes CvUnitProductionAI::RecommendUnit(UnitAITypes eUnitAIType)

// TODO: CvUnitProductionAI::LogPossibleBuilds(UnitAITypes) (419 total instructions, 106 differ)
// void CvUnitProductionAI::LogPossibleBuilds(UnitAITypes eUnitAIType)

// TODO: CvUnitProductionAI::AddQuestWeights() (54 total instructions)
// void CvUnitProductionAI::AddQuestWeights()
