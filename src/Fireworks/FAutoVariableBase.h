#pragma once
#include <string>
#include <vector>
class FDataStream;
class FAutoArchive;
class FAutoVariableBase
{
public:
	FAutoVariableBase(const std::string & name, FAutoArchive & owner);

	// used for extended debugging out of sync errors. Does nothing in release builds
	FAutoVariableBase(const std::string & name, FAutoArchive & owner, bool callStackTracking);

	virtual ~FAutoVariableBase() = 0;
	virtual void load(FDataStream & loadFrom) = 0;
	virtual void loadDelta(FDataStream & loadFrom) = 0;
	virtual void save(FDataStream & saveTo) const = 0;
	virtual void saveDelta(FDataStream & saveTo) const = 0;
	virtual void clearDelta() = 0;
	virtual bool compare(FDataStream & otherValue) const = 0;
	virtual void reset() = 0;

	virtual const std::string & name() const = 0;

	// used for extended debugging out of sync errors. Does nothing in release builds
	std::string  getStackTrace() const;
	std::string  getStackTraceRemark() const;
	virtual void setStackTraceRemark() = 0;
	virtual std::string  debugDump(const std::vector<std::pair<std::string, std::string> > &) const;
	virtual std::string toString() const = 0;

};
