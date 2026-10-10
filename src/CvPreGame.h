#pragma once

namespace CvPreGame
{
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

const std::vector<SlotStatus>& GetSlotStatus();
void setAllSlotStatus(const std::vector<SlotStatus>& vSlotStatus);
// TODO: CvPreGame (remaining SDK declarations).
}
