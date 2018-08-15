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
	m_tInfo.vPos = { 20.f, 20.f, 0.f };

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

	return NO_EVENT;
}

void CUI::LateUpdate()
{
}

void CUI::Render()
{
	D3DXMATRIX matTrans;

	
	if (m_iHp == 1) {

		/* Ã¹Â° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 1);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* µÑÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 30.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 2);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* ¼ÂÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 60.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 2);

		NULL_CHECK(pTexInfo);

		 fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		 fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (m_iHp == 2) {

		/* Ã¹Â° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* µÑÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 30.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 2);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* ¼ÂÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 60.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 2);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (m_iHp == 3) {

		/* Ã¹Â° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* µÑÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 30.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 1);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* ¼ÂÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 60.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 2);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (m_iHp == 4) {

		/* Ã¹Â° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* µÑÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 30.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* ¼ÂÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 60.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 2);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (m_iHp == 5) {

		/* Ã¹Â° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* µÑÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 30.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* ¼ÂÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 60.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 1);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if (m_iHp >= 6) {

		/* Ã¹Â° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* µÑÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 30.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/* ¼ÂÂ° Ä­ */
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + 60.f,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);

		m_tInfo.matWorld = matTrans;

		pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI",
			L"Hp", 0);

		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CUI::Release()
{
	SafeDelete(m_pObserver);;
}
