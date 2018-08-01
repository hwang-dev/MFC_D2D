#pragma once
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

private:
	vector<TILE*> m_vecSubTile;
};

