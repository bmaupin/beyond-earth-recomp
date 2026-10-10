#pragma once

#ifndef CIV5_PROJECT_CLASSES_H
#define CIV5_PROJECT_CLASSES_H

class CvCity;

class CvProjectEntry: public CvBaseInfo
{
public:
	CvProjectEntry(void);
	~CvProjectEntry(void);
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

	int GetVictoryPrereq() const;
	int GetTechPrereq() const;
	int GetBuildingPrereq() const;
	int GetProjectPrereq() const;
	int GetAnyoneProjectPrereq() const;
	void SetAnyoneProjectPrereq(int i);
	int GetMaxGlobalInstances() const;
	int GetMaxTeamInstances() const;
	int GetProductionCost() const;
	int GetCultureBranchesRequired() const;
	int GetTechShare() const;
	int GetEveryoneSpecialUnit() const;
	int GetVictoryDelayPercent() const;
	int GetFlavorValue(int i) const;
	bool IsPlotProject() const;
	bool UseSpecialCost() const;
	bool OnlyAllowedByQuest() const;
	AffinityType GetPrimaryAffinityType() const;
	int GetAffinityPrereq(int i) const;
	const char* GetMovieArtDef() const;
	ImprovementTypes GetConstructionImprovementType() const;
	ImprovementTypes GetCompleteImprovementType() const;
	ProjectTypes GetObsoleteProject() const;
	const char* GetCreateSound() const;
	void SetCreateSound(const char* szVal);
	int GetResourceQuantityRequirement(int i) const;
	int GetVictoryThreshold(int i) const;
	int GetVictoryMinThreshold(int i) const;
	int GetProjectsNeeded(int i) const;

	// These SDK methods do not exist in Beyond Earth.
	// int GetNukeInterception() const;
	// bool IsSpaceship() const;
	// bool IsAllowsNukes() const;

protected:
	int m_iVictoryPrereq;
	int m_iTechPrereq;
	int m_iBuildingPrereq;
	int m_iProjectPrereq;
	int m_iAnyoneProjectPrereq;
	int m_iMaxGlobalInstances;
	int m_iMaxTeamInstances;
	int m_iProductionCost;
	int m_iCultureBranchesRequired;
	int m_iTechShare;
	int m_iEveryoneSpecialUnit;
	int m_iVictoryDelayPercent;
	bool m_isPlotProject;
	bool m_useSpecialCost;
	bool m_onlyAllowedByQuest;
	CvString m_strCreateSound;
	CvString m_strMovieArtDef;
	ImprovementTypes m_constructionImprovementType;
	ImprovementTypes m_completeImprovementType;
	ProjectTypes m_obsoleteProject;
	int* m_piResourceQuantityRequirements;
	int* m_piVictoryThreshold;
	int* m_piVictoryMinThreshold;
	int* m_piProjectsNeeded;
	int* m_piAffinityPrereqs;
	int* m_piFlavorValue;
};

class CvProjectXMLEntries
{
public:
	CvProjectXMLEntries(void);
	~CvProjectXMLEntries(void);
	std::vector<CvProjectEntry*>& GetProjectEntries();
	int GetNumProjects();
	CvProjectEntry* GetEntry(int index);
	void DeleteArray();

private:
	std::vector<CvProjectEntry*> m_paProjectEntries;
};

namespace CvProjectHelpers
{
	int GetSpecialProductionCost(const CvCity* pCity, ProjectTypes eProject);
}

#endif //CIV5_PROJECT_CLASSES_H