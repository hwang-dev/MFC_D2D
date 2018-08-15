#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"

CSubject::CSubject()
{
}


CSubject::~CSubject()
{
	Release();
}

void CSubject::Release()
{
	m_ObserverLst.clear();
}

void CSubject::SubScribe(CObserver * pObserver)
{
	m_ObserverLst.push_back(pObserver);
}

void CSubject::UnSubscribe(CObserver * pObserver)
{
	for (auto& iter_begin = m_ObserverLst.begin(); iter_begin != m_ObserverLst.end(); ++iter_begin) {
		if (*iter_begin == pObserver) {
			iter_begin = m_ObserverLst.erase(iter_begin);
		}
		else
			++iter_begin;
	}
}

void CSubject::Notify(int iMessage, void * pData)
{
	for (auto& pObserver : m_ObserverLst) {
		pObserver->Update(iMessage, pData);
	}
}
