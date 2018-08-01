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
}TILE;

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXMATRIX  matWorld;

	BYTE byOption;		// 타일의 옵션.
	BYTE byDrawID;		// 렌더링 옵션.
}INFO;

typedef struct tagTexturePath
{
	wstring wstrObjKey = L"";
	wstring wstrStateKey = L"";
	wstring wstrPath = L"";
	int iCount = 0;
}IMGPATH;