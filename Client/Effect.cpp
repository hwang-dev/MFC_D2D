#include "stdafx.h"
#include "Effect.h"
#include "EffectIMP.h"

CEffect::CEffect()
{
}


CEffect::~CEffect()
{
	Release();
}

HRESULT CEffect::Initialize()
{
	m_wstrObjKey = L"Effect";
	return S_OK;
}

void CEffect::LateInit()
{
	m_pBridge->SetObj(this);
}

int CEffect::Update()
{
	LateInit();

	return m_pBridge->Update();
}

void CEffect::LateUpdate()
{
	m_pBridge->LateUpdate();
}

void CEffect::Render()
{
	m_pBridge->Render();
}

void CEffect::Release()
{
	SafeDelete(m_pBridge);
}
