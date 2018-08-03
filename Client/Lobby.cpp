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
	return S_OK;
}

void CLobby::Update()
{
}


void CLobby::LateUpdate()
{
}

void CLobby::Render()
{
	CTileMgr::GetInstance()->Render();
}

void CLobby::Release()
{
}
