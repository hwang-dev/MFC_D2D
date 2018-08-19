#include "stdafx.h"
#include "Weapon.h"


CWeapon::CWeapon()
	: m_fReloadTime(0.f),
	m_fWeaponDelay(0.f),
	m_fWeaponDelayTime(0.f),
	m_bCanShot(false) 
{
	ZeroMemory(&m_tGunData, sizeof(GUN_DATA));
}


CWeapon::~CWeapon() 
{
}

