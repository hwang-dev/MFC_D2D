#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
	: m_pTexInfo(nullptr)
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::InsertTexture(const TCHAR * pFilePath, 
	const TCHAR * pStateKey /*= L""*/, 
	const int & iCount/* = 0*/)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	// D3DXGetImageInfoFromFile: 지정한 이미지 파일에 관한 정보를 D3DXIMAGE_INFO에게 기록해주는 함수.
	if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &m_pTexInfo->tImgInfo)))
	{
		ERR_MSG(pFilePath);
		SafeDelete(m_pTexInfo);
		return E_FAIL;
	}

	// D3DXIMAGE_INFO정보를 바탕으로 LPDIRECT3DTEXTURE9객체를 생성.
	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice() /*Texture Com객체 생성 주체*/,
		pFilePath /*이미지 경로*/,
		m_pTexInfo->tImgInfo.Width /*이미지의 가로 크기*/,
		m_pTexInfo->tImgInfo.Height /*이미지의 세로 크기*/,
		m_pTexInfo->tImgInfo.MipLevels /*mipmap을 사용하기 위한 가중치*/,
		0, /*생성한 텍스쳐를 사용하는 방식*/
		m_pTexInfo->tImgInfo.Format /*텍스쳐에 대한 픽셀 포맷*/,
		D3DPOOL_MANAGED /*Direct3D 자원들에 대해 어떤 메모리에 보관할 것인가에 대한 지정*/,
		D3DX_DEFAULT, D3DX_DEFAULT, 0, &m_pTexInfo->tImgInfo, nullptr, &m_pTexInfo->pTexture)))
	{
		ERR_MSG(L"Single Texture Load Failed!!!");
		SafeDelete(m_pTexInfo);
		return E_FAIL;
	}

	return S_OK;
}

void CSingleTexture::Release()
{
	// 순서 주의.
	m_pTexInfo->pTexture->Release(); // Com객체를 먼저 해제.
	SafeDelete(m_pTexInfo);
}
