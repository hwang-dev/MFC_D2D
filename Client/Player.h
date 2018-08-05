#pragma once
#include "Obj.h"

/* Player 추상층 */
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
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void PlayerMove();
	
private:
	CPlayerIMP* m_pBridge;
};

