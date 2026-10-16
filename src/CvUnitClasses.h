#pragma once

class CvUnitEntry: public CvBaseInfo
{
public:
	CvUnitEntry(void);
	~CvUnitEntry(void);

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	int GetCombat() const;
	int GetDomainType() const;
	int GetFlavorValue(int i) const;
	bool GetUnitAIType(int i) const;
	UnitMoveRate GetMoveRate(int numHexes) const;
	const char* GetUnitArtInfoTag() const;
	const bool GetUnitArtInfoCulturalVariation() const;
	const bool GetUnitArtInfoEraVariation() const;

	// Beyond Earth adds unit-art variations and orbital unit types.
	const bool GetUnitArtInfoUpgradeVariation() const;
	int GetUnitArtInfoVariationStart() const;
	const bool GetUnitArtInfoAmphibiousVariation() const;
	int GetOrbitalUnitType() const;
	// TODO: CvUnitEntry (remaining SDK methods and Beyond Earth members).
};

class CvUnitXMLEntries
{
public:
	CvUnitXMLEntries(void);
	~CvUnitXMLEntries(void);

	std::vector<CvUnitEntry*>& GetUnitEntries();
	int GetNumUnits();
	CvUnitEntry* GetEntry(int index);
	void DeleteArray();

private:
	std::vector<CvUnitEntry*> m_paUnitEntries;
};
