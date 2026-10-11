#pragma once

#include <cstddef>
#include "Fireworks/FMemHooks.h"
#include "Fireworks/FDefNew.h"
#include "Fireworks/FFastVector.h"

enum CvAStarListType
{
	NO_CVASTARLIST = -1,
	CVASTARLIST_OPEN,
	CVASTARLIST_CLOSED,
	NUM_CVASTARLIST_TYPES
};

struct CvPathNodeCacheData
{
	bool bPlotVisibleToTeam : 1;
	bool bIsMountain : 1;
	bool bIsCanyon : 1;
	bool bIsWater : 1;
	bool bIsMiasmaDamage : 1;
	bool bCanEnterTerrain : 1;
	bool bIsRevealedToTeam : 1;
	bool bContainsOtherFriendlyTeamCity : 1;
	bool bContainsEnemyCity : 1;
	bool bContainsOtherFriendlyTeamOutpost : 1;
	bool bContainsEnemyOutpost : 1;
	bool bContainsVisibleEnemy : 1;
	bool bContainsVisibleEnemyDefender : 1;
	int iNumFriendlyUnitsOfType;
};

class CvAStarNode
{
public:
	int m_iTotalCost;
	int m_iKnownCost;
	int m_iHeuristicCost;
	int m_iData1;
	int m_iData2;
	CvAStarListType m_eCvAStarListType;
	CvAStarNode* m_pParent;
	CvAStarNode* m_pNext;
	CvAStarNode* m_pPrev;
	CvAStarNode* m_pStack;
	FStaticVector<CvAStarNode*, 6, true, 1256, 0> m_apChildren;
	short m_iX;
	short m_iY;
	short m_iNumChildren;
	bool m_bOnStack;
	CvPathNodeCacheData m_kCostCacheData;
};

static_assert(sizeof(CvPathNodeCacheData) == 8, "Beyond Earth path cache layout");
static_assert(sizeof(CvAStarNode) == 96, "Beyond Earth AStar node layout");
static_assert(offsetof(CvAStarNode, m_pParent) == 24, "Beyond Earth path parent offset");
static_assert(offsetof(CvAStarNode, m_apChildren) == 40, "Beyond Earth path children offset");
static_assert(offsetof(CvAStarNode, m_iX) == 80, "Beyond Earth path coordinate offset");
static_assert(offsetof(CvAStarNode, m_iY) == 82, "Beyond Earth path coordinate offset");
static_assert(offsetof(CvAStarNode, m_kCostCacheData) == 88, "Beyond Earth path cache offset");
