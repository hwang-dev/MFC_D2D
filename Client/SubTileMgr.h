#pragma once
class CSubTileMgr
{
	DECLARE_SINGLETON(CSubTileMgr)

private:
	CSubTileMgr();
	~CSubTileMgr();

public:
	HRESULT Initialize();
	HRESULT LoadSubTile();
	void Render();
	void Release();

private:
	vector<TILE*>		m_vecSubTile;
	vector<TEXINFO*>	m_vecSubTileTexInfo;
};

