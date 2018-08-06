#include "stdafx.h"
#include "ScrollMgr.h"

D3DXVECTOR3 CScrollMgr::m_vScroll = {};

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::SetScroll(float x, float y)
{
	m_vScroll.x += x;
	m_vScroll.y += y;
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
