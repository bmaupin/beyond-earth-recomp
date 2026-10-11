#pragma once

#include "CvAStarNode.h"

class CvUnit;
class CvPlot;
class CvAStar;

typedef int (*CvAPointFunc)(int, int, const void*, CvAStar*);
typedef int (*CvAHeuristic)(int, int, int, int);
typedef int (*CvAStarFunc)(CvAStarNode*, CvAStarNode*, int, const void*, CvAStar*);
typedef int (*CvANumExtraChildren)(CvAStarNode*, CvAStar*);
typedef int (*CvAGetExtraChild)(CvAStarNode*, int, int&, int&, CvAStar*);
typedef void (*CvABegin)(const void*, CvAStar*);
typedef void (*CvAEnd)(const void*, CvAStar*);

class CvAStar
{
public:
	CvAStar();
	~CvAStar();
	void Initialize(int, int, bool, bool, CvAPointFunc, CvAPointFunc, CvAHeuristic,
		CvAStarFunc, CvAStarFunc, CvAStarFunc, CvAStarFunc, CvANumExtraChildren,
		CvAGetExtraChild, CvABegin, CvAEnd, const void*);
	void DeInit();
	bool GeneratePath(int iXstart, int iYstart, int iXdest, int iYdest, int iInfo = 0, bool bReuse = false);
	CvAStarNode* GetLastNode() { return m_pBest; }
	void ForceReset() { m_bForceReset = true; }
	void SetData(const void* pData)
	{
		if(m_bDataChangeInvalidatesCache && m_pData != pData)
			m_bForceReset = true;
		m_pData = pData;
	}
	CvAPointFunc GetDestValidFunc() { return udDestValid; }
	void SetDestValidFunc(CvAPointFunc pFunc) { udDestValid = pFunc; }
	CvAStarFunc GetValidFunc() { return udValid; }
	void SetValidFunc(CvAStarFunc pFunc) { udValid = pFunc; }
	CvAStarFunc GetNotifyChildFunc() { return udNotifyChild; }
	void SetNotifyChildFunc(CvAStarFunc pFunc) { udNotifyChild = pFunc; }

protected:
	CvAPointFunc udIsPathDest;
	CvAPointFunc udDestValid;
	CvAHeuristic udHeuristic;
	CvAStarFunc udCost;
	CvAStarFunc udValid;
	CvAStarFunc udNotifyChild;
	CvAStarFunc udNotifyList;
	CvANumExtraChildren udNumExtraChildrenFunc;
	CvAGetExtraChild udGetExtraChildFunc;
	CvABegin udInitializeFunc;
	CvAEnd udUninitializeFunc;
	const void* m_pData;
	int m_iColumns;
	int m_iRows;
	int m_iXstart;
	int m_iYstart;
	int m_iXdest;
	int m_iYdest;
	int m_iInfo;
	bool m_bWrapX;
	bool m_bWrapY;
	bool m_bForceReset;
	bool m_bIsMPCacheSafe;
	bool m_bDataChangeInvalidatesCache;
	CvAStarNode* m_pOpen;
	CvAStarNode* m_pOpenTail;
	CvAStarNode* m_pClosed;
	CvAStarNode* m_pBest;
	CvAStarNode* m_pStackHead;
	CvAStarNode** m_ppaaNodes;
	void* m_pScratchPtr1;
	void* m_pScratchPtr2;
	char m_ScratchBuffer[512];
};

class CvTwoLayerPathFinder : public CvAStar
{
public:
	CvTwoLayerPathFinder();
	~CvTwoLayerPathFinder();
	void Initialize(int, int, bool, bool, CvAPointFunc, CvAPointFunc, CvAHeuristic,
		CvAStarFunc, CvAStarFunc, CvAStarFunc, CvAStarFunc, CvABegin, CvAEnd, const void*);
	void DeInit();
	CvAStarNode* GetPartialMoveNode(int, int);
	CvPlot* GetPathEndTurnPlot() const;
	bool GenerateUnitPath(const CvUnit*, int, int, int, int, int, bool);

private:
	CvAStarNode** m_ppaaPartialMoveNodes;
};

static_assert(sizeof(CvAStar) == 628, "Beyond Earth AStar layout");
static_assert(sizeof(CvTwoLayerPathFinder) == 632, "Beyond Earth two-layer pathfinder layout");

enum
{
	MOVE_UNITS_IGNORE_DANGER = 0x00000008,
	MOVE_UNITS_THROUGH_ENEMY = 0x00000010,
	MOVE_DECLARE_WAR = 0x00000020
};
