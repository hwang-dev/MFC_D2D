#pragma once

class CTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	CTextureMgr();
	~CTextureMgr();

public:
	HRESULT Initialize();
	const TEXINFO* GetTexture(const TCHAR* pObjKey, const TCHAR* pStateKey = L"" ,
		const int& iIndex = 0 );

public:
	HRESULT ReadImgPath(const wstring& wstrPath);
	HRESULT InsertTexture(const TCHAR* pFilePath , const TCHAR* pObjKey, TEXTYPE eType, 
		const TCHAR* pStateKey = L"" ,	const int& iCount = 0 );
	void Release();
	float GetTextureCount(const TCHAR* pObjKey, const TCHAR* pStateKey);
	
public:
	vector<TEXINFO*>& GetVecTexInfo(const TCHAR* pObjKey, const TCHAR* pStateKey);

private:
	map<wstring, CTexture*>		m_MapTexture;
};

