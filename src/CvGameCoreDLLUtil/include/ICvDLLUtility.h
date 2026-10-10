#pragma once
#ifndef ICvDLLUtility_h
#define ICvDLLUtility_h

#include "CvDllInterfaces.h"

//
// abstract interface for utility functions used by DLL
// Copyright 2010 Firaxis Games
//
class ICvEngineScriptSystem1;
class CvDLLInterfaceIFaceBase;

#include "Fireworks/FDefNew.h"
#include "Fireworks/FMemHooks.h"
#include "Fireworks/FFastList.h"
#include <utility>

namespace Database { class Connection; }
class FMemoryStream;
class ICvCombatInfo1;
class ICvOutpost1;
class ICvStation1;
class ICvWarStatus1;
class ICvStrategicSite1;

typedef FFastVector<int, true, c_eMPoolTypeGame> CvPlotIndexVector;

// Native application vtable order through the SDK fourth interface extension.
class ICvEngineUtility1 : public ICvUnknown
{
public:
	typedef FFastList<char*, c_eMPoolTypeGame, 0> EnumeratedFilesList;
	struct PlotLayout
	{
		struct LayerInfo
		{
			ResourceTypes m_eRevealedResource;
			ImprovementTypes m_eRevealedImprovement;
			int m_iRevealedImprovementState;
			LayerInfo();
		};
		LayerInfo m_Layers[2];
		RouteTypes m_eRevealedRoute;
		int m_iRevealedRouteState;
		PlotLayout();
	};

