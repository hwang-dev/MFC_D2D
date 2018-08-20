#include "stdafx.h"
#include "BossBullet2.h"

#include "Effect.h"
#include "AnimEffect.h"
CBossBullet2::CBossBullet2()
{
}


CBossBullet2::~CBossBullet2()
{
	Release();
}

HRESULT CBossBullet2::Initialize()
{
	m_eObjectID = OBJ_MOSTERBULLET;
	m_wstrObjKey = L"Bullet";
	m_wstrStateKey = L"MonsterBullet";

	m_fSpeed = 200.f;
	m_iBulletDamage = 1;
	m_tInfo.vSize = { 32.f, 32.f, 0.f };
	m_fVanishTime = 3.f;
	m_fAnimSpeed = 5.f;
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str()
	);

	return S_OK;
}

void CBossBullet2::LateInit()
{
}

int CBossBullet2::Update()
{
	CObj::LateInit();

	if (m_fVanishTimer > m_fVanishTime || m_bIsDead)
	{
		CObj* pEffect = CEffectFactory<CEffect, CAnimEffect>::CreateEffect(
			m_tInfo.vPos, L"Step", { 0.f, 7.f });
		CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);
		return DEAD_OBJ;
	}

	D3DXMATRIX matScale, matTrans, matRot;

	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = matScale * matRot * matTrans;

	D3DXVECTOR3 vLook = CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
	D3DXVec3Normalize(&vLook, &vLook);

	D3DXVec3TransformNormal(&m_tInfo.vDir, &vLook, &m_tInfo.matWorld);

	return NO_EVENT;
}

void CBossBullet2::LateUpdate()
{
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

	m_fVanishTimer += CTimeMgr::GetInstance()->GetTime();

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * m_fAnimSpeed;
	if (m_tFrame.fFrame > m_tFrame.fMax) {
		m_tFrame.fFrame = 0.f;
	}
}

void CBossBullet2::Render()
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

void CBossBullet2::Release()
{
}
