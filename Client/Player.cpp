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
	m_wstrObjKey = L"Idle";
	m_pBridge = new CPlayerIdleIMP;
	m_pBridge->SetStateKey(L"Down");
	m_pBridge->SetObj(this);

	m_fSpeed = 100.f;

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

	D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrnas,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrnas;

	///* 방향 벡터 구하기 */
	//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

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
		m_wstrObjKey = L"Move";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetObj(this);
		m_pBridge->SetStateKey(L"Up");
		
		m_tInfo.vPos += D3DXVECTOR3(0.f, -1.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;
		m_ePlayerDir = UP;
	}
	/* 하 */
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_S))
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"Move";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetObj(this);
		m_pBridge->SetStateKey(L"Down");

		m_tInfo.vPos += D3DXVECTOR3(0.f, 1.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;
		m_ePlayerDir = DOWN;
	}
	/* 좌 */
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_A))
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"Move";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetObj(this);
		m_pBridge->SetStateKey(L"Left");

		m_tInfo.vPos += D3DXVECTOR3(-1.f, 0.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;
		m_ePlayerDir = LEFT;
	}
	/* 우 */
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_D))
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"Move";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetObj(this);
		m_pBridge->SetStateKey(L"Right");

		m_tInfo.vPos += D3DXVECTOR3(1.f, 0.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

		m_ePlayerDir = RIGHT;
	}
	else
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"Idle";
		m_pBridge = new CPlayerMoveIMP;
		m_pBridge->SetObj(this);
		
		switch (m_ePlayerDir)
		{
		case UP:
			m_pBridge->SetStateKey(L"Up");
			break;
		case DOWN:
			m_pBridge->SetStateKey(L"Down");
			break;
		case RIGHT:
			m_pBridge->SetStateKey(L"Right");
			break;
		case LEFT:
			m_pBridge->SetStateKey(L"Left");
			break;
		default:
			break;
		}
		
	}
}