	virtual CvDLLInterfaceIFaceBase* getInterfaceIFace() = 0;
	virtual ICvEngineScriptSystem1* GetScriptSystem() = 0;
	virtual void reset() = 0;
	virtual void DoMapSetup(int) = 0;
	virtual void DoTurn() = 0;
	virtual bool IsHost() const = 0;
	virtual bool IsPlayerConnected(PlayerTypes) = 0;
	virtual Database::Connection* GetModsDatabase() = 0;
	virtual bool IsModActivated(char const*) = 0;
	virtual bool IsModActivated(char const*, int) = 0;
	virtual bool IsCurrentGamecore(char const*) const = 0;
	virtual int getAssignedNetworkID(int) = 0;
	virtual bool IsPitbossHost() const = 0;
	virtual CvString GetPitbossSmtpHost() const = 0;
	virtual CvString GetPitbossSmtpLogin() const = 0;
	virtual CvString GetPitbossSmtpPassword() const = 0;
	virtual CvString GetPitbossEmail() const = 0;
	virtual void netMessageDebugLog(std::string const&) const = 0;
	virtual void sendPlayerInfo(PlayerTypes) = 0;
	virtual void sendGameInfo(CvString const&, CvString const&) = 0;
	virtual void sendPlayerOption(PlayerOptionTypes, bool) = 0;
	virtual void sendExtendedGame() = 0;
	virtual void SendAcquireBelief(PlayerTypes, BeliefTypes) = 0;
	virtual void SendMoveSpy(PlayerTypes, int, int, int) = 0;
	virtual void SendStageCoup(PlayerTypes, int) = 0;
	virtual void SendFaithPurchase(PlayerTypes, FaithPurchaseTypes, int) = 0;
	virtual void sendAutoMoves() = 0;
	virtual void sendTurnComplete() = 0;
	virtual bool HasSentTurnComplete() = 0;
	virtual bool HasReceivedTurnComplete(PlayerTypes) = 0;
	virtual bool HasSentTurnAllComplete() = 0;
	virtual bool HasReceivedTurnAllComplete(PlayerTypes) = 0;
	virtual bool HasReceivedTurnAllCompleteFromAllPlayers() = 0;
	virtual bool sendTurnUnready() = 0;
	virtual void sendPushMission(int, MissionTypes, int, int, int, bool) = 0;
	virtual void sendAutoMission(int) = 0;
	virtual void sendDoCommand(int, CommandTypes, int, int, bool) = 0;
	virtual void sendPushOrder(int, int, OrderTypes, int, bool, bool, bool) = 0;
	virtual void sendPopOrder(int, int) = 0;
	virtual void sendSwapOrder(int, int) = 0;
	virtual void sendPurchase(int, UnitTypes, BuildingTypes, ProjectTypes) = 0;
	virtual void sendDoTask(int, TaskTypes, int, int, bool, bool, bool, bool) = 0;
	virtual void sendResearch(TechTypes, int, PlayerTypes, bool) = 0;
	virtual void sendChat(CvString const&, ChatTargetTypes, PlayerTypes) = 0;
	virtual void sendPing(int, int) = 0;
	virtual void sendPause(int) = 0;
	virtual void sendChangeWar(TeamTypes, bool) = 0;
	virtual void sendIgnoreWarning(TeamTypes) = 0;
	virtual void SendPledgeMinorProtection(PlayerTypes, bool) = 0;
	virtual void SendMinorNoUnitSpawning(PlayerTypes, bool) = 0;
	virtual void SendLiberateMinor(PlayerTypes, int) = 0;
	virtual void sendUpdatePolicies(bool, int, bool) = 0;
	virtual void SendDiploVote(PlayerTypes) = 0;
	virtual void sendLaunch(PlayerTypes, VictoryTypes) = 0;
	virtual void sendAdvancedStartAction(AdvancedStartActionTypes, PlayerTypes, int, int, int, bool) = 0;
	virtual void sendMinorCivQuestNoInterest(PlayerTypes, bool) = 0;
	virtual void sendMinorCivQuestCompleted(PlayerTypes, bool) = 0;
	virtual void sendMinorCivIntrusion(PlayerTypes, int) = 0;
	virtual void sendMinorCivEnterTerritory(PlayerTypes) = 0;
	virtual void sendBarbarianRansom(int, int) = 0;
	virtual void sendGiftUnit(PlayerTypes, int) = 0;
	virtual void sendReturnCivilian(bool, PlayerTypes, int) = 0;
	virtual void SendUpdateCityCitizens(int) = 0;
	virtual void SendSellBuilding(int, BuildingTypes) = 0;
	virtual void SendRenameCity(int, CvString) = 0;
	virtual void SendRenameUnit(int, CvString) = 0;
	virtual void sendPlayerHurry(HurryTypes) = 0;
	virtual void sendSwapUnits(int, MissionTypes, int, int, int, bool) = 0;
	virtual void sendCityBuyPlot(int, int, int) = 0;
	virtual void sendMinorPledgeProtection(PlayerTypes, PlayerTypes, bool, bool) = 0;
	virtual void sendMinorGiftGold(PlayerTypes, int) = 0;
	virtual void sendMinorGiftTileImprovement(PlayerTypes, PlayerTypes, int, int) = 0;
	virtual void sendMinorBullyGold(PlayerTypes, PlayerTypes, int) = 0;
	virtual void sendMinorBullyUnit(PlayerTypes, PlayerTypes, UnitTypes) = 0;
	virtual void sendSetCityAIFocus(int, CityAIFocusTypes) = 0;
	virtual void sendSetCityAvoidGrowth(int, bool) = 0;
	virtual void sendUnitSyncCheck(PlayerTypes, int, FMemoryStream&, std::vector<std::pair<std::string, std::string> > const&) const = 0;
	virtual void sendPlotSyncCheck(PlayerTypes, short, short, FMemoryStream&, std::vector<std::pair<std::string, std::string> > const&) const = 0;
	virtual void sendCitySyncCheck(PlayerTypes, int, FMemoryStream&, std::vector<std::pair<std::string, std::string> > const&) const = 0;
	virtual void sendRandomNumberGeneratorSyncCheck(PlayerTypes, ICvRandom1*) const = 0;
	virtual void sendPlayerSyncCheck(PlayerTypes, FMemoryStream&, std::vector<std::pair<std::string, std::string> > const&) const = 0;
	virtual void sendFromUIDiploEvent(PlayerTypes, FromUIDiploEventTypes, int, int, bool) = 0;
	virtual void sendNetDealAccepted(PlayerTypes, PlayerTypes, ICvDeal1*, int, int, int) const = 0;
	virtual void sendNetDemandAccepted(PlayerTypes, PlayerTypes, ICvDeal1*) const = 0;
	virtual void sendTurnReminder(PlayerTypes) = 0;
	virtual void sendGoodyChoice(PlayerTypes, int, int, GoodyTypes, int) = 0;
	virtual void SendLoadout(PlayerTypes, ColonistTypes, SpacecraftTypes, CargoTypes) = 0;
	virtual void SendPlanetfall(PlayerTypes, int, int, bool) = 0;
	virtual void OutpostCreated(ICvOutpost1&) = 0;
	virtual void OutpostRemoved(ICvOutpost1&, OutpostRemovalMethod) = 0;
	virtual void StationCreated(ICvStation1*) = 0;
	virtual void StationRemoved(ICvStation1*) = 0;
	virtual void SendLandmarkAction(PlayerTypes, LandmarkActionTypes, int) = 0;
	virtual void SendQuestAction(PlayerTypes, int, int, int) = 0;
	virtual void SetOrbitalView(bool) = 0;
	virtual bool IsInOrbitalView() = 0;
	virtual bool IsTimedEffectPlaying() = 0;
	virtual void UpdateUnitUpgradePreview(UnitTypes, UnitUpgradeTypes, UnitPerkTypes) = 0;
	virtual void SendMoveCovertAgent(PlayerTypes, int, int, int) = 0;
	virtual void SendCovertReturnToHeadquarters(PlayerTypes, int) = 0;
	virtual void SendDoCovertOperation(PlayerTypes, int, CovertOperationTypes) = 0;
	virtual void SendAbortCovertOperation(PlayerTypes, int) = 0;
	virtual void SendStartNationalSecurityProject(PlayerTypes, NationalSecurityProjectTypes) = 0;
	virtual void SendEstablishBlackMarket(PlayerTypes, int, ResourceTypes, bool) = 0;
	virtual void SendChooseFreeAffinityLevel(PlayerTypes, AffinityType) = 0;
	virtual void SendChooseUnitUpgrade(PlayerTypes, UnitUpgradeMode, UnitTypes, UnitUpgradeTypes, UnitPerkTypes) = 0;
	virtual void SendProcessArtifacts(PlayerTypes, char, std::vector<int> const&) = 0;
	virtual void SendToggleTradeConnectionAutoRenew(int, bool) = 0;
	virtual void SendStrategicSiteCommand(StrategicSiteCommandTypes, int, int) = 0;
	virtual void SendCancelAgreement(int, PlayerTypes) = 0;
	virtual void SendAddPersonalityTrait(PlayerTypes, PersonalityTraitTypes) = 0;
	virtual void SendRemovePersonalityTrait(PlayerTypes, PersonalityTraitTypes) = 0;
	virtual void SendLevelUpPersonalityTrait(PlayerTypes, PersonalityTraitTypes) = 0;
	virtual void SendCreateProposeRelationshipTransaction(PlayerTypes, PlayerTypes, RelationshipLevels) = 0;
	virtual void SendCreateProposeAgreementTransaction(PlayerTypes, PlayerTypes, ForeignPolicyTypes) = 0;
	virtual void SendCreateConfrontationTransaction(PlayerTypes, PlayerTypes, ReactionTypes) = 0;
	virtual void SendCreatePeaceTransaction(PlayerTypes, PlayerTypes, ICvWarStatus1*) = 0;
	virtual void EnterDiplomacy(PlayerTypes) = 0;
	virtual void GameplayDiplomacyAgreementCreated(int) = 0;
	virtual void GameplayDiplomacyAgreementCanceled(int) = 0;
	virtual void GameplayDiplomacyRelationshipChanged(PlayerTypes, PlayerTypes, RelationshipLevels, RelationshipLevels) = 0;
	virtual void GameplayTransactionCreated(int, bool) = 0;
	virtual void GameplayTransactionResolved(int) = 0;
	virtual void GameplayPersonalityTraitAdded(PlayerTypes, PersonalityTraitTypes) = 0;
	virtual void GameplayPersonalityTraitRemoved(PlayerTypes, PersonalityTraitTypes) = 0;
	virtual void GameplayPersonalityTraitLeveledUp(PlayerTypes, PersonalityTraitTypes, int) = 0;
	virtual void netDisconnect() = 0;
	virtual void sendInitialUnitAIProcessed() const = 0;
	virtual bool allInitialUnitAIProcessed() const = 0;
	virtual bool allInitialTurnProcessingComplete() const = 0;
	virtual void hotJoinComplete() const = 0;
	virtual int getMillisecsPerTurn() = 0;
	virtual float getSecsPerTurn() = 0;
	virtual int getTurnsPerSecond() = 0;
	virtual int getTurnsPerMinute() = 0;
	virtual bool CanAdvanceTurn() = 0;
	virtual bool IsLoadScreenDisplayed() = 0;
	virtual void openSlot(PlayerTypes) = 0;
	virtual void closeSlot(PlayerTypes) = 0;
	virtual CvString getMapScriptName() = 0;
	virtual bool getTransferredMap() = 0;
	virtual bool isWBMapScript() = 0;
	virtual bool isWBMapNoPlayers() = 0;
	virtual CvString getPlayerName(int, unsigned int) = 0;
	virtual CvString getPlayerNameKey(int) = 0;
	virtual CvString getPlayerDisplayNickName(int) = 0;
	virtual CvString getCivDescription(int, unsigned int) = 0;
	virtual CvString getCivDescriptionKey(int) = 0;
	virtual CvString getCivShortDesc(int, unsigned int) = 0;
	virtual CvString getCivShortDescKey(int) = 0;
	virtual CvString getCivAdjective(int, unsigned int) = 0;
	virtual CvString getCivAdjectiveKey(int) = 0;
	virtual void stripSpecialCharacters(CvString&) = 0;
	virtual void InitGlobals() = 0;
	virtual void UninitGlobals() = 0;
	virtual void SetDone(bool) = 0;
	virtual bool GetDone() = 0;
	virtual bool GetAutorun() = 0;
	virtual int GetAudioTagIndex(char const*, int) = 0;
	virtual int GetAudioTagIndex(unsigned int, int) = 0;
	virtual bool altKey() = 0;
	virtual bool shiftKey() = 0;
	virtual bool ctrlKey() = 0;
	virtual void EnumerateFiles(EnumeratedFilesList&, char const*, unsigned int, char const*, unsigned int, bool) = 0;
	virtual void ReleaseEnumeratedFilesList(EnumeratedFilesList&) = 0;
	virtual void SaveGame() = 0;
	virtual void LoadGame() = 0;
	virtual void AutoSave(bool, bool) = 0;
	virtual bool saveReplay() = 0;
	virtual void QuickSave() = 0;
	virtual void QuickLoad() = 0;
	virtual void sendPbemTurn(PlayerTypes) = 0;
	virtual void getPassword(PlayerTypes) = 0;
	virtual void RestartGame() = 0;
	virtual bool getPlayerOption(PlayerOptionTypes) = 0;
	virtual const char* GetCacheFolderPath() = 0;
	virtual void GameplayEraChanged(PlayerTypes, EraTypes) = 0;
	virtual void GameplayBridgeChanged(bool, unsigned char) = 0;
	virtual void GameplayUnitCreated(ICvUnit1*, bool, int) = 0;
	virtual void GameplayUnitMoved(ICvUnit1*, CvPlotIndexVector const&) = 0;
	virtual void GameplayUnitTeleported(ICvUnit1*, ICvPlot1*) = 0;
	virtual void GameplayUnitDestroyed(ICvUnit1*, bool, bool) = 0;
	virtual void GameplayUnitDestroyedInCombat(ICvUnit1*) = 0;
	virtual void GameplayUnitSetDamage(ICvUnit1*, int, int, bool) = 0;
	virtual void GameplayUnitFortify(ICvUnit1*, bool) = 0;
	virtual void GameplayUnitSetupRangedAttack(ICvUnit1*, bool) = 0;
	virtual void GameplayUnitWork(ICvUnit1*, int) = 0;
	virtual void GameplayUnitWork(ICvUnit1*, char const*) = 0;
	virtual void GameplayUnitParadrop(ICvUnit1*, ICvPlot1*) = 0;
	virtual void GameplayUnitActivate(ICvUnit1*) = 0;
	virtual void GameplayUnitEmbark(ICvUnit1*, bool) = 0;
	virtual void GameplayUnitGarrison(ICvUnit1*, bool) = 0;
	virtual void GameplayUnitShouldDimFlag(ICvUnit1*, bool) = 0;
	virtual void GameplayUnitMarkThreatening(ICvUnit1*, bool) = 0;
	virtual void GameplayUnitVisibility(ICvUnit1*, bool, bool, float) = 0;
	virtual unsigned int GameplayUnitCombat(ICvCombatInfo1*) = 0;
	virtual void GameplayCityCreated(ICvCity1*, EraTypes) = 0;
	virtual void GameplayCityPopulationChanged(ICvCity1*, int) = 0;
	virtual void GameplayCityMoved(ICvCity1*, ICvPlot1*, ICvPlot1*) = 0;
	virtual void GameplayUnitChangeModel(ICvUnit1*, int, char const*) = 0;
	virtual void GameplayUnitDeployPassiveAbility(ICvUnit1*, UnitPassiveAbilityTypes, bool) = 0;
	virtual void Visuals_StartCityMove(ICvCity1*, ICvPlot1*, ICvPlot1*) = 0;
	virtual void Visuals_EndCityMove(ICvCity1*, ICvPlot1*, ICvPlot1*) = 0;
	virtual unsigned int GameplaySiteCombat(ICvCombatInfo1*) = 0;
	virtual void GameplaySiteDestroyed(ICvStrategicSite1*, PlayerTypes) = 0;
	virtual void GameplaySiteCaptured(ICvStrategicSite1*, PlayerTypes) = 0;
	virtual void GameplaySiteSetDamage(ICvStrategicSite1*, int, int) = 0;
	virtual void GameplayUnitMissionEnd(ICvUnit1*) = 0;
	virtual void GameplayUnitRebased(ICvUnit1*, ICvPlot1*, ICvPlot1*) = 0;
	virtual void GameplayUnitResetAnimationState(ICvUnit1*) = 0;
	virtual void GameplayUnitSetOrbital(ICvUnit1*, bool) = 0;
	virtual int GetGameplayUnitTypeMap(ICvUnit1*) = 0;
	virtual bool GetGameplayUnitName(ICvUnit1*, CvString&, CvString&) = 0;
	virtual void GameplayTechAcquired(TeamTypes, TechTypes) = 0;
	virtual void GameplayMinorMarvelUsed(PlayerTypes, int, MarvelTypes) = 0;
	virtual void GameplayFeatureChanged(ICvPlot1*, FeatureTypes) = 0;
	virtual void GameplayFeatureRemoved(ICvPlot1*, FeatureTypes) = 0;
	virtual void GameplayPlotStateChange(ICvPlot1 const*, PlotLayout const*) = 0;
	virtual void GameplayPlotIconStateChange(ICvPlot1 const*, PlotLayout const*) = 0;
	virtual void GameplayPlotEvent(ICvPlot1 const*, int, int, int) = 0;
	virtual void GameplayWallCreated(ICvPlot1*) = 0;
	virtual void GameplayDoFX(ICvPlot1*, unsigned int) = 0;
	virtual void GameplayFOWChanged(int, int, int, bool) = 0;
	virtual void GameplayYieldMightHaveChanged(ICvPlot1*) = 0;
	virtual void NotifyAILeadersInGame() = 0;
	virtual void NotifySpecificAILeaderInGame(PlayerTypes) = 0;
	virtual void GameplayWarStateChanged(TeamTypes, TeamTypes, bool) = 0;
	virtual void DoClearDiplomacyTradeTable() = 0;
	virtual void GameplayDiplomacyAILeaderMessage(PlayerTypes, DiploUIStateTypes, char const*, LeaderheadAnimationTypes, int) = 0;
	virtual void GameplayMetTeam(TeamTypes, TeamTypes) = 0;
	virtual void NetMessageDebug(std::string const&) const = 0;
	virtual float endTurnTimerLength(float) = 0;
	virtual float endTurnTimerLength() const = 0;
	virtual void GameplayWonderCreated(PlayerTypes, ICvPlot1*, BuildingTypes, int) = 0;
	virtual void GameplayWonderEdited(PlayerTypes, ICvPlot1*, BuildingTypes, int) = 0;
	virtual void GameplayWonderRemoved(PlayerTypes, ICvPlot1*, BuildingTypes) = 0;
	virtual void GameplaySpaceshipCreated(ICvPlot1*, int) = 0;
	virtual void GameplaySpaceshipEdited(ICvPlot1*, int) = 0;
	virtual void GameplaySpaceshipRemoved(ICvPlot1*) = 0;
	virtual void GameplayOpenOptionsScreen() = 0;
	virtual void GameplaySearchForPediaEntry(char const*) = 0;
	virtual void GameplayOpenInfoCorner(int) = 0;
	virtual void ShowRetirePopup() = 0;
	virtual void GameplayWorldAnchor(GenericWorldAnchorTypes, bool, int, int, int) = 0;
	virtual void GameplayMinimapUnitSelect(int, int) = 0;
	virtual void GameplayMinimapNotification(int, int, int) = 0;
	virtual void GameplayEraOfProsperityStarted() = 0;
	virtual void GameplayEraOfProsperityEnded() = 0;
	virtual void GameplayPlayerAffinityChanged(PlayerTypes, std::vector<float>) = 0;
	virtual void GameplayPlayerColorChanged(PlayerTypes) = 0;
	virtual void GameplayTurnChanged(int) = 0;
	virtual void GameplayActivePlayerChanged(PlayerTypes) = 0;
	virtual void GameplayUnlockCamera() = 0;
	virtual void GameplayStartPlanetfallEffect(PlayerTypes, int, int, bool) = 0;
	virtual void GameplayEndPlanetfallEffect(PlayerTypes, int, int, bool) = 0;
	virtual void GameplayStartMeteorEffect(int, int) = 0;
	virtual void GameplayEndMeteorEffect(int, int) = 0;
	virtual void GameplaySupremacyGateEffect(int, int) = 0;
	virtual void GameplayBeaconEffect(int, int) = 0;
	virtual void GameplayStartOrbitalLaunchEffect(ICvUnit1*, int, int, bool) = 0;
	virtual void GameplayEndOrbitalLaunchEffect(ICvUnit1*, int, int, bool) = 0;
	virtual void GameplayWaitForEffect(PlayerTypes, bool, int, int, int) = 0;
	virtual void PublishActivePlayer(PlayerTypes, PlayerTypes) = 0;
	virtual void PublishNewGameTurn(int) = 0;
	virtual void UnlockAchievement(EAchievement) = 0;
	virtual bool IsAchievementUnlocked(EAchievement) const = 0;
	virtual bool GetSteamStat(ESteamStat, int*) const = 0;
	virtual bool SetSteamStat(ESteamStat, int) = 0;
	virtual bool IncrementSteamStat(ESteamStat) = 0;
	virtual bool IncrementSteamStatAndUnlock(ESteamStat, int, EAchievement, int) = 0;
	virtual void SetAdvisorBadAttackInterrupt(bool) = 0;
	virtual bool GetAdvisorBadAttackInterrupt() = 0;
	virtual void SetAdvisorCityAttackInterrupt(bool) = 0;
	virtual bool GetAdvisorCityAttackInterrupt() = 0;
	virtual int  GetTutorialLevel() = 0;
	virtual CvString GetLocalizedFile(char const*) = 0;
	virtual void ReseatPlayer(PlayerTypes, bool) const = 0;
	virtual bool IsNetPlayer(PlayerTypes) const = 0;
	virtual void SendGameDoTurnProcessed() const = 0;
	virtual bool RecordVictoryInformation(int) = 0;
	virtual bool RecordLeaderboardScore(int) = 0;
	virtual bool TunerConnected() = 0;
	virtual bool TunerEverConnected() = 0;
	virtual void PublishEraChanges() = 0;
	virtual void RecordGameCoreMessages(bool) = 0;
	virtual bool IsProcessingGameCoreMessages() = 0;
	virtual void GetGameCoreLock() = 0;
	virtual void ReleaseGameCoreLock() = 0;
	virtual bool TryGameCoreLock() = 0;
	virtual bool HasGameCoreLock() = 0;
	virtual bool IsGameCoreThread() = 0;
	virtual bool IsGameCoreExecuting() = 0;
};

