#include "stdafx.h"
#include "ScrollMgr.h"

float CScrollMgr::m_fScrollX = 0.f;
float CScrollMgr::m_fScrollY = 0.f;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::SetScroll(float x, float y)
{
	m_fScrollX += x;
	m_fScrollY += y;
}
