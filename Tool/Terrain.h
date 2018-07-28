#pragma once

class CToolView;
class CTerrain
{

	DECLARE_SINGLETON(CTerrain)

private:
	CTerrain();
	~CTerrain();


public:
	void Initialize();
	void Update();
	void Render();
	void MiniRender(float fRatio);
	void Release();

	void SetMainView(CToolView* pView) { m_pMainView = pView; }
	vector<TILE*>& GetVecTile() { return m_vecTile; }

public:
	void TileChange(const D3DXVECTOR3& vPos, const int& iDrawID);

private:
	int GetTileIndex(const D3DXVECTOR3& vPos);
	bool Picking(const D3DXVECTOR3& vPos, const int& iIndex);

private:
	vector<TILE*>	m_vecTile;
	CToolView*		m_pMainView;

};

