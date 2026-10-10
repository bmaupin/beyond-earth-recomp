#pragma once

class CvDiplomacyRequests
{
public:
	bool Add(PlayerTypes ePlayer, DiploUIStateTypes eState, const char* message, LeaderheadAnimationTypes eAnimation, int iExtraGameData);
	void ActiveRequestComplete();
};
