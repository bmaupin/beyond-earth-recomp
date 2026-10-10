#include "CvGameCoreDLLPCH.h"
#include "CvBuildingProductionAI.h"
#include "CvInfosSerializationHelper.h"

#include "LintFree.h"

CvBuildingProductionAI::CvBuildingProductionAI(CvCity* pCity, CvCityBuildings* pCityBuildings)
	: m_pCity(pCity)
	, m_pCityBuildings(pCityBuildings)
{
}

CvBuildingProductionAI::~CvBuildingProductionAI(void)
{
}

void CvBuildingProductionAI::Reset()
{
	m_BuildingAIWeights.clear();

	if(m_pCityBuildings)
	{
		for(int i = 0; i < m_pCityBuildings->GetBuildings()->GetNumBuildings(); i++)
			m_BuildingAIWeights.push_back(i, 0);
	}
}

void CvBuildingProductionAI::Read(FDataStream& kStream)
{
	uint uiVersion;
	kStream >> uiVersion;

	m_BuildingAIWeights.clear();

	if(m_pCityBuildings)
	{
		for(int i = 0; i < m_pCityBuildings->GetBuildings()->GetNumBuildings(); i++)
			m_BuildingAIWeights.push_back(i, 0);

		int iNumEntries;
		kStream >> iNumEntries;

		for(int i = 0; i < iNumEntries; i++)
		{
			bool bValid = true;
			const int iType = CvInfosSerializationHelper::ReadHashed(kStream, &bValid);
			if(iType != NO_BUILDING || !bValid)
			{
				int iWeight;
				kStream >> iWeight;
				if(iType != NO_BUILDING)
					m_BuildingAIWeights.IncreaseWeight(iType, iWeight);
				else
				{
					CvString szError;
					szError.Format("LOAD ERROR: Building Type not found");
					GC.LogMessage(szError.GetCString());
					CvAssertMsg(false, szError);
				}
			}
		}
	}
}

void CvBuildingProductionAI::Write(FDataStream& kStream)
{
	uint uiVersion = 1;
	kStream << uiVersion;

	if(m_pCityBuildings)
	{
		const int iNumBuildings = m_pCityBuildings->GetBuildings()->GetNumBuildings();
		kStream << iNumBuildings;

		for(int i = 0; i < iNumBuildings; i++)
		{
			CvBuildingEntry* pBuilding = GC.getBuildingInfo((BuildingTypes)i);
			if(pBuilding)
			{
				CvInfosSerializationHelper::WriteHashed(kStream, pBuilding);
				kStream << m_BuildingAIWeights.GetWeight(i);
			}
			else
				kStream << 0;
		}
	}
}

void CvBuildingProductionAI::AddFlavorWeights(FlavorTypes eFlavor, int iWeight)
{
	CvBuildingXMLEntries* pBuildings = m_pCityBuildings->GetBuildings();
	for(int i = 0; i < m_pCityBuildings->GetBuildings()->GetNumBuildings(); i++)
	{
		CvBuildingEntry* pBuilding = pBuildings->GetEntry(i);
		if(pBuilding)
			m_BuildingAIWeights.IncreaseWeight(i, pBuilding->GetFlavorValue(eFlavor) * iWeight);
	}
}

int CvBuildingProductionAI::GetWeight(BuildingTypes eBuilding)
{
	return m_BuildingAIWeights.GetWeight(eBuilding);
}

BuildingTypes CvBuildingProductionAI::RecommendBuilding()
{
	m_Buildables.clear();

	for(int i = 0; i < GC.GetGameBuildings()->GetNumBuildings(); i++)
	{
		const BuildingTypes eBuilding = (BuildingTypes)i;
		if(m_pCity->canConstruct(eBuilding))
		{
			const int iTurnsLeft = m_pCity->getProductionTurnsLeft(eBuilding, 0);
			const int iWeight = CityStrategyAIHelpers::ReweightByTurnsLeft(m_BuildingAIWeights.GetWeight(i), iTurnsLeft);
			m_Buildables.push_back(i, iWeight);
		}
	}

	if(m_Buildables.size() > 0)
	{
		m_Buildables.SortItems();
		LogPossibleBuilds();
		return (BuildingTypes)m_Buildables.GetElement(0);
	}

	return NO_BUILDING;
}

void CvBuildingProductionAI::LogPossibleBuilds()
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString playerName = GET_PLAYER(m_pCity->getOwner()).getCivilizationShortDescription();
		CvString cityName = m_pCity->getName();
		FILogFile* pLog = LOGFILEMGR.GetLog(m_pCity->GetCityStrategyAI()->GetLogFileName(playerName, cityName), FILogFile::kDontTimeStamp);

		CvString strBaseString;
		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName + ", " + cityName + ", ";

		CvBuildingXMLEntries* pBuildings = GC.GetGameBuildings();
		if(pBuildings)
		{
			for(int i = 0; i < m_Buildables.size(); i++)
			{
				CvBuildingEntry* pBuilding = pBuildings->GetEntry(m_Buildables.GetElement(i));
				if(pBuilding)
				{
					CvString strTemp;
					strTemp.Format("Building, %s, %d", pBuilding->GetDescription(), m_Buildables.GetWeight(i));
					const std::string strOutBuf = strBaseString + strTemp;
					pLog->Msg(strOutBuf.c_str());
				}
			}
		}
	}
}
