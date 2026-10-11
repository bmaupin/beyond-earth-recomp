#include "CvGameCoreDLLPCH.h"
#include "CvDatabaseUtility.h"
#include "CvFlavorManager.h"
#include "CvInfosSerializationHelper.h"
#include "CvCitySpecializationAI.h"
#include "Lua/CvLuaSupport.h"
#include "CvLocalization.h"
#include "CvGameCoreDLLUtil/include/ICvDLLUserInterface.h"
#include "CvGameCoreDLLUtil/include/LinkedList.h"
#include <algorithm>
#include <cmath>
#include <climits>

void operator delete(void*, size_t) noexcept;
void operator delete[](void*, size_t) noexcept;
FDataStream& operator>>(FDataStream&, TechTypes&);
FDataStream& operator<<(FDataStream&, const TechTypes&);
extern bool TechBind(Database::Results*, int, const char*, int, bool) asm("_ZN8Database7Results4BindEiPKcib");
static_assert(sizeof(CvBaseInfo) == 0x74, "Beyond Earth base layout");
static_assert(sizeof(CvTechEntry) == 0x12c, "Beyond Earth technology layout");
static_assert(sizeof(CvTechXMLEntries) == 12, "Beyond Earth technology collection layout");
static_assert(sizeof(CvPlayerTechs) == 52, "Beyond Earth player technology layout");
static_assert(sizeof(CvTeamTechs) == 28, "Beyond Earth team technology layout");
static_assert(sizeof(CvTechAI) == 0x524, "Beyond Earth technology AI allocation layout");
static_assert(sizeof(CLLNode<TechTypes>) == 16, "Beyond Earth research queue node layout");

CvTechEntry::CvTechEntry() :
 m_iAIWeight(0), m_iAITradeModifier(0), m_iResearchCost(0), m_iAdvancedStartCost(0), m_iEra(NO_ERA),
 m_iFeatureProductionModifier(0), m_iUnitFortificationModifier(0), m_iUnitBaseHealModifier(0), m_iUnitBaseMiasmaHeal(0),
 m_iWorkerSpeedModifier(0), m_iFirstFreeUnitClass(NO_UNITCLASS), m_iFirstFreeTechs(0), m_iEmbarkedMoveChange(0),
 m_iInternationalTradeRoutesChange(0), m_iInfluenceSpreadModifier(0), m_iExtraVotesPerDiplomat(0),
 m_gridRadius(0), m_gridDegrees(0), m_leafTech(false), m_bEndsGame(false), m_bAllowsEmbarking(false),
 m_bAllowsDeepWaterCityMove(false), m_bRepeat(false), m_bTrade(false),
 m_bDisable(false), m_bGoodyTech(false), m_bExtraWaterSeeFrom(false), m_bMapCentering(false), m_bMapVisible(false),
 m_bMapTrading(false), m_bTechTrading(false), m_bGoldTrading(false), m_bBridgeBuilding(false), m_bWaterWork(false),
 m_bTriggersArchaeologicalSites(false), m_bAllowsMiasmaImmunity(false), m_piAffinities(NULL), m_piDomainExtraMoves(NULL),
 m_piTradeRouteDomainExtraRange(NULL), m_piFlavorValue(NULL), m_piPrereqOrTechs(NULL), m_piPrereqAndTechs(NULL),
 m_pabFreePlayerPerks(NULL), m_pabFreePromotion(NULL)
{}
CvTechEntry::~CvTechEntry()
{
 SAFE_DELETE_ARRAY(m_piAffinities);
 SAFE_DELETE_ARRAY(m_piDomainExtraMoves);
 SAFE_DELETE_ARRAY(m_piTradeRouteDomainExtraRange);
 SAFE_DELETE_ARRAY(m_piFlavorValue);
 SAFE_DELETE_ARRAY(m_piPrereqOrTechs);
 SAFE_DELETE_ARRAY(m_piPrereqAndTechs);
 SAFE_DELETE_ARRAY(m_pabFreePromotion);
 SAFE_DELETE_ARRAY(m_pabFreePlayerPerks);
}

