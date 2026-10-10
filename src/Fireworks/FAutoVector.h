#pragma once

#include "FAutoVariable.h"
#include <vector>

template<typename ElementType>
struct AutoVectorCommand
{
	enum CommandTypes { ERASE, INSERT, SET, PUSH_BACK, CLEAR, RESIZE, RESIZE_WITH_VALUE, NO_COMMAND };
	unsigned char command;
	unsigned int index;
	ElementType value;
};

template<typename ElementType, typename ClassContainer>
class FAutoVariable<std::vector<ElementType>, ClassContainer> : public FAutoVariableBase
{
public:
	virtual ~FAutoVariable();
	virtual void load(FDataStream&);
	virtual void loadDelta(FDataStream&);
	virtual void save(FDataStream&) const;
	virtual void saveDelta(FDataStream&) const;
	virtual void clearDelta();
	virtual bool compare(FDataStream&) const;
	virtual void reset();
	virtual const std::string& name() const;
	virtual void setStackTraceRemark();
	virtual std::string toString() const;
private:
	typedef std::vector<AutoVectorCommand<ElementType> > COMMAND_VEC_TYPE;
	mutable COMMAND_VEC_TYPE m_commands;
	std::vector<ElementType> m_value;
	FAutoArchiveClassContainer<ClassContainer>& m_owner;
	bool m_retainSize;
};
