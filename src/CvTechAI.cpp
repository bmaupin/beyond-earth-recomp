#include "CvGameCoreDLLPCH.h"
#include "CvTechClasses.h"
#include "CvInfosSerializationHelper.h"
#include <cmath>
#include <vector>

CvTechAI::CvTechAI(CvPlayerTechs* currentTechs) : m_pCurrentTechs(currentTechs)
{
}

CvTechAI::~CvTechAI()
{
}

void CvTechAI::Reset()
{
	m_TechAIWeights.clear();
	if (!m_pCurrentTechs) return;
	CvTechXMLEntries* pTechs = m_pCurrentTechs->GetTechs();
	if (!pTechs) return;
	for (int i = 0; i < pTechs->GetNumTechs(); ++i)
		m_TechAIWeights.push_back(i, 0);
}

void CvTechAI::Read(FDataStream& kStream)
{
	unsigned int uiVersion;
	kStream >> uiVersion;
	const int iTechCount = m_pCurrentTechs->GetTechs()->GetNumTechs();
	m_TechAIWeights.clear();
	m_TechAIWeights.resize(iTechCount);
	for (int i = 0; i < iTechCount; ++i) m_TechAIWeights.SetWeight(i, 0);

	int iCount;
	kStream >> iCount;
	for (int i = 0; i < iCount; ++i)
	{
		const int iIndex = CvInfosSerializationHelper::ReadHashed(kStream);
		int iWeight;
		kStream >> iWeight;
		if (iIndex >= 0 && iIndex < iTechCount) m_TechAIWeights.SetWeight(iIndex, iWeight);
	}
}

void CvTechAI::Write(FDataStream& kStream) const
{
	const unsigned int uiVersion = 1;
	kStream << uiVersion;
	const unsigned int uiCount = m_pCurrentTechs->GetTechs()->GetNumTechs();
	kStream << uiCount;
	for (unsigned int i = 0; i < uiCount; ++i)
	{
		CvInfosSerializationHelper::WriteHashed(kStream, m_pCurrentTechs->GetTechs()->GetEntry(i));
		const int iWeight = m_TechAIWeights.GetWeight(i);
		kStream << iWeight;
	}
}

int CvTechAI::GetQuestSpecificWeight(TechTypes eTech, int& iWeight, int& iPropagationPercent) const
{
	iWeight = 0;
	iPropagationPercent = 0;
	if (GC.getGame().getGameTurn() < 150) return 0;

	CvPlayer* pPlayer = m_pCurrentTechs->GetPlayer();
	const CvQuest* pQuest = pPlayer->GetGrandStrategyAI()->GetActiveGrandStrategyQuest();
	if (pQuest && pQuest->GetTechAIWeight(eTech) > 0)
	{
		iWeight = 500;
		iPropagationPercent = pPlayer->GetGameProgress() >= 3 ? 3 : 2;
		return iWeight;
	}

	const AffinityType eNeed = pPlayer->GetGrandStrategyAI()->GetVictoryAffinityNeed(NULL);
	CvTechEntry* pTech = GC.getTechInfo(eTech);
	if (eNeed != NO_AFFINITY_TYPE && pTech && pTech->GetAffinityValue(eNeed) > 0)
	{
		iWeight = 300;
		iPropagationPercent = 2;
	}
	return iWeight;
}

void CvTechAI::AddQuestWeights(int iWeight)
{
	if (!m_pCurrentTechs) return;
	for (int i = 0; i < m_pCurrentTechs->GetTechs()->GetNumTechs(); ++i)
	{
		int iQuestWeight, iPropagationPercent;
		if (GetQuestSpecificWeight((TechTypes)i, iQuestWeight, iPropagationPercent) > 0)
		{
			WeightConnections(i, iQuestWeight, iPropagationPercent, iWeight);
			m_TechAIWeights.IncreaseWeight(i, iQuestWeight);
		}
	}
}

