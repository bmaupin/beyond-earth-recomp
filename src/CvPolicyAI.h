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
// TODO(Phase1 audit): CvPolicyAI::~CvPolicyAI UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	~CvPolicyAI();
// TODO(Phase1 audit): CvPolicyAI::Reset UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=44; Civ5 changed/new=UNVERIFIED.
	void Reset();
// TODO(Phase1 audit): CvPolicyAI::Read UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=71; Civ5 changed/new=UNVERIFIED.
	void Read(FDataStream& kStream);
// TODO(Phase1 audit): CvPolicyAI::Write UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=57; Civ5 changed/new=UNVERIFIED.
	void Write(FDataStream& kStream);
// TODO(Phase1 audit): CvPolicyAI::AddFlavorWeights UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=107; Civ5 changed/new=UNVERIFIED.
	void AddFlavorWeights(FlavorTypes eFlavor, int iWeight, int iPropagationPercent);
// TODO(Phase1 audit): CvPolicyAI::ChooseNextPolicy MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x5c,%esp] vs BE [sub    $0x6c,%esp]; BE instructions=503; Civ5 changed/new=UNVERIFIED.
	int ChooseNextPolicy(CvPlayer* pPlayer);
// TODO(Phase1 audit): CvPolicyAI::ChooseNextVirtue MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x5c,%esp] vs BE [sub    $0x4c,%esp]; BE instructions=174; Civ5 changed/new=UNVERIFIED.
	int ChooseNextVirtue(CvPlayer* pPlayer);
	void DoChooseIdeology(CvPlayer* pPlayer);
	void DoConsiderIdeologySwitch(CvPlayer* pPlayer);

private:
// TODO(Phase1 audit): CvPolicyAI::WeightPrereqs UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=42; Civ5 changed/new=UNVERIFIED.
	void WeightPrereqs(int* paiTempWeights, int iPropagationPercent);
// TODO(Phase1 audit): CvPolicyAI::PropagateWeights UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=64; Civ5 changed/new=UNVERIFIED.
	void PropagateWeights(int iPolicy, int iWeight, int iPropagationPercent, int iPropagationLevel);
// TODO(Phase1 audit): CvPolicyAI::WeightKickers MISMATCH: Instruction 1 differs before first target reference: object [push   %ebp] vs BE [push   %ebx]; BE instructions=23; Civ5 changed/new=UNVERIFIED.
	int WeightKickers(const std::vector<PolicyTypes>& kickers) const;
// TODO(Phase1 audit): CvPolicyAI::WeighBranch UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=24; Civ5 changed/new=UNVERIFIED.
	int WeighBranch(PolicyBranchTypes eBranch);
// TODO(Phase1 audit): CvPolicyAI::IsBranchEffectiveInGame UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=63; Civ5 changed/new=UNVERIFIED.
	bool IsBranchEffectiveInGame(PolicyBranchTypes eBranch);
// TODO(Phase1 audit): CvPolicyAI::GetBranchBuildingHealth UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=99; Civ5 changed/new=UNVERIFIED.
	int GetBranchBuildingHealth(CvPlayer* pPlayer, PolicyBranchTypes eBranch);
// TODO(Phase1 audit): CvPolicyAI::GetNumHealthPolicies UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=79; Civ5 changed/new=UNVERIFIED.
	int GetNumHealthPolicies(CvPlayer* pPlayer, PolicyBranchTypes eBranch);
// TODO(Phase1 audit): CvPolicyAI::LogPossiblePolicies MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x7c,%esp] vs BE [sub    $0x8c,%esp]; BE instructions=226; Civ5 changed/new=UNVERIFIED.
	void LogPossiblePolicies();
// TODO(Phase1 audit): CvPolicyAI::LogPolicyChoice MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x4c,%esp] vs BE [sub    $0x8c,%esp]; BE instructions=210; Civ5 changed/new=UNVERIFIED.
	void LogPolicyChoice(PolicyTypes ePolicy);
// TODO(Phase1 audit): CvPolicyAI::LogBranchChoice MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x4c,%esp] vs BE [sub    $0x8c,%esp]; BE instructions=197; Civ5 changed/new=UNVERIFIED.
	void LogBranchChoice(PolicyBranchTypes eBranch);
// TODO(Phase1 audit): CvPolicyAI::LogIdeologyChoice MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x5c,%esp] vs BE [sub    $0x8c,%esp]; BE instructions=208; Civ5 changed/new=UNVERIFIED.
	void LogIdeologyChoice(CvString& strMessage, int iFreedom, int iOrder, int iAutocracy);
// TODO(Phase1 audit): CvPolicyAI::GetLogFileName UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=83; Civ5 changed/new=UNVERIFIED.
	CvString GetLogFileName(CvString& playerName) const;

	CvPlayerPolicies* m_pCurrentPolicies;
	CvWeightedVector<int, 64, true> m_PolicyAIWeights;
	CvWeightedVector<int, 64, true> m_AdoptablePolicies;
	int m_iPolicyWeightPropagationLevels;
	int m_iPolicyWeightPercentDropNewBranch;
};
