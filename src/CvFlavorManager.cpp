#include "CvGameCoreDLLPCH.h"
#include "CvFlavorManager.h"
#include "CvMinorCivAI.h"

#include <cmath>

// TODO(Phase1 audit): CvFlavorRecipient::CvFlavorRecipient UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=10; Civ5 changed/new=UNVERIFIED.
CvFlavorRecipient::CvFlavorRecipient()
	: m_bIsCity(false), m_piLatestFlavorValues(NULL)
{
}

// TODO(Phase1 audit): CvFlavorRecipient::~CvFlavorRecipient MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=20; Civ5 changed/new=UNVERIFIED.
CvFlavorRecipient::~CvFlavorRecipient()
{
}

// TODO(Phase1 audit): CvFlavorRecipient::Init UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=37; Civ5 changed/new=UNVERIFIED.
void CvFlavorRecipient::Init()
{
	const int iNumFlavors = GC.getNumFlavorTypes();
	m_piLatestFlavorValues = FNEW(int[iNumFlavors], c_eCiv5GameplayDLL, 0);
	memset(m_piLatestFlavorValues, 0, iNumFlavors * sizeof(int));
}

// TODO(Phase1 audit): CvFlavorRecipient::Uninit UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
void CvFlavorRecipient::Uninit()
{
	SAFE_DELETE_ARRAY(m_piLatestFlavorValues);
}

bool CvFlavorRecipient::IsCity()
{
	return m_bIsCity;
}

// TODO(Phase1 audit): CvFlavorRecipient::SetFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=31; Civ5 changed/new=UNVERIFIED.
void CvFlavorRecipient::SetFlavors(int* piUpdatedFlavorValues)
{
	CvAssertMsg(piUpdatedFlavorValues != NULL, "Invalid flavor values");
	if (!piUpdatedFlavorValues)
		return;

	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
		m_piLatestFlavorValues[i] = piUpdatedFlavorValues[i];

	FlavorUpdate();
}

// TODO(Phase1 audit): CvFlavorRecipient::ChangeFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=63; Civ5 changed/new=UNVERIFIED.
void CvFlavorRecipient::ChangeFlavors(int* piDeltaFlavorValues, bool bDontLog)
{
	CvAssertMsg(piDeltaFlavorValues != NULL, "Invalid flavor deltas");
	if (!piDeltaFlavorValues)
		return;

	const int iMin = GC.getFLAVOR_MIN_VALUE();
	const int iMax = GC.getFLAVOR_MAX_VALUE();
	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
	{
		if (piDeltaFlavorValues[i] == 0)
			continue;

		m_piLatestFlavorValues[i] += piDeltaFlavorValues[i];
		if (m_piLatestFlavorValues[i] < iMin)
			m_piLatestFlavorValues[i] = iMin;
		else if (m_piLatestFlavorValues[i] > iMax)
			m_piLatestFlavorValues[i] = iMax;

		if (!bDontLog)
			LogFlavors((FlavorTypes)i);
	}
	FlavorUpdate();
}

// TODO(Phase1 audit): CvFlavorRecipient::GetLatestFlavorValue MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=11; Civ5 changed/new=UNVERIFIED.
int CvFlavorRecipient::GetLatestFlavorValue(FlavorTypes eFlavor, bool bAllowNegative)
{
	CvAssertMsg(eFlavor >= 0 && eFlavor < GC.getNumFlavorTypes(), "Flavor index out of bounds");
	const int iValue = m_piLatestFlavorValues[eFlavor];
	return !bAllowNegative && iValue < 0 ? 0 : iValue;
}

// TODO(Phase1 audit): CvFlavorManager::CvFlavorManager MISMATCH: First instruction opcode differs: object push, BE mov; BE instructions=12; Civ5 changed/new=UNVERIFIED.
CvFlavorManager::CvFlavorManager()
	: m_piPersonalityFlavor(NULL), m_piActiveFlavor(NULL), m_pPlayer(NULL)
{
}

