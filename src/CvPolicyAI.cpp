#include "CvGameCoreDLLPCH.h"
#include "CvPolicyAI.h"
#include "CvInfosSerializationHelper.h"

CvPolicyAI::CvPolicyAI(CvPlayerPolicies* currentPolicies) : m_pCurrentPolicies(currentPolicies)
{
}

CvPolicyAI::~CvPolicyAI()
{
}

void CvPolicyAI::Reset()
{
	m_PolicyAIWeights.clear();
	m_iPolicyWeightPropagationLevels = GC.getPOLICY_WEIGHT_PROPAGATION_LEVELS();
	m_iPolicyWeightPercentDropNewBranch = GC.getPOLICY_WEIGHT_PERCENT_DROP_NEW_BRANCH();
	for(int i = 0; i < m_pCurrentPolicies->GetPolicies()->GetNumPolicies(); ++i)
		m_PolicyAIWeights.push_back(i, 0);
}

void CvPolicyAI::Read(FDataStream& kStream)
{
	unsigned int uiVersion;
	kStream >> uiVersion;
	const int iNumPolicies = m_pCurrentPolicies->GetPolicies()->GetNumPolicies();
	m_PolicyAIWeights.clear();
	m_PolicyAIWeights.resize(iNumPolicies);
	for(int i = 0; i < iNumPolicies; ++i) m_PolicyAIWeights.SetWeight(i, 0);
	unsigned int uiCount;
	kStream >> uiCount;
	for(unsigned int i = 0; i < uiCount; ++i)
	{
		const int iPolicy = CvInfosSerializationHelper::ReadHashed(kStream);
		int iWeight;
		kStream >> iWeight;
		if(iPolicy >= 0 && iPolicy < iNumPolicies) m_PolicyAIWeights.SetWeight(iPolicy, iWeight);
	}
}

void CvPolicyAI::Write(FDataStream& kStream)
{
	const int iVersion = 1;
	kStream << iVersion;
	const unsigned int uiCount = m_pCurrentPolicies->GetPolicies()->GetNumPolicies();
	kStream << uiCount;
	for(unsigned int i = 0; i < uiCount; ++i)
	{
		CvInfosSerializationHelper::WriteHashed(kStream, (PolicyTypes)i);
		const int iWeight = m_PolicyAIWeights.GetWeight(i);
		kStream << iWeight;
	}
}

void CvPolicyAI::AddFlavorWeights(FlavorTypes eFlavor, int iWeight, int iPropagationPercent)
{
	CvPolicyXMLEntries* pPolicies = m_pCurrentPolicies->GetPolicies();
	int* weights = static_cast<int*>(__builtin_alloca(pPolicies->GetNumPolicies() * sizeof(int)));
	for(int i = 0; i < pPolicies->GetNumPolicies(); ++i)
	{
		CvPolicyEntry* pPolicy = pPolicies->GetPolicyEntry(i);
		weights[i] = pPolicy ? pPolicy->GetFlavorValue(eFlavor) * iWeight : 0;
	}
	if(iPropagationPercent > 0) WeightPrereqs(weights, iPropagationPercent);
	for(int i = 0; i < pPolicies->GetNumPolicies(); ++i) m_PolicyAIWeights.IncreaseWeight(i, weights[i]);
}

void CvPolicyAI::WeightPrereqs(int* paiTempWeights, int iPropagationPercent)
{
	for(int i = 0; i < m_pCurrentPolicies->GetPolicies()->GetNumPolicies(); ++i)
		if(paiTempWeights[i] > 0) PropagateWeights(i, paiTempWeights[i], iPropagationPercent, 0);
}

void CvPolicyAI::PropagateWeights(int iPolicy, int iWeight, int iPropagationPercent, int iPropagationLevel)
{
	if(iPropagationLevel >= m_iPolicyWeightPropagationLevels) return;
	const int iProduct = iWeight * iPropagationPercent;
	const int iPrereqWeight = iProduct / 100;
	for(int i = 0; i < GC.getNUM_OR_TECH_PREREQS(); ++i)
	{
		const int iPrereq = m_pCurrentPolicies->GetPolicies()->GetPolicyEntry(iPolicy)->GetPrereqOrPolicies(i);
		if(iPrereq == NO_POLICY) break;
		m_PolicyAIWeights.IncreaseWeight(iPrereq, iPrereqWeight);
		// The target advances the caller's level after passing it to each child.
		if(iProduct >= 100) PropagateWeights(iPrereq, iPrereqWeight, iPropagationPercent, iPropagationLevel++);
	}
}

int CvPolicyAI::WeightKickers(const std::vector<PolicyTypes>& kickers) const
{
	int iWeight = 0;
	for(std::vector<PolicyTypes>::const_iterator it = kickers.begin(); it != kickers.end(); ++it)
		if(*it != NO_POLICY) iWeight += m_PolicyAIWeights.GetWeight(*it);
	return iWeight;
}

