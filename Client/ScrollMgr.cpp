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
