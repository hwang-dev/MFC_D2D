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
	void MiniMapRender(float fRatio); // ¹Ì´Ï¸Ê
	void Release();

public:
	vector<TILE*>& GetVecTile() { return m_vecTile; }
	vector<list<TILE*>>& GetvecAdj() { return m_vecAdjacency; }

	int	GetTileIndex(const D3DXVECTOR3& vPos);
	bool Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	HRESULT LoadTile();
	
public:
	void ReadyAdjacency();

private:
	vector<TILE*>		m_vecTile;
	vector<TEXINFO*>	m_vecTileTexInfo;

	vector<list<TILE*>> m_vecAdjacency;
};