int CvPolicyAI::ChooseNextVirtue(CvPlayer*)
{
	RandomNumberDelegate rand(&GC.getGame(), &CvGame::getGameRandNum);
	m_AdoptablePolicies.clear();
	CvPolicyXMLEntries* pPolicies = m_pCurrentPolicies->GetPolicies();
	for(int i = 0; i < pPolicies->GetNumPolicies(); ++i)
	{
		CvPolicyEntry* pPolicy = GC.getPolicyInfo((PolicyTypes)i);
		if(!m_pCurrentPolicies->CanAdoptPolicy((PolicyTypes)i, false) || !pPolicy || pPolicy->IsKickerPolicy()) continue;
		int iWeight = m_PolicyAIWeights.GetWeight(i);
		std::vector<PolicyTypes> kickers;
		if(m_pCurrentPolicies->GetNewKickersEarnedByAdoptingPolicy((PolicyTypes)i, kickers) > 0)
			iWeight += 3 * WeightKickers(kickers);
		m_AdoptablePolicies.push_back(i, iWeight);
	}
	m_AdoptablePolicies.SortItems();
	LogPossiblePolicies();
	int iChoice = NO_POLICY;
	if(m_AdoptablePolicies.size() > 0)
	{
		const int iTotal = m_AdoptablePolicies.GetTotalWeight();
		if(iTotal > 0)
			iChoice = m_AdoptablePolicies.ChooseFromTopChoices(GC.getGame().getHandicapInfo().GetAIVirtueNumOptions(), &rand, "Choosing virtue from Top Choices");
		else if(iTotal == 0)
			iChoice = m_AdoptablePolicies.ChooseAtRandom(&rand, "Choosing virtue at random (no good choices)");
	}
	if(iChoice != NO_POLICY) LogPolicyChoice((PolicyTypes)iChoice);
	return iChoice;
}

int CvPolicyAI::ChooseNextPolicy(CvPlayer* pPlayer)
{
	RandomNumberDelegate rand(&GC.getGame(), &CvGame::getGameRandNum);
	m_AdoptablePolicies.clear();
	std::vector<int> levelThree;
	CvPolicyXMLEntries* pPolicies = m_pCurrentPolicies->GetPolicies();
	const int iNumBranches = GC.getNumPolicyBranchInfos();
	const int iFreeTenets = pPlayer->GetNumFreeTenets();
	for(int i = 0; i < pPolicies->GetNumPolicies(); ++i)
	{
		if(!m_pCurrentPolicies->CanAdoptPolicy((PolicyTypes)i, false)) continue;
		CvPolicyEntry* pPolicy = pPolicies->GetPolicyEntry(i);
		if(iFreeTenets > 0 && pPolicy->GetLevel() <= 0) continue;
		int iWeight = m_PolicyAIWeights.GetWeight(i);
		if(m_pCurrentPolicies->WillFinishBranchIfAdopted((PolicyTypes)i))
		{
			const int iBranch = pPolicy->GetPolicyBranchType();
			if(iBranch != NO_POLICY_BRANCH_TYPE)
			{
				const int iFinisher = pPolicies->GetPolicyBranchEntry(iBranch)->GetFreeFinishingPolicy();
				if(iFinisher != NO_POLICY) iWeight += m_PolicyAIWeights.GetWeight(iFinisher);
			}
		}
		m_AdoptablePolicies.push_back(i + iNumBranches, iWeight);
		if(pPolicy->GetLevel() == 3) levelThree.push_back(i);
	}
	bool bExclusiveUnlocked = false;
	for(int i = 0; i < iNumBranches; ++i)
	{
		CvPolicyBranchEntry* pBranch = GC.getPolicyBranchInfo((PolicyBranchTypes)i);
		if(pBranch && pPlayer->GetPlayerPolicies()->IsPolicyBranchUnlocked((PolicyBranchTypes)i) && pBranch->IsMutuallyExclusive())
			bExclusiveUnlocked = true;
	}
	const int iCultureStrategy = GC.getInfoTypeForString("AIGRANDSTRATEGY_CULTURE");
	const int iActiveStrategy = pPlayer->GetGrandStrategyAI()->GetActiveGrandStrategy();
	for(int i = 0; iFreeTenets <= 0 && i < iNumBranches; ++i)
	{
		CvPolicyBranchEntry* pBranch = GC.getPolicyBranchInfo((PolicyBranchTypes)i);
		if(!pBranch || (bExclusiveUnlocked && pBranch->IsMutuallyExclusive())) continue;
		if(!pPlayer->GetPlayerPolicies()->CanUnlockPolicyBranch((PolicyBranchTypes)i) || pPlayer->GetPlayerPolicies()->IsPolicyBranchUnlocked((PolicyBranchTypes)i)) continue;
		int iWeight = 0;
		if(IsBranchEffectiveInGame((PolicyBranchTypes)i))
			iWeight = WeighBranch((PolicyBranchTypes)i) * (100 - m_iPolicyWeightPercentDropNewBranch) / (iActiveStrategy == iCultureStrategy ? 300 : 100);
		m_AdoptablePolicies.push_back(i, iWeight);
	}
	m_AdoptablePolicies.SortItems();
	LogPossiblePolicies();
	const char* strategies[] = { "AIGRANDSTRATEGY_CONQUEST", "AIGRANDSTRATEGY_SPACESHIP", "AIGRANDSTRATEGY_UNITED_NATIONS", "AIGRANDSTRATEGY_CULTURE" };
	const char* flavors[] = { "FLAVOR_OFFENSE", "FLAVOR_SPACESHIP", "FLAVOR_DIPLOMACY", "FLAVOR_CULTURE" };
	for(std::vector<int>::const_iterator it = levelThree.begin(); it != levelThree.end(); ++it)
	{
		CvPolicyEntry* pPolicy = pPolicies->GetPolicyEntry(*it);
		for(int i = 0; i < 4; ++i)
			if(iActiveStrategy == GC.getInfoTypeForString(strategies[i]) && pPolicy->GetFlavorValue(GC.getInfoTypeForString(flavors[i])) > 0)
			{
				LogPolicyChoice((PolicyTypes)*it);
				return *it + iNumBranches;
			}
	}
	if(m_AdoptablePolicies.size() == 0) return NO_POLICY;
	const int iTotal = m_AdoptablePolicies.GetTotalWeight();
	int iChoice;
	if(iTotal > 0)
		iChoice = m_AdoptablePolicies.ChooseFromTopChoices(GC.getGame().getHandicapInfo().GetAIVirtueNumOptions(), &rand, "Choosing policy from Top Choices");
	else if(iTotal == 0)
		iChoice = m_AdoptablePolicies.ChooseAtRandom(&rand, "Choosing policy at random (no good choices)");
	else return NO_POLICY;
	if(iChoice < iNumBranches) LogBranchChoice((PolicyBranchTypes)iChoice);
	else LogPolicyChoice((PolicyTypes)(iChoice - iNumBranches));
	return iChoice;
}

