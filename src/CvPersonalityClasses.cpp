#include "CvGameCoreDLLPCH.h"
#include "CvPersonalityClasses.h"
#include "CvDatabaseUtility.h"
#include "CvGameCoreDLLUtil.h"
#include "CvGlobals.h"
#include "CvPlayer.h"
#include "CvPlayerAI.h"
#include "CvGame.h"
#include <cmath>

void operator delete(void*, size_t) noexcept;

CvPersonalityTraitEntry::CvPersonalityTraitEntry() :
	m_bUnique(false),
	m_eCategoryType(NO_PERSONALITY_TRAIT_CATEGORY)
{
}

CvPersonalityTraitEntry::~CvPersonalityTraitEntry()
{
}

bool CvPersonalityTraitCategoryEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	return CvBaseInfo::CacheResults(kResults, kUtility);
}

bool CvPersonalityTraitEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults, kUtility))
		return false;

	m_bUnique = kResults.GetBool("Unique");
	const char* szCategoryType = kResults.GetText("PersonalityTraitCategoryType");
	m_eCategoryType = static_cast<PersonalityTraitCategoryTypes>(GC.getInfoTypeForString(szCategoryType));

	const char* szTraitType = GetType();
	m_perks.clear();
	static const char* szPerksQuery = "select PlayerPerks.ID as PlayerPerkID, * from PersonalityTraits_Perks inner join PlayerPerks on PlayerPerks.Type = PlayerPerkType where PersonalityTraitType = ?";
	std::string strQueryKey("PersonalityTraits_Perks");
	Database::Results* pPerks = kUtility.GetResults(strQueryKey);
	if(!pPerks)
		pPerks = kUtility.PrepareResults(strQueryKey, szPerksQuery);
	pPerks->Bind(1, szTraitType);
	while(pPerks->Step())
	{
		const PlayerPerkTypes ePerk = static_cast<PlayerPerkTypes>(pPerks->GetInt(0));
		const int iLevel = pPerks->GetInt(3);
		m_perks[iLevel].push_back(ePerk);
	}

	m_foreignPolicies.clear();
	static const char* szPoliciesQuery = "select ForeignPolicies.ID as ForeignPoliciesID, * from PersonalityTraits_ForeignPolicies inner join ForeignPolicies on ForeignPolicies.Type = ForeignPolicyType where PersonalityTraitType = ?";
	strQueryKey.assign("PersonalityTraits_ForeignPolicies");
	Database::Results* pPolicies = kUtility.GetResults(strQueryKey);
	if(!pPolicies)
		pPolicies = kUtility.PrepareResults(strQueryKey, szPoliciesQuery);
	pPolicies->Bind(1, szTraitType);
	while(pPolicies->Step())
	{
		const ForeignPolicyTypes ePolicy = static_cast<ForeignPolicyTypes>(pPolicies->GetInt(0));
		const int iLevel = pPolicies->GetInt(2);
		m_foreignPolicies[iLevel].push_back(ePolicy);
	}
	return true;
}

const std::vector<PlayerPerkTypes>* CvPersonalityTraitEntry::GetPerks(int iLevel) const
{
	PersonalityPerksByLevel::const_iterator it = m_perks.lower_bound(iLevel);
	return it != m_perks.end() ? &it->second : NULL;
}

const std::vector<ForeignPolicyTypes>* CvPersonalityTraitEntry::GetForeignPolicies(int iLevel) const
{
	PersonalityPoliciesByLevel::const_iterator it = m_foreignPolicies.lower_bound(iLevel);
	return it != m_foreignPolicies.end() ? &it->second : NULL;
}

bool CvPersonalityTraitEntry::HasForeignPolicyType(ForeignPolicyTypes eType) const
{
	for(PersonalityPoliciesByLevel::const_iterator it = m_foreignPolicies.begin(); it != m_foreignPolicies.end(); ++it)
	{
		const std::vector<ForeignPolicyTypes>& policies = it->second;
		if(std::find(policies.begin(), policies.end(), eType) != policies.end())
			return true;
	}
	return false;
}

