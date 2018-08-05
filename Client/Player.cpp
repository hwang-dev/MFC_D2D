#include "stdafx.h"
#include "Player.h"

/* Player IMP */
#include "PlayerIMP.h"
#include "PlayerMoveIMP.h"
#include "PlayerIdleIMP.h"
#include "PlayerDodgeIMP.h"

CPlayer::CPlayer()
	: m_pBridge(nullptr)
{
}


CPlayer::~CPlayer()
{
	SafeDelete(m_pBridge);
}

HRESULT CPlayer::Initialize()
{
	/* 처음 상태 */
	SafeDelete(m_pBridge);
	m_wstrObjKey = L"Idle";
	m_pBridge = new CPlayerIdleIMP;
	m_pBridge->SetStateKey(L"Down");
	m_pBridge->SetObj(this);

	return S_OK;
}

void CPlayer::LateInit()
{
}

int CPlayer::Update()
{
	PlayerMove();

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

	m_pBridge->Update();

	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	m_pBridge->LateUpdate();
}

void CPlayer::Render()
{
	CObj::UpdateRect();

	m_pBridge->Render();
}

void CPlayer::Release()
{
	SafeDelete(m_pBridge);
}

void CPlayer::PlayerMove()
{


	/* 상 */
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_W))
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"MOVE";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetStateKey(L"Up");
		m_pBridge->SetObj(this);
	}
	/* 하 */
	else if (CKeyMgr::GetInstance()->KeyPressing(KEY_S))
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"MOVE";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetStateKey(L"Down");
		m_pBridge->SetObj(this);
	}
	/* 좌 */
	else if (CKeyMgr::GetInstance()->KeyPressing(KEY_A))
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"MOVE";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetStateKey(L"Left");
		m_pBridge->SetObj(this);
	}
	else /* 우 */
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_D))
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"MOVE";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetStateKey(L"Right");
		m_pBridge->SetObj(this);
	}
}
