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
	void TileChange(const D3DXVECTOR3& vPos, const int& iDrawID, const BYTE& byOption, const BYTE& byRoomNum);
	int GetTileIndex(const D3DXVECTOR3& vPos);
	D3DXVECTOR3& GetTilePos(int iIndex) { return m_vecTile[iIndex]->vPos; }

private:
	bool Picking(const D3DXVECTOR3& vPos, const int& iIndex);

private:
	vector<TILE*>	m_vecTile;
	CToolView*		m_pMainView;

};

