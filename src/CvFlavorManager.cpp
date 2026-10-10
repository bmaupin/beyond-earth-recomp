#include "CvGameCoreDLLPCH.h"
#include "CvFlavorManager.h"
#include "CvMinorCivAI.h"

#include <cmath>

CvFlavorRecipient::CvFlavorRecipient()
	: m_bIsCity(false), m_piLatestFlavorValues(NULL)
{
}

CvFlavorRecipient::~CvFlavorRecipient()
{
}

void CvFlavorRecipient::Init()
{
	const int iNumFlavors = GC.getNumFlavorTypes();
	m_piLatestFlavorValues = FNEW(int[iNumFlavors], c_eCiv5GameplayDLL, 0);
	memset(m_piLatestFlavorValues, 0, iNumFlavors * sizeof(int));
}

void CvFlavorRecipient::Uninit()
{
	SAFE_DELETE_ARRAY(m_piLatestFlavorValues);
}

bool CvFlavorRecipient::IsCity()
{
	return m_bIsCity;
}

void CvFlavorRecipient::SetFlavors(int* piUpdatedFlavorValues)
{
	CvAssertMsg(piUpdatedFlavorValues != NULL, "Invalid flavor values");
	if (!piUpdatedFlavorValues)
		return;

	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
		m_piLatestFlavorValues[i] = piUpdatedFlavorValues[i];

	FlavorUpdate();
}

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

int CvFlavorRecipient::GetLatestFlavorValue(FlavorTypes eFlavor, bool bAllowNegative)
{
	CvAssertMsg(eFlavor >= 0 && eFlavor < GC.getNumFlavorTypes(), "Flavor index out of bounds");
	const int iValue = m_piLatestFlavorValues[eFlavor];
	return !bAllowNegative && iValue < 0 ? 0 : iValue;
}

CvFlavorManager::CvFlavorManager()
	: m_piPersonalityFlavor(NULL), m_piActiveFlavor(NULL), m_pPlayer(NULL)
{
}

CvFlavorManager::~CvFlavorManager()
{
	Uninit();
}

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

void CvFlavorManager::Uninit()
{
	SAFE_DELETE_ARRAY(m_piPersonalityFlavor);
	SAFE_DELETE_ARRAY(m_piActiveFlavor);
	m_FlavorTargetList.clear();
}

void CvFlavorManager::Reset()
{
	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
	{
		m_piPersonalityFlavor[i] = 0;
		m_piActiveFlavor[i] = 0;
	}
}

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

void CvFlavorManager::Write(FDataStream& kStream)
{
	const uint uiVersion = 2;
	kStream << uiVersion;
	kStream << GC.getNumFlavorTypes();
	kStream << ArrayWrapper<int>(GC.getNumFlavorTypes(), m_piPersonalityFlavor);
	kStream << ArrayWrapper<int>(GC.getNumFlavorTypes(), m_piActiveFlavor);
}

void CvFlavorManager::AddFlavorRecipient(CvFlavorRecipient* pTargetObject, bool bPropagateFlavorValues)
{
	m_FlavorTargetList.push_back(pTargetObject);
	if (m_piPersonalityFlavor && bPropagateFlavorValues)
		pTargetObject->SetFlavors(m_piPersonalityFlavor);
}

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

void CvFlavorManager::ResetToBasePersonality()
{
	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
		m_piActiveFlavor[i] = m_piPersonalityFlavor[i];
	BroadcastBaseFlavors();
}

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

void CvFlavorManager::RandomizeWeights()
{
	const int iMin = GC.getPERSONALITY_FLAVOR_MIN_VALUE();
	const int iMax = GC.getPERSONALITY_FLAVOR_MAX_VALUE();
	const int iRange = GC.getFLAVOR_RANDOMIZATION_RANGE();
	for (int i = 0; i < GC.getNumFlavorTypes(); ++i)
		if (m_piPersonalityFlavor[i] != 0)
			m_piPersonalityFlavor[i] = GetAdjustedValue(m_piPersonalityFlavor[i], iRange, iMin, iMax);
}

int CvFlavorManager::GetAdjustedValue(int iOriginalValue, int iPlusMinus, int iMin, int iMax)
{
	int iValue = iOriginalValue + GC.getGame().getJonRandNum(iPlusMinus * 2 + 1, "Adjusting Personality Flavor") - iPlusMinus;
	if (iValue < iMin)
		iValue = iMin;
	else if (iValue > iMax)
		iValue = iMax;
	return iValue;
}

void CvFlavorManager::BroadcastFlavors(int* piDeltaFlavorValues, bool bPlayerLevelUpdate)
{
	for (Flavor_List::iterator it = m_FlavorTargetList.begin(); it != m_FlavorTargetList.end(); ++it)
	{
		if ((bPlayerLevelUpdate && !(*it)->IsCity()) || (!bPlayerLevelUpdate && (*it)->IsCity()))
			(*it)->ChangeFlavors(piDeltaFlavorValues);
	}
}

void CvFlavorManager::BroadcastBaseFlavors()
{
	for (Flavor_List::iterator it = m_FlavorTargetList.begin(); it != m_FlavorTargetList.end(); ++it)
		(*it)->SetFlavors(m_piPersonalityFlavor);
}

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
