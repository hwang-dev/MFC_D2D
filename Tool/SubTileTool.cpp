// SubTileTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "SubTileTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"
// CSubTileTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSubTileTool, CDialog)

CSubTileTool::CSubTileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SUBTILETOOL, pParent),
	m_pImage(nullptr)
{

}

CSubTileTool::~CSubTileTool()
{
	Release();
}

void CSubTileTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE2, m_PictureCtrl);
	DDX_Control(pDX, IDC_LIST1, m_SubTileBox);
}


BEGIN_MESSAGE_MAP(CSubTileTool, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON5, &CSubTileTool::OnBnClickedSubTileListSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CSubTileTool::OnBnClickedSubTileListLoad)
	ON_LBN_SELCHANGE(IDC_LIST1, &CSubTileTool::OnLbnSelectSubTileBox)
END_MESSAGE_MAP()


// CSubTileTool 메시지 처리기입니다.


void CSubTileTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nID == SC_CLOSE)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bOnSubTileTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CSubTileTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);

	//m_TileBox.ResetContent();
	TCHAR szFilePath[MAX_STR] = L"";

	int iFileCnt = DragQueryFile(hDropInfo, -1, nullptr, 0);
	TCHAR szFileName[MAX_STR] = L"";

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_STR);

		CString strRelativePath = CFileInfo::ConvertRelativePath(szFilePath);

		CString strFileName = PathFindFileName(strRelativePath.GetString());

		lstrcpy(szFileName, strFileName.GetString());	// 상대 경로
		PathRemoveExtension(szFileName);	// 파일명

		strFileName = szFileName;

		auto iter_find = m_mapTilePath.find(strFileName);

		if (m_mapTilePath.end() == iter_find)
		{
			m_mapTilePath.insert({ strFileName, szFilePath });
			m_SubTileBox.AddString(szFileName);
		}
	}

	// 맵에 이미지 이름, 상대 경로 저장


	UpdateData(FALSE);


	CDialog::OnDropFiles(hDropInfo);
}


void CSubTileTool::Release()
{
	if (m_pImage)
	{
		m_pImage->Destroy();
		delete m_pImage;
		m_pImage = nullptr;
	}
}


void CSubTileTool::OnBnClickedSubTileListSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);

	CFileInfo::ConvertRelativePath(szPath);

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;
	if (IDOK == Dlg.DoModal())
	{
		CString strGetPath = Dlg.GetPathName();
		const TCHAR* pGetPath = strGetPath.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"TileList Save Failed!!");
			return;
		}

		DWORD dwByte = 0;

		for (auto& MyPair : m_mapTilePath)
		{
			const TCHAR* pKey = MyPair.first.GetString();
			int iKeyLength = MyPair.first.GetLength() + 1;
			const TCHAR* pPath = MyPair.second.GetString();
			int iPathLength = MyPair.second.GetLength() + 1;


			WriteFile(hFile, &iKeyLength, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, pKey, sizeof(TCHAR) * iKeyLength, &dwByte, nullptr);
			WriteFile(hFile, &iPathLength, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, pPath, sizeof(TCHAR) * iPathLength, &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

	AfxMessageBox(L"TileList Save Success");
	UpdateData(FALSE);
}


void CSubTileTool::OnBnClickedSubTileListLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HANDLE hFile = CreateFile(L"../Data/SubTileList.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		AfxMessageBox(L"TileList Load Failed!!");
		/*return;*/
	}

	int i = 0;

	DWORD dwByte = 0;
	TCHAR* pKey = L"";
	TCHAR* pPath = L"";
	int iLength = 0;

	while (true)
	{
		ReadFile(hFile, &iLength, sizeof(int), &dwByte, nullptr);
		pKey = new TCHAR[iLength];
		ReadFile(hFile, pKey, sizeof(TCHAR) * iLength, &dwByte, nullptr);

		ReadFile(hFile, &iLength, sizeof(int), &dwByte, nullptr);
		pPath = new TCHAR[iLength];
		ReadFile(hFile, pPath, sizeof(TCHAR) * iLength, &dwByte, nullptr);

		if (dwByte == 0)
		{
			delete pKey;
			pKey = nullptr;

			delete pPath;
			pPath = nullptr;

			break;
		}

		m_mapTilePath.insert({ pKey, pPath });
		m_SubTileBox.AddString(pKey);
	}
}


void CSubTileTool::OnLbnSelectSubTileBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iSelect = m_SubTileBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	CString strSelectName;
	m_SubTileBox.GetText(iSelect, strSelectName);


	// 이미지 띄우기
	auto& iter_find = m_mapTilePath.find(strSelectName);

	if (m_pImage)
	{
		m_pImage->Destroy();
		delete m_pImage;
		m_pImage = nullptr;
	}

	m_pImage = new CImage;
	m_pImage->Load(iter_find->second);
	m_PictureCtrl.SetBitmap(*m_pImage);

	// DrawID 변경
	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
	{
		if (0 != isdigit(strSelectName[i]))
			break;
	}

	strSelectName.Delete(0, i);
	m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);
}
