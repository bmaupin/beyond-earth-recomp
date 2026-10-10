/*	-------------------------------------------------------------------------------------------------------
	� 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */

//
//  FILE:    CvGameTextMgr.cpp
//
//  PURPOSE: Private implementation of CvGameTextMgr.
//
#include "CvGameCoreDLLPCH.h"
#include "CvGameTextMgr.h"
#include "CvGameCoreUtils.h"

// must be included after all other headers
#include "LintFree.h"

void CvGameTextMgr::setYearStr(CvString& strString, int iGameTurn, bool bSave, CalendarTypes eCalendar, int iStartYear, GameSpeedTypes eSpeed)
{
	int iTurnYear = getTurnYearForGame(iGameTurn, iStartYear, eCalendar, eSpeed);

	if(iTurnYear < 0)
	{
		if(bSave)
		{
			strString = GetLocalizedText("TXT_KEY_TIME_BC_SAVE", CvString::format("%04d", -iTurnYear).GetCString(), CvString::format("%04d", iGameTurn).GetCString());
		}
		else
		{
			strString = GetLocalizedText("TXT_KEY_TIME_BC", -(iTurnYear));
		}
	}
	else if(iTurnYear > 0)
	{
		if(bSave)
		{
			strString = GetLocalizedText("TXT_KEY_TIME_AD_SAVE", CvString::format("%04d", iTurnYear).GetCString(), CvString::format("%04d", iGameTurn).GetCString());
		}
		else
		{
			strString = GetLocalizedText("TXT_KEY_TIME_AD", iTurnYear);
		}
	}
	else
	{
		if(bSave)
		{
			strString = GetLocalizedText("TXT_KEY_TIME_AD_SAVE", "0001", CvString::format("%04d", iGameTurn).GetCString());
		}
		else
		{
			strString = GetLocalizedText("TXT_KEY_TIME_AD", 1);
		}
	}
}

void CvGameTextMgr::setDateStr(CvString& strString, int iGameTurn, bool bSave, CalendarTypes eCalendar, int iStartYear, GameSpeedTypes eSpeed)
{
	// Beyond Earth displays the turn number instead of calendar dates.
	if(bSave)
	{
		strString = GetLocalizedText("TXT_KEY_TIME_TURN_SAVE", iGameTurn + GC.getHIDDEN_START_TURN_OFFSET() + 1);
	}
	else
	{
		strString = GetLocalizedText("TXT_KEY_TIME_TURN", iGameTurn + GC.getHIDDEN_START_TURN_OFFSET() + 1);
	}
}
