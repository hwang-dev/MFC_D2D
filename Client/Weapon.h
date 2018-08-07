#pragma once
#include "Obj.h"
class CWeapon :
	public CObj
{
public:
	CWeapon();
	virtual ~CWeapon();

	wstring& GetStateKey() { return m_wstrObjKey; }

protected:
	int			m_iMaxBullet;
	int			m_iMagazine;
	float		m_fReloadTime;
	float		m_fWeaponDelay;
	bool		m_bIsGet;
	wstring		m_wstrStateKey;
};


