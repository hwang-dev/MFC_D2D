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
	float fpos = 20.f;
	float fScaleX = 1.5f;

	/* 총구 방향 조정 */
	if (m_pTarget->GetInfo().vPos.x + CScrollMgr::GetScroll().x > CMouse::GetInstance()->GetMousePos().x) {
		fpos *= -1;
		fScaleX *= -1;
	}

	/* 구르기 상태 아닐때만 Render */
	if(dynamic_cast<CPlayer*>(m_pTarget)->GetPlayerStance() != DODGE) {
	D3DXMATRIX matWorld, matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, fScaleX, 1.5f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_pTarget->GetInfo().vPos.x + CScrollMgr::GetScroll().x + fpos,
		m_pTarget->GetInfo().vPos.y + CScrollMgr::GetScroll().y + 5.f,
		m_pTarget->GetInfo().vPos.z);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));

	matWorld = matScale * matRotZ * matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Revolver", L"Stance", 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CWeaponMgr::AddWeapon(CObj * pObj)
{
	m_vecWeapon.push_back(pObj);
}
