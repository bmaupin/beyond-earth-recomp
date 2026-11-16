#pragma once

#include "CvEnums.h"
#include "CvInfos.h"
#include "ASL/HashMap.h"
#include <memory>
#include <string>
#include <vector>

class CvPlayer;
class CvCity;
class CvDatabaseUtility;
class FDataStream;
struct lua_State;
namespace Database { class Results; }

typedef ASL::StdLib::HashMap::hash_map<int, std::vector<PlayerPerkTypes> > PersonalityPerksByLevel;
typedef ASL::StdLib::HashMap::hash_map<int, std::vector<ForeignPolicyTypes> > PersonalityPoliciesByLevel;

class CvPersonalityTraitCategoryEntry : public CvBaseInfo
{
public:
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
};

class CvPersonalityTraitEntry : public CvBaseInfo
{
public:
	CvPersonalityTraitEntry();
	virtual ~CvPersonalityTraitEntry();
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	const std::vector<PlayerPerkTypes>* GetPerks(int iLevel) const;
	const std::vector<ForeignPolicyTypes>* GetForeignPolicies(int iLevel) const;
	bool HasForeignPolicyType(ForeignPolicyTypes eType) const;
	int GetMaxLevel() const;
	bool IsUnique() const { return m_bUnique; }
	PersonalityTraitCategoryTypes GetCategoryType() const { return m_eCategoryType; }

private:
	bool m_bUnique;
	PersonalityTraitCategoryTypes m_eCategoryType;
	PersonalityPerksByLevel m_perks;
	PersonalityPoliciesByLevel m_foreignPolicies;
};

class CvPersonalityEntry : public CvBaseInfo
{
public:
	CvPersonalityEntry();
	virtual ~CvPersonalityEntry();
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	const std::string& GetScriptName() const { return m_scriptName; }
	PersonalityTraitTypes GetUniqueTraitType() const { return m_eUniqueTrait; }

private:
	std::string m_scriptName;
	PersonalityTraitTypes m_eUniqueTrait;
};

class CvReactionEntry : public CvBaseInfo
{
public:
	CvReactionEntry();
	virtual ~CvReactionEntry();
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	int GetRespectChange() const { return m_iRespectChange; }
	int GetMinTurnsBetween() const { return m_iMinTurnsBetween; }
	bool IsConfrontation() const { return m_bConfrontation; }

private:
	int m_iRespectChange;
	int m_iMinTurnsBetween;
	bool m_bConfrontation;
};

class CvPersonalityTrait
{
public:
	CvPersonalityTrait();
	CvPersonalityTrait(PersonalityTraitTypes eTrait, PlayerTypes eOwner);
	CvPersonalityTrait(CvPersonalityTrait&& rhs);
	~CvPersonalityTrait();
	void Init();
	bool CanLevelUp() const;
	void LevelUp();
	void UpdateEffects(bool bAdd);
	void UpdateForeignPolicies(bool bAdd);
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream) const;
	PersonalityTraitTypes GetType() const { return m_eTrait; }
	PlayerTypes GetOwner() const { return m_eOwner; }
	int GetLevel() const { return m_iLevel; }
	const CvPersonalityTraitEntry* GetInfo() const { return m_pkInfo; }

private:
	friend class CvPlayerPersonality;
	PersonalityTraitTypes m_eTrait;
	PlayerTypes m_eOwner;
	int m_iLevel;
	CvPersonalityTraitEntry* m_pkInfo;
};

class CvPlayerDiplomacy
{
public:
	bool HasForeignPolicy(ForeignPolicyTypes ePolicy) const;
	void AddForeignPolicy(ForeignPolicyTypes ePolicy);
	void RemoveForeignPolicy(ForeignPolicyTypes ePolicy);
};

class CvPlayerPersonality
{
public:
	CvPlayerPersonality();
	~CvPlayerPersonality();
	void Init(CvPlayer* pPlayer, lua_State* pLuaContext);
	void Uninit();
	void Reset();
	void InitTrait(CvPersonalityTrait& kTrait);
	CvPersonalityTrait* GetTrait(PersonalityTraitTypes eTrait);
	const CvPersonalityTrait* GetTrait(PersonalityTraitTypes eTrait) const;
	CvPersonalityTrait* GetTraitInCategory(PersonalityTraitCategoryTypes eCategory);
	const CvPersonalityTrait* GetTraitInCategory(PersonalityTraitCategoryTypes eCategory) const;
	void AddTrait(PersonalityTraitTypes eTrait, bool bFree = false);
	void RemoveTrait(PersonalityTraitTypes eTrait);
	void RaiseAddEvents(PersonalityTraitTypes eTrait) const;
	void RaiseRemoveEvents(PersonalityTraitTypes eTrait) const;
	int GetTraitModificationCost() const;
	const CvPersonalityEntry* GetPersonalityInfo() const;
	int GetFear(PlayerTypes eOtherPlayer) const;
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream) const;
	void ChangeNumTraitModifications(int iChange) { m_numTraitModifications += iChange; }

private:
	friend class CvPersonalityTrait;

	CvPlayer* m_player;
	lua_State* m_luaContext;
	std::vector<std::unique_ptr<CvPersonalityTrait> > m_traits;
	int m_respect[22];
	int m_fear[22];
	int m_traitLevelCostPercentModifier;
	int m_numTraitModifications;
	int m_aggressiveExpansionFactIDs[22];
	int m_aggressiveMilitaryFactIDs[22];
	int m_caughtAgentFactIDs[22];
	int m_affinityDiffersFactIDs[22];
	int m_orbitalDeploymentFactIDs[22];
	int m_debugRespect[22];
	int m_debugFear[22];
};

void operator<<(FDataStream& kStream, const CvPersonalityTrait& kTrait);
void operator>>(FDataStream& kStream, CvPersonalityTrait& kTrait);

namespace CvInfosSerializationHelper
{
int ReadHashed(FDataStream& kStream, bool* bValid = NULL);
bool WriteHashed(FDataStream& kStream, PersonalityTraitTypes eTrait);
}
