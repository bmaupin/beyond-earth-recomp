#pragma once

class CvCity;
class CvPlayer;
class FDataStream;

class CvTreasury
{
public:
// TODO(Phase1 audit): CvTreasury::CvTreasury UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=14; Civ5 changed/new=UNVERIFIED.
	CvTreasury();
// TODO(Phase1 audit): CvTreasury::~CvTreasury MISMATCH: Instruction 3 differs before first target reference: object [push   %eax] vs BE [sub    $0x14,%esp]; BE instructions=23,20; Civ5 changed/new=UNVERIFIED.
	virtual ~CvTreasury();
// TODO(Phase1 audit): CvTreasury::Init UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=54; Civ5 changed/new=UNVERIFIED.
	void Init(CvPlayer* pPlayer);
	void Uninit();
// TODO(Phase1 audit): CvTreasury::Read UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=72; Civ5 changed/new=UNVERIFIED.
	void Read(FDataStream& kStream);
// TODO(Phase1 audit): CvTreasury::Write UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=71; Civ5 changed/new=UNVERIFIED.
	void Write(FDataStream& kStream);
// TODO(Phase1 audit): CvTreasury::DoEnergyTurn UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=104; Civ5 changed/new=UNVERIFIED.
	void DoEnergyTurn();

	int GetEnergyTimes100() const;
// TODO(Phase1 audit): CvTreasury::SetEnergyTimes100 MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=43; Civ5 changed/new=UNVERIFIED.
	void SetEnergyTimes100(int iValue);
// TODO(Phase1 audit): CvTreasury::ChangeEnergyTimes100 MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=14; Civ5 changed/new=UNVERIFIED.
	void ChangeEnergyTimes100(int iChange);
// TODO(Phase1 audit): CvTreasury::GetTotalAccumulatedEnergy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=8; Civ5 changed/new=UNVERIFIED.
	int GetTotalAccumulatedEnergy() const;
// TODO(Phase1 audit): CvTreasury::SetTotalAccumulatedEnergy MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=13; Civ5 changed/new=UNVERIFIED.
	void SetTotalAccumulatedEnergy(int iValue);
// TODO(Phase1 audit): CvTreasury::ChangeTotalAccumulatedEnergy MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=14; Civ5 changed/new=UNVERIFIED.
	void ChangeTotalAccumulatedEnergy(int iChange);
// TODO(Phase1 audit): CvTreasury::GetEnergyFromCities UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=18; Civ5 changed/new=UNVERIFIED.
	int GetEnergyFromCities() const;
// TODO(Phase1 audit): CvTreasury::GetEnergyFromCitiesTimes100 UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=41; Civ5 changed/new=UNVERIFIED.
	int GetEnergyFromCitiesTimes100(bool bExcludeTradeRoutes = false) const;
// TODO(Phase1 audit): CvTreasury::GetEnergyPerTurnFromDiplomacy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
	int GetEnergyPerTurnFromDiplomacy() const;
// TODO(Phase1 audit): CvTreasury::SetEnergyPerTurnFromDiplomacy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=4; Civ5 changed/new=UNVERIFIED.
	void SetEnergyPerTurnFromDiplomacy(int iValue);
// TODO(Phase1 audit): CvTreasury::ChangeEnergyPerTurnFromDiplomacy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=4; Civ5 changed/new=UNVERIFIED.
	void ChangeEnergyPerTurnFromDiplomacy(int iChange);
// TODO(Phase1 audit): CvTreasury::GetCityConnectionRouteEnergyTimes100 MISMATCH: Instruction 5 differs before first target reference: object [sub    $0xc,%esp] vs BE [sub    $0x1c,%esp]; BE instructions=58; Civ5 changed/new=UNVERIFIED.
	int GetCityConnectionRouteEnergyTimes100(CvCity* pCity) const;
// TODO(Phase1 audit): CvTreasury::GetCityConnectionEnergy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=8; Civ5 changed/new=UNVERIFIED.
	int GetCityConnectionEnergy() const;
// TODO(Phase1 audit): CvTreasury::GetCityConnectionEnergyTimes100 MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
	int GetCityConnectionEnergyTimes100() const;
// TODO(Phase1 audit): CvTreasury::DoUpdateCityConnectionEnergy MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=61; Civ5 changed/new=UNVERIFIED.
	void DoUpdateCityConnectionEnergy();
// TODO(Phase1 audit): CvTreasury::GetCityConnectionTradeRouteEnergyModifier MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
	int GetCityConnectionTradeRouteEnergyModifier() const;
// TODO(Phase1 audit): CvTreasury::ChangeCityConnectionTradeRouteEnergyModifier MISMATCH: First instruction opcode differs: object mov, BE call; BE instructions=11; Civ5 changed/new=UNVERIFIED.
	void ChangeCityConnectionTradeRouteEnergyModifier(int iChange);
// TODO(Phase1 audit): CvTreasury::GetCityConnectionTradeRouteEnergyChange MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
	int GetCityConnectionTradeRouteEnergyChange() const;
// TODO(Phase1 audit): CvTreasury::ChangeCityConnectionTradeRouteEnergyChange MISMATCH: First instruction opcode differs: object mov, BE call; BE instructions=11; Civ5 changed/new=UNVERIFIED.
	void ChangeCityConnectionTradeRouteEnergyChange(int iChange);
// TODO(Phase1 audit): CvTreasury::HasCityConnectionRouteBetweenCities MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=81; Civ5 changed/new=UNVERIFIED.
	bool HasCityConnectionRouteBetweenCities(CvCity* pFirstCity, CvCity* pSecondCity, bool bBestRoute = false) const;
	int GetEnergyPerTurnFromTradeRoutes() const;
	int GetEnergyPerTurnFromTradeRoutesTimes100() const;
// TODO(Phase1 audit): CvTreasury::GetEnergyPerTurnFromTraits MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=23; Civ5 changed/new=UNVERIFIED.
	int GetEnergyPerTurnFromTraits() const;
// TODO(Phase1 audit): CvTreasury::GetEnergyPerTurnFromReligion MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=60; Civ5 changed/new=UNVERIFIED.
	int GetEnergyPerTurnFromReligion() const;
// TODO(Phase1 audit): CvTreasury::GetEnergyPerTurnFromPolicies MISMATCH: First instruction opcode differs: object xor, BE push; BE instructions=47; Civ5 changed/new=UNVERIFIED.
	int GetEnergyPerTurnFromPolicies() const;
// TODO(Phase1 audit): CvTreasury::GetTotalEnergyPerTurn UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	int GetTotalEnergyPerTurn();
// TODO(Phase1 audit): CvTreasury::GetTotalEnergyPerTurnTimes100 MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=38; Civ5 changed/new=UNVERIFIED.
	int GetTotalEnergyPerTurnTimes100();
// TODO(Phase1 audit): CvTreasury::GetLifetimeGrossEnergy MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
	int GetLifetimeGrossEnergy();
// TODO(Phase1 audit): CvTreasury::GetTotalNetEnergyPerTurn UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=17; Civ5 changed/new=UNVERIFIED.
	int GetTotalNetEnergyPerTurn();
// TODO(Phase1 audit): CvTreasury::GetTotalNetEnergyPerTurnTimes100 UNVERIFIED: Full target-preserving relocation/PIC/branch comparison not established; equal counts/first opcode are not match evidence; BE instructions=44; Civ5 changed/new=UNVERIFIED.
	int GetTotalNetEnergyPerTurnTimes100();
// TODO(Phase1 audit): CvTreasury::GetTotalEnergyCostsPerTurn MISMATCH: Instruction 1 differs before first target reference: object [push   %ebx] vs BE [push   %ebp]; BE instructions=58; Civ5 changed/new=UNVERIFIED.
	int GetTotalEnergyCostsPerTurn();
// TODO(Phase1 audit): CvTreasury::GetTotalEnergyCostsPerTurnTimes100 MISMATCH: Instruction 2 differs before first target reference: object [push   %edi] vs BE [sub    $0x8,%esp]; BE instructions=12; Civ5 changed/new=UNVERIFIED.
	int GetTotalEnergyCostsPerTurnTimes100();
// TODO(Phase1 audit): CvTreasury::CalculateUnitCost MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=256; Civ5 changed/new=UNVERIFIED.
	int CalculateUnitCost(int& iFreeUnits, int& iPaidUnits, int& iBaseUnitCost, int& iExtraCost);
// TODO(Phase1 audit): CvTreasury::CalculateUnitSupply MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=96; Civ5 changed/new=UNVERIFIED.
	int CalculateUnitSupply(int& iPaidUnits, int& iBaseSupplyCost);
// TODO(Phase1 audit): CvTreasury::GetBuildingEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=86; Civ5 changed/new=UNVERIFIED.
	int GetBuildingEnergyMaintenance() const;
// TODO(Phase1 audit): CvTreasury::GetBaseBuildingEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
	int GetBaseBuildingEnergyMaintenance() const;
// TODO(Phase1 audit): CvTreasury::SetBaseBuildingEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=7; Civ5 changed/new=UNVERIFIED.
	void SetBaseBuildingEnergyMaintenance(int iValue);
// TODO(Phase1 audit): CvTreasury::ChangeBaseBuildingEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=7; Civ5 changed/new=UNVERIFIED.
	void ChangeBaseBuildingEnergyMaintenance(int iChange);
// TODO(Phase1 audit): CvTreasury::GetImprovementEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=42; Civ5 changed/new=UNVERIFIED.
	int GetImprovementEnergyMaintenance() const;
// TODO(Phase1 audit): CvTreasury::GetBaseImprovementEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
	int GetBaseImprovementEnergyMaintenance() const;
// TODO(Phase1 audit): CvTreasury::SetBaseImprovementEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=34; Civ5 changed/new=UNVERIFIED.
	void SetBaseImprovementEnergyMaintenance(int iValue);
// TODO(Phase1 audit): CvTreasury::ChangeBaseImprovementEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=14; Civ5 changed/new=UNVERIFIED.
	void ChangeBaseImprovementEnergyMaintenance(int iChange);
// TODO(Phase1 audit): CvTreasury::GetRouteEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=25; Civ5 changed/new=UNVERIFIED.
	int GetRouteEnergyMaintenance() const;
// TODO(Phase1 audit): CvTreasury::GetBaseRouteEnergyMaintenance MISMATCH: Reference-free full instruction streams differ in instructions/registers/constants/field offsets; BE instructions=3; Civ5 changed/new=UNVERIFIED.
	int GetBaseRouteEnergyMaintenance() const;
// TODO(Phase1 audit): CvTreasury::SetBaseRouteEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=34; Civ5 changed/new=UNVERIFIED.
	void SetBaseRouteEnergyMaintenance(int iValue);
// TODO(Phase1 audit): CvTreasury::ChangeBaseRouteEnergyMaintenance MISMATCH: First instruction opcode differs: object mov, BE push; BE instructions=14; Civ5 changed/new=UNVERIFIED.
	void ChangeBaseRouteEnergyMaintenance(int iChange);
// TODO(Phase1 audit): CvTreasury::AverageIncome MISMATCH: Instruction 1 differs before first target reference: object [push   %edi] vs BE [push   %esi]; BE instructions=29; Civ5 changed/new=UNVERIFIED.
	double AverageIncome(int iTurns);
// TODO(Phase1 audit): CvTreasury::LogExpenditure MISMATCH: First instruction opcode differs: object ret, BE push; BE instructions=1442; Civ5 changed/new=UNVERIFIED.
	void LogExpenditure(CvString strExpenditure, int iAmount, int iColumn);

private:
	CvPlayer* m_pPlayer;
	int m_iEnergy;
	int m_iTotalAccumulatedEnergy;
	int m_iEnergyPerTurnFromDiplomacy;
	int m_iExpensePerTurnUnitMaintenance;
	int m_iExpensePerTurnUnitSupply;
	int m_iCityConnectionEnergyTimes100;
	int m_iCityConnectionTradeRouteEnergyModifier;
	int m_iCityConnectionTradeRouteEnergyChange;
	int m_iBaseBuildingEnergyMaintenance;
	int m_iBaseImprovementEnergyMaintenance;
	int m_iBaseRouteEnergyMaintenance;
	int m_iLifetimeGrossEnergyIncome;
	std::vector<int> m_EnergyBalanceForTurnTimes100;
	std::vector<int> m_EnergyChangeForTurnTimes100;
};

namespace TreasuryHelpers
{
// TODO(Phase1 audit): TreasuryHelpers::AppendToLog UNVERIFIED: Overloads require exact signature attribution; inspect per-mangled-symbol results (some overloads have proved instruction mismatches); BE instructions=67,69,52; Civ5 changed/new=UNVERIFIED.
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, CvString strValue);
// TODO(Phase1 audit): TreasuryHelpers::AppendToLog UNVERIFIED: Overloads require exact signature attribution; inspect per-mangled-symbol results (some overloads have proved instruction mismatches); BE instructions=67,69,52; Civ5 changed/new=UNVERIFIED.
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, int iValue);
// TODO(Phase1 audit): TreasuryHelpers::AppendToLog UNVERIFIED: Overloads require exact signature attribution; inspect per-mangled-symbol results (some overloads have proved instruction mismatches); BE instructions=67,69,52; Civ5 changed/new=UNVERIFIED.
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, float fValue);
}
