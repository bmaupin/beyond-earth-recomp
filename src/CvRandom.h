#pragma once
#ifndef CIV5_RANDOM_H
#define CIV5_RANDOM_H

// Partial SDK declaration; remaining methods are not reconstructed.
class CvRandom
{
public:
	virtual ~CvRandom();
	void init(unsigned long ulSeed);
	void reset(unsigned long ulSeed = 0);
	unsigned short get(unsigned short usNum, const char* pszLog = NULL);
	float getFloat();
	unsigned long getSeed() const;

protected:
	unsigned long m_ulRandomSeed;
	unsigned long m_ulCallCount;
	unsigned long m_ulResetCount;
	bool m_bSynchronous;
};

FDataStream& operator<<(FDataStream& saveTo, const CvRandom& readFrom);
FDataStream& operator>>(FDataStream& loadFrom, CvRandom& writeTo);
#endif
