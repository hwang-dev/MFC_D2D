#include "stdafx.h"
#include "Player.h"

/* Player IMP */
#include "PlayerIMP.h"
#include "PlayerMoveIMP.h"
#include "PlayerIdleIMP.h"
#include "PlayerDodgeIMP.h"

/* Weapon */
#include "Revolver.h"
#include "ShotGun.h"

/* Bullet */
#include "NormalBullet.h"

/* UI */
#include "UI.h"
#include "MpUI.h"
#include "CkeyUI.h"
#include "MoneyUI.h"

/* Effect*/
#include "Effect.h"
#include "AnimEffect.h"


CPlayer::CPlayer()
	: m_ePlayerDir(DOWN),
	m_eCurStance(STANCE_END),
	m_ePreStance(STANCE_END),
	m_fAnimSpeed(0.f),
	m_fDodgePow(0.f),
	m_bIsDodge(false),
	m_fDodgeTime(0.f),
	m_pCurGun(nullptr)
{
	ZeroMemory(&m_tData, sizeof(DATA));
}


CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize()
{
	/* 최초 상태 */
	m_eObjectID = OBJ_PLAYER;
	m_eCurStance = IDLE;
	m_wstrObjKey = L"Idle";
	m_wstrStateKey = L"Down";
	m_tFrame.fMax = CTextureMgr::GetInstance()->GetTextureCount(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str()
	);

	/* 최초 설정 */
	m_tInfo.vSize = { 20.f, 30.f, 0.f };
	m_fAnimSpeed = 2.f;
	m_fSpeed = 150.f;
	m_fDodgePow = 2.f;
	m_tInfo.byRoomNum = 0;

	m_tData.iHp = 6;
	m_tData.iMp = 2;
	m_tData.iKey = 100;
	m_tData.iMoney = 100;
	/* 플레이어 기본 무기 */
	CWeaponMgr::GetInstance()->AddWeapon(CAbstractFactory<CRevolver>::CreateObj());
	CWeaponMgr::GetInstance()->AddWeapon(CAbstractFactory<CShotGun>::CreateObj());

	return S_OK;
}

void CPlayer::LateInit()
{
	/* 최초 무기*/
	m_pCurGun = CWeaponMgr::GetInstance()->GetVecWeapon().front();

	/* HP Observer */
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CUI>::CreateObj(), OBJ_UI);
	/* MP Observer */
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CMpUI>::CreateObj(), OBJ_UI);
	/* Key Observer */
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CkeyUI>::CreateObj(), OBJ_UI);
	/* Money Observer */
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CMoneyUI>::CreateObj(), OBJ_UI);
	CDataSubejct::GetInstance()->AddData(PLAYER_DATA, &m_tData);
	CDataSubejct::GetInstance()->Notify(PLAYER_DATA, &m_tData);
}

int CPlayer::Update()
{
	CObj::LateInit();
	PlayerMove();
	MakeStep();
	
	/* 플레이어 좌표 */
	D3DXMATRIX matScale, matRotZ, matTrnas;

	D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrnas,
		m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrnas;

	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	// 움직이지 않을때 방향 변경
	if(m_bIsMove == false) 
	{
		if ((CMouse::GetInstance()->GetMousePos().y + CScrollMgr::GetScroll().y) > m_tInfo.vPos.y &&
			(CMouse::GetInstance()->GetMousePos().x + CScrollMgr::GetScroll().x) > m_tInfo.vPos.x)

		{
			m_wstrStateKey = L"Down_Right";
		}
		if ((CMouse::GetInstance()->GetMousePos().y + CScrollMgr::GetScroll().y) > m_tInfo.vPos.y &&
			(CMouse::GetInstance()->GetMousePos().x + CScrollMgr::GetScroll().x) < m_tInfo.vPos.x)

		{
			m_wstrStateKey = L"Down_Left";
		}
		if ((CMouse::GetInstance()->GetMousePos().y + CScrollMgr::GetScroll().y) < m_tInfo.vPos.y &&
			(CMouse::GetInstance()->GetMousePos().x + CScrollMgr::GetScroll().x) < m_tInfo.vPos.x)

		{
			m_wstrStateKey = L"Up_Left";
		}
		if ((CMouse::GetInstance()->GetMousePos().y + CScrollMgr::GetScroll().y) < m_tInfo.vPos.y &&
			(CMouse::GetInstance()->GetMousePos().x + CScrollMgr::GetScroll().x) > m_tInfo.vPos.x)

		{
			m_wstrStateKey = L"Up_Right";
		}

	}
	//IsOffSet();
	StanceChange();
	ChangeWeapon();

	/* 플레이어 애니메이션 */
	PlayAnimation();
	PlayerDodge();

	if (m_eCurStance == MOVE)
	{
		if(m_fWalkSoundDelay > 0.2f)
		{
			CSoundMgr::GetInstance()->PlaySound(L"Walk.wav", CSoundMgr::EFFECT);
			m_fWalkSoundDelay = 0.f;
		}
	}
	m_fWalkSoundDelay += CTimeMgr::GetInstance()->GetTime();
}

