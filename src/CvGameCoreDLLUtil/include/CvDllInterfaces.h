#pragma once

// The Linux port uses the default calling convention for these interfaces.
#define DLLCALL

// Beyond Earth uses different interface IDs from the Civ V SDK.
// {D70014AE-D960-4668-BD97-88A9C5B36B9A}
static const GUID guidICvUnknown =
{0xd70014ae, 0xd960, 0x4668, {0xbd, 0x97, 0x88, 0xa9, 0xc5, 0xb3, 0x6b, 0x9a}};

//------------------------------------------------------------------------------
// Base Interfaces
//------------------------------------------------------------------------------
class ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId(){ return guidICvUnknown; }

	void DLLCALL operator delete(void* p)
	{
		if (p)
		{
			ICvUnknown* inst = (ICvUnknown*)(p);
			inst->Destroy();
		}
	}

	virtual void* DLLCALL QueryInterface(GUID guidInterface) = 0;

	template<typename T>
	T* DLLCALL QueryInterface()
	{
		return static_cast<T*>(QueryInterface(T::GetInterfaceId()));
	}

protected:
	virtual void DLLCALL Destroy() = 0;
};

// {DEB48522-90CD-4925-83AA-DB514AC024D8}
static const GUID guidICvEnumerator =
{0xdeb48522, 0x90cd, 0x4925, {0x83, 0xaa, 0xdb, 0x51, 0x4a, 0xc0, 0x24, 0xd8}};

class ICvEnumerator : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvEnumerator; }
	virtual bool DLLCALL MoveNext() = 0;
	virtual void DLLCALL Reset() = 0;
	virtual ICvUnknown* DLLCALL GetCurrent() = 0;
};

// {0D86341D-6466-4D85-99C8-47376CA27236}
static const GUID guidICvDlcPackageInfo1 =
{0x0d86341d, 0x6466, 0x4d85, {0x99, 0xc8, 0x47, 0x37, 0x6c, 0xa2, 0x72, 0x36}};

class ICvDlcPackageInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvDlcPackageInfo1; }
	virtual GUID DLLCALL GetPackageID() = 0;
};

// {78F69ECA-75C5-4B66-B960-6B318B4A65F7}
static const GUID guidICvCivilizationInfo1 =
{0x78f69eca, 0x75c5, 0x4b66, {0xb9, 0x60, 0x6b, 0x31, 0x8b, 0x4a, 0x65, 0xf7}};

class ICvCivilizationInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvCivilizationInfo1; }
	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	virtual bool DLLCALL IsAIPlayable() = 0;
	virtual bool DLLCALL IsPlayable() = 0;
	virtual const char* DLLCALL GetShortDescription() = 0;
	virtual int DLLCALL GetDefaultPlayerColor() = 0;
	virtual int DLLCALL GetArtStyleType() = 0;
	virtual int DLLCALL GetNumCityNames() = 0;
	virtual const char* DLLCALL GetArtStylePrefix() = 0;
	virtual const char* DLLCALL GetArtStyleSuffix() = 0;
	virtual const char* DLLCALL GetDawnOfManAudio() = 0;
	virtual int DLLCALL GetCivilizationBuildings(int i) = 0;
	virtual bool DLLCALL IsLeaders(int i) = 0;
	virtual const char* DLLCALL GetCityNames(int i) = 0;
	virtual const char* DLLCALL GetSoundtrackKey() = 0;
};

// {E8414191-00BB-47A1-9933-D6BC9DF7D889}
static const GUID guidICvColorInfo1 =
{0xe8414191, 0x00bb, 0x47a1, {0x99, 0x33, 0xd6, 0xbc, 0x9d, 0xf7, 0xd8, 0x89}};

struct CvColorA;
class ICvColorInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvColorInfo1; }
	virtual const char* DLLCALL GetType() = 0;
	virtual const CvColorA& DLLCALL GetColor() = 0;
};

// {4057ACD7-50C1-4598-AFF6-0FC21598CA5E}
static const GUID guidICvPlayerOptionInfo1 =
{0x4057acd7, 0x50c1, 0x4598, {0xaf, 0xf6, 0x0f, 0xc2, 0x15, 0x98, 0xca, 0x5e}};

class ICvPlayerOptionInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvPlayerOptionInfo1; }

	virtual bool DLLCALL GetDefault() = 0;
};

class ICvInterfaceModeInfo1 : public ICvUnknown
{
public:
	// TODO: ICvInterfaceModeInfo1::GetInterfaceId (Beyond Earth GUID).
	virtual int DLLCALL GetMissionType() = 0;
};

