#pragma once

class CvCityStrategyAI;
class CvPlot;

// Partial SDK declarations.
class CvCity
{
public:
	// Beyond Earth adds the optional failure-message argument.
	bool canCreate(ProjectTypes eProject, bool bContinue = false, bool bTestVisible = false, CvString* pFailureMessage = NULL) const;
	int getProductionTurnsLeft(ProjectTypes eProject, int iNum) const;
	// TODO: CvCity::getOwner() (restore SDK inline accessor after reconstructing its real member layout).
	PlayerTypes getOwner() const;
	bool IsPuppet() const;
	void GetProjectPlotList(ProjectTypes eProject, std::vector<int>& kPlots) const;
	const CvString getName() const;
	CvCityStrategyAI* GetCityStrategyAI() const;
	CvPlot* plot() const;
	CvPlot* GetBestCityMovePlot(int* piScore) const;
	// TODO: CvCity (remaining members).
};