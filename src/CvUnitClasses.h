#pragma once

class CvUnitEntry: public CvBaseInfo
{
public:
	CvUnitEntry(void);
	~CvUnitEntry(void);

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	int GetCombat() const;
	int GetDomainType() const;
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

// TODO: CvUnitXMLEntries.
