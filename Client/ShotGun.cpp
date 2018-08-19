#include "stdafx.h"
#include "ShotGun.h"
#include "ShotGunBullet.h"

CShotGun::CShotGun()
	: m_iShotGunCount(0) 
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
	m_fSpeed = 100.f;
	m_fReloadTime = 2.f;
	m_fWeaponDelay = 2.f;
	m_iShotGunCount = 4;

	// 총알 세팅
	m_tGunData.iMaxBullet = 100;
	m_tGunData.iCurBullet = m_tGunData.iMaxBullet;
	m_tGunData.iMagazineMax = 5;
	m_tGunData.iMagazine = m_tGunData.iMagazineMax;

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
	/* 일정 시간이 지나면 총알 발사 가능*/
	m_fWeaponDelayTime += CTimeMgr::GetInstance()->GetTime();
	
	if (m_fWeaponDelayTime > m_fWeaponDelay) {
		m_fWeaponDelayTime = 0.f;
		m_bCanShot = true;
	}
}

void CShotGun::Render()
{
}

void CShotGun::Release()
{
}

void CShotGun::CreateBullet()
{
	if (m_bCanShot) {
		if (m_tGunData.iMagazine > 0) {
			D3DXVECTOR3 vLength = CMouse::GetInstance()->GetMousePos() + CScrollMgr::GetScroll() - CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
			D3DXVec3Normalize(&vLength, &vLength);
			D3DXVECTOR3 vPos = CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
			m_tGunData.iMagazine--;
			m_tGunData.iCurBullet--;
			for (int i = 0; i < m_iShotGunCount; ++i) {
				CObjMgr::GetInstance()->AddObject(CAbstractFactory<CShotGunBullet>::CreateObj(vPos + vLength * 50),
					OBJ_BULLET);
				CScrollMgr::CameraShakeNormal();
			}

			CSoundMgr::GetInstance()->PlaySound(L"Shotgun.wav", CSoundMgr::EFFECT);
			m_bCanShot = false;
		}
	}
}

void CShotGun::WeaponReload()
{
	int iReloadCount = m_tGunData.iMagazineMax - m_tGunData.iMagazine;

	m_tGunData.iMagazine += iReloadCount;
	m_tGunData.iCurBullet -= iReloadCount;
}
