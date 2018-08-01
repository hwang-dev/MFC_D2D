#include "stdafx.h"
#include "SubTile.h"


CSubTile::CSubTile()
{
}


CSubTile::~CSubTile()
{
	Release();
}

void CSubTile::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/TERRAIN/SUBTILE/SubTile%d.png", L"Terrain",
		TEX_MULTI, L"SUBTILE", 64)))
	{
		AfxMessageBox(L"SubTile Image Insert Failed");
		return;
	}
}

void CSubTile::Render()
{
}

void CSubTile::Release()
{
	for_each(m_vecSubTile.begin(), m_vecSubTile.end(), SafeDelete<TILE*>);
	m_vecSubTile.shrink_to_fit();
	m_vecSubTile.clear();
}
