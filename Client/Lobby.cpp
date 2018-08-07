#include "stdafx.h"
#include "Lobby.h"

#include "Player.h"

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
	if (FAILED(CTileMgr::GetInstance()->LoadTile()))
	{
		return E_FAIL;
	}

	// Player 생성
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CPlayer>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f, WINCY * 0.5, 0.f }),
		OBJ_PLAYER);

	//	WeaponMgr Init
	if (FAILED(CWeaponMgr::GetInstance()->Initialize())) {
		ERR_MSG(L"WeaponMgr Init Fail");
		return E_FAIL;
	}

	return S_OK;
}

void CLobby::Update()
{
	CTileMgr::GetInstance()->Update();
	CMouse::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
}


void CLobby::LateUpdate()
{
	CTileMgr::GetInstance()->LateUpdate();
	CObjMgr::GetInstance()->LateUpdate();
	CWeaponMgr::GetInstance()->Render();
	//CScrollMgr::ScrollLock();
}

void CLobby::Render()
{
	CTileMgr::GetInstance()->Render();
	CMouse::GetInstance()->Render();
	CObjMgr::GetInstance()->Render();
}

void CLobby::Release()
{
}