// {F7C7CC11-394D-4EC5-BB3A-399FC7405459}
static const GUID guidICvUnit1 =
{0xf7c7cc11, 0x394d, 0x4ec5, {0xbb, 0x3a, 0x39, 0x9f, 0xc7, 0x40, 0x54, 0x59}};

class ICvUnit1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvUnit1; }
	// TODO: ICvUnit1 (remaining SDK methods and Beyond Earth changes).
};

// {92D85D44-7102-4093-941E-5A99849FFE7B}
static const GUID guidICvPolicyInfo1 =
{0x92d85d44, 0x7102, 0x4093, {0x94, 0x1e, 0x5a, 0x99, 0x84, 0x9f, 0xfe, 0x7b}};

class ICvPolicyInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvPolicyInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	// Beyond Earth adds this slot after the SDK's description getter.
	virtual bool DLLCALL IsKickerPolicy() = 0;
};

// {895B6976-33D1-44AA-95B6-E951CE12AAFC}
static const GUID guidICvMissionInfo1 =
{0x895b6976, 0x33d1, 0x44aa, {0x95, 0xb6, 0xe9, 0x51, 0xce, 0x12, 0xaa, 0xfc}};

class ICvMissionInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvMissionInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
};

// {C789E475-1D7B-4428-B777-145D2D09EDA0}
static const GUID guidICvVictoryInfo1 =
{0xc789e475, 0x1d7b, 0x4428, {0xb7, 0x77, 0x14, 0x5d, 0x2d, 0x09, 0xed, 0xa0}};

class ICvVictoryInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvVictoryInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
};

// {6D88E55D-C179-4EA0-BA92-B4FD7A42ABDF}
static const GUID guidICvPromotionInfo1 =
{0x6d88e55d, 0xc179, 0x4ea0, {0xba, 0x92, 0xb4, 0xfd, 0x7a, 0x42, 0xab, 0xdf}};

class ICvPromotionInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvPromotionInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
};

// {8630C786-FC47-43C7-9729-394C43DC39BF}
static const GUID guidICvBuildInfo1 =
{ 0x8630c786, 0xfc47, 0x43c7, { 0x97, 0x29, 0x39, 0x4c, 0x43, 0xdc, 0x39, 0xbf } };

class ICvBuildInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvBuildInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	// Beyond Earth adds entity-event slots before improvement and route.
	virtual const char* DLLCALL GetEntityEventType() = 0;
	virtual int DLLCALL GetEntityEvent() = 0;
	virtual int DLLCALL GetImprovement() = 0;
	virtual int DLLCALL GetRoute() = 0;
};

// {B9885768-1B1D-41F7-9974-10EDB7FFB342}
static const GUID guidICvNetLoadGameInfo1 =
{ 0xb9885768, 0x1b1d, 0x41f7, { 0x99, 0x74, 0x10, 0xed, 0xb7, 0xff, 0xb3, 0x42 } };

class ICvNetLoadGameInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvNetLoadGameInfo1; }

	virtual bool DLLCALL Read(FDataStream& kStream) = 0;
	virtual bool DLLCALL Write(FDataStream& kStream) = 0;
	virtual bool DLLCALL Commit() = 0;
};

// {BA4940C1-E77C-45AE-B802-76BCD8E130CF}
static const GUID guidICvLeaderHeadInfo1 =
{ 0xba4940c1, 0xe77c, 0x45ae, { 0xb8, 0x02, 0x76, 0xbc, 0xd8, 0xe1, 0x30, 0xcf } };

class ICvLeaderHeadInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvLeaderHeadInfo1; }

	virtual const char* DLLCALL GetDescription() = 0;
	virtual const char* DLLCALL GetArtDefineTag() = 0;
};

// {A7667130-0837-4313-83D9-412B41309F24}
static const GUID guidICvUnitCombatClassInfo1 =
{ 0xa7667130, 0x0837, 0x4313, { 0x83, 0xd9, 0x41, 0x2b, 0x41, 0x30, 0x9f, 0x24 } };

class ICvUnitCombatClassInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvUnitCombatClassInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
};

// {9C945D7A-42E9-406A-AE4B-C91F464954B1}
static const GUID guidICvHandicapInfo1 =
{ 0x9c945d7a, 0x42e9, 0x406a, { 0xae, 0x4b, 0xc9, 0x1f, 0x46, 0x49, 0x54, 0xb1 } };

class ICvHandicapInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvHandicapInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	// Beyond Earth renames the SDK GetBarbSpawnMod slot.
	virtual int DLLCALL GetAlienSpawnMod() = 0;
};

