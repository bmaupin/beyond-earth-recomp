#pragma once
#include "CvGameCoreDLLUtil/CvEnums.h"

class CvTechXMLEntries;
class CvTeam;
class FDataStream;

// TODO: CvTechEntry, CvTechXMLEntries, CvTechAI and CvPlayerTechs.
class CvTeamTechs
{
public:
	CvTeamTechs(void);
	~CvTeamTechs(void);
	void Init(CvTechXMLEntries* pTechs, CvTeam* pTeam);
	void Uninit();
	void Reset();
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream);

	void SetHasTech(TechTypes eIndex, bool bNewValue);
	bool HasTech(TechTypes eIndex) const;
	TechTypes GetLastTechAcquired() const;
	void SetLastTechAcquired(TechTypes eTech);
	int GetNumTechsKnown() const;
	bool HasResearchedAllTechs() const;
	void SetNoTradeTech(TechTypes eIndex, bool bNewValue);
	bool IsNoTradeTech(TechTypes eIndex) const;
	void IncrementTechCount(TechTypes eIndex);
	int GetTechCount(TechTypes eIndex) const;
	void SetResearchProgress(TechTypes eIndex, int iNewValue, PlayerTypes ePlayer);
	void SetResearchProgressTimes100(TechTypes eIndex, int iNewValue, PlayerTypes ePlayer);
	int GetResearchProgress(TechTypes eIndex) const;
	int GetResearchProgressTimes100(TechTypes eIndex) const;
	void ChangeResearchProgress(TechTypes eIndex, int iChange, PlayerTypes ePlayer);
	void ChangeResearchProgressTimes100(TechTypes eIndex, int iChange, PlayerTypes ePlayer);
	int ChangeResearchProgressPercent(TechTypes eIndex, int iPercent, PlayerTypes ePlayer);
	int GetResearchCost(TechTypes eTech) const;
	int GetResearchLeft(TechTypes eTech) const;
	CvTechXMLEntries* GetTechs() const;

private:
	int GetMaxResearchOverflow(TechTypes eTech, PlayerTypes ePlayer) const;
	TechTypes m_eLastTechAcquired;
	bool* m_pabHasTech;
	bool* m_pabNoTradeTech;
	int* m_paiResearchProgress; // Stored in hundredths
	int* m_paiTechCount;
	CvTechXMLEntries* m_pTechs;
	CvTeam* m_pTeam;
};
