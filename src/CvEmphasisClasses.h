#pragma once

class CvEmphasisEntry : public CvBaseInfo
{
public:
	CvEmphasisEntry();
	~CvEmphasisEntry();
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	bool IsAvoidGrowth() const;
	// NOTE: Great People emphasis does not exist in Beyond Earth.
	// bool IsGreatPeople() const;
	int GetYieldChange(int i) const;

private:
	bool m_bAvoidGrowth;
	int* m_piYieldModifiers;
	// Intentionally undefined, as in the SDK: entries are noncopyable.
	CvEmphasisEntry(const CvEmphasisEntry&);
	CvEmphasisEntry& operator=(const CvEmphasisEntry&);
};

class CvEmphasisXMLEntries
{
public:
	CvEmphasisXMLEntries();
	~CvEmphasisXMLEntries();
	std::vector<CvEmphasisEntry*>& GetEmphasisEntries();
	int GetNumEmphases();
	_Ret_maybenull_ CvEmphasisEntry* GetEntry(int index);
	void DeleteArray();

private:
	std::vector<CvEmphasisEntry*> m_paEmphasisEntries;
};

class CvCityEmphases
{
public:
	CvCityEmphases();
	~CvCityEmphases();
	void Init(CvEmphasisXMLEntries* pEmphases, CvCity* pCity);
	void Uninit();
	void Reset();
	int GetEmphasizeAvoidGrowthCount();
	bool IsEmphasizeAvoidGrowth();
	// NOTE: Great People emphasis does not exist in Beyond Earth.
	// int GetEmphasizeGreatPeopleCount();
	// bool IsEmphasizeGreatPeople();
	int GetEmphasizeYieldCount(YieldTypes eIndex);
	bool IsEmphasizeYield(YieldTypes eIndex);
	bool IsEmphasize(EmphasizeTypes eIndex);
	void SetEmphasize(EmphasizeTypes eIndex, bool bNewValue);
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream);

private:
	// Beyond Earth removes the SDK's Great People counter and entry flag.
	int m_iEmphasizeAvoidGrowthCount;
	int m_aiEmphasizeYieldCount[NUM_YIELD_TYPES];
	bool* m_pbEmphasize;
	CvEmphasisXMLEntries* m_pEmphases;
	CvCity* m_pCity;
};
