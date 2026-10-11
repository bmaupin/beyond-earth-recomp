#pragma once
#include "CvDllContextInterfaces.h"
class CvGameVictories;
class CvPlanetInfo;
class CvAffinityEntry;
class CvAffinityLevelEntry;
class CvCovertOperationEntry;
class CvUnitUpgradeEntry;
class CvStationEntry;
class CvHeroLandmarkInfo;
class CvOrbitalUnitEntry;

class CvDllNetworkSyncronization : public ICvNetworkSyncronization1 {

  public:
    CvDllNetworkSyncronization();
    ~CvDllNetworkSyncronization();
    virtual void * QueryInterface(GUID);
    static void operator delete(void *);
    static void * operator new(size_t);
    virtual void ClearCityDeltas();
    virtual void ClearPlayerDeltas();
    virtual void ClearPlotDeltas();
    virtual void ClearRandomDeltas();
    virtual void ClearUnitDeltas();
    virtual void SyncCities();
    virtual void SyncPlayers();
    virtual void SyncPlots();
    virtual void SyncUnits();
  private:
    virtual void Destroy();
};

class CvDllNetMessageHandler : public ICvNetMessageHandler1 {

  public:
    CvDllNetMessageHandler();
    ~CvDllNetMessageHandler();
    virtual void * QueryInterface(GUID);
    static void operator delete(void *);
    static void * operator new(size_t);
    virtual void ResponseAdvancedStartAction(PlayerTypes, AdvancedStartActionTypes, int, int, int, bool);
    virtual void ResponseAutoMission(PlayerTypes, int);
    virtual void ResponseBarbarianRansom(PlayerTypes, int, int);
    virtual void ResponseChangeWar(PlayerTypes, TeamTypes, bool);
    virtual void ResponseChangeStationHostile(StationTypes, TeamTypes, bool);
    virtual void ResponseIgnoreWarning(PlayerTypes, TeamTypes);
    virtual void ResponseCityBuyPlot(PlayerTypes, int, int, int);
    virtual void ResponseCityDoTask(PlayerTypes, int, TaskTypes, int, int, bool, bool, bool, bool);
    virtual void ResponseCityPopOrder(PlayerTypes, int, int);
    virtual void ResponseCityPurchase(PlayerTypes, int, UnitTypes, BuildingTypes, ProjectTypes);
    virtual void ResponseCityPurchase(PlayerTypes, int, UnitTypes, BuildingTypes, ProjectTypes, int);
    virtual void ResponseCityPushOrder(PlayerTypes, int, int, OrderTypes, int, bool, bool, bool);
    virtual void ResponseCitySwapOrder(PlayerTypes, int, int);
    virtual void ResponseDestroyUnit(PlayerTypes, int);
    virtual void ResponseDiplomacyFromUI(PlayerTypes, PlayerTypes, FromUIDiploEventTypes, int, int, bool);
    virtual void ResponseDiploVote(PlayerTypes, PlayerTypes);
    virtual void ResponseDoCommand(PlayerTypes, int, CommandTypes, int, int, bool);
    virtual void ResponseExtendedGame(PlayerTypes);
    virtual void ResponseAcquireBelief(PlayerTypes, BeliefTypes);
    virtual void ResponseMoveSpy(PlayerTypes, int, int, int);
    virtual void ResponseStageCoup(PlayerTypes, int);
    virtual void ResponseFaithPurchase(PlayerTypes, FaithPurchaseTypes, int);
    virtual void ResponseLeagueVoteEnact(LeagueTypes, int, PlayerTypes, int, int);
    virtual void ResponseLeagueVoteRepeal(LeagueTypes, int, PlayerTypes, int, int);
    virtual void ResponseLeagueVoteAbstain(LeagueTypes, PlayerTypes, int);
    virtual void ResponseLeagueProposeEnact(LeagueTypes, ResolutionTypes, PlayerTypes, int);
    virtual void ResponseLeagueProposeRepeal(LeagueTypes, int, PlayerTypes);
    virtual void ResponseLeagueEditName(LeagueTypes, PlayerTypes, const char *);
    virtual void ResponseGiftUnit(PlayerTypes, PlayerTypes, int);
    virtual void ResponseGoodyChoice(PlayerTypes, int, int, GoodyTypes, int);
    virtual void ResponseLaunchSpaceship(PlayerTypes, VictoryTypes);
    virtual void ResponseLiberatePlayer(PlayerTypes, PlayerTypes, int);
    virtual void ResponseMinorCivBullyGold(PlayerTypes, PlayerTypes, int);
    virtual void ResponseMinorCivBullyUnit(PlayerTypes, PlayerTypes, UnitTypes);
    virtual void ResponseMinorCivGiftGold(PlayerTypes, PlayerTypes, int);
    virtual void ResponseMinorCivGiftTileImprovement(PlayerTypes, PlayerTypes, int, int);
    virtual void ResponseMinorCivBuyout(PlayerTypes, PlayerTypes);
    virtual void ResponseMinorNoUnitSpawning(PlayerTypes, PlayerTypes, bool);
    virtual void ResponsePlayerDealFinalized(PlayerTypes, PlayerTypes, PlayerTypes, bool);
    virtual void ResponsePlayerOption(PlayerTypes, PlayerOptionTypes, bool);
    virtual void ResponsePledgeMinorProtection(PlayerTypes, PlayerTypes, bool, bool);
    virtual void ResponsePushMission(PlayerTypes, int, MissionTypes, int, int, int, bool);
    virtual void ResponseRenameCity(PlayerTypes, int, const char *);
    virtual void ResponseRenameUnit(PlayerTypes, int, const char *);
    virtual void ResponseResearch(PlayerTypes, TechTypes, int, bool);
    virtual void ResponseResearch(PlayerTypes, TechTypes, int, PlayerTypes, bool);
    virtual void ResponseReturnCivilian(PlayerTypes, PlayerTypes, int, bool);
    virtual void ResponseSellBuilding(PlayerTypes, int, BuildingTypes);
    virtual void ResponseSetCityAIFocus(PlayerTypes, int, CityAIFocusTypes);
    virtual void ResponseSetCityAvoidGrowth(PlayerTypes, int, bool);
    virtual void ResponseSwapUnits(PlayerTypes, int, MissionTypes, int, int, int, bool);
    virtual void ResponseUpdateCityCitizens(PlayerTypes, int);
    virtual void ResponseUpdatePolicies(PlayerTypes, bool, int, bool);
    virtual void ResponseLoadout(PlayerTypes, ColonistTypes, SpacecraftTypes, CargoTypes);
    virtual void ResponsePlanetfall(PlayerTypes, int, int, bool);
    virtual void ResponseMeteor(int, int, ResourceTypes);
    virtual void ResponseLandmarkAction(PlayerTypes, LandmarkActionTypes, int);
    virtual void ResponseQuestStart(PlayerTypes, QuestTypes);
    virtual void ResponseQuestAction(PlayerTypes, int, int, int);
    virtual void ResponseCovertOpsMoveAgent(PlayerTypes, int, int, int);
    virtual void ResponseCovertOpsReturnToHeadquarters(PlayerTypes, int);
    virtual void ResponseCovertOpsDoOperation(PlayerTypes, int, CovertOperationTypes);
    virtual void ResponseCovertOpsAbortOperation(PlayerTypes, int);
    virtual void ResponseStartNationalSecurityProject(PlayerTypes, NationalSecurityProjectTypes);
    virtual void ResponseEstablishBlackMarket(PlayerTypes, int, ResourceTypes, bool);
    virtual void ResponseChooseFreeAffinityLevel(PlayerTypes, AffinityType);
    virtual void ResponseChooseUnitUpgrade(PlayerTypes, UnitUpgradeMode, UnitTypes, UnitUpgradeTypes, UnitPerkTypes);
    virtual void ResponseProcessArtifacts(PlayerTypes, char, const class std::__1::vector<int, std::__1::allocator<int> > &);
    virtual void ResponseToggleTradeConnectionAutoRenew(int, bool);
    virtual void ResponseStrategicSiteCommand(StrategicSiteCommandTypes, int, int);
    virtual void ResponseCreateAgreement(PlayerTypes, PlayerTypes, ForeignPolicyTypes);
    virtual void ResponseCancelAgreement(int, PlayerTypes);
    virtual void ResponseAddPersonalityTrait(PlayerTypes, PersonalityTraitTypes);
    virtual void ResponseRemovePersonalityTrait(PlayerTypes, PersonalityTraitTypes);
    virtual void ResponseLevelUpPersonalityTrait(PlayerTypes, PersonalityTraitTypes);
    virtual void ResponseCreateTransaction(PlayerTypes, PlayerTypes, ForeignPolicyTypes, RelationshipLevels, ReactionTypes, bool);
    virtual void ResponseResolveTransaction(int, bool);
    virtual void ResponseCreatePeaceProposal(PlayerTypes, PlayerTypes, class std::__1::vector<IDInfo, std::__1::allocator<IDInfo> >, class std::__1::vector<TechTypes, std::__1::allocator<TechTypes> >, int, int);
  private:
    virtual void Destroy();
};

