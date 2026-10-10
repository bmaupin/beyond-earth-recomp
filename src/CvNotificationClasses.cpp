#include "CvGameCoreDLLPCH.h"
#include "CvGameCoreDLLUtil.h"
#include "ICvDLLUserInterface.h"
#include "CvGameCoreUtils.h"

// Beyond Earth's entry allocation uses the sized delete overload.
void operator delete(void*, unsigned int) noexcept;

// must be included after all other headers
#include "LintFree.h"

CvNotificationEntry::CvNotificationEntry(void) : m_turnBlocking(0)
{
	// Beyond Earth leaves the default-constructed type string empty.
}

CvNotificationEntry::~CvNotificationEntry(void)
{
}

bool CvNotificationEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility&)
{
	m_strNotificationType = kResults.GetText("NotificationType");
	// Beyond Earth caches the byte-valued turn-blocking property.
	m_turnBlocking = kResults.GetInt("TurnBlocking");
	return true;
}

const char* CvNotificationEntry::GetTypeName()
{
	return m_strNotificationType.c_str();
}

CvNotificationXMLEntries::CvNotificationXMLEntries(void)
{
}

CvNotificationXMLEntries::~CvNotificationXMLEntries(void)
{
	DeleteArray();
}

std::vector<CvNotificationEntry*>& CvNotificationXMLEntries::GetNotificationEntries()
{
	return m_paNotificationEntries;
}

int CvNotificationXMLEntries::GetNumNotifications()
{
	return m_paNotificationEntries.size();
}

void CvNotificationXMLEntries::DeleteArray()
{
	for(std::vector<CvNotificationEntry*>::iterator it = m_paNotificationEntries.begin(); it != m_paNotificationEntries.end(); ++it)
	{
		CvNotificationEntry* pEntry = *it;
		if(pEntry)
		{
			pEntry->~CvNotificationEntry();
			::operator delete(pEntry, sizeof(CvNotificationEntry));
		}
		*it = NULL;
	}

	// Beyond Earth also clears its notification-name lookup map.
	m_mEntries.clear();
	m_paNotificationEntries.clear();
}

CvNotificationEntry* CvNotificationXMLEntries::GetEntry(int index)
{
	FAssert(index < static_cast<int>(m_paNotificationEntries.size()));

	if(index < static_cast<int>(m_paNotificationEntries.size()))
		return m_paNotificationEntries[index];
	return NULL;
}

CvNotificationEntry* CvNotificationXMLEntries::GetByID(uint hHash)
{
	EntryHashTable::iterator itr = m_mEntries.find(hHash);
	if(itr != m_mEntries.end())
		return GetEntry((*itr).second);
	return NULL;
}

CvNotificationEntry* CvNotificationXMLEntries::GetByString(const char* pszName)
{
	if(pszName && pszName[0] != 0)
		return GetByID(FString::Hash(pszName));
	return NULL;
}

// Beyond Earth rebuilds the hash-to-entry lookup after loading notification types.
void CvNotificationXMLEntries::UpdateMap()
{
	m_mEntries.clear();
	for(int i = 0; i < GetNumNotifications(); ++i)
	{
		m_mEntries.insert(std::make_pair(FString::Hash(m_paNotificationEntries[i]->GetTypeName()), i));
	}
}
