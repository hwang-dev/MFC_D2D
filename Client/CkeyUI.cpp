#include "stdafx.h"
#include "CkeyUI.h"
#include "UIObserver.h"

CkeyUI::CkeyUI()
{
}


CkeyUI::~CkeyUI()
{
	Release();
}

HRESULT CkeyUI::Initialize()
{
	m_tInfo.vPos = { 20.f, 80.f, 0.f };

	m_pObserver = new CUIObserver;
	CDataSubejct::GetInstance()->SubScribe(m_pObserver);
	return S_OK;
}

void CkeyUI::LateInit()
{
}

int CkeyUI::Update()
{
	CObj::LateInit();

	m_iKey = dynamic_cast<CUIObserver*>(m_pObserver)->GetData().iKey;
	return NO_EVENT;
}

void CkeyUI::LateUpdate()
{
}

void CkeyUI::Render()
{
	D3DXMATRIX matTrans, matScale;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
		L"Key", 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	/* 열쇠 개수 출력 */
	D3DXMatrixScaling(&matScale, 1.4f, 1.4f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + 20.f,
		m_tInfo.vPos.y - 10.f,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;
	TCHAR szKey[MIN_STR] = L"";
	swprintf_s(szKey,L"%d", m_iKey);
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetFont2()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szKey, lstrlen(szKey), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CkeyUI::Release()
{
	SafeDelete(m_pObserver);
}
