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
	~CvBaseInfo();
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	virtual bool operator==(const CvBaseInfo&) const;
	virtual void readFrom(FDataStream&);
	virtual void writeTo(FDataStream&) const;
	const char* GetDescription() const
	{
		return m_strDescription.c_str();
	}
	const char* GetType() const
	{
		return m_strType.c_str();
	}
	const char* GetText() const;
	const char* GetTextKey() const;
	const char* GetDescriptionKey() const
	{
		return m_strDescriptionKey.c_str();
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

// Partial SDK civilization declarations; native getters remain external.
class CvCivilizationBaseInfo : public CvBaseInfo
{
public:
	CvCivilizationBaseInfo();
	virtual ~CvCivilizationBaseInfo();
	bool isAIPlayable() const;
	bool isPlayable() const;
	const char* getShortDescription() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvCivilizationBaseInfo (remaining SDK methods and members).
};

class CvCivilizationInfo : public CvCivilizationBaseInfo
{
public:
	CvCivilizationInfo();
	virtual ~CvCivilizationInfo();
	int getDefaultPlayerColor() const;
	int getArtStyleType() const;
	int getNumCityNames() const;
	const char* getArtStylePrefix() const;
	const char* getArtStyleSuffix() const;
	const char* GetDawnOfManAudio() const;
	int getCivilizationBuildings(int i) const;
	bool isLeaders(int i) const;
	const char* getCityNames(int i) const;
	const char* getSoundtrackKey() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvCivilizationInfo (remaining SDK methods and members).
};

class CvEraInfo : public CvBaseInfo
{
public:
	CvEraInfo();
	virtual ~CvEraInfo();

	int GetNumEraVOs() const;
	const char* GetEraVO(int iIndex);
	const char* getArtPrefix() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvEraInfo (remaining SDK methods and Beyond Earth members).
};

class CvWorldInfo : public CvBaseInfo
{
public:
	CvWorldInfo();
	int getDefaultPlayers() const;
	int getGridWidth() const;
	int getGridHeight() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvWorldInfo (remaining SDK methods and Beyond Earth members).
};

class CvResourceInfo : public CvBaseInfo
{
public:
	CvResourceInfo();
	virtual ~CvResourceInfo();

	int getResourceClassType() const;
	ResourceUsageTypes getResourceUsage() const;
	const char* GetIconString() const;
	const char* getArtDefineTag() const;
	const char* getArtDefineTagHeavy() const;
	const char* getAltArtDefineTag() const;
	const char* getAltArtDefineTagHeavy() const;
	bool isTerrain(int i) const;
	bool isFeature(int i) const;
	bool isFeatureTerrain(int i) const;
	// Beyond Earth adds the improvement-placement predicate.
	bool ImprovementInResource() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvResourceInfo (remaining SDK methods and Beyond Earth members).
};

class CvFeatureInfo : public CvBaseInfo
{
public:
	CvFeatureInfo();
	virtual ~CvFeatureInfo();

	// Beyond Earth renames the SDK placement predicates.
	bool RequiresNoCoast() const;
	bool RequiresNoRiver() const;
	bool RequiresNoAdjacentSameFeature() const;
	bool RequiresFlatTerrain() const;
	bool RequiresRiver() const;
	bool RequiresTerrainType(int i) const;
	const char* getArtDefineTag() const;
	int getWorldSoundscapeScriptId() const;
	const char* getEffectTypeTag() const;
	void RefreshWorldSoundscapeID();
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvFeatureInfo (remaining SDK methods and Beyond Earth members).
};

class CvTerrainInfo : public CvBaseInfo
{
public:
	CvTerrainInfo();
	virtual ~CvTerrainInfo();

	bool isWater() const;
	const char* getArtDefineTag() const;
	int getWorldSoundscapeScriptId() const;
	const char* getEffectTypeTag() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

	// Beyond Earth refreshes the cached soundscape script ID.
	void RefreshWorldSoundscapeID();
	// TODO: CvTerrainInfo (remaining SDK methods and Beyond Earth members).
};

class CvPlayerColorInfo : public CvBaseInfo
{
public:
	CvPlayerColorInfo();

	int GetColorTypePrimary() const;
	int GetColorTypeSecondary() const;
	int GetColorTypeText() const;

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtilty);

private:
	int m_iColorTypePrimary;
	int m_iColorTypeSecondary;
	int m_iColorTypeText;
};

class CvGameOptionInfo : public CvBaseInfo
{
public:
	CvGameOptionInfo();

	bool getDefault() const;
	bool getVisible() const;

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

private:
	bool m_bDefault;
	bool m_bVisible;
};

class CvGameSpeedInfo : public CvBaseInfo
{
public:
	CvGameSpeedInfo();
	virtual ~CvGameSpeedInfo();

	// Beyond Earth adds turn thresholds exposed by the DLL wrapper.
	int getCreatePercent() const;
	int getMidGameTurn() const;
	int getLateGameTurn() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvGameSpeedInfo (remaining SDK methods and Beyond Earth members).
};

class CvHandicapInfo : public CvBaseInfo
{
public:
	CvHandicapInfo();
	virtual ~CvHandicapInfo();

	// Beyond Earth replaces getBarbSpawnMod with getAlienSpawnMod.
	int getAlienSpawnMod() const;
	int getAIWorldCreatePercent() const;
	int getAICreatePercent() const;
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvHandicapInfo (remaining SDK methods and Beyond Earth members).
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

class CvMissionInfo : public CvHotKeyInfo
{
public:
	CvMissionInfo();

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvMissionInfo (remaining SDK methods and members).
};

class CvBuildInfo : public CvHotKeyInfo
{
public:
	CvBuildInfo();
	virtual ~CvBuildInfo();

	int getImprovement() const { return m_iImprovement; }
	int getRoute() const { return m_iRoute; }
	int getEntityEvent() const { return m_iEntityEvent; }

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

protected:
	int m_iTime;
	int m_iCost;
	int m_iCostIncreasePerImprovement;
	// Beyond Earth adds expedition charges and terrain/feature changes.
	int m_iExpeditionChargesNeeded;
	int m_iTechPrereq;
	int m_iImprovement;
	int m_iTerrainTypeChange;
	int m_iFeatureTypeChange;
	int m_iRoute;
	int m_iEntityEvent;
	// TODO: CvBuildInfo (remaining SDK methods and Beyond Earth members).
};

class CvEntityEventInfo : public CvBaseInfo
{
public:
	CvEntityEventInfo();
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvEntityEventInfo (remaining SDK methods and members).
};

class CvLeaderHeadInfo : public CvBaseInfo
{
public:
	CvLeaderHeadInfo();
	virtual ~CvLeaderHeadInfo();

	const char* getArtDefineTag() const;

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvLeaderHeadInfo (remaining SDK methods and Beyond Earth members).
};

class CvVictoryInfo : public CvBaseInfo
{
public:
	CvVictoryInfo();
	virtual ~CvVictoryInfo();

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	// TODO: CvVictoryInfo (remaining SDK methods and Beyond Earth members).
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