void CvTechAI::WeightConnections(int iTech, int iWeight, int iPropagationPercent, int iPropagationLevel)
{
	CvTechEntry* pSeed = m_pCurrentTechs->GetTechs()->GetEntry(iTech);
	if (!pSeed || iPropagationLevel <= 0) return;

	const int iTechCount = m_pCurrentTechs->GetTechs()->GetNumTechs();
	std::vector<bool> visited(iTechCount, false);
	std::vector<int> current;
	visited[iTech] = true;
	for (int i = 0; i < pSeed->GetNumConnectedTechs(); ++i)
	{
		const int iConnected = pSeed->GetConnectedTechs(i);
		if (iConnected >= 0 && iConnected < iTechCount && !visited[iConnected])
		{
			visited[iConnected] = true;
			current.push_back(iConnected);
		}
	}

	for (int iLevel = 1; iLevel <= iPropagationLevel && !current.empty(); ++iLevel)
	{
		const int iLevelWeight = (int)(((float)iWeight * iPropagationPercent) / (iLevel * 100.0f));
		std::vector<int> next;
		for (size_t i = 0; i < current.size(); ++i)
		{
			const int iCurrent = current[i];
			if (!m_pCurrentTechs->IsResearched((TechTypes)iCurrent))
				m_TechAIWeights.IncreaseWeight(iCurrent, iLevelWeight);

			CvTechEntry* pCurrent = m_pCurrentTechs->GetTechs()->GetEntry(iCurrent);
			if (!pCurrent) continue;
			for (int j = 0; j < pCurrent->GetNumConnectedTechs(); ++j)
			{
				const int iConnected = pCurrent->GetConnectedTechs(j);
				if (iConnected >= 0 && iConnected < iTechCount && !visited[iConnected])
				{
					visited[iConnected] = true;
					next.push_back(iConnected);
				}
			}
		}
		current.swap(next);
	}
}

void CvTechAI::AddFlavorWeights(FlavorTypes eFlavor, int iWeight, int iPropagationPercent)
{
	const int iCount = m_pCurrentTechs->GetTechs()->GetNumTechs();
	for (int i = 0; i < iCount; ++i)
	{
		CvTechEntry* pTech = m_pCurrentTechs->GetTechs()->GetEntry(i);
		if (!pTech) continue;
		const int iTechWeight = pTech->GetFlavorValue(eFlavor) * iWeight;
		if (iTechWeight) WeightConnections(i, iTechWeight, iPropagationPercent, 1);
		m_TechAIWeights.IncreaseWeight(i, iTechWeight);
	}
}

TechTypes CvTechAI::ChooseNextTech(bool bFreeTech)
{
	m_ResearchableTechs.clear();
	for (int i = 0; i < m_pCurrentTechs->GetTechs()->GetNumTechs(); ++i)
		if (m_pCurrentTechs->CanResearch((TechTypes)i) && (!bFreeTech || m_pCurrentTechs->CanResearchForFree((TechTypes)i)))
			m_ResearchableTechs.push_back(i, m_TechAIWeights.GetWeight(i));
	ReweightByAffinity();
	if (!bFreeTech) ReweightByCost();
	ReweightByStrategy();
	m_ResearchableTechs.SortItems();
	LogPossibleResearch();
	if (!m_ResearchableTechs.size()) return NO_TECH;
	RandomNumberDelegate fcn(&GC.getGame(), &CvGame::getGameRandNum);
	const TechTypes eTech = (TechTypes)(m_ResearchableTechs.GetTotalWeight() > 0 ?
		m_ResearchableTechs.ChooseFromTopChoices(GC.getGame().getHandicapInfo().GetAITechNumOptions(), &fcn, "Choosing tech from Top Choices") :
		m_ResearchableTechs.ChooseAtRandom(&fcn, "Choosing tech at random"));
	LogResearchChoice(eTech);
	return eTech;
}

