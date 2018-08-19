#pragma once
#include "Monster.h"

class CBossIMP;
class CBoss2 :
	public CMonster
{
public:
	enum PATTERN { NORMAL, HALF, SKILL, END };

	CBoss2();
	virtual ~CBoss2();

public:
	void SetBridge(CBossIMP* _pBridge) { m_pBridge = _pBridge; }

public:
	// CMonster을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void AstarMove();
	void BossAttack();
	void PatternChange();
	void PatternRandom();
	
private:
	CBossIMP*	m_pBridge = nullptr;
	PATTERN		m_eCurPattern = END;
	PATTERN		m_ePrePattern = END;
	float		m_fPatternTime = 0.f;
};

