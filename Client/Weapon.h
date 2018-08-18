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

protected:
	int			m_iMaxBullet;		// 최대 총알
	int			m_iMagazine;		// 탄창의 총알 갯수

	float		m_fReloadTime;		// 재장전 시간
	float		m_fWeaponDelay;		// 연사 속도
	float		m_fWeaponDelayTime;
	bool		m_bCanShot;
};