bool CvTechEntry::CacheResults(Database::Results& r, CvDatabaseUtility& u)
{
 if (!CvBaseInfo::CacheResults(r, u)) return false;
 m_iAIWeight = r.GetInt("AIWeight");
 m_iAITradeModifier = r.GetInt("AITradeModifier");
 m_iResearchCost = r.GetInt("Cost");
 m_iAdvancedStartCost = r.GetInt("AdvancedStartCost");
 m_iFeatureProductionModifier = r.GetInt("FeatureProductionModifier");
 m_iUnitFortificationModifier = r.GetInt("UnitFortificationModifier");
 m_iUnitBaseHealModifier = r.GetInt("UnitBaseHealModifier");
 m_iUnitBaseMiasmaHeal = r.GetInt("UnitBaseMiasmaHeal");
 m_iWorkerSpeedModifier = r.GetInt("WorkerSpeedModifier");
 m_iFirstFreeTechs = r.GetInt("FirstFreeTechs");
 m_iEmbarkedMoveChange = r.GetInt("EmbarkedMoveChange");
 m_iInternationalTradeRoutesChange = r.GetInt("InternationalTradeRoutesChange");
 m_iInfluenceSpreadModifier = r.GetInt("InfluenceSpreadModifier");
 m_iExtraVotesPerDiplomat = r.GetInt("ExtraVotesPerDiplomat");
 m_bEndsGame = r.GetBool("EndsGame");
 m_bAllowsEmbarking = r.GetBool("AllowsEmbarking");
 m_bAllowsDeepWaterCityMove = r.GetBool("AllowsDeepWaterCityMovement");
 m_bRepeat = r.GetBool("Repeat");
 m_bTrade = r.GetBool("Trade");
 m_bDisable = r.GetBool("Disable");
 m_bGoodyTech = r.GetBool("GoodyTech");
 m_bTriggersArchaeologicalSites = r.GetBool("TriggersArchaeologicalSites");
 m_bAllowsMiasmaImmunity = r.GetBool("AllowsMiasmaImmunity");
 m_bExtraWaterSeeFrom = r.GetBool("ExtraWaterSeeFrom");
 m_bMapCentering = r.GetBool("MapCentering");
 m_bMapVisible = r.GetBool("MapVisible");
 m_bMapTrading = r.GetBool("MapTrading");
 m_bTechTrading = r.GetBool("TechTrading");
 m_bGoldTrading = r.GetBool("GoldTrading");
 m_bBridgeBuilding = r.GetBool("BridgeBuilding");
 m_bWaterWork = r.GetBool("WaterWork");
 m_gridRadius = r.GetFloat("GridRadius");
 m_gridDegrees = r.GetInt("GridDegrees");
 m_leafTech = r.GetBool("LeafTech");
 m_iEra = GC.getInfoTypeForString(r.GetText("Era"), true);
 m_iFirstFreeUnitClass = GC.getInfoTypeForString(r.GetText("FirstFreeUnitClass"), true);
 SetQuoteKey(r.GetText("Quote"));
 SetSound(r.GetText("AudioIntro"));
 SetSoundMP(r.GetText("AudioIntroHeader"));
 const char* type = GetType();
 u.PopulateArrayByValue(m_piAffinities, "Affinity_Types", "Technology_Affinities", "AffinityType", "TechType", type, "AffinityValue", 0, GC.getNumAffinityInfos());
 u.PopulateArrayByValue(m_piDomainExtraMoves, "Domains", "Technology_DomainExtraMoves", "DomainType", "TechType", type, "Moves", 0, NUM_DOMAIN_TYPES);
 u.PopulateArrayByValue(m_piTradeRouteDomainExtraRange, "Domains", "Technology_TradeRouteDomainExtraRange", "DomainType", "TechType", type, "Range", 0, NUM_DOMAIN_TYPES);
 u.PopulateArrayByExistence(m_pabFreePromotion, "UnitPromotions", "Technology_FreePromotions", "PromotionType", "TechType", type);
 u.PopulateArrayByExistence(m_pabFreePlayerPerks, "PlayerPerks", "Technology_FreePlayerPerks", "PlayerPerkType", "TechType", type);
 u.SetFlavors(m_piFlavorValue, "Technology_Flavors", "TechType", type);
 const size_t count = u.MaxRows("Technologies");
 u.InitializeArray(m_piPrereqOrTechs, count, NO_TECH);
 std::string key = "Technologies - Technology_ORPrereqTechs";
 Database::Results* rows = u.GetResults(key);
 if (!rows) rows = u.PrepareResults(key, "select Technologies.ID from Technology_ORPrereqTechs inner join Technologies on Technologies.Type = PrereqTech where TechType = ?;");
 TechBind(rows, 1, type, -1, false);
 int i = 0;
 while (rows->Step()) m_piPrereqOrTechs[i++] = rows->GetInt(0);
 rows->Reset();
 u.InitializeArray(m_piPrereqAndTechs, count, NO_TECH);
 key = "Technologies - Technology_PrereqTechs";
 rows = u.GetResults(key);
 if (!rows) rows = u.PrepareResults(key, "select Technologies.ID from Technology_PrereqTechs inner join Technologies on Technologies.Type = PrereqTech where TechType = ?;");
 TechBind(rows, 1, type, -1, false);
 i = 0;
 while (rows->Step()) m_piPrereqAndTechs[i++] = rows->GetInt(0);
 rows->Reset();
 key = "Technologies - Technology_Connections";
 rows = u.GetResults(key);
 if (!rows) rows = u.PrepareResults(key, "SELECT Technologies.ID FROM Technology_Connections INNER JOIN Technologies ON Technologies.Type = Technology_Connections.SecondTech WHERE FirstTech = ? UNION SELECT Technologies.ID FROM Technology_Connections INNER JOIN Technologies ON Technologies.Type = Technology_Connections.FirstTech WHERE SecondTech = ?;");
 TechBind(rows, 1, type, -1, false);
 TechBind(rows, 2, type, -1, false);
 while (rows->Step()) m_ConnectedTechs.push_back(rows->GetInt(0));
 rows->Reset();
 return true;
}
#define TECH_INT(Name, Member) int CvTechEntry::Name() const { return Member; }
TECH_INT(GetAIWeight, m_iAIWeight)
TECH_INT(GetAITradeModifier, m_iAITradeModifier)
TECH_INT(GetResearchCost, m_iResearchCost)
TECH_INT(GetAdvancedStartCost, m_iAdvancedStartCost)
TECH_INT(GetEra, m_iEra)
TECH_INT(GetFeatureProductionModifier, m_iFeatureProductionModifier)
TECH_INT(GetUnitFortificationModifier, m_iUnitFortificationModifier)
TECH_INT(GetUnitBaseHealModifier, m_iUnitBaseHealModifier)
TECH_INT(GetUnitBaseMiasmaHeal, m_iUnitBaseMiasmaHeal)
TECH_INT(GetWorkerSpeedModifier, m_iWorkerSpeedModifier)
TECH_INT(GetFirstFreeUnitClass, m_iFirstFreeUnitClass)
TECH_INT(GetFirstFreeTechs, m_iFirstFreeTechs)
TECH_INT(GetEmbarkedMoveChange, m_iEmbarkedMoveChange)
TECH_INT(GetNumInternationalTradeRoutesChange, m_iInternationalTradeRoutesChange)
TECH_INT(GetInfluenceSpreadModifier, m_iInfluenceSpreadModifier)
TECH_INT(GetExtraVotesPerDiplomat, m_iExtraVotesPerDiplomat)
TECH_INT(GetGridDegrees, m_gridDegrees)
#undef TECH_INT
float CvTechEntry::GetGridRadius() const { return m_gridRadius; }
#define TECH_BOOL(Name, Member) bool CvTechEntry::Name() const { return Member; }
TECH_BOOL(IsLeafTech, m_leafTech)
TECH_BOOL(IsEndsGame, m_bEndsGame)
TECH_BOOL(IsAllowsEmbarking, m_bAllowsEmbarking)
TECH_BOOL(IsAllowsDeepWaterCityMove, m_bAllowsDeepWaterCityMove)
TECH_BOOL(IsRepeat, m_bRepeat)
TECH_BOOL(IsTrade, m_bTrade)
TECH_BOOL(IsDisable, m_bDisable)
TECH_BOOL(IsGoodyTech, m_bGoodyTech)
TECH_BOOL(IsExtraWaterSeeFrom, m_bExtraWaterSeeFrom)
TECH_BOOL(IsMapCentering, m_bMapCentering)
TECH_BOOL(IsMapVisible, m_bMapVisible)
TECH_BOOL(IsMapTrading, m_bMapTrading)
TECH_BOOL(IsTechTrading, m_bTechTrading)
TECH_BOOL(IsGoldTrading, m_bGoldTrading)
TECH_BOOL(IsBridgeBuilding, m_bBridgeBuilding)
TECH_BOOL(IsWaterWork, m_bWaterWork)
TECH_BOOL(IsTriggersArchaeologicalSites, m_bTriggersArchaeologicalSites)
TECH_BOOL(IsAllowsMiasmaImmunity, m_bAllowsMiasmaImmunity)
#undef TECH_BOOL
int CvTechEntry::IsFreePromotion(int i) const { return m_pabFreePromotion ? m_pabFreePromotion[i] : -1; }
bool CvTechEntry::IsFreePlayerPerk(int i) const { return m_pabFreePlayerPerks && m_pabFreePlayerPerks[i]; }
const char* CvTechEntry::GetQuote() { return m_wstrQuote.c_str(); }
void CvTechEntry::SetQuoteKey(const char* s)
{
 m_strQuoteKey = s;
 Localization::String quote = Localization::Lookup(m_strQuoteKey.c_str());
 unsigned int length = 0;
 const char* text = quote.toUTF8(length, 1);
 m_wstrQuote.assign(text, length);
}
const char* CvTechEntry::GetSound() const { return m_strSound.c_str(); }
void CvTechEntry::SetSound(const char* s) { m_strSound = s; }
const char* CvTechEntry::GetSoundMP() const { return m_strSoundMP.c_str(); }
void CvTechEntry::SetSoundMP(const char* s) { m_strSoundMP = s; }
int CvTechEntry::GetAffinityValue(AffinityType i) const { return m_piAffinities ? m_piAffinities[i] : -1; }
int CvTechEntry::GetDomainExtraMoves(int i) const { return m_piDomainExtraMoves ? m_piDomainExtraMoves[i] : -1; }
int CvTechEntry::GetTradeRouteDomainExtraRange(int i) const { return m_piTradeRouteDomainExtraRange ? m_piTradeRouteDomainExtraRange[i] : -1; }
int CvTechEntry::GetFlavorValue(int i) const { return m_piFlavorValue ? m_piFlavorValue[i] : -1; }
int CvTechEntry::GetNumConnectedTechs() const { return m_ConnectedTechs.size(); }
TechTypes CvTechEntry::GetConnectedTechs(int i) const { return m_ConnectedTechs.empty() ? NO_TECH : static_cast<TechTypes>(m_ConnectedTechs[i]); }

CvTechXMLEntries::CvTechXMLEntries() {}
CvTechXMLEntries::~CvTechXMLEntries() { DeleteArray(); }
void CvTechXMLEntries::DeleteArray()
{
 for (std::vector<CvTechEntry*>::iterator i = m_paTechEntries.begin(); i != m_paTechEntries.end(); ++i)
 {
  if (*i) { (*i)->~CvTechEntry(); ::operator delete(*i, sizeof(CvTechEntry)); }
  *i = NULL;
 }
 m_paTechEntries.clear();
}
std::vector<CvTechEntry*>& CvTechXMLEntries::GetTechEntries() { return m_paTechEntries; }
const std::vector<CvTechEntry*>& CvTechXMLEntries::GetTechEntries() const { return m_paTechEntries; }
int CvTechXMLEntries::GetNumTechs() { return m_paTechEntries.size(); }
CvTechEntry* CvTechXMLEntries::GetEntry(int i) { return i == NO_TECH ? NULL : m_paTechEntries[i]; }
CvPlayerTechs::CvPlayerTechs() : m_pabResearchingTech(NULL),
	m_piCivTechPriority(NULL),
	m_piLocaleTechPriority(NULL),
	m_peLocaleTechResources(NULL),
	m_peCivTechUniqueBuildings(NULL),
	m_peCivTechUniqueUnits(NULL),
	m_peCivTechUniqueImprovements(NULL),
	m_pTechs(NULL),
	m_pPlayer(NULL),
	m_pTechAI(NULL)
{
}

