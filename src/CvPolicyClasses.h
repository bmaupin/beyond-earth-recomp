#pragma once

#ifndef CIV5_POLICY_CLASSES_H
#define CIV5_POLICY_CLASSES_H

class CvPolicyEntry: public CvBaseInfo
{
public:
	CvPolicyEntry(void);
	~CvPolicyEntry(void);

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

	// Beyond Earth adds kicker policies; the underlying implementation remains external.
	bool IsKickerPolicy() const;
	int GetFlavorValue(int i) const;
	int GetPrereqOrPolicies(int i) const;
	int GetLevel() const;
	int GetPolicyBranchType() const;
	int GetBuildingClassHealth(int i) const;
	// TODO: CvPolicyEntry (remaining SDK members and Beyond Earth changes).
};

class CvPolicyBranchEntry : public CvBaseInfo
{
public:
	int GetFreePolicy() const;
	int GetFreeFinishingPolicy() const;
	bool IsMutuallyExclusive() const;
	bool IsDelayWhenNoReligion() const;
	bool IsDelayWhenNoCulture() const;
	bool IsDelayWhenNoScience() const;
	bool IsDelayWhenNoCityStates() const;
};

class CvPolicyXMLEntries
{
public:
	int GetNumPolicies();
	int GetNumPolicies() const;
	CvPolicyEntry* GetPolicyEntry(int i);
	CvPolicyBranchEntry* GetPolicyBranchEntry(int i);
};

class CvPlayer;
class CvPlayerPolicies
{
public:
	int GetNumPolicyBranchesFinished() const;
	CvPolicyXMLEntries* GetPolicies() const;
	CvPlayer* GetPlayer();
	bool CanAdoptPolicy(PolicyTypes ePolicy, bool bIgnoreCost) const;
	bool WillFinishBranchIfAdopted(PolicyTypes ePolicy) const;
	bool IsPolicyBranchUnlocked(PolicyBranchTypes eBranch) const;
	bool CanUnlockPolicyBranch(PolicyBranchTypes eBranch);
	bool HasPolicy(PolicyTypes ePolicy) const;
	int GetNewKickersEarnedByAdoptingPolicy(PolicyTypes ePolicy, std::vector<PolicyTypes>& kickers) const;
};

#endif // CIV5_POLICY_CLASSES_H
