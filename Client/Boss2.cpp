#include "stdafx.h"
#include "Boss2.h"
#include "BossIMP.h"

// IMP
#include "BossNormalIMP.h"
#include "BossSkillIMP.h"
#include "BossHalfIMP.h"

#include "Effect.h"
#include "AnimEffect.h"

CBoss2::CBoss2()
{
}


CBoss2::~CBoss2()
{
	Release();
}

HRESULT CBoss2::Initialize()
{
	m_eObjectID = OBJ_MONSTER;
	m_eCurPattern = NORMAL;
	m_wstrObjKey = L"BMove";
	m_wstrStateKey = L"BDown";
	m_tInfo.vSize = { 70.f, 70.f, 0.f };
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
		m_wstrStateKey.c_str());
	m_iMonsterHp = 50;
	m_iCurHp = m_iMonsterHp;
	m_iAlpha = 255;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 30.f;
	m_fAttackTime = 0.2f;

	return S_OK;
}

void CBoss2::LateInit()
{
	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	// 처음 브릿지
	//m_pBridge = new CBossNormalIMP;
	m_pBridge = new CBossHalfIMP;
	m_pBridge->Initialize();
	
	m_pBridge->SetObj(this);
	//SetBridge(m_pBridge);
	
}

int CBoss2::Update()
{
	if (m_iMonsterHp < 0)
	{
		CObjMgr::GetInstance()->AddObject(CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(WINCX*0.5f + CScrollMgr::GetScroll().x, 
			WINCY*0.5f + CScrollMgr::GetScroll().y, 0.f), L"Book", { 0.f, 42.f })
			, OBJ_EFFECT);
		m_iMonsterHp = 0;
		return DEAD_OBJ;
	}

	PatternChange();

	// 행렬 계산
	CObj::LateInit();

	D3DXMATRIX matScale, matTrans;
	
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;


	return m_pBridge->Update();
}

void CBoss2::LateUpdate()
{
	CObj::LateInit();

	//방향 변경
	if (m_eCurPattern != SKILL)
	{

		m_tInfo.vDir = m_pTarget->GetInfo().vPos - m_tInfo.vPos;
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

		SetMonsterDir();
		m_wstrObjKey = L"BMove";
		MonsterDirChange();
	}
	m_fAttackTimer += CTimeMgr::GetInstance()->GetTime();



	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();
	if (m_tFrame.fFrame > m_tFrame.fMax) {
		m_tFrame.fFrame = 0.f;

	}
	m_pBridge->LateUpdate();
}

void CBoss2::Render()
{
	CObj::LateInit();

	// 렉트 업데이트
	UpdateRect();

	// 충돌 렉트
	if (g_bOnRect)
		RenderLine();

	// 보스 UI
	D3DXMATRIX matWorld, matScale, matTrans;
	
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 0.7f, 0.7f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		WINCX * 0.4f,
		(float)WINCY - 100.f,
		0.f);

	matWorld = matScale * matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI", L"Boss", 1);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	// HP Bar
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, (float)m_iMonsterHp / (float)m_iCurHp, 1.5f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		WINCX * 0.4f,
		(float)WINCY + 100.f,
		0.f);

	matWorld = matScale * matTrans;

	pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"UI", L"Boss", 0);

	NULL_CHECK(pTexInfo);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(0.f, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));



	m_pBridge->Render();
}

void CBoss2::Release()
{
	SafeDelete(m_pBridge);
}

void CBoss2::AstarMove()
{
}



void CBoss2::PatternChange()
{
	m_fPatternTime += CTimeMgr::GetInstance()->GetTime();

	if (m_fPatternTime > 5.f)
	{
		int iRandom = rand() % 3;
		m_eCurPattern = (PATTERN)iRandom;

		if (m_eCurPattern != m_ePrePattern)
		{
			SafeDelete(m_pBridge);

			switch (m_eCurPattern)
			{
			case NORMAL:
				//m_pBridge = new CBossNormalIMP;
				m_pBridge = new CBossHalfIMP;
				m_pBridge->Initialize();
				m_wstrObjKey = L"BMove";
				m_wstrStateKey = L"BDown";
				break;
			case HALF:
				m_pBridge = new CBossHalfIMP;
				m_pBridge->Initialize();
				m_wstrObjKey = L"BMove";
				m_wstrStateKey = L"BDown";
				break;
			case SKILL:
				m_pBridge = new CBossSkillIMP;
				m_pBridge->Initialize();
				m_wstrObjKey = L"Boss";
				m_wstrStateKey = L"BSkill";
				break;

			}
			m_pBridge->SetObj(this);
			m_ePrePattern = m_eCurPattern;
		}
		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str());
		m_fPatternTime = 0.f;
	}
}

