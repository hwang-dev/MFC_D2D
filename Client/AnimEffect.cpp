#include "stdafx.h"
#include "AnimEffect.h"
#include "Obj.h"

CAnimEffect::CAnimEffect()
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CAnimEffect::~CAnimEffect()
{
	Release();
}

HRESULT CAnimEffect::Initialize()
{
	return S_OK;
}

void CAnimEffect::LateInit()
{
}

int CAnimEffect::Update()
{
	CEffectIMP::LateInit();

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * 3.f;

	if (m_tFrame.fFrame > m_tFrame.fMax)
		return DEAD_OBJ;


	return NO_EVENT;
}

void CAnimEffect::LateUpdate()
{
}

void CAnimEffect::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_pObj->GetObjKey().c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo().matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
}

void CAnimEffect::Release()
{
}
