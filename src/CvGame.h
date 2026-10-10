#pragma once

class CvRandom;
class CvGameSpeedInfo;
class CvHandicapInfo;
class CvGame
{
public:
	int getElapsedGameTurns() const;
	CvRandom& getMapRand();
	PlayerTypes getActivePlayer() const;
	TeamTypes getActiveTeam();
	int getGameTurn() const;
	GameSpeedTypes getGameSpeedType() const;
	CvGameSpeedInfo& getGameSpeedInfo() const;
	CvHandicapInfo& getHandicapInfo() const;
	GameStateTypes getGameState();
	// Beyond Earth exposes whether the game has ever been extended.
	bool hasGameEverBeenExtended();
	HandicapTypes getHandicapType() const;
	int IsAction(int iKeyStroke, bool bAlt, bool bShift, bool bCtrl);
	bool isDebugMode() const;
	bool isFinalInitialized() const;
	bool isGameMultiPlayer() const;
	bool isHotSeat() const;
	bool isMPOption(MultiplayerOptionTypes eIndex) const;
	bool isNetworkMultiPlayer() const;
	bool isOption(GameOptionTypes eIndex) const;
	bool isPaused();
	bool isPbem() const;
	bool isTeamGame() const;
	bool TunerEverConnected() const;
	// TODO: CvGame (remaining members).
};