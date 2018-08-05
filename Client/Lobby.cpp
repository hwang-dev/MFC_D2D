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
	// Tile �ҷ�����
	if (FAILED(CTileMgr::GetInstance()->LoadTile()))
	{
		return E_FAIL;
	}

	// Player ����
	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CPlayer>::CreateObj(D3DXVECTOR3{ WINCX * 0.5f, WINCY * 0.5, 0.f }),
		OBJ_PLAYER);

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