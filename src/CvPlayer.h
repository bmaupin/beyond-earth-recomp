#pragma once

class CvCity;
class CvPlayerPerks
{
public:
	int GetCityMoveCostMod(const CvCity& city) const;
	// TODO: Inline after restoring authentic members through m_aquaticCityMoveCostMod (target offset 0x44).
	int GetAquaticCityMoveCostMod() const;
};

class CvPlayer
{
public:
	bool isHuman() const;
	bool IsAITeammateOfHuman() const;
	bool isAlien() const;
	bool isNeutralProxy() const;
	// TODO: Inline after restoring authentic members through m_pPlayerPerks (target offset 0xf4bc).
	CvPlayerPerks* GetPlayerPerks() const;
	const char* getCivilizationShortDescription() const;
	const CvCity* firstCity(int* pIterIdx, bool bRev = false) const;
	const CvCity* nextCity(int* pIterIdx, bool bRev = false) const;
	// TODO: CvPlayer (remaining members).
};