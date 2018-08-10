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
	vector<TILE*>& GetVecTile() { return m_vecTile; }
	int	GetTileIndex(const D3DXVECTOR3& vPos);
	bool Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	HRESULT LoadTile();
	
private:
	void ReadyAdjacency();

private:
	vector<TILE*>		m_vecTile;
	vector<TEXINFO*>	m_vecTileTexInfo;

	vector<list<TILE*>> m_vecAdjacency;
};

