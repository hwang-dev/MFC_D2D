#include "stdafx.h"
#include "ShotGun.h"


CShotGun::CShotGun()
{
}


CShotGun::~CShotGun()
{
	Release();
}

HRESULT CShotGun::Initialize()
{
	m_wstrObjKey = L"Shotgun";
	m_wstrStateKey = L"Stance";

	/* 초기 상태 */
	m_fSpeed = 10.f;
	m_fReloadTime = 2.f;
	m_fWeaponDelay = 0.5f;
	m_iMagazine = 5;
	m_iMagazine = 500;

	return S_OK;
}

void CShotGun::LateInit()
{
}

int CShotGun::Update()
{

	return NO_EVENT;
}

void CShotGun::LateUpdate()
{
}

void CShotGun::Render()
{
}

void CShotGun::Release()
{
}

void CShotGun::CreateBullet()
{
}

void CShotGun::WeaponReload()
{
}
