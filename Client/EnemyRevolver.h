#pragma once
#include "Weapon.h"
class CEnemyRevolver :
	public CWeapon
{
public:
	CEnemyRevolver();
	virtual ~CEnemyRevolver();

	// CWeapon을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void CreateBullet() override;
	virtual void WeaponReload() override;
};

