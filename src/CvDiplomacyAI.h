#pragma once

#include <string>
#include <vector>
#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvDiplomacyAIEnums.h"
#include "CvLocalization.h"

// TODO: Restore the remaining diplomacy enum definitions.
enum DiploMessageTypes : int;
enum PublicDeclarationTypes : int;
enum WarGoalTypes : int;

class FDataStream;
class CvPlayer;
class CvString;
class FILogFile;
class CvDiplomacyAI;
class GCEventContainer;
struct BuildFinishedData;
struct StationRemovedData;
struct UnitAttackedData;
struct UnitKilledData;
struct AlienNestClearedData;

namespace Events
{
template<int value> struct Int2Type {};
struct LinearEventDispatcher {};
struct NullEventClass {};
struct EmptySubscriptionValidator {};
struct EventStream {};
struct DispatchData {};
template<class T> struct EventQueue {};
template<class TQueue, class TDispatchData> struct EventDispatcher {};
template<class TQueue, class TDispatcher, unsigned int capacity> struct EventSystem {};

template<class TAccessor, class TValidator> struct BaseEvent
{
	template<class TEvent>
	static void Subscribe(unsigned int eventId, const typename TEvent::SUBSCRIPTION& subscription,
		EventSystem<EventQueue<EventStream>, EventDispatcher<EventQueue<EventStream>, DispatchData>, 512>& eventSystem);
	template<class TEvent>
	static void UnSubscribe(unsigned int eventId, const typename TEvent::SUBSCRIPTION& subscription,
		EventSystem<EventQueue<EventStream>, EventDispatcher<EventQueue<EventStream>, DispatchData>, 512>& eventSystem);
};

template<class TId, class TData, class TDispatcher, class TContainer, class TBefore, class TBase, class TAfter>
struct EventTemplate
{
	struct SUBSCRIPTION
	{
		CvDiplomacyAI* object;
		void (CvDiplomacyAI::*callback)(EventTemplate&);
	};
};
}

class GCEventSystemAccessor
{
public:
	static Events::EventSystem<Events::EventQueue<Events::EventStream>,
		Events::EventDispatcher<Events::EventQueue<Events::EventStream>, Events::DispatchData>, 512> g_GCEventSystem;
};

namespace CvDiplomacyAIEvents
{
typedef Events::EventTemplate<Events::Int2Type<13>, BuildFinishedData, Events::LinearEventDispatcher,
	GCEventContainer, Events::NullEventClass,
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> BuildFinished;
typedef Events::EventTemplate<Events::Int2Type<4>, StationRemovedData, Events::LinearEventDispatcher,
	GCEventContainer, Events::NullEventClass,
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> StationRemoved;
typedef Events::EventTemplate<Events::Int2Type<19>, UnitAttackedData, Events::LinearEventDispatcher,
	GCEventContainer, Events::NullEventClass,
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> UnitAttacked;
typedef Events::EventTemplate<Events::Int2Type<20>, UnitKilledData, Events::LinearEventDispatcher,
	GCEventContainer, Events::NullEventClass,
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> UnitKilled;
typedef Events::EventTemplate<Events::Int2Type<33>, AlienNestClearedData, Events::LinearEventDispatcher,
	GCEventContainer, Events::NullEventClass,
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>, Events::NullEventClass> AlienNestCleared;
}

struct DiploLogData
{
	DiploStatementTypes m_eDiploLogStatement;
	int m_iTurn;
};


struct DeclarationLogData
{
	PublicDeclarationTypes m_eDeclaration;
	int m_iData1;
	int m_iData2;
	PlayerTypes m_eMustHaveMetPlayer;
	bool m_bActive;
	int m_iTurn;
};

FDataStream& operator<<(FDataStream&, const DiploLogData&);
FDataStream& operator>>(FDataStream&, DiploLogData&);
FDataStream& operator<<(FDataStream&, const DeclarationLogData&);
FDataStream& operator>>(FDataStream&, DeclarationLogData&);

