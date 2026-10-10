#pragma once

#include "CvGameCoreDLLUtil/include/CvStructs.h"

class CvPlot;
class CvStrategicSite;

class CvOutpost
{
public:
	void InitFromLoad();
	const char* GetName() const;
	TeamTypes GetTeam() const;
	CvPlot* GetPlot() const;
	IDInfo GetIDInfo() const;
	CvStrategicSite* GetStrategicSite() const;
	const char* GetBombardEffectTag();
};
