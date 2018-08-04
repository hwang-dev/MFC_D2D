#pragma once
#include "Obj.h"

class CPlayerIMP;
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void SetBridge(CPlayerIMP* pBridge) { m_pBridge = pBridge; }

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CPlayerIMP* m_pBridge;
};

