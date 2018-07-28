#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_bIsInit(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
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
