#pragma once

#include <string>
#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvDiplomacyAIEnums.h"

// TODO: Restore the remaining diplomacy enum definitions.
enum MajorCivApproachTypes : int;
enum DiploMessageTypes : int;
enum DiploStatementTypes : int;

namespace Localization { class String; }
class CvPlayer;

class CvDiplomacyAI
{
public:
	void DoBeginDiploWithHuman();
	int GetTotalLandDisputeLevel();
	int GetPersonalityMajorCivApproachBias(MajorCivApproachTypes eApproach) const;
	std::string GetDiploStringForMessage(DiploMessageTypes message, PlayerTypes player, const Localization::String& optionalKey);
	void TestUIDiploStatement(PlayerTypes player, DiploStatementTypes statement, int data);
	int GetAffinityDiffersScore(PlayerTypes ePlayer) const;
private:
	CvPlayer* m_pPlayer;
	// TODO: CvDiplomacyAI (remaining members).
};
