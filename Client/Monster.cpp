#include "stdafx.h"
#include "Monster.h"

#include "MonsterIMP.h"

CMonster::CMonster()
	: m_iMonsterHp(0),
	m_pTarget(nullptr),
	m_fAttackTime(0.f),
	m_fAttackTimer(0.f),
	m_eCurDir(DIR_END),
	m_ePreDir(DIR_END),
	m_fAnimSpeed(0.f),
	m_fARange(0.f),
	m_fDeadAnimTime(0.f),
	m_fDeadAnimTimer(0.f),
	m_eCurStance(MON_END),
	m_ePreStance(MON_END),
	m_iAlpha(0),
	m_fJumpPow(0.f)
{}


CMonster::~CMonster() 
{}

void CMonster::MonsterDirChange()
{
	if (m_eCurDir != m_ePreDir) {
		switch (m_eCurDir) {
		case DOWN_LEFT:
			m_wstrStateKey = L"Down_Left";
			break;
		case DOWN_RIGHT:
			m_wstrStateKey = L"Down_Right";
			break;
		case UP_LEFT:
			m_wstrStateKey = L"Up_Left";
			break;
		case UP_RIGHT:
			m_wstrStateKey = L"Up_Right";
			break;
		default:
			break;
		}
		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str());
		m_ePreDir = m_eCurDir;
	}
}

void CMonster::SetMonsterDir()
{
	const D3DXVECTOR3 vTargetPos = m_pTarget->GetInfo().vPos;

	/* ÁÂ»ó */
	if (vTargetPos.x < m_tInfo.vPos.x && vTargetPos.y < m_tInfo.vPos.y)
		m_eCurDir = UP_LEFT;
	/* ¿ì»ó */
	else if (vTargetPos.x > m_tInfo.vPos.x && vTargetPos.y < m_tInfo.vPos.y)
		m_eCurDir = UP_RIGHT;
	/* ÁÂÇÏ */
	else if (vTargetPos.x > m_tInfo.vPos.x && vTargetPos.y > m_tInfo.vPos.y)
		m_eCurDir = DOWN_RIGHT;
	/* ¿ìÇÏ */
	else if (vTargetPos.x < m_tInfo.vPos.x && vTargetPos.y > m_tInfo.vPos.y)
		m_eCurDir = DOWN_LEFT;
	else
		return;
}

void CMonster::MonsterDead()
{
	if (m_iMonsterHp < 0) {
		m_wstrStateKey = L"NMonsterDead";
		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str());
	}
}

