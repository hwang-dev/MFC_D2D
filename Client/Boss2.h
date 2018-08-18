#pragma once
#include "Monster.h"
class CBoss2 :
	public CMonster
{
public:
	CBoss2();
	virtual ~CBoss2();

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
};

