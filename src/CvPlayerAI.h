#pragma once

#include "CvPlayer.h"

class CvPlayerAI : public CvPlayer
{
public:
	// TODO: CvPlayerAI::getPlayer(PlayerTypes) (restore SDK array indexing after reconstructing the real player size).
	static CvPlayerAI& getPlayer(PlayerTypes ePlayer);
	// TODO: CvPlayerAI (remaining members).
private:
	static CvPlayerAI* m_aPlayers;
};

#define GET_PLAYER CvPlayerAI::getPlayer