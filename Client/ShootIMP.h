#pragma once
#include "WeaponIMP.h"
class CShootIMP :
	public CWeaponIMP
{
public:
	CShootIMP();
	virtual ~CShootIMP();

	// CWeaponIMP을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

