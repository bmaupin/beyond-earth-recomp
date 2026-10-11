#pragma once
#include "CvDllInterfaces.h"

typedef void* HANDLE;

class ICvNetworkSyncronization1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0xbf3a714a, 0xc06f, 0x4cf9, {0xa6, 0x48, 0xf9, 0x1b, 0xd6, 0x14, 0x95, 0x92}}; return id; }
    virtual void ClearCityDeltas() = 0;
    virtual void ClearPlayerDeltas() = 0;
    virtual void ClearPlotDeltas() = 0;
    virtual void ClearRandomDeltas() = 0;
    virtual void ClearUnitDeltas() = 0;
    virtual void SyncCities() = 0;
    virtual void SyncPlayers() = 0;
    virtual void SyncPlots() = 0;
    virtual void SyncUnits() = 0;
};

class ICvNetMessageHandler1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0x8127f91f, 0x7567, 0x44bc, {0x9a, 0x59, 0xf6, 0xae, 0xfe, 0x19, 0x18, 0xe3}}; return id; }
    virtual void ResponseAdvancedStartAction(PlayerTypes, AdvancedStartActionTypes, int, int, int, bool) = 0;
    virtual void ResponseAutoMission(PlayerTypes, int) = 0;
    virtual void ResponseBarbarianRansom(PlayerTypes, int, int) = 0;
    virtual void ResponseChangeWar(PlayerTypes, TeamTypes, bool) = 0;
    virtual void ResponseChangeStationHostile(StationTypes, TeamTypes, bool) = 0;
    virtual void ResponseCityBuyPlot(PlayerTypes, int, int, int) = 0;
    virtual void ResponseCityDoTask(PlayerTypes, int, TaskTypes, int, int, bool, bool, bool, bool) = 0;
    virtual void ResponseCityPopOrder(PlayerTypes, int, int) = 0;
    virtual void ResponseCityPurchase(PlayerTypes, int, UnitTypes, BuildingTypes, ProjectTypes) = 0;
    virtual void ResponseCityPurchase(PlayerTypes, int, UnitTypes, BuildingTypes, ProjectTypes, int) = 0;
    virtual void ResponseCityPushOrder(PlayerTypes, int, int, OrderTypes, int, bool, bool, bool) = 0;
    virtual void ResponseCitySwapOrder(PlayerTypes, int, int) = 0;
    virtual void ResponseDestroyUnit(PlayerTypes, int) = 0;
    virtual void ResponseDiplomacyFromUI(PlayerTypes, PlayerTypes, FromUIDiploEventTypes, int, int, bool) = 0;
    virtual void ResponseDiploVote(PlayerTypes, PlayerTypes) = 0;
    virtual void ResponseDoCommand(PlayerTypes, int, CommandTypes, int, int, bool) = 0;
    virtual void ResponseExtendedGame(PlayerTypes) = 0;
    virtual void ResponseGiftUnit(PlayerTypes, PlayerTypes, int) = 0;
    virtual void ResponseLaunchSpaceship(PlayerTypes, VictoryTypes) = 0;
    virtual void ResponseLiberatePlayer(PlayerTypes, PlayerTypes, int) = 0;
    virtual void ResponseMinorCivGiftGold(PlayerTypes, PlayerTypes, int) = 0;
    virtual void ResponseMinorNoUnitSpawning(PlayerTypes, PlayerTypes, bool) = 0;
    virtual void ResponsePlayerDealFinalized(PlayerTypes, PlayerTypes, PlayerTypes, bool) = 0;
    virtual void ResponsePlayerOption(PlayerTypes, PlayerOptionTypes, bool) = 0;
    virtual void ResponsePushMission(PlayerTypes, int, MissionTypes, int, int, int, bool) = 0;
    virtual void ResponseRenameCity(PlayerTypes, int, const char *) = 0;
    virtual void ResponseRenameUnit(PlayerTypes, int, const char *) = 0;
    virtual void ResponseResearch(PlayerTypes, TechTypes, int, bool) = 0;
    virtual void ResponseResearch(PlayerTypes, TechTypes, int, PlayerTypes, bool) = 0;
    virtual void ResponseReturnCivilian(PlayerTypes, PlayerTypes, int, bool) = 0;
    virtual void ResponseSellBuilding(PlayerTypes, int, BuildingTypes) = 0;
    virtual void ResponseSetCityAIFocus(PlayerTypes, int, CityAIFocusTypes) = 0;
    virtual void ResponseSetCityAvoidGrowth(PlayerTypes, int, bool) = 0;
    virtual void ResponseSwapUnits(PlayerTypes, int, MissionTypes, int, int, int, bool) = 0;
    virtual void ResponseUpdateCityCitizens(PlayerTypes, int) = 0;
    virtual void ResponseUpdatePolicies(PlayerTypes, bool, int, bool) = 0;
    virtual void ResponseAcquireBelief(PlayerTypes, BeliefTypes) = 0;
    virtual void ResponseMoveSpy(PlayerTypes, int, int, int) = 0;
    virtual void ResponseStageCoup(PlayerTypes, int) = 0;
    virtual void ResponseFaithPurchase(PlayerTypes, FaithPurchaseTypes, int) = 0;
    virtual void ResponseMinorCivBullyGold(PlayerTypes, PlayerTypes, int) = 0;
    virtual void ResponseMinorCivBullyUnit(PlayerTypes, PlayerTypes, UnitTypes) = 0;
    virtual void ResponseMinorCivGiftTileImprovement(PlayerTypes, PlayerTypes, int, int) = 0;
    virtual void ResponseMinorCivBuyout(PlayerTypes, PlayerTypes) = 0;
    virtual void ResponsePledgeMinorProtection(PlayerTypes, PlayerTypes, bool, bool) = 0;
    virtual void ResponseIgnoreWarning(PlayerTypes, TeamTypes) = 0;
    virtual void ResponseLeagueVoteEnact(LeagueTypes, int, PlayerTypes, int, int) = 0;
    virtual void ResponseLeagueVoteRepeal(LeagueTypes, int, PlayerTypes, int, int) = 0;
    virtual void ResponseLeagueVoteAbstain(LeagueTypes, PlayerTypes, int) = 0;
    virtual void ResponseLeagueProposeEnact(LeagueTypes, ResolutionTypes, PlayerTypes, int) = 0;
    virtual void ResponseLeagueProposeRepeal(LeagueTypes, int, PlayerTypes) = 0;
    virtual void ResponseLeagueEditName(LeagueTypes, PlayerTypes, const char *) = 0;
    virtual void ResponseGoodyChoice(PlayerTypes, int, int, GoodyTypes, int) = 0;
    virtual void ResponseLoadout(PlayerTypes, ColonistTypes, SpacecraftTypes, CargoTypes) = 0;
    virtual void ResponsePlanetfall(PlayerTypes, int, int, bool) = 0;
    virtual void ResponseMeteor(int, int, ResourceTypes) = 0;
    virtual void ResponseLandmarkAction(PlayerTypes, LandmarkActionTypes, int) = 0;
    virtual void ResponseQuestStart(PlayerTypes, QuestTypes) = 0;
    virtual void ResponseQuestAction(PlayerTypes, int, int, int) = 0;
    virtual void ResponseCovertOpsMoveAgent(PlayerTypes, int, int, int) = 0;
    virtual void ResponseCovertOpsReturnToHeadquarters(PlayerTypes, int) = 0;
    virtual void ResponseCovertOpsDoOperation(PlayerTypes, int, CovertOperationTypes) = 0;
    virtual void ResponseCovertOpsAbortOperation(PlayerTypes, int) = 0;
    virtual void ResponseStartNationalSecurityProject(PlayerTypes, NationalSecurityProjectTypes) = 0;
    virtual void ResponseEstablishBlackMarket(PlayerTypes, int, ResourceTypes, bool) = 0;
    virtual void ResponseChooseFreeAffinityLevel(PlayerTypes, AffinityType) = 0;
    virtual void ResponseChooseUnitUpgrade(PlayerTypes, UnitUpgradeMode, UnitTypes, UnitUpgradeTypes, UnitPerkTypes) = 0;
    virtual void ResponseProcessArtifacts(PlayerTypes, char, const std::__1::vector<int, std::__1::allocator<int> > &) = 0;
    virtual void ResponseToggleTradeConnectionAutoRenew(int, bool) = 0;
    virtual void ResponseStrategicSiteCommand(StrategicSiteCommandTypes, int, int) = 0;
    virtual void ResponseCreateAgreement(PlayerTypes, PlayerTypes, ForeignPolicyTypes) = 0;
    virtual void ResponseCancelAgreement(int, PlayerTypes) = 0;
    virtual void ResponseAddPersonalityTrait(PlayerTypes, PersonalityTraitTypes) = 0;
    virtual void ResponseRemovePersonalityTrait(PlayerTypes, PersonalityTraitTypes) = 0;
    virtual void ResponseLevelUpPersonalityTrait(PlayerTypes, PersonalityTraitTypes) = 0;
    virtual void ResponseCreateTransaction(PlayerTypes, PlayerTypes, ForeignPolicyTypes, RelationshipLevels, ReactionTypes, bool) = 0;
    virtual void ResponseResolveTransaction(int, bool) = 0;
    virtual void ResponseCreatePeaceProposal(PlayerTypes, PlayerTypes, std::__1::vector<IDInfo, std::__1::allocator<IDInfo> >, std::__1::vector<TechTypes, std::__1::allocator<TechTypes> >, int, int) = 0;
};