void CvTechAI::ReweightByAffinity()
{
	CvPlayer* pPlayer = m_pCurrentTechs->GetPlayer();
	const AffinityType eNeed = pPlayer->GetGrandStrategyAI()->GetVictoryAffinityNeed(NULL);
	for (int i = 0; i < m_ResearchableTechs.size(); ++i)
	{
		AffinityType eAffinity = NO_AFFINITY_TYPE;
		int iAffinityWeight = 0;
		int iMultiplier = 5;
		const TechTypes eTech = (TechTypes)m_ResearchableTechs.GetElement(i);
		if (IsAffinityBooster(eTech, &eAffinity, &iAffinityWeight))
			iMultiplier = eAffinity == eNeed ? 20 : 5;
		else if (HasLeafAffinityMatch(eNeed, eTech, &iAffinityWeight))
			iMultiplier = 5;
		else
			continue;
		if (eAffinity != NO_AFFINITY_TYPE && pPlayer->GetAffinities()->GetAffinityLevel(eAffinity) > 9) continue;
		m_ResearchableTechs.IncreaseWeight(i, iMultiplier * iAffinityWeight);
	}
}

void CvTechAI::ReweightByCost()
{
	for (int i = 0; i < m_ResearchableTechs.size(); ++i)
	{
		const int iTurns = m_pCurrentTechs->GetResearchTurnsLeft((TechTypes)m_ResearchableTechs.GetElement(i), true);
		const double fDivisor = pow((double)iTurns, GC.getAI_RESEARCH_WEIGHT_BASE_MOD() + GC.getAI_RESEARCH_WEIGHT_MOD_PER_TURN_LEFT() * iTurns);
		m_ResearchableTechs.SetWeight(i, (int)(m_ResearchableTechs.GetWeight(i) / fDivisor));
	}
}

void CvTechAI::ReweightByStrategy()
{
	CvPlayer* pPlayer = m_pCurrentTechs->GetPlayer();
	int iIter = 0;
	for (const CvCity* pCity = pPlayer->firstCity(&iIter); pCity; pCity = pPlayer->nextCity(&iIter))
	{
		const int eStrategy = GC.getInfoTypeForString("AICITYSTRATEGY_NEED_NAVAL_GROWTH", false);
		if (!pCity->GetCityStrategyAI()->IsUsingCityStrategy(eStrategy)) continue;
		const int iTech = GC.getInfoTypeForString("TECH_PIONEERING", false);
		for (int i = 0; i < m_ResearchableTechs.size(); ++i)
			if (m_ResearchableTechs.GetElement(i) == iTech) m_ResearchableTechs.SetWeight(i, m_ResearchableTechs.GetWeight(i) * 10);
		break;
	}
}

void CvTechAI::LogPossibleResearch()
{
	if (!GC.getLogging() || !GC.getAILogging()) return;
	CvString playerName = m_pCurrentTechs->GetPlayer()->getCivilizationShortDescription();
	FILogFile* pLog = LOGFILEMGR.GetLog(GetLogFileName(playerName), FILogFile::kDontTimeStamp);
	for (int i = 0; i < m_ResearchableTechs.size(); ++i)
	{
		CvTechEntry* pTech = GC.getTechInfo((TechTypes)m_ResearchableTechs.GetElement(i));
		pLog->Msg("%03d, %s, %s, %d", GC.getGame().getElapsedGameTurns(), playerName.c_str(), pTech ? pTech->GetType() : "Unknown Tech", m_ResearchableTechs.GetWeight(i));
	}
}

void CvTechAI::LogResearchChoice(TechTypes eTech)
{
	if (!GC.getLogging() || !GC.getAILogging()) return;
	CvString playerName = m_pCurrentTechs->GetPlayer()->getCivilizationShortDescription();
	CvTechEntry* pTech = GC.getTechInfo(eTech);
	LOGFILEMGR.GetLog(GetLogFileName(playerName), FILogFile::kDontTimeStamp)->Msg("%03d, %s, CHOSEN, %s", GC.getGame().getElapsedGameTurns(), playerName.c_str(), pTech ? pTech->GetType() : "Unknown Tech");
}

TechTypes CvTechAI::RecommendNextTech(TechTypes eIgnoreTech)
{
	m_ResearchableTechs.clear();
	for (int i = 0; i < m_pCurrentTechs->GetTechs()->GetNumTechs(); ++i)
		if (i != eIgnoreTech && m_pCurrentTechs->CanResearch((TechTypes)i)) m_ResearchableTechs.push_back(i, m_TechAIWeights.GetWeight(i));
	ReweightByCost();
	m_ResearchableTechs.SortItems();
	LogPossibleResearch();
	if (m_ResearchableTechs.GetTotalWeight() <= 0) return NO_TECH;
	const TechTypes eTech = (TechTypes)m_ResearchableTechs.GetElement(0);
	LogResearchChoice(eTech);
	return eTech;
}

