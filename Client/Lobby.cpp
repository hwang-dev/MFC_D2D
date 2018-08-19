#include "stdafx.h"
#include "Lobby.h"

#include "Player.h"
#include "NormalMonster.h"
#include "Trigger.h"
#include "Boss2.h"
#include "Obstacle.h"
#include "Dark2.h"
CLobby::CLobby()
{
}


CLobby::~CLobby()
{
	Release();
}

HRESULT CLobby::Initialize()
{
	CSoundMgr::GetInstance()->PlayBGM(L"Lobby.wav");

	// Tile 불러오기
	if (FAILED(CTileMgr::GetInstance()->LoadTile())) {
		return E_FAIL;
	}
	// 인접 타일 검사(Astar)
	CTileMgr::GetInstance()->ReadyAdjacency();
	// SubTileMgr Load

	if (FAILED(CSubTileMgr::GetInstance()->LoadSubTile())) {
		ERR_MSG(L"SubTile Load Fail");
		return E_FAIL;
	}
	// Player 생성
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CPlayer>::CreateObj(D3DXVECTOR3{ 445.f, 360.f, 0.f }),
		OBJ_PLAYER);
	//	WeaponMgr Init
	if (FAILED(CWeaponMgr::GetInstance()->Initialize())) {
		ERR_MSG(L"WeaponMgr Init Fail");
		return E_FAIL;
	}
	// 트리거 불러오기
	CTrigger temp;
	if (FAILED(temp.LoadTrigger())) {
		return E_FAIL;
	}
	// 장애물 불러오기
	CObstacle temp2;
	if (FAILED(temp2.LoadObstacle())) {
		return E_FAIL;
	}

	CDark2 temp3;
	if (FAILED(temp3.LoadDark())) {
		return E_FAIL;
	}



	CRoomMgr::GetInstance()->Initialize();

	return S_OK;
}

void CLobby::Update()
{
	CTileMgr::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
	CMouse::GetInstance()->Update();
	CWeaponMgr::GetInstance()->Update();
	CRoomMgr::GetInstance()->Update();
	
}


void CLobby::LateUpdate()
{
	CScrollMgr::ScrollLock2();
	CTileMgr::GetInstance()->LateUpdate();
	CObjMgr::GetInstance()->LateUpdate();
	CMouse::GetInstance()->LateUpdate();
	CWeaponMgr::GetInstance()->LateUpdate();
}

void CLobby::Render()
{
	CTileMgr::GetInstance()->Render();
	CSubTileMgr::GetInstance()->Render();
	CWeaponMgr::GetInstance()->Render();
	CObjMgr::GetInstance()->Render();
	CMouse::GetInstance()->Render();

	// 미니맵
	CTileMgr::GetInstance()->MiniMapRender(0.05f);
}

void CLobby::Release()
{
}
