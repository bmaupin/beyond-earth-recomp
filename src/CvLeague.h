#pragma once

#include "Fireworks/FFastVector.h"
#include <vector>
#include "CvGameCoreDLLUtil/include/CvString.h"

enum LeagueProjectTypes { NO_LEAGUE_PROJECT = -1 };
enum LeagueSpecialSessionTypes { NO_LEAGUE_SPECIAL_SESSION = -1 };
enum ResolutionDecisionTypes { NO_RESOLUTION_DECISION = -1 };
enum UnitClassTypes { NO_UNITCLASS = -1 };

namespace Localization { class String { public: CvString toUTF8() const; }; }

class CvResolutionDecision { public: int GetDecision(); };
class CvVoterDecision : public CvResolutionDecision {};
class CvProposerDecision : public CvResolutionDecision {};
class CvResolution {
public:
	int GetID() const;
	ResolutionTypes GetType() const;
	CvVoterDecision* GetVoterDecision();
	CvProposerDecision* GetProposerDecision();
};
class CvProposal : public CvResolution { public: PlayerTypes GetProposalPlayer() const; };
class CvEnactProposal : public CvProposal {};
class CvRepealProposal : public CvProposal {
public:
	int GetTargetResolutionID() const;
	CvVoterDecision* GetRepealDecision();
};
class CvActiveResolution : public CvResolution { public: int GetTurnEnacted() const; };
typedef FStaticVector<CvEnactProposal, 2, false> EnactProposalList;
typedef FStaticVector<CvRepealProposal, 2, false> RepealProposalList;
typedef FStaticVector<CvActiveResolution, 12, false> ActiveResolutionList;

class CvLeague
{
public:
	enum ContributionTier { CONTRIBUTION_TIER_0, CONTRIBUTION_TIER_1, CONTRIBUTION_TIER_2, CONTRIBUTION_TIER_3 };
	LeagueTypes GetID() const;
	Localization::String GetName();
	bool CanChangeCustomName(PlayerTypes);
	bool IsInSession(); bool IsInSpecialSession(); int GetTurnsUntilSession() const; int GetTurnsUntilVictorySession();
	bool CanProposeEnactAnyChoice(ResolutionTypes, PlayerTypes); bool CanProposeEnact(ResolutionTypes, PlayerTypes, int); bool CanProposeRepeal(int, PlayerTypes); bool IsProposed(int, bool);
	std::vector<int> GetChoicesForDecision(ResolutionDecisionTypes, PlayerTypes); CvString GetTextForChoice(ResolutionDecisionTypes, int); std::vector<ResolutionTypes> GetInactiveResolutions() const;
	EnactProposalList GetEnactProposals() const; EnactProposalList GetEnactProposalsOnHold() const; RepealProposalList GetRepealProposals() const; RepealProposalList GetRepealProposalsOnHold() const; ActiveResolutionList GetActiveResolutions() const;
	bool IsMember(PlayerTypes) const; bool CanVote(PlayerTypes); int GetRemainingVotesForMember(PlayerTypes); int GetSpentVotesForMember(PlayerTypes); int GetCoreVotesForMember(PlayerTypes); int CalculateStartingVotesForMember(PlayerTypes, bool = false); bool CanPropose(PlayerTypes); int GetRemainingProposalsForMember(PlayerTypes);
	bool IsHostMember(PlayerTypes) const; PlayerTypes GetHostMember() const; bool IsUnitedNations() const;
	bool IsProjectActive(LeagueProjectTypes) const; bool IsProjectComplete(LeagueProjectTypes) const; int GetProjectCostPerPlayer(LeagueProjectTypes) const; int GetProjectBuildingCostPerPlayer(BuildingTypes) const; int GetProjectCost(LeagueProjectTypes) const; int GetMemberContribution(PlayerTypes, LeagueProjectTypes) const; int GetMemberContributionTier(PlayerTypes, LeagueProjectTypes); float GetContributionTierThreshold(ContributionTier, LeagueProjectTypes);
	int GetArtsyGreatPersonRateModifier(); int GetScienceyGreatPersonRateModifier();
	CvString GetResolutionName(ResolutionTypes, int, int, bool); CvString GetResolutionDetails(ResolutionTypes, PlayerTypes, int, int); CvString GetMemberDetails(PlayerTypes, PlayerTypes); CvString GetProjectDetails(LeagueProjectTypes, PlayerTypes); CvString GetProjectRewardTierDetails(int, LeagueProjectTypes, PlayerTypes); std::vector<CvString> GetCurrentEffectsSummary(PlayerTypes); CvString GetLeagueSplashTitle(LeagueSpecialSessionTypes, bool); CvString GetLeagueSplashDescription(LeagueSpecialSessionTypes, bool); CvString GetLeagueSplashThisEraDetails(LeagueSpecialSessionTypes, bool); CvString GetLeagueSplashNextEraDetails(LeagueSpecialSessionTypes, bool); CvString GetGreatPersonRateModifierDetails(UnitClassTypes);
};
