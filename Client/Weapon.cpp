#include "stdafx.h"
#include "Weapon.h"


CWeapon::CWeapon()
	: m_iMagazine(0),
	m_iMaxBullet(0),
	m_fReloadTime(0.f),
	m_fWeaponDelay(0.f),
	m_fWeaponDelayTime(0.f),
	m_bCanShot(false)
{
}


CWeapon::~CWeapon()
{
}

