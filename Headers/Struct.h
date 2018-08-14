#pragma once

typedef struct tagTexture
{
	// LPDIRECT3DTEXTURE9: 이미지 한장을 제어할 Com객체
	LPDIRECT3DTEXTURE9	pTexture;

	// 이미지 정보를 보관하기 위한 구조체.
	D3DXIMAGE_INFO		tImgInfo;
}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;	// 타일의 중점.
	D3DXVECTOR3	vSize;	// 타일의 크기.
	BYTE byOption;		// 타일의 옵션.
	BYTE byDrawID;		// 렌더링 옵션.
	BYTE byRoomNum;		// 
	BYTE byMiniMap;

	int iIndex = 0;
	int iParentIdx = 0;

	BYTE& GetTileOption() { return byOption; }
	D3DXVECTOR3& GetTileSize() { return vSize; }
	D3DXVECTOR3& GetTilePos() { return vPos; }
}TILE;

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXMATRIX  matWorld;
	BYTE		byRoomNum;

	BYTE byOption;		// 타일의 옵션.
	BYTE byDrawID;		// 렌더링 옵션.
} INFO;

typedef struct tagTexturePath
{
	wstring wstrObjKey = L"";
	wstring wstrStateKey = L"";
	wstring wstrPath = L"";
	int iCount = 0;

} IMGPATH;

typedef struct tagFrame
{
	tagFrame()
		: fFrame(0.f), fMax(0.f)
	{}

	tagFrame(float frame, float max)
		: fFrame(frame), fMax(max)
	{}

	float fFrame; // 현재 애니메이션 재생 구간.
	float fMax;	// 최대 재생 길이.

} FRAME;