bool CvPolicyAI::IsBranchEffectiveInGame(PolicyBranchTypes eBranch)
{
	CvPolicyBranchEntry* pBranch = GC.getPolicyBranchInfo(eBranch);
	if(!pBranch) return false;
	if(pBranch->IsDelayWhenNoReligion() && GC.getGame().isOption((GameOptionTypes)16)) return false;
	if(pBranch->IsDelayWhenNoCulture() && GC.getGame().isOption((GameOptionTypes)13)) return false;
	if(pBranch->IsDelayWhenNoScience() && GC.getGame().isOption((GameOptionTypes)12)) return false;
	if(pBranch->IsDelayWhenNoCityStates() && GC.getGame().GetNumMinorCivsEver() <= 0) return false;
	return true;
}

int CvPolicyAI::WeighBranch(PolicyBranchTypes eBranch)
{
	CvPolicyBranchEntry* pBranch = GC.getPolicyBranchInfo(eBranch);
	return pBranch ? m_PolicyAIWeights.GetWeight(pBranch->GetFreePolicy()) : 0;
}

void CvPolicyAI::DoChooseIdeology(CvPlayer*)
{
}

void CvPolicyAI::DoConsiderIdeologySwitch(CvPlayer*)
{
}

int CvPolicyAI::GetBranchBuildingHealth(CvPlayer* pPlayer, PolicyBranchTypes eBranch)
{
	int iHealth = 0;
	for(int i = 0; i < GC.getNumPolicyInfos(); ++i)
	{
		CvPolicyEntry* pPolicy = GC.getPolicyInfo((PolicyTypes)i);
		if(!pPolicy || pPolicy->GetPolicyBranchType() != eBranch) continue;
		for(int j = 0; j < GC.getNumBuildingClassInfos(); ++j)
		{
			if(!GC.getBuildingClassInfo((BuildingClassTypes)j) || pPolicy->GetBuildingClassHealth(j) == 0) continue;
			const BuildingTypes eBuilding = (BuildingTypes)pPlayer->getCivilizationInfo().getCivilizationBuildings(j);
			if(eBuilding == NO_BUILDING) continue;
			int iLoop;
			for(CvCity* pCity = pPlayer->firstCity(&iLoop); pCity; pCity = pPlayer->nextCity(&iLoop))
				if(pCity->GetCityBuildings()->GetNumBuilding(eBuilding) > 0) iHealth += pPolicy->GetBuildingClassHealth(j);
		}
	}
	return iHealth;
}

