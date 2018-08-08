#include "stdafx.h"
#include "NormalBullet.h"


CNormalBullet::CNormalBullet()
{
}


CNormalBullet::~CNormalBullet()
{
	Release();
}

HRESULT CNormalBullet::Initialize()
{
	m_fSpeed = 200.f;
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
		m_tInfo.vPos.x + CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y + CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;


	/* 화면 밖으로 나가면 소멸*/
	if (m_tInfo.vPos.x < (0.f - CScrollMgr::GetScroll().x) ||
		m_tInfo.vPos.x >float(WINCX - CScrollMgr::GetScroll().x) ||
		m_tInfo.vPos.y < (0.f - CScrollMgr::GetScroll().y) ||
		m_tInfo.vPos.y >float(WINCY - CScrollMgr::GetScroll().y)) {
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CNormalBullet::LateUpdate()
{
}

void CNormalBullet::Render()
{
	CObj::UpdateRect();

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
