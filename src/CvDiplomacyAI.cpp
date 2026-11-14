#include "CvGameCoreDLLPCH.h"
#include "CvDiplomacyAI.h"
#include "CvMilitaryAI.h"
#include "CvPlayerAffinities.h"
#include "CvInfos.h"


CvDiplomacyAI::DiplomacyAIData::DiplomacyAIData() :
	m_aDiploLogStatementTurnCountScratchPad()
	, m_aiMajorCivOpinion()
	, m_aeMajorCivApproach()
	, m_aeApproachScratchPad()
	, m_aeMinorCivApproach()
	, m_aeApproachTowardsUsGuess()
	, m_aeApproachTowardsUsGuessCounter()
	, m_aeWantPeaceCounter()
	, m_aePeaceTreatyWillingToOffer()
	, m_aePeaceTreatyWillingToAccept()
	, m_aiNumWondersBeatenTo()
	, m_aiNumFavors()
	, m_abMusteringForAttack()
	, m_aeWarFace()
	, m_aeWarState()
	, m_aeWarProjection()
	, m_aeWarGoal()
	, m_aiPlayerNumTurnsAtWar()
	, m_aiNumWarsFought()
	, m_aePlayerMilitaryStrengthComparedToUs()
	, m_aePlayerEconomicStrengthComparedToUs()
	, m_aePlayerTargetValue()
	, m_aePlayerLandDisputeLevel()
	, m_aePlayerLastTurnLandDisputeLevel()
	, m_aePlayerVictoryDisputeLevel()
	, m_aePlayerWonderDisputeLevel()
	, m_aeMilitaryAggressivePosture()
	, m_aeLastTurnMilitaryAggressivePosture()
	, m_aeExpansionAggressivePosture()
	, m_aePlotBuyingAggressivePosture()
	, m_aeMilitaryThreat()
	, m_aeWarDamageLevel()
	, m_aiWarValueLost()
	, m_aeWarmongerThreat()
	, m_aiPersonalityMajorCivApproachBiases()
	, m_aiPersonalityMinorCivApproachBiases()
	, m_aiCondemnWillingness()
	, m_aDeclarationsLog()
	, m_abPlayerNoSettleRequest()
	, m_aiPlayerNoSettleRequestCounter()
	, m_abPlayerStopSpyingRequest()
	, m_aiPlayerStopSpyingRequestCounter()
	, m_aiDemandCounter()
	, m_aiDemandTooSoonNumTurns()
	, m_abCoopAgreementAccepted()
	, m_aiCoopAgreementCounter()
	, m_aiDenouncedPlayer()
	, m_abFriendDenouncedUs()
	, m_abFriendDeclaredWarOnUs()
	, m_aiDenouncedPlayerCounter()
	, m_aiNumCiviliansReturnedToMe()
	, m_aiStationsDestroyedScore()
	, m_aiResurrectedOnTurn()
	, m_aiNumTimesCultureBombed()
	, m_paiNegativeArchaeologyPoints()
	, m_aiNumTimesNuked()
	, m_aiNumTimesRobbedBy()
	, m_abPlayerMadeMilitaryPromise()
	, m_abPlayerBrokenMilitaryPromise()
	, m_abPlayerIgnoredMilitaryPromise()
	, m_aiPlayerMilitaryPromiseCounter()
	, m_aiPlayerMadeExpansionPromiseTurn()
	, m_abPlayerBrokenExpansionPromise()
	, m_abPlayerIgnoredExpansionPromise()
	, m_aePlayerExpansionPromiseData()
	, m_aiPlayerMadeBorderPromiseTurn()
	, m_abPlayerBrokenBorderPromise()
	, m_abPlayerIgnoredBorderPromise()
	, m_aePlayerBorderPromiseData()
	, m_abPlayerMadeRemoveMiasmaPromise()
	, m_abPlayerBrokenRemoveMiasmaPromise()
	, m_abPlayerIgnoredRemoveMiasmaPromise()
	, m_abPlayerAskedNotToRemoveMiasma()
	, m_abPlayerAgreedNotToRemoveMiasma()
	, m_abPlayerMadeSpreadMiasmaPromise()
	, m_abPlayerBrokenSpreadMiasmaPromise()
	, m_abPlayerIgnoredSpreadMiasmaPromise()
	, m_abPlayerAskedNotToSpreadMiasma()
	, m_abPlayerAgreedNotToSpreadMiasma()
	, m_abPlayerMadeAntagonizeAliensPromise()
	, m_abPlayerBrokenAntagonizeAliensPromise()
	, m_abPlayerIgnoredAntagonizeAliensPromise()
	, m_abPlayerAskedNotToAntagonizeAliens()
	, m_abPlayerAgreedNotToAntagonizeAliens()
	, m_abPlayerMadeSpyPromise()
	, m_abPlayerBrokenSpyPromise()
	, m_abPlayerIgnoredSpyPromise()
	, m_abPlayerForgaveForSpying()
	, m_abPlayerMadeOrbitalDeploymentPromise()
	, m_abPlayerBrokenOrbitalDeploymentPromise()
	, m_abPlayerIgnoredOrbitalDeploymentPromise()
	, m_abPlayerAskedNotToOrbitalDeployment()
	, m_abPlayerAgreedNotToOrbitalDeployment()
	, m_abPlayerMadeNoDiggingPromise()
	, m_abPlayerBrokenNoDiggingPromise()
	, m_abPlayerIgnoredNoDiggingPromise()
	, m_abPlayerAskedNotToDig()
	, m_abPlayerAgreedNotToDig()
	, m_abPlayerBrokenCoopWarPromise()
	, m_aiOtherPlayerNumMajorsAttacked()
	, m_aiOtherPlayerNumMajorsConquered()
	, m_apaeOtherPlayerMajorCivOpinion()
	, m_apaeOtherPlayerLandDisputeLevel()
	, m_apaeOtherPlayerVictoryDisputeLevel()
	, m_apaeOtherPlayerWonderDisputeLevel()
	, m_apaeOtherPlayerWarDamageLevel()
	, m_apaiOtherPlayerWarValueLost()
	, m_apaiOtherPlayerLastRoundWarValueLost()
	, m_apabSentAttackMessageToMinorCivProtector()
	, m_apaeOtherPlayerMilitaryThreat()
	, m_apaDiploStatementsLog()
	, m_apabWorkingAgainstPlayerAccepted()
	, m_apaiWorkingAgainstPlayerCounter()
	, m_apacCoopWarAcceptedState()
	, m_apaiCoopWarCounter()
	, m_aaeOtherPlayerMajorCivOpinion()
	, m_aaeOtherPlayerLandDisputeLevel()
	, m_aaeOtherPlayerVictoryDisputeLevel()
	, m_aaeOtherPlayerWarDamageLevel()
	, m_aaiOtherPlayerWarValueLost()
	, m_aaiOtherPlayerLastRoundWarValueLost()
	, m_aabSentAttackMessageToMinorCivProtector()
	, m_aaeOtherPlayerMilitaryThreat()
	, m_aaDiploStatementsLog()
	, m_aabWorkingAgainstPlayerAccepted()
	, m_aaiWorkingAgainstPlayerCounter()
	, m_aacCoopWarAcceptedState()
	, m_aaiCoopWarCounter()
{
}

