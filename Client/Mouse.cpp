#include "stdafx.h"
#include "Mouse.h"

IMPLEMENT_SINGLETON(CMouse)

CMouse::CMouse()
	: m_vMouse {}
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

void CMouse::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_vMouse.x, m_vMouse.y, m_vMouse.z);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		L"MOUSE", L"CURSOR", 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

D3DXVECTOR3& CMouse::GetMousePos()
{
	return m_vMouse;
}
