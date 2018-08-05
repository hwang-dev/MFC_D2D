#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	: m_pBridge(nullptr)
{
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Initialize()
{
	return S_OK;
}

void CPlayer::LateInit()
{
}

int CPlayer::Update()
{
	// 플레이어 스크롤 적용
	m_tInfo.vPos += CScrollMgr::GetScroll();

	D3DXMATRIX matScale, matRotZ, matTrnas;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrnas,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrnas;


	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
}

void CPlayer::Render()
{
}

void CPlayer::Release()
{
}
