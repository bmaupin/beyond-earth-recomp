#include "CvGameCoreDLLPCH.h"
#include "CvDiplomacyAI.h"
#include "CvPlayerAffinities.h"

// TODO: operator<<(FDataStream&, DiploLogData const&) (25 total instructions, 1 differs)
// TODO: operator>>(FDataStream&, DiploLogData&) (25 total instructions)

FDataStream& operator<<(FDataStream& saveTo, const DeclarationLogData& readFrom)
{
	saveTo << readFrom.m_eDeclaration;
	saveTo << readFrom.m_iData1;
	saveTo << readFrom.m_iData2;
	saveTo << readFrom.m_eMustHaveMetPlayer;
	saveTo << readFrom.m_bActive;
	saveTo << readFrom.m_iTurn;
	return saveTo;
}

inline FDataStream& operator>>(FDataStream& loadFrom, PublicDeclarationTypes& writeTo)
{
	int value;
	loadFrom >> value;
	writeTo = static_cast<PublicDeclarationTypes>(value);
	return loadFrom;
}

FDataStream& operator>>(FDataStream& loadFrom, DeclarationLogData& writeTo)
{
	loadFrom >> writeTo.m_eDeclaration;
	loadFrom >> writeTo.m_iData1;
	loadFrom >> writeTo.m_iData2;
	loadFrom >> writeTo.m_eMustHaveMetPlayer;
	loadFrom >> writeTo.m_bActive;
	loadFrom >> writeTo.m_iTurn;
	return loadFrom;
}

// Beyond Earth scales differing dominant affinity levels by the requesting leader's devotion.
int CvDiplomacyAI::GetAffinityDiffersScore(PlayerTypes ePlayer) const
{
	CvPlayerAffinities* myAffinities = m_pPlayer->GetPlayerAffinities();
	if(myAffinities == NULL)
		return 0;

	CvPlayerAffinities* yourAffinities = GET_PLAYER(ePlayer).GetPlayerAffinities();
	if(yourAffinities == NULL)
		return 0;

	AffinityType myDominantAffinity = myAffinities->GetDominantAffinityType();
	AffinityType yourDominantAffinity = yourAffinities->GetDominantAffinityType();
	if(myDominantAffinity == yourDominantAffinity)
		return 0;
	if(myDominantAffinity == NO_AFFINITY_TYPE)
		return 0;
	if(yourDominantAffinity == NO_AFFINITY_TYPE)
		return 0;

	int minAffinityPercent = GC.getOPINION_WEIGHT_AFFINITY_DIFFERS_MIN_PERCENT_TOWARDS_MAX_LEVEL();
	if(myAffinities->GetAffinityPercentTowardsMaxLevel(myDominantAffinity) < minAffinityPercent)
		return 0;
	if(yourAffinities->GetAffinityPercentTowardsMaxLevel(yourDominantAffinity) < minAffinityPercent)
		return 0;

	int myAffinityWeight = myAffinities->GetAffinityLevel(myDominantAffinity) * 200;
	int yourAffinityWeight = yourAffinities->GetAffinityLevel(yourDominantAffinity) * 100;
	int sumWeight = myAffinityWeight + yourAffinityWeight;

	int myAffinityDevotion = m_pPlayer->getLeaderInfo().GetAffinityDevotion();
	if(myAffinityDevotion < 4)
		sumWeight = sumWeight * 50 / 100;
	else if(myAffinityDevotion < 7)
		sumWeight = sumWeight * 75 / 100;

	int score = sumWeight / 100 + GC.getOPINION_WEIGHT_AFFINITY_DIFFERS();
	return score;
}
