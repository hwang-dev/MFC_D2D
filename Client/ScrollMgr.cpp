#include "stdafx.h"
#include "ScrollMgr.h"
#include "Obj.h"

D3DXVECTOR3 CScrollMgr::m_vScroll = {};
D3DXVECTOR3 CScrollMgr::m_vCamera = {};
float CScrollMgr::m_fShakeTime = 0.f;
int CScrollMgr::m_iRandom = 0;
bool CScrollMgr::m_bIsShaking = false;
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

	if (m_bIsShaking)
	{
		m_iRandom = (rand() % 12) - 6;
	}
	m_vScroll.x = pPlayer->GetInfo().vPos.x - WINCX * 0.5f + m_iRandom;
	m_vScroll.y = pPlayer->GetInfo().vPos.y - WINCY * 0.5f + m_iRandom;

	if (m_bIsShaking)
	{
		m_fShakeTime += 18.f * CTimeMgr::GetInstance()->GetTime();
		if (m_fShakeTime > 1.f) {
			m_fShakeTime = 0.f;
			m_iRandom = 0;
			m_bIsShaking = false;
		}
	}
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
	srand((unsigned int)time(NULL));
	m_bIsShaking = true;
}
