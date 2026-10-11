#pragma once
#include <cstddef>

template<class T> class CLinkList;
template<class T> class CLLNode
{
 friend class CLinkList<T>;
public:
 CLLNode(const T& value) : m_data(value), m_pNext(NULL), m_pPrev(NULL) {}
 virtual ~CLLNode() {}
 T m_data;
protected:
 CLLNode<T>* m_pNext;
 CLLNode<T>* m_pPrev;
};

template<class tVARTYPE> class CLinkList
{
public:
 CLinkList();
 virtual ~CLinkList();
 void clear();
 void insertAtBeginning(const tVARTYPE& val);
 void insertAtEnd(const tVARTYPE& val);
 void insertBefore(const tVARTYPE& val, CLLNode<tVARTYPE>* pThisNode);
 void insertAfter(const tVARTYPE& val, CLLNode<tVARTYPE>* pThisNode);
 CLLNode<tVARTYPE>* deleteNode(CLLNode<tVARTYPE>* pNode);
 void moveToEnd(CLLNode<tVARTYPE>* pThisNode);
 const CLLNode<tVARTYPE>* next(const CLLNode<tVARTYPE>* pNode) const;
 CLLNode<tVARTYPE>* next(CLLNode<tVARTYPE>* pNode);
 const CLLNode<tVARTYPE>* prev(const CLLNode<tVARTYPE>* pNode) const;
 CLLNode<tVARTYPE>* prev(CLLNode<tVARTYPE>* pNode);
 CLLNode<tVARTYPE>* nodeNum(int iNum) const;
 void swapUp(int iNum);
 void Read(FDataStream& kStream);
 void Write(FDataStream& kStream) const;
 int getLength() const { return m_iLength; }
 const CLLNode<tVARTYPE>* head() const { return m_pHead; }
 CLLNode<tVARTYPE>* head() { return m_pHead; }
 const CLLNode<tVARTYPE>* tail() const { return m_pTail; }
 CLLNode<tVARTYPE>* tail() { return m_pTail; }
 bool operator==(const CLinkList& rhs) const;
 bool operator!=(const CLinkList& rhs) const;
protected:
 int m_iLength;
 CLLNode<tVARTYPE>* m_pHead;
 CLLNode<tVARTYPE>* m_pTail;
};
