#include "CvGameCoreDLLPCH.h"
#include "CvDllScriptSystemUtility.h"
#include "CvDllContext.h"
#include "CvDllCity.h"
#include "CvDllOutpost.h"
#include "CvDllStation.h"
#include "CvDllStrategicSite.h"
#include "CvDllDeal.h"
#include "CvDllPlot.h"
#include "CvDllUnit.h"
#include "Lua/CvLuaSupport.h"
#include "Lua/CvLuaCity.h"
#include "Lua/CvLuaOutpost.h"
#include "Lua/CvLuaStation.h"
#include "Lua/CvLuaStrategicSite.h"
#include "Lua/CvLuaDeal.h"
#include "Lua/CvLuaPlot.h"
#include "Lua/CvLuaUnit.h"
#include "CvReplayInfo.h"
#include "CvReplayMessage.h"

static_assert(sizeof(CvDllScriptSystemUtility) == 4, "Beyond Earth utility layout");
static_assert(sizeof(CvReplayInfo) == 0xac, "Beyond Earth replay layout");
static_assert(sizeof(CvReplayInfo::PlotState) == 0x10, "Beyond Earth replay plot layout");

// TODO: Phase1 CvDllScriptSystemUtility::CvDllScriptSystemUtility — UNVERIFIED: Full operand and relocation-target comparison not established.
CvDllScriptSystemUtility::CvDllScriptSystemUtility()
{
}

CvDllScriptSystemUtility::~CvDllScriptSystemUtility()
{
}

// TODO: Phase1 CvDllScriptSystemUtility::QueryInterface — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllScriptSystemUtility::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() ||
		guidInterface == ICvScriptSystemUtility1::GetInterfaceId())
		return this;
	return NULL;
}

void CvDllScriptSystemUtility::Destroy()
{
	// The context owns this object; releasing the interface must not destroy it.
}

// TODO: Phase1 CvDllScriptSystemUtility::operator delete — MISMATCH: Non-padding instruction mnemonic sequence differs.
void CvDllScriptSystemUtility::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}

// TODO: Phase1 CvDllScriptSystemUtility::operator new — UNVERIFIED: Full operand and relocation-target comparison not established.
void* CvDllScriptSystemUtility::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}

// TODO: Phase1 CvDllScriptSystemUtility::RegisterScriptLibraries — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllScriptSystemUtility::RegisterScriptLibraries(lua_State* L)
{
	LuaSupport::RegisterScriptData(L);
}

// TODO: Phase1 CvDllScriptSystemUtility::PushCvCityInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllScriptSystemUtility::PushCvCityInstance(lua_State* L, ICvCity1* pCity)
{
	if(L != NULL && pCity != NULL)
		CvLuaCity::Push(L, static_cast<CvDllCity*>(pCity)->GetInstance());
	else
		lua_pushnil(L);
}

// TODO: Phase1 CvDllScriptSystemUtility::GetCvCityInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvCity1* CvDllScriptSystemUtility::GetCvCityInstance(lua_State* L, int index, bool bErrorOnFail)
{
	CvCity* pCity = CvLuaCity::GetInstance(L, index, bErrorOnFail);
	return pCity != NULL ? new CvDllCity(pCity) : NULL;
}

// TODO: Phase1 CvDllScriptSystemUtility::PushCvOutpostInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllScriptSystemUtility::PushCvOutpostInstance(lua_State* L, ICvOutpost1* pOutpost)
{
	if(L != NULL && pOutpost != NULL)
		CvLuaOutpost::Push(L, static_cast<CvDllOutpost*>(pOutpost)->GetInstance());
	else
		lua_pushnil(L);
}

// TODO: Phase1 CvDllScriptSystemUtility::GetCvOutpostInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvOutpost1* CvDllScriptSystemUtility::GetCvOutpostInstance(lua_State* L, int index, bool bErrorOnFail)
{
	CvOutpost* pOutpost = CvLuaOutpost::GetInstance(L, index, bErrorOnFail);
	return pOutpost != NULL ? new CvDllOutpost(pOutpost) : NULL;
}

