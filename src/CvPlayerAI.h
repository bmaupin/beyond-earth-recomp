#pragma once

#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvPlayer.h"

class CvPlayerAI : public CvPlayer
{
public:
	// TODO: Reimplement using m_aPlayers[ePlayer] after restoring the authentic CvPlayerAI layout; DWARF stride 0xf598.
	static CvPlayerAI& getPlayer(PlayerTypes ePlayer)
	{
		return *reinterpret_cast<CvPlayerAI*>(reinterpret_cast<char*>(m_aPlayers) + ePlayer * 0xf598);
	}
	// TODO: CvPlayerAI (remaining members).
private:
	static CvPlayerAI* m_aPlayers;
};

#define GET_PLAYER CvPlayerAI::getPlayer