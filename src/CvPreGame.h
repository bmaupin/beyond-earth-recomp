#pragma once

#include <list>

enum GameTypes : int;
enum GameStartTypes : int;
enum BandwidthType : int;
enum SlotClaim : int;
class FIGameIniParser;
class CvWorldInfo;

namespace CvPreGame
{
extern std::vector<TeamTypes>* sr_TeamTypes;
static TeamTypes teamType(PlayerTypes p)
{
	if(p >= 0 && p < MAX_PLAYERS)
		return (*sr_TeamTypes)[p];
	return NO_TEAM;
}
class CustomOption
{
public:
	CustomOption();
	CustomOption(const char* szOptionName, int iVal);
	CustomOption(const CustomOption& copy);
	CustomOption& operator=(const CustomOption&);
	bool operator ==(const CustomOption& b) const;

	const char* GetName() const;
	const char* GetName(size_t& bytes) const;
	int GetValue() const;

	friend FDataStream& operator<<(FDataStream& saveTo, const CustomOption& readFrom);
	friend FDataStream& operator>>(FDataStream& loadFrom, CustomOption& writeTo);

private:
	char m_szOptionName[64];
	int m_iValue;
};

FDataStream& operator>>(FDataStream&, CustomOption&);
FDataStream& operator<<(FDataStream&, const CustomOption&);

int advancedStartPoints();
CalendarTypes calendar();
ClimateTypes climate();
EraTypes era();
GameMode gameMode();
const CvString& gameName();
GameSpeedTypes gameSpeed();
bool gameStarted();
int gameTurn();
const std::vector<CustomOption>& GetGameOptions();
const std::vector<CustomOption>& GetMapOptions();
bool GetMapOption(const char* szOptionName, int& iValue);
const CvString& loadFileName();
StorageLocation loadFileStorage();
bool mapNoPlayers();
unsigned int mapRandomSeed();
const CvString& mapScriptName();
int maxCityElimination();
int maxTurns();
const std::vector<bool>& multiplayerOptions();
int numMinorCivs();
int pitBossTurnTime();
bool randomMapScript();
bool randomWorldSize();
SeaLevelTypes seaLevel();
unsigned int syncRandomSeed();
TurnTimerTypes turnTimer();
const std::vector<bool>& victories();
WorldSizeTypes worldSize();

void setAdvancedStartPoints(int a);
void setCalendar(CalendarTypes c);
void setClimate(ClimateTypes c);
void setEra(EraTypes e);
void setGameMode(GameMode g);
void setGameName(const CvString& g);
bool SetGameOptions(const std::vector<CustomOption>& gameOptions);
void setGameSpeed(GameSpeedTypes g);
void setGameStarted(bool);
void setGameTurn(int turn);
void setLoadFileName(const CvString& fileName, StorageLocation eStorage);
void setMapNoPlayers(bool p);
bool SetMapOptions(const std::vector<CustomOption>& mapOptions);
void setMapRandomSeed(unsigned int newSeed);
void setMapScriptName(const CvString& s);
void setMaxCityElimination(int m);
void setMaxTurns(int maxTurns);
void setMultiplayerOptions(const std::vector<bool>& o);
void setNumMinorCivs(int n);
void setPitBossTurnTime(int t);
void setRandomMapScript(bool isRandomWorldScript);
void setRandomWorldSize(bool isRandomWorldSize);
void setSeaLevel(SeaLevelTypes s);
void setSyncRandomSeed(unsigned int newSeed);
void setTransferredMap(bool transferred);
void setTurnTimer(TurnTimerTypes t);
void setVictories(const std::vector<bool>& v);
void setWorldSize(WorldSizeTypes w, bool bResetSlots=true);

// Beyond Earth adds planet selection and the initial maximum turn limit.
PlanetTypes planet();
void setPlanet(PlanetTypes);
int initialMaxTurns();
void setInitialMaxTurns(int);

SlotStatus slotStatus(PlayerTypes eID);
const std::vector<SlotStatus>& GetSlotStatus();
void setAllSlotStatus(const std::vector<SlotStatus>& vSlotStatus);
// TODO: CvPreGame (remaining SDK declarations).
}

