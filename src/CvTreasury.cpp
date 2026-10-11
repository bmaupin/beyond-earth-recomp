#include "CvGameCoreDLLPCH.h"
#include "CvTreasury.h"

#include <cmath>

// TODO(Phase1 audit): CvTreasury::CvTreasury UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=14; Civ5 changed/new=UNVERIFIED.
CvTreasury::CvTreasury()
	: m_pPlayer(NULL), m_iEnergy(0), m_iTotalAccumulatedEnergy(0), m_iEnergyPerTurnFromDiplomacy(0),
	m_iExpensePerTurnUnitMaintenance(0), m_iExpensePerTurnUnitSupply(0), m_iCityConnectionEnergyTimes100(0),
	m_iCityConnectionTradeRouteEnergyModifier(0), m_iCityConnectionTradeRouteEnergyChange(0),
	m_iBaseBuildingEnergyMaintenance(0), m_iBaseImprovementEnergyMaintenance(0), m_iBaseRouteEnergyMaintenance(0),
	m_iLifetimeGrossEnergyIncome(0)
{
}

// TODO(Phase1 audit): CvTreasury::~CvTreasury MISMATCH: Instruction 3 differs before first target reference: object [push   %eax] vs BE [sub    $0x14,%esp]; BE instructions=23,20; Civ5 changed/new=UNVERIFIED.
CvTreasury::~CvTreasury()
{
}

// TODO(Phase1 audit): CvTreasury::Init UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=54; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTreasury::DoEnergyTurn UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=104; Civ5 changed/new=UNVERIFIED.
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
// TODO(Phase1 audit): CvTreasury::SetEnergyTimes100 MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=43; Civ5 changed/new=UNVERIFIED.
void CvTreasury::SetEnergyTimes100(int iValue) { m_iEnergy = iValue; }
// TODO(Phase1 audit): CvTreasury::ChangeEnergyTimes100 MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=14; Civ5 changed/new=UNVERIFIED.
void CvTreasury::ChangeEnergyTimes100(int iChange) { SetEnergyTimes100(m_iEnergy + iChange); }
// TODO(Phase1 audit): CvTreasury::GetTotalAccumulatedEnergy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=8; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetTotalAccumulatedEnergy() const { return m_iTotalAccumulatedEnergy; }
// TODO(Phase1 audit): CvTreasury::SetTotalAccumulatedEnergy MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=13; Civ5 changed/new=UNVERIFIED.
void CvTreasury::SetTotalAccumulatedEnergy(int iValue) { m_iTotalAccumulatedEnergy = iValue; }
// TODO(Phase1 audit): CvTreasury::ChangeTotalAccumulatedEnergy MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=14; Civ5 changed/new=UNVERIFIED.
void CvTreasury::ChangeTotalAccumulatedEnergy(int iChange) { m_iTotalAccumulatedEnergy += iChange; }

// TODO(Phase1 audit): CvTreasury::GetEnergyFromCities UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=18; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetEnergyFromCities() const { return GetEnergyFromCitiesTimes100() / 100; }
// TODO(Phase1 audit): CvTreasury::GetEnergyFromCitiesTimes100 UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=41; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetEnergyFromCitiesTimes100(bool bExcludeTradeRoutes) const
{
	int iEnergy = 0;
	int iLoop = 0;
	for (const CvCity* pCity = m_pPlayer->firstCity(&iLoop); pCity; pCity = m_pPlayer->nextCity(&iLoop))
		iEnergy += pCity->getYieldRateTimes100(YIELD_ENERGY, bExcludeTradeRoutes);
	return iEnergy;
}

// TODO(Phase1 audit): CvTreasury::GetEnergyPerTurnFromDiplomacy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetEnergyPerTurnFromDiplomacy() const { return m_iEnergyPerTurnFromDiplomacy; }
// TODO(Phase1 audit): CvTreasury::SetEnergyPerTurnFromDiplomacy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=4; Civ5 changed/new=UNVERIFIED.
void CvTreasury::SetEnergyPerTurnFromDiplomacy(int iValue) { m_iEnergyPerTurnFromDiplomacy = iValue; }
// TODO(Phase1 audit): CvTreasury::ChangeEnergyPerTurnFromDiplomacy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=4; Civ5 changed/new=UNVERIFIED.
void CvTreasury::ChangeEnergyPerTurnFromDiplomacy(int iChange) { m_iEnergyPerTurnFromDiplomacy += iChange; }

