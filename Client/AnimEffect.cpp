#include "stdafx.h"
#include "AnimEffect.h"
#include "Obj.h"

CAnimEffect::CAnimEffect()
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CAnimEffect::~CAnimEffect()
{
	Release();
}

HRESULT CAnimEffect::Initialize()
{
	return S_OK;
}

void CAnimEffect::LateInit()
{
}

int CAnimEffect::Update()
{
	CEffectIMP::LateInit();

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

	if (m_tFrame.fFrame > m_tFrame.fMax)
		return DEAD_OBJ;


	return NO_EVENT;
}

void CAnimEffect::LateUpdate()
{
}

void CAnimEffect::Render()
{
}

void CAnimEffect::Release()
{
}
