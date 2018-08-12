#pragma once
#include "Monster.h"
class CNormalMonster :
	public CMonster
{
public:
	CNormalMonster();
	virtual ~CNormalMonster();

	// CMonster을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void AStarMove();
};

