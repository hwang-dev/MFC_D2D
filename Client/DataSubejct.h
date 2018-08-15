#pragma once
#include "Subject.h"
class CDataSubejct :
	public CSubject
{
	DECLARE_SINGLETON(CDataSubejct)

public:
	CDataSubejct();
	virtual ~CDataSubejct();

public:
	list<void*>* GetDataLst(int iMessage);
	virtual void Release();

public:
	void AddData(int iMessage, void* pData);
	void RemoveData(int iMessage, void* pData);

private:
	map<int, list<void*>> m_MapData;

};

