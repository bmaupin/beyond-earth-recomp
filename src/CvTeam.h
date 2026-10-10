#pragma once

class CvTeamTechs;

// Partial SDK declarations and the leading SDK member layout.
class CvTeam
{
public:
	int getAtWarCount(bool bIgnoreMinors) const;
	EraTypes GetCurrentEra() const;
	PlayerTypes getLeaderID() const;
	int getProjectCount(ProjectTypes eIndex) const;
	int GetTotalSecuredVotes() const;
	void init(TeamTypes eID);
	bool isAlive() const
	{
		return m_iAliveCount > 0;
	}
	bool isAtWar(TeamTypes eIndex) const;
	// Beyond Earth uses alien teams instead of barbarians.
	bool isAlien() const;
	bool isBridgeBuilding() const;
	bool isHasMet(TeamTypes eIndex) const;
	bool IsHomeOfUnitedNations() const;
	void uninit();
	CvTeamTechs* GetTeamTechs() const;

	virtual void Read(FDataStream& kStream);
	virtual void Write(FDataStream& kStream) const;

protected:
	TeamTypes m_eID;
	static CvTeam* m_aTeams;
	int m_iNumMembers;
	int m_iAliveCount;
	// TODO: CvTeam (remaining members).
};
