#include "stdafx.h"
#include "WeaponMgr.h"
#include "Obj.h"
#include "Weapon.h"
#include "Player.h"

IMPLEMENT_SINGLETON(CWeaponMgr)

CWeaponMgr::CWeaponMgr()
	: m_fAngle(0.f),
	m_fScaleX(0.f),
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
	m_fScaleX = 2.f;
	m_fGunPos = 28.f;
	return S_OK;
}

void CWeaponMgr::Release()
{
}

void CWeaponMgr::Update()
{
	
	/* 총구방향 = Mouse - Player */
	D3DXVECTOR3 vDir = (CMouse::GetInstance()->GetMousePos() + CScrollMgr::GetScroll())
		- m_pTarget->GetInfo().vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_fAngle = D3DXVec3Dot(&vDir, &m_pTarget->GetInfo().vLook);
	float fRadian = acosf(m_fAngle);




	D3DXMATRIX matScale, matRotZ, matTrans;

	if (CMouse::GetInstance()->GetMousePos().x + CScrollMgr::GetScroll().x > m_pTarget->GetInfo().vPos.x)
		m_fScaleX = 2.f;
	else if (CMouse::GetInstance()->GetMousePos().x + CScrollMgr::GetScroll().x < m_pTarget->GetInfo().vPos.x)
		m_fScaleX = -2.f;

	if (CMouse::GetInstance()->GetMousePos().y + CScrollMgr::GetScroll().y < m_pTarget->GetInfo().vPos.y)
		fRadian *= -1;

	D3DXMatrixScaling(&matScale, 2.f, m_fScaleX, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_pTarget->GetInfo().vPos.x - CScrollMgr::GetScroll().x,
		m_pTarget->GetInfo().vPos.y - CScrollMgr::GetScroll().y,
		m_pTarget->GetInfo().vPos.z);
	D3DXMatrixRotationZ(&matRotZ, fRadian);

	m_matWorld = matScale * matRotZ * matTrans;
}


void CWeaponMgr::Render()
{
	if (dynamic_cast<CPlayer*>(m_pTarget)->GetPlayerStance() != DODGE) {
		CObj* pPlayerGun = dynamic_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer())->GetCurGun();
		NULL_CHECK(pPlayerGun);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(pPlayerGun->GetObjKey().c_str(),
			pPlayerGun->GetSateKey().c_str(), 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX - 15.f, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
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
