#pragma once

#include "Fireworks/FFastList.h"

class CvPlayer;
class FDataStream;

class CvFlavorRecipient
{
public:
// TODO(Phase1 audit): CvFlavorRecipient::CvFlavorRecipient UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=10; Civ5 changed/new=UNVERIFIED.
	CvFlavorRecipient();
// TODO(Phase1 audit): CvFlavorRecipient::~CvFlavorRecipient MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=20; Civ5 changed/new=UNVERIFIED.
	~CvFlavorRecipient();
// TODO(Phase1 audit): CvFlavorRecipient::Init UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=37; Civ5 changed/new=UNVERIFIED.
	virtual void Init();
// TODO(Phase1 audit): CvFlavorRecipient::Uninit UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	virtual void Uninit();

	bool IsCity();
// TODO(Phase1 audit): CvFlavorRecipient::SetFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=31; Civ5 changed/new=UNVERIFIED.
	void SetFlavors(int* piUpdatedFlavorValues);
// TODO(Phase1 audit): CvFlavorRecipient::ChangeFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=63; Civ5 changed/new=UNVERIFIED.
	void ChangeFlavors(int* piDeltaFlavorValues, bool bDontLog = false);
// TODO(Phase1 audit): CvFlavorRecipient::GetLatestFlavorValue MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=11; Civ5 changed/new=UNVERIFIED.
	int GetLatestFlavorValue(FlavorTypes eFlavor, bool bAllowNegative = false);

protected:
// TODO(Phase1 audit): CvFlavorRecipient::FlavorUpdate UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	virtual void FlavorUpdate() = 0;
// TODO(Phase1 audit): CvFlavorRecipient::LogFlavors UNVERIFIED: No emitted body with a verified target-preserving comparison; BE instructions=unverified/no attributed target; Civ5 changed/new=UNVERIFIED.
	virtual void LogFlavors(FlavorTypes eFlavor = NO_FLAVOR) = 0;

	bool m_bIsCity;
	int* m_piLatestFlavorValues;
};

class CvFlavorManager
{
public:
// TODO(Phase1 audit): CvFlavorManager::CvFlavorManager MISMATCH: First instruction opcode differs: object push, BE mov; BE instructions=12; Civ5 changed/new=UNVERIFIED.
	CvFlavorManager();
// TODO(Phase1 audit): CvFlavorManager::~CvFlavorManager UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=19; Civ5 changed/new=UNVERIFIED.
	~CvFlavorManager();
// TODO(Phase1 audit): CvFlavorManager::Init UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=164; Civ5 changed/new=UNVERIFIED.
	void Init(CvPlayer* pPlayer);
// TODO(Phase1 audit): CvFlavorManager::Uninit MISMATCH: Instruction 3 differs before first target reference: object [push   %eax] vs BE [sub    $0x14,%esp]; BE instructions=29; Civ5 changed/new=UNVERIFIED.
	void Uninit();
// TODO(Phase1 audit): CvFlavorManager::Reset UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=18; Civ5 changed/new=UNVERIFIED.
	void Reset();
// TODO(Phase1 audit): CvFlavorManager::Read UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=45; Civ5 changed/new=UNVERIFIED.
	void Read(FDataStream& kStream);
// TODO(Phase1 audit): CvFlavorManager::Write UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=51; Civ5 changed/new=UNVERIFIED.
	void Write(FDataStream& kStream);
// TODO(Phase1 audit): CvFlavorManager::AddFlavorRecipient MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=34; Civ5 changed/new=UNVERIFIED.
	void AddFlavorRecipient(CvFlavorRecipient* pTargetObject, bool bPropagateFlavorValues = true);
// TODO(Phase1 audit): CvFlavorManager::RemoveFlavorRecipient MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x1c,%esp] vs BE [sub    $0xc,%esp]; BE instructions=39; Civ5 changed/new=UNVERIFIED.
	void RemoveFlavorRecipient(CvFlavorRecipient* pTargetObject);
// TODO(Phase1 audit): CvFlavorManager::ChangeFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=62; Civ5 changed/new=UNVERIFIED.
	void ChangeFlavors(int* piDeltaFlavorValues, bool bPlayerLevelUpdate);
// TODO(Phase1 audit): CvFlavorManager::ResetToBasePersonality UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=23; Civ5 changed/new=UNVERIFIED.
	void ResetToBasePersonality();
// TODO(Phase1 audit): CvFlavorManager::AdjustWeightsForMap UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=90; Civ5 changed/new=UNVERIFIED.
	void AdjustWeightsForMap();
	int GetIndividualFlavor(FlavorTypes eType);
	int* GetAllFlavors();
	int GetPersonalityIndividualFlavor(FlavorTypes eType);
	int* GetAllPersonalityFlavors();
// TODO(Phase1 audit): CvFlavorManager::GetAdjustedValue UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=35; Civ5 changed/new=UNVERIFIED.
	int GetAdjustedValue(int iOriginalValue, int iPlusMinus, int iMin, int iMax);

private:
// TODO(Phase1 audit): CvFlavorManager::RandomizeWeights MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x1c,%esp] vs BE [sub    $0x2c,%esp]; BE instructions=59; Civ5 changed/new=UNVERIFIED.
	void RandomizeWeights();
// TODO(Phase1 audit): CvFlavorManager::BroadcastFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=44; Civ5 changed/new=UNVERIFIED.
	void BroadcastFlavors(int* piDeltaFlavorValues, bool bPlayerLevelUpdate);
// TODO(Phase1 audit): CvFlavorManager::BroadcastBaseFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=27; Civ5 changed/new=UNVERIFIED.
	void BroadcastBaseFlavors();
// TODO(Phase1 audit): CvFlavorManager::LogFlavors MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x9c,%esp] vs BE [sub    $0xbc,%esp]; BE instructions=329; Civ5 changed/new=UNVERIFIED.
	void LogFlavors(FlavorTypes eFlavor = NO_FLAVOR);

	typedef FFastList<CvFlavorRecipient*, c_eCiv5GameplayDLL, 0> Flavor_List;
	int* m_piPersonalityFlavor;
	int* m_piActiveFlavor;
	CvPlayer* m_pPlayer;
	Flavor_List m_FlavorTargetList;
};
