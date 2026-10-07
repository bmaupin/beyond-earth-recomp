#pragma once

#ifndef CIV5_PROJECT_CLASSES_H
#define CIV5_PROJECT_CLASSES_H

// Partial SDK declarations needed by CvProjectProductionAI.
class CvProjectEntry: public CvBaseInfo
{
public:
	int GetFlavorValue(int i) const;
	// TODO: CvProjectEntry (remaining SDK members and Beyond Earth changes).
};

class CvProjectXMLEntries
{
public:
	CvProjectXMLEntries(void);
	~CvProjectXMLEntries(void);
	std::vector<CvProjectEntry*>& GetProjectEntries();
	int GetNumProjects();
	CvProjectEntry* GetEntry(int index);
	void DeleteArray();

private:
	std::vector<CvProjectEntry*> m_paProjectEntries;
};

#endif //CIV5_PROJECT_CLASSES_H