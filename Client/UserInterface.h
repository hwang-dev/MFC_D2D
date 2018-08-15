#pragma once
#include "Obj.h"

class CObserver;
class CUserInterface
	: public CObj
{
public:
	CUserInterface();
	virtual ~CUserInterface();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override PURE;
	virtual void LateInit() override PURE;
	virtual int Update() override PURE;
	virtual void LateUpdate() override PURE;
	virtual void Render() override PURE;
	virtual void Release() override PURE;

protected:
	CObserver*	m_pObserver = nullptr;
};

