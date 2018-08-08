#include "stdafx.h"
#include "Player.h"

/* Player IMP */
#include "PlayerIMP.h"
#include "PlayerMoveIMP.h"
#include "PlayerIdleIMP.h"
#include "PlayerDodgeIMP.h"

/* Weapon */
#include "Revolver.h"

/* Bullet */
#include "NormalBullet.h"

CPlayer::CPlayer()
	: m_ePlayerDir(DOWN),
	m_eCurStance(STANCE_END),
	m_ePreStance(STANCE_END),
	m_wstrStateKey(L""),
	m_fAnimSpeed(0.f),
	m_fDodgePow(0.f),
	m_bIsDodge(false),
	m_fDodgeTime(0.f)
{
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Initialize()
{
	/* 처음 상태 */
	m_eCurStance = IDLE;
	m_wstrObjKey = L"Idle";
	m_wstrStateKey = L"Down";
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str()
	);

	/* 초기 설정 */
	m_fAnimSpeed = 2.f;
	m_fSpeed = 150.f;
	m_fDodgePow = 2.f;

	return S_OK;
}

void CPlayer::LateInit()
{
	/* 플레이어 기본 무기 */
	CWeaponMgr::GetInstance()->AddWeapon(CAbstractFactory<CRevolver>::CreateObj());
}

int CPlayer::Update()
{
	CObj::LateInit();
	PlayerMove();

	/* 플레이어 좌표 */
	D3DXMATRIX matScale, matRotZ, matTrnas;

	D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrnas,
		m_tInfo.vPos.x + CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y + CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrnas;

	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	IsOffSet();
	StanceChange();
}

void CPlayer::Render()
{
	CObj::UpdateRect();

	/* 플레이어 스프라이트*/
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	/* 플레이어 방향 벡터 */
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	/* 플레이어 애니메이션 */
	PlayAnimation();
	PlayerDodge();


	// 콘솔에 위치, 스크롤 출력
	//#ifdef _DEBUG
	//	system("cls");
	//	cout << "Player X: " << m_tInfo.vPos.x << endl;
	//	cout << "Player Y: " << m_tInfo.vPos.y << endl;
	//	cout << endl;
	//	cout << "Scroll X: " << CScrollMgr::GetScroll().x << endl;
	//	cout << "Scroll Y: " << CScrollMgr::GetScroll().y << endl;
	//	cout << endl;
	//	wcout << "ObjKey: " << m_wstrObjKey.c_str() << endl;
	//	wcout << "StateKey: " << m_wstrStateKey.c_str() << endl;
	//	cout << "Frame: " << m_tFrame.fFrame << endl;
	//	cout << "Max: " << m_tFrame.fMax << endl;
	//#endif // DEBUG
}

void CPlayer::Release()
{
}

