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
	// TODO: CvPolicyEntry (remaining SDK members and Beyond Earth changes).
};

#endif // CIV5_POLICY_CLASSES_H
