#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENEID {LOGO, LOBBY, NORMAL, BOSS, END};

private:
	CSceneMgr();
	~CSceneMgr();

public:
	HRESULT SceneChange(SCENEID eID);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	CScene*		m_pScene;
	SCENEID		m_eCurScene;
	SCENEID		m_ePreScene;
};