// TODO(Phase1 audit): CvTreasury::GetCityConnectionRouteEnergyTimes100 MISMATCH: Instruction 5 differs before first target reference: object [sub    $0xc,%esp] vs BE [sub    $0x1c,%esp]; BE instructions=58; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTreasury::GetCityConnectionEnergy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=8; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetCityConnectionEnergy() const { return m_iCityConnectionEnergyTimes100 / 100; }
// TODO(Phase1 audit): CvTreasury::GetCityConnectionEnergyTimes100 MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetCityConnectionEnergyTimes100() const { return m_iCityConnectionEnergyTimes100; }
// TODO(Phase1 audit): CvTreasury::DoUpdateCityConnectionEnergy MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=61; Civ5 changed/new=UNVERIFIED.
void CvTreasury::DoUpdateCityConnectionEnergy() { m_iCityConnectionEnergyTimes100 = 0; }
// TODO(Phase1 audit): CvTreasury::GetCityConnectionTradeRouteEnergyModifier MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetCityConnectionTradeRouteEnergyModifier() const { return m_iCityConnectionTradeRouteEnergyModifier; }
// TODO(Phase1 audit): CvTreasury::ChangeCityConnectionTradeRouteEnergyModifier MISMATCH: First instruction opcode differs: object mov, BE call; BE instructions=11; Civ5 changed/new=UNVERIFIED.
void CvTreasury::ChangeCityConnectionTradeRouteEnergyModifier(int iChange) { if (iChange) { m_iCityConnectionTradeRouteEnergyModifier += iChange; DoUpdateCityConnectionEnergy(); } }
// TODO(Phase1 audit): CvTreasury::GetCityConnectionTradeRouteEnergyChange MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetCityConnectionTradeRouteEnergyChange() const { return m_iCityConnectionTradeRouteEnergyChange; }
// TODO(Phase1 audit): CvTreasury::ChangeCityConnectionTradeRouteEnergyChange MISMATCH: First instruction opcode differs: object mov, BE call; BE instructions=11; Civ5 changed/new=UNVERIFIED.
void CvTreasury::ChangeCityConnectionTradeRouteEnergyChange(int iChange) { if (iChange) { m_iCityConnectionTradeRouteEnergyChange += iChange; DoUpdateCityConnectionEnergy(); } }
// TODO(Phase1 audit): CvTreasury::HasCityConnectionRouteBetweenCities MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=81; Civ5 changed/new=UNVERIFIED.
bool CvTreasury::HasCityConnectionRouteBetweenCities(CvCity*, CvCity*, bool) const { return false; }

int CvTreasury::GetEnergyPerTurnFromTradeRoutes() const { return 0; }
int CvTreasury::GetEnergyPerTurnFromTradeRoutesTimes100() const { return 0; }
// TODO(Phase1 audit): CvTreasury::GetEnergyPerTurnFromTraits MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=23; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetEnergyPerTurnFromTraits() const { return 0; }
// TODO(Phase1 audit): CvTreasury::GetEnergyPerTurnFromReligion MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=60; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetEnergyPerTurnFromReligion() const { return 0; }
// TODO(Phase1 audit): CvTreasury::GetEnergyPerTurnFromPolicies MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=47; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetEnergyPerTurnFromPolicies() const { return 0; }

