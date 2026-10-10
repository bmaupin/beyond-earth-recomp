#pragma once

#ifndef CIV5_NOTIFICATION_CLASSES_H
#define CIV5_NOTIFICATION_CLASSES_H

#include <map>

class CvDatabaseUtility;

class CvNotificationEntry
{
public:
	CvNotificationEntry(void);
	~CvNotificationEntry(void);
	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);
	const char* GetTypeName();

private:
	CvString m_strNotificationType;
	// Beyond Earth stores the TurnBlocking database value after the type string.
	char m_turnBlocking;
};

class CvNotificationXMLEntries
{
public:
	CvNotificationXMLEntries(void);
	~CvNotificationXMLEntries(void);

	typedef std::vector<CvNotificationEntry*> EntryArray;
	EntryArray& GetNotificationEntries();
	int GetNumNotifications();
	CvNotificationEntry* GetEntry(int index);
	CvNotificationEntry* GetByID(uint hHash);
	CvNotificationEntry* GetByString(const char* pszName);
	void DeleteArray();
	void UpdateMap();

private:
	EntryArray m_paNotificationEntries;
	typedef std::map<uint, int> EntryHashTable;
	EntryHashTable m_mEntries;
};

#endif // CIV5_NOTIFICATION_CLASSES_H
