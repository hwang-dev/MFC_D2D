#include "stdafx.h"
#include "Revolver.h"
#include "NormalBullet.h"

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
	m_fWeaponDelay = 0.7f;
	m_iMagazine = 10;
	m_iMagazine = 500;

	return S_OK;
}

void CRevolver::LateInit()
{
}

int CRevolver::Update()
{
	LateInit();

	return NO_EVENT;
}

void CRevolver::LateUpdate()
{
	/* 일정 시간이 지나면 총알 발사 가능*/
	m_fWeaponDelayTime += CTimeMgr::GetInstance()->GetTime();

	if (m_fWeaponDelayTime > m_fWeaponDelay) {
		m_bCanShot = true;
		m_fWeaponDelayTime = 0.f;
	}
}

void CRevolver::Render()
{
}

void CRevolver::Release()
{
}

void CRevolver::CreateBullet()
{
	if(m_bCanShot) {
		D3DXVECTOR3 vLength = CMouse::GetInstance()->GetMousePos() + CScrollMgr::GetScroll() - CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
		D3DXVec3Normalize(&vLength, &vLength);
		D3DXVECTOR3 vPos = CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalBullet>::CreateObj(vPos + vLength * 40.f),
			OBJ_BULLET);
		/* 카메라 흔들림 */
		CScrollMgr::CameraShakeNormal();
		m_bCanShot = false;

	}
}

void CRevolver::WeaponReload()
{
}
