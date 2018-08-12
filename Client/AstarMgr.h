#pragma once
class CAstarMgr
{
	DECLARE_SINGLETON(CAstarMgr)

private:
	CAstarMgr();
	~CAstarMgr();

public:
	list<TILE*>& GetBestLst() { return m_BestLst; }

public:
	void StartAstar(const D3DXVECTOR3& vStart, const D3DXVECTOR3& vGoal);

private:
	bool MakeRoute(int iStartIdx, int iGoalIdx);
	void MakeBestLst(int iStartIdx, int iGoalIdx);
	int GetTileIndex(const D3DXVECTOR3& vPos);
	bool Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool CheckOpenLst(int iIndex);
	bool CheckCloseLst(int iIndex);

private:
	list<int>	m_OpenLst;
	list<int>	m_CloseLst;
	list<TILE*>	m_BestLst;
};

