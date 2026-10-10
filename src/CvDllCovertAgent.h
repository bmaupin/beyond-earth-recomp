#pragma once
#include "CvDllInterfaces.h"
#include <tuple>

class CvDllCovertAgent : public ICvCovertAgent1 {
    unsigned int m_refCount;
    CvCovertAgent *m_agent;

  public:
    CvDllCovertAgent(CvCovertAgent* agent)
        : m_refCount(1), m_agent(agent)
    {
    }
    ~CvDllCovertAgent();
    virtual void * QueryInterface(GUID);
    static void operator delete(void *);
    static void * operator new(size_t);
    virtual PlayerTypes GetOwner() const;
    virtual int GetRank() const;
    virtual std::string GetName() const;
    virtual int GetIndex() const;
    virtual int GetNumOperationsCompleted() const;
    virtual int GetRankProgressRate() const;
    virtual int GetNumTurnsInCity() const;
    virtual bool GetHasEstablishedNetwork() const;
    virtual std::unique_ptr<ICvCity1> GetCity() const;
    virtual bool IsIdle() const;
    virtual bool IsTraveling() const;
    virtual bool CanTravel() const;
    virtual bool IsDead() const;
    virtual int GetGoal() const;
    virtual int GetProgress() const;
    virtual bool IsAtHeadquarters() const;
    virtual bool IsDoingCounterIntelligence() const;
    virtual bool CanDoAnyOperation() const;
    virtual std::tuple<bool, std::string> CanDoOperation(CovertOperationTypes) const;
  private:
    unsigned int IncrementReference();
    unsigned int DecrementReference();
    unsigned int GetReferenceCount() const;
    virtual void Destroy();
}
;
