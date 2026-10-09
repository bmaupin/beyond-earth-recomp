#pragma once

#include "CvDiplomacyAIEnums.h"
#include "Fireworks/FFastList.h"

class FDataStream;

// Beyond Earth replaces gold with energy and adds research, alliance and favor trades.
enum TradeableItems
{
	TRADE_ITEM_NONE = -1,
	TRADE_ITEM_ENERGY,
	TRADE_ITEM_ENERGY_PER_TURN,
	TRADE_ITEM_RESEARCH_PER_TURN,
	TRADE_ITEM_MAPS,
	TRADE_ITEM_RESOURCES,
	TRADE_ITEM_CITIES,
	TRADE_ITEM_UNITS,
	TRADE_ITEM_OPEN_BORDERS,
	TRADE_ITEM_ALLIANCE,
	TRADE_ITEM_TRADE_AGREEMENT,
	TRADE_ITEM_PERMANENT_ALLIANCE,
	TRADE_ITEM_SURRENDER,
	TRADE_ITEM_TRUCE,
	TRADE_ITEM_PEACE_TREATY,
	TRADE_ITEM_THIRD_PARTY_PEACE,
	TRADE_ITEM_THIRD_PARTY_WAR,
	TRADE_ITEM_THIRD_PARTY_EMBARGO,
	TRADE_ITEM_COOPERATION_AGREEMENT,
	TRADE_ITEM_FAVOR,
	NUM_TRADEABLE_ITEMS
};

struct CvTradedItem
{
	CvTradedItem();
	bool operator==(const CvTradedItem& rhs) const;

	TradeableItems m_eItemType;
	int m_iDuration;
	int m_iFinalTurn;
	int m_iData1;
	int m_iData2;
	int m_iData3;
	bool m_bFlag1;
	PlayerTypes m_eFromPlayer;
	bool m_bFromRenewed;
	bool m_bToRenewed;
};
typedef FFastList<CvTradedItem, 19, 0> TradedItemList;

class CvDeal
{
public:
	CvDeal();
	CvDeal(PlayerTypes eFromPlayer, PlayerTypes eToPlayer);
	CvDeal(const CvDeal& source);
	virtual ~CvDeal();
	CvDeal& operator=(const CvDeal& source);

	PlayerTypes m_eFromPlayer;
	PlayerTypes m_eToPlayer;
	int m_iStartTurn;
	int m_iFinalTurn;
	int m_iDuration;
	PeaceTreatyTypes m_ePeaceTreatyType;
	PlayerTypes m_eSurrenderingPlayer;
	PlayerTypes m_eDemandingPlayer;
	PlayerTypes m_eRequestingPlayer;
	bool m_bConsideringForRenewal;
	bool m_bCheckedForRenewal;
	bool m_bDealCancelled;
	TradedItemList m_TradedItems;

