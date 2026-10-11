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
	int GetFlavorValue(int i) const;
	int GetTechPrereq() const;
	bool IsNoOccupiedUnhealth() const;
	int GetSpecialistType() const;
	int GetSpecialistCount() const;
	// TODO: CvBuildingEntry (remaining SDK methods and Beyond Earth members).
};

class CvBuildingXMLEntries
{
public:
	int GetNumBuildings();
	CvBuildingEntry* GetEntry(int iIndex);
};
