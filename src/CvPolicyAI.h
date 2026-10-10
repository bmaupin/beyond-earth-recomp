#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvGameCoreDLLUtil/include/CvWeightedVector.h"
#include "CvGameCoreDLLUtil/include/CvString.h"
#include <vector>

class CvPlayerPolicies;
class CvPlayer;
class FDataStream;

class CvPolicyAI
{
public:
	CvPolicyAI(CvPlayerPolicies* currentPolicies);
	~CvPolicyAI();
	void Reset();
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream);
	void AddFlavorWeights(FlavorTypes eFlavor, int iWeight, int iPropagationPercent);
	int ChooseNextPolicy(CvPlayer* pPlayer);
	int ChooseNextVirtue(CvPlayer* pPlayer);
	void DoChooseIdeology(CvPlayer* pPlayer);
	void DoConsiderIdeologySwitch(CvPlayer* pPlayer);

private:
	void WeightPrereqs(int* paiTempWeights, int iPropagationPercent);
	void PropagateWeights(int iPolicy, int iWeight, int iPropagationPercent, int iPropagationLevel);
	int WeightKickers(const std::vector<PolicyTypes>& kickers) const;
	int WeighBranch(PolicyBranchTypes eBranch);
	bool IsBranchEffectiveInGame(PolicyBranchTypes eBranch);
	int GetBranchBuildingHealth(CvPlayer* pPlayer, PolicyBranchTypes eBranch);
	int GetNumHealthPolicies(CvPlayer* pPlayer, PolicyBranchTypes eBranch);
	void LogPossiblePolicies();
	void LogPolicyChoice(PolicyTypes ePolicy);
	void LogBranchChoice(PolicyBranchTypes eBranch);
	void LogIdeologyChoice(CvString& strMessage, int iFreedom, int iOrder, int iAutocracy);
	CvString GetLogFileName(CvString& playerName) const;

	CvPlayerPolicies* m_pCurrentPolicies;
	CvWeightedVector<int, 64, true> m_PolicyAIWeights;
	CvWeightedVector<int, 64, true> m_AdoptablePolicies;
	int m_iPolicyWeightPropagationLevels;
	int m_iPolicyWeightPercentDropNewBranch;
};
