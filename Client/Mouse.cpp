#include "stdafx.h"
#include "Mouse.h"
#include "Obj.h"
IMPLEMENT_SINGLETON(CMouse)

CMouse::CMouse()
	: m_vMouse{}
{
}


CMouse::~CMouse()
{
}


void CMouse::Update()
{
	POINT pt = {};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	m_vMouse = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
}

void CMouse::LateUpdate()
{
	D3DXVECTOR3 vCamera = m_vMouse + CScrollMgr::GetScroll() -
		CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;

	CScrollMgr::AddScroll(vCamera * 0.2f);

}

void CMouse::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_vMouse.x, m_vMouse.y, m_vMouse.z);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		L"Mouse", L"Cursor", 0);
	
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(200, 255, 255, 255));

	/* ¸¶¿ì½º ÁÂÇ¥ */
	TCHAR szPos[MIN_STR] = L"";
	swprintf_s(szPos, L"%d, %d", (int)m_vMouse.x,
		(int)m_vMouse.x);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szPos, lstrlen(szPos), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (g_bOnRect) {
		D3DXVECTOR2 vPoint[5] = {
			{ (WINCX * 0.5f - 200.f), (WINCY * 0.5f - 200.f) },
			{ (WINCX * 0.5f + 200.f), (WINCY * 0.5f - 200.f) },
			{ (WINCX * 0.5f + 200.f), (WINCY * 0.5f + 200.f) },
			{ (WINCX * 0.5f - 200.f), (WINCY * 0.5f + 200.f) },
			{ (WINCX * 0.5f - 200.f), (WINCY * 0.5f - 200.f) },
		};

		CDevice::GetInstance()->GetLine()->SetWidth(2.f);

		CDevice::GetInstance()->GetSprite()->End();

		CDevice::GetInstance()->GetLine()->Begin();
		CDevice::GetInstance()->GetLine()->Draw(vPoint, 5, D3DCOLOR_ARGB(255, 0, 0, 255));
		CDevice::GetInstance()->GetLine()->End();

		CDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	}

}

D3DXVECTOR3& CMouse::GetMousePos()
{
	return m_vMouse;
}