#define MAX_DIPLO_LOG_STATEMENTS 60

class CvDiplomacyAI
{
public:
	CvDiplomacyAI();
	~CvDiplomacyAI();
	void DoBeginDiploWithHuman();
	int GetTotalLandDisputeLevel();
	int GetPersonalityMajorCivApproachBias(MajorCivApproachTypes eApproach) const;
	std::string GetDiploStringForMessage(DiploMessageTypes message, PlayerTypes player, const Localization::String& optionalKey);
	void TestUIDiploStatement(PlayerTypes player, DiploStatementTypes statement, int data);
	bool IsDemandReady();
	void SetDemandReady(bool bValue);
	void SetWarGoal(PlayerTypes ePlayer, WarGoalTypes eWarGoal);
	void LogPeaceMade(PlayerTypes ePlayer);
	void LogDenounce(PlayerTypes ePlayer, bool bBackstab, bool bRefusal);
	void LogFriendRequestDenounce(PlayerTypes ePlayer, PlayerTypes eAgainstPlayer, bool bAgreed);
	void LogCoopWar(PlayerTypes ePlayer, PlayerTypes eAgainstPlayer, CoopWarStates eAcceptedState);
	void LogWantRA(PlayerTypes ePlayer);
	void LogOpinionUpdate(PlayerTypes ePlayer, std::vector<int>& viOpinionValues);
	void LogMajorCivApproachUpdate(PlayerTypes ePlayer, const int* aiApproachValues, MajorCivApproachTypes eNewMajorCivApproach, MajorCivApproachTypes eOldApproach, WarFaceTypes eNewWarFace);
	void LogMinorCivApproachUpdate(PlayerTypes ePlayer, const int* aiApproachValues, MinorCivApproachTypes eNewMinorCivApproach, MinorCivApproachTypes eOldApproach);
	void LogPersonality();
	void LogStatus();
	int GetAffinityDiffersScore(PlayerTypes ePlayer) const;
private:
	bool IsPlayerValid(PlayerTypes ePlayer, bool bMyTeamIsValid = false) const;
	bool IsDoFAccepted(PlayerTypes ePlayer) const;
	bool IsDenouncedPlayer(PlayerTypes ePlayer) const;
	CoopWarStates GetGlobalCoopWarAcceptedState(PlayerTypes ePlayer);
	MajorCivOpinionTypes GetMajorCivOpinion(PlayerTypes ePlayer) const;
	int GetPersonalityMinorCivApproachBias(MinorCivApproachTypes eApproach) const;
	int GetVictoryCompetitiveness() const;
	int GetWonderCompetitiveness() const;
	int GetMinorCivCompetitiveness() const;
	int GetBoldness() const;
	int GetDiploBalance() const;
	int GetWarmongerHate() const;
	int GetDenounceWillingness() const;
	int GetDoFWillingness() const;
	int GetLoyalty() const;
	int GetNeediness() const;
	int GetForgiveness() const;
	int GetChattiness() const;
	int GetMeanness() const;
	FILogFile* GetDiploApproachLog();
	void LogGrandStrategy(CvString& strString);
	void LogWarState(CvString& strString, PlayerTypes ePlayer);
	void LogEconomicStrength(CvString& strString, PlayerTypes ePlayer) const;
	void LogMilitaryStrength(CvString& strString, PlayerTypes ePlayer) const;
	void LogExpansionAggressivePosture(CvString& strString, PlayerTypes ePlayer);
	void LogPlotBuyingAggressivePosture(CvString& strString, PlayerTypes ePlayer);
	void LogMinorCivDispute(CvString& strString, PlayerTypes ePlayer);
	void LogMajorCivApproach(CvString& strString, MajorCivApproachTypes eApproach, WarFaceTypes eWarFace);
	void LogMajorCivApproachWeights(CvString& strString, const int* aiApproachValues);
	void LogFearRespect(CvString& strString, PlayerTypes ePlayer) const;
	void LogMinorCivApproach(CvString& strString, MinorCivApproachTypes eApproach);
	void LogMinorCivQuestType(CvString& strString, MinorCivQuestTypes eQuestType);
	void LogOpinion(CvString& strString, PlayerTypes ePlayer);
	void LogWarmongerThreat(CvString& strString, PlayerTypes ePlayer);
	void LogMilitaryThreat(CvString& strString, PlayerTypes ePlayer) const;
	void LogTargetValue(CvString& strString, PlayerTypes ePlayer);
	void LogWarGoal(CvString& strString, PlayerTypes ePlayer);
	void LogMilitaryAggressivePosture(CvString& strString, PlayerTypes ePlayer);
	void LogProximity(CvString& strString, PlayerTypes ePlayer) const;
	void LogLandDispute(CvString& strString, PlayerTypes ePlayer);
	void LogVictoryDispute(CvString& strString, PlayerTypes ePlayer);
	void LogWonderDispute(CvString& strString, PlayerTypes ePlayer);
	struct DiplomacyAIData
	{
		DiplomacyAIData();

