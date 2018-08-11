#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

protected:
	void MonsterDirChange();
	void SetMonsterDir();

protected:
	int			m_iMonsterHp;
	CObj*		m_pTarget;
	float		m_fAttackTime;
	float		m_fAttackTimer;
	PLAYER_DIR	m_eCurDir;
	PLAYER_DIR	m_ePreDir;
	float		m_fAnimSpeed;
};

