#include "CvGameCoreDLLPCH.h"
#include "CvDiplomacyAI.h"
#include "CvPlayerAffinities.h"

// Beyond Earth scales differing dominant affinity levels by the requesting leader's devotion.
int CvDiplomacyAI::GetAffinityDiffersScore(PlayerTypes ePlayer) const
{
	CvPlayerAffinities* pOurAffinities = m_pPlayer->GetPlayerAffinities();
	if(pOurAffinities == NULL)
		return 0;

	CvPlayerAffinities* pTheirAffinities = GET_PLAYER(ePlayer).GetPlayerAffinities();
	if(pTheirAffinities == NULL)
		return 0;

	AffinityType eOurAffinity = pOurAffinities->GetDominantAffinityType();
	AffinityType eTheirAffinity = pTheirAffinities->GetDominantAffinityType();
	if(eOurAffinity == eTheirAffinity)
		return 0;
	if(eOurAffinity == NO_AFFINITY_TYPE)
		return 0;
	if(eTheirAffinity == NO_AFFINITY_TYPE)
		return 0;

	int iMinPercent = GC.getOPINION_WEIGHT_AFFINITY_DIFFERS_MIN_PERCENT_TOWARDS_MAX_LEVEL();
	if(pOurAffinities->GetAffinityPercentTowardsMaxLevel(eOurAffinity) < iMinPercent)
		return 0;
	if(pTheirAffinities->GetAffinityPercentTowardsMaxLevel(eTheirAffinity) < iMinPercent)
		return 0;

	int iOurWeight = pOurAffinities->GetAffinityLevel(eOurAffinity) * 200;
	int iTheirWeight = pTheirAffinities->GetAffinityLevel(eTheirAffinity) * 100;
	int iSumWeight = iOurWeight + iTheirWeight;

	int iDevotion = m_pPlayer->getLeaderInfo().GetAffinityDevotion();
	if(iDevotion <= 3)
		iSumWeight = iSumWeight * 50 / 100;
	else
	{
		switch(iDevotion)
		{
		case 4:
		case 5:
		case 6:
			iSumWeight = iSumWeight * 75 / 100;
			break;
		}
	}

	return iSumWeight / 100 + GC.getOPINION_WEIGHT_AFFINITY_DIFFERS();
}
