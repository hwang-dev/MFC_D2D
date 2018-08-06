#include "stdafx.h"
#include "Player.h"

/* Player IMP */
#include "PlayerIMP.h"
#include "PlayerMoveIMP.h"
#include "PlayerIdleIMP.h"
#include "PlayerDodgeIMP.h"

CPlayer::CPlayer()
	: m_pBridge(nullptr),
	m_ePlayerDir(DOWN)
{
}


CPlayer::~CPlayer()
{
	SafeDelete(m_pBridge);
}

HRESULT CPlayer::Initialize()
{
	m_fSpeed = 150.f;

	return S_OK;
}

void CPlayer::LateInit()
{
}

int CPlayer::Update()
{
	PlayerMove();

	D3DXMATRIX matScale, matRotZ, matTrnas;

	D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrnas,
		m_tInfo.vPos.x + CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y + CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrnas;

	//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	m_pBridge->Update();

	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	IsOffSet();
	m_pBridge->LateUpdate();
	// 콘솔에 위치, 스크롤 출력
//#ifdef _DEBUG
//	system("cls");
//	cout << "Player X: " << m_tInfo.vPos.x << endl;
//	cout << "Player Y: " << m_tInfo.vPos.y << endl;
//	cout << endl;
//	cout << "Scroll X: " << CScrollMgr::GetScroll().x << endl;
//	cout << "Scroll Y: " << CScrollMgr::GetScroll().y << endl;
//	
//#endif // DEBUG
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
		m_pBridge->SetStateKey(L"Right");

		m_tInfo.vPos += D3DXVECTOR3(1.f, 0.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;
		m_ePlayerDir = RIGHT;
	}
	else
	{
		SafeDelete(m_pBridge);
		m_wstrObjKey = L"Idle";
		m_pBridge = new CPlayerMoveIMP;
		
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

void CPlayer::IsOffSet()
{
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();
	float fTime = CTimeMgr::GetInstance()->GetTime();

	/* 우 */
	if (float(m_tInfo.vPos.x + vScroll.x) > WINCX * 0.5f + 150.f) {
		CScrollMgr::SetScroll(-m_fSpeed * fTime, 0.f);
	}
	/* 좌 */
	if (float(m_tInfo.vPos.x + vScroll.x) < WINCX * 0.5f - 150.f) {
		CScrollMgr::SetScroll(m_fSpeed * fTime, 0.f);
	}
	/* 하 */
	if (float(m_tInfo.vPos.y + vScroll.y) > WINCY * 0.5f + 100.f) {
		CScrollMgr::SetScroll(0.f, -m_fSpeed * fTime);
	}
	/* 상 */
	if (float(m_tInfo.vPos.y + vScroll.y) < WINCY * 0.5f - 100.f) {
		CScrollMgr::SetScroll(0.f, m_fSpeed * fTime);
	}

}