// TODO(Phase1 audit): CvTreasury::GetTotalEnergyPerTurn UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetTotalEnergyPerTurn() { return GetTotalEnergyPerTurnTimes100() / 100; }
// TODO(Phase1 audit): CvTreasury::GetTotalEnergyPerTurnTimes100 MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=38; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetTotalEnergyPerTurnTimes100()
{
	const int iPerks = m_pPlayer->GetPlayerPerks() ? m_pPlayer->GetPlayerPerks()->GetGlobalYieldPerTurnTimes100(YIELD_ENERGY) : 0;
	return GetEnergyFromCitiesTimes100() + GetEnergyPerTurnFromTraits() * 100 + GetEnergyPerTurnFromPolicies() * 100 + iPerks;
}
// TODO(Phase1 audit): CvTreasury::GetLifetimeGrossEnergy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetLifetimeGrossEnergy() { return m_iLifetimeGrossEnergyIncome; }
// TODO(Phase1 audit): CvTreasury::GetTotalNetEnergyPerTurn UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetTotalNetEnergyPerTurn() { return GetTotalNetEnergyPerTurnTimes100() / 100; }
// TODO(Phase1 audit): CvTreasury::GetTotalNetEnergyPerTurnTimes100 UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=44; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetTotalNetEnergyPerTurnTimes100() { return GetTotalEnergyPerTurnTimes100() - GetTotalEnergyCostsPerTurn() * 100; }
// TODO(Phase1 audit): CvTreasury::GetTotalEnergyCostsPerTurn MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=58; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetTotalEnergyCostsPerTurn() { return GetTotalEnergyCostsPerTurnTimes100() / 100; }
// TODO(Phase1 audit): CvTreasury::GetTotalEnergyCostsPerTurnTimes100 MISMATCH: Instruction 2 differs before first target reference: object [push   %edi] vs BE [sub    $0x8,%esp]; BE instructions=12; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetTotalEnergyCostsPerTurnTimes100()
{
	int iFreeUnits = 0, iPaidUnits = 0, iBaseUnitCost = 0, iExtraCost = 0, iBaseSupplyCost = 0;
	m_iExpensePerTurnUnitMaintenance = CalculateUnitCost(iFreeUnits, iPaidUnits, iBaseUnitCost, iExtraCost);
	m_iExpensePerTurnUnitSupply = CalculateUnitSupply(iPaidUnits, iBaseSupplyCost);
	const int iRouteMaintenance = GetRouteEnergyMaintenance() * (100 + m_pPlayer->GetRouteEnergyMaintenanceMod()) / 100;
	return (m_iExpensePerTurnUnitMaintenance + m_iExpensePerTurnUnitSupply + GetBuildingEnergyMaintenance() + GetImprovementEnergyMaintenance() + iRouteMaintenance) * 100;
}

// TODO(Phase1 audit): CvTreasury::CalculateUnitCost MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=256; Civ5 changed/new=UNVERIFIED.
int CvTreasury::CalculateUnitCost(int&, int& iPaidUnits, int& iBaseUnitCost, int& iExtraCost)
{
	iPaidUnits = 0;
	iBaseUnitCost = 0;
	iExtraCost = 0;
	return 0;
}

// TODO(Phase1 audit): CvTreasury::CalculateUnitSupply MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=96; Civ5 changed/new=UNVERIFIED.
int CvTreasury::CalculateUnitSupply(int& iPaidUnits, int& iBaseSupplyCost)
{
	iPaidUnits = 0;
	iBaseSupplyCost = 0;
	return 0;
}

// TODO(Phase1 audit): CvTreasury::GetBuildingEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=86; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetBuildingEnergyMaintenance() const { return GetBaseBuildingEnergyMaintenance(); }
// TODO(Phase1 audit): CvTreasury::GetBaseBuildingEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetBaseBuildingEnergyMaintenance() const { return m_iBaseBuildingEnergyMaintenance; }
// TODO(Phase1 audit): CvTreasury::SetBaseBuildingEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=7; Civ5 changed/new=UNVERIFIED.
void CvTreasury::SetBaseBuildingEnergyMaintenance(int iValue) { m_iBaseBuildingEnergyMaintenance = std::max(0, iValue); }
// TODO(Phase1 audit): CvTreasury::ChangeBaseBuildingEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=7; Civ5 changed/new=UNVERIFIED.
void CvTreasury::ChangeBaseBuildingEnergyMaintenance(int iChange) { SetBaseBuildingEnergyMaintenance(m_iBaseBuildingEnergyMaintenance + iChange); }
// TODO(Phase1 audit): CvTreasury::GetImprovementEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=42; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetImprovementEnergyMaintenance() const { return m_iBaseImprovementEnergyMaintenance; }
// TODO(Phase1 audit): CvTreasury::GetBaseImprovementEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetBaseImprovementEnergyMaintenance() const { return m_iBaseImprovementEnergyMaintenance; }
// TODO(Phase1 audit): CvTreasury::SetBaseImprovementEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=34; Civ5 changed/new=UNVERIFIED.
void CvTreasury::SetBaseImprovementEnergyMaintenance(int iValue) { m_iBaseImprovementEnergyMaintenance = std::max(0, iValue); }
// TODO(Phase1 audit): CvTreasury::ChangeBaseImprovementEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=14; Civ5 changed/new=UNVERIFIED.
void CvTreasury::ChangeBaseImprovementEnergyMaintenance(int iChange) { SetBaseImprovementEnergyMaintenance(m_iBaseImprovementEnergyMaintenance + iChange); }
// TODO(Phase1 audit): CvTreasury::GetRouteEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=25; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetRouteEnergyMaintenance() const { return m_iBaseRouteEnergyMaintenance; }
// TODO(Phase1 audit): CvTreasury::GetBaseRouteEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
int CvTreasury::GetBaseRouteEnergyMaintenance() const { return m_iBaseRouteEnergyMaintenance; }
// TODO(Phase1 audit): CvTreasury::SetBaseRouteEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=34; Civ5 changed/new=UNVERIFIED.
void CvTreasury::SetBaseRouteEnergyMaintenance(int iValue) { m_iBaseRouteEnergyMaintenance = std::max(0, iValue); }
// TODO(Phase1 audit): CvTreasury::ChangeBaseRouteEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=14; Civ5 changed/new=UNVERIFIED.
void CvTreasury::ChangeBaseRouteEnergyMaintenance(int iChange) { SetBaseRouteEnergyMaintenance(m_iBaseRouteEnergyMaintenance + iChange); }

