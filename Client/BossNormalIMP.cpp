#include "stdafx.h"
#include "BossNormalIMP.h"
#include "Obj.h"
#include "MonsterBullet.h"
#include "BossBullet.h"

CBossNormalIMP::CBossNormalIMP()
{
}


CBossNormalIMP::~CBossNormalIMP()
{
}

HRESULT CBossNormalIMP::Initialize()
{

	return S_OK;
}

void CBossNormalIMP::LateInit()
{
}

int CBossNormalIMP::Update()
{
	LateInit();


	if (m_fPatternDelay < 5.f)
	{
		if (m_fAttackTime > 0.2f)
		{
			D3DXVECTOR3 vPos = m_pObj->GetInfo().vPos;
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CBossBullet>::CreateObj(vPos),
				OBJ_MOSTERBULLET);
			m_fAttackTime = 0.f;
		}
	}
	else
		m_fPatternDelay = 0.f;

	return NO_EVENT;
}

void CBossNormalIMP::LateUpdate()
{
	m_fAttackTime += CTimeMgr::GetInstance()->GetTime();
	m_fPatternDelay += CTimeMgr::GetInstance()->GetTime();
}

void CBossNormalIMP::Render()
{
	// ÀÌ¹ÌÁö ·»´õ
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey().c_str(),
		m_pObj->GetSateKey().c_str(), 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo().matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBossNormalIMP::Release()
{
}