int CvPolicyAI::GetNumHealthPolicies(CvPlayer* pPlayer, PolicyBranchTypes eBranch)
{
	int iCount = 0;
	for(int i = 0; i < GC.getNumPolicyInfos(); ++i)
	{
		CvPolicyEntry* pPolicy = GC.getPolicyInfo((PolicyTypes)i);
		if(!pPolicy || pPolicy->GetPolicyBranchType() != eBranch) continue;
		for(int j = 0; j < GC.getNumBuildingClassInfos(); ++j)
		{
			if(!GC.getBuildingClassInfo((BuildingClassTypes)j)) continue;
			const BuildingTypes eBuilding = (BuildingTypes)pPlayer->getCivilizationInfo().getCivilizationBuildings(j);
			if(eBuilding == NO_BUILDING) continue;
			CvBuildingEntry* pBuilding = GC.getBuildingInfo(eBuilding);
			if(pBuilding && !pBuilding->IsNoOccupiedUnhealth() && pPolicy->GetBuildingClassHealth(j) != 0)
			{
				++iCount;
				break;
			}
		}
	}
	return iCount;
}

CvString CvPolicyAI::GetLogFileName(CvString& playerName) const
{
	CvString filename;
	if(GC.getPlayerAndCityAILogSplit()) filename = "PolicyAILog_" + playerName + ".csv";
	else filename = "PolicyAILog.csv";
	return filename;
}

void CvPolicyAI::LogPossiblePolicies()
{
	if(!GC.getLogging() || !GC.getAILogging()) return;
	CvString playerName = m_pCurrentPolicies->GetPlayer()->getCivilizationShortDescription();
	FILogFile* pLog = LOGFILEMGR.GetLog(GetLogFileName(playerName), FILogFile::kDontTimeStamp);
	CvString prefix;
	prefix.Format("%03d, ", GC.getGame().getElapsedGameTurns());
	prefix += playerName + ", ";
	for(int i = 0; i < m_AdoptablePolicies.size(); ++i)
	{
		CvPolicyEntry* pPolicy = GC.getPolicyInfo((PolicyTypes)m_AdoptablePolicies.GetElement(i));
		CvString message;
		message.Format("%s, %d", pPolicy ? pPolicy->GetDescription() : "Unknown", m_AdoptablePolicies.GetWeight(i));
		pLog->Msg((prefix + message).c_str());
	}
}

void CvPolicyAI::LogPolicyChoice(PolicyTypes ePolicy)
{
	if(!GC.getLogging() || !GC.getAILogging()) return;
	CvString playerName = m_pCurrentPolicies->GetPlayer()->getCivilizationShortDescription();
	FILogFile* pLog = LOGFILEMGR.GetLog(GetLogFileName(playerName), FILogFile::kDontTimeStamp);
	CvPolicyEntry* pPolicy = GC.getPolicyInfo(ePolicy);
	CvString message;
	message.Format("%03d, %s, CHOSEN, %s", GC.getGame().getElapsedGameTurns(), playerName.c_str(), pPolicy ? pPolicy->GetDescription() : "Unknown");
	pLog->Msg(message.c_str());
}

void CvPolicyAI::LogBranchChoice(PolicyBranchTypes eBranch)
{
	if(!GC.getLogging() || !GC.getAILogging()) return;
	CvString playerName = m_pCurrentPolicies->GetPlayer()->getCivilizationShortDescription();
	FILogFile* pLog = LOGFILEMGR.GetLog(GetLogFileName(playerName), FILogFile::kDontTimeStamp);
	CvString message;
	message.Format("%03d, %s, CHOSEN, Branch %d", GC.getGame().getElapsedGameTurns(), playerName.c_str(), eBranch);
	pLog->Msg(message.c_str());
}

void CvPolicyAI::LogIdeologyChoice(CvString& strMessage, int iFreedom, int iOrder, int iAutocracy)
{
	if(!GC.getLogging() || !GC.getAILogging()) return;
	CvString playerName = m_pCurrentPolicies->GetPlayer()->getCivilizationShortDescription();
	FILogFile* pLog = LOGFILEMGR.GetLog(GetLogFileName(playerName), FILogFile::kDontTimeStamp);
	CvString message;
	message.Format("%03d, %s, %s, Freedom: %d, Order: %d, Autocracy: %d", GC.getGame().getElapsedGameTurns(), playerName.c_str(), strMessage.c_str(), iFreedom, iOrder, iAutocracy);
	pLog->Msg(message.c_str());
}

static_assert(sizeof(CvPolicyAI) == 0x42c, "CvPolicyAI i386 target layout");
