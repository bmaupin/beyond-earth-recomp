#pragma once

#include <string>
#include "CvGameCoreDLLUtil/CvEnums.h"

namespace Localization { class String; }

class CvDiplomacyAI
{
public:
	void DoBeginDiploWithHuman();
	int GetTotalLandDisputeLevel();
	int GetPersonalityMajorCivApproachBias(MajorCivApproachTypes eApproach) const;
	std::string GetDiploStringForMessage(DiploMessageTypes message, PlayerTypes player, const Localization::String& optionalKey);
	void TestUIDiploStatement(PlayerTypes player, DiploStatementTypes statement, int data);
};