class ICvGameVictories1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0xa57e09e0, 0x2568, 0x484e, {0x84, 0x35, 0xa9, 0x37, 0xb9, 0xf7, 0x27, 0xa2}}; return id; }
    virtual bool IsVictoryProjectInProgress(PlayerTypes, ProjectTypes) const = 0;
    virtual bool IsVictoryProjectComplete(PlayerTypes, ProjectTypes) const = 0;
    virtual int GetVictoryProjectCompleteTurnsLeft(PlayerTypes, ProjectTypes) const = 0;
    virtual int GetVictoryTurnsLeft(PlayerTypes, ProjectTypes) const = 0;
    virtual ProjectTypes GetTranscendenceVictoryProject() const = 0;
    virtual ProjectTypes GetContactVictoryProject() const = 0;
    virtual ProjectTypes GetEmancipationVictoryProject() const = 0;
    virtual ProjectTypes GetPromisedLandVictoryProject() const = 0;
};

class ICvPlanetInfo1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0xf79cf00a, 0x43bb, 0x413d, {0x92, 0xd0, 0x24, 0xaf, 0xce, 0xda, 0x4b, 0x07}}; return id; }
    virtual const char * GetType() = 0;
    virtual const char * GetDescription() = 0;
};

class ICvAffinityInfo1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0xce7c3ed2, 0xbed5, 0x40b3, {0xa9, 0x40, 0x0a, 0xe3, 0x69, 0xb8, 0xa1, 0x24}}; return id; }
    virtual const char * GetType() = 0;
    virtual const char * GetDescription() = 0;
};

