#pragma once

#include "CvPlayer.h"

class CvPlayerAI : public CvPlayer
{
public:
	// TODO: CvPlayerAI::getPlayer (SDK inline body; requires full player layout).
	static CvPlayerAI& getPlayer(PlayerTypes ePlayer);
	// TODO: CvPlayerAI (remaining members).
};

#define GET_PLAYER CvPlayerAI::getPlayer