// Beyond Earth also initializes affinity state and subscribes to its gameplay events.
CvDiplomacyAI::CvDiplomacyAI()
	: m_pDiploData(NULL),
	  m_paDiploLogStatementTurnCountScratchPad(NULL),
	  m_paeMajorCivOpinion(NULL),
	  m_ppaaeOtherPlayerMajorCivOpinion(NULL),
	  m_paeMajorCivApproach(NULL),
	  m_paeApproachScratchPad(NULL),
	  m_paeMinorCivApproach(NULL),
	  m_paeApproachTowardsUsGuess(NULL),
	  m_paeApproachTowardsUsGuessCounter(NULL),
	  m_paeWantPeaceCounter(NULL),
	  m_paePeaceTreatyWillingToOffer(NULL),
	  m_paePeaceTreatyWillingToAccept(NULL),
	  m_paiNumWondersBeatenTo(NULL),
	  m_paiNumFavors(NULL),
	  m_pabMusteringForAttack(NULL),
	  m_paeWarFace(NULL),
	  m_paeWarState(NULL),
	  m_paeWarProjection(NULL),
	  m_paeLastWarProjection(NULL),
	  m_paeWarGoal(NULL),
	  m_paiPlayerNumTurnsAtWar(NULL),
	  m_paiNumWarsFought(NULL),
	  m_paePlayerMilitaryStrengthComparedToUs(NULL),
	  m_paePlayerEconomicStrengthComparedToUs(NULL),
	  m_paePlayerTargetValue(NULL),
	  m_paeWarDamageLevel(NULL),
	  m_paiWarValueLost(NULL),
	  m_ppaaeOtherPlayerWarDamageLevel(NULL),
	  m_ppaaiOtherPlayerWarValueLost(NULL),
	  m_ppaaiOtherPlayerLastRoundWarValueLost(NULL),
	  m_ppaabSentAttackMessageToMinorCivProtector(NULL),
	  m_paeMilitaryAggressivePosture(NULL),
	  m_paeLastTurnMilitaryAggressivePosture(NULL),
	  m_paeExpansionAggressivePosture(NULL),
	  m_paePlotBuyingAggressivePosture(NULL),
	  m_paePlayerLandDisputeLevel(NULL),
	  m_paePlayerLastTurnLandDisputeLevel(NULL),
	  m_paePlayerVictoryDisputeLevel(NULL),
	  m_paePlayerWonderDisputeLevel(NULL),
	  m_ppaaeOtherPlayerLandDisputeLevel(NULL),
	  m_ppaaeOtherPlayerVictoryDisputeLevel(NULL),
	  m_paeMilitaryThreat(NULL),
	  m_ppaaeOtherPlayerMilitaryThreat(NULL),
	  m_paeWarmongerThreat(NULL),
	  m_pabPlayerNoSettleRequestAccepted(NULL),
	  m_paiPlayerNoSettleRequestCounter(NULL),
	  m_pabPlayerStopSpyingRequestAccepted(NULL),
	  m_paiPlayerStopSpyingRequestCounter(NULL),
	  m_paiDemandCounter(NULL),
	  m_paiDemandTooSoonNumTurns(NULL),
	  m_pabCoopAgreementAccepted(NULL),
	  m_paiCoopAgreementCounter(NULL),
	  m_paiDenouncedPlayer(NULL),
	  m_pabFriendDenouncedUs(NULL),
	  m_pabFriendDeclaredWarOnUs(NULL),
	  m_paiDenouncedPlayerCounter(NULL),
	  m_paiNumCiviliansReturnedToMe(NULL),
	  m_paiStationsDestroyedScore(NULL),
	  m_paiResurrectedOnTurn(NULL),
	  m_paiNumTimesCultureBombed(NULL),
	  m_paiNegativeArchaeologyPoints(NULL),
	  m_paiNumTimesNuked(NULL),
	  m_paiNumTimesRobbedBy(NULL),
	  m_paiBrokenExpansionPromiseValue(NULL),
	  m_paiIgnoredExpansionPromiseValue(NULL),
	  m_paiBrokenBorderPromiseValue(NULL),
	  m_paiIgnoredBorderPromiseValue(NULL),
	  m_paiDeclaredWarOnFriendValue(NULL),
	  m_paiTradeValue(NULL),
	  m_paiCommonFoeValue(NULL),
	  m_paiAssistValue(NULL),
	  m_paiUnitsGiftedValue(NULL),
	  m_paiNumCitiesLiberated(NULL),
	  m_ppaabWorkingAgainstPlayerAccepted(NULL),
	  m_ppaaiWorkingAgainstPlayerCounter(NULL),
	  m_ppaacCoopWarAcceptedState(NULL),
	  m_ppaaiCoopWarCounter(NULL),
	  m_pabPlayerMadeMilitaryPromise(NULL),
	  m_pabPlayerBrokenMilitaryPromise(NULL),
	  m_pabPlayerIgnoredMilitaryPromise(NULL),
	  m_paiPlayerMilitaryPromiseCounter(NULL),
	  m_paiPlayerMadeExpansionPromiseTurn(NULL),
	  m_pabPlayerBrokenExpansionPromise(NULL),
	  m_pabPlayerIgnoredExpansionPromise(NULL),
	  m_paePlayerExpansionPromiseData(NULL),
	  m_paiPlayerMadeBorderPromiseTurn(NULL),
	  m_pabPlayerBrokenBorderPromise(NULL),
	  m_pabPlayerIgnoredBorderPromise(NULL),
	  m_paePlayerBorderPromiseData(NULL),
	  m_pabPlayerMadeRemoveMiasmaPromise(NULL),
	  m_pabPlayerBrokenRemoveMiasmaPromise(NULL),
	  m_pabPlayerIgnoredRemoveMiasmaPromise(NULL),
	  m_pabPlayerMadeSpreadMiasmaPromise(NULL),
	  m_pabPlayerBrokenSpreadMiasmaPromise(NULL),
	  m_pabPlayerIgnoredSpreadMiasmaPromise(NULL),
	  m_pabPlayerMadeAntagonizeAliensPromise(NULL),
	  m_pabPlayerBrokenAntagonizeAliensPromise(NULL),
	  m_pabPlayerIgnoredAntagonizeAliensPromise(NULL),
	  m_pabPlayerMadeSpyPromise(NULL),
	  m_pabPlayerBrokenSpyPromise(NULL),
	  m_pabPlayerIgnoredSpyPromise(NULL),
	  m_pabPlayerForgaveForSpying(NULL),
	  m_pabPlayerMadeOrbitalDeploymentPromise(NULL),
	  m_pabPlayerBrokenOrbitalDeploymentPromise(NULL),
	  m_pabPlayerIgnoredOrbitalDeploymentPromise(NULL),
	  m_pabPlayerMadeStationAggressionPromise(NULL),
	  m_pabPlayerBrokenStationAggressionPromise(NULL),
	  m_pabPlayerIgnoredStationAggressionPromise(NULL),
	  m_pabPlayerMadeNoDiggingPromise(NULL),
	  m_pabPlayerBrokenNoDiggingPromise(NULL),
	  m_pabPlayerIgnoredNoDiggingPromise(NULL),
	  m_pabPlayerAskedNotToDig(NULL),
	  m_pabPlayerAgreedNotToDig(NULL),
	  m_pabPlayerAskedNotToRemoveMiasma(NULL),
	  m_pabPlayerAgreedNotToRemoveMiasma(NULL),
	  m_pabPlayerAskedNotToSpreadMiasma(NULL),
	  m_pabPlayerAgreedNotToSpreadMiasma(NULL),
	  m_pabPlayerAskedNotToAntagonizeAliens(NULL),
	  m_pabPlayerAgreedNotToAntagonizeAliens(NULL),
	  m_pabPlayerAskedNotToOrbitalDeployment(NULL),
	  m_pabPlayerAgreedNotToOrbitalDeployment(NULL),
	  m_pabPlayerAskedNotToStationAggression(NULL),
	  m_pabPlayerAgreedNotToStationAggression(NULL),
	  m_pabPlayerBrokenCoopWarPromise(NULL),
	  m_paiPersonalityMajorCivApproachBiases(NULL),
	  m_paiCondemnWillingness(NULL),
	  m_paiOtherPlayerNumMajorsAttacked(NULL),
	  m_paiOtherPlayerNumMajorsConquered(NULL),
	  m_paiOtherPlayerWarmongerAmount(NULL),
	  m_paiOtherPlayerTurnSpreadMiasma(NULL),
	  m_paiOtherPlayerTurnRemovedMiasma(NULL),
	  m_paiOtherPlayerAntiAliensAmount(NULL),
	  m_paiOtherPlayerTurnOrbitalDeployment(NULL),
	  m_ppaDiploStatementsLog(NULL),
	  m_paDeclarationsLog(NULL),
	  m_lastDiploEventType(static_cast<FromUIDiploEventTypes>(-1)),
	  m_eStateAllWars(0),
	  m_eTargetPlayer(NO_PLAYER),
	  m_eTestToPlayer(NO_PLAYER),
	  m_eTestStatement(static_cast<DiploStatementTypes>(-1)),
	  m_iTestStatementArg1(-1),
	  m_ePurityAffinityType(NO_AFFINITY_TYPE),
	  m_eHarmonyAffinityType(NO_AFFINITY_TYPE),
	  m_eSupremacyAffinityType(NO_AFFINITY_TYPE)
{
	CvDiplomacyAIEvents::AlienNestCleared::SUBSCRIPTION alienNestCleared;
	CvDiplomacyAIEvents::UnitKilled::SUBSCRIPTION unitKilled;
	CvDiplomacyAIEvents::UnitAttacked::SUBSCRIPTION unitAttacked;
	CvDiplomacyAIEvents::StationRemoved::SUBSCRIPTION stationRemoved;
	CvDiplomacyAIEvents::BuildFinished::SUBSCRIPTION buildFinished;

	buildFinished.callback = &CvDiplomacyAI::OnBuildFinished;
	buildFinished.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::Subscribe<CvDiplomacyAIEvents::BuildFinished>(
		13, buildFinished, GCEventSystemAccessor::g_GCEventSystem);

	stationRemoved.callback = &CvDiplomacyAI::OnStationDestroyed;
	stationRemoved.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::Subscribe<CvDiplomacyAIEvents::StationRemoved>(
		4, stationRemoved, GCEventSystemAccessor::g_GCEventSystem);

	unitAttacked.callback = &CvDiplomacyAI::OnAlienUnitAttacked;
	unitAttacked.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::Subscribe<CvDiplomacyAIEvents::UnitAttacked>(
		19, unitAttacked, GCEventSystemAccessor::g_GCEventSystem);

	unitKilled.callback = &CvDiplomacyAI::OnAlienUnitKilled;
	unitKilled.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::Subscribe<CvDiplomacyAIEvents::UnitKilled>(
		20, unitKilled, GCEventSystemAccessor::g_GCEventSystem);

	alienNestCleared.callback = &CvDiplomacyAI::OnAlienNestDestroyed;
	alienNestCleared.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::Subscribe<CvDiplomacyAIEvents::AlienNestCleared>(
		33, alienNestCleared, GCEventSystemAccessor::g_GCEventSystem);
}