class ICvAffinityLevelInfo1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0xae8f5b13, 0x032e, 0x47d5, {0x97, 0x24, 0xb8, 0xc4, 0xa5, 0x63, 0x8e, 0xdf}}; return id; }
    virtual const char * GetHarmonyFlavorAudio() = 0;
    virtual const char * GetPurityFlavorAudio() = 0;
    virtual const char * GetSupremacyFlavorAudio() = 0;
};

class ICvCovertOperationInfo1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0xc125fdd2, 0x2c16, 0x4547, {0xb4, 0xdb, 0x07, 0xe2, 0x29, 0x9f, 0x46, 0x2c}}; return id; }
    virtual const char * GetDescription() const = 0;
    virtual int GetBaseTurns() const = 0;
    virtual int GetBaseDifficulty() const = 0;
    virtual int GetBaseIntrigue() const = 0;
    virtual int GetBaseRequiredIntrigueLevel() const = 0;
    virtual int IsQuestOp() const = 0;
    virtual int GetBaseRequiredAffinityLevel(AffinityType) = 0;
};

class ICvUnitUpgradeInfo1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0xba242c5f, 0x238e, 0x4786, {0xbb, 0xa9, 0x4e, 0x07, 0xac, 0x23, 0x5b, 0x61}}; return id; }
    virtual const char * GetType() const = 0;
    virtual const char * GetDescription() const = 0;
    virtual const char * GetDescriptionKey() const = 0;
    virtual int GetAffinityRequired(AffinityType) const = 0;
};

