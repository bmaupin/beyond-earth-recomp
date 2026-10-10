#pragma once

class CvUnit;

class CvAStarNode
{
public:
	int m_iTotalCost;
	int m_iKnownCost;
	int m_iHeuristicCost;
	int m_iData1;
	int m_iData2;
};

class CvAStar
{
public:
	bool GeneratePath(int iXstart, int iYstart, int iXdest, int iYdest, int iInfo = 0, bool bReuse = false);
	CvAStarNode* GetLastNode();
};

class CvTwoLayerPathFinder : public CvAStar
{
public:
	void SetData(CvUnit* pUnit);
};

enum
{
	MOVE_UNITS_IGNORE_DANGER = 0x00000008,
	MOVE_UNITS_THROUGH_ENEMY = 0x00000010
};
