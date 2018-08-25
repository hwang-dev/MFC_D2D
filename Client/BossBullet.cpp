#include "stdafx.h"
#include "BossBullet.h"

#include "Effect.h"
#include "AnimEffect.h"

CBossBullet::CBossBullet()
{
}


CBossBullet::~CBossBullet()
{
}

HRESULT CBossBullet::Initialize()
{
	m_eObjectID = OBJ_BOSSBULLET;
	m_wstrObjKey = L"Bullet";
	m_wstrStateKey = L"MonsterBullet";

	m_fSpeed = 350.f;
	m_iBulletDamage = 1;
	m_tInfo.vSize = { 32.f, 32.f, 0.f };
	m_fVanishTime = 3.f;
	m_fAnimSpeed = 5.f;
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str()
	);
	return S_OK;
}

void CBossBullet::LateInit()
{
	m_tInfo.vDir = CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos
		- m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

int CBossBullet::Update()
{
	CObj::LateInit();

	if (m_bIsDead)
	{
		//CObj* pEffect = CEffectFactory<CEffect, CAnimEffect>::CreateEffect(
		//	m_tInfo.vPos, L"Step", { 0.f, 7.f });
		//CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);
		return DEAD_OBJ;
	}

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CBossBullet::LateUpdate()
{
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

	m_fVanishTimer += CTimeMgr::GetInstance()->GetTime();

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * m_fAnimSpeed;
	if (m_tFrame.fFrame > m_tFrame.fMax) {
		m_tFrame.fFrame = 0.f;
	}
}

void CBossBullet::Render()
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

	/* 충돌 렉트 렌더 */
	if (g_bOnRect)
		CObj::RenderLine();
}

void CBossBullet::Release()
{
}