int CvPersonalityTraitEntry::GetMaxLevel() const
{
	int iMaxLevel = 0;
	for(PersonalityPerksByLevel::const_iterator it = m_perks.begin(); it != m_perks.end(); ++it)
		iMaxLevel = std::max(iMaxLevel, it->first);
	for(PersonalityPoliciesByLevel::const_iterator it = m_foreignPolicies.begin(); it != m_foreignPolicies.end(); ++it)
		iMaxLevel = std::max(iMaxLevel, it->first);
	return iMaxLevel;
}

CvPersonalityEntry::CvPersonalityEntry() :
	m_eUniqueTrait(NO_PERSONALITY_TRAIT)
{
}

CvPersonalityEntry::~CvPersonalityEntry()
{
}

bool CvPersonalityEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults, kUtility))
		return false;

	m_scriptName = kResults.GetText("ScriptName");
	const char* szUniqueTrait = kResults.GetText("UniqueTrait");
	m_eUniqueTrait = static_cast<PersonalityTraitTypes>(GC.getInfoTypeForString(szUniqueTrait));
	return true;
}

CvReactionEntry::CvReactionEntry() :
	m_iRespectChange(0),
	m_iMinTurnsBetween(0),
	m_bConfrontation(false)
{
}

CvReactionEntry::~CvReactionEntry()
{
}

bool CvReactionEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults, kUtility))
		return false;

	m_iRespectChange = kResults.GetInt("RespectChange");
	m_iMinTurnsBetween = kResults.GetInt("MinTurnsBetween");
	m_bConfrontation = kResults.GetBool("IsConfrontation");
	return true;
}

CvPersonalityTrait::CvPersonalityTrait() :
	m_eTrait(NO_PERSONALITY_TRAIT),
	m_eOwner(NO_PLAYER),
	m_iLevel(1),
	m_pkInfo(NULL)
{
}

CvPersonalityTrait::CvPersonalityTrait(PersonalityTraitTypes eTrait, PlayerTypes eOwner) :
	m_eTrait(eTrait),
	m_eOwner(eOwner),
	m_iLevel(1),
	m_pkInfo(NULL)
{
	m_pkInfo = GC.getPersonalityTraitInfo(m_eTrait);
}

CvPersonalityTrait::CvPersonalityTrait(CvPersonalityTrait&& rhs)
{
	m_eTrait = rhs.m_eTrait;
	m_eOwner = rhs.m_eOwner;
	m_pkInfo = rhs.m_pkInfo;
	m_iLevel = rhs.m_iLevel;
	rhs.m_eTrait = NO_PERSONALITY_TRAIT;
	rhs.m_eOwner = NO_PLAYER;
	rhs.m_pkInfo = NULL;
	rhs.m_iLevel = 1;
}

CvPersonalityTrait::~CvPersonalityTrait()
{
}

void CvPersonalityTrait::Init()
{
}

// TODO: Match the remaining control-flow differences with Beyond Earth's implementation.
bool CvPersonalityTrait::CanLevelUp() const
{
	CvPlayer& kPlayer = GET_PLAYER(m_eOwner);
	if(!kPlayer.GetPlayerDiplomacy())
		return false;

	CvPlayerPersonality* pPersonality = kPlayer.GetPlayerPersonality();
	if(!pPersonality)
		return false;

	std::vector<std::unique_ptr<CvPersonalityTrait> >::const_iterator it = pPersonality->m_traits.begin();
	std::vector<std::unique_ptr<CvPersonalityTrait> >::const_iterator itEnd = pPersonality->m_traits.end();
	volatile bool bTraitNotFound;
	while(it != itEnd)
	{
		if((*it)->GetType() == m_eTrait)
			break;

		++it;
		bTraitNotFound = true;
	}
	bTraitNotFound = true;
	if(it != itEnd)
		bTraitNotFound = it->get() == NULL;

	const int iDiplomaticCapital = kPlayer.GetDiplomaticCapital();
	const int iTraitModificationCost = pPersonality->GetTraitModificationCost();
	const int iMaxTraitLevels = *reinterpret_cast<const int*>(reinterpret_cast<const char*>(&gGlobals) + 0x1d20);
	const bool bBelowMaxLevel = m_iLevel < iMaxTraitLevels;
	return !bTraitNotFound && iDiplomaticCapital >= iTraitModificationCost && bBelowMaxLevel;
}

