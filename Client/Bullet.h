#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

protected:
	int		m_iBulletDamage;
	float	m_fVanishTime;
	float	m_fVanishTimer;
};

