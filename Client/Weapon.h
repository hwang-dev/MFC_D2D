#pragma once
#include "Obj.h"
class CWeapon :
	public CObj
{
public:
	CWeapon();
	virtual ~CWeapon();

public:
	virtual void CreateBullet() PURE;	// 총알 발사
	virtual void WeaponReload() PURE;	// 재장전
	
	GUN_DATA& GetGunData() { return m_tGunData; }

protected:
	GUN_DATA	m_tGunData;
	float		m_fReloadTime;		// 재장전 시간
	float		m_fWeaponDelay;		// 연사 속도
	float		m_fWeaponDelayTime;
	bool		m_bCanShot;
};


