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
	// m_pTarget : «√∑π¿ÃæÓ
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
	
	/* √—±∏πÊ«‚ = Mouse - Player */
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
			pPlayerGun->GetSateKey().c_str(), (int)pPlayerGun->GetFrame().fFrame);

		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX - 15.f, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	// UI ΩΩ∑‘ 
	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		WINCX - 100.f,
		WINCY - 50.f,
		0.f);

	matWorld = matScale * matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI", L"Slot", 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// UI ΩΩ∑‘ -> √—
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 3.f, 3.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		WINCX - 100.f,
		WINCY - 50.f,
		0.f);

	matWorld = matScale * matTrans;

	CObj* pPlayerGun = dynamic_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer())->GetCurGun();
	NULL_CHECK(pPlayerGun);

	pTexInfo = CTextureMgr::GetInstance()->GetTexture(pPlayerGun->GetObjKey().c_str(),
		pPlayerGun->GetSateKey().c_str(), (int)pPlayerGun->GetFrame().fFrame);

	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// √—æÀ ∞πºˆ
	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	//D3DXMatrixTranslation(&matTrans,
	//	WINCX - 100.f,
	//	WINCY - 50.f,
	//	0.f);

	//matWorld = matScale * matTrans;



	//NULL_CHECK(pTexInfo);

	//fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	//fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	//CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	//CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
	//	&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


}

void CWeaponMgr::LateUpdate()
{
	/* º±≈√µ» √—∏∏ LateUpdate */
	CObj* pPlayerGun = dynamic_cast<CPlayer*>(CObjMgr::GetInstance()->GetPlayer())->GetCurGun();
	pPlayerGun->LateUpdate();
}

void CWeaponMgr::AddWeapon(CObj * pObj)
{
	m_vecWeapon.push_back(pObj);
}