	void ClearItems();
	int GetNumItems();
	void SetFromPlayer(PlayerTypes ePlayer);
	void SetToPlayer(PlayerTypes ePlayer);
	PlayerTypes GetSurrenderingPlayer() const;
	void SetSurrenderingPlayer(PlayerTypes ePlayer);
	PlayerTypes GetDemandingPlayer() const;
	void SetDemandingPlayer(PlayerTypes ePlayer);
	PlayerTypes GetRequestingPlayer() const;
	void SetRequestingPlayer(PlayerTypes ePlayer);
	int GetGoldAvailable(PlayerTypes ePlayer, TradeableItems eItem);
	bool IsPossibleToTradeItem(PlayerTypes eFromPlayer, PlayerTypes eToPlayer, TradeableItems eItem,
	                          int iData1 = -1, int iData2 = -1, int iData3 = -1,
	                          bool bFlag1 = false, bool bCheckOtherPlayerValidity = true, bool bFinalizing = false);
	int GetNumResource(PlayerTypes ePlayer, ResourceTypes eResource);
	void AddEnergyTrade(PlayerTypes eFromPlayer, int iAmount);
	void AddEnergyPerTurnTrade(PlayerTypes eFromPlayer, int iAmount, int iDuration);
	void AddResearchPerTurnTrade(PlayerTypes eFromPlayer, int iAmount, int iDuration);
	void AddMapTrade(PlayerTypes eFromPlayer);
	void AddResourceTrade(PlayerTypes eFromPlayer, ResourceTypes eResource, int iAmount, int iDuration);
	void AddCityTrade(PlayerTypes eFromPlayer, int iCityID);
	void AddUnitTrade(PlayerTypes eFromPlayer, int iUnitID);
	void AddOpenBorders(PlayerTypes eFromPlayer, int iDuration);
	void AddAlliance(PlayerTypes eFromPlayer, int iDuration);
	void AddTradeAgreement(PlayerTypes eFromPlayer, int iDuration);
	void AddPermamentAlliance();
	void AddSurrender(PlayerTypes eFromPlayer);
	void AddTruce();
	void AddPeaceTreaty(PlayerTypes eFromPlayer, int iDuration);
	void AddThirdPartyPeace(PlayerTypes eFromPlayer, TeamTypes eThirdPartyTeam, int iDuration);
	void AddThirdPartyWar(PlayerTypes eFromPlayer, TeamTypes eThirdPartyTeam);
	void AddThirdPartyEmbargo(PlayerTypes eFromPlayer, PlayerTypes eThirdPartyPlayer, int iDuration);
	void AddCooperationAgreement(PlayerTypes eFromPlayer);
	void AddFavorTrade(PlayerTypes eFromPlayer, int iAmount);
	bool ChangeGoldTrade(PlayerTypes eFromPlayer, int iAmount);
	bool ChangeGoldPerTurnTrade(PlayerTypes eFromPlayer, int iAmount, int iDuration);
	bool ChangeResearchPerTurnTrade(PlayerTypes eFromPlayer, int iAmount, int iDuration);
	bool SetFavorTrade(PlayerTypes eFromPlayer, int iAmount);
	bool ChangeResourceTrade(PlayerTypes eFromPlayer, ResourceTypes eResource, int iAmount, int iDuration);
	void ChangeThirdPartyWarDuration(PlayerTypes eFromPlayer, TeamTypes eThirdPartyTeam, int iDuration);
	void ChangeThirdPartyPeaceDuration(PlayerTypes eFromPlayer, TeamTypes eThirdPartyTeam, int iDuration);
	void ChangeThirdPartyEmbargoDuration(PlayerTypes eFromPlayer, PlayerTypes eThirdPartyPlayer, int iDuration);
	void RemoveByType(TradeableItems eItem, PlayerTypes eFromPlayer);
	void RemoveResourceTrade(ResourceTypes eResource);
	void RemoveCityTrade(PlayerTypes eFromPlayer, int iCityID);
	void RemoveUnitTrade(int iUnitID);
	void RemoveThirdPartyPeace(PlayerTypes eFromPlayer, TeamTypes eThirdPartyTeam);
	void RemoveThirdPartyWar(PlayerTypes eFromPlayer, TeamTypes eThirdPartyTeam);
	void RemoveThirdPartyEmbargo(PlayerTypes eFromPlayer, PlayerTypes eThirdPartyPlayer);

	PlayerTypes GetOtherPlayer(PlayerTypes eFromPlayer) const;
	PlayerTypes GetToPlayer() const
	{
		return m_eToPlayer;
	};
	PlayerTypes GetFromPlayer() const
	{
		return m_eFromPlayer;
	};
	uint GetStartTurn() const
	{
		return m_iStartTurn;
	};
	uint GetDuration() const
	{
		return m_iDuration;
	};
	uint GetEndTurn() const
	{
		return m_iFinalTurn;
	};
	// TODO: CvDeal (remaining SDK and Beyond Earth methods).
};

FDataStream& operator>>(FDataStream&, CvDeal&);
FDataStream& operator<<(FDataStream&, const CvDeal&);

// TODO: CvGameDeals.
