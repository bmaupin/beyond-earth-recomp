#pragma once

class CvBuildingEntry: public CvBaseInfo
{
public:
	CvBuildingEntry(void);
	~CvBuildingEntry(void);

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	int GetPreferredDisplayPosition() const;
	const char* GetArtDefineTag() const;
	const char* GetWonderSplashAudio() const;
	// TODO: CvBuildingEntry (remaining SDK methods and Beyond Earth members).
};

// TODO: CvBuildingXMLEntries.
