#include "stdafx.h"
#include "NormalMonster.h"


CNormalMonster::CNormalMonster()
{
}


CNormalMonster::~CNormalMonster()
{
}

HRESULT CNormalMonster::Initialize()
{

	m_wstrObjKey = L"NMonsterMove";
	m_wstrStateKey = L"Down_Right";
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
		m_wstrStateKey.c_str());
	m_tInfo.vSize = { 10.f, 25.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 80.f;
	m_fAnimSpeed = 1.5f;
	return S_OK;
}

void CNormalMonster::LateInit()
{
	// 타겟 설정
	m_pTarget = CObjMgr::GetInstance()->GetPlayer();
	//m_tInfo.vDir = m_pTarget->GetInfo().vPos - m_tInfo.vPos;
	//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

}

int CNormalMonster::Update()
{
	LateInit();

	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y + CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;


	return NO_EVENT;
}

void CNormalMonster::LateUpdate()
{
	//m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

	/* 몬스터 이동(Astar) */
	AStarMove();
	
	/* 몬스터 방향 변경 */
	SetMonsterDir();
	MonsterDirChange();

	/* 몬스터 애니메이션 */
	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * m_fAnimSpeed;
	if (m_tFrame.fFrame > m_tFrame.fMax) {
		m_tFrame.fFrame = 0.f;
		CAstarMgr::GetInstance()->StartAstar(m_tInfo.vPos, m_pTarget->GetInfo().vPos);
	}
}

void CNormalMonster::Render()
{
	UpdateRect();

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (g_bOnRect)
		CObj::RenderLine();
}

void CNormalMonster::Release()
{
}

void CNormalMonster::AStarMove()
{
	list<TILE*>& BestLst = CAstarMgr::GetInstance()->GetBestLst();

	if (!BestLst.empty()) {
		D3DXVECTOR3 vDir = BestLst.front()->vPos - m_tInfo.vPos;

		float fDist = D3DXVec3Length(&vDir);
		D3DXVec3Normalize(&vDir, &vDir);

		m_tInfo.vPos += vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

		if (fDist < 5.f)
			BestLst.pop_front();
	}
}