CvDiplomacyAI::~CvDiplomacyAI()
{
	CvDiplomacyAIEvents::AlienNestCleared::SUBSCRIPTION alienNestCleared;
	CvDiplomacyAIEvents::UnitKilled::SUBSCRIPTION unitKilled;
	CvDiplomacyAIEvents::UnitAttacked::SUBSCRIPTION unitAttacked;
	CvDiplomacyAIEvents::StationRemoved::SUBSCRIPTION stationRemoved;
	CvDiplomacyAIEvents::BuildFinished::SUBSCRIPTION buildFinished;

	buildFinished.callback = &CvDiplomacyAI::OnBuildFinished;
	buildFinished.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::UnSubscribe<CvDiplomacyAIEvents::BuildFinished>(
		13, buildFinished, GCEventSystemAccessor::g_GCEventSystem);

	stationRemoved.callback = &CvDiplomacyAI::OnStationDestroyed;
	stationRemoved.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::UnSubscribe<CvDiplomacyAIEvents::StationRemoved>(
		4, stationRemoved, GCEventSystemAccessor::g_GCEventSystem);

	unitAttacked.callback = &CvDiplomacyAI::OnAlienUnitAttacked;
	unitAttacked.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::UnSubscribe<CvDiplomacyAIEvents::UnitAttacked>(
		19, unitAttacked, GCEventSystemAccessor::g_GCEventSystem);

	unitKilled.callback = &CvDiplomacyAI::OnAlienUnitKilled;
	unitKilled.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::UnSubscribe<CvDiplomacyAIEvents::UnitKilled>(
		20, unitKilled, GCEventSystemAccessor::g_GCEventSystem);

	alienNestCleared.callback = &CvDiplomacyAI::OnAlienNestDestroyed;
	alienNestCleared.object = this;
	Events::BaseEvent<GCEventSystemAccessor, Events::EmptySubscriptionValidator>::UnSubscribe<CvDiplomacyAIEvents::AlienNestCleared>(
		33, alienNestCleared, GCEventSystemAccessor::g_GCEventSystem);
}

