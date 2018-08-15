#include "stdafx.h"
#include "UI.h"
#include "UIObserver.h"

CUI::CUI()
{
}


CUI::~CUI()
{
	Release();
}

HRESULT CUI::Initialize()
{
	m_tInfo.vPos = { 10.f, 10.f, 0.f };

	m_pObserver = new CUIObserver;
	CDataSubejct::GetInstance()->SubScribe(m_pObserver);
	return S_OK;
}

void CUI::LateInit()
{
}

int CUI::Update()
{
	CObj::LateInit();

	m_iHp = dynamic_cast<CUIObserver*>(m_pObserver)->GetData().iHp;

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x, 
		m_tInfo.vPos.y, 
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	return NO_EVENT;
}

void CUI::LateUpdate()
{
}

void CUI::Render()
{
	TCHAR szBuf[MIN_STR] = L"";
	swprintf_s(szBuf, L"HP: %d", m_iHp);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 0, 0));

}

void CUI::Release()
{
	SafeDelete(m_pObserver);;
}