/// Destructor
CvPlayerTechs::~CvPlayerTechs(void)
{
}

/// Initialize
void CvPlayerTechs::Init(CvTechXMLEntries* pTechs, CvPlayer* pPlayer, bool bIsCity)
{
	// Init base class
	CvFlavorRecipient::Init();

	// Store off the pointers to objects we'll need later
	m_bIsCity = bIsCity;
	m_pTechs = pTechs;
	m_pPlayer = pPlayer;

	// Initialize arrays
	const int iNumTechs = m_pTechs->GetNumTechs();

	CvAssertMsg(m_pabResearchingTech==NULL, "about to leak memory, CvPlayerTechs::m_pabResearchingTech");
	m_pabResearchingTech = FNEW(bool[iNumTechs], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_piCivTechPriority==NULL, "about to leak memory, CvPlayerTechs::m_piCivTechPriority");
	m_piCivTechPriority = FNEW(int[iNumTechs], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_piLocaleTechPriority==NULL, "about to leak memory, CvPlayerTechs::m_piLocaleTechPriority");
	m_piLocaleTechPriority = FNEW(int[iNumTechs], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_peLocaleTechResources==NULL, "about to leak memory, CvPlayerTechs::m_peLocaleTechResources");
	m_peLocaleTechResources = FNEW(ResourceTypes[iNumTechs], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_peCivTechUniqueUnits==NULL, "about to leak memory, CvPlayerTechs::m_peCivTechUniqueUnits");
	m_peCivTechUniqueUnits = FNEW(UnitTypes[iNumTechs], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_peCivTechUniqueBuildings==NULL, "about to leak memory, CvPlayerTechs::m_peCivTechUniqueBuildings");
	m_peCivTechUniqueBuildings = FNEW(BuildingTypes[iNumTechs], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_peCivTechUniqueImprovements==NULL, "about to leak memory, CvPlayerTechs::m_peCivTechUniqueImprovements");
	m_peCivTechUniqueImprovements = FNEW(ImprovementTypes[iNumTechs], c_eCiv5GameplayDLL, 0);

	// Create AI object
	m_pTechAI = FNEW(CvTechAI(this), c_eCiv5GameplayDLL, 0);

	Reset();
}

/// Deallocate memory created in initialize
void CvPlayerTechs::Uninit()
{
	// Uninit base class
	CvFlavorRecipient::Uninit();

	SAFE_DELETE_ARRAY(m_pabResearchingTech);
	SAFE_DELETE_ARRAY(m_piCivTechPriority);
	SAFE_DELETE_ARRAY(m_piLocaleTechPriority);
	SAFE_DELETE_ARRAY(m_peLocaleTechResources);
	SAFE_DELETE_ARRAY(m_peCivTechUniqueBuildings);
	SAFE_DELETE_ARRAY(m_peCivTechUniqueUnits);
	SAFE_DELETE_ARRAY(m_peCivTechUniqueImprovements);
	if (m_pTechAI) { m_pTechAI->~CvTechAI(); ::operator delete(m_pTechAI, sizeof(CvTechAI)); m_pTechAI = NULL; }
}

/// Reset tech status array to all false
void CvPlayerTechs::Reset()
{
 for (int i = 0; i < m_pTechs->GetNumTechs(); ++i)
 {
  m_pabResearchingTech[i] = false;
  m_piCivTechPriority[i] = m_piLocaleTechPriority[i] = 1;
  m_peLocaleTechResources[i] = NO_RESOURCE;
  m_peCivTechUniqueUnits[i] = NO_UNIT;
  m_peCivTechUniqueBuildings[i] = NO_BUILDING;
  m_peCivTechUniqueImprovements[i] = NO_IMPROVEMENT;
 }
 if (!m_pPlayer->isMinorCiv() && !m_pPlayer->isAlien() && !m_pPlayer->isNeutralProxy() && m_pPlayer->getCivilizationType() != NO_CIVILIZATION)
 {
  CvCivilizationInfo* civ = GC.getCivilizationInfo(m_pPlayer->getCivilizationType());
  if (civ)
  {
   for (int i = 0; i < GC.getNumBuildingClassInfos(); ++i)
   {
    BuildingTypes building = static_cast<BuildingTypes>(civ->getCivilizationBuildings(i));
    CvBuildingEntry* entry = building == NO_BUILDING ? NULL : GC.GetGameBuildings()->GetEntry(building);
    if (entry && civ->isCivilizationBuildingOverridden(i) && entry->GetTechPrereq() != NO_TECH)
    {
     int tech = entry->GetTechPrereq();
     m_piCivTechPriority[tech] *= GC.getTECH_PRIORITY_UNIQUE_ITEM();
     m_peCivTechUniqueBuildings[tech] = building;
    }
   }
   for (int i = 0; i < GC.getNumUnitClassInfos(); ++i)
   {
    if (!civ->isCivilizationUnitOverridden(i)) continue;
    UnitTypes unit = static_cast<UnitTypes>(civ->getCivilizationUnits(i));
    CvUnitEntry* entry = unit == NO_UNIT ? NULL : GC.getUnitInfo(unit);
    if (entry && entry->GetPrereqAndTech() != NO_TECH)
    {
     int tech = entry->GetPrereqAndTech();
     m_piCivTechPriority[tech] *= GC.getTECH_PRIORITY_UNIQUE_ITEM();
     m_peCivTechUniqueUnits[tech] = unit;
    }
   }
   for (int i = 0; i < GC.getNumImprovementInfos(); ++i)
   {
    CvImprovementEntry* entry = GC.getImprovementInfo(static_cast<ImprovementTypes>(i));
    if (!entry || entry->GetRequiredCivilization() == NO_CIVILIZATION || entry->GetRequiredCivilization() != m_pPlayer->getCivilizationType()) continue;
    for (int j = 0; j < GC.getNumBuildInfos(); ++j)
    {
     CvBuildInfo* build = GC.getBuildInfo(static_cast<BuildTypes>(j));
     if (build && build->getImprovement() == i && build->getTechPrereq() != NO_TECH)
     {
      int tech = build->getTechPrereq();
      m_piCivTechPriority[tech] *= GC.getTECH_PRIORITY_UNIQUE_ITEM();
      m_peCivTechUniqueImprovements[tech] = static_cast<ImprovementTypes>(i);
     }
    }
   }
  }
 }
 m_pTechAI->Reset();
}
void CvPlayerTechs::Read(FDataStream& kStream)
{
	// Version number to maintain backwards compatibility
	uint uiVersion;
	kStream >> uiVersion;

	// TODO: If m_pTechs is NULL then the stream will not be advanced causing errors to occur.
	CvAssertMsg(m_pTechs != NULL && m_pTechs->GetNumTechs() > 0, "Number of techs to serialize is expected to greater than 0");
	if(m_pTechs != NULL)
	{
		const int iNumTechs = m_pTechs->GetNumTechs();

		CvInfosSerializationHelper::ReadHashedDataArray(kStream, m_pabResearchingTech, iNumTechs);
		CvInfosSerializationHelper::ReadHashedDataArray(kStream, m_piCivTechPriority, iNumTechs);
		CvInfosSerializationHelper::ReadHashedDataArray(kStream, m_piLocaleTechPriority, iNumTechs);
		CvInfosSerializationHelper::ReadHashedDataArray(kStream, m_peLocaleTechResources, iNumTechs);
		CvInfosSerializationHelper::ReadHashedDataArray(kStream, m_peCivTechUniqueUnits, iNumTechs);
		CvInfosSerializationHelper::ReadHashedDataArray(kStream, m_peCivTechUniqueBuildings, iNumTechs);
		CvInfosSerializationHelper::ReadHashedDataArray(kStream, m_peCivTechUniqueImprovements, iNumTechs);
	}

	// Now for AI
	m_pTechAI->Read(kStream);

	CvAssertMsg(m_piLatestFlavorValues != NULL && GC.getNumFlavorTypes() > 0, "Number of flavor values to serialize is expected to greater than 0");

	int iNumFlavors;
	kStream >> iNumFlavors;

	for (int i = 0; i < iNumFlavors; ++i) kStream >> m_piLatestFlavorValues[i];
}

