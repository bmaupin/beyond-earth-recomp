// TODO: Phase1 hksi_lua_setfield(lua_State*, int, char const*): MISMATCH; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<ResolutionTypes, std::__1::allocator<ResolutionTypes> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<CvString, std::__1::allocator<CvString> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
// TODO: Phase1 std::__1::__vector_base<int, std::__1::allocator<int> >::~__vector_base(): UNVERIFIED; complete export comparison pending (see docs/ai/phase1-lua-map-audit.md).
#include "CvGameCoreDLLPCH.h"
#include "CvLeague.h"
#include "CvLuaSupport.h"
#include "CvLuaLeague.h"

#define Method(N) lua_pushcclosure(L, l##N, 0); lua_setfield(L, t, #N)
#define League(L) CvLeague* pLeague = GetInstance(L)
#define NoArgInt(N, E) int CvLuaLeague::l##N(lua_State* L) { League(L); lua_pushinteger(L, (E)); return 1; }
#define NoArgBool(N, E) int CvLuaLeague::l##N(lua_State* L) { League(L); lua_pushboolean(L, (E)); return 1; }
#define PlayerInt(N, E) int CvLuaLeague::l##N(lua_State* L) { League(L); PlayerTypes p=(PlayerTypes)lua_tointeger(L,2); lua_pushinteger(L,(E)); return 1; }
#define PlayerBool(N, E) int CvLuaLeague::l##N(lua_State* L) { League(L); PlayerTypes p=(PlayerTypes)lua_tointeger(L,2); lua_pushboolean(L,(E)); return 1; }
#define ProjectBool(N, E) int CvLuaLeague::l##N(lua_State* L) { League(L); LeagueProjectTypes p=(LeagueProjectTypes)lua_tointeger(L,2); lua_pushboolean(L,(E)); return 1; }
#define ProjectInt(N, E) int CvLuaLeague::l##N(lua_State* L) { League(L); LeagueProjectTypes p=(LeagueProjectTypes)lua_tointeger(L,2); lua_pushinteger(L,(E)); return 1; }
#define StringMethod(N, E) int CvLuaLeague::l##N(lua_State* L) { League(L); CvString s=(E); lua_pushstring(L,s.c_str()); return 1; }

