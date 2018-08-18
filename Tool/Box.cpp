#include "stdafx.h"
#include "Box.h"

#include "ToolView.h"

IMPLEMENT_SINGLETON(CBox)

CBox::CBox()
{
}


CBox::~CBox()
{
	Release();
}

void CBox::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Terrain/Box/%d.png", L"Terrain",
		TEX_MULTI, L"Box", 1)))
	{
		AfxMessageBox(L"Box Image Insert Failed");
		return;
	}
}

void CBox::Update()
{
}

void CBox::LateUpdate()
{
}

void CBox::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	for (size_t i = 0; i < m_vecBox.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			(m_vecBox[i]->vPos.x - m_pMainView->GetScrollPos(0))/*0: x축 스크롤 값*/,
			(m_vecBox[i]->vPos.y - m_pMainView->GetScrollPos(1))/*1: y축 스크롤 값*/,
			m_vecBox[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
			L"Terrain", L"Box", m_vecBox[i]->byDrawID);

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(200, 255, 255, 255));
	}
}

void CBox::Release()
{
	for_each(m_vecBox.begin(), m_vecBox.end(), SafeDelete<INFO*>);
	m_vecBox.clear();
	m_vecBox.shrink_to_fit();
}

void CBox::AddTrigger(D3DXVECTOR3 & vPos)
{
	INFO* pInfo = new INFO;

	pInfo->vPos = vPos;
	pInfo->byRoomNum = 0;
	pInfo->vSize = { 36.f, 36.f, 0.f };
	pInfo->byDrawID = 0;

	m_vecBox.push_back(pInfo);

}
