#include "CvGameCoreDLLPCH.h"
#include "CvEmphasisClasses.h"
#include "CvGameCoreDLLUtil.h"
#include "CvDatabaseUtility.h"
#include "CvInfosSerializationHelper.h"
#include "ICvDLLUserInterface.h"

// Clang 3.4 does not emit Beyond Earth's sized delete expression automatically.
void operator delete(void*, size_t) noexcept;

#include "LintFree.h"

CvEmphasisEntry::CvEmphasisEntry() :
	m_bAvoidGrowth(false),
	m_piYieldModifiers(NULL)
{
}

CvEmphasisEntry::~CvEmphasisEntry()
{
	SAFE_DELETE_ARRAY(m_piYieldModifiers);
}

bool CvEmphasisEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults, kUtility))
		return false;

	// Beyond Earth omits the GreatPeople column and evaluates GetType first.
	m_bAvoidGrowth = kResults.GetBool("AvoidGrowth");
	const char* szEmphasizeType = GetType();
	kUtility.SetYields(m_piYieldModifiers, "EmphasizeInfo_Yields", "EmphasizeType", szEmphasizeType);
	return true;
}

bool CvEmphasisEntry::IsAvoidGrowth() const
{
	return m_bAvoidGrowth;
}

int CvEmphasisEntry::GetYieldChange(int i) const
{
	return m_piYieldModifiers ? m_piYieldModifiers[i] : -1;
}

CvEmphasisXMLEntries::CvEmphasisXMLEntries()
{
}

CvEmphasisXMLEntries::~CvEmphasisXMLEntries()
{
	DeleteArray();
}

std::vector<CvEmphasisEntry*>& CvEmphasisXMLEntries::GetEmphasisEntries()
{
	return m_paEmphasisEntries;
}

int CvEmphasisXMLEntries::GetNumEmphases()
{
	return m_paEmphasisEntries.size();
}

void CvEmphasisXMLEntries::DeleteArray()
{
	for(std::vector<CvEmphasisEntry*>::iterator it = m_paEmphasisEntries.begin(); it != m_paEmphasisEntries.end(); ++it)
	{
		// Beyond Earth uses sized deletion and clears even an already-null slot.
		CvEmphasisEntry* pEntry = *it;
		if(pEntry)
		{
			pEntry->~CvEmphasisEntry();
			::operator delete(pEntry, sizeof(CvEmphasisEntry));
		}
		*it = NULL;
	}
	m_paEmphasisEntries.clear();
}

CvEmphasisEntry* CvEmphasisXMLEntries::GetEntry(int index)
{
	return m_paEmphasisEntries[index];
}

CvCityEmphases::CvCityEmphases()
{
	m_pbEmphasize = NULL;
}

CvCityEmphases::~CvCityEmphases()
{
}

void CvCityEmphases::Init(CvEmphasisXMLEntries* pEmphases, CvCity* pCity)
{
	m_pEmphases = pEmphases;
	m_pCity = pCity;
	Reset();
}

void CvCityEmphases::Uninit()
{
	SAFE_DELETE_ARRAY(m_pbEmphasize);
}

void CvCityEmphases::Reset()
{
	Uninit();
	m_iEmphasizeAvoidGrowthCount = 0;

	for(int iI = 0; iI < NUM_YIELD_TYPES; iI++)
		m_aiEmphasizeYieldCount[iI] = 0;

	// Beyond Earth uses an unsigned allocation bound; retain its allocator provenance.
#line 147 "../../../Civ5/Src/App/CvGameCoreDLL_Expansion1/CvEmphasisClasses.cpp"
	m_pbEmphasize = FNEW(bool[static_cast<unsigned int>(GC.getNumEmphasisInfos())], c_eCiv5GameplayDLL, 0);
#line 120 "src/CvEmphasisClasses.cpp"
	for(int iI = 0; iI < GC.getNumEmphasisInfos(); iI++)
		m_pbEmphasize[iI] = false;
}

void CvCityEmphases::SetEmphasize(EmphasizeTypes eIndex, bool bNewValue)
{
	if(IsEmphasize(eIndex) != bNewValue)
	{
		m_pbEmphasize[eIndex] = bNewValue;

		CvEmphasisEntry* pkEmphasis = GC.getEmphasisInfo(eIndex);
		// Beyond Earth tolerates a missing entry and has no Great People counter.
		if(!pkEmphasis)
			return;

		if(pkEmphasis->IsAvoidGrowth())
			m_iEmphasizeAvoidGrowthCount += IsEmphasize(eIndex) ? 1 : -1;

		for(int iI = 0; iI < NUM_YIELD_TYPES; iI++)
		{
			if(pkEmphasis->GetYieldChange(iI))
				m_aiEmphasizeYieldCount[iI] += IsEmphasize(eIndex) ? 1 : -1;
		}

		if((m_pCity->getOwner() == GC.getGame().getActivePlayer()) && m_pCity->isCitySelected())
			GC.GetEngineUserInterface()->setDirty(SelectionButtons_DIRTY_BIT, true);
	}
}

void CvCityEmphases::Read(FDataStream& kStream)
{
	unsigned int uiVersion;
	kStream >> uiVersion;
	kStream >> m_iEmphasizeAvoidGrowthCount;
	for(int iI = 0; iI < NUM_YIELD_TYPES; iI++)
		kStream >> m_aiEmphasizeYieldCount[iI];
	CvInfosSerializationHelper::ReadHashedDataArray(kStream, m_pbEmphasize, GC.getNumEmphasisInfos());
}

void CvCityEmphases::Write(FDataStream& kStream)
{
	// Beyond Earth writes the version through the signed stream overload.
	int uiVersion = 1;
	kStream << uiVersion;
	kStream << m_iEmphasizeAvoidGrowthCount;
	for(int iI = 0; iI < NUM_YIELD_TYPES; iI++)
		kStream << m_aiEmphasizeYieldCount[iI];
	CvInfosSerializationHelper::WriteHashedDataArray<EmphasizeTypes, bool>(kStream, m_pbEmphasize, GC.getNumEmphasisInfos());
}

int CvCityEmphases::GetEmphasizeAvoidGrowthCount()
{
	return m_iEmphasizeAvoidGrowthCount;
}

bool CvCityEmphases::IsEmphasizeAvoidGrowth()
{
	return GetEmphasizeAvoidGrowthCount() > 0;
}

int CvCityEmphases::GetEmphasizeYieldCount(YieldTypes eIndex)
{
	if(eIndex >= 0 && eIndex < NUM_YIELD_TYPES)
		return m_aiEmphasizeYieldCount[eIndex];
	return 0;
}

bool CvCityEmphases::IsEmphasizeYield(YieldTypes eIndex)
{
	return GetEmphasizeYieldCount(eIndex) > 0;
}

bool CvCityEmphases::IsEmphasize(EmphasizeTypes eIndex)
{
	if(!m_pbEmphasize)
		return false;
	return m_pbEmphasize[eIndex];
}
