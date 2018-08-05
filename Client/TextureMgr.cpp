#include "stdafx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEXINFO* CTextureMgr::GetTexture(const TCHAR* pObjKey, const TCHAR* pStateKey, 
	const int & iIndex)
{
	// 우선 ObjKey로 CTexture를 탐색
	auto iter_find = find_if(m_MapTexture.begin(), m_MapTexture.end(),
		[&pObjKey](auto& MyPair)
	{
		return pObjKey == MyPair.first;
	});

	if (m_MapTexture.end() == iter_find)
		return nullptr;

	return iter_find->second->GetTexture(pStateKey, iIndex);
}

HRESULT CTextureMgr::ReadImgPath(const wstring & wstrPath)
{
	wifstream fin;

	TCHAR szObjKey[MAX_STR] = L"";
	TCHAR szStateKey[MAX_STR] = L"";
	TCHAR szCount[MIN_STR] = L"";
	TCHAR szPath[MAX_STR] = L"";

	fin.open(wstrPath);

	if (fin.fail())
	{
		ERR_MSG(L"ImgPath Load Fail");
		return E_FAIL;
	}

	while (true)
	{
		fin.getline(szObjKey, MAX_STR, '|');
		fin.getline(szStateKey, MAX_STR, '|');
		fin.getline(szCount, MIN_STR, '|');
		fin.getline(szPath, MAX_STR);

		if (fin.eof())
			break;

		int iCount = _ttoi(szCount);

		if (FAILED(InsertTexture(szPath, szObjKey, TEX_MULTI, szStateKey, iCount)))
		{
			fin.close();

			ERR_MSG(L"Multi Texture Load Failed");
			return E_FAIL;
		}
	}

	return S_OK;
}

HRESULT CTextureMgr::InsertTexture(const TCHAR * pFilePath, const TCHAR * pObjKey, TEXTYPE eType,
	const TCHAR * pStateKey, const int & iCount)
{
	// 우선 ObjKey로 CTexture를 탐색
	auto iter_find = find_if(m_MapTexture.begin(), m_MapTexture.end(),
		[&pObjKey](auto& MyPair)
	{
		return pObjKey == MyPair.first;
	});

	// 해당 ObjKey를 찾지 못하면 새로 삽입해주어야 한다.
	if (m_MapTexture.end() == iter_find)
	{
		CTexture* pTexture = nullptr;

		switch (eType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;
		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(pFilePath, pStateKey, iCount)))
		{
			ERR_MSG(pFilePath);
			SafeDelete(pTexture);
			return E_FAIL;
		}

		m_MapTexture.insert({ pObjKey, pTexture });
	}	
	else if (TEX_MULTI == eType)
		iter_find->second->InsertTexture(pFilePath, pStateKey, iCount);

	return S_OK;
}

void CTextureMgr::Release()
{
	for_each(m_MapTexture.begin(), m_MapTexture.end(),
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_MapTexture.clear();
}

float CTextureMgr::GetTextureCount(const TCHAR * pObjKey, const TCHAR * pStateKey)
{
	auto& iter_find = m_MapTexture.find(pObjKey);

	if (iter_find == m_MapTexture.end())
		return 0;

	return (float)dynamic_cast<CMultiTexture*>(iter_find->second)->GetFrameCount(pStateKey);
}
