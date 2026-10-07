#pragma once

// Forward declaration retained from CvGlobals.h for CvBuildingClassInfo users.
class CvBuildingClassInfo;
class CvPolicyEntry;
class CvProjectXMLEntries;
class CvGame;
class CvActionInfo;

// Partial SDK declaration.
// TODO: CvGlobals (remaining members).
class CvGlobals
{
public:
	typedef stdext::hash_map<std::string /* type string */, int /* info index */> InfosMap;
	const InfosMap& GetInfoTypes() const;
	std::vector<CvActionInfo*>& getActionInfo();

	CvProjectXMLEntries* GetGameProjects() const;
	bool getLogging();
	bool getAILogging();
	CvGame& getGame()
	{
		return *m_game;    // inlined for perf reasons, do not use outside of dll
	}

	ICvEngineUtility4* getDLLIFace()
	{
		return m_pDLL;
	}

private:
	CvGame* m_game;
	// DLL interface
	ICvEngineUtility4* m_pDLL;
};

extern CvGlobals gGlobals;
#define GC gGlobals
#define gDLL GC.getDLLIFace()