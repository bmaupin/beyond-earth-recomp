#pragma once

class CvCity;

class CvPlayer
{
public:
	const char* getCivilizationShortDescription() const;
	const CvCity* firstCity(int* pIterIdx, bool bRev = false) const;
	const CvCity* nextCity(int* pIterIdx, bool bRev = false) const;
	// TODO: CvPlayer (remaining members).
};