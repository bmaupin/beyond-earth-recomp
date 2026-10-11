// TODO: Phase1 hksi_lua_setfield(lua_State*, int, char const*): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<ResolutionTypes, std::__1::allocator<ResolutionTypes> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<CvString, std::__1::allocator<CvString> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<int, std::__1::allocator<int> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
#pragma once
#include "CvLuaScopedInstance.h"
class CvResolution; class CvProposal;
class CvLuaLeague : public CvLuaScopedInstance<CvLuaLeague, CvLeague> {
public:
// TODO: Phase1 CvLuaLeague::GetTypeName(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::HandleMissingInstance(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::PushMethods(lua_State*, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
 static void PushMethods(lua_State*, int); static void HandleMissingInstance(lua_State*); static const char* GetTypeName();
protected:
// TODO: Phase1 CvLuaLeague::lGetID(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsInSession(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsNone(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsInSpecialSession(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCanChangeCustomName(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetTurnsUntilVictorySession(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetName(lua_State*): MISMATCH; Non-padding instruction count: BE 73, object 54; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetTurnsUntilSession(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
 static int lIsNone(lua_State*); static int lGetID(lua_State*); static int lGetName(lua_State*); static int lCanChangeCustomName(lua_State*); static int lIsInSession(lua_State*); static int lIsInSpecialSession(lua_State*); static int lGetTurnsUntilSession(lua_State*); static int lGetTurnsUntilVictorySession(lua_State*);
// TODO: Phase1 CvLuaLeague::lCanProposeRepeal(lua_State*): MISMATCH; Non-padding instruction count: BE 55, object 54; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetEnactProposals(lua_State*): MISMATCH; Non-padding instruction count: BE 70, object 60; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetTextForChoice(lua_State*): MISMATCH; Non-padding instruction count: BE 81, object 73; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetChoicesForDecision(lua_State*): MISMATCH; Non-padding instruction count: BE 146, object 135; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCanProposeEnactAnyChoice(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCanProposeEnact(lua_State*): MISMATCH; Non-padding instruction count: BE 67, object 66; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetRepealProposalsOnHold(lua_State*): MISMATCH; Non-padding instruction count: BE 104, object 93; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetActiveResolutions(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 76; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetRepealProposals(lua_State*): MISMATCH; Non-padding instruction count: BE 104, object 93; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetInactiveResolutions(lua_State*): MISMATCH; Non-padding instruction count: BE 75, object 70; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetEnactProposalsOnHold(lua_State*): MISMATCH; Non-padding instruction count: BE 70, object 60; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsProposed(lua_State*): MISMATCH; Non-padding instruction count: BE 59, object 58; Civ5 changed/new instruction count unverified.
 static int lCanProposeEnactAnyChoice(lua_State*); static int lCanProposeEnact(lua_State*); static int lCanProposeRepeal(lua_State*); static int lIsProposed(lua_State*); static int lGetChoicesForDecision(lua_State*); static int lGetTextForChoice(lua_State*); static int lGetInactiveResolutions(lua_State*); static int lGetEnactProposals(lua_State*); static int lGetEnactProposalsOnHold(lua_State*); static int lGetRepealProposals(lua_State*); static int lGetRepealProposalsOnHold(lua_State*); static int lGetActiveResolutions(lua_State*);
// TODO: Phase1 CvLuaLeague::lIsUnitedNations(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetRemainingVotesForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCanPropose(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetHostMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCalculateStartingVotesForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsHostMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetSpentVotesForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCanVote(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetRemainingProposalsForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetCoreVotesForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
 static int lIsMember(lua_State*); static int lCanVote(lua_State*); static int lGetRemainingVotesForMember(lua_State*); static int lGetSpentVotesForMember(lua_State*); static int lGetCoreVotesForMember(lua_State*); static int lCalculateStartingVotesForMember(lua_State*); static int lCanPropose(lua_State*); static int lGetRemainingProposalsForMember(lua_State*); static int lIsHostMember(lua_State*); static int lGetHostMember(lua_State*); static int lIsUnitedNations(lua_State*);
// TODO: Phase1 CvLuaLeague::lGetProjectBuildingCostPerPlayer(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsProjectComplete(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetContributionTierThreshold(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetScienceyGreatPersonRateModifier(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetArtsyGreatPersonRateModifier(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetMemberContributionTier(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetMemberContribution(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetProjectCostPerPlayer(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsProjectActive(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetProjectCost(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
 static int lIsProjectActive(lua_State*); static int lIsProjectComplete(lua_State*); static int lGetProjectCostPerPlayer(lua_State*); static int lGetProjectBuildingCostPerPlayer(lua_State*); static int lGetProjectCost(lua_State*); static int lGetMemberContribution(lua_State*); static int lGetMemberContributionTier(lua_State*); static int lGetContributionTierThreshold(lua_State*); static int lGetArtsyGreatPersonRateModifier(lua_State*); static int lGetScienceyGreatPersonRateModifier(lua_State*);
// TODO: Phase1 CvLuaLeague::lGetCurrentEffectsSummary(lua_State*): MISMATCH; Non-padding instruction count: BE 169, object 132; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetLeagueSplashThisEraDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 77; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetLeagueSplashDescription(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 77; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetLeagueSplashTitle(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 77; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetGreatPersonRateModifierDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 65, object 57; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetLeagueSplashNextEraDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 77; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetProjectDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 72, object 64; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetProjectRewardTierDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 86, object 78; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetResolutionDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 109, object 101; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetResolutionName(lua_State*): MISMATCH; Non-padding instruction count: BE 113, object 105; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetMemberDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 81, object 73; Civ5 changed/new instruction count unverified.
 static int lGetResolutionName(lua_State*); static int lGetResolutionDetails(lua_State*); static int lGetMemberDetails(lua_State*); static int lGetProjectDetails(lua_State*); static int lGetProjectRewardTierDetails(lua_State*); static int lGetCurrentEffectsSummary(lua_State*); static int lGetLeagueSplashTitle(lua_State*); static int lGetLeagueSplashDescription(lua_State*); static int lGetLeagueSplashThisEraDetails(lua_State*); static int lGetLeagueSplashNextEraDetails(lua_State*); static int lGetGreatPersonRateModifierDetails(lua_State*);
// TODO: Phase1 CvLuaLeague::lResolutionTableHelper(lua_State*, int, CvResolution&): MISMATCH; Mnemonic divergence at BE #42 mov, object #42 call; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lProposalTableHelper(lua_State*, int, CvProposal&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
 static int lResolutionTableHelper(lua_State*, int, CvResolution&); static int lProposalTableHelper(lua_State*, int, CvProposal&);
};
