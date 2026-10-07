#pragma once

namespace Database { class Results; }
class CvDatabaseUtility;

// Partial SDK declarations for Lua action exposures.
class CvActionInfo
{
public:
	CvActionInfo();
	int getMissionData() const;
	int getCommandData() const;
	int getAutomateType() const;
	int getInterfaceModeType() const;
	int getMissionType() const;
	int getCommandType() const;
	int getControlType() const;
	int getOriginalIndex() const;
	bool isConfirmCommand() const;
	bool isVisible() const;
	ActionSubTypes getSubType() const;
	const char* GetType() const;
	const char* GetHelp() const;
	const char* GetDisabledHelp() const;
	const char* GetTextKey() const;
	int getActionInfoIndex() const;
	int getHotKeyVal() const;
	int getHotKeyPriority() const;
	int getHotKeyValAlt() const;
	int getHotKeyPriorityAlt() const;
	int getOrderPriority() const;
	bool isAltDown() const;
	bool isShiftDown() const;
	bool isCtrlDown() const;
	bool isAltDownAlt() const;
	bool isShiftDownAlt() const;
	bool isCtrlDownAlt() const;
	const char* getHotKeyString() const;
	// TODO: CvActionInfo (remaining SDK members).
};

// Partial SDK base-info declaration.
class CvBaseInfo
{
public:
	CvBaseInfo();
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	const char* GetDescription() const
	{
		return m_strDescription.c_str();
	}
private:
	int m_iID;
	CvString m_strCivilopedia;
	CvString m_strDescription;
	// TODO: CvBaseInfo (remaining SDK members).
};

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