FDataStream& operator<<(FDataStream& saveTo, const DeclarationLogData& readFrom)
{
	saveTo << readFrom.m_eDeclaration;
	saveTo << readFrom.m_iData1;
	saveTo << readFrom.m_iData2;
	saveTo << readFrom.m_eMustHaveMetPlayer;
	saveTo << readFrom.m_bActive;
	saveTo << readFrom.m_iTurn;
	return saveTo;
}

inline FDataStream& operator>>(FDataStream& loadFrom, PublicDeclarationTypes& writeTo)
{
	int value;
	loadFrom >> value;
	writeTo = static_cast<PublicDeclarationTypes>(value);
	return loadFrom;
}

FDataStream& operator>>(FDataStream& loadFrom, DeclarationLogData& writeTo)
{
	loadFrom >> writeTo.m_eDeclaration;
	loadFrom >> writeTo.m_iData1;
	loadFrom >> writeTo.m_iData2;
	loadFrom >> writeTo.m_eMustHaveMetPlayer;
	loadFrom >> writeTo.m_bActive;
	loadFrom >> writeTo.m_iTurn;
	return loadFrom;
}

bool CvDiplomacyAI::IsDemandReady()
{
	return m_bDemandReady;
}

void CvDiplomacyAI::SetDemandReady(bool bValue)
{
	m_bDemandReady = bValue;
}

// Beyond Earth scales differing dominant affinity levels by the requesting leader's devotion.
int CvDiplomacyAI::GetAffinityDiffersScore(PlayerTypes ePlayer) const
{
	CvPlayerAffinities* myAffinities = m_pPlayer->GetPlayerAffinities();
	if(myAffinities == NULL)
		return 0;

	CvPlayerAffinities* yourAffinities = GET_PLAYER(ePlayer).GetPlayerAffinities();
	if(yourAffinities == NULL)
		return 0;

	AffinityType myDominantAffinity = myAffinities->GetDominantAffinityType();
	AffinityType yourDominantAffinity = yourAffinities->GetDominantAffinityType();
	if(myDominantAffinity == yourDominantAffinity)
		return 0;
	if(myDominantAffinity == NO_AFFINITY_TYPE)
		return 0;
	if(yourDominantAffinity == NO_AFFINITY_TYPE)
		return 0;

	int minAffinityPercent = GC.getOPINION_WEIGHT_AFFINITY_DIFFERS_MIN_PERCENT_TOWARDS_MAX_LEVEL();
	if(myAffinities->GetAffinityPercentTowardsMaxLevel(myDominantAffinity) < minAffinityPercent)
		return 0;
	if(yourAffinities->GetAffinityPercentTowardsMaxLevel(yourDominantAffinity) < minAffinityPercent)
		return 0;

	int myAffinityWeight = myAffinities->GetAffinityLevel(myDominantAffinity) * 200;
	int yourAffinityWeight = yourAffinities->GetAffinityLevel(yourDominantAffinity) * 100;
	int sumWeight = myAffinityWeight + yourAffinityWeight;

	int myAffinityDevotion = m_pPlayer->getLeaderInfo().GetAffinityDevotion();
	if(myAffinityDevotion < 4)
		sumWeight = sumWeight * 50 / 100;
	else if(myAffinityDevotion < 7)
		sumWeight = sumWeight * 75 / 100;

	int score = sumWeight / 100 + GC.getOPINION_WEIGHT_AFFINITY_DIFFERS();
	return score;
}

void CvDiplomacyAI::SetWarGoal(PlayerTypes ePlayer, WarGoalTypes eWarGoal)
{
	m_paeWarGoal[ePlayer] = eWarGoal;
}

// Beyond Earth uses explicit string lengths and omits debug-only logging calls.
void CvDiplomacyAI::LogPeaceMade(PlayerTypes ePlayer)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString playerName;
		CvString otherPlayerName;
		CvString strDesc;
		CvString strLogName;

		playerName = m_pPlayer->getCivilizationShortDescription();

		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "DiplomacyAI_Log_" + playerName + ".csv";
		}
		else
		{
			strLogName.assign("DiplomacyAI_Log.csv", 19);
		}

		FILogFile* pLog;
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName + ", ";

		otherPlayerName = GET_PLAYER(ePlayer).getCivilizationShortDescription();
		strOutBuf = strBaseString + ", ***** PEACE MADE! *****, " + otherPlayerName;

		pLog->Msg(strOutBuf);

		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "DiplomacyAI_Messages_Log_" + playerName + ".csv";
		}
		else
		{
			strLogName.assign("DiplomacyAI_Messages_Log.csv", 28);
		}
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);
		pLog->Msg(strOutBuf);

		m_pPlayer->GetMilitaryAI()->LogPeace(ePlayer);
	}
}

// Beyond Earth uses explicit string lengths and omits debug-only logging calls.
void CvDiplomacyAI::LogDenounce(PlayerTypes ePlayer, bool bBackstab, bool bRefusal)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString playerName;
		CvString strDesc;
		CvString strLogName;

		playerName = m_pPlayer->getCivilizationShortDescription();

		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "DiplomacyAI_Messages_Log_" + playerName + ".csv";
		}
		else
		{
			strLogName.assign("DiplomacyAI_Messages_Log.csv", 28);
		}

		FILogFile* pLog;
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName + ", ";

		CvString otherPlayerName = GET_PLAYER(ePlayer).getCivilizationShortDescription();

		if(bBackstab)
			strOutBuf = strBaseString + ",***** BACKSTABBED " + otherPlayerName + "! *****";
		else if(bRefusal)
			strOutBuf = strBaseString + ",***** REFUSED TO FORGIVE " + otherPlayerName + "! *****";
		else
			strOutBuf = strBaseString + ",***** DENOUNCED " + otherPlayerName + "! *****";

		pLog->Msg(strOutBuf);
	}
}

