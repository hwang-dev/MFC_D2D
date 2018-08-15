#pragma once
#include "MonsterIMP.h"
class MonsterShotIMP :
	public MonsterIMP
{
public:
	MonsterShotIMP();
	virtual ~MonsterShotIMP();

	// MonsterIMP을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

