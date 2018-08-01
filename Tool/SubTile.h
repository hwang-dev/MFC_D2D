#pragma once

class ToolView;
class CSubTile
{
	DECLARE_SINGLETON(CSubTile)

private:
	CSubTile();
	~CSubTile();

public:
	void Initialize();
	void Render();
	void Release();

public:
	void SetMainView(CToolView* pView) { m_pMainView = pView; }
	void AddSubTile(D3DXVECTOR3& vPos, int& iDrawID);
	vector<TILE*>&	GetSubTile() { return m_vecSubTile; }

private:
	vector<TILE*>	m_vecSubTile;
	CToolView*		m_pMainView;
};