class ICvStationInfo1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0x34980319, 0xc5f4, 0x42cf, {0xb0, 0xfb, 0x38, 0x38, 0x8c, 0xa8, 0x84, 0x1e}}; return id; }
    virtual const char * GetType() const = 0;
    virtual const char * GetDescription() const = 0;
    virtual const char * GetArtDefineTag() const = 0;
};

class ICvHeroLandmarkInfo1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0x1efede47, 0xc828, 0x41ad, {0xa9, 0x30, 0x79, 0xf3, 0x54, 0x20, 0xa8, 0xc8}}; return id; }
    virtual const char * GetType() = 0;
    virtual const char * GetDescription() = 0;
    virtual const char * GetArtDefineTag() = 0;
    virtual bool GetTerrainMakesValid(int) = 0;
};

class ICvOrbitalUnitInfo1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0x62988b57, 0x30e2, 0x4c0f, {0x91, 0xcc, 0x78, 0x42, 0x20, 0xa5, 0x9f, 0xad}}; return id; }
    virtual const char * GetType() const = 0;
    virtual const char * GetText() const = 0;
    virtual const char * GetTextKey() const = 0;
    virtual const char * GetInOrbitUnitArtInfoTag() const = 0;
};

class ICvDLLDatabaseUtility1 : public ICvUnknown {
  public:
    static GUID GetInterfaceId() { const GUID id = {0xbe0459a8, 0xaf97, 0x45de, {0x90, 0xc2, 0x42, 0xc2, 0x99, 0xd4, 0xcc, 0xc5}}; return id; }
    virtual bool CacheGameDatabaseData() = 0;
    virtual bool FlushGameDatabaseData() = 0;
    virtual bool PerformDatabasePostProcessing() = 0;
};

