#pragma once
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString ConvertRelativePath(CString strFullPath);

	// 경로를 토대로 ObjectKey와 StateKey 등의 정보를 추출하는 함수.
	static void DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathInfoLst);

	// 현재 경로에 들어있는 이미지 파일의 개수를 반환.
	static int DirFileCount(const wstring& wstrPath);
};