// TODO: Match Beyond Earth's perk update flow in the disassembly.
void CvPersonalityTrait::UpdateEffects(bool bRemove)
{
	CvPlayerPerks* pPlayerPerks = GET_PLAYER(m_eOwner).GetPlayerPerks();
	for(int iLevel = 1; iLevel <= m_iLevel; ++iLevel)
	{
		const std::vector<PlayerPerkTypes>* pPerks = m_pkInfo->GetPerks(iLevel);
		if(!pPerks)
			continue;

		for(std::vector<PlayerPerkTypes>::const_iterator it = pPerks->begin(); it != pPerks->end(); ++it)
		{
			if(bRemove)
				pPlayerPerks->RemovePerk(*it);
			else if(iLevel == m_iLevel)
				pPlayerPerks->AddPerk(*it);
		}
	}
}

// TODO: Match Beyond Earth's foreign-policy update flow in the disassembly.
void CvPersonalityTrait::UpdateForeignPolicies(bool bRemove)
{
	CvPlayerDiplomacy* pDiplomacy = GET_PLAYER(m_eOwner).GetPlayerDiplomacy();
	if(!pDiplomacy)
		return;

	for(int iLevel = 0; iLevel <= m_iLevel; ++iLevel)
	{
		const std::vector<ForeignPolicyTypes>* pPolicies = m_pkInfo->GetForeignPolicies(iLevel);
		if(!pPolicies)
			continue;

		for(std::vector<ForeignPolicyTypes>::const_iterator it = pPolicies->begin(); it != pPolicies->end(); ++it)
		{
			if(bRemove)
			{
				if(pDiplomacy->HasForeignPolicy(*it))
					pDiplomacy->RemoveForeignPolicy(*it);
			}
			else if(!pDiplomacy->HasForeignPolicy(*it))
				pDiplomacy->AddForeignPolicy(*it);
		}
	}
}

// TODO: Match Beyond Earth's level-up and gameplay event sequence.
void CvPersonalityTrait::LevelUp()
{
	if(!CanLevelUp())
		return;

	CvPlayer& kPlayer = GET_PLAYER(m_eOwner);
	CvPlayerPersonality* pPersonality = kPlayer.GetPlayerPersonality();
	UpdateEffects(true);
	kPlayer.ChangeDiplomaticCapital(-pPersonality->GetTraitModificationCost());
	++m_iLevel;
	UpdateEffects(false);
	UpdateForeignPolicies(false);
	pPersonality->ChangeNumTraitModifications(1);
	gDLL->GameplayPersonalityTraitLeveledUp(m_eOwner, m_eTrait, m_iLevel);
}

// TODO: Match Beyond Earth's trait serialization disassembly.
void CvPersonalityTrait::Read(FDataStream& kStream)
{
	unsigned int uiVersion;
	kStream >> uiVersion;
	m_eTrait = static_cast<PersonalityTraitTypes>(CvInfosSerializationHelper::ReadHashed(kStream));
	kStream >> m_eOwner;
	if(uiVersion >= 3)
		kStream >> m_iLevel;
	m_pkInfo = GC.getPersonalityTraitInfo(m_eTrait);
}

// TODO: Match Beyond Earth's trait serialization disassembly.
void CvPersonalityTrait::Write(FDataStream& kStream) const
{
	int iVersion = 3;
	kStream << iVersion;
	CvInfosSerializationHelper::WriteHashed(kStream, m_eTrait);
	kStream << m_eOwner;
	kStream << m_iLevel;
}

// TODO: Match Beyond Earth's stream-operator wrapper disassembly.
void operator<<(FDataStream& kStream, const CvPersonalityTrait& kTrait)
{
	kTrait.Write(kStream);
}