class ICvEngineUtility2 : public ICvEngineUtility1
{
public:
	using ICvEngineUtility1::sendPurchase;
	virtual void sendPurchase(int, UnitTypes, BuildingTypes, ProjectTypes, int) = 0;
	virtual bool ReseatConnectedPlayer(PlayerTypes) const = 0;
};

class ICvEngineUtility3 : public ICvEngineUtility2
{
public:
	virtual void SendLeagueVoteEnact(LeagueTypes, int, PlayerTypes, int, int) = 0;
	virtual void SendLeagueVoteRepeal(LeagueTypes, int, PlayerTypes, int, int) = 0;
	virtual void SendLeagueVoteAbstain(LeagueTypes, PlayerTypes, int) = 0;
	virtual void SendLeagueProposeEnact(LeagueTypes, ResolutionTypes, PlayerTypes, int) = 0;
	virtual void SendLeagueProposeRepeal(LeagueTypes, int, PlayerTypes) = 0;
	virtual void SendLeagueEditName(LeagueTypes, PlayerTypes, char const*) = 0;
	virtual void TradeVisuals_NewRoute(int, int, TradeConnectionType, int, int*, int*) = 0;
	virtual void TradeVisuals_UpdateRouteDirection(int, bool) = 0;
	virtual void TradeVisuals_DestroyRoute(int, int) = 0;
	virtual void TradeVisuals_ActivatePopupRoute(int) = 0;
	virtual void TradeVisuals_DeactivatePopupRoute() = 0;
	virtual void TradeVisuals_ActivateSpecificRoutes(std::vector<int> const&) = 0;
	virtual void TradeVisuals_DeactivateSpecificRoutes() = 0;
	virtual void FlushTurnReminders() = 0;
	virtual void BeginSendBundle() = 0;
	virtual void EndSendBundle() = 0;
	virtual bool IsPlayerKicked(int) = 0;
	virtual bool IsPlayerHotJoining(int) = 0;
	virtual void SendInitialAICivsFinished() const = 0;
	virtual bool HasReceivedInitialAICivsFinished(PlayerTypes) const = 0;
	virtual int	 GetNumAICivsProcessed() const = 0;
	virtual void VerifyPlayerSlot(PlayerTypes) const = 0;
	virtual bool ShouldValidateGameDatabase() const = 0;
};

class ICvEngineUtility4 : public ICvEngineUtility3
{
public:
	virtual bool GetEvaluatedMapScriptPath(char const*, char*, unsigned int) const = 0;
};

#endif // ICvDLLUtility_h
