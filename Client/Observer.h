#pragma once
class CObserver
{
public:
	CObserver();
	virtual ~CObserver();

public:
	virtual void Update(int iMessage, void* pData) PURE;
};

