#include "stdafx.h"
#include "WeaponMgr.h"
#include "Obj.h"
#include "Weapon.h"
#include "Player.h"

IMPLEMENT_SINGLETON(CWeaponMgr)

CWeaponMgr::CWeaponMgr()
	: m_fAngle(0.f),
	m_fScaleY(0.f),
	m_fGunPos(0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


CWeaponMgr::~CWeaponMgr()
{
	Release();
}

HRESULT CWeaponMgr::Initialize()
{
	// m_pTarget : 플레이어
	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	return S_OK;
}

void CWeaponMgr::Release()
{
}

void CWeaponMgr::Update()
{
	float fpos = 12.f;
	m_fGunPos = 5.f;


	/* 총구 방향: 마우스 - 플레이어 */
	D3DXVECTOR3 vDir = (CMouse::GetInstance()->GetMousePos() + CScrollMgr::GetScroll()) - m_pTarget->GetInfo().vPos;
	D3DXVec3Normalize(&vDir, &vDir); // 방향벡터 정규화
	m_fAngle = D3DXVec3Dot(&vDir, &m_pTarget->GetInfo().vLook);
	float fRadian = acosf(m_fAngle);

	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 2.f, m_fScaleY, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_pTarget->GetInfo().vPos.x,
		m_pTarget->GetInfo().vPos.y,
		m_pTarget->GetInfo().vPos.z);
	D3DXMatrixRotationZ(&matRotZ, -fRadian);

	m_matWorld = matScale * matRotZ * matTrans;
}


void CWeaponMgr::Render()
{
	CObj* pPlayerGun = dynamic_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer())->GetCurGun();
	NULL_CHECK(pPlayerGun);

	if (dynamic_cast<CPlayer*>(m_pTarget)->GetPlayerStance() != DODGE) {
		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(pPlayerGun->GetObjKey().c_str(),
			pPlayerGun->GetSateKey().c_str(), 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CWeaponMgr::LateUpdate()
{
	/* 선택된 총만 LateUpdate */
	CObj* pPlayerGun = dynamic_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer())->GetCurGun();
	pPlayerGun->LateUpdate();
}

void CWeaponMgr::AddWeapon(CObj * pObj)
{
	m_vecWeapon.push_back(pObj);
}
