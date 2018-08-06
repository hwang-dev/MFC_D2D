#include "stdafx.h"
#include "PlayerMoveIMP.h"
#include "Obj.h"

CPlayerMoveIMP::CPlayerMoveIMP()
{
}


CPlayerMoveIMP::~CPlayerMoveIMP()
{
	Release();
}

HRESULT CPlayerMoveIMP::Initialize()
{
	return S_OK;
}

void CPlayerMoveIMP::LateInit()
{
	m_fAnimAcc = 1.5f;
	
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_pObj->GetObjKey().c_str(), m_wstrStateKey.c_str());

	if (m_tFrame.fMax < 0.f)
		return;
	
}

int CPlayerMoveIMP::Update()
{
	CPlayerIMP::LateInit();

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * m_fAnimAcc;

	// 애니메이션 이펙트는 애니메이션 재생이 끝나면 소멸.
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;

	return NO_EVENT;
}

void CPlayerMoveIMP::LateUpdate()
{
}

void CPlayerMoveIMP::Render()
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

void CPlayerMoveIMP::Release()
{
}
