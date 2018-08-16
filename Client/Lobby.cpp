#include "stdafx.h"
#include "Lobby.h"

#include "Player.h"
#include "NormalMonster.h"
#include "Trigger.h"
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
	// 
	CTrigger temp;
	if (FAILED(temp.LoadTrigger())) {
		E_FAIL;
	}

	// 임시 Monster 생성
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f - 300.f, WINCY * 0.5, 0.f }),
		OBJ_MONSTER);
	// 임시 Monster 생성
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f - 100.f, WINCY * 0.5 + 100.f, 0.f }),
		OBJ_MONSTER);
	// 임시 Monster 생성
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNormalMonster>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f - 200.f, WINCY * 0.5, 0.f }),
		OBJ_MONSTER);

	return S_OK;
}

void CLobby::Update()
{
	CTileMgr::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
	CMouse::GetInstance()->Update();
	CWeaponMgr::GetInstance()->Update();
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
