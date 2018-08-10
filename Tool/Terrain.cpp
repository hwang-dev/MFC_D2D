#include "stdafx.h"
#include "Terrain.h"
#include "ToolView.h"

IMPLEMENT_SINGLETON(CTerrain)

CTerrain::CTerrain()
	: m_pMainView(nullptr)
{
}


CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/TERRAIN/TILE/Tile%d.png", L"Terrain",
		TEX_MULTI, L"Tile", 59)))
	{
		AfxMessageBox(L"Terrain Image Insert Failed");
		return;
	}

	//for (int i = 0; i < TILEY; ++i)
	//{
	//	for (int j = 0; j < TILEX; ++j)
	//	{
	//		TILE* pTile = new TILE;

	//		float fX = float((j * (TILECX)) + TILECX);
	//		float fY = float((i * (TILECY)) + TILECY);

	//		pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
	//		pTile->vSize = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
	//		pTile->byOption = 0;
	//		pTile->byDrawID = 0;
	//		pTile->byRoomNum = 0;

	//		m_vecTile.push_back(pTile);
	//	}
	//}
}

void CTerrain::Update()
{
}

void CTerrain::Render()
{

	D3DXMATRIX matWorld, matScale, matTrans;
	TCHAR szIndex[MIN_STR] = L"";

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			(m_vecTile[i]->vPos.x - m_pMainView->GetScrollPos(0))/*0: x축 스크롤 값*/,
			(m_vecTile[i]->vPos.y - m_pMainView->GetScrollPos(1))/*1: y축 스크롤 값*/,
			m_vecTile[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
			L"Terrain", L"Tile", m_vecTile[i]->byDrawID);

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		// 폰트 출력
		swprintf_s(szIndex, L"%d", i);

		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
			szIndex, lstrlen(szIndex), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CTerrain::MiniRender(float fRatio)
{
	D3DXMATRIX matWorld, matScale, matTrans;
	

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, fRatio, fRatio, 0.f);
		D3DXMatrixTranslation(&matTrans,
			(m_vecTile[i]->vPos.x - m_pMainView->GetScrollPos(0)) * fRatio,
			(m_vecTile[i]->vPos.y - m_pMainView->GetScrollPos(1)) * fRatio,
			m_vecTile[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
			L"Terrain", L"Tile", m_vecTile[i]->byDrawID);

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		
	}
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}



void CTerrain::SetTile(int iTileX, int iTileY)
{
	for (int i = 0; i < iTileY; ++i)
	{
		for (int j = 0; j < iTileX; ++j)
		{
			TILE* pTile = new TILE;

			float fX = float((j * (TILECX) + (TILECX * 0.5f)));
			float fY = float((i * (TILECY) + (TILECY * 0.5f)));

			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
			pTile->byOption = 0;
			pTile->byDrawID = 0;
			pTile->byRoomNum = 0;

			m_vecTile.push_back(pTile);
		}
	}

}

void CTerrain::TileChange(const D3DXVECTOR3 & vPos, const int & iDrawID, const BYTE& byOption, const BYTE& byRoomNum)
{
	int iIndex = GetTileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID		= iDrawID;
	m_vecTile[iIndex]->byOption		= byOption;
	m_vecTile[iIndex]->byRoomNum	= byRoomNum;
}

int CTerrain::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (Picking(vPos, i))
			return i;
	}

	return -1;	// 인덱스 찾기 실패!
}

bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	// 내적을 이용한 픽킹

	// 1. 12시를 기준으로 시계 방향의 마름모 꼭지점을 구한다.
	D3DXVECTOR3 vPoint[4] = {
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f)
	};

	// 2. 시계 방향으로 방향 벡터를 구한다.
	D3DXVECTOR3 vDir[4] =
	{
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