		// Arrays
		short m_aDiploLogStatementTurnCountScratchPad[NUM_DIPLO_LOG_STATEMENT_TYPES];
		char m_aiMajorCivOpinion[MAX_MAJOR_CIVS];
		char m_aeMajorCivApproach[MAX_MAJOR_CIVS];
		char m_aeApproachScratchPad[REALLY_MAX_PLAYERS];
		char m_aeMinorCivApproach[REALLY_MAX_PLAYERS-MAX_MAJOR_CIVS];
		char m_aeApproachTowardsUsGuess[MAX_MAJOR_CIVS];
		char m_aeApproachTowardsUsGuessCounter[MAX_MAJOR_CIVS];
		short m_aeWantPeaceCounter[REALLY_MAX_PLAYERS];
		char m_aePeaceTreatyWillingToOffer[MAX_MAJOR_CIVS];
		char m_aePeaceTreatyWillingToAccept[MAX_MAJOR_CIVS];
		short m_aiNumWondersBeatenTo[REALLY_MAX_PLAYERS];
		short m_aiNumFavors[MAX_MAJOR_CIVS];
		bool m_abMusteringForAttack[REALLY_MAX_PLAYERS];
		char m_aeWarFace[REALLY_MAX_PLAYERS];
		char m_aeWarState[REALLY_MAX_PLAYERS];
		char m_aeWarProjection[REALLY_MAX_PLAYERS];
		char m_aeLastWarProjection[REALLY_MAX_PLAYERS];
		char m_aeWarGoal[REALLY_MAX_PLAYERS];
		short m_aiPlayerNumTurnsAtWar[REALLY_MAX_PLAYERS];
		short m_aiNumWarsFought[REALLY_MAX_PLAYERS];
		char m_aePlayerMilitaryStrengthComparedToUs[REALLY_MAX_PLAYERS];
		char m_aePlayerEconomicStrengthComparedToUs[REALLY_MAX_PLAYERS];
		char m_aePlayerTargetValue[REALLY_MAX_PLAYERS];
		char m_aePlayerLandDisputeLevel[REALLY_MAX_PLAYERS];
		char m_aePlayerLastTurnLandDisputeLevel[REALLY_MAX_PLAYERS];
		char m_aePlayerVictoryDisputeLevel[REALLY_MAX_PLAYERS];
		char m_aePlayerWonderDisputeLevel[REALLY_MAX_PLAYERS];
		char m_aeMilitaryAggressivePosture[REALLY_MAX_PLAYERS];
		char m_aeLastTurnMilitaryAggressivePosture[REALLY_MAX_PLAYERS];
		char m_aeExpansionAggressivePosture[REALLY_MAX_PLAYERS];
		char m_aePlotBuyingAggressivePosture[REALLY_MAX_PLAYERS];
		char m_aeMilitaryThreat[REALLY_MAX_PLAYERS];
		char m_aeWarDamageLevel[REALLY_MAX_PLAYERS];
		int m_aiWarValueLost[REALLY_MAX_PLAYERS];
		char m_aeWarmongerThreat[REALLY_MAX_PLAYERS];
		char m_aiPersonalityMajorCivApproachBiases[NUM_MAJOR_CIV_APPROACHES];
		char m_aiPersonalityMinorCivApproachBiases[NUM_MINOR_CIV_APPROACHES];
		char m_aiCondemnWillingness[NUM_MAJOR_CIV_APPROACHES];
		DeclarationLogData m_aDeclarationsLog[MAX_DIPLO_LOG_STATEMENTS];

