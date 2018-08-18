#include "stdafx.h"
#include "Boss2.h"


CBoss2::CBoss2()
{
}


CBoss2::~CBoss2()
{
}

HRESULT CBoss2::Initialize()
{
	m_eObjectID = OBJ_MONSTER;
	m_wstrObjKey = L"BMove";
	m_wstrStateKey = L"BDown";
	m_tInfo.vSize = { 70.f, 70.f, 0.f };
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
		m_wstrStateKey.c_str());
	m_iMonsterHp = 50;
	m_iAlpha = 255;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 50.f;
	m_fAttackTime = 0.2f;

	return S_OK;
}

void CBoss2::LateInit()
{
	m_pTarget = CObjMgr::GetInstance()->GetPlayer();
}

int CBoss2::Update()
{
	// 행렬 계산
	LateInit();

	D3DXMATRIX matScale, matTrans;
	
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;


	return NO_EVENT;
}

void CBoss2::LateUpdate()
{
	SetMonsterDir();
	MonsterDirChange();

	// 방향 구하기
	m_tInfo.vDir = m_pTarget->GetInfo().vPos - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	// 이동
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::GetInstance()->GetTime();
	
	//
	m_fAttackTimer += CTimeMgr::GetInstance()->GetTime();
}

void CBoss2::Render()
{
	// 렉트
	UpdateRect();

	// 이미지 렌더
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey.c_str(),
		m_wstrStateKey.c_str(), 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

	if (g_bOnRect)
		RenderLine();
}

void CBoss2::Release()
{
}

void CBoss2::AstarMove()
{
}

void CBoss2::BossAttack()
{

}