namespace CvPreGame
{
PlayerTypes activePlayer();
bool autorun();
float autorunTurnDelay();
int autorunTurnLimit();
bool canReadyLocalPlayer();
const CvString& civilizationAdjective(PlayerTypes p);
const CvString& civilizationAdjectiveKey(PlayerTypes p);
const CvString& civilizationDescription(PlayerTypes p);
const CvString& civilizationDescriptionKey(PlayerTypes p);
CivilizationTypes civilization(PlayerTypes p);
const CvString& civilizationPassword(PlayerTypes p);
const CvString& civilizationShortDescription(PlayerTypes p);
const CvString& civilizationShortDescriptionKey(PlayerTypes p);
const CvString& civilizationKey(PlayerTypes p);
bool civilizationKeyAvailable(PlayerTypes p);
void clearDLCAllowed();
void closeAllSlots();
void closeInactiveSlots();
const CvString& emailAddress(PlayerTypes p);
const CvString& emailAddress();
float endTurnTimerLength();
PlayerTypes findPlayerByNickname(const char* const name);
void ReseatConnectedPlayers();
bool GetGameOption(const char* szOptionName, int& iValue);
bool GetGameOption(GameOptionTypes eOption, int& iValue);
bool GetPersistSettings();
uint getDLCAllowedCount();
const std::list<GUID>& getDLCAllowed();
const std::list<GUID>& getDLCAvailable(PlayerTypes p);
void setDLCAvailable(PlayerTypes p, const std::list<GUID>& kList);
GameTypes gameType();
GameStartTypes gameStartType();
HandicapTypes handicap(PlayerTypes p);
bool isDLCAllowed(const GUID& kDLCID);
bool isDLCAvailable(PlayerTypes p, const GUID& kDLCID);
bool isHotSeat();
bool isHotSeatGame();
bool isHuman(PlayerTypes p);
bool isInternetGame();
bool isMinorCiv(PlayerTypes p);
bool isNetworkMultiplayerGame();
bool isPitBoss();
bool isPlayable(PlayerTypes p);
bool isPlayByEmail();
bool isReady(PlayerTypes p);
bool isVictory(VictoryTypes v);
bool isWBMapScript();
bool isWhiteFlag(PlayerTypes p);
bool isTurnNotifySteamInvite(PlayerTypes p);
bool isTurnNotifyEmail(PlayerTypes p);
const CvString& getTurnNotifyEmailAddress(PlayerTypes p);
LeaderHeadTypes leaderHead(PlayerTypes p);
const CvString& leaderName(PlayerTypes p);
const CvString& leaderNameKey(PlayerTypes p);
const CvString& leaderKey(PlayerTypes p);
bool leaderKeyAvailable(PlayerTypes p);
const GUID& leaderKeyPackageID(PlayerTypes p);
void loadFromIni(FIGameIniParser& iniParser);
bool loadWBScenario();
bool overrideScenarioHandicap();
MinorCivTypes minorCivType(PlayerTypes p);
bool multiplayerAIEnabled();
int netID(PlayerTypes p);
const CvString& nickname(PlayerTypes p);
const CvString& nicknameDisplayed(PlayerTypes p);
PlayerColorTypes playerColor(PlayerTypes p);
bool privateGame();
bool quickCombat();
bool quickstart();
bool quickMovement();
void read(FDataStream& loadFrom);
bool readPlayerSlotInfo(FDataStream& loadFrom);
void resetGame();
void ResetGameOptions();
void ResetMapOptions();
void resetPlayer(PlayerTypes p);
void resetPlayers();
void resetSlots();
void restoreSlots();
void saveSlots();
void setActivePlayer(PlayerTypes p);
void setAdminPassword(const CvString& p);
void setAlias(const CvString& a);
void setAutorun(bool isAutoStart);
void setAutorunTurnDelay(float turnDelay);
void setAutorunTurnLimit(int turnLimit);
void setBandwidth(BandwidthType b);
void setBandwidth(const CvString& b);
void setCalendar(const CvString& c);
void setCivilization(PlayerTypes p, CivilizationTypes c);
void setCivilizationAdjective(PlayerTypes p, const CvString& a);
void setCivilizationDescription(PlayerTypes p, const CvString& d);
void setCivilizationPassword(PlayerTypes p, const CvString& pwd);
void setCivilizationShortDescription(PlayerTypes p, const CvString& d);
void setCivilizationKey(PlayerTypes p, const CvString& d);
void setCivilizationKeyPackageID(PlayerTypes p, const GUID& kKey);
void setClimate(const CvString& c);
void setCustomWorldSize(int iWidth, int iHeight, int iPlayers, int iMinorCivs);
void setDLCAllowed(const GUID& kDLCID, bool bState);
void setEmailAddress(PlayerTypes p, const CvString& a);
void setEmailAddress(const CvString& a);
void setEndTurnTimerLength(float f);
void setEra(const CvString& e);
void setGameSpeed(const CvString& g);
bool SetGameOption(const char* szOptionName, int iValue);
bool SetGameOption(GameOptionTypes eOption, int iValue);
void setGameType(GameTypes g);
void setGameType(GameTypes g, GameStartTypes eStartType);
void setGameType(const CvString& g);
void setGameStartType(GameStartTypes g);
void setGameUpdateTime(int updateTime);
void setHandicap(PlayerTypes p, HandicapTypes h);
void setInternetGame(bool isInternetGame);
void setLeaderHead(PlayerTypes p, LeaderHeadTypes l);
void setLeaderName(PlayerTypes p, const CvString& n);
void setLeaderKey(PlayerTypes p, const CvString& n);
void setLeaderKeyPackageID(PlayerTypes p, const GUID& n);
void setLoadFileName(const CvString& fileName);
void setLoadWBScenario(bool b);
void setOverrideScenarioHandicap(bool b);
bool SetMapOption(const char* szOptionName, int iValue);
void setMinorCivType(PlayerTypes p, MinorCivTypes m);
void setMinorCiv(PlayerTypes p, bool isMinor);
void setMultiplayerAIEnabled(bool isEnabled);
void setNetID(PlayerTypes p, int id);
void setNickname(PlayerTypes p, const CvString& n);
void setPersistSettings(bool bPersist);
void setPlayable(PlayerTypes p, bool playable);
void setPlayerColor(PlayerTypes p, PlayerColorTypes c);
void setPrivateGame(bool isPrivateGame);
void setQuickCombat(bool isQuickCombat);
void setQuickHandicap(HandicapTypes h);
void setQuickHandicap(const CvString& h);
void setQuickMovement(bool isQuickMovement);
void setQuickstart(bool isQuickStart);
void setReady(PlayerTypes p, bool bIsReady);
void setSeaLevel(const CvString& s);
void setSlotClaim(PlayerTypes p, SlotClaim c);
void setSlotStatus(PlayerTypes eID, SlotStatus eSlotStatus);
void setTeamType(PlayerTypes p, TeamTypes t);
void setTurnTimer(const CvString& t);
void SetCityScreenBlocked(bool bCityScreenBlocked);
void setVersionString(const std::string& v);
void setVictory(VictoryTypes v, bool isValid);
void setWhiteFlag(PlayerTypes p, bool flag);
void setTurnNotifySteamInvite(PlayerTypes p, bool flag);
void setTurnNotifyEmail(PlayerTypes p, bool flag);
void setTurnNotifyEmailAddress(PlayerTypes p, const CvString& emailAddress);
void VerifyHandicap(PlayerTypes p);
void setWorldSize(const CvString& w);
SlotClaim slotClaim(PlayerTypes p);
bool transferredMap();
const std::string& versionString();
const CvWorldInfo& worldInfo();
void write(FDataStream& saveTo);
int getActiveSlotCount();
int readActiveSlotCountFromSaveGame(FDataStream& loadFrom);
const GUID& civilizationKeyPackageID(PlayerTypes);
CargoTypes loadoutCargo(PlayerTypes);
ColonistTypes loadoutColonist(PlayerTypes);
SpacecraftTypes loadoutSpacecraft(PlayerTypes);
void FillEmptyLoadoutSlots(PlayerTypes);
void setLoadoutCargo(PlayerTypes, CargoTypes);
void setLoadoutColonist(PlayerTypes, ColonistTypes);
void setLoadoutSpacecraft(PlayerTypes, SpacecraftTypes);
int getNumPlanets();
const char* getPlanetFileName();
const char* getPlanetFileName(PlanetTypes);
unsigned long long getGameID();
void setGameID(unsigned long long);
const char* getRandomMapScript();
unsigned int getDLCAvailableCount(PlayerTypes);
void setUsingFirstTimeUserExperience(bool);
bool isUsingFirstTimeUserExperience();
}
