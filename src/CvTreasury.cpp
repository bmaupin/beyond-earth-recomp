#include "CvGameCoreDLLPCH.h"
#include "CvTreasury.h"

#include <cmath>

CvTreasury::CvTreasury()
	: m_pPlayer(NULL), m_iEnergy(0), m_iTotalAccumulatedEnergy(0), m_iEnergyPerTurnFromDiplomacy(0),
	m_iExpensePerTurnUnitMaintenance(0), m_iExpensePerTurnUnitSupply(0), m_iCityConnectionEnergyTimes100(0),
	m_iCityConnectionTradeRouteEnergyModifier(0), m_iCityConnectionTradeRouteEnergyChange(0),
	m_iBaseBuildingEnergyMaintenance(0), m_iBaseImprovementEnergyMaintenance(0), m_iBaseRouteEnergyMaintenance(0),
	m_iLifetimeGrossEnergyIncome(0)
{
}

CvTreasury::~CvTreasury()
{
}

void CvTreasury::Init(CvPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
	m_iEnergy = m_iTotalAccumulatedEnergy = m_iEnergyPerTurnFromDiplomacy = 0;
	m_iExpensePerTurnUnitMaintenance = m_iExpensePerTurnUnitSupply = 0;
	m_iCityConnectionEnergyTimes100 = m_iCityConnectionTradeRouteEnergyModifier = m_iCityConnectionTradeRouteEnergyChange = 0;
	m_iBaseBuildingEnergyMaintenance = m_iBaseImprovementEnergyMaintenance = m_iBaseRouteEnergyMaintenance = 0;
	m_iLifetimeGrossEnergyIncome = 0;
	m_EnergyBalanceForTurnTimes100.clear();
	m_EnergyBalanceForTurnTimes100.reserve(750);
	m_EnergyChangeForTurnTimes100.clear();
	m_EnergyChangeForTurnTimes100.reserve(750);
}

void CvTreasury::Uninit()
{
}

void CvTreasury::DoEnergyTurn()
{
	const int iEnergyChange = GetTotalNetEnergyPerTurnTimes100();
	const int iEnergyAfterThisTurn = iEnergyChange + GetEnergyTimes100();
	if (iEnergyAfterThisTurn < 0)
		SetEnergyTimes100(0);
	else
		ChangeEnergyTimes100(iEnergyChange);

	const int iGrossEnergyChange = GetTotalEnergyPerTurn();
	if (iGrossEnergyChange > 0)
		m_iLifetimeGrossEnergyIncome += iGrossEnergyChange;

	const int iTurn = GC.getGame().getGameTurn();
	if (m_EnergyBalanceForTurnTimes100.size() < static_cast<unsigned int>(iTurn))
		m_EnergyBalanceForTurnTimes100.push_back(GetEnergyTimes100());
	if (m_EnergyChangeForTurnTimes100.size() < static_cast<unsigned int>(iTurn))
		m_EnergyChangeForTurnTimes100.push_back(iEnergyChange);
}

int CvTreasury::GetEnergyTimes100() const { return m_iEnergy; }
void CvTreasury::SetEnergyTimes100(int iValue) { m_iEnergy = iValue; }
void CvTreasury::ChangeEnergyTimes100(int iChange) { SetEnergyTimes100(m_iEnergy + iChange); }
int CvTreasury::GetTotalAccumulatedEnergy() const { return m_iTotalAccumulatedEnergy; }
void CvTreasury::SetTotalAccumulatedEnergy(int iValue) { m_iTotalAccumulatedEnergy = iValue; }
void CvTreasury::ChangeTotalAccumulatedEnergy(int iChange) { m_iTotalAccumulatedEnergy += iChange; }

int CvTreasury::GetEnergyFromCities() const { return GetEnergyFromCitiesTimes100() / 100; }
int CvTreasury::GetEnergyFromCitiesTimes100(bool bExcludeTradeRoutes) const
{
	int iEnergy = 0;
	int iLoop = 0;
	for (const CvCity* pCity = m_pPlayer->firstCity(&iLoop); pCity; pCity = m_pPlayer->nextCity(&iLoop))
		iEnergy += pCity->getYieldRateTimes100(YIELD_ENERGY, bExcludeTradeRoutes);
	return iEnergy;
}

int CvTreasury::GetEnergyPerTurnFromDiplomacy() const { return m_iEnergyPerTurnFromDiplomacy; }
void CvTreasury::SetEnergyPerTurnFromDiplomacy(int iValue) { m_iEnergyPerTurnFromDiplomacy = iValue; }
void CvTreasury::ChangeEnergyPerTurnFromDiplomacy(int iChange) { m_iEnergyPerTurnFromDiplomacy += iChange; }

