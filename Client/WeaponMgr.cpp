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
	D3DXMatrixIdentity(&m_matWolrd);
}


CWeaponMgr::~CWeaponMgr()
{
}

HRESULT CWeaponMgr::Initialize()
{
	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	return S_OK;
}

void CWeaponMgr::Update()
{
	float fpos = 12.f;
	m_fGunPos = 5.f;

	MATRIX matScale, matRotZ, matTrans;

	VECTOR3 vDir = (CMouse::GetInstance()->GetMousePos() + CScrollMgr::GetScroll())
		- m_pTarget->GetInfo().vPos;
	D3DXVec3Normalize(&vDir, &vDir); // 방향벡터 정규화
	m_fAngle = D3DXVec3Dot(&vDir, &m_pTarget->GetInfo().vLook);
	float fDegree = acosf(m_fAngle);


	/* 총구 방향 조정*/
	//if (CMouse::GetInstance()->GetMousePos().x < m_pTarget->GetInfo().vPos.x) {
	//	m_fScaleY *= -1.f;
	//	fpos *= -1.f;
	//}
	//if (m_pTarget->GetInfo().vPos.y < CMouse::GetInstance()->GetMousePos().y)
	//	fDegree *= -1;

	D3DXMatrixScaling(&matScale, 2.f, m_fScaleY, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_pTarget->GetInfo().vPos.x /*+ CScrollMgr::GetScroll().x*/,
		m_pTarget->GetInfo().vPos.y /*+ CScrollMgr::GetScroll().y*/,
		m_pTarget->GetInfo().vPos.z);
	D3DXMatrixRotationZ(&matRotZ, -fDegree);

	m_matWolrd = matScale * matRotZ * matTrans;
}


void CWeaponMgr::Render()
{
	/* 현재 플레이어 총 가져오기 */
	CObj* pPlayerGun = dynamic_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer())->GetCurGun();
	NULL_CHECK(pPlayerGun);

	if (dynamic_cast<CPlayer*>(m_pTarget)->GetPlayerStance() != DODGE) {
		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(pPlayerGun->GetObjKey().c_str(),
			pPlayerGun->GetSateKey().c_str(), 0);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWolrd);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		TCHAR szPos[MIN_STR] = L"";
		swprintf_s(szPos, L"%d, %d", (int)pPlayerGun->GetInfo().vPos.x, (int)pPlayerGun->GetInfo().vPos.y);
		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
			szPos, lstrlen(szPos), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

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
