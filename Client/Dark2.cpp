#include "stdafx.h"
#include "Dark2.h"


CDark2::CDark2()
{
}


CDark2::~CDark2()
{
}

HRESULT CDark2::Initialize()
{
	m_eObjectID = OBJ_DARK;
	return S_OK;
}

int CDark2::Update()
{
	return NO_EVENT;
}

void CDark2::LateUpdate()
{
}

void CDark2::Render()
{
	CObj::UpdateRect();


	D3DXVECTOR3 vPlayerPos = CObjMgr::GetInstance()->GetPlayer()->GetInfo().vPos;

	if (m_tInfo.vPos.x > (vPlayerPos.x - WINCX * 0.5f) - 100.f &&
		m_tInfo.vPos.x < (vPlayerPos.x + WINCX * 0.5f) + 100.f &&
		m_tInfo.vPos.y > (vPlayerPos.y - WINCY * 0.5f) - 100.f &&
		m_tInfo.vPos.y < (vPlayerPos.y + WINCY * 0.5f) + 100.f)
	{
		
	

	BYTE byPlayerRoom = CObjMgr::GetInstance()->GetPlayer()->GetInfo().byRoomNum;

	if (m_tInfo.byRoomNum == byPlayerRoom)
	{
		m_iAlpha = 100;
	}
	else
		m_iAlpha = 230;


	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScrollMgr::GetScroll().x,
		m_tInfo.vPos.y - CScrollMgr::GetScroll().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		L"Terrain",L"Dark", 0);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
	}
	if (g_bOnRect)
		RenderLine();
}

void CDark2::Release()
{
}

HRESULT CDark2::LoadDark()
{
	HANDLE hFile = CreateFile(L"../Data/DarkData.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		ERR_MSG(L"Data Load Failed!!");
		return E_FAIL;
	}

	Release();

	INFO tInfo = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		tInfo.vSize = { 36.f, 36.f ,36.f };
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CDark2>::CreateObj(tInfo), OBJ_DARK);

	}

	CloseHandle(hFile);
	return S_OK;
}
