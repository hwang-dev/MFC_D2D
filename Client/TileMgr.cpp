#include "stdafx.h"
#include "TileMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)

CTileMgr::CTileMgr() {}

CTileMgr::~CTileMgr() { Release(); }

HRESULT CTileMgr::Initialize()
{
	/* Tile TexInfo Load */
	m_vecTileTexInfo = CTextureMgr::GetInstance()->GetVecTexInfo(L"Terrain", L"Tile");

	return S_OK;
}

void CTileMgr::Update()
{
}

void CTileMgr::LateUpdate()
{
}

void CTileMgr::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();

	int iCullX = -(int)vScroll.x / TILECX;
	int iCullY = -(int)vScroll.y / TILECY;

	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;

	for (int i = iCullY; i < iCullEndY + 3; ++i) {
		for (int j = iCullX; j < iCullEndX + 2; ++j) {

			int iIndex = j + (TILEY * i);

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans,
				(m_vecTile[iIndex]->vPos.x ) + CScrollMgr::GetScroll().x,
				(m_vecTile[iIndex]->vPos.y ) + CScrollMgr::GetScroll().y,
				m_vecTile[iIndex]->vPos.z);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			const TEXINFO* pTexInfo = m_vecTileTexInfo[m_vecTile[iIndex]->byDrawID];

			if (nullptr == pTexInfo)
				continue;

			float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

HRESULT CTileMgr::LoadTile()
{
	HANDLE hFile = CreateFile(L"../Data/TileData.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile) {
		ERR_MSG(L"Tile Load Failed!!");
		return E_FAIL;
	}

	Release();

	TILE tTile = {};
	DWORD dwByte = 0;

	while (true) {

		ReadFile(hFile, &tTile, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		TILE* pTile = new TILE(tTile);
		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
	return S_OK;
}

void CTileMgr::ReadyAdjacency()
{
	m_vecAdjacency.resize(m_vecTile.size());

	for (int i = 0; i < TILEY ; ++i) {
		for (int j = 0; j < TILEX; ++j) {

			int iIndex = j + (TILEX * i);

			/* 상 */
			if (iIndex - TILEX >= 0 &&
				m_vecTile[iIndex - TILEX]->byOption != 1) {
				m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex - TILEX]);
			}
			/* 하 */
			if (iIndex + TILEX < (int)m_vecTile.size() &&
				m_vecTile[iIndex + TILEX]->byOption != 1) {
				m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex + TILEX]);
			}
			/* 좌 */
			if (iIndex % TILEX != 0 &&
				m_vecTile[iIndex - 1]->byOption != 1) {
				m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex - 1]);
			}
			/* 우 */
			if (iIndex != (TILEX * (i + 1) - 1) &&
				m_vecTile[iIndex + 1]->byOption != 1) {
				m_vecAdjacency[iIndex].push_back(m_vecTile[iIndex + 1]);
			}
			
		}
	}
}

int CTileMgr::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i) {
		if (Picking(vPos, i)) {
			return i;
		}
	}
	return -1;
}

bool CTileMgr::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	D3DXVECTOR3 vPoint[4] = {
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f)
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
