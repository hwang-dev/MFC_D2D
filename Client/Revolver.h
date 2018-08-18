#pragma once
#include "Weapon.h"

class CRevolver :
	public CWeapon
{
public:
	CRevolver();
	virtual ~CRevolver();

	// CWeapon을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	
	virtual void CreateBullet() override;
	virtual void WeaponReload() override;


};