		// Things a player has told the AI
		bool m_abPlayerNoSettleRequest[MAX_MAJOR_CIVS];
		short m_aiPlayerNoSettleRequestCounter[MAX_MAJOR_CIVS];
		bool m_abPlayerStopSpyingRequest[MAX_MAJOR_CIVS];
		short m_aiPlayerStopSpyingRequestCounter[MAX_MAJOR_CIVS];
		short m_aiDemandCounter[MAX_MAJOR_CIVS];
		short m_aiDemandTooSoonNumTurns[MAX_MAJOR_CIVS];
		bool m_abCoopAgreementAccepted[MAX_MAJOR_CIVS];
		short m_aiCoopAgreementCounter[MAX_MAJOR_CIVS];
		int m_aiDenouncedPlayer[MAX_MAJOR_CIVS];
		bool m_abFriendDenouncedUs[MAX_MAJOR_CIVS];
		bool m_abFriendDeclaredWarOnUs[MAX_MAJOR_CIVS];
		short m_aiDenouncedPlayerCounter[MAX_MAJOR_CIVS];
		short m_aiNumCiviliansReturnedToMe[MAX_MAJOR_CIVS];
		short m_aiStationsDestroyedScore[MAX_MAJOR_CIVS];
		short m_aiResurrectedOnTurn[MAX_MAJOR_CIVS];
		short m_aiNumTimesCultureBombed[MAX_MAJOR_CIVS];
		short m_paiNegativeArchaeologyPoints[MAX_MAJOR_CIVS];
		short m_aiNumTimesNuked[MAX_MAJOR_CIVS];
		short m_aiNumTimesRobbedBy[MAX_MAJOR_CIVS];
		short m_aiBrokenExpansionPromiseValue[MAX_MAJOR_CIVS];
		short m_aiIgnoredExpansionPromiseValue[MAX_MAJOR_CIVS];
		short m_aiBrokenBorderPromiseValue[MAX_MAJOR_CIVS];
		short m_aiIgnoredBorderPromiseValue[MAX_MAJOR_CIVS];
		short m_aiDeclaredWarOnFriendValue[MAX_MAJOR_CIVS];
		short m_aiNumCitiesLiberated[MAX_MAJOR_CIVS];
		short m_aiTradeValue[MAX_MAJOR_CIVS];
		short m_aiCommonFoeValue[MAX_MAJOR_CIVS];
		short m_aiAssistValue[MAX_MAJOR_CIVS];
		short m_aiUnitsGiftedValue[MAX_MAJOR_CIVS];

