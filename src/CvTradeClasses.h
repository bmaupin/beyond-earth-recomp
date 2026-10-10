#pragma once

#include <vector>

struct TradeConnection
{
	int m_iID;
	char m_padding[0x1dc];
};

class CvGameTrade
{
public:
	std::vector<TradeConnection> GetCovertOpsVisibleTradeRoutes(PlayerTypes ePlayer) const;
};
