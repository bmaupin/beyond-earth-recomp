#pragma once

class CvCity;
class CvPlayerAffinities;
class CvLeaderHeadInfo;
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
	// TODO: Reimplement using m_pAffinities after restoring the authentic CvPlayer layout; DWARF offset 0xf4b4.
	CvPlayerAffinities* GetPlayerAffinities() const
	{
		return *reinterpret_cast<CvPlayerAffinities* const*>(reinterpret_cast<const char*>(this) + 0xf4b4);
	}
	CvLeaderHeadInfo& getLeaderInfo() const;
	const char* getCivilizationShortDescription() const;
	const CvCity* firstCity(int* pIterIdx, bool bRev = false) const;
	const CvCity* nextCity(int* pIterIdx, bool bRev = false) const;
	// TODO: CvPlayer (remaining members).
};