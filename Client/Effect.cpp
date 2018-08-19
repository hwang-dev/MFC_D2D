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
	CObj::LateInit();

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;


	return m_pBridge->Update();
}

void CEffect::LateUpdate()
{
	CObj::LateInit();

	m_pBridge->LateUpdate();
}

void CEffect::Render()
{
	CObj::LateInit();

	m_pBridge->Render();
}

void CEffect::Release()
{
	CObj::LateInit();

	SafeDelete(m_pBridge);
}
