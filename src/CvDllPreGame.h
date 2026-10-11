#pragma once

#include "CvDllInterfaces.h"

class FIGameIniParser;

class CvDllPreGame : public ICvPreGame1
{
public:
	// TODO: Phase1 CvDllPreGame::CvDllPreGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvDllPreGame();
	// TODO: Phase1 CvDllPreGame::~CvDllPreGame — UNVERIFIED: Exact body matches only with existing PCH preinclude; direct current translation unit compilation fails.
	~CvDllPreGame();

	// TODO: Phase1 CvDllPreGame::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
	void* DLLCALL QueryInterface(GUID guidInterface);

	// TODO: Phase1 CvDllPreGame::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
	static void operator delete(void* p);
	// TODO: Phase1 CvDllPreGame::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
	static void* operator new(size_t bytes);


	// TODO: Phase1 CvDllPreGame::activePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	PlayerTypes DLLCALL activePlayer();
	// TODO: Phase1 CvDllPreGame::advancedStartPoints — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL advancedStartPoints();
	// TODO: Phase1 CvDllPreGame::autorun — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL autorun();
	// TODO: Phase1 CvDllPreGame::autorunTurnDelay — UNVERIFIED: Full operand and relocation-target comparison not established.
	float DLLCALL autorunTurnDelay();
	// TODO: Phase1 CvDllPreGame::autorunTurnLimit — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL autorunTurnLimit();
	// TODO: Phase1 CvDllPreGame::calendar — UNVERIFIED: Full operand and relocation-target comparison not established.
	CalendarTypes DLLCALL calendar();
	// TODO: Phase1 CvDllPreGame::canReadyLocalPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL canReadyLocalPlayer();
	// TODO: Phase1 CvDllPreGame::civilizationAdjective — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvString DLLCALL civilizationAdjective(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationAdjectiveKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL civilizationAdjectiveKey(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvString DLLCALL civilizationDescription(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationDescriptionKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL civilizationDescriptionKey(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilization — UNVERIFIED: Full operand and relocation-target comparison not established.
	CivilizationTypes DLLCALL civilization(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationPassword — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL civilizationPassword(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationShortDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvString DLLCALL civilizationShortDescription(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationShortDescriptionKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL civilizationShortDescriptionKey(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL civilizationKey(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationKeyAvailable — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL civilizationKeyAvailable(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::civilizationKeyPackageID — UNVERIFIED: Full operand and relocation-target comparison not established.
	const GUID DLLCALL  civilizationKeyPackageID(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::clearDLCAllowed — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL clearDLCAllowed();
	// TODO: Phase1 CvDllPreGame::climate — UNVERIFIED: Full operand and relocation-target comparison not established.
	ClimateTypes DLLCALL climate();
	// TODO: Phase1 CvDllPreGame::closeAllSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL closeAllSlots();
	// TODO: Phase1 CvDllPreGame::closeInactiveSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL closeInactiveSlots();
	// TODO: Phase1 CvDllPreGame::emailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL emailAddress(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::emailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL emailAddress();
	// TODO: Phase1 CvDllPreGame::endTurnTimerLength — UNVERIFIED: Full operand and relocation-target comparison not established.
	float DLLCALL endTurnTimerLength();
	// TODO: Phase1 CvDllPreGame::era — UNVERIFIED: Full operand and relocation-target comparison not established.
	EraTypes DLLCALL era();
	// TODO: Phase1 CvDllPreGame::findPlayerByNickname — UNVERIFIED: Full operand and relocation-target comparison not established.
	PlayerTypes DLLCALL findPlayerByNickname(const char* const name);
	// TODO: Phase1 CvDllPreGame::gameMode — UNVERIFIED: Full operand and relocation-target comparison not established.
	GameMode DLLCALL gameMode();
	// TODO: Phase1 CvDllPreGame::gameName — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL  gameName();
	// TODO: Phase1 CvDllPreGame::gameStarted — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL gameStarted();
	// TODO: Phase1 CvDllPreGame::GetGameOptionCount — UNVERIFIED: Full operand and relocation-target comparison not established.
	uint DLLCALL GetGameOptionCount();
	// TODO: Phase1 CvDllPreGame::GetGameOption — UNVERIFIED: Overloads have differing audit results; complete signature-specific comparison remains necessary.
	bool DLLCALL GetGameOption(uint uiIndex, char* szOptionNameBuffer, uint nOptionNameBufferSize, int& iValue);
	// TODO: Phase1 CvDllPreGame::GetGameOption — UNVERIFIED: Overloads have differing audit results; complete signature-specific comparison remains necessary.
	bool DLLCALL GetGameOption(const char* szOptionName, int& iValue);
	// TODO: Phase1 CvDllPreGame::GetGameOption — UNVERIFIED: Overloads have differing audit results; complete signature-specific comparison remains necessary.
	bool DLLCALL GetGameOption(GameOptionTypes eOption, int& iValue);
	// TODO: Phase1 CvDllPreGame::GetMapOptionCount — UNVERIFIED: Full operand and relocation-target comparison not established.
	uint DLLCALL GetMapOptionCount();
	// TODO: Phase1 CvDllPreGame::GetMapOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL GetMapOption(uint uiIndex, char* szOptionNameBuffer, uint nOptionNameBuffersize, int& iValue);
	// TODO: Phase1 CvDllPreGame::GetMapOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL GetMapOption(const char* szOptionName, int& iValue);
	// TODO: Phase1 CvDllPreGame::GetPersistSettings — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL GetPersistSettings();
	// TODO: Phase1 CvDllPreGame::gameSpeed — UNVERIFIED: Full operand and relocation-target comparison not established.
	GameSpeedTypes DLLCALL gameSpeed();
	// TODO: Phase1 CvDllPreGame::gameTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL gameTurn();
	// TODO: Phase1 CvDllPreGame::gameType — UNVERIFIED: Full operand and relocation-target comparison not established.
	GameTypes DLLCALL gameType();
	// TODO: Phase1 CvDllPreGame::gameStartType — UNVERIFIED: Full operand and relocation-target comparison not established.
	GameStartTypes DLLCALL gameStartType();
	// TODO: Phase1 CvDllPreGame::handicap — UNVERIFIED: Full operand and relocation-target comparison not established.
	HandicapTypes DLLCALL handicap(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::isDLCAllowed — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isDLCAllowed(const GUID& kDLCID);
	// TODO: Phase1 CvDllPreGame::isDLCAvailable — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isDLCAvailable(PlayerTypes p, const GUID& kDLCID);
	// TODO: Phase1 CvDllPreGame::isEarthMap — UNVERIFIED: Exact body matches only with existing PCH preinclude; direct current translation unit compilation fails.
	bool DLLCALL isEarthMap();
	// TODO: Phase1 CvDllPreGame::isHotSeat — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isHotSeat();
	// TODO: Phase1 CvDllPreGame::isHotSeatGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isHotSeatGame();
	// TODO: Phase1 CvDllPreGame::isHuman — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isHuman(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::isInternetGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isInternetGame();
	// TODO: Phase1 CvDllPreGame::isMinorCiv — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isMinorCiv(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::isNetworkMultiplayerGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isNetworkMultiplayerGame();
	// TODO: Phase1 CvDllPreGame::isPitBoss — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isPitBoss();
	// TODO: Phase1 CvDllPreGame::isPlayable — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isPlayable(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::isPlayByEmail — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isPlayByEmail();
	// TODO: Phase1 CvDllPreGame::isReady — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isReady(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::isVictory — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isVictory(VictoryTypes v);
	// TODO: Phase1 CvDllPreGame::isWBMapScript — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isWBMapScript();
	// TODO: Phase1 CvDllPreGame::isWhiteFlag — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isWhiteFlag(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::leaderHead — UNVERIFIED: Full operand and relocation-target comparison not established.
	LeaderHeadTypes DLLCALL leaderHead(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::leaderName — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvString DLLCALL leaderName(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::leaderNameKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL leaderNameKey(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::leaderKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL leaderKey(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::leaderKeyAvailable — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL leaderKeyAvailable(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::leaderKeyPackageID — UNVERIFIED: Full operand and relocation-target comparison not established.
	const GUID DLLCALL leaderKeyPackageID(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::loadFileName — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL loadFileName();
	// TODO: Phase1 CvDllPreGame::loadFromIni — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL loadFromIni(FIGameIniParser& iniParser);
	// TODO: Phase1 CvDllPreGame::loadoutCargo — UNVERIFIED: Full operand and relocation-target comparison not established.
	CargoTypes DLLCALL loadoutCargo(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::loadoutColonist — UNVERIFIED: Full operand and relocation-target comparison not established.
	ColonistTypes DLLCALL loadoutColonist(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::loadoutSpacecraft — UNVERIFIED: Full operand and relocation-target comparison not established.
	SpacecraftTypes DLLCALL loadoutSpacecraft(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::FillEmptyLoadoutSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL FillEmptyLoadoutSlots(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::mapNoPlayers — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL mapNoPlayers();
	// TODO: Phase1 CvDllPreGame::mapRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
	unsigned int DLLCALL mapRandomSeed();
	// TODO: Phase1 CvDllPreGame::loadWBScenario — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL loadWBScenario();
	// TODO: Phase1 CvDllPreGame::overrideScenarioHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL overrideScenarioHandicap();
	// TODO: Phase1 CvDllPreGame::mapScriptName — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL mapScriptName();
	// TODO: Phase1 CvDllPreGame::maxCityElimination — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL maxCityElimination();
	// TODO: Phase1 CvDllPreGame::maxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL maxTurns();
	// TODO: Phase1 CvDllPreGame::initialMaxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL initialMaxTurns() const;
	// TODO: Phase1 CvDllPreGame::minorCivType — UNVERIFIED: Full operand and relocation-target comparison not established.
	MinorCivTypes DLLCALL minorCivType(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::multiplayerAIEnabled — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL multiplayerAIEnabled();
	// TODO: Phase1 CvDllPreGame::netID — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL netID(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::nickname — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL nickname(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::nicknameDisplayed — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString DLLCALL nicknameDisplayed(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::numMinorCivs — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL numMinorCivs();
	// TODO: Phase1 CvDllPreGame::planet — UNVERIFIED: Full operand and relocation-target comparison not established.
	PlanetTypes DLLCALL planet();
	// TODO: Phase1 CvDllPreGame::getNumPlanets — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL getNumPlanets();
	// TODO: Phase1 CvDllPreGame::getPlanetFileName — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* DLLCALL getPlanetFileName();
	// TODO: Phase1 CvDllPreGame::getPlanetFileName — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* DLLCALL getPlanetFileName(PlanetTypes p);
	// TODO: Phase1 CvDllPreGame::getGameID — UNVERIFIED: Full operand and relocation-target comparison not established.
	const unsigned long long DLLCALL getGameID();
	// TODO: Phase1 CvDllPreGame::playerColor — UNVERIFIED: Full operand and relocation-target comparison not established.
	PlayerColorTypes DLLCALL playerColor(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::privateGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL privateGame();
	// TODO: Phase1 CvDllPreGame::quickCombat — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL quickCombat();
	// TODO: Phase1 CvDllPreGame::quickMovement — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL quickMovement();
	// TODO: Phase1 CvDllPreGame::quickstart — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL quickstart();
	// TODO: Phase1 CvDllPreGame::randomWorldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL randomWorldSize();
	// TODO: Phase1 CvDllPreGame::randomMapScript — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL randomMapScript();
	// TODO: Phase1 CvDllPreGame::getRandomMapScript — UNVERIFIED: Full operand and relocation-target comparison not established.
	const char* DLLCALL getRandomMapScript();
	// TODO: Phase1 CvDllPreGame::getMapRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
	unsigned int getMapRandomSeed();
	// TODO: Phase1 CvDllPreGame::read — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL read(FDataStream& loadFrom);
	// TODO: Phase1 CvDllPreGame::readPlayerSlotInfo — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL readPlayerSlotInfo(FDataStream& loadFrom);
	// TODO: Phase1 CvDllPreGame::resetGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL resetGame();
	// TODO: Phase1 CvDllPreGame::ResetGameOptions — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL ResetGameOptions();
	// TODO: Phase1 CvDllPreGame::ResetMapOptions — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL ResetMapOptions();
	// TODO: Phase1 CvDllPreGame::resetPlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL resetPlayer(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::resetPlayers — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL resetPlayers();
	// TODO: Phase1 CvDllPreGame::resetSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL resetSlots();
	// TODO: Phase1 CvDllPreGame::restoreSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL restoreSlots();
	// TODO: Phase1 CvDllPreGame::saveSlots — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL saveSlots();
	// TODO: Phase1 CvDllPreGame::seaLevel — UNVERIFIED: Full operand and relocation-target comparison not established.
	SeaLevelTypes DLLCALL seaLevel();
	// TODO: Phase1 CvDllPreGame::setActivePlayer — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setActivePlayer(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::setAdminPassword — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setAdminPassword(const CvString& p);
	// TODO: Phase1 CvDllPreGame::setAdvancedStartPoints — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setAdvancedStartPoints(int a);
	// TODO: Phase1 CvDllPreGame::setAlias — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setAlias(const CvString& a);
	// TODO: Phase1 CvDllPreGame::setAutorun — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setAutorun(bool isAutoStart);
	// TODO: Phase1 CvDllPreGame::setAutorunTurnDelay — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setAutorunTurnDelay(float turnDelay);
	// TODO: Phase1 CvDllPreGame::setAutorunTurnLimit — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setAutorunTurnLimit(int turnLimit);
	// TODO: Phase1 CvDllPreGame::setBandwidth — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setBandwidth(BandwidthType b);
	// TODO: Phase1 CvDllPreGame::setBandwidth — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setBandwidth(const CvString& b);
	// TODO: Phase1 CvDllPreGame::setCalendar — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCalendar(CalendarTypes c);
	// TODO: Phase1 CvDllPreGame::setCalendar — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCalendar(const CvString& c);
	// TODO: Phase1 CvDllPreGame::setCivilization — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCivilization(PlayerTypes p, CivilizationTypes c);
	// TODO: Phase1 CvDllPreGame::setCivilizationAdjective — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCivilizationAdjective(PlayerTypes p, const CvString& a);
	// TODO: Phase1 CvDllPreGame::setCivilizationDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCivilizationDescription(PlayerTypes p, const CvString& d);
	// TODO: Phase1 CvDllPreGame::setCivilizationPassword — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCivilizationPassword(PlayerTypes p, const CvString& pwd);
	// TODO: Phase1 CvDllPreGame::setCivilizationShortDescription — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCivilizationShortDescription(PlayerTypes p, const CvString& d);
	// TODO: Phase1 CvDllPreGame::setCivilizationKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCivilizationKey(PlayerTypes p, const CvString& d);
	// TODO: Phase1 CvDllPreGame::setCivilizationKeyPackageID — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setCivilizationKeyPackageID(PlayerTypes p, const GUID& kKey);
	// TODO: Phase1 CvDllPreGame::setClimate — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setClimate(ClimateTypes c);
	// TODO: Phase1 CvDllPreGame::setClimate — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setClimate(const CvString& c);
	// TODO: Phase1 CvDllPreGame::setCustomWorldSize — MISMATCH: Current relocations reference target-absent imports: _ZN9CvPreGame18setCustomWorldSizeEiiii.
	void DLLCALL setCustomWorldSize(int iWidth, int iHeight, int iPlayers = 0, int iMinorCivs = 0);
	// TODO: Phase1 CvDllPreGame::setDLCAllowed — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setDLCAllowed(const GUID& kDLCID, bool bState);
	// TODO: Phase1 CvDllPreGame::setEarthMap — UNVERIFIED: Exact body matches only with existing PCH preinclude; direct current translation unit compilation fails.
	void DLLCALL setEarthMap(bool bIsEarthMap);
	// TODO: Phase1 CvDllPreGame::setEmailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setEmailAddress(PlayerTypes p, const CvString& a);
	// TODO: Phase1 CvDllPreGame::setEmailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setEmailAddress(const CvString& a);
	// TODO: Phase1 CvDllPreGame::setEndTurnTimerLength — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setEndTurnTimerLength(float f);
	// TODO: Phase1 CvDllPreGame::setEra — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setEra(EraTypes e);
	// TODO: Phase1 CvDllPreGame::setEra — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setEra(const CvString& e);
	// TODO: Phase1 CvDllPreGame::setGameMode — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameMode(GameMode g);
	// TODO: Phase1 CvDllPreGame::setGameName — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameName(const CvString& g);
	// TODO: Phase1 CvDllPreGame::setGameSpeed — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameSpeed(GameSpeedTypes g);
	// TODO: Phase1 CvDllPreGame::setGameSpeed — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameSpeed(const CvString& g);
	// TODO: Phase1 CvDllPreGame::setGameStarted — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameStarted(bool);
	// TODO: Phase1 CvDllPreGame::setGameTurn — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameTurn(int turn);
	// TODO: Phase1 CvDllPreGame::SetGameOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL SetGameOption(const char* szOptionName, int iValue);
	// TODO: Phase1 CvDllPreGame::SetGameOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL SetGameOption(GameOptionTypes eOption, int iValue);
	// TODO: Phase1 CvDllPreGame::setGameType — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameType(GameTypes g);
	// TODO: Phase1 CvDllPreGame::setGameType — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameType(GameTypes g, GameStartTypes eStartType);
	// TODO: Phase1 CvDllPreGame::setGameType — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameType(const CvString& g);
	// TODO: Phase1 CvDllPreGame::setGameStartType — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameStartType(GameStartTypes g);
	// TODO: Phase1 CvDllPreGame::setGameUpdateTime — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameUpdateTime(int updateTime);
	// TODO: Phase1 CvDllPreGame::setHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setHandicap(PlayerTypes p, HandicapTypes h);
	// TODO: Phase1 CvDllPreGame::setInternetGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setInternetGame(bool isInternetGame);
	// TODO: Phase1 CvDllPreGame::setLeaderHead — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLeaderHead(PlayerTypes p, LeaderHeadTypes l);
	// TODO: Phase1 CvDllPreGame::setLeaderName — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLeaderName(PlayerTypes p, const CvString& n);
	// TODO: Phase1 CvDllPreGame::setLeaderKey — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLeaderKey(PlayerTypes p, const CvString& n);
	// TODO: Phase1 CvDllPreGame::setLeaderKeyPackageID — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLeaderKeyPackageID(PlayerTypes p, const GUID& n);
	// TODO: Phase1 CvDllPreGame::setLoadFileName — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLoadFileName(const CvString& fileName);
	// TODO: Phase1 CvDllPreGame::setLoadoutCargo — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLoadoutCargo(PlayerTypes p, CargoTypes c);
	// TODO: Phase1 CvDllPreGame::setLoadoutColonist — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLoadoutColonist(PlayerTypes p, ColonistTypes c);
	// TODO: Phase1 CvDllPreGame::setLoadoutSpacecraft — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLoadoutSpacecraft(PlayerTypes p, SpacecraftTypes c);
	// TODO: Phase1 CvDllPreGame::setMapNoPlayers — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setMapNoPlayers(bool p);
	// TODO: Phase1 CvDllPreGame::setMapRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setMapRandomSeed(unsigned int newSeed);
	// TODO: Phase1 CvDllPreGame::setLoadWBScenario — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setLoadWBScenario(bool b);
	// TODO: Phase1 CvDllPreGame::setOverrideScenarioHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setOverrideScenarioHandicap(bool b);
	// TODO: Phase1 CvDllPreGame::setMapScriptName — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setMapScriptName(const CvString& s);
	// TODO: Phase1 CvDllPreGame::SetMapOption — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL SetMapOption(const char* szOptionName, int iValue);
	// TODO: Phase1 CvDllPreGame::setMaxCityElimination — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setMaxCityElimination(int m);
	// TODO: Phase1 CvDllPreGame::setMaxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setMaxTurns(int maxTurns);
	// TODO: Phase1 CvDllPreGame::setInitialMaxTurns — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setInitialMaxTurns(int maxTurns);
	// TODO: Phase1 CvDllPreGame::setMinorCivType — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setMinorCivType(PlayerTypes p, MinorCivTypes m);
	// TODO: Phase1 CvDllPreGame::setMinorCiv — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setMinorCiv(PlayerTypes p, bool isMinor);
	// TODO: Phase1 CvDllPreGame::setMultiplayerAIEnabled — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setMultiplayerAIEnabled(bool isEnabled);
	// TODO: Phase1 CvDllPreGame::setNetID — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setNetID(PlayerTypes p, int id);
	// TODO: Phase1 CvDllPreGame::setNickname — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setNickname(PlayerTypes p, const CvString& n);
	// TODO: Phase1 CvDllPreGame::setNumMinorCivs — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setNumMinorCivs(int n);
	// TODO: Phase1 CvDllPreGame::setPersistSettings — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setPersistSettings(bool bPersist);
	// TODO: Phase1 CvDllPreGame::setPlanet — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setPlanet(PlanetTypes p);
	// TODO: Phase1 CvDllPreGame::setGameID — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setGameID(unsigned long long id);
	// TODO: Phase1 CvDllPreGame::setPlayable — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setPlayable(PlayerTypes p, bool playable);
	// TODO: Phase1 CvDllPreGame::setPlayerColor — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setPlayerColor(PlayerTypes p, PlayerColorTypes c);
	// TODO: Phase1 CvDllPreGame::setPrivateGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setPrivateGame(bool isPrivateGame);
	// TODO: Phase1 CvDllPreGame::setQuickCombat — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setQuickCombat(bool isQuickCombat);
	// TODO: Phase1 CvDllPreGame::setQuickMovement — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setQuickMovement(bool isQuickMovement);
	// TODO: Phase1 CvDllPreGame::setQuickHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setQuickHandicap(HandicapTypes h);
	// TODO: Phase1 CvDllPreGame::setQuickHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setQuickHandicap(const CvString& h);
	// TODO: Phase1 CvDllPreGame::setQuickstart — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setQuickstart(bool isQuickStart);
	// TODO: Phase1 CvDllPreGame::setRandomWorldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setRandomWorldSize(bool isRandomWorldSize);
	// TODO: Phase1 CvDllPreGame::setRandomMapScript — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setRandomMapScript(bool isRandomWorldScript);
	// TODO: Phase1 CvDllPreGame::setReady — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setReady(PlayerTypes p, bool bIsReady);
	// TODO: Phase1 CvDllPreGame::setSeaLevel — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setSeaLevel(SeaLevelTypes s);
	// TODO: Phase1 CvDllPreGame::setSeaLevel — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setSeaLevel(const CvString& s);
	// TODO: Phase1 CvDllPreGame::setSlotClaim — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setSlotClaim(PlayerTypes p, SlotClaim c);
	// TODO: Phase1 CvDllPreGame::setSlotStatus — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setSlotStatus(PlayerTypes eID, SlotStatus eSlotStatus);
	// TODO: Phase1 CvDllPreGame::setSyncRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setSyncRandomSeed(unsigned int newSeed);
	// TODO: Phase1 CvDllPreGame::setTeamType — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setTeamType(PlayerTypes p, TeamTypes t);
	// TODO: Phase1 CvDllPreGame::setTransferredMap — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setTransferredMap(bool transferred);
	// TODO: Phase1 CvDllPreGame::setTurnTimer — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setTurnTimer(TurnTimerTypes t);
	// TODO: Phase1 CvDllPreGame::setTurnTimer — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setTurnTimer(const CvString& t);
	// TODO: Phase1 CvDllPreGame::SetCityScreenBlocked — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL SetCityScreenBlocked(bool bCityScreenBlocked);
	// TODO: Phase1 CvDllPreGame::setVersionString — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setVersionString(const std::string& v);
	// TODO: Phase1 CvDllPreGame::setVictory — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setVictory(VictoryTypes v, bool isValid);
	// TODO: Phase1 CvDllPreGame::setVictories — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setVictories(const std::vector<bool>& v);
	// TODO: Phase1 CvDllPreGame::setWhiteFlag — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setWhiteFlag(PlayerTypes p, bool flag);
	// TODO: Phase1 CvDllPreGame::setWorldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setWorldSize(WorldSizeTypes w, bool bResetSlots=true);
	// TODO: Phase1 CvDllPreGame::setWorldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setWorldSize(const CvString& w);
	// TODO: Phase1 CvDllPreGame::slotClaim — UNVERIFIED: Full operand and relocation-target comparison not established.
	SlotClaim DLLCALL slotClaim(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::slotStatus — UNVERIFIED: Full operand and relocation-target comparison not established.
	SlotStatus DLLCALL slotStatus(PlayerTypes eID);
	// TODO: Phase1 CvDllPreGame::syncRandomSeed — UNVERIFIED: Full operand and relocation-target comparison not established.
	unsigned int DLLCALL syncRandomSeed();
	// TODO: Phase1 CvDllPreGame::transferredMap — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL transferredMap();
	// TODO: Phase1 CvDllPreGame::teamType — UNVERIFIED: Full operand and relocation-target comparison not established.
	TeamTypes DLLCALL teamType(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::turnTimer — UNVERIFIED: Full operand and relocation-target comparison not established.
	TurnTimerTypes DLLCALL turnTimer();
	// TODO: Phase1 CvDllPreGame::versionString — UNVERIFIED: Full operand and relocation-target comparison not established.
	const std::string DLLCALL versionString();
	// TODO: Phase1 CvDllPreGame::worldSize — UNVERIFIED: Full operand and relocation-target comparison not established.
	WorldSizeTypes DLLCALL worldSize();
	// TODO: Phase1 CvDllPreGame::GetWorldInfo — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvWorldInfo1* DLLCALL GetWorldInfo();
	// TODO: Phase1 CvDllPreGame::write — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL write(FDataStream& saveTo);
	// TODO: Phase1 CvDllPreGame::getActiveSlotCount — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL getActiveSlotCount();
	// TODO: Phase1 CvDllPreGame::readActiveSlotCountFromSaveGame — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL readActiveSlotCountFromSaveGame(FDataStream& loadFrom);

	// TODO: Phase1 CvDllPreGame::LoadFileStorage — UNVERIFIED: Full operand and relocation-target comparison not established.
	StorageLocation DLLCALL LoadFileStorage();
	// TODO: Phase1 CvDllPreGame::SetLoadFileName — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	void DLLCALL SetLoadFileName(_In_z_ const char* szFileName, StorageLocation eStorage);

	// TODO: Phase1 CvDllPreGame::GetDLCAllowed — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvEnumerator* DLLCALL GetDLCAllowed();
	// TODO: Phase1 CvDllPreGame::GetDLCAllowedCount — UNVERIFIED: Full operand and relocation-target comparison not established.
	unsigned int DLLCALL GetDLCAllowedCount();
	// TODO: Phase1 CvDllPreGame::GetDLCAvailable — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvEnumerator* DLLCALL GetDLCAvailable(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::GetDLCAvailableCount — UNVERIFIED: Full operand and relocation-target comparison not established.
	unsigned int DLLCALL GetDLCAvailableCount(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::SetDLCAvailable — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	void DLLCALL SetDLCAvailable(PlayerTypes p, ICvEnumerator* pList);

	// TODO: Phase1 CvDllPreGame::pitBossTurnTime — UNVERIFIED: Full operand and relocation-target comparison not established.
	int DLLCALL pitBossTurnTime();
	// TODO: Phase1 CvDllPreGame::setPitBossTurnTime — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setPitBossTurnTime(int turnTime);

	// TODO: Phase1 CvDllPreGame::isTurnNotifySteamInvite — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isTurnNotifySteamInvite(PlayerTypes p) const;
	// TODO: Phase1 CvDllPreGame::setTurnNotifySteamInvite — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setTurnNotifySteamInvite(PlayerTypes p, bool wantsSteamInvite);

	// TODO: Phase1 CvDllPreGame::isTurnNotifyEmail — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isTurnNotifyEmail(PlayerTypes p) const;
	// TODO: Phase1 CvDllPreGame::setTurnNotifyEmail — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setTurnNotifyEmail(PlayerTypes p, bool wantsEmail);

	// TODO: Phase1 CvDllPreGame::getTurnNotifyEmailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
	const CvString& DLLCALL getTurnNotifyEmailAddress(PlayerTypes p) const;
	// TODO: Phase1 CvDllPreGame::setTurnNotifyEmailAddress — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setTurnNotifyEmailAddress(PlayerTypes p, const CvString& emailAddress);

	// TODO: Phase1 CvDllPreGame::VerifyHandicap — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL VerifyHandicap(PlayerTypes p);
	// TODO: Phase1 CvDllPreGame::ReseatConnectedPlayers — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL ReseatConnectedPlayers();
	// TODO: Phase1 CvDllPreGame::setUsingFirstTimeUserExperience — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL setUsingFirstTimeUserExperience(bool value);
	// TODO: Phase1 CvDllPreGame::isUsingFirstTimeUserExperience — UNVERIFIED: Full operand and relocation-target comparison not established.
	bool DLLCALL isUsingFirstTimeUserExperience();

private:
	// TODO: Phase1 CvDllPreGame::Destroy — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL Destroy();
};