// TODO: Match Beyond Earth's stream-operator wrapper disassembly.
void operator>>(FDataStream& kStream, CvPersonalityTrait& kTrait)
{
	kTrait.Read(kStream);
}

// TODO: Match Beyond Earth's constructor initialization sequence.
CvPlayerPersonality::CvPlayerPersonality() :
	m_player(NULL),
	m_luaContext(NULL),
	m_traitLevelCostPercentModifier(0),
	m_numTraitModifications(0)
{
	Reset();
}

// TODO: Match Beyond Earth's destructor disassembly.
CvPlayerPersonality::~CvPlayerPersonality()
{
}

// TODO: Match Beyond Earth's player and Lua-context initialization.
void CvPlayerPersonality::Init(CvPlayer* pPlayer, lua_State* pLuaContext)
{
	m_player = pPlayer;
	m_luaContext = pLuaContext;
	Reset();
}

// TODO: Match Beyond Earth's uninitialization disassembly.
void CvPlayerPersonality::Uninit()
{
	m_traits.clear();
	m_player = NULL;
	m_luaContext = NULL;
}

// TODO: Match Beyond Earth's reset sequence, including fact and debug arrays.
void CvPlayerPersonality::Reset()
{
	m_traits.clear();
	std::fill(m_respect, m_respect + 22, 0);
	std::fill(m_fear, m_fear + 22, 0);
	std::fill(m_aggressiveExpansionFactIDs, m_aggressiveExpansionFactIDs + 22, -1);
	std::fill(m_aggressiveMilitaryFactIDs, m_aggressiveMilitaryFactIDs + 22, -1);
	std::fill(m_caughtAgentFactIDs, m_caughtAgentFactIDs + 22, -1);
	std::fill(m_affinityDiffersFactIDs, m_affinityDiffersFactIDs + 22, -1);
	std::fill(m_orbitalDeploymentFactIDs, m_orbitalDeploymentFactIDs + 22, -1);
	std::fill(m_debugRespect, m_debugRespect + 22, 0);
	std::fill(m_debugFear, m_debugFear + 22, 0);
	m_traitLevelCostPercentModifier = 0;
	m_numTraitModifications = 0;
}

// TODO: Match Beyond Earth's trait setup and effect application.
void CvPlayerPersonality::InitTrait(CvPersonalityTrait& kTrait)
{
	kTrait.Init();
}

// TODO: Match Beyond Earth's trait lookup disassembly.
CvPersonalityTrait* CvPlayerPersonality::GetTrait(PersonalityTraitTypes eTrait)
{
	for(std::vector<std::unique_ptr<CvPersonalityTrait> >::iterator it = m_traits.begin(); it != m_traits.end(); ++it)
		if((*it)->GetType() == eTrait)
			return it->get();
	return NULL;
}

// TODO: Match Beyond Earth's const trait lookup disassembly.
const CvPersonalityTrait* CvPlayerPersonality::GetTrait(PersonalityTraitTypes eTrait) const
{
	for(std::vector<std::unique_ptr<CvPersonalityTrait> >::const_iterator it = m_traits.begin(); it != m_traits.end(); ++it)
		if((*it)->GetType() == eTrait)
			return it->get();
	return NULL;
}

// TODO: Match Beyond Earth's category lookup disassembly.
CvPersonalityTrait* CvPlayerPersonality::GetTraitInCategory(PersonalityTraitCategoryTypes eCategory)
{
	for(std::vector<std::unique_ptr<CvPersonalityTrait> >::iterator it = m_traits.begin(); it != m_traits.end(); ++it)
		if((*it)->GetInfo()->GetCategoryType() == eCategory)
			return it->get();
	return NULL;
}

// TODO: Match Beyond Earth's const category lookup disassembly.
const CvPersonalityTrait* CvPlayerPersonality::GetTraitInCategory(PersonalityTraitCategoryTypes eCategory) const
{
	for(std::vector<std::unique_ptr<CvPersonalityTrait> >::const_iterator it = m_traits.begin(); it != m_traits.end(); ++it)
		if((*it)->GetInfo()->GetCategoryType() == eCategory)
			return it->get();
	return NULL;
}

