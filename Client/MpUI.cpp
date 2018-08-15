#include "stdafx.h"
#include "MpUI.h"
#include "UIObserver.h"

CMpUI::CMpUI()
{
}


CMpUI::~CMpUI()
{
}

HRESULT CMpUI::Initialize()
{
	m_tInfo.vPos = { 20.f, 50.f, 0.f };

	m_pObserver = new CUIObserver;
	CDataSubejct::GetInstance()->SubScribe(m_pObserver);
	
	return S_OK;
}

void CMpUI::LateInit()
{
}

int CMpUI::Update()
{
	CObj::LateInit();

	m_iMp = dynamic_cast<CUIObserver*>(m_pObserver)->GetData().iMp;

	return NO_EVENT;
}

void CMpUI::LateUpdate()
{
}

void CMpUI::Render()
{
	for (int i = 0; i < m_iMp; ++i) {
		D3DXMATRIX matTrans;
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + (i * 30),
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI", L"Mp", 0);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMpUI::Release()
{
	SafeDelete(m_pObserver);
}
