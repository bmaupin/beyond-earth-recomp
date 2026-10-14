#pragma once

#include <cstdlib>

class CvPlot;

bool isWorldProject(ProjectTypes eProject);

// Beyond Earth adds a plot-pointer overload of the distance utility.
int plotDistance(const CvPlot* pPlot1, const CvPlot* pPlot2);
int getTurnYearForGame(int iGameTurn, int iStartYear, CalendarTypes eCalendar, GameSpeedTypes eSpeed);

// TODO: Restore SDK inline bodies with authentic localization dependencies.
template<typename T>
CvString GetLocalizedText(const char* szString, T arg1);
template<typename T1, typename T2>
CvString GetLocalizedText(const char* szString, const T1& arg1, const T2& arg2);

inline int wrapCoordDifference(int iDiff, uint uiRange, bool bWrap)
{
	if(bWrap)
	{
		if(iDiff > (int)(uiRange >> 1))		// Using an unsigned int so we can safely assume that value >> 1 == value / 2
		{
			return (iDiff - (int)uiRange);
		}
		else if(iDiff < -(int)(uiRange >> 1))
		{
			return (iDiff + (int)uiRange);
		}
	}

	return iDiff;
}

inline int dxWrap(int iDX)
{
	const CvMap& kMap = GC.getMap();
	return wrapCoordDifference(iDX, kMap.getGridWidth(), kMap.isWrapX());
}

inline int dyWrap(int iDY)
{
	const CvMap& kMap = GC.getMap();
	return wrapCoordDifference(iDY, kMap.getGridHeight(), kMap.isWrapY());
}

inline int xToHexspaceX(int iX, int iY)
{
	return iX - ((iY >= 0) ? (iY>>1) : ((iY - 1)/2));
}

inline int plotDistance(int iX1, int iY1, int iX2, int iY2)
{
	int iDX;
	int iWrappedDX = dxWrap(iX2 - iX1);
	int iWrappedDY = dyWrap(iY2 - iY1);
	int iDY = abs(iWrappedDY);

	// convert to hex-space coordinates - the coordinate system axes are E and NE (not orthogonal)
	int iHX1 = xToHexspaceX(iX1, iY1);
	int iHX2 = xToHexspaceX(iX1 + iWrappedDX, iY1 + iWrappedDY);

	iDX = abs(dxWrap(iHX2 - iHX1));

	if((iHX2 - iHX1 >= 0) == (iWrappedDY >= 0))  // the signs match
	{
		return iDX + iDY;
	}
	else
	{
		return (std::max(iDX, iDY));
	}
}