// {5A7C97D9-58A3-4FBD-8364-7135EDB5E209}
static const GUID guidICvGameSpeedInfo1 =
{ 0x5a7c97d9, 0x58a3, 0x4fbd, { 0x83, 0x64, 0x71, 0x35, 0xed, 0xb5, 0xe2, 0x09 } };

class ICvGameSpeedInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvGameSpeedInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	// NOTE: GetBarbPercent does not exist in Beyond Earth game core.
	// virtual int DLLCALL GetBarbPercent() = 0;
	// Beyond Earth adds mid- and late-game turn slots.
	virtual int DLLCALL GetMidGameTurn() = 0;
	virtual int DLLCALL GetLateGameTurn() = 0;
};

// {9A635FE2-E49E-41E0-B407-A1F6DBB4DB4D}
static const GUID guidICvGameOptionInfo1 =
{ 0x9a635fe2, 0xe49e, 0x41e0, { 0xb4, 0x07, 0xa1, 0xf6, 0xdb, 0xb4, 0xdb, 0x4d } };

class ICvGameOptionInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvGameOptionInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	virtual bool DLLCALL GetDefault() = 0;
};

// {252463BA-8460-4362-8582-6E30BDBF915C}
static const GUID guidICvMissionData1 =
{ 0x252463ba, 0x8460, 0x4362, { 0x85, 0x82, 0x6e, 0x30, 0xbd, 0xbf, 0x91, 0x5c } };

class ICvMissionData1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvMissionData1; }

	virtual int DLLCALL GetData1() const = 0;
	virtual int DLLCALL GetData2() const = 0;
	virtual int DLLCALL GetFlags() const = 0;
	virtual int DLLCALL GetPushTurn() const = 0;
	virtual MissionTypes DLLCALL GetMissionType() const = 0;
};

// {CA8E279E-428F-4C42-BDF6-9FE7FEA9810F}
static const GUID guidICvWorldInfo1 =
{ 0xca8e279e, 0x428f, 0x4c42, { 0xbd, 0xf6, 0x9f, 0xe7, 0xfe, 0xa9, 0x81, 0x0f } };

class ICvWorldInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvWorldInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescriptionKey() = 0;
	virtual int DLLCALL GetDefaultPlayers() = 0;
	// NOTE: GetDefaultMinorCivs does not exist in Beyond Earth game core.
	// virtual int DLLCALL GetDefaultMinorCivs() = 0;
	// Beyond Earth adds grid-dimension slots.
	virtual int DLLCALL GetGridWidth() = 0;
	virtual int DLLCALL GetGridHeight() = 0;
};

// {08011D93-D264-457D-B109-1A958DCB6EF1}
static const GUID guidICvEraInfo1 =
{ 0x08011d93, 0xd264, 0x457d, { 0xb1, 0x09, 0x1a, 0x95, 0x8d, 0xcb, 0x6e, 0xf1 } };

class ICvEraInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvEraInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	virtual int DLLCALL GetNumEraVOs() = 0;
	virtual const char* DLLCALL GetEraVO(int iIndex) = 0;
	virtual const char* DLLCALL GetArtPrefix() = 0;
};

// Beyond Earth changes the GUID and adds polar technology-web coordinates.
// {5A5A940B-31A5-4869-A28C-DC8A1D45FD89}
static const GUID guidICvTechInfo1 =
{ 0x5a5a940b, 0x31a5, 0x4869, { 0xa2, 0x8c, 0xdc, 0x8a, 0x1d, 0x45, 0xfd, 0x89 } };

class ICvTechInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvTechInfo1; }

	virtual const char* DLLCALL GetDescription() const = 0;
	virtual const char* DLLCALL GetType() const = 0;
	virtual const char* DLLCALL GetText() const = 0;
	virtual int DLLCALL GetEra() const = 0;
	virtual int DLLCALL GetGridRadius() const = 0;
	virtual int DLLCALL GetGridDegrees() const = 0;
	virtual const char* DLLCALL GetSound() const = 0;
	virtual const char* DLLCALL GetSoundMP() const = 0;
};

// Beyond Earth uses a different player-color interface GUID.
// {3CCE3E73-D97A-4DD4-84A6-6636A434D384}
static const GUID guidICvPlayerColorInfo1 =
{ 0x3cce3e73, 0xd97a, 0x4dd4, { 0x84, 0xa6, 0x66, 0x36, 0xa4, 0x34, 0xd3, 0x84 } };

class ICvPlayerColorInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvPlayerColorInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual ColorTypes DLLCALL GetColorTypePrimary() = 0;
	virtual ColorTypes DLLCALL GetColorTypeSecondary() = 0;
};

