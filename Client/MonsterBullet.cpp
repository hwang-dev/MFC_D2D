#include "stdafx.h"
#include "MonsterBullet.h"


CMonsterBullet::CMonsterBullet()
{
}


CMonsterBullet::~CMonsterBullet()
{
}

HRESULT CMonsterBullet::Initialize()
{
	m_eObjectID = OBJ_MOSTERBULLET;
	m_wstrObjKey = L"Bullet";
	m_wstrStateKey = L"MonsterBullet";

	m_fSpeed = 300.f;
	m_iBulletDamage = 1;
	m_tInfo.vSize = { 16.f, 16.f, 16.f };
	m_fVanishTime = 5.f;
	m_fAnimSpeed = 3.f;
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str()
	);

	return S_OK;
}

void CMonsterBullet::LateInit()
{
	m_tInfo.vDir = CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos
		- m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

int CMonsterBullet::Update()
{
	CObj::LateInit();

	/* ¼Ò¸ê Á¶°Ç */
	if (m_fVanishTimer > m_fVanishTime)
		return DEAD_OBJ;



	/* */
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CMonsterBullet::LateUpdate()
{
	/* ÃÑ¾Ë ÀÌµ¿ */
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

	m_fVanishTime += CTimeMgr::GetInstance()->GetTime();
	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * m_fAnimSpeed;
	if (m_tFrame.fFrame > m_tFrame.fMax) {
		m_tFrame.fFrame = 0.f;
	}
}

void CMonsterBullet::Render()
{
	UpdateRect();
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DXCOLOR(255, 255, 255, 255));

	/* Ãæµ¹ ·ºÆ® ·»´õ */
	if (g_bOnRect)
		CObj::RenderLine();
}

void CMonsterBullet::Release()
{
}
