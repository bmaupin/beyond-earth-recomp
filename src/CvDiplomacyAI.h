#pragma once

#include <string>
#include "CvGameCoreDLLUtil/CvEnums.h"
#include "CvDiplomacyAIEnums.h"

// TODO: Restore the remaining diplomacy enum definitions.
enum MajorCivApproachTypes : int;
enum DiploMessageTypes : int;
enum DiploStatementTypes : int;
enum PublicDeclarationTypes : int;

class FDataStream;
namespace Localization { class String; }
class CvPlayer;

struct DiploLogData
{
	DiploStatementTypes m_eDiploLogStatement;
	int m_iTurn;
};

struct DeclarationLogData
{
	PublicDeclarationTypes m_eDeclaration;
	int m_iData1;
	int m_iData2;
	PlayerTypes m_eMustHaveMetPlayer;
	bool m_bActive;
	int m_iTurn;
};

FDataStream& operator<<(FDataStream&, const DeclarationLogData&);
FDataStream& operator>>(FDataStream&, DeclarationLogData&);

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
