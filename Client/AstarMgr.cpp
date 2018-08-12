#include "stdafx.h"
#include "AstarMgr.h"

IMPLEMENT_SINGLETON(CAstarMgr)

CAstarMgr::CAstarMgr()
{
}


CAstarMgr::~CAstarMgr()
{
}

void CAstarMgr::StartAstar(const D3DXVECTOR3 & vStart, const D3DXVECTOR3 & vGoal)
{
	vector<TILE*>& vecTile = CTileMgr::GetInstance()->GetVecTile();

	for (auto& pTile : vecTile) {
		if (pTile->byOption == 1)
			continue;

		pTile->byDrawID = 0;
	}

	m_OpenLst.clear();
	m_CloseLst.clear();
	m_BestLst.clear();

	int iStartIdx = GetTileIndex(vStart);

	int iGoalIdx = GetTileIndex(vGoal);

	if (iStartIdx < 0 || iGoalIdx < 0)
		return;

	if (iStartIdx == iGoalIdx)
		return;

	if (vecTile[iGoalIdx]->byOption == 1)
		return;

	if (MakeRoute(iStartIdx, iGoalIdx) == true)
		MakeBestLst(iStartIdx, iGoalIdx); // 경로를 만든다.
}

bool CAstarMgr::MakeRoute(int iStartIdx, int iGoalIdx)
{
	vector<TILE*>& vecTile = CTileMgr::GetInstance()->GetVecTile();
	vector<list<TILE*>>& vecAdj = CTileMgr::GetInstance()->GetvecAdj();

	if (!m_OpenLst.empty())
		m_OpenLst.pop_front();

	// 현재 거쳐온 경로는 close에 보관.
	m_CloseLst.push_back(iStartIdx);

	for (auto& pTile : vecAdj[iStartIdx]) {
		if (iGoalIdx == pTile->iIndex) {
			pTile->iParentIdx = iStartIdx;
			return true; 
		}
		if (CheckOpenLst(pTile->iIndex) == false &&
			CheckCloseLst(pTile->iIndex) == false) {
			pTile->iParentIdx = iStartIdx;
			m_OpenLst.push_back(pTile->iIndex);
		}
	}

	m_OpenLst.sort([&vecTile, &iStartIdx, &iGoalIdx](int a, int b) {
		D3DXVECTOR3 vDir1 = vecTile[iGoalIdx]->vPos - vecTile[a]->vPos;
		D3DXVECTOR3 vDir2 = vecTile[iStartIdx]->vPos - vecTile[a]->vPos;

		D3DXVECTOR3 vDir3 = vecTile[iGoalIdx]->vPos - vecTile[b]->vPos;
		D3DXVECTOR3 vDir4 = vecTile[iStartIdx]->vPos - vecTile[b]->vPos;

		float fDistA = D3DXVec3Length(&vDir1) + D3DXVec3Length(&vDir2);
		float fDistB = D3DXVec3Length(&vDir3) + D3DXVec3Length(&vDir4);

		return fDistA < fDistB;
	});

	// 아무리 탐색해봐도 경로가 없을 때
	if (m_OpenLst.empty())
		return false; 

	return MakeRoute(m_OpenLst.front(), iGoalIdx);
}

void CAstarMgr::MakeBestLst(int iStartIdx, int iGoalIdx)
{
	vector<TILE*>& vecTile = CTileMgr::GetInstance()->GetVecTile();

	m_BestLst.push_front(vecTile[iGoalIdx]);

	vecTile[iGoalIdx]->byDrawID = 36;
	int iRouteIdx = vecTile[iGoalIdx]->iParentIdx;

	while (true) {
		if (iRouteIdx == iStartIdx)
			break;

		vecTile[iRouteIdx]->byDrawID = 36;
		m_BestLst.push_front(vecTile[iRouteIdx]);
		iRouteIdx = vecTile[iRouteIdx]->iParentIdx;
	}
}

int CAstarMgr::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	vector<TILE*>& vecTile = CTileMgr::GetInstance()->GetVecTile();

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		if (Picking(vPos, i))
			return i;
	}

	return -1;	// 인덱스 찾기 실패!
}

bool CAstarMgr::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	vector<TILE*>& vecTile = CTileMgr::GetInstance()->GetVecTile();

	D3DXVECTOR3 vPoint[4] = {
		D3DXVECTOR3(vecTile[iIndex]->vPos.x - (TILECX * 0.5f), vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(vecTile[iIndex]->vPos.x + (TILECX * 0.5f), vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(vecTile[iIndex]->vPos.x + (TILECX * 0.5f), vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(vecTile[iIndex]->vPos.x - (TILECX * 0.5f), vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f)
	};

	// 2. 시계 방향으로 방향 벡터를 구한다.
	D3DXVECTOR3 vDir[4] = {
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3],
	};

	// 3. 각 법선 벡터를 구한다.
	D3DXVECTOR3 vNormal[4] = {
		D3DXVECTOR3(-vDir[0].y, vDir[0].x, 0.f),
		D3DXVECTOR3(-vDir[1].y, vDir[1].x, 0.f),
		D3DXVECTOR3(-vDir[2].y, vDir[2].x, 0.f),
		D3DXVECTOR3(-vDir[3].y, vDir[3].x, 0.f),
	};

	// 4. 구한 법선 벡터들을 단위벡터로 만들어 준다.
	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	// 5. 각 꼭지점과 마우스 간의 방향벡터를 구한다.
	D3DXVECTOR3 vMouseDir[4] = {
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);

	for (int i = 0; i < 4; ++i) {
		// 하나라도 양수가 나오면 false
		if (0.f < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
			return false;
	}
	return true;
}

bool CAstarMgr::CheckOpenLst(int iIndex)
{
	for (int& iOpenIndex : m_OpenLst)
	{
		if (iIndex == iOpenIndex)
			return true;	// open에 존재함.
	}

	return false;
}

bool CAstarMgr::CheckCloseLst(int iIndex)
{
	for (int& iCloseIndex : m_CloseLst)
	{
		if (iIndex == iCloseIndex)
			return true;	// Close에 존재함.
	}

	return false;
}