// TODO: Match Beyond Earth's trait add flow and side effects.
void CvPlayerPersonality::AddTrait(PersonalityTraitTypes eTrait, bool bFree)
{
	if(GetTrait(eTrait))
		return;

	CvPersonalityTraitEntry* pInfo = GC.getPersonalityTraitInfo(eTrait);
	if(!pInfo)
		return;

	CvPersonalityTrait* pCategoryTrait = GetTraitInCategory(pInfo->GetCategoryType());
	if(pCategoryTrait)
		RemoveTrait(pCategoryTrait->GetType());

	CvPersonalityTrait* pTrait = new CvPersonalityTrait(eTrait, m_player->GetID());
	pTrait->m_iLevel = 1;
	InitTrait(*pTrait);
	pTrait->UpdateEffects(false);
	pTrait->UpdateForeignPolicies(false);
	m_traits.push_back(std::unique_ptr<CvPersonalityTrait>(pTrait));

	if(!bFree)
		m_player->ChangeDiplomaticCapital(-GetTraitModificationCost());
	++m_numTraitModifications;
	RaiseAddEvents(eTrait);
}

// TODO: Match Beyond Earth's trait removal flow and side effects.
void CvPlayerPersonality::RemoveTrait(PersonalityTraitTypes eTrait)
{
	for(std::vector<std::unique_ptr<CvPersonalityTrait> >::iterator it = m_traits.begin(); it != m_traits.end(); ++it)
	{
		if((*it)->GetType() == eTrait)
		{
			(*it)->UpdateEffects(true);
			(*it)->UpdateForeignPolicies(true);
			m_traits.erase(it);
			RaiseRemoveEvents(eTrait);
			return;
		}
	}
}

// TODO: Match Beyond Earth's add-event sequence and hooks.
void CvPlayerPersonality::RaiseAddEvents(PersonalityTraitTypes eTrait) const
{
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(m_player->GetID());
	gDLL->SendAddPersonalityTrait(ePlayer, eTrait);
	gDLL->GameplayPersonalityTraitAdded(ePlayer, eTrait);
}

// TODO: Match Beyond Earth's remove-event sequence and hooks.
void CvPlayerPersonality::RaiseRemoveEvents(PersonalityTraitTypes eTrait) const
{
	const PlayerTypes ePlayer = static_cast<PlayerTypes>(m_player->GetID());
	gDLL->SendRemovePersonalityTrait(ePlayer, eTrait);
	gDLL->GameplayPersonalityTraitRemoved(ePlayer, eTrait);
}

// TODO: Match Beyond Earth's trait-cost calculation and global accesses.
int CvPlayerPersonality::GetTraitModificationCost() const
{
	const char* pGlobals = reinterpret_cast<const char*>(&gGlobals);
	const int iBaseCost = *reinterpret_cast<const int*>(pGlobals + 0x1d28);
	const float fCostGrowth = *reinterpret_cast<const float*>(pGlobals + 0x1d2c);
	const float fCostExponent = *reinterpret_cast<const float*>(pGlobals + 0x1d30);
	const int iCostRounding = static_cast<int>(*reinterpret_cast<const float*>(pGlobals + 0x1d34));
	const int iGrowth = static_cast<int>(static_cast<float>(m_numTraitModifications) * fCostGrowth);
	int iCost = iBaseCost + static_cast<int>(std::pow(static_cast<double>(iGrowth), static_cast<double>(fCostExponent)));
	iCost = (iCost * (m_traitLevelCostPercentModifier + 100)) / 100;
	iCost = (iCost * GC.getGame().getGameSpeedInfo().getDiploTraitModificationCostPercent()) / 100;
	iCost = (iCost * m_player->getHandicapInfo().getDiploTraitModificationCostPercent()) / 100;
	return iCost - (iCost % iCostRounding);
}