class CvDllGameVictories : public ICvGameVictories1 {
    unsigned int m_uiRefCount;
    CvGameVictories *m_pVictoryClasses;

  public:
    CvDllGameVictories(class CvGameVictories *);
    ~CvDllGameVictories();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    CvGameVictories * GetInstance();
    virtual bool IsVictoryProjectInProgress(PlayerTypes, ProjectTypes) const;
    virtual bool IsVictoryProjectComplete(PlayerTypes, ProjectTypes) const;
    virtual int GetVictoryProjectCompleteTurnsLeft(PlayerTypes, ProjectTypes) const;
    virtual int GetVictoryTurnsLeft(PlayerTypes, ProjectTypes) const;
    virtual ProjectTypes GetTranscendenceVictoryProject() const;
    virtual ProjectTypes GetContactVictoryProject() const;
    virtual ProjectTypes GetEmancipationVictoryProject() const;
    virtual ProjectTypes GetPromisedLandVictoryProject() const;
  private:
    virtual void Destroy();
};

class CvDllPlanetInfo : public ICvPlanetInfo1 {
    unsigned int m_uiRefCount;
    CvPlanetInfo *m_pPlanetInfo;

  public:
    CvDllPlanetInfo(class CvPlanetInfo *);
    ~CvDllPlanetInfo();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    CvPlanetInfo * GetInstance();
    virtual const char * GetType();
    virtual const char * GetDescription();
  private:
    virtual void Destroy();
};

