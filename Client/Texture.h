#pragma once
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();

public:
	virtual const TEXINFO* GetTexture(const TCHAR* pStateKey = L"" /*멀티 텍스처일 경우 사용되는 인자*/,
		const int& iIndex = 0 /*멀티 텍스처의 이미지 인덱스 정보*/) PURE;

public:
	virtual HRESULT InsertTexture(const TCHAR* pFilePath /*이미지 경로*/,
		const TCHAR* pStateKey = L"" /*멀티 텍스처일 경우 사용되는 인자*/,
		const int& iCount = 0 /*멀티 텍스처의 이미지 개수*/) PURE;
	virtual void Release() PURE;
};

