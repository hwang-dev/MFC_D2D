#include "stdafx.h"
#include "WeaponMgr.h"
#include "Obj.h"
#include "Weapon.h"
#include "Player.h"

IMPLEMENT_SINGLETON(CWeaponMgr)

CWeaponMgr::CWeaponMgr()
{
}


CWeaponMgr::~CWeaponMgr()
{
}

HRESULT CWeaponMgr::Initialize()
{
	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	return S_OK;
}


void CWeaponMgr::Render()
{
	float fpos = 12.f;
	float fScaleY = 2.f;
	float fGunPos = 5.f;
	float fRadian = 0.f;

	D3DXVECTOR3 vDir = CMouse::GetInstance()->GetMousePos() -
		(m_pTarget->GetInfo().vPos + CScrollMgr::GetScroll());
	D3DXVec3Normalize(&vDir, &vDir); // 방향벡터 정규화
	fRadian = D3DXVec3Dot(&vDir, &m_pTarget->GetInfo().vLook);
	float fDegree = acosf(fRadian);

	/* 구르기 상태 아닐때만 Render */
	if (dynamic_cast<CPlayer*>(m_pTarget)->GetPlayerStance() != DODGE) {

		D3DXMATRIX matWorld, matScale, matRotZ, matTrans;

		if (CMouse::GetInstance()->GetMousePos().x - CScrollMgr::GetScroll().x < m_pTarget->GetInfo().vPos.x) {
			fScaleY *= -1.f;
			fpos *= -1.f;
		}

		if (m_pTarget->GetInfo().vPos.y < CMouse::GetInstance()->GetMousePos().y)
			fDegree *= -1;

		D3DXMatrixScaling(&matScale, 2.f, fScaleY, 1.f);
		D3DXMatrixTranslation(&matTrans, m_pTarget->GetInfo().vPos.x + CScrollMgr::GetScroll().x + fpos,
			m_pTarget->GetInfo().vPos.y + CScrollMgr::GetScroll().y + 5.f,
			m_pTarget->GetInfo().vPos.z);
		D3DXMatrixRotationZ(&matRotZ, -fDegree);

		matWorld = matScale * matRotZ * matTrans;

		/* 현재 플레이어 총 가져오기 */
		CObj* pPlayerGun = dynamic_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer())->GetCurGun();
		NULL_CHECK(pPlayerGun);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(pPlayerGun->GetObjKey().c_str(),
			pPlayerGun->GetSateKey().c_str(), 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX - fGunPos, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CWeaponMgr::AddWeapon(CObj * pObj)
{
	m_vecWeapon.push_back(pObj);
}