// Beyond Earth uses explicit string lengths and omits debug-only logging calls.
void CvDiplomacyAI::LogFriendRequestDenounce(PlayerTypes ePlayer, PlayerTypes eAgainstPlayer, bool bAgreed)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString playerName;
		CvString strDesc;
		CvString strLogName;

		playerName = m_pPlayer->getCivilizationShortDescription();

		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "DiplomacyAI_Messages_Log_" + playerName + ".csv";
		}
		else
		{
			strLogName.assign("DiplomacyAI_Messages_Log.csv", 28);
		}

		FILogFile* pLog;
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName + ", ";

		CvString otherPlayerName = GET_PLAYER(ePlayer).getCivilizationShortDescription();
		CvString againstPlayerName = GET_PLAYER(eAgainstPlayer).getCivilizationShortDescription();

		if(bAgreed)
			strOutBuf = strBaseString + ",***** CONVINCED " + otherPlayerName + " TO DENOUNCE " + againstPlayerName + "! *****";
		else
			strOutBuf = strBaseString + ", ASKED " + otherPlayerName + " TO DENOUNCE " + againstPlayerName + "!";

		pLog->Msg(strOutBuf);
	}
}

// Beyond Earth uses explicit string lengths and omits debug-only logging calls.
void CvDiplomacyAI::LogCoopWar(PlayerTypes ePlayer, PlayerTypes eAgainstPlayer, CoopWarStates eAcceptedState)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString playerName;
		CvString strDesc;
		CvString strLogName;

		playerName = m_pPlayer->getCivilizationShortDescription();

		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "DiplomacyAI_Messages_Log_" + playerName + ".csv";
		}
		else
		{
			strLogName.assign("DiplomacyAI_Messages_Log.csv", 28);
		}

		FILogFile* pLog;
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName + ", ";

		CvString otherPlayerName = GET_PLAYER(ePlayer).getCivilizationShortDescription();
		CvString againstPlayerName = GET_PLAYER(eAgainstPlayer).getCivilizationShortDescription();

		if(eAcceptedState == COOP_WAR_STATE_ACCEPTED)
			strOutBuf = strBaseString + ",***** NOW coop war with " + otherPlayerName + " against " + againstPlayerName + "! *****";
		else if(eAcceptedState == COOP_WAR_STATE_SOON)
			strOutBuf = strBaseString + ",***** SOON coop war with " + otherPlayerName + " against " + againstPlayerName + "! *****";
		else if(eAcceptedState == COOP_WAR_STATE_REJECTED)
			strOutBuf = strBaseString + ", wanted coop war with " + otherPlayerName + " against " + againstPlayerName + "!";

		pLog->Msg(strOutBuf);
	}
}

void CvDiplomacyAI::LogWantRA(PlayerTypes ePlayer)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString playerName;
		CvString otherPlayerName;
		CvString strDesc;
		CvString strLogName;

		playerName = m_pPlayer->getCivilizationShortDescription();
		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "DiplomacyAI_Messages_Log_" + playerName + ".csv";
		}
		else
		{
			strLogName.assign("DiplomacyAI_Messages_Log.csv", 28);
		}

		FILogFile* pLog;
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName + ", ";

		otherPlayerName = GET_PLAYER(ePlayer).getCivilizationShortDescription();
		strOutBuf = strBaseString + otherPlayerName + ", Wants Research Agreement!";
		pLog->Msg(strOutBuf);
	}
}

void CvDiplomacyAI::LogOpinionUpdate(PlayerTypes ePlayer, std::vector<int>& viOpinionValues)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString strTemp;
		CvString playerName;
		CvString otherPlayerName;
		CvString strDesc;

		playerName = m_pPlayer->getCivilizationShortDescription();
		FILogFile* pLog = GetDiploApproachLog();

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName;

		otherPlayerName = GET_PLAYER(ePlayer).getCivilizationShortDescription();
		strBaseString += ", " + otherPlayerName;

		strTemp.Format("OPINION");
		strOutBuf += ", " + strTemp;

		MajorCivOpinionTypes eMajorCivOpinion;
		if(!GET_PLAYER(ePlayer).isMinorCiv())
		{
			switch(static_cast<MajorCivOpinionTypes>(m_paeMajorCivOpinion[ePlayer]))
			{
			case MAJOR_CIV_OPINION_ALLY:
				strTemp.Format("** ALLY **");
				break;
			case MAJOR_CIV_OPINION_FRIEND:
				strTemp.Format("FRIEND");
				break;
			case MAJOR_CIV_OPINION_FAVORABLE:
				strTemp.Format("Favorable");
				break;
			case MAJOR_CIV_OPINION_NEUTRAL:
				strTemp.Format("N");
				break;
			case MAJOR_CIV_OPINION_COMPETITOR:
				strTemp.Format("Competitor");
				break;
			case MAJOR_CIV_OPINION_ENEMY:
				strTemp.Format("ENEMY");
				break;
			case MAJOR_CIV_OPINION_UNFORGIVABLE:
				strTemp.Format("**UNFORGIVABLE**");
				break;
			default:
				strTemp.Format("XXX");
				break;
			}
			strOutBuf += ", " + strTemp;

			for(int iMajorCivOpinionLoop = 0; iMajorCivOpinionLoop < NUM_MAJOR_CIV_OPINION_TYPES; iMajorCivOpinionLoop++)
			{
				eMajorCivOpinion = (MajorCivOpinionTypes)iMajorCivOpinionLoop;
				switch(eMajorCivOpinion)
				{
				case MAJOR_CIV_OPINION_ALLY:
					strTemp.Format("Ally");
					break;
				case MAJOR_CIV_OPINION_FRIEND:
					strTemp.Format("Friend");
					break;
				case MAJOR_CIV_OPINION_NEUTRAL:
					strTemp.Format("Neutral");
					break;
				case MAJOR_CIV_OPINION_COMPETITOR:
					strTemp.Format("Competitor");
					break;
				case MAJOR_CIV_OPINION_ENEMY:
					strTemp.Format("Enemy");
					break;
				default:
					strTemp.Format("XXX");
					break;
				}
				strOutBuf += ", " + strTemp;

				strTemp.Format("%d", viOpinionValues[eMajorCivOpinion]);
				strOutBuf += ", " + strTemp;
			}

			strOutBuf = strBaseString + strOutBuf;
			pLog->Msg(strOutBuf);
		}
	}
}

