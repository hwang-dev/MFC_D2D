#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_bIsInit(false),
	m_fSpeed(0.f),
	m_wstrObjKey(L""),
	m_wstrStateKey(L"")
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
}


CObj::~CObj()
{
}

void CObj::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}

void CObj::MoveFrame()
{
	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}

void CObj::UpdateRect()
{
	m_tRect.left	= LONG(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f);
	m_tRect.top		= LONG(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f);
	m_tRect.right	= LONG(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f);
	m_tRect.bottom	= LONG(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f);
}
