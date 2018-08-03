#pragma once
class CTileMgr
{
	DECLARE_SINGLETON(CTileMgr)

private:
	CTileMgr();
	~CTileMgr();

public:
	HRESULT Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
	HRESULT LoadTile();

private:
	vector<TILE*> m_vecTile;
};

