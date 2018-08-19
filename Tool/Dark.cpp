#include "stdafx.h"
#include "Dark.h"
#include "ToolView.h"
IMPLEMENT_SINGLETON(CDark)

CDark::CDark()
{
}


CDark::~CDark()
{
	Release();
}

void CDark::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Terrain/Dark/%d.png", L"Terrain",
		TEX_MULTI, L"Dark", 1)))
	{
		AfxMessageBox(L"Dark Image Insert Failed");
		return;
	}
}

void CDark::Update()
{
}

void CDark::LateUpdate()
{
}

void CDark::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	for (size_t i = 0; i < m_vecDark.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			(m_vecDark[i]->vPos.x - m_pMainView->GetScrollPos(0))/*0: x축 스크롤 값*/,
			(m_vecDark[i]->vPos.y - m_pMainView->GetScrollPos(1))/*1: y축 스크롤 값*/,
			m_vecDark[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
			L"Terrain", L"Dark", m_vecDark[i]->byDrawID);

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(150, 255, 255, 255));
	}
}

void CDark::Release()
{
	for_each(m_vecDark.begin(), m_vecDark.end(), SafeDelete<INFO*>);
	m_vecDark.clear();
	m_vecDark.shrink_to_fit();
}

void CDark::AddDark(D3DXVECTOR3 & vPos, BYTE & RoomNum)
{
	INFO* pInfo = new INFO;

	pInfo->vPos = vPos;
	pInfo->byRoomNum = RoomNum;
	pInfo->byOption = 0;
	pInfo->byDrawID = 0;

	m_vecDark.push_back(pInfo);
}


