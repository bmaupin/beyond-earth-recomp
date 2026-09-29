#pragma once

// Supporting declaration copied from CvInfos.h as required by
// CvInternalGameCoreUtils.cpp.
class CvBuildingClassInfo
{
public:
	CvBuildingClassInfo();
	virtual ~CvBuildingClassInfo();

	int getMaxGlobalInstances() const;
	int getMaxTeamInstances() const;
	int getMaxPlayerInstances() const;
	int getExtraPlayerInstances() const;
	int getDefaultBuildingIndex() const;
	void setDefaultBuildingIndex(int i);

	bool isNoLimit() const;
	bool isMonument() const;
};