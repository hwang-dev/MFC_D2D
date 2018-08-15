#include "stdafx.h"
#include "DataSubejct.h"

IMPLEMENT_SINGLETON(CDataSubejct)

CDataSubejct::CDataSubejct()
{
}


CDataSubejct::~CDataSubejct()
{
	Release();
}

list<void*>* CDataSubejct::GetDataLst(int iMessage)
{
	auto& iter_find = m_MapData.find(iMessage);

	if (iter_find == m_MapData.end())
		return nullptr;

	return &iter_find->second;
}

void CDataSubejct::Release()
{
	for (auto& MyPair : m_MapData) {
		MyPair.second.clear();
	}
	m_MapData.clear();
}

void CDataSubejct::AddData(int iMessage, void * pData)
{
	if(pData != nullptr) {
		m_MapData[iMessage].push_back(pData);
		CSubject::Notify(iMessage, pData);
	}
}

void CDataSubejct::RemoveData(int iMessage, void * pData)
{
	auto& Map_iter = m_MapData.find(iMessage);

	if (Map_iter != m_MapData.end()) {
		auto iter_begin = Map_iter->second.begin();
		auto iter_end = Map_iter->second.end();

		for (; iter_begin != iter_end; ++iter_begin) {
			if (*iter_begin == pData) {
				iter_begin = Map_iter->second.erase(iter_begin);
			}
			else {
				++iter_begin;
			}
		}
	}
}