class CvDllAffinityInfo : public ICvAffinityInfo1 {
    unsigned int m_uiRefCount;
    CvAffinityEntry *m_pAffinityEntry;

  public:
    CvDllAffinityInfo(class CvAffinityEntry *);
    ~CvDllAffinityInfo();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    CvAffinityEntry * GetInstance();
    virtual const char * GetType();
    virtual const char * GetDescription();
  private:
    virtual void Destroy();
};

class CvDllAffinityLevelInfo : public ICvAffinityLevelInfo1 {
    unsigned int m_uiRefCount;
    CvAffinityLevelEntry *m_pAffinityLevelEntry;

  public:
    CvDllAffinityLevelInfo(class CvAffinityLevelEntry *);
    ~CvDllAffinityLevelInfo();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    CvAffinityLevelEntry * GetInstance();
    virtual const char * GetHarmonyFlavorAudio();
    virtual const char * GetPurityFlavorAudio();
    virtual const char * GetSupremacyFlavorAudio();
  private:
    virtual void Destroy();
};

class CvDllCovertOperationInfo : public ICvCovertOperationInfo1 {
    unsigned int m_refCount;
    CvCovertOperationEntry *m_info;

  public:
    CvDllCovertOperationInfo(class CvCovertOperationEntry *);
    ~CvDllCovertOperationInfo();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    virtual const char * GetDescription() const;
    virtual int GetBaseTurns() const;
    virtual int GetBaseDifficulty() const;
    virtual int GetBaseIntrigue() const;
    virtual int GetBaseRequiredIntrigueLevel() const;
    virtual int IsQuestOp() const;
    virtual int GetBaseRequiredAffinityLevel(AffinityType);
  private:
    virtual void Destroy();
};

class CvDllUnitUpgradeInfo : public ICvUnitUpgradeInfo1 {
    unsigned int m_uiRefCount;
    CvUnitUpgradeEntry *m_pUnitUpgradeInfo;

  public:
    CvDllUnitUpgradeInfo(class CvUnitUpgradeEntry *);
    ~CvDllUnitUpgradeInfo();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    virtual const char * GetType() const;
    virtual const char * GetDescription() const;
    virtual const char * GetDescriptionKey() const;
    virtual int GetAffinityRequired(AffinityType) const;
  private:
    virtual void Destroy();
};

class CvDllStationInfo : public ICvStationInfo1 {
    unsigned int m_uiRefCount;
    CvStationEntry *m_pStationInfo;

  public:
    CvDllStationInfo(class CvStationEntry *);
    ~CvDllStationInfo();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    virtual const char * GetType() const;
    virtual const char * GetDescription() const;
    virtual const char * GetArtDefineTag() const;
  private:
    virtual void Destroy();
};

class CvDllHeroLandmarkInfo : public ICvHeroLandmarkInfo1 {
    unsigned int m_uiRefCount;
    CvHeroLandmarkInfo *m_pHeroLandmarkInfo;

  public:
    CvDllHeroLandmarkInfo(class CvHeroLandmarkInfo *);
    ~CvDllHeroLandmarkInfo();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    CvHeroLandmarkInfo * GetInstance();
    virtual const char * GetType();
    virtual const char * GetDescription();
    virtual const char * GetArtDefineTag();
    virtual bool GetTerrainMakesValid(int);
  private:
    virtual void Destroy();
};

class CvDllOrbitalUnitInfo : public ICvOrbitalUnitInfo1 {
    unsigned int m_uiRefCount;
    CvOrbitalUnitEntry *m_pUnitInfo;

  public:
    CvDllOrbitalUnitInfo(class CvOrbitalUnitEntry *);
    ~CvDllOrbitalUnitInfo();
    virtual void * QueryInterface(GUID);
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount();
    static void operator delete(void *);
    static void * operator new(size_t);
    virtual const char * GetType() const;
    virtual const char * GetText() const;
    virtual const char * GetTextKey() const;
    virtual const char * GetInOrbitUnitArtInfoTag() const;
  private:
    virtual void Destroy();
};

