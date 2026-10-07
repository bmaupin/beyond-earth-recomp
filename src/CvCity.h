#pragma once

class CvCityStrategyAI;

// Partial SDK declarations.
class CvCity
{
public:
	// Beyond Earth adds the optional failure-message argument.
	bool canCreate(ProjectTypes eProject, bool bContinue = false, bool bTestVisible = false, CvString* pFailureMessage = NULL) const;
	int getProductionTurnsLeft(ProjectTypes eProject, int iNum) const;
	// TODO: CvCity::getOwner (SDK inline body; requires m_eOwner).
	PlayerTypes getOwner() const;
	const CvString getName() const;
	CvCityStrategyAI* GetCityStrategyAI() const;
	// TODO: CvCity (remaining members).
};