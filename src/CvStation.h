#pragma once

class CvStation;

class CvGameMinorPowers
{
public:
	CvStation* GetStation(int iID);
	CvStation* GetStationByPlot(int iPlotIndex);
	CvStation* FirstStation(int* pIndex, bool bRevive);
	CvStation* NextStation(int* pIndex, bool bRevive);

	int GetNumStations() const
	{
		return m_iStationEnd + 1 - m_iStationBegin;
	}

private:
	char m_padding[8];
	int m_iStationBegin;
	int m_iStationEnd;
};
