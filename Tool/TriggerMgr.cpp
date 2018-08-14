#include "stdafx.h"
#include "TriggerMgr.h"

#include "ToolView.h"

IMPLEMENT_SINGLETON(CTriggerMgr)

CTriggerMgr::CTriggerMgr()
	: m_pMainView(nullptr)
{
}


CTriggerMgr::~CTriggerMgr()
{
	Release();
}

void CTriggerMgr::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Terrain/Trigger/%d.png", L"Terrain",
		TEX_MULTI, L"Trigger", 3)))
	{
		AfxMessageBox(L"Trigger Image Insert Failed");
		return;
	}
}

void CTriggerMgr::Update()
{
}

void CTriggerMgr::LateUpdate()
{
}

void CTriggerMgr::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	for (size_t i = 0; i < m_vecTrigger.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			(m_vecTrigger[i]->vPos.x - m_pMainView->GetScrollPos(0))/*0: x축 스크롤 값*/,
			(m_vecTrigger[i]->vPos.y - m_pMainView->GetScrollPos(1))/*1: y축 스크롤 값*/,
			m_vecTrigger[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
			L"Terrain", L"Trigger", m_vecTrigger[i]->byDrawID);

		if (nullptr == pTexInfo)
			continue;

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(150, 255, 255, 255));
	}
}

void CTriggerMgr::Release()
{
	for_each(m_vecTrigger.begin(), m_vecTrigger.end(), SafeDelete<INFO*>);
	m_vecTrigger.clear();
	m_vecTrigger.shrink_to_fit();
}

void CTriggerMgr::AddTrigger(D3DXVECTOR3 & vPos, BYTE & RoomNum)
{
	INFO* pInfo = new INFO;

	pInfo->vPos = vPos;
	pInfo->byRoomNum = RoomNum;
	pInfo->byOption = 0;
	pInfo->byDrawID = 2;

	m_vecTrigger.push_back(pInfo);
}