		// Player's response to AI statements
		bool m_abPlayerMadeMilitaryPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenMilitaryPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredMilitaryPromise[MAX_MAJOR_CIVS];
		short m_aiPlayerMilitaryPromiseCounter[MAX_MAJOR_CIVS];
		short m_aiPlayerMadeExpansionPromiseTurn[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenExpansionPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredExpansionPromise[MAX_MAJOR_CIVS];
		char m_aePlayerExpansionPromiseData[MAX_MAJOR_CIVS];
		short m_aiPlayerMadeBorderPromiseTurn[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenBorderPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredBorderPromise[MAX_MAJOR_CIVS];
		char m_aePlayerBorderPromiseData[MAX_MAJOR_CIVS];
		bool m_abPlayerMadeRemoveMiasmaPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenRemoveMiasmaPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredRemoveMiasmaPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerAskedNotToRemoveMiasma[MAX_MAJOR_CIVS];
		bool m_abPlayerAgreedNotToRemoveMiasma[MAX_MAJOR_CIVS];
		bool m_abPlayerMadeSpreadMiasmaPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenSpreadMiasmaPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredSpreadMiasmaPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerAskedNotToSpreadMiasma[MAX_MAJOR_CIVS];
		bool m_abPlayerAgreedNotToSpreadMiasma[MAX_MAJOR_CIVS];
		bool m_abPlayerMadeAntagonizeAliensPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenAntagonizeAliensPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredAntagonizeAliensPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerAskedNotToAntagonizeAliens[MAX_MAJOR_CIVS];
		bool m_abPlayerAgreedNotToAntagonizeAliens[MAX_MAJOR_CIVS];
		bool m_abPlayerMadeSpyPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenSpyPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredSpyPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerForgaveForSpying[MAX_MAJOR_CIVS];
		bool m_abPlayerMadeOrbitalDeploymentPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenOrbitalDeploymentPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredOrbitalDeploymentPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerAskedNotToOrbitalDeployment[MAX_MAJOR_CIVS];
		bool m_abPlayerAgreedNotToOrbitalDeployment[MAX_MAJOR_CIVS];
		bool m_abPlayerMadeStationAggressionPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenStationAggressionPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredStationAggressionPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerAskedNotToStationAggression[MAX_MAJOR_CIVS];
		bool m_abPlayerAgreedNotToStationAggression[MAX_MAJOR_CIVS];
		bool m_abPlayerMadeNoDiggingPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenNoDiggingPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerIgnoredNoDiggingPromise[MAX_MAJOR_CIVS];
		bool m_abPlayerAskedNotToDig[MAX_MAJOR_CIVS];
		bool m_abPlayerAgreedNotToDig[MAX_MAJOR_CIVS];
		bool m_abPlayerBrokenCoopWarPromise[MAX_MAJOR_CIVS];

		// Evaluation of Other Players' Tendencies
		char m_aiOtherPlayerNumMajorsAttacked[MAX_MAJOR_CIVS];
		char m_aiOtherPlayerNumMajorsConquered[MAX_MAJOR_CIVS];
		int m_aiOtherPlayerWarmongerAmount[MAX_MAJOR_CIVS];
		int m_aiOtherPlayerTurnSpreadMiasma[MAX_MAJOR_CIVS];
		int m_aiOtherPlayerTurnRemovedMiasma[MAX_MAJOR_CIVS];
		int m_aiOtherPlayerAntiAliensAmount[MAX_MAJOR_CIVS];
		int m_aiOtherPlayerTurnOrbitalDeployment[MAX_MAJOR_CIVS];

		// 2D Arrays
		char* m_apaeOtherPlayerMajorCivOpinion[REALLY_MAX_PLAYERS];
		char* m_apaeOtherPlayerLandDisputeLevel[REALLY_MAX_PLAYERS];
		char* m_apaeOtherPlayerVictoryDisputeLevel[REALLY_MAX_PLAYERS];
		char* m_apaeOtherPlayerWonderDisputeLevel[REALLY_MAX_PLAYERS];
		char* m_apaeOtherPlayerWarDamageLevel[REALLY_MAX_PLAYERS];
		int* m_apaiOtherPlayerWarValueLost[REALLY_MAX_PLAYERS];
		int* m_apaiOtherPlayerLastRoundWarValueLost[REALLY_MAX_PLAYERS];
		bool* m_apabSentAttackMessageToMinorCivProtector[REALLY_MAX_PLAYERS];
		char* m_apaeOtherPlayerMilitaryThreat[REALLY_MAX_PLAYERS];
		DiploLogData* m_apaDiploStatementsLog[MAX_MAJOR_CIVS];
		bool* m_apabWorkingAgainstPlayerAccepted[MAX_MAJOR_CIVS];
		short* m_apaiWorkingAgainstPlayerCounter[MAX_MAJOR_CIVS];
		char* m_apacCoopWarAcceptedState[MAX_MAJOR_CIVS];
		short* m_apaiCoopWarCounter[MAX_MAJOR_CIVS];
		char m_aaeOtherPlayerMajorCivOpinion[MAX_MAJOR_CIVS * MAX_MAJOR_CIVS];
		char m_aaeOtherPlayerLandDisputeLevel[REALLY_MAX_PLAYERS * REALLY_MAX_PLAYERS];
		char m_aaeOtherPlayerVictoryDisputeLevel[REALLY_MAX_PLAYERS];
		char m_aaeOtherPlayerWarDamageLevel[REALLY_MAX_PLAYERS * REALLY_MAX_PLAYERS];
		int m_aaiOtherPlayerWarValueLost[REALLY_MAX_PLAYERS * REALLY_MAX_PLAYERS];
		int m_aaiOtherPlayerLastRoundWarValueLost[REALLY_MAX_PLAYERS * REALLY_MAX_PLAYERS];
		bool m_aabSentAttackMessageToMinorCivProtector[REALLY_MAX_PLAYERS * REALLY_MAX_PLAYERS];
		char m_aaeOtherPlayerMilitaryThreat[REALLY_MAX_PLAYERS * REALLY_MAX_PLAYERS];
		DiploLogData m_aaDiploStatementsLog[MAX_MAJOR_CIVS* MAX_DIPLO_LOG_STATEMENTS];
		bool m_aabWorkingAgainstPlayerAccepted[MAX_MAJOR_CIVS* MAX_MAJOR_CIVS];
		short m_aaiWorkingAgainstPlayerCounter[MAX_MAJOR_CIVS* MAX_MAJOR_CIVS];
		char m_aacCoopWarAcceptedState[MAX_MAJOR_CIVS* MAX_MAJOR_CIVS];
		short m_aaiCoopWarCounter[MAX_MAJOR_CIVS* MAX_MAJOR_CIVS];
	};

	// Member order follows the Beyond Earth DWARF layout.
	CvPlayer* m_pPlayer;
	Localization::String m_strDiploText;
	DiplomacyAIData* m_pDiploData;
	short* m_paDiploLogStatementTurnCountScratchPad;
	char* m_paeMajorCivOpinion;
	char** m_ppaaeOtherPlayerMajorCivOpinion;
	char* m_paeMajorCivApproach;
	char* m_paeApproachScratchPad;
	char* m_paeMinorCivApproach;
	char* m_paeApproachTowardsUsGuess;
	char* m_paeApproachTowardsUsGuessCounter;
	char m_eDemandTargetPlayer;
	bool m_bDemandReady;
	short* m_paeWantPeaceCounter;
	char* m_paePeaceTreatyWillingToOffer;
	char* m_paePeaceTreatyWillingToAccept;
	short* m_paiNumWondersBeatenTo;
	short* m_paiNumFavors;
	bool* m_pabMusteringForAttack;
	char* m_paeWarFace;
	char* m_paeWarState;
	char* m_paeWarProjection;
	char* m_paeLastWarProjection;
	char* m_paeWarGoal;
	short* m_paiPlayerNumTurnsAtWar;
	short* m_paiNumWarsFought;
	char* m_paePlayerMilitaryStrengthComparedToUs;
	char* m_paePlayerEconomicStrengthComparedToUs;
	char* m_paePlayerTargetValue;
	char* m_paeWarDamageLevel;
	int* m_paiWarValueLost;
	char** m_ppaaeOtherPlayerWarDamageLevel;
	int** m_ppaaiOtherPlayerWarValueLost;
	int** m_ppaaiOtherPlayerLastRoundWarValueLost;
	bool** m_ppaabSentAttackMessageToMinorCivProtector;
	char* m_paeMilitaryAggressivePosture;
	char* m_paeLastTurnMilitaryAggressivePosture;
	char* m_paeExpansionAggressivePosture;
	char* m_paePlotBuyingAggressivePosture;
	char* m_paePlayerLandDisputeLevel;
	char* m_paePlayerLastTurnLandDisputeLevel;
	char* m_paePlayerVictoryDisputeLevel;
	char* m_paePlayerWonderDisputeLevel;
	char** m_ppaaeOtherPlayerLandDisputeLevel;
	char** m_ppaaeOtherPlayerVictoryDisputeLevel;
	char* m_paeMilitaryThreat;
	char** m_ppaaeOtherPlayerMilitaryThreat;
	char* m_paeWarmongerThreat;
	bool* m_pabPlayerNoSettleRequestAccepted;
	short* m_paiPlayerNoSettleRequestCounter;
	bool* m_pabPlayerStopSpyingRequestAccepted;
	short* m_paiPlayerStopSpyingRequestCounter;
	short* m_paiDemandCounter;
	short* m_paiDemandTooSoonNumTurns;
	bool* m_pabCoopAgreementAccepted;
	short* m_paiCoopAgreementCounter;
	int* m_paiDenouncedPlayer;
	bool* m_pabFriendDenouncedUs;
	bool* m_pabFriendDeclaredWarOnUs;
	short* m_paiDenouncedPlayerCounter;
	short* m_paiNumCiviliansReturnedToMe;
	short* m_paiStationsDestroyedScore;
	short* m_paiResurrectedOnTurn;
	short* m_paiNumTimesCultureBombed;
	short* m_paiNegativeArchaeologyPoints;
	short* m_paiNumTimesNuked;
	short* m_paiNumTimesRobbedBy;
	short* m_paiBrokenExpansionPromiseValue;
	short* m_paiIgnoredExpansionPromiseValue;
	short* m_paiBrokenBorderPromiseValue;
	short* m_paiIgnoredBorderPromiseValue;
	short* m_paiDeclaredWarOnFriendValue;
	short* m_paiTradeValue;
	short* m_paiCommonFoeValue;
	short* m_paiAssistValue;
	short* m_paiUnitsGiftedValue;
	short* m_paiNumCitiesLiberated;
	bool** m_ppaabWorkingAgainstPlayerAccepted;
	short** m_ppaaiWorkingAgainstPlayerCounter;
	char** m_ppaacCoopWarAcceptedState;
	short** m_ppaaiCoopWarCounter;
	bool* m_pabPlayerMadeMilitaryPromise;
	bool* m_pabPlayerBrokenMilitaryPromise;
	bool* m_pabPlayerIgnoredMilitaryPromise;
	short* m_paiPlayerMilitaryPromiseCounter;
	short* m_paiPlayerMadeExpansionPromiseTurn;
	bool* m_pabPlayerBrokenExpansionPromise;
	bool* m_pabPlayerIgnoredExpansionPromise;
	char* m_paePlayerExpansionPromiseData;
	short* m_paiPlayerMadeBorderPromiseTurn;
	bool* m_pabPlayerBrokenBorderPromise;
	bool* m_pabPlayerIgnoredBorderPromise;
	char* m_paePlayerBorderPromiseData;
	bool* m_pabPlayerMadeRemoveMiasmaPromise;
	bool* m_pabPlayerBrokenRemoveMiasmaPromise;
	bool* m_pabPlayerIgnoredRemoveMiasmaPromise;
	bool* m_pabPlayerMadeSpreadMiasmaPromise;
	bool* m_pabPlayerBrokenSpreadMiasmaPromise;
	bool* m_pabPlayerIgnoredSpreadMiasmaPromise;
	bool* m_pabPlayerMadeAntagonizeAliensPromise;
	bool* m_pabPlayerBrokenAntagonizeAliensPromise;
	bool* m_pabPlayerIgnoredAntagonizeAliensPromise;
	bool* m_pabPlayerMadeSpyPromise;
	bool* m_pabPlayerBrokenSpyPromise;
	bool* m_pabPlayerIgnoredSpyPromise;
	bool* m_pabPlayerForgaveForSpying;
	bool* m_pabPlayerMadeOrbitalDeploymentPromise;
	bool* m_pabPlayerBrokenOrbitalDeploymentPromise;
	bool* m_pabPlayerIgnoredOrbitalDeploymentPromise;
	bool* m_pabPlayerMadeStationAggressionPromise;
	bool* m_pabPlayerBrokenStationAggressionPromise;
	bool* m_pabPlayerIgnoredStationAggressionPromise;
	bool* m_pabPlayerMadeNoDiggingPromise;
	bool* m_pabPlayerBrokenNoDiggingPromise;
	bool* m_pabPlayerIgnoredNoDiggingPromise;
	bool* m_pabPlayerAskedNotToDig;
	bool* m_pabPlayerAgreedNotToDig;
	bool* m_pabPlayerAskedNotToRemoveMiasma;
	bool* m_pabPlayerAgreedNotToRemoveMiasma;
	bool* m_pabPlayerAskedNotToSpreadMiasma;
	bool* m_pabPlayerAgreedNotToSpreadMiasma;
	bool* m_pabPlayerAskedNotToAntagonizeAliens;
	bool* m_pabPlayerAgreedNotToAntagonizeAliens;
	bool* m_pabPlayerAskedNotToOrbitalDeployment;
	bool* m_pabPlayerAgreedNotToOrbitalDeployment;
	bool* m_pabPlayerAskedNotToStationAggression;
	bool* m_pabPlayerAgreedNotToStationAggression;
	bool* m_pabPlayerBrokenCoopWarPromise;
	int m_iVictoryCompetitiveness;
	int m_iWonderCompetitiveness;
	int m_iBoldness;
	int m_iDiploBalance;
	int m_iWarmongerHate;
	int m_iCoopWillingness;
	int m_iLoyalty;
	int m_iNeediness;
	int m_iForgiveness;
	int m_iChattiness;
	int m_iMeanness;
	int m_iAffinityDevotion;
	int m_iAntiAlien;
	char* m_paiPersonalityMajorCivApproachBiases;
	char* m_paiCondemnWillingness;
	char* m_paiOtherPlayerNumMajorsAttacked;
	char* m_paiOtherPlayerNumMajorsConquered;
	int* m_paiOtherPlayerWarmongerAmount;
	int* m_paiOtherPlayerTurnSpreadMiasma;
	int* m_paiOtherPlayerTurnRemovedMiasma;
	int* m_paiOtherPlayerAntiAliensAmount;
	int* m_paiOtherPlayerTurnOrbitalDeployment;
	DiploLogData** m_ppaDiploStatementsLog;
	DeclarationLogData* m_paDeclarationsLog;
	FromUIDiploEventTypes m_lastDiploEventType;
	PlayerTypes m_lastDiploTargetPlayer;
	int m_eStateAllWars;
	std::vector<PlayerTypes> m_aGreetPlayers;
	PlayerTypes m_eTargetPlayer;
	PlayerTypes m_eTestToPlayer;
	DiploStatementTypes m_eTestStatement;
	int m_iTestStatementArg1;
	AffinityType m_ePurityAffinityType;
	AffinityType m_eHarmonyAffinityType;
	AffinityType m_eSupremacyAffinityType;

	void OnBuildFinished(CvDiplomacyAIEvents::BuildFinished& event);
	void OnStationDestroyed(CvDiplomacyAIEvents::StationRemoved& event);
	void OnAlienUnitAttacked(CvDiplomacyAIEvents::UnitAttacked& event);
	void OnAlienUnitKilled(CvDiplomacyAIEvents::UnitKilled& event);
	void OnAlienNestDestroyed(CvDiplomacyAIEvents::AlienNestCleared& event);
};