// Beyond Earth changes the resource GUID and adds an improvement predicate.
// {CA779B89-8A7A-401D-B080-B91A50F1BD1F}
static const GUID guidICvResourceInfo1 =
{ 0xca779b89, 0x8a7a, 0x401d, { 0xb0, 0x80, 0xb9, 0x1a, 0x50, 0xf1, 0xbd, 0x1f } };

class ICvResourceInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvResourceInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	virtual int DLLCALL GetResourceClassType() = 0;
	virtual ResourceUsageTypes DLLCALL GetResourceUsage() = 0;
	virtual const char* DLLCALL GetIconString() = 0;
	virtual const char* DLLCALL GetArtDefineTag() = 0;
	virtual const char* DLLCALL GetArtDefineTagHeavy() = 0;
	virtual const char* DLLCALL GetAltArtDefineTag() = 0;
	virtual const char* DLLCALL GetAltArtDefineTagHeavy() = 0;
	virtual bool DLLCALL IsTerrain(int i) = 0;
	virtual bool DLLCALL IsFeature(int i) = 0;
	virtual bool DLLCALL IsFeatureTerrain(int i) = 0;
	virtual bool DLLCALL ImprovementInResource() const = 0;
};

// Beyond Earth changes the GUID and adds a soundscape refresh operation.
// {9151D6C6-0D2B-497A-BB76-8A279364FE1D}
static const GUID guidICvTerrainInfo1 =
{ 0x9151d6c6, 0x0d2b, 0x497a, { 0xbb, 0x76, 0x8a, 0x27, 0x93, 0x64, 0xfe, 0x1d } };

class ICvTerrainInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvTerrainInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	virtual bool DLLCALL IsWater() = 0;
	virtual const char* DLLCALL GetArtDefineTag() = 0;
	virtual int DLLCALL GetWorldSoundscapeScriptId() = 0;
	virtual void DLLCALL RefreshWorldSoundscapeID() = 0;
	virtual const char* DLLCALL GetEffectTypeTag() = 0;
};

// Beyond Earth replaces the natural-wonder slot with soundscape refresh.
// {9CB1CCD8-CD13-4F0D-BE54-40E1A2BA97F3}
static const GUID guidICvFeatureInfo1 =
{ 0x9cb1ccd8, 0xcd13, 0x4f0d, { 0xbe, 0x54, 0x40, 0xe1, 0xa2, 0xba, 0x97, 0xf3 } };

class ICvFeatureInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvFeatureInfo1; }

	virtual const char* DLLCALL GetType() = 0;
	virtual const char* DLLCALL GetDescription() = 0;
	virtual bool DLLCALL IsNoCoast() = 0;
	virtual bool DLLCALL IsNoRiver() = 0;
	virtual bool DLLCALL IsNoAdjacent() = 0;
	virtual bool DLLCALL IsRequiresFlatlands() = 0;
	virtual bool DLLCALL IsRequiresRiver() = 0;
	// NOTE: IsNaturalWonder does not exist in the Beyond Earth interface.
	// virtual bool DLLCALL IsNaturalWonder() = 0;
	virtual const char* DLLCALL GetArtDefineTag() = 0;
	virtual int DLLCALL GetWorldSoundscapeScriptId() = 0;
	virtual void DLLCALL RefreshWorldSoundscapeID() = 0;
	virtual const char* DLLCALL GetEffectTypeTag() = 0;
	virtual bool DLLCALL IsTerrain(int i) = 0;
};

// Beyond Earth uses a different deal interface GUID.
// {82793400-F09F-492C-8EA9-28BAC5296B2B}
static const GUID guidICvDeal1 =
{ 0x82793400, 0xf09f, 0x492c, { 0x8e, 0xa9, 0x28, 0xba, 0xc5, 0x29, 0x6b, 0x2b } };

class ICvDeal1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvDeal1; }

	virtual PlayerTypes DLLCALL GetOtherPlayer(PlayerTypes eFromPlayer) = 0;
	virtual PlayerTypes DLLCALL GetToPlayer() = 0;
	virtual PlayerTypes DLLCALL GetFromPlayer() = 0;
	virtual unsigned int DLLCALL GetStartTurn() = 0;
	virtual unsigned int DLLCALL GetDuration() = 0;
	virtual unsigned int DLLCALL GetEndTurn() = 0;

	virtual void DLLCALL CopyFrom(ICvDeal1* pOtherDeal) = 0;
	virtual void DLLCALL Read(FDataStream& kStream) = 0;
	virtual void DLLCALL Write(FDataStream& kStream) = 0;
};

