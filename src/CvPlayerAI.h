#pragma once

#include "CvPlayer.h"

class CvQuestAI;
class CvStationAI;
class CvUnitUpgradeAI;
class CvArtifactAI;
class CvAIFactManager;

class CvPlayerAI : public CvPlayer
{
public:
	static CvPlayerAI& getPlayer(PlayerTypes ePlayer)
	{
		return m_aPlayers[ePlayer];
	}
	// TODO(Phase1): CvPlayerAI (remaining method declarations and implementations).
private:
	static CvPlayerAI* m_aPlayers;
	CvQuestAI* m_pQuestAI;
	CvStationAI* m_pStationAI;
	CvUnitUpgradeAI* m_pUpgradeAI;
	CvArtifactAI* m_pArtifactAI;
	CvAIFactManager* m_pAIFactManager;
	AffinityType m_affinityChoice;
};

#define GET_PLAYER CvPlayerAI::getPlayer