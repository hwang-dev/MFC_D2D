// FilePath.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "FilePath.h"
#include "afxdialogex.h"
#include "FileInfo.h"

// CFilePath 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFilePath, CDialog)

CFilePath::CFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_FILEPATH, pParent)
{

}

CFilePath::~CFilePath()
{
	for_each(m_PathInfoLst.begin(), m_PathInfoLst.end(), SafeDelete<IMGPATH*>);
	m_PathInfoLst.clear();
}

void CFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListBox);
}


BEGIN_MESSAGE_MAP(CFilePath, CDialog)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CFilePath::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CFilePath::OnBnClickedLoad)
END_MESSAGE_MAP()


// CFilePath 메시지 처리기입니다.


void CFilePath::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE);

	int iCount = DragQueryFile(hDropInfo, -1, nullptr, 0);

	TCHAR szFullPath[MAX_STR] = L"";

	for (int i = 0; i < iCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, MAX_STR);
		CFileInfo::DirInfoExtraction(szFullPath, m_PathInfoLst);
	}

	m_ListBox.ResetContent();

	wstring wstrCombine = L"";
	TCHAR szCount[MIN_STR] = L"";

	for (auto& pImgPath : m_PathInfoLst)
	{
		// _itow_s: 정수 -> 문자열로 변환.
		_itow_s(pImgPath->iCount, szCount, 10); // 현재 10진수로 변환.


		wstrCombine = pImgPath->wstrObjKey + L"|" + pImgPath->wstrStateKey +
			L"|" + szCount + L"|" + pImgPath->wstrPath;

		m_ListBox.AddString(wstrCombine.c_str());
	}

	UpdateData(FALSE);
}


void CFilePath::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	wofstream fout;

	fout.open(L"../Data/ImgPath.txt");

	if (fout.fail())
	{
		AfxMessageBox(L"ImgPath Save Failed");
		return;
	}

	for (auto& pImgPath : m_PathInfoLst)
	{
		fout << pImgPath->wstrObjKey << L"|" << pImgPath->wstrStateKey << L"|"
			<< pImgPath->iCount << L"|" << pImgPath->wstrPath << endl;
	}

	fout.close();

	// WinExec: 윈도우의 기본 프로그램을 실행.
	WinExec("notepad.exe ../Data/ImgPath.txt", SW_SHOW);
}


void CFilePath::OnBnClickedLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//UpdateData(TRUE);

	//wifstream fin;

	//fin.open(L"../Data/ImgPath.txt");

	//if (fin.fail())
	//{
	//	AfxMessageBox(L"ImgPath Load Failed");
	//	return;
	//}

	//// 불러오기 전에 모든 정보를 리셋!
	//for_each(m_PathInfoLst.begin(), m_PathInfoLst.end(), SafeDelete<IMGPATH*>);
	//m_PathInfoLst.clear();

	//m_ListBox.ResetContent();

	//TCHAR szObjKey[MAX_STR] = L"";
	//TCHAR szStateKey[MAX_STR] = L"";
	//TCHAR szCount[MIN_STR] = L"";
	//TCHAR szPath[MAX_STR] = L"";

	//wstring strCombine = L"";

	//while (true)
	//{
	//	// 구분자('|') 단위로 끊어서 읽어들임.
	//	fin.getline(szObjKey, MAX_STR, '|');
	//	fin.getline(szStateKey, MAX_STR, '|');
	//	fin.getline(szCount, MIN_STR, '|');
	//	fin.getline(szPath, MAX_STR);

	//	// eof: 현재 지시자가 eof자리를 넘어서면 true 반환.
	//	if (fin.eof())
	//		break;

	//	strCombine = wstring(szObjKey) + L"|" + szStateKey + L"|" + szCount + L"|"
	//		+ szPath;

	//	m_ListBox.AddString(strCombine.c_str());

	//	IMGPATH* pImgPath = new IMGPATH;

	//	pImgPath->wstrObjKey = szObjKey;
	//	pImgPath->wstrStateKey = szStateKey;
	//	pImgPath->wstrPath = szPath;

	//	// _ttoi: 문자열 -> 정수로 변환.
	//	pImgPath->iCount = _ttoi(szCount);

	//	m_PathInfoLst.push_back(pImgPath);
	//}

	//UpdateData(FALSE);
}
