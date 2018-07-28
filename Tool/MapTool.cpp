// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "Terrain.h"

// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent), m_iDrawID(0)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TileBox);
	DDX_Control(pDX, IDC_PICTURE, m_PictureCtrl);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)

	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelectTileBox)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSaveTile)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBnClickedLoadTile)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::Release()
{
	for_each(m_MapImg.begin(), m_MapImg.end(),
		[](auto& MyPair)
	{
		MyPair.second->Destroy();
		SafeDelete(MyPair.second);
	});

	m_MapImg.clear();
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}








void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE);

	m_TileBox.ResetContent();
	TCHAR szFilePath[MAX_STR] = L"";

	int iFileCnt = DragQueryFile(hDropInfo, -1, nullptr, 0);
	TCHAR szFileName[MAX_STR] = L"";

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_STR);

		CString strRelativePath = CFileInfo::ConvertRelativePath(szFilePath);

		CString strFileName = PathFindFileName(strRelativePath.GetString());

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto iter_find = m_MapImg.find(strFileName);

		if (m_MapImg.end() == iter_find)
		{
			CImage* pImage = new CImage;
			pImage->Load(strRelativePath);

			m_MapImg.insert({ strFileName, pImage });
			m_TileBox.AddString(szFileName);
		}
	}

	UpdateData(FALSE);
}


void CMapTool::OnLbnSelectTileBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	int iSelect = m_TileBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	CString strSelectName;
	m_TileBox.GetText(iSelect, strSelectName);

	auto iter_find = m_MapImg.find(strSelectName);

	if (m_MapImg.end() == iter_find)
		return;

	m_PictureCtrl.SetBitmap(*(iter_find->second));

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


void CMapTool::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nID == SC_CLOSE)
	{
		CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMainFrame->m_MainSplit.GetPane(0, 1));

		pMainView->m_bIsMapTool = false;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CMapTool::OnBnClickedSaveTile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Tile Save Failed!!");
			return;
		}

		vector<TILE*>& vecTile = CTerrain::GetInstance()->GetVecTile();

		DWORD dwByte = 0;

		for (auto& pTile : vecTile)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CMapTool::OnBnClickedLoadTile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName().GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Tile Load Failed!!");
			return;
		}

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplit.GetPane(0, 1));
		

		CTerrain::GetInstance()->Release();
		vector<TILE*>& vecTile = CTerrain::GetInstance()->GetVecTile();

		TILE tTile = {};
		DWORD dwByte = 0;

		while (true)
		{
			ReadFile(hFile, &tTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			TILE* pTile = new TILE(tTile);
			vecTile.push_back(pTile);
		}

		CloseHandle(hFile);
		pMainView->Invalidate(FALSE);
	}

	UpdateData(FALSE);
}
