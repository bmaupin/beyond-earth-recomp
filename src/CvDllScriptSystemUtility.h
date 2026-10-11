#pragma once

#include "CvDllInterfaces.h"

class CvDllScriptSystemUtility : public ICvScriptSystemUtility1
{
public:
	// TODO: Phase1 CvDllScriptSystemUtility::CvDllScriptSystemUtility — UNVERIFIED: Full operand and relocation-target comparison not established.
	CvDllScriptSystemUtility();
	~CvDllScriptSystemUtility();

	// TODO: Phase1 CvDllScriptSystemUtility::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
	void* DLLCALL QueryInterface(GUID guidInterface);
	// TODO: Phase1 CvDllScriptSystemUtility::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
	static void operator delete(void* p);
	// TODO: Phase1 CvDllScriptSystemUtility::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
	static void* operator new(size_t bytes);

	// TODO: Phase1 CvDllScriptSystemUtility::RegisterScriptLibraries — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL RegisterScriptLibraries(lua_State* L);
	// TODO: Phase1 CvDllScriptSystemUtility::PushCvCityInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL PushCvCityInstance(lua_State* L, ICvCity1* pCity);
	// TODO: Phase1 CvDllScriptSystemUtility::GetCvCityInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvCity1* DLLCALL GetCvCityInstance(lua_State* L, int index, bool bErrorOnFail = true);
	// TODO: Phase1 CvDllScriptSystemUtility::PushCvDealInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL PushCvDealInstance(lua_State* L, ICvDeal1* pDeal);
	// TODO: Phase1 CvDllScriptSystemUtility::GetCvDealInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvDeal1* DLLCALL GetCvDealInstance(lua_State* L, int index, bool bErrorOnFail = true);
	// TODO: Phase1 CvDllScriptSystemUtility::PushCvPlotInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL PushCvPlotInstance(lua_State* L, ICvPlot1* pPlot);
	// TODO: Phase1 CvDllScriptSystemUtility::GetCvPlotInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvPlot1* DLLCALL GetCvPlotInstance(lua_State* L, int index, bool bErrorOnFail = true);
	// TODO: Phase1 CvDllScriptSystemUtility::PushCvUnitInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL PushCvUnitInstance(lua_State* L, ICvUnit1* pUnit);
	// TODO: Phase1 CvDllScriptSystemUtility::GetCvUnitInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvUnit1* DLLCALL GetCvUnitInstance(lua_State* L, int index, bool bErrorOnFail = true);
	// TODO: Phase1 CvDllScriptSystemUtility::PushReplayFromStream — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	void DLLCALL PushReplayFromStream(lua_State* L, FDataStream& stream);

	// Beyond Earth's additional wrappers are nonvirtual, outside the utility interface.
	// TODO: Phase1 CvDllScriptSystemUtility::PushCvOutpostInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL PushCvOutpostInstance(lua_State* L, ICvOutpost1* pOutpost);
	// TODO: Phase1 CvDllScriptSystemUtility::GetCvOutpostInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvOutpost1* DLLCALL GetCvOutpostInstance(lua_State* L, int index, bool bErrorOnFail = true);
	// TODO: Phase1 CvDllScriptSystemUtility::PushCvStationInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL PushCvStationInstance(lua_State* L, ICvStation1* pStation);
	// TODO: Phase1 CvDllScriptSystemUtility::GetCvStationInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvStation1* DLLCALL GetCvStationInstance(lua_State* L, int index, bool bErrorOnFail = true);
	// TODO: Phase1 CvDllScriptSystemUtility::PushCvStrategicSiteInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
	void DLLCALL PushCvStrategicSiteInstance(lua_State* L, ICvStrategicSite1* pStrategicSite);
	// TODO: Phase1 CvDllScriptSystemUtility::GetCvStrategicSiteInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
	ICvStrategicSite1* DLLCALL GetCvStrategicSiteInstance(lua_State* L, int index, bool bErrorOnFail = true);

private:
	void DLLCALL Destroy();
};