class ICvGameContext1 : public ICvUnknown {
public:
    static GUID GetInterfaceId() { const GUID id = {0xf24caaac,0xf9ac,0x439a,{0xbe,0x7f,0xbd,0xb7,0xad,0x61,0xf7,0x6a}}; return id; }
    virtual GUID GetDLLGUID() = 0;
    virtual const char * GetDLLVersion() = 0;
    virtual ICvNetworkSyncronization1 * GetNetworkSyncronizer() = 0;
    virtual ICvNetMessageHandler1 * GetNetMessageHandler() = 0;
    virtual ICvWorldBuilderMapLoader1 * GetWorldBuilderMapLoader() = 0;
    virtual ICvPreGame1 * GetPreGame() = 0;
    virtual ICvGame1 * GetGame() = 0;
    virtual ICvGameAsynch1 * GetGameAsynch() = 0;
    virtual ICvMap1 * GetMap() = 0;
    virtual ICvTeam1 * GetTeam(TeamTypes) = 0;
    virtual ICvGameVictories1 * GetGameVictories() = 0;
    virtual int GetInfoTypeForString(const char *, bool) const = 0;
    virtual int GetInfoTypeForHash(unsigned int, bool) const = 0;
    virtual CivilizationTypes GetCivilizationInfoIndex(const char *) = 0;
    virtual int GetNumPlayableCivilizationInfos() = 0;
    virtual int GetNumAIPlayableCivilizationInfos() = 0;
    virtual int GetNumPlayableMinorCivs() = 0;
    virtual int GetNumBuildInfos() = 0;
    virtual int GetNumBuildingInfos() = 0;
    virtual int GetNumCargoInfos() = 0;
    virtual int GetNumCivilizationInfos() = 0;
    virtual int GetNumClimateInfos() = 0;
    virtual int GetNumColonistInfos() = 0;
    virtual int GetNumColorInfos() = 0;
    virtual int GetNumEraInfos() = 0;
    virtual int GetNumFeatureInfos() = 0;
    virtual int GetNumGameOptionInfos() = 0;
    virtual int GetNumGameSpeedInfos() = 0;
    virtual int GetNumHandicapInfos() = 0;
    virtual int GetNumImprovementInfos() = 0;
    virtual int GetNumLeaderHeadInfos() = 0;
    virtual int GetNumMinorCivInfos() = 0;
    virtual int GetNumPlanetInfos() = 0;
    virtual int GetNumPlayerColorInfos() = 0;
    virtual int GetNumPolicyInfos() = 0;
    virtual int GetNumPromotionInfos() = 0;
    virtual int GetNumResourceInfos() = 0;
    virtual int GetNumSeaLevelInfos() = 0;
    virtual int GetNumSpacecraftInfos() = 0;
    virtual int GetNumStationInfos() = 0;
    virtual int GetNumTechInfos() = 0;
    virtual int GetNumTerrainInfos() = 0;
    virtual int GetNumUnitCombatClassInfos() = 0;
    virtual int GetNumUnitInfos() = 0;
    virtual int GetNumVictoryInfos() = 0;
    virtual int GetNumWorldInfos() = 0;
    virtual int GetNumAffinityInfos() = 0;
    virtual int GetNumCovertOperationInfos() = 0;
    virtual int GetNumUnitUpgradeInfos() = 0;
    virtual int GetNumHeroLandmarkInfos() = 0;
    virtual ICvBuildInfo1 * GetBuildInfo(BuildTypes) = 0;
    virtual ICvBuildingInfo1 * GetBuildingInfo(BuildingTypes) = 0;
    virtual ICvCivilizationInfo1 * GetCivilizationInfo(CivilizationTypes) = 0;
    virtual ICvColorInfo1 * GetColorInfo(ColorTypes) = 0;
    virtual ICvEraInfo1 * GetEraInfo(EraTypes) = 0;
    virtual ICvFeatureInfo1 * GetFeatureInfo(FeatureTypes) = 0;
    virtual ICvGameOptionInfo1 * GetGameOptionInfo(GameOptionTypes) = 0;
    virtual ICvGameSpeedInfo1 * GetGameSpeedInfo(GameSpeedTypes) = 0;
    virtual ICvHandicapInfo1 * GetHandicapInfo(HandicapTypes) = 0;
    virtual ICvInterfaceModeInfo1 * GetInterfaceModeInfo(InterfaceModeTypes) = 0;
    virtual ICvImprovementInfo1 * GetImprovementInfo(ImprovementTypes) = 0;
    virtual ICvLeaderHeadInfo1 * GetLeaderHeadInfo(LeaderHeadTypes) = 0;
    virtual ICvMinorCivInfo1 * GetMinorCivInfo(MinorCivTypes) = 0;
    virtual ICvMissionInfo1 * GetMissionInfo(MissionTypes) = 0;
    virtual ICvPlayerColorInfo1 * GetPlayerColorInfo(PlayerColorTypes) = 0;
    virtual ICvPlayerOptionInfo1 * GetPlayerOptionInfo(PlayerOptionTypes) = 0;
    virtual ICvPolicyInfo1 * GetPolicyInfo(PolicyTypes) = 0;
    virtual ICvPromotionInfo1 * GetPromotionInfo(PromotionTypes) = 0;
    virtual ICvResourceInfo1 * GetResourceInfo(ResourceTypes) = 0;
    virtual ICvTechInfo1 * GetTechInfo(TechTypes) = 0;
    virtual ICvTerrainInfo1 * GetTerrainInfo(TerrainTypes) = 0;
    virtual ICvUnitInfo1 * GetUnitInfo(UnitTypes) = 0;
    virtual ICvOrbitalUnitInfo1 * GetOrbitalUnitInfo(OrbitalUnitTypes) = 0;
    virtual ICvUnitCombatClassInfo1 * GetUnitCombatClassInfo(UnitCombatTypes) = 0;
    virtual ICvVictoryInfo1 * GetVictoryInfo(VictoryTypes) = 0;
    virtual ICvPlanetInfo1 * GetPlanetInfo(PlanetTypes) = 0;
    virtual ICvAffinityInfo1 * GetAffinityInfo(AffinityType) = 0;
    virtual ICvAffinityLevelInfo1 * GetAffinityLevelInfo(int) = 0;
    virtual ICvCovertOperationInfo1 * GetCovertOperationInfo(CovertOperationTypes) = 0;
    virtual ICvUnitUpgradeInfo1 * GetUnitUpgradeInfo(UnitUpgradeTypes) = 0;
    virtual ICvStationInfo1 * GetStationInfo(StationTypes) = 0;
    virtual ICvHeroLandmarkInfo1 * GetHeroLandmarkInfo(HeroLandmarkTypes) = 0;
    virtual bool GetDefineSTRING(char *, size_t, const char *, bool) = 0;
    virtual int GetMOVE_DENOMINATOR() const = 0;
    virtual int GetMAX_CITY_HIT_POINTS() const = 0;
    virtual float GetCITY_ZOOM_OFFSET() const = 0;
    virtual float GetCITY_ZOOM_LEVEL_1() const = 0;
    virtual float GetCITY_ZOOM_LEVEL_2() const = 0;
    virtual float GetCITY_ZOOM_LEVEL_3() const = 0;
    virtual float GetORBITAL_ZOOM_DELTA() const = 0;
    virtual int GetRUINS_IMPROVEMENT() const = 0;
    virtual int GetWATER_RUINS_IMPROVEMENT() const = 0;
    virtual int GetSHALLOW_WATER_TERRAIN() const = 0;
    virtual int GetDEFICIT_UNIT_DISBANDING_THRESHOLD() const = 0;
    virtual int GetLAST_UNIT_ART_ERA() const = 0;
    virtual int GetLAST_EMBARK_ART_ERA() const = 0;
    virtual int GetHEAVY_RESOURCE_THRESHOLD() const = 0;
    virtual int GetSTANDARD_HANDICAP() const = 0;
    virtual int GetSTANDARD_GAMESPEED() const = 0;
    virtual int GetLAST_BRIDGE_ART_ERA() const = 0;
    virtual int GetALIEN_CIVILIZATION() const = 0;
    virtual int GetMINOR_CIVILIZATION() const = 0;
    virtual int GetALIEN_HANDICAP() const = 0;
    virtual int GetALIEN_LEADER() const = 0;
    virtual int GetMINOR_CIV_HANDICAP() const = 0;
    virtual int GetAI_HANDICAP() const = 0;
    virtual int GetNUM_CITY_PLOTS() const = 0;
    virtual FeatureTypes GetFEATURE_FLOOD_PLAINS_ID() const = 0;
    virtual FeatureTypes GetFEATURE_FOREST_ID() const = 0;
    virtual FeatureTypes GetFEATURE_ICE_ID() const = 0;
    virtual FeatureTypes GetFEATURE_MARSH_ID() const = 0;
    virtual FeatureTypes GetFEATURE_MIASMA_ID() const = 0;
    virtual FeatureTypes GetFEATURE_REEF_ID() const = 0;
    virtual FeatureTypes GetFEATURE_BUBBLES_ID() const = 0;
    virtual FeatureTypes GetFEATURE_TRENCH_BUBBLES_ID() const = 0;
    virtual const char * GetAMPHIBIOUS_UNIT_LAND_EXTENSION() const = 0;
    virtual const char * GetAMPHIBIOUS_UNIT_WATER_EXTENSION() const = 0;
    virtual const char ** GetHexDebugLayerNames() = 0;
    virtual float GetHexDebugLayerScale(const char *) = 0;
    virtual bool GetHexDebugLayerString(ICvPlot1 *, const char *, PlayerTypes, char *, unsigned int) = 0;
    virtual void Init() = 0;
    virtual void Uninit() = 0;
    virtual ICvScriptSystemUtility1 * GetScriptSystemUtility() = 0;
    virtual const char * GetNotificationType(int) const = 0;
    virtual bool GetLogging() = 0;
    virtual void SetLogging(bool) = 0;
    virtual int GetRandLogging() = 0;
    virtual void SetRandLogging(int) = 0;
    virtual bool GetAILogging() = 0;
    virtual void SetAILogging(bool) = 0;
    virtual bool GetAIPerfLogging() = 0;
    virtual void SetAIPerfLogging(bool) = 0;
    virtual bool GetBuilderAILogging() = 0;
    virtual void SetBuilderAILogging(bool) = 0;
    virtual bool GetBuilderAIYieldLogging() = 0;
    virtual void SetBuilderAIYieldLogging(bool) = 0;
    virtual bool GetPlayerAndCityAILogSplit() = 0;
    virtual void SetPlayerAndCityAILogSplit(bool) = 0;
    virtual bool GetTutorialLogging() = 0;
    virtual void SetTutorialLogging(bool) = 0;
    virtual bool GetTutorialDebugging() = 0;
    virtual void SetTutorialDebugging(bool) = 0;
    virtual bool GetAllowRClickMovementWhileScrolling() = 0;
    virtual void SetAllowRClickMovementWhileScrolling(bool) = 0;
    virtual bool GetPostTurnAutosaves() = 0;
    virtual void SetPostTurnAutosaves(bool) = 0;
    virtual ICvDLLDatabaseUtility1 * GetDatabaseLoadUtility() = 0;
    virtual int * GetPlotDirectionX() = 0;
    virtual int * GetPlotDirectionY() = 0;
    virtual int * GetCityPlotX() = 0;
    virtual int * GetCityPlotY() = 0;
    virtual void SetGameDatabase(Database::Connection *) = 0;
    virtual bool SetDLLIFace(ICvEngineUtility1 *) = 0;
    virtual bool IsGraphicsInitialized() const = 0;
    virtual void SetGraphicsInitialized(bool) = 0;
    virtual void SetOutOfSyncDebuggingEnabled(bool) = 0;
    virtual bool RandomNumberGeneratorSyncCheck(PlayerTypes, ICvRandom1 *, bool) = 0;
    virtual unsigned int CreateRandomNumberGenerator() = 0;
    virtual ICvRandom1 * GetRandomNumberGenerator(unsigned int) = 0;
    virtual void DestroyRandomNumberGenerator(unsigned int) = 0;
    virtual unsigned int CreateNetInitInfo() = 0;
    virtual ICvNetInitInfo1 * GetNetInitInfo(unsigned int) = 0;
    virtual void DestroyNetInitInfo(unsigned int) = 0;
    virtual unsigned int CreateNetLoadGameInfo() = 0;
    virtual ICvNetLoadGameInfo1 * GetNetLoadGameInfo(unsigned int) = 0;
    virtual void DestroyNetLoadGameInfo(unsigned int) = 0;
    virtual void TEMPOnHexUnitChanged(ICvUnit1 *) = 0;
    virtual void TEMPOnHexUnitChangedAttack(ICvUnit1 *) = 0;
    virtual ICvEnumerator * TEMPCalculatePathFinderUpdates(ICvUnit1 *, int, int) = 0;
    virtual void ResetPathFinder() = 0;
    virtual void SetEngineUserInterface(ICvUserInterface1 *) = 0;
    virtual void* Debug_GetHeap() const = 0;
};

extern "C" void* HeapCreate(unsigned int, size_t, size_t);
extern "C" int HeapSetInformation(void*, int, void*, size_t);
extern "C" int HeapDestroy(void*);
extern "C" void* HeapAlloc(void*, unsigned int, size_t);
extern "C" int HeapFree(void*, unsigned int, void*);
