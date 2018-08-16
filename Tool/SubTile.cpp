#include "stdafx.h"
#include "SubTile.h"
#include "ToolView.h"

IMPLEMENT_SINGLETON(CSubTile)

CSubTile::CSubTile()
	: m_pMainView(nullptr)
{
}


CSubTile::~CSubTile()
{
	Release();
}

void CSubTile::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Terrain/SubTile/SubTile%d.png", L"Terrain",
		TEX_MULTI, L"SubTile", 66)))
	{
		AfxMessageBox(L"SubTile Image Insert Failed");
		return;
	}
}

void CSubTile::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	for (size_t i = 0; i < m_vecSubTile.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			(m_vecSubTile[i]->vPos.x - m_pMainView->GetScrollPos(0))/*0: x축 스크롤 값*/,
			(m_vecSubTile[i]->vPos.y - m_pMainView->GetScrollPos(1))/*1: y축 스크롤 값*/,
			m_vecSubTile[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
			L"Terrain", L"SubTile", m_vecSubTile[i]->byDrawID);

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CSubTile::Release()
{
	for_each(m_vecSubTile.begin(), m_vecSubTile.end(), SafeDelete<TILE*>);
	m_vecSubTile.shrink_to_fit();
	m_vecSubTile.clear();
}

void CSubTile::AddSubTile(D3DXVECTOR3 & vPos, int& iDrawID)
{
	TILE* pTile = new TILE;

	pTile->vPos = vPos;
	pTile->byDrawID = iDrawID;
	pTile->byRoomNum = 0;
	pTile->byOption = 0;
	pTile->byMiniMap = 0;
	m_vecSubTile.push_back(pTile);
}
