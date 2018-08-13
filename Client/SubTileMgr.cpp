#include "stdafx.h"
#include "SubTileMgr.h"

IMPLEMENT_SINGLETON(CSubTileMgr)

CSubTileMgr::CSubTileMgr()
{
}


CSubTileMgr::~CSubTileMgr()
{
	Release();
}

HRESULT CSubTileMgr::Initialize()
{
	m_vecSubTileTexInfo = CTextureMgr::GetInstance()->GetVecTexInfo(L"Terrain", L"SubTile");

	return S_OK;
}

HRESULT CSubTileMgr::LoadSubTile()
{
	HANDLE hFile = CreateFile(L"../Data/SubTileData.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile) {
		ERR_MSG(L"SubTile Load Failed!!");
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
		m_vecSubTile.push_back(pTile);
	}

	CloseHandle(hFile);
	return S_OK;
}

void CSubTileMgr::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();

	for (size_t i = 0; i < m_vecSubTile.size(); ++i) {

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			m_vecSubTile[i]->vPos.x - CScrollMgr::GetScroll().x,
			m_vecSubTile[i]->vPos.y - CScrollMgr::GetScroll().y,
			m_vecSubTile[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = m_vecSubTileTexInfo[m_vecSubTile[i]->byDrawID];

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CSubTileMgr::Release()
{
	for_each(m_vecSubTile.begin(), m_vecSubTile.end(), SafeDelete<TILE*>);
	m_vecSubTile.clear();
	m_vecSubTile.shrink_to_fit();
}