// TODO: Phase1 CvDllScriptSystemUtility::PushCvStationInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllScriptSystemUtility::PushCvStationInstance(lua_State* L, ICvStation1* pStation)
{
	if(L != NULL && pStation != NULL)
		CvLuaStation::Push(L, static_cast<CvDllStation*>(pStation)->GetInstance());
	else
		lua_pushnil(L);
}

// TODO: Phase1 CvDllScriptSystemUtility::GetCvStationInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvStation1* CvDllScriptSystemUtility::GetCvStationInstance(lua_State* L, int index, bool bErrorOnFail)
{
	CvStation* pStation = CvLuaStation::GetInstance(L, index, bErrorOnFail);
	return pStation != NULL ? new CvDllStation(pStation) : NULL;
}

// TODO: Phase1 CvDllScriptSystemUtility::PushCvStrategicSiteInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllScriptSystemUtility::PushCvStrategicSiteInstance(lua_State* L, ICvStrategicSite1* pStrategicSite)
{
	if(L != NULL && pStrategicSite != NULL)
		CvLuaStrategicSite::Push(L, static_cast<CvDllStrategicSite*>(pStrategicSite)->GetInstance());
	else
		lua_pushnil(L);
}

// TODO: Phase1 CvDllScriptSystemUtility::GetCvStrategicSiteInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvStrategicSite1* CvDllScriptSystemUtility::GetCvStrategicSiteInstance(lua_State* L, int index, bool bErrorOnFail)
{
	CvStrategicSite* pStrategicSite = CvLuaStrategicSite::GetInstance(L, index, bErrorOnFail);
	return pStrategicSite != NULL ? new CvDllStrategicSite(pStrategicSite) : NULL;
}

// TODO: Phase1 CvDllScriptSystemUtility::PushCvDealInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllScriptSystemUtility::PushCvDealInstance(lua_State* L, ICvDeal1* pDeal)
{
	if(L != NULL && pDeal != NULL)
		CvLuaDeal::Push(L, static_cast<CvDllDeal*>(pDeal)->GetInstance());
	else
		lua_pushnil(L);
}

// TODO: Phase1 CvDllScriptSystemUtility::GetCvDealInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvDeal1* CvDllScriptSystemUtility::GetCvDealInstance(lua_State* L, int index, bool bErrorOnFail)
{
	CvDeal* pDeal = CvLuaDeal::GetInstance(L, index, bErrorOnFail);
	return pDeal != NULL ? new CvDllDeal(pDeal) : NULL;
}

// TODO: Phase1 CvDllScriptSystemUtility::PushCvPlotInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllScriptSystemUtility::PushCvPlotInstance(lua_State* L, ICvPlot1* pPlot)
{
	if(L != NULL && pPlot != NULL)
		CvLuaPlot::Push(L, static_cast<CvDllPlot*>(pPlot)->GetInstance());
	else
		lua_pushnil(L);
}

// TODO: Phase1 CvDllScriptSystemUtility::GetCvPlotInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvPlot1* CvDllScriptSystemUtility::GetCvPlotInstance(lua_State* L, int index, bool bErrorOnFail)
{
	CvPlot* pPlot = CvLuaPlot::GetInstance(L, index, bErrorOnFail);
	return pPlot != NULL ? new CvDllPlot(pPlot) : NULL;
}

// TODO: Phase1 CvDllScriptSystemUtility::PushCvUnitInstance — UNVERIFIED: Full operand and relocation-target comparison not established.
void CvDllScriptSystemUtility::PushCvUnitInstance(lua_State* L, ICvUnit1* pUnit)
{
	if(L != NULL && pUnit != NULL)
		CvLuaUnit::Push(L, static_cast<CvDllUnit*>(pUnit)->GetInstance());
	else
		lua_pushnil(L);
}

