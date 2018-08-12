#include "stdafx.h"
#include "ScrollMgr.h"
#include "Obj.h"

D3DXVECTOR3 CScrollMgr::m_vScroll = {};

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
