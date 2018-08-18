#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

HRESULT CLogo::Initialize()
{
	CSoundMgr::GetInstance()->PlaySound(L"Opening.wav", CSoundMgr::BGM);

	return S_OK;
}

void CLogo::Update()
{

}

void CLogo::LateUpdate()
{
	


	if (CKeyMgr::GetInstance()->KeyUp(KEY_LBUTTON))
	{
		CSoundMgr::GetInstance()->StopAll();
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::LOBBY);
	}
}

void CLogo::Render()
{
	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		WINCX * 0.5f,
		WINCY * 0.5f,
		0.f);
	
	matWorld = matScale * matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Main",
		L"Logo", 0);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	

}

void CLogo::Release()
{
}
