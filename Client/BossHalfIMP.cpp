#include "stdafx.h"
#include "BossHalfIMP.h"
#include "Obj.h"
#include "BossBullet2.h"

CBossHalfIMP::CBossHalfIMP()
{
}


CBossHalfIMP::~CBossHalfIMP()
{
}

HRESULT CBossHalfIMP::Initialize()
{
	return S_OK;
}

void CBossHalfIMP::LateInit()
{
}

int CBossHalfIMP::Update()
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
					OBJ_MOSTERBULLET);
				m_fAttackTime = 0.f;
			}
		}
	}
	else
		m_fPatternDelay = 0.f;


	return NO_EVENT;
}

void CBossHalfIMP::LateUpdate()
{
	m_fAttackTime += CTimeMgr::GetInstance()->GetTime();
	m_fPatternDelay += CTimeMgr::GetInstance()->GetTime();

	LateInit();
}

void CBossHalfIMP::Render()
{
	LateInit();

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey().c_str(),
		m_pObj->GetSateKey().c_str(), 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo().matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBossHalfIMP::Release()
{
}
