#include "CvGameCoreDLLPCH.h"
#include "ICvDLLUserInterface.h"
#include "CvGameCoreUtils.h"
#include "CvDatabaseUtility.h"
#include <cmath>

#include "LintFree.h"

// Beyond Earth's deletion ABI passes the allocation size (Clang 3.4 lacks sized delete expressions).
void operator delete(void*, size_t) noexcept;

// Beyond Earth adds affinity requirements and plot-project improvement identifiers.
CvProjectEntry::CvProjectEntry(void):
	m_constructionImprovementType(NO_IMPROVEMENT),
	m_completeImprovementType(NO_IMPROVEMENT),
	m_obsoleteProject(NO_PROJECT),
	m_piResourceQuantityRequirements(NULL),
	m_piVictoryThreshold(NULL),
	m_piVictoryMinThreshold(NULL),
	m_piProjectsNeeded(NULL),
	m_piAffinityPrereqs(NULL),
	m_piFlavorValue(NULL)
{
}

// Beyond Earth adds an affinity array and shifts the remaining arrays and strings.
CvProjectEntry::~CvProjectEntry(void)
{
	SAFE_DELETE_ARRAY(m_piResourceQuantityRequirements);
	SAFE_DELETE_ARRAY(m_piVictoryThreshold);
	SAFE_DELETE_ARRAY(m_piVictoryMinThreshold);
	SAFE_DELETE_ARRAY(m_piProjectsNeeded);
	SAFE_DELETE_ARRAY(m_piAffinityPrereqs);
	SAFE_DELETE_ARRAY(m_piFlavorValue);
}

// TODO: Match CacheResults register allocation and exception cleanup (354 target instructions).
// Beyond Earth replaces nuclear/space flags with plot-project and affinity prerequisites.
bool CvProjectEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults, kUtility))
		return false;

	m_iMaxGlobalInstances = kResults.GetInt("MaxGlobalInstances");
	m_iMaxTeamInstances = kResults.GetInt("MaxTeamInstances");
	m_iProductionCost = kResults.GetInt("Cost");
	m_iCultureBranchesRequired = kResults.GetInt("CultureBranchesRequired");
	m_iTechShare = kResults.GetInt("TechShare");
	m_iVictoryDelayPercent = kResults.GetInt("VictoryDelayPercent");
	m_isPlotProject = kResults.GetBool("PlotProject");
	m_useSpecialCost = kResults.GetBool("UseSpecialCost");
	m_onlyAllowedByQuest = kResults.GetBool("OnlyAllowedByQuest");
	m_strMovieArtDef = kResults.GetText("MovieDefineTag");

	const char* szPartialImprovement = kResults.GetText("PartialImprovement");
	m_constructionImprovementType = (ImprovementTypes)GC.getInfoTypeForString(szPartialImprovement, true);
	const char* szCompleteImprovement = kResults.GetText("CompleteImprovement");
	m_completeImprovementType = (ImprovementTypes)GC.getInfoTypeForString(szCompleteImprovement, true);
	const char* szObsoleteProject = kResults.GetText("ObsoleteProject");
	m_obsoleteProject = (ProjectTypes)GC.getInfoTypeForString(szObsoleteProject, true);
	const char* szVictoryPrereq = kResults.GetText("VictoryPrereq");
	m_iVictoryPrereq = GC.getInfoTypeForString(szVictoryPrereq, true);
	const char* szTechPrereq = kResults.GetText("TechPrereq");
	m_iTechPrereq = GC.getInfoTypeForString(szTechPrereq, true);
	const char* szBuildingPrereq = kResults.GetText("BuildingPrereq");
	m_iBuildingPrereq = GC.getInfoTypeForString(szBuildingPrereq, true);
	const char* szProjectPrereq = kResults.GetText("ProjectPrereq");
	m_iProjectPrereq = GC.getInfoTypeForString(szProjectPrereq, true);
	const char* szEveryoneSpecialUnit = kResults.GetText("EveryoneSpecialUnit");
	m_iEveryoneSpecialUnit = GC.getInfoTypeForString(szEveryoneSpecialUnit, true);
	const char* szCreateSound = kResults.GetText("CreateSound");
	SetCreateSound(szCreateSound);
	const char* szAnyonePrereqProject = kResults.GetText("AnyonePrereqProject");
	m_iAnyoneProjectPrereq = GC.getInfoTypeForString(szAnyonePrereqProject, true);

	const char* szProjectType = GetType();
	kUtility.PopulateArrayByValue(m_piResourceQuantityRequirements, "Resources", "Project_ResourceQuantityRequirements", "ResourceType", "ProjectType", szProjectType, "Quantity");
	{
		const int iNumVictories = kUtility.MaxRows("Victories");
		kUtility.InitializeArray(m_piVictoryThreshold, iNumVictories);
		kUtility.InitializeArray(m_piVictoryMinThreshold, iNumVictories);
		Database::Results kDBResults;
		char szQuery[512] = {0};
		sprintf_s(szQuery, "select VictoryType, Threshold, MinThreshold from Project_VictoryThresholds where ProjectType = '%s';", szProjectType);
		if(DB.Execute(kDBResults, szQuery))
		{
			while(kDBResults.Step())
			{
				const char* szVictoryType = kDBResults.GetText("VictoryType");
				const int idx = GC.getInfoTypeForString(szVictoryType, true);
				const int iThreshold = kDBResults.GetInt("Threshold");
				const int iMinThreshold = kDBResults.GetInt("MinThreshold");
				m_piVictoryThreshold[idx] = iThreshold;
				m_piVictoryMinThreshold[idx] = iMinThreshold;
			}
		}
	}
	kUtility.SetFlavors(m_piFlavorValue, "Project_Flavors", "ProjectType", szProjectType);
	kUtility.PopulateArrayByValue(m_piProjectsNeeded, "Projects", "Project_Prereqs", "PrereqProjectType", "ProjectType", szProjectType, "AmountNeeded");
	kUtility.PopulateArrayByValue(m_piAffinityPrereqs, "Affinity_Types", "Project_AffinityPrereqs", "AffinityType", "ProjectType", szProjectType, "Level");
	return true;
}

