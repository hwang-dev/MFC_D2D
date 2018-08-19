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

	m_tFrame.fFrame = 0.f;
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
		m_wstrStateKey.c_str());

	/* 초기 상태 */
	m_fSpeed = 10.f;
	m_fReloadTime = 1.f;
	m_fWeaponDelay = 0.7f;

	// 총알 세팅
	m_tGunData.iMaxBullet = 500;
	m_tGunData.iCurBullet = m_tGunData.iMaxBullet;
	m_tGunData.iMagazineMax = 10;
	m_tGunData.iMagazine = m_tGunData.iMagazineMax;
	m_fAnimSpeed = 4.f;

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
		m_fWeaponDelayTime = 0.f;
		m_bCanShot = true;
	}

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * m_fAnimSpeed;
	if (m_tFrame.fFrame > m_tFrame.fMax) {
		
		if (!wcscmp(L"Attack", m_wstrStateKey.c_str()))
		{
			m_wstrStateKey = L"Stance";
			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
				m_wstrStateKey.c_str());
		}
		else if (!wcscmp(L"Reload", m_wstrStateKey.c_str()))
		{
			m_wstrStateKey = L"Stance";
			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
				m_wstrStateKey.c_str());
		}
		else
			m_tFrame.fFrame = 0.f;

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
		if(m_tGunData.iMagazine > 0)
		{
			m_wstrStateKey = L"Attack";
			D3DXVECTOR3 vLength = CMouse::GetInstance()->GetMousePos() + CScrollMgr::GetScroll() - CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
			D3DXVec3Normalize(&vLength, &vLength);
			D3DXVECTOR3 vPos = CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalBullet>::CreateObj(vPos + vLength * 40.f),
				OBJ_BULLET);
			m_tGunData.iMagazine--;
			m_tGunData.iCurBullet--;

			m_tFrame.fFrame = 0;
			m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
				m_wstrStateKey.c_str());

			/* 카메라 흔들림 */
			CScrollMgr::CameraShakeNormal();
			CSoundMgr::GetInstance()->PlaySound(L"Revolver.wav", CSoundMgr::EFFECT);
			m_bCanShot = false;
		}

	}
}

void CRevolver::WeaponReload()
{
	m_wstrStateKey = L"Reload";
	m_tFrame.fFrame = 0;
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
		m_wstrStateKey.c_str());


	int iReloadCount = m_tGunData.iMagazineMax - m_tGunData.iMagazine;

	m_tGunData.iMagazine += iReloadCount;
	m_tGunData.iCurBullet -= iReloadCount;
}
