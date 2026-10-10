#pragma once

class CvCity;
class CvPlayer;
class FDataStream;

class CvTreasury
{
public:
	CvTreasury();
	virtual ~CvTreasury();
	void Init(CvPlayer* pPlayer);
	void Uninit();
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream);
	void DoEnergyTurn();

	int GetEnergyTimes100() const;
	void SetEnergyTimes100(int iValue);
	void ChangeEnergyTimes100(int iChange);
	int GetTotalAccumulatedEnergy() const;
	void SetTotalAccumulatedEnergy(int iValue);
	void ChangeTotalAccumulatedEnergy(int iChange);
	int GetEnergyFromCities() const;
	int GetEnergyFromCitiesTimes100(bool bExcludeTradeRoutes = false) const;
	int GetEnergyPerTurnFromDiplomacy() const;
	void SetEnergyPerTurnFromDiplomacy(int iValue);
	void ChangeEnergyPerTurnFromDiplomacy(int iChange);
	int GetCityConnectionRouteEnergyTimes100(CvCity* pCity) const;
	int GetCityConnectionEnergy() const;
	int GetCityConnectionEnergyTimes100() const;
	void DoUpdateCityConnectionEnergy();
	int GetCityConnectionTradeRouteEnergyModifier() const;
	void ChangeCityConnectionTradeRouteEnergyModifier(int iChange);
	int GetCityConnectionTradeRouteEnergyChange() const;
	void ChangeCityConnectionTradeRouteEnergyChange(int iChange);
	bool HasCityConnectionRouteBetweenCities(CvCity* pFirstCity, CvCity* pSecondCity, bool bBestRoute = false) const;
	int GetEnergyPerTurnFromTradeRoutes() const;
	int GetEnergyPerTurnFromTradeRoutesTimes100() const;
	int GetEnergyPerTurnFromTraits() const;
	int GetEnergyPerTurnFromReligion() const;
	int GetEnergyPerTurnFromPolicies() const;
	int GetTotalEnergyPerTurn();
	int GetTotalEnergyPerTurnTimes100();
	int GetLifetimeGrossEnergy();
	int GetTotalNetEnergyPerTurn();
	int GetTotalNetEnergyPerTurnTimes100();
	int GetTotalEnergyCostsPerTurn();
	int GetTotalEnergyCostsPerTurnTimes100();
	int CalculateUnitCost(int& iFreeUnits, int& iPaidUnits, int& iBaseUnitCost, int& iExtraCost);
	int CalculateUnitSupply(int& iPaidUnits, int& iBaseSupplyCost);
	int GetBuildingEnergyMaintenance() const;
	int GetBaseBuildingEnergyMaintenance() const;
	void SetBaseBuildingEnergyMaintenance(int iValue);
	void ChangeBaseBuildingEnergyMaintenance(int iChange);
	int GetImprovementEnergyMaintenance() const;
	int GetBaseImprovementEnergyMaintenance() const;
	void SetBaseImprovementEnergyMaintenance(int iValue);
	void ChangeBaseImprovementEnergyMaintenance(int iChange);
	int GetRouteEnergyMaintenance() const;
	int GetBaseRouteEnergyMaintenance() const;
	void SetBaseRouteEnergyMaintenance(int iValue);
	void ChangeBaseRouteEnergyMaintenance(int iChange);
	double AverageIncome(int iTurns);
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
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, CvString strValue);
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, int iValue);
	void AppendToLog(CvString& strHeader, CvString& strLog, CvString strHeaderValue, float fValue);
}
