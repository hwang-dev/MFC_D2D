#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

public:
	virtual const TEXINFO* GetTexture(const TCHAR* pStateKey = L"" /*��Ƽ �ؽ�ó�� ��� ���Ǵ� ����*/,
		const int& iIndex = 0 /*��Ƽ �ؽ�ó�� �̹��� ����*/) { return m_pTexInfo;	}

public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT InsertTexture(const TCHAR * pFilePath, 
		const TCHAR * pStateKey = L"", 
		const int & iCount = 0) override;
	virtual void Release() override;

private:
	TEXINFO*	m_pTexInfo;
};