/// Serialization write
void CvPlayerTechs::Write(FDataStream& kStream)
{
	// Current version number
	uint uiVersion = 1;
	kStream << uiVersion;

	// TODO: If m_pTechs is NULL then the stream will not advance
	CvAssertMsg(m_pTechs != NULL && m_pTechs->GetNumTechs() > 0, "Number of techs to serialize is expected to greater than 0");
	if(m_pTechs != NULL)
	{
		const int iNumTechs = m_pTechs->GetNumTechs();

		CvInfosSerializationHelper::WriteHashedDataArray<TechTypes, bool>(kStream, m_pabResearchingTech, iNumTechs);
		CvInfosSerializationHelper::WriteHashedDataArray<TechTypes, int>(kStream, m_piCivTechPriority, iNumTechs);
		CvInfosSerializationHelper::WriteHashedDataArray<TechTypes, int>(kStream, m_piLocaleTechPriority, iNumTechs);
		CvInfosSerializationHelper::WriteHashedDataArray<TechTypes, ResourceTypes>(kStream, m_peLocaleTechResources, iNumTechs);
		CvInfosSerializationHelper::WriteHashedDataArray<TechTypes, UnitTypes>(kStream, m_peCivTechUniqueUnits, iNumTechs);
		CvInfosSerializationHelper::WriteHashedDataArray<TechTypes, BuildingTypes>(kStream, m_peCivTechUniqueBuildings, iNumTechs);
		CvInfosSerializationHelper::WriteHashedDataArray<TechTypes, ImprovementTypes>(kStream, m_peCivTechUniqueImprovements, iNumTechs);
	}

	// Now for AI
	m_pTechAI->Write(kStream);

	CvAssertMsg(m_piLatestFlavorValues != NULL && GC.getNumFlavorTypes() > 0, "Number of flavor values to serialize is expected to greater than 0");
	kStream << GC.getNumFlavorTypes();
	kStream << ArrayWrapper<int>(GC.getNumFlavorTypes(), m_piLatestFlavorValues);
}

/// Respond to a new set of flavor values
void CvPlayerTechs::FlavorUpdate()
{
	SetLocalePriorities();
	AddFlavorAsStrategies(GC.getTECH_WEIGHT_PROPAGATION_PERCENT());
}

/// Accessor: Player object
CvPlayer* CvPlayerTechs::GetPlayer()
{
	return m_pPlayer;
}
CvTechAI* CvPlayerTechs::GetTechAI() { return m_pTechAI; }
bool CvPlayerTechs::IsResearchingTech(TechTypes eIndex) const { return m_pabResearchingTech[eIndex]; }
void CvPlayerTechs::SetResearchingTech(TechTypes eIndex, bool bNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	if(m_pabResearchingTech[eIndex] != bNewValue)
	{
		m_pabResearchingTech[eIndex] = bNewValue;
	}
}

/// Accessor: set Civ's priority multiplier for researching techs (for instance techs that unlock civ unique bonuses)
void CvPlayerTechs::SetCivTechPriority(TechTypes eIndex, int iNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	m_piCivTechPriority[eIndex] = iNewValue;
}

/// Accessor: get Civ's priority multiplier for researching techs (for instance techs that unlock civ unique bonuses)
int CvPlayerTechs::GetCivTechPriority(TechTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");
	return m_piCivTechPriority[eIndex];
}

/// Accessor: set locale priority multiplier for researching techs (for instance techs that unlock nearby resources)
void CvPlayerTechs::SetLocaleTechPriority(TechTypes eIndex, int iNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	m_piLocaleTechPriority[eIndex] = iNewValue;
}

/// Accessor: get locale priority multiplier for researching techs (for instance techs that unlock nearby resources)
int CvPlayerTechs::GetLocaleTechPriority(TechTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");
	return m_piLocaleTechPriority[eIndex];
}

ResourceTypes CvPlayerTechs::GetLocaleTechResource(TechTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	return m_peLocaleTechResources[eIndex];
}

UnitTypes CvPlayerTechs::GetCivTechUniqueUnit(TechTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	return m_peCivTechUniqueUnits[eIndex];
}

BuildingTypes CvPlayerTechs::GetCivTechUniqueBuilding(TechTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	return m_peCivTechUniqueBuildings[eIndex];
}

ImprovementTypes CvPlayerTechs::GetCivTechUniqueImprovement(TechTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	return m_peCivTechUniqueImprovements[eIndex];
}

/// Recompute weights taking into account tech cost
/// Accessor: Can we start research?
bool CvPlayerTechs::IsResearch() const
{
	// Have we founded a city?
	if(!m_pPlayer->isFoundedFirstCity())
	{
		return false;
	}

	return true;
}

/// Accessor: Is this tech disabled?
bool CvPlayerTechs::CanEverResearch(TechTypes eTech) const
{
	CvTechEntry* pkTechInfo = GC.getTechInfo(eTech);
	if(pkTechInfo == NULL)
	{
		return false;
	}

	if(pkTechInfo->IsDisable())
	{
		return false;
	}

	if(m_pPlayer->getCivilizationInfo().isCivilizationDisableTechs(eTech))
	{
		return false;
	}

	ICvEngineScriptSystem1* pkScriptSystem = gDLL->GetScriptSystem();
	if(pkScriptSystem)
	{
		CvLuaArgsHandle args;
		args->Push(m_pPlayer->GetID());
		args->Push(eTech);

		// Attempt to execute the game events.
		// Will return false if there are no registered listeners.
		bool bResult = false;
		if(LuaSupport::CallTestAll(pkScriptSystem, "PlayerCanEverResearch", args.get(), bResult))
		{
			// Check the result.
			if(bResult == false)
			{
				return false;
			}
		}
	}


	return true;
}

/// Accessor: Is it possible to research this tech?
bool CvPlayerTechs::CanResearch(TechTypes eTech, bool bTrade) const
{
 CvTechEntry* entry = GC.getTechInfo(eTech);
 if (!entry || (!IsResearch() && m_pPlayer->getAdvancedStartPoints() < 0)) return false;
 CvTeamTechs* team = GET_TEAM(m_pPlayer->getTeam()).GetTeamTechs();
 if (team->HasTech(eTech)) return false;
 bool connected = false;
 for (int i = 0; i < entry->GetNumConnectedTechs(); ++i)
 {
  TechTypes tech = entry->GetConnectedTechs(i);
  if (tech != NO_TECH && team->HasTech(tech) && (!bTrade || !team->IsNoTradeTech(tech)))
  {
   connected = true;
   break;
  }
 }
 if (!connected || !CanEverResearch(eTech)) return false;
 ICvEngineScriptSystem1* script = gDLL->GetScriptSystem();
 if (script)
 {
  CvLuaArgsHandle args;
  args->Push(m_pPlayer->GetID());
  args->Push(eTech);
  bool result = false;
  if (LuaSupport::CallTestAll(script, "PlayerCanResearch", args.get(), result) && !result) return false;
 }
 return true;
}
bool CvPlayerTechs::CanResearchForFree(TechTypes eTech) const
{
	CvAssertMsg(eTech >= 0, "eTech is expected to be non-negative (invalid Index)");
	CvAssertMsg(eTech < GC.getNumTechInfos(), "eTech is expected to be within maximum bounds (invalid Index)");
	if(eTech < 0 || eTech >= GC.getNumTechInfos()) return false;

	// We can pick any tech that we are able to research
	return CanResearch(eTech);
}