// TODO: Phase1 CvLuaLeague::HandleMissingInstance(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvLuaLeague::HandleMissingInstance(lua_State* L) { luaL_error(L, "Instance no longer exists."); }
// TODO: Phase1 CvLuaLeague::GetTypeName(): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
const char* CvLuaLeague::GetTypeName() { return "League"; }
// TODO: Phase1 CvLuaLeague::PushMethods(lua_State*, int): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
void CvLuaLeague::PushMethods(lua_State* L, int t) {
 Method(IsNone); Method(GetID); Method(GetName); Method(CanChangeCustomName); Method(IsInSession); Method(IsInSpecialSession); Method(GetTurnsUntilSession); Method(GetTurnsUntilVictorySession); Method(CanProposeEnactAnyChoice); Method(CanProposeEnact); Method(CanProposeRepeal); Method(IsProposed); Method(GetChoicesForDecision); Method(GetTextForChoice); Method(GetInactiveResolutions); Method(GetEnactProposals); Method(GetEnactProposalsOnHold); Method(GetRepealProposals); Method(GetRepealProposalsOnHold); Method(GetActiveResolutions); Method(IsMember); Method(CanVote); Method(GetRemainingVotesForMember); Method(GetSpentVotesForMember); Method(GetCoreVotesForMember); Method(CalculateStartingVotesForMember); Method(CanPropose); Method(GetRemainingProposalsForMember); Method(IsHostMember); Method(GetHostMember); Method(IsUnitedNations); Method(IsProjectActive); Method(IsProjectComplete); Method(GetProjectCostPerPlayer); Method(GetProjectBuildingCostPerPlayer); Method(GetProjectCost); Method(GetMemberContribution); Method(GetMemberContributionTier); Method(GetContributionTierThreshold); Method(GetArtsyGreatPersonRateModifier); Method(GetScienceyGreatPersonRateModifier); Method(GetResolutionName); Method(GetResolutionDetails); Method(GetMemberDetails); Method(GetProjectDetails); Method(GetProjectRewardTierDetails); Method(GetCurrentEffectsSummary); Method(GetLeagueSplashTitle); Method(GetLeagueSplashDescription); Method(GetLeagueSplashThisEraDetails); Method(GetLeagueSplashNextEraDetails); Method(GetGreatPersonRateModifierDetails);
}
// TODO: Phase1 CvLuaLeague::lIsNone(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lIsNone(lua_State* L) { lua_pushboolean(L, GetInstance(L, false) == NULL); return 1; }
// TODO: Phase1 CvLuaLeague::lGetID(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
NoArgInt(GetID, pLeague->GetID())
// TODO: Phase1 CvLuaLeague::lGetName(lua_State*): MISMATCH; Non-padding instruction count: BE 73, object 54; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetName(lua_State* L) { League(L); Localization::String n=pLeague->GetName(); CvString s=n.toUTF8(); lua_pushstring(L,s.c_str()); return 1; }
// TODO: Phase1 CvLuaLeague::lCanChangeCustomName(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
PlayerBool(CanChangeCustomName,pLeague->CanChangeCustomName(p))
// TODO: Phase1 CvLuaLeague::lIsInSession(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsInSpecialSession(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetTurnsUntilVictorySession(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetTurnsUntilSession(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
NoArgBool(IsInSession,pLeague->IsInSession()) NoArgBool(IsInSpecialSession,pLeague->IsInSpecialSession()) NoArgInt(GetTurnsUntilSession,pLeague->GetTurnsUntilSession()) NoArgInt(GetTurnsUntilVictorySession,pLeague->GetTurnsUntilVictorySession())
// TODO: Phase1 CvLuaLeague::lCanProposeEnactAnyChoice(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lCanProposeEnactAnyChoice(lua_State* L) { League(L); lua_pushboolean(L,pLeague->CanProposeEnactAnyChoice((ResolutionTypes)lua_tointeger(L,2),(PlayerTypes)lua_tointeger(L,3))); return 1; }
// TODO: Phase1 CvLuaLeague::lCanProposeEnact(lua_State*): MISMATCH; Non-padding instruction count: BE 67, object 66; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lCanProposeEnact(lua_State* L) { League(L); lua_pushboolean(L,pLeague->CanProposeEnact((ResolutionTypes)lua_tointeger(L,2),(PlayerTypes)lua_tointeger(L,3),lua_tointeger(L,4))); return 1; }
// TODO: Phase1 CvLuaLeague::lCanProposeRepeal(lua_State*): MISMATCH; Non-padding instruction count: BE 55, object 54; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lCanProposeRepeal(lua_State* L) { League(L); lua_pushboolean(L,pLeague->CanProposeRepeal(lua_tointeger(L,2),(PlayerTypes)lua_tointeger(L,3))); return 1; }
// TODO: Phase1 CvLuaLeague::lIsProposed(lua_State*): MISMATCH; Non-padding instruction count: BE 59, object 58; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lIsProposed(lua_State* L) { League(L); lua_pushboolean(L,pLeague->IsProposed(lua_tointeger(L,2),lua_toboolean(L,3))); return 1; }
// TODO: Phase1 CvLuaLeague::lGetChoicesForDecision(lua_State*): MISMATCH; Non-padding instruction count: BE 146, object 135; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetChoicesForDecision(lua_State* L) { League(L); std::vector<int> v=pLeague->GetChoicesForDecision((ResolutionDecisionTypes)lua_tointeger(L,2),(PlayerTypes)lua_tointeger(L,3)); lua_createtable(L,0,0); int t=lua_gettop(L); for(unsigned i=0;i<v.size();++i){lua_pushinteger(L,v[i]);lua_rawseti(L,t,i+1);} return 1; }
// TODO: Phase1 CvLuaLeague::lGetTextForChoice(lua_State*): MISMATCH; Non-padding instruction count: BE 81, object 73; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetTextForChoice(lua_State* L) { League(L); CvString s=pLeague->GetTextForChoice((ResolutionDecisionTypes)lua_tointeger(L,2),lua_tointeger(L,3)); lua_pushstring(L,s.c_str()); return 1; }
// TODO: Phase1 CvLuaLeague::lGetInactiveResolutions(lua_State*): MISMATCH; Non-padding instruction count: BE 75, object 70; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetInactiveResolutions(lua_State* L) { League(L); std::vector<ResolutionTypes> v=pLeague->GetInactiveResolutions(); lua_createtable(L,0,0); for(unsigned i=0;i<v.size();++i){lua_createtable(L,0,0);int t=lua_gettop(L);lua_pushinteger(L,v[i]);lua_setfield(L,t,"Type");lua_rawseti(L,-2,i+1);} return 1; }
#define ProposalTable(N, Getter, Extra) int CvLuaLeague::l##N(lua_State* L) { League(L); typename Getter::iterator it; Getter v=pLeague->Getter(); lua_createtable(L,0,0); int i=1; for(it=v.begin();it!=v.end();++it){lua_createtable(L,0,0);int t=lua_gettop(L);lProposalTableHelper(L,t,*it); Extra lua_rawseti(L,-2,i++);} return 1; }
// TODO: Phase1 CvLuaLeague::lGetEnactProposals(lua_State*): MISMATCH; Non-padding instruction count: BE 70, object 60; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetEnactProposals(lua_State* L) { League(L); EnactProposalList v=pLeague->GetEnactProposals(); lua_createtable(L,0,0); for(unsigned i=0;i<v.size();++i){lua_createtable(L,0,0);int t=lua_gettop(L);lProposalTableHelper(L,t,v[i]);lua_rawseti(L,-2,i+1);}return 1; }
// TODO: Phase1 CvLuaLeague::lGetEnactProposalsOnHold(lua_State*): MISMATCH; Non-padding instruction count: BE 70, object 60; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetEnactProposalsOnHold(lua_State* L) { League(L); EnactProposalList v=pLeague->GetEnactProposalsOnHold(); lua_createtable(L,0,0); for(unsigned i=0;i<v.size();++i){lua_createtable(L,0,0);int t=lua_gettop(L);lProposalTableHelper(L,t,v[i]);lua_rawseti(L,-2,i+1);}return 1; }
#define RepealMethod(N, G) int CvLuaLeague::l##N(lua_State* L) { League(L); RepealProposalList v=pLeague->G(); lua_createtable(L,0,0); for(unsigned i=0;i<v.size();++i){lua_createtable(L,0,0);int t=lua_gettop(L);lProposalTableHelper(L,t,v[i]);lua_pushinteger(L,v[i].GetTargetResolutionID());lua_setfield(L,t,"TargetResolutionID");lua_pushinteger(L,v[i].GetRepealDecision()->GetDecision());lua_setfield(L,t,"RepealDecision");lua_rawseti(L,-2,i+1);}return 1; }
// TODO: Phase1 CvLuaLeague::lGetRepealProposalsOnHold(lua_State*): MISMATCH; Non-padding instruction count: BE 104, object 93; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetRepealProposals(lua_State*): MISMATCH; Non-padding instruction count: BE 104, object 93; Civ5 changed/new instruction count unverified.
RepealMethod(GetRepealProposals,GetRepealProposals) RepealMethod(GetRepealProposalsOnHold,GetRepealProposalsOnHold)
// TODO: Phase1 CvLuaLeague::lGetActiveResolutions(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 76; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetActiveResolutions(lua_State* L) { League(L); ActiveResolutionList v=pLeague->GetActiveResolutions();lua_createtable(L,0,0);for(unsigned i=0;i<v.size();++i){lua_createtable(L,0,0);int t=lua_gettop(L);lResolutionTableHelper(L,t,v[i]);lua_pushinteger(L,v[i].GetTurnEnacted());lua_setfield(L,t,"TurnEnacted");lua_rawseti(L,-2,i+1);}return 1; }
// TODO: Phase1 CvLuaLeague::lGetRemainingVotesForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCanPropose(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCalculateStartingVotesForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsHostMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetSpentVotesForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lCanVote(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetRemainingProposalsForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetCoreVotesForMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
PlayerBool(IsMember,pLeague->IsMember(p)) PlayerBool(CanVote,pLeague->CanVote(p)) PlayerInt(GetRemainingVotesForMember,pLeague->GetRemainingVotesForMember(p)) PlayerInt(GetSpentVotesForMember,pLeague->GetSpentVotesForMember(p)) PlayerInt(GetCoreVotesForMember,pLeague->GetCoreVotesForMember(p)) PlayerInt(CalculateStartingVotesForMember,pLeague->CalculateStartingVotesForMember(p)) PlayerBool(CanPropose,pLeague->CanPropose(p)) PlayerInt(GetRemainingProposalsForMember,pLeague->GetRemainingProposalsForMember(p)) PlayerBool(IsHostMember,pLeague->IsHostMember(p))
// TODO: Phase1 CvLuaLeague::lIsProjectComplete(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsUnitedNations(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetHostMember(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetProjectCostPerPlayer(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lIsProjectActive(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetProjectCost(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
NoArgInt(GetHostMember,pLeague->GetHostMember()) NoArgBool(IsUnitedNations,pLeague->IsUnitedNations()) ProjectBool(IsProjectActive,pLeague->IsProjectActive(p)) ProjectBool(IsProjectComplete,pLeague->IsProjectComplete(p)) ProjectInt(GetProjectCostPerPlayer,pLeague->GetProjectCostPerPlayer(p)) ProjectInt(GetProjectCost,pLeague->GetProjectCost(p))
// TODO: Phase1 CvLuaLeague::lGetProjectBuildingCostPerPlayer(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetProjectBuildingCostPerPlayer(lua_State* L){League(L);lua_pushinteger(L,pLeague->GetProjectBuildingCostPerPlayer((BuildingTypes)lua_tointeger(L,2)));return 1;}
// TODO: Phase1 CvLuaLeague::lGetMemberContribution(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetMemberContribution(lua_State* L){League(L);lua_pushinteger(L,pLeague->GetMemberContribution((PlayerTypes)lua_tointeger(L,2),(LeagueProjectTypes)lua_tointeger(L,3)));return 1;}
// TODO: Phase1 CvLuaLeague::lGetMemberContributionTier(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetMemberContributionTier(lua_State* L){League(L);lua_pushinteger(L,pLeague->GetMemberContributionTier((PlayerTypes)lua_tointeger(L,2),(LeagueProjectTypes)lua_tointeger(L,3)));return 1;}
// TODO: Phase1 CvLuaLeague::lGetContributionTierThreshold(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetContributionTierThreshold(lua_State* L){League(L);lua_pushinteger(L,(int)pLeague->GetContributionTierThreshold((CvLeague::ContributionTier)lua_tointeger(L,2),(LeagueProjectTypes)lua_tointeger(L,3)));return 1;}
// TODO: Phase1 CvLuaLeague::lGetScienceyGreatPersonRateModifier(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetArtsyGreatPersonRateModifier(lua_State*): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
NoArgInt(GetArtsyGreatPersonRateModifier,pLeague->GetArtsyGreatPersonRateModifier()) NoArgInt(GetScienceyGreatPersonRateModifier,pLeague->GetScienceyGreatPersonRateModifier())
// TODO: Phase1 CvLuaLeague::lGetProjectDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 72, object 64; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetProjectRewardTierDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 86, object 78; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetResolutionDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 109, object 101; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetResolutionName(lua_State*): MISMATCH; Non-padding instruction count: BE 113, object 105; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetMemberDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 81, object 73; Civ5 changed/new instruction count unverified.
StringMethod(GetResolutionName,pLeague->GetResolutionName((ResolutionTypes)lua_tointeger(L,2),lua_tointeger(L,3),lua_tointeger(L,4),lua_toboolean(L,5))) StringMethod(GetResolutionDetails,pLeague->GetResolutionDetails((ResolutionTypes)lua_tointeger(L,2),(PlayerTypes)lua_tointeger(L,3),lua_tointeger(L,4),lua_tointeger(L,5))) StringMethod(GetMemberDetails,pLeague->GetMemberDetails((PlayerTypes)lua_tointeger(L,2),(PlayerTypes)lua_tointeger(L,3))) StringMethod(GetProjectDetails,pLeague->GetProjectDetails((LeagueProjectTypes)lua_tointeger(L,2),(PlayerTypes)luaL_optint(L,3,NO_PLAYER))) StringMethod(GetProjectRewardTierDetails,pLeague->GetProjectRewardTierDetails(lua_tointeger(L,2),(LeagueProjectTypes)lua_tointeger(L,3),(PlayerTypes)luaL_optint(L,4,NO_PLAYER)))
// TODO: Phase1 CvLuaLeague::lGetCurrentEffectsSummary(lua_State*): MISMATCH; Non-padding instruction count: BE 169, object 132; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lGetCurrentEffectsSummary(lua_State* L){League(L);std::vector<CvString> v=pLeague->GetCurrentEffectsSummary((PlayerTypes)luaL_optint(L,2,NO_PLAYER));lua_createtable(L,0,0);int t=lua_gettop(L);for(unsigned i=0;i<v.size();++i){lua_pushstring(L,v[i].c_str());lua_rawseti(L,t,i+1);}return 1;}
#define Splash(N, E) int CvLuaLeague::l##N(lua_State* L){League(L);CvString s=(E);lua_pushstring(L,s.c_str());return 1;}
// TODO: Phase1 CvLuaLeague::lGetLeagueSplashThisEraDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 77; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetLeagueSplashDescription(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 77; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetLeagueSplashTitle(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 77; Civ5 changed/new instruction count unverified.
// TODO: Phase1 CvLuaLeague::lGetLeagueSplashNextEraDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 85, object 77; Civ5 changed/new instruction count unverified.
Splash(GetLeagueSplashTitle,pLeague->GetLeagueSplashTitle((LeagueSpecialSessionTypes)lua_tointeger(L,2),lua_toboolean(L,3))) Splash(GetLeagueSplashDescription,pLeague->GetLeagueSplashDescription((LeagueSpecialSessionTypes)lua_tointeger(L,2),lua_toboolean(L,3))) Splash(GetLeagueSplashThisEraDetails,pLeague->GetLeagueSplashThisEraDetails((LeagueSpecialSessionTypes)lua_tointeger(L,2),lua_toboolean(L,3))) Splash(GetLeagueSplashNextEraDetails,pLeague->GetLeagueSplashNextEraDetails((LeagueSpecialSessionTypes)lua_tointeger(L,2),lua_toboolean(L,3)))
// TODO: Phase1 CvLuaLeague::lGetGreatPersonRateModifierDetails(lua_State*): MISMATCH; Non-padding instruction count: BE 65, object 57; Civ5 changed/new instruction count unverified.
StringMethod(GetGreatPersonRateModifierDetails,pLeague->GetGreatPersonRateModifierDetails((UnitClassTypes)lua_tointeger(L,2)))
// TODO: Phase1 CvLuaLeague::lResolutionTableHelper(lua_State*, int, CvResolution&): MISMATCH; Mnemonic divergence at BE #42 mov, object #42 call; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lResolutionTableHelper(lua_State* L,int t,CvResolution& r){lua_pushinteger(L,r.GetID());lua_setfield(L,t,"ID");lua_pushinteger(L,r.GetType());lua_setfield(L,t,"Type");lua_pushinteger(L,r.GetVoterDecision()->GetDecision());lua_setfield(L,t,"VoterDecision");lua_pushinteger(L,r.GetProposerDecision()->GetDecision());lua_setfield(L,t,"ProposerDecision");return 0;}
// TODO: Phase1 CvLuaLeague::lProposalTableHelper(lua_State*, int, CvProposal&): UNVERIFIED; Relocation-aware full equality not established; Civ5 changed/new instruction count unverified.
int CvLuaLeague::lProposalTableHelper(lua_State* L,int t,CvProposal& p){lResolutionTableHelper(L,t,p);lua_pushinteger(L,p.GetProposalPlayer());lua_setfield(L,t,"ProposalPlayer");return 0;}