// TODO(Phase1 audit): CvFlavorManager::~CvFlavorManager UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=19; Civ5 changed/new=UNVERIFIED.
CvFlavorManager::~CvFlavorManager()
{
	Uninit();
}

// TODO(Phase1 audit): CvFlavorManager::Init UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=164; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::Init(CvPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
	const int iNumFlavors = GC.getNumFlavorTypes();
	m_piPersonalityFlavor = FNEW(int[iNumFlavors], c_eCiv5GameplayDLL, 0);
	m_piActiveFlavor = FNEW(int[iNumFlavors], c_eCiv5GameplayDLL, 0);
	m_FlavorTargetList.Reserve((3 * 64) + 100);
	Reset();

	const PlayerTypes ePlayer = (PlayerTypes)pPlayer->GetID();
	if (ePlayer == NO_PLAYER)
		return;

	const SlotStatus eStatus = CvPreGame::slotStatus(ePlayer);
	if ((eStatus != SS_TAKEN && eStatus != SS_COMPUTER) || pPlayer->isAlien() || pPlayer->isNeutralProxy())
		return;

	if (!pPlayer->isHuman())
	{
		const int eLeader = pPlayer->getPersonalityType();
		CvLeaderHeadInfo* pLeader = eLeader < 0 ? NULL : GC.getLeaderHeadInfo(eLeader);
		if (pLeader)
		{
			const int iDefault = GC.getDEFAULT_FLAVOR_VALUE();
			for (int i = 0; i < iNumFlavors; ++i)
			{
				m_piPersonalityFlavor[i] = pPlayer->isMinorCiv()
					? GC.getMinorCivInfo(pPlayer->GetMinorCivAI()->GetMinorCivType())->getFlavorValue(i)
					: pLeader->getFlavorValue(i);
				if (m_piPersonalityFlavor[i] == -1)
					m_piPersonalityFlavor[i] = iDefault;
			}
		}
		RandomizeWeights();
	}
	else
	{
		const int iDefault = GC.getDEFAULT_FLAVOR_VALUE();
		for (int i = 0; i < iNumFlavors; ++i)
			m_piPersonalityFlavor[i] = iDefault;
	}

	BroadcastBaseFlavors();
	ResetToBasePersonality();
	if (GC.getLogging() && GC.getAILogging())
		LogFlavors();
}

// TODO(Phase1 audit): CvFlavorManager::Uninit MISMATCH: Instruction 3 differs before first target reference: object [push   %eax] vs BE [sub    $0x14,%esp]; BE instructions=29; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::Uninit()
{
	SAFE_DELETE_ARRAY(m_piPersonalityFlavor);
	SAFE_DELETE_ARRAY(m_piActiveFlavor);
	m_FlavorTargetList.clear();
}

// TODO(Phase1 audit): CvFlavorManager::Reset UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=18; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::Reset()
{
	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
	{
		m_piPersonalityFlavor[i] = 0;
		m_piActiveFlavor[i] = 0;
	}
}

// TODO(Phase1 audit): CvFlavorManager::Read UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=45; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::Read(FDataStream& kStream)
{
	uint uiVersion;
	kStream >> uiVersion;
	int iNumFlavors = 27;
	if (uiVersion >= 2)
		kStream >> iNumFlavors;
	ArrayWrapper<int> personality(iNumFlavors, m_piPersonalityFlavor);
	ArrayWrapper<int> active(iNumFlavors, m_piActiveFlavor);
	kStream >> personality;
	kStream >> active;
}

// TODO(Phase1 audit): CvFlavorManager::Write UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=51; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::Write(FDataStream& kStream)
{
	const uint uiVersion = 2;
	kStream << uiVersion;
	kStream << GC.getNumFlavorTypes();
	kStream << ArrayWrapper<int>(GC.getNumFlavorTypes(), m_piPersonalityFlavor);
	kStream << ArrayWrapper<int>(GC.getNumFlavorTypes(), m_piActiveFlavor);
}

// TODO(Phase1 audit): CvFlavorManager::AddFlavorRecipient MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=34; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::AddFlavorRecipient(CvFlavorRecipient* pTargetObject, bool bPropagateFlavorValues)
{
	m_FlavorTargetList.push_back(pTargetObject);
	if (m_piPersonalityFlavor && bPropagateFlavorValues)
		pTargetObject->SetFlavors(m_piPersonalityFlavor);
}