/// Accessor: Which tech are we researching?
TechTypes CvPlayerTechs::GetCurrentResearch() const
{
	CLLNode<TechTypes>* pResearchNode;

	pResearchNode = m_pPlayer->headResearchQueueNode();

	if(pResearchNode != NULL)
	{
		return pResearchNode->m_data;
	}
	else
	{
		return NO_TECH;
	}
}

/// Accessor: Are we currently researching something that can be repeatedly researched?
bool CvPlayerTechs::IsCurrentResearchRepeat() const
{
	const TechTypes eCurrentResearch = GetCurrentResearch();
	if(eCurrentResearch == NO_TECH)
	{
		return false;
	}

	CvTechEntry* pkTechInfo = GC.getTechInfo(eCurrentResearch);
	if(pkTechInfo == NULL)
	{
		return false;
	}

	return pkTechInfo->IsRepeat();
}

/// Accessor: Is there anything left to research?
bool CvPlayerTechs::IsNoResearchAvailable() const
{
	int iI;

	if(GetCurrentResearch() != NO_TECH)
	{
		return false;
	}

	for(iI = 0; iI < GC.getNumTechInfos(); iI++)
	{
		if(CanResearch((TechTypes)iI))
		{
			return false;
		}
	}
	return true;
}

int CvPlayerTechs::GetResearchTurnsLeft(TechTypes eTech, bool bOverflow) const
{
	int iTurnsLeft = GetResearchTurnsLeftTimes100(eTech, bOverflow);

	if(iTurnsLeft == INT_MAX)
	{
		return INT_MAX;
	}

	iTurnsLeft = (iTurnsLeft + 99) / 100; // round up

	return std::max(1, iTurnsLeft);
}

/// Accessor: How many turns of research left? (in hundredths)
int CvPlayerTechs::GetResearchTurnsLeftTimes100(TechTypes eTech, bool bOverflow) const
{
	int iResearchRate;
	int iOverflow;
	int iTurnsLeft;
	int iI;

	iResearchRate = 0;
	iOverflow = 0;

	for(iI = 0; iI < MAX_PLAYERS; iI++)
	{
		CvPlayerAI& kPlayer = GET_PLAYER((PlayerTypes)iI);
		if(kPlayer.isAlive())
		{
			// Find everyone on our team
			if(kPlayer.getTeam() == m_pPlayer->getTeam())
			{
				// If this is us or if the tech matches, then increment totals
				if((iI == m_pPlayer->GetID()) || kPlayer.GetPlayerTechs()->GetCurrentResearch() == eTech)
				{
					iResearchRate += kPlayer.GetTotalSciencePerTurnTimes100();
					iOverflow += (kPlayer.getOverflowResearch() * m_pPlayer->calculateResearchModifier(eTech)) / 100;
				}
			}
		}
	}

	if(iResearchRate == 0)
	{
		return INT_MAX;
	}

	int iResearchCost = GetResearchCost(eTech);				// Get our research cost (not the 'team' one which doesn't use our player modifier)
	// Get the team progress
	int iResearchProgress = GET_TEAM(m_pPlayer->getTeam()).GetTeamTechs()->GetResearchProgress(eTech);
	// Get the raw amount left
	int iResearchLeft = std::max(0, (iResearchCost - iResearchProgress));

	// Removed any current overflow if requested.
	if(bOverflow)
	{
		iResearchLeft -= iOverflow;
	}

	iResearchLeft *= 10000;

	iTurnsLeft = (iResearchLeft / iResearchRate);

	if(iTurnsLeft * iResearchRate < iResearchLeft)
	{
		++iTurnsLeft;
	}

	return std::max(1, iTurnsLeft);
}

/// How many techs can we research at present?
int CvPlayerTechs::GetNumTechsCanBeResearched() const
{
	int rtnValue = 0;

	for(int iTechLoop = 0; iTechLoop < GetTechs()->GetNumTechs(); iTechLoop++)
	{
		if(CanResearch((TechTypes)iTechLoop))
		{
			rtnValue++;
		}
	}

	return rtnValue;
}

/// Return the tech data (from XML)
CvTechXMLEntries* CvPlayerTechs::GetTechs() const
{
	return m_pTechs;
}

//	----------------------------------------------------------------------------
/// Return the research cost for a tech for this player.  This will be different from the team research cost as it will
/// include the player's research adjustment
int CvPlayerTechs::GetResearchCost(TechTypes eTech) const
{
 int cost = GET_TEAM(m_pPlayer->getTeam()).GetTeamTechs()->GetResearchCost(eTech);
 cost -= cost * (m_pPlayer->calculateResearchModifier(eTech) - 100) / 100;
 cost *= 100;
 float cityModifier = static_cast<float>(GC.getMap().getWorldInfo().GetNumCitiesTechCostMod());
 int discount = m_pPlayer->GetNumCitiesResearchCostDiscount();
 if (discount) cityModifier = cityModifier * (100.0f + discount) / 100.0f;
 cityModifier *= m_pPlayer->GetMaxEffectiveCities(true) - 1;
 cost = static_cast<int>((100.0f + cityModifier) * cost / 100.0f);
 return cost / 100 + (cost % 100 != 0);
}

//	----------------------------------------------------------------------------
/// Return the research progress for a tech for this player.
int CvPlayerTechs::GetResearchProgress(TechTypes eTech) const
{
	// Get the research progress for the team
	int iResearchProgress = GET_TEAM(m_pPlayer->getTeam()).GetTeamTechs()->GetResearchProgress(eTech);
	// Add in any overflow we have yet to accumulate into the research progress.
	// Overflow is the leftover research from the previous research.  It is automatically rolled into the main progress value
	// the next time research is 'updated'.
	iResearchProgress += m_pPlayer->getOverflowResearch();

	return iResearchProgress;
}

void CvPlayerTechs::AddFlavorAsStrategies(int iPropagatePercent)
{
	// Start by resetting the AI
	m_pTechAI->Reset();

	int iBiggestFlavor = -1000;
	for(int iFlavor = 0; iFlavor < GC.getNumFlavorTypes(); iFlavor++)
	{
		int iFlavorValue = GetLatestFlavorValue((FlavorTypes) iFlavor);
		if(iFlavorValue > iBiggestFlavor)
		{
			iBiggestFlavor = iFlavorValue;
		}
	}

	// Now populate the AI with the current flavor information
	int iGameProgressFactor = (GC.getGame().getElapsedGameTurns() * 1000) / GC.getGame().getDefaultEstimateEndTurn();
	iGameProgressFactor = std::min(900,std::max(100,iGameProgressFactor));
	for(int iFlavor = 0; iFlavor < GC.getNumFlavorTypes(); iFlavor++)
	{
		int iCurrentFlavorValue = GetLatestFlavorValue((FlavorTypes) iFlavor);

		// Scale the current to the same scale as the personality
		iCurrentFlavorValue = (iCurrentFlavorValue * 10) / iBiggestFlavor;

		int iPersonalityFlavorValue = m_pPlayer->GetGrandStrategyAI()->GetPersonalityAndGrandStrategy((FlavorTypes) iFlavor);

		// this should give a more even blend between the personality and long term strategy and the more fickle current needs
		// in the beginning of the game it will be responsive to current events, but later it should try to go for the goal more strongly
		int iFlavorValue = ((iCurrentFlavorValue * (1000 - iGameProgressFactor)) + (iPersonalityFlavorValue * iGameProgressFactor)) / 1000;

		if(iFlavorValue > 0)
		{
			m_pTechAI->AddFlavorWeights((FlavorTypes)iFlavor, iFlavorValue, iPropagatePercent);
		}
	}
}

