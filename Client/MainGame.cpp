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
	ShowCursor(false);

	// TImeMgr 초기화
	CTimeMgr::GetInstance()->InitTime();

	// Device 초기화
	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		ERR_MSG(L"Device Init Failed");
		return E_FAIL;
	}

	// Texture 불러오기
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
		return E_FAIL;

	////////////////////////////////////////////////////////////////////////////////////

	// SceneMgr
	if (FAILED(CSceneMgr::GetInstance()->SceneChange(CSceneMgr::LOBBY)))
	{
		ERR_MSG(L"Scene Change Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CMainGame::Update()
{
	// 시간 갱신은 Update 최상단에서 호출.
	CTimeMgr::GetInstance()->UpdateTime();

	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	CDevice::GetInstance()->Render_Begin();

	CSceneMgr::GetInstance()->Render();
	
	CDevice::GetInstance()->Render_End();
}

void CMainGame::Release()
{
	///// Manager Destory
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();

	CTileMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CMouse::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
}
