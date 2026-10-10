#include "CvGameCoreDLLPCH.h"
#include "CvInfosSerializationHelper.h"

#include "LintFree.h"

class CvQuest
{
public:
	int GetUnitAIWeight(UnitTypes eUnit) const;
};

int ScaleFlavorWeightByTime(FlavorTypes eFlavor)
{
	const int iGameTurn = GC.getGame().getGameTurn();
	if(iGameTurn >= 101)
	{
		if(eFlavor == GC.getInfoTypeForString("FLAVOR_HEALTH", false))
			return 150;
	}
	else if(iGameTurn >= 151)
	{
		if(eFlavor == GC.getInfoTypeForString("FLAVOR_HEALTH", false))
			return 200;
	}

	if(eFlavor == GC.getInfoTypeForString("FLAVOR_OFFENSE", false) ||
		eFlavor == GC.getInfoTypeForString("FLAVOR_DEFENSE", false) ||
		eFlavor == GC.getInfoTypeForString("FLAVOR_MILITARY_TRAINING", false))
		return 100;

	return 100;
}

CvUnitProductionAI::CvUnitProductionAI(CvCity* pCity, CvUnitXMLEntries* pUnits)
	: m_pCity(pCity)
	, m_pUnits(pUnits)
{
}

CvUnitProductionAI::~CvUnitProductionAI(void)
{
}

void CvUnitProductionAI::Reset()
{
	m_UnitAIWeights.clear();
	if(m_pUnits)
	{
		for(int i = 0; i < m_pUnits->GetNumUnits(); ++i)
			m_UnitAIWeights.push_back(i, 0);
	}
}

void CvUnitProductionAI::Read(FDataStream& kStream)
{
	uint uiVersion;
	kStream >> uiVersion;

	m_UnitAIWeights.clear();
	if(!m_pUnits)
		return;

	for(int i = 0; i < m_pUnits->GetNumUnits(); ++i)
		m_UnitAIWeights.push_back(i, 0);

	int iNumEntries;
	kStream >> iNumEntries;
	for(int i = 0; i < iNumEntries; ++i)
	{
		bool bValid = true;
		const int iType = CvInfosSerializationHelper::ReadHashed(kStream, &bValid);
		if(iType != NO_UNIT || !bValid)
		{
			int iWeight;
			kStream >> iWeight;
			if(iType != NO_UNIT)
				m_UnitAIWeights.IncreaseWeight(iType, iWeight);
			else
			{
				CvString szError;
				szError.Format("LOAD ERROR: Unit Type not found");
				GC.LogMessage(szError.GetCString());
				CvAssertMsg(false, szError);
			}
		}
	}
}

void CvUnitProductionAI::Write(FDataStream& kStream) const
{
	const uint uiVersion = 1;
	kStream << uiVersion;

	if(!m_pUnits)
		return;

	const int iNumUnits = m_pUnits->GetNumUnits();
	kStream << iNumUnits;
	for(int i = 0; i < iNumUnits; ++i)
	{
		CvUnitEntry* pUnit = GC.getUnitInfo((UnitTypes)i);
		if(pUnit)
		{
			CvInfosSerializationHelper::WriteHashed(kStream, pUnit);
			kStream << m_UnitAIWeights.GetWeight(i);
		}
		else
			kStream << 0;
	}
}

void CvUnitProductionAI::AddFlavorWeights(FlavorTypes eFlavor, int iWeight)
{
	for(int i = 0; i < m_pUnits->GetNumUnits(); ++i)
	{
		CvUnitEntry* pUnit = m_pUnits->GetEntry(i);
		if(pUnit)
			m_UnitAIWeights.IncreaseWeight(i, pUnit->GetFlavorValue(eFlavor) * iWeight);
	}
}

void CvUnitProductionAI::AddQuestWeights()
{
	if(GC.getGame().getGameTurn() < 100 || !m_pCity)
		return;

	const CvQuest* pQuest = m_pCity->GetPlayer()->GetGrandStrategyAI()->GetActiveGrandStrategyQuest();
	if(!pQuest)
		return;

	for(int i = 0; i < m_pUnits->GetNumUnits(); ++i)
	{
		if(pQuest->GetUnitAIWeight((UnitTypes)i) > 0)
			m_UnitAIWeights.IncreaseWeight(i, 7500);
	}
}

int CvUnitProductionAI::GetWeight(UnitTypes eUnit)
{
	return m_UnitAIWeights.GetWeight(eUnit);
}

UnitTypes CvUnitProductionAI::RecommendUnit(UnitAITypes eUnitAIType)
{
	if(eUnitAIType < NO_UNITAI)
		return NO_UNIT;

	m_Buildables.clear();
	for(int i = 0; i < GC.GetGameUnits()->GetNumUnits(); ++i)
	{
		const UnitTypes eUnit = (UnitTypes)i;
		CvUnitEntry* pUnit = GC.getUnitInfo(eUnit);
		if(pUnit && m_pCity->canTrain(eUnit) &&
			(eUnitAIType == NO_UNITAI || pUnit->GetUnitAIType(eUnitAIType)))
		{
			const int iTurnsLeft = m_pCity->getProductionTurnsLeft(eUnit, 0);
			const int iWeight = CityStrategyAIHelpers::ReweightByTurnsLeft(m_UnitAIWeights.GetWeight(eUnit), iTurnsLeft);
			m_Buildables.push_back(i, iWeight);
		}
	}

	if(m_Buildables.size() <= 0)
		return NO_UNIT;

	m_Buildables.SortItems();
	LogPossibleBuilds(eUnitAIType);
	return (UnitTypes)m_Buildables.GetElement(0);
}

void CvUnitProductionAI::LogPossibleBuilds(UnitAITypes eUnitAIType)
{
	if(!GC.getLogging() || !GC.getAILogging())
		return;

	CvString playerName = GET_PLAYER(m_pCity->getOwner()).getCivilizationShortDescription();
	CvString cityName = m_pCity->getName();
	FILogFile* pLog = LOGFILEMGR.GetLog(m_pCity->GetCityStrategyAI()->GetLogFileName(playerName, cityName), FILogFile::kDontTimeStamp);

	CvString strBaseString;
	strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
	strBaseString += playerName + ", " + cityName + ", ";

	for(int i = 0; i < m_Buildables.size(); ++i)
	{
		CvUnitEntry* pUnit = GC.GetGameUnits()->GetEntry(m_Buildables.GetElement(i));
		CvString strDesc = pUnit ? pUnit->GetDescription() : "Unknown Unit";
		CvString strTemp;
		if(eUnitAIType == NO_UNITAI)
			strTemp.Format("Unit, %s, %d", strDesc.GetCString(), m_Buildables.GetWeight(i));
		else
		{
			CvString strUnitAI;
			getUnitAIString(strUnitAI, eUnitAIType);
			strTemp.Format("Special request for unit of type: %s, %s, %d", strUnitAI.GetCString(), strDesc.GetCString(), m_Buildables.GetWeight(i));
		}
		const std::string strOutBuf = strBaseString + strTemp;
		pLog->Msg(strOutBuf.c_str());
	}
}
