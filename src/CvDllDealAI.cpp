#include "CvGameCoreDLLPCH.h"
#include "CvDllDealAI.h"
#include "CvDllContext.h"
#include "CvDllDeal.h"
#include "CvDllPlayer.h"
#include "CvDealAI.h"

// The native player wrapper retains allocation cleanup and terminating delete handlers.
#ifndef __EXCEPTIONS
#error CvDllDealAI.cpp requires exception handling to match the Beyond Earth binary.
#endif

CvDllDealAI::CvDllDealAI(CvDealAI* pDealAI)
	: m_pDealAI(pDealAI)
	, m_uiRefCount(1)
{
}

CvDllDealAI::~CvDllDealAI()
{
}

void* CvDllDealAI::QueryInterface(GUID guidInterface)
{
	if(guidInterface == ICvUnknown::GetInterfaceId() || guidInterface == ICvDealAI1::GetInterfaceId())
	{
		IncrementReference();
		return this;
	}

	return NULL;
}

unsigned int CvDllDealAI::IncrementReference()
{
	++m_uiRefCount;
	return m_uiRefCount;
}

unsigned int CvDllDealAI::DecrementReference()
{
	if(m_uiRefCount == 1)
	{
		delete this;
		return 0;
	}

	--m_uiRefCount;
	return m_uiRefCount;
}

unsigned int CvDllDealAI::GetReferenceCount()
{
	return m_uiRefCount;
}

void CvDllDealAI::Destroy()
{
	DecrementReference();
}

void CvDllDealAI::operator delete(void* p)
{
	CvDllGameContext::Free(p);
}

void* CvDllDealAI::operator new(size_t bytes)
{
	return CvDllGameContext::Allocate(bytes);
}

CvDealAI* CvDllDealAI::GetInstance()
{
	return m_pDealAI;
}

ICvPlayer1* CvDllDealAI::GetPlayer()
{
	CvPlayerAI* pPlayer = static_cast<CvPlayerAI*>(m_pDealAI->GetPlayer());
	return pPlayer != NULL ? new CvDllPlayer(pPlayer) : NULL;
}

int CvDllDealAI::DoHumanOfferDealToThisAI(ICvDeal1* pDeal)
{
	CvDeal* pNativeDeal = pDeal != NULL ? static_cast<CvDllDeal*>(pDeal)->GetInstance() : NULL;
	return m_pDealAI->DoHumanOfferDealToThisAI(pNativeDeal);
}

void CvDllDealAI::DoAcceptedDeal(PlayerTypes eFromPlayer, ICvDeal1* pDeal, int iDealValueToMe, int iValueImOffering, int iValueTheyreOffering)
{
	CvDeal* pNativeDeal = pDeal != NULL ? static_cast<CvDllDeal*>(pDeal)->GetInstance() : NULL;
	if(pNativeDeal != NULL)
		m_pDealAI->DoAcceptedDeal(eFromPlayer, *pNativeDeal, iDealValueToMe, iValueImOffering, iValueTheyreOffering);
}

int CvDllDealAI::DoHumanDemand(ICvDeal1* pDeal)
{
	CvDeal* pNativeDeal = pDeal != NULL ? static_cast<CvDllDeal*>(pDeal)->GetInstance() : NULL;
	return m_pDealAI->DoHumanDemand(pNativeDeal);
}

void CvDllDealAI::DoAcceptedDemand(PlayerTypes eFromPlayer, ICvDeal1* pDeal)
{
	CvDeal* pNativeDeal = pDeal != NULL ? static_cast<CvDllDeal*>(pDeal)->GetInstance() : NULL;
	if(pNativeDeal != NULL)
		m_pDealAI->DoAcceptedDemand(eFromPlayer, *pNativeDeal);
}

bool CvDllDealAI::DoEqualizeDealWithHuman(ICvDeal1* pDeal, PlayerTypes eOtherPlayer, bool bDontChangeMyExistingItems, bool bDontChangeTheirExistingItems, bool& bDealGoodToBeginWith, bool& bCantMatchOffer)
{
	CvDeal* pNativeDeal = pDeal != NULL ? static_cast<CvDllDeal*>(pDeal)->GetInstance() : NULL;
	return m_pDealAI->DoEqualizeDealWithHuman(pNativeDeal, eOtherPlayer, bDontChangeMyExistingItems, bDontChangeTheirExistingItems, bDealGoodToBeginWith, bCantMatchOffer);
}