int CvProjectEntry::GetVictoryPrereq() const
{
	return m_iVictoryPrereq;
}

int CvProjectEntry::GetTechPrereq() const
{
	return m_iTechPrereq;
}

// Beyond Earth adds building and project prerequisites.
int CvProjectEntry::GetBuildingPrereq() const
{
	return m_iBuildingPrereq;
}

int CvProjectEntry::GetProjectPrereq() const
{
	return m_iProjectPrereq;
}

// Added prerequisites shift the SDK fields; authentic member declarations determine the offsets.
int CvProjectEntry::GetAnyoneProjectPrereq() const
{
	return m_iAnyoneProjectPrereq;
}

void CvProjectEntry::SetAnyoneProjectPrereq(int i)
{
	m_iAnyoneProjectPrereq = i;
}

int CvProjectEntry::GetMaxGlobalInstances() const
{
	return m_iMaxGlobalInstances;
}

int CvProjectEntry::GetMaxTeamInstances() const
{
	return m_iMaxTeamInstances;
}

int CvProjectEntry::GetProductionCost() const
{
	return m_iProductionCost;
}

int CvProjectEntry::GetCultureBranchesRequired() const
{
	return m_iCultureBranchesRequired;
}

int CvProjectEntry::GetTechShare() const
{
	return m_iTechShare;
}

int CvProjectEntry::GetEveryoneSpecialUnit() const
{
	return m_iEveryoneSpecialUnit;
}

int CvProjectEntry::GetVictoryDelayPercent() const
{
	return m_iVictoryDelayPercent;
}