// TODO: not an exact binary match for Beyond Earth (97% match)
void CvDiplomacyAI::LogMajorCivApproachUpdate(PlayerTypes ePlayer, const int* aiApproachValues, MajorCivApproachTypes eNewMajorCivApproach, MajorCivApproachTypes eOldApproach, WarFaceTypes eNewWarFace)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString strTemp;
		CvString playerName;
		CvString otherPlayerName;
		CvString strDesc;

		playerName = m_pPlayer->getCivilizationShortDescription();
		FILogFile* pLog = GetDiploApproachLog();

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName;

		otherPlayerName = GET_PLAYER(ePlayer).getCivilizationShortDescription();
		strBaseString += ", " + otherPlayerName;

		MajorCivApproachTypes eMajorCivApproach;
		if(!GET_PLAYER(ePlayer).isMinorCiv())
		{
			LogMajorCivApproach(strOutBuf, eNewMajorCivApproach, eNewWarFace);
			if(eNewMajorCivApproach != eOldApproach)
			{
				LogMajorCivApproach(strOutBuf, eOldApproach, eNewWarFace);
			}
			else
			{
				strTemp.Format("---");
				strOutBuf += ", " + strTemp;
			}

			LogFearRespect(strOutBuf, ePlayer);
			LogOpinion(strOutBuf, ePlayer);
			LogWarmongerThreat(strOutBuf, ePlayer);
			LogMilitaryThreat(strOutBuf, ePlayer);
			LogTargetValue(strOutBuf, ePlayer);
			LogWarGoal(strOutBuf, ePlayer);
			LogMilitaryAggressivePosture(strOutBuf, ePlayer);
			LogProximity(strOutBuf, ePlayer);
			LogLandDispute(strOutBuf, ePlayer);
			LogVictoryDispute(strOutBuf, ePlayer);
			LogWonderDispute(strOutBuf, ePlayer);

			strTemp.Format("---");
			strOutBuf += ", " + strTemp;
			LogMajorCivApproachWeights(strOutBuf, aiApproachValues);

			strOutBuf = strBaseString + strOutBuf;
			pLog->Msg(strOutBuf);
		}
	}
}

// TODO: not an exact binary match for Beyond Earth (97% match)
void CvDiplomacyAI::LogMinorCivApproachUpdate(PlayerTypes ePlayer, const int* aiApproachValues, MinorCivApproachTypes eNewMinorCivApproach, MinorCivApproachTypes eOldApproach)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString strTemp;
		CvString playerName;
		CvString otherPlayerName;
		CvString strDesc;

		playerName = m_pPlayer->getCivilizationShortDescription();
		FILogFile* pLog = GetDiploApproachLog();

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName;

		otherPlayerName = GET_PLAYER(ePlayer).getCivilizationShortDescription();
		strBaseString += ", --- " + otherPlayerName;

		MinorCivApproachTypes eMinorCivApproach;
		if(GET_PLAYER(ePlayer).isMinorCiv())
		{
			LogMinorCivApproach(strOutBuf, eNewMinorCivApproach);
			if(eNewMinorCivApproach != eOldApproach)
			{
				LogMinorCivApproach(strOutBuf, eOldApproach);
			}
			else
			{
				strTemp.Format("---");
				strOutBuf += ", " + strTemp;
			}

			strOutBuf += ", ";
			strOutBuf += ", ";
			strOutBuf += ", ";
			LogTargetValue(strOutBuf, ePlayer);
			LogWarGoal(strOutBuf, ePlayer);
			LogMilitaryAggressivePosture(strOutBuf, ePlayer);
			LogProximity(strOutBuf, ePlayer);
			LogLandDispute(strOutBuf, ePlayer);
			strOutBuf += ", ";
			strOutBuf += ", ---";

			for(int iMinorCivApproachLoop = 0; iMinorCivApproachLoop < NUM_MINOR_CIV_APPROACHES; iMinorCivApproachLoop++)
			{
				eMinorCivApproach = (MinorCivApproachTypes)iMinorCivApproachLoop;
				switch(eMinorCivApproach)
				{
				case MINOR_CIV_APPROACH_IGNORE:
					strTemp.Format("Ignore");
					break;
				case MINOR_CIV_APPROACH_FRIENDLY:
					strTemp.Format("Friendly");
					break;
				case MINOR_CIV_APPROACH_PROTECTIVE:
					strTemp.Format("Protective");
					break;
				case MINOR_CIV_APPROACH_CONQUEST:
					strTemp.Format("Conquest");
					break;
				case MINOR_CIV_APPROACH_BULLY:
					strTemp.Format("Bully");
					break;
				default:
					strTemp.Format("XXX");
					break;
				}
				strOutBuf += ", " + strTemp;

				strTemp.Format("%d", aiApproachValues[eMinorCivApproach] / 100);
				strOutBuf += ", " + strTemp;
			}

			strOutBuf = strBaseString + strOutBuf;
			pLog->Msg(strOutBuf);
		}
	}
}

void CvDiplomacyAI::LogPersonality()
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString playerName;
		CvString strDesc;
		CvString strLogName;
		CvString strTemp;

		playerName = m_pPlayer->getCivilizationShortDescription();
		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "AI_Personality_Log_" + playerName + ".csv";
		}
		else
		{
			strLogName.assign("AI_Personality_Log.csv", 22);
		}

		FILogFile* pLog;
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);

		strBaseString.Format("%03d, PERSONALITY, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName;

		for(int iFlavorLoop = 0; iFlavorLoop < GC.getNumFlavorTypes(); iFlavorLoop++)
		{
			strTemp.Format("%s, %d", GC.getFlavorTypes((FlavorTypes)iFlavorLoop).GetCString(), m_pPlayer->GetFlavorManager()->GetPersonalityIndividualFlavor((FlavorTypes)iFlavorLoop));
			strOutBuf = strBaseString + ", " + strTemp;
			pLog->Msg(strOutBuf);
		}

		MajorCivApproachTypes eMajorCivApproach;
		for(int iApproachLoop = 0; iApproachLoop < NUM_MAJOR_CIV_APPROACHES; iApproachLoop++)
		{
			eMajorCivApproach = (MajorCivApproachTypes)iApproachLoop;
			switch(eMajorCivApproach)
			{
			case MAJOR_CIV_APPROACH_WAR:
				strTemp.Format("War");
				break;
			case MAJOR_CIV_APPROACH_HOSTILE:
				strTemp.Format("Hostile");
				break;
			case MAJOR_CIV_APPROACH_DECEPTIVE:
				strTemp.Format("Deceptive");
				break;
			case MAJOR_CIV_APPROACH_GUARDED:
				strTemp.Format("Guarded");
				break;
			case MAJOR_CIV_APPROACH_AFRAID:
				strTemp.Format("Afraid");
				break;
			case MAJOR_CIV_APPROACH_FRIENDLY:
				strTemp.Format("Friendly");
				break;
			case MAJOR_CIV_APPROACH_NEUTRAL:
				strTemp.Format("Neutral");
				break;
			default:
				strTemp.Format("XXX");
				break;
			}
			strOutBuf = strBaseString + ", " + strTemp;
			strTemp.Format("%d", m_paiPersonalityMajorCivApproachBiases[eMajorCivApproach]);
			strOutBuf += ", " + strTemp;
			pLog->Msg(strOutBuf);
		}

		strTemp.Format("VICTORY COMPETITIVENESS, %d", m_iVictoryCompetitiveness);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("WONDER COMPETITIVENESS, %d", m_iWonderCompetitiveness);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("BOLDNESS, %d", m_iBoldness);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("DIPLO BALANCE, %d", m_iDiploBalance);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("WARMONGER HATE, %d", m_iWarmongerHate);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);

		for(int iCondemnLoop = 0; iCondemnLoop < NUM_MAJOR_CIV_APPROACHES; iCondemnLoop++)
		{
			strTemp.Format("CONDEMN %d, %d", iCondemnLoop, m_paiCondemnWillingness[iCondemnLoop]);
			strOutBuf = strBaseString + ", " + strTemp;
			pLog->Msg(strOutBuf);
		}

		strTemp.Format("Cooperativeness, %d", m_iCoopWillingness);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("LOYALTY, %d", m_iLoyalty);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("NEEDINESS, %d", m_iNeediness);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("FORGIVENESS, %d", m_iForgiveness);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("CHATTINESS, %d", m_iChattiness);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
		strTemp.Format("MEANNESS, %d", m_iMeanness);
		strOutBuf = strBaseString + ", " + strTemp;
		pLog->Msg(strOutBuf);
	}
}