int CvTreasury::GetCityConnectionRouteEnergyTimes100(CvCity* pCity) const
{
	const CvCity* pCapital = m_pPlayer->getCapitalCity();
	if (!pCity || pCity == pCapital || !pCapital)
		return 0;
	int iEnergy = GC.getTRADE_ROUTE_BASE_ENERGY();
	iEnergy += pCapital->getPopulation() * GC.getTRADE_ROUTE_CAPITAL_POP_ENERGY_MULTIPLIER();
	iEnergy += pCity->getPopulation() * GC.getTRADE_ROUTE_CITY_POP_ENERGY_MULTIPLIER();
	iEnergy += GetCityConnectionTradeRouteEnergyChange() * 100;
	return iEnergy * (100 + GetCityConnectionTradeRouteEnergyModifier()) / 100;
}

int CvTreasury::GetCityConnectionEnergy() const { return m_iCityConnectionEnergyTimes100 / 100; }
int CvTreasury::GetCityConnectionEnergyTimes100() const { return m_iCityConnectionEnergyTimes100; }
void CvTreasury::DoUpdateCityConnectionEnergy() { m_iCityConnectionEnergyTimes100 = 0; }
int CvTreasury::GetCityConnectionTradeRouteEnergyModifier() const { return m_iCityConnectionTradeRouteEnergyModifier; }
void CvTreasury::ChangeCityConnectionTradeRouteEnergyModifier(int iChange) { if (iChange) { m_iCityConnectionTradeRouteEnergyModifier += iChange; DoUpdateCityConnectionEnergy(); } }
int CvTreasury::GetCityConnectionTradeRouteEnergyChange() const { return m_iCityConnectionTradeRouteEnergyChange; }
void CvTreasury::ChangeCityConnectionTradeRouteEnergyChange(int iChange) { if (iChange) { m_iCityConnectionTradeRouteEnergyChange += iChange; DoUpdateCityConnectionEnergy(); } }
bool CvTreasury::HasCityConnectionRouteBetweenCities(CvCity*, CvCity*, bool) const { return false; }

int CvTreasury::GetEnergyPerTurnFromTradeRoutes() const { return 0; }
int CvTreasury::GetEnergyPerTurnFromTradeRoutesTimes100() const { return 0; }
int CvTreasury::GetEnergyPerTurnFromTraits() const { return 0; }
int CvTreasury::GetEnergyPerTurnFromReligion() const { return 0; }
int CvTreasury::GetEnergyPerTurnFromPolicies() const { return 0; }

int CvTreasury::GetTotalEnergyPerTurn() { return GetTotalEnergyPerTurnTimes100() / 100; }
int CvTreasury::GetTotalEnergyPerTurnTimes100()
{
	const int iPerks = m_pPlayer->GetPlayerPerks() ? m_pPlayer->GetPlayerPerks()->GetGlobalYieldPerTurnTimes100(YIELD_ENERGY) : 0;
	return GetEnergyFromCitiesTimes100() + GetEnergyPerTurnFromTraits() * 100 + GetEnergyPerTurnFromPolicies() * 100 + iPerks;
}
int CvTreasury::GetLifetimeGrossEnergy() { return m_iLifetimeGrossEnergyIncome; }
int CvTreasury::GetTotalNetEnergyPerTurn() { return GetTotalNetEnergyPerTurnTimes100() / 100; }
int CvTreasury::GetTotalNetEnergyPerTurnTimes100() { return GetTotalEnergyPerTurnTimes100() - GetTotalEnergyCostsPerTurn() * 100; }
int CvTreasury::GetTotalEnergyCostsPerTurn() { return GetTotalEnergyCostsPerTurnTimes100() / 100; }
int CvTreasury::GetTotalEnergyCostsPerTurnTimes100()
{
	int iFreeUnits = 0, iPaidUnits = 0, iBaseUnitCost = 0, iExtraCost = 0, iBaseSupplyCost = 0;
	m_iExpensePerTurnUnitMaintenance = CalculateUnitCost(iFreeUnits, iPaidUnits, iBaseUnitCost, iExtraCost);
	m_iExpensePerTurnUnitSupply = CalculateUnitSupply(iPaidUnits, iBaseSupplyCost);
	const int iRouteMaintenance = GetRouteEnergyMaintenance() * (100 + m_pPlayer->GetRouteEnergyMaintenanceMod()) / 100;
	return (m_iExpensePerTurnUnitMaintenance + m_iExpensePerTurnUnitSupply + GetBuildingEnergyMaintenance() + GetImprovementEnergyMaintenance() + iRouteMaintenance) * 100;
}

int CvTreasury::CalculateUnitCost(int&, int& iPaidUnits, int& iBaseUnitCost, int& iExtraCost)
{
	iPaidUnits = 0;
	iBaseUnitCost = 0;
	iExtraCost = 0;
	return 0;
}

