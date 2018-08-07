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