void CvPlayerTechs::LogFlavors(FlavorTypes eFlavor)
{
	if(GC.getLogging() && GC.getAILogging())
	{
		CvString strOutBuf;
		CvString strBaseString;
		CvString strTemp;
		CvString playerName;
		CvString strDesc;
		CvString strLogName;

		// Find the name of this civ
		playerName = m_pPlayer->getCivilizationShortDescription();

		// Open the log file
		if(GC.getPlayerAndCityAILogSplit())
		{
			strLogName = "TechAILog_" + playerName + ".csv";
		}
		else
		{
			strLogName = "TechAILog.csv";
		}

		FILogFile* pLog;
		pLog = LOGFILEMGR.GetLog(strLogName, FILogFile::kDontTimeStamp);

		// Get the leading info for this line
		strBaseString.Format("%03d, ", GC.getGame().getElapsedGameTurns());
		strBaseString += playerName + ", ";

		// Dump out the setting for each flavor
		if(eFlavor == NO_FLAVOR)
		{
			for(int iI = 0; iI < GC.getNumFlavorTypes(); iI++)
			{
				strTemp.Format("Flavor, %s, %d", GC.getFlavorTypes((FlavorTypes)iI), m_piLatestFlavorValues[iI]);
				strOutBuf = strBaseString + strTemp;
				pLog->Msg(strOutBuf);
			}
		}
		else
		{
			strTemp.Format("Flavor, %s, %d", GC.getFlavorTypes(eFlavor), m_piLatestFlavorValues[eFlavor]);
			strOutBuf = strBaseString + strTemp;
			pLog->Msg(strOutBuf);
		}
	}
}

//=====================================
// CvTeamTechs
CvTeamTechs::CvTeamTechs():
 m_eLastTechAcquired(NO_TECH),
	m_pabHasTech(NULL),
	m_pabNoTradeTech(NULL),
	m_paiResearchProgress(NULL),
	m_paiTechCount(NULL), m_pTechs(NULL), m_pTeam(NULL)
{
}

/// Destructor
CvTeamTechs::~CvTeamTechs(void)
{
}

/// Initialize
void CvTeamTechs::Init(CvTechXMLEntries* pTechs, CvTeam* pTeam)
{
	// Store off the pointer to the techs active for this game and pointer to our team
	m_pTechs = pTechs;
	m_pTeam = pTeam;

	// Initialize status arrays
	CvAssertMsg(m_pabHasTech==NULL, "about to leak memory, CvTeamTechs::m_pabHasTech");
	m_pabHasTech = FNEW(bool[m_pTechs->GetNumTechs()], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_pabNoTradeTech==NULL, "about to leak memory, CvTeamTechs::m_pabNoTradeTech");
	m_pabNoTradeTech = FNEW(bool[m_pTechs->GetNumTechs()], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_paiResearchProgress==NULL, "about to leak memory, CvTeamTechs::m_paiResearchProgress");
	m_paiResearchProgress = FNEW(int [m_pTechs->GetNumTechs()], c_eCiv5GameplayDLL, 0);
	CvAssertMsg(m_paiTechCount==NULL, "about to leak memory, CvTeamTechs::m_paiTechCount");
	m_paiTechCount = FNEW(int [m_pTechs->GetNumTechs()], c_eCiv5GameplayDLL, 0);

	Reset();
}

/// Deallocate memory created in initialize
void CvTeamTechs::Uninit()
{
	SAFE_DELETE_ARRAY(m_pabHasTech);
	SAFE_DELETE_ARRAY(m_pabNoTradeTech);
	SAFE_DELETE_ARRAY(m_paiResearchProgress);
	SAFE_DELETE_ARRAY(m_paiTechCount);
}

/// Reset tech status arrays
void CvTeamTechs::Reset()
{
	int iI;

	m_eLastTechAcquired = NO_TECH;

	for(iI = 0; iI < m_pTechs->GetNumTechs(); iI++)
	{
		m_pabHasTech[iI] = false;
		m_pabNoTradeTech[iI] = false;
		m_paiResearchProgress[iI] = 0;
		m_paiTechCount[iI] = 0;
	}
}

void CvTeamTechs::Read(FDataStream& kStream)
{
	// Version number to maintain backwards compatibility
	uint uiVersion;
	kStream >> uiVersion;

	operator>>(kStream, m_eLastTechAcquired);

	// Read the number of techs
	int iNumSavedTechs;
	kStream >> iNumSavedTechs;

	if(iNumSavedTechs)
	{
		int iNumActiveTechs = m_pTechs->GetNumTechs();

		// Next is an array of the tech IDs that were available when the save was made.
		CvAssert(m_pTechs == GC.GetGameTechs());	// The hash to indices conversion will convert the hash to the index in the main game techs array, so these better be the same.
  const size_t bytes = iNumSavedTechs * sizeof(int) + 8;
  unsigned int* allocation = static_cast<unsigned int*>(bytes > 1024 ? malloc(bytes) : __builtin_alloca(bytes));
  int* paTechIDs = NULL;
  if (allocation)
  {
   allocation[0] = bytes > 1024 ? 0xdddd : 0xcccc;
   paTechIDs = reinterpret_cast<int*>(allocation + 2);
  }
  for (int i = 0; i < iNumSavedTechs; ++i) paTechIDs[i] = CvInfosSerializationHelper::ReadHashed(kStream);

		CvInfosSerializationHelper::ReadAndRemapDataArray(kStream, iNumSavedTechs, m_pabHasTech, iNumActiveTechs, paTechIDs);
		CvInfosSerializationHelper::ReadAndRemapDataArray(kStream, iNumSavedTechs, m_pabNoTradeTech, iNumActiveTechs, paTechIDs);
		CvInfosSerializationHelper::ReadAndRemapDataArray(kStream, iNumSavedTechs, m_paiResearchProgress, iNumActiveTechs, paTechIDs);
		CvInfosSerializationHelper::ReadAndRemapDataArray(kStream, iNumSavedTechs, m_paiTechCount, iNumActiveTechs, paTechIDs);

  if (paTechIDs && allocation[0] == 0xdddd) free(allocation);
	}
}

//	---------------------------------------------------------------------------
/// Serialization write
void CvTeamTechs::Write(FDataStream& kStream)
{
	// Current version number
	uint uiVersion = 1;
	kStream << uiVersion;

	operator<<(kStream, m_eLastTechAcquired);

	if(m_pTechs != NULL && m_pTechs->GetNumTechs())
	{
		// Write out an array of all the active tech's hash types so we can re-map on loading if need be.
		int iNumTechs = m_pTechs->GetNumTechs();
		kStream << (int)iNumTechs;

		for(int i = 0; i < iNumTechs; ++i)
			CvInfosSerializationHelper::WriteHashed(kStream, m_pTechs->GetEntry(i));

		kStream << ArrayWrapper<bool>(iNumTechs, m_pabHasTech);
		kStream << ArrayWrapper<bool>(iNumTechs, m_pabNoTradeTech);
		kStream << ArrayWrapper<int>(iNumTechs, m_paiResearchProgress);
		kStream << ArrayWrapper<int>(iNumTechs, m_paiTechCount);
	}
	else
	{
		kStream << (int)0;
	}
}

/// Accessor: set whether team owns a tech
void CvTeamTechs::SetHasTech(TechTypes eIndex, bool bNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	if(m_pabHasTech[eIndex] != bNewValue)
	{
		m_pabHasTech[eIndex] = bNewValue;

		if(bNewValue)
			SetLastTechAcquired(eIndex);

		ICvEngineScriptSystem1* pkScriptSystem = gDLL->GetScriptSystem();
		if(pkScriptSystem)
		{
			CvLuaArgsHandle args;
			args->Push(m_pTeam->GetID());
			args->Push(eIndex);
			args->Push(bNewValue);

			// Attempt to execute the game events.
			// Will return false if there are no registered listeners.
			bool bResult = false;
			LuaSupport::CallHook(pkScriptSystem, "TeamSetHasTech", args.get(), bResult);
		}
	}
}

/// Accessor: does team have a tech?
bool CvTeamTechs::HasTech(TechTypes eIndex) const
{
	if(eIndex == NO_TECH)
	{
		return true;
	}

	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");
	CvAssertMsg(m_pabHasTech != NULL, "m_pabHasTech is not expected to be equal with NULL");
	if(eIndex >= 0 && eIndex < GC.getNumTechInfos() && m_pabHasTech != NULL)
		return m_pabHasTech[eIndex];
	else
		return false;
}

/// What was the most recent tech acquired?
TechTypes CvTeamTechs::GetLastTechAcquired() const
{
	return m_eLastTechAcquired;
}