// TODO: Match Beyond Earth's personality-info lookup disassembly.
const CvPersonalityEntry* CvPlayerPersonality::GetPersonalityInfo() const
{
	return m_player ? GC.getPersonalityInfo(m_player->getPersonalityType()) : NULL;
}

// TODO: Match Beyond Earth's fear lookup disassembly.
int CvPlayerPersonality::GetFear(PlayerTypes eOtherPlayer) const
{
	return m_fear[eOtherPlayer] + m_debugFear[eOtherPlayer];
}

// TODO: Match Beyond Earth's player-personality serialization disassembly.
void CvPlayerPersonality::Read(FDataStream& kStream)
{
	unsigned int uiVersion;
	unsigned int uiTraitCount;
	kStream >> uiVersion;
	kStream >> uiTraitCount;
	Reset();
	for(unsigned int i = 0; i < uiTraitCount; ++i)
	{
		std::unique_ptr<CvPersonalityTrait> pTrait(new CvPersonalityTrait());
		pTrait->Read(kStream);
		InitTrait(*pTrait);
		m_traits.push_back(std::move(pTrait));
	}
	if(uiVersion >= 2)
		for(int i = 0; i < 22; ++i)
			kStream >> m_respect[i];
	if(uiVersion >= 3)
		for(int i = 0; i < 22; ++i)
			kStream >> m_fear[i];
	if(uiVersion >= 4)
		kStream >> m_traitLevelCostPercentModifier;
	if(uiVersion >= 6)
		kStream >> m_numTraitModifications;
	if(uiVersion >= 5)
	{
		for(int i = 0; i < 22; ++i)
			kStream >> m_aggressiveExpansionFactIDs[i];
		for(int i = 0; i < 22; ++i)
			kStream >> m_aggressiveMilitaryFactIDs[i];
		for(int i = 0; i < 22; ++i)
			kStream >> m_caughtAgentFactIDs[i];
		for(int i = 0; i < 22; ++i)
			kStream >> m_affinityDiffersFactIDs[i];
		if(uiVersion >= 7)
			for(int i = 0; i < 22; ++i)
				kStream >> m_orbitalDeploymentFactIDs[i];
	}
}

// TODO: Match Beyond Earth's player-personality serialization disassembly.
void CvPlayerPersonality::Write(FDataStream& kStream) const
{
	int iVersion = 7;
	unsigned int uiTraitCount = static_cast<unsigned int>(m_traits.size());
	kStream << iVersion;
	kStream << uiTraitCount;
	for(std::vector<std::unique_ptr<CvPersonalityTrait> >::const_iterator it = m_traits.begin(); it != m_traits.end(); ++it)
		(*it)->Write(kStream);
	for(int i = 0; i < 22; ++i)
		kStream << m_respect[i];
	for(int i = 0; i < 22; ++i)
		kStream << m_fear[i];
	kStream << m_traitLevelCostPercentModifier;
	kStream << m_numTraitModifications;
	for(int i = 0; i < 22; ++i)
		kStream << m_aggressiveExpansionFactIDs[i];
	for(int i = 0; i < 22; ++i)
		kStream << m_aggressiveMilitaryFactIDs[i];
	for(int i = 0; i < 22; ++i)
		kStream << m_caughtAgentFactIDs[i];
	for(int i = 0; i < 22; ++i)
		kStream << m_affinityDiffersFactIDs[i];
	for(int i = 0; i < 22; ++i)
		kStream << m_orbitalDeploymentFactIDs[i];
}

