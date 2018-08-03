#include "stdafx.h"
#include "Lobby.h"


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

	return S_OK;
}

void CLobby::Update()
{
	CTileMgr::GetInstance()->Update();
	CMouse::GetInstance()->Update();
}


void CLobby::LateUpdate()
{
	CTileMgr::GetInstance()->LateUpdate();
}

void CLobby::Render()
{
	CTileMgr::GetInstance()->Render();
	CMouse::GetInstance()->Render();
}

void CLobby::Release()
{
}
