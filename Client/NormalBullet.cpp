#include "stdafx.h"
#include "NormalBullet.h"


CNormalBullet::CNormalBullet()
{
}


CNormalBullet::~CNormalBullet()
{
}

HRESULT CNormalBullet::Initialize()
{
	m_fSpeed = 10.f;
	m_iBulletDamage = 2;
	m_tInfo.vSize = { 5.f, 5.f, 0 };

	return S_OK;
}

void CNormalBullet::LateInit()
{
	// 총알 방향 = 마우스 - 플레이어
	m_tInfo.vDir = (CMouse::GetInstance()->GetMousePos() - CScrollMgr::GetScroll()) -
		CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

int CNormalBullet::Update()
{
	CObj::LateInit();

	/* 총알 이동 */
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

	/* 총알 행렬 연산 */
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vDir.x,
		m_tInfo.vDir.y,
		m_tInfo.vDir.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CNormalBullet::LateUpdate()
{
}

void CNormalBullet::Render()
{
	CObj::LateInit();

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		L"Bullet", L"Normal", 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DXCOLOR(255, 255, 255, 255));
}

void CNormalBullet::Release()
{
}
