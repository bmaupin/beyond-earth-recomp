#include <list>
#include <memory>
#include "CvGameCoreDLLUtil_Win32Headers.h"
#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvGameCoreDLLUtil/include/CvString.h"
#include "Fireworks/FFreeListArrayBase.h"
#include "CvGameCoreDLLUtil/include/CvStructs.h"
#include "CvDllPreGame.h"
#include "CvDllContext.h"
#include "CvDllDlcPackageInfo.h"
#include "CvDllWorldInfo.h"
#include "CvPreGame.h"

// TODO: Phase1 CvDllPreGame::CvDllPreGame — UNVERIFIED: Full operand and relocation-target comparison not established.
CvDllPreGame::CvDllPreGame()
{
}
// TODO: Phase1 CvDllPreGame::~CvDllPreGame — UNVERIFIED: Exact body matches only with existing PCH preinclude; direct current translation unit compilation fails.
CvDllPreGame::~CvDllPreGame()
{
}
// TODO: Phase1 CvDllPreGame::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllPreGame::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
		guidInterface == ICvPreGame1::GetInterfaceId())
	{
		return this;
	}

	return NULL;
}
// TODO: Phase1 CvDllPreGame::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::Destroy()
{
	delete this;
}
// TODO: Phase1 CvDllPreGame::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllPreGame::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}
// TODO: Phase1 CvDllPreGame::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllPreGame::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}
// TODO: Phase1 CvDllPreGame::activePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
PlayerTypes CvDllPreGame::activePlayer()
{
	return CvPreGame::activePlayer();
}
// TODO: Phase1 CvDllPreGame::advancedStartPoints — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::advancedStartPoints()
{
	return CvPreGame::advancedStartPoints();
}
// TODO: Phase1 CvDllPreGame::autorun — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::autorun()
{
	return CvPreGame::autorun();
}
// TODO: Phase1 CvDllPreGame::autorunTurnDelay — UNVERIFIED: Full operand and relocation-target comparison not established.
float CvDllPreGame::autorunTurnDelay()
{
	return CvPreGame::autorunTurnDelay();
}
// TODO: Phase1 CvDllPreGame::autorunTurnLimit — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::autorunTurnLimit()
{
	return CvPreGame::autorunTurnLimit();
}
// TODO: Phase1 CvDllPreGame::calendar — UNVERIFIED: Full operand and relocation-target comparison not established.
CalendarTypes CvDllPreGame::calendar()
{
	return CvPreGame::calendar();
}
// TODO: Phase1 CvDllPreGame::canReadyLocalPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::canReadyLocalPlayer()
{
	return CvPreGame::canReadyLocalPlayer();
}
// TODO: Phase1 CvDllPreGame::civilizationAdjective — UNVERIFIED: Full operand and relocation-target comparison not established.
CvString CvDllPreGame::civilizationAdjective(PlayerTypes p)
{
	return CvPreGame::civilizationAdjective(p);
}
// TODO: Phase1 CvDllPreGame::civilizationAdjectiveKey — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::civilizationAdjectiveKey(PlayerTypes p)
{
	return CvPreGame::civilizationAdjectiveKey(p);
}
// TODO: Phase1 CvDllPreGame::civilizationDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
CvString CvDllPreGame::civilizationDescription(PlayerTypes p)
{
	return CvPreGame::civilizationDescription(p);
}
// TODO: Phase1 CvDllPreGame::civilizationDescriptionKey — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::civilizationDescriptionKey(PlayerTypes p)
{
	return CvPreGame::civilizationDescriptionKey(p);
}
// TODO: Phase1 CvDllPreGame::civilization — UNVERIFIED: Full operand and relocation-target comparison not established.
CivilizationTypes CvDllPreGame::civilization(PlayerTypes p)
{
	return CvPreGame::civilization(p);
}
// TODO: Phase1 CvDllPreGame::civilizationPassword — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::civilizationPassword(PlayerTypes p)
{
	return CvPreGame::civilizationPassword(p);
}
// TODO: Phase1 CvDllPreGame::civilizationShortDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
CvString CvDllPreGame::civilizationShortDescription(PlayerTypes p)
{
	return CvPreGame::civilizationShortDescription(p);
}
// TODO: Phase1 CvDllPreGame::civilizationShortDescriptionKey — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::civilizationShortDescriptionKey(PlayerTypes p)
{
	return CvPreGame::civilizationShortDescriptionKey(p);
}
// TODO: Phase1 CvDllPreGame::civilizationKey — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::civilizationKey(PlayerTypes p)
{
	return CvPreGame::civilizationKey(p);
}
// TODO: Phase1 CvDllPreGame::civilizationKeyAvailable — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::civilizationKeyAvailable(PlayerTypes p)
{
	return CvPreGame::civilizationKeyAvailable(p);
}
// TODO: Phase1 CvDllPreGame::civilizationKeyPackageID — UNVERIFIED: Full operand and relocation-target comparison not established.
const GUID CvDllPreGame:: civilizationKeyPackageID(PlayerTypes p)
{
	return CvPreGame:: civilizationKeyPackageID(p);
}
// TODO: Phase1 CvDllPreGame::clearDLCAllowed — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::clearDLCAllowed()
{
	CvPreGame::clearDLCAllowed();
}
// TODO: Phase1 CvDllPreGame::climate — UNVERIFIED: Full operand and relocation-target comparison not established.
ClimateTypes CvDllPreGame::climate()
{
	return CvPreGame::climate();
}
// TODO: Phase1 CvDllPreGame::closeAllSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::closeAllSlots()
{
	CvPreGame::closeAllSlots();
}
// TODO: Phase1 CvDllPreGame::closeInactiveSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::closeInactiveSlots()
{
	CvPreGame::closeInactiveSlots();
}
// TODO: Phase1 CvDllPreGame::emailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::emailAddress(PlayerTypes p)
{
	return CvPreGame::emailAddress(p);
}
// TODO: Phase1 CvDllPreGame::emailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::emailAddress()
{
	return CvPreGame::emailAddress();
}
// TODO: Phase1 CvDllPreGame::endTurnTimerLength — UNVERIFIED: Full operand and relocation-target comparison not established.
float CvDllPreGame::endTurnTimerLength()
{
	return CvPreGame::endTurnTimerLength();
}
// TODO: Phase1 CvDllPreGame::era — UNVERIFIED: Full operand and relocation-target comparison not established.
EraTypes CvDllPreGame::era()
{
	return CvPreGame::era();
}
// TODO: Phase1 CvDllPreGame::findPlayerByNickname — UNVERIFIED: Full operand and relocation-target comparison not established.
PlayerTypes CvDllPreGame::findPlayerByNickname(const char* const name)
{
	return CvPreGame::findPlayerByNickname(name);
}
// TODO: Phase1 CvDllPreGame::gameMode — UNVERIFIED: Full operand and relocation-target comparison not established.
GameMode CvDllPreGame::gameMode()
{
	return CvPreGame::gameMode();
}
// TODO: Phase1 CvDllPreGame::gameName — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::gameName()
{
	return CvPreGame::gameName();
}
// TODO: Phase1 CvDllPreGame::gameStarted — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::gameStarted()
{
	return CvPreGame::gameStarted();
}
// TODO: Phase1 CvDllPreGame::GetGameOption — UNVERIFIED: Overloads have differing audit results; complete signature-specific comparison remains necessary.
bool CvDllPreGame::GetGameOption(const char* szOptionName, int& iValue)
{
	return CvPreGame::GetGameOption(szOptionName, iValue);
}
// TODO: Phase1 CvDllPreGame::GetGameOption — UNVERIFIED: Overloads have differing audit results; complete signature-specific comparison remains necessary.
bool CvDllPreGame::GetGameOption(GameOptionTypes eOption, int& iValue)
{
	return CvPreGame::GetGameOption(eOption, iValue);
}
// TODO: Phase1 CvDllPreGame::GetGameOptionCount — UNVERIFIED: Full operand and relocation-target comparison not established.
uint CvDllPreGame::GetGameOptionCount()
{
	return CvPreGame::GetGameOptions().size();
}
// TODO: Phase1 CvDllPreGame::GetGameOption — UNVERIFIED: Overloads have differing audit results; complete signature-specific comparison remains necessary.
bool CvDllPreGame::GetGameOption(uint uiIndex, char* szOptionNameBuffer, uint nOptionNameBufferSize, int& iValue)
{
	const std::vector<CvPreGame::CustomOption>& kOptions = CvPreGame::GetGameOptions();
	if(uiIndex < kOptions.size())
	{
		size_t nSourceBufferSize;
		const char* pszSourceBuffer = kOptions[uiIndex].GetName(nSourceBufferSize);
		if(nOptionNameBufferSize+1 > nSourceBufferSize)
		{
			strcpy(szOptionNameBuffer, pszSourceBuffer);
			iValue = kOptions[uiIndex].GetValue();
			return true;
		}
	}
	return false;
}
// TODO: Phase1 CvDllPreGame::GetMapOptionCount — UNVERIFIED: Full operand and relocation-target comparison not established.
uint CvDllPreGame::GetMapOptionCount()
{
	return CvPreGame::GetMapOptions().size();
}
// TODO: Phase1 CvDllPreGame::GetMapOption — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::GetMapOption(uint uiIndex, char* szOptionNameBuffer, uint nOptionNameBufferSize, int& iValue)
{
	const std::vector<CvPreGame::CustomOption>& kOptions = CvPreGame::GetMapOptions();
	if(uiIndex < kOptions.size())
	{
		size_t nSourceBufferSize;
		const char* pszSourceBuffer = kOptions[uiIndex].GetName(nSourceBufferSize);
		if(nOptionNameBufferSize+1 > nSourceBufferSize)
		{
			strcpy(szOptionNameBuffer, pszSourceBuffer);
			iValue = kOptions[uiIndex].GetValue();
			return true;
		}
	}
	return false;
}
// TODO: Phase1 CvDllPreGame::GetMapOption — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::GetMapOption(const char* szOptionName, int& iValue)
{
	return CvPreGame::GetMapOption(szOptionName, iValue);
}
// TODO: Phase1 CvDllPreGame::GetPersistSettings — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::GetPersistSettings()
{
	return CvPreGame::GetPersistSettings();
}
// TODO: Phase1 CvDllPreGame::gameSpeed — UNVERIFIED: Full operand and relocation-target comparison not established.
GameSpeedTypes CvDllPreGame::gameSpeed()
{
	return CvPreGame::gameSpeed();
}
// TODO: Phase1 CvDllPreGame::gameTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::gameTurn()
{
	return CvPreGame::gameTurn();
}
// TODO: Phase1 CvDllPreGame::gameType — UNVERIFIED: Full operand and relocation-target comparison not established.
GameTypes CvDllPreGame::gameType()
{
	return CvPreGame::gameType();
}
// TODO: Phase1 CvDllPreGame::gameStartType — UNVERIFIED: Full operand and relocation-target comparison not established.
GameStartTypes CvDllPreGame::gameStartType()
{
	return CvPreGame::gameStartType();
}
// TODO: Phase1 CvDllPreGame::handicap — UNVERIFIED: Full operand and relocation-target comparison not established.
HandicapTypes CvDllPreGame::handicap(PlayerTypes p)
{
	return CvPreGame::handicap(p);
}
// TODO: Phase1 CvDllPreGame::isDLCAllowed — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isDLCAllowed(const GUID& kDLCID)
{
	return CvPreGame::isDLCAllowed(kDLCID);
}
// TODO: Phase1 CvDllPreGame::isDLCAvailable — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isDLCAvailable(PlayerTypes p, const GUID& kDLCID)
{
	return CvPreGame::isDLCAvailable(p, kDLCID);
}
// TODO: Phase1 CvDllPreGame::isEarthMap — UNVERIFIED: Exact body matches only with existing PCH preinclude; direct current translation unit compilation fails.
bool CvDllPreGame::isEarthMap()
{
	//This function is no longer used, it only exists for interface compatibility.
	return false;
}
// TODO: Phase1 CvDllPreGame::isHotSeat — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isHotSeat()
{
	return CvPreGame::isHotSeat();
}
// TODO: Phase1 CvDllPreGame::isHotSeatGame — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isHotSeatGame()
{
	return CvPreGame::isHotSeatGame();
}
// TODO: Phase1 CvDllPreGame::isHuman — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isHuman(PlayerTypes p)
{
	return CvPreGame::isHuman(p);
}
// TODO: Phase1 CvDllPreGame::isInternetGame — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isInternetGame()
{
	return CvPreGame::isInternetGame();
}
// TODO: Phase1 CvDllPreGame::isMinorCiv — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isMinorCiv(PlayerTypes p)
{
	return CvPreGame::isMinorCiv(p);
}
// TODO: Phase1 CvDllPreGame::isNetworkMultiplayerGame — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isNetworkMultiplayerGame()
{
	return CvPreGame::isNetworkMultiplayerGame();
}
// TODO: Phase1 CvDllPreGame::isPitBoss — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isPitBoss()
{
	return CvPreGame::isPitBoss();
}
// TODO: Phase1 CvDllPreGame::isPlayable — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isPlayable(PlayerTypes p)
{
	return CvPreGame::isPlayable(p);
}
// TODO: Phase1 CvDllPreGame::isPlayByEmail — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isPlayByEmail()
{
	return CvPreGame::isPlayByEmail();
}
// TODO: Phase1 CvDllPreGame::isReady — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isReady(PlayerTypes p)
{
	return CvPreGame::isReady(p);
}
// TODO: Phase1 CvDllPreGame::isVictory — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isVictory(VictoryTypes v)
{
	return CvPreGame::isVictory(v);
}
// TODO: Phase1 CvDllPreGame::isWBMapScript — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isWBMapScript()
{
	return CvPreGame::isWBMapScript();
}
// TODO: Phase1 CvDllPreGame::isWhiteFlag — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isWhiteFlag(PlayerTypes p)
{
	return CvPreGame::isWhiteFlag(p);
}
// TODO: Phase1 CvDllPreGame::leaderHead — UNVERIFIED: Full operand and relocation-target comparison not established.
LeaderHeadTypes CvDllPreGame::leaderHead(PlayerTypes p)
{
	return CvPreGame::leaderHead(p);
}
// TODO: Phase1 CvDllPreGame::leaderName — UNVERIFIED: Full operand and relocation-target comparison not established.
CvString CvDllPreGame::leaderName(PlayerTypes p)
{
	return CvPreGame::leaderName(p);
}
// TODO: Phase1 CvDllPreGame::leaderNameKey — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::leaderNameKey(PlayerTypes p)
{
	return CvPreGame::leaderNameKey(p);
}
// TODO: Phase1 CvDllPreGame::leaderKey — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::leaderKey(PlayerTypes p)
{
	return CvPreGame::leaderKey(p);
}
// TODO: Phase1 CvDllPreGame::leaderKeyAvailable — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::leaderKeyAvailable(PlayerTypes p)
{
	return CvPreGame::leaderKeyAvailable(p);
}
// TODO: Phase1 CvDllPreGame::leaderKeyPackageID — UNVERIFIED: Full operand and relocation-target comparison not established.
const GUID CvDllPreGame::leaderKeyPackageID(PlayerTypes p)
{
	return CvPreGame::leaderKeyPackageID(p);
}
// TODO: Phase1 CvDllPreGame::loadFileName — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::loadFileName()
{
	return CvPreGame::loadFileName();
}
// TODO: Phase1 CvDllPreGame::loadFromIni — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::loadFromIni(FIGameIniParser& iniParser)
{
	CvPreGame::loadFromIni(iniParser);
}
// TODO: Phase1 CvDllPreGame::mapNoPlayers — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::mapNoPlayers()
{
	return CvPreGame::mapNoPlayers();
}
// TODO: Phase1 CvDllPreGame::mapRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
unsigned int CvDllPreGame::mapRandomSeed()
{
	return CvPreGame::mapRandomSeed();
}
// TODO: Phase1 CvDllPreGame::loadWBScenario — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::loadWBScenario()
{
	return CvPreGame::loadWBScenario();
}
// TODO: Phase1 CvDllPreGame::overrideScenarioHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::overrideScenarioHandicap()
{
	return CvPreGame::overrideScenarioHandicap();
}
// TODO: Phase1 CvDllPreGame::mapScriptName — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::mapScriptName()
{
	return CvPreGame::mapScriptName();
}
// TODO: Phase1 CvDllPreGame::maxCityElimination — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::maxCityElimination()
{
	return CvPreGame::maxCityElimination();
}
// TODO: Phase1 CvDllPreGame::maxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::maxTurns()
{
	return CvPreGame::maxTurns();
}
// TODO: Phase1 CvDllPreGame::minorCivType — UNVERIFIED: Full operand and relocation-target comparison not established.
MinorCivTypes CvDllPreGame::minorCivType(PlayerTypes p)
{
	return CvPreGame::minorCivType(p);
}
// TODO: Phase1 CvDllPreGame::multiplayerAIEnabled — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::multiplayerAIEnabled()
{
	return CvPreGame::multiplayerAIEnabled();
}
// TODO: Phase1 CvDllPreGame::netID — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::netID(PlayerTypes p)
{
	return CvPreGame::netID(p);
}
// TODO: Phase1 CvDllPreGame::nickname — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::nickname(PlayerTypes p)
{
	return CvPreGame::nickname(p);
}
// TODO: Phase1 CvDllPreGame::nicknameDisplayed — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString CvDllPreGame::nicknameDisplayed(PlayerTypes p)
{
	return CvPreGame::nicknameDisplayed(p);
}
// TODO: Phase1 CvDllPreGame::numMinorCivs — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::numMinorCivs()
{
	return CvPreGame::numMinorCivs();
}
// TODO: Phase1 CvDllPreGame::playerColor — UNVERIFIED: Full operand and relocation-target comparison not established.
PlayerColorTypes CvDllPreGame::playerColor(PlayerTypes p)
{
	return CvPreGame::playerColor(p);
}
// TODO: Phase1 CvDllPreGame::privateGame — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::privateGame()
{
	return CvPreGame::privateGame();
}
// TODO: Phase1 CvDllPreGame::quickCombat — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::quickCombat()
{
	return CvPreGame::quickCombat();
}
// TODO: Phase1 CvDllPreGame::quickMovement — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::quickMovement()
{
	return CvPreGame::quickMovement();
}
// TODO: Phase1 CvDllPreGame::quickstart — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::quickstart()
{
	return CvPreGame::quickstart();
}
// TODO: Phase1 CvDllPreGame::randomWorldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::randomWorldSize()
{
	return CvPreGame::randomWorldSize();
}
// TODO: Phase1 CvDllPreGame::randomMapScript — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::randomMapScript()
{
	return CvPreGame::randomMapScript();
}
// TODO: Phase1 CvDllPreGame::read — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::read(FDataStream& loadFrom)
{
	CvPreGame::read(loadFrom);
}
// TODO: Phase1 CvDllPreGame::readPlayerSlotInfo — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::readPlayerSlotInfo(FDataStream& loadFrom)
{
	return CvPreGame::readPlayerSlotInfo(loadFrom);
}
// TODO: Phase1 CvDllPreGame::resetGame — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::resetGame()
{
	CvPreGame::resetGame();
}
// TODO: Phase1 CvDllPreGame::ResetGameOptions — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::ResetGameOptions()
{
	CvPreGame::ResetGameOptions();
}
// TODO: Phase1 CvDllPreGame::ResetMapOptions — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::ResetMapOptions()
{
	CvPreGame::ResetMapOptions();
}
// TODO: Phase1 CvDllPreGame::resetPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::resetPlayer(PlayerTypes p)
{
	CvPreGame::resetPlayer(p);
}
// TODO: Phase1 CvDllPreGame::resetPlayers — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::resetPlayers()
{
	CvPreGame::resetPlayers();
}
// TODO: Phase1 CvDllPreGame::resetSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::resetSlots()
{
	CvPreGame::resetSlots();
}
// TODO: Phase1 CvDllPreGame::restoreSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::restoreSlots()
{
	CvPreGame::restoreSlots();
}
// TODO: Phase1 CvDllPreGame::saveSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::saveSlots()
{
	CvPreGame::saveSlots();
}
// TODO: Phase1 CvDllPreGame::seaLevel — UNVERIFIED: Full operand and relocation-target comparison not established.
SeaLevelTypes CvDllPreGame::seaLevel()
{
	return CvPreGame::seaLevel();
}
// TODO: Phase1 CvDllPreGame::setActivePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setActivePlayer(PlayerTypes p)
{
	CvPreGame::setActivePlayer(p);
}
// TODO: Phase1 CvDllPreGame::setAdminPassword — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setAdminPassword(const CvString& p)
{
	CvPreGame::setAdminPassword(p);
}
// TODO: Phase1 CvDllPreGame::setAdvancedStartPoints — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setAdvancedStartPoints(int a)
{
	CvPreGame::setAdvancedStartPoints(a);
}
// TODO: Phase1 CvDllPreGame::setAlias — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setAlias(const CvString& a)
{
	CvPreGame::setAlias(a);
}
// TODO: Phase1 CvDllPreGame::setAutorun — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setAutorun(bool isAutoStart)
{
	CvPreGame::setAutorun(isAutoStart);
}
// TODO: Phase1 CvDllPreGame::setAutorunTurnDelay — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setAutorunTurnDelay(float turnDelay)
{
	CvPreGame::setAutorunTurnDelay(turnDelay);
}
// TODO: Phase1 CvDllPreGame::setAutorunTurnLimit — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setAutorunTurnLimit(int turnLimit)
{
	CvPreGame::setAutorunTurnLimit(turnLimit);
}
// TODO: Phase1 CvDllPreGame::setBandwidth — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setBandwidth(BandwidthType b)
{
	CvPreGame::setBandwidth(b);
}
// TODO: Phase1 CvDllPreGame::setBandwidth — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setBandwidth(const CvString& b)
{
	CvPreGame::setBandwidth(b);
}
// TODO: Phase1 CvDllPreGame::setCalendar — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCalendar(CalendarTypes c)
{
	CvPreGame::setCalendar(c);
}
// TODO: Phase1 CvDllPreGame::setCalendar — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCalendar(const CvString& c)
{
	CvPreGame::setCalendar(c);
}
// TODO: Phase1 CvDllPreGame::setCivilization — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCivilization(PlayerTypes p, CivilizationTypes c)
{
	CvPreGame::setCivilization(p, c);
}
// TODO: Phase1 CvDllPreGame::setCivilizationAdjective — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCivilizationAdjective(PlayerTypes p, const CvString& a)
{
	CvPreGame::setCivilizationAdjective(p, a);
}
// TODO: Phase1 CvDllPreGame::setCivilizationDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCivilizationDescription(PlayerTypes p, const CvString& d)
{
	CvPreGame::setCivilizationDescription(p, d);
}
// TODO: Phase1 CvDllPreGame::setCivilizationPassword — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCivilizationPassword(PlayerTypes p, const CvString& pwd)
{
	CvPreGame::setCivilizationPassword(p, pwd);
}
// TODO: Phase1 CvDllPreGame::setCivilizationShortDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCivilizationShortDescription(PlayerTypes p, const CvString& d)
{
	CvPreGame::setCivilizationShortDescription(p, d);
}
// TODO: Phase1 CvDllPreGame::setCivilizationKey — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCivilizationKey(PlayerTypes p, const CvString& d)
{
	CvPreGame::setCivilizationKey(p, d);
}
// TODO: Phase1 CvDllPreGame::setCivilizationKeyPackageID — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setCivilizationKeyPackageID(PlayerTypes p, const GUID& kKey)
{
	CvPreGame::setCivilizationKeyPackageID(p, kKey);
}
// TODO: Phase1 CvDllPreGame::setClimate — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setClimate(ClimateTypes c)
{
	CvPreGame::setClimate(c);
}
// TODO: Phase1 CvDllPreGame::setClimate — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setClimate(const CvString& c)
{
	CvPreGame::setClimate(c);
}
// TODO: Phase1 CvDllPreGame::setCustomWorldSize — MISMATCH: Current relocations reference target-absent imports: _ZN9CvPreGame18setCustomWorldSizeEiiii.
void CvDllPreGame::setCustomWorldSize(int iWidth, int iHeight, int iPlayers, int iMinorCivs)
{
	CvPreGame::setCustomWorldSize(iWidth, iHeight, iPlayers, iMinorCivs);
}
// TODO: Phase1 CvDllPreGame::setDLCAllowed — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setDLCAllowed(const GUID& kDLCID, bool bState)
{
	CvPreGame::setDLCAllowed(kDLCID, bState);
}
// TODO: Phase1 CvDllPreGame::setEarthMap — UNVERIFIED: Exact body matches only with existing PCH preinclude; direct current translation unit compilation fails.
void CvDllPreGame::setEarthMap(bool bIsEarthMap)
{
	//This function is no longer used, it only exists for interface compatibility.
}
// TODO: Phase1 CvDllPreGame::setEmailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setEmailAddress(PlayerTypes p, const CvString& a)
{
	CvPreGame::setEmailAddress(p, a);
}
// TODO: Phase1 CvDllPreGame::setEmailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setEmailAddress(const CvString& a)
{
	CvPreGame::setEmailAddress(a);
}
// TODO: Phase1 CvDllPreGame::setEndTurnTimerLength — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setEndTurnTimerLength(float f)
{
	CvPreGame::setEndTurnTimerLength(f);
}
// TODO: Phase1 CvDllPreGame::setEra — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setEra(EraTypes e)
{
	CvPreGame::setEra(e);
}
// TODO: Phase1 CvDllPreGame::setEra — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setEra(const CvString& e)
{
	CvPreGame::setEra(e);
}
// TODO: Phase1 CvDllPreGame::setGameMode — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameMode(GameMode g)
{
	CvPreGame::setGameMode(g);
}
// TODO: Phase1 CvDllPreGame::setGameName — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameName(const CvString& g)
{
	CvPreGame::setGameName(g);
}
// TODO: Phase1 CvDllPreGame::setGameSpeed — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameSpeed(GameSpeedTypes g)
{
	CvPreGame::setGameSpeed(g);
}
// TODO: Phase1 CvDllPreGame::setGameSpeed — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameSpeed(const CvString& g)
{
	CvPreGame::setGameSpeed(g);
}
// TODO: Phase1 CvDllPreGame::setGameStarted — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameStarted(bool bStarted)
{
	CvPreGame::setGameStarted(bStarted);
}
// TODO: Phase1 CvDllPreGame::setGameTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameTurn(int turn)
{
	CvPreGame::setGameTurn(turn);
}
// TODO: Phase1 CvDllPreGame::SetGameOption — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::SetGameOption(const char* szOptionName, int iValue)
{
	return CvPreGame::SetGameOption(szOptionName, iValue);
}
// TODO: Phase1 CvDllPreGame::SetGameOption — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::SetGameOption(GameOptionTypes eOption, int iValue)
{
	return CvPreGame::SetGameOption(eOption, iValue);
}
// TODO: Phase1 CvDllPreGame::setGameType — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameType(GameTypes g)
{
	CvPreGame::setGameType(g);
}
// TODO: Phase1 CvDllPreGame::setGameType — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameType(GameTypes g, GameStartTypes eStartType)
{
	CvPreGame::setGameType(g, eStartType);
}
// TODO: Phase1 CvDllPreGame::setGameType — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameType(const CvString& g)
{
	CvPreGame::setGameType(g);
}
// TODO: Phase1 CvDllPreGame::setGameStartType — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameStartType(GameStartTypes g)
{
	CvPreGame::setGameStartType(g);
}
// TODO: Phase1 CvDllPreGame::setGameUpdateTime — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameUpdateTime(int updateTime)
{
	CvPreGame::setGameUpdateTime(updateTime);
}
// TODO: Phase1 CvDllPreGame::setHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setHandicap(PlayerTypes p, HandicapTypes h)
{
	CvPreGame::setHandicap(p, h);
}
// TODO: Phase1 CvDllPreGame::setInternetGame — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setInternetGame(bool isInternetGame)
{
	CvPreGame::setInternetGame(isInternetGame);
}
// TODO: Phase1 CvDllPreGame::setLeaderHead — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLeaderHead(PlayerTypes p, LeaderHeadTypes l)
{
	CvPreGame::setLeaderHead(p, l);
}
// TODO: Phase1 CvDllPreGame::setLeaderName — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLeaderName(PlayerTypes p, const CvString& n)
{
	CvPreGame::setLeaderName(p, n);
}
// TODO: Phase1 CvDllPreGame::setLeaderKey — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLeaderKey(PlayerTypes p, const CvString& n)
{
	CvPreGame::setLeaderKey(p, n);
}
// TODO: Phase1 CvDllPreGame::setLeaderKeyPackageID — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLeaderKeyPackageID(PlayerTypes p, const GUID& n)
{
	CvPreGame::setLeaderKeyPackageID(p, n);
}
// TODO: Phase1 CvDllPreGame::setLoadFileName — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLoadFileName(const CvString& fileName)
{
	CvPreGame::setLoadFileName(fileName);
}
// TODO: Phase1 CvDllPreGame::setMapNoPlayers — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setMapNoPlayers(bool p)
{
	CvPreGame::setMapNoPlayers(p);
}
// TODO: Phase1 CvDllPreGame::setMapRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setMapRandomSeed(unsigned int newSeed)
{
	CvPreGame::setMapRandomSeed(newSeed);
}
// TODO: Phase1 CvDllPreGame::setLoadWBScenario — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLoadWBScenario(bool b)
{
	CvPreGame::setLoadWBScenario(b);
}
// TODO: Phase1 CvDllPreGame::setOverrideScenarioHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setOverrideScenarioHandicap(bool b)
{
	CvPreGame::setOverrideScenarioHandicap(b);
}
// TODO: Phase1 CvDllPreGame::setMapScriptName — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setMapScriptName(const CvString& s)
{
	CvPreGame::setMapScriptName(s);
}
// TODO: Phase1 CvDllPreGame::SetMapOption — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::SetMapOption(const char* szOptionName, int iValue)
{
	return CvPreGame::SetMapOption(szOptionName, iValue);
}
//bool CvDllPreGame::SetMapOptions(const std::vector<CustomOption>& mapOptions)
//{
//	CvPreGame::SetMapOptions();
//}
// TODO: Phase1 CvDllPreGame::setMaxCityElimination — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setMaxCityElimination(int m)
{
	CvPreGame::setMaxCityElimination(m);
}
// TODO: Phase1 CvDllPreGame::setMaxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setMaxTurns(int maxTurns)
{
	CvPreGame::setMaxTurns(maxTurns);
}
// TODO: Phase1 CvDllPreGame::setMinorCivType — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setMinorCivType(PlayerTypes p, MinorCivTypes m)
{
	CvPreGame::setMinorCivType(p, m);
}
// TODO: Phase1 CvDllPreGame::setMinorCiv — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setMinorCiv(PlayerTypes p, bool isMinor)
{
	CvPreGame::setMinorCiv(p, isMinor);
}
// TODO: Phase1 CvDllPreGame::setMultiplayerAIEnabled — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setMultiplayerAIEnabled(bool isEnabled)
{
	CvPreGame::setMultiplayerAIEnabled(isEnabled);
}
// TODO: Phase1 CvDllPreGame::setNetID — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setNetID(PlayerTypes p, int id)
{
	CvPreGame::setNetID(p, id);
}
// TODO: Phase1 CvDllPreGame::setNickname — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setNickname(PlayerTypes p, const CvString& n)
{
	CvPreGame::setNickname(p, n);
}
// TODO: Phase1 CvDllPreGame::setNumMinorCivs — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setNumMinorCivs(int n)
{
	CvPreGame::setNumMinorCivs(n);
}
// TODO: Phase1 CvDllPreGame::setPersistSettings — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setPersistSettings(bool bPersist)
{
	CvPreGame::setPersistSettings(bPersist);
}
// TODO: Phase1 CvDllPreGame::setPlayable — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setPlayable(PlayerTypes p, bool playable)
{
	CvPreGame::setPlayable(p, playable);
}
// TODO: Phase1 CvDllPreGame::setPlayerColor — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setPlayerColor(PlayerTypes p, PlayerColorTypes c)
{
	CvPreGame::setPlayerColor(p, c);
}
// TODO: Phase1 CvDllPreGame::setPrivateGame — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setPrivateGame(bool isPrivateGame)
{
	CvPreGame::setPrivateGame(isPrivateGame);
}
// TODO: Phase1 CvDllPreGame::setQuickCombat — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setQuickCombat(bool isQuickCombat)
{
	CvPreGame::setQuickCombat(isQuickCombat);
}
// TODO: Phase1 CvDllPreGame::setQuickMovement — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setQuickMovement(bool isQuickMovement)
{
	CvPreGame::setQuickMovement(isQuickMovement);
}
// TODO: Phase1 CvDllPreGame::setQuickHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setQuickHandicap(HandicapTypes h)
{
	CvPreGame::setQuickHandicap(h);
}
// TODO: Phase1 CvDllPreGame::setQuickHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setQuickHandicap(const CvString& h)
{
	CvPreGame::setQuickHandicap(h);
}
// TODO: Phase1 CvDllPreGame::setQuickstart — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setQuickstart(bool isQuickStart)
{
	CvPreGame::setQuickstart(isQuickStart);
}
// TODO: Phase1 CvDllPreGame::setRandomWorldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setRandomWorldSize(bool isRandomWorldSize)
{
	CvPreGame::setRandomWorldSize(isRandomWorldSize);
}
// TODO: Phase1 CvDllPreGame::setRandomMapScript — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setRandomMapScript(bool isRandomWorldScript)
{
	CvPreGame::setRandomMapScript(isRandomWorldScript);
}
// TODO: Phase1 CvDllPreGame::setReady — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setReady(PlayerTypes p, bool bIsReady)
{
	CvPreGame::setReady(p, bIsReady);
}
// TODO: Phase1 CvDllPreGame::setSeaLevel — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setSeaLevel(SeaLevelTypes s)
{
	CvPreGame::setSeaLevel(s);
}
// TODO: Phase1 CvDllPreGame::setSeaLevel — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setSeaLevel(const CvString& s)
{
	CvPreGame::setSeaLevel(s);
}
// TODO: Phase1 CvDllPreGame::setSlotClaim — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setSlotClaim(PlayerTypes p, SlotClaim c)
{
	CvPreGame::setSlotClaim(p, c);
}
// TODO: Phase1 CvDllPreGame::setSlotStatus — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setSlotStatus(PlayerTypes eID, SlotStatus eSlotStatus)
{
	CvPreGame::setSlotStatus(eID, eSlotStatus);
}
// TODO: Phase1 CvDllPreGame::setSyncRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setSyncRandomSeed(unsigned int newSeed)
{
	CvPreGame::setSyncRandomSeed(newSeed);
}
// TODO: Phase1 CvDllPreGame::setTeamType — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setTeamType(PlayerTypes p, TeamTypes t)
{
	CvPreGame::setTeamType(p, t);
}
// TODO: Phase1 CvDllPreGame::setTransferredMap — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setTransferredMap(bool transferred)
{
	CvPreGame::setTransferredMap(transferred);
}
// TODO: Phase1 CvDllPreGame::setTurnTimer — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setTurnTimer(TurnTimerTypes t)
{
	CvPreGame::setTurnTimer(t);
}
// TODO: Phase1 CvDllPreGame::setTurnTimer — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setTurnTimer(const CvString& t)
{
	CvPreGame::setTurnTimer(t);
}
// TODO: Phase1 CvDllPreGame::SetCityScreenBlocked — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::SetCityScreenBlocked(bool bCityScreenBlocked)
{
	CvPreGame::SetCityScreenBlocked(bCityScreenBlocked);
}
// TODO: Phase1 CvDllPreGame::setVersionString — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setVersionString(const std::string& v)
{
	CvPreGame::setVersionString(v);
}
// TODO: Phase1 CvDllPreGame::setVictory — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setVictory(VictoryTypes v, bool isValid)
{
	CvPreGame::setVictory(v, isValid);
}
// TODO: Phase1 CvDllPreGame::setVictories — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setVictories(const std::vector<bool>& v)
{
	CvPreGame::setVictories(v);
}
// TODO: Phase1 CvDllPreGame::setWhiteFlag — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setWhiteFlag(PlayerTypes p, bool flag)
{
	CvPreGame::setWhiteFlag(p, flag);
}
// TODO: Phase1 CvDllPreGame::setWorldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setWorldSize(WorldSizeTypes w, bool bResetSlots)
{
	CvPreGame::setWorldSize(w, bResetSlots);
}
// TODO: Phase1 CvDllPreGame::setWorldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setWorldSize(const CvString& w)
{
	CvPreGame::setWorldSize(w);
}
// TODO: Phase1 CvDllPreGame::slotClaim — UNVERIFIED: Full operand and relocation-target comparison not established.
SlotClaim CvDllPreGame::slotClaim(PlayerTypes p)
{
	return CvPreGame::slotClaim(p);
}
// TODO: Phase1 CvDllPreGame::slotStatus — UNVERIFIED: Full operand and relocation-target comparison not established.
SlotStatus CvDllPreGame::slotStatus(PlayerTypes eID)
{
	return CvPreGame::slotStatus(eID);
}
// TODO: Phase1 CvDllPreGame::syncRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
unsigned int CvDllPreGame::syncRandomSeed()
{
	return CvPreGame::syncRandomSeed();
}
// TODO: Phase1 CvDllPreGame::transferredMap — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::transferredMap()
{
	return CvPreGame::transferredMap();
}
// TODO: Phase1 CvDllPreGame::teamType — UNVERIFIED: Full operand and relocation-target comparison not established.
TeamTypes CvDllPreGame::teamType(PlayerTypes p)
{
	return static_cast<unsigned int>(p) < 64 ? (*CvPreGame::sr_TeamTypes)[p] : NO_TEAM;
}
// TODO: Phase1 CvDllPreGame::turnTimer — UNVERIFIED: Full operand and relocation-target comparison not established.
TurnTimerTypes CvDllPreGame::turnTimer()
{
	return CvPreGame::turnTimer();
}
// TODO: Phase1 CvDllPreGame::versionString — UNVERIFIED: Full operand and relocation-target comparison not established.
const std::string CvDllPreGame::versionString()
{
	return CvPreGame::versionString();
}
// TODO: Phase1 CvDllPreGame::worldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
WorldSizeTypes CvDllPreGame::worldSize()
{
	return CvPreGame::worldSize();
}
// TODO: Phase1 CvDllPreGame::GetWorldInfo — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvWorldInfo1* CvDllPreGame::GetWorldInfo()
{
	const CvWorldInfo& kWorldInfo = CvPreGame::worldInfo();
	const CvWorldInfo* pWorldInfo = &(kWorldInfo);
	return new CvDllWorldInfo(const_cast<CvWorldInfo*>(pWorldInfo));
}
// TODO: Phase1 CvDllPreGame::write — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::write(FDataStream& saveTo)
{
	CvPreGame::write(saveTo);
}
// TODO: Phase1 CvDllPreGame::getActiveSlotCount — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::getActiveSlotCount()
{
	return CvPreGame::getActiveSlotCount();
}
// TODO: Phase1 CvDllPreGame::readActiveSlotCountFromSaveGame — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::readActiveSlotCountFromSaveGame(FDataStream& loadFrom)
{
	return CvPreGame::readActiveSlotCountFromSaveGame(loadFrom);
}
// TODO: Phase1 CvDllPreGame::LoadFileStorage — UNVERIFIED: Full operand and relocation-target comparison not established.
StorageLocation CvDllPreGame::LoadFileStorage()
{
	return CvPreGame::loadFileStorage();
}
// TODO: Phase1 CvDllPreGame::SetLoadFileName — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
void CvDllPreGame::SetLoadFileName(const char* szFileName, StorageLocation eStorage)
{
	CvString strFileName = szFileName;
	CvPreGame::setLoadFileName(strFileName, eStorage);
}
// TODO: Phase1 CvDllPreGame::GetDLCAllowed — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvEnumerator* CvDllPreGame::GetDLCAllowed()
{
	return new CvDllDlcPackageInfoList(CvPreGame::getDLCAllowed());
}
// TODO: Phase1 CvDllPreGame::GetDLCAvailable — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvEnumerator* CvDllPreGame::GetDLCAvailable(PlayerTypes p)
{
	return new CvDllDlcPackageInfoList(CvPreGame::getDLCAvailable(p));
}
// TODO: Phase1 CvDllPreGame::SetDLCAvailable — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
void CvDllPreGame::SetDLCAvailable(PlayerTypes p, ICvEnumerator* pList)
{
	PackageIDList kDLCList;

	std::auto_ptr<ICvEnumerator> enumerator(pList->QueryInterface<ICvEnumerator>());
	while(enumerator.get() != NULL && enumerator->MoveNext())
	{
		ICvDlcPackageInfo1* package = NULL;
		{
			std::auto_ptr<ICvUnknown> current(enumerator->GetCurrent());
			if(current.get() != NULL)
				package = current->QueryInterface<ICvDlcPackageInfo1>();
		}
		std::auto_ptr<ICvDlcPackageInfo1> packageInfo(package);
		if(packageInfo.get() != NULL)
			kDLCList.push_back(packageInfo->GetPackageID());
	}

	CvPreGame::setDLCAvailable(p, kDLCList);
}
// TODO: Phase1 CvDllPreGame::pitBossTurnTime — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::pitBossTurnTime()
{
	return CvPreGame::pitBossTurnTime();
}
// TODO: Phase1 CvDllPreGame::setPitBossTurnTime — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setPitBossTurnTime(int turnTime)
{
	CvPreGame::setPitBossTurnTime(turnTime);
}
// TODO: Phase1 CvDllPreGame::isTurnNotifySteamInvite — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isTurnNotifySteamInvite(PlayerTypes p) const
{
	return CvPreGame::isTurnNotifySteamInvite(p);
}
// TODO: Phase1 CvDllPreGame::setTurnNotifySteamInvite — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setTurnNotifySteamInvite(PlayerTypes p, bool wantsSteamInvite)
{
	CvPreGame::setTurnNotifySteamInvite(p, wantsSteamInvite);
}
// TODO: Phase1 CvDllPreGame::isTurnNotifyEmail — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isTurnNotifyEmail(PlayerTypes p) const
{
	return CvPreGame::isTurnNotifyEmail(p);
}
// TODO: Phase1 CvDllPreGame::setTurnNotifyEmail — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setTurnNotifyEmail(PlayerTypes p, bool wantsEmail)
{
	CvPreGame::setTurnNotifyEmail(p, wantsEmail);
}
// TODO: Phase1 CvDllPreGame::getTurnNotifyEmailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
const CvString& CvDllPreGame::getTurnNotifyEmailAddress(PlayerTypes p) const
{
	return CvPreGame::getTurnNotifyEmailAddress(p);
}
// TODO: Phase1 CvDllPreGame::setTurnNotifyEmailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setTurnNotifyEmailAddress(PlayerTypes p, const CvString& emailAddress)
{
	CvPreGame::setTurnNotifyEmailAddress(p, emailAddress);
}
// TODO: Phase1 CvDllPreGame::VerifyHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::VerifyHandicap(PlayerTypes p)
{
	CvPreGame::VerifyHandicap(p);
}
// TODO: Phase1 CvDllPreGame::ReseatConnectedPlayers — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::ReseatConnectedPlayers()
{
	CvPreGame::ReseatConnectedPlayers();
}



