#pragma once

class CvImprovementEntry: public CvBaseInfo
{
public:
	CvImprovementEntry(void);
	~CvImprovementEntry(void);

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	bool IsWater() const;
	bool IsDestroyedWhenPillaged() const;
	bool IsGoody() const;
	const char* GetArtDefineTag() const;
	ImprovementUsageTypes GetImprovementUsage() const;
	int GetWorldSoundscapeScriptId() const;
	bool GetTerrainMakesValid(int i) const;
	bool IsImprovementResourceMakesValid(int i) const;

	// Beyond Earth adds soundscape refresh and selection/resource-visibility methods.
	void RefreshWorldSoundscapeID();
	bool IsSelectable() const;
	bool ResourceStaysVisible() const;
	// TODO: CvImprovementEntry (remaining SDK methods and Beyond Earth members).
};

// TODO: CvImprovementXMLEntries.
