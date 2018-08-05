#pragma once
#include "Obj.h"
class CWeapon :
	public CObj
{
public:
	CWeapon();
	virtual ~CWeapon();

protected:
	int		m_iMaxBullet;
	int		m_iMagazine;
	float	m_fReloadTime;
	float	m_fWeaponDelay;
	bool	m_bIsGet;
};