// TODO: Phase1 CvDllPreGame::loadoutCargo — UNVERIFIED: Full operand and relocation-target comparison not established.
CargoTypes CvDllPreGame::loadoutCargo(PlayerTypes p)
{
	return CvPreGame::loadoutCargo(p);
}
// TODO: Phase1 CvDllPreGame::loadoutColonist — UNVERIFIED: Full operand and relocation-target comparison not established.
ColonistTypes CvDllPreGame::loadoutColonist(PlayerTypes p)
{
	return CvPreGame::loadoutColonist(p);
}
// TODO: Phase1 CvDllPreGame::loadoutSpacecraft — UNVERIFIED: Full operand and relocation-target comparison not established.
SpacecraftTypes CvDllPreGame::loadoutSpacecraft(PlayerTypes p)
{
	return CvPreGame::loadoutSpacecraft(p);
}
// TODO: Phase1 CvDllPreGame::FillEmptyLoadoutSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::FillEmptyLoadoutSlots(PlayerTypes p)
{
	CvPreGame::FillEmptyLoadoutSlots(p);
}
// TODO: Phase1 CvDllPreGame::initialMaxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::initialMaxTurns() const
{
	return CvPreGame::initialMaxTurns();
}
// TODO: Phase1 CvDllPreGame::planet — UNVERIFIED: Full operand and relocation-target comparison not established.
PlanetTypes CvDllPreGame::planet()
{
	return CvPreGame::planet();
}
// TODO: Phase1 CvDllPreGame::getNumPlanets — UNVERIFIED: Full operand and relocation-target comparison not established.
int CvDllPreGame::getNumPlanets()
{
	return CvPreGame::getNumPlanets();
}
// TODO: Phase1 CvDllPreGame::getPlanetFileName — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllPreGame::getPlanetFileName()
{
	return CvPreGame::getPlanetFileName();
}
// TODO: Phase1 CvDllPreGame::getPlanetFileName — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllPreGame::getPlanetFileName(PlanetTypes p)
{
	return CvPreGame::getPlanetFileName(p);
}
// TODO: Phase1 CvDllPreGame::getGameID — UNVERIFIED: Full operand and relocation-target comparison not established.
const unsigned long long CvDllPreGame::getGameID()
{
	return CvPreGame::getGameID();
}
// TODO: Phase1 CvDllPreGame::getRandomMapScript — UNVERIFIED: Full operand and relocation-target comparison not established.
const char* CvDllPreGame::getRandomMapScript()
{
	return CvPreGame::getRandomMapScript();
}
// TODO: Phase1 CvDllPreGame::getMapRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
unsigned int CvDllPreGame::getMapRandomSeed()
{
	return CvPreGame::mapRandomSeed();
}
// TODO: Phase1 CvDllPreGame::setLoadoutCargo — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLoadoutCargo(PlayerTypes p, CargoTypes c)
{
	CvPreGame::setLoadoutCargo(p, c);
}
// TODO: Phase1 CvDllPreGame::setLoadoutColonist — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLoadoutColonist(PlayerTypes p, ColonistTypes c)
{
	CvPreGame::setLoadoutColonist(p, c);
}
// TODO: Phase1 CvDllPreGame::setLoadoutSpacecraft — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setLoadoutSpacecraft(PlayerTypes p, SpacecraftTypes c)
{
	CvPreGame::setLoadoutSpacecraft(p, c);
}
// TODO: Phase1 CvDllPreGame::setInitialMaxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setInitialMaxTurns(int maxTurns)
{
	CvPreGame::setInitialMaxTurns(maxTurns);
}
// TODO: Phase1 CvDllPreGame::setPlanet — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setPlanet(PlanetTypes p)
{
	CvPreGame::setPlanet(p);
}
// TODO: Phase1 CvDllPreGame::setGameID — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setGameID(unsigned long long id)
{
	CvPreGame::setGameID(id);
}
// TODO: Phase1 CvDllPreGame::GetDLCAllowedCount — UNVERIFIED: Full operand and relocation-target comparison not established.
unsigned int CvDllPreGame::GetDLCAllowedCount()
{
	return CvPreGame::getDLCAllowedCount();
}
// TODO: Phase1 CvDllPreGame::GetDLCAvailableCount — UNVERIFIED: Full operand and relocation-target comparison not established.
unsigned int CvDllPreGame::GetDLCAvailableCount(PlayerTypes p)
{
	return CvPreGame::getDLCAvailableCount(p);
}
// TODO: Phase1 CvDllPreGame::setUsingFirstTimeUserExperience — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllPreGame::setUsingFirstTimeUserExperience(bool value)
{
	CvPreGame::setUsingFirstTimeUserExperience(value);
}
// TODO: Phase1 CvDllPreGame::isUsingFirstTimeUserExperience — UNVERIFIED: Full operand and relocation-target comparison not established.
bool CvDllPreGame::isUsingFirstTimeUserExperience()
{
	return CvPreGame::isUsingFirstTimeUserExperience();
}
