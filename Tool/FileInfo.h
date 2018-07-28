#pragma once
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString ConvertRelativePath(CString strFullPath);
};

