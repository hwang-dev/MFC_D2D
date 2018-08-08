#include "stdafx.h"
#include "Revolver.h"


CRevolver::CRevolver()
{
}


CRevolver::~CRevolver()
{
}

HRESULT CRevolver::Initialize()
{
	m_wstrObjKey = L"Revolver";
	m_wstrStateKey = L"Stance";

	/* 초기 상태 */
	m_fSpeed = 10.f;
	m_fReloadTime = 1.f;
	m_fWeaponDelay = 0.1f;
	m_iMagazine = 10;
	m_iMagazine = 500;

	return S_OK;
}

void CRevolver::LateInit()
{
}

int CRevolver::Update()
{
	return NO_EVENT;
}

void CRevolver::LateUpdate()
{
}

void CRevolver::Render()
{
}

void CRevolver::Release()
{
}