void CPlayer::PlayerMove()
{
	if (!m_bIsDodge) {
		/* 공격 */
		if (CKeyMgr::GetInstance()->KeyDown(KEY_LBUTTON)) {
			MakeBullet();
		}
		/* 좌상 */
		if (CKeyMgr::GetInstance()->KeyCombinePressing(KEY_W, KEY_A)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = UP_LEFT;
			m_wstrStateKey = L"Up_Left";
			m_tInfo.vPos += D3DXVECTOR3(-0.7f, -0.7f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		/* 우상 */
		else if (CKeyMgr::GetInstance()->KeyCombinePressing(KEY_W, KEY_D)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = UP_RIGHT;
			m_wstrStateKey = L"Up_Right";
			m_tInfo.vPos += D3DXVECTOR3(0.7f, -0.7f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		/* 좌하 */
		else if (CKeyMgr::GetInstance()->KeyCombinePressing(KEY_A, KEY_S)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = DOWN_LEFT;
			m_wstrStateKey = L"Down_Left";
			m_tInfo.vPos += D3DXVECTOR3(-0.7f, 0.7f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		/* 우하 */
		else if (CKeyMgr::GetInstance()->KeyCombinePressing(KEY_S, KEY_D)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = DOWN_RIGHT;
			m_wstrStateKey = L"Down_Right";
			m_tInfo.vPos += D3DXVECTOR3(0.7f, 0.7f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		/* 상 */
		else if (CKeyMgr::GetInstance()->KeyPressing(KEY_W)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = UP;
			m_wstrStateKey = L"Up";
			m_tInfo.vPos += D3DXVECTOR3(0.f, -1.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		/* 하 */
		else if (CKeyMgr::GetInstance()->KeyPressing(KEY_S)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = DOWN;
			m_wstrStateKey = L"Down";
			m_tInfo.vPos += D3DXVECTOR3(0.f, 1.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		/* 좌 */
		else if (CKeyMgr::GetInstance()->KeyPressing(KEY_A)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = LEFT;
			m_wstrStateKey = L"Left";
			m_tInfo.vPos += D3DXVECTOR3(-1.f, 0.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		/* 우 */
		else if (CKeyMgr::GetInstance()->KeyPressing(KEY_D)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = RIGHT;
			m_wstrStateKey = L"Right";
			m_tInfo.vPos += D3DXVECTOR3(1.f, 0.f, 0.f) * CTimeMgr::GetInstance()->GetTime() * m_fSpeed;

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		else {
			m_eCurStance = IDLE;
			m_wstrObjKey = L"Idle";
			switch (m_ePlayerDir) {
			case UP:
				m_wstrStateKey = L"Up";
				break;
			case DOWN:
				m_wstrStateKey = L"Down";
				break;
			case RIGHT:
				m_wstrStateKey = L"Right";
				break;
			case LEFT:
				m_wstrStateKey = L"Left";
				break;
			case UP_LEFT:
				m_wstrStateKey = L"Up_Left";
				break;
			case UP_RIGHT:
				m_wstrStateKey = L"Up_Right";
				break;
			case DOWN_LEFT:
				m_wstrStateKey = L"Down_Left";
				break;
			case DOWN_RIGHT:
				m_wstrStateKey = L"Down_Right";
				break;
			default:
				break;
			}
		}
	}
}

void CPlayer::IsOffSet()
{
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();
	float fTime = CTimeMgr::GetInstance()->GetTime();

	/* 우 */
	if (float(m_tInfo.vPos.x + vScroll.x) > WINCX * 0.5f + 70.f) {
		CScrollMgr::SetScroll(-m_fSpeed * fTime, 0.f);
	}
	/* 좌 */
	if (float(m_tInfo.vPos.x + vScroll.x) < WINCX * 0.5f - 70.f) {
		CScrollMgr::SetScroll(m_fSpeed * fTime, 0.f);
	}
	/* 하 */
	if (float(m_tInfo.vPos.y + vScroll.y) > WINCY * 0.5f + 70.f) {
		CScrollMgr::SetScroll(0.f, -m_fSpeed * fTime);
	}
	/* 상 */
	if (float(m_tInfo.vPos.y + vScroll.y) < WINCY * 0.5f - 70.f) {
		CScrollMgr::SetScroll(0.f, m_fSpeed * fTime);
	}

}

void CPlayer::StanceChange()
{
	if (m_eCurStance != m_ePreStance) {
		switch (m_eCurStance) {
		case IDLE:
			m_wstrObjKey = L"Idle";
			break;
		case MOVE:
			m_wstrObjKey = L"Move";
			break;
		case DODGE:
			m_wstrObjKey = L"Dodge";
			break;
		default:
			break;
		}

		/* 상태 변경에 따른 애니메이션 초기화 */
		if (!DODGE) {
			m_tFrame.fFrame = 0.f;
		}
		m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str());
		m_ePreStance = m_eCurStance;
	}
}

void CPlayer::PlayAnimation()
{
	/* 상태에 따른 애니메이션 속도 조절 */
	if(m_bIsDodge) {
		m_fAnimSpeed = 2.f;
	}
	else {
		m_fAnimSpeed = 2.f;
	}

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * m_fAnimSpeed;
	if (m_tFrame.fFrame > m_tFrame.fMax) {
		m_tFrame.fFrame = 0.f;
	}
}

void CPlayer::PlayerDodge()
{
	if (m_bIsDodge) {
		m_eCurStance = DODGE;
		m_wstrObjKey = L"Dodge";

		D3DXVECTOR3 vDodge = {};

		switch (m_ePlayerDir)
		{
		case UP:
			vDodge = { 0.f, -1.f, 0.f };
			break;
		case RIGHT:
			vDodge = { 1.f, 0.f, 0.f };
			break;
		case LEFT:
			vDodge = { -1.f, 0.f, 0.f };
			break;
		case DOWN:
			vDodge = { 0.f, 1.f, 0.f };
			break;
		case UP_RIGHT:
			vDodge = { 0.7f, -0.7f, 0.f };
			break;
		case UP_LEFT:
			vDodge = { -0.7f, -0.7f, 0.f };
			break;
		case DOWN_RIGHT:
			vDodge = { 0.7f, 0.7f, 0.f };
			break;
		case DOWN_LEFT:
			vDodge = { -0.7f, 0.7f, 0.f };
			break;
		default:
			break;
		}

		m_tInfo.vPos += vDodge * CTimeMgr::GetInstance()->GetTime() * m_fSpeed * m_fDodgePow;
		m_fDodgeTime += CTimeMgr::GetInstance()->GetTime();

		/* 대쉬 종료 조건 */
		if (m_fDodgeTime > 0.3f) {
			m_fDodgeTime = 0.f;
			m_bIsDodge = false;
		}
	}
}

void CPlayer::MakeBullet()
{
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalBullet>::CreateObj(m_tInfo.vPos),
		OBJ_BULLET);
}
