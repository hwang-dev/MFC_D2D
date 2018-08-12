#include "stdafx.h"
#include "ScrollMgr.h"
#include "Obj.h"

D3DXVECTOR3 CScrollMgr::m_vScroll = {};
D3DXVECTOR3 CScrollMgr::m_vCamera = {};

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::SetScroll(float x, float y)
{
	m_vScroll.x = x;
	m_vScroll.y = y;
}

void CScrollMgr::ScrollLock()
{
	if (m_vScroll.x > 0.f)
		m_vScroll.x = 0.f;
	if (m_vScroll.y > 0.f)
		m_vScroll.y = 0.f;

	if (m_vScroll.x < WINCX - TILECX * TILEX)
		m_vScroll.x = float(WINCX - TILECX * TILEX);
	if (m_vScroll.y < WINCY - TILECY * TILEY)
		m_vScroll.y = float(WINCY - TILECY * TILEY);
}

void CScrollMgr::ScrollLock2()
{
	CObj* pPlayer = CObjMgr::GetInstance()->GetPlayer();

	m_vScroll.x = pPlayer->GetInfo().vPos.x - WINCX * 0.5f;
	m_vScroll.y = pPlayer->GetInfo().vPos.y - WINCY * 0.5f;
}

void CScrollMgr::SetCamera(float x, float y)
{
	m_vCamera.x = x;
	m_vCamera.y = y;
}

void CScrollMgr::AddScroll(D3DXVECTOR3 & vPos)
{
	m_vScroll += vPos;
}

void CScrollMgr::CameraShakeNormal()
{
	VECTOR3 vTemp = m_vScroll;

	int iRandomX = rand() % 200;
	int iRandomY = rand() % 200;

	m_vScroll += VECTOR3((float)iRandomX, (float)iRandomY, 0.f);

	m_vScroll = vTemp;
}