int CvProjectEntry::GetFlavorValue(int i) const
{
	CvAssertMsg(i < GC.getNumFlavorTypes(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	if(i > -1 && i < GC.getNumFlavorTypes() && m_piFlavorValue)
		return m_piFlavorValue[i];
	return 0;
}

// Beyond Earth replaces spaceship/nuke flags with plot-project and quest flags.
bool CvProjectEntry::IsPlotProject() const
{
	return m_isPlotProject;
}

bool CvProjectEntry::UseSpecialCost() const
{
	return m_useSpecialCost;
}

bool CvProjectEntry::OnlyAllowedByQuest() const
{
	return m_onlyAllowedByQuest;
}

// Beyond Earth selects the first affinity with the greatest positive prerequisite.
AffinityType CvProjectEntry::GetPrimaryAffinityType() const
{
	AffinityType ePrimaryAffinity = NO_AFFINITY_TYPE;
	int iHighestPrereq = 0;
	for(int i = 0; i < GC.getNumAffinityInfos(); ++i)
	{
		int iPrereq = GetAffinityPrereq(i);
		if(iPrereq > 0 && iPrereq > iHighestPrereq)
		{
			iHighestPrereq = iPrereq;
			ePrimaryAffinity = (AffinityType)i;
		}
	}
	return ePrimaryAffinity;
}

int CvProjectEntry::GetAffinityPrereq(int i) const
{
	return m_piAffinityPrereqs ? m_piAffinityPrereqs[i] : 0;
}

const char* CvProjectEntry::GetMovieArtDef() const
{
	return m_strMovieArtDef;
}

ImprovementTypes CvProjectEntry::GetConstructionImprovementType() const
{
	return m_constructionImprovementType;
}

ImprovementTypes CvProjectEntry::GetCompleteImprovementType() const
{
	return m_completeImprovementType;
}

ProjectTypes CvProjectEntry::GetObsoleteProject() const
{
	return m_obsoleteProject;
}

const char* CvProjectEntry::GetCreateSound() const
{
	return m_strCreateSound;
}

void CvProjectEntry::SetCreateSound(const char* szVal)
{
	m_strCreateSound = szVal;
}

int CvProjectEntry::GetResourceQuantityRequirement(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	if(i > -1 && i < GC.getNumResourceInfos() && m_piResourceQuantityRequirements)
		return m_piResourceQuantityRequirements[i];
	return -1;
}

int CvProjectEntry::GetVictoryThreshold(int i) const
{
	CvAssertMsg(i < GC.getNumVictoryInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	if(i > -1 && i < GC.getNumVictoryInfos() && m_piVictoryThreshold)
		return m_piVictoryThreshold[i];
	return -1;
}

int CvProjectEntry::GetVictoryMinThreshold(int i) const
{
	CvAssertMsg(i < GC.getNumVictoryInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	if(i > -1 && i < GC.getNumVictoryInfos())
	{
		if(m_piVictoryMinThreshold && m_piVictoryMinThreshold[i] != 0)
			return m_piVictoryMinThreshold[i];
		return GetVictoryThreshold(i);
	}
	return 0;
}

int CvProjectEntry::GetProjectsNeeded(int i) const
{
	CvAssertMsg(i < GC.getNumProjectInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	if(i > -1 && i < GC.getNumProjectInfos() && m_piProjectsNeeded)
		return m_piProjectsNeeded[i];
	return 0;
}

// TODO: Match after restoring the two inline perks accessors declared in CvPlayer.h.
//       We need to implement as much of the relevant code in CvPlayer.h as possible and then compile again and see if it fixes this
int CvProjectHelpers::GetSpecialProductionCost(const CvCity* pCity, ProjectTypes eProject)
{
	CvProjectEntry* pProject = GC.getProjectInfo(eProject);
	if(!pProject)
		return 1;

	const CvPlayer* pPlayer = pCity->GetPlayer();
	int iProductionCost = pProject->GetProductionCost();
	if(eProject == GC.getPROJECT_MOVE_CITY())
	{
		CvPlayerPerks* pPerks = pPlayer->GetPlayerPerks();
		float fProductionCost = iProductionCost;
		CvCityBuildings* pBuildings = pCity->GetCityBuildings();
		int iNumBuildings = 1;
		if(pBuildings)
		{
			BuildingClassTypes eHeadquarters = (BuildingClassTypes)GC.getInfoTypeForString("BUILDINGCLASS_HEADQUARTERS");
			int iNumHeadquarters = 0;
			if(eHeadquarters != NO_BUILDINGCLASS)
				iNumHeadquarters = pBuildings->GetNumBuildingClass(eHeadquarters);
			iNumBuildings = std::max(1, pBuildings->GetNumBuildings() - iNumHeadquarters);
		}
		double fCost = fProductionCost + log((double)iNumBuildings) * (double)0.6f * 50.0;
		int iModifier = pCity->GetMoveCityCostModifier();
		if(pPerks)
		{
			iModifier += pPerks->GetCityMoveCostMod(*pCity);
			iModifier += pPerks->GetAquaticCityMoveCostMod();
		}
		iProductionCost = (int)fCost;
		if(iModifier != 0)
			iProductionCost += iProductionCost * iModifier / 100;
	}

	iProductionCost = iProductionCost * GC.getPROJECT_PRODUCTION_PERCENT() / 100;
	iProductionCost = iProductionCost * GC.getGame().getGameSpeedInfo().getCreatePercent() / 100;
	if(!pPlayer->isHuman() && !pPlayer->IsAITeammateOfHuman() && !pPlayer->isAlien() && !pPlayer->isNeutralProxy())
	{
		if(isWorldProject(eProject))
			iProductionCost = iProductionCost * GC.getGame().getHandicapInfo().getAIWorldCreatePercent() / 100;
		else
			iProductionCost = iProductionCost * GC.getGame().getHandicapInfo().getAICreatePercent() / 100;
	}
	return std::max(1, iProductionCost / 5 * 5);
}

CvProjectXMLEntries::CvProjectXMLEntries(void)
{
}

CvProjectXMLEntries::~CvProjectXMLEntries(void)
{
	DeleteArray();
}

std::vector<CvProjectEntry*>& CvProjectXMLEntries::GetProjectEntries()
{
	return m_paProjectEntries;
}

int CvProjectXMLEntries::GetNumProjects()
{
	return m_paProjectEntries.size();
}

void CvProjectXMLEntries::DeleteArray()
{
	for(std::vector<CvProjectEntry*>::iterator it = m_paProjectEntries.begin(); it != m_paProjectEntries.end(); ++it)
	{
		CvProjectEntry* pEntry = *it;
		if(pEntry)
		{
			pEntry->~CvProjectEntry();
			::operator delete(pEntry, sizeof(CvProjectEntry));
		}
		*it = NULL;
	}
	m_paProjectEntries.clear();
}

CvProjectEntry* CvProjectXMLEntries::GetEntry(int index)
{
	return m_paProjectEntries[index];
}