void CvDiplomacyAI::LogStatus()
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString playerName;
		CvString otherPlayerName;
		CvString strMinorString;
		CvString strDesc;
		CvString strLogName;
		CvString strTemp;

		playerName = m_pPlayer->getCivilizationShortDescription();
		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "DiplomacyAI_Log_" + playerName + ".csv";
		}
		else
		{
			strLogName.assign("DiplomacyAI_Log.csv", 19);
		}

		FILogFile* pLog;
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);

		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName;

		int iPlayerLoop;
		PlayerTypes eLoopPlayer;
		for(iPlayerLoop = 0; iPlayerLoop < MAX_CIV_PLAYERS; iPlayerLoop++)
		{
			eLoopPlayer = (PlayerTypes)iPlayerLoop;
			if(IsPlayerValid(eLoopPlayer))
			{
				strOutBuf = strBaseString;
				LogGrandStrategy(strOutBuf);

				if(GET_PLAYER(eLoopPlayer).isMinorCiv())
				{
					// Beyond Earth assigns the minor-civ prefix with an explicit length.
					strMinorString.assign("--- ", 4);
				}

				otherPlayerName = GET_PLAYER(eLoopPlayer).getCivilizationShortDescription();
				strOutBuf += ", " + strMinorString + otherPlayerName;

				if(!GET_PLAYER(eLoopPlayer).isMinorCiv())
				{
					if(m_pabCoopAgreementAccepted[eLoopPlayer])
						strOutBuf += ", WW";
					else
						strOutBuf += ", ";

					if(m_paiDenouncedPlayer[eLoopPlayer] > 0)
						strOutBuf += ", DEN";
					else
						strOutBuf += ", ";

					if(GetGlobalCoopWarAcceptedState(eLoopPlayer) == COOP_WAR_STATE_ACCEPTED)
						strOutBuf += ", CW";
					else if(GetGlobalCoopWarAcceptedState(eLoopPlayer) == COOP_WAR_STATE_SOON)
						strOutBuf += ", CWS";
					else
						strOutBuf += ", ";

					LogMajorCivApproach(strOutBuf, static_cast<MajorCivApproachTypes>(m_paeMajorCivApproach[eLoopPlayer]), static_cast<WarFaceTypes>(m_paeWarFace[eLoopPlayer]));
					LogFearRespect(strOutBuf, eLoopPlayer);
					LogOpinion(strOutBuf, eLoopPlayer);
				}
				else
				{
					strOutBuf += ", ";
					strOutBuf += ", ";
					strOutBuf += ", ";
					LogMinorCivApproach(strOutBuf, static_cast<MinorCivApproachTypes>(m_paeMinorCivApproach[eLoopPlayer - MAX_MAJOR_CIVS]));
					strOutBuf += ", ";
				}

				LogProximity(strOutBuf, eLoopPlayer);
				LogWarState(strOutBuf, eLoopPlayer);
				LogEconomicStrength(strOutBuf, eLoopPlayer);
				LogMilitaryStrength(strOutBuf, eLoopPlayer);
				LogTargetValue(strOutBuf, eLoopPlayer);
				LogMilitaryAggressivePosture(strOutBuf, eLoopPlayer);
				LogWarmongerThreat(strOutBuf, eLoopPlayer);
				LogMilitaryThreat(strOutBuf, eLoopPlayer);
				LogExpansionAggressivePosture(strOutBuf, eLoopPlayer);
				LogPlotBuyingAggressivePosture(strOutBuf, eLoopPlayer);
				LogLandDispute(strOutBuf, eLoopPlayer);
				LogVictoryDispute(strOutBuf, eLoopPlayer);
				LogWonderDispute(strOutBuf, eLoopPlayer);

				if(!GET_PLAYER(eLoopPlayer).isMinorCiv())
				{
					AIGrandStrategyTypes eGrandStrategy = m_pPlayer->GetGrandStrategyAI()->GetGuessOtherPlayerActiveGrandStrategy(eLoopPlayer);
					CvAIGrandStrategyXMLEntry* pEntry = (eGrandStrategy != NO_AIGRANDSTRATEGY) ? GC.getAIGrandStrategyInfo(eGrandStrategy) : NULL;
					if(pEntry != NULL)
					{
						strTemp.Format("GSS %s", pEntry->GetType());
						strOutBuf += ", " + strTemp;
						switch(m_pPlayer->GetGrandStrategyAI()->GetGuessOtherPlayerActiveGrandStrategyConfidence(eLoopPlayer))
						{
						case GUESS_CONFIDENCE_POSITIVE:
							strTemp.Format("POSITIVE");
							break;
						case GUESS_CONFIDENCE_LIKELY:
							strTemp.Format("Likely");
							break;
						case GUESS_CONFIDENCE_UNSURE:
							strTemp.Format("Unsure");
							break;
						default:
							strTemp.Format("XXX");
							break;
						}
					}
					else
					{
						strTemp.Format("No GS Guess, ");
					}
				}
				else
				{
					strTemp.Format(", ");
				}
				strOutBuf += ", " + strTemp;
				pLog->Msg(strOutBuf);
			}
		}
	}
}

