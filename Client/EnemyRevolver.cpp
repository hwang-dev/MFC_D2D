#include "stdafx.h"
#include "EnemyRevolver.h"


CEnemyRevolver::CEnemyRevolver()
{
}


CEnemyRevolver::~CEnemyRevolver()
{
}

HRESULT CEnemyRevolver::Initialize()
{
	m_wstrObjKey = L"Revolver";
	m_wstrStateKey = L"Stance";

	return S_OK;
}

int CEnemyRevolver::Update()
{
	return 0;
}

void CEnemyRevolver::LateUpdate()
{
}

void CEnemyRevolver::Render()
{
}

void CEnemyRevolver::Release()
{
}

void CEnemyRevolver::CreateBullet()
{
}

void CEnemyRevolver::WeaponReload()
{
}
