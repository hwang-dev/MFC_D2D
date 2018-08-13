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
	void MonsterDead();

protected:
	int			m_iMonsterHp;
	CObj*		m_pTarget;
	float		m_fAttackTime;
	float		m_fAttackTimer;

	PLAYER_DIR	m_eCurDir;
	PLAYER_DIR	m_ePreDir;
	float		m_fAnimSpeed;
	float		m_fARange;

	float		m_fDeadAnimTime;
	float		m_fDeadAnimTimer;

	MONSTER_STANCE	m_eCurStance;
	MONSTER_STANCE	m_ePreStance;

	int			m_iAlpha;
};

