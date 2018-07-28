#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

public:
	virtual const TEXINFO* GetTexture(const TCHAR* pStateKey = L"" /*멀티 텍스처일 경우 사용되는 인자*/,
		const int& iIndex = 0 /*멀티 텍스처의 이미지 개수*/) { return m_pTexInfo;	}

public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT InsertTexture(const TCHAR * pFilePath, 
		const TCHAR * pStateKey = L"", 
		const int & iCount = 0) override;
	virtual void Release() override;

private:
	TEXINFO*	m_pTexInfo;
};

