#include "CvGameCoreDLLPCH.h"
#include "CvTechClasses.h"
#include "CvInfosSerializationHelper.h"
#include <cmath>
#include <vector>

CvTechAI::CvTechAI(CvPlayerTechs* currentTechs) : m_pCurrentTechs(currentTechs)
{
}

// TODO(Phase1 audit): CvTechAI::~CvTechAI UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
CvTechAI::~CvTechAI()
{
}

// TODO(Phase1 audit): CvTechAI::Reset UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=41; Civ5 changed/new=UNVERIFIED.
void CvTechAI::Reset()
{
	m_TechAIWeights.clear();
	if (!m_pCurrentTechs) return;
	CvTechXMLEntries* pTechs = m_pCurrentTechs->GetTechs();
	if (!pTechs) return;
	for (int i = 0; i < pTechs->GetNumTechs(); ++i)
		m_TechAIWeights.push_back(i, 0);
}

// TODO(Phase1 audit): CvTechAI::Read UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=73; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::Write UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=47; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::GetQuestSpecificWeight UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=95; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::AddQuestWeights MISMATCH: Instruction 2 differs before first target reference: object [push   %ebx] vs BE [mov    %esp,%ebp]; BE instructions=133; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::WeightConnections MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x5c,%esp] vs BE [sub    $0xac,%esp]; BE instructions=256; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::AddFlavorWeights MISMATCH: Instruction 2 differs before first target reference: object [push   %ebx] vs BE [mov    %esp,%ebp]; BE instructions=127; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::ChooseNextTech UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=120; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::ReweightByAffinity UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=84; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::ReweightByCost MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x3c,%esp] vs BE [sub    $0x1c,%esp]; BE instructions=46; Civ5 changed/new=UNVERIFIED.
void CvTechAI::ReweightByCost()
{
	for (int i = 0; i < m_ResearchableTechs.size(); ++i)
	{
		const int iTurns = m_pCurrentTechs->GetResearchTurnsLeft((TechTypes)m_ResearchableTechs.GetElement(i), true);
		const double fDivisor = pow((double)iTurns, GC.getAI_RESEARCH_WEIGHT_BASE_MOD() + GC.getAI_RESEARCH_WEIGHT_MOD_PER_TURN_LEFT() * iTurns);
		m_ResearchableTechs.SetWeight(i, (int)(m_ResearchableTechs.GetWeight(i) / fDivisor));
	}
}

// TODO(Phase1 audit): CvTechAI::ReweightByStrategy UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=75; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::LogPossibleResearch MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x4c,%esp] vs BE [sub    $0x9c,%esp]; BE instructions=295; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::LogResearchChoice MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x3c,%esp] vs BE [sub    $0x8c,%esp]; BE instructions=210; Civ5 changed/new=UNVERIFIED.
void CvTechAI::LogResearchChoice(TechTypes eTech)
{
	if (!GC.getLogging() || !GC.getAILogging()) return;
	CvString playerName = m_pCurrentTechs->GetPlayer()->getCivilizationShortDescription();
	CvTechEntry* pTech = GC.getTechInfo(eTech);
	LOGFILEMGR.GetLog(GetLogFileName(playerName), FILogFile::kDontTimeStamp)->Msg("%03d, %s, CHOSEN, %s", GC.getGame().getElapsedGameTurns(), playerName.c_str(), pTech ? pTech->GetType() : "Unknown Tech");
}

// TODO(Phase1 audit): CvTechAI::RecommendNextTech MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x2c,%esp] vs BE [sub    $0x1c,%esp]; BE instructions=85; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::GetTechRatio MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x3c,%esp] vs BE [sub    $0x5c,%esp]; BE instructions=151; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::IsAffinityMatch MISMATCH: Instruction 2 differs before first target reference: object [push   %edi] vs BE [push   %esi]; BE instructions=29; Civ5 changed/new=UNVERIFIED.
bool CvTechAI::IsAffinityMatch(const CvPlayerAI& kPlayer, TechTypes eTech)
{
	const AffinityType eAffinity = kPlayer.GetGrandStrategyAI()->GetVictoryAffinityNeed(NULL);
	CvTechEntry* pTech = GC.getTechInfo(eTech);
	return eAffinity != NO_AFFINITY_TYPE && pTech && pTech->GetAffinityValue(eAffinity) > 0;
}

// TODO(Phase1 audit): CvTechAI::HasLeafAffinityMatch UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=67; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::IsAffinityBooster UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=51; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTechAI::ShouldBoostNonChosenAffinity MISMATCH: Instruction 2 differs before first target reference: object [push   %edi] vs BE [sub    $0x8,%esp]; BE instructions=24; Civ5 changed/new=UNVERIFIED.
bool CvTechAI::ShouldBoostNonChosenAffinity(const CvPlayerAI& kPlayer) const
{
	const AffinityType eAffinity = kPlayer.GetGrandStrategyAI()->GetVictoryAffinityNeed(NULL);
	return eAffinity == NO_AFFINITY_TYPE || kPlayer.GetAffinities()->GetAffinityLevel(eAffinity) <= 9;
}

// TODO(Phase1 audit): CvTechAI::GetLogFileName MISMATCH: Instruction 2 differs before first target reference: object [push   %esi] vs BE [push   %edi]; BE instructions=83; Civ5 changed/new=UNVERIFIED.
CvString CvTechAI::GetLogFileName(CvString& playerName) const
{
	if (!GC.getPlayerAndCityAILogSplit()) return CvString("TechAILog.csv");
	CvString result;
	result.Format("TechAILog_%s.csv", playerName.c_str());
	return result;
}

// TODO(Phase1 audit): CvTechAI::GetWeight MISMATCH: First instruction opcode differs: object push, BE mov; BE instructions=5; Civ5 changed/new=UNVERIFIED.
int CvTechAI::GetWeight(TechTypes eTech)
{
	return m_TechAIWeights.GetWeight(eTech);
}
