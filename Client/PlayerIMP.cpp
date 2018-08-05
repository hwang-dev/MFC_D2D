#include "stdafx.h"
#include "PlayerIMP.h"


CPlayerIMP::CPlayerIMP()
	: m_pObj(nullptr),
	m_bIsInit(false),
	m_wstrStateKey(L""),
	m_fAnimAcc(1.f)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CPlayerIMP::~CPlayerIMP()
{
}

void CPlayerIMP::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}