void CPlayer::Render()
{
		UpdateRect();

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



	/* 플레이어 좌표 */
	/* 충돌 렉트 */
	if (g_bOnRect)
	{
		if (m_eCurStance != DODGE) {
		TCHAR szPos[MIN_STR] = L"";
		swprintf_s(szPos, L"%d, %d", (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y);
		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
			szPos, lstrlen(szPos), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));


		D3DXVECTOR2 vPoint[5] = {
			{ (m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f) - CScrollMgr::GetScroll().x, (m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f) - CScrollMgr::GetScroll().y },
			{ (m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f) - CScrollMgr::GetScroll().x, (m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f) - CScrollMgr::GetScroll().y },
			{ (m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f) - CScrollMgr::GetScroll().x, (m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f) - CScrollMgr::GetScroll().y },
			{ (m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f) - CScrollMgr::GetScroll().x, (m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f) - CScrollMgr::GetScroll().y },
			{ (m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f) - CScrollMgr::GetScroll().x, (m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f) - CScrollMgr::GetScroll().y },
		};

		CDevice::GetInstance()->GetLine()->SetWidth(1.f);

		CDevice::GetInstance()->GetSprite()->End();

		CDevice::GetInstance()->GetLine()->Begin();
		CDevice::GetInstance()->GetLine()->Draw(vPoint, 5, D3DCOLOR_ARGB(255, 255, 0, 0));
		CDevice::GetInstance()->GetLine()->End();

		CDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
		}
	}

}

void CPlayer::Release()
{
	SafeDelete(m_pCurGun);
}

void CPlayer::PlayerMove()
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_R)) {
		CSoundMgr::GetInstance()->PlaySound(L"Reload.wav", CSoundMgr::EFFECT);
		dynamic_cast<CWeapon*>(m_pCurGun)->WeaponReload();
	}

	if (!m_bIsDodge) {
		m_bIsMove = true;
		/* 섬광탄 */
		if (CKeyMgr::GetInstance()->KeyDown(KEY_SPACE)) {
			if (m_tData.iMp > 0) {
				CObjMgr::GetInstance()->GetBulletList().clear();
				--m_tData.iMp;
				CDataSubejct::GetInstance()->Notify(PLAYER_DATA, &m_tData);
			}
		}
		/* 공격 */
		if (CKeyMgr::GetInstance()->KeyPressing(KEY_LBUTTON)) {
			MakeBullet();
		}
		/* 좌상 */
		if (CKeyMgr::GetInstance()->KeyCombinePressing(KEY_W, KEY_A)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = UP_LEFT;
			m_wstrStateKey = L"Up_Left";
			m_tInfo.vPos += VECTOR3(-0.7f, -0.7f, 0.f) * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

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
			m_tInfo.vPos += VECTOR3(0.7f, -0.7f, 0.f) * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

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
			m_tInfo.vPos += VECTOR3(-0.7f, 0.7f, 0.f) * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

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
			m_tInfo.vPos += VECTOR3(0.7f, 0.7f, 0.f) * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

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
			m_tInfo.vPos += VECTOR3(0.f, -1.f, 0.f) * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
				//m_tData.iHp++;
				//CDataSubejct::GetInstance()->Notify(PLAYER_DATA, &m_tData);
			}
		}
		/* 하 */
		else if (CKeyMgr::GetInstance()->KeyPressing(KEY_S)) {
			m_eCurStance = MOVE;
			m_wstrObjKey = L"Move";
			m_ePlayerDir = DOWN;
			m_wstrStateKey = L"Down";
			m_tInfo.vPos += VECTOR3(0.f, 1.f, 0.f) * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

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
			m_tInfo.vPos += VECTOR3(-1.f, 0.f, 0.f) * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

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
			m_tInfo.vPos += VECTOR3(1.f, 0.f, 0.f) * m_fSpeed * CTimeMgr::GetInstance()->GetTime();

			/* 대쉬 */
			if (CKeyMgr::GetInstance()->KeyDown(KEY_RBUTTON)) {
				m_bIsDodge = true;
			}
		}
		else {
			m_bIsMove = false;
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
		CScrollMgr::SetScroll(-m_fSpeed * fTime * 1.5f, 0.f);
	}
	/* 좌 */
	if (float(m_tInfo.vPos.x + vScroll.x) < WINCX * 0.5f - 70.f) {
		CScrollMgr::SetScroll(m_fSpeed * fTime* 1.5f, 0.f);
	}
	/* 하 */
	if (float(m_tInfo.vPos.y + vScroll.y) > WINCY * 0.5f + 70.f) {
		CScrollMgr::SetScroll(0.f, -m_fSpeed * fTime * 1.5f);
	}
	/* 상 */
	if (float(m_tInfo.vPos.y + vScroll.y) < WINCY * 0.5f - 70.f) {
		CScrollMgr::SetScroll(0.f, m_fSpeed * fTime * 1.5f);
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
		CSoundMgr::GetInstance()->PlaySound(L"Dodge.wav", CSoundMgr::EFFECT);
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
		if (m_fDodgeTime > 0.4f) {
			m_fDodgeTime = 0.f;
			m_bIsDodge = false;
		}
	}
}

void CPlayer::MakeBullet()
{
	dynamic_cast<CWeapon*>(m_pCurGun)->CreateBullet();

}

void CPlayer::ChangeWeapon()
{
	//SafeDelete(m_pCurGun);
	vector<CObj*>& vecWeapon = CWeaponMgr::GetInstance()->GetVecWeapon();

	if (CKeyMgr::GetInstance()->KeyDown(KEY_1)) {
		m_pCurGun = vecWeapon[0];
	}
	else if (CKeyMgr::GetInstance()->KeyDown(KEY_2)) {
		m_pCurGun = vecWeapon[1];
	}
	else if (vecWeapon.size() == 3) {
		if (CKeyMgr::GetInstance()->KeyDown(KEY_3)) {
			m_pCurGun = vecWeapon[2];
		}
	}
}

void CPlayer::MakeStep()
{
	m_fStepTime += CTimeMgr::GetInstance()->GetTime();

	if (m_eCurStance == MOVE) {
		if (m_fStepTime > 0.7f) {
			CObj* pEffect = CEffectFactory<CEffect, CAnimEffect>::CreateEffect(
				D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 20.f, 0.f), L"Step", { 0.f, 7.f });
			CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);
			m_fStepTime = 0.f;
		}
	}
}


