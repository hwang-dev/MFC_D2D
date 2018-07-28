#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	HRESULT Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

};

