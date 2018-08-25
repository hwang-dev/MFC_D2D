#include "stdafx.h"
#include "BossSkillIMP.h"
#include "Obj.h"
#include "BossBullet2.h"

CBossSkillIMP::CBossSkillIMP()
{
}


CBossSkillIMP::~CBossSkillIMP()
{
}

HRESULT CBossSkillIMP::Initialize()
{
	return E_NOTIMPL;
}

void CBossSkillIMP::LateInit()
{
	
}

int CBossSkillIMP::Update()
{
	LateInit();

	// ÃÑ¾Ë ¹ß»ç
	D3DXVECTOR3 vPos = m_pObj->GetInfo().vPos;


	if (m_fPatternDelay < 5.f)
	{
		if (m_fAttackTime > 0.3f)
		{
			for (int i = 0; i < 13; ++i)
			{
				CObjMgr::GetInstance()->AddObject(CAbstractFactory<CBossBullet2>::CreateObj(vPos, float(30 * i)),
					OBJ_BOSSBULLET);
				m_fAttackTime = 0.f;
			}
		}
	}
	else
		m_fPatternDelay = 0.f;




	return NO_EVENT;
}

void CBossSkillIMP::LateUpdate()
{
	m_fAttackTime += CTimeMgr::GetInstance()->GetTime();
	m_fPatternDelay += CTimeMgr::GetInstance()->GetTime();

	LateInit();
}

void CBossSkillIMP::Render()
{
	LateInit();

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Boss",
		L"BSkill", (int)m_pObj->GetFrame().fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo().matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBossSkillIMP::Release()
{
}