float CvTechAI::GetTechRatio()
{
	struct LeaderWithNumTechs
	{
		PlayerTypes eLeader;
		int iNumTechs;
	};

	std::vector<LeaderWithNumTechs> leaders;
	for (int i = 0; i < 22; ++i)
	{
		CvPlayerAI& kPlayer = GET_PLAYER((PlayerTypes)i);
		if (kPlayer.isEverAlive())
			leaders.push_back(LeaderWithNumTechs{ (PlayerTypes)i, kPlayer.GetPlayerTechs()->GetNumTechsKnown() });
	}
	for (size_t i = 1; i < leaders.size(); ++i)
	{
		LeaderWithNumTechs value = leaders[i];
		size_t j = i;
		while (j > 0 && leaders[j - 1].iNumTechs > value.iNumTechs)
		{
			leaders[j] = leaders[j - 1];
			--j;
		}
		leaders[j] = value;
	}
	for (size_t i = 0; i < leaders.size(); ++i)
		if (leaders[i].eLeader == m_pCurrentTechs->GetPlayer()->GetID())
			return leaders.size() >= 2 ? (float)i / (leaders.size() - 1) : 0.0f;
	return 0.0f;
}

bool CvTechAI::IsAffinityMatch(const CvPlayerAI& kPlayer, TechTypes eTech)
{
	const AffinityType eAffinity = kPlayer.GetGrandStrategyAI()->GetVictoryAffinityNeed(NULL);
	CvTechEntry* pTech = GC.getTechInfo(eTech);
	return eAffinity != NO_AFFINITY_TYPE && pTech && pTech->GetAffinityValue(eAffinity) > 0;
}

bool CvTechAI::HasLeafAffinityMatch(AffinityType eAffinity, TechTypes eTech, int* piWeight)
{
	if (eAffinity == NO_AFFINITY_TYPE) return false;
	CvTechEntry* pTech = GC.getTechInfo(eTech);
	if (!pTech) return false;
	for (int i = 0; i < pTech->GetNumConnectedTechs(); ++i)
	{
		CvTechEntry* pConnectedTech = GC.getTechInfo(pTech->GetConnectedTechs(i));
		if (pConnectedTech && pConnectedTech->IsLeafTech())
		{
			const int iWeight = pConnectedTech->GetAffinityValue(eAffinity);
			if (iWeight > 0)
			{
				if (piWeight) *piWeight = iWeight;
				return true;
			}
		}
	}
	return false;
}

bool CvTechAI::IsAffinityBooster(TechTypes eTech, AffinityType* peAffinity, int* piWeight)
{
	CvTechEntry* pTech = GC.getTechInfo(eTech);
	if (!pTech) return false;
	for (int i = 0; i < GC.getNumAffinityInfos(); ++i)
	{
		const int iWeight = pTech->GetAffinityValue((AffinityType)i);
		if (iWeight > 0)
		{
			*peAffinity = (AffinityType)i;
			*piWeight = iWeight;
			return true;
		}
	}
	return false;
}

bool CvTechAI::ShouldBoostNonChosenAffinity(const CvPlayerAI& kPlayer) const
{
	const AffinityType eAffinity = kPlayer.GetGrandStrategyAI()->GetVictoryAffinityNeed(NULL);
	return eAffinity == NO_AFFINITY_TYPE || kPlayer.GetAffinities()->GetAffinityLevel(eAffinity) <= 9;
}

CvString CvTechAI::GetLogFileName(CvString& playerName) const
{
	if (!GC.getPlayerAndCityAILogSplit()) return CvString("TechAILog.csv");
	CvString result;
	result.Format("TechAILog_%s.csv", playerName.c_str());
	return result;
}

int CvTechAI::GetWeight(TechTypes eTech)
{
	return m_TechAIWeights.GetWeight(eTech);
}