// TODO: Phase1 CvDllScriptSystemUtility::GetCvUnitInstance — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
ICvUnit1* CvDllScriptSystemUtility::GetCvUnitInstance(lua_State* L, int index, bool bErrorOnFail)
{
	CvUnit* pUnit = CvLuaUnit::GetInstance(L, index, bErrorOnFail);
	return pUnit != NULL ? new CvDllUnit(pUnit) : NULL;
}

// TODO: Phase1 CvDllScriptSystemUtility::PushReplayFromStream — MISMATCH: Target exception cleanup tail absent from required -fno-exceptions build.
void CvDllScriptSystemUtility::PushReplayFromStream(lua_State* L, FDataStream& stream)
{
	CvReplayInfo* pReplay = FNEW(CvReplayInfo(), c_eMPoolTypeGame, 0);
	if(pReplay == NULL)
		return;
	if(!pReplay->read(stream))
	{
		delete pReplay;
		return;
	}

	lua_createtable(L, 0, 0);
	const int replayTable = lua_gettop(L);
	lua_pushstring(L, pReplay->getMapScriptName());
	lua_setfield(L, replayTable, "MapScriptName");
	lua_pushinteger(L, pReplay->getActivePlayer());
	lua_setfield(L, replayTable, "ActivePlayer");
	lua_pushinteger(L, pReplay->getWorldSize());
	lua_setfield(L, replayTable, "WorldSize");
	lua_pushinteger(L, pReplay->getClimate());
	lua_setfield(L, replayTable, "Climate");
	lua_pushinteger(L, pReplay->getSeaLevel());
	lua_setfield(L, replayTable, "SeaLevel");
	lua_pushinteger(L, pReplay->getEra());
	lua_setfield(L, replayTable, "Era");
	lua_pushinteger(L, pReplay->getGameSpeed());
	lua_setfield(L, replayTable, "GameSpeed");
	lua_pushinteger(L, pReplay->getVictoryType());
	lua_setfield(L, replayTable, "VictoryType");
	lua_pushinteger(L, pReplay->getGameType());
	lua_setfield(L, replayTable, "GameType");
	lua_pushinteger(L, pReplay->getInitialTurn());
	lua_setfield(L, replayTable, "InitialTurn");
	lua_pushinteger(L, pReplay->getFinalTurn());
	lua_setfield(L, replayTable, "FinalTurn");
	lua_pushinteger(L, pReplay->getStartYear());
	lua_setfield(L, replayTable, "StartYear");
	lua_pushstring(L, pReplay->getFinalDate());
	lua_setfield(L, replayTable, "FinalDate");
	lua_pushinteger(L, pReplay->getCalendar());
	lua_setfield(L, replayTable, "Calendar");
	lua_pushinteger(L, pReplay->getNormalizedScore());
	lua_setfield(L, replayTable, "NormalizedScore");
	lua_pushinteger(L, pReplay->getMapHeight());
	lua_setfield(L, replayTable, "MapHeight");
	lua_pushinteger(L, pReplay->getMapWidth());
	lua_setfield(L, replayTable, "MapWidth");

	const int numPlayers = pReplay->getNumPlayers();
	lua_createtable(L, numPlayers, 0);
	const unsigned int numDataSets = pReplay->getNumPlayerDataSets();
	for(int player = 0; player < numPlayers; ++player)
	{
		lua_createtable(L, 0, 0);
		const int playerTable = lua_gettop(L);
		lua_pushinteger(L, pReplay->getPlayerCivilization(player));
		lua_setfield(L, playerTable, "Civilization");
		lua_pushinteger(L, pReplay->getPlayerLeader(player));
		lua_setfield(L, playerTable, "Leader");
		lua_pushinteger(L, pReplay->getPlayerColor(player));
		lua_setfield(L, playerTable, "PlayerColor");
		lua_pushinteger(L, pReplay->getPlayerDifficulty(player));
		lua_setfield(L, playerTable, "Difficulty");
		lua_pushstring(L, pReplay->getPlayerLeaderName(player));
		lua_setfield(L, playerTable, "LeaderName");
		lua_pushstring(L, pReplay->getPlayerCivDescription(player));
		lua_setfield(L, playerTable, "CivDescription");
		lua_pushstring(L, pReplay->getPlayerShortCivDescription(player));
		lua_setfield(L, playerTable, "CivShortDescription");
		lua_pushstring(L, pReplay->getPlayerCivAdjective(player));
		lua_setfield(L, playerTable, "CivAdjective");
		lua_createtable(L, 0, 0);
		const int finalTurn = pReplay->getFinalTurn();
		for(int turn = pReplay->getInitialTurn(); turn <= finalTurn; ++turn)
		{
			lua_createtable(L, 0, 0);
			for(unsigned int dataSet = 0; dataSet < numDataSets; ++dataSet)
			{
				int value = 0;
				if(pReplay->getPlayerDataSetValue(player, dataSet, turn, value))
				{
					lua_pushinteger(L, value);
					lua_setfield(L, -2, pReplay->getPlayerDataSetName(dataSet));
				}
			}
			lua_rawseti(L, -2, turn);
		}
		lua_setfield(L, playerTable, "Scores");
		lua_rawseti(L, -2, player + 1);
	}
	lua_setfield(L, replayTable, "PlayerInfo");

	const int numMessages = pReplay->getNumReplayMessages();
	lua_createtable(L, numMessages, 0);
	for(int message = 0; message < numMessages; ++message)
	{
		const CvReplayMessage* pMessage = pReplay->getReplayMessage(message);
		lua_createtable(L, 0, 0);
		lua_pushinteger(L, pMessage->getTurn());
		lua_setfield(L, -2, "Turn");
		lua_pushinteger(L, pMessage->getType());
		lua_setfield(L, -2, "Type");
		const int player = pMessage->getPlayer();
		lua_pushinteger(L, player > -1 ? player + 1 : player);
		lua_setfield(L, -2, "Player");
		lua_pushstring(L, pMessage->getText());
		lua_setfield(L, -2, "Text");
		const int numPlots = pMessage->getNumPlots();
		lua_createtable(L, numPlots, 0);
		for(int plot = 0; plot < numPlots; ++plot)
		{
			int x = 0;
			int y = 0;
			pMessage->getPlot(plot, x, y);
			lua_createtable(L, 0, 2);
			lua_pushinteger(L, x);
			lua_setfield(L, -2, "X");
			lua_pushinteger(L, y);
			lua_setfield(L, -2, "Y");
			lua_rawseti(L, -2, plot + 1);
		}
		lua_setfield(L, -2, "Plots");
		// Messages deliberately retain zero-based indices, unlike players and plots.
		lua_rawseti(L, -2, message);
	}
	lua_setfield(L, replayTable, "Messages");

	const int height = pReplay->getMapHeight();
	const int width = pReplay->getMapWidth();
	lua_createtable(L, height * width, 0);
	int plotIndex = 1;
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			lua_createtable(L, 0, 0);
			for(int turn = pReplay->getInitialTurn(); turn <= pReplay->getFinalTurn(); ++turn)
			{
				CvReplayInfo::PlotState state;
				if(pReplay->getPlotState(x, y, turn, state))
				{
					lua_createtable(L, 6, 0);
					lua_pushinteger(L, state.m_ePlotType);
					lua_setfield(L, -2, "PlotType");
					lua_pushinteger(L, state.m_eTerrain);
					lua_setfield(L, -2, "TerrainType");
					lua_pushinteger(L, state.m_eFeature);
					lua_setfield(L, -2, "FeatureType");
					lua_pushinteger(L, state.m_bNEOfRiver);
					lua_setfield(L, -2, "NEOfRiver");
					lua_pushinteger(L, state.m_bWOfRiver);
					lua_setfield(L, -2, "WOfRiver");
					lua_pushinteger(L, state.m_bNWOfRiver);
					lua_setfield(L, -2, "NWOfRiver");
					lua_rawseti(L, -2, turn);
				}
			}
			lua_rawseti(L, -2, plotIndex++);
		}
	}
	lua_setfield(L, replayTable, "Plots");
	delete pReplay;
}