void CvDiplomacyAI::LogGrandStrategy(CvString& strString)
{
	CvString strTemp;

	AIGrandStrategyTypes eGrandStrategy = m_pPlayer->GetGrandStrategyAI()->GetActiveGrandStrategy();

	if(eGrandStrategy == GC.getInfoTypeForString("AIGRANDSTRATEGY_CONQUEST"))
	{
		strTemp.Format("WC");
	}
	else if(eGrandStrategy == GC.getInfoTypeForString("AIGRANDSTRATEGY_SPACESHIP"))
	{
		strTemp.Format("Spaceship");
	}
	else if(eGrandStrategy == GC.getInfoTypeForString("AIGRANDSTRATEGY_UNITED_NATIONS"))
	{
		strTemp.Format("Diplomacy");
	}
	else if(eGrandStrategy == GC.getInfoTypeForString("AIGRANDSTRATEGY_CULTURE"))
	{
		strTemp.Format("Culture");
	}

	strString += ", " + strTemp;
}

void CvDiplomacyAI::LogMajorCivApproach(CvString& strString, MajorCivApproachTypes eNewMajorCivApproach, WarFaceTypes eNewWarFace)
{
	CvString strTemp;

	switch(eNewMajorCivApproach)
	{
	case MAJOR_CIV_APPROACH_WAR:
		switch(eNewWarFace)
		{
		case WAR_FACE_HOSTILE:
			strTemp.Format("** WAR (H) **");
			break;
		case WAR_FACE_NEUTRAL:
			strTemp.Format("** WAR (N) **");
			break;
		case WAR_FACE_FRIENDLY:
			strTemp.Format("** WAR (F) **");
			break;
		default:
			strTemp.Format("** WAR **");
			break;
		}
		break;
	case MAJOR_CIV_APPROACH_HOSTILE:
		strTemp.Format("HOSTILE");
		break;
	case MAJOR_CIV_APPROACH_DECEPTIVE:
		strTemp.Format("DECEPTIVE");
		break;
	case MAJOR_CIV_APPROACH_GUARDED:
		strTemp.Format("GUARDED");
		break;
	case MAJOR_CIV_APPROACH_AFRAID:
		strTemp.Format("AFRAID");
		break;
	case MAJOR_CIV_APPROACH_FRIENDLY:
		strTemp.Format("FRIENDLY");
		break;
	case MAJOR_CIV_APPROACH_NEUTRAL:
		strTemp.Format("N");
		break;
	default:
		strTemp.Format("XXX");
		break;
	}
	strString += ", " + strTemp;
}

void CvDiplomacyAI::LogMinorCivApproach(CvString& strString, MinorCivApproachTypes eNewMinorCivApproach)
{
	CvString strTemp;

	switch(eNewMinorCivApproach)
	{
	case MINOR_CIV_APPROACH_IGNORE:
		strTemp.Format("IG");
		break;
	case MINOR_CIV_APPROACH_FRIENDLY:
		strTemp.Format("FRIENDLY");
		break;
	case MINOR_CIV_APPROACH_PROTECTIVE:
		strTemp.Format("PROTECTIVE");
		break;
	case MINOR_CIV_APPROACH_CONQUEST:
		strTemp.Format("** CONQUEST **");
		break;
	case MINOR_CIV_APPROACH_BULLY:
		strTemp.Format("BULLY");
		break;
	default:
		strTemp.Format("XXX");
		break;
	}
	strString += ", " + strTemp;
}

void CvDiplomacyAI::LogMinorCivQuestType(CvString& strString, MinorCivQuestTypes eQuestType)
{
	CvString strTemp;

	switch(eQuestType)
	{
	case MINOR_CIV_QUEST_ROUTE:
		strTemp.Format("Route");
		break;
	case MINOR_CIV_QUEST_KILL_CAMP:
		strTemp.Format("Kill Camp");
		break;
	case MINOR_CIV_QUEST_CONNECT_RESOURCE:
		strTemp.Format("Connect Resource");
		break;
	case MINOR_CIV_QUEST_CONSTRUCT_WONDER:
		strTemp.Format("Construct Wonder");
		break;
	case MINOR_CIV_QUEST_GREAT_PERSON:
		strTemp.Format("Great Person");
		break;
	case MINOR_CIV_QUEST_KILL_CITY_STATE:
		strTemp.Format("Kill City State");
		break;
	case MINOR_CIV_QUEST_FIND_PLAYER:
		strTemp.Format("Find Player");
		break;
	case MINOR_CIV_QUEST_FIND_NATURAL_WONDER:
		strTemp.Format("Find Natural Wonder");
		break;
	case MINOR_CIV_QUEST_GIVE_GOLD:
		strTemp.Format("Give Gold");
		break;
	case MINOR_CIV_QUEST_PLEDGE_TO_PROTECT:
		strTemp.Format("Pledge to Protect");
		break;
	case MINOR_CIV_QUEST_CONTEST_CULTURE:
		strTemp.Format("Contest Culture");
		break;
	case MINOR_CIV_QUEST_CONTEST_FAITH:
		strTemp.Format("Contest Faith");
		break;
	case MINOR_CIV_QUEST_CONTEST_TECHS:
		strTemp.Format("Contest Techs");
		break;
	case MINOR_CIV_QUEST_INVEST:
		strTemp.Format("Invest");
		break;
	case MINOR_CIV_QUEST_BULLY_CITY_STATE:
		strTemp.Format("Bully City-State");
		break;
	case MINOR_CIV_QUEST_DENOUNCE_MAJOR:
		strTemp.Format("Denounce Major");
		break;
	case MINOR_CIV_QUEST_SPREAD_RELIGION:
		strTemp.Format("Spread Religion");
		break;
	default:
		strTemp.Format("XXX");
		break;
	}

	strString += ", " + strTemp;
}

FDataStream& operator<<(FDataStream& saveTo, const DiploLogData& readFrom)
{
	saveTo << readFrom.m_eDiploLogStatement;
	saveTo << readFrom.m_iTurn;
	return saveTo;
}

inline FDataStream& operator>>(FDataStream& loadFrom, DiploStatementTypes& writeTo)
{
	int value;
	loadFrom >> value;
	writeTo = static_cast<DiploStatementTypes>(value);
	return loadFrom;
}

FDataStream& operator>>(FDataStream& loadFrom, DiploLogData& writeTo)
{
	loadFrom >> writeTo.m_eDiploLogStatement;
	loadFrom >> writeTo.m_iTurn;
	return loadFrom;
}