/// What was the most recent tech acquired?
void CvTeamTechs::SetLastTechAcquired(TechTypes eTech)
{
	CvAssertMsg(eTech >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eTech < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	m_eLastTechAcquired = eTech;
}

/// How many total Techs does this team have?
int CvTeamTechs::GetNumTechsKnown() const
{
	int iNumTechs = 0;

	for(int iTechLoop = 0; iTechLoop < GC.getNumTechInfos(); iTechLoop++)
	{
		if(HasTech((TechTypes) iTechLoop))
		{
			iNumTechs++;
		}
	}

	return iNumTechs;
}

/// Has this team researched all techs once?
bool CvTeamTechs::HasResearchedAllTechs() const
{
	int iNumTechs = 0;

	for(int iTechLoop = 0; iTechLoop < GC.getNumTechInfos(); iTechLoop++)
	{
		if(HasTech((TechTypes) iTechLoop) || GetTechCount((TechTypes)iTechLoop) > 0)
		{
			iNumTechs++;
		}
	}

	return (iNumTechs >= m_pTechs->GetNumTechs());
}

/// Accessor: set whether team owns a tech
void CvTeamTechs::SetNoTradeTech(TechTypes eIndex, bool bNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");

	if(m_pabNoTradeTech[eIndex] != bNewValue)
	{
		m_pabNoTradeTech[eIndex] = bNewValue;
	}
}

/// Accessor: does team have a tech?
bool CvTeamTechs::IsNoTradeTech(TechTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex is expected to be non-negative (invalid Index)");
	CvAssertMsg(eIndex < GC.getNumTechInfos(), "eIndex is expected to be within maximum bounds (invalid Index)");
	return m_pabNoTradeTech[eIndex];
}

/// Accessor: increment count of times this has been researched
void CvTeamTechs::IncrementTechCount(TechTypes eIndex)
{
	m_paiTechCount[eIndex]++;
}

/// Accessor: get count of times this has been researched
int CvTeamTechs::GetTechCount(TechTypes eIndex)const
{
	return m_paiTechCount[eIndex];
}

/// Accessor: set research done on one tech
void CvTeamTechs::SetResearchProgress(TechTypes eIndex, int iNewValue, PlayerTypes ePlayer)
{
	SetResearchProgressTimes100(eIndex, iNewValue * 100, ePlayer);
}

int CvTeamTechs::GetResearchProgress(TechTypes eIndex) const
{
	if(eIndex != NO_TECH)
	{
		return m_paiResearchProgress[eIndex] / 100;
	}
	else
	{
		return 0;
	}
}

/// Accessor: get research done on one tech (in hundredths)
int CvTeamTechs::GetResearchProgressTimes100(TechTypes eIndex) const
{
	if(eIndex != NO_TECH)
	{
		return m_paiResearchProgress[eIndex];
	}
	else
	{
		return 0;
	}
}

/// Accessor: what is the cost of researching this tech (taking all modifiers into account)
int CvTeamTechs::GetResearchLeft(TechTypes eTech) const
{
	return std::max(0, (GetResearchCost(eTech) - GetResearchProgress(eTech)));
}

/// Return the tech data (from XML)
CvTechXMLEntries* CvTeamTechs::GetTechs() const
{
	return m_pTechs;
}

/// Add an increment of research to a tech
void CvTeamTechs::ChangeResearchProgress(TechTypes eIndex, int iChange, PlayerTypes ePlayer)
{
	ChangeResearchProgressTimes100(eIndex, iChange * 100, ePlayer);
}

/// Add an increment of research to a tech (in hundredths)
void CvTeamTechs::ChangeResearchProgressTimes100(TechTypes eIndex, int iChange, PlayerTypes ePlayer)
{
	SetResearchProgressTimes100(eIndex, (GetResearchProgressTimes100(eIndex) + iChange), ePlayer);
}

/// Add research for a tech to a specified percent complete
int CvTeamTechs::ChangeResearchProgressPercent(TechTypes eIndex, int iPercent, PlayerTypes ePlayer)
{
	int iBeakers = 0;

	if(0 != iPercent && !HasTech(eIndex))
	{
		if(iPercent > 0)
		{
			iBeakers = std::min(GetResearchLeft(eIndex), (GetResearchCost(eIndex) * iPercent) / 100);
		}
		else
		{
			iBeakers = std::max(GetResearchLeft(eIndex) - GetResearchCost(eIndex), (GetResearchCost(eIndex) * iPercent) / 100);
		}

		ChangeResearchProgress(eIndex, iBeakers, ePlayer);
	}

	return iBeakers;
}

void CvPlayerTechs::SetLocalePriorities()
{
	int iLoop;
	CvCity* pCity;
	int iI;

	for(iI = 0; iI < m_pTechs->GetNumTechs(); iI++)
	{
		m_piLocaleTechPriority[iI] = 1;
		m_peLocaleTechResources[iI] = NO_RESOURCE;
	}

	// Loop through all our cities
	for(pCity = m_pPlayer->firstCity(&iLoop); pCity != NULL; pCity = m_pPlayer->nextCity(&iLoop))
	{
		// Look at all Tiles this City could potentially work to see if there are any non-water resources that could be improved
		for(int iPlotLoop = 0; iPlotLoop < NUM_CITY_PLOTS; iPlotLoop++)
		{
			CvPlot* pLoopPlot = plotCity(pCity->getX(), pCity->getY(), iPlotLoop);

			if(pLoopPlot != NULL)
			{
				int iDistance = plotDistance(pLoopPlot->getX(), pLoopPlot->getY(), pCity->getX(), pCity->getY());

				if(pLoopPlot->getOwner() == pCity->getOwner() || (iDistance <= 2 && pLoopPlot->getOwner() == NO_PLAYER))
				{
					if(!pLoopPlot->isWater())
					{
						ResourceTypes eResource = pLoopPlot->getResourceType(m_pPlayer->getTeam());
						if(eResource == NO_RESOURCE)
						{
							continue;
						}

						// Loop through the build types to find one that we can use
						ImprovementTypes eCorrectImprovement = NO_IMPROVEMENT;
						BuildTypes eCorrectBuild = NO_BUILD;
						int iBuildIndex;
						for(iBuildIndex = 0; iBuildIndex < GC.getNumBuildInfos(); iBuildIndex++)
						{
							const BuildTypes eBuild = static_cast<BuildTypes>(iBuildIndex);
							CvBuildInfo* pkBuildInfo = GC.getBuildInfo(eBuild);
							if(pkBuildInfo)
							{
								// If this is the improvement we're looking for
								const ImprovementTypes eImprovement = (ImprovementTypes)pkBuildInfo->getImprovement();
								if(eImprovement != NO_IMPROVEMENT)
								{
									CvImprovementEntry* pkImprovementInfo = GC.getImprovementInfo(eImprovement);
									if(pkImprovementInfo && pkImprovementInfo->IsImprovementResourceTrade(eResource))
									{
										eCorrectBuild = eBuild;
										eCorrectImprovement = eImprovement;
										break;
									}
								}
							}
						}

						// No valid build found
						if(eCorrectBuild == NO_BUILD || eCorrectImprovement == NO_IMPROVEMENT)
						{
							continue;
						}


						// Looking for cases where we can't build the improvement for the resource
						if(!m_pPlayer->canBuild(pLoopPlot, eCorrectBuild, false, false, false, false))
						{
							// Find the tech associated with this build and increment its multiplier
							int iTech = GC.getBuildInfo(eCorrectBuild)->getTechPrereq();
							CvAssert(iTech < m_pTechs->GetNumTechs());		// Just assert on a value off the top end, a -1 is ok to just skip silently
							if (iTech >= 0 && iTech < m_pTechs->GetNumTechs())
							{
								m_piLocaleTechPriority[iTech]++;
								m_peLocaleTechResources[iTech] = eResource;
							}
						}
					}
				}
			}
		}
	}
}

int CvPlayerTechs::GetMedianTechResearch() const
{
	std::vector<int> aiTechCosts;
	int iRtnValue = 0;

	for(int iTechLoop = 0; iTechLoop < GC.getNumTechInfos(); iTechLoop++)
	{
		TechTypes eTech = (TechTypes)iTechLoop;

		if(CanResearch(eTech))
		{
			aiTechCosts.push_back(GetResearchCost(eTech));
		}
	}

	int iNumEntries = aiTechCosts.size();
	if(iNumEntries > 0)
	{
		std::sort(aiTechCosts.begin(), aiTechCosts.end());

		// Odd number, take middle?
		if((iNumEntries / 2) * 2 != iNumEntries)
		{
			iRtnValue = aiTechCosts[iNumEntries / 2];
		}

		// Even number, average middle 2
		else
		{
			iRtnValue = (aiTechCosts[(iNumEntries - 1) / 2] + aiTechCosts[iNumEntries / 2]) / 2;
		}
	}

	return iRtnValue;
}

// PRIVATE METHODS


bool CvPlayerTechs::IsResearched(TechTypes tech) const
{
 return GC.getTechInfo(tech) && GET_TEAM(m_pPlayer->getTeam()).GetTeamTechs()->HasTech(tech);
}
int CvPlayerTechs::GetNumTechsKnown() const
{
 return GET_TEAM(m_pPlayer->getTeam()).GetTeamTechs()->GetNumTechsKnown();
}
std::vector<TechTypes> CvPlayerTechs::GetAllAvailableTechs() const
{
 std::vector<TechTypes> result;
 for (int i = 0; i < GC.getNumTechInfos(); ++i)
  if (CanResearch(static_cast<TechTypes>(i))) result.push_back(static_cast<TechTypes>(i));
 return result;
}
std::vector<const CvTechEntry*> CvPlayerTechs::GetPathToTech(const CvTechEntry* from, const CvTechEntry* to) const
{
 CvGraphSearch<CvTechGraphTraversalPolicy, CvTechGraphHeuristicPolicy, CvTechGraphResearchCostPolicy> search(m_pPlayer);
 float cost = 0;
 return search.GetPath(*from, *to, cost);
}
void CvPlayerTechs::CheckForTechAchievement() const
{
 if (!m_pPlayer->isLocalPlayer() || (!IsNoResearchAvailable() && !IsCurrentResearchRepeat())) return;
 CvTeamTechs* team = GET_TEAM(m_pPlayer->getTeam()).GetTeamTechs();
 for (int i = 0; i < GC.getNumTechInfos() - 1; ++i)
 {
  CvTechEntry* tech = GC.getTechInfo(static_cast<TechTypes>(i));
  if (tech && !team->HasTech(static_cast<TechTypes>(i))) return;
 }
 if (IsCurrentResearchRepeat() && team->GetTechCount(GetCurrentResearch()) <= 0) return;
 gDLL->UnlockAchievement(static_cast<EAchievement>(43));
}
int CvTeamTechs::GetResearchCost(TechTypes tech) const
{
 CvTechEntry* entry = GC.getTechInfo(tech);
 if (!entry) return 0;
 int cost = entry->GetResearchCost();
 CvHandicapInfo* handicap = GC.getHandicapInfo(m_pTeam->getHandicapType());
 if (handicap) cost = cost * handicap->getResearchPercent() / 100;
 cost = cost * GC.getGame().getGameSpeedInfo().getResearchPercent() / 100;
 cost = cost * (100 + GC.getTECH_COST_EXTRA_TEAM_MEMBER_MODIFIER() * (m_pTeam->getNumMembers() - 1)) / 100;
 return std::max(1, cost);
}
void CvTeamTechs::SetResearchProgressTimes100(TechTypes tech, int progress, PlayerTypes player)
{
 if (GetResearchProgressTimes100(tech) == progress) return;
 FILogFile* log = LOGFILEMGR.GetLog("techs.csv", FILogFile::kDontTimeStamp);
 CvTechEntry* entry = GC.getTechInfo(tech);
 if (log && entry)
 {
  FStringA line;
  line.Format("%03d, %03d, %s, %s, %d", GC.getGame().getElapsedGameTurns(), m_pTeam->GetID(),
              GET_PLAYER(player).getCivilizationShortDescription(), entry->GetType(), progress);
  log->Msg(line.c_str());
 }
 m_paiResearchProgress[tech] = progress;
 if (m_pTeam->GetID() == GC.getGame().getActiveTeam())
 {
  GC.GetEngineUserInterface()->setDirty(GameData_DIRTY_BIT, true);
  GC.GetEngineUserInterface()->setDirty(Score_DIRTY_BIT, true);
 }
 int overflow = progress - GET_PLAYER(player).GetPlayerTechs()->GetResearchCost(tech) * 100;
 if (overflow < 0) return;
 GET_PLAYER(player).changeOverflowResearchTimes100(overflow);
 m_pTeam->setHasTech(tech, true, player, true, true);
 SetNoTradeTech(tech, true);
 GET_PLAYER(player).GetCitySpecializationAI()->SetSpecializationsDirty(static_cast<CitySpecializationUpdateType>(7));
 for (int i = 0; i < 22; ++i)
 {
  CvPlayerAI& member = GET_PLAYER(static_cast<PlayerTypes>(i));
  if (member.getTeam() != m_pTeam->GetID()) continue;
  int culture = member.GetCulturePerTechResearched();
  if (culture) member.ChangeTotalAccumulatedCulture(culture);
 }
}
const CvTechEntry* CvTechGraphTraversalPolicy::GetConnectedNode(const CvTechEntry& node, int i, const CvPlayer*) const
{
 return GC.getTechInfo(node.GetConnectedTechs(i));
}
int CvTechGraphTraversalPolicy::GetNumConnectedNodes(const CvTechEntry& node, const CvPlayer*) const
{
 return node.GetNumConnectedTechs();
}
bool CvTechGraphTraversalPolicy::Compare(const CvTechEntry& a, const CvTechEntry& b, const CvPlayer* player) const
{
 return player->GetPlayerTechs()->GetResearchCost(static_cast<TechTypes>(a.GetID())) <
        player->GetPlayerTechs()->GetResearchCost(static_cast<TechTypes>(b.GetID()));
}
float CvTechGraphHeuristicPolicy::GetH(const CvTechEntry& a, const CvTechEntry& b, const CvPlayer*) const
{
 return std::fabs(a.GetGridRadius() - b.GetGridRadius()) + std::abs(a.GetGridDegrees() - b.GetGridDegrees());
}
float CvTechGraphResearchCostPolicy::GetCost(const CvTechEntry& a, const CvTechEntry& b, const CvPlayer* player) const
{
 CvTeamTechs* team = GET_TEAM(player->getTeam()).GetTeamTechs();
 TechTypes from = static_cast<TechTypes>(a.GetID());
 TechTypes to = static_cast<TechTypes>(b.GetID());
 if ((team->HasTech(from) && team->HasTech(to)) || player->getQueuePosition(to) != -1) return 1.0f;
 return player->GetPlayerTechs()->GetResearchCost(to) * 100.0f;
}
float CvTechGraphFlatCostPolicy::GetCost(const CvTechEntry& a, const CvTechEntry& b, const CvPlayer* player) const
{
 CvTeamTechs* team = GET_TEAM(player->getTeam()).GetTeamTechs();
 return team->HasTech(static_cast<TechTypes>(a.GetID())) && team->HasTech(static_cast<TechTypes>(b.GetID())) ? 0.1f : 1.0f;
}
static_assert(sizeof(CvTechGraphTraversalPolicy) == 8, "Beyond Earth traversal policy layout");
static_assert(sizeof(CvTechGraphHeuristicPolicy) == 8, "Beyond Earth heuristic policy layout");
static_assert(sizeof(CvTechGraphResearchCostPolicy) == 8, "Beyond Earth research policy layout");
static_assert(sizeof(CvTechGraphFlatCostPolicy) == 4, "Beyond Earth flat policy layout");
static_assert(sizeof(CvGraphSearch<CvTechGraphTraversalPolicy, CvTechGraphHeuristicPolicy, CvTechGraphResearchCostPolicy>) == 28, "Beyond Earth graph search layout");
