#include "stdafx.h"
#include "Boss2.h"
#include "BossIMP.h"

// IMP
#include "BossNormalIMP.h"
#include "BossSkillIMP.h"
#include "BossHalfIMP.h"

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
	m_pBridge = new CBossNormalIMP;
	m_pBridge->Initialize();
	
	m_pBridge->SetObj(this);
	//SetBridge(m_pBridge);
	
}

int CBoss2::Update()
{
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
		SetMonsterDir();
		MonsterDirChange();

		m_tInfo.vDir = m_pTarget->GetInfo().vPos - m_tInfo.vPos;
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();
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

	m_pBridge->Render();
}

void CBoss2::Release()
{
	SafeDelete(m_pBridge);
}

void CBoss2::AstarMove()
{
}

void CBoss2::BossAttack()
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
				m_pBridge = new CBossNormalIMP;
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

void CBoss2::PatternRandom()
{
}
