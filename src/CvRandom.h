#pragma once
#ifndef CIV5_RANDOM_H
#define CIV5_RANDOM_H

#include <cstddef>
#include <string>
#include <vector>

class FDataStream;

class CvRandom
{
public:
	CvRandom(bool bSynchronous);
	CvRandom();
	CvRandom(const CvRandom& other);
	virtual ~CvRandom();
	void uninit();
	bool coinflip();
	unsigned short roll2DSix();
	void reseed(unsigned long ulSeed);
	unsigned long getCallCount() const;
	unsigned long getResetCount() const;
	void read(FDataStream& stream);
	void write(FDataStream& stream) const;
	bool operator==(const CvRandom& other) const;
	bool operator!=(const CvRandom& other) const;
	const std::vector<std::string>& getResolvedCallStacks() const;
	const std::vector<unsigned long>& getSeedHistory() const;
	void resolveCallStacks() const;
	bool callStackDebuggingEnabled() const;
	void setCallStackDebuggingEnabled(bool bEnabled);
	void clearCallstacks();
	void init(unsigned long ulSeed);
	void reset(unsigned long ulSeed = 0);
	unsigned short get(unsigned short usNum, const char* pszLog = NULL);
	float getFloat();
	unsigned long getSeed() const;

protected:
	void recordCallStack();
	void log(unsigned short usNum, unsigned short usResult, const char* pszLog);
	unsigned long m_ulRandomSeed;
	unsigned long m_ulCallCount;
	unsigned long m_ulResetCount;
	bool m_bSynchronous;
};

static_assert(sizeof(CvRandom) == 20, "Beyond Earth random generator layout");

FDataStream& operator<<(FDataStream& saveTo, const CvRandom& readFrom);
FDataStream& operator>>(FDataStream& loadFrom, CvRandom& writeTo);
#endif
