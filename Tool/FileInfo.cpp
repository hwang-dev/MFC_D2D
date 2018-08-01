#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(CString strFullPath)
{
	TCHAR szRelativePath[MAX_STR] = L"";

	TCHAR szCurrentPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szCurrentPath);

	PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY,
		strFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}

void CFileInfo::DirInfoExtraction(const wstring & wstrPath, list<IMGPATH*>& rPathInfoLst)
{
	wstring wstrFilePath = wstrPath + L"\\*.*";

	// CFileFind: 파일 및 경로 제어에 관련된 기능들을 제공하는 MFC의 클래스.
	CFileFind	find;

	// 현재 경로에서 첫번째 파일을 탐색.
	find.FindFile(wstrFilePath.c_str());

	int iContinue = 1;

	while (iContinue)
	{
		// 동일 경로 안에서 다음 파일 탐색.
		iContinue = find.FindNextFile();

		// IsDots: 현재 찾은 파일이름이 .이나 ..인지 확인하는 함수. .이나 ..이라면 true를 반환.
		if (find.IsDots())
			continue;

		// IsDirectory: 찾은 이름이 파일명이 아닌 폴더명이라면 true를 반환.
		else if (find.IsDirectory())
		{
			// GetFilePath: 현재 find객체가 유지하고 있는 경로를 반환.
			DirInfoExtraction(wstring(find.GetFilePath()), rPathInfoLst); // 재귀 호출
		}
		else // find객체가 찾은게 파일명일 때
		{
			// 찾은 파일이 숨겨져있는 시스템 파일이라면 건너뛰어라!
			if (find.IsSystem())
				continue;

			IMGPATH* pImgPath = new IMGPATH;
			TCHAR szCurPath[MAX_STR] = L"";

			// \87기\Framework87\Texture\Stage\PLAYER\Attack\AKIHA_AKI01_000.png
			lstrcpy(szCurPath, find.GetFilePath().GetString());

			// 파일명과 확장자를 잘라낸다.
			// \87기\Framework87\Texture\Stage\PLAYER\Attack
			PathRemoveFileSpec(szCurPath);

			// 현재 폴더 내의 파일의 개수를 얻는다.
			pImgPath->iCount = DirFileCount(szCurPath);

			// GetFileTitle: 경로 상에서 온전히 파일명만 얻어오는 함수.
			// wstrTextureName = AKIHA_AKI01_000;
			wstring wstrTextureName = find.GetFileTitle().GetString();

			// substr(시작, 끝): 시작과 끝에 해당하는 문자열을 얻어오는 함수.
			// wstrTextureName = AKIHA_AKI01_00%d.png;
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.length() - 1) + L"%d.png";

			TCHAR szFullPath[MAX_STR] = L"";

			// PathCombine(dst, src1, src2): src1과 src2를 결합한 완성된 경로를 dst에 저장.
			// src1과 src2 사이에 \나 \\를 자동 삽입.
			// szFullPath: \87기\Framework87\Texture\Stage\PLAYER\Attack\AKIHA_AKI01_00%d.png;
			PathCombine(szFullPath, szCurPath, wstrTextureName.c_str());

			// 상대 경로 변환.
			// pImgPath->wstrPath: ..\Texture\Stage\PLAYER\Attack\AKIHA_AKI01_00%d.png;
			pImgPath->wstrPath = ConvertRelativePath(szFullPath);

			// PathFindFileName: 경로 상에 파일명을 찾거나 말단 폴더명을 찾는 함수.
			pImgPath->wstrStateKey = PathFindFileName(szCurPath);

			PathRemoveFileSpec(szCurPath);
			pImgPath->wstrObjKey = PathFindFileName(szCurPath);

			rPathInfoLst.push_back(pImgPath);
			iContinue = 0;
		}

	}
}

int CFileInfo::DirFileCount(const wstring & wstrPath)
{
	wstring wstrFilePath = wstrPath + L"\\*.*";

	CFileFind find;

	// 탐색 시작.
	find.FindFile(wstrFilePath.c_str());

	int iFileCnt = 0;
	int iContinue = 1;

	while (iContinue)
	{
		iContinue = find.FindNextFile();

		if (find.IsDots())
			continue;
		else if (find.IsDirectory())
			continue;
		else if (find.IsSystem())
			continue;

		++iFileCnt;
	}

	return iFileCnt;
}
