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
	return S_OK;
}

void CTileMgr::Update()
{
}

void CTileMgr::LateUpdate()
{
	float fTime = CTimeMgr::GetInstance()->GetTime();

	if (CMouse::GetInstance()->GetMousePos().x < 0)
	{
		CScrollMgr::SetScroll(250.f * fTime, 0.f);
	}
	if (CMouse::GetInstance()->GetMousePos().x > WINCX)
	{
		CScrollMgr::SetScroll(-250.f * fTime, 0.f);
	}
	if (CMouse::GetInstance()->GetMousePos().y < 0)
	{
		CScrollMgr::SetScroll(0.f, 250.f * fTime);
	}
	if (CMouse::GetInstance()->GetMousePos().y > WINCY)
	{
		CScrollMgr::SetScroll(0, -250.f * fTime);
	}
}

void CTileMgr::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();

	int iCullX = -(int)vScroll.x / TILECX;
	int iCullY = -(int)vScroll.y / TILECY;

	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;

	for (int i = iCullY; i < iCullEndY + 3; ++i)
	{
		for (int j = iCullX; j < iCullEndX + 2; ++j)
		{
			int iIndex = j + (40 * i);

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
