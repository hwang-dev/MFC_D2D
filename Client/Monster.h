#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

protected:
	int		m_iMonsterHp;
	CObj*	m_pTarget;
};

