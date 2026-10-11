#pragma once

class FDataStream;

#include "CvGameCoreDLLUtil/include/LinkedList.h"

class CvPlayer;
class CvUnit;

class CvUnitCycler
{
public:
	typedef CLLNode<int> Node;
	typedef CLinkList<int> NodeList;

	CvUnitCycler(CvPlayer*);
	void Clear();
	void Rebuild(CvUnit* = NULL);
	CvUnit* Cycle(CvUnit*, bool, bool, bool*);
	void RemoveUnit(int);
	void AddUnit(int);
	Node* DeleteNode(Node*);
	Node* NextNode(Node*);
	const Node* NextNode(const Node*) const;
	const Node* PreviousNode(const Node*) const;
	const Node* HeadNode() const;
	Node* HeadNode();
	const Node* TailNode() const;

protected:
	NodeList m_kNodeList;
	CvPlayer* m_pkPlayer;

	friend FDataStream& operator>>(FDataStream&, CvUnitCycler&);
	friend FDataStream& operator<<(FDataStream&, const CvUnitCycler&);
};

FDataStream& operator>>(FDataStream&, CvUnitCycler&);
FDataStream& operator<<(FDataStream&, const CvUnitCycler&);
