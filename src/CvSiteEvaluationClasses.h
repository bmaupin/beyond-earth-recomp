#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"

class CvPlot;
class CvPlayer;

// Declaration-only virtual ABI; evaluator storage is not reconstructed here.
class CvCitySiteEvaluator
{
public:
	virtual void Init();
	virtual void ComputeFlavorMultipliers(CvPlayer* pPlayer);
	virtual bool CanFound(CvPlot* pPlot, const CvPlayer* pPlayer, bool bTestVisible) const;
	virtual int PlotFoundValue(CvPlot* pPlot, CvPlayer* pPlayer, YieldTypes eYield, bool bCoastOnly, bool bIsAquatic) const;
	virtual int PlotFertilityValue(CvPlot* pPlot);
	virtual int BestFoundValueForSpecificYield(CvPlayer* pPlayer, YieldTypes eYield);
protected:
	virtual int ComputeFoodValue(CvPlot* pPlot, CvPlayer* pPlayer) const;
	virtual int ComputeHealthValue(CvPlot* pPlot, CvPlayer* pPlayer) const;
	virtual int ComputeProductionValue(CvPlot* pPlot, CvPlayer* pPlayer) const;
	virtual int ComputeEnergyValue(CvPlot* pPlot, CvPlayer* pPlayer) const;
	virtual int ComputeScienceValue(CvPlot* pPlot, CvPlayer* pPlayer) const;
	virtual int ComputeStrategicResourceValue(CvPlot* pPlot, CvPlayer* pPlayer) const;
	virtual int ComputeMilitaryValue(CvPlot* pPlot, CvPlayer* pPlayer, int iPlotsFromCity) const;
	virtual int ComputeAquaticFactor(const CvPlayer& player) const;
};

class CvSiteEvaluatorForSettler : public CvCitySiteEvaluator
{
};

class CvSiteEvaluatorForStart : public CvCitySiteEvaluator
{
public:
	virtual void ComputeFlavorMultipliers(CvPlayer* pPlayer);
	int PlotFoundValue(CvPlot* pPlot, CvPlayer* pPlayer, YieldTypes eYield = NO_YIELD, bool bCoastOnly = false, bool bIsAquatic = false);
};