// Beyond Earth changes the GUID, adds text/art/orbital getters and omits the flag offset.
// {5CCB91A7-FCCC-44C5-9B1E-7EE77952D5A8}
static const GUID guidICvUnitInfo1 =
{ 0x5ccb91a7, 0xfccc, 0x44c5, { 0x9b, 0x1e, 0x7e, 0xe7, 0x79, 0x52, 0xd5, 0xa8 } };

class ICvUnitInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvUnitInfo1; }

	virtual int DLLCALL GetCombat() const = 0;
	virtual int DLLCALL GetDomainType() const = 0;
	virtual const char* DLLCALL GetType() const = 0;
	virtual const char* DLLCALL GetText() const = 0;
	virtual const char* DLLCALL GetTextKey() const = 0;
	virtual UnitMoveRate DLLCALL GetMoveRate(int numHexes) const = 0;
	virtual const char* DLLCALL GetUnitArtInfoTag() const = 0;
	virtual bool DLLCALL GetUnitArtInfoCulturalVariation() const = 0;
	virtual bool DLLCALL GetUnitArtInfoEraVariation() const = 0;
	virtual bool DLLCALL GetUnitArtInfoUpgradeVariation() const = 0;
	virtual int DLLCALL GetUnitArtInfoVariationStart() const = 0;
	virtual bool DLLCALL GetUnitArtInfoAmphibiousVariation() const = 0;
	virtual int DLLCALL GetOrbitalUnitType() const = 0;
	// NOTE: GetUnitFlagIconOffset does not exist in Beyond Earth game core.
	// virtual int DLLCALL GetUnitFlagIconOffset() const = 0;
};

// Beyond Earth uses a different building-interface GUID and omits five SDK getters.
// {92510AC0-DC46-47B5-8A5D-FAAFBBACAF0E}
static const GUID guidICvBuildingInfo1 =
{ 0x92510ac0, 0xdc46, 0x47b5, { 0x8a, 0x5d, 0xfa, 0xaf, 0xbb, 0xac, 0xaf, 0x0e } };

class ICvBuildingInfo1 : public ICvUnknown
{
public:
	// The SDK returns guidICvCombatInfo1 here; use the actual target building GUID.
	static GUID DLLCALL GetInterfaceId() { return guidICvBuildingInfo1; }

	virtual const char* DLLCALL GetType() const = 0;
	virtual const char* DLLCALL GetText() const = 0;
	virtual int DLLCALL GetPreferredDisplayPosition() const = 0;
	// NOTE: Border-obstacle getters do not exist in Beyond Earth game core.
	// virtual bool DLLCALL IsBorderObstacle() const = 0;
	// virtual bool DLLCALL IsPlayerBorderObstacle() const = 0;
	virtual const char* DLLCALL GetArtDefineTag() const = 0;
	// NOTE: Building art-variation getters do not exist in Beyond Earth game core.
	// virtual const bool DLLCALL GetArtInfoCulturalVariation() const = 0;
	// virtual const bool DLLCALL GetArtInfoEraVariation() const = 0;
	// virtual const bool DLLCALL GetArtInfoRandomVariation() const = 0;
	virtual const char* DLLCALL GetWonderSplashAudio() const = 0;
};

// Beyond Earth uses a different improvement-interface GUID and adds three methods.
// {80DFC281-D8A4-4107-8A43-529871F17743}
static const GUID guidICvImprovementInfo1 =
{ 0x80dfc281, 0xd8a4, 0x4107, { 0x8a, 0x43, 0x52, 0x98, 0x71, 0xf1, 0x77, 0x43 } };

class ICvImprovementInfo1 : public ICvUnknown
{
public:
	static GUID DLLCALL GetInterfaceId() { return guidICvImprovementInfo1; }

	virtual const char* DLLCALL GetType() const = 0;
	virtual const char* DLLCALL GetText() const = 0;
	virtual bool DLLCALL IsWater() const = 0;
	virtual bool DLLCALL IsDestroyedWhenPillaged() const = 0;
	virtual bool DLLCALL IsGoody() const = 0;
	virtual const char* DLLCALL GetArtDefineTag() const = 0;
	virtual ImprovementUsageTypes DLLCALL GetImprovementUsage() const = 0;
	virtual int DLLCALL GetWorldSoundscapeScriptId() const = 0;
	virtual void DLLCALL RefreshWorldSoundscapeID() = 0;
	virtual bool DLLCALL GetTerrainMakesValid(int i) const = 0;
	virtual bool DLLCALL IsImprovementResourceMakesValid(int i) const = 0;
	virtual bool DLLCALL IsSelectable() const = 0;
	virtual bool DLLCALL ResourceStaysVisible() const = 0;
};

// TODO: CvDllInterfaces.h (remaining SDK interfaces).