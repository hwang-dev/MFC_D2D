#pragma once
#include "Obj.h"

class CEffectIMP;
class CEffect :
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	void SetBridge(CEffectIMP* pBridge) { m_pBridge = pBridge; }

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CEffectIMP* m_pBridge = nullptr;
};

