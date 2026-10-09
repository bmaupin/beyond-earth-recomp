#pragma once
#include "CvPoint.h"

// Forward declaration retained from CvGlobals.h for CvBuildingClassInfo users.
class CvBuildingClassInfo;
class CvPolicyEntry;
class CvProjectXMLEntries;
class CvGame;
class CvRandom;
class CvActionInfo;
class CvEntityEventInfo;
class CvDeal;
class ICvDeal1;
class CvMap;
class CvTwoLayerPathFinder;
class CvIgnoreUnitsPathFinder;
class CvStepPathFinder;
class CvAStar;
class ICvDLLDatabaseUtility1;
class CvInterfaceModeInfo;
namespace Database { class Connection; }

// Partial SDK declaration.
// TODO: CvGlobals (remaining members).
class CvGlobals
{
public:
	virtual ~CvGlobals();
	typedef stdext::hash_map<std::string /* type string */, int /* info index */> InfosMap;
	const InfosMap& GetInfoTypes() const;
	std::vector<CvActionInfo*>& getActionInfo();
	_Ret_maybenull_ CvEntityEventInfo* getEntityEventInfo(EntityEventTypes e);

	CvDeal* UnwrapDealPointer(ICvDeal1* pDeal);
	CvProjectXMLEntries* GetGameProjects() const;
	bool getLogging();
	bool getAILogging();
	Database::Connection* GetGameDatabase()
	{
		return m_pGameDatabase;
	}
	const Database::Connection* GetGameDatabase() const
	{
		return m_pGameDatabase;
	}
	CvGame& getGame()
	{
		return *m_game;    // inlined for perf reasons, do not use outside of dll
	}

	ICvEngineUtility4* getDLLIFace()
	{
		// Remaining globals members are not imported; DWARF places m_pDLL at 9480.
		return *reinterpret_cast<ICvEngineUtility4**>(reinterpret_cast<char*>(this) + 9480);
	}

protected:
	// Real Beyond Earth prefix, verified against DWARF (m_game at +0x30).
	bool m_bGraphicsInitialized;
	bool m_bDLLProfiler;
	bool m_bTutorialDisabled;
	bool m_bLogging;
	int m_iRandLogging;
	bool m_bAILogging;
	bool m_bAIPerfLogging;
	bool m_bBuilderAILogging;
	bool m_bBuilderAIYieldLogging;
	bool m_bPlayerAndCityAILogSplit;
	bool m_bTutorialLogging;
	bool m_bTutorialDebugging;
	bool m_bAllowRClickMovementWhileCameraScrolling;
	bool m_bPostTurnAutosaves;
	bool m_bOutOfSyncDebuggingEnabled;
	CvPoint3f m_pt3CameraDir;
	int m_iNewPlayers;
	bool m_bZoomOut;
	bool m_bZoomIn;
	bool m_bLoadGameFromFile;
	CvRandom* m_asyncRand;
	CvGame* m_game;
	CvMap* m_map;
	CvTwoLayerPathFinder* m_pathFinder;
	CvTwoLayerPathFinder* m_interfacePathFinder;
	CvIgnoreUnitsPathFinder* m_ignoreUnitsPathFinder;
	CvStepPathFinder* m_stepFinder;
	CvAStar* m_routeFinder;
	CvAStar* m_waterRouteFinder;
	CvAStar* m_borderFinder;
	CvAStar* m_areaFinder;
	CvAStar* m_influenceFinder;
	CvAStar* m_buildRouteFinder;
	CvAStar* m_internationalTradeRouteLandFinder;
	CvAStar* m_internationalTradeRouteWaterFinder;
	// Beyond Earth adds the amphibious trade pathfinder and lake yields.
	CvAStar* m_internationalTradeRouteAmphibiousFinder;
	CvTwoLayerPathFinder* m_tacticalAnalysisMapFinder;
	ICvDLLDatabaseUtility1* m_pkDatabaseLoadUtility;
	int m_aiPlotDirectionX[NUM_DIRECTION_TYPES];
	int m_aiPlotDirectionY[NUM_DIRECTION_TYPES];
	int m_aiCityPlotX[37];
	int m_aiCityPlotY[37];
	int m_aiCityPlotPriority[37];
	int m_aaiXYCityPlot[7][7];
	DirectionTypes m_aeTurnLeftDirection[NUM_DIRECTION_TYPES];
	DirectionTypes m_aeTurnRightDirection[NUM_DIRECTION_TYPES];
	FlowDirectionTypes* m_aeTurnLeftFlowDirection[NUM_FLOWDIRECTION_TYPES];
	FlowDirectionTypes* m_aeTurnRightFlowDirection[NUM_FLOWDIRECTION_TYPES];
	std::vector<CvInterfaceModeInfo*> m_paInterfaceModeInfo;
	int m_lakeYields[NUM_YIELD_TYPES];
	Database::Connection* m_pGameDatabase;
	// TODO: CvGlobals (remaining data members, including m_pDLL).
};

extern CvGlobals gGlobals;
#define GC gGlobals
#define DB (*GC.GetGameDatabase())
#define gDLL GC.getDLLIFace()