// TODO(Phase1 audit): CvFlavorManager::RemoveFlavorRecipient MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x1c,%esp] vs BE [sub    $0xc,%esp]; BE instructions=39; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::RemoveFlavorRecipient(CvFlavorRecipient* pTargetObject)
{
	for (Flavor_List::iterator it = m_FlavorTargetList.begin(); it != m_FlavorTargetList.end(); ++it)
	{
		if (*it == pTargetObject)
		{
			m_FlavorTargetList.erase(it);
			return;
		}
	}
}

// TODO(Phase1 audit): CvFlavorManager::ChangeFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=62; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::ChangeFlavors(int* piDeltaFlavorValues, bool bPlayerLevelUpdate)
{
	CvAssertMsg(piDeltaFlavorValues != NULL, "Invalid flavor deltas");
	if (!piDeltaFlavorValues)
		return;

	if (bPlayerLevelUpdate)
	{
		const int iMin = GC.getFLAVOR_MIN_VALUE();
		const int iMax = GC.getFLAVOR_MAX_VALUE();
		for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
		{
			if (piDeltaFlavorValues[i] == 0)
				continue;
			m_piActiveFlavor[i] += piDeltaFlavorValues[i];
			if (m_piActiveFlavor[i] < iMin)
				m_piActiveFlavor[i] = iMin;
			else if (m_piActiveFlavor[i] > iMax)
				m_piActiveFlavor[i] = iMax;
			LogFlavors((FlavorTypes)i);
		}
	}
	BroadcastFlavors(piDeltaFlavorValues, bPlayerLevelUpdate);
}

// TODO(Phase1 audit): CvFlavorManager::ResetToBasePersonality UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=23; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::ResetToBasePersonality()
{
	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
		m_piActiveFlavor[i] = m_piPersonalityFlavor[i];
	BroadcastBaseFlavors();
}

// TODO(Phase1 audit): CvFlavorManager::AdjustWeightsForMap UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=90; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::AdjustWeightsForMap()
{
	const int iPlayers = GC.getGame().countMajorCivsAlive();
	if (iPlayers <= 0)
		return;

	const int iAdjust = (int)((log10((double)GC.getMap().getLandPlots() / iPlayers) - GC.getFLAVOR_STANDARD_LOG10_TILES_PER_PLAYER()) * GC.getFLAVOR_EXPANDGROW_COEFFICIENT());
	const int iNumFlavors = GC.getNumFlavorTypes();
	const int iExpansion = GC.getInfoTypeForString("FLAVOR_EXPANSION");
	const int iGrowth = GC.getInfoTypeForString("FLAVOR_GROWTH");
	if (iExpansion >= 0 && iExpansion < iNumFlavors)
	{
		m_piPersonalityFlavor[iExpansion] += iAdjust;
		if (m_piPersonalityFlavor[iExpansion] > GC.getPERSONALITY_FLAVOR_MAX_VALUE())
			m_piPersonalityFlavor[iExpansion] = GC.getPERSONALITY_FLAVOR_MAX_VALUE();
	}
	if (iGrowth >= 0 && iGrowth < iNumFlavors)
	{
		m_piPersonalityFlavor[iGrowth] -= iAdjust;
		if (m_piPersonalityFlavor[iGrowth] < GC.getPERSONALITY_FLAVOR_MIN_VALUE())
			m_piPersonalityFlavor[iGrowth] = GC.getPERSONALITY_FLAVOR_MIN_VALUE();
	}
	ResetToBasePersonality();
}

int CvFlavorManager::GetIndividualFlavor(FlavorTypes eType)
{
	CvAssertMsg(eType >= 0 && eType < GC.getNumFlavorTypes(), "Flavor index out of bounds");
	return m_piActiveFlavor[eType];
}

int* CvFlavorManager::GetAllFlavors()
{
	return m_piActiveFlavor;
}