int CvTreasury::CalculateUnitSupply(int& iPaidUnits, int& iBaseSupplyCost)
{
	iPaidUnits = 0;
	iBaseSupplyCost = 0;
	return 0;
}

int CvTreasury::GetBuildingEnergyMaintenance() const { return GetBaseBuildingEnergyMaintenance(); }
int CvTreasury::GetBaseBuildingEnergyMaintenance() const { return m_iBaseBuildingEnergyMaintenance; }
void CvTreasury::SetBaseBuildingEnergyMaintenance(int iValue) { m_iBaseBuildingEnergyMaintenance = std::max(0, iValue); }
void CvTreasury::ChangeBaseBuildingEnergyMaintenance(int iChange) { SetBaseBuildingEnergyMaintenance(m_iBaseBuildingEnergyMaintenance + iChange); }
int CvTreasury::GetImprovementEnergyMaintenance() const { return m_iBaseImprovementEnergyMaintenance; }
int CvTreasury::GetBaseImprovementEnergyMaintenance() const { return m_iBaseImprovementEnergyMaintenance; }
void CvTreasury::SetBaseImprovementEnergyMaintenance(int iValue) { m_iBaseImprovementEnergyMaintenance = std::max(0, iValue); }
void CvTreasury::ChangeBaseImprovementEnergyMaintenance(int iChange) { SetBaseImprovementEnergyMaintenance(m_iBaseImprovementEnergyMaintenance + iChange); }
int CvTreasury::GetRouteEnergyMaintenance() const { return m_iBaseRouteEnergyMaintenance; }
int CvTreasury::GetBaseRouteEnergyMaintenance() const { return m_iBaseRouteEnergyMaintenance; }
void CvTreasury::SetBaseRouteEnergyMaintenance(int iValue) { m_iBaseRouteEnergyMaintenance = std::max(0, iValue); }
void CvTreasury::ChangeBaseRouteEnergyMaintenance(int iChange) { SetBaseRouteEnergyMaintenance(m_iBaseRouteEnergyMaintenance + iChange); }

double CvTreasury::AverageIncome(int iTurns)
{
	if (iTurns <= 0 || m_EnergyChangeForTurnTimes100.empty())
		return 0.0;
	const int iSamples = std::min(iTurns, static_cast<int>(m_EnergyChangeForTurnTimes100.size()));
	int iTotal = 0;
	for (int i = 0; i < iSamples; ++i)
		iTotal += m_EnergyChangeForTurnTimes100[m_EnergyChangeForTurnTimes100.size() - 1 - i];
	return static_cast<double>(iTotal) / iSamples / 100.0;
}

void CvTreasury::LogExpenditure(CvString, int, int)
{
}

void CvTreasury::Read(FDataStream& kStream)
{
	unsigned int uiVersion;
	kStream >> uiVersion >> m_iEnergy >> m_iTotalAccumulatedEnergy >> m_iEnergyPerTurnFromDiplomacy >> m_iExpensePerTurnUnitMaintenance >> m_iExpensePerTurnUnitSupply >> m_iCityConnectionEnergyTimes100 >> m_iCityConnectionTradeRouteEnergyModifier >> m_iCityConnectionTradeRouteEnergyChange >> m_iBaseBuildingEnergyMaintenance >> m_iBaseImprovementEnergyMaintenance >> m_iBaseRouteEnergyMaintenance;
	if (uiVersion >= 2)
		kStream >> m_iLifetimeGrossEnergyIncome;
	else
		m_iLifetimeGrossEnergyIncome = 0;
}

void CvTreasury::Write(FDataStream& kStream)
{
	const unsigned int uiVersion = 2;
	kStream << uiVersion << m_iEnergy << m_iTotalAccumulatedEnergy << m_iEnergyPerTurnFromDiplomacy << m_iExpensePerTurnUnitMaintenance << m_iExpensePerTurnUnitSupply << m_iCityConnectionEnergyTimes100 << m_iCityConnectionTradeRouteEnergyModifier << m_iCityConnectionTradeRouteEnergyChange << m_iBaseBuildingEnergyMaintenance << m_iBaseImprovementEnergyMaintenance << m_iBaseRouteEnergyMaintenance << m_iLifetimeGrossEnergyIncome;
}

namespace TreasuryHelpers
{
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, CvString strValue) { strHeader += strHeaderValue; strHeader += ","; strLog += strValue; strLog += ","; }
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, int iValue) { CvString strValue; strValue.Format("%d", iValue); AppendToLog(strHeader, strLog, strHeaderValue, strValue); }
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, float fValue) { CvString strValue; strValue.Format("%f", fValue); AppendToLog(strHeader, strLog, strHeaderValue, strValue); }
}
