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

public:
	HRESULT LoadTile();
	vector<TILE*>& GetVecTile() { return m_vecTile; }

private:
	vector<TILE*>		m_vecTile;
	vector<TEXINFO*>	m_vecTileTexInfo;
};

