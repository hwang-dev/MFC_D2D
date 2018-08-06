#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXINFO * CMultiTexture::GetTexture(const TCHAR * pStateKey/* = L""*/, const int & iIndex/* = 0*/)
{
	auto iter_find = find_if(m_MapMultiTex.begin(), m_MapMultiTex.end(),
		[&pStateKey](auto& MyPair)
	{
		return pStateKey == MyPair.first;
	});

	if(m_MapMultiTex.end() == iter_find)
		return nullptr;

	if ((size_t)iIndex < 0 || (size_t)iIndex >= iter_find->second.size())
		return nullptr;

	return iter_find->second[iIndex];
}

HRESULT CMultiTexture::InsertTexture(const TCHAR * pFilePath, const TCHAR * pStateKey/* = L""*/, 
	const int & iCount/* = 0*/)
{
	TCHAR szFullPath[MAX_PATH] = L"";

	for (int i = 0; i < iCount; ++i)
	{
		swprintf_s(szFullPath, pFilePath, i);

		TEXINFO* m_pTexInfo = new TEXINFO;
		ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

		// D3DXGetImageInfoFromFile: 지정한 이미지 파일에 관한 정보를 D3DXIMAGE_INFO에게 기록해주는 함수.
		if (FAILED(D3DXGetImageInfoFromFile(szFullPath, &m_pTexInfo->tImgInfo)))
		{
			ERR_MSG(szFullPath);
			SafeDelete(m_pTexInfo);
			return E_FAIL;
		}

		// D3DXIMAGE_INFO정보를 바탕으로 LPDIRECT3DTEXTURE9객체를 생성.
		if (FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice() /*Texture Com객체 생성 주체*/,
			szFullPath /*이미지 경로*/,
			m_pTexInfo->tImgInfo.Width /*이미지의 가로 크기*/,
			m_pTexInfo->tImgInfo.Height /*이미지의 세로 크기*/,
			m_pTexInfo->tImgInfo.MipLevels /*mipmap을 사용하기 위한 가중치*/,
			0, /*생성한 텍스쳐를 사용하는 방식*/
			m_pTexInfo->tImgInfo.Format /*텍스쳐에 대한 픽셀 포맷*/,
			D3DPOOL_MANAGED /*Direct3D 자원들에 대해 어떤 메모리에 보관할 것인가에 대한 지정*/,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, &m_pTexInfo->tImgInfo, nullptr, &m_pTexInfo->pTexture)))
		{
			ERR_MSG(L"Multi Texture Load Failed!!!");
			SafeDelete(m_pTexInfo);
			return E_FAIL;
		}

		m_MapMultiTex[pStateKey].push_back(m_pTexInfo);
	}

	return S_OK;
}

void CMultiTexture::Release()
{
	for (auto& MyPair : m_MapMultiTex)
	{
		for_each(MyPair.second.begin(), MyPair.second.end(),
			[](TEXINFO*& pTexInfo)
		{
			// 순서 주의.
			pTexInfo->pTexture->Release(); // Com객체를 먼저 해제.
			SafeDelete(pTexInfo);
		});

		MyPair.second.clear();
		MyPair.second.shrink_to_fit();
	}

	m_MapMultiTex.clear();	
}

int CMultiTexture::GetFrameCount(const TCHAR * pStateKey)
{
	auto& iter_find = m_MapMultiTex.find(pStateKey);

	// 없으면
	if (iter_find == m_MapMultiTex.end())
		return 0;

	// 있으면
	return iter_find->second.size();
}

vector<TEXINFO*>& CMultiTexture::GetVecTexInfo(const TCHAR * pStateKey)
{
	auto& iter_find = m_MapMultiTex.find(pStateKey);

	return iter_find->second;
}

