#pragma once
#include "EffectIMP.h"
class CAnimEffect :
	public CEffectIMP
{
public:
	CAnimEffect();
	virtual ~CAnimEffect();

public:
	void SetFrame(const FRAME& tFrame) { m_tFrame = tFrame; }

public:
	// CEffectIMP을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	FRAME	m_tFrame;
};

