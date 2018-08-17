#include "stdafx.h"
#include "Lobby.h"

#include "Player.h"
#include "NormalMonster.h"
#include "Trigger.h"
#include "Boss2.h"

CLobby::CLobby()
{
}


CLobby::~CLobby()
{
	Release();
}

HRESULT CLobby::Initialize()
{
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
		E_FAIL;
	}
	// 
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CBoss2>::CreateObj(D3DXVECTOR3{ 445.f, 300.f, 0.f }),
		OBJ_MONSTER);

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