// TODO: Implement target-only CvConversationEntry constructor, destructor, and CacheResults.
// TODO: Implement target-only CvPersonalityTraitCategoryEntry constructor and destructor.
// TODO: Implement target-only CvPersonalityTrait::GetNumForiegnPolicies() const.
// TODO: Implement target-only CvPersonalityTrait::GetNumForiegnPoliciesAtLevel(int) const.
// TODO: Implement target-only CvPlayerPersonality::CalcRespectChange(CvPlayerReaction const&) const.
// TODO: Implement target-only CvPlayerPersonality::CalculateApproach(PlayerTypes&) const.
// TODO: Implement target-only CvPlayerPersonality::CalculateOpinion(PlayerTypes&) const.
// TODO: Implement target-only CvPlayerPersonality::ChangeRespect(PlayerTypes, int).
// TODO: Implement target-only CvPlayerPersonality::CheckFacts().
// TODO: Implement target-only CvPlayerPersonality::DoAgreementsAdvisor().
// TODO: Implement target-only CvPlayerPersonality::DoTurn().
// TODO: Implement target-only CvPlayerPersonality::GetFearStage(PlayerTypes) const.
// TODO: Implement target-only CvPlayerPersonality::GetHighestFear() const.
// TODO: Implement target-only CvPlayerPersonality::GetRespect(PlayerTypes) const.
// TODO: Implement target-only CvPlayerPersonality::GetRespectStage(PlayerTypes) const.
// TODO: Implement target-only CvPlayerPersonality::InitStartingPersonality().
// TODO: Implement target-only CvPlayerPersonality::IsFearStageOrHigher(StageTypes, PlayerTypes) const.
// TODO: Implement target-only CvPlayerPersonality::IsRespectStageOrHigher(StageTypes, PlayerTypes) const.
// TODO: Implement target-only CvPlayerPersonality::RecalculateFear(PlayerTypes).
// TODO: Implement target-only CvPlayerPersonality::ReceiveReaction(CvPlayerReaction&).
// TODO: Implement target-only CvPlayerPersonality::SendReaction(CvPlayerReaction&).
// TODO: Implement target-only CvPlayerPersonality::SetDebugFear(PlayerTypes, int).
// TODO: Implement target-only CvPlayerPersonality::SetDebugRespect(PlayerTypes, int).
// TODO: Implement target-only CvPlayerPersonality::SetRespect(PlayerTypes, int).
// TODO: Implement target-only CvPlayerPersonality::UpdateAffinityDiffersFact(PlayerTypes).
// TODO: Implement target-only CvPlayerPersonality::UpdateAggressiveExpansionFact(PlayerTypes).
// TODO: Implement target-only CvPlayerPersonality::UpdateAggressiveMilitaryFact(PlayerTypes).
// TODO: Implement target-only CvPlayerPersonality::UpdateCaughtAgentFact(PlayerTypes).
// TODO: Implement target-only CvPlayerPersonality::UpdateFacts().
// TODO: Implement target-only CvPlayerPersonality::UpdateFear().
// TODO: Implement target-only CvPlayerPersonality::UpdateOrbitalDeploymentFact(PlayerTypes, CvUnit const&).
// TODO: Implement target-only CvPlayerReaction::CvPlayerReaction().
// TODO: Implement target-only CvPlayerReaction::CvPlayerReaction(ReactionTypes, PlayerTypes, PlayerTypes).
// TODO: Implement target-only CvPlayerReaction::CvPlayerReaction(ReactionTypes, PlayerTypes, PlayerTypes, int, int).
// TODO: Implement target-only CvPlayerReaction::GetPlayerReactionLogFileName(PlayerTypes).
// TODO: Implement target-only CvPlayerReaction::GetPlot() const.
// TODO: Implement target-only CvPlayerReaction::GetReactionLogFileName().
// TODO: Implement target-only CvPlayerReaction::Log() const.
// TODO: Implement target-only CvPlayerReaction::Read(FDataStream&).
// TODO: Implement target-only CvPlayerReaction::Resolve().
// TODO: Implement target-only CvPlayerReaction::Write(FDataStream&) const.
// TODO: Implement target-only CvStageEntry constructor, destructor, and CacheResults.
// TODO: Implement target-only CvTopicEntry constructor, destructor, and CacheResults.
// TODO: Implement target-only operator<<(FDataStream&, CvPlayerPersonality const&).
// TODO: Implement target-only operator>>(FDataStream&, CvPlayerPersonality&).
// TODO: Implement target-only operator<<(FDataStream&, CvPlayerReaction const&).
// TODO: Implement target-only operator>>(FDataStream&, CvPlayerReaction&).