int CvFlavorManager::GetPersonalityIndividualFlavor(FlavorTypes eType)
{
	CvAssertMsg(eType >= 0 && eType < GC.getNumFlavorTypes(), "Flavor index out of bounds");
	return m_piPersonalityFlavor[eType];
}

int* CvFlavorManager::GetAllPersonalityFlavors()
{
	return m_piPersonalityFlavor;
}

// TODO(Phase1 audit): CvFlavorManager::RandomizeWeights MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x1c,%esp] vs BE [sub    $0x2c,%esp]; BE instructions=59; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::RandomizeWeights()
{
	const int iMin = GC.getPERSONALITY_FLAVOR_MIN_VALUE();
	const int iMax = GC.getPERSONALITY_FLAVOR_MAX_VALUE();
	const int iRange = GC.getFLAVOR_RANDOMIZATION_RANGE();
	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
		if (m_piPersonalityFlavor[i] != 0)
			m_piPersonalityFlavor[i] = GetAdjustedValue(m_piPersonalityFlavor[i], iRange, iMin, iMax);
}

// TODO(Phase1 audit): CvFlavorManager::GetAdjustedValue UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=35; Civ5 changed/new=UNVERIFIED.
int CvFlavorManager::GetAdjustedValue(int iOriginalValue, int iPlusMinus, int iMin, int iMax)
{
	int iValue = iOriginalValue + GC.getGame().getJonRandNum(iPlusMinus * 2 + 1, "Adjusting Personality Flavor") - iPlusMinus;
	if (iValue < iMin)
		iValue = iMin;
	else if (iValue > iMax)
		iValue = iMax;
	return iValue;
}

// TODO(Phase1 audit): CvFlavorManager::BroadcastFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=44; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::BroadcastFlavors(int* piDeltaFlavorValues, bool bPlayerLevelUpdate)
{
	for (Flavor_List::iterator it = m_FlavorTargetList.begin(); it != m_FlavorTargetList.end(); ++it)
	{
		if ((bPlayerLevelUpdate && !(*it)->IsCity()) || (!bPlayerLevelUpdate && (*it)->IsCity()))
			(*it)->ChangeFlavors(piDeltaFlavorValues);
	}
}

// TODO(Phase1 audit): CvFlavorManager::BroadcastBaseFlavors UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=27; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::BroadcastBaseFlavors()
{
	for (Flavor_List::iterator it = m_FlavorTargetList.begin(); it != m_FlavorTargetList.end(); ++it)
		(*it)->SetFlavors(m_piPersonalityFlavor);
}

// TODO(Phase1 audit): CvFlavorManager::LogFlavors MISMATCH: Instruction 5 differs before first target reference: object [sub    $0x9c,%esp] vs BE [sub    $0xbc,%esp]; BE instructions=329; Civ5 changed/new=UNVERIFIED.
void CvFlavorManager::LogFlavors(FlavorTypes eFlavor)
{
	if (!GC.getLogging() || !GC.getAILogging())
		return;

	const CvString playerName = m_pPlayer->getCivilizationShortDescription();
	CvString logName("FlavorAILog.csv");
	if (GC.getPlayerAndCityAILogSplit())
		logName = (CvString("FlavorAILog_") + playerName + ".csv").c_str();
	FILogFile* pLog = LOGFILEMGR.GetLog(logName.c_str(), FILogFile::kDontTimeStamp);
	CvString base;
	base.Format("%03d, %s, ", GC.getGame().getElapsedGameTurns(), playerName.c_str());
	if (eFlavor == NO_FLAVOR)
	{
		for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
		{
			CvString message;
			message.Format("Flavor, %s, %d", GC.getFlavorTypes((FlavorTypes)i), GetIndividualFlavor((FlavorTypes)i));
			pLog->Msg("%s%s", base.c_str(), message.c_str());
		}
	}
	else
	{
		CvString message;
		message.Format("Flavor, %s, %d", GC.getFlavorTypes(eFlavor), GetIndividualFlavor(eFlavor));
		pLog->Msg("%s%s", base.c_str(), message.c_str());
	}
}
