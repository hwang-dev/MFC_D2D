#include "stdafx.h"
#include "BossHalfIMP.h"
#include "Obj.h"

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
