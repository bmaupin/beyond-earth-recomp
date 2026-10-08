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
	const char* GetType() const
	{
		return m_strType.c_str();
	}
private:
	int m_iID;
	CvString m_strCivilopedia;
	CvString m_strDescription;
	CvString m_strDescriptionKey;
	CvString m_strHelp;
	CvString m_strDisabledHelp;
	CvString m_strStrategy;
	CvString m_strType;
	CvString m_strTextKey;
	CvString m_strText;
	// TODO: CvBaseInfo (remaining SDK methods).
};

class CvHotKeyInfo : public CvBaseInfo
{
public:
	CvHotKeyInfo();

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

	int getActionInfoIndex() const;
	void setActionInfoIndex(int i);
	int getHotKeyVal() const;
	void setHotKeyVal(int i);
	int getHotKeyPriority() const;
	void setHotKeyPriority(int i);
	int getHotKeyValAlt() const;
	void setHotKeyValAlt(int i);
	int getHotKeyPriorityAlt() const;
	void setHotKeyPriorityAlt(int i);
	int getOrderPriority() const;
	void setOrderPriority(int i);

	bool isAltDown() const;
	void setAltDown(bool b);
	bool isShiftDown() const;
	void setShiftDown(bool b);
	bool isCtrlDown() const;
	void setCtrlDown(bool b);
	bool isAltDownAlt() const;
	void setAltDownAlt(bool b);
	bool isShiftDownAlt() const;
	void setShiftDownAlt(bool b);
	bool isCtrlDownAlt() const;
	void setCtrlDownAlt(bool b);

	const char* getHotKey() const;
	void setHotKey(const char* szVal);
	const char* getHelp() const;
	const char* getDisabledHelp() const;
	std::string getHotKeyDescription() const;
	const char* getHotKeyString() const;
	void setHotKeyDescription(const char* swzHotKeyDescKey, const char* szHotKeyAltDescKey, const char* szHotKeyString);

	static CvString CreateHotKeyFromDescription(const char* pszHotKey, bool bShift, bool bAlt, bool bCtrl);
	static CvString CreateKeyStringFromKBCode(const char* pszHotKey);

protected:
	int GetHotKeyInt(const char* pszHotKeyVal);

	int m_iActionInfoIndex;
	int m_iHotKeyVal;
	int m_iHotKeyPriority;
	int m_iHotKeyValAlt;
	int m_iHotKeyPriorityAlt;
	int m_iOrderPriority;

	bool m_bAltDown;
	bool m_bShiftDown;
	bool m_bCtrlDown;
	bool m_bAltDownAlt;
	bool m_bShiftDownAlt;
	bool m_bCtrlDownAlt;

	CvString m_strHotKey;
	CvString m_strHotKeyDescriptionKey;
	CvString m_strHotKeyAltDescriptionKey;
	CvString m_strHotKeyString;
	CvString m_strHelp;
	CvString m_strDisabledHelp;
};

class CvInterfaceModeInfo : public CvHotKeyInfo
{
public:
	CvInterfaceModeInfo();

	int getCursorIndex() const;
	int getMissionType() const;
	bool getVisible() const;
	bool getHighlightPlot() const;
	bool getSelectType() const;
	bool getSelectAll() const;

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

protected:
	int m_iCursorIndex;
	int m_iMissionType;
	bool m_bVisible;
	bool m_bHighlightPlot;
	bool m_bSelectType;
	bool m_bSelectAll;
};

class CvColorInfo : public CvBaseInfo
{
public:
	const CvColorA& GetColor() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
protected:
	CvColorA m_Color;
};

class CvPlayerOptionInfo : public CvBaseInfo
{
public:
	CvPlayerOptionInfo();

	bool getDefault() const;

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

private:
	bool m_bDefault;
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