// TODO(Phase1 audit): CvTreasury::AverageIncome MISMATCH: Instruction 1 differs before first target reference: object [push   %edi] vs BE [push   %esi]; BE instructions=29; Civ5 changed/new=UNVERIFIED.
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

// TODO(Phase1 audit): CvTreasury::LogExpenditure MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=1442; Civ5 changed/new=UNVERIFIED.
void CvTreasury::LogExpenditure(CvString, int, int)
{
}

// TODO(Phase1 audit): CvTreasury::Read UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=72; Civ5 changed/new=UNVERIFIED.
void CvTreasury::Read(FDataStream& kStream)
{
	unsigned int uiVersion;
	kStream >> uiVersion >> m_iEnergy >> m_iTotalAccumulatedEnergy >> m_iEnergyPerTurnFromDiplomacy >> m_iExpensePerTurnUnitMaintenance >> m_iExpensePerTurnUnitSupply >> m_iCityConnectionEnergyTimes100 >> m_iCityConnectionTradeRouteEnergyModifier >> m_iCityConnectionTradeRouteEnergyChange >> m_iBaseBuildingEnergyMaintenance >> m_iBaseImprovementEnergyMaintenance >> m_iBaseRouteEnergyMaintenance;
	if (uiVersion >= 2)
		kStream >> m_iLifetimeGrossEnergyIncome;
	else
		m_iLifetimeGrossEnergyIncome = 0;
}

// TODO(Phase1 audit): CvTreasury::Write UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=71; Civ5 changed/new=UNVERIFIED.
void CvTreasury::Write(FDataStream& kStream)
{
	const unsigned int uiVersion = 2;
	kStream << uiVersion << m_iEnergy << m_iTotalAccumulatedEnergy << m_iEnergyPerTurnFromDiplomacy << m_iExpensePerTurnUnitMaintenance << m_iExpensePerTurnUnitSupply << m_iCityConnectionEnergyTimes100 << m_iCityConnectionTradeRouteEnergyModifier << m_iCityConnectionTradeRouteEnergyChange << m_iBaseBuildingEnergyMaintenance << m_iBaseImprovementEnergyMaintenance << m_iBaseRouteEnergyMaintenance << m_iLifetimeGrossEnergyIncome;
}

namespace TreasuryHelpers
{
// TODO(Phase1 audit): TreasuryHelpers::AppendToLog UNVERIFIED: Overloads require exact signature attribution; inspect per-mangled-symbol results (some overloads have proved instruction mismatches); BE instructions=67,69,52; Civ5 changed/new=UNVERIFIED.
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, CvString strValue) { strHeader += strHeaderValue; strHeader += ","; strLog += strValue; strLog += ","; }
// TODO(Phase1 audit): TreasuryHelpers::AppendToLog UNVERIFIED: Overloads require exact signature attribution; inspect per-mangled-symbol results (some overloads have proved instruction mismatches); BE instructions=67,69,52; Civ5 changed/new=UNVERIFIED.
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, int iValue) { CvString strValue; strValue.Format("%d", iValue); AppendToLog(strHeader, strLog, strHeaderValue, strValue); }
// TODO(Phase1 audit): TreasuryHelpers::AppendToLog UNVERIFIED: Overloads require exact signature attribution; inspect per-mangled-symbol results (some overloads have proved instruction mismatches); BE instructions=67,69,52; Civ5 changed/new=UNVERIFIED.
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, float fValue) { CvString strValue; strValue.Format("%f", fValue); AppendToLog(strHeader, strLog, strHeaderValue, strValue); }
}
