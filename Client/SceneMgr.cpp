#include "stdafx.h"
#include "SceneMgr.h"

#include "Lobby.h"
#include "Logo.h"
#include "Boss.h"
#include "Normal.h"
IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr),
	m_eCurScene(END),
	m_ePreScene(END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

HRESULT CSceneMgr::SceneChange(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_eCurScene != m_ePreScene)
	{
		SafeDelete(m_pScene);

		switch (m_eCurScene)
		{
		case LOGO:
			m_pScene = new CLogo;
			break;
		case LOBBY:
			m_pScene = new CLobby;
			break;
		case NORMAL:
			m_pScene = new CNormal;
			break;
		case BOSS:
			m_pScene = new CBoss;
			break;
		default:
			break;
		}

		m_ePreScene = m_eCurScene;
		return m_pScene->Initialize();
	}

	return S_OK;
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render()
{
	m_pScene->Render();
}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
}
