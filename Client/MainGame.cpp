#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize()
{
	CTimeMgr::GetInstance()->InitTime();

	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		ERR_MSG(L"Device Init Failed");
		return E_FAIL;
	}

	// Tile Init
	if (FAILED(CTileMgr::GetInstance()->Initialize()))
	{
		ERR_MSG(L"Tile Init Failed");
		return E_FAIL;
	}


	return S_OK;
}

void CMainGame::Update()
{
	// 시간 갱신은 Update 최상단에서 호출.
	CTimeMgr::GetInstance()->UpdateTime();
}

void CMainGame::LateUpdate()
{
	CTileMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	CDevice::GetInstance()->Render_Begin();

	CTileMgr::GetInstance()->Render();

	CDevice::GetInstance()->Render_End();
}

void CMainGame::Release()
{

	CTileMgr::GetInstance()->DestroyInstance();

	///// Manager Destory
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
}
