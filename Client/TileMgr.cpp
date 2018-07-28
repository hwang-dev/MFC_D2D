#include "stdafx.h"
#include "TileMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

HRESULT CTileMgr::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile%d.png", L"Terrain",
		TEX_MULTI, L"Tile", 59)))
	{
		ERR_MSG(L"Terrain Image Insert Failed");
		return E_FAIL;
	}

	if (FAILED(LoadTile()))
		return E_FAIL;

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


	float fScrollX = CScrollMgr::GetScrollX();
	float fScrollY = CScrollMgr::GetScrollY();

	int iCullX = -(int)fScrollX / TILECX;
	int iCullY = -(int)fScrollY / TILECY;

	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;

	for (int i = iCullY; i < iCullEndY + 3; ++i)
	{
		for (int j = iCullX; j < iCullEndX + 2; ++j)
		{
			int iIndex = j + (TILEX * i);

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixTranslation(&matTrans,
				(m_vecTile[iIndex]->vPos.x ) + fScrollX,
				(m_vecTile[iIndex]->vPos.y ) + fScrollY,
				m_vecTile[iIndex]->vPos.z);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
				L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);

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

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"Tile Load Failed!!");
		return E_FAIL;
	}

	Release();

	TILE tTile = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		TILE* pTile = new TILE(tTile);
		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
	return S